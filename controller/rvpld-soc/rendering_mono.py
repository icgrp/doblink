from pld_axi import *
from litex.soc.interconnect.axi import AXIStreamInterface
from litex.soc.interconnect.stream import Converter, Endpoint
from migen import *

class RenderingMono(Module):
    def __init__(self, clk, rst, platform):
        self.source = PldAXIStreamInterface(data_width=32)
        self.sink = PldAXIStreamInterface(data_width=32)
        self.clk = clk
        self.rst = rst
        self.platform = platform
        source_sigs = self.source.get_signals()
        sink_sigs = self.sink.get_signals()
        self.platform.add_source('rtl/rendering.v')
        self.platform.add_source('rtl/rendering_mono/zculling_z_buffer_V_ram.dat')
        self.specials += Instance("rendering_mono",
                            i_ap_clk = self.clk,
                            i_ap_rst = self.rst,
                            i_ap_start = 1,
                            #stream interface
                            i_Input_1_V_V = sink_sigs['tpayload'].data,
                            i_Input_1_V_V_ap_vld = sink_sigs['tvalid'],
                            o_Input_1_V_V_ap_ack = sink_sigs['tready'],
                            o_Output_1_V_V = source_sigs['tpayload'].data,
                            o_Output_1_V_V_ap_vld = source_sigs['tvalid'],
                            i_Output_1_V_V_ap_ack = source_sigs['tready'],
                            )

    def connect_input(self, stream):
        assert isinstance(stream, Endpoint)
        if stream.payload.data.nbits != 32:
            self.submodules.input_converter = input_converter = Converter(stream.payload.data.nbits, 32)
            self.comb += input_converter.source.connect(self.sink)
            self.comb += stream.connect(input_converter.sink)
        else:
            self.comb += stream.connect(self.sink)

    def connect_output(self, stream):
        assert isinstance(stream, Endpoint)
        if stream.payload.data.nbits != 32:
            self.submodules.output_converter = output_converter = Converter(32, stream.payload.data.nbits)
            self.comb += output_converter.source.connect(stream)
            self.comb += self.source.connect(output_converter.sink)
        else:
            self.comb += self.source.connect(stream)
