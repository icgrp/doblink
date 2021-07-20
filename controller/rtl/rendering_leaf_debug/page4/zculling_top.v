// ==============================================================
// RTL generated by Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Version: 2020.2
// Copyright (C) Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

`timescale 1 ns / 1 ps 

(* CORE_GENERATION_INFO="zculling_top_zculling_top,hls_ip_2020_2,{HLS_INPUT_TYPE=cxx,HLS_INPUT_FLOAT=0,HLS_INPUT_FIXED=0,HLS_INPUT_PART=xc7a200t-sbg484-1,HLS_INPUT_CLOCK=4.000000,HLS_INPUT_ARCH=others,HLS_SYN_CLOCK=4.845000,HLS_SYN_LAT=-1,HLS_SYN_TPT=none,HLS_SYN_MEM=32,HLS_SYN_DSP=0,HLS_SYN_FF=221,HLS_SYN_LUT=418,HLS_VERSION=2020_2}" *)

module zculling_top (
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
        Output_1_V_TREADY
);

parameter    ap_ST_fsm_state1 = 9'd1;
parameter    ap_ST_fsm_pp0_stage0 = 9'd2;
parameter    ap_ST_fsm_state4 = 9'd4;
parameter    ap_ST_fsm_pp1_stage0 = 9'd8;
parameter    ap_ST_fsm_pp1_stage1 = 9'd16;
parameter    ap_ST_fsm_pp1_stage2 = 9'd32;
parameter    ap_ST_fsm_state9 = 9'd64;
parameter    ap_ST_fsm_state10 = 9'd128;
parameter    ap_ST_fsm_state11 = 9'd256;

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

reg ap_done;
reg ap_idle;
reg ap_ready;

 reg    ap_rst_n_inv;
(* fsm_encoding = "none" *) reg   [8:0] ap_CS_fsm;
wire    ap_CS_fsm_state1;
reg   [15:0] counter_V;
reg   [15:0] z_buffer_V_address0;
reg    z_buffer_V_ce0;
reg    z_buffer_V_we0;
reg   [7:0] z_buffer_V_d0;
wire   [7:0] z_buffer_V_q0;
reg    Input_1_V_TDATA_blk_n;
wire    ap_CS_fsm_pp1_stage1;
reg    ap_enable_reg_pp1_iter0;
wire    ap_block_pp1_stage1;
reg   [0:0] icmp_ln43_reg_350;
reg    Output_1_V_TDATA_blk_n;
wire    ap_CS_fsm_pp1_stage2;
wire    ap_block_pp1_stage2;
wire    ap_CS_fsm_pp1_stage0;
reg    ap_enable_reg_pp1_iter1;
wire    ap_block_pp1_stage0;
reg   [16:0] indvar_flatten_reg_114;
reg   [8:0] i_V_reg_125;
reg   [8:0] j_V_reg_136;
reg   [15:0] n_V_reg_147;
reg   [31:0] tmp_V_reg_299;
wire   [0:0] icmp_ln870_fu_162_p2;
wire   [16:0] add_ln878_fu_168_p2;
wire    ap_CS_fsm_pp0_stage0;
reg    ap_enable_reg_pp0_iter0;
wire    ap_block_state2_pp0_stage0_iter0;
wire    ap_block_state3_pp0_stage0_iter1;
wire    ap_block_pp0_stage0_11001;
wire   [0:0] icmp_ln878_fu_174_p2;
reg   [0:0] icmp_ln878_reg_316;
wire   [8:0] select_ln28_fu_192_p3;
reg   [8:0] select_ln28_reg_320;
wire   [8:0] select_ln28_1_fu_200_p3;
reg   [8:0] select_ln28_1_reg_325;
wire   [7:0] trunc_ln33_fu_208_p1;
reg   [7:0] trunc_ln33_reg_330;
wire   [8:0] j_V_1_fu_212_p2;
wire   [15:0] empty_9_fu_239_p1;
reg   [15:0] empty_9_reg_340;
wire    ap_CS_fsm_state4;
wire   [15:0] n_V_1_fu_242_p2;
reg   [15:0] n_V_1_reg_345;
wire    ap_block_state5_pp1_stage0_iter0;
reg    ap_block_state8_pp1_stage0_iter1;
reg    ap_block_pp1_stage0_11001;
wire   [0:0] icmp_ln43_fu_248_p2;
reg   [7:0] fragment_z_V_reg_354;
reg    ap_block_state6_pp1_stage1_iter0;
reg    ap_block_pp1_stage1_11001;
reg   [15:0] z_buffer_V_addr_1_reg_360;
wire   [15:0] add_ln691_fu_277_p2;
reg   [15:0] add_ln691_reg_368;
wire    ap_CS_fsm_state9;
wire   [0:0] icmp_ln870_1_fu_282_p2;
reg   [0:0] icmp_ln870_1_reg_374;
wire    ap_CS_fsm_state10;
reg    ap_block_state1;
wire    ap_block_pp0_stage0_subdone;
reg    ap_condition_pp0_exit_iter0_state2;
reg    ap_enable_reg_pp0_iter1;
reg    ap_block_pp1_stage0_subdone;
reg    ap_condition_pp1_exit_iter0_state5;
reg    ap_block_state7_pp1_stage2_iter0;
reg    ap_block_state7_io;
reg    ap_block_pp1_stage2_subdone;
reg   [8:0] ap_phi_mux_i_V_phi_fu_129_p4;
wire    ap_block_pp0_stage0;
reg   [15:0] ap_phi_mux_n_V_phi_fu_151_p4;
wire   [63:0] zext_ln33_1_fu_234_p1;
wire   [63:0] zext_ln878_fu_267_p1;
wire   [15:0] select_ln79_fu_287_p3;
wire    ap_CS_fsm_state11;
wire    regslice_both_Output_1_V_U_apdone_blk;
reg    ap_block_pp1_stage2_01001;
reg    ap_block_pp1_stage2_11001;
wire   [0:0] icmp_ln878_2_fu_272_p2;
wire   [0:0] icmp_ln878_1_fu_186_p2;
wire   [8:0] i_V_2_fu_180_p2;
wire   [15:0] tmp_1_cast_fu_218_p3;
wire   [15:0] zext_ln33_fu_225_p1;
wire   [15:0] add_ln33_fu_228_p2;
wire   [15:0] trunc_ln878_fu_263_p1;
reg   [8:0] ap_NS_fsm;
reg    ap_block_pp1_stage1_subdone;
reg    ap_idle_pp0;
wire    ap_enable_pp0;
reg    ap_idle_pp1;
wire    ap_enable_pp1;
wire    regslice_both_Input_1_V_U_apdone_blk;
wire   [31:0] Input_1_V_TDATA_int_regslice;
wire    Input_1_V_TVALID_int_regslice;
reg    Input_1_V_TREADY_int_regslice;
wire    regslice_both_Input_1_V_U_ack_in;
reg    Output_1_V_TVALID_int_regslice;
wire    Output_1_V_TREADY_int_regslice;
wire    regslice_both_Output_1_V_U_vld_out;
wire    ap_ce_reg;

// power-on initialization
initial begin
#0 ap_CS_fsm = 9'd1;
#0 counter_V = 16'd0;
#0 ap_enable_reg_pp1_iter0 = 1'b0;
#0 ap_enable_reg_pp1_iter1 = 1'b0;
#0 ap_enable_reg_pp0_iter0 = 1'b0;
#0 ap_enable_reg_pp0_iter1 = 1'b0;
end

zculling_top_z_buffer_V #(
    .DataWidth( 8 ),
    .AddressRange( 65536 ),
    .AddressWidth( 16 ))
z_buffer_V_U(
    .clk(ap_clk),
    .reset(ap_rst_n_inv),
    .address0(z_buffer_V_address0),
    .ce0(z_buffer_V_ce0),
    .we0(z_buffer_V_we0),
    .d0(z_buffer_V_d0),
    .q0(z_buffer_V_q0)
);

zculling_top_regslice_both #(
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

zculling_top_regslice_both #(
    .DataWidth( 32 ))
regslice_both_Output_1_V_U(
    .ap_clk(ap_clk),
    .ap_rst(ap_rst_n_inv),
    .data_in(32'd0),
    .vld_in(Output_1_V_TVALID_int_regslice),
    .ack_in(Output_1_V_TREADY_int_regslice),
    .data_out(Output_1_V_TDATA),
    .vld_out(regslice_both_Output_1_V_U_vld_out),
    .ack_out(Output_1_V_TREADY),
    .apdone_blk(regslice_both_Output_1_V_U_apdone_blk)
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
        ap_enable_reg_pp0_iter0 <= 1'b0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_subdone) & (1'b1 == ap_condition_pp0_exit_iter0_state2) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            ap_enable_reg_pp0_iter0 <= 1'b0;
        end else if ((~((1'b0 == Input_1_V_TVALID_int_regslice) | (ap_start == 1'b0)) & (1'b1 == ap_CS_fsm_state1) & (icmp_ln870_fu_162_p2 == 1'd1))) begin
            ap_enable_reg_pp0_iter0 <= 1'b1;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst_n_inv == 1'b1) begin
        ap_enable_reg_pp0_iter1 <= 1'b0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_subdone) & (1'b1 == ap_condition_pp0_exit_iter0_state2))) begin
            ap_enable_reg_pp0_iter1 <= (1'b1 ^ ap_condition_pp0_exit_iter0_state2);
        end else if ((1'b0 == ap_block_pp0_stage0_subdone)) begin
            ap_enable_reg_pp0_iter1 <= ap_enable_reg_pp0_iter0;
        end else if ((~((1'b0 == Input_1_V_TVALID_int_regslice) | (ap_start == 1'b0)) & (1'b1 == ap_CS_fsm_state1) & (icmp_ln870_fu_162_p2 == 1'd1))) begin
            ap_enable_reg_pp0_iter1 <= 1'b0;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst_n_inv == 1'b1) begin
        ap_enable_reg_pp1_iter0 <= 1'b0;
    end else begin
        if (((1'b0 == ap_block_pp1_stage0_subdone) & (1'b1 == ap_CS_fsm_pp1_stage0) & (1'b1 == ap_condition_pp1_exit_iter0_state5))) begin
            ap_enable_reg_pp1_iter0 <= 1'b0;
        end else if ((1'b1 == ap_CS_fsm_state4)) begin
            ap_enable_reg_pp1_iter0 <= 1'b1;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst_n_inv == 1'b1) begin
        ap_enable_reg_pp1_iter1 <= 1'b0;
    end else begin
        if ((((1'b0 == ap_block_pp1_stage2_subdone) & (1'b1 == ap_CS_fsm_pp1_stage2)) | ((1'b0 == ap_block_pp1_stage0_subdone) & (ap_enable_reg_pp1_iter0 == 1'b0) & (1'b1 == ap_CS_fsm_pp1_stage0)))) begin
            ap_enable_reg_pp1_iter1 <= ap_enable_reg_pp1_iter0;
        end else if ((1'b1 == ap_CS_fsm_state4)) begin
            ap_enable_reg_pp1_iter1 <= 1'b0;
        end
    end
end

always @ (posedge ap_clk) begin
    if ((~((1'b0 == Input_1_V_TVALID_int_regslice) | (ap_start == 1'b0)) & (1'b1 == ap_CS_fsm_state1) & (icmp_ln870_fu_162_p2 == 1'd1))) begin
        i_V_reg_125 <= 9'd0;
    end else if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0) & (ap_enable_reg_pp0_iter1 == 1'b1) & (icmp_ln878_reg_316 == 1'd0))) begin
        i_V_reg_125 <= select_ln28_1_reg_325;
    end
end

always @ (posedge ap_clk) begin
    if ((~((1'b0 == Input_1_V_TVALID_int_regslice) | (ap_start == 1'b0)) & (1'b1 == ap_CS_fsm_state1) & (icmp_ln870_fu_162_p2 == 1'd1))) begin
        indvar_flatten_reg_114 <= 17'd0;
    end else if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0) & (icmp_ln878_fu_174_p2 == 1'd0) & (ap_enable_reg_pp0_iter0 == 1'b1))) begin
        indvar_flatten_reg_114 <= add_ln878_fu_168_p2;
    end
end

always @ (posedge ap_clk) begin
    if ((~((1'b0 == Input_1_V_TVALID_int_regslice) | (ap_start == 1'b0)) & (1'b1 == ap_CS_fsm_state1) & (icmp_ln870_fu_162_p2 == 1'd1))) begin
        j_V_reg_136 <= 9'd0;
    end else if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0) & (icmp_ln878_fu_174_p2 == 1'd0) & (ap_enable_reg_pp0_iter0 == 1'b1))) begin
        j_V_reg_136 <= j_V_1_fu_212_p2;
    end
end

always @ (posedge ap_clk) begin
    if (((ap_enable_reg_pp1_iter1 == 1'b1) & (icmp_ln43_reg_350 == 1'd0) & (1'b0 == ap_block_pp1_stage0_11001) & (1'b1 == ap_CS_fsm_pp1_stage0))) begin
        n_V_reg_147 <= n_V_1_reg_345;
    end else if ((1'b1 == ap_CS_fsm_state4)) begin
        n_V_reg_147 <= 16'd0;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state9)) begin
        add_ln691_reg_368 <= add_ln691_fu_277_p2;
    end
end

always @ (posedge ap_clk) begin
    if (((regslice_both_Output_1_V_U_apdone_blk == 1'b0) & (1'b1 == ap_CS_fsm_state11))) begin
        counter_V <= select_ln79_fu_287_p3;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state4)) begin
        empty_9_reg_340 <= empty_9_fu_239_p1;
    end
end

always @ (posedge ap_clk) begin
    if (((icmp_ln43_reg_350 == 1'd0) & (1'b0 == ap_block_pp1_stage1_11001) & (1'b1 == ap_CS_fsm_pp1_stage1))) begin
        fragment_z_V_reg_354 <= {{Input_1_V_TDATA_int_regslice[23:16]}};
        z_buffer_V_addr_1_reg_360 <= zext_ln878_fu_267_p1;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b0 == ap_block_pp1_stage0_11001) & (1'b1 == ap_CS_fsm_pp1_stage0))) begin
        icmp_ln43_reg_350 <= icmp_ln43_fu_248_p2;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state10)) begin
        icmp_ln870_1_reg_374 <= icmp_ln870_1_fu_282_p2;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
        icmp_ln878_reg_316 <= icmp_ln878_fu_174_p2;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b0 == ap_block_pp1_stage0_11001) & (ap_enable_reg_pp1_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp1_stage0))) begin
        n_V_1_reg_345 <= n_V_1_fu_242_p2;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0) & (icmp_ln878_fu_174_p2 == 1'd0) & (ap_enable_reg_pp0_iter0 == 1'b1))) begin
        select_ln28_1_reg_325 <= select_ln28_1_fu_200_p3;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0) & (icmp_ln878_fu_174_p2 == 1'd0))) begin
        select_ln28_reg_320 <= select_ln28_fu_192_p3;
        trunc_ln33_reg_330 <= trunc_ln33_fu_208_p1;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state1)) begin
        tmp_V_reg_299 <= Input_1_V_TDATA_int_regslice;
    end
end

always @ (*) begin
    if ((((icmp_ln43_reg_350 == 1'd0) & (1'b0 == ap_block_pp1_stage1) & (ap_enable_reg_pp1_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp1_stage1)) | ((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b1)))) begin
        Input_1_V_TDATA_blk_n = Input_1_V_TVALID_int_regslice;
    end else begin
        Input_1_V_TDATA_blk_n = 1'b1;
    end
end

always @ (*) begin
    if ((((icmp_ln43_reg_350 == 1'd0) & (1'b0 == ap_block_pp1_stage1_11001) & (ap_enable_reg_pp1_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp1_stage1)) | (~((1'b0 == Input_1_V_TVALID_int_regslice) | (ap_start == 1'b0)) & (1'b1 == ap_CS_fsm_state1)))) begin
        Input_1_V_TREADY_int_regslice = 1'b1;
    end else begin
        Input_1_V_TREADY_int_regslice = 1'b0;
    end
end

always @ (*) begin
    if ((((ap_enable_reg_pp1_iter1 == 1'b1) & (1'b0 == ap_block_pp1_stage0) & (1'b1 == ap_CS_fsm_pp1_stage0)) | ((icmp_ln43_reg_350 == 1'd0) & (1'b0 == ap_block_pp1_stage2) & (ap_enable_reg_pp1_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp1_stage2)))) begin
        Output_1_V_TDATA_blk_n = Output_1_V_TREADY_int_regslice;
    end else begin
        Output_1_V_TDATA_blk_n = 1'b1;
    end
end

always @ (*) begin
    if (((icmp_ln43_reg_350 == 1'd0) & (1'b0 == ap_block_pp1_stage2_11001) & (ap_enable_reg_pp1_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp1_stage2))) begin
        Output_1_V_TVALID_int_regslice = 1'b1;
    end else begin
        Output_1_V_TVALID_int_regslice = 1'b0;
    end
end

always @ (*) begin
    if ((icmp_ln878_fu_174_p2 == 1'd1)) begin
        ap_condition_pp0_exit_iter0_state2 = 1'b1;
    end else begin
        ap_condition_pp0_exit_iter0_state2 = 1'b0;
    end
end

always @ (*) begin
    if ((icmp_ln43_fu_248_p2 == 1'd1)) begin
        ap_condition_pp1_exit_iter0_state5 = 1'b1;
    end else begin
        ap_condition_pp1_exit_iter0_state5 = 1'b0;
    end
end

always @ (*) begin
    if (((regslice_both_Output_1_V_U_apdone_blk == 1'b0) & (1'b1 == ap_CS_fsm_state11))) begin
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
    if (((ap_enable_reg_pp0_iter1 == 1'b0) & (ap_enable_reg_pp0_iter0 == 1'b0))) begin
        ap_idle_pp0 = 1'b1;
    end else begin
        ap_idle_pp0 = 1'b0;
    end
end

always @ (*) begin
    if (((ap_enable_reg_pp1_iter1 == 1'b0) & (ap_enable_reg_pp1_iter0 == 1'b0))) begin
        ap_idle_pp1 = 1'b1;
    end else begin
        ap_idle_pp1 = 1'b0;
    end
end

always @ (*) begin
    if (((1'b0 == ap_block_pp0_stage0) & (1'b1 == ap_CS_fsm_pp0_stage0) & (ap_enable_reg_pp0_iter1 == 1'b1) & (icmp_ln878_reg_316 == 1'd0))) begin
        ap_phi_mux_i_V_phi_fu_129_p4 = select_ln28_1_reg_325;
    end else begin
        ap_phi_mux_i_V_phi_fu_129_p4 = i_V_reg_125;
    end
end

always @ (*) begin
    if (((ap_enable_reg_pp1_iter1 == 1'b1) & (icmp_ln43_reg_350 == 1'd0) & (1'b0 == ap_block_pp1_stage0) & (1'b1 == ap_CS_fsm_pp1_stage0))) begin
        ap_phi_mux_n_V_phi_fu_151_p4 = n_V_1_reg_345;
    end else begin
        ap_phi_mux_n_V_phi_fu_151_p4 = n_V_reg_147;
    end
end

always @ (*) begin
    if (((regslice_both_Output_1_V_U_apdone_blk == 1'b0) & (1'b1 == ap_CS_fsm_state11))) begin
        ap_ready = 1'b1;
    end else begin
        ap_ready = 1'b0;
    end
end

always @ (*) begin
    if (((ap_enable_reg_pp1_iter1 == 1'b1) & (1'b0 == ap_block_pp1_stage0) & (1'b1 == ap_CS_fsm_pp1_stage0))) begin
        z_buffer_V_address0 = z_buffer_V_addr_1_reg_360;
    end else if (((1'b0 == ap_block_pp1_stage1) & (ap_enable_reg_pp1_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp1_stage1))) begin
        z_buffer_V_address0 = zext_ln878_fu_267_p1;
    end else if (((1'b0 == ap_block_pp0_stage0) & (1'b1 == ap_CS_fsm_pp0_stage0) & (ap_enable_reg_pp0_iter1 == 1'b1))) begin
        z_buffer_V_address0 = zext_ln33_1_fu_234_p1;
    end else begin
        z_buffer_V_address0 = 'bx;
    end
end

always @ (*) begin
    if ((((ap_enable_reg_pp1_iter1 == 1'b1) & (1'b0 == ap_block_pp1_stage0_11001) & (1'b1 == ap_CS_fsm_pp1_stage0)) | ((1'b0 == ap_block_pp1_stage2_11001) & (ap_enable_reg_pp1_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp1_stage2)) | ((1'b0 == ap_block_pp1_stage1_11001) & (ap_enable_reg_pp1_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp1_stage1)) | ((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0) & (ap_enable_reg_pp0_iter1 == 1'b1)))) begin
        z_buffer_V_ce0 = 1'b1;
    end else begin
        z_buffer_V_ce0 = 1'b0;
    end
end

always @ (*) begin
    if (((ap_enable_reg_pp1_iter1 == 1'b1) & (1'b0 == ap_block_pp1_stage0) & (1'b1 == ap_CS_fsm_pp1_stage0))) begin
        z_buffer_V_d0 = fragment_z_V_reg_354;
    end else if (((1'b0 == ap_block_pp0_stage0) & (1'b1 == ap_CS_fsm_pp0_stage0) & (ap_enable_reg_pp0_iter1 == 1'b1))) begin
        z_buffer_V_d0 = 8'd255;
    end else begin
        z_buffer_V_d0 = 'bx;
    end
end

always @ (*) begin
    if ((((ap_enable_reg_pp1_iter1 == 1'b1) & (1'b0 == ap_block_pp1_stage0_11001) & (icmp_ln878_2_fu_272_p2 == 1'd1) & (1'b1 == ap_CS_fsm_pp1_stage0)) | ((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0) & (ap_enable_reg_pp0_iter1 == 1'b1) & (icmp_ln878_reg_316 == 1'd0)))) begin
        z_buffer_V_we0 = 1'b1;
    end else begin
        z_buffer_V_we0 = 1'b0;
    end
end

always @ (*) begin
    case (ap_CS_fsm)
        ap_ST_fsm_state1 : begin
            if ((~((1'b0 == Input_1_V_TVALID_int_regslice) | (ap_start == 1'b0)) & (1'b1 == ap_CS_fsm_state1) & (icmp_ln870_fu_162_p2 == 1'd1))) begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage0;
            end else if ((~((1'b0 == Input_1_V_TVALID_int_regslice) | (ap_start == 1'b0)) & (1'b1 == ap_CS_fsm_state1) & (icmp_ln870_fu_162_p2 == 1'd0))) begin
                ap_NS_fsm = ap_ST_fsm_state4;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state1;
            end
        end
        ap_ST_fsm_pp0_stage0 : begin
            if (~((1'b0 == ap_block_pp0_stage0_subdone) & (icmp_ln878_fu_174_p2 == 1'd1) & (ap_enable_reg_pp0_iter0 == 1'b1))) begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage0;
            end else if (((1'b0 == ap_block_pp0_stage0_subdone) & (icmp_ln878_fu_174_p2 == 1'd1) & (ap_enable_reg_pp0_iter0 == 1'b1))) begin
                ap_NS_fsm = ap_ST_fsm_state4;
            end else begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage0;
            end
        end
        ap_ST_fsm_state4 : begin
            ap_NS_fsm = ap_ST_fsm_pp1_stage0;
        end
        ap_ST_fsm_pp1_stage0 : begin
            if ((~((1'b0 == ap_block_pp1_stage0_subdone) & (ap_enable_reg_pp1_iter0 == 1'b1) & (icmp_ln43_fu_248_p2 == 1'd1)) & (1'b0 == ap_block_pp1_stage0_subdone))) begin
                ap_NS_fsm = ap_ST_fsm_pp1_stage1;
            end else if (((1'b0 == ap_block_pp1_stage0_subdone) & (ap_enable_reg_pp1_iter0 == 1'b1) & (icmp_ln43_fu_248_p2 == 1'd1))) begin
                ap_NS_fsm = ap_ST_fsm_state9;
            end else begin
                ap_NS_fsm = ap_ST_fsm_pp1_stage0;
            end
        end
        ap_ST_fsm_pp1_stage1 : begin
            if ((1'b0 == ap_block_pp1_stage1_subdone)) begin
                ap_NS_fsm = ap_ST_fsm_pp1_stage2;
            end else begin
                ap_NS_fsm = ap_ST_fsm_pp1_stage1;
            end
        end
        ap_ST_fsm_pp1_stage2 : begin
            if ((1'b0 == ap_block_pp1_stage2_subdone)) begin
                ap_NS_fsm = ap_ST_fsm_pp1_stage0;
            end else begin
                ap_NS_fsm = ap_ST_fsm_pp1_stage2;
            end
        end
        ap_ST_fsm_state9 : begin
            ap_NS_fsm = ap_ST_fsm_state10;
        end
        ap_ST_fsm_state10 : begin
            ap_NS_fsm = ap_ST_fsm_state11;
        end
        ap_ST_fsm_state11 : begin
            if (((regslice_both_Output_1_V_U_apdone_blk == 1'b0) & (1'b1 == ap_CS_fsm_state11))) begin
                ap_NS_fsm = ap_ST_fsm_state1;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state11;
            end
        end
        default : begin
            ap_NS_fsm = 'bx;
        end
    endcase
end

assign Input_1_V_TREADY = regslice_both_Input_1_V_U_ack_in;

assign Output_1_V_TVALID = regslice_both_Output_1_V_U_vld_out;

assign add_ln33_fu_228_p2 = (tmp_1_cast_fu_218_p3 + zext_ln33_fu_225_p1);

assign add_ln691_fu_277_p2 = (counter_V + 16'd1);

assign add_ln878_fu_168_p2 = (indvar_flatten_reg_114 + 17'd1);

assign ap_CS_fsm_pp0_stage0 = ap_CS_fsm[32'd1];

assign ap_CS_fsm_pp1_stage0 = ap_CS_fsm[32'd3];

assign ap_CS_fsm_pp1_stage1 = ap_CS_fsm[32'd4];

assign ap_CS_fsm_pp1_stage2 = ap_CS_fsm[32'd5];

assign ap_CS_fsm_state1 = ap_CS_fsm[32'd0];

assign ap_CS_fsm_state10 = ap_CS_fsm[32'd7];

assign ap_CS_fsm_state11 = ap_CS_fsm[32'd8];

assign ap_CS_fsm_state4 = ap_CS_fsm[32'd2];

assign ap_CS_fsm_state9 = ap_CS_fsm[32'd6];

assign ap_block_pp0_stage0 = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage0_11001 = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage0_subdone = ~(1'b1 == 1'b1);

assign ap_block_pp1_stage0 = ~(1'b1 == 1'b1);

always @ (*) begin
    ap_block_pp1_stage0_11001 = ((ap_enable_reg_pp1_iter1 == 1'b1) & (1'b0 == Output_1_V_TREADY_int_regslice));
end

always @ (*) begin
    ap_block_pp1_stage0_subdone = ((ap_enable_reg_pp1_iter1 == 1'b1) & (1'b0 == Output_1_V_TREADY_int_regslice));
end

assign ap_block_pp1_stage1 = ~(1'b1 == 1'b1);

always @ (*) begin
    ap_block_pp1_stage1_11001 = ((icmp_ln43_reg_350 == 1'd0) & (ap_enable_reg_pp1_iter0 == 1'b1) & (1'b0 == Input_1_V_TVALID_int_regslice));
end

always @ (*) begin
    ap_block_pp1_stage1_subdone = ((icmp_ln43_reg_350 == 1'd0) & (ap_enable_reg_pp1_iter0 == 1'b1) & (1'b0 == Input_1_V_TVALID_int_regslice));
end

assign ap_block_pp1_stage2 = ~(1'b1 == 1'b1);

always @ (*) begin
    ap_block_pp1_stage2_01001 = ((icmp_ln43_reg_350 == 1'd0) & (ap_enable_reg_pp1_iter0 == 1'b1) & (1'b0 == Output_1_V_TREADY_int_regslice));
end

always @ (*) begin
    ap_block_pp1_stage2_11001 = ((ap_enable_reg_pp1_iter0 == 1'b1) & ((1'b1 == ap_block_state7_io) | ((icmp_ln43_reg_350 == 1'd0) & (1'b0 == Output_1_V_TREADY_int_regslice))));
end

always @ (*) begin
    ap_block_pp1_stage2_subdone = ((ap_enable_reg_pp1_iter0 == 1'b1) & ((1'b1 == ap_block_state7_io) | ((icmp_ln43_reg_350 == 1'd0) & (1'b0 == Output_1_V_TREADY_int_regslice))));
end

always @ (*) begin
    ap_block_state1 = ((1'b0 == Input_1_V_TVALID_int_regslice) | (ap_start == 1'b0));
end

assign ap_block_state2_pp0_stage0_iter0 = ~(1'b1 == 1'b1);

assign ap_block_state3_pp0_stage0_iter1 = ~(1'b1 == 1'b1);

assign ap_block_state5_pp1_stage0_iter0 = ~(1'b1 == 1'b1);

always @ (*) begin
    ap_block_state6_pp1_stage1_iter0 = ((icmp_ln43_reg_350 == 1'd0) & (1'b0 == Input_1_V_TVALID_int_regslice));
end

always @ (*) begin
    ap_block_state7_io = ((icmp_ln43_reg_350 == 1'd0) & (1'b0 == Output_1_V_TREADY_int_regslice));
end

always @ (*) begin
    ap_block_state7_pp1_stage2_iter0 = ((icmp_ln43_reg_350 == 1'd0) & (1'b0 == Output_1_V_TREADY_int_regslice));
end

always @ (*) begin
    ap_block_state8_pp1_stage0_iter1 = (1'b0 == Output_1_V_TREADY_int_regslice);
end

assign ap_enable_pp0 = (ap_idle_pp0 ^ 1'b1);

assign ap_enable_pp1 = (ap_idle_pp1 ^ 1'b1);

always @ (*) begin
    ap_rst_n_inv = ~ap_rst_n;
end

assign empty_9_fu_239_p1 = tmp_V_reg_299[15:0];

assign i_V_2_fu_180_p2 = (ap_phi_mux_i_V_phi_fu_129_p4 + 9'd1);

assign icmp_ln43_fu_248_p2 = ((ap_phi_mux_n_V_phi_fu_151_p4 == empty_9_reg_340) ? 1'b1 : 1'b0);

assign icmp_ln870_1_fu_282_p2 = ((add_ln691_reg_368 == 16'd3192) ? 1'b1 : 1'b0);

assign icmp_ln870_fu_162_p2 = ((counter_V == 16'd0) ? 1'b1 : 1'b0);

assign icmp_ln878_1_fu_186_p2 = ((j_V_reg_136 == 9'd256) ? 1'b1 : 1'b0);

assign icmp_ln878_2_fu_272_p2 = ((fragment_z_V_reg_354 < z_buffer_V_q0) ? 1'b1 : 1'b0);

assign icmp_ln878_fu_174_p2 = ((indvar_flatten_reg_114 == 17'd65536) ? 1'b1 : 1'b0);

assign j_V_1_fu_212_p2 = (select_ln28_fu_192_p3 + 9'd1);

assign n_V_1_fu_242_p2 = (ap_phi_mux_n_V_phi_fu_151_p4 + 16'd1);

assign select_ln28_1_fu_200_p3 = ((icmp_ln878_1_fu_186_p2[0:0] == 1'b1) ? i_V_2_fu_180_p2 : ap_phi_mux_i_V_phi_fu_129_p4);

assign select_ln28_fu_192_p3 = ((icmp_ln878_1_fu_186_p2[0:0] == 1'b1) ? 9'd0 : j_V_reg_136);

assign select_ln79_fu_287_p3 = ((icmp_ln870_1_reg_374[0:0] == 1'b1) ? 16'd0 : add_ln691_reg_368);

assign tmp_1_cast_fu_218_p3 = {{trunc_ln33_reg_330}, {8'd0}};

assign trunc_ln33_fu_208_p1 = select_ln28_1_fu_200_p3[7:0];

assign trunc_ln878_fu_263_p1 = Input_1_V_TDATA_int_regslice[15:0];

assign zext_ln33_1_fu_234_p1 = add_ln33_fu_228_p2;

assign zext_ln33_fu_225_p1 = select_ln28_reg_320;

assign zext_ln878_fu_267_p1 = trunc_ln878_fu_263_p1;

endmodule //zculling_top
