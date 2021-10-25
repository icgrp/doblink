from migen import *
from pld_axi import PldAXILiteInterface


class AxilCDC(Module):
    def __init__(
        self,
        s_clk,
        s_rst,
        m_clk,
        m_rst,
        platform,
        s_clock_domain="sys",
        m_clock_domain="sys",
    ):
        self.slave = PldAXILiteInterface(
            data_width=32, address_width=5, clock_domain=s_clock_domain
        )
        self.master = PldAXILiteInterface(
            data_width=32, address_width=5, clock_domain=m_clock_domain
        )
        self.s_clk = s_clk
        self.s_rst = s_rst
        self.m_clk = m_clk
        self.m_rst = m_rst
        self.platform = platform
        s_axil_sigs = self.slave.get_signals()
        m_axil_sigs = self.master.get_signals()
        self.platform.add_source("rtl/axil_cdc/axil_cdc.v")
        self.platform.add_source("rtl/axil_cdc/axil_cdc_rd.v")
        self.platform.add_source("rtl/axil_cdc/axil_cdc_wr.v")
        self.specials += Instance(
            "axil_cdc",
            i_s_clk=self.s_clk,
            i_s_rst=self.s_rst,
            i_s_axil_awaddr=s_axil_sigs["awaddr"],
            i_s_axil_awvalid=s_axil_sigs["awvalid"],
            o_s_axil_awready=s_axil_sigs["awready"],
            i_s_axil_wdata=s_axil_sigs["wdata"],
            i_s_axil_wstrb=s_axil_sigs["wstrb"],
            i_s_axil_wvalid=s_axil_sigs["wvalid"],
            o_s_axil_wready=s_axil_sigs["wready"],
            o_s_axil_bresp=s_axil_sigs["bresp"],
            o_s_axil_bvalid=s_axil_sigs["bvalid"],
            i_s_axil_bready=s_axil_sigs["bready"],
            i_s_axil_araddr=s_axil_sigs["araddr"],
            i_s_axil_arvalid=s_axil_sigs["arvalid"],
            o_s_axil_arready=s_axil_sigs["arready"],
            o_s_axil_rdata=s_axil_sigs["rdata"],
            o_s_axil_rresp=s_axil_sigs["rresp"],
            o_s_axil_rvalid=s_axil_sigs["rvalid"],
            i_s_axil_rready=s_axil_sigs["rready"],
            i_m_clk=self.m_clk,
            i_m_rst=self.m_rst,
            o_m_axil_awaddr=m_axil_sigs["awaddr"],
            o_m_axil_awvalid=m_axil_sigs["awvalid"],
            i_m_axil_awready=m_axil_sigs["awready"],
            o_m_axil_wdata=m_axil_sigs["wdata"],
            o_m_axil_wstrb=m_axil_sigs["wstrb"],
            o_m_axil_wvalid=m_axil_sigs["wvalid"],
            i_m_axil_wready=m_axil_sigs["wready"],
            i_m_axil_bresp=m_axil_sigs["bresp"],
            i_m_axil_bvalid=m_axil_sigs["bvalid"],
            o_m_axil_bready=m_axil_sigs["bready"],
            o_m_axil_araddr=m_axil_sigs["araddr"],
            o_m_axil_arvalid=m_axil_sigs["arvalid"],
            i_m_axil_arready=m_axil_sigs["arready"],
            i_m_axil_rdata=m_axil_sigs["rdata"],
            i_m_axil_rresp=m_axil_sigs["rresp"],
            i_m_axil_rvalid=m_axil_sigs["rvalid"],
            o_m_axil_rready=m_axil_sigs["rready"],
        )
