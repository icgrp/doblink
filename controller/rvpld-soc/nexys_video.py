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
from litex.soc.interconnect import axi
from litex.soc.interconnect import wishbone
from litex.soc.cores.led import LedChaser
from litex.soc.integration.soc import SoCRegion
from pld_axil import PldAXILiteInterface

from litedram.modules import MT41K256M16
from litedram.phy import s7ddrphy

from liteeth.phy.s7rgmii import LiteEthPHYRGMII


# CRG ----------------------------------------------------------------------------------------------

class _CRG(Module):
    def __init__(self, platform, sys_clk_freq, cpu_reset):
        self.clock_domains.cd_sys       = ClockDomain()
        self.clock_domains.cd_sys4x     = ClockDomain(reset_less=True)
        self.clock_domains.cd_sys4x_dqs = ClockDomain(reset_less=True)
        self.clock_domains.cd_clk200    = ClockDomain()
        self.clock_domains.cd_clk100    = ClockDomain()

        # # #

        self.submodules.pll = pll = S7MMCM(speedgrade=-1)
        self.comb += pll.reset.eq(~cpu_reset)
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
        cpu_reset = platform.request("cpu_reset")
        crg = _CRG(platform, sys_clk_freq, cpu_reset)
        self.submodules.crg = crg

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

        # AXILite2Led ------------------------------------------------------------------------------
        axi_bus = PldAXILiteInterface(data_width=32, address_width=32)
        axilite2bft_region = SoCRegion(origin=0x02000000, size=0x10000)
        self.bus.add_slave(name="axilite2led", slave=axi_bus, region=axilite2bft_region)
        LED = Signal(2, name="LED")
        SW = Signal(2, name="SW")

        axil_sigs = axi_bus.get_signals()
        self.specials += Instance("AxiLite2Led",
                                  o_LED = LED,
                                  i_SW = SW,
                                  i_s00_axi_aclk = crg.cd_sys.clk,
                                  i_s00_axi_aresetn = cpu_reset,
                                  i_s00_axi_awaddr = axil_sigs['awaddr'],
                                  i_s00_axi_awvalid = axil_sigs['awvalid'],
                                  o_s00_axi_awready = axil_sigs['awready'],
                                  i_s00_axi_wdata = axil_sigs['wdata'],
                                  i_s00_axi_wstrb = axil_sigs['wstrb'],
                                  i_s00_axi_wvalid = axil_sigs['wvalid'],
                                  o_s00_axi_wready = axil_sigs['wready'],
                                  o_s00_axi_bresp = axil_sigs['bresp'],
                                  o_s00_axi_bvalid = axil_sigs['bvalid'],
                                  o_s00_axi_bready = axil_sigs['bready'],
                                  i_s00_axi_araddr = axil_sigs['araddr'],
                                  i_s00_axi_arvalid = axil_sigs['arvalid'],
                                  o_s00_axi_arready = axil_sigs['arready'],
                                  o_s00_axi_rdata = axil_sigs['rdata'],
                                  o_s00_axi_rresp = axil_sigs['rresp'],
                                  o_s00_axi_rvalid = axil_sigs['rvalid'],
                                  i_s00_axi_rready = axil_sigs['rready']
                                  )
        platform.add_source('rtl/AxiLite2Led.v')

        #led_pads = Cat([platform.request("user_led", 0), platform.request("user_led", 1)])
        #self.comb += led_pads.eq(LED)

        #reset_pad = platform.request("user_led", 7)
        #self.comb += reset_pad.eq(cpu_reset)

        led_pads = platform.request_all("user_led")
        self.comb += led_pads.eq(axil_sigs['awaddr'])

        sw_pads = Cat([platform.request("user_sw", 0), platform.request("user_sw", 1)])
        self.comb += sw_pads.eq(SW)
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
