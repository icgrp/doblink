from litex.soc.interconnect.axi import AXIStreamInterface
from litex.soc.interconnect.stream import Converter, Endpoint
from migen import *
from pld_axi import *


class ArrayMono(Module):
    def __init__(self, clk, rst, platform, start=1, clock_domain="bft"):
        self.source = PldAXIStreamInterface(data_width=32)
        self.sink = PldAXIStreamInterface(data_width=32)
        self.clk = clk
        self.rst = rst
        self.start = start
        self.platform = platform
        source_sigs = self.source.get_signals()
        sink_sigs = self.sink.get_signals()
        # self.platform.add_source_dir('rtl/rendering_4_debug')
        self.platform.add_source_dir("rtl/array_partition")
        # self.platform.add_source_dir('rtl/user_fifo')
        self.specials += Instance(
            "array_mono",
            i_ap_clk=self.clk,
            i_ap_rst_n=~self.rst,
            i_ap_start=self.start,
            # stream interface
            i_Input_1_V_TDATA=sink_sigs["tpayload"].data,
            i_Input_1_V_TVALID=sink_sigs["tvalid"],
            o_Input_1_V_TREADY=sink_sigs["tready"],
            o_Output_1_V_TDATA=source_sigs["tpayload"].data,
            o_Output_1_V_TVALID=source_sigs["tvalid"],
            i_Output_1_V_TREADY=source_sigs["tready"],
        )

    def connect_input(self, stream):
        assert isinstance(stream, Endpoint)
        self.comb += stream.connect(self.sink)

    def connect_output(self, stream):
        assert isinstance(stream, Endpoint)
        self.comb += self.source.connect(stream)
