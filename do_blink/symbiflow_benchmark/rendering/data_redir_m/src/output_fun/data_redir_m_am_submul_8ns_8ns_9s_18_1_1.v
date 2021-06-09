// ==============================================================
// File generated on Fri Jan 15 16:19:46 EST 2021
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2018.3 (64-bit)
// SW Build 2405991 on Thu Dec  6 23:36:41 MST 2018
// IP Build 2404404 on Fri Dec  7 01:43:56 MST 2018
// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
// ==============================================================
`timescale 1 ns / 1 ps

module data_redir_m_am_submul_8ns_8ns_9s_18_1_1_DSP48_0(
    input  [8 - 1:0] in0,
    input  [8 - 1:0] in1,
    input  [9 - 1:0] in2,
    output [18 - 1:0]  dout);

wire signed [18 - 1:0]     b;
wire signed [27 - 1:0]     a;
wire signed [27 - 1:0]     d;
wire signed [45 - 1:0]     m;
wire signed [27 - 1:0]    ad;

assign a = $unsigned(in0);
assign d = $unsigned(in1);
assign b = $signed(in2);

assign ad = a - d;
assign m  = ad * b;

assign dout = m;

endmodule
`timescale 1 ns / 1 ps
module data_redir_m_am_submul_8ns_8ns_9s_18_1_1(
    din0,
    din1,
    din2,
    dout);

parameter ID = 32'd1;
parameter NUM_STAGE = 32'd1;
parameter din0_WIDTH = 32'd1;
parameter din1_WIDTH = 32'd1;
parameter din2_WIDTH = 32'd1;
parameter dout_WIDTH = 32'd1;
input[din0_WIDTH - 1:0] din0;
input[din1_WIDTH - 1:0] din1;
input[din2_WIDTH - 1:0] din2;
output[dout_WIDTH - 1:0] dout;



data_redir_m_am_submul_8ns_8ns_9s_18_1_1_DSP48_0 data_redir_m_am_submul_8ns_8ns_9s_18_1_1_DSP48_0_U(
    .in0( din0 ),
    .in1( din1 ),
    .in2( din2 ),
    .dout( dout ));

endmodule

