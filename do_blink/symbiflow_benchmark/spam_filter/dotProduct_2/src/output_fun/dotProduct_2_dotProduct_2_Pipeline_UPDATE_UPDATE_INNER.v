// ==============================================================
// RTL generated by Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2021.1 (64-bit)
// Version: 2021.1
// Copyright (C) Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

`timescale 1 ns / 1 ps 

module dotProduct_2_dotProduct_2_Pipeline_UPDATE_UPDATE_INNER (
        ap_clk,
        ap_rst,
        ap_start,
        ap_done,
        ap_idle,
        ap_ready,
        grad_V_address0,
        grad_V_ce0,
        grad_V_q0,
        param_V_address0,
        param_V_ce0,
        param_V_we0,
        param_V_d0,
        param_V_q0,
        grp_fu_324_p_din0,
        grp_fu_324_p_din1,
        grp_fu_324_p_dout0,
        grp_fu_324_p_ce
);

parameter    ap_ST_fsm_pp0_stage0 = 2'd1;
parameter    ap_ST_fsm_pp0_stage1 = 2'd2;

input   ap_clk;
input   ap_rst;
input   ap_start;
output   ap_done;
output   ap_idle;
output   ap_ready;
output  [8:0] grad_V_address0;
output   grad_V_ce0;
input  [31:0] grad_V_q0;
output  [8:0] param_V_address0;
output   param_V_ce0;
output   param_V_we0;
output  [31:0] param_V_d0;
input  [31:0] param_V_q0;
output  [31:0] grp_fu_324_p_din0;
output  [31:0] grp_fu_324_p_din1;
input  [50:0] grp_fu_324_p_dout0;
output   grp_fu_324_p_ce;

reg ap_idle;
reg grad_V_ce0;
reg[8:0] param_V_address0;
reg param_V_ce0;
reg param_V_we0;

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
reg   [0:0] icmp_ln77_reg_246;
reg    ap_condition_exit_pp0_iter0_stage1;
wire    ap_loop_exit_ready;
reg    ap_ready_int;
wire   [0:0] icmp_ln77_fu_117_p2;
wire    ap_block_state1_pp0_stage0_iter0;
wire    ap_block_state3_pp0_stage0_iter1;
wire    ap_block_state5_pp0_stage0_iter2;
wire    ap_block_state7_pp0_stage0_iter3;
wire    ap_block_state9_pp0_stage0_iter4;
wire    ap_block_state11_pp0_stage0_iter5;
wire    ap_block_state13_pp0_stage0_iter6;
wire    ap_block_pp0_stage0_11001;
reg   [0:0] icmp_ln77_reg_246_pp0_iter1_reg;
reg   [0:0] icmp_ln77_reg_246_pp0_iter2_reg;
reg   [0:0] icmp_ln77_reg_246_pp0_iter3_reg;
reg   [0:0] icmp_ln77_reg_246_pp0_iter4_reg;
wire   [9:0] add_ln77_fu_123_p2;
reg   [9:0] add_ln77_reg_250;
reg   [2:0] j_load_reg_255;
reg   [7:0] i_load_reg_260;
wire   [0:0] icmp_ln80_fu_135_p2;
reg   [0:0] icmp_ln80_reg_265;
wire   [7:0] add_ln77_1_fu_141_p2;
reg   [7:0] add_ln77_1_reg_271;
wire   [2:0] select_ln77_fu_147_p3;
reg   [2:0] select_ln77_reg_276;
wire    ap_block_pp0_stage1_11001;
wire   [6:0] trunc_ln77_fu_158_p1;
reg   [6:0] trunc_ln77_reg_281;
wire   [2:0] add_ln80_fu_162_p2;
reg   [2:0] add_ln80_reg_286;
wire   [8:0] add_ln82_fu_187_p2;
reg   [8:0] add_ln82_reg_291;
reg   [8:0] param_V_addr_reg_301;
reg   [8:0] param_V_addr_reg_301_pp0_iter2_reg;
reg   [8:0] param_V_addr_reg_301_pp0_iter3_reg;
reg   [8:0] param_V_addr_reg_301_pp0_iter4_reg;
reg   [8:0] param_V_addr_reg_301_pp0_iter5_reg;
reg   [31:0] grad_V_load_reg_306;
wire  signed [50:0] sext_ln1171_fu_202_p1;
reg   [31:0] param_V_load_reg_316;
reg   [31:0] tmp_V_reg_321;
wire   [31:0] add_ln712_fu_221_p2;
reg   [31:0] add_ln712_reg_326;
reg    ap_enable_reg_pp0_iter0_reg;
wire    ap_block_pp0_stage0_subdone;
wire   [63:0] zext_ln1171_fu_197_p1;
wire    ap_block_pp0_stage1;
reg   [2:0] j_fu_62;
reg   [2:0] ap_sig_allocacmp_j_load;
wire    ap_block_pp0_stage0;
wire    ap_loop_init;
reg   [7:0] i_fu_66;
wire   [7:0] select_ln77_1_fu_153_p3;
reg   [7:0] ap_sig_allocacmp_i_load;
reg   [9:0] indvar_flatten19_fu_70;
reg   [9:0] ap_sig_allocacmp_indvar_flatten19_load;
wire   [8:0] j_1_cast_fu_184_p1;
wire   [8:0] p_mid1_fu_177_p3;
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
#0 icmp_ln77_reg_246 = 1'd0;
#0 icmp_ln77_reg_246_pp0_iter1_reg = 1'd0;
#0 icmp_ln77_reg_246_pp0_iter2_reg = 1'd0;
#0 icmp_ln77_reg_246_pp0_iter3_reg = 1'd0;
#0 icmp_ln77_reg_246_pp0_iter4_reg = 1'd0;
#0 add_ln77_reg_250 = 10'd0;
#0 j_load_reg_255 = 3'd0;
#0 i_load_reg_260 = 8'd0;
#0 icmp_ln80_reg_265 = 1'd0;
#0 add_ln77_1_reg_271 = 8'd0;
#0 select_ln77_reg_276 = 3'd0;
#0 trunc_ln77_reg_281 = 7'd0;
#0 add_ln80_reg_286 = 3'd0;
#0 add_ln82_reg_291 = 9'd0;
#0 param_V_addr_reg_301 = 9'd0;
#0 param_V_addr_reg_301_pp0_iter2_reg = 9'd0;
#0 param_V_addr_reg_301_pp0_iter3_reg = 9'd0;
#0 param_V_addr_reg_301_pp0_iter4_reg = 9'd0;
#0 param_V_addr_reg_301_pp0_iter5_reg = 9'd0;
#0 grad_V_load_reg_306 = 32'd0;
#0 param_V_load_reg_316 = 32'd0;
#0 tmp_V_reg_321 = 32'd0;
#0 add_ln712_reg_326 = 32'd0;
#0 ap_enable_reg_pp0_iter0_reg = 1'b0;
#0 j_fu_62 = 3'd0;
#0 i_fu_66 = 8'd0;
#0 indvar_flatten19_fu_70 = 10'd0;
#0 ap_done_reg = 1'b0;
#0 ap_loop_exit_ready_pp0_iter1_reg = 1'b0;
#0 ap_loop_exit_ready_pp0_iter2_reg = 1'b0;
#0 ap_loop_exit_ready_pp0_iter3_reg = 1'b0;
#0 ap_loop_exit_ready_pp0_iter4_reg = 1'b0;
#0 ap_loop_exit_ready_pp0_iter5_reg = 1'b0;
end

dotProduct_2_flow_control_loop_pipe_sequential_init flow_control_loop_pipe_sequential_init_U(
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
        add_ln712_reg_326 <= 32'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage1_11001) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
            add_ln712_reg_326 <= add_ln712_fu_221_p2;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        add_ln77_1_reg_271 <= 8'd0;
    end else begin
        if (((icmp_ln77_fu_117_p2 == 1'd0) & (1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            add_ln77_1_reg_271 <= add_ln77_1_fu_141_p2;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        add_ln77_reg_250 <= 10'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            add_ln77_reg_250 <= add_ln77_fu_123_p2;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        add_ln80_reg_286 <= 3'd0;
    end else begin
        if (((icmp_ln77_reg_246 == 1'd0) & (1'b0 == ap_block_pp0_stage1_11001) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
            add_ln80_reg_286 <= add_ln80_fu_162_p2;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        add_ln82_reg_291 <= 9'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            add_ln82_reg_291 <= add_ln82_fu_187_p2;
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
        grad_V_load_reg_306 <= 32'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage1_11001) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
            grad_V_load_reg_306 <= grad_V_q0;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        i_fu_66 <= 8'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0) & (ap_loop_init == 1'b1))) begin
            i_fu_66 <= 8'd0;
        end else if (((icmp_ln77_reg_246 == 1'd0) & (1'b0 == ap_block_pp0_stage1_11001) & (ap_enable_reg_pp0_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
            i_fu_66 <= select_ln77_1_fu_153_p3;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        i_load_reg_260 <= 8'd0;
    end else begin
        if (((icmp_ln77_fu_117_p2 == 1'd0) & (1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            i_load_reg_260 <= ap_sig_allocacmp_i_load;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        icmp_ln77_reg_246 <= 1'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            icmp_ln77_reg_246 <= icmp_ln77_fu_117_p2;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        icmp_ln77_reg_246_pp0_iter1_reg <= 1'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            icmp_ln77_reg_246_pp0_iter1_reg <= icmp_ln77_reg_246;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        icmp_ln77_reg_246_pp0_iter2_reg <= 1'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            icmp_ln77_reg_246_pp0_iter2_reg <= icmp_ln77_reg_246_pp0_iter1_reg;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        icmp_ln77_reg_246_pp0_iter3_reg <= 1'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            icmp_ln77_reg_246_pp0_iter3_reg <= icmp_ln77_reg_246_pp0_iter2_reg;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        icmp_ln77_reg_246_pp0_iter4_reg <= 1'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            icmp_ln77_reg_246_pp0_iter4_reg <= icmp_ln77_reg_246_pp0_iter3_reg;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        icmp_ln80_reg_265 <= 1'd0;
    end else begin
        if (((icmp_ln77_fu_117_p2 == 1'd0) & (1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            icmp_ln80_reg_265 <= icmp_ln80_fu_135_p2;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        indvar_flatten19_fu_70 <= 10'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0) & (ap_loop_init == 1'b1))) begin
            indvar_flatten19_fu_70 <= 10'd0;
        end else if (((icmp_ln77_reg_246 == 1'd0) & (1'b0 == ap_block_pp0_stage1_11001) & (ap_enable_reg_pp0_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
            indvar_flatten19_fu_70 <= add_ln77_reg_250;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        j_fu_62 <= 3'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            if ((ap_loop_init == 1'b1)) begin
                j_fu_62 <= 3'd0;
            end else if ((ap_enable_reg_pp0_iter1 == 1'b1)) begin
                j_fu_62 <= add_ln80_reg_286;
            end
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        j_load_reg_255 <= 3'd0;
    end else begin
        if (((icmp_ln77_fu_117_p2 == 1'd0) & (1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            j_load_reg_255 <= ap_sig_allocacmp_j_load;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        param_V_addr_reg_301 <= 9'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage1_11001) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
            param_V_addr_reg_301 <= zext_ln1171_fu_197_p1;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        param_V_addr_reg_301_pp0_iter2_reg <= 9'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage1_11001) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
            param_V_addr_reg_301_pp0_iter2_reg <= param_V_addr_reg_301;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        param_V_addr_reg_301_pp0_iter3_reg <= 9'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage1_11001) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
            param_V_addr_reg_301_pp0_iter3_reg <= param_V_addr_reg_301_pp0_iter2_reg;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        param_V_addr_reg_301_pp0_iter4_reg <= 9'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage1_11001) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
            param_V_addr_reg_301_pp0_iter4_reg <= param_V_addr_reg_301_pp0_iter3_reg;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        param_V_addr_reg_301_pp0_iter5_reg <= 9'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage1_11001) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
            param_V_addr_reg_301_pp0_iter5_reg <= param_V_addr_reg_301_pp0_iter4_reg;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        param_V_load_reg_316 <= 32'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage1_11001) & (ap_enable_reg_pp0_iter4 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
            param_V_load_reg_316 <= param_V_q0;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        select_ln77_reg_276 <= 3'd0;
    end else begin
        if (((icmp_ln77_reg_246 == 1'd0) & (1'b0 == ap_block_pp0_stage1_11001) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
            select_ln77_reg_276 <= select_ln77_fu_147_p3;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        tmp_V_reg_321 <= 32'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            tmp_V_reg_321 <= {{grp_fu_324_p_dout0[50:19]}};
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        trunc_ln77_reg_281 <= 7'd0;
    end else begin
        if (((icmp_ln77_reg_246 == 1'd0) & (1'b0 == ap_block_pp0_stage1_11001) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
            trunc_ln77_reg_281 <= trunc_ln77_fu_158_p1;
        end
    end
end

always @ (*) begin
    if (((icmp_ln77_reg_246 == 1'd1) & (1'b0 == ap_block_pp0_stage1_subdone) & (ap_enable_reg_pp0_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
        ap_condition_exit_pp0_iter0_stage1 = 1'b1;
    end else begin
        ap_condition_exit_pp0_iter0_stage1 = 1'b0;
    end
end

always @ (*) begin
    if (((icmp_ln77_reg_246_pp0_iter4_reg == 1'd1) & (1'b0 == ap_block_pp0_stage0_subdone) & (ap_enable_reg_pp0_iter5 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
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
    if (((1'b0 == ap_block_pp0_stage0) & (1'b1 == ap_CS_fsm_pp0_stage0) & (ap_loop_init == 1'b1))) begin
        ap_sig_allocacmp_i_load = 8'd0;
    end else begin
        ap_sig_allocacmp_i_load = i_fu_66;
    end
end

always @ (*) begin
    if (((1'b0 == ap_block_pp0_stage0) & (1'b1 == ap_CS_fsm_pp0_stage0) & (ap_loop_init == 1'b1))) begin
        ap_sig_allocacmp_indvar_flatten19_load = 10'd0;
    end else begin
        ap_sig_allocacmp_indvar_flatten19_load = indvar_flatten19_fu_70;
    end
end

always @ (*) begin
    if (((1'b0 == ap_block_pp0_stage0) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
        if ((ap_loop_init == 1'b1)) begin
            ap_sig_allocacmp_j_load = 3'd0;
        end else if ((ap_enable_reg_pp0_iter1 == 1'b1)) begin
            ap_sig_allocacmp_j_load = add_ln80_reg_286;
        end else begin
            ap_sig_allocacmp_j_load = j_fu_62;
        end
    end else begin
        ap_sig_allocacmp_j_load = j_fu_62;
    end
end

always @ (*) begin
    if ((((1'b0 == ap_block_pp0_stage0_11001) & (ap_enable_reg_pp0_iter2 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage0)) | ((1'b0 == ap_block_pp0_stage1_11001) & (ap_enable_reg_pp0_iter2 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage1)) | ((1'b0 == ap_block_pp0_stage1_11001) & (ap_enable_reg_pp0_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage1)))) begin
        grad_V_ce0 = 1'b1;
    end else begin
        grad_V_ce0 = 1'b0;
    end
end

always @ (*) begin
    if (((1'b0 == ap_block_pp0_stage0) & (ap_enable_reg_pp0_iter6 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
        param_V_address0 = param_V_addr_reg_301_pp0_iter5_reg;
    end else if (((1'b0 == ap_block_pp0_stage1) & (ap_enable_reg_pp0_iter3 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
        param_V_address0 = param_V_addr_reg_301_pp0_iter2_reg;
    end else begin
        param_V_address0 = 'bx;
    end
end

always @ (*) begin
    if ((((1'b0 == ap_block_pp0_stage0_11001) & (ap_enable_reg_pp0_iter6 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage0)) | ((1'b0 == ap_block_pp0_stage0_11001) & (ap_enable_reg_pp0_iter4 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage0)) | ((1'b0 == ap_block_pp0_stage1_11001) & (ap_enable_reg_pp0_iter3 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage1)) | ((1'b0 == ap_block_pp0_stage1_11001) & (ap_enable_reg_pp0_iter4 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage1)))) begin
        param_V_ce0 = 1'b1;
    end else begin
        param_V_ce0 = 1'b0;
    end
end

always @ (*) begin
    if (((1'b0 == ap_block_pp0_stage0_11001) & (ap_enable_reg_pp0_iter6 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
        param_V_we0 = 1'b1;
    end else begin
        param_V_we0 = 1'b0;
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

assign add_ln712_fu_221_p2 = (param_V_load_reg_316 + tmp_V_reg_321);

assign add_ln77_1_fu_141_p2 = (ap_sig_allocacmp_i_load + 8'd1);

assign add_ln77_fu_123_p2 = (ap_sig_allocacmp_indvar_flatten19_load + 10'd1);

assign add_ln80_fu_162_p2 = (select_ln77_fu_147_p3 + 3'd1);

assign add_ln82_fu_187_p2 = (j_1_cast_fu_184_p1 + p_mid1_fu_177_p3);

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

assign grad_V_address0 = zext_ln1171_fu_197_p1;

assign grp_fu_324_p_ce = 1'b1;

assign grp_fu_324_p_din0 = sext_ln1171_fu_202_p1;

assign grp_fu_324_p_din1 = 51'd2251798421176320;

assign icmp_ln77_fu_117_p2 = ((ap_sig_allocacmp_indvar_flatten19_load == 10'd512) ? 1'b1 : 1'b0);

assign icmp_ln80_fu_135_p2 = ((ap_sig_allocacmp_j_load == 3'd4) ? 1'b1 : 1'b0);

assign j_1_cast_fu_184_p1 = select_ln77_reg_276;

assign p_mid1_fu_177_p3 = {{trunc_ln77_reg_281}, {2'd0}};

assign param_V_d0 = add_ln712_reg_326;

assign select_ln77_1_fu_153_p3 = ((icmp_ln80_reg_265[0:0] == 1'b1) ? add_ln77_1_reg_271 : i_load_reg_260);

assign select_ln77_fu_147_p3 = ((icmp_ln80_reg_265[0:0] == 1'b1) ? 3'd0 : j_load_reg_255);

assign sext_ln1171_fu_202_p1 = $signed(grad_V_load_reg_306);

assign trunc_ln77_fu_158_p1 = select_ln77_1_fu_153_p3[6:0];

assign zext_ln1171_fu_197_p1 = add_ln82_reg_291;

endmodule //dotProduct_2_dotProduct_2_Pipeline_UPDATE_UPDATE_INNER
