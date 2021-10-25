from pld_axi import *
from litex.soc.interconnect.axi import AXIStreamInterface
from litex.soc.interconnect.stream import Converter, Endpoint
from migen import *


class InterfaceWrapper(Module):
    def __init__(self, clk, rst, platform, clock_domain="bft"):
        self.source = PldAXIStreamInterface(data_width=32)
        self.sink = PldAXIStreamInterface(data_width=32)
        self.clk = clk
        self.rst = rst
        self.resend = Signal(1, name="resend")
        self.din_leaf_bft2interface = Signal(49, name="din_leaf_bft2interface")
        self.dout_leaf_interface2bft = Signal(49, name="dout_leaf_interface2bft")
        self.platform = platform
        source_sigs = self.source.get_signals()
        sink_sigs = self.sink.get_signals()
        self.specials += Instance(
            "InterfaceWrapper1",
            i_clk=self.clk,
            i_reset=self.rst,
            i_resend=self.resend,
            # bft interface
            i_din_leaf_bft2interface=self.din_leaf_bft2interface,
            o_dout_leaf_interface2bft=self.dout_leaf_interface2bft,
            # stream interface
            i_Input_1_V_V=sink_sigs["tpayload"].data,
            i_Input_1_V_V_ap_vld=sink_sigs["tvalid"],
            o_Input_1_V_V_ap_ack=sink_sigs["tready"],
            o_Output_1_V_V=source_sigs["tpayload"].data,
            o_Output_1_V_V_ap_vld=source_sigs["tvalid"],
            # i_Output_1_V_V_ap_ack = 1,
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
