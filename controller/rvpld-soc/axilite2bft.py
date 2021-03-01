from pld_axi import PldAXILiteInterface
from migen import *

class AxiLite2Bft(Module):
    def __init__(self, clk, rst, platform, clock_domain):
        self.bus = PldAXILiteInterface(data_width=32, address_width=5, clock_domain=clock_domain)
        self.resend = Signal(1, name="resend")
        self.host_bft2interface = Signal(49, name="host_bft2interface")
        self.host_interface2bft = Signal(49, name="host_interface2bft")
        self.clk = clk
        self.rst = rst
        self.platform = platform
        axil_sigs = self.bus.get_signals()
        self.platform.add_source('rtl/AxiLite2Bft_v2_0.v')
        self.platform.add_source('rtl/SynFIFO.v')
        self.platform.add_source('rtl/gen_nw8.v')
        self.specials += Instance("AxiLite2Bft_v2_0",
                          i_resend = self.resend,
                          i_host_bft2interface = self.host_bft2interface,
                          o_host_interface2bft = self.host_interface2bft,
                          i_s00_axi_aclk = self.clk,
                          i_s00_axi_aresetn = self.rst,
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
