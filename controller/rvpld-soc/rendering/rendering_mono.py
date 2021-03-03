from pld_axi import *
from litex.soc.interconnect.axi import AXIStreamInterface
from litex.soc.interconnect.stream import Converter, Endpoint
from migen import *

class RenderingMono(Module):
    def __init__(self, clk, rst, platform, clock_domain='bft'):
        self.source = PldAXIStreamInterface(data_width=32)
        self.sink = PldAXIStreamInterface(data_width=32)
        self.clk = clk
        self.rst = rst
        self.platform = platform
        source_sigs = self.source.get_signals()
        sink_sigs = self.sink.get_signals()
        self.platform.add_source('rtl/rendering_mono/rendering.v')
        self.platform.add_source('rtl/rendering_mono/rendering_m_zculling_top_z_buffer_V_ram.dat')
        self.platform.add_source('rtl/rendering_mono/rendering_m_rasterization2_odd_fragment_color_V_ram.dat')
        self.platform.add_source('rtl/rendering_mono/rendering_m_rasterization2_odd_fragment_x_V_ram.dat')
        self.platform.add_source('rtl/rendering_mono/rendering_m_coloringFB_bot_m_frame_buffer_V_ram.dat')
        self.specials += Instance("rendering_m",
                            i_ap_clk = self.clk,
                            i_ap_rst_n = ~self.rst,
                            i_ap_start = 1,
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
        if stream.payload.data.nbits != 32:
            self.submodules.input_converter = input_converter = Converter(stream.payload.data.nbits, 32, reverse=True)
            self.comb += input_converter.source.connect(self.sink)
            self.comb += stream.connect(input_converter.sink)
        else:
            self.comb += stream.connect(self.sink)

    def connect_output(self, stream):
        assert isinstance(stream, Endpoint)
        if stream.payload.data.nbits != 32:
            self.submodules.output_converter = output_converter = Converter(32, stream.payload.data.nbits, reverse=True)
            self.comb += output_converter.source.connect(stream)
            self.comb += self.source.connect(output_converter.sink)
        else:
            self.comb += self.source.connect(stream)
