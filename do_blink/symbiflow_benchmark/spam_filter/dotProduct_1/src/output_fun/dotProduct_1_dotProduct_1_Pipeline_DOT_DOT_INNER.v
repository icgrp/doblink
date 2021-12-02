// ==============================================================
// RTL generated by Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2021.1 (64-bit)
// Version: 2021.1
// Copyright (C) Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

`timescale 1 ns / 1 ps 

module dotProduct_1_dotProduct_1_Pipeline_DOT_DOT_INNER (
        ap_clk,
        ap_rst,
        ap_start,
        ap_done,
        ap_idle,
        ap_ready,
        result_V_1_out,
        result_V_1_out_ap_vld,
        feature_V_1_address0,
        feature_V_1_ce0,
        feature_V_1_q0,
        feature_V_0_address0,
        feature_V_0_ce0,
        feature_V_0_q0,
        param_V_address0,
        param_V_ce0,
        param_V_q0,
        grp_fu_316_p_din0,
        grp_fu_316_p_din1,
        grp_fu_316_p_dout0,
        grp_fu_316_p_ce
);

parameter    ap_ST_fsm_pp0_stage0 = 2'd1;
parameter    ap_ST_fsm_pp0_stage1 = 2'd2;

input   ap_clk;
input   ap_rst;
input   ap_start;
output   ap_done;
output   ap_idle;
output   ap_ready;
output  [31:0] result_V_1_out;
output   result_V_1_out_ap_vld;
output  [7:0] feature_V_1_address0;
output   feature_V_1_ce0;
input  [15:0] feature_V_1_q0;
output  [7:0] feature_V_0_address0;
output   feature_V_0_ce0;
input  [15:0] feature_V_0_q0;
output  [8:0] param_V_address0;
output   param_V_ce0;
input  [31:0] param_V_q0;
output  [31:0] grp_fu_316_p_din0;
output  [22:0] grp_fu_316_p_din1;
input  [50:0] grp_fu_316_p_dout0;
output   grp_fu_316_p_ce;

reg ap_idle;
reg result_V_1_out_ap_vld;
reg feature_V_1_ce0;
reg feature_V_0_ce0;
reg param_V_ce0;

(* fsm_encoding = "none" *) reg   [1:0] ap_CS_fsm;
wire    ap_CS_fsm_pp0_stage0;
reg    ap_enable_reg_pp0_iter0;
reg    ap_enable_reg_pp0_iter1;
reg    ap_enable_reg_pp0_iter2;
reg    ap_enable_reg_pp0_iter3;
reg    ap_enable_reg_pp0_iter4;
reg    ap_enable_reg_pp0_iter5;
reg    ap_enable_reg_pp0_iter6;
reg    ap_idle_pp0;
wire    ap_CS_fsm_pp0_stage1;
wire    ap_block_state2_pp0_stage1_iter0;
wire    ap_block_state4_pp0_stage1_iter1;
wire    ap_block_state6_pp0_stage1_iter2;
wire    ap_block_state8_pp0_stage1_iter3;
wire    ap_block_state10_pp0_stage1_iter4;
wire    ap_block_state12_pp0_stage1_iter5;
wire    ap_block_state14_pp0_stage1_iter6;
wire    ap_block_pp0_stage1_subdone;
reg   [0:0] icmp_ln51_reg_342;
reg    ap_condition_exit_pp0_iter0_stage1;
wire    ap_loop_exit_ready;
reg    ap_ready_int;
wire    ap_block_state1_pp0_stage0_iter0;
wire    ap_block_state3_pp0_stage0_iter1;
wire    ap_block_state5_pp0_stage0_iter2;
wire    ap_block_state7_pp0_stage0_iter3;
wire    ap_block_state9_pp0_stage0_iter4;
wire    ap_block_state11_pp0_stage0_iter5;
wire    ap_block_state13_pp0_stage0_iter6;
wire    ap_block_pp0_stage0_11001;
wire   [0:0] icmp_ln51_fu_159_p2;
reg   [0:0] icmp_ln51_reg_342_pp0_iter1_reg;
reg   [0:0] icmp_ln51_reg_342_pp0_iter2_reg;
reg   [0:0] icmp_ln51_reg_342_pp0_iter3_reg;
reg   [0:0] icmp_ln51_reg_342_pp0_iter4_reg;
reg   [0:0] icmp_ln51_reg_342_pp0_iter5_reg;
wire   [9:0] add_ln51_fu_165_p2;
reg   [9:0] add_ln51_reg_346;
reg   [2:0] j_load_reg_351;
reg   [7:0] i_load_reg_356;
wire   [0:0] icmp_ln54_fu_177_p2;
reg   [0:0] icmp_ln54_reg_361;
wire   [7:0] add_ln51_1_fu_183_p2;
reg   [7:0] add_ln51_1_reg_367;
wire   [2:0] select_ln51_fu_189_p3;
reg   [2:0] select_ln51_reg_372;
wire    ap_block_pp0_stage1_11001;
wire   [6:0] trunc_ln51_fu_200_p1;
reg   [6:0] trunc_ln51_reg_377;
wire   [0:0] trunc_ln56_fu_204_p1;
reg   [0:0] trunc_ln56_reg_382;
reg   [0:0] trunc_ln56_reg_382_pp0_iter1_reg;
reg   [0:0] trunc_ln56_reg_382_pp0_iter2_reg;
wire   [2:0] add_ln54_fu_208_p2;
reg   [2:0] add_ln54_reg_387;
wire   [8:0] add_ln56_fu_233_p2;
reg   [8:0] add_ln56_reg_392;
reg   [7:0] lshr_ln736_1_reg_397;
reg   [15:0] feature_V_1_load_reg_417;
reg   [15:0] feature_V_0_load_reg_422;
reg   [31:0] r_V_reg_427;
wire   [15:0] select_ln56_fu_262_p3;
reg   [15:0] select_ln56_reg_432;
wire  signed [50:0] sext_ln1168_fu_274_p1;
wire  signed [50:0] sext_ln1171_fu_277_p1;
reg   [31:0] term_reg_447;
wire   [31:0] result_V_fu_300_p2;
reg   [31:0] result_V_reg_452;
reg    ap_enable_reg_pp0_iter0_reg;
wire   [63:0] zext_ln736_2_fu_257_p1;
wire    ap_block_pp0_stage1;
wire   [63:0] zext_ln736_fu_253_p1;
reg   [31:0] result_V_1_fu_74;
wire    ap_loop_init;
wire    ap_block_pp0_stage0;
reg   [2:0] j_fu_78;
reg   [2:0] ap_sig_allocacmp_j_load;
reg   [7:0] i_fu_82;
wire   [7:0] select_ln51_1_fu_195_p3;
reg   [7:0] ap_sig_allocacmp_i_load;
reg   [9:0] indvar_flatten_fu_86;
reg   [9:0] ap_sig_allocacmp_indvar_flatten_load;
wire    ap_block_pp0_stage1_01001;
wire   [8:0] j_2_cast_fu_230_p1;
wire   [8:0] p_mid2_fu_223_p3;
wire   [22:0] shl_ln737_2_fu_267_p3;
reg    ap_done_reg;
wire    ap_continue_int;
reg    ap_done_int;
reg    ap_loop_exit_ready_pp0_iter1_reg;
reg    ap_loop_exit_ready_pp0_iter2_reg;
reg    ap_loop_exit_ready_pp0_iter3_reg;
reg    ap_loop_exit_ready_pp0_iter4_reg;
reg    ap_loop_exit_ready_pp0_iter5_reg;
reg   [1:0] ap_NS_fsm;
wire    ap_block_pp0_stage0_subdone;
reg    ap_idle_pp0_1to6;
wire    ap_enable_pp0;
wire    ap_start_int;
wire    ap_ce_reg;

// power-on initialization
initial begin
#0 ap_CS_fsm = 2'd1;
#0 ap_enable_reg_pp0_iter1 = 1'b0;
#0 ap_enable_reg_pp0_iter2 = 1'b0;
#0 ap_enable_reg_pp0_iter3 = 1'b0;
#0 ap_enable_reg_pp0_iter4 = 1'b0;
#0 ap_enable_reg_pp0_iter5 = 1'b0;
#0 ap_enable_reg_pp0_iter6 = 1'b0;
#0 icmp_ln51_reg_342 = 1'd0;
#0 icmp_ln51_reg_342_pp0_iter1_reg = 1'd0;
#0 icmp_ln51_reg_342_pp0_iter2_reg = 1'd0;
#0 icmp_ln51_reg_342_pp0_iter3_reg = 1'd0;
#0 icmp_ln51_reg_342_pp0_iter4_reg = 1'd0;
#0 icmp_ln51_reg_342_pp0_iter5_reg = 1'd0;
#0 add_ln51_reg_346 = 10'd0;
#0 j_load_reg_351 = 3'd0;
#0 i_load_reg_356 = 8'd0;
#0 icmp_ln54_reg_361 = 1'd0;
#0 add_ln51_1_reg_367 = 8'd0;
#0 select_ln51_reg_372 = 3'd0;
#0 trunc_ln51_reg_377 = 7'd0;
#0 trunc_ln56_reg_382 = 1'd0;
#0 trunc_ln56_reg_382_pp0_iter1_reg = 1'd0;
#0 trunc_ln56_reg_382_pp0_iter2_reg = 1'd0;
#0 add_ln54_reg_387 = 3'd0;
#0 add_ln56_reg_392 = 9'd0;
#0 lshr_ln736_1_reg_397 = 8'd0;
#0 feature_V_1_load_reg_417 = 16'd0;
#0 feature_V_0_load_reg_422 = 16'd0;
#0 r_V_reg_427 = 32'd0;
#0 select_ln56_reg_432 = 16'd0;
#0 term_reg_447 = 32'd0;
#0 result_V_reg_452 = 32'd0;
#0 ap_enable_reg_pp0_iter0_reg = 1'b0;
#0 result_V_1_fu_74 = 32'd0;
#0 j_fu_78 = 3'd0;
#0 i_fu_82 = 8'd0;
#0 indvar_flatten_fu_86 = 10'd0;
#0 ap_done_reg = 1'b0;
#0 ap_loop_exit_ready_pp0_iter1_reg = 1'b0;
#0 ap_loop_exit_ready_pp0_iter2_reg = 1'b0;
#0 ap_loop_exit_ready_pp0_iter3_reg = 1'b0;
#0 ap_loop_exit_ready_pp0_iter4_reg = 1'b0;
#0 ap_loop_exit_ready_pp0_iter5_reg = 1'b0;
end

dotProduct_1_flow_control_loop_pipe_sequential_init flow_control_loop_pipe_sequential_init_U(
    .ap_clk(ap_clk),
    .ap_rst(ap_rst),
    .ap_start(ap_start),
    .ap_ready(ap_ready),
    .ap_done(ap_done),
    .ap_start_int(ap_start_int),
    .ap_loop_init(ap_loop_init),
    .ap_ready_int(ap_ready_int),
    .ap_loop_exit_ready(ap_condition_exit_pp0_iter0_stage1),
    .ap_loop_exit_done(ap_done_int),
    .ap_continue_int(ap_continue_int),
    .ap_done_int(ap_done_int)
);

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        add_ln51_1_reg_367 <= 8'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0) & (icmp_ln51_fu_159_p2 == 1'd0))) begin
            add_ln51_1_reg_367 <= add_ln51_1_fu_183_p2;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        add_ln51_reg_346 <= 10'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            add_ln51_reg_346 <= add_ln51_fu_165_p2;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        add_ln54_reg_387 <= 3'd0;
    end else begin
        if (((icmp_ln51_reg_342 == 1'd0) & (1'b0 == ap_block_pp0_stage1_11001) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
            add_ln54_reg_387 <= add_ln54_fu_208_p2;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        add_ln56_reg_392 <= 9'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            add_ln56_reg_392 <= add_ln56_fu_233_p2;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_CS_fsm <= ap_ST_fsm_pp0_stage0;
    end else begin
        ap_CS_fsm <= ap_NS_fsm;
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_done_reg <= 1'b0;
    end else begin
        if ((ap_continue_int == 1'b1)) begin
            ap_done_reg <= 1'b0;
        end else if (((1'b0 == ap_block_pp0_stage1_subdone) & (ap_loop_exit_ready_pp0_iter5_reg == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
            ap_done_reg <= 1'b1;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp0_iter0_reg <= 1'b0;
    end else begin
        if ((1'b1 == ap_CS_fsm_pp0_stage0)) begin
            ap_enable_reg_pp0_iter0_reg <= ap_start_int;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp0_iter1 <= 1'b0;
    end else begin
        if ((1'b1 == ap_condition_exit_pp0_iter0_stage1)) begin
            ap_enable_reg_pp0_iter1 <= 1'b0;
        end else if (((1'b0 == ap_block_pp0_stage1_subdone) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
            ap_enable_reg_pp0_iter1 <= ap_enable_reg_pp0_iter0;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp0_iter2 <= 1'b0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage1_subdone) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
            ap_enable_reg_pp0_iter2 <= ap_enable_reg_pp0_iter1;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp0_iter3 <= 1'b0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage1_subdone) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
            ap_enable_reg_pp0_iter3 <= ap_enable_reg_pp0_iter2;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp0_iter4 <= 1'b0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage1_subdone) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
            ap_enable_reg_pp0_iter4 <= ap_enable_reg_pp0_iter3;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp0_iter5 <= 1'b0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage1_subdone) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
            ap_enable_reg_pp0_iter5 <= ap_enable_reg_pp0_iter4;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp0_iter6 <= 1'b0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage1_subdone) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
            ap_enable_reg_pp0_iter6 <= ap_enable_reg_pp0_iter5;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_loop_exit_ready_pp0_iter1_reg <= 1'b0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage1_11001) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
            ap_loop_exit_ready_pp0_iter1_reg <= ap_loop_exit_ready;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_loop_exit_ready_pp0_iter2_reg <= 1'b0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage1_11001) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
            ap_loop_exit_ready_pp0_iter2_reg <= ap_loop_exit_ready_pp0_iter1_reg;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_loop_exit_ready_pp0_iter3_reg <= 1'b0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage1_11001) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
            ap_loop_exit_ready_pp0_iter3_reg <= ap_loop_exit_ready_pp0_iter2_reg;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_loop_exit_ready_pp0_iter4_reg <= 1'b0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage1_11001) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
            ap_loop_exit_ready_pp0_iter4_reg <= ap_loop_exit_ready_pp0_iter3_reg;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_loop_exit_ready_pp0_iter5_reg <= 1'b0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage1_11001) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
            ap_loop_exit_ready_pp0_iter5_reg <= ap_loop_exit_ready_pp0_iter4_reg;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        feature_V_0_load_reg_422 <= 16'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage1_11001) & (1'b1 == ap_CS_fsm_pp0_stage1) & (trunc_ln56_reg_382_pp0_iter1_reg == 1'd0))) begin
            feature_V_0_load_reg_422 <= feature_V_0_q0;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        feature_V_1_load_reg_417 <= 16'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage1_11001) & (1'b1 == ap_CS_fsm_pp0_stage1) & (trunc_ln56_reg_382_pp0_iter1_reg == 1'd1))) begin
            feature_V_1_load_reg_417 <= feature_V_1_q0;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        i_fu_82 <= 8'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0) & (ap_loop_init == 1'b1))) begin
            i_fu_82 <= 8'd0;
        end else if (((icmp_ln51_reg_342 == 1'd0) & (1'b0 == ap_block_pp0_stage1_11001) & (ap_enable_reg_pp0_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
            i_fu_82 <= select_ln51_1_fu_195_p3;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        i_load_reg_356 <= 8'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0) & (icmp_ln51_fu_159_p2 == 1'd0))) begin
            i_load_reg_356 <= ap_sig_allocacmp_i_load;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        icmp_ln51_reg_342 <= 1'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            icmp_ln51_reg_342 <= icmp_ln51_fu_159_p2;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        icmp_ln51_reg_342_pp0_iter1_reg <= 1'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            icmp_ln51_reg_342_pp0_iter1_reg <= icmp_ln51_reg_342;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        icmp_ln51_reg_342_pp0_iter2_reg <= 1'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            icmp_ln51_reg_342_pp0_iter2_reg <= icmp_ln51_reg_342_pp0_iter1_reg;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        icmp_ln51_reg_342_pp0_iter3_reg <= 1'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            icmp_ln51_reg_342_pp0_iter3_reg <= icmp_ln51_reg_342_pp0_iter2_reg;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        icmp_ln51_reg_342_pp0_iter4_reg <= 1'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            icmp_ln51_reg_342_pp0_iter4_reg <= icmp_ln51_reg_342_pp0_iter3_reg;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        icmp_ln51_reg_342_pp0_iter5_reg <= 1'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            icmp_ln51_reg_342_pp0_iter5_reg <= icmp_ln51_reg_342_pp0_iter4_reg;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        icmp_ln54_reg_361 <= 1'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0) & (icmp_ln51_fu_159_p2 == 1'd0))) begin
            icmp_ln54_reg_361 <= icmp_ln54_fu_177_p2;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        indvar_flatten_fu_86 <= 10'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0) & (ap_loop_init == 1'b1))) begin
            indvar_flatten_fu_86 <= 10'd0;
        end else if (((icmp_ln51_reg_342 == 1'd0) & (1'b0 == ap_block_pp0_stage1_11001) & (ap_enable_reg_pp0_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
            indvar_flatten_fu_86 <= add_ln51_reg_346;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        j_fu_78 <= 3'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            if ((ap_loop_init == 1'b1)) begin
                j_fu_78 <= 3'd0;
            end else if ((ap_enable_reg_pp0_iter1 == 1'b1)) begin
                j_fu_78 <= add_ln54_reg_387;
            end
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        j_load_reg_351 <= 3'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0) & (icmp_ln51_fu_159_p2 == 1'd0))) begin
            j_load_reg_351 <= ap_sig_allocacmp_j_load;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        lshr_ln736_1_reg_397 <= 8'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            lshr_ln736_1_reg_397 <= {{add_ln56_fu_233_p2[8:1]}};
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        r_V_reg_427 <= 32'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage1_11001) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
            r_V_reg_427 <= param_V_q0;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        result_V_1_fu_74 <= 32'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0) & (ap_loop_init == 1'b1))) begin
            result_V_1_fu_74 <= 32'd0;
        end else if (((1'b0 == ap_block_pp0_stage1_11001) & (ap_enable_reg_pp0_iter6 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
            result_V_1_fu_74 <= result_V_reg_452;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        result_V_reg_452 <= 32'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            result_V_reg_452 <= result_V_fu_300_p2;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        select_ln51_reg_372 <= 3'd0;
    end else begin
        if (((icmp_ln51_reg_342 == 1'd0) & (1'b0 == ap_block_pp0_stage1_11001) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
            select_ln51_reg_372 <= select_ln51_fu_189_p3;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        select_ln56_reg_432 <= 16'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            select_ln56_reg_432 <= select_ln56_fu_262_p3;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        term_reg_447 <= 32'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage1_11001) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
            term_reg_447 <= {{grp_fu_316_p_dout0[50:19]}};
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        trunc_ln51_reg_377 <= 7'd0;
    end else begin
        if (((icmp_ln51_reg_342 == 1'd0) & (1'b0 == ap_block_pp0_stage1_11001) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
            trunc_ln51_reg_377 <= trunc_ln51_fu_200_p1;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        trunc_ln56_reg_382 <= 1'd0;
    end else begin
        if (((icmp_ln51_reg_342 == 1'd0) & (1'b0 == ap_block_pp0_stage1_11001) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
            trunc_ln56_reg_382 <= trunc_ln56_fu_204_p1;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        trunc_ln56_reg_382_pp0_iter1_reg <= 1'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage1_11001) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
            trunc_ln56_reg_382_pp0_iter1_reg <= trunc_ln56_reg_382;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        trunc_ln56_reg_382_pp0_iter2_reg <= 1'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage1_11001) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
            trunc_ln56_reg_382_pp0_iter2_reg <= trunc_ln56_reg_382_pp0_iter1_reg;
        end
    end
end

always @ (*) begin
    if (((icmp_ln51_reg_342 == 1'd1) & (1'b0 == ap_block_pp0_stage1_subdone) & (ap_enable_reg_pp0_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
        ap_condition_exit_pp0_iter0_stage1 = 1'b1;
    end else begin
        ap_condition_exit_pp0_iter0_stage1 = 1'b0;
    end
end

always @ (*) begin
    if (((1'b0 == ap_block_pp0_stage1_subdone) & (ap_loop_exit_ready_pp0_iter5_reg == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
        ap_done_int = 1'b1;
    end else begin
        ap_done_int = ap_done_reg;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_pp0_stage0)) begin
        ap_enable_reg_pp0_iter0 = ap_start_int;
    end else begin
        ap_enable_reg_pp0_iter0 = ap_enable_reg_pp0_iter0_reg;
    end
end

always @ (*) begin
    if (((ap_idle_pp0 == 1'b1) & (ap_start_int == 1'b0) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
        ap_idle = 1'b1;
    end else begin
        ap_idle = 1'b0;
    end
end

always @ (*) begin
    if (((ap_enable_reg_pp0_iter6 == 1'b0) & (ap_enable_reg_pp0_iter5 == 1'b0) & (ap_enable_reg_pp0_iter4 == 1'b0) & (ap_enable_reg_pp0_iter3 == 1'b0) & (ap_enable_reg_pp0_iter2 == 1'b0) & (ap_enable_reg_pp0_iter1 == 1'b0) & (ap_enable_reg_pp0_iter0 == 1'b0))) begin
        ap_idle_pp0 = 1'b1;
    end else begin
        ap_idle_pp0 = 1'b0;
    end
end

always @ (*) begin
    if (((ap_enable_reg_pp0_iter6 == 1'b0) & (ap_enable_reg_pp0_iter5 == 1'b0) & (ap_enable_reg_pp0_iter4 == 1'b0) & (ap_enable_reg_pp0_iter3 == 1'b0) & (ap_enable_reg_pp0_iter2 == 1'b0) & (ap_enable_reg_pp0_iter1 == 1'b0))) begin
        ap_idle_pp0_1to6 = 1'b1;
    end else begin
        ap_idle_pp0_1to6 = 1'b0;
    end
end

always @ (*) begin
    if (((1'b0 == ap_block_pp0_stage1_subdone) & (ap_enable_reg_pp0_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
        ap_ready_int = 1'b1;
    end else begin
        ap_ready_int = 1'b0;
    end
end

always @ (*) begin
    if (((1'b0 == ap_block_pp0_stage0) & (1'b1 == ap_CS_fsm_pp0_stage0) & (ap_loop_init == 1'b1))) begin
        ap_sig_allocacmp_i_load = 8'd0;
    end else begin
        ap_sig_allocacmp_i_load = i_fu_82;
    end
end

always @ (*) begin
    if (((1'b0 == ap_block_pp0_stage0) & (1'b1 == ap_CS_fsm_pp0_stage0) & (ap_loop_init == 1'b1))) begin
        ap_sig_allocacmp_indvar_flatten_load = 10'd0;
    end else begin
        ap_sig_allocacmp_indvar_flatten_load = indvar_flatten_fu_86;
    end
end

always @ (*) begin
    if (((1'b0 == ap_block_pp0_stage0) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
        if ((ap_loop_init == 1'b1)) begin
            ap_sig_allocacmp_j_load = 3'd0;
        end else if ((ap_enable_reg_pp0_iter1 == 1'b1)) begin
            ap_sig_allocacmp_j_load = add_ln54_reg_387;
        end else begin
            ap_sig_allocacmp_j_load = j_fu_78;
        end
    end else begin
        ap_sig_allocacmp_j_load = j_fu_78;
    end
end

always @ (*) begin
    if ((((1'b0 == ap_block_pp0_stage1_11001) & (ap_enable_reg_pp0_iter2 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage1)) | ((1'b0 == ap_block_pp0_stage1_11001) & (ap_enable_reg_pp0_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage1)) | ((1'b0 == ap_block_pp0_stage0_11001) & (ap_enable_reg_pp0_iter2 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage0)))) begin
        feature_V_0_ce0 = 1'b1;
    end else begin
        feature_V_0_ce0 = 1'b0;
    end
end

always @ (*) begin
    if ((((1'b0 == ap_block_pp0_stage1_11001) & (ap_enable_reg_pp0_iter2 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage1)) | ((1'b0 == ap_block_pp0_stage1_11001) & (ap_enable_reg_pp0_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage1)) | ((1'b0 == ap_block_pp0_stage0_11001) & (ap_enable_reg_pp0_iter2 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage0)))) begin
        feature_V_1_ce0 = 1'b1;
    end else begin
        feature_V_1_ce0 = 1'b0;
    end
end

always @ (*) begin
    if ((((1'b0 == ap_block_pp0_stage1_11001) & (ap_enable_reg_pp0_iter2 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage1)) | ((1'b0 == ap_block_pp0_stage1_11001) & (ap_enable_reg_pp0_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage1)) | ((1'b0 == ap_block_pp0_stage0_11001) & (ap_enable_reg_pp0_iter2 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage0)))) begin
        param_V_ce0 = 1'b1;
    end else begin
        param_V_ce0 = 1'b0;
    end
end

always @ (*) begin
    if (((1'b0 == ap_block_pp0_stage1_11001) & (1'b1 == ap_CS_fsm_pp0_stage1) & (icmp_ln51_reg_342_pp0_iter5_reg == 1'd1))) begin
        result_V_1_out_ap_vld = 1'b1;
    end else begin
        result_V_1_out_ap_vld = 1'b0;
    end
end

always @ (*) begin
    case (ap_CS_fsm)
        ap_ST_fsm_pp0_stage0 : begin
            if ((~((ap_start_int == 1'b0) & (ap_idle_pp0_1to6 == 1'b1)) & (1'b0 == ap_block_pp0_stage0_subdone))) begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage1;
            end else begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage0;
            end
        end
        ap_ST_fsm_pp0_stage1 : begin
            if ((1'b0 == ap_block_pp0_stage1_subdone)) begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage0;
            end else begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage1;
            end
        end
        default : begin
            ap_NS_fsm = 'bx;
        end
    endcase
end

assign add_ln51_1_fu_183_p2 = (ap_sig_allocacmp_i_load + 8'd1);

assign add_ln51_fu_165_p2 = (ap_sig_allocacmp_indvar_flatten_load + 10'd1);

assign add_ln54_fu_208_p2 = (select_ln51_fu_189_p3 + 3'd1);

assign add_ln56_fu_233_p2 = (j_2_cast_fu_230_p1 + p_mid2_fu_223_p3);

assign ap_CS_fsm_pp0_stage0 = ap_CS_fsm[32'd0];

assign ap_CS_fsm_pp0_stage1 = ap_CS_fsm[32'd1];

assign ap_block_pp0_stage0 = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage0_11001 = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage0_subdone = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage1 = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage1_01001 = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage1_11001 = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage1_subdone = ~(1'b1 == 1'b1);

assign ap_block_state10_pp0_stage1_iter4 = ~(1'b1 == 1'b1);

assign ap_block_state11_pp0_stage0_iter5 = ~(1'b1 == 1'b1);

assign ap_block_state12_pp0_stage1_iter5 = ~(1'b1 == 1'b1);

assign ap_block_state13_pp0_stage0_iter6 = ~(1'b1 == 1'b1);

assign ap_block_state14_pp0_stage1_iter6 = ~(1'b1 == 1'b1);

assign ap_block_state1_pp0_stage0_iter0 = ~(1'b1 == 1'b1);

assign ap_block_state2_pp0_stage1_iter0 = ~(1'b1 == 1'b1);

assign ap_block_state3_pp0_stage0_iter1 = ~(1'b1 == 1'b1);

assign ap_block_state4_pp0_stage1_iter1 = ~(1'b1 == 1'b1);

assign ap_block_state5_pp0_stage0_iter2 = ~(1'b1 == 1'b1);

assign ap_block_state6_pp0_stage1_iter2 = ~(1'b1 == 1'b1);

assign ap_block_state7_pp0_stage0_iter3 = ~(1'b1 == 1'b1);

assign ap_block_state8_pp0_stage1_iter3 = ~(1'b1 == 1'b1);

assign ap_block_state9_pp0_stage0_iter4 = ~(1'b1 == 1'b1);

assign ap_enable_pp0 = (ap_idle_pp0 ^ 1'b1);

assign ap_loop_exit_ready = ap_condition_exit_pp0_iter0_stage1;

assign feature_V_0_address0 = zext_ln736_2_fu_257_p1;

assign feature_V_1_address0 = zext_ln736_2_fu_257_p1;

assign grp_fu_316_p_ce = 1'b1;

assign grp_fu_316_p_din0 = sext_ln1168_fu_274_p1;

assign grp_fu_316_p_din1 = sext_ln1171_fu_277_p1;

assign icmp_ln51_fu_159_p2 = ((ap_sig_allocacmp_indvar_flatten_load == 10'd512) ? 1'b1 : 1'b0);

assign icmp_ln54_fu_177_p2 = ((ap_sig_allocacmp_j_load == 3'd4) ? 1'b1 : 1'b0);

assign j_2_cast_fu_230_p1 = select_ln51_reg_372;

assign p_mid2_fu_223_p3 = {{trunc_ln51_reg_377}, {2'd0}};

assign param_V_address0 = zext_ln736_fu_253_p1;

assign result_V_1_out = result_V_1_fu_74;

assign result_V_fu_300_p2 = (term_reg_447 + result_V_1_fu_74);

assign select_ln51_1_fu_195_p3 = ((icmp_ln54_reg_361[0:0] == 1'b1) ? add_ln51_1_reg_367 : i_load_reg_356);

assign select_ln51_fu_189_p3 = ((icmp_ln54_reg_361[0:0] == 1'b1) ? 3'd0 : j_load_reg_351);

assign select_ln56_fu_262_p3 = ((trunc_ln56_reg_382_pp0_iter2_reg[0:0] == 1'b1) ? feature_V_1_load_reg_417 : feature_V_0_load_reg_422);

assign sext_ln1168_fu_274_p1 = $signed(r_V_reg_427);

assign sext_ln1171_fu_277_p1 = $signed(shl_ln737_2_fu_267_p3);

assign shl_ln737_2_fu_267_p3 = {{select_ln56_reg_432}, {7'd0}};

assign trunc_ln51_fu_200_p1 = select_ln51_1_fu_195_p3[6:0];

assign trunc_ln56_fu_204_p1 = select_ln51_fu_189_p3[0:0];

assign zext_ln736_2_fu_257_p1 = lshr_ln736_1_reg_397;

assign zext_ln736_fu_253_p1 = add_ln56_reg_392;

endmodule //dotProduct_1_dotProduct_1_Pipeline_DOT_DOT_INNER