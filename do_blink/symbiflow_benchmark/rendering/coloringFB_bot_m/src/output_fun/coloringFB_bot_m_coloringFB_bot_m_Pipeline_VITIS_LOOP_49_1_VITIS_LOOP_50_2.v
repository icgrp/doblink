// ==============================================================
// RTL generated by Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2021.1 (64-bit)
// Version: 2021.1
// Copyright (C) Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

`timescale 1 ns / 1 ps 

module coloringFB_bot_m_coloringFB_bot_m_Pipeline_VITIS_LOOP_49_1_VITIS_LOOP_50_2 (
        ap_clk,
        ap_rst,
        ap_start,
        ap_done,
        ap_idle,
        ap_ready,
        Output_1_V_TREADY,
        Output_1_V_TDATA,
        Output_1_V_TVALID,
        frame_buffer_V_address0,
        frame_buffer_V_ce0,
        frame_buffer_V_q0
);

parameter    ap_ST_fsm_pp0_stage0 = 4'd1;
parameter    ap_ST_fsm_pp0_stage1 = 4'd2;
parameter    ap_ST_fsm_pp0_stage2 = 4'd4;
parameter    ap_ST_fsm_pp0_stage3 = 4'd8;

input   ap_clk;
input   ap_rst;
input   ap_start;
output   ap_done;
output   ap_idle;
output   ap_ready;
input   Output_1_V_TREADY;
output  [31:0] Output_1_V_TDATA;
output   Output_1_V_TVALID;
output  [14:0] frame_buffer_V_address0;
output   frame_buffer_V_ce0;
input  [7:0] frame_buffer_V_q0;

reg ap_idle;
reg Output_1_V_TVALID;
reg[14:0] frame_buffer_V_address0;
reg frame_buffer_V_ce0;

(* fsm_encoding = "none" *) reg   [3:0] ap_CS_fsm;
wire    ap_CS_fsm_pp0_stage0;
reg    ap_enable_reg_pp0_iter0;
reg    ap_enable_reg_pp0_iter1;
reg    ap_idle_pp0;
wire    ap_block_state1_pp0_stage0_iter0;
reg    ap_block_state5_pp0_stage0_iter1;
reg    ap_block_pp0_stage0_subdone;
wire   [0:0] icmp_ln49_fu_152_p2;
reg    ap_condition_exit_pp0_iter0_stage0;
wire    ap_loop_exit_ready;
reg    ap_ready_int;
wire    ap_CS_fsm_pp0_stage3;
wire    ap_block_state4_pp0_stage3_iter0;
wire    ap_block_pp0_stage3_subdone;
reg    Output_1_V_TDATA_blk_n;
wire    ap_block_pp0_stage0;
reg   [0:0] icmp_ln49_reg_335;
reg    ap_block_pp0_stage0_11001;
wire   [8:0] select_ln49_1_fu_192_p3;
reg   [8:0] select_ln49_1_reg_339;
wire   [14:0] add_ln225_fu_216_p2;
reg   [14:0] add_ln225_reg_345;
wire   [6:0] empty_11_fu_222_p1;
reg   [6:0] empty_11_reg_350;
reg   [7:0] frame_buffer_V_load_1_reg_361;
wire    ap_CS_fsm_pp0_stage1;
wire    ap_block_state2_pp0_stage1_iter0;
wire    ap_block_pp0_stage1_11001;
reg   [7:0] frame_buffer_V_load_2_reg_371;
wire    ap_CS_fsm_pp0_stage2;
wire    ap_block_state3_pp0_stage2_iter0;
wire    ap_block_pp0_stage2_11001;
wire    ap_block_pp0_stage3_11001;
reg   [7:0] frame_buffer_V_load_3_reg_386;
reg    ap_enable_reg_pp0_iter0_reg;
wire   [63:0] zext_ln225_1_fu_240_p1;
wire   [63:0] zext_ln225_2_fu_278_p1;
wire    ap_block_pp0_stage1;
wire   [63:0] zext_ln225_3_fu_295_p1;
wire    ap_block_pp0_stage2;
wire   [63:0] zext_ln225_4_fu_300_p1;
wire    ap_block_pp0_stage3;
reg   [7:0] j_fu_78;
wire    ap_loop_init;
reg   [7:0] ap_sig_allocacmp_j_load;
wire   [7:0] add_ln50_fu_245_p2;
reg   [8:0] i_fu_82;
reg   [8:0] ap_sig_allocacmp_i_load;
reg   [13:0] indvar_flatten7_fu_86;
reg   [13:0] ap_sig_allocacmp_indvar_flatten7_load;
wire   [13:0] add_ln49_1_fu_158_p2;
reg    ap_block_pp0_stage0_01001;
wire   [0:0] tmp_fu_176_p3;
wire   [8:0] add_ln49_fu_170_p2;
wire   [7:0] trunc_ln225_fu_200_p1;
wire   [7:0] select_ln49_fu_184_p3;
wire   [14:0] tmp_3_cast_fu_204_p3;
wire   [14:0] zext_ln225_fu_212_p1;
wire   [6:0] or_ln53_fu_226_p2;
wire   [15:0] tmp_4_fu_232_p3;
wire   [6:0] or_ln53_1_fu_266_p2;
wire   [15:0] tmp_5_fu_271_p3;
wire   [6:0] or_ln53_2_fu_283_p2;
wire   [15:0] tmp_6_fu_288_p3;
reg    ap_done_reg;
wire    ap_continue_int;
reg    ap_done_int;
reg   [3:0] ap_NS_fsm;
reg    ap_idle_pp0_1to1;
wire    ap_block_pp0_stage1_subdone;
wire    ap_block_pp0_stage2_subdone;
wire    ap_enable_pp0;
wire    ap_start_int;
wire    ap_ce_reg;

// power-on initialization
initial begin
#0 ap_CS_fsm = 4'd1;
#0 ap_enable_reg_pp0_iter1 = 1'b0;
#0 icmp_ln49_reg_335 = 1'd0;
#0 select_ln49_1_reg_339 = 9'd0;
#0 add_ln225_reg_345 = 15'd0;
#0 empty_11_reg_350 = 7'd0;
#0 frame_buffer_V_load_1_reg_361 = 8'd0;
#0 frame_buffer_V_load_2_reg_371 = 8'd0;
#0 frame_buffer_V_load_3_reg_386 = 8'd0;
#0 ap_enable_reg_pp0_iter0_reg = 1'b0;
#0 j_fu_78 = 8'd0;
#0 i_fu_82 = 9'd0;
#0 indvar_flatten7_fu_86 = 14'd0;
#0 ap_done_reg = 1'b0;
end

coloringFB_bot_m_flow_control_loop_pipe_sequential_init flow_control_loop_pipe_sequential_init_U(
    .ap_clk(ap_clk),
    .ap_rst(ap_rst),
    .ap_start(ap_start),
    .ap_ready(ap_ready),
    .ap_done(ap_done),
    .ap_start_int(ap_start_int),
    .ap_loop_init(ap_loop_init),
    .ap_ready_int(ap_ready_int),
    .ap_loop_exit_ready(ap_condition_exit_pp0_iter0_stage0),
    .ap_loop_exit_done(ap_done_int),
    .ap_continue_int(ap_continue_int),
    .ap_done_int(ap_done_int)
);

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        add_ln225_reg_345 <= 15'd0;
    end else begin
        if (((icmp_ln49_fu_152_p2 == 1'd0) & (1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            add_ln225_reg_345 <= add_ln225_fu_216_p2;
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
        end else if (((ap_loop_exit_ready == 1'b1) & (1'b0 == ap_block_pp0_stage0_subdone) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            ap_done_reg <= 1'b1;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp0_iter0_reg <= 1'b0;
    end else begin
        if ((1'b1 == ap_condition_exit_pp0_iter0_stage0)) begin
            ap_enable_reg_pp0_iter0_reg <= 1'b0;
        end else if ((1'b1 == ap_CS_fsm_pp0_stage0)) begin
            ap_enable_reg_pp0_iter0_reg <= ap_start_int;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp0_iter1 <= 1'b0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_subdone) & (ap_enable_reg_pp0_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            ap_enable_reg_pp0_iter1 <= 1'b0;
        end else if (((1'b0 == ap_block_pp0_stage3_subdone) & (1'b1 == ap_CS_fsm_pp0_stage3))) begin
            ap_enable_reg_pp0_iter1 <= ap_enable_reg_pp0_iter0;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        empty_11_reg_350 <= 7'd0;
    end else begin
        if (((icmp_ln49_fu_152_p2 == 1'd0) & (1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            empty_11_reg_350 <= empty_11_fu_222_p1;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        frame_buffer_V_load_1_reg_361 <= 8'd0;
    end else begin
        if (((icmp_ln49_reg_335 == 1'd0) & (1'b0 == ap_block_pp0_stage1_11001) & (ap_enable_reg_pp0_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
            frame_buffer_V_load_1_reg_361 <= frame_buffer_V_q0;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        frame_buffer_V_load_2_reg_371 <= 8'd0;
    end else begin
        if (((icmp_ln49_reg_335 == 1'd0) & (1'b0 == ap_block_pp0_stage2_11001) & (ap_enable_reg_pp0_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage2))) begin
            frame_buffer_V_load_2_reg_371 <= frame_buffer_V_q0;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        frame_buffer_V_load_3_reg_386 <= 8'd0;
    end else begin
        if (((icmp_ln49_reg_335 == 1'd0) & (1'b0 == ap_block_pp0_stage3_11001) & (ap_enable_reg_pp0_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage3))) begin
            frame_buffer_V_load_3_reg_386 <= frame_buffer_V_q0;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        i_fu_82 <= 9'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            if (((icmp_ln49_fu_152_p2 == 1'd0) & (ap_enable_reg_pp0_iter0 == 1'b1))) begin
                i_fu_82 <= select_ln49_1_fu_192_p3;
            end else if ((ap_loop_init == 1'b1)) begin
                i_fu_82 <= 9'd0;
            end
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        icmp_ln49_reg_335 <= 1'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            icmp_ln49_reg_335 <= icmp_ln49_fu_152_p2;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        indvar_flatten7_fu_86 <= 14'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            if (((icmp_ln49_fu_152_p2 == 1'd0) & (ap_enable_reg_pp0_iter0 == 1'b1))) begin
                indvar_flatten7_fu_86 <= add_ln49_1_fu_158_p2;
            end else if ((ap_loop_init == 1'b1)) begin
                indvar_flatten7_fu_86 <= 14'd0;
            end
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        j_fu_78 <= 8'd0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            if (((icmp_ln49_fu_152_p2 == 1'd0) & (ap_enable_reg_pp0_iter0 == 1'b1))) begin
                j_fu_78 <= add_ln50_fu_245_p2;
            end else if ((ap_loop_init == 1'b1)) begin
                j_fu_78 <= 8'd0;
            end
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        select_ln49_1_reg_339 <= 9'd0;
    end else begin
        if (((icmp_ln49_fu_152_p2 == 1'd0) & (1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            select_ln49_1_reg_339 <= select_ln49_1_fu_192_p3;
        end
    end
end

always @ (*) begin
    if (((1'b0 == ap_block_pp0_stage0) & (ap_enable_reg_pp0_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
        Output_1_V_TDATA_blk_n = Output_1_V_TREADY;
    end else begin
        Output_1_V_TDATA_blk_n = 1'b1;
    end
end

always @ (*) begin
    if (((1'b0 == ap_block_pp0_stage0_11001) & (ap_enable_reg_pp0_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
        Output_1_V_TVALID = 1'b1;
    end else begin
        Output_1_V_TVALID = 1'b0;
    end
end

always @ (*) begin
    if (((icmp_ln49_fu_152_p2 == 1'd1) & (1'b0 == ap_block_pp0_stage0_subdone) & (ap_enable_reg_pp0_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
        ap_condition_exit_pp0_iter0_stage0 = 1'b1;
    end else begin
        ap_condition_exit_pp0_iter0_stage0 = 1'b0;
    end
end

always @ (*) begin
    if (((ap_loop_exit_ready == 1'b1) & (1'b0 == ap_block_pp0_stage0_subdone) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
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
    if (((ap_start_int == 1'b0) & (ap_idle_pp0 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
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
    if ((ap_enable_reg_pp0_iter1 == 1'b0)) begin
        ap_idle_pp0_1to1 = 1'b1;
    end else begin
        ap_idle_pp0_1to1 = 1'b0;
    end
end

always @ (*) begin
    if (((1'b0 == ap_block_pp0_stage3_subdone) & (ap_enable_reg_pp0_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage3))) begin
        ap_ready_int = 1'b1;
    end else begin
        ap_ready_int = 1'b0;
    end
end

always @ (*) begin
    if (((1'b0 == ap_block_pp0_stage0) & (1'b1 == ap_CS_fsm_pp0_stage0) & (ap_loop_init == 1'b1))) begin
        ap_sig_allocacmp_i_load = 9'd0;
    end else begin
        ap_sig_allocacmp_i_load = i_fu_82;
    end
end

always @ (*) begin
    if (((1'b0 == ap_block_pp0_stage0) & (1'b1 == ap_CS_fsm_pp0_stage0) & (ap_loop_init == 1'b1))) begin
        ap_sig_allocacmp_indvar_flatten7_load = 14'd0;
    end else begin
        ap_sig_allocacmp_indvar_flatten7_load = indvar_flatten7_fu_86;
    end
end

always @ (*) begin
    if (((1'b0 == ap_block_pp0_stage0) & (1'b1 == ap_CS_fsm_pp0_stage0) & (ap_loop_init == 1'b1))) begin
        ap_sig_allocacmp_j_load = 8'd0;
    end else begin
        ap_sig_allocacmp_j_load = j_fu_78;
    end
end

always @ (*) begin
    if ((ap_enable_reg_pp0_iter0 == 1'b1)) begin
        if (((1'b0 == ap_block_pp0_stage3) & (1'b1 == ap_CS_fsm_pp0_stage3))) begin
            frame_buffer_V_address0 = zext_ln225_4_fu_300_p1;
        end else if (((1'b0 == ap_block_pp0_stage2) & (1'b1 == ap_CS_fsm_pp0_stage2))) begin
            frame_buffer_V_address0 = zext_ln225_3_fu_295_p1;
        end else if (((1'b0 == ap_block_pp0_stage1) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
            frame_buffer_V_address0 = zext_ln225_2_fu_278_p1;
        end else if (((1'b0 == ap_block_pp0_stage0) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            frame_buffer_V_address0 = zext_ln225_1_fu_240_p1;
        end else begin
            frame_buffer_V_address0 = 'bx;
        end
    end else begin
        frame_buffer_V_address0 = 'bx;
    end
end

always @ (*) begin
    if ((((1'b0 == ap_block_pp0_stage0_11001) & (ap_enable_reg_pp0_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage0)) | ((1'b0 == ap_block_pp0_stage3_11001) & (ap_enable_reg_pp0_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage3)) | ((1'b0 == ap_block_pp0_stage2_11001) & (ap_enable_reg_pp0_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage2)) | ((1'b0 == ap_block_pp0_stage1_11001) & (ap_enable_reg_pp0_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage1)))) begin
        frame_buffer_V_ce0 = 1'b1;
    end else begin
        frame_buffer_V_ce0 = 1'b0;
    end
end

always @ (*) begin
    case (ap_CS_fsm)
        ap_ST_fsm_pp0_stage0 : begin
            if ((1'b1 == ap_condition_exit_pp0_iter0_stage0)) begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage0;
            end else if ((~((ap_start_int == 1'b0) & (ap_idle_pp0_1to1 == 1'b1)) & (1'b0 == ap_block_pp0_stage0_subdone))) begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage1;
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
        default : begin
            ap_NS_fsm = 'bx;
        end
    endcase
end

assign Output_1_V_TDATA = {{{{frame_buffer_V_load_3_reg_386}, {frame_buffer_V_load_2_reg_371}}, {frame_buffer_V_load_1_reg_361}}, {frame_buffer_V_q0}};

assign add_ln225_fu_216_p2 = (tmp_3_cast_fu_204_p3 + zext_ln225_fu_212_p1);

assign add_ln49_1_fu_158_p2 = (ap_sig_allocacmp_indvar_flatten7_load + 14'd1);

assign add_ln49_fu_170_p2 = (ap_sig_allocacmp_i_load + 9'd1);

assign add_ln50_fu_245_p2 = (select_ln49_fu_184_p3 + 8'd4);

assign ap_CS_fsm_pp0_stage0 = ap_CS_fsm[32'd0];

assign ap_CS_fsm_pp0_stage1 = ap_CS_fsm[32'd1];

assign ap_CS_fsm_pp0_stage2 = ap_CS_fsm[32'd2];

assign ap_CS_fsm_pp0_stage3 = ap_CS_fsm[32'd3];

assign ap_block_pp0_stage0 = ~(1'b1 == 1'b1);

always @ (*) begin
    ap_block_pp0_stage0_01001 = ((1'b0 == Output_1_V_TREADY) & (ap_enable_reg_pp0_iter1 == 1'b1));
end

always @ (*) begin
    ap_block_pp0_stage0_11001 = ((1'b0 == Output_1_V_TREADY) & (ap_enable_reg_pp0_iter1 == 1'b1));
end

always @ (*) begin
    ap_block_pp0_stage0_subdone = ((1'b0 == Output_1_V_TREADY) & (ap_enable_reg_pp0_iter1 == 1'b1));
end

assign ap_block_pp0_stage1 = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage1_11001 = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage1_subdone = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage2 = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage2_11001 = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage2_subdone = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage3 = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage3_11001 = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage3_subdone = ~(1'b1 == 1'b1);

assign ap_block_state1_pp0_stage0_iter0 = ~(1'b1 == 1'b1);

assign ap_block_state2_pp0_stage1_iter0 = ~(1'b1 == 1'b1);

assign ap_block_state3_pp0_stage2_iter0 = ~(1'b1 == 1'b1);

assign ap_block_state4_pp0_stage3_iter0 = ~(1'b1 == 1'b1);

always @ (*) begin
    ap_block_state5_pp0_stage0_iter1 = (1'b0 == Output_1_V_TREADY);
end

assign ap_enable_pp0 = (ap_idle_pp0 ^ 1'b1);

assign ap_loop_exit_ready = ap_condition_exit_pp0_iter0_stage0;

assign empty_11_fu_222_p1 = select_ln49_fu_184_p3[6:0];

assign icmp_ln49_fu_152_p2 = ((ap_sig_allocacmp_indvar_flatten7_load == 14'd8192) ? 1'b1 : 1'b0);

assign or_ln53_1_fu_266_p2 = (empty_11_reg_350 | 7'd2);

assign or_ln53_2_fu_283_p2 = (empty_11_reg_350 | 7'd3);

assign or_ln53_fu_226_p2 = (empty_11_fu_222_p1 | 7'd1);

assign select_ln49_1_fu_192_p3 = ((tmp_fu_176_p3[0:0] == 1'b1) ? add_ln49_fu_170_p2 : ap_sig_allocacmp_i_load);

assign select_ln49_fu_184_p3 = ((tmp_fu_176_p3[0:0] == 1'b1) ? 8'd0 : ap_sig_allocacmp_j_load);

assign tmp_3_cast_fu_204_p3 = {{trunc_ln225_fu_200_p1}, {7'd0}};

assign tmp_4_fu_232_p3 = {{select_ln49_1_fu_192_p3}, {or_ln53_fu_226_p2}};

assign tmp_5_fu_271_p3 = {{select_ln49_1_reg_339}, {or_ln53_1_fu_266_p2}};

assign tmp_6_fu_288_p3 = {{select_ln49_1_reg_339}, {or_ln53_2_fu_283_p2}};

assign tmp_fu_176_p3 = ap_sig_allocacmp_j_load[32'd7];

assign trunc_ln225_fu_200_p1 = select_ln49_1_fu_192_p3[7:0];

assign zext_ln225_1_fu_240_p1 = tmp_4_fu_232_p3;

assign zext_ln225_2_fu_278_p1 = tmp_5_fu_271_p3;

assign zext_ln225_3_fu_295_p1 = tmp_6_fu_288_p3;

assign zext_ln225_4_fu_300_p1 = add_ln225_reg_345;

assign zext_ln225_fu_212_p1 = select_ln49_fu_184_p3;

endmodule //coloringFB_bot_m_coloringFB_bot_m_Pipeline_VITIS_LOOP_49_1_VITIS_LOOP_50_2
