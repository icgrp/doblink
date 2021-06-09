#!/usr/bin/env python3

#
# This file is part of LiteX-Boards.
#
# Copyright (c) 2015-2019 Florent Kermarrec <florent@enjoy-digital.fr>
# SPDX-License-Identifier: BSD-2-Clause

import os
import argparse

from migen import *

from litex.soc.cores.clock import *
from litex.soc.integration.soc_core import *
from litex.soc.integration.soc import *
from litex.soc.integration.builder import *
from litex.soc.interconnect.stream import Converter, Endpoint, ClockDomainCrossing
from litex.soc.interconnect import wishbone
from litex.soc.interconnect.axi import AXILiteInterface
from litex.soc.interconnect.stream import SyncFIFO
from litex.soc.cores.led import LedChaser
from litex.soc.integration.soc import SoCRegion
from litex.build.xilinx.vivado import vivado_build_args, vivado_build_argdict

from litedram.modules import MT41K256M16
from litedram.phy import s7ddrphy
from litedram.frontend.dma import *

from litex.build.generic_platform import Subsignal, Pins
from litesata.phy import LiteSATAPHY

from liteeth.phy.s7rgmii import LiteEthPHYRGMII
from litescope import LiteScopeAnalyzer

from pld_axi import PldAXILiteInterface
from axilite2led import AxiLite2Led
from rendering.rendering_mono import RenderingMono
from rendering.rendering_6_page import Rendering6Page

from platforms import nexys_video
# CRG ----------------------------------------------------------------------------------------------

class _CRG(Module):
    def __init__(self, platform, sys_clk_freq, toolchain):
        self.rst = Signal()
        self.clock_domains.cd_sys       = ClockDomain()
        self.clock_domains.cd_sys4x     = ClockDomain(reset_less=True)
        self.clock_domains.cd_sys4x_dqs = ClockDomain(reset_less=True)
        self.clock_domains.cd_idelay    = ClockDomain()
        self.clock_domains.cd_clk100    = ClockDomain()
        self.clock_domains.cd_bft       = ClockDomain()

        # # #

        self.submodules.pll = pll = S7PLL(speedgrade=-1)
        self.comb += pll.reset.eq(~platform.request("cpu_reset") | self.rst)
        pll.register_clkin(platform.request("clk100"), 100e6)
        pll.create_clkout(self.cd_sys,       sys_clk_freq)
        pll.create_clkout(self.cd_sys4x,     4*sys_clk_freq)
        pll.create_clkout(self.cd_sys4x_dqs, 4*sys_clk_freq, phase=90)
        pll.create_clkout(self.cd_idelay,    200e6)
        pll.create_clkout(self.cd_clk100,    100e6)
        pll.create_clkout(self.cd_bft,    10e6)
        platform.add_false_path_constraints(self.cd_sys.clk, pll.clkin) # Ignore sys_clk to pll.clkin path created by SoC's rst.

        self.submodules.idelayctrl = S7IDELAYCTRL(self.cd_idelay)

# BaseSoC ------------------------------------------------------------------------------------------

class BaseSoC(SoCCore):
    def __init__(self, toolchain="vivado", sys_clk_freq=int(100e6), with_ethernet=False, with_sata=False, **kwargs):
        platform = nexys_video.Platform(toolchain=toolchain)

        # SoCCore ----------------------------------------------------------------------------------
        SoCCore.__init__(self, platform, sys_clk_freq,
            ident          = "LiteX SoC on Nexys Video",
            ident_version  = True,
            **kwargs)

        # CRG --------------------------------------------------------------------------------------
        self.submodules.crg = _CRG(platform, sys_clk_freq, toolchain)

        # DDR3 SDRAM -------------------------------------------------------------------------------
        if not self.integrated_main_ram_size:
            self.submodules.ddrphy = s7ddrphy.A7DDRPHY(platform.request("ddram"),
                memtype      = "DDR3",
                nphases      = 4,
                sys_clk_freq = sys_clk_freq)
            self.add_csr("ddrphy")
            self.add_sdram("sdram",
                phy                     = self.ddrphy,
                module                  = MT41K256M16(sys_clk_freq, "1:4"),
                origin                  = self.mem_map["main_ram"],
                size                    = kwargs.get("max_sdram_size", 0x40000000),
                l2_cache_size           = kwargs.get("l2_size", 8192),
                l2_cache_min_data_width = kwargs.get("min_l2_data_width", 128),
                l2_cache_reverse        = True
            )

        # Ethernet ---------------------------------------------------------------------------------
        self.submodules.ethphy = LiteEthPHYRGMII(
            clock_pads = self.platform.request("eth_clocks"),
            pads       = self.platform.request("eth"))
        self.add_csr("ethphy")
        self.add_etherbone(
            phy=self.ethphy,
            ip_address = "192.168.1.50"
        )

        rst = self.crg.cd_sys.rst
        rstn = ~rst
        clk = self.crg.cd_sys.clk
        rst_bft = self.crg.cd_bft.rst
        rst_bftn = ~rst_bft
        clk_bft = self.crg.cd_bft.clk

        # AXILite2Led ------------------------------------------------------------------------------
        self.submodules.axilite2led = axilite2led = AxiLite2Led(self.crg.cd_sys.clk, ~self.crg.cd_sys.clk, platform, "sys")
        axilite2led_region = SoCRegion(origin=0x02000000, size=0x10000)
        self.bus.add_slave(name="axilite2led", slave=axilite2led.bus, region=axilite2led_region)

        #led_pads = Cat([platform.request("user_led", 0), platform.request("user_led", 1)])
        #self.comb += led_pads.eq(axilite2led.led)

        sw_pads = Cat([platform.request("user_sw", 0), platform.request("user_sw", 1)])
        self.comb += axilite2led.sw.eq(sw_pads)

        # AXILite2BFT ------------------------------------------------------------------------------
        axi_bft_bus = AXILiteInterface(data_width=32, address_width=5, clock_domain="sys")
        axilite2bft_region = SoCRegion(origin=0x02010000, size=0x10000)
        self.bus.add_slave(name="axilite2bft", slave=axi_bft_bus, region=axilite2bft_region)

        # mm2s -------------------------------------------------------------------------------------
        self.submodules.mm2s = mm2s = LiteDRAMDMAReader(self.sdram.crossbar.get_port(data_width=32))
        mm2s.add_csr()
        self.add_csr("mm2s")

        # s2mm -------------------------------------------------------------------------------------
        self.submodules.s2mm = s2mm = LiteDRAMDMAWriter(self.sdram.crossbar.get_port(data_width=32))
        s2mm.add_csr()
        self.add_csr("s2mm")

        # Debug ------------------------------------------------------------------------------------
        analyzer_signals = [s2mm.sink]
        self.submodules.analyzer = LiteScopeAnalyzer(analyzer_signals,
                                                     depth = 2048,
                                                     clock_domain = "sys",
                                                     csr_csv = "analyzer.csv")
        self.add_csr("analyzer")

        #self.submodules.sync_fifo = sync_fifo = SyncFIFO([("data", 128)], 100, True)
        #self.comb += mm2s.source.connect(sync_fifo.sink)
        #self.comb += sync_fifo.source.connect(s2mm.sink)

        #self.comb += platform.request('user_led', 0).eq(s2mm.sink.valid)
        #self.comb += platform.request('user_led', 1).eq(s2mm.sink.ready)
        #self.comb += platform.request('user_led', 2).eq(mm2s.source.valid)
        #self.comb += platform.request('user_led', 3).eq(mm2s.source.ready)
        #self.comb += platform.request_all('user_led').eq(sync_fifo.level)

        # Rendering6Page -------------------------------------------------------------------------------
        self.submodules.rendering = rendering = Rendering6Page(clk_bft, rst_bft, platform, 'bft')
        rendering.connect_input(mm2s.source)
        rendering.connect_output(s2mm.sink)
        rendering.connect_axil(axi_bft_bus)

# Build --------------------------------------------------------------------------------------------

def main():
    parser = argparse.ArgumentParser(description="LiteX SoC on Nexys Video")
    parser.add_argument("--build",           action="store_true", help="Build bitstream")
    parser.add_argument("--load",            action="store_true", help="Load bitstream")
    parser.add_argument("--toolchain",       default="vivado",    help="Toolchain use to build (default: vivado)")
    parser.add_argument("--sys-clk-freq",    default=100e6,       help="System clock frequency (default: 100MHz)")
    parser.add_argument("--with-ethernet",   action="store_true", help="Enable Ethernet support")
    parser.add_argument("--with-spi-sdcard", action="store_true", help="Enable SPI-mode SDCard support")
    parser.add_argument("--with-sdcard",     action="store_true", help="Enable SDCard support")
    parser.add_argument("--with-sata",       action="store_true", help="Enable SATA support (over FMCRAID)")
    builder_args(parser)
    soc_core_args(parser)
    args = parser.parse_args()

    soc = BaseSoC(
        toolchain      = args.toolchain,
        sys_clk_freq  = int(float(args.sys_clk_freq)),
        with_ethernet = args.with_ethernet,
        with_sata     = args.with_sata,
        **soc_core_argdict(args)
    )

    assert not (args.with_spi_sdcard and args.with_sdcard)
    if args.with_spi_sdcard:
        soc.add_spi_sdcard()
    if args.with_sdcard:
        soc.add_sdcard()
    builder = Builder(soc, **builder_argdict(args))
    builder.build(run=args.build)

    if args.load:
        prog = soc.platform.create_programmer()
        prog.load_bitstream(os.path.join(builder.gateware_dir, soc.build_name + ".bit"))

if __name__ == "__main__":
    main()
