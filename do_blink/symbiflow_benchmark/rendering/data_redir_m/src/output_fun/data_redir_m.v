// ==============================================================
// RTL generated by Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Version: 2020.2
// Copyright (C) Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

`timescale 1 ns / 1 ps 

(* CORE_GENERATION_INFO="data_redir_m_data_redir_m,hls_ip_2020_2,{HLS_INPUT_TYPE=cxx,HLS_INPUT_FLOAT=0,HLS_INPUT_FIXED=0,HLS_INPUT_PART=xc7a200t-sbg484-1,HLS_INPUT_CLOCK=4.000000,HLS_INPUT_ARCH=others,HLS_SYN_CLOCK=3.678000,HLS_SYN_LAT=23,HLS_SYN_TPT=none,HLS_SYN_MEM=0,HLS_SYN_DSP=0,HLS_SYN_FF=638,HLS_SYN_LUT=808,HLS_VERSION=2020_2}" *)

module data_redir_m (
        ap_clk,
        ap_rst_n,
        ap_start,
        ap_done,
        ap_idle,
        ap_ready,
        Input_1_V_TDATA,
        Input_1_V_TVALID,
        Input_1_V_TREADY,
        Output_1_V_TDATA,
        Output_1_V_TVALID,
        Output_1_V_TREADY,
        Output_2_V_TDATA,
        Output_2_V_TVALID,
        Output_2_V_TREADY
);

parameter    ap_ST_fsm_state1 = 7'd1;
parameter    ap_ST_fsm_state2 = 7'd2;
parameter    ap_ST_fsm_state3 = 7'd4;
parameter    ap_ST_fsm_state4 = 7'd8;
parameter    ap_ST_fsm_state5 = 7'd16;
parameter    ap_ST_fsm_state6 = 7'd32;
parameter    ap_ST_fsm_state7 = 7'd64;

input   ap_clk;
input   ap_rst_n;
input   ap_start;
output   ap_done;
output   ap_idle;
output   ap_ready;
input  [31:0] Input_1_V_TDATA;
input   Input_1_V_TVALID;
output   Input_1_V_TREADY;
output  [31:0] Output_1_V_TDATA;
output   Output_1_V_TVALID;
input   Output_1_V_TREADY;
output  [31:0] Output_2_V_TDATA;
output   Output_2_V_TVALID;
input   Output_2_V_TREADY;

reg ap_done;
reg ap_idle;
reg ap_ready;

 reg    ap_rst_n_inv;
(* fsm_encoding = "none" *) reg   [6:0] ap_CS_fsm;
wire    ap_CS_fsm_state1;
reg   [31:0] cnt;
reg    Input_1_V_TDATA_blk_n;
wire    ap_CS_fsm_state2;
wire    ap_CS_fsm_state3;
reg   [31:0] tmp_reg_137;
reg   [31:0] tmp_3_reg_142;
wire   [7:0] trunc_ln155_fu_104_p1;
reg   [7:0] trunc_ln155_reg_147;
reg   [7:0] triangle_2ds_1_x0_V_reg_152;
wire    ap_CS_fsm_state4;
reg   [7:0] triangle_2ds_1_y0_V_reg_157;
reg   [7:0] triangle_2ds_1_x1_V_reg_162;
reg   [7:0] triangle_2ds_1_y1_V_reg_167;
reg   [7:0] triangle_2ds_1_x2_V_reg_172;
reg   [7:0] triangle_2ds_1_y2_V_reg_177;
reg   [7:0] triangle_2ds_1_z_V_reg_182;
wire    grp_rasterization1_fu_52_ap_start;
wire    grp_rasterization1_fu_52_ap_done;
wire    grp_rasterization1_fu_52_ap_idle;
wire    grp_rasterization1_fu_52_ap_ready;
wire   [31:0] grp_rasterization1_fu_52_Output_1_V_TDATA;
wire    grp_rasterization1_fu_52_Output_1_V_TVALID;
wire    grp_rasterization1_fu_52_Output_1_V_TREADY;
wire   [31:0] grp_rasterization1_fu_52_Output_2_V_TDATA;
wire    grp_rasterization1_fu_52_Output_2_V_TVALID;
wire    grp_rasterization1_fu_52_Output_2_V_TREADY;
wire  signed [8:0] grp_rasterization1_fu_52_grp_fu_199_p_din0;
wire  signed [8:0] grp_rasterization1_fu_52_grp_fu_199_p_din1;
wire   [17:0] grp_rasterization1_fu_52_grp_fu_199_p_dout0;
wire    grp_rasterization1_fu_52_grp_fu_199_p_ce;
wire  signed [8:0] grp_rasterization1_fu_52_grp_fu_203_p_din0;
wire  signed [8:0] grp_rasterization1_fu_52_grp_fu_203_p_din1;
wire   [17:0] grp_rasterization1_fu_52_grp_fu_203_p_dout0;
wire    grp_rasterization1_fu_52_grp_fu_203_p_ce;
wire  signed [8:0] grp_rasterization1_fu_52_grp_fu_207_p_din0;
wire  signed [8:0] grp_rasterization1_fu_52_grp_fu_207_p_din1;
wire   [15:0] grp_rasterization1_fu_52_grp_fu_207_p_dout0;
wire    grp_rasterization1_fu_52_grp_fu_207_p_ce;
wire    grp_projection_fu_81_ap_start;
wire    grp_projection_fu_81_ap_done;
wire    grp_projection_fu_81_ap_idle;
wire    grp_projection_fu_81_ap_ready;
wire   [7:0] grp_projection_fu_81_ap_return_0;
wire   [7:0] grp_projection_fu_81_ap_return_1;
wire   [7:0] grp_projection_fu_81_ap_return_2;
wire   [7:0] grp_projection_fu_81_ap_return_3;
wire   [7:0] grp_projection_fu_81_ap_return_4;
wire   [7:0] grp_projection_fu_81_ap_return_5;
wire   [7:0] grp_projection_fu_81_ap_return_6;
wire   [7:0] grp_projection_fu_81_grp_fu_187_p_din0;
wire   [9:0] grp_projection_fu_81_grp_fu_187_p_din1;
wire   [16:0] grp_projection_fu_81_grp_fu_187_p_dout0;
wire    grp_projection_fu_81_grp_fu_187_p_ce;
wire   [7:0] grp_projection_fu_81_grp_fu_191_p_din0;
wire   [9:0] grp_projection_fu_81_grp_fu_191_p_din1;
wire   [16:0] grp_projection_fu_81_grp_fu_191_p_dout0;
wire    grp_projection_fu_81_grp_fu_191_p_ce;
wire   [7:0] grp_projection_fu_81_grp_fu_195_p_din0;
wire   [9:0] grp_projection_fu_81_grp_fu_195_p_din1;
wire   [16:0] grp_projection_fu_81_grp_fu_195_p_dout0;
wire    grp_projection_fu_81_grp_fu_195_p_ce;
reg    grp_rasterization1_fu_52_ap_start_reg;
wire    ap_CS_fsm_state5;
wire    ap_CS_fsm_state6;
reg    grp_projection_fu_81_ap_start_reg;
wire   [31:0] add_ln317_fu_92_p2;
reg    ap_block_state1;
wire   [16:0] grp_fu_187_p2;
wire   [7:0] grp_fu_187_p0;
wire   [9:0] grp_fu_187_p1;
reg    grp_fu_187_ce;
wire   [16:0] grp_fu_191_p2;
wire   [7:0] grp_fu_191_p0;
wire   [9:0] grp_fu_191_p1;
reg    grp_fu_191_ce;
wire   [16:0] grp_fu_195_p2;
wire   [7:0] grp_fu_195_p0;
wire   [9:0] grp_fu_195_p1;
reg    grp_fu_195_ce;
wire   [17:0] grp_fu_199_p2;
wire  signed [8:0] grp_fu_199_p0;
wire  signed [8:0] grp_fu_199_p1;
reg    grp_fu_199_ce;
wire   [17:0] grp_fu_203_p2;
wire  signed [8:0] grp_fu_203_p0;
wire  signed [8:0] grp_fu_203_p1;
reg    grp_fu_203_ce;
wire   [15:0] grp_fu_207_p2;
wire  signed [8:0] grp_fu_207_p0;
wire  signed [8:0] grp_fu_207_p1;
reg    grp_fu_207_ce;
wire    ap_CS_fsm_state7;
wire    regslice_both_Output_1_V_U_apdone_blk;
wire    regslice_both_Output_2_V_U_apdone_blk;
reg    ap_block_state7;
reg   [6:0] ap_NS_fsm;
wire    regslice_both_Input_1_V_U_apdone_blk;
wire   [31:0] Input_1_V_TDATA_int_regslice;
wire    Input_1_V_TVALID_int_regslice;
reg    Input_1_V_TREADY_int_regslice;
wire    regslice_both_Input_1_V_U_ack_in;
wire    Output_1_V_TREADY_int_regslice;
wire    regslice_both_Output_1_V_U_vld_out;
wire    Output_2_V_TREADY_int_regslice;
wire    regslice_both_Output_2_V_U_vld_out;
wire    ap_ce_reg;

// power-on initialization
initial begin
#0 ap_CS_fsm = 7'd1;
#0 cnt = 32'd0;
#0 tmp_reg_137 = 32'd0;
#0 tmp_3_reg_142 = 32'd0;
#0 trunc_ln155_reg_147 = 8'd0;
#0 triangle_2ds_1_x0_V_reg_152 = 8'd0;
#0 triangle_2ds_1_y0_V_reg_157 = 8'd0;
#0 triangle_2ds_1_x1_V_reg_162 = 8'd0;
#0 triangle_2ds_1_y1_V_reg_167 = 8'd0;
#0 triangle_2ds_1_x2_V_reg_172 = 8'd0;
#0 triangle_2ds_1_y2_V_reg_177 = 8'd0;
#0 triangle_2ds_1_z_V_reg_182 = 8'd0;
#0 grp_rasterization1_fu_52_ap_start_reg = 1'b0;
#0 grp_projection_fu_81_ap_start_reg = 1'b0;
end

data_redir_m_rasterization1 grp_rasterization1_fu_52(
    .ap_clk(ap_clk),
    .ap_rst(ap_rst_n_inv),
    .ap_start(grp_rasterization1_fu_52_ap_start),
    .ap_done(grp_rasterization1_fu_52_ap_done),
    .ap_idle(grp_rasterization1_fu_52_ap_idle),
    .ap_ready(grp_rasterization1_fu_52_ap_ready),
    .Output_1_V_TDATA(grp_rasterization1_fu_52_Output_1_V_TDATA),
    .Output_1_V_TVALID(grp_rasterization1_fu_52_Output_1_V_TVALID),
    .Output_1_V_TREADY(grp_rasterization1_fu_52_Output_1_V_TREADY),
    .Output_2_V_TDATA(grp_rasterization1_fu_52_Output_2_V_TDATA),
    .Output_2_V_TVALID(grp_rasterization1_fu_52_Output_2_V_TVALID),
    .Output_2_V_TREADY(grp_rasterization1_fu_52_Output_2_V_TREADY),
    .triangle_2d_x0(triangle_2ds_1_x0_V_reg_152),
    .triangle_2d_y0(triangle_2ds_1_y0_V_reg_157),
    .triangle_2d_x1(triangle_2ds_1_x1_V_reg_162),
    .triangle_2d_y1(triangle_2ds_1_y1_V_reg_167),
    .triangle_2d_x2(triangle_2ds_1_x2_V_reg_172),
    .triangle_2d_y2(triangle_2ds_1_y2_V_reg_177),
    .triangle_2d_z(triangle_2ds_1_z_V_reg_182),
    .grp_fu_199_p_din0(grp_rasterization1_fu_52_grp_fu_199_p_din0),
    .grp_fu_199_p_din1(grp_rasterization1_fu_52_grp_fu_199_p_din1),
    .grp_fu_199_p_dout0(grp_rasterization1_fu_52_grp_fu_199_p_dout0),
    .grp_fu_199_p_ce(grp_rasterization1_fu_52_grp_fu_199_p_ce),
    .grp_fu_203_p_din0(grp_rasterization1_fu_52_grp_fu_203_p_din0),
    .grp_fu_203_p_din1(grp_rasterization1_fu_52_grp_fu_203_p_din1),
    .grp_fu_203_p_dout0(grp_rasterization1_fu_52_grp_fu_203_p_dout0),
    .grp_fu_203_p_ce(grp_rasterization1_fu_52_grp_fu_203_p_ce),
    .grp_fu_207_p_din0(grp_rasterization1_fu_52_grp_fu_207_p_din0),
    .grp_fu_207_p_din1(grp_rasterization1_fu_52_grp_fu_207_p_din1),
    .grp_fu_207_p_dout0(grp_rasterization1_fu_52_grp_fu_207_p_dout0),
    .grp_fu_207_p_ce(grp_rasterization1_fu_52_grp_fu_207_p_ce)
);

data_redir_m_projection grp_projection_fu_81(
    .ap_clk(ap_clk),
    .ap_rst(ap_rst_n_inv),
    .ap_start(grp_projection_fu_81_ap_start),
    .ap_done(grp_projection_fu_81_ap_done),
    .ap_idle(grp_projection_fu_81_ap_idle),
    .ap_ready(grp_projection_fu_81_ap_ready),
    .input_lo(tmp_reg_137),
    .input_mi(tmp_3_reg_142),
    .input_hi(trunc_ln155_reg_147),
    .ap_return_0(grp_projection_fu_81_ap_return_0),
    .ap_return_1(grp_projection_fu_81_ap_return_1),
    .ap_return_2(grp_projection_fu_81_ap_return_2),
    .ap_return_3(grp_projection_fu_81_ap_return_3),
    .ap_return_4(grp_projection_fu_81_ap_return_4),
    .ap_return_5(grp_projection_fu_81_ap_return_5),
    .ap_return_6(grp_projection_fu_81_ap_return_6),
    .grp_fu_187_p_din0(grp_projection_fu_81_grp_fu_187_p_din0),
    .grp_fu_187_p_din1(grp_projection_fu_81_grp_fu_187_p_din1),
    .grp_fu_187_p_dout0(grp_projection_fu_81_grp_fu_187_p_dout0),
    .grp_fu_187_p_ce(grp_projection_fu_81_grp_fu_187_p_ce),
    .grp_fu_191_p_din0(grp_projection_fu_81_grp_fu_191_p_din0),
    .grp_fu_191_p_din1(grp_projection_fu_81_grp_fu_191_p_din1),
    .grp_fu_191_p_dout0(grp_projection_fu_81_grp_fu_191_p_dout0),
    .grp_fu_191_p_ce(grp_projection_fu_81_grp_fu_191_p_ce),
    .grp_fu_195_p_din0(grp_projection_fu_81_grp_fu_195_p_din0),
    .grp_fu_195_p_din1(grp_projection_fu_81_grp_fu_195_p_din1),
    .grp_fu_195_p_dout0(grp_projection_fu_81_grp_fu_195_p_dout0),
    .grp_fu_195_p_ce(grp_projection_fu_81_grp_fu_195_p_ce)
);

data_redir_m_mul_8ns_10ns_17_4_1 #(
    .ID( 1 ),
    .NUM_STAGE( 4 ),
    .din0_WIDTH( 8 ),
    .din1_WIDTH( 10 ),
    .dout_WIDTH( 17 ))
mul_8ns_10ns_17_4_1_U22(
    .clk(ap_clk),
    .reset(ap_rst_n_inv),
    .din0(grp_fu_187_p0),
    .din1(grp_fu_187_p1),
    .ce(grp_fu_187_ce),
    .dout(grp_fu_187_p2)
);

data_redir_m_mul_8ns_10ns_17_4_1 #(
    .ID( 1 ),
    .NUM_STAGE( 4 ),
    .din0_WIDTH( 8 ),
    .din1_WIDTH( 10 ),
    .dout_WIDTH( 17 ))
mul_8ns_10ns_17_4_1_U23(
    .clk(ap_clk),
    .reset(ap_rst_n_inv),
    .din0(grp_fu_191_p0),
    .din1(grp_fu_191_p1),
    .ce(grp_fu_191_ce),
    .dout(grp_fu_191_p2)
);

data_redir_m_mul_8ns_10ns_17_4_1 #(
    .ID( 1 ),
    .NUM_STAGE( 4 ),
    .din0_WIDTH( 8 ),
    .din1_WIDTH( 10 ),
    .dout_WIDTH( 17 ))
mul_8ns_10ns_17_4_1_U24(
    .clk(ap_clk),
    .reset(ap_rst_n_inv),
    .din0(grp_fu_195_p0),
    .din1(grp_fu_195_p1),
    .ce(grp_fu_195_ce),
    .dout(grp_fu_195_p2)
);

data_redir_m_mul_9s_9s_18_4_1 #(
    .ID( 1 ),
    .NUM_STAGE( 4 ),
    .din0_WIDTH( 9 ),
    .din1_WIDTH( 9 ),
    .dout_WIDTH( 18 ))
mul_9s_9s_18_4_1_U25(
    .clk(ap_clk),
    .reset(ap_rst_n_inv),
    .din0(grp_fu_199_p0),
    .din1(grp_fu_199_p1),
    .ce(grp_fu_199_ce),
    .dout(grp_fu_199_p2)
);

data_redir_m_mul_9s_9s_18_4_1 #(
    .ID( 1 ),
    .NUM_STAGE( 4 ),
    .din0_WIDTH( 9 ),
    .din1_WIDTH( 9 ),
    .dout_WIDTH( 18 ))
mul_9s_9s_18_4_1_U26(
    .clk(ap_clk),
    .reset(ap_rst_n_inv),
    .din0(grp_fu_203_p0),
    .din1(grp_fu_203_p1),
    .ce(grp_fu_203_ce),
    .dout(grp_fu_203_p2)
);

data_redir_m_mul_9s_9s_16_4_1 #(
    .ID( 1 ),
    .NUM_STAGE( 4 ),
    .din0_WIDTH( 9 ),
    .din1_WIDTH( 9 ),
    .dout_WIDTH( 16 ))
mul_9s_9s_16_4_1_U27(
    .clk(ap_clk),
    .reset(ap_rst_n_inv),
    .din0(grp_fu_207_p0),
    .din1(grp_fu_207_p1),
    .ce(grp_fu_207_ce),
    .dout(grp_fu_207_p2)
);

data_redir_m_regslice_both #(
    .DataWidth( 32 ))
regslice_both_Input_1_V_U(
    .ap_clk(ap_clk),
    .ap_rst(ap_rst_n_inv),
    .data_in(Input_1_V_TDATA),
    .vld_in(Input_1_V_TVALID),
    .ack_in(regslice_both_Input_1_V_U_ack_in),
    .data_out(Input_1_V_TDATA_int_regslice),
    .vld_out(Input_1_V_TVALID_int_regslice),
    .ack_out(Input_1_V_TREADY_int_regslice),
    .apdone_blk(regslice_both_Input_1_V_U_apdone_blk)
);

data_redir_m_regslice_both #(
    .DataWidth( 32 ))
regslice_both_Output_1_V_U(
    .ap_clk(ap_clk),
    .ap_rst(ap_rst_n_inv),
    .data_in(grp_rasterization1_fu_52_Output_1_V_TDATA),
    .vld_in(grp_rasterization1_fu_52_Output_1_V_TVALID),
    .ack_in(Output_1_V_TREADY_int_regslice),
    .data_out(Output_1_V_TDATA),
    .vld_out(regslice_both_Output_1_V_U_vld_out),
    .ack_out(Output_1_V_TREADY),
    .apdone_blk(regslice_both_Output_1_V_U_apdone_blk)
);

data_redir_m_regslice_both #(
    .DataWidth( 32 ))
regslice_both_Output_2_V_U(
    .ap_clk(ap_clk),
    .ap_rst(ap_rst_n_inv),
    .data_in(grp_rasterization1_fu_52_Output_2_V_TDATA),
    .vld_in(grp_rasterization1_fu_52_Output_2_V_TVALID),
    .ack_in(Output_2_V_TREADY_int_regslice),
    .data_out(Output_2_V_TDATA),
    .vld_out(regslice_both_Output_2_V_U_vld_out),
    .ack_out(Output_2_V_TREADY),
    .apdone_blk(regslice_both_Output_2_V_U_apdone_blk)
);

always @ (posedge ap_clk) begin
    if (ap_rst_n_inv == 1'b1) begin
        ap_CS_fsm <= ap_ST_fsm_state1;
    end else begin
        ap_CS_fsm <= ap_NS_fsm;
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst_n_inv == 1'b1) begin
        cnt <= 32'd0;
    end else begin
        if ((~((1'b0 == Input_1_V_TVALID_int_regslice) | (ap_start == 1'b0)) & (1'b1 == ap_CS_fsm_state1))) begin
            cnt <= add_ln317_fu_92_p2;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst_n_inv == 1'b1) begin
        grp_projection_fu_81_ap_start_reg <= 1'b0;
    end else begin
        if (((1'b1 == ap_CS_fsm_state3) & (1'b1 == Input_1_V_TVALID_int_regslice))) begin
            grp_projection_fu_81_ap_start_reg <= 1'b1;
        end else if ((grp_projection_fu_81_ap_ready == 1'b1)) begin
            grp_projection_fu_81_ap_start_reg <= 1'b0;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst_n_inv == 1'b1) begin
        grp_rasterization1_fu_52_ap_start_reg <= 1'b0;
    end else begin
        if ((1'b1 == ap_CS_fsm_state5)) begin
            grp_rasterization1_fu_52_ap_start_reg <= 1'b1;
        end else if ((grp_rasterization1_fu_52_ap_ready == 1'b1)) begin
            grp_rasterization1_fu_52_ap_start_reg <= 1'b0;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst_n_inv == 1'b1) begin
        tmp_3_reg_142 <= 32'd0;
    end else begin
        if ((1'b1 == ap_CS_fsm_state2)) begin
            tmp_3_reg_142 <= Input_1_V_TDATA_int_regslice;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst_n_inv == 1'b1) begin
        tmp_reg_137 <= 32'd0;
    end else begin
        if ((1'b1 == ap_CS_fsm_state1)) begin
            tmp_reg_137 <= Input_1_V_TDATA_int_regslice;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst_n_inv == 1'b1) begin
        triangle_2ds_1_x0_V_reg_152 <= 8'd0;
    end else begin
        if ((1'b1 == ap_CS_fsm_state4)) begin
            triangle_2ds_1_x0_V_reg_152 <= grp_projection_fu_81_ap_return_0;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst_n_inv == 1'b1) begin
        triangle_2ds_1_x1_V_reg_162 <= 8'd0;
    end else begin
        if ((1'b1 == ap_CS_fsm_state4)) begin
            triangle_2ds_1_x1_V_reg_162 <= grp_projection_fu_81_ap_return_2;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst_n_inv == 1'b1) begin
        triangle_2ds_1_x2_V_reg_172 <= 8'd0;
    end else begin
        if ((1'b1 == ap_CS_fsm_state4)) begin
            triangle_2ds_1_x2_V_reg_172 <= grp_projection_fu_81_ap_return_4;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst_n_inv == 1'b1) begin
        triangle_2ds_1_y0_V_reg_157 <= 8'd0;
    end else begin
        if ((1'b1 == ap_CS_fsm_state4)) begin
            triangle_2ds_1_y0_V_reg_157 <= grp_projection_fu_81_ap_return_1;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst_n_inv == 1'b1) begin
        triangle_2ds_1_y1_V_reg_167 <= 8'd0;
    end else begin
        if ((1'b1 == ap_CS_fsm_state4)) begin
            triangle_2ds_1_y1_V_reg_167 <= grp_projection_fu_81_ap_return_3;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst_n_inv == 1'b1) begin
        triangle_2ds_1_y2_V_reg_177 <= 8'd0;
    end else begin
        if ((1'b1 == ap_CS_fsm_state4)) begin
            triangle_2ds_1_y2_V_reg_177 <= grp_projection_fu_81_ap_return_5;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst_n_inv == 1'b1) begin
        triangle_2ds_1_z_V_reg_182 <= 8'd0;
    end else begin
        if ((1'b1 == ap_CS_fsm_state4)) begin
            triangle_2ds_1_z_V_reg_182 <= grp_projection_fu_81_ap_return_6;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst_n_inv == 1'b1) begin
        trunc_ln155_reg_147 <= 8'd0;
    end else begin
        if ((1'b1 == ap_CS_fsm_state3)) begin
            trunc_ln155_reg_147 <= trunc_ln155_fu_104_p1;
        end
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state3) | (1'b1 == ap_CS_fsm_state2) | ((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b1)))) begin
        Input_1_V_TDATA_blk_n = Input_1_V_TVALID_int_regslice;
    end else begin
        Input_1_V_TDATA_blk_n = 1'b1;
    end
end

always @ (*) begin
    if ((((1'b1 == ap_CS_fsm_state3) & (1'b1 == Input_1_V_TVALID_int_regslice)) | ((1'b1 == ap_CS_fsm_state2) & (1'b1 == Input_1_V_TVALID_int_regslice)) | (~((1'b0 == Input_1_V_TVALID_int_regslice) | (ap_start == 1'b0)) & (1'b1 == ap_CS_fsm_state1)))) begin
        Input_1_V_TREADY_int_regslice = 1'b1;
    end else begin
        Input_1_V_TREADY_int_regslice = 1'b0;
    end
end

always @ (*) begin
    if ((~((regslice_both_Output_2_V_U_apdone_blk == 1'b1) | (regslice_both_Output_1_V_U_apdone_blk == 1'b1)) & (1'b1 == ap_CS_fsm_state7))) begin
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
    if ((~((regslice_both_Output_2_V_U_apdone_blk == 1'b1) | (regslice_both_Output_1_V_U_apdone_blk == 1'b1)) & (1'b1 == ap_CS_fsm_state7))) begin
        ap_ready = 1'b1;
    end else begin
        ap_ready = 1'b0;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state4) | (1'b1 == ap_CS_fsm_state3))) begin
        grp_fu_187_ce = grp_projection_fu_81_grp_fu_187_p_ce;
    end else begin
        grp_fu_187_ce = 1'b1;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state4) | (1'b1 == ap_CS_fsm_state3))) begin
        grp_fu_191_ce = grp_projection_fu_81_grp_fu_191_p_ce;
    end else begin
        grp_fu_191_ce = 1'b1;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state4) | (1'b1 == ap_CS_fsm_state3))) begin
        grp_fu_195_ce = grp_projection_fu_81_grp_fu_195_p_ce;
    end else begin
        grp_fu_195_ce = 1'b1;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state6) | (1'b1 == ap_CS_fsm_state5))) begin
        grp_fu_199_ce = grp_rasterization1_fu_52_grp_fu_199_p_ce;
    end else begin
        grp_fu_199_ce = 1'b1;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state6) | (1'b1 == ap_CS_fsm_state5))) begin
        grp_fu_203_ce = grp_rasterization1_fu_52_grp_fu_203_p_ce;
    end else begin
        grp_fu_203_ce = 1'b1;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state6) | (1'b1 == ap_CS_fsm_state5))) begin
        grp_fu_207_ce = grp_rasterization1_fu_52_grp_fu_207_p_ce;
    end else begin
        grp_fu_207_ce = 1'b1;
    end
end

always @ (*) begin
    case (ap_CS_fsm)
        ap_ST_fsm_state1 : begin
            if ((~((1'b0 == Input_1_V_TVALID_int_regslice) | (ap_start == 1'b0)) & (1'b1 == ap_CS_fsm_state1))) begin
                ap_NS_fsm = ap_ST_fsm_state2;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state1;
            end
        end
        ap_ST_fsm_state2 : begin
            if (((1'b1 == ap_CS_fsm_state2) & (1'b1 == Input_1_V_TVALID_int_regslice))) begin
                ap_NS_fsm = ap_ST_fsm_state3;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state2;
            end
        end
        ap_ST_fsm_state3 : begin
            if (((1'b1 == ap_CS_fsm_state3) & (1'b1 == Input_1_V_TVALID_int_regslice))) begin
                ap_NS_fsm = ap_ST_fsm_state4;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state3;
            end
        end
        ap_ST_fsm_state4 : begin
            if (((1'b1 == ap_CS_fsm_state4) & (grp_projection_fu_81_ap_done == 1'b1))) begin
                ap_NS_fsm = ap_ST_fsm_state5;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state4;
            end
        end
        ap_ST_fsm_state5 : begin
            ap_NS_fsm = ap_ST_fsm_state6;
        end
        ap_ST_fsm_state6 : begin
            if (((grp_rasterization1_fu_52_ap_done == 1'b1) & (1'b1 == ap_CS_fsm_state6))) begin
                ap_NS_fsm = ap_ST_fsm_state7;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state6;
            end
        end
        ap_ST_fsm_state7 : begin
            if ((~((regslice_both_Output_2_V_U_apdone_blk == 1'b1) | (regslice_both_Output_1_V_U_apdone_blk == 1'b1)) & (1'b1 == ap_CS_fsm_state7))) begin
                ap_NS_fsm = ap_ST_fsm_state1;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state7;
            end
        end
        default : begin
            ap_NS_fsm = 'bx;
        end
    endcase
end

assign Input_1_V_TREADY = regslice_both_Input_1_V_U_ack_in;

assign Output_1_V_TVALID = regslice_both_Output_1_V_U_vld_out;

assign Output_2_V_TVALID = regslice_both_Output_2_V_U_vld_out;

assign add_ln317_fu_92_p2 = (cnt + 32'd1);

assign ap_CS_fsm_state1 = ap_CS_fsm[32'd0];

assign ap_CS_fsm_state2 = ap_CS_fsm[32'd1];

assign ap_CS_fsm_state3 = ap_CS_fsm[32'd2];

assign ap_CS_fsm_state4 = ap_CS_fsm[32'd3];

assign ap_CS_fsm_state5 = ap_CS_fsm[32'd4];

assign ap_CS_fsm_state6 = ap_CS_fsm[32'd5];

assign ap_CS_fsm_state7 = ap_CS_fsm[32'd6];

always @ (*) begin
    ap_block_state1 = ((1'b0 == Input_1_V_TVALID_int_regslice) | (ap_start == 1'b0));
end

always @ (*) begin
    ap_block_state7 = ((regslice_both_Output_2_V_U_apdone_blk == 1'b1) | (regslice_both_Output_1_V_U_apdone_blk == 1'b1));
end

always @ (*) begin
    ap_rst_n_inv = ~ap_rst_n;
end

assign grp_fu_187_p0 = grp_projection_fu_81_grp_fu_187_p_din0;

assign grp_fu_187_p1 = grp_projection_fu_81_grp_fu_187_p_din1;

assign grp_fu_191_p0 = grp_projection_fu_81_grp_fu_191_p_din0;

assign grp_fu_191_p1 = grp_projection_fu_81_grp_fu_191_p_din1;

assign grp_fu_195_p0 = grp_projection_fu_81_grp_fu_195_p_din0;

assign grp_fu_195_p1 = grp_projection_fu_81_grp_fu_195_p_din1;

assign grp_fu_199_p0 = grp_rasterization1_fu_52_grp_fu_199_p_din0;

assign grp_fu_199_p1 = grp_rasterization1_fu_52_grp_fu_199_p_din1;

assign grp_fu_203_p0 = grp_rasterization1_fu_52_grp_fu_203_p_din0;

assign grp_fu_203_p1 = grp_rasterization1_fu_52_grp_fu_203_p_din1;

assign grp_fu_207_p0 = grp_rasterization1_fu_52_grp_fu_207_p_din0;

assign grp_fu_207_p1 = grp_rasterization1_fu_52_grp_fu_207_p_din1;

assign grp_projection_fu_81_ap_start = grp_projection_fu_81_ap_start_reg;

assign grp_projection_fu_81_grp_fu_187_p_dout0 = grp_fu_187_p2;

assign grp_projection_fu_81_grp_fu_191_p_dout0 = grp_fu_191_p2;

assign grp_projection_fu_81_grp_fu_195_p_dout0 = grp_fu_195_p2;

assign grp_rasterization1_fu_52_Output_1_V_TREADY = (ap_CS_fsm_state6 & Output_1_V_TREADY_int_regslice);

assign grp_rasterization1_fu_52_Output_2_V_TREADY = (ap_CS_fsm_state6 & Output_2_V_TREADY_int_regslice);

assign grp_rasterization1_fu_52_ap_start = grp_rasterization1_fu_52_ap_start_reg;

assign grp_rasterization1_fu_52_grp_fu_199_p_dout0 = grp_fu_199_p2;

assign grp_rasterization1_fu_52_grp_fu_203_p_dout0 = grp_fu_203_p2;

assign grp_rasterization1_fu_52_grp_fu_207_p_dout0 = grp_fu_207_p2;

assign trunc_ln155_fu_104_p1 = Input_1_V_TDATA_int_regslice[7:0];

endmodule //data_redir_m
