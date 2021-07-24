from litex.soc.interconnect.axi import AXIStreamInterface, AXILiteInterface
from litex.soc.interconnect.stream import Converter, Endpoint, ClockDomainCrossing
from migen import *
from pld_axi import *
from axilite2bft import AxiLite2Bft
from bft import Bft
from interface_wrapper import InterfaceWrapper
from axil_cdc import AxilCDC


class Leaf(Module):
    def __init__(self, clk, rst, start, platform):
        self.platform = platform
        self.clk = clk
        self.reset = rst
        self.start = start
        self.resend = Signal(1, name='resend')
        self.din_leaf_bft2interface = Signal(49, name='din_leaf_bft2interface')
        self.dout_leaf_interface2bft = Signal(49, name='dout_leaf_interface2bft')

    def connect(self, din, dout, resend):
        self.comb += self.din_leaf_bft2interface.eq(din)
        self.comb += dout.eq(self.dout_leaf_interface2bft)
        self.comb += self.resend.eq(resend)



class Leaf2(Leaf):
    def __init__(self, clk, rst, start, platform):
        super().__init__(clk, rst, start, platform)
        self.specials += Instance('leaf_2',
                                  i_clk = self.clk,
                                  i_din_leaf_bft2interface = self.din_leaf_bft2interface,
                                  o_dout_leaf_interface2bft = self.dout_leaf_interface2bft,
                                  i_resend = self.resend,
                                  i_ap_start = self.start,
                                  i_reset = self.reset
                                  )

class Leaf3(Leaf):
    def __init__(self, clk, rst, start, platform):
        super().__init__(clk, rst, start, platform)
        self.specials += Instance('leaf_3',
                                  i_clk = self.clk,
                                  i_din_leaf_bft2interface = self.din_leaf_bft2interface,
                                  o_dout_leaf_interface2bft = self.dout_leaf_interface2bft,
                                  i_resend = self.resend,
                                  i_ap_start = self.start,
                                  i_reset = self.reset
                                  )

class Leaf4(Leaf):
    def __init__(self, clk, rst, start, platform):
        super().__init__(clk, rst, start, platform)
        self.specials += Instance('leaf_4',
                                  i_clk = self.clk,
                                  i_din_leaf_bft2interface = self.din_leaf_bft2interface,
                                  o_dout_leaf_interface2bft = self.dout_leaf_interface2bft,
                                  i_resend = self.resend,
                                  i_ap_start = self.start,
                                  i_reset = self.reset
                                  )

class Leaf5(Leaf):
    def __init__(self, clk, rst, start, platform):
        super().__init__(clk, rst, start, platform)
        self.specials += Instance('leaf_5',
                                  i_clk = self.clk,
                                  i_din_leaf_bft2interface = self.din_leaf_bft2interface,
                                  o_dout_leaf_interface2bft = self.dout_leaf_interface2bft,
                                  i_resend = self.resend,
                                  i_ap_start = self.start,
                                  i_reset = self.reset
                                  )

class Leaf6(Leaf):
    def __init__(self, clk, rst, start, platform):
        super().__init__(clk, rst, start, platform)
        self.specials += Instance('leaf_6',
                                  i_clk = self.clk,
                                  i_din_leaf_bft2interface = self.din_leaf_bft2interface,
                                  o_dout_leaf_interface2bft = self.dout_leaf_interface2bft,
                                  i_resend = self.resend,
                                  i_ap_start = self.start,
                                  i_reset = self.reset
                                  )

class Leaf7(Leaf):
    def __init__(self, clk, rst, start, platform):
        super().__init__(clk, rst, start, platform)
        self.specials += Instance('leaf_7',
                                  i_clk = self.clk,
                                  i_din_leaf_bft2interface = self.din_leaf_bft2interface,
                                  o_dout_leaf_interface2bft = self.dout_leaf_interface2bft,
                                  i_resend = self.resend,
                                  i_ap_start = self.start,
                                  i_reset = self.reset
                                  )

class Leaf8(Leaf):
    def __init__(self, clk, rst, start, platform):
        super().__init__(clk, rst, start, platform)
        self.specials += Instance('leaf_8',
                                  i_clk = self.clk,
                                  i_din_leaf_bft2interface = self.din_leaf_bft2interface,
                                  o_dout_leaf_interface2bft = self.dout_leaf_interface2bft,
                                  i_resend = self.resend,
                                  i_ap_start = self.start,
                                  i_reset = self.reset
                                  )

class Leaf9(Leaf):
    def __init__(self, clk, rst, start, platform):
        super().__init__(clk, rst, start, platform)
        self.specials += Instance('leaf_9',
                                  i_clk = self.clk,
                                  i_din_leaf_bft2interface = self.din_leaf_bft2interface,
                                  o_dout_leaf_interface2bft = self.dout_leaf_interface2bft,
                                  i_resend = self.resend,
                                  i_ap_start = self.start,
                                  i_reset = self.reset
                                  )

class Leaf10(Leaf):
    def __init__(self, clk, rst, start, platform):
        super().__init__(clk, rst, start, platform)
        self.specials += Instance('leaf_10',
                                  i_clk = self.clk,
                                  i_din_leaf_bft2interface = self.din_leaf_bft2interface,
                                  o_dout_leaf_interface2bft = self.dout_leaf_interface2bft,
                                  i_resend = self.resend,
                                  i_ap_start = self.start,
                                  i_reset = self.reset
                                  )

class Leaf11(Leaf):
    def __init__(self, clk, rst, start, platform):
        super().__init__(clk, rst, start, platform)
        self.specials += Instance('leaf_11',
                                  i_clk = self.clk,
                                  i_din_leaf_bft2interface = self.din_leaf_bft2interface,
                                  o_dout_leaf_interface2bft = self.dout_leaf_interface2bft,
                                  i_resend = self.resend,
                                  i_ap_start = self.start,
                                  i_reset = self.reset
                                  )

class DigitRecognition10Page(Module):
    def __init__(self, clk, rst, platform, start=1, clock_domain='bft'):
        self.axil = AXILiteInterface(data_width=32, address_width=5, clock_domain=clock_domain)
        self.clk = clk
        self.rst = rst
        self.start = start
        self.platform = platform
        self.clock_domain = clock_domain
        self.submodules.axilite2bft = axilite2bft = AxiLite2Bft(clk, rst, platform, clock_domain)
        self.submodules.bft = bft = Bft(clk, rst, platform)
        self.submodules.interface_wrapper = interface_wrapper = InterfaceWrapper(clk, rst, platform)
        self.submodules.leaf_2 = leaf_2 = Leaf2(clk, rst, start, platform)
        self.submodules.leaf_3 = leaf_3 = Leaf3(clk, rst, start, platform)
        self.submodules.leaf_4 = leaf_4 = Leaf4(clk, rst, start, platform)
        self.submodules.leaf_5 = leaf_5 = Leaf5(clk, rst, start, platform)
        self.submodules.leaf_6 = leaf_6 = Leaf6(clk, rst, start, platform)
        self.submodules.leaf_7 = leaf_7 = Leaf7(clk, rst, start, platform)
        self.submodules.leaf_8 = leaf_8 = Leaf8(clk, rst, start, platform)
        self.submodules.leaf_9 = leaf_9 = Leaf9(clk, rst, start, platform)
        self.submodules.leaf_10 = leaf_10 = Leaf10(clk, rst, start, platform)
        self.submodules.leaf_11 = leaf_11 = Leaf11(clk, rst, start, platform)

        # axilite2bft
        self.comb += self.axil.connect(axilite2bft.bus)
        self.comb += axilite2bft.resend.eq(bft.resend_0)
        self.comb += axilite2bft.host_bft2interface.eq(bft.din_leaf_0)
        self.comb += bft.dout_leaf_0.eq(axilite2bft.host_interface2bft)

        # interface_wrapper
        self.comb += interface_wrapper.din_leaf_bft2interface.eq(bft.din_leaf_1)
        self.comb += bft.dout_leaf_1.eq(interface_wrapper.dout_leaf_interface2bft)
        self.comb += interface_wrapper.resend.eq(bft.resend_1)

        # leaves
        leaf_2.connect(bft.din_leaf_2, bft.dout_leaf_2, bft.resend_2)
        leaf_3.connect(bft.din_leaf_3, bft.dout_leaf_3, bft.resend_3)
        leaf_4.connect(bft.din_leaf_4, bft.dout_leaf_4, bft.resend_4)
        leaf_5.connect(bft.din_leaf_5, bft.dout_leaf_5, bft.resend_5)
        leaf_6.connect(bft.din_leaf_6, bft.dout_leaf_6, bft.resend_6)
        leaf_7.connect(bft.din_leaf_7, bft.dout_leaf_7, bft.resend_7)
        leaf_8.connect(bft.din_leaf_8, bft.dout_leaf_8, bft.resend_8)
        leaf_9.connect(bft.din_leaf_9, bft.dout_leaf_9, bft.resend_9)
        leaf_10.connect(bft.din_leaf_10, bft.dout_leaf_10, bft.resend_10)
        leaf_11.connect(bft.din_leaf_11, bft.dout_leaf_11, bft.resend_11)
        self.platform.add_source_dir('rtl/leaf_interface/')
        self.platform.add_source_dir('rtl/digit_recognition_pages/')

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

    def connect_axil(self, axil):
        assert isinstance(axil, AXILiteInterface)

        clock_domain = axil.clock_domain

        # if clock_domain != self.clock_domain:
        #     self.submodules.axil_cdc_sys2bft = axil_cdc_sys2bft = \
        #         AxilCDC(ClockSignal(clock_domain), ResetSignal(clock_domain), self.clk, self.rst, self.platform, clock_domain, self.clock_domain)
        #     self.comb += axil.connect(axil_cdc_sys2bft.slave)
        #     self.comb += axil_cdc_sys2bft.master.connect(self.axil)

        self.comb += axil.connect(self.axil)
