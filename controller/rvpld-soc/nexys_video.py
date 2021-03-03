#!/usr/bin/env python3

#
# This file is part of LiteX-Boards.
#
# Copyright (c) 2015-2019 Florent Kermarrec <florent@enjoy-digital.fr>
# SPDX-License-Identifier: BSD-2-Clause

import os
import argparse

from migen import *

from platforms import nexys_video

from litex.soc.cores.clock import *
from litex.soc.integration.soc_core import *
from litex.soc.integration.soc import *
from litex.soc.integration.soc_sdram import *
from litex.soc.integration.builder import *
from litex.soc.interconnect.stream import Converter, Endpoint, ClockDomainCrossing
from litex.soc.interconnect import axi, wishbone
from litex.soc.interconnect.stream import SyncFIFO
from litex.soc.cores.led import LedChaser
from litex.soc.integration.soc import SoCRegion
from litex.build.xilinx.vivado import vivado_build_args, vivado_build_argdict
from pld_axi import PldAXILiteInterface
from axilite2led import AxiLite2Led
from axil_cdc import AxilCDC
from rendering.rendering_6_page import Rendering6Page
from rendering.rendering_mono import RenderingMono

from litedram.modules import MT41K256M16
from litedram.phy import s7ddrphy
from litedram.frontend.dma import *

from litex.build.generic_platform import Subsignal, Pins
from litesata.phy import LiteSATAPHY

from liteeth.phy.s7rgmii import LiteEthPHYRGMII

# CRG ----------------------------------------------------------------------------------------------

class _CRG(Module):
    def __init__(self, platform, sys_clk_freq):
        self.rst = Signal()
        self.clock_domains.cd_sys       = ClockDomain()
        self.clock_domains.cd_sys4x     = ClockDomain(reset_less=True)
        self.clock_domains.cd_sys4x_dqs = ClockDomain(reset_less=True)
        self.clock_domains.cd_idelay    = ClockDomain()
        self.clock_domains.cd_bft       = ClockDomain()

        # # #

        self.submodules.pll = pll = S7PLL(speedgrade=-1)
        cpu_reset_n = ~platform.request("cpu_reset")
        self.comb += pll.reset.eq(cpu_reset_n | self.rst)
        pll.register_clkin(platform.request("clk100"), 100e6)
        pll.create_clkout(self.cd_sys,       sys_clk_freq)
        pll.create_clkout(self.cd_sys4x,     4*sys_clk_freq)
        pll.create_clkout(self.cd_sys4x_dqs, 4*sys_clk_freq, phase=90)
        pll.create_clkout(self.cd_idelay,    200e6)
        pll.create_clkout(self.cd_bft,    30e6)
        platform.add_false_path_constraints(self.cd_sys.clk, pll.clkin) # Ignore sys_clk to pll.clkin path created by SoC's rst.

        self.submodules.idelayctrl = S7IDELAYCTRL(self.cd_idelay)

        #platform.add_false_path_constraints(self.cd_sys.clk, pll_bft.clkin) # Ignore sys_clk to pll.clkin path created by SoC's rst.


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
        self.submodules.crg = _CRG(platform, sys_clk_freq)

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
        if with_ethernet:
            self.submodules.ethphy = LiteEthPHYRGMII(
                clock_pads = self.platform.request("eth_clocks"),
                pads       = self.platform.request("eth"))
            self.add_csr("ethphy")
            self.add_ethernet(phy=self.ethphy)

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

        led_pads = Cat([platform.request("user_led", 0), platform.request("user_led", 1)])
        self.comb += led_pads.eq(axilite2led.led)

        sw_pads = Cat([platform.request("user_sw", 0), platform.request("user_sw", 1)])
        self.comb += axilite2led.sw.eq(sw_pads)

        # AXILite2BFT ------------------------------------------------------------------------------
        axi_bft_bus_sys = axi.AXILiteInterface(data_width=32, address_width=5, clock_domain="sys")
        axi_bft_bus_bft = axi.AXILiteInterface(data_width=32, address_width=5, clock_domain="bft")
        self.submodules.axil_cdc_sys2bft = axil_cdc_sys2bft = AxilCDC(clk, rst, clk_bft, rst_bft, self.platform, 'sys', 'bft')
        self.comb += axi_bft_bus_sys.connect(axil_cdc_sys2bft.slave)
        self.comb += axil_cdc_sys2bft.master.connect(axi_bft_bus_bft)
        axilite2bft_region = SoCRegion(origin=0x02010000, size=0x10000)
        self.bus.add_slave(name="axilite2bft", slave=axi_bft_bus_sys, region=axilite2bft_region)

        # mm2s -------------------------------------------------------------------------------------
        self.submodules.mm2s = mm2s = LiteDRAMDMAReader(self.sdram.crossbar.get_port())
        mm2s.add_csr()
        self.add_csr("mm2s")
        self.submodules.input_converter = input_converter = Converter(128, 32, reverse=True)
        self.comb += mm2s.source.connect(input_converter.sink)
        mm2s_axis = axi.AXIStreamInterface(32)
        self.comb += input_converter.source.connect(mm2s_axis)
        self.submodules.input_cross_domain_converter = input_cross_domain_converter = ClockDomainCrossing(mm2s_axis.description, cd_from="sys", cd_to="bft", depth=8)
        mm2s_axis_bft = axi.AXIStreamInterface(32)
        self.comb += mm2s_axis.connect(input_cross_domain_converter.sink)
        self.comb += input_cross_domain_converter.source.connect(mm2s_axis_bft)

        # s2mm -------------------------------------------------------------------------------------
        self.submodules.s2mm = s2mm = LiteDRAMDMAWriter(self.sdram.crossbar.get_port())
        s2mm.add_csr()
        self.add_csr("s2mm")
        self.submodules.output_converter = output_converter = Converter(32, 128, reverse=True)
        self.comb += output_converter.source.connect(s2mm.sink)
        s2mm_axis = axi.AXIStreamInterface(32)
        self.comb += s2mm_axis.connect(output_converter.sink)
        self.submodules.output_cross_domain_converter = output_cross_domain_converter = ClockDomainCrossing(s2mm_axis.description, cd_from="bft", cd_to="sys", depth=8)
        s2mm_axis_bft = axi.AXIStreamInterface(32)
        self.comb += output_cross_domain_converter.source.connect(s2mm_axis)
        self.comb += s2mm_axis_bft.connect(output_cross_domain_converter.sink)

        # sync fifo -------------------------------------------------------------------------------
        #self.submodules.sync_fifo = sync_fifo = SyncFIFO([("data", 128)], 400, True)

        #self.submodules.rendering = rendering = Rendering6Page(clk_bft, rst_bft, platform, 'bft')
        self.submodules.rendering = rendering = RenderingMono(clk_bft, rst_bft, platform, 'bft')
        rendering.connect_input(mm2s_axis_bft)
        rendering.connect_output(s2mm_axis_bft)

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
    soc_sdram_args(parser)
    args = parser.parse_args()

    soc = BaseSoC(
        toolchain      = args.toolchain,
        sys_clk_freq  = int(float(args.sys_clk_freq)),
        with_ethernet = args.with_ethernet,
        with_sata     = args.with_sata,
        **soc_sdram_argdict(args)
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
