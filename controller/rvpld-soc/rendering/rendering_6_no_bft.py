from litex.soc.interconnect.axi import AXIStreamInterface, AXILiteInterface
from litex.soc.interconnect.stream import Converter, Endpoint, ClockDomainCrossing
from migen import *
from pld_axi import *
from axilite2bft import AxiLite2Bft
from bft import Bft
from interface_wrapper import InterfaceWrapper
from axil_cdc import AxilCDC


class Rendering6Mono(Module):
    def __init__(self, clk, rst, platform, start=1, clock_domain="bft"):
        self.source = PldAXIStreamInterface(data_width=32)
        self.sink = PldAXIStreamInterface(data_width=32)
        self.clk = clk
        self.rst = rst
        self.start = start
        self.platform = platform
        source_sigs = self.source.get_signals()
        sink_sigs = self.sink.get_signals()
        self.platform.add_source("rtl/rendering_6_page/rendering_mono.v")
        self.platform.add_source("rtl/rendering_6_page/regslice_core.v")
        self.platform.add_source("rtl/rendering_6_page/zculling_top_prj/leaf_7.v")
        self.platform.add_source("rtl/rendering_6_page/zculling_top_prj/zculling_top.v")
        self.platform.add_source(
            "rtl/rendering_6_page/zculling_top_prj/zculling_top_pixecud.v"
        )
        self.platform.add_source(
            "rtl/rendering_6_page/zculling_top_prj/zculling_top_z_bubkb.v"
        )
        self.platform.add_source("rtl/rendering_6_page/rasterization2_m_prj/leaf_6.v")
        self.platform.add_source(
            "rtl/rendering_6_page/rasterization2_m_prj/rasterization2_m.v"
        )
        self.platform.add_source(
            "rtl/rendering_6_page/rasterization2_m_prj/rasterization2_odd.v"
        )
        self.platform.add_source(
            "rtl/rendering_6_page/rasterization2_m_prj/rasterization2_even.v"
        )
        self.platform.add_source(
            "rtl/rendering_6_page/rasterization2_m_prj/rasterization2_odd_fragment_x_V_1.v"
        )
        self.platform.add_source(
            "rtl/rendering_6_page/rasterization2_m_prj/rasterization2_m_udiv_16ns_8ns_8_20_1.v"
        )
        self.platform.add_source(
            "rtl/rendering_6_page/rasterization2_m_prj/rasterization2_m_urem_16ns_8ns_8_20_1.v"
        )
        self.platform.add_source(
            "rtl/rendering_6_page/rasterization2_m_prj/rasterization2_m_am_submul_8ns_8ns_9s_18_1_1.v"
        )
        self.platform.add_source(
            "rtl/rendering_6_page/rasterization2_m_prj/rasterization2_m_ama_submul_sub_8ns_8ns_9s_18s_18_1_1.v"
        )
        self.platform.add_source("rtl/rendering_6_page/zculling_bot_prj/zculling_bot.v")
        self.platform.add_source(
            "rtl/rendering_6_page/zculling_bot_prj/zculling_bot_pixecud.v"
        )
        self.platform.add_source(
            "rtl/rendering_6_page/zculling_bot_prj/zculling_bot_z_bubkb.v"
        )
        self.platform.add_source("rtl/rendering_6_page/zculling_bot_prj/leaf_5.v")
        self.platform.add_source(
            "rtl/rendering_6_page/coloringFB_bot_m_prj/coloringFB_bot_m.v"
        )
        self.platform.add_source(
            "rtl/rendering_6_page/coloringFB_bot_m_prj/coloringFB_bot_m_bkb.v"
        )
        self.platform.add_source("rtl/rendering_6_page/coloringFB_bot_m_prj/leaf_4.v")
        self.platform.add_source(
            "rtl/rendering_6_page/data_redir_m_prj/data_redir_m_am_submul_8ns_8ns_9s_16_1_1.v"
        )
        self.platform.add_source(
            "rtl/rendering_6_page/data_redir_m_prj/data_redir_m_am_submul_8ns_8ns_9s_18_1_1.v"
        )
        self.platform.add_source("rtl/rendering_6_page/data_redir_m_prj/data_redir_m.v")
        self.platform.add_source(
            "rtl/rendering_6_page/data_redir_m_prj/projection_odd_m.v"
        )
        self.platform.add_source(
            "rtl/rendering_6_page/data_redir_m_prj/projection_even_m.v"
        )
        self.platform.add_source(
            "rtl/rendering_6_page/data_redir_m_prj/rasterization1_odd_m.v"
        )
        self.platform.add_source(
            "rtl/rendering_6_page/data_redir_m_prj/rasterization1_even_s.v"
        )
        self.platform.add_source("rtl/rendering_6_page/data_redir_m_prj/leaf_3.v")
        self.platform.add_source("rtl/rendering_6_page/coloringFB_top_m_prj/leaf_2.v")
        self.platform.add_source(
            "rtl/rendering_6_page/coloringFB_top_m_prj/coloringFB_top_m.v"
        )
        self.platform.add_source(
            "rtl/rendering_6_page/coloringFB_top_m_prj/coloringFB_top_m_bkb.v"
        )
        self.specials += Instance(
            "rendering_mono",
            i_ap_clk=self.clk,
            i_ap_rst=self.rst,
            i_ap_start=self.start,
            # stream interface
            i_Input_1_V_V=sink_sigs["tpayload"].data,
            i_Input_1_V_V_ap_vld=sink_sigs["tvalid"],
            o_Input_1_V_V_ap_ack=sink_sigs["tready"],
            o_Output_1_V_V=source_sigs["tpayload"].data,
            o_Output_1_V_V_ap_vld=source_sigs["tvalid"],
            i_Output_1_V_V_ap_ack=source_sigs["tready"],
        )

    def connect_input(self, stream):
        assert isinstance(stream, Endpoint)
        assert stream.payload.data.nbits == 32
        self.comb += stream.connect(self.sink)

    def connect_output(self, stream):
        assert isinstance(stream, Endpoint)
        assert stream.payload.data.nbits == 32
        self.comb += self.source.connect(stream)
