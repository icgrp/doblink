// ==============================================================
// RTL generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC
// Version: 2018.3
// Copyright (C) 1986-2018 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

`timescale 1 ns / 1 ps 

module rasterization1_even_s (
        ap_clk,
        ap_rst,
        ap_start,
        ap_done,
        ap_idle,
        ap_ready,
        triangle_2d_x0_V,
        triangle_2d_y0_V,
        triangle_2d_x1_V,
        triangle_2d_y1_V,
        triangle_2d_x2_V,
        triangle_2d_y2_V,
        triangle_2d_z_V,
        Output_1_V_V,
        Output_1_V_V_ap_vld,
        Output_1_V_V_ap_ack
);

parameter    ap_ST_fsm_state1 = 28'd1;
parameter    ap_ST_fsm_state2 = 28'd2;
parameter    ap_ST_fsm_state3 = 28'd4;
parameter    ap_ST_fsm_state4 = 28'd8;
parameter    ap_ST_fsm_state5 = 28'd16;
parameter    ap_ST_fsm_state6 = 28'd32;
parameter    ap_ST_fsm_state7 = 28'd64;
parameter    ap_ST_fsm_state8 = 28'd128;
parameter    ap_ST_fsm_state9 = 28'd256;
parameter    ap_ST_fsm_state10 = 28'd512;
parameter    ap_ST_fsm_state11 = 28'd1024;
parameter    ap_ST_fsm_state12 = 28'd2048;
parameter    ap_ST_fsm_state13 = 28'd4096;
parameter    ap_ST_fsm_state14 = 28'd8192;
parameter    ap_ST_fsm_state15 = 28'd16384;
parameter    ap_ST_fsm_state16 = 28'd32768;
parameter    ap_ST_fsm_state17 = 28'd65536;
parameter    ap_ST_fsm_state18 = 28'd131072;
parameter    ap_ST_fsm_state19 = 28'd262144;
parameter    ap_ST_fsm_state20 = 28'd524288;
parameter    ap_ST_fsm_state21 = 28'd1048576;
parameter    ap_ST_fsm_state22 = 28'd2097152;
parameter    ap_ST_fsm_state23 = 28'd4194304;
parameter    ap_ST_fsm_state24 = 28'd8388608;
parameter    ap_ST_fsm_state25 = 28'd16777216;
parameter    ap_ST_fsm_state26 = 28'd33554432;
parameter    ap_ST_fsm_state27 = 28'd67108864;
parameter    ap_ST_fsm_state28 = 28'd134217728;

input   ap_clk;
input   ap_rst;
input   ap_start;
output   ap_done;
output   ap_idle;
output   ap_ready;
input  [7:0] triangle_2d_x0_V;
input  [7:0] triangle_2d_y0_V;
input  [7:0] triangle_2d_x1_V;
input  [7:0] triangle_2d_y1_V;
input  [7:0] triangle_2d_x2_V;
input  [7:0] triangle_2d_y2_V;
input  [7:0] triangle_2d_z_V;
output  [31:0] Output_1_V_V;
output   Output_1_V_V_ap_vld;
input   Output_1_V_V_ap_ack;

reg ap_done;
reg ap_idle;
reg ap_ready;
reg[31:0] Output_1_V_V;
reg Output_1_V_V_ap_vld;

(* fsm_encoding = "none" *) reg   [27:0] ap_CS_fsm;
wire    ap_CS_fsm_state1;
reg   [7:0] max_min_V_0;
reg   [7:0] max_min_V_1;
reg   [7:0] max_min_V_2;
reg   [15:0] max_index_V_0;
reg   [7:0] max_min_V_3;
reg   [7:0] max_min_V_4;
reg    Output_1_V_V_blk_n;
wire    ap_CS_fsm_state3;
wire   [0:0] tmp_s_fu_146_p2;
wire    ap_CS_fsm_state17;
wire    ap_CS_fsm_state18;
wire    ap_CS_fsm_state19;
wire    ap_CS_fsm_state20;
wire    ap_CS_fsm_state21;
wire    ap_CS_fsm_state22;
wire    ap_CS_fsm_state23;
wire    ap_CS_fsm_state24;
wire    ap_CS_fsm_state25;
wire    ap_CS_fsm_state26;
wire    ap_CS_fsm_state27;
wire    ap_CS_fsm_state28;
wire    ap_CS_fsm_state16;
reg   [0:0] tmp_s_reg_594;
wire    ap_CS_fsm_state4;
wire    ap_CS_fsm_state5;
wire    ap_CS_fsm_state6;
wire    ap_CS_fsm_state7;
wire    ap_CS_fsm_state8;
wire    ap_CS_fsm_state9;
wire    ap_CS_fsm_state10;
wire    ap_CS_fsm_state11;
wire    ap_CS_fsm_state12;
wire    ap_CS_fsm_state13;
wire    ap_CS_fsm_state14;
wire    ap_CS_fsm_state15;
wire   [8:0] rhs_V_6_fu_98_p1;
reg   [8:0] rhs_V_6_reg_537;
wire   [8:0] ret_V_9_fu_102_p2;
reg  signed [8:0] ret_V_9_reg_542;
wire   [8:0] rhs_V_7_fu_108_p1;
reg   [8:0] rhs_V_7_reg_547;
wire   [8:0] ret_V_12_fu_116_p2;
reg  signed [8:0] ret_V_12_reg_552;
wire    ap_CS_fsm_state2;
wire  signed [17:0] grp_fu_473_p3;
reg  signed [17:0] ret_V_11_reg_569;
wire   [16:0] tmp_fu_129_p1;
reg   [16:0] tmp_reg_574;
wire  signed [17:0] grp_fu_481_p3;
reg  signed [17:0] ret_V_14_reg_579;
wire   [16:0] tmp_8_fu_139_p1;
reg   [16:0] tmp_8_reg_584;
reg    ap_block_state3_io;
reg   [7:0] max_min_V_0_load_reg_598;
reg   [7:0] max_min_V_1_load_reg_603;
reg   [7:0] max_min_V_2_load_reg_608;
wire   [7:0] triangle_2d_same_x0_s_fu_170_p3;
reg   [7:0] triangle_2d_same_x0_s_reg_613;
wire   [7:0] triangle_2d_same_y0_s_fu_176_p3;
reg   [7:0] triangle_2d_same_y0_s_reg_624;
wire   [7:0] triangle_2d_same_x1_s_fu_182_p3;
reg   [7:0] triangle_2d_same_x1_s_reg_635;
wire   [7:0] triangle_2d_same_y1_s_fu_188_p3;
reg   [7:0] triangle_2d_same_y1_s_reg_646;
wire   [7:0] agg_result_V_i_fu_234_p3;
reg   [7:0] agg_result_V_i_reg_657;
wire   [7:0] agg_result_V_i4_fu_272_p3;
reg   [7:0] agg_result_V_i4_reg_664;
wire   [7:0] agg_result_V_i5_fu_314_p3;
reg   [7:0] agg_result_V_i5_reg_671;
wire   [7:0] agg_result_V_i6_fu_352_p3;
reg   [7:0] agg_result_V_i6_reg_677;
wire   [8:0] ret_V_fu_376_p2;
reg  signed [8:0] ret_V_reg_683;
wire   [7:0] tmp_9_fu_408_p2;
reg   [7:0] tmp_9_reg_688;
wire  signed [15:0] grp_fu_489_p3;
wire   [31:0] tmp_V_24_fu_194_p1;
wire   [31:0] tmp_V_25_fu_198_p1;
wire   [31:0] tmp_V_26_fu_202_p1;
wire   [31:0] tmp_V_27_fu_206_p1;
wire   [31:0] tmp_V_28_fu_286_p1;
wire   [31:0] tmp_V_29_fu_366_p1;
wire   [31:0] tmp_V_30_fu_382_p1;
wire   [31:0] tmp_V_31_fu_400_p1;
wire   [31:0] tmp_V_32_fu_404_p1;
wire   [31:0] tmp_V_33_fu_418_p1;
wire   [31:0] tmp_V_34_fu_422_p1;
wire   [31:0] tmp_V_35_fu_426_p1;
wire   [31:0] tmp_V_36_fu_430_p1;
wire   [31:0] tmp_V_23_fu_438_p1;
wire   [31:0] tmp_V_fu_447_p1;
wire   [31:0] tmp_V_19_fu_452_p1;
wire   [31:0] tmp_V_20_fu_456_p1;
wire   [31:0] tmp_V_21_fu_460_p1;
wire   [31:0] tmp_V_22_fu_468_p1;
reg    ap_block_state16_io;
wire   [8:0] lhs_V_8_fu_94_p1;
wire   [8:0] lhs_V_11_fu_112_p1;
(* use_dsp48 = "no" *) wire   [17:0] ret_V_15_fu_142_p2;
wire   [0:0] tmp_10_fu_162_p3;
wire   [0:0] tmp_i_10_fu_214_p2;
wire   [0:0] tmp_4_i_fu_224_p2;
wire   [0:0] tmp_i_fu_210_p2;
wire   [7:0] in0_V_in2_V_i_fu_218_p3;
wire   [7:0] in1_V_in2_V_i_fu_228_p3;
wire   [0:0] tmp_i4_11_fu_252_p2;
wire   [0:0] tmp_5_i_fu_262_p2;
wire   [0:0] tmp_i4_fu_248_p2;
wire   [7:0] in0_V_in2_V_i4_fu_256_p3;
wire   [7:0] in1_V_in2_V_i4_fu_266_p3;
wire   [0:0] tmp_i5_12_fu_294_p2;
wire   [0:0] tmp_4_i2_fu_304_p2;
wire   [0:0] tmp_i5_fu_290_p2;
wire   [7:0] in0_V_in2_V_i5_fu_298_p3;
wire   [7:0] in1_V_in2_V_i5_fu_308_p3;
wire   [0:0] tmp_i6_13_fu_332_p2;
wire   [0:0] tmp_5_i2_fu_342_p2;
wire   [0:0] tmp_i6_fu_328_p2;
wire   [7:0] in0_V_in2_V_i6_fu_336_p3;
wire   [7:0] in1_V_in2_V_i6_fu_346_p3;
wire   [8:0] lhs_V_fu_370_p1;
wire   [8:0] rhs_V_fu_373_p1;
wire   [7:0] grp_fu_473_p0;
wire   [7:0] grp_fu_473_p1;
wire   [7:0] grp_fu_481_p0;
wire   [7:0] grp_fu_481_p1;
wire   [7:0] grp_fu_489_p0;
wire   [7:0] grp_fu_489_p1;
reg   [27:0] ap_NS_fsm;
wire   [8:0] grp_fu_473_p00;
wire   [8:0] grp_fu_481_p00;
wire   [8:0] grp_fu_489_p00;
wire   [8:0] grp_fu_489_p10;

// power-on initialization
initial begin
#0 ap_CS_fsm = 28'd1;
#0 max_min_V_0 = 8'd0;
#0 max_min_V_1 = 8'd0;
#0 max_min_V_2 = 8'd0;
#0 max_index_V_0 = 16'd0;
#0 max_min_V_3 = 8'd0;
#0 max_min_V_4 = 8'd0;
end

data_redir_m_am_submul_8ns_8ns_9s_18_1_1 #(
    .ID( 1 ),
    .NUM_STAGE( 1 ),
    .din0_WIDTH( 8 ),
    .din1_WIDTH( 8 ),
    .din2_WIDTH( 9 ),
    .dout_WIDTH( 18 ))
data_redir_m_am_submul_8ns_8ns_9s_18_1_1_U20(
    .din0(grp_fu_473_p0),
    .din1(grp_fu_473_p1),
    .din2(ret_V_9_reg_542),
    .dout(grp_fu_473_p3)
);

data_redir_m_am_submul_8ns_8ns_9s_18_1_1 #(
    .ID( 1 ),
    .NUM_STAGE( 1 ),
    .din0_WIDTH( 8 ),
    .din1_WIDTH( 8 ),
    .din2_WIDTH( 9 ),
    .dout_WIDTH( 18 ))
data_redir_m_am_submul_8ns_8ns_9s_18_1_1_U21(
    .din0(grp_fu_481_p0),
    .din1(grp_fu_481_p1),
    .din2(ret_V_12_reg_552),
    .dout(grp_fu_481_p3)
);

data_redir_m_am_submul_8ns_8ns_9s_16_1_1 #(
    .ID( 1 ),
    .NUM_STAGE( 1 ),
    .din0_WIDTH( 8 ),
    .din1_WIDTH( 8 ),
    .din2_WIDTH( 9 ),
    .dout_WIDTH( 16 ))
data_redir_m_am_submul_8ns_8ns_9s_16_1_1_U22(
    .din0(grp_fu_489_p0),
    .din1(grp_fu_489_p1),
    .din2(ret_V_reg_683),
    .dout(grp_fu_489_p3)
);

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_CS_fsm <= ap_ST_fsm_state1;
    end else begin
        ap_CS_fsm <= ap_NS_fsm;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state8))) begin
        agg_result_V_i4_reg_664 <= agg_result_V_i4_fu_272_p3;
        agg_result_V_i_reg_657 <= agg_result_V_i_fu_234_p3;
        max_min_V_0 <= agg_result_V_i_fu_234_p3;
        max_min_V_1 <= agg_result_V_i4_fu_272_p3;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state9))) begin
        agg_result_V_i5_reg_671 <= agg_result_V_i5_fu_314_p3;
        agg_result_V_i6_reg_677 <= agg_result_V_i6_fu_352_p3;
        max_min_V_2 <= agg_result_V_i5_fu_314_p3;
        max_min_V_3 <= agg_result_V_i6_fu_352_p3;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state11))) begin
        max_index_V_0 <= grp_fu_489_p3;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b0 == ap_block_state3_io) & (1'b1 == ap_CS_fsm_state3))) begin
        max_min_V_0_load_reg_598 <= max_min_V_0;
        max_min_V_1_load_reg_603 <= max_min_V_1;
        max_min_V_2_load_reg_608 <= max_min_V_2;
        tmp_s_reg_594 <= tmp_s_fu_146_p2;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state13))) begin
        max_min_V_4 <= tmp_9_fu_408_p2;
        tmp_9_reg_688 <= tmp_9_fu_408_p2;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state2)) begin
        ret_V_11_reg_569 <= grp_fu_473_p3;
        ret_V_14_reg_579 <= grp_fu_481_p3;
        tmp_8_reg_584 <= tmp_8_fu_139_p1;
        tmp_reg_574 <= tmp_fu_129_p1;
    end
end

always @ (posedge ap_clk) begin
    if (((ap_start == 1'b1) & (1'b1 == ap_CS_fsm_state1))) begin
        ret_V_12_reg_552 <= ret_V_12_fu_116_p2;
        ret_V_9_reg_542 <= ret_V_9_fu_102_p2;
        rhs_V_6_reg_537[7 : 0] <= rhs_V_6_fu_98_p1[7 : 0];
        rhs_V_7_reg_547[7 : 0] <= rhs_V_7_fu_108_p1[7 : 0];
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state10))) begin
        ret_V_reg_683 <= ret_V_fu_376_p2;
    end
end

always @ (posedge ap_clk) begin
    if (((tmp_s_fu_146_p2 == 1'd0) & (1'b0 == ap_block_state3_io) & (1'b1 == ap_CS_fsm_state3))) begin
        triangle_2d_same_x0_s_reg_613 <= triangle_2d_same_x0_s_fu_170_p3;
        triangle_2d_same_x1_s_reg_635 <= triangle_2d_same_x1_s_fu_182_p3;
        triangle_2d_same_y0_s_reg_624 <= triangle_2d_same_y0_s_fu_176_p3;
        triangle_2d_same_y1_s_reg_646 <= triangle_2d_same_y1_s_fu_188_p3;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state28)) begin
        Output_1_V_V = tmp_V_22_fu_468_p1;
    end else if ((1'b1 == ap_CS_fsm_state27)) begin
        Output_1_V_V = tmp_V_21_fu_460_p1;
    end else if ((1'b1 == ap_CS_fsm_state26)) begin
        Output_1_V_V = tmp_V_20_fu_456_p1;
    end else if ((1'b1 == ap_CS_fsm_state25)) begin
        Output_1_V_V = tmp_V_19_fu_452_p1;
    end else if ((1'b1 == ap_CS_fsm_state24)) begin
        Output_1_V_V = tmp_V_fu_447_p1;
    end else if (((tmp_s_reg_594 == 1'd1) & (1'b1 == ap_CS_fsm_state16))) begin
        Output_1_V_V = tmp_V_23_fu_438_p1;
    end else if (((1'b1 == ap_CS_fsm_state16) & (tmp_s_reg_594 == 1'd0))) begin
        Output_1_V_V = tmp_V_36_fu_430_p1;
    end else if ((1'b1 == ap_CS_fsm_state15)) begin
        Output_1_V_V = tmp_V_35_fu_426_p1;
    end else if ((1'b1 == ap_CS_fsm_state14)) begin
        Output_1_V_V = tmp_V_34_fu_422_p1;
    end else if ((1'b1 == ap_CS_fsm_state13)) begin
        Output_1_V_V = tmp_V_33_fu_418_p1;
    end else if ((1'b1 == ap_CS_fsm_state12)) begin
        Output_1_V_V = tmp_V_32_fu_404_p1;
    end else if ((1'b1 == ap_CS_fsm_state11)) begin
        Output_1_V_V = tmp_V_31_fu_400_p1;
    end else if ((1'b1 == ap_CS_fsm_state10)) begin
        Output_1_V_V = tmp_V_30_fu_382_p1;
    end else if ((1'b1 == ap_CS_fsm_state9)) begin
        Output_1_V_V = tmp_V_29_fu_366_p1;
    end else if ((1'b1 == ap_CS_fsm_state8)) begin
        Output_1_V_V = tmp_V_28_fu_286_p1;
    end else if ((1'b1 == ap_CS_fsm_state7)) begin
        Output_1_V_V = tmp_V_27_fu_206_p1;
    end else if ((1'b1 == ap_CS_fsm_state6)) begin
        Output_1_V_V = tmp_V_26_fu_202_p1;
    end else if ((1'b1 == ap_CS_fsm_state5)) begin
        Output_1_V_V = tmp_V_25_fu_198_p1;
    end else if ((1'b1 == ap_CS_fsm_state4)) begin
        Output_1_V_V = tmp_V_24_fu_194_p1;
    end else if (((tmp_s_fu_146_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state3))) begin
        Output_1_V_V = 32'd1;
    end else if (((1'b1 == ap_CS_fsm_state20) | (1'b1 == ap_CS_fsm_state19) | (1'b1 == ap_CS_fsm_state18) | (1'b1 == ap_CS_fsm_state17) | (1'b1 == ap_CS_fsm_state23) | (1'b1 == ap_CS_fsm_state22) | (1'b1 == ap_CS_fsm_state21) | ((tmp_s_fu_146_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state3)))) begin
        Output_1_V_V = 32'd0;
    end else begin
        Output_1_V_V = 'bx;
    end
end

always @ (*) begin
    if ((((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state20)) | ((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state19)) | ((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state18)) | ((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state17)) | ((tmp_s_fu_146_p2 == 1'd1) & (1'b0 == ap_block_state3_io) & (1'b1 == ap_CS_fsm_state3)) | ((tmp_s_fu_146_p2 == 1'd0) & (1'b0 == ap_block_state3_io) & (1'b1 == ap_CS_fsm_state3)) | ((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state15)) | ((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state14)) | ((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state13)) | ((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state12)) | ((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state11)) | ((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state10)) | ((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state9)) | ((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state8)) | ((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state7)) | ((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state6)) | ((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state5)) | ((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state4)) | ((1'b0 == ap_block_state16_io) & (1'b1 == ap_CS_fsm_state16) & (tmp_s_reg_594 == 1'd0)) | ((tmp_s_reg_594 == 1'd1) & (1'b0 == ap_block_state16_io) & (1'b1 == ap_CS_fsm_state16)) | ((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state28)) | ((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state27)) | ((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state26)) | ((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state25)) | ((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state24)) | ((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state23)) | ((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state22)) | ((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state21)))) begin
        Output_1_V_V_ap_vld = 1'b1;
    end else begin
        Output_1_V_V_ap_vld = 1'b0;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state20) | (1'b1 == ap_CS_fsm_state19) | (1'b1 == ap_CS_fsm_state18) | (1'b1 == ap_CS_fsm_state17) | (1'b1 == ap_CS_fsm_state15) | (1'b1 == ap_CS_fsm_state14) | (1'b1 == ap_CS_fsm_state13) | (1'b1 == ap_CS_fsm_state12) | (1'b1 == ap_CS_fsm_state11) | (1'b1 == ap_CS_fsm_state10) | (1'b1 == ap_CS_fsm_state9) | (1'b1 == ap_CS_fsm_state8) | (1'b1 == ap_CS_fsm_state7) | (1'b1 == ap_CS_fsm_state6) | (1'b1 == ap_CS_fsm_state5) | (1'b1 == ap_CS_fsm_state4) | (1'b1 == ap_CS_fsm_state28) | (1'b1 == ap_CS_fsm_state27) | (1'b1 == ap_CS_fsm_state26) | (1'b1 == ap_CS_fsm_state25) | (1'b1 == ap_CS_fsm_state24) | (1'b1 == ap_CS_fsm_state23) | (1'b1 == ap_CS_fsm_state22) | (1'b1 == ap_CS_fsm_state21) | ((tmp_s_fu_146_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state3)) | ((tmp_s_fu_146_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state3)) | ((1'b1 == ap_CS_fsm_state16) & (tmp_s_reg_594 == 1'd0)) | ((tmp_s_reg_594 == 1'd1) & (1'b1 == ap_CS_fsm_state16)))) begin
        Output_1_V_V_blk_n = Output_1_V_V_ap_ack;
    end else begin
        Output_1_V_V_blk_n = 1'b1;
    end
end

always @ (*) begin
    if ((((ap_start == 1'b0) & (1'b1 == ap_CS_fsm_state1)) | ((1'b0 == ap_block_state16_io) & (1'b1 == ap_CS_fsm_state16)))) begin
        ap_done = 1'b1;
    end else begin
        ap_done = 1'b0;
    end
end

always @ (*) begin
    if (((ap_start == 1'b0) & (1'b1 == ap_CS_fsm_state1))) begin
        ap_idle = 1'b1;
    end else begin
        ap_idle = 1'b0;
    end
end

always @ (*) begin
    if (((1'b0 == ap_block_state16_io) & (1'b1 == ap_CS_fsm_state16))) begin
        ap_ready = 1'b1;
    end else begin
        ap_ready = 1'b0;
    end
end

always @ (*) begin
    case (ap_CS_fsm)
        ap_ST_fsm_state1 : begin
            if (((ap_start == 1'b1) & (1'b1 == ap_CS_fsm_state1))) begin
                ap_NS_fsm = ap_ST_fsm_state2;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state1;
            end
        end
        ap_ST_fsm_state2 : begin
            ap_NS_fsm = ap_ST_fsm_state3;
        end
        ap_ST_fsm_state3 : begin
            if (((tmp_s_fu_146_p2 == 1'd1) & (1'b0 == ap_block_state3_io) & (1'b1 == ap_CS_fsm_state3))) begin
                ap_NS_fsm = ap_ST_fsm_state17;
            end else if (((tmp_s_fu_146_p2 == 1'd0) & (1'b0 == ap_block_state3_io) & (1'b1 == ap_CS_fsm_state3))) begin
                ap_NS_fsm = ap_ST_fsm_state4;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state3;
            end
        end
        ap_ST_fsm_state4 : begin
            if (((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state4))) begin
                ap_NS_fsm = ap_ST_fsm_state5;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state4;
            end
        end
        ap_ST_fsm_state5 : begin
            if (((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state5))) begin
                ap_NS_fsm = ap_ST_fsm_state6;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state5;
            end
        end
        ap_ST_fsm_state6 : begin
            if (((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state6))) begin
                ap_NS_fsm = ap_ST_fsm_state7;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state6;
            end
        end
        ap_ST_fsm_state7 : begin
            if (((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state7))) begin
                ap_NS_fsm = ap_ST_fsm_state8;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state7;
            end
        end
        ap_ST_fsm_state8 : begin
            if (((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state8))) begin
                ap_NS_fsm = ap_ST_fsm_state9;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state8;
            end
        end
        ap_ST_fsm_state9 : begin
            if (((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state9))) begin
                ap_NS_fsm = ap_ST_fsm_state10;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state9;
            end
        end
        ap_ST_fsm_state10 : begin
            if (((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state10))) begin
                ap_NS_fsm = ap_ST_fsm_state11;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state10;
            end
        end
        ap_ST_fsm_state11 : begin
            if (((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state11))) begin
                ap_NS_fsm = ap_ST_fsm_state12;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state11;
            end
        end
        ap_ST_fsm_state12 : begin
            if (((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state12))) begin
                ap_NS_fsm = ap_ST_fsm_state13;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state12;
            end
        end
        ap_ST_fsm_state13 : begin
            if (((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state13))) begin
                ap_NS_fsm = ap_ST_fsm_state14;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state13;
            end
        end
        ap_ST_fsm_state14 : begin
            if (((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state14))) begin
                ap_NS_fsm = ap_ST_fsm_state15;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state14;
            end
        end
        ap_ST_fsm_state15 : begin
            if (((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state15))) begin
                ap_NS_fsm = ap_ST_fsm_state16;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state15;
            end
        end
        ap_ST_fsm_state16 : begin
            if (((1'b0 == ap_block_state16_io) & (1'b1 == ap_CS_fsm_state16))) begin
                ap_NS_fsm = ap_ST_fsm_state1;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state16;
            end
        end
        ap_ST_fsm_state17 : begin
            if (((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state17))) begin
                ap_NS_fsm = ap_ST_fsm_state18;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state17;
            end
        end
        ap_ST_fsm_state18 : begin
            if (((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state18))) begin
                ap_NS_fsm = ap_ST_fsm_state19;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state18;
            end
        end
        ap_ST_fsm_state19 : begin
            if (((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state19))) begin
                ap_NS_fsm = ap_ST_fsm_state20;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state19;
            end
        end
        ap_ST_fsm_state20 : begin
            if (((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state20))) begin
                ap_NS_fsm = ap_ST_fsm_state21;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state20;
            end
        end
        ap_ST_fsm_state21 : begin
            if (((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state21))) begin
                ap_NS_fsm = ap_ST_fsm_state22;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state21;
            end
        end
        ap_ST_fsm_state22 : begin
            if (((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state22))) begin
                ap_NS_fsm = ap_ST_fsm_state23;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state22;
            end
        end
        ap_ST_fsm_state23 : begin
            if (((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state23))) begin
                ap_NS_fsm = ap_ST_fsm_state24;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state23;
            end
        end
        ap_ST_fsm_state24 : begin
            if (((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state24))) begin
                ap_NS_fsm = ap_ST_fsm_state25;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state24;
            end
        end
        ap_ST_fsm_state25 : begin
            if (((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state25))) begin
                ap_NS_fsm = ap_ST_fsm_state26;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state25;
            end
        end
        ap_ST_fsm_state26 : begin
            if (((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state26))) begin
                ap_NS_fsm = ap_ST_fsm_state27;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state26;
            end
        end
        ap_ST_fsm_state27 : begin
            if (((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state27))) begin
                ap_NS_fsm = ap_ST_fsm_state28;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state27;
            end
        end
        ap_ST_fsm_state28 : begin
            if (((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state28))) begin
                ap_NS_fsm = ap_ST_fsm_state16;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state28;
            end
        end
        default : begin
            ap_NS_fsm = 'bx;
        end
    endcase
end

assign agg_result_V_i4_fu_272_p3 = ((tmp_i4_fu_248_p2[0:0] === 1'b1) ? in0_V_in2_V_i4_fu_256_p3 : in1_V_in2_V_i4_fu_266_p3);

assign agg_result_V_i5_fu_314_p3 = ((tmp_i5_fu_290_p2[0:0] === 1'b1) ? in0_V_in2_V_i5_fu_298_p3 : in1_V_in2_V_i5_fu_308_p3);

assign agg_result_V_i6_fu_352_p3 = ((tmp_i6_fu_328_p2[0:0] === 1'b1) ? in0_V_in2_V_i6_fu_336_p3 : in1_V_in2_V_i6_fu_346_p3);

assign agg_result_V_i_fu_234_p3 = ((tmp_i_fu_210_p2[0:0] === 1'b1) ? in0_V_in2_V_i_fu_218_p3 : in1_V_in2_V_i_fu_228_p3);

assign ap_CS_fsm_state1 = ap_CS_fsm[32'd0];

assign ap_CS_fsm_state10 = ap_CS_fsm[32'd9];

assign ap_CS_fsm_state11 = ap_CS_fsm[32'd10];

assign ap_CS_fsm_state12 = ap_CS_fsm[32'd11];

assign ap_CS_fsm_state13 = ap_CS_fsm[32'd12];

assign ap_CS_fsm_state14 = ap_CS_fsm[32'd13];

assign ap_CS_fsm_state15 = ap_CS_fsm[32'd14];

assign ap_CS_fsm_state16 = ap_CS_fsm[32'd15];

assign ap_CS_fsm_state17 = ap_CS_fsm[32'd16];

assign ap_CS_fsm_state18 = ap_CS_fsm[32'd17];

assign ap_CS_fsm_state19 = ap_CS_fsm[32'd18];

assign ap_CS_fsm_state2 = ap_CS_fsm[32'd1];

assign ap_CS_fsm_state20 = ap_CS_fsm[32'd19];

assign ap_CS_fsm_state21 = ap_CS_fsm[32'd20];

assign ap_CS_fsm_state22 = ap_CS_fsm[32'd21];

assign ap_CS_fsm_state23 = ap_CS_fsm[32'd22];

assign ap_CS_fsm_state24 = ap_CS_fsm[32'd23];

assign ap_CS_fsm_state25 = ap_CS_fsm[32'd24];

assign ap_CS_fsm_state26 = ap_CS_fsm[32'd25];

assign ap_CS_fsm_state27 = ap_CS_fsm[32'd26];

assign ap_CS_fsm_state28 = ap_CS_fsm[32'd27];

assign ap_CS_fsm_state3 = ap_CS_fsm[32'd2];

assign ap_CS_fsm_state4 = ap_CS_fsm[32'd3];

assign ap_CS_fsm_state5 = ap_CS_fsm[32'd4];

assign ap_CS_fsm_state6 = ap_CS_fsm[32'd5];

assign ap_CS_fsm_state7 = ap_CS_fsm[32'd6];

assign ap_CS_fsm_state8 = ap_CS_fsm[32'd7];

assign ap_CS_fsm_state9 = ap_CS_fsm[32'd8];

always @ (*) begin
    ap_block_state16_io = (((1'b0 == Output_1_V_V_ap_ack) & (tmp_s_reg_594 == 1'd0)) | ((tmp_s_reg_594 == 1'd1) & (1'b0 == Output_1_V_V_ap_ack)));
end

always @ (*) begin
    ap_block_state3_io = (((tmp_s_fu_146_p2 == 1'd1) & (1'b0 == Output_1_V_V_ap_ack)) | ((tmp_s_fu_146_p2 == 1'd0) & (1'b0 == Output_1_V_V_ap_ack)));
end

assign grp_fu_473_p0 = grp_fu_473_p00;

assign grp_fu_473_p00 = triangle_2d_y1_V;

assign grp_fu_473_p1 = rhs_V_7_reg_547;

assign grp_fu_481_p0 = grp_fu_481_p00;

assign grp_fu_481_p00 = triangle_2d_x1_V;

assign grp_fu_481_p1 = rhs_V_6_reg_537;

assign grp_fu_489_p0 = grp_fu_489_p00;

assign grp_fu_489_p00 = agg_result_V_i6_reg_677;

assign grp_fu_489_p1 = grp_fu_489_p10;

assign grp_fu_489_p10 = agg_result_V_i5_reg_671;

assign in0_V_in2_V_i4_fu_256_p3 = ((tmp_i4_11_fu_252_p2[0:0] === 1'b1) ? triangle_2d_same_x0_s_reg_613 : triangle_2d_x2_V);

assign in0_V_in2_V_i5_fu_298_p3 = ((tmp_i5_12_fu_294_p2[0:0] === 1'b1) ? triangle_2d_same_y0_s_reg_624 : triangle_2d_y2_V);

assign in0_V_in2_V_i6_fu_336_p3 = ((tmp_i6_13_fu_332_p2[0:0] === 1'b1) ? triangle_2d_same_y0_s_reg_624 : triangle_2d_y2_V);

assign in0_V_in2_V_i_fu_218_p3 = ((tmp_i_10_fu_214_p2[0:0] === 1'b1) ? triangle_2d_same_x0_s_reg_613 : triangle_2d_x2_V);

assign in1_V_in2_V_i4_fu_266_p3 = ((tmp_5_i_fu_262_p2[0:0] === 1'b1) ? triangle_2d_same_x1_s_reg_635 : triangle_2d_x2_V);

assign in1_V_in2_V_i5_fu_308_p3 = ((tmp_4_i2_fu_304_p2[0:0] === 1'b1) ? triangle_2d_same_y1_s_reg_646 : triangle_2d_y2_V);

assign in1_V_in2_V_i6_fu_346_p3 = ((tmp_5_i2_fu_342_p2[0:0] === 1'b1) ? triangle_2d_same_y1_s_reg_646 : triangle_2d_y2_V);

assign in1_V_in2_V_i_fu_228_p3 = ((tmp_4_i_fu_224_p2[0:0] === 1'b1) ? triangle_2d_same_x1_s_reg_635 : triangle_2d_x2_V);

assign lhs_V_11_fu_112_p1 = triangle_2d_y2_V;

assign lhs_V_8_fu_94_p1 = triangle_2d_x2_V;

assign lhs_V_fu_370_p1 = agg_result_V_i4_reg_664;

assign ret_V_12_fu_116_p2 = (lhs_V_11_fu_112_p1 - rhs_V_7_fu_108_p1);

assign ret_V_15_fu_142_p2 = ($signed(ret_V_11_reg_569) - $signed(ret_V_14_reg_579));

assign ret_V_9_fu_102_p2 = (lhs_V_8_fu_94_p1 - rhs_V_6_fu_98_p1);

assign ret_V_fu_376_p2 = (lhs_V_fu_370_p1 - rhs_V_fu_373_p1);

assign rhs_V_6_fu_98_p1 = triangle_2d_x0_V;

assign rhs_V_7_fu_108_p1 = triangle_2d_y0_V;

assign rhs_V_fu_373_p1 = agg_result_V_i_reg_657;

assign tmp_10_fu_162_p3 = ret_V_15_fu_142_p2[32'd17];

assign tmp_4_i2_fu_304_p2 = ((triangle_2d_same_y1_s_reg_646 < triangle_2d_y2_V) ? 1'b1 : 1'b0);

assign tmp_4_i_fu_224_p2 = ((triangle_2d_same_x1_s_reg_635 < triangle_2d_x2_V) ? 1'b1 : 1'b0);

assign tmp_5_i2_fu_342_p2 = ((triangle_2d_same_y1_s_reg_646 > triangle_2d_y2_V) ? 1'b1 : 1'b0);

assign tmp_5_i_fu_262_p2 = ((triangle_2d_same_x1_s_reg_635 > triangle_2d_x2_V) ? 1'b1 : 1'b0);

assign tmp_8_fu_139_p1 = grp_fu_481_p3[16:0];

assign tmp_9_fu_408_p2 = (agg_result_V_i4_reg_664 - agg_result_V_i_reg_657);

assign tmp_V_19_fu_452_p1 = max_min_V_0_load_reg_598;

assign tmp_V_20_fu_456_p1 = max_min_V_1_load_reg_603;

assign tmp_V_21_fu_460_p1 = max_min_V_2_load_reg_608;

assign tmp_V_22_fu_468_p1 = max_min_V_3;

assign tmp_V_23_fu_438_p1 = max_min_V_4;

assign tmp_V_24_fu_194_p1 = triangle_2d_same_x0_s_reg_613;

assign tmp_V_25_fu_198_p1 = triangle_2d_same_y0_s_reg_624;

assign tmp_V_26_fu_202_p1 = triangle_2d_same_x1_s_reg_635;

assign tmp_V_27_fu_206_p1 = triangle_2d_same_y1_s_reg_646;

assign tmp_V_28_fu_286_p1 = triangle_2d_x2_V;

assign tmp_V_29_fu_366_p1 = triangle_2d_y2_V;

assign tmp_V_30_fu_382_p1 = triangle_2d_z_V;

assign tmp_V_31_fu_400_p1 = $unsigned(grp_fu_489_p3);

assign tmp_V_32_fu_404_p1 = agg_result_V_i_reg_657;

assign tmp_V_33_fu_418_p1 = agg_result_V_i4_reg_664;

assign tmp_V_34_fu_422_p1 = agg_result_V_i5_reg_671;

assign tmp_V_35_fu_426_p1 = agg_result_V_i6_reg_677;

assign tmp_V_36_fu_430_p1 = tmp_9_reg_688;

assign tmp_V_fu_447_p1 = max_index_V_0;

assign tmp_fu_129_p1 = grp_fu_473_p3[16:0];

assign tmp_i4_11_fu_252_p2 = ((triangle_2d_same_x0_s_reg_613 > triangle_2d_x2_V) ? 1'b1 : 1'b0);

assign tmp_i4_fu_248_p2 = ((triangle_2d_same_x0_s_reg_613 > triangle_2d_same_x1_s_reg_635) ? 1'b1 : 1'b0);

assign tmp_i5_12_fu_294_p2 = ((triangle_2d_same_y0_s_reg_624 < triangle_2d_y2_V) ? 1'b1 : 1'b0);

assign tmp_i5_fu_290_p2 = ((triangle_2d_same_y0_s_reg_624 < triangle_2d_same_y1_s_reg_646) ? 1'b1 : 1'b0);

assign tmp_i6_13_fu_332_p2 = ((triangle_2d_same_y0_s_reg_624 > triangle_2d_y2_V) ? 1'b1 : 1'b0);

assign tmp_i6_fu_328_p2 = ((triangle_2d_same_y0_s_reg_624 > triangle_2d_same_y1_s_reg_646) ? 1'b1 : 1'b0);

assign tmp_i_10_fu_214_p2 = ((triangle_2d_same_x0_s_reg_613 < triangle_2d_x2_V) ? 1'b1 : 1'b0);

assign tmp_i_fu_210_p2 = ((triangle_2d_same_x0_s_reg_613 < triangle_2d_same_x1_s_reg_635) ? 1'b1 : 1'b0);

assign tmp_s_fu_146_p2 = ((tmp_reg_574 == tmp_8_reg_584) ? 1'b1 : 1'b0);

assign triangle_2d_same_x0_s_fu_170_p3 = ((tmp_10_fu_162_p3[0:0] === 1'b1) ? triangle_2d_x1_V : triangle_2d_x0_V);

assign triangle_2d_same_x1_s_fu_182_p3 = ((tmp_10_fu_162_p3[0:0] === 1'b1) ? triangle_2d_x0_V : triangle_2d_x1_V);

assign triangle_2d_same_y0_s_fu_176_p3 = ((tmp_10_fu_162_p3[0:0] === 1'b1) ? triangle_2d_y1_V : triangle_2d_y0_V);

assign triangle_2d_same_y1_s_fu_188_p3 = ((tmp_10_fu_162_p3[0:0] === 1'b1) ? triangle_2d_y0_V : triangle_2d_y1_V);

always @ (posedge ap_clk) begin
    rhs_V_6_reg_537[8] <= 1'b0;
    rhs_V_7_reg_547[8] <= 1'b0;
end

endmodule //rasterization1_even_s
