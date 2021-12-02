// ==============================================================
// RTL generated by Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2021.1 (64-bit)
// Version: 2021.1
// Copyright (C) Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

`timescale 1 ns / 1 ps 

module dotProduct_1_dotProduct_1_Pipeline_GRAD_GRAD_INNER (
        ap_clk,
        ap_rst,
        ap_start,
        ap_done,
        ap_idle,
        ap_ready,
        sext_ln69,
        grad_V_address0,
        grad_V_ce0,
        grad_V_we0,
        grad_V_d0,
        feature_V_1_address0,
        feature_V_1_ce0,
        feature_V_1_q0,
        feature_V_0_address0,
        feature_V_0_ce0,
        feature_V_0_q0,
        grp_fu_320_p_din0,
        grp_fu_320_p_din1,
        grp_fu_320_p_dout0,
        grp_fu_320_p_ce
);

parameter    ap_ST_fsm_pp0_stage0 = 2'd1;
parameter    ap_ST_fsm_pp0_stage1 = 2'd2;

input   ap_clk;
input   ap_rst;
input   ap_start;
output   ap_done;
output   ap_idle;
output   ap_ready;
input  [31:0] sext_ln69;
output  [8:0] grad_V_address0;
output   grad_V_ce0;
output   grad_V_we0;
output  [31:0] grad_V_d0;
output  [7:0] feature_V_1_address0;
output   feature_V_1_ce0;
input  [15:0] feature_V_1_q0;
output  [7:0] feature_V_0_address0;
output   feature_V_0_ce0;
input  [15:0] feature_V_0_q0;
output  [22:0] grp_fu_320_p_din0;
output  [31:0] grp_fu_320_p_din1;
input  [50:0] grp_fu_320_p_dout0;
output   grp_fu_320_p_ce;

reg ap_idle;
reg grad_V_ce0;
reg grad_V_we0;
reg feature_V_1_ce0;
reg feature_V_0_ce0;

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
wire    ap_block_pp0_stage1_subdone;
reg   [0:0] icmp_ln69_reg_313;
reg    ap_condition_exit_pp0_iter0_stage1;
wire    ap_loop_exit_ready;
reg    ap_ready_int;
wire  signed [50:0] sext_ln69_cast_fu_131_p1;
reg  signed [50:0] sext_ln69_cast_reg_308;
wire    ap_block_state1_pp0_stage0_iter0;
wire    ap_block_state3_pp0_stage0_iter1;
wire    ap_block_state5_pp0_stage0_iter2;
wire    ap_block_state7_pp0_stage0_iter3;
wire    ap_block_state9_pp0_stage0_iter4;
wire    ap_block_state11_pp0_stage0_iter5;
wire    ap_block_state13_pp0_stage0_iter6;
wire    ap_block_pp0_stage0_11001;
wire   [0:0] icmp_ln69_fu_153_p2;
reg   [0:0] icmp_ln69_reg_313_pp0_iter1_reg;
reg   [0:0] icmp_ln69_reg_313_pp0_iter2_reg;
reg   [0:0] icmp_ln69_reg_313_pp0_iter3_reg;
reg   [0:0] icmp_ln69_reg_313_pp0_iter4_reg;
wire   [9:0] add_ln69_fu_159_p2;
reg   [9:0] add_ln69_reg_317;
reg   [2:0] j_load_reg_322;
reg   [7:0] i_load_reg_327;
wire   [0:0] icmp_ln72_fu_171_p2;
reg   [0:0] icmp_ln72_reg_332;
wire   [7:0] add_ln69_1_fu_177_p2;
reg   [7:0] add_ln69_1_reg_338;
wire   [2:0] select_ln69_fu_183_p3;
reg   [2:0] select_ln69_reg_343;
wire    ap_block_pp0_stage1_11001;
wire   [6:0] trunc_ln69_fu_194_p1;
reg   [6:0] trunc_ln69_reg_348;
wire   [0:0] trunc_ln73_fu_198_p1;
reg   [0:0] trunc_ln73_reg_353;
reg   [0:0] trunc_ln73_reg_353_pp0_iter1_reg;
reg   [0:0] trunc_ln73_reg_353_pp0_iter2_reg;
wire   [2:0] add_ln72_fu_202_p2;
reg   [2:0] add_ln72_reg_358;
wire   [8:0] add_ln73_fu_227_p2;
reg   [8:0] add_ln73_reg_363;
reg   [8:0] add_ln73_reg_363_pp0_iter2_reg;
reg   [8:0] add_ln73_reg_363_pp0_iter3_reg;
reg   [8:0] add_ln73_reg_363_pp0_iter4_reg;
reg   [8:0] add_ln73_reg_363_pp0_iter5_reg;
reg   [7:0] lshr_ln_reg_368;
reg   [15:0] feature_V_1_load_reg_383;
reg   [15:0] feature_V_0_load_reg_388;
wire   [15:0] select_ln73_fu_252_p3;
reg   [15:0] select_ln73_reg_393;
wire  signed [50:0] sext_ln1171_fu_264_p1;
reg   [31:0] trunc_ln1_reg_403;
reg    ap_enable_reg_pp0_iter0_reg;
wire    ap_block_pp0_stage0_subdone;
wire   [63:0] zext_ln736_1_fu_247_p1;
wire    ap_block_pp0_stage1;
wire   [63:0] zext_ln736_fu_283_p1;
wire    ap_block_pp0_stage0;
reg   [2:0] j_fu_74;
reg   [2:0] ap_sig_allocacmp_j_load;
wire    ap_loop_init;
reg   [7:0] i_fu_78;
wire   [7:0] select_ln69_1_fu_189_p3;
reg   [7:0] ap_sig_allocacmp_i_load;
reg   [9:0] indvar_flatten9_fu_82;
reg   [9:0] ap_sig_allocacmp_indvar_flatten9_load;
wire   [8:0] j_cast_fu_224_p1;
wire   [8:0] p_mid_fu_217_p3;
wire   [22:0] shl_ln737_1_fu_257_p3;
reg    ap_done_reg;
wire    ap_continue_int;
reg    ap_done_int;
reg    ap_loop_exit_ready_pp0_iter1_reg;
reg    ap_condition_exit_pp0_iter5_stage0;
reg    ap_idle_pp0_0to4;
reg    ap_loop_exit_ready_pp0_iter2_reg;
reg    ap_loop_exit_ready_pp0_iter3_reg;
reg    ap_loop_exit_ready_pp0_iter4_reg;
reg    ap_loop_exit_ready_pp0_iter5_reg;
reg   [1:0] ap_NS_fsm;
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
#0 icmp_ln69_reg_313 = 1'd0;
#0 sext_ln69_cast_reg_308 = 51'd0;
#0 icmp_ln69_reg_313_pp0_iter1_reg = 1'd0;
#0 icmp_ln69_reg_313_pp0_iter2_reg = 1'd0;
#0 icmp_ln69_reg_313_pp0_iter3_reg = 1'd0;
#0 icmp_ln69_reg_313_pp0_iter4_reg = 1'd0;
#0 add_ln69_reg_317 = 10'd0;
#0 j_load_reg_322 = 3'd0;
#0 i_load_reg_327 = 8'd0;
#0 icmp_ln72_reg_332 = 1'd0;
#0 add_ln69_1_reg_338 = 8'd0;
#0 select_ln69_reg_343 = 3'd0;
#0 trunc_ln69_reg_348 = 7'd0;
#0 trunc_ln73_reg_353 = 1'd0;
#0 trunc_ln73_reg_353_pp0_iter1_reg = 1'd0;
#0 trunc_ln73_reg_353_pp0_iter2_reg = 1'd0;
#0 add_ln72_reg_358 = 3'd0;
#0 add_ln73_reg_363 = 9'd0;
#0 add_ln73_reg_363_pp0_iter2_reg = 9'd0;
#0 add_ln73_reg_363_pp0_iter3_reg = 9'd0;
#0 add_ln73_reg_363_pp0_iter4_reg = 9'd0;
#0 add_ln73_reg_363_pp0_iter5_reg = 9'd0;
#0 lshr_ln_reg_368 = 8'd0;
#0 feature_V_1_load_reg_383 = 16'd0;
#0 feature_V_0_load_reg_388 = 16'd0;
#0 select_ln73_reg_393 = 16'd0;
#0 trunc_ln1_reg_403 = 32'd0;
#0 ap_enable_reg_pp0_iter0_reg = 1'b0;
#0 j_fu_74 = 3'd0;
#0 i_fu_78 = 8'd0;
#0 indvar_flatten9_fu_82 = 10'd0;
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
        add_ln69_1_reg_338 <= 8'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0) & (icmp_ln69_fu_153_p2 == 1'd0))) begin
            add_ln69_1_reg_338 <= add_ln69_1_fu_177_p2;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        add_ln69_reg_317 <= 10'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            add_ln69_reg_317 <= add_ln69_fu_159_p2;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        add_ln72_reg_358 <= 3'd0;
    end else begin
        if (((icmp_ln69_reg_313 == 1'd0) & (1'b0 == ap_block_pp0_stage1_11001) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
            add_ln72_reg_358 <= add_ln72_fu_202_p2;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        add_ln73_reg_363 <= 9'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            add_ln73_reg_363 <= add_ln73_fu_227_p2;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        add_ln73_reg_363_pp0_iter2_reg <= 9'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            add_ln73_reg_363_pp0_iter2_reg <= add_ln73_reg_363;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        add_ln73_reg_363_pp0_iter3_reg <= 9'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            add_ln73_reg_363_pp0_iter3_reg <= add_ln73_reg_363_pp0_iter2_reg;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        add_ln73_reg_363_pp0_iter4_reg <= 9'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            add_ln73_reg_363_pp0_iter4_reg <= add_ln73_reg_363_pp0_iter3_reg;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        add_ln73_reg_363_pp0_iter5_reg <= 9'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            add_ln73_reg_363_pp0_iter5_reg <= add_ln73_reg_363_pp0_iter4_reg;
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
        end else if (((1'b0 == ap_block_pp0_stage0_subdone) & (ap_loop_exit_ready_pp0_iter5_reg == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
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
        if (((1'b0 == ap_block_pp0_stage0_subdone) & (ap_enable_reg_pp0_iter6 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            ap_enable_reg_pp0_iter6 <= 1'b0;
        end else if (((1'b0 == ap_block_pp0_stage1_subdone) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
            ap_enable_reg_pp0_iter6 <= ap_enable_reg_pp0_iter5;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_loop_exit_ready_pp0_iter1_reg <= 1'b0;
    end else begin
        if (((ap_idle_pp0_0to4 == 1'b1) & (1'b1 == ap_condition_exit_pp0_iter5_stage0))) begin
            ap_loop_exit_ready_pp0_iter1_reg <= 1'b0;
        end else if (((1'b0 == ap_block_pp0_stage1_11001) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
            ap_loop_exit_ready_pp0_iter1_reg <= ap_loop_exit_ready;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_loop_exit_ready_pp0_iter2_reg <= 1'b0;
    end else begin
        if (((ap_idle_pp0_0to4 == 1'b1) & (1'b1 == ap_condition_exit_pp0_iter5_stage0))) begin
            ap_loop_exit_ready_pp0_iter2_reg <= 1'b0;
        end else if (((1'b0 == ap_block_pp0_stage1_11001) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
            ap_loop_exit_ready_pp0_iter2_reg <= ap_loop_exit_ready_pp0_iter1_reg;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_loop_exit_ready_pp0_iter3_reg <= 1'b0;
    end else begin
        if (((ap_idle_pp0_0to4 == 1'b1) & (1'b1 == ap_condition_exit_pp0_iter5_stage0))) begin
            ap_loop_exit_ready_pp0_iter3_reg <= 1'b0;
        end else if (((1'b0 == ap_block_pp0_stage1_11001) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
            ap_loop_exit_ready_pp0_iter3_reg <= ap_loop_exit_ready_pp0_iter2_reg;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_loop_exit_ready_pp0_iter4_reg <= 1'b0;
    end else begin
        if (((ap_idle_pp0_0to4 == 1'b1) & (1'b1 == ap_condition_exit_pp0_iter5_stage0))) begin
            ap_loop_exit_ready_pp0_iter4_reg <= 1'b0;
        end else if (((1'b0 == ap_block_pp0_stage1_11001) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
            ap_loop_exit_ready_pp0_iter4_reg <= ap_loop_exit_ready_pp0_iter3_reg;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_loop_exit_ready_pp0_iter5_reg <= 1'b0;
    end else begin
        if (((ap_idle_pp0_0to4 == 1'b1) & (1'b1 == ap_condition_exit_pp0_iter5_stage0))) begin
            ap_loop_exit_ready_pp0_iter5_reg <= 1'b0;
        end else if (((1'b0 == ap_block_pp0_stage1_11001) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
            ap_loop_exit_ready_pp0_iter5_reg <= ap_loop_exit_ready_pp0_iter4_reg;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        feature_V_0_load_reg_388 <= 16'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage1_11001) & (1'b1 == ap_CS_fsm_pp0_stage1) & (trunc_ln73_reg_353_pp0_iter1_reg == 1'd0))) begin
            feature_V_0_load_reg_388 <= feature_V_0_q0;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        feature_V_1_load_reg_383 <= 16'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage1_11001) & (1'b1 == ap_CS_fsm_pp0_stage1) & (trunc_ln73_reg_353_pp0_iter1_reg == 1'd1))) begin
            feature_V_1_load_reg_383 <= feature_V_1_q0;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        i_fu_78 <= 8'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (ap_loop_init == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            i_fu_78 <= 8'd0;
        end else if (((icmp_ln69_reg_313 == 1'd0) & (1'b0 == ap_block_pp0_stage1_11001) & (ap_enable_reg_pp0_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
            i_fu_78 <= select_ln69_1_fu_189_p3;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        i_load_reg_327 <= 8'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0) & (icmp_ln69_fu_153_p2 == 1'd0))) begin
            i_load_reg_327 <= ap_sig_allocacmp_i_load;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        icmp_ln69_reg_313 <= 1'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            icmp_ln69_reg_313 <= icmp_ln69_fu_153_p2;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        icmp_ln69_reg_313_pp0_iter1_reg <= 1'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            icmp_ln69_reg_313_pp0_iter1_reg <= icmp_ln69_reg_313;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        icmp_ln69_reg_313_pp0_iter2_reg <= 1'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            icmp_ln69_reg_313_pp0_iter2_reg <= icmp_ln69_reg_313_pp0_iter1_reg;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        icmp_ln69_reg_313_pp0_iter3_reg <= 1'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            icmp_ln69_reg_313_pp0_iter3_reg <= icmp_ln69_reg_313_pp0_iter2_reg;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        icmp_ln69_reg_313_pp0_iter4_reg <= 1'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            icmp_ln69_reg_313_pp0_iter4_reg <= icmp_ln69_reg_313_pp0_iter3_reg;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        icmp_ln72_reg_332 <= 1'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0) & (icmp_ln69_fu_153_p2 == 1'd0))) begin
            icmp_ln72_reg_332 <= icmp_ln72_fu_171_p2;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        indvar_flatten9_fu_82 <= 10'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (ap_loop_init == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            indvar_flatten9_fu_82 <= 10'd0;
        end else if (((icmp_ln69_reg_313 == 1'd0) & (1'b0 == ap_block_pp0_stage1_11001) & (ap_enable_reg_pp0_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
            indvar_flatten9_fu_82 <= add_ln69_reg_317;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        j_fu_74 <= 3'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            if ((ap_loop_init == 1'b1)) begin
                j_fu_74 <= 3'd0;
            end else if ((ap_enable_reg_pp0_iter1 == 1'b1)) begin
                j_fu_74 <= add_ln72_reg_358;
            end
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        j_load_reg_322 <= 3'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0) & (icmp_ln69_fu_153_p2 == 1'd0))) begin
            j_load_reg_322 <= ap_sig_allocacmp_j_load;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        lshr_ln_reg_368 <= 8'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            lshr_ln_reg_368 <= {{add_ln73_fu_227_p2[8:1]}};
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        select_ln69_reg_343 <= 3'd0;
    end else begin
        if (((icmp_ln69_reg_313 == 1'd0) & (1'b0 == ap_block_pp0_stage1_11001) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
            select_ln69_reg_343 <= select_ln69_fu_183_p3;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        select_ln73_reg_393 <= 16'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            select_ln73_reg_393 <= select_ln73_fu_252_p3;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        sext_ln69_cast_reg_308 <= 51'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            sext_ln69_cast_reg_308 <= sext_ln69_cast_fu_131_p1;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        trunc_ln1_reg_403 <= 32'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage1_11001) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
            trunc_ln1_reg_403 <= {{grp_fu_320_p_dout0[50:19]}};
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        trunc_ln69_reg_348 <= 7'd0;
    end else begin
        if (((icmp_ln69_reg_313 == 1'd0) & (1'b0 == ap_block_pp0_stage1_11001) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
            trunc_ln69_reg_348 <= trunc_ln69_fu_194_p1;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        trunc_ln73_reg_353 <= 1'd0;
    end else begin
        if (((icmp_ln69_reg_313 == 1'd0) & (1'b0 == ap_block_pp0_stage1_11001) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
            trunc_ln73_reg_353 <= trunc_ln73_fu_198_p1;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        trunc_ln73_reg_353_pp0_iter1_reg <= 1'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage1_11001) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
            trunc_ln73_reg_353_pp0_iter1_reg <= trunc_ln73_reg_353;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        trunc_ln73_reg_353_pp0_iter2_reg <= 1'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage1_11001) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
            trunc_ln73_reg_353_pp0_iter2_reg <= trunc_ln73_reg_353_pp0_iter1_reg;
        end
    end
end

always @ (*) begin
    if (((icmp_ln69_reg_313 == 1'd1) & (1'b0 == ap_block_pp0_stage1_subdone) & (ap_enable_reg_pp0_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
        ap_condition_exit_pp0_iter0_stage1 = 1'b1;
    end else begin
        ap_condition_exit_pp0_iter0_stage1 = 1'b0;
    end
end

always @ (*) begin
    if (((1'b0 == ap_block_pp0_stage0_subdone) & (ap_enable_reg_pp0_iter5 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage0) & (icmp_ln69_reg_313_pp0_iter4_reg == 1'd1))) begin
        ap_condition_exit_pp0_iter5_stage0 = 1'b1;
    end else begin
        ap_condition_exit_pp0_iter5_stage0 = 1'b0;
    end
end

always @ (*) begin
    if (((1'b0 == ap_block_pp0_stage0_subdone) & (ap_loop_exit_ready_pp0_iter5_reg == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
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
    if (((ap_enable_reg_pp0_iter4 == 1'b0) & (ap_enable_reg_pp0_iter3 == 1'b0) & (ap_enable_reg_pp0_iter2 == 1'b0) & (ap_enable_reg_pp0_iter1 == 1'b0) & (ap_enable_reg_pp0_iter0 == 1'b0))) begin
        ap_idle_pp0_0to4 = 1'b1;
    end else begin
        ap_idle_pp0_0to4 = 1'b0;
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
    if (((1'b0 == ap_block_pp0_stage0) & (ap_loop_init == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
        ap_sig_allocacmp_i_load = 8'd0;
    end else begin
        ap_sig_allocacmp_i_load = i_fu_78;
    end
end

always @ (*) begin
    if (((1'b0 == ap_block_pp0_stage0) & (ap_loop_init == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
        ap_sig_allocacmp_indvar_flatten9_load = 10'd0;
    end else begin
        ap_sig_allocacmp_indvar_flatten9_load = indvar_flatten9_fu_82;
    end
end

always @ (*) begin
    if (((1'b0 == ap_block_pp0_stage0) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
        if ((ap_loop_init == 1'b1)) begin
            ap_sig_allocacmp_j_load = 3'd0;
        end else if ((ap_enable_reg_pp0_iter1 == 1'b1)) begin
            ap_sig_allocacmp_j_load = add_ln72_reg_358;
        end else begin
            ap_sig_allocacmp_j_load = j_fu_74;
        end
    end else begin
        ap_sig_allocacmp_j_load = j_fu_74;
    end
end

always @ (*) begin
    if ((((1'b0 == ap_block_pp0_stage0_11001) & (ap_enable_reg_pp0_iter2 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage0)) | ((1'b0 == ap_block_pp0_stage1_11001) & (ap_enable_reg_pp0_iter2 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage1)) | ((1'b0 == ap_block_pp0_stage1_11001) & (ap_enable_reg_pp0_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage1)))) begin
        feature_V_0_ce0 = 1'b1;
    end else begin
        feature_V_0_ce0 = 1'b0;
    end
end

always @ (*) begin
    if ((((1'b0 == ap_block_pp0_stage0_11001) & (ap_enable_reg_pp0_iter2 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage0)) | ((1'b0 == ap_block_pp0_stage1_11001) & (ap_enable_reg_pp0_iter2 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage1)) | ((1'b0 == ap_block_pp0_stage1_11001) & (ap_enable_reg_pp0_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage1)))) begin
        feature_V_1_ce0 = 1'b1;
    end else begin
        feature_V_1_ce0 = 1'b0;
    end
end

always @ (*) begin
    if (((1'b0 == ap_block_pp0_stage0_11001) & (ap_enable_reg_pp0_iter6 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
        grad_V_ce0 = 1'b1;
    end else begin
        grad_V_ce0 = 1'b0;
    end
end

always @ (*) begin
    if (((1'b0 == ap_block_pp0_stage0_11001) & (ap_enable_reg_pp0_iter6 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
        grad_V_we0 = 1'b1;
    end else begin
        grad_V_we0 = 1'b0;
    end
end

always @ (*) begin
    case (ap_CS_fsm)
        ap_ST_fsm_pp0_stage0 : begin
            if (((ap_idle_pp0_0to4 == 1'b1) & (1'b1 == ap_condition_exit_pp0_iter5_stage0))) begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage0;
            end else if ((~((ap_start_int == 1'b0) & (ap_idle_pp0_1to6 == 1'b1)) & (1'b0 == ap_block_pp0_stage0_subdone))) begin
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

assign add_ln69_1_fu_177_p2 = (ap_sig_allocacmp_i_load + 8'd1);

assign add_ln69_fu_159_p2 = (ap_sig_allocacmp_indvar_flatten9_load + 10'd1);

assign add_ln72_fu_202_p2 = (select_ln69_fu_183_p3 + 3'd1);

assign add_ln73_fu_227_p2 = (j_cast_fu_224_p1 + p_mid_fu_217_p3);

assign ap_CS_fsm_pp0_stage0 = ap_CS_fsm[32'd0];

assign ap_CS_fsm_pp0_stage1 = ap_CS_fsm[32'd1];

assign ap_block_pp0_stage0 = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage0_11001 = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage0_subdone = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage1 = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage1_11001 = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage1_subdone = ~(1'b1 == 1'b1);

assign ap_block_state10_pp0_stage1_iter4 = ~(1'b1 == 1'b1);

assign ap_block_state11_pp0_stage0_iter5 = ~(1'b1 == 1'b1);

assign ap_block_state12_pp0_stage1_iter5 = ~(1'b1 == 1'b1);

assign ap_block_state13_pp0_stage0_iter6 = ~(1'b1 == 1'b1);

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

assign feature_V_0_address0 = zext_ln736_1_fu_247_p1;

assign feature_V_1_address0 = zext_ln736_1_fu_247_p1;

assign grad_V_address0 = zext_ln736_fu_283_p1;

assign grad_V_d0 = trunc_ln1_reg_403;

assign grp_fu_320_p_ce = 1'b1;

assign grp_fu_320_p_din0 = sext_ln1171_fu_264_p1;

assign grp_fu_320_p_din1 = sext_ln69_cast_reg_308;

assign icmp_ln69_fu_153_p2 = ((ap_sig_allocacmp_indvar_flatten9_load == 10'd512) ? 1'b1 : 1'b0);

assign icmp_ln72_fu_171_p2 = ((ap_sig_allocacmp_j_load == 3'd4) ? 1'b1 : 1'b0);

assign j_cast_fu_224_p1 = select_ln69_reg_343;

assign p_mid_fu_217_p3 = {{trunc_ln69_reg_348}, {2'd0}};

assign select_ln69_1_fu_189_p3 = ((icmp_ln72_reg_332[0:0] == 1'b1) ? add_ln69_1_reg_338 : i_load_reg_327);

assign select_ln69_fu_183_p3 = ((icmp_ln72_reg_332[0:0] == 1'b1) ? 3'd0 : j_load_reg_322);

assign select_ln73_fu_252_p3 = ((trunc_ln73_reg_353_pp0_iter2_reg[0:0] == 1'b1) ? feature_V_1_load_reg_383 : feature_V_0_load_reg_388);

assign sext_ln1171_fu_264_p1 = $signed(shl_ln737_1_fu_257_p3);

assign sext_ln69_cast_fu_131_p1 = $signed(sext_ln69);

assign shl_ln737_1_fu_257_p3 = {{select_ln73_reg_393}, {7'd0}};

assign trunc_ln69_fu_194_p1 = select_ln69_1_fu_189_p3[6:0];

assign trunc_ln73_fu_198_p1 = select_ln69_fu_183_p3[0:0];

assign zext_ln736_1_fu_247_p1 = lshr_ln_reg_368;

assign zext_ln736_fu_283_p1 = add_ln73_reg_363_pp0_iter5_reg;

endmodule //dotProduct_1_dotProduct_1_Pipeline_GRAD_GRAD_INNER
