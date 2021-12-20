#!/usr/bin/env python3

#
# This file is part of LiteX-Boards.
#
# Copyright (c) 2015-2019 Florent Kermarrec <florent@enjoy-digital.fr>
# SPDX-License-Identifier: BSD-2-Clause

import argparse
import os

from axil_cdc import AxilCDC
from axilite2bft import AxiLite2Bft
from axilite2led import AxiLite2Led
from litedram.frontend.adapter import LiteDRAMNativePortConverter
from litedram.frontend.dma import *
from litedram.modules import MT41K256M16
from litedram.phy import s7ddrphy
from liteeth.phy.s7rgmii import LiteEthPHYRGMII
from litesata.phy import LiteSATAPHY
from litescope import LiteScopeAnalyzer
from litex.build.generic_platform import Pins, Subsignal
from litex.build.xilinx.vivado import vivado_build_argdict, vivado_build_args
from litex.soc.cores.clock import *
from litex.soc.cores.led import LedChaser
from litex.soc.integration.builder import *
from litex.soc.integration.soc import *
from litex.soc.integration.soc import SoCRegion
from litex.soc.integration.soc_core import *
from litex.soc.interconnect import wishbone
from litex.soc.interconnect.axi import AXILiteInterface
from litex.soc.interconnect.stream import (ClockDomainCrossing, Converter,
                                           Endpoint, SyncFIFO)
from migen import *
from platforms import nexys_video
from pld_axi import PldAXILiteInterface
from rendering.rendering_4_no_bft import Rendering4Mono
from rendering.rendering_4_page import Rendering4Page
from rendering.rendering_6_no_bft import Rendering6Mono
from rendering.rendering_6_no_bft_vitis import Rendering6MonoVitis
from rendering.rendering_6_page import Rendering6Page
from rendering.rendering_6_page_vitis import Rendering6PageVitis
from rendering.rendering_leaf_only import RenderingLeafOnly
from rendering.rendering_mono import RenderingMono
from start import StartWriter

# CRG ----------------------------------------------------------------------------------------------


class _CRG(Module):
    def __init__(self, platform, sys_clk_freq, toolchain):
        self.rst = Signal()
        self.clock_domains.cd_sys = ClockDomain()
        self.clock_domains.cd_sys4x = ClockDomain(reset_less=True)
        self.clock_domains.cd_sys4x_dqs = ClockDomain(reset_less=True)
        self.clock_domains.cd_idelay = ClockDomain()
        self.clock_domains.cd_clk100 = ClockDomain()
        self.clock_domains.cd_bft = ClockDomain()

        # # #

        self.submodules.pll = pll = S7PLL(speedgrade=-1)
        self.comb += pll.reset.eq(~platform.request("cpu_reset") | self.rst)
        pll.register_clkin(platform.request("clk100"), 100e6)
        pll.create_clkout(self.cd_sys, sys_clk_freq)
        pll.create_clkout(self.cd_sys4x, 4 * sys_clk_freq)
        pll.create_clkout(self.cd_sys4x_dqs, 4 * sys_clk_freq, phase=90)
        pll.create_clkout(self.cd_idelay, 200e6)
        pll.create_clkout(self.cd_clk100, 100e6)
        pll.create_clkout(self.cd_bft, 30e6)
        platform.add_false_path_constraints(
            self.cd_sys.clk, pll.clkin
        )  # Ignore sys_clk to pll.clkin path created by SoC's rst.

        self.submodules.idelayctrl = S7IDELAYCTRL(self.cd_idelay)


# BaseSoC ------------------------------------------------------------------------------------------


class BaseSoC(SoCCore):
    def __init__(
        self,
        toolchain="vivado",
        sys_clk_freq=int(100e6),
        with_ethernet=False,
        with_sata=False,
        **kwargs
    ):
        platform = nexys_video.Platform(toolchain=toolchain)

        # SoCCore ----------------------------------------------------------------------------------
        SoCCore.__init__(
            self,
            platform,
            sys_clk_freq,
            ident="LiteX SoC on Nexys Video",
            ident_version=True,
            **kwargs
        )

        # CRG --------------------------------------------------------------------------------------
        self.submodules.crg = _CRG(platform, sys_clk_freq, toolchain)

        # DDR3 SDRAM -------------------------------------------------------------------------------
        if not self.integrated_main_ram_size:
            self.submodules.ddrphy = s7ddrphy.A7DDRPHY(
                platform.request("ddram"),
                memtype="DDR3",
                nphases=4,
                cl=7,
                cwl=7,
                sys_clk_freq=sys_clk_freq,
            )
            self.add_csr("ddrphy")
            self.add_sdram(
                "sdram",
                phy=self.ddrphy,
                module=MT41K256M16(sys_clk_freq, "1:4"),
                origin=self.mem_map["main_ram"],
                size=kwargs.get("max_sdram_size", 0x40000000),
                l2_cache_size=kwargs.get("l2_size", 8192),
                l2_cache_min_data_width=kwargs.get("min_l2_data_width", 128),
                l2_cache_reverse=True,
            )

        # Ethernet ---------------------------------------------------------------------------------
        # self.submodules.ethphy = LiteEthPHYRGMII(
        #     clock_pads = self.platform.request("eth_clocks"),
        #     pads       = self.platform.request("eth"))
        # self.add_csr("ethphy")
        # self.add_etherbone(
        #     phy=self.ethphy,
        #     ip_address = "192.168.1.50"
        # )

        rst = self.crg.cd_sys.rst
        rstn = ~rst
        clk = self.crg.cd_sys.clk
        rst_bft = self.crg.cd_bft.rst
        rst_bftn = ~rst_bft
        clk_bft = self.crg.cd_bft.clk

        # AXILite2Led ------------------------------------------------------------------------------
        # self.submodules.axilite2led = axilite2led = AxiLite2Led(self.crg.cd_sys.clk, ~self.crg.cd_sys.clk, platform, "sys")
        # axilite2led_region = SoCRegion(origin=0x02000000, size=0x10000)
        # self.bus.add_slave(name="axilite2led", slave=axilite2led.bus, region=axilite2led_region)

        # led_pads = Cat([platform.request("user_led", 0), platform.request("user_led", 1)])
        # self.comb += led_pads.eq(axilite2led.led)

        # sw_pads = Cat([platform.request("user_sw", 0), platform.request("user_sw", 1)])
        # self.comb += axilite2led.sw.eq(sw_pads)

        # AXILite2BFT ------------------------------------------------------------------------------
        axi_bft_bus_sys = axi.AXILiteInterface(
            data_width=32, address_width=5, clock_domain="sys"
        )
        axi_bft_bus_bft = axi.AXILiteInterface(
            data_width=32, address_width=5, clock_domain="bft"
        )
        self.submodules.axil_cdc_sys2bft = axil_cdc_sys2bft = AxilCDC(
            clk, rst, clk_bft, rst_bft, self.platform, "sys", "bft"
        )
        self.comb += axi_bft_bus_sys.connect(axil_cdc_sys2bft.slave)
        self.comb += axil_cdc_sys2bft.master.connect(axi_bft_bus_bft)
        axilite2bft_region = SoCRegion(origin=0x02010000, size=0x10000)
        self.bus.add_slave(
            name="axilite2bft", slave=axi_bft_bus_sys, region=axilite2bft_region
        )

        # mm2s -------------------------------------------------------------------------------------
        # litedram_read_32 = LiteDRAMNativePort('both', 27, 32)
        # self.submodules.dram_read_converter = LiteDRAMNativePortConverter(litedram_read_32, self.sdram.crossbar.get_port(), reverse=True)
        self.submodules.mm2s = mm2s = LiteDRAMDMAReader(
            self.sdram.crossbar.get_port(data_width=32, reverse=True), with_csr=True
        )
        self.add_csr("mm2s")
        mm2s_axis = axi.AXIStreamInterface(32)
        self.comb += mm2s.source.connect(mm2s_axis)
        # self.submodules.input_cross_domain_converter = (
        #     input_cross_domain_converter
        # ) = ClockDomainCrossing(
        #     mm2s_axis.description, cd_from="sys", cd_to="bft", depth=8
        # )
        # mm2s_axis_bft = axi.AXIStreamInterface(32)
        # self.comb += mm2s_axis.connect(input_cross_domain_converter.sink)
        # self.comb += input_cross_domain_converter.source.connect(mm2s_axis_bft)

        # s2mm -------------------------------------------------------------------------------------
        # litedram_write_32 = LiteDRAMNativePort('both', 27, 32)
        # self.submodules.dram_write_converter = LiteDRAMNativePortConverter(litedram_write_32, self.sdram.crossbar.get_port(), reverse=True)
        self.submodules.s2mm = s2mm = LiteDRAMDMAWriter(
            self.sdram.crossbar.get_port(data_width=32, reverse=True), with_csr=True
        )
        self.add_csr("s2mm")
        s2mm_axis = axi.AXIStreamInterface(32)
        self.comb += s2mm_axis.connect(s2mm.sink)
        # self.submodules.output_cross_domain_converter = (
        #     output_cross_domain_converter
        # ) = ClockDomainCrossing(
        #     s2mm_axis.description, cd_from="bft", cd_to="sys", depth=8
        # )
        # s2mm_axis_bft = axi.AXIStreamInterface(32)
        # self.comb += output_cross_domain_converter.source.connect(s2mm_axis)
        # self.comb += s2mm_axis_bft.connect(output_cross_domain_converter.sink)

        # start ------------------------------------------------------------------------------------
        start_signal = Signal()
        self.submodules.start = start = StartWriter(start_signal)
        self.add_csr("start")

        # sync fifo -------------------------------------------------------------------------------
        # self.submodules.sync_fifo = sync_fifo = SyncFIFO([("data", 32)], 8, True)
        # self.comb += mm2s.source.connect(sync_fifo.sink)
        # self.comb += sync_fifo.source.connect(s2mm.sink)

        benchmark = kwargs.get("bench", "rendering")
        if benchmark == "rendering":
            # Rendering6Page ---------------------------------------------------------------------------
            # self.submodules.rendering = rendering = RenderingLeafOnly(
            #     clk, rst, platform, clock_domain="sys", start=start_signal
            # )
            # self.submodules.rendering = rendering = Rendering6Mono(clk_bft, rst_bft, platform, start=start_signal, clock_domain='bft')
            # self.submodules.rendering = rendering = RenderingMono(clk, rst, platform, clock_domain='sys')
            self.submodules.rendering = rendering = Rendering4Mono(clk, rst, platform, clock_domain='sys', start=start_signal)
            # self.submodules.rendering = rendering = Rendering6MonoVitis(clk_bft, rst_bft, platform, clock_domain='bft', start=start_signal)
            rendering.connect_input(mm2s_axis)
            rendering.connect_output(s2mm_axis)
            #rendering.connect_axil(axi_bft_bus_bft)
        elif benchmark == "digit_recognition":
            from digit_recognition.digit_recognition_mono import DigitMono

            # DigitRecognition10Page ---------------------------------------------------------------------------
            self.submodules.digit_recognition = digit_recognition = DigitMono(
                clk, rst, platform, clock_domain="sys"
            )
            digit_recognition.connect_input(mm2s_axis)
            digit_recognition.connect_output(s2mm_axis)
            # digit_recognition.connect_axil(axi_bft_bus_bft)
        elif benchmark == "array_partition":
            from array_partition.array_partition_bft import ArrayPartitionBFT

            # DigitRecognition10Page ---------------------------------------------------------------------------
            self.submodules.array_partition = array_partition = ArrayPartitionBFT(
                clk_bft, rst_bft, platform, clock_domain="bft"
            )
            array_partition.connect_input(mm2s_axis_bft)
            array_partition.connect_output(s2mm_axis_bft)
            array_partition.connect_axil(axi_bft_bus_bft)
        elif benchmark == "digit_recognition_5":
            from digit_recognition.digit_recognition_6_page import \
                DigitRecognition6Page

            # DigitRecognition6Page ---------------------------------------------------------------------------
            self.submodules.digit_recognition = (
                digit_recognition
            ) = DigitRecognition6Page(clk_bft, rst_bft, platform, clock_domain="bft")
            digit_recognition.connect_input(mm2s_axis_bft)
            digit_recognition.connect_output(s2mm_axis_bft)
            digit_recognition.connect_axil(axi_bft_bus_bft)
        elif benchmark == "spam_filter":
            from spam_filter.spam_filter_mono import SpamFilterMono

            # SpamFilter11Page ---------------------------------------------------------------------------
            self.submodules.spam_filter = spam_filter = SpamFilterMono(
                clk, rst, platform, clock_domain="sys"
            )
            spam_filter.connect_input(mm2s_axis)
            spam_filter.connect_output(s2mm_axis)
            # spam_filter.connect_axil(axi_bft_bus_bft)
        # self.comb += platform.request("user_led", 0).eq(s2mm.fsm.ongoing("RUN"))
        # self.comb += platform.request("user_led", 1).eq(s2mm.fsm.ongoing("DONE"))
        # mm2s_ever_valid = Signal()
        # s2mm_ever_valid = Signal()
        # s2mm_handshake = Signal()
        # self.sync += If(mm2s.source.valid, mm2s_ever_valid.eq(1))
        # self.sync += If(s2mm.sink.valid, s2mm_ever_valid.eq(1))
        # self.sync += If(s2mm.sink.valid & s2mm.sink.ready, s2mm_handshake.eq(1))
        # self.comb += platform.request("user_led", 2).eq(mm2s.source.valid)
        # self.comb += platform.request("user_led", 3).eq(mm2s.source.ready)
        # self.comb += platform.request("user_led", 4).eq(s2mm.sink.valid)
        # self.comb += platform.request("user_led", 5).eq(s2mm.sink.ready)
        # self.comb += platform.request("user_led", 6).eq(s2mm._sink.last)
        # self.comb += platform.request("user_led", 7).eq(s2mm_handshake)


# Build --------------------------------------------------------------------------------------------


def main():
    parser = argparse.ArgumentParser(description="LiteX SoC on Nexys Video")
    parser.add_argument("--build", action="store_true", help="Build bitstream")
    parser.add_argument("--load", action="store_true", help="Load bitstream")
    parser.add_argument(
        "--toolchain", default="vivado", help="Toolchain use to build (default: vivado)"
    )
    parser.add_argument(
        "--sys-clk-freq", default=100e6, help="System clock frequency (default: 100MHz)"
    )
    parser.add_argument(
        "--with-ethernet", action="store_true", help="Enable Ethernet support"
    )
    parser.add_argument(
        "--with-spi-sdcard", action="store_true", help="Enable SPI-mode SDCard support"
    )
    parser.add_argument(
        "--with-sdcard", action="store_true", help="Enable SDCard support"
    )
    parser.add_argument(
        "--with-sata", action="store_true", help="Enable SATA support (over FMCRAID)"
    )
    parser.add_argument(
        "--bench",
        default="rendering",
        help="Benchmark use to build (default: rendering)",
    )
    builder_args(parser)
    soc_core_args(parser)
    vivado_build_args(parser)
    args = parser.parse_args()

    soc = BaseSoC(
        toolchain=args.toolchain,
        sys_clk_freq=int(float(args.sys_clk_freq)),
        with_ethernet=args.with_ethernet,
        with_sata=args.with_sata,
        bench=args.bench,
        **soc_core_argdict(args)
    )

    assert not (args.with_spi_sdcard and args.with_sdcard)
    if args.with_spi_sdcard:
        soc.add_spi_sdcard()
    if args.with_sdcard:
        soc.add_sdcard()
    builder = Builder(soc, **builder_argdict(args))
    builder_kwargs = vivado_build_argdict(args) if args.toolchain == "vivado" else {}
    builder.build(**builder_kwargs, run=args.build)

    if args.load:
        prog = soc.platform.create_programmer()
        prog.load_bitstream(os.path.join(builder.gateware_dir, soc.build_name + ".bit"))


if __name__ == "__main__":
    main()
