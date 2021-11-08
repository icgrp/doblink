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

parameter    ap_ST_fsm_state1 = 8'd1;
parameter    ap_ST_fsm_state2 = 8'd2;
parameter    ap_ST_fsm_state3 = 8'd4;
parameter    ap_ST_fsm_state4 = 8'd8;
parameter    ap_ST_fsm_state5 = 8'd16;
parameter    ap_ST_fsm_state6 = 8'd32;
parameter    ap_ST_fsm_state7 = 8'd64;
parameter    ap_ST_fsm_state8 = 8'd128;

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

(* fsm_encoding = "none" *) reg   [7:0] ap_CS_fsm;
wire    ap_CS_fsm_state1;
reg   [15:0] max_index_V;
reg   [7:0] max_min_V_4;
reg   [7:0] max_min_V_3;
reg   [7:0] max_min_V_2;
reg   [7:0] max_min_V_1;
reg   [7:0] max_min_V;
reg    Output_1_V_TDATA_blk_n;
wire   [0:0] icmp_ln208_fu_187_p2;
wire    ap_CS_fsm_state5;
wire    ap_CS_fsm_state6;
wire    ap_CS_fsm_state7;
wire    ap_CS_fsm_state2;
wire    ap_CS_fsm_state3;
wire    ap_CS_fsm_state4;
wire   [7:0] triangle_2d_same_y1_V_fu_201_p3;
reg   [7:0] triangle_2d_same_y1_V_reg_574;
wire   [7:0] triangle_2d_same_y0_V_fu_217_p3;
reg   [7:0] triangle_2d_same_y0_V_reg_585;
wire   [7:0] rhs_5_fu_267_p3;
reg   [7:0] rhs_5_reg_595;
wire   [7:0] lhs_5_fu_315_p3;
reg   [7:0] lhs_5_reg_601;
wire   [7:0] rhs_6_fu_366_p3;
reg   [7:0] rhs_6_reg_607;
wire   [7:0] lhs_6_fu_404_p3;
reg   [7:0] lhs_6_reg_613;
wire   [7:0] trunc_ln213_fu_439_p1;
reg   [7:0] trunc_ln213_reg_619;
wire   [15:0] mul_ln213_fu_469_p2;
reg    ap_block_state1;
reg    ap_block_state1_io;
wire   [31:0] p_Result_2_fu_329_p5;
wire   [31:0] p_Result_3_fu_418_p5;
wire   [31:0] p_Result_4_fu_481_p4;
wire   [31:0] p_Result_5_fu_490_p5;
wire   [31:0] p_Result_s_fu_512_p4;
wire   [31:0] p_Result_1_fu_535_p5;
wire   [8:0] zext_ln215_fu_105_p1;
wire   [8:0] zext_ln1347_fu_109_p1;
wire   [8:0] zext_ln215_1_fu_119_p1;
wire   [8:0] zext_ln1347_1_fu_123_p1;
wire  signed [8:0] ret_15_fu_113_p2;
wire  signed [8:0] ret_16_fu_127_p2;
wire   [8:0] zext_ln1347_2_fu_147_p1;
wire   [8:0] zext_ln1347_3_fu_157_p1;
wire  signed [8:0] ret_18_fu_151_p2;
wire  signed [8:0] ret_19_fu_161_p2;
wire   [17:0] ret_17_fu_141_p2;
wire   [17:0] ret_20_fu_175_p2;
wire   [17:0] ret_fu_181_p2;
wire   [0:0] tmp_fu_193_p3;
wire   [7:0] triangle_2d_same_x0_V_fu_225_p3;
wire   [7:0] triangle_2d_same_x1_V_fu_209_p3;
wire   [0:0] icmp_ln878_1_fu_239_p2;
wire   [0:0] icmp_ln878_2_fu_253_p2;
wire   [0:0] icmp_ln878_fu_233_p2;
wire   [7:0] select_ln119_fu_245_p3;
wire   [7:0] select_ln126_fu_259_p3;
wire   [0:0] icmp_ln886_1_fu_287_p2;
wire   [0:0] icmp_ln886_2_fu_301_p2;
wire   [0:0] icmp_ln886_fu_281_p2;
wire   [7:0] select_ln100_fu_293_p3;
wire   [7:0] select_ln107_fu_307_p3;
wire   [0:0] icmp_ln878_4_fu_346_p2;
wire   [0:0] icmp_ln878_5_fu_356_p2;
wire   [0:0] icmp_ln878_3_fu_342_p2;
wire   [7:0] select_ln119_1_fu_350_p3;
wire   [7:0] select_ln126_1_fu_360_p3;
wire   [0:0] icmp_ln886_4_fu_384_p2;
wire   [0:0] icmp_ln886_5_fu_394_p2;
wire   [0:0] icmp_ln886_3_fu_380_p2;
wire   [7:0] select_ln100_1_fu_388_p3;
wire   [7:0] select_ln107_1_fu_398_p3;
wire   [8:0] zext_ln215_2_fu_427_p1;
wire   [8:0] zext_ln215_3_fu_430_p1;
wire  signed [8:0] ret_13_fu_433_p2;
wire   [8:0] zext_ln215_4_fu_449_p1;
wire   [8:0] zext_ln215_5_fu_452_p1;
wire  signed [8:0] ret_14_fu_455_p2;
wire    ap_CS_fsm_state8;
reg   [7:0] ap_NS_fsm;
wire    ap_ce_reg;

// power-on initialization
initial begin
#0 ap_CS_fsm = 8'd1;
#0 max_index_V = 16'd0;
#0 max_min_V_4 = 8'd0;
#0 max_min_V_3 = 8'd0;
#0 max_min_V_2 = 8'd0;
#0 max_min_V_1 = 8'd0;
#0 max_min_V = 8'd0;
end

data_redir_m_mul_9s_9s_18_1_1 #(
    .ID( 1 ),
    .NUM_STAGE( 1 ),
    .din0_WIDTH( 9 ),
    .din1_WIDTH( 9 ),
    .dout_WIDTH( 18 ))
mul_9s_9s_18_1_1_U8(
    .din0(ret_15_fu_113_p2),
    .din1(ret_16_fu_127_p2),
    .dout(ret_17_fu_141_p2)
);

data_redir_m_mul_9s_9s_18_1_1 #(
    .ID( 1 ),
    .NUM_STAGE( 1 ),
    .din0_WIDTH( 9 ),
    .din1_WIDTH( 9 ),
    .dout_WIDTH( 18 ))
mul_9s_9s_18_1_1_U9(
    .din0(ret_18_fu_151_p2),
    .din1(ret_19_fu_161_p2),
    .dout(ret_20_fu_175_p2)
);

data_redir_m_mul_9s_9s_16_1_1 #(
    .ID( 1 ),
    .NUM_STAGE( 1 ),
    .din0_WIDTH( 9 ),
    .din1_WIDTH( 9 ),
    .dout_WIDTH( 16 ))
mul_9s_9s_16_1_1_U10(
    .din0(ret_13_fu_433_p2),
    .din1(ret_14_fu_455_p2),
    .dout(mul_ln213_fu_469_p2)
);

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_CS_fsm <= ap_ST_fsm_state1;
    end else begin
        ap_CS_fsm <= ap_NS_fsm;
    end
end

always @ (posedge ap_clk) begin
    if (((icmp_ln208_fu_187_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state1))) begin
        lhs_5_reg_601 <= lhs_5_fu_315_p3;
        rhs_5_reg_595 <= rhs_5_fu_267_p3;
        triangle_2d_same_y0_V_reg_585 <= triangle_2d_same_y0_V_fu_217_p3;
        triangle_2d_same_y1_V_reg_574 <= triangle_2d_same_y1_V_fu_201_p3;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state2)) begin
        lhs_6_reg_613 <= lhs_6_fu_404_p3;
        rhs_6_reg_607 <= rhs_6_fu_366_p3;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == ap_CS_fsm_state3) & (1'b1 == Output_1_V_TREADY))) begin
        max_index_V <= mul_ln213_fu_469_p2;
        max_min_V <= trunc_ln213_fu_439_p1;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == ap_CS_fsm_state2) & (1'b1 == Output_1_V_TREADY))) begin
        max_min_V_1 <= lhs_6_fu_404_p3;
        max_min_V_2 <= rhs_6_fu_366_p3;
    end
end

always @ (posedge ap_clk) begin
    if ((~((1'b1 == ap_block_state1_io) | (ap_start == 1'b0) | ((icmp_ln208_fu_187_p2 == 1'd0) & (1'b0 == Output_1_V_TREADY)) | ((icmp_ln208_fu_187_p2 == 1'd1) & (1'b0 == Output_1_V_TREADY))) & (icmp_ln208_fu_187_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state1))) begin
        max_min_V_3 <= lhs_5_fu_315_p3;
        max_min_V_4 <= rhs_5_fu_267_p3;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state3)) begin
        trunc_ln213_reg_619 <= trunc_ln213_fu_439_p1;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state7) & (1'b1 == Output_1_V_TREADY))) begin
        Output_1_V_TDATA = p_Result_1_fu_535_p5;
    end else if (((1'b1 == ap_CS_fsm_state6) & (1'b1 == Output_1_V_TREADY))) begin
        Output_1_V_TDATA = p_Result_s_fu_512_p4;
    end else if (((1'b1 == ap_CS_fsm_state5) & (1'b1 == Output_1_V_TREADY))) begin
        Output_1_V_TDATA = 32'd0;
    end else if (((1'b1 == ap_CS_fsm_state4) & (1'b1 == Output_1_V_TREADY))) begin
        Output_1_V_TDATA = p_Result_5_fu_490_p5;
    end else if (((1'b1 == ap_CS_fsm_state3) & (1'b1 == Output_1_V_TREADY))) begin
        Output_1_V_TDATA = p_Result_4_fu_481_p4;
    end else if (((1'b1 == ap_CS_fsm_state2) & (1'b1 == Output_1_V_TREADY))) begin
        Output_1_V_TDATA = p_Result_3_fu_418_p5;
    end else if ((~((ap_start == 1'b0) | ((icmp_ln208_fu_187_p2 == 1'd0) & (1'b0 == Output_1_V_TREADY)) | ((icmp_ln208_fu_187_p2 == 1'd1) & (1'b0 == Output_1_V_TREADY))) & (icmp_ln208_fu_187_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state1))) begin
        Output_1_V_TDATA = 32'd1;
    end else if ((~((ap_start == 1'b0) | ((icmp_ln208_fu_187_p2 == 1'd0) & (1'b0 == Output_1_V_TREADY)) | ((icmp_ln208_fu_187_p2 == 1'd1) & (1'b0 == Output_1_V_TREADY))) & (icmp_ln208_fu_187_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state1))) begin
        Output_1_V_TDATA = p_Result_2_fu_329_p5;
    end else begin
        Output_1_V_TDATA = 'bx;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state4) | (1'b1 == ap_CS_fsm_state3) | (1'b1 == ap_CS_fsm_state2) | (1'b1 == ap_CS_fsm_state7) | (1'b1 == ap_CS_fsm_state6) | (1'b1 == ap_CS_fsm_state5) | ((icmp_ln208_fu_187_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b1)) | ((icmp_ln208_fu_187_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b1)))) begin
        Output_1_V_TDATA_blk_n = Output_1_V_TREADY;
    end else begin
        Output_1_V_TDATA_blk_n = 1'b1;
    end
end

always @ (*) begin
    if ((((1'b1 == ap_CS_fsm_state4) & (1'b1 == Output_1_V_TREADY)) | ((1'b1 == ap_CS_fsm_state3) & (1'b1 == Output_1_V_TREADY)) | ((1'b1 == ap_CS_fsm_state2) & (1'b1 == Output_1_V_TREADY)) | ((1'b1 == ap_CS_fsm_state7) & (1'b1 == Output_1_V_TREADY)) | ((1'b1 == ap_CS_fsm_state6) & (1'b1 == Output_1_V_TREADY)) | ((1'b1 == ap_CS_fsm_state5) & (1'b1 == Output_1_V_TREADY)) | (~((1'b1 == ap_block_state1_io) | (ap_start == 1'b0) | ((icmp_ln208_fu_187_p2 == 1'd0) & (1'b0 == Output_1_V_TREADY)) | ((icmp_ln208_fu_187_p2 == 1'd1) & (1'b0 == Output_1_V_TREADY))) & (icmp_ln208_fu_187_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state1)) | (~((1'b1 == ap_block_state1_io) | (ap_start == 1'b0) | ((icmp_ln208_fu_187_p2 == 1'd0) & (1'b0 == Output_1_V_TREADY)) | ((icmp_ln208_fu_187_p2 == 1'd1) & (1'b0 == Output_1_V_TREADY))) & (icmp_ln208_fu_187_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state1)))) begin
        Output_1_V_TVALID = 1'b1;
    end else begin
        Output_1_V_TVALID = 1'b0;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state8) | ((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b0)))) begin
        ap_done = 1'b1;
    end else begin
        ap_done = 1'b0;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b0))) begin
        ap_idle = 1'b1;
    end else begin
        ap_idle = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state8)) begin
        ap_ready = 1'b1;
    end else begin
        ap_ready = 1'b0;
    end
end

always @ (*) begin
    case (ap_CS_fsm)
        ap_ST_fsm_state1 : begin
            if ((~((1'b1 == ap_block_state1_io) | (ap_start == 1'b0) | ((icmp_ln208_fu_187_p2 == 1'd0) & (1'b0 == Output_1_V_TREADY)) | ((icmp_ln208_fu_187_p2 == 1'd1) & (1'b0 == Output_1_V_TREADY))) & (icmp_ln208_fu_187_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state1))) begin
                ap_NS_fsm = ap_ST_fsm_state5;
            end else if ((~((1'b1 == ap_block_state1_io) | (ap_start == 1'b0) | ((icmp_ln208_fu_187_p2 == 1'd0) & (1'b0 == Output_1_V_TREADY)) | ((icmp_ln208_fu_187_p2 == 1'd1) & (1'b0 == Output_1_V_TREADY))) & (icmp_ln208_fu_187_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state1))) begin
                ap_NS_fsm = ap_ST_fsm_state2;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state1;
            end
        end
        ap_ST_fsm_state2 : begin
            if (((1'b1 == ap_CS_fsm_state2) & (1'b1 == Output_1_V_TREADY))) begin
                ap_NS_fsm = ap_ST_fsm_state3;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state2;
            end
        end
        ap_ST_fsm_state3 : begin
            if (((1'b1 == ap_CS_fsm_state3) & (1'b1 == Output_1_V_TREADY))) begin
                ap_NS_fsm = ap_ST_fsm_state4;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state3;
            end
        end
        ap_ST_fsm_state4 : begin
            if (((1'b1 == ap_CS_fsm_state4) & (1'b1 == Output_1_V_TREADY))) begin
                ap_NS_fsm = ap_ST_fsm_state8;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state4;
            end
        end
        ap_ST_fsm_state5 : begin
            if (((1'b1 == ap_CS_fsm_state5) & (1'b1 == Output_1_V_TREADY))) begin
                ap_NS_fsm = ap_ST_fsm_state6;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state5;
            end
        end
        ap_ST_fsm_state6 : begin
            if (((1'b1 == ap_CS_fsm_state6) & (1'b1 == Output_1_V_TREADY))) begin
                ap_NS_fsm = ap_ST_fsm_state7;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state6;
            end
        end
        ap_ST_fsm_state7 : begin
            if (((1'b1 == ap_CS_fsm_state7) & (1'b1 == Output_1_V_TREADY))) begin
                ap_NS_fsm = ap_ST_fsm_state8;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state7;
            end
        end
        ap_ST_fsm_state8 : begin
            ap_NS_fsm = ap_ST_fsm_state1;
        end
        default : begin
            ap_NS_fsm = 'bx;
        end
    endcase
end

assign ap_CS_fsm_state1 = ap_CS_fsm[32'd0];

assign ap_CS_fsm_state2 = ap_CS_fsm[32'd1];

assign ap_CS_fsm_state3 = ap_CS_fsm[32'd2];

assign ap_CS_fsm_state4 = ap_CS_fsm[32'd3];

assign ap_CS_fsm_state5 = ap_CS_fsm[32'd4];

assign ap_CS_fsm_state6 = ap_CS_fsm[32'd5];

assign ap_CS_fsm_state7 = ap_CS_fsm[32'd6];

assign ap_CS_fsm_state8 = ap_CS_fsm[32'd7];

always @ (*) begin
    ap_block_state1 = ((ap_start == 1'b0) | ((icmp_ln208_fu_187_p2 == 1'd0) & (1'b0 == Output_1_V_TREADY)) | ((icmp_ln208_fu_187_p2 == 1'd1) & (1'b0 == Output_1_V_TREADY)));
end

always @ (*) begin
    ap_block_state1_io = (((icmp_ln208_fu_187_p2 == 1'd0) & (1'b0 == Output_1_V_TREADY)) | ((icmp_ln208_fu_187_p2 == 1'd1) & (1'b0 == Output_1_V_TREADY)));
end

assign icmp_ln208_fu_187_p2 = ((ret_17_fu_141_p2 == ret_20_fu_175_p2) ? 1'b1 : 1'b0);

assign icmp_ln878_1_fu_239_p2 = ((triangle_2d_same_x0_V_fu_225_p3 < triangle_2d_x2) ? 1'b1 : 1'b0);

assign icmp_ln878_2_fu_253_p2 = ((triangle_2d_same_x1_V_fu_209_p3 < triangle_2d_x2) ? 1'b1 : 1'b0);

assign icmp_ln878_3_fu_342_p2 = ((triangle_2d_same_y0_V_reg_585 < triangle_2d_same_y1_V_reg_574) ? 1'b1 : 1'b0);

assign icmp_ln878_4_fu_346_p2 = ((triangle_2d_same_y0_V_reg_585 < triangle_2d_y2) ? 1'b1 : 1'b0);

assign icmp_ln878_5_fu_356_p2 = ((triangle_2d_same_y1_V_reg_574 < triangle_2d_y2) ? 1'b1 : 1'b0);

assign icmp_ln878_fu_233_p2 = ((triangle_2d_same_x0_V_fu_225_p3 < triangle_2d_same_x1_V_fu_209_p3) ? 1'b1 : 1'b0);

assign icmp_ln886_1_fu_287_p2 = ((triangle_2d_same_x0_V_fu_225_p3 > triangle_2d_x2) ? 1'b1 : 1'b0);

assign icmp_ln886_2_fu_301_p2 = ((triangle_2d_same_x1_V_fu_209_p3 > triangle_2d_x2) ? 1'b1 : 1'b0);

assign icmp_ln886_3_fu_380_p2 = ((triangle_2d_same_y0_V_reg_585 > triangle_2d_same_y1_V_reg_574) ? 1'b1 : 1'b0);

assign icmp_ln886_4_fu_384_p2 = ((triangle_2d_same_y0_V_reg_585 > triangle_2d_y2) ? 1'b1 : 1'b0);

assign icmp_ln886_5_fu_394_p2 = ((triangle_2d_same_y1_V_reg_574 > triangle_2d_y2) ? 1'b1 : 1'b0);

assign icmp_ln886_fu_281_p2 = ((triangle_2d_same_x0_V_fu_225_p3 > triangle_2d_same_x1_V_fu_209_p3) ? 1'b1 : 1'b0);

assign lhs_5_fu_315_p3 = ((icmp_ln886_fu_281_p2[0:0] == 1'b1) ? select_ln100_fu_293_p3 : select_ln107_fu_307_p3);

assign lhs_6_fu_404_p3 = ((icmp_ln886_3_fu_380_p2[0:0] == 1'b1) ? select_ln100_1_fu_388_p3 : select_ln107_1_fu_398_p3);

assign p_Result_1_fu_535_p5 = {{{{{{8'd0}, {max_min_V}}}, {max_min_V_1}}}, {max_min_V_2}};

assign p_Result_2_fu_329_p5 = {{{{triangle_2d_same_x1_V_fu_209_p3}, {triangle_2d_same_y0_V_fu_217_p3}}, {triangle_2d_same_x0_V_fu_225_p3}}, {8'd0}};

assign p_Result_3_fu_418_p5 = {{{{triangle_2d_z}, {triangle_2d_y2}}, {triangle_2d_x2}}, {triangle_2d_same_y1_V_reg_574}};

assign p_Result_4_fu_481_p4 = {{{lhs_5_reg_601}, {rhs_5_reg_595}}, {mul_ln213_fu_469_p2}};

assign p_Result_5_fu_490_p5 = {{{{{{8'd0}, {trunc_ln213_reg_619}}}, {lhs_6_reg_613}}}, {rhs_6_reg_607}};

assign p_Result_s_fu_512_p4 = {{{max_min_V_3}, {max_min_V_4}}, {max_index_V}};

assign ret_13_fu_433_p2 = (zext_ln215_2_fu_427_p1 - zext_ln215_3_fu_430_p1);

assign ret_14_fu_455_p2 = (zext_ln215_4_fu_449_p1 - zext_ln215_5_fu_452_p1);

assign ret_15_fu_113_p2 = (zext_ln215_fu_105_p1 - zext_ln1347_fu_109_p1);

assign ret_16_fu_127_p2 = (zext_ln215_1_fu_119_p1 - zext_ln1347_1_fu_123_p1);

assign ret_18_fu_151_p2 = (zext_ln1347_2_fu_147_p1 - zext_ln1347_1_fu_123_p1);

assign ret_19_fu_161_p2 = (zext_ln1347_3_fu_157_p1 - zext_ln1347_fu_109_p1);

assign ret_fu_181_p2 = (ret_17_fu_141_p2 - ret_20_fu_175_p2);

assign rhs_5_fu_267_p3 = ((icmp_ln878_fu_233_p2[0:0] == 1'b1) ? select_ln119_fu_245_p3 : select_ln126_fu_259_p3);

assign rhs_6_fu_366_p3 = ((icmp_ln878_3_fu_342_p2[0:0] == 1'b1) ? select_ln119_1_fu_350_p3 : select_ln126_1_fu_360_p3);

assign select_ln100_1_fu_388_p3 = ((icmp_ln886_4_fu_384_p2[0:0] == 1'b1) ? triangle_2d_same_y0_V_reg_585 : triangle_2d_y2);

assign select_ln100_fu_293_p3 = ((icmp_ln886_1_fu_287_p2[0:0] == 1'b1) ? triangle_2d_same_x0_V_fu_225_p3 : triangle_2d_x2);

assign select_ln107_1_fu_398_p3 = ((icmp_ln886_5_fu_394_p2[0:0] == 1'b1) ? triangle_2d_same_y1_V_reg_574 : triangle_2d_y2);

assign select_ln107_fu_307_p3 = ((icmp_ln886_2_fu_301_p2[0:0] == 1'b1) ? triangle_2d_same_x1_V_fu_209_p3 : triangle_2d_x2);

assign select_ln119_1_fu_350_p3 = ((icmp_ln878_4_fu_346_p2[0:0] == 1'b1) ? triangle_2d_same_y0_V_reg_585 : triangle_2d_y2);

assign select_ln119_fu_245_p3 = ((icmp_ln878_1_fu_239_p2[0:0] == 1'b1) ? triangle_2d_same_x0_V_fu_225_p3 : triangle_2d_x2);

assign select_ln126_1_fu_360_p3 = ((icmp_ln878_5_fu_356_p2[0:0] == 1'b1) ? triangle_2d_same_y1_V_reg_574 : triangle_2d_y2);

assign select_ln126_fu_259_p3 = ((icmp_ln878_2_fu_253_p2[0:0] == 1'b1) ? triangle_2d_same_x1_V_fu_209_p3 : triangle_2d_x2);

assign tmp_fu_193_p3 = ret_fu_181_p2[32'd17];

assign triangle_2d_same_x0_V_fu_225_p3 = ((tmp_fu_193_p3[0:0] == 1'b1) ? triangle_2d_x1 : triangle_2d_x0);

assign triangle_2d_same_x1_V_fu_209_p3 = ((tmp_fu_193_p3[0:0] == 1'b1) ? triangle_2d_x0 : triangle_2d_x1);

assign triangle_2d_same_y0_V_fu_217_p3 = ((tmp_fu_193_p3[0:0] == 1'b1) ? triangle_2d_y1 : triangle_2d_y0);

assign triangle_2d_same_y1_V_fu_201_p3 = ((tmp_fu_193_p3[0:0] == 1'b1) ? triangle_2d_y0 : triangle_2d_y1);

assign trunc_ln213_fu_439_p1 = ret_13_fu_433_p2[7:0];

assign zext_ln1347_1_fu_123_p1 = triangle_2d_y0;

assign zext_ln1347_2_fu_147_p1 = triangle_2d_y2;

assign zext_ln1347_3_fu_157_p1 = triangle_2d_x1;

assign zext_ln1347_fu_109_p1 = triangle_2d_x0;

assign zext_ln215_1_fu_119_p1 = triangle_2d_y1;

assign zext_ln215_2_fu_427_p1 = lhs_5_reg_601;

assign zext_ln215_3_fu_430_p1 = rhs_5_reg_595;

assign zext_ln215_4_fu_449_p1 = lhs_6_reg_613;

assign zext_ln215_5_fu_452_p1 = rhs_6_reg_607;

assign zext_ln215_fu_105_p1 = triangle_2d_x2;

endmodule //data_redir_m_rasterization1_odd_m