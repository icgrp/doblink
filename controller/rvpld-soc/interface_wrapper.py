from pld_axi import *
from litex.soc.interconnect.axi import AXIStreamInterface
from litex.soc.interconnect.stream import Converter, Endpoint
from migen import *

class InterfaceWrapper(Module):
    def __init__(self, clk, rst, platform):
        self.source = PldAXIStreamInterface(data_width=32)
        self.sink = PldAXIStreamInterface(data_width=32)
        self.clk = clk
        self.rst = rst
        self.resend = Signal(1, name='resend')
        self.din_leaf_bft2interface = Signal(49, name='din_leaf_bft2interface')
        self.dout_leaf_interface2bft = Signal(49, name='dout_leaf_interface2bft')
        self.platform = platform
        source_sigs = self.source.get_signals()
        sink_sigs = self.sink.get_signals()
        self.platform.add_source('rtl/leaf_interface/Config_Controls.v')
        self.platform.add_source('rtl/leaf_interface/converge_ctrl.v')
        self.platform.add_source('rtl/leaf_interface/ExtractCtrl.v')
        self.platform.add_source('rtl/leaf_interface/Input_Port_Cluster.v')
        self.platform.add_source('rtl/leaf_interface/Input_Port.v')
        self.platform.add_source('rtl/leaf_interface/leaf_interface.v')
        self.platform.add_source('rtl/leaf_interface/Output_Port_Cluster.v')
        self.platform.add_source('rtl/leaf_interface/Output_Port.v')
        self.platform.add_source('rtl/leaf_interface/read_b_in.v')
        self.platform.add_source('rtl/leaf_interface/Stream_Flow_Control.v')
        self.platform.add_source('rtl/leaf_interface/write_b_in.v')
        self.platform.add_source('rtl/leaf_interface/write_b_out.v')
        self.platform.add_source('rtl/leaf_interface/user_kernel.v')
        self.platform.add_source('rtl/leaf_interface/InterfaceWrapper.v')
        self.platform.add_source('rtl/leaf_interface/single_ram.v')
        self.platform.add_source('rtl/leaf_interface/ram0.v')
        self.specials += Instance("InterfaceWrapper1",
                            i_clk = self.clk,
                            i_reset = self.rst,
                            i_resend = self.resend,
                            #bft interface
                            i_din_leaf_bft2interface = self.din_leaf_bft2interface,
                            o_dout_leaf_interface2bft = self.dout_leaf_interface2bft,
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
