#
# This file is part of LiteX.
#
# This file is Copyright (c) 2014-2020 Florent Kermarrec <florent@enjoy-digital.fr>
# This file is Copyright (c) 2013-2014 Sebastien Bourdeauducq <sb@m-labs.hk>
# This file is Copyright (c) 2019 Gabriel L. Somlo <somlo@cmu.edu>
# SPDX-License-Identifier: BSD-2-Clause

import logging
import time
import datetime
from math import log2, ceil

from migen import *

from litex.soc.cores import cpu
from litex.soc.cores.identifier import Identifier
from litex.soc.cores.timer import Timer
from litex.soc.cores.spi_flash import SpiFlash
from litex.soc.cores.spi import SPIMaster

from litex.soc.interconnect.csr import *
from litex.soc.interconnect import csr_bus
from litex.soc.interconnect import stream
from litex.soc.interconnect import wishbone
from litex.soc.interconnect import axi
from litex.soc.integration.soc import *

logging.basicConfig(level=logging.INFO)

class RvpldSoC(SoC):
    # Add Identifier -------------------------------------------------------------------------------
    def add_identifier(self, name="identifier", identifier="rvpld SoC", with_build_time=True):
        self.check_if_exists(name)
        if with_build_time:
            identifier += " " + build_time()
        setattr(self.submodules, name, Identifier(identifier))
        self.csr.add(name + "_mem", use_loc_if_exists=True)

    # Add UART -------------------------------------------------------------------------------------
    def add_uart(self, name, baudrate=115200, fifo_depth=16):
        from litex.soc.cores import uart

        # Stub / Stream
        if name in ["stub", "stream"]:
            self.submodules.uart = uart.UART(tx_fifo_depth=0, rx_fifo_depth=0)
            if name == "stub":
                self.comb += self.uart.sink.ready.eq(1)

        # UARTBone / Bridge
        elif name in ["uartbone", "bridge"]:
            self.add_uartbone(baudrate=baudrate)

        # Crossover
        elif name in ["crossover"]:
            self.submodules.uart = uart.UARTCrossover()

        # Model/Sim
        elif name in ["model", "sim"]:
            self.submodules.uart_phy = uart.RS232PHYModel(self.platform.request("serial"))
            self.submodules.uart = ResetInserter()(uart.UART(self.uart_phy,
                tx_fifo_depth = fifo_depth,
                rx_fifo_depth = fifo_depth))

        # JTAG Atlantic
        elif name in ["jtag_atlantic"]:
            from litex.soc.cores.jtag import JTAGAtlantic
            self.submodules.uart_phy = JTAGAtlantic()
            self.submodules.uart = ResetInserter()(uart.UART(self.uart_phy,
                tx_fifo_depth = fifo_depth,
                rx_fifo_depth = fifo_depth))

        # JTAG UART
        elif name in ["jtag_uart"]:
            from litex.soc.cores.jtag import JTAGPHY
            self.submodules.uart_phy = JTAGPHY(device=self.platform.device)
            self.submodules.uart = ResetInserter()(uart.UART(self.uart_phy,
                tx_fifo_depth = fifo_depth,
                rx_fifo_depth = fifo_depth))

        # USB ACM (with ValentyUSB core)
        elif name in ["usb_acm"]:
            import valentyusb.usbcore.io as usbio
            import valentyusb.usbcore.cpu.cdc_eptri as cdc_eptri
            usb_pads = self.platform.request("usb")
            usb_iobuf = usbio.IoBuf(usb_pads.d_p, usb_pads.d_n, usb_pads.pullup)
            self.submodules.uart = cdc_eptri.CDCUsb(usb_iobuf)

        # Classic UART
        else:
            self.submodules.uart_phy = uart.UARTPHY(
                pads     = self.platform.request(name),
                clk_freq = self.sys_clk_freq,
                baudrate = baudrate)
            self.submodules.uart = ResetInserter()(uart.UART(self.uart_phy,
                tx_fifo_depth = fifo_depth,
                rx_fifo_depth = fifo_depth))

        self.csr.add("uart_phy", use_loc_if_exists=True)
        self.csr.add("uart", use_loc_if_exists=True)
        if hasattr(self.cpu, "interrupt"):
            self.irq.add("uart", use_loc_if_exists=True)
        else:
            self.add_constant("UART_POLLING")

    # Add UARTbone ---------------------------------------------------------------------------------
    def add_uartbone(self, name="serial", clk_freq=None, baudrate=115200, cd="sys"):
        from litex.soc.cores import uart
        self.submodules.uartbone = uart.UARTBone(
            pads     = self.platform.request(name),
            clk_freq = clk_freq if clk_freq is not None else self.sys_clk_freq,
            baudrate = baudrate,
            cd       = cd)
        self.bus.add_master(name="uartbone", master=self.uartbone.wishbone)

    # Add SDRAM ------------------------------------------------------------------------------------
    def add_sdram(self, name, phy, module, origin, size=None, with_soc_interconnect=True,
        l2_cache_size           = 8192,
        l2_cache_min_data_width = 128,
        l2_cache_reverse        = True,
        l2_cache_full_memory_we = True,
        expose_axi = True,
        **kwargs):

        # Imports
        from litedram.common import LiteDRAMNativePort
        from litedram.core import LiteDRAMCore
        from litedram.frontend.wishbone import LiteDRAMWishbone2Native
        from litedram.frontend.axi import LiteDRAMAXI2Native

        # LiteDRAM core
        self.submodules.sdram = LiteDRAMCore(
            phy             = phy,
            geom_settings   = module.geom_settings,
            timing_settings = module.timing_settings,
            clk_freq        = self.sys_clk_freq,
            **kwargs)
        self.csr.add("sdram", use_loc_if_exists=True)

        # Save SPD data to be able to verify it at runtime
        if hasattr(module, "_spd_data"):
            # pack the data into words of bus width
            bytes_per_word = self.bus.data_width // 8
            mem = [0] * ceil(len(module._spd_data) / bytes_per_word)
            for i in range(len(mem)):
                for offset in range(bytes_per_word):
                    mem[i] <<= 8
                    if self.cpu.endianness == "little":
                        offset = bytes_per_word - 1 - offset
                    spd_byte = i * bytes_per_word + offset
                    if spd_byte < len(module._spd_data):
                        mem[i] |= module._spd_data[spd_byte]
            self.add_rom(
                name     = "spd",
                origin   = self.mem_map.get("spd", None),
                size     = len(module._spd_data),
                contents = mem,
            )

        if not with_soc_interconnect: return

        # Compute/Check SDRAM size
        sdram_size = 2**(module.geom_settings.bankbits +
                         module.geom_settings.rowbits +
                         module.geom_settings.colbits)*phy.settings.databits//8
        if size is not None:
            sdram_size = min(sdram_size, size)

        # Add SDRAM region
        self.bus.add_region("main_ram", SoCRegion(origin=origin, size=sdram_size))

        # Add CPU's direct memory buses (if not already declared) ----------------------------------
        if hasattr(self.cpu, "add_memory_buses"):
            self.cpu.add_memory_buses(
                address_width = 32,
                data_width    = self.sdram.crossbar.controller.data_width
            )

        # Connect CPU's direct memory buses to LiteDRAM --------------------------------------------
        if len(self.cpu.memory_buses):
            # When CPU has at least a direct memory bus, connect them directly to LiteDRAM.
            for mem_bus in self.cpu.memory_buses:
                # Request a LiteDRAM native port.
                port = self.sdram.crossbar.get_port()
                port.data_width = 2**int(log2(port.data_width)) # Round to nearest power of 2.

                # Check if bus is an AXI bus and connect it.
                if isinstance(mem_bus, axi.AXIInterface):
                    # If same data_width, connect it directly.
                    if port.data_width == mem_bus.data_width:
                        self.logger.info("Matching AXI MEM data width ({})\n".format(port.data_width))
                        self.submodules += LiteDRAMAXI2Native(
                            axi          = self.cpu.mem_axi,
                            port         = port,
                            base_address = self.bus.regions["main_ram"].origin)
                    # If different data_width, do the adaptation and connect it via Wishbone.
                    else:
                        self.logger.info("Converting MEM data width: {} to {} via Wishbone".format(
                            port.data_width,
                            self.cpu.mem_axi.data_width))
                        # FIXME: replace WB data-width converter with native AXI converter!!!
                        mem_wb  = wishbone.Interface(
                            data_width = self.cpu.mem_axi.data_width,
                            adr_width  = 32-log2_int(self.cpu.mem_axi.data_width//8))
                        # NOTE: AXI2Wishbone FSMs must be reset with the CPU!
                        mem_a2w = ResetInserter()(axi.AXI2Wishbone(
                            axi          = self.cpu.mem_axi,
                            wishbone     = mem_wb,
                            base_address = 0))
                        self.comb += mem_a2w.reset.eq(ResetSignal() | self.cpu.reset)
                        self.submodules += mem_a2w
                        litedram_wb = wishbone.Interface(port.data_width)
                        self.submodules += LiteDRAMWishbone2Native(
                            wishbone     = litedram_wb,
                            port         = port,
                            base_address = origin)
                        self.submodules += wishbone.Converter(mem_wb, litedram_wb)
                # Check if bus is a Native bus and connect it.
                if isinstance(mem_bus, LiteDRAMNativePort):
                    # If same data_width, connect it directly.
                    if port.data_width == mem_bus.data_width:
                        self.comb += mem_bus.cmd.connect(port.cmd)
                        self.comb += mem_bus.wdata.connect(port.wdata)
                        self.comb += port.rdata.connect(mem_bus.rdata)
                    # Else raise Error.
                    else:
                        raise NotImplementedError

        # Connect Main bus to LiteDRAM (with optional L2 Cache) ------------------------------------
        connect_main_bus_to_dram = (
            # No memory buses.
            (not len(self.cpu.memory_buses)) or
            # Memory buses but no DMA bus.
            (len(self.cpu.memory_buses) and not hasattr(self.cpu, "dma_bus"))
        )
        if connect_main_bus_to_dram:
            # Request a LiteDRAM native port.
            port = self.sdram.crossbar.get_port()
            port.data_width = 2**int(log2(port.data_width)) # Round to nearest power of 2.

            # Create Wishbone Slave.
            wb_sdram = wishbone.Interface()
            self.bus.add_slave("main_ram", wb_sdram)

            # L2 Cache
            if l2_cache_size != 0:
                # Insert L2 cache inbetween Wishbone bus and LiteDRAM
                l2_cache_size = max(l2_cache_size, int(2*port.data_width/8)) # Use minimal size if lower
                l2_cache_size = 2**int(log2(l2_cache_size))                  # Round to nearest power of 2
                l2_cache_data_width = max(port.data_width, l2_cache_min_data_width)
                l2_cache = wishbone.Cache(
                    cachesize = l2_cache_size//4,
                    master    = wb_sdram,
                    slave     = wishbone.Interface(l2_cache_data_width),
                    reverse   = l2_cache_reverse)
                if l2_cache_full_memory_we:
                    l2_cache = FullMemoryWE()(l2_cache)
                self.submodules.l2_cache = l2_cache
                litedram_wb = self.l2_cache.slave
            else:
                litedram_wb = wishbone.Interface(port.data_width)
                self.submodules += wishbone.Converter(wb_sdram, litedram_wb)
            self.add_config("L2_SIZE", l2_cache_size)

            # Wishbone Slave <--> LiteDRAM bridge
            self.submodules.wishbone_bridge = LiteDRAMWishbone2Native(
                wishbone     = litedram_wb,
                port         = port,
                base_address = self.bus.regions["main_ram"].origin)

    # Add Ethernet ---------------------------------------------------------------------------------
    def add_ethernet(self, name="ethmac", phy=None):
        # Imports
        from liteeth.mac import LiteEthMAC
        # MAC
        ethmac = LiteEthMAC(
            phy        = phy,
            dw         = 32,
            interface  = "wishbone",
            endianness = self.cpu.endianness)
        setattr(self.submodules, name, ethmac)
        ethmac_region = SoCRegion(origin=self.mem_map.get(name, None), size=0x2000, cached=False)
        self.bus.add_slave(name=name, slave=ethmac.bus, region=ethmac_region)
        self.csr.add(name, use_loc_if_exists=True)
        self.add_interrupt(name)
        # Timing constraints
        if hasattr(phy, "crg"):
            eth_rx_clk = phy.crg.cd_eth_rx.clk
            eth_tx_clk = phy.crg.cd_eth_tx.clk
        else:
            eth_rx_clk = phy.cd_eth_rx.clk
            eth_tx_clk = phy.cd_eth_tx.clk
        self.platform.add_period_constraint(eth_rx_clk, 1e9/phy.rx_clk_freq)
        self.platform.add_period_constraint(eth_tx_clk, 1e9/phy.tx_clk_freq)
        self.platform.add_false_path_constraints(
            self.crg.cd_sys.clk,
            eth_rx_clk,
            eth_tx_clk)

    # Add Etherbone --------------------------------------------------------------------------------
    def add_etherbone(self, name="etherbone", phy=None,
        mac_address = 0x10e2d5000000,
        ip_address  = "192.168.1.50",
        udp_port    = 1234):
        # Imports
        from liteeth.core import LiteEthUDPIPCore
        from liteeth.frontend.etherbone import LiteEthEtherbone
        # Core
        ethcore = LiteEthUDPIPCore(
            phy         = phy,
            mac_address = mac_address,
            ip_address  = ip_address,
            clk_freq    = self.clk_freq)
        ethcore = ClockDomainsRenamer("eth_tx")(ethcore)
        self.submodules.ethcore = ethcore

        # Clock domain renaming
        self.clock_domains.cd_etherbone = ClockDomain("etherbone")
        self.comb += self.cd_etherbone.clk.eq(ClockSignal("sys"))
        self.comb += self.cd_etherbone.rst.eq(ResetSignal("sys"))

        # Etherbone
        etherbone = LiteEthEtherbone(ethcore.udp, udp_port, cd="etherbone")
        setattr(self.submodules, name, etherbone)
        self.add_wb_master(etherbone.wishbone.bus)
        # Timing constraints
        if hasattr(phy, "crg"):
            eth_rx_clk = phy.crg.cd_eth_rx.clk
            eth_tx_clk = phy.crg.cd_eth_tx.clk
        else:
            eth_rx_clk = phy.cd_eth_rx.clk
            eth_tx_clk = phy.cd_eth_tx.clk
        self.platform.add_period_constraint(eth_rx_clk, 1e9/phy.rx_clk_freq)
        self.platform.add_period_constraint(eth_tx_clk, 1e9/phy.tx_clk_freq)
        self.platform.add_false_path_constraints(
            self.crg.cd_sys.clk,
            eth_rx_clk,
            eth_tx_clk)

    # Add SPI Flash --------------------------------------------------------------------------------
    def add_spi_flash(self, name="spiflash", mode="4x", dummy_cycles=None, clk_freq=None):
        assert dummy_cycles is not None                 # FIXME: Get dummy_cycles from SPI Flash
        assert mode in ["1x", "4x"]
        if clk_freq is None: clk_freq = self.clk_freq/2 # FIXME: Get max clk_freq from SPI Flash
        spiflash = SpiFlash(
            pads         = self.platform.request(name if mode == "1x" else name + mode),
            dummy        = dummy_cycles,
            div          = ceil(self.clk_freq/clk_freq),
            with_bitbang = True,
            endianness   = self.cpu.endianness)
        spiflash.add_clk_primitive(self.platform.device)
        setattr(self.submodules, name, spiflash)
        spiflash_region = SoCRegion(origin=self.mem_map.get(name, None), size=0x1000000) # FIXME: Get size from SPI Flash
        self.bus.add_slave(name=name, slave=spiflash.bus, region=spiflash_region)
        self.csr.add(name, use_loc_if_exists=True)

    # Add SPI SDCard -------------------------------------------------------------------------------
    def add_spi_sdcard(self, name="spisdcard", spi_clk_freq=400e3):
        pads = self.platform.request(name)
        if hasattr(pads, "rst"):
            self.comb += pads.rst.eq(0)
        spisdcard = SPIMaster(pads, 8, self.sys_clk_freq, spi_clk_freq)
        spisdcard.add_clk_divider()
        setattr(self.submodules, name, spisdcard)
        self.csr.add(name, use_loc_if_exists=True)

    # Add SDCard -----------------------------------------------------------------------------------
    def add_sdcard(self, name="sdcard", mode="read+write", use_emulator=False):
        assert mode in ["read", "write", "read+write"]
        # Imports
        from litesdcard.emulator import SDEmulator
        from litesdcard.phy import SDPHY
        from litesdcard.core import SDCore
        from litesdcard.frontend.dma import SDBlock2MemDMA, SDMem2BlockDMA

        # Emulator / Pads
        if use_emulator:
            sdemulator = SDEmulator(self.platform)
            self.submodules += sdemulator
            sdcard_pads = sdemulator.pads
        else:
            sdcard_pads = self.platform.request(name)

        # Core
        self.submodules.sdphy  = SDPHY(sdcard_pads, self.platform.device, self.clk_freq)
        self.submodules.sdcore = SDCore(self.sdphy)
        self.csr.add("sdphy", use_loc_if_exists=True)
        self.csr.add("sdcore", use_loc_if_exists=True)

        # Block2Mem DMA
        if "read" in mode:
            bus = wishbone.Interface(data_width=self.bus.data_width, adr_width=self.bus.address_width)
            self.submodules.sdblock2mem = SDBlock2MemDMA(bus=bus, endianness=self.cpu.endianness)
            self.comb += self.sdcore.source.connect(self.sdblock2mem.sink)
            dma_bus = self.bus if not hasattr(self, "dma_bus") else self.dma_bus
            dma_bus.add_master("sdblock2mem", master=bus)
            self.csr.add("sdblock2mem", use_loc_if_exists=True)

        # Mem2Block DMA
        if "write" in mode:
            bus = wishbone.Interface(data_width=self.bus.data_width, adr_width=self.bus.address_width)
            self.submodules.sdmem2block = SDMem2BlockDMA(bus=bus, endianness=self.cpu.endianness)
            self.comb += self.sdmem2block.source.connect(self.sdcore.sink)
            dma_bus = self.bus if not hasattr(self, "dma_bus") else self.dma_bus
            dma_bus.add_master("sdmem2block", master=bus)
            self.csr.add("sdmem2block", use_loc_if_exists=True)
