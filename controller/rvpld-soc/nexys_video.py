#!/usr/bin/env python3

#
# This file is part of LiteX-Boards.
#
# Copyright (c) 2015-2019 Florent Kermarrec <florent@enjoy-digital.fr>
# SPDX-License-Identifier: BSD-2-Clause

import os
import argparse

from migen import *

from litex_boards.platforms import nexys_video

from litex.soc.cores.clock import *
from soc_core import *
from litex.soc.integration.soc_sdram import *
from litex.soc.integration.builder import *
from litex.soc.interconnect import axi, wishbone
from litex.soc.interconnect.stream import SyncFIFO
from litex.soc.cores.led import LedChaser
from litex.soc.integration.soc import SoCRegion
from pld_axi import PldAXILiteInterface
from axilite2led import AxiLite2Led
from rendering_mono import RenderingMono

from litedram.modules import MT41K256M16
from litedram.phy import s7ddrphy
from litedram.frontend.dma import LiteDRAMDMAReader, LiteDRAMDMAWriter
from litescope import LiteScopeAnalyzer
from litex.soc.cores import uart

from liteeth.phy.s7rgmii import LiteEthPHYRGMII

DEBUG = False

# CRG ----------------------------------------------------------------------------------------------

class _CRG(Module):
    def __init__(self, platform, sys_clk_freq):
        self.clock_domains.cd_sys       = ClockDomain()
        self.clock_domains.cd_sys4x     = ClockDomain(reset_less=True)
        self.clock_domains.cd_sys4x_dqs = ClockDomain(reset_less=True)
        self.clock_domains.cd_clk200    = ClockDomain()
        self.clock_domains.cd_clk100    = ClockDomain()

        # # #

        self.submodules.pll = pll = S7MMCM(speedgrade=-1)
        self.comb += pll.reset.eq(~platform.request("cpu_reset"))
        pll.register_clkin(platform.request("clk100"), 100e6)
        pll.create_clkout(self.cd_sys,       sys_clk_freq)
        pll.create_clkout(self.cd_sys4x,     4*sys_clk_freq)
        pll.create_clkout(self.cd_sys4x_dqs, 4*sys_clk_freq, phase=90)
        pll.create_clkout(self.cd_clk200,    200e6)
        pll.create_clkout(self.cd_clk100,    100e6)
        self.submodules.idelayctrl = S7IDELAYCTRL(self.cd_clk200)

# BaseSoC ------------------------------------------------------------------------------------------

class BaseSoC(RvpldSoCCore):
    def __init__(self, sys_clk_freq=int(100e6), with_ethernet=False, **kwargs):
        platform = nexys_video.Platform()

        # SoCCore ----------------------------------------------------------------------------------
        RvpldSoCCore.__init__(self, platform, sys_clk_freq,
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
            self.add_etherbone(
                phy=self.ethphy,
                ip_address = "192.168.1.50"
            )

        # AXILite2Led ------------------------------------------------------------------------------
        rst = self.crg.cd_sys.rst
        rstn = ~rst
        clk = self.crg.cd_sys.clk
        self.submodules.axilite2led = axilite2led = AxiLite2Led(clk, rstn, platform)
        axilite2led_region = SoCRegion(origin=0x02000000, size=0x10000)
        self.bus.add_slave(name="axilite2led", slave=axilite2led.bus, region=axilite2led_region)

        axilite2led.add_axi_lite_to_led()

        led_pads = Cat([platform.request("user_led", 0), platform.request("user_led", 1)])
        self.comb += led_pads.eq(axilite2led.led)

        sw_pads = Cat([platform.request("user_sw", 0), platform.request("user_sw", 1)])
        self.comb += axilite2led.sw.eq(sw_pads)

        # mm2s -------------------------------------------------------------------------------------
        self.submodules.mm2s = mm2s = LiteDRAMDMAReader(self.sdram.crossbar.get_port())
        mm2s.add_csr()
        self.add_csr("mm2s")

        # s2mm -------------------------------------------------------------------------------------
        self.submodules.s2mm = s2mm = LiteDRAMDMAWriter(self.sdram.crossbar.get_port())
        s2mm.add_csr()
        self.add_csr("s2mm")

        # sync fifo -------------------------------------------------------------------------------
        #self.submodules.sync_fifo = sync_fifo = SyncFIFO([("data", 128)], 400, True)

        self.submodules.rendering = rendering = RenderingMono(clk, rst, platform)
        rendering.connect_input(mm2s.source)
        rendering.connect_output(s2mm.sink)

        if DEBUG:
            analyzer_signals = [mm2s.source, sync_fifo.level, mm2s.rsv_level, mm2s.sink, mm2s.port.cmd, mm2s.port.rdata]
            self.submodules.analyzer = LiteScopeAnalyzer(analyzer_signals,
                                                         depth = 2048,
                                                         clock_domain = "sys",
                                                         csr_csv = "analyzer.csv")
            self.add_csr("analyzer")

        #level_pads = Cat([platform.request("user_led", 2), platform.request("user_led", 3), \
        #                    platform.request("user_led", 4), platform.request("user_led", 5), \
        #                    platform.request("user_led", 6)])
        #self.comb += level_pads.eq(sync_fifo.level)

        # Leds -------------------------------------------------------------------------------------
        #self.submodules.leds = LedChaser(
        #    pads         = platform.request_all("user_led"),
        #    sys_clk_freq = sys_clk_freq)
        #self.add_csr("leds")

# Build --------------------------------------------------------------------------------------------

def main():
    parser = argparse.ArgumentParser(description="LiteX SoC on Nexys Video")
    parser.add_argument("--build", action="store_true", help="Build bitstream")
    parser.add_argument("--load",  action="store_true", help="Load bitstream")
    builder_args(parser)
    soc_sdram_args(parser)
    parser.add_argument("--with-ethernet", action="store_true", help="Enable Ethernet support")
    parser.add_argument("--with-spi-sdcard", action="store_true", help="Enable SPI-mode SDCard support")
    parser.add_argument("--with-sdcard", action="store_true",     help="Enable SDCard support")
    args = parser.parse_args()

    soc = BaseSoC(with_ethernet=args.with_ethernet, **soc_sdram_argdict(args))
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
