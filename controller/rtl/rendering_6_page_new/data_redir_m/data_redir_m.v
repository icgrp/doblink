// ==============================================================
// RTL generated by Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Version: 2020.2
// Copyright (C) Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

`timescale 1 ns / 1 ps 

(* CORE_GENERATION_INFO="data_redir_m_data_redir_m,hls_ip_2020_2,{HLS_INPUT_TYPE=cxx,HLS_INPUT_FLOAT=0,HLS_INPUT_FIXED=0,HLS_INPUT_PART=xc7a200t-sbg484-1,HLS_INPUT_CLOCK=4.000000,HLS_INPUT_ARCH=others,HLS_SYN_CLOCK=3.678000,HLS_SYN_LAT=31,HLS_SYN_TPT=none,HLS_SYN_MEM=0,HLS_SYN_DSP=0,HLS_SYN_FF=681,HLS_SYN_LUT=1454,HLS_VERSION=2020_2}" *)

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

parameter    ap_ST_fsm_state1 = 13'd1;
parameter    ap_ST_fsm_state2 = 13'd2;
parameter    ap_ST_fsm_state3 = 13'd4;
parameter    ap_ST_fsm_state4 = 13'd8;
parameter    ap_ST_fsm_state5 = 13'd16;
parameter    ap_ST_fsm_state6 = 13'd32;
parameter    ap_ST_fsm_state7 = 13'd64;
parameter    ap_ST_fsm_state8 = 13'd128;
parameter    ap_ST_fsm_state9 = 13'd256;
parameter    ap_ST_fsm_state10 = 13'd512;
parameter    ap_ST_fsm_state11 = 13'd1024;
parameter    ap_ST_fsm_state12 = 13'd2048;
parameter    ap_ST_fsm_state13 = 13'd4096;

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
(* fsm_encoding = "none" *) reg   [12:0] ap_CS_fsm;
wire    ap_CS_fsm_state1;
reg    Input_1_V_TDATA_blk_n;
wire    ap_CS_fsm_state2;
wire    ap_CS_fsm_state3;
wire    ap_CS_fsm_state4;
wire    ap_CS_fsm_state5;
wire    ap_CS_fsm_state6;
wire   [7:0] triangle_3d_x0_V_fu_160_p1;
reg   [7:0] triangle_3d_x0_V_reg_346;
wire   [7:0] grp_fu_130_p4;
reg   [7:0] triangle_3d_y0_V_reg_351;
reg   [7:0] triangle_3d_x1_V_reg_356;
wire   [7:0] triangle_3d_y1_V_fu_174_p1;
reg   [7:0] triangle_3d_y1_V_reg_366;
wire   [7:0] grp_fu_140_p4;
reg   [7:0] triangle_3d_x2_V_reg_371;
reg   [7:0] triangle_3d_y2_V_reg_376;
reg   [6:0] tmp_reg_391;
wire   [7:0] triangle_3d_x0_V_1_fu_212_p1;
reg   [7:0] triangle_3d_x0_V_1_reg_396;
reg   [7:0] triangle_3d_y0_V_1_reg_401;
reg   [7:0] triangle_3d_x1_V_1_reg_406;
reg   [6:0] tmp_1_reg_416;
wire   [7:0] triangle_3d_y1_V_1_fu_236_p1;
reg   [7:0] triangle_3d_y1_V_1_reg_421;
reg   [7:0] triangle_3d_x2_V_1_reg_426;
reg   [7:0] triangle_3d_y2_V_1_reg_431;
reg   [6:0] tmp_2_reg_441;
wire   [7:0] triangle_2ds_1_z_V_fu_289_p2;
reg   [7:0] triangle_2ds_1_z_V_reg_451;
wire    ap_CS_fsm_state7;
reg   [6:0] tmp_6_reg_456;
reg   [6:0] tmp_7_reg_461;
wire    ap_CS_fsm_state8;
reg   [6:0] tmp_8_reg_466;
wire    ap_CS_fsm_state9;
wire   [7:0] triangle_2ds_2_z_V_fu_340_p2;
reg   [7:0] triangle_2ds_2_z_V_reg_471;
wire    ap_CS_fsm_state10;
wire    grp_rasterization1_odd_m_fu_80_ap_start;
wire    grp_rasterization1_odd_m_fu_80_ap_done;
wire    grp_rasterization1_odd_m_fu_80_ap_idle;
wire    grp_rasterization1_odd_m_fu_80_ap_ready;
wire   [31:0] grp_rasterization1_odd_m_fu_80_Output_1_V_TDATA;
wire    grp_rasterization1_odd_m_fu_80_Output_1_V_TVALID;
wire    grp_rasterization1_odd_m_fu_80_Output_1_V_TREADY;
wire    grp_rasterization1_even_m_fu_105_ap_start;
wire    grp_rasterization1_even_m_fu_105_ap_done;
wire    grp_rasterization1_even_m_fu_105_ap_idle;
wire    grp_rasterization1_even_m_fu_105_ap_ready;
wire   [31:0] grp_rasterization1_even_m_fu_105_Output_2_V_TDATA;
wire    grp_rasterization1_even_m_fu_105_Output_2_V_TVALID;
wire    grp_rasterization1_even_m_fu_105_Output_2_V_TREADY;
reg    grp_rasterization1_odd_m_fu_80_ap_start_reg;
wire    ap_CS_fsm_state11;
wire    ap_CS_fsm_state12;
reg    ap_block_state12_on_subcall_done;
reg    grp_rasterization1_even_m_fu_105_ap_start_reg;
reg    ap_block_state1;
wire   [7:0] grp_fu_168_p0;
wire   [9:0] grp_fu_168_p1;
wire   [7:0] grp_fu_182_p0;
wire   [9:0] grp_fu_182_p1;
wire   [7:0] triangle_3d_z2_V_fu_188_p1;
wire   [7:0] grp_fu_196_p0;
wire   [9:0] grp_fu_196_p1;
wire   [16:0] grp_fu_168_p2;
wire   [7:0] grp_fu_220_p0;
wire   [9:0] grp_fu_220_p1;
wire   [16:0] grp_fu_182_p2;
wire   [7:0] grp_fu_244_p0;
wire   [9:0] grp_fu_244_p1;
wire   [16:0] grp_fu_196_p2;
wire   [7:0] triangle_3d_z2_V_1_fu_260_p1;
wire   [7:0] grp_fu_268_p0;
wire   [9:0] grp_fu_268_p1;
wire   [7:0] zext_ln1364_1_fu_274_p1;
wire   [7:0] zext_ln1364_5_fu_280_p1;
wire   [7:0] add_ln213_fu_283_p2;
wire   [7:0] zext_ln1364_3_fu_277_p1;
wire   [16:0] grp_fu_220_p2;
wire   [16:0] grp_fu_244_p2;
wire   [16:0] grp_fu_268_p2;
wire   [7:0] zext_ln1364_7_fu_325_p1;
wire   [7:0] zext_ln1364_11_fu_331_p1;
wire   [7:0] add_ln213_2_fu_334_p2;
wire   [7:0] zext_ln1364_9_fu_328_p1;
reg    grp_fu_168_ce;
reg    grp_fu_182_ce;
reg    grp_fu_196_ce;
reg    grp_fu_220_ce;
reg    grp_fu_244_ce;
reg    grp_fu_268_ce;
wire    ap_CS_fsm_state13;
wire    regslice_both_Output_1_V_U_apdone_blk;
wire    regslice_both_Output_2_V_U_apdone_blk;
reg    ap_block_state13;
reg   [12:0] ap_NS_fsm;
wire    regslice_both_Input_1_V_U_apdone_blk;
wire   [31:0] Input_1_V_TDATA_int_regslice;
wire    Input_1_V_TVALID_int_regslice;
reg    Input_1_V_TREADY_int_regslice;
wire    regslice_both_Input_1_V_U_ack_in;
wire    Output_1_V_TREADY_int_regslice;
wire    regslice_both_Output_1_V_U_vld_out;
wire    Output_2_V_TREADY_int_regslice;
wire    regslice_both_Output_2_V_U_vld_out;
wire   [16:0] grp_fu_168_p00;
wire   [16:0] grp_fu_182_p00;
wire   [16:0] grp_fu_196_p00;
wire   [16:0] grp_fu_220_p00;
wire   [16:0] grp_fu_244_p00;
wire   [16:0] grp_fu_268_p00;
wire    ap_ce_reg;

// power-on initialization
initial begin
#0 ap_CS_fsm = 13'd1;
#0 grp_rasterization1_odd_m_fu_80_ap_start_reg = 1'b0;
#0 grp_rasterization1_even_m_fu_105_ap_start_reg = 1'b0;
end

data_redir_m_rasterization1_odd_m grp_rasterization1_odd_m_fu_80(
    .ap_clk(ap_clk),
    .ap_rst(ap_rst_n_inv),
    .ap_start(grp_rasterization1_odd_m_fu_80_ap_start),
    .ap_done(grp_rasterization1_odd_m_fu_80_ap_done),
    .ap_idle(grp_rasterization1_odd_m_fu_80_ap_idle),
    .ap_ready(grp_rasterization1_odd_m_fu_80_ap_ready),
    .Output_1_V_TDATA(grp_rasterization1_odd_m_fu_80_Output_1_V_TDATA),
    .Output_1_V_TVALID(grp_rasterization1_odd_m_fu_80_Output_1_V_TVALID),
    .Output_1_V_TREADY(grp_rasterization1_odd_m_fu_80_Output_1_V_TREADY),
    .triangle_2d_x0(triangle_3d_x0_V_reg_346),
    .triangle_2d_y0(triangle_3d_y0_V_reg_351),
    .triangle_2d_x1(triangle_3d_x1_V_reg_356),
    .triangle_2d_y1(triangle_3d_y1_V_reg_366),
    .triangle_2d_x2(triangle_3d_x2_V_reg_371),
    .triangle_2d_y2(triangle_3d_y2_V_reg_376),
    .triangle_2d_z(triangle_2ds_1_z_V_reg_451)
);

data_redir_m_rasterization1_even_m grp_rasterization1_even_m_fu_105(
    .ap_clk(ap_clk),
    .ap_rst(ap_rst_n_inv),
    .ap_start(grp_rasterization1_even_m_fu_105_ap_start),
    .ap_done(grp_rasterization1_even_m_fu_105_ap_done),
    .ap_idle(grp_rasterization1_even_m_fu_105_ap_idle),
    .ap_ready(grp_rasterization1_even_m_fu_105_ap_ready),
    .Output_2_V_TDATA(grp_rasterization1_even_m_fu_105_Output_2_V_TDATA),
    .Output_2_V_TVALID(grp_rasterization1_even_m_fu_105_Output_2_V_TVALID),
    .Output_2_V_TREADY(grp_rasterization1_even_m_fu_105_Output_2_V_TREADY),
    .triangle_2d_x0(triangle_3d_x0_V_1_reg_396),
    .triangle_2d_y0(triangle_3d_y0_V_1_reg_401),
    .triangle_2d_x1(triangle_3d_x1_V_1_reg_406),
    .triangle_2d_y1(triangle_3d_y1_V_1_reg_421),
    .triangle_2d_x2(triangle_3d_x2_V_1_reg_426),
    .triangle_2d_y2(triangle_3d_y2_V_1_reg_431),
    .triangle_2d_z(triangle_2ds_2_z_V_reg_471)
);

data_redir_m_mul_8ns_10ns_17_4_1 #(
    .ID( 1 ),
    .NUM_STAGE( 4 ),
    .din0_WIDTH( 8 ),
    .din1_WIDTH( 10 ),
    .dout_WIDTH( 17 ))
mul_8ns_10ns_17_4_1_U25(
    .clk(ap_clk),
    .reset(ap_rst_n_inv),
    .din0(grp_fu_168_p0),
    .din1(grp_fu_168_p1),
    .ce(grp_fu_168_ce),
    .dout(grp_fu_168_p2)
);

data_redir_m_mul_8ns_10ns_17_4_1 #(
    .ID( 1 ),
    .NUM_STAGE( 4 ),
    .din0_WIDTH( 8 ),
    .din1_WIDTH( 10 ),
    .dout_WIDTH( 17 ))
mul_8ns_10ns_17_4_1_U26(
    .clk(ap_clk),
    .reset(ap_rst_n_inv),
    .din0(grp_fu_182_p0),
    .din1(grp_fu_182_p1),
    .ce(grp_fu_182_ce),
    .dout(grp_fu_182_p2)
);

data_redir_m_mul_8ns_10ns_17_4_1 #(
    .ID( 1 ),
    .NUM_STAGE( 4 ),
    .din0_WIDTH( 8 ),
    .din1_WIDTH( 10 ),
    .dout_WIDTH( 17 ))
mul_8ns_10ns_17_4_1_U27(
    .clk(ap_clk),
    .reset(ap_rst_n_inv),
    .din0(grp_fu_196_p0),
    .din1(grp_fu_196_p1),
    .ce(grp_fu_196_ce),
    .dout(grp_fu_196_p2)
);

data_redir_m_mul_8ns_10ns_17_4_1 #(
    .ID( 1 ),
    .NUM_STAGE( 4 ),
    .din0_WIDTH( 8 ),
    .din1_WIDTH( 10 ),
    .dout_WIDTH( 17 ))
mul_8ns_10ns_17_4_1_U28(
    .clk(ap_clk),
    .reset(ap_rst_n_inv),
    .din0(grp_fu_220_p0),
    .din1(grp_fu_220_p1),
    .ce(grp_fu_220_ce),
    .dout(grp_fu_220_p2)
);

data_redir_m_mul_8ns_10ns_17_4_1 #(
    .ID( 1 ),
    .NUM_STAGE( 4 ),
    .din0_WIDTH( 8 ),
    .din1_WIDTH( 10 ),
    .dout_WIDTH( 17 ))
mul_8ns_10ns_17_4_1_U29(
    .clk(ap_clk),
    .reset(ap_rst_n_inv),
    .din0(grp_fu_244_p0),
    .din1(grp_fu_244_p1),
    .ce(grp_fu_244_ce),
    .dout(grp_fu_244_p2)
);

data_redir_m_mul_8ns_10ns_17_4_1 #(
    .ID( 1 ),
    .NUM_STAGE( 4 ),
    .din0_WIDTH( 8 ),
    .din1_WIDTH( 10 ),
    .dout_WIDTH( 17 ))
mul_8ns_10ns_17_4_1_U30(
    .clk(ap_clk),
    .reset(ap_rst_n_inv),
    .din0(grp_fu_268_p0),
    .din1(grp_fu_268_p1),
    .ce(grp_fu_268_ce),
    .dout(grp_fu_268_p2)
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
    .data_in(grp_rasterization1_odd_m_fu_80_Output_1_V_TDATA),
    .vld_in(grp_rasterization1_odd_m_fu_80_Output_1_V_TVALID),
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
    .data_in(grp_rasterization1_even_m_fu_105_Output_2_V_TDATA),
    .vld_in(grp_rasterization1_even_m_fu_105_Output_2_V_TVALID),
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
        grp_rasterization1_even_m_fu_105_ap_start_reg <= 1'b0;
    end else begin
        if ((1'b1 == ap_CS_fsm_state11)) begin
            grp_rasterization1_even_m_fu_105_ap_start_reg <= 1'b1;
        end else if ((grp_rasterization1_even_m_fu_105_ap_ready == 1'b1)) begin
            grp_rasterization1_even_m_fu_105_ap_start_reg <= 1'b0;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst_n_inv == 1'b1) begin
        grp_rasterization1_odd_m_fu_80_ap_start_reg <= 1'b0;
    end else begin
        if ((1'b1 == ap_CS_fsm_state11)) begin
            grp_rasterization1_odd_m_fu_80_ap_start_reg <= 1'b1;
        end else if ((grp_rasterization1_odd_m_fu_80_ap_ready == 1'b1)) begin
            grp_rasterization1_odd_m_fu_80_ap_start_reg <= 1'b0;
        end
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state5)) begin
        tmp_1_reg_416 <= {{grp_fu_182_p2[16:10]}};
        triangle_3d_x2_V_1_reg_426 <= {{Input_1_V_TDATA_int_regslice[23:16]}};
        triangle_3d_y1_V_1_reg_421 <= triangle_3d_y1_V_1_fu_236_p1;
        triangle_3d_y2_V_1_reg_431 <= {{Input_1_V_TDATA_int_regslice[31:24]}};
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state6)) begin
        tmp_2_reg_441 <= {{grp_fu_196_p2[16:10]}};
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state7)) begin
        tmp_6_reg_456 <= {{grp_fu_220_p2[16:10]}};
        triangle_2ds_1_z_V_reg_451 <= triangle_2ds_1_z_V_fu_289_p2;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state8)) begin
        tmp_7_reg_461 <= {{grp_fu_244_p2[16:10]}};
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state9)) begin
        tmp_8_reg_466 <= {{grp_fu_268_p2[16:10]}};
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state4)) begin
        tmp_reg_391 <= {{grp_fu_168_p2[16:10]}};
        triangle_3d_x0_V_1_reg_396 <= triangle_3d_x0_V_1_fu_212_p1;
        triangle_3d_x1_V_1_reg_406 <= {{Input_1_V_TDATA_int_regslice[31:24]}};
        triangle_3d_y0_V_1_reg_401 <= {{Input_1_V_TDATA_int_regslice[15:8]}};
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state10)) begin
        triangle_2ds_2_z_V_reg_471 <= triangle_2ds_2_z_V_fu_340_p2;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state1)) begin
        triangle_3d_x0_V_reg_346 <= triangle_3d_x0_V_fu_160_p1;
        triangle_3d_x1_V_reg_356 <= {{Input_1_V_TDATA_int_regslice[31:24]}};
        triangle_3d_y0_V_reg_351 <= {{Input_1_V_TDATA_int_regslice[15:8]}};
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state2)) begin
        triangle_3d_x2_V_reg_371 <= {{Input_1_V_TDATA_int_regslice[23:16]}};
        triangle_3d_y1_V_reg_366 <= triangle_3d_y1_V_fu_174_p1;
        triangle_3d_y2_V_reg_376 <= {{Input_1_V_TDATA_int_regslice[31:24]}};
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state6) | (1'b1 == ap_CS_fsm_state5) | (1'b1 == ap_CS_fsm_state4) | (1'b1 == ap_CS_fsm_state3) | (1'b1 == ap_CS_fsm_state2) | ((ap_start == 1'b1) & (1'b1 == ap_CS_fsm_state1)))) begin
        Input_1_V_TDATA_blk_n = Input_1_V_TVALID_int_regslice;
    end else begin
        Input_1_V_TDATA_blk_n = 1'b1;
    end
end

always @ (*) begin
    if ((((1'b1 == ap_CS_fsm_state6) & (1'b1 == Input_1_V_TVALID_int_regslice)) | ((1'b1 == ap_CS_fsm_state5) & (1'b1 == Input_1_V_TVALID_int_regslice)) | ((1'b1 == ap_CS_fsm_state4) & (1'b1 == Input_1_V_TVALID_int_regslice)) | ((1'b1 == ap_CS_fsm_state3) & (1'b1 == Input_1_V_TVALID_int_regslice)) | ((1'b1 == ap_CS_fsm_state2) & (1'b1 == Input_1_V_TVALID_int_regslice)) | (~((1'b0 == Input_1_V_TVALID_int_regslice) | (ap_start == 1'b0)) & (1'b1 == ap_CS_fsm_state1)))) begin
        Input_1_V_TREADY_int_regslice = 1'b1;
    end else begin
        Input_1_V_TREADY_int_regslice = 1'b0;
    end
end

always @ (*) begin
    if ((~((regslice_both_Output_2_V_U_apdone_blk == 1'b1) | (regslice_both_Output_1_V_U_apdone_blk == 1'b1)) & (1'b1 == ap_CS_fsm_state13))) begin
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
    if ((~((regslice_both_Output_2_V_U_apdone_blk == 1'b1) | (regslice_both_Output_1_V_U_apdone_blk == 1'b1)) & (1'b1 == ap_CS_fsm_state13))) begin
        ap_ready = 1'b1;
    end else begin
        ap_ready = 1'b0;
    end
end

always @ (*) begin
    if ((((1'b1 == ap_CS_fsm_state4) & (1'b1 == Input_1_V_TVALID_int_regslice)) | ((1'b1 == ap_CS_fsm_state3) & (1'b1 == Input_1_V_TVALID_int_regslice)) | ((1'b1 == ap_CS_fsm_state2) & (1'b1 == Input_1_V_TVALID_int_regslice)) | (~((1'b0 == Input_1_V_TVALID_int_regslice) | (ap_start == 1'b0)) & (1'b1 == ap_CS_fsm_state1)))) begin
        grp_fu_168_ce = 1'b1;
    end else begin
        grp_fu_168_ce = 1'b0;
    end
end

always @ (*) begin
    if ((((1'b1 == ap_CS_fsm_state5) & (1'b1 == Input_1_V_TVALID_int_regslice)) | ((1'b1 == ap_CS_fsm_state4) & (1'b1 == Input_1_V_TVALID_int_regslice)) | ((1'b1 == ap_CS_fsm_state3) & (1'b1 == Input_1_V_TVALID_int_regslice)) | ((1'b1 == ap_CS_fsm_state2) & (1'b1 == Input_1_V_TVALID_int_regslice)))) begin
        grp_fu_182_ce = 1'b1;
    end else begin
        grp_fu_182_ce = 1'b0;
    end
end

always @ (*) begin
    if ((((1'b1 == ap_CS_fsm_state6) & (1'b1 == Input_1_V_TVALID_int_regslice)) | ((1'b1 == ap_CS_fsm_state5) & (1'b1 == Input_1_V_TVALID_int_regslice)) | ((1'b1 == ap_CS_fsm_state4) & (1'b1 == Input_1_V_TVALID_int_regslice)) | ((1'b1 == ap_CS_fsm_state3) & (1'b1 == Input_1_V_TVALID_int_regslice)))) begin
        grp_fu_196_ce = 1'b1;
    end else begin
        grp_fu_196_ce = 1'b0;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state7) | ((1'b1 == ap_CS_fsm_state6) & (1'b1 == Input_1_V_TVALID_int_regslice)) | ((1'b1 == ap_CS_fsm_state5) & (1'b1 == Input_1_V_TVALID_int_regslice)) | ((1'b1 == ap_CS_fsm_state4) & (1'b1 == Input_1_V_TVALID_int_regslice)))) begin
        grp_fu_220_ce = 1'b1;
    end else begin
        grp_fu_220_ce = 1'b0;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state8) | (1'b1 == ap_CS_fsm_state7) | ((1'b1 == ap_CS_fsm_state6) & (1'b1 == Input_1_V_TVALID_int_regslice)) | ((1'b1 == ap_CS_fsm_state5) & (1'b1 == Input_1_V_TVALID_int_regslice)))) begin
        grp_fu_244_ce = 1'b1;
    end else begin
        grp_fu_244_ce = 1'b0;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state9) | (1'b1 == ap_CS_fsm_state8) | (1'b1 == ap_CS_fsm_state7) | ((1'b1 == ap_CS_fsm_state6) & (1'b1 == Input_1_V_TVALID_int_regslice)))) begin
        grp_fu_268_ce = 1'b1;
    end else begin
        grp_fu_268_ce = 1'b0;
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
            if (((1'b1 == ap_CS_fsm_state4) & (1'b1 == Input_1_V_TVALID_int_regslice))) begin
                ap_NS_fsm = ap_ST_fsm_state5;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state4;
            end
        end
        ap_ST_fsm_state5 : begin
            if (((1'b1 == ap_CS_fsm_state5) & (1'b1 == Input_1_V_TVALID_int_regslice))) begin
                ap_NS_fsm = ap_ST_fsm_state6;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state5;
            end
        end
        ap_ST_fsm_state6 : begin
            if (((1'b1 == ap_CS_fsm_state6) & (1'b1 == Input_1_V_TVALID_int_regslice))) begin
                ap_NS_fsm = ap_ST_fsm_state7;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state6;
            end
        end
        ap_ST_fsm_state7 : begin
            ap_NS_fsm = ap_ST_fsm_state8;
        end
        ap_ST_fsm_state8 : begin
            ap_NS_fsm = ap_ST_fsm_state9;
        end
        ap_ST_fsm_state9 : begin
            ap_NS_fsm = ap_ST_fsm_state10;
        end
        ap_ST_fsm_state10 : begin
            ap_NS_fsm = ap_ST_fsm_state11;
        end
        ap_ST_fsm_state11 : begin
            ap_NS_fsm = ap_ST_fsm_state12;
        end
        ap_ST_fsm_state12 : begin
            if (((1'b1 == ap_CS_fsm_state12) & (1'b0 == ap_block_state12_on_subcall_done))) begin
                ap_NS_fsm = ap_ST_fsm_state13;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state12;
            end
        end
        ap_ST_fsm_state13 : begin
            if ((~((regslice_both_Output_2_V_U_apdone_blk == 1'b1) | (regslice_both_Output_1_V_U_apdone_blk == 1'b1)) & (1'b1 == ap_CS_fsm_state13))) begin
                ap_NS_fsm = ap_ST_fsm_state1;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state13;
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

assign add_ln213_2_fu_334_p2 = (zext_ln1364_7_fu_325_p1 + zext_ln1364_11_fu_331_p1);

assign add_ln213_fu_283_p2 = (zext_ln1364_1_fu_274_p1 + zext_ln1364_5_fu_280_p1);

assign ap_CS_fsm_state1 = ap_CS_fsm[32'd0];

assign ap_CS_fsm_state10 = ap_CS_fsm[32'd9];

assign ap_CS_fsm_state11 = ap_CS_fsm[32'd10];

assign ap_CS_fsm_state12 = ap_CS_fsm[32'd11];

assign ap_CS_fsm_state13 = ap_CS_fsm[32'd12];

assign ap_CS_fsm_state2 = ap_CS_fsm[32'd1];

assign ap_CS_fsm_state3 = ap_CS_fsm[32'd2];

assign ap_CS_fsm_state4 = ap_CS_fsm[32'd3];

assign ap_CS_fsm_state5 = ap_CS_fsm[32'd4];

assign ap_CS_fsm_state6 = ap_CS_fsm[32'd5];

assign ap_CS_fsm_state7 = ap_CS_fsm[32'd6];

assign ap_CS_fsm_state8 = ap_CS_fsm[32'd7];

assign ap_CS_fsm_state9 = ap_CS_fsm[32'd8];

always @ (*) begin
    ap_block_state1 = ((1'b0 == Input_1_V_TVALID_int_regslice) | (ap_start == 1'b0));
end

always @ (*) begin
    ap_block_state12_on_subcall_done = ((grp_rasterization1_even_m_fu_105_ap_done == 1'b0) | (grp_rasterization1_odd_m_fu_80_ap_done == 1'b0));
end

always @ (*) begin
    ap_block_state13 = ((regslice_both_Output_2_V_U_apdone_blk == 1'b1) | (regslice_both_Output_1_V_U_apdone_blk == 1'b1));
end

always @ (*) begin
    ap_rst_n_inv = ~ap_rst_n;
end

assign grp_fu_130_p4 = {{Input_1_V_TDATA_int_regslice[15:8]}};

assign grp_fu_140_p4 = {{Input_1_V_TDATA_int_regslice[23:16]}};

assign grp_fu_168_p0 = grp_fu_168_p00;

assign grp_fu_168_p00 = grp_fu_140_p4;

assign grp_fu_168_p1 = 17'd342;

assign grp_fu_182_p0 = grp_fu_182_p00;

assign grp_fu_182_p00 = grp_fu_130_p4;

assign grp_fu_182_p1 = 17'd342;

assign grp_fu_196_p0 = grp_fu_196_p00;

assign grp_fu_196_p00 = triangle_3d_z2_V_fu_188_p1;

assign grp_fu_196_p1 = 17'd342;

assign grp_fu_220_p0 = grp_fu_220_p00;

assign grp_fu_220_p00 = grp_fu_140_p4;

assign grp_fu_220_p1 = 17'd342;

assign grp_fu_244_p0 = grp_fu_244_p00;

assign grp_fu_244_p00 = grp_fu_130_p4;

assign grp_fu_244_p1 = 17'd342;

assign grp_fu_268_p0 = grp_fu_268_p00;

assign grp_fu_268_p00 = triangle_3d_z2_V_1_fu_260_p1;

assign grp_fu_268_p1 = 17'd342;

assign grp_rasterization1_even_m_fu_105_Output_2_V_TREADY = (ap_CS_fsm_state12 & Output_2_V_TREADY_int_regslice);

assign grp_rasterization1_even_m_fu_105_ap_start = grp_rasterization1_even_m_fu_105_ap_start_reg;

assign grp_rasterization1_odd_m_fu_80_Output_1_V_TREADY = (ap_CS_fsm_state12 & Output_1_V_TREADY_int_regslice);

assign grp_rasterization1_odd_m_fu_80_ap_start = grp_rasterization1_odd_m_fu_80_ap_start_reg;

assign triangle_2ds_1_z_V_fu_289_p2 = (add_ln213_fu_283_p2 + zext_ln1364_3_fu_277_p1);

assign triangle_2ds_2_z_V_fu_340_p2 = (add_ln213_2_fu_334_p2 + zext_ln1364_9_fu_328_p1);

assign triangle_3d_x0_V_1_fu_212_p1 = Input_1_V_TDATA_int_regslice[7:0];

assign triangle_3d_x0_V_fu_160_p1 = Input_1_V_TDATA_int_regslice[7:0];

assign triangle_3d_y1_V_1_fu_236_p1 = Input_1_V_TDATA_int_regslice[7:0];

assign triangle_3d_y1_V_fu_174_p1 = Input_1_V_TDATA_int_regslice[7:0];

assign triangle_3d_z2_V_1_fu_260_p1 = Input_1_V_TDATA_int_regslice[7:0];

assign triangle_3d_z2_V_fu_188_p1 = Input_1_V_TDATA_int_regslice[7:0];

assign zext_ln1364_11_fu_331_p1 = tmp_8_reg_466;

assign zext_ln1364_1_fu_274_p1 = tmp_reg_391;

assign zext_ln1364_3_fu_277_p1 = tmp_1_reg_416;

assign zext_ln1364_5_fu_280_p1 = tmp_2_reg_441;

assign zext_ln1364_7_fu_325_p1 = tmp_6_reg_456;

assign zext_ln1364_9_fu_328_p1 = tmp_7_reg_461;

endmodule //data_redir_m
