// ==============================================================
// RTL generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC
// Version: 2018.2
// Copyright (C) 1986-2018 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

`timescale 1 ns / 1 ps 

(* CORE_GENERATION_INFO="output_fun,hls_ip_2018_2,{HLS_INPUT_TYPE=cxx,HLS_INPUT_FLOAT=0,HLS_INPUT_FIXED=1,HLS_INPUT_PART=xczu9eg-ffvb1156-2-e,HLS_INPUT_CLOCK=4.000000,HLS_INPUT_ARCH=others,HLS_SYN_CLOCK=1.088125,HLS_SYN_LAT=-1,HLS_SYN_TPT=none,HLS_SYN_MEM=0,HLS_SYN_DSP=0,HLS_SYN_FF=118,HLS_SYN_LUT=255,HLS_VERSION=2018_2}" *)

module output_fun (
        ap_clk,
        ap_rst,
        ap_start,
        ap_done,
        ap_idle,
        ap_ready,
        Input_1_V_V,
        Input_1_V_V_ap_vld,
        Input_1_V_V_ap_ack,
        Input_2_V_V,
        Input_2_V_V_ap_vld,
        Input_2_V_V_ap_ack,
        Output_1_V_V,
        Output_1_V_V_ap_vld,
        Output_1_V_V_ap_ack
);

parameter    ap_ST_fsm_state1 = 14'd1;
parameter    ap_ST_fsm_state2 = 14'd2;
parameter    ap_ST_fsm_state3 = 14'd4;
parameter    ap_ST_fsm_state4 = 14'd8;
parameter    ap_ST_fsm_state5 = 14'd16;
parameter    ap_ST_fsm_state6 = 14'd32;
parameter    ap_ST_fsm_state7 = 14'd64;
parameter    ap_ST_fsm_state8 = 14'd128;
parameter    ap_ST_fsm_state9 = 14'd256;
parameter    ap_ST_fsm_pp0_stage0 = 14'd512;
parameter    ap_ST_fsm_pp0_stage1 = 14'd1024;
parameter    ap_ST_fsm_pp0_stage2 = 14'd2048;
parameter    ap_ST_fsm_pp0_stage3 = 14'd4096;
parameter    ap_ST_fsm_state15 = 14'd8192;

input   ap_clk;
input   ap_rst;
input   ap_start;
output   ap_done;
output   ap_idle;
output   ap_ready;
input  [31:0] Input_1_V_V;
input   Input_1_V_V_ap_vld;
output   Input_1_V_V_ap_ack;
input  [31:0] Input_2_V_V;
input   Input_2_V_V_ap_vld;
output   Input_2_V_V_ap_ack;
output  [31:0] Output_1_V_V;
output   Output_1_V_V_ap_vld;
input   Output_1_V_V_ap_ack;

reg ap_done;
reg ap_idle;
reg ap_ready;
reg Input_1_V_V_ap_ack;
reg Input_2_V_V_ap_ack;
reg[31:0] Output_1_V_V;
reg Output_1_V_V_ap_vld;

(* fsm_encoding = "none" *) reg   [13:0] ap_CS_fsm;
wire    ap_CS_fsm_state1;
reg    Input_1_V_V_blk_n;
wire    ap_CS_fsm_state2;
wire   [0:0] tmp_nbreadreq_fu_54_p3;
wire    ap_CS_fsm_state7;
wire    ap_CS_fsm_pp0_stage1;
reg    ap_enable_reg_pp0_iter0;
wire    ap_block_pp0_stage1;
reg   [0:0] exitcond_reg_129;
wire    ap_CS_fsm_pp0_stage3;
wire    ap_block_pp0_stage3;
reg    Input_2_V_V_blk_n;
wire    ap_CS_fsm_state9;
reg    Output_1_V_V_blk_n;
wire   [0:0] tmp_2_fu_105_p2;
wire    ap_CS_fsm_state3;
wire    ap_CS_fsm_state4;
wire    ap_CS_fsm_state5;
wire    ap_CS_fsm_state6;
wire    ap_CS_fsm_state8;
wire    ap_CS_fsm_pp0_stage2;
wire    ap_block_pp0_stage2;
wire    ap_CS_fsm_pp0_stage0;
reg    ap_enable_reg_pp0_iter1;
wire    ap_block_pp0_stage0;
reg   [17:0] i_reg_84;
reg   [31:0] reg_95;
reg    ap_block_state2;
reg    ap_sig_ioackin_Output_1_V_V_ap_ack;
reg    ap_predicate_op29_write_state2;
reg    ap_block_state2_io;
reg    ap_block_state7;
reg   [31:0] reg_100;
reg    ap_block_state11_pp0_stage1_iter0;
reg    ap_block_state11_io;
reg    ap_block_pp0_stage1_11001;
reg    ap_block_state13_pp0_stage3_iter0;
reg    ap_block_state13_io;
reg    ap_block_pp0_stage3_11001;
wire   [0:0] exitcond_fu_111_p2;
wire    ap_block_state10_pp0_stage0_iter0;
wire    ap_block_state14_pp0_stage0_iter1;
reg    ap_block_state14_io;
reg    ap_block_pp0_stage0_11001;
wire   [17:0] i_1_fu_117_p2;
reg   [17:0] i_1_reg_133;
reg    ap_block_pp0_stage0_subdone;
reg    ap_condition_pp0_exit_iter0_state10;
reg    ap_block_pp0_stage3_subdone;
reg   [17:0] ap_phi_mux_i_phi_fu_88_p4;
reg    ap_block_pp0_stage1_01001;
wire    ap_block_state12_pp0_stage2_iter0;
wire    ap_block_pp0_stage2_01001;
reg    ap_block_pp0_stage3_01001;
wire    ap_block_pp0_stage0_01001;
reg    ap_reg_ioackin_Output_1_V_V_ap_ack;
reg    ap_block_state12_io;
reg    ap_block_pp0_stage2_11001;
wire    ap_CS_fsm_state15;
reg   [13:0] ap_NS_fsm;
reg    ap_block_pp0_stage1_subdone;
reg    ap_block_pp0_stage2_subdone;
reg    ap_idle_pp0;
wire    ap_enable_pp0;

// power-on initialization
initial begin
#0 ap_CS_fsm = 14'd1;
#0 ap_enable_reg_pp0_iter0 = 1'b0;
#0 ap_enable_reg_pp0_iter1 = 1'b0;
#0 ap_reg_ioackin_Output_1_V_V_ap_ack = 1'b0;
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_CS_fsm <= ap_ST_fsm_state1;
    end else begin
        ap_CS_fsm <= ap_NS_fsm;
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp0_iter0 <= 1'b0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_subdone) & (1'b1 == ap_condition_pp0_exit_iter0_state10) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            ap_enable_reg_pp0_iter0 <= 1'b0;
        end else if ((~((1'b0 == Input_2_V_V_ap_vld) | (ap_sig_ioackin_Output_1_V_V_ap_ack == 1'b0)) & (1'b1 == ap_CS_fsm_state9))) begin
            ap_enable_reg_pp0_iter0 <= 1'b1;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp0_iter1 <= 1'b0;
    end else begin
        if (((1'b1 == ap_condition_pp0_exit_iter0_state10) & (((1'b0 == ap_block_pp0_stage3_subdone) & (1'b1 == ap_CS_fsm_pp0_stage3)) | ((1'b0 == ap_block_pp0_stage0_subdone) & (1'b1 == ap_CS_fsm_pp0_stage0))))) begin
            ap_enable_reg_pp0_iter1 <= (1'b1 ^ ap_condition_pp0_exit_iter0_state10);
        end else if ((((1'b0 == ap_block_pp0_stage3_subdone) & (1'b1 == ap_CS_fsm_pp0_stage3)) | ((1'b0 == ap_block_pp0_stage0_subdone) & (1'b1 == ap_CS_fsm_pp0_stage0)))) begin
            ap_enable_reg_pp0_iter1 <= ap_enable_reg_pp0_iter0;
        end else if ((~((1'b0 == Input_2_V_V_ap_vld) | (ap_sig_ioackin_Output_1_V_V_ap_ack == 1'b0)) & (1'b1 == ap_CS_fsm_state9))) begin
            ap_enable_reg_pp0_iter1 <= 1'b0;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_reg_ioackin_Output_1_V_V_ap_ack <= 1'b0;
    end else begin
        if (((~((1'b0 == Input_2_V_V_ap_vld) | (ap_sig_ioackin_Output_1_V_V_ap_ack == 1'b0)) & (1'b1 == ap_CS_fsm_state9)) | ((exitcond_reg_129 == 1'd0) & (1'b0 == ap_block_pp0_stage0_11001) & (ap_enable_reg_pp0_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage0)) | ((exitcond_reg_129 == 1'd0) & (1'b0 == ap_block_pp0_stage3_11001) & (1'b1 == ap_CS_fsm_pp0_stage3) & (ap_enable_reg_pp0_iter0 == 1'b1)) | ((exitcond_reg_129 == 1'd0) & (1'b0 == ap_block_pp0_stage2_11001) & (ap_enable_reg_pp0_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage2)) | ((exitcond_reg_129 == 1'd0) & (ap_enable_reg_pp0_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage1) & (1'b0 == ap_block_pp0_stage1_11001)) | (~((1'b0 == Input_2_V_V_ap_vld) | (1'b0 == Input_1_V_V_ap_vld) | (ap_sig_ioackin_Output_1_V_V_ap_ack == 1'b0)) & (1'b1 == ap_CS_fsm_state7)) | (~((1'b1 == ap_block_state2_io) | ((tmp_nbreadreq_fu_54_p3 == 1'd1) & (1'b0 == Input_1_V_V_ap_vld))) & (ap_predicate_op29_write_state2 == 1'b1) & (1'b1 == ap_CS_fsm_state2)) | ((1'b1 == ap_CS_fsm_state8) & (ap_sig_ioackin_Output_1_V_V_ap_ack == 1'b1)) | ((1'b1 == ap_CS_fsm_state6) & (ap_sig_ioackin_Output_1_V_V_ap_ack == 1'b1)) | ((1'b1 == ap_CS_fsm_state5) & (ap_sig_ioackin_Output_1_V_V_ap_ack == 1'b1)) | ((1'b1 == ap_CS_fsm_state4) & (ap_sig_ioackin_Output_1_V_V_ap_ack == 1'b1)) | ((1'b1 == ap_CS_fsm_state3) & (ap_sig_ioackin_Output_1_V_V_ap_ack == 1'b1)))) begin
            ap_reg_ioackin_Output_1_V_V_ap_ack <= 1'b0;
        end else if ((((1'b1 == Input_2_V_V_ap_vld) & (1'b1 == ap_CS_fsm_state9) & (1'b1 == Output_1_V_V_ap_ack)) | ((exitcond_reg_129 == 1'd0) & (1'b0 == ap_block_pp0_stage0_01001) & (1'b1 == Output_1_V_V_ap_ack) & (ap_enable_reg_pp0_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage0)) | ((exitcond_reg_129 == 1'd0) & (1'b0 == ap_block_pp0_stage3_01001) & (1'b1 == ap_CS_fsm_pp0_stage3) & (ap_enable_reg_pp0_iter0 == 1'b1) & (1'b1 == Output_1_V_V_ap_ack)) | ((exitcond_reg_129 == 1'd0) & (1'b0 == ap_block_pp0_stage2_01001) & (ap_enable_reg_pp0_iter0 == 1'b1) & (1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_pp0_stage2)) | ((exitcond_reg_129 == 1'd0) & (1'b0 == ap_block_pp0_stage1_01001) & (ap_enable_reg_pp0_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage1) & (1'b1 == Output_1_V_V_ap_ack)) | (~((1'b0 == Input_2_V_V_ap_vld) | (1'b0 == Input_1_V_V_ap_vld)) & (1'b1 == ap_CS_fsm_state7) & (1'b1 == Output_1_V_V_ap_ack)) | (~((tmp_nbreadreq_fu_54_p3 == 1'd1) & (1'b0 == Input_1_V_V_ap_vld)) & (ap_predicate_op29_write_state2 == 1'b1) & (1'b1 == ap_CS_fsm_state2) & (1'b1 == Output_1_V_V_ap_ack)) | ((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state8)) | ((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state6)) | ((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state5)) | ((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state4)) | ((1'b1 == Output_1_V_V_ap_ack) & (1'b1 == ap_CS_fsm_state3)))) begin
            ap_reg_ioackin_Output_1_V_V_ap_ack <= 1'b1;
        end
    end
end

always @ (posedge ap_clk) begin
    if (((exitcond_reg_129 == 1'd0) & (1'b0 == ap_block_pp0_stage0_11001) & (ap_enable_reg_pp0_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
        i_reg_84 <= i_1_reg_133;
    end else if ((~((1'b0 == Input_2_V_V_ap_vld) | (ap_sig_ioackin_Output_1_V_V_ap_ack == 1'b0)) & (1'b1 == ap_CS_fsm_state9))) begin
        i_reg_84 <= 18'd0;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
        exitcond_reg_129 <= exitcond_fu_111_p2;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b0 == ap_block_pp0_stage0_11001) & (ap_enable_reg_pp0_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
        i_1_reg_133 <= i_1_fu_117_p2;
    end
end

always @ (posedge ap_clk) begin
    if ((((exitcond_reg_129 == 1'd0) & (1'b0 == ap_block_pp0_stage3_11001) & (1'b1 == ap_CS_fsm_pp0_stage3) & (ap_enable_reg_pp0_iter0 == 1'b1)) | ((exitcond_reg_129 == 1'd0) & (ap_enable_reg_pp0_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage1) & (1'b0 == ap_block_pp0_stage1_11001)))) begin
        reg_100 <= Input_2_V_V;
    end
end

always @ (posedge ap_clk) begin
    if (((~((1'b0 == Input_2_V_V_ap_vld) | (1'b0 == Input_1_V_V_ap_vld) | (ap_sig_ioackin_Output_1_V_V_ap_ack == 1'b0)) & (1'b1 == ap_CS_fsm_state7)) | (~((1'b1 == ap_block_state2_io) | ((tmp_nbreadreq_fu_54_p3 == 1'd1) & (1'b0 == Input_1_V_V_ap_vld))) & (tmp_nbreadreq_fu_54_p3 == 1'd1) & (1'b1 == ap_CS_fsm_state2)))) begin
        reg_95 <= Input_1_V_V;
    end
end

always @ (*) begin
    if ((((exitcond_reg_129 == 1'd0) & (1'b0 == ap_block_pp0_stage3_11001) & (1'b1 == ap_CS_fsm_pp0_stage3) & (ap_enable_reg_pp0_iter0 == 1'b1)) | ((exitcond_reg_129 == 1'd0) & (ap_enable_reg_pp0_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage1) & (1'b0 == ap_block_pp0_stage1_11001)) | (~((1'b0 == Input_2_V_V_ap_vld) | (1'b0 == Input_1_V_V_ap_vld) | (ap_sig_ioackin_Output_1_V_V_ap_ack == 1'b0)) & (1'b1 == ap_CS_fsm_state7)) | (~((1'b1 == ap_block_state2_io) | ((tmp_nbreadreq_fu_54_p3 == 1'd1) & (1'b0 == Input_1_V_V_ap_vld))) & (tmp_nbreadreq_fu_54_p3 == 1'd1) & (1'b1 == ap_CS_fsm_state2)))) begin
        Input_1_V_V_ap_ack = 1'b1;
    end else begin
        Input_1_V_V_ap_ack = 1'b0;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state7) | ((1'b0 == ap_block_pp0_stage3) & (exitcond_reg_129 == 1'd0) & (1'b1 == ap_CS_fsm_pp0_stage3) & (ap_enable_reg_pp0_iter0 == 1'b1)) | ((exitcond_reg_129 == 1'd0) & (1'b0 == ap_block_pp0_stage1) & (ap_enable_reg_pp0_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage1)) | ((tmp_nbreadreq_fu_54_p3 == 1'd1) & (1'b1 == ap_CS_fsm_state2)))) begin
        Input_1_V_V_blk_n = Input_1_V_V_ap_vld;
    end else begin
        Input_1_V_V_blk_n = 1'b1;
    end
end

always @ (*) begin
    if (((~((1'b0 == Input_2_V_V_ap_vld) | (ap_sig_ioackin_Output_1_V_V_ap_ack == 1'b0)) & (1'b1 == ap_CS_fsm_state9)) | ((exitcond_reg_129 == 1'd0) & (1'b0 == ap_block_pp0_stage3_11001) & (1'b1 == ap_CS_fsm_pp0_stage3) & (ap_enable_reg_pp0_iter0 == 1'b1)) | ((exitcond_reg_129 == 1'd0) & (ap_enable_reg_pp0_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage1) & (1'b0 == ap_block_pp0_stage1_11001)) | (~((1'b0 == Input_2_V_V_ap_vld) | (1'b0 == Input_1_V_V_ap_vld) | (ap_sig_ioackin_Output_1_V_V_ap_ack == 1'b0)) & (1'b1 == ap_CS_fsm_state7)))) begin
        Input_2_V_V_ap_ack = 1'b1;
    end else begin
        Input_2_V_V_ap_ack = 1'b0;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state9) | (1'b1 == ap_CS_fsm_state7) | ((1'b0 == ap_block_pp0_stage3) & (exitcond_reg_129 == 1'd0) & (1'b1 == ap_CS_fsm_pp0_stage3) & (ap_enable_reg_pp0_iter0 == 1'b1)) | ((exitcond_reg_129 == 1'd0) & (1'b0 == ap_block_pp0_stage1) & (ap_enable_reg_pp0_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage1)))) begin
        Input_2_V_V_blk_n = Input_2_V_V_ap_vld;
    end else begin
        Input_2_V_V_blk_n = 1'b1;
    end
end

always @ (*) begin
    if ((((exitcond_reg_129 == 1'd0) & (1'b0 == ap_block_pp0_stage0_01001) & (ap_enable_reg_pp0_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage0)) | ((exitcond_reg_129 == 1'd0) & (1'b0 == ap_block_pp0_stage2_01001) & (ap_enable_reg_pp0_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage2)))) begin
        Output_1_V_V = reg_100;
    end else if ((((exitcond_reg_129 == 1'd0) & (1'b0 == ap_block_pp0_stage3_01001) & (1'b1 == ap_CS_fsm_pp0_stage3) & (ap_enable_reg_pp0_iter0 == 1'b1)) | ((exitcond_reg_129 == 1'd0) & (1'b0 == ap_block_pp0_stage1_01001) & (ap_enable_reg_pp0_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage1)))) begin
        Output_1_V_V = Input_1_V_V;
    end else if ((((1'b1 == Input_2_V_V_ap_vld) & (1'b1 == ap_CS_fsm_state9)) | (~((1'b0 == Input_2_V_V_ap_vld) | (1'b0 == Input_1_V_V_ap_vld)) & (1'b1 == ap_CS_fsm_state7)))) begin
        Output_1_V_V = Input_2_V_V;
    end else if (((1'b1 == ap_CS_fsm_state8) | (1'b1 == ap_CS_fsm_state6))) begin
        Output_1_V_V = reg_95;
    end else if (((1'b1 == ap_CS_fsm_state5) | (1'b1 == ap_CS_fsm_state4) | (1'b1 == ap_CS_fsm_state3) | (~((tmp_nbreadreq_fu_54_p3 == 1'd1) & (1'b0 == Input_1_V_V_ap_vld)) & (ap_predicate_op29_write_state2 == 1'b1) & (1'b1 == ap_CS_fsm_state2)))) begin
        Output_1_V_V = 32'd892932;
    end else begin
        Output_1_V_V = 'bx;
    end
end

always @ (*) begin
    if ((((1'b1 == Input_2_V_V_ap_vld) & (ap_reg_ioackin_Output_1_V_V_ap_ack == 1'b0) & (1'b1 == ap_CS_fsm_state9)) | ((exitcond_reg_129 == 1'd0) & (ap_reg_ioackin_Output_1_V_V_ap_ack == 1'b0) & (1'b0 == ap_block_pp0_stage0_01001) & (ap_enable_reg_pp0_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage0)) | ((exitcond_reg_129 == 1'd0) & (ap_reg_ioackin_Output_1_V_V_ap_ack == 1'b0) & (1'b0 == ap_block_pp0_stage3_01001) & (1'b1 == ap_CS_fsm_pp0_stage3) & (ap_enable_reg_pp0_iter0 == 1'b1)) | ((exitcond_reg_129 == 1'd0) & (ap_reg_ioackin_Output_1_V_V_ap_ack == 1'b0) & (1'b0 == ap_block_pp0_stage2_01001) & (ap_enable_reg_pp0_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage2)) | ((exitcond_reg_129 == 1'd0) & (ap_reg_ioackin_Output_1_V_V_ap_ack == 1'b0) & (1'b0 == ap_block_pp0_stage1_01001) & (ap_enable_reg_pp0_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage1)) | (~((1'b0 == Input_2_V_V_ap_vld) | (1'b0 == Input_1_V_V_ap_vld)) & (ap_reg_ioackin_Output_1_V_V_ap_ack == 1'b0) & (1'b1 == ap_CS_fsm_state7)) | (~((tmp_nbreadreq_fu_54_p3 == 1'd1) & (1'b0 == Input_1_V_V_ap_vld)) & (ap_reg_ioackin_Output_1_V_V_ap_ack == 1'b0) & (ap_predicate_op29_write_state2 == 1'b1) & (1'b1 == ap_CS_fsm_state2)) | ((ap_reg_ioackin_Output_1_V_V_ap_ack == 1'b0) & (1'b1 == ap_CS_fsm_state8)) | ((ap_reg_ioackin_Output_1_V_V_ap_ack == 1'b0) & (1'b1 == ap_CS_fsm_state6)) | ((ap_reg_ioackin_Output_1_V_V_ap_ack == 1'b0) & (1'b1 == ap_CS_fsm_state5)) | ((ap_reg_ioackin_Output_1_V_V_ap_ack == 1'b0) & (1'b1 == ap_CS_fsm_state4)) | ((ap_reg_ioackin_Output_1_V_V_ap_ack == 1'b0) & (1'b1 == ap_CS_fsm_state3)))) begin
        Output_1_V_V_ap_vld = 1'b1;
    end else begin
        Output_1_V_V_ap_vld = 1'b0;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state9) | (1'b1 == ap_CS_fsm_state7) | (1'b1 == ap_CS_fsm_state8) | (1'b1 == ap_CS_fsm_state6) | (1'b1 == ap_CS_fsm_state5) | (1'b1 == ap_CS_fsm_state4) | (1'b1 == ap_CS_fsm_state3) | ((exitcond_reg_129 == 1'd0) & (ap_enable_reg_pp0_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage0) & (1'b0 == ap_block_pp0_stage0)) | ((1'b0 == ap_block_pp0_stage3) & (exitcond_reg_129 == 1'd0) & (1'b1 == ap_CS_fsm_pp0_stage3) & (ap_enable_reg_pp0_iter0 == 1'b1)) | ((exitcond_reg_129 == 1'd0) & (ap_enable_reg_pp0_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage2) & (1'b0 == ap_block_pp0_stage2)) | ((exitcond_reg_129 == 1'd0) & (1'b0 == ap_block_pp0_stage1) & (ap_enable_reg_pp0_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage1)) | ((tmp_2_fu_105_p2 == 1'd0) & (tmp_nbreadreq_fu_54_p3 == 1'd1) & (1'b1 == ap_CS_fsm_state2)))) begin
        Output_1_V_V_blk_n = Output_1_V_V_ap_ack;
    end else begin
        Output_1_V_V_blk_n = 1'b1;
    end
end

always @ (*) begin
    if ((exitcond_fu_111_p2 == 1'd1)) begin
        ap_condition_pp0_exit_iter0_state10 = 1'b1;
    end else begin
        ap_condition_pp0_exit_iter0_state10 = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state15)) begin
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
    if (((ap_enable_reg_pp0_iter0 == 1'b0) & (ap_enable_reg_pp0_iter1 == 1'b0))) begin
        ap_idle_pp0 = 1'b1;
    end else begin
        ap_idle_pp0 = 1'b0;
    end
end

always @ (*) begin
    if (((exitcond_reg_129 == 1'd0) & (ap_enable_reg_pp0_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage0) & (1'b0 == ap_block_pp0_stage0))) begin
        ap_phi_mux_i_phi_fu_88_p4 = i_1_reg_133;
    end else begin
        ap_phi_mux_i_phi_fu_88_p4 = i_reg_84;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state15)) begin
        ap_ready = 1'b1;
    end else begin
        ap_ready = 1'b0;
    end
end

always @ (*) begin
    if ((ap_reg_ioackin_Output_1_V_V_ap_ack == 1'b0)) begin
        ap_sig_ioackin_Output_1_V_V_ap_ack = Output_1_V_V_ap_ack;
    end else begin
        ap_sig_ioackin_Output_1_V_V_ap_ack = 1'b1;
    end
end

always @ (*) begin
    case (ap_CS_fsm)
        ap_ST_fsm_state1 : begin
            if (((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b1))) begin
                ap_NS_fsm = ap_ST_fsm_state2;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state1;
            end
        end
        ap_ST_fsm_state2 : begin
            if ((~((1'b1 == ap_block_state2_io) | ((tmp_nbreadreq_fu_54_p3 == 1'd1) & (1'b0 == Input_1_V_V_ap_vld))) & (tmp_2_fu_105_p2 == 1'd1) & (tmp_nbreadreq_fu_54_p3 == 1'd1) & (1'b1 == ap_CS_fsm_state2))) begin
                ap_NS_fsm = ap_ST_fsm_state6;
            end else if ((~((1'b1 == ap_block_state2_io) | ((tmp_nbreadreq_fu_54_p3 == 1'd1) & (1'b0 == Input_1_V_V_ap_vld))) & (tmp_2_fu_105_p2 == 1'd0) & (tmp_nbreadreq_fu_54_p3 == 1'd1) & (1'b1 == ap_CS_fsm_state2))) begin
                ap_NS_fsm = ap_ST_fsm_state3;
            end else if ((~((1'b1 == ap_block_state2_io) | ((tmp_nbreadreq_fu_54_p3 == 1'd1) & (1'b0 == Input_1_V_V_ap_vld))) & (tmp_nbreadreq_fu_54_p3 == 1'd0) & (1'b1 == ap_CS_fsm_state2))) begin
                ap_NS_fsm = ap_ST_fsm_state2;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state2;
            end
        end
        ap_ST_fsm_state3 : begin
            if (((1'b1 == ap_CS_fsm_state3) & (ap_sig_ioackin_Output_1_V_V_ap_ack == 1'b1))) begin
                ap_NS_fsm = ap_ST_fsm_state4;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state3;
            end
        end
        ap_ST_fsm_state4 : begin
            if (((1'b1 == ap_CS_fsm_state4) & (ap_sig_ioackin_Output_1_V_V_ap_ack == 1'b1))) begin
                ap_NS_fsm = ap_ST_fsm_state5;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state4;
            end
        end
        ap_ST_fsm_state5 : begin
            if (((1'b1 == ap_CS_fsm_state5) & (ap_sig_ioackin_Output_1_V_V_ap_ack == 1'b1))) begin
                ap_NS_fsm = ap_ST_fsm_state6;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state5;
            end
        end
        ap_ST_fsm_state6 : begin
            if (((1'b1 == ap_CS_fsm_state6) & (ap_sig_ioackin_Output_1_V_V_ap_ack == 1'b1))) begin
                ap_NS_fsm = ap_ST_fsm_state7;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state6;
            end
        end
        ap_ST_fsm_state7 : begin
            if ((~((1'b0 == Input_2_V_V_ap_vld) | (1'b0 == Input_1_V_V_ap_vld) | (ap_sig_ioackin_Output_1_V_V_ap_ack == 1'b0)) & (1'b1 == ap_CS_fsm_state7))) begin
                ap_NS_fsm = ap_ST_fsm_state8;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state7;
            end
        end
        ap_ST_fsm_state8 : begin
            if (((1'b1 == ap_CS_fsm_state8) & (ap_sig_ioackin_Output_1_V_V_ap_ack == 1'b1))) begin
                ap_NS_fsm = ap_ST_fsm_state9;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state8;
            end
        end
        ap_ST_fsm_state9 : begin
            if ((~((1'b0 == Input_2_V_V_ap_vld) | (ap_sig_ioackin_Output_1_V_V_ap_ack == 1'b0)) & (1'b1 == ap_CS_fsm_state9))) begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage0;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state9;
            end
        end
        ap_ST_fsm_pp0_stage0 : begin
            if ((~((exitcond_fu_111_p2 == 1'd1) & (1'b0 == ap_block_pp0_stage0_subdone) & (ap_enable_reg_pp0_iter0 == 1'b1)) & (1'b0 == ap_block_pp0_stage0_subdone))) begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage1;
            end else if (((exitcond_fu_111_p2 == 1'd1) & (1'b0 == ap_block_pp0_stage0_subdone) & (ap_enable_reg_pp0_iter0 == 1'b1))) begin
                ap_NS_fsm = ap_ST_fsm_state15;
            end else begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage0;
            end
        end
        ap_ST_fsm_pp0_stage1 : begin
            if ((1'b0 == ap_block_pp0_stage1_subdone)) begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage2;
            end else begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage1;
            end
        end
        ap_ST_fsm_pp0_stage2 : begin
            if ((1'b0 == ap_block_pp0_stage2_subdone)) begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage3;
            end else begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage2;
            end
        end
        ap_ST_fsm_pp0_stage3 : begin
            if ((1'b0 == ap_block_pp0_stage3_subdone)) begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage0;
            end else begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage3;
            end
        end
        ap_ST_fsm_state15 : begin
            ap_NS_fsm = ap_ST_fsm_state1;
        end
        default : begin
            ap_NS_fsm = 'bx;
        end
    endcase
end

assign ap_CS_fsm_pp0_stage0 = ap_CS_fsm[32'd9];

assign ap_CS_fsm_pp0_stage1 = ap_CS_fsm[32'd10];

assign ap_CS_fsm_pp0_stage2 = ap_CS_fsm[32'd11];

assign ap_CS_fsm_pp0_stage3 = ap_CS_fsm[32'd12];

assign ap_CS_fsm_state1 = ap_CS_fsm[32'd0];

assign ap_CS_fsm_state15 = ap_CS_fsm[32'd13];

assign ap_CS_fsm_state2 = ap_CS_fsm[32'd1];

assign ap_CS_fsm_state3 = ap_CS_fsm[32'd2];

assign ap_CS_fsm_state4 = ap_CS_fsm[32'd3];

assign ap_CS_fsm_state5 = ap_CS_fsm[32'd4];

assign ap_CS_fsm_state6 = ap_CS_fsm[32'd5];

assign ap_CS_fsm_state7 = ap_CS_fsm[32'd6];

assign ap_CS_fsm_state8 = ap_CS_fsm[32'd7];

assign ap_CS_fsm_state9 = ap_CS_fsm[32'd8];

assign ap_block_pp0_stage0 = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage0_01001 = ~(1'b1 == 1'b1);

always @ (*) begin
    ap_block_pp0_stage0_11001 = ((1'b1 == ap_block_state14_io) & (ap_enable_reg_pp0_iter1 == 1'b1));
end

always @ (*) begin
    ap_block_pp0_stage0_subdone = ((1'b1 == ap_block_state14_io) & (ap_enable_reg_pp0_iter1 == 1'b1));
end

assign ap_block_pp0_stage1 = ~(1'b1 == 1'b1);

always @ (*) begin
    ap_block_pp0_stage1_01001 = ((ap_enable_reg_pp0_iter0 == 1'b1) & (((exitcond_reg_129 == 1'd0) & (1'b0 == Input_2_V_V_ap_vld)) | ((exitcond_reg_129 == 1'd0) & (1'b0 == Input_1_V_V_ap_vld))));
end

always @ (*) begin
    ap_block_pp0_stage1_11001 = ((ap_enable_reg_pp0_iter0 == 1'b1) & ((1'b1 == ap_block_state11_io) | ((exitcond_reg_129 == 1'd0) & (1'b0 == Input_2_V_V_ap_vld)) | ((exitcond_reg_129 == 1'd0) & (1'b0 == Input_1_V_V_ap_vld))));
end

always @ (*) begin
    ap_block_pp0_stage1_subdone = ((ap_enable_reg_pp0_iter0 == 1'b1) & ((1'b1 == ap_block_state11_io) | ((exitcond_reg_129 == 1'd0) & (1'b0 == Input_2_V_V_ap_vld)) | ((exitcond_reg_129 == 1'd0) & (1'b0 == Input_1_V_V_ap_vld))));
end

assign ap_block_pp0_stage2 = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage2_01001 = ~(1'b1 == 1'b1);

always @ (*) begin
    ap_block_pp0_stage2_11001 = ((1'b1 == ap_block_state12_io) & (ap_enable_reg_pp0_iter0 == 1'b1));
end

always @ (*) begin
    ap_block_pp0_stage2_subdone = ((1'b1 == ap_block_state12_io) & (ap_enable_reg_pp0_iter0 == 1'b1));
end

assign ap_block_pp0_stage3 = ~(1'b1 == 1'b1);

always @ (*) begin
    ap_block_pp0_stage3_01001 = ((ap_enable_reg_pp0_iter0 == 1'b1) & (((exitcond_reg_129 == 1'd0) & (1'b0 == Input_2_V_V_ap_vld)) | ((exitcond_reg_129 == 1'd0) & (1'b0 == Input_1_V_V_ap_vld))));
end

always @ (*) begin
    ap_block_pp0_stage3_11001 = ((ap_enable_reg_pp0_iter0 == 1'b1) & ((1'b1 == ap_block_state13_io) | ((exitcond_reg_129 == 1'd0) & (1'b0 == Input_2_V_V_ap_vld)) | ((exitcond_reg_129 == 1'd0) & (1'b0 == Input_1_V_V_ap_vld))));
end

always @ (*) begin
    ap_block_pp0_stage3_subdone = ((ap_enable_reg_pp0_iter0 == 1'b1) & ((1'b1 == ap_block_state13_io) | ((exitcond_reg_129 == 1'd0) & (1'b0 == Input_2_V_V_ap_vld)) | ((exitcond_reg_129 == 1'd0) & (1'b0 == Input_1_V_V_ap_vld))));
end

assign ap_block_state10_pp0_stage0_iter0 = ~(1'b1 == 1'b1);

always @ (*) begin
    ap_block_state11_io = ((exitcond_reg_129 == 1'd0) & (ap_sig_ioackin_Output_1_V_V_ap_ack == 1'b0));
end

always @ (*) begin
    ap_block_state11_pp0_stage1_iter0 = (((exitcond_reg_129 == 1'd0) & (1'b0 == Input_2_V_V_ap_vld)) | ((exitcond_reg_129 == 1'd0) & (1'b0 == Input_1_V_V_ap_vld)));
end

always @ (*) begin
    ap_block_state12_io = ((exitcond_reg_129 == 1'd0) & (ap_sig_ioackin_Output_1_V_V_ap_ack == 1'b0));
end

assign ap_block_state12_pp0_stage2_iter0 = ~(1'b1 == 1'b1);

always @ (*) begin
    ap_block_state13_io = ((exitcond_reg_129 == 1'd0) & (ap_sig_ioackin_Output_1_V_V_ap_ack == 1'b0));
end

always @ (*) begin
    ap_block_state13_pp0_stage3_iter0 = (((exitcond_reg_129 == 1'd0) & (1'b0 == Input_2_V_V_ap_vld)) | ((exitcond_reg_129 == 1'd0) & (1'b0 == Input_1_V_V_ap_vld)));
end

always @ (*) begin
    ap_block_state14_io = ((exitcond_reg_129 == 1'd0) & (ap_sig_ioackin_Output_1_V_V_ap_ack == 1'b0));
end

assign ap_block_state14_pp0_stage0_iter1 = ~(1'b1 == 1'b1);

always @ (*) begin
    ap_block_state2 = ((tmp_nbreadreq_fu_54_p3 == 1'd1) & (1'b0 == Input_1_V_V_ap_vld));
end

always @ (*) begin
    ap_block_state2_io = ((ap_sig_ioackin_Output_1_V_V_ap_ack == 1'b0) & (ap_predicate_op29_write_state2 == 1'b1));
end

always @ (*) begin
    ap_block_state7 = ((1'b0 == Input_2_V_V_ap_vld) | (1'b0 == Input_1_V_V_ap_vld));
end

assign ap_enable_pp0 = (ap_idle_pp0 ^ 1'b1);

always @ (*) begin
    ap_predicate_op29_write_state2 = ((tmp_2_fu_105_p2 == 1'd0) & (tmp_nbreadreq_fu_54_p3 == 1'd1));
end

assign exitcond_fu_111_p2 = ((ap_phi_mux_i_phi_fu_88_p4 == 18'd223231) ? 1'b1 : 1'b0);

assign i_1_fu_117_p2 = (ap_phi_mux_i_phi_fu_88_p4 + 18'd1);

assign tmp_2_fu_105_p2 = ((Input_1_V_V == 32'd10) ? 1'b1 : 1'b0);

assign tmp_nbreadreq_fu_54_p3 = Input_1_V_V_ap_vld;

endmodule //output_fun
