from pld_axi import *
from litedram.frontend.axi import LiteDRAMAXI2Native
from migen import *

class ZipDMAStream(Module):
    def __init__(self, dram_port, clk, rst, platform):
        self.mm2s_bus = PldAXILiteInterface(data_width=32, address_width=5)
        self.s2mm_bus = PldAXILiteInterface(data_width=32, address_width=5)
        self.port = dram_port;
        self.axi = PldAXIInterface(data_width=32, address_width=32)
        self.submodules.axi2native = LiteDRAMAXI2Native(self.axi, self.port)
        self.m_axis = PldAXIStreamInterface()
        self.s_axis = PldAXIStreamInterface()
        self.clk = clk
        self.rst = rst
        self.platform = platform

    def add_axi_mm2s(self):
        axil_sigs = self.mm2s_bus.get_signals()
        axi_sigs = self.axi.get_signals()
        axis_sigs = self.m_axis.get_signals()
        self.platform.add_source('rtl/aximm2s.v')
        self.specials += Instance("aximm2s",
                            i_S_AXI_ACLK = self.clk,
                            i_S_AXI_ARESETN = self.rst,
                            #stream interface
                            o_M_AXIS_TVALID = axis_sigs['tvalid'],
                            i_M_AXIS_TREADY = axis_sigs['tready'],
                            o_M_AXIS_TDATA = axis_sigs['tdata'],
                            o_M_AXIS_TLAST = axis_sigs['tlast'],
                            #control axil interface
                            i_S_AXIL_AWVALID = axil_sigs['awvalid'],
                            i_S_AXIL_AWADDR = axil_sigs['awaddr'],
                            o_S_AXIL_AWREADY = axil_sigs['awready'],
                            i_S_AXIL_WDATA = axil_sigs['wdata'],
                            i_S_AXIL_WSTRB = axil_sigs['wstrb'],
                            i_S_AXIL_WVALID = axil_sigs['wvalid'],
                            o_S_AXIL_WREADY = axil_sigs['wready'],
                            o_S_AXIL_BRESP = axil_sigs['bresp'],
                            o_S_AXIL_BVALID = axil_sigs['bvalid'],
                            o_S_AXIL_BREADY = axil_sigs['bready'],
                            i_S_AXIL_ARADDR = axil_sigs['araddr'],
                            i_S_AXIL_ARVALID = axil_sigs['arvalid'],
                            o_S_AXIL_ARREADY = axil_sigs['arready'],
                            o_S_AXIL_RDATA = axil_sigs['rdata'],
                            o_S_AXIL_RRESP = axil_sigs['rresp'],
                            o_S_AXIL_RVALID = axil_sigs['rvalid'],
                            i_S_AXIL_RREADY = axil_sigs['rready'],
                            # AXI (full) read interface
                            o_M_AXI_ARVALID = axi_sigs['arvalid'],
                            i_M_AXI_ARREADY = axi_sigs['arready'],
                            o_M_AXI_ARID = axi_sigs['arid'],
                            o_M_AXI_ARADDR = axi_sigs['araddr'],
                            o_M_AXI_ARLEN = axi_sigs['arlen'],
                            o_M_AXI_ARSIZE = axi_sigs['arsize'],
                            o_M_AXI_ARBURST = axi_sigs['arburst'],
                            o_M_AXI_ARLOCK = axi_sigs['arlock'],
                            o_M_AXI_ARCACHE = axi_sigs['arcache'],
                            o_M_AXI_ARPROT = axi_sigs['arprot'],
                            o_M_AXI_ARQOS = axi_sigs['arqos'],
                            i_M_AXI_RVALID = axi_sigs['rvalid'],
                            o_M_AXI_RREADY = axi_sigs['rready'],
                            i_M_AXI_RDATA = axi_sigs['rdata'],
                            i_M_AXI_RLAST = axi_sigs['rlast'],
                            i_M_AXI_RID = axi_sigs['rid'],
                            i_M_AXI_RRESP = axi_sigs['rresp'],
                            )

    def add_axi_s2mm(self):
        axil_sigs = self.s2mm_bus.get_signals()
        axi_sigs = self.axi.get_signals()
        axis_sigs = self.s_axis.get_signals()
        self.platform.add_source('rtl/axis2mm.v')
        self.specials += Instance("axis2mm",
                            i_S_AXI_ACLK = self.clk,
                            i_S_AXI_ARESETN = self.rst,
                            #stream interface
                            o_M_AXIS_TVALID = axis_sigs['tvalid'],
                            i_M_AXIS_TREADY = axis_sigs['tready'],
                            o_M_AXIS_TDATA = axis_sigs['tdata'],
                            o_M_AXIS_TLAST = axis_sigs['tlast'],
                            #control axil interface
                            i_S_AXIL_AWVALID = axil_sigs['awvalid'],
                            i_S_AXIL_AWADDR = axil_sigs['awaddr'],
                            o_S_AXIL_AWREADY = axil_sigs['awready'],
                            i_S_AXIL_WDATA = axil_sigs['wdata'],
                            i_S_AXIL_WSTRB = axil_sigs['wstrb'],
                            i_S_AXIL_WVALID = axil_sigs['wvalid'],
                            o_S_AXIL_WREADY = axil_sigs['wready'],
                            o_S_AXIL_BRESP = axil_sigs['bresp'],
                            o_S_AXIL_BVALID = axil_sigs['bvalid'],
                            o_S_AXIL_BREADY = axil_sigs['bready'],
                            i_S_AXIL_ARADDR = axil_sigs['araddr'],
                            i_S_AXIL_ARVALID = axil_sigs['arvalid'],
                            o_S_AXIL_ARREADY = axil_sigs['arready'],
                            o_S_AXIL_RDATA = axil_sigs['rdata'],
                            o_S_AXIL_RRESP = axil_sigs['rresp'],
                            o_S_AXIL_RVALID = axil_sigs['rvalid'],
                            i_S_AXIL_RREADY = axil_sigs['rready'],
                            # AXI (full) read interface
                            o_M_AXI_ARVALID = axi_sigs['arvalid'],
                            i_M_AXI_ARREADY = axi_sigs['arready'],
                            o_M_AXI_ARID = axi_sigs['arid'],
                            o_M_AXI_ARADDR = axi_sigs['araddr'],
                            o_M_AXI_ARLEN = axi_sigs['arlen'],
                            o_M_AXI_ARSIZE = axi_sigs['arsize'],
                            o_M_AXI_ARBURST = axi_sigs['arburst'],
                            o_M_AXI_ARLOCK = axi_sigs['arlock'],
                            o_M_AXI_ARCACHE = axi_sigs['arcache'],
                            o_M_AXI_ARPROT = axi_sigs['arprot'],
                            o_M_AXI_ARQOS = axi_sigs['arqos'],
                            i_M_AXI_RVALID = axi_sigs['rvalid'],
                            o_M_AXI_RREADY = axi_sigs['rready'],
                            i_M_AXI_RDATA = axi_sigs['rdata'],
                            i_M_AXI_RLAST = axi_sigs['rlast'],
                            i_M_AXI_RID = axi_sigs['rid'],
                            i_M_AXI_RRESP = axi_sigs['rresp'],
                            )
