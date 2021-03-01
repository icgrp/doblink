from pld_axi import PldAXILiteInterface
from migen import *

class Bft(Module):
    def __init__(self, clk, rst, platform, clock_domain):
        self.bus = PldAXILiteInterface(data_width=32, address_width=5, clock_domain=clock_domain)
        self.clk = clk
        self.rst = rst
        self.dout_leaf_0 = Signal(49, name='dout_leaf_0')
        self.dout_leaf_1 = Signal(49, name='dout_leaf_1')
        self.dout_leaf_2 = Signal(49, name='dout_leaf_2')
        self.dout_leaf_3 = Signal(49, name='dout_leaf_3')
        self.dout_leaf_4 = Signal(49, name='dout_leaf_4')
        self.dout_leaf_5 = Signal(49, name='dout_leaf_5')
        self.dout_leaf_6 = Signal(49, name='dout_leaf_6')
        self.dout_leaf_7 = Signal(49, name='dout_leaf_7')
        self.din_leaf_0 = Signal(49, name='din_leaf_0')
        self.din_leaf_1 = Signal(49, name='din_leaf_1')
        self.din_leaf_2 = Signal(49, name='din_leaf_2')
        self.din_leaf_3 = Signal(49, name='din_leaf_3')
        self.din_leaf_4 = Signal(49, name='din_leaf_4')
        self.din_leaf_5 = Signal(49, name='din_leaf_5')
        self.din_leaf_6 = Signal(49, name='din_leaf_6')
        self.din_leaf_7 = Signal(49, name='din_leaf_7')
        self.resend_0 = Signal(1, name='resend_0')
        self.resend_1 = Signal(1, name='resend_1')
        self.resend_2 = Signal(1, name='resend_2')
        self.resend_3 = Signal(1, name='resend_3')
        self.resend_4 = Signal(1, name='resend_4')
        self.resend_5 = Signal(1, name='resend_5')
        self.resend_6 = Signal(1, name='resend_6')
        self.resend_7 = Signal(1, name='resend_7')
        self.platform = platform

        axil_sigs = self.bus.get_signals()
        self.platform.add_source('rtl/bft.v')
        self.specials += Instance("bft",
                          i_clk = self.clk,
                          i_reset = self.rst,
                          i_dout_leaf_0 = self.dout_leaf_0,
                          i_dout_leaf_1 = self.dout_leaf_1,
                          i_dout_leaf_2 = self.dout_leaf_2,
                          i_dout_leaf_3 = self.dout_leaf_3,
                          i_dout_leaf_4 = self.dout_leaf_4,
                          i_dout_leaf_5 = self.dout_leaf_5,
                          i_dout_leaf_6 = self.dout_leaf_6,
                          i_dout_leaf_7 = self.dout_leaf_7,
                          o_din_leaf_0 = self.din_leaf_0,
                          o_din_leaf_1 = self.din_leaf_1,
                          o_din_leaf_2 = self.din_leaf_2,
                          o_din_leaf_3 = self.din_leaf_3,
                          o_din_leaf_4 = self.din_leaf_4,
                          o_din_leaf_5 = self.din_leaf_5,
                          o_din_leaf_6 = self.din_leaf_6,
                          o_din_leaf_7 = self.din_leaf_7,
                          o_resend_0 = self.resend_0,
                          o_resend_1 = self.resend_1,
                          o_resend_2 = self.resend_2,
                          o_resend_3 = self.resend_3,
                          o_resend_4 = self.resend_4,
                          o_resend_5 = self.resend_5,
                          o_resend_6 = self.resend_6,
                          o_resend_7 = self.resend_7,
                          )
