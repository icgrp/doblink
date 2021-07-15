from litex.soc.interconnect.axi import AXIStreamInterface, AXILiteInterface
from litex.soc.interconnect.stream import Converter, Endpoint, ClockDomainCrossing
from migen import *
from pld_axi import *
from axilite2bft import AxiLite2Bft
from bft import Bft
from axil_cdc import AxilCDC


class Leaf(Module):
    def __init__(self, clk, rst, start, platform):
        self.platform = platform
        self.clk = clk
        self.reset = rst
        self.start = start
        self.resend = 0
        self.din_leaf_bft2interface_1 = Signal(49, name='din_leaf_bft2interface_1')
        self.dout_leaf_interface2bft_1 = Signal(49, name='dout_leaf_interface2bft_1')
        self.din_leaf_bft2interface_2 = Signal(49, name='din_leaf_bft2interface_2')
        self.dout_leaf_interface2bft_2 = Signal(49, name='dout_leaf_interface2bft_2')

    def connect_input(self, din, dout):
        self.comb += self.din_leaf_bft2interface_1.eq(din)
        self.comb += dout.eq(self.dout_leaf_interface2bft_1)

    def connect_output(self, din, dout):
        self.comb += self.din_leaf_bft2interface_2.eq(din)
        self.comb += dout.eq(self.dout_leaf_interface2bft_2)


class Leaf2(Leaf):
    def __init__(self, clk, rst, start, platform):
        super().__init__(clk, rst, start, platform)
        self.specials += Instance('leaf_2',
                                  i_clk = self.clk,
                                  i_din_leaf_bft2interface_1 = self.din_leaf_bft2interface_1,
                                  o_dout_leaf_interface2bft_1 = self.dout_leaf_interface2bft_1,
                                  i_din_leaf_bft2interface_2 = self.din_leaf_bft2interface_2,
                                  o_dout_leaf_interface2bft_2 = self.dout_leaf_interface2bft_2,
                                  i_start = self.start,
                                  i_resend = self.resend,
                                  i_reset = self.reset
                                  )

class Leaf3(Leaf):
    def __init__(self, clk, rst, start, platform):
        super().__init__(clk, rst, start, platform)
        self.specials += Instance('leaf_3',
                                  i_clk = self.clk,
                                  i_din_leaf_bft2interface_1 = self.din_leaf_bft2interface_1,
                                  o_dout_leaf_interface2bft_1 = self.dout_leaf_interface2bft_1,
                                  i_din_leaf_bft2interface_2 = self.din_leaf_bft2interface_2,
                                  o_dout_leaf_interface2bft_2 = self.dout_leaf_interface2bft_2,
                                  i_start = self.start,
                                  i_resend = self.resend,
                                  i_reset = self.reset
                                  )

class Leaf4(Leaf):
    def __init__(self, clk, rst, start, platform):
        super().__init__(clk, rst, start, platform)
        self.specials += Instance('leaf_4',
                                  i_clk = self.clk,
                                  i_din_leaf_bft2interface_1 = self.din_leaf_bft2interface_1,
                                  o_dout_leaf_interface2bft_1 = self.dout_leaf_interface2bft_1,
                                  i_din_leaf_bft2interface_2 = self.din_leaf_bft2interface_2,
                                  o_dout_leaf_interface2bft_2 = self.dout_leaf_interface2bft_2,
                                  i_start = self.start,
                                  i_resend = self.resend,
                                  i_reset = self.reset
                                  )

class Leaf5(Leaf):
    def __init__(self, clk, rst, start, platform):
        super().__init__(clk, rst, start, platform)
        self.specials += Instance('leaf_5',
                                  i_clk = self.clk,
                                  i_din_leaf_bft2interface_1 = self.din_leaf_bft2interface_1,
                                  o_dout_leaf_interface2bft_1 = self.dout_leaf_interface2bft_1,
                                  i_din_leaf_bft2interface_2 = self.din_leaf_bft2interface_2,
                                  o_dout_leaf_interface2bft_2 = self.dout_leaf_interface2bft_2,
                                  i_start = self.start,
                                  i_resend = self.resend,
                                  i_reset = self.reset
                                  )

class InterfaceWrapperLeafOnly(Module):
    def __init__(self, clk, rst, platform, clock_domain='bft'):
        self.source = PldAXIStreamInterface(data_width=32)
        self.sink = PldAXIStreamInterface(data_width=32)
        self.clk = clk
        self.rst = rst
        self.resend = Signal(1, name='resend')
        self.din_leaf_bft2interface_1 = Signal(49, name='din_leaf_bft2interface_1')
        self.dout_leaf_interface2bft_1 = Signal(49, name='dout_leaf_interface2bft_1')
        self.din_leaf_bft2interface_2 = Signal(49, name='din_leaf_bft2interface_2')
        self.dout_leaf_interface2bft_2 = Signal(49, name='dout_leaf_interface2bft_2')
        self.platform = platform
        source_sigs = self.source.get_signals()
        sink_sigs = self.sink.get_signals()
        self.specials += Instance("InterfaceWrapperLeafOnly",
                            i_clk = self.clk,
                            i_reset = self.rst,
                            i_resend = self.resend,
                            #bft interface
                            i_din_leaf_bft2interface_1 = self.din_leaf_bft2interface_1,
                            o_dout_leaf_interface2bft_1 = self.dout_leaf_interface2bft_1,
                            i_din_leaf_bft2interface_2 = self.din_leaf_bft2interface_2,
                            o_dout_leaf_interface2bft_2 = self.dout_leaf_interface2bft_2,
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
        assert stream.payload.data.nbits == 32
        self.comb += stream.connect(self.sink)

    def connect_output(self, stream):
        assert isinstance(stream, Endpoint)
        assert stream.payload.data.nbits == 32
        self.comb += self.source.connect(stream)

class RenderingLeafOnly(Module):
    def __init__(self, clk, rst, platform, start=1, clock_domain='bft'):
        self.axil = AXILiteInterface(data_width=32, address_width=5, clock_domain=clock_domain)
        self.clk = clk
        self.rst = rst
        self.start = start
        self.platform = platform
        self.clock_domain = clock_domain
        self.submodules.interface_wrapper = interface_wrapper = InterfaceWrapperLeafOnly(clk, rst, platform)
        self.submodules.leaf_2 = leaf_2 = Leaf2(clk, rst, start, platform)
        # self.submodules.leaf_3 = leaf_3 = Leaf3(clk, rst, start, platform)
        # self.submodules.leaf_4 = leaf_4 = Leaf4(clk, rst, start, platform)
        # self.submodules.leaf_5 = leaf_5 = Leaf5(clk, rst, start, platform)

        data_1 = Signal(49)
        data_2 = Signal(49)
        data_3 = Signal(49)
        data_4 = Signal(49)
        data_5 = Signal(49)
        data_6 = Signal(49)
        data_7 = Signal(49)
        data_8 = Signal(49)
        data_9 = Signal(49)
        data_a = Signal(49)

        # interface_wrapper
        self.comb += data_1.eq(interface_wrapper.dout_leaf_interface2bft_1)
        self.comb += interface_wrapper.din_leaf_bft2interface_1.eq(data_3)

        self.comb += data_2.eq(interface_wrapper.dout_leaf_interface2bft_2)
        self.comb += interface_wrapper.din_leaf_bft2interface_2.eq(data_4)

        self.comb += interface_wrapper.resend.eq(0)

        # leaves
        leaf_2.connect_input(data_1, data_3)
        leaf_2.connect_output(data_2, data_4)

        # leaf_3.connect_input(data_6, data_5)
        # leaf_3.connect_output(data_7, data_8)

        # leaf_4.connect_input(data_8, data_7)
        # leaf_4.connect_output(data_9, data_a)

        # leaf_5.connect_input(data_a, data_9)
        # leaf_5.connect_output(data_2, data_4)

        self.platform.add_source_dir('rtl/leaf_interface/')
        self.platform.add_source_dir('rtl/rendering_leaf_only/')
        self.platform.add_source("rtl/SynFIFO.v")

    def connect_input(self, stream, clock_domain='sys'):
        assert isinstance(stream, Endpoint)
        input_stream = stream

        # if clock_domain != self.clock_domain:
        #     from IPython import embed; embed()
        #     self.submodules.input_cross_domain_converter = input_cross_domain_converter = \
        #         ClockDomainCrossing(input_stream.description, cd_from=clock_domain, cd_to=self.clock_domain, depth=8)
        #     mm2s_axis_bft = AXIStreamInterface(32)
        #     self.comb += input_stream.connect(input_cross_domain_converter.sink)
        #     self.comb += input_cross_domain_converter.source.connect(mm2s_axis_bft)
        #     input_stream = mm2s_axis_bft

        self.interface_wrapper.connect_input(input_stream)

    def connect_output(self, stream, clock_domain='sys'):
        assert isinstance(stream, Endpoint)
        output_stream = stream

        # if clock_domain != self.clock_domain:
        #     from IPython import embed; embed()
        #     self.submodules.output_cross_domain_converter = output_cross_domain_converter = \
        #         ClockDomainCrossing(output_stream.description, cd_from=self.clock_domain, cd_to=clock_domain, depth=8)
        #     s2mm_axis_bft = AXIStreamInterface(32)
        #     self.comb += output_cross_domain_converter.source.connect(output_stream)
        #     self.comb += s2mm_axis_bft.connect(output_cross_domain_converter.sink)
        #     output_stream = s2mm_axis_bft

        self.interface_wrapper.connect_output(output_stream)
