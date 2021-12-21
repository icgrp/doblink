// ==============================================================
// RTL generated by Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Version: 2020.2
// Copyright (C) Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

`timescale 1 ns / 1 ps 

module data_redir_m_rasterization1_odd_m (
        ap_clk,
        ap_rst,
        ap_start,
        ap_done,
        ap_idle,
        ap_ready,
        Output_1_V_TDATA,
        Output_1_V_TVALID,
        Output_1_V_TREADY,
        triangle_2d_x0,
        triangle_2d_y0,
        triangle_2d_x1,
        triangle_2d_y1,
        triangle_2d_x2,
        triangle_2d_y2,
        triangle_2d_z
);

parameter    ap_ST_fsm_state1 = 33'd1;
parameter    ap_ST_fsm_state2 = 33'd2;
parameter    ap_ST_fsm_state3 = 33'd4;
parameter    ap_ST_fsm_state4 = 33'd8;
parameter    ap_ST_fsm_state5 = 33'd16;
parameter    ap_ST_fsm_state6 = 33'd32;
parameter    ap_ST_fsm_state7 = 33'd64;
parameter    ap_ST_fsm_state8 = 33'd128;
parameter    ap_ST_fsm_state9 = 33'd256;
parameter    ap_ST_fsm_state10 = 33'd512;
parameter    ap_ST_fsm_state11 = 33'd1024;
parameter    ap_ST_fsm_state12 = 33'd2048;
parameter    ap_ST_fsm_state13 = 33'd4096;
parameter    ap_ST_fsm_state14 = 33'd8192;
parameter    ap_ST_fsm_state15 = 33'd16384;
parameter    ap_ST_fsm_state16 = 33'd32768;
parameter    ap_ST_fsm_state17 = 33'd65536;
parameter    ap_ST_fsm_state18 = 33'd131072;
parameter    ap_ST_fsm_state19 = 33'd262144;
parameter    ap_ST_fsm_state20 = 33'd524288;
parameter    ap_ST_fsm_state21 = 33'd1048576;
parameter    ap_ST_fsm_state22 = 33'd2097152;
parameter    ap_ST_fsm_state23 = 33'd4194304;
parameter    ap_ST_fsm_state24 = 33'd8388608;
parameter    ap_ST_fsm_state25 = 33'd16777216;
parameter    ap_ST_fsm_state26 = 33'd33554432;
parameter    ap_ST_fsm_state27 = 33'd67108864;
parameter    ap_ST_fsm_state28 = 33'd134217728;
parameter    ap_ST_fsm_state29 = 33'd268435456;
parameter    ap_ST_fsm_state30 = 33'd536870912;
parameter    ap_ST_fsm_state31 = 33'd1073741824;
parameter    ap_ST_fsm_state32 = 33'd2147483648;
parameter    ap_ST_fsm_state33 = 33'd4294967296;

input   ap_clk;
input   ap_rst;
input   ap_start;
output   ap_done;
output   ap_idle;
output   ap_ready;
output  [31:0] Output_1_V_TDATA;
output   Output_1_V_TVALID;
input   Output_1_V_TREADY;
input  [7:0] triangle_2d_x0;
input  [7:0] triangle_2d_y0;
input  [7:0] triangle_2d_x1;
input  [7:0] triangle_2d_y1;
input  [7:0] triangle_2d_x2;
input  [7:0] triangle_2d_y2;
input  [7:0] triangle_2d_z;

reg ap_done;
reg ap_idle;
reg ap_ready;
reg[31:0] Output_1_V_TDATA;
reg Output_1_V_TVALID;

(* fsm_encoding = "none" *) reg   [32:0] ap_CS_fsm;
wire    ap_CS_fsm_state1;
reg   [15:0] max_index_V;
reg   [7:0] max_min_V_7;
reg   [7:0] max_min_V_6;
reg   [7:0] max_min_V_5;
reg   [7:0] max_min_V_4;
reg   [7:0] max_min_V;
reg    Output_1_V_TDATA_blk_n;
wire    ap_CS_fsm_state6;
wire   [0:0] icmp_ln207_fu_175_p2;
wire    ap_CS_fsm_state20;
wire    ap_CS_fsm_state21;
wire    ap_CS_fsm_state22;
wire    ap_CS_fsm_state23;
wire    ap_CS_fsm_state24;
wire    ap_CS_fsm_state25;
wire    ap_CS_fsm_state26;
wire    ap_CS_fsm_state27;
wire    ap_CS_fsm_state28;
wire    ap_CS_fsm_state29;
wire    ap_CS_fsm_state30;
wire    ap_CS_fsm_state31;
wire    ap_CS_fsm_state32;
wire    ap_CS_fsm_state7;
wire    ap_CS_fsm_state8;
wire    ap_CS_fsm_state9;
wire    ap_CS_fsm_state10;
wire    ap_CS_fsm_state11;
wire    ap_CS_fsm_state12;
wire    ap_CS_fsm_state13;
wire    ap_CS_fsm_state14;
wire    ap_CS_fsm_state15;
wire    ap_CS_fsm_state16;
wire    ap_CS_fsm_state17;
wire    ap_CS_fsm_state18;
wire    ap_CS_fsm_state19;
wire   [8:0] ret_15_fu_107_p2;
reg  signed [8:0] ret_15_reg_565;
wire   [8:0] ret_16_fu_121_p2;
reg  signed [8:0] ret_16_reg_570;
wire   [8:0] ret_18_fu_131_p2;
reg  signed [8:0] ret_18_reg_575;
wire   [8:0] ret_19_fu_141_p2;
reg  signed [8:0] ret_19_reg_580;
wire    ap_CS_fsm_state2;
wire   [17:0] grp_fu_153_p2;
reg   [17:0] ret_17_reg_605;
wire    ap_CS_fsm_state5;
wire   [17:0] grp_fu_165_p2;
reg   [17:0] ret_20_reg_611;
reg   [0:0] tmp_reg_625;
wire   [7:0] triangle_2d_same_y1_V_fu_187_p3;
reg   [7:0] triangle_2d_same_y1_V_reg_633;
wire   [7:0] triangle_2d_same_x1_V_fu_192_p3;
reg   [7:0] triangle_2d_same_x1_V_reg_644;
wire   [7:0] triangle_2d_same_y0_V_fu_197_p3;
reg   [7:0] triangle_2d_same_y0_V_reg_655;
wire   [7:0] triangle_2d_same_x0_V_fu_202_p3;
reg   [7:0] triangle_2d_same_x0_V_reg_666;
wire   [0:0] icmp_ln878_2_fu_212_p2;
reg   [0:0] icmp_ln878_2_reg_676;
wire   [0:0] icmp_ln886_2_fu_216_p2;
reg   [0:0] icmp_ln886_2_reg_681;
wire   [0:0] icmp_ln878_5_fu_224_p2;
reg   [0:0] icmp_ln878_5_reg_686;
wire   [0:0] icmp_ln886_5_fu_228_p2;
reg   [0:0] icmp_ln886_5_reg_691;
wire   [7:0] rhs_5_fu_255_p3;
reg   [7:0] rhs_5_reg_696;
wire   [7:0] lhs_5_fu_288_p3;
reg   [7:0] lhs_5_reg_702;
wire   [7:0] rhs_6_fu_321_p3;
reg   [7:0] rhs_6_reg_708;
wire   [7:0] lhs_6_fu_354_p3;
reg   [7:0] lhs_6_reg_714;
wire  signed [8:0] ret_13_fu_378_p2;
reg  signed [8:0] ret_13_reg_720;
wire   [7:0] trunc_ln213_fu_384_p1;
reg   [7:0] trunc_ln213_reg_725;
wire   [8:0] ret_14_fu_400_p2;
reg  signed [8:0] ret_14_reg_730;
wire   [15:0] grp_fu_416_p2;
reg    ap_block_state6;
reg    ap_block_state6_io;
wire   [31:0] zext_ln878_fu_207_p1;
wire   [31:0] zext_ln878_3_fu_220_p1;
wire   [31:0] zext_ln878_1_fu_232_p1;
wire   [31:0] zext_ln878_4_fu_368_p1;
wire   [31:0] zext_ln878_2_fu_406_p1;
wire   [31:0] zext_ln878_5_fu_422_p1;
wire   [31:0] zext_ln208_6_fu_426_p1;
wire   [31:0] zext_ln208_7_fu_436_p1;
wire   [31:0] zext_ln208_8_fu_441_p1;
wire   [31:0] zext_ln208_9_fu_445_p1;
wire   [31:0] zext_ln208_10_fu_449_p1;
wire   [31:0] zext_ln208_11_fu_453_p1;
wire   [31:0] zext_ln208_12_fu_457_p1;
wire   [31:0] zext_ln208_fu_465_p1;
wire   [31:0] zext_ln208_1_fu_474_p1;
wire   [31:0] zext_ln208_2_fu_483_p1;
wire   [31:0] zext_ln208_3_fu_492_p1;
wire   [31:0] zext_ln208_4_fu_501_p1;
wire   [31:0] zext_ln208_5_fu_510_p1;
wire   [8:0] zext_ln215_fu_99_p1;
wire   [8:0] zext_ln1347_fu_103_p1;
wire   [8:0] zext_ln215_1_fu_113_p1;
wire   [8:0] zext_ln1347_1_fu_117_p1;
wire   [8:0] zext_ln1347_2_fu_127_p1;
wire   [8:0] zext_ln1347_3_fu_137_p1;
wire   [17:0] ret_fu_171_p2;
wire   [0:0] icmp_ln878_1_fu_240_p2;
wire   [0:0] icmp_ln878_fu_236_p2;
wire   [7:0] select_ln43_fu_244_p3;
wire   [7:0] select_ln50_fu_250_p3;
wire   [0:0] icmp_ln886_1_fu_273_p2;
wire   [0:0] icmp_ln886_fu_269_p2;
wire   [7:0] select_ln63_fu_277_p3;
wire   [7:0] select_ln70_fu_283_p3;
wire   [0:0] icmp_ln878_4_fu_306_p2;
wire   [0:0] icmp_ln878_3_fu_302_p2;
wire   [7:0] select_ln43_1_fu_310_p3;
wire   [7:0] select_ln50_1_fu_316_p3;
wire   [0:0] icmp_ln886_4_fu_339_p2;
wire   [0:0] icmp_ln886_3_fu_335_p2;
wire   [7:0] select_ln63_1_fu_343_p3;
wire   [7:0] select_ln70_1_fu_349_p3;
wire   [8:0] zext_ln215_2_fu_372_p1;
wire   [8:0] zext_ln215_3_fu_375_p1;
wire   [8:0] zext_ln215_4_fu_394_p1;
wire   [8:0] zext_ln215_5_fu_397_p1;
reg    grp_fu_416_ce;
wire    ap_CS_fsm_state33;
reg   [32:0] ap_NS_fsm;
wire    ap_ce_reg;

// power-on initialization
initial begin
#0 ap_CS_fsm = 33'd1;
#0 max_index_V = 16'd0;
#0 max_min_V_7 = 8'd0;
#0 max_min_V_6 = 8'd0;
#0 max_min_V_5 = 8'd0;
#0 max_min_V_4 = 8'd0;
#0 max_min_V = 8'd0;
end

data_redir_m_mul_9s_9s_18_4_1 #(
    .ID( 1 ),
    .NUM_STAGE( 4 ),
    .din0_WIDTH( 9 ),
    .din1_WIDTH( 9 ),
    .dout_WIDTH( 18 ))
mul_9s_9s_18_4_1_U1(
    .clk(ap_clk),
    .reset(ap_rst),
    .din0(ret_15_reg_565),
    .din1(ret_16_reg_570),
    .ce(1'b1),
    .dout(grp_fu_153_p2)
);

data_redir_m_mul_9s_9s_18_4_1 #(
    .ID( 1 ),
    .NUM_STAGE( 4 ),
    .din0_WIDTH( 9 ),
    .din1_WIDTH( 9 ),
    .dout_WIDTH( 18 ))
mul_9s_9s_18_4_1_U2(
    .clk(ap_clk),
    .reset(ap_rst),
    .din0(ret_18_reg_575),
    .din1(ret_19_reg_580),
    .ce(1'b1),
    .dout(grp_fu_165_p2)
);

data_redir_m_mul_9s_9s_16_4_1 #(
    .ID( 1 ),
    .NUM_STAGE( 4 ),
    .din0_WIDTH( 9 ),
    .din1_WIDTH( 9 ),
    .dout_WIDTH( 16 ))
mul_9s_9s_16_4_1_U3(
    .clk(ap_clk),
    .reset(ap_rst),
    .din0(ret_13_reg_720),
    .din1(ret_14_reg_730),
    .ce(grp_fu_416_ce),
    .dout(grp_fu_416_p2)
);

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_CS_fsm <= ap_ST_fsm_state1;
    end else begin
        ap_CS_fsm <= ap_NS_fsm;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state8)) begin
        icmp_ln878_2_reg_676 <= icmp_ln878_2_fu_212_p2;
        icmp_ln878_5_reg_686 <= icmp_ln878_5_fu_224_p2;
        icmp_ln886_2_reg_681 <= icmp_ln886_2_fu_216_p2;
        icmp_ln886_5_reg_691 <= icmp_ln886_5_fu_228_p2;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state9)) begin
        lhs_5_reg_702 <= lhs_5_fu_288_p3;
        lhs_6_reg_714 <= lhs_6_fu_354_p3;
        rhs_5_reg_696 <= rhs_5_fu_255_p3;
        rhs_6_reg_708 <= rhs_6_fu_321_p3;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state14))) begin
        max_index_V <= grp_fu_416_p2;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state10))) begin
        max_min_V <= trunc_ln213_fu_384_p1;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state9))) begin
        max_min_V_4 <= lhs_6_fu_354_p3;
        max_min_V_5 <= rhs_6_fu_321_p3;
        max_min_V_6 <= lhs_5_fu_288_p3;
        max_min_V_7 <= rhs_5_fu_255_p3;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state10)) begin
        ret_13_reg_720 <= ret_13_fu_378_p2;
        ret_14_reg_730 <= ret_14_fu_400_p2;
        trunc_ln213_reg_725 <= trunc_ln213_fu_384_p1;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state1)) begin
        ret_15_reg_565 <= ret_15_fu_107_p2;
        ret_16_reg_570 <= ret_16_fu_121_p2;
        ret_18_reg_575 <= ret_18_fu_131_p2;
        ret_19_reg_580 <= ret_19_fu_141_p2;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state5)) begin
        ret_17_reg_605 <= grp_fu_153_p2;
        ret_20_reg_611 <= grp_fu_165_p2;
    end
end

always @ (posedge ap_clk) begin
    if (((icmp_ln207_fu_175_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state6))) begin
        tmp_reg_625 <= ret_fu_171_p2[32'd17];
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state7)) begin
        triangle_2d_same_x0_V_reg_666 <= triangle_2d_same_x0_V_fu_202_p3;
        triangle_2d_same_x1_V_reg_644 <= triangle_2d_same_x1_V_fu_192_p3;
        triangle_2d_same_y0_V_reg_655 <= triangle_2d_same_y0_V_fu_197_p3;
        triangle_2d_same_y1_V_reg_633 <= triangle_2d_same_y1_V_fu_187_p3;
    end
end

always @ (*) begin
    if (((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state32))) begin
        Output_1_V_TDATA = zext_ln208_5_fu_510_p1;
    end else if (((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state31))) begin
        Output_1_V_TDATA = zext_ln208_4_fu_501_p1;
    end else if (((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state30))) begin
        Output_1_V_TDATA = zext_ln208_3_fu_492_p1;
    end else if (((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state29))) begin
        Output_1_V_TDATA = zext_ln208_2_fu_483_p1;
    end else if (((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state28))) begin
        Output_1_V_TDATA = zext_ln208_1_fu_474_p1;
    end else if (((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state27))) begin
        Output_1_V_TDATA = zext_ln208_fu_465_p1;
    end else if (((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state19))) begin
        Output_1_V_TDATA = zext_ln208_12_fu_457_p1;
    end else if (((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state18))) begin
        Output_1_V_TDATA = zext_ln208_11_fu_453_p1;
    end else if (((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state17))) begin
        Output_1_V_TDATA = zext_ln208_10_fu_449_p1;
    end else if (((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state16))) begin
        Output_1_V_TDATA = zext_ln208_9_fu_445_p1;
    end else if (((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state15))) begin
        Output_1_V_TDATA = zext_ln208_8_fu_441_p1;
    end else if (((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state14))) begin
        Output_1_V_TDATA = zext_ln208_7_fu_436_p1;
    end else if (((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state13))) begin
        Output_1_V_TDATA = zext_ln208_6_fu_426_p1;
    end else if (((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state12))) begin
        Output_1_V_TDATA = zext_ln878_5_fu_422_p1;
    end else if (((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state11))) begin
        Output_1_V_TDATA = zext_ln878_2_fu_406_p1;
    end else if (((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state10))) begin
        Output_1_V_TDATA = zext_ln878_4_fu_368_p1;
    end else if (((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state9))) begin
        Output_1_V_TDATA = zext_ln878_1_fu_232_p1;
    end else if (((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state8))) begin
        Output_1_V_TDATA = zext_ln878_3_fu_220_p1;
    end else if (((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state7))) begin
        Output_1_V_TDATA = zext_ln878_fu_207_p1;
    end else if ((~(((icmp_ln207_fu_175_p2 == 1'd1) & (1'b0 == Output_1_V_TREADY)) | ((icmp_ln207_fu_175_p2 == 1'd0) & (1'b0 == Output_1_V_TREADY))) & (icmp_ln207_fu_175_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state6))) begin
        Output_1_V_TDATA = 32'd1;
    end else if ((((1'b1 == ap_CS_fsm_state22) & (1'b1 == Output_1_V_TREADY)) | ((1'b1 == ap_CS_fsm_state21) & (1'b1 == Output_1_V_TREADY)) | ((1'b1 == ap_CS_fsm_state20) & (1'b1 == Output_1_V_TREADY)) | (~(((icmp_ln207_fu_175_p2 == 1'd1) & (1'b0 == Output_1_V_TREADY)) | ((icmp_ln207_fu_175_p2 == 1'd0) & (1'b0 == Output_1_V_TREADY))) & (icmp_ln207_fu_175_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state6)) | ((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state26)) | ((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state25)) | ((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state24)) | ((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state23)))) begin
        Output_1_V_TDATA = 32'd0;
    end else begin
        Output_1_V_TDATA = 'bx;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state22) | (1'b1 == ap_CS_fsm_state21) | (1'b1 == ap_CS_fsm_state20) | (1'b1 == ap_CS_fsm_state19) | (1'b1 == ap_CS_fsm_state18) | (1'b1 == ap_CS_fsm_state17) | (1'b1 == ap_CS_fsm_state16) | (1'b1 == ap_CS_fsm_state15) | (1'b1 == ap_CS_fsm_state14) | (1'b1 == ap_CS_fsm_state13) | (1'b1 == ap_CS_fsm_state12) | (1'b1 == ap_CS_fsm_state11) | (1'b1 == ap_CS_fsm_state10) | (1'b1 == ap_CS_fsm_state9) | (1'b1 == ap_CS_fsm_state8) | (1'b1 == ap_CS_fsm_state7) | (1'b1 == ap_CS_fsm_state32) | (1'b1 == ap_CS_fsm_state31) | (1'b1 == ap_CS_fsm_state30) | (1'b1 == ap_CS_fsm_state29) | (1'b1 == ap_CS_fsm_state28) | (1'b1 == ap_CS_fsm_state27) | (1'b1 == ap_CS_fsm_state26) | (1'b1 == ap_CS_fsm_state25) | (1'b1 == ap_CS_fsm_state24) | (1'b1 == ap_CS_fsm_state23) | ((icmp_ln207_fu_175_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state6)) | ((icmp_ln207_fu_175_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state6)))) begin
        Output_1_V_TDATA_blk_n = Output_1_V_TREADY;
    end else begin
        Output_1_V_TDATA_blk_n = 1'b1;
    end
end

always @ (*) begin
    if ((((1'b1 == ap_CS_fsm_state22) & (1'b1 == Output_1_V_TREADY)) | ((1'b1 == ap_CS_fsm_state21) & (1'b1 == Output_1_V_TREADY)) | ((1'b1 == ap_CS_fsm_state20) & (1'b1 == Output_1_V_TREADY)) | (~((1'b1 == ap_block_state6_io) | ((icmp_ln207_fu_175_p2 == 1'd1) & (1'b0 == Output_1_V_TREADY)) | ((icmp_ln207_fu_175_p2 == 1'd0) & (1'b0 == Output_1_V_TREADY))) & (icmp_ln207_fu_175_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state6)) | (~((1'b1 == ap_block_state6_io) | ((icmp_ln207_fu_175_p2 == 1'd1) & (1'b0 == Output_1_V_TREADY)) | ((icmp_ln207_fu_175_p2 == 1'd0) & (1'b0 == Output_1_V_TREADY))) & (icmp_ln207_fu_175_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state6)) | ((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state19)) | ((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state18)) | ((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state17)) | ((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state16)) | ((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state15)) | ((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state14)) | ((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state13)) | ((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state12)) | ((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state11)) | ((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state10)) | ((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state9)) | ((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state8)) | ((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state7)) | ((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state32)) | ((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state31)) | ((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state30)) | ((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state29)) | ((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state28)) | ((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state27)) | ((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state26)) | ((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state25)) | ((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state24)) | ((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state23)))) begin
        Output_1_V_TVALID = 1'b1;
    end else begin
        Output_1_V_TVALID = 1'b0;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state33) | ((ap_start == 1'b0) & (1'b1 == ap_CS_fsm_state1)))) begin
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
    if ((1'b1 == ap_CS_fsm_state33)) begin
        ap_ready = 1'b1;
    end else begin
        ap_ready = 1'b0;
    end
end

always @ (*) begin
    if ((((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state14)) | ((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state13)) | ((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state12)) | ((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state11)))) begin
        grp_fu_416_ce = 1'b1;
    end else begin
        grp_fu_416_ce = 1'b0;
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
            ap_NS_fsm = ap_ST_fsm_state4;
        end
        ap_ST_fsm_state4 : begin
            ap_NS_fsm = ap_ST_fsm_state5;
        end
        ap_ST_fsm_state5 : begin
            ap_NS_fsm = ap_ST_fsm_state6;
        end
        ap_ST_fsm_state6 : begin
            if ((~((1'b1 == ap_block_state6_io) | ((icmp_ln207_fu_175_p2 == 1'd1) & (1'b0 == Output_1_V_TREADY)) | ((icmp_ln207_fu_175_p2 == 1'd0) & (1'b0 == Output_1_V_TREADY))) & (icmp_ln207_fu_175_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state6))) begin
                ap_NS_fsm = ap_ST_fsm_state20;
            end else if ((~((1'b1 == ap_block_state6_io) | ((icmp_ln207_fu_175_p2 == 1'd1) & (1'b0 == Output_1_V_TREADY)) | ((icmp_ln207_fu_175_p2 == 1'd0) & (1'b0 == Output_1_V_TREADY))) & (icmp_ln207_fu_175_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state6))) begin
                ap_NS_fsm = ap_ST_fsm_state7;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state6;
            end
        end
        ap_ST_fsm_state7 : begin
            if (((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state7))) begin
                ap_NS_fsm = ap_ST_fsm_state8;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state7;
            end
        end
        ap_ST_fsm_state8 : begin
            if (((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state8))) begin
                ap_NS_fsm = ap_ST_fsm_state9;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state8;
            end
        end
        ap_ST_fsm_state9 : begin
            if (((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state9))) begin
                ap_NS_fsm = ap_ST_fsm_state10;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state9;
            end
        end
        ap_ST_fsm_state10 : begin
            if (((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state10))) begin
                ap_NS_fsm = ap_ST_fsm_state11;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state10;
            end
        end
        ap_ST_fsm_state11 : begin
            if (((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state11))) begin
                ap_NS_fsm = ap_ST_fsm_state12;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state11;
            end
        end
        ap_ST_fsm_state12 : begin
            if (((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state12))) begin
                ap_NS_fsm = ap_ST_fsm_state13;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state12;
            end
        end
        ap_ST_fsm_state13 : begin
            if (((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state13))) begin
                ap_NS_fsm = ap_ST_fsm_state14;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state13;
            end
        end
        ap_ST_fsm_state14 : begin
            if (((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state14))) begin
                ap_NS_fsm = ap_ST_fsm_state15;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state14;
            end
        end
        ap_ST_fsm_state15 : begin
            if (((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state15))) begin
                ap_NS_fsm = ap_ST_fsm_state16;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state15;
            end
        end
        ap_ST_fsm_state16 : begin
            if (((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state16))) begin
                ap_NS_fsm = ap_ST_fsm_state17;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state16;
            end
        end
        ap_ST_fsm_state17 : begin
            if (((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state17))) begin
                ap_NS_fsm = ap_ST_fsm_state18;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state17;
            end
        end
        ap_ST_fsm_state18 : begin
            if (((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state18))) begin
                ap_NS_fsm = ap_ST_fsm_state19;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state18;
            end
        end
        ap_ST_fsm_state19 : begin
            if (((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state19))) begin
                ap_NS_fsm = ap_ST_fsm_state33;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state19;
            end
        end
        ap_ST_fsm_state20 : begin
            if (((1'b1 == ap_CS_fsm_state20) & (1'b1 == Output_1_V_TREADY))) begin
                ap_NS_fsm = ap_ST_fsm_state21;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state20;
            end
        end
        ap_ST_fsm_state21 : begin
            if (((1'b1 == ap_CS_fsm_state21) & (1'b1 == Output_1_V_TREADY))) begin
                ap_NS_fsm = ap_ST_fsm_state22;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state21;
            end
        end
        ap_ST_fsm_state22 : begin
            if (((1'b1 == ap_CS_fsm_state22) & (1'b1 == Output_1_V_TREADY))) begin
                ap_NS_fsm = ap_ST_fsm_state23;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state22;
            end
        end
        ap_ST_fsm_state23 : begin
            if (((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state23))) begin
                ap_NS_fsm = ap_ST_fsm_state24;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state23;
            end
        end
        ap_ST_fsm_state24 : begin
            if (((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state24))) begin
                ap_NS_fsm = ap_ST_fsm_state25;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state24;
            end
        end
        ap_ST_fsm_state25 : begin
            if (((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state25))) begin
                ap_NS_fsm = ap_ST_fsm_state26;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state25;
            end
        end
        ap_ST_fsm_state26 : begin
            if (((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state26))) begin
                ap_NS_fsm = ap_ST_fsm_state27;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state26;
            end
        end
        ap_ST_fsm_state27 : begin
            if (((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state27))) begin
                ap_NS_fsm = ap_ST_fsm_state28;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state27;
            end
        end
        ap_ST_fsm_state28 : begin
            if (((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state28))) begin
                ap_NS_fsm = ap_ST_fsm_state29;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state28;
            end
        end
        ap_ST_fsm_state29 : begin
            if (((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state29))) begin
                ap_NS_fsm = ap_ST_fsm_state30;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state29;
            end
        end
        ap_ST_fsm_state30 : begin
            if (((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state30))) begin
                ap_NS_fsm = ap_ST_fsm_state31;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state30;
            end
        end
        ap_ST_fsm_state31 : begin
            if (((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state31))) begin
                ap_NS_fsm = ap_ST_fsm_state32;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state31;
            end
        end
        ap_ST_fsm_state32 : begin
            if (((1'b1 == Output_1_V_TREADY) & (1'b1 == ap_CS_fsm_state32))) begin
                ap_NS_fsm = ap_ST_fsm_state33;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state32;
            end
        end
        ap_ST_fsm_state33 : begin
            ap_NS_fsm = ap_ST_fsm_state1;
        end
        default : begin
            ap_NS_fsm = 'bx;
        end
    endcase
end

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

assign ap_CS_fsm_state29 = ap_CS_fsm[32'd28];

assign ap_CS_fsm_state30 = ap_CS_fsm[32'd29];

assign ap_CS_fsm_state31 = ap_CS_fsm[32'd30];

assign ap_CS_fsm_state32 = ap_CS_fsm[32'd31];

assign ap_CS_fsm_state33 = ap_CS_fsm[32'd32];

assign ap_CS_fsm_state5 = ap_CS_fsm[32'd4];

assign ap_CS_fsm_state6 = ap_CS_fsm[32'd5];

assign ap_CS_fsm_state7 = ap_CS_fsm[32'd6];

assign ap_CS_fsm_state8 = ap_CS_fsm[32'd7];

assign ap_CS_fsm_state9 = ap_CS_fsm[32'd8];

always @ (*) begin
    ap_block_state6 = (((icmp_ln207_fu_175_p2 == 1'd1) & (1'b0 == Output_1_V_TREADY)) | ((icmp_ln207_fu_175_p2 == 1'd0) & (1'b0 == Output_1_V_TREADY)));
end

always @ (*) begin
    ap_block_state6_io = (((icmp_ln207_fu_175_p2 == 1'd1) & (1'b0 == Output_1_V_TREADY)) | ((icmp_ln207_fu_175_p2 == 1'd0) & (1'b0 == Output_1_V_TREADY)));
end

assign icmp_ln207_fu_175_p2 = ((ret_17_reg_605 == ret_20_reg_611) ? 1'b1 : 1'b0);

assign icmp_ln878_1_fu_240_p2 = ((triangle_2d_same_x0_V_reg_666 < triangle_2d_x2) ? 1'b1 : 1'b0);

assign icmp_ln878_2_fu_212_p2 = ((triangle_2d_same_x1_V_reg_644 < triangle_2d_x2) ? 1'b1 : 1'b0);

assign icmp_ln878_3_fu_302_p2 = ((triangle_2d_same_y0_V_reg_655 < triangle_2d_same_y1_V_reg_633) ? 1'b1 : 1'b0);

assign icmp_ln878_4_fu_306_p2 = ((triangle_2d_same_y0_V_reg_655 < triangle_2d_y2) ? 1'b1 : 1'b0);

assign icmp_ln878_5_fu_224_p2 = ((triangle_2d_same_y1_V_reg_633 < triangle_2d_y2) ? 1'b1 : 1'b0);

assign icmp_ln878_fu_236_p2 = ((triangle_2d_same_x0_V_reg_666 < triangle_2d_same_x1_V_reg_644) ? 1'b1 : 1'b0);

assign icmp_ln886_1_fu_273_p2 = ((triangle_2d_same_x0_V_reg_666 > triangle_2d_x2) ? 1'b1 : 1'b0);

assign icmp_ln886_2_fu_216_p2 = ((triangle_2d_same_x1_V_reg_644 > triangle_2d_x2) ? 1'b1 : 1'b0);

assign icmp_ln886_3_fu_335_p2 = ((triangle_2d_same_y0_V_reg_655 > triangle_2d_same_y1_V_reg_633) ? 1'b1 : 1'b0);

assign icmp_ln886_4_fu_339_p2 = ((triangle_2d_same_y0_V_reg_655 > triangle_2d_y2) ? 1'b1 : 1'b0);

assign icmp_ln886_5_fu_228_p2 = ((triangle_2d_same_y1_V_reg_633 > triangle_2d_y2) ? 1'b1 : 1'b0);

assign icmp_ln886_fu_269_p2 = ((triangle_2d_same_x0_V_reg_666 > triangle_2d_same_x1_V_reg_644) ? 1'b1 : 1'b0);

assign lhs_5_fu_288_p3 = ((icmp_ln886_fu_269_p2[0:0] == 1'b1) ? select_ln63_fu_277_p3 : select_ln70_fu_283_p3);

assign lhs_6_fu_354_p3 = ((icmp_ln886_3_fu_335_p2[0:0] == 1'b1) ? select_ln63_1_fu_343_p3 : select_ln70_1_fu_349_p3);

assign ret_13_fu_378_p2 = (zext_ln215_2_fu_372_p1 - zext_ln215_3_fu_375_p1);

assign ret_14_fu_400_p2 = (zext_ln215_4_fu_394_p1 - zext_ln215_5_fu_397_p1);

assign ret_15_fu_107_p2 = (zext_ln215_fu_99_p1 - zext_ln1347_fu_103_p1);

assign ret_16_fu_121_p2 = (zext_ln215_1_fu_113_p1 - zext_ln1347_1_fu_117_p1);

assign ret_18_fu_131_p2 = (zext_ln1347_2_fu_127_p1 - zext_ln1347_1_fu_117_p1);

assign ret_19_fu_141_p2 = (zext_ln1347_3_fu_137_p1 - zext_ln1347_fu_103_p1);

assign ret_fu_171_p2 = (ret_17_reg_605 - ret_20_reg_611);

assign rhs_5_fu_255_p3 = ((icmp_ln878_fu_236_p2[0:0] == 1'b1) ? select_ln43_fu_244_p3 : select_ln50_fu_250_p3);

assign rhs_6_fu_321_p3 = ((icmp_ln878_3_fu_302_p2[0:0] == 1'b1) ? select_ln43_1_fu_310_p3 : select_ln50_1_fu_316_p3);

assign select_ln43_1_fu_310_p3 = ((icmp_ln878_4_fu_306_p2[0:0] == 1'b1) ? triangle_2d_same_y0_V_reg_655 : triangle_2d_y2);

assign select_ln43_fu_244_p3 = ((icmp_ln878_1_fu_240_p2[0:0] == 1'b1) ? triangle_2d_same_x0_V_reg_666 : triangle_2d_x2);

assign select_ln50_1_fu_316_p3 = ((icmp_ln878_5_reg_686[0:0] == 1'b1) ? triangle_2d_same_y1_V_reg_633 : triangle_2d_y2);

assign select_ln50_fu_250_p3 = ((icmp_ln878_2_reg_676[0:0] == 1'b1) ? triangle_2d_same_x1_V_reg_644 : triangle_2d_x2);

assign select_ln63_1_fu_343_p3 = ((icmp_ln886_4_fu_339_p2[0:0] == 1'b1) ? triangle_2d_same_y0_V_reg_655 : triangle_2d_y2);

assign select_ln63_fu_277_p3 = ((icmp_ln886_1_fu_273_p2[0:0] == 1'b1) ? triangle_2d_same_x0_V_reg_666 : triangle_2d_x2);

assign select_ln70_1_fu_349_p3 = ((icmp_ln886_5_reg_691[0:0] == 1'b1) ? triangle_2d_same_y1_V_reg_633 : triangle_2d_y2);

assign select_ln70_fu_283_p3 = ((icmp_ln886_2_reg_681[0:0] == 1'b1) ? triangle_2d_same_x1_V_reg_644 : triangle_2d_x2);

assign triangle_2d_same_x0_V_fu_202_p3 = ((tmp_reg_625[0:0] == 1'b1) ? triangle_2d_x1 : triangle_2d_x0);

assign triangle_2d_same_x1_V_fu_192_p3 = ((tmp_reg_625[0:0] == 1'b1) ? triangle_2d_x0 : triangle_2d_x1);

assign triangle_2d_same_y0_V_fu_197_p3 = ((tmp_reg_625[0:0] == 1'b1) ? triangle_2d_y1 : triangle_2d_y0);

assign triangle_2d_same_y1_V_fu_187_p3 = ((tmp_reg_625[0:0] == 1'b1) ? triangle_2d_y0 : triangle_2d_y1);

assign trunc_ln213_fu_384_p1 = ret_13_fu_378_p2[7:0];

assign zext_ln1347_1_fu_117_p1 = triangle_2d_y0;

assign zext_ln1347_2_fu_127_p1 = triangle_2d_y2;

assign zext_ln1347_3_fu_137_p1 = triangle_2d_x1;

assign zext_ln1347_fu_103_p1 = triangle_2d_x0;

assign zext_ln208_10_fu_449_p1 = rhs_6_reg_708;

assign zext_ln208_11_fu_453_p1 = lhs_6_reg_714;

assign zext_ln208_12_fu_457_p1 = trunc_ln213_reg_725;

assign zext_ln208_1_fu_474_p1 = max_min_V_7;

assign zext_ln208_2_fu_483_p1 = max_min_V_6;

assign zext_ln208_3_fu_492_p1 = max_min_V_5;

assign zext_ln208_4_fu_501_p1 = max_min_V_4;

assign zext_ln208_5_fu_510_p1 = max_min_V;

assign zext_ln208_6_fu_426_p1 = triangle_2d_z;

assign zext_ln208_7_fu_436_p1 = grp_fu_416_p2;

assign zext_ln208_8_fu_441_p1 = rhs_5_reg_696;

assign zext_ln208_9_fu_445_p1 = lhs_5_reg_702;

assign zext_ln208_fu_465_p1 = max_index_V;

assign zext_ln215_1_fu_113_p1 = triangle_2d_y1;

assign zext_ln215_2_fu_372_p1 = lhs_5_reg_702;

assign zext_ln215_3_fu_375_p1 = rhs_5_reg_696;

assign zext_ln215_4_fu_394_p1 = lhs_6_reg_714;

assign zext_ln215_5_fu_397_p1 = rhs_6_reg_708;

assign zext_ln215_fu_99_p1 = triangle_2d_x2;

assign zext_ln878_1_fu_232_p1 = triangle_2d_same_x1_V_reg_644;

assign zext_ln878_2_fu_406_p1 = triangle_2d_x2;

assign zext_ln878_3_fu_220_p1 = triangle_2d_same_y0_V_reg_655;

assign zext_ln878_4_fu_368_p1 = triangle_2d_same_y1_V_reg_633;

assign zext_ln878_5_fu_422_p1 = triangle_2d_y2;

assign zext_ln878_fu_207_p1 = triangle_2d_same_x0_V_fu_202_p3;

endmodule //data_redir_m_rasterization1_odd_m
