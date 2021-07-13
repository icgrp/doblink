from litex.soc.interconnect.axi import AXIStreamInterface, AXILiteInterface
from litex.soc.interconnect.stream import Converter, Endpoint, ClockDomainCrossing
from migen import *
from pld_axi import *
from axilite2bft import AxiLite2Bft
from bft import Bft
from interface_wrapper import InterfaceWrapper
from axil_cdc import AxilCDC


class Rendering6MonoVitis(Module):
    def __init__(self, clk, rst, platform, start=1, clock_domain='bft'):
        self.source = PldAXIStreamInterface(data_width=32)
        self.sink = PldAXIStreamInterface(data_width=32)
        self.clk = clk
        self.rst = rst
        self.start = start
        self.platform = platform
        source_sigs = self.source.get_signals()
        sink_sigs = self.sink.get_signals()
        self.platform.add_source_dir('rtl/rendering_6_page_new')
        self.specials += Instance("rendering_mono",
                            i_ap_clk = self.clk,
                            i_ap_rst_n = ~self.rst,
                            i_ap_start = self.start,
                            #stream interface
                            i_Input_1_V_TDATA = sink_sigs['tpayload'].data,
                            i_Input_1_V_TVALID = sink_sigs['tvalid'],
                            o_Input_1_V_TREADY = sink_sigs['tready'],
                            o_Output_1_V_TDATA = source_sigs['tpayload'].data,
                            o_Output_1_V_TVALID = source_sigs['tvalid'],
                            i_Output_1_V_TREADY = source_sigs['tready'],
                            )

    def connect_input(self, stream):
        assert isinstance(stream, Endpoint)
        assert stream.payload.data.nbits == 32
        self.comb += stream.connect(self.sink)

    def connect_output(self, stream):
        assert isinstance(stream, Endpoint)
        assert stream.payload.data.nbits == 32
        self.comb += self.source.connect(stream)
