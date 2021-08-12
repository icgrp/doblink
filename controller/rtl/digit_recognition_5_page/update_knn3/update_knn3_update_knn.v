// ==============================================================
// RTL generated by Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Version: 2020.2
// Copyright (C) Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

`timescale 1 ns / 1 ps 

module update_knn3_update_knn (
        ap_clk,
        ap_rst,
        ap_start,
        ap_done,
        ap_idle,
        ap_ready,
        test_inst,
        train_inst,
        p_read,
        min_distances_read,
        p_read1,
        min_distances12_read,
        p_read2,
        min_distances2_read,
        p_read3,
        min_distances3_read,
        p_read4,
        min_distances4_read,
        p_read5,
        min_distances5_read,
        min_distances_offset,
        ap_return_0,
        ap_return_1,
        ap_return_2,
        ap_return_3,
        ap_return_4,
        ap_return_5
);

parameter    ap_ST_fsm_pp0_stage0 = 8'd1;
parameter    ap_ST_fsm_pp0_stage1 = 8'd2;
parameter    ap_ST_fsm_pp0_stage2 = 8'd4;
parameter    ap_ST_fsm_pp0_stage3 = 8'd8;
parameter    ap_ST_fsm_pp0_stage4 = 8'd16;
parameter    ap_ST_fsm_pp0_stage5 = 8'd32;
parameter    ap_ST_fsm_pp0_stage6 = 8'd64;
parameter    ap_ST_fsm_pp0_stage7 = 8'd128;

input   ap_clk;
input   ap_rst;
input   ap_start;
output   ap_done;
output   ap_idle;
output   ap_ready;
input  [255:0] test_inst;
input  [255:0] train_inst;
input  [31:0] p_read;
input  [31:0] min_distances_read;
input  [31:0] p_read1;
input  [31:0] min_distances12_read;
input  [31:0] p_read2;
input  [31:0] min_distances2_read;
input  [31:0] p_read3;
input  [31:0] min_distances3_read;
input  [31:0] p_read4;
input  [31:0] min_distances4_read;
input  [31:0] p_read5;
input  [31:0] min_distances5_read;
input  [0:0] min_distances_offset;
output  [31:0] ap_return_0;
output  [31:0] ap_return_1;
output  [31:0] ap_return_2;
output  [31:0] ap_return_3;
output  [31:0] ap_return_4;
output  [31:0] ap_return_5;

reg ap_done;
reg ap_idle;
reg ap_ready;

(* fsm_encoding = "none" *) reg   [7:0] ap_CS_fsm;
wire    ap_CS_fsm_pp0_stage0;
reg    ap_enable_reg_pp0_iter0;
wire    ap_block_pp0_stage0;
reg    ap_enable_reg_pp0_iter1;
reg    ap_enable_reg_pp0_iter2;
reg    ap_idle_pp0;
wire    ap_CS_fsm_pp0_stage7;
wire    ap_block_state8_pp0_stage7_iter0;
wire    ap_block_state16_pp0_stage7_iter1;
wire    ap_block_pp0_stage7_11001;
wire   [255:0] ret_fu_215_p2;
reg   [255:0] ret_reg_562;
wire    ap_block_state1_pp0_stage0_iter0;
wire    ap_block_state9_pp0_stage0_iter1;
wire    ap_block_state17_pp0_stage0_iter2;
wire    ap_block_pp0_stage0_11001;
reg   [31:0] p_read_1_reg_567;
reg   [31:0] p_read_1_reg_567_pp0_iter1_reg;
reg   [31:0] p_read_2_reg_573;
reg   [31:0] p_read_2_reg_573_pp0_iter1_reg;
reg   [31:0] p_read_3_reg_579;
reg   [31:0] p_read_3_reg_579_pp0_iter1_reg;
reg   [31:0] p_read_4_reg_585;
reg   [31:0] p_read_4_reg_585_pp0_iter1_reg;
reg   [31:0] p_read_5_reg_591;
reg   [31:0] p_read_5_reg_591_pp0_iter1_reg;
reg   [31:0] p_read_6_reg_597;
reg   [31:0] p_read_6_reg_597_pp0_iter1_reg;
wire   [2:0] select_ln35_3_fu_221_p3;
reg   [2:0] select_ln35_3_reg_603;
reg   [2:0] select_ln35_3_reg_603_pp0_iter1_reg;
wire   [31:0] tmp_fu_229_p8;
reg   [31:0] tmp_reg_608;
wire   [30:0] trunc_ln35_fu_247_p1;
reg   [30:0] trunc_ln35_reg_613;
wire   [31:0] tmp_s_fu_259_p8;
reg   [31:0] tmp_s_reg_618;
wire   [31:0] tmp_1_fu_285_p8;
reg   [31:0] tmp_1_reg_624;
reg   [31:0] tmp_1_reg_624_pp0_iter1_reg;
wire   [0:0] icmp_ln35_fu_303_p2;
reg   [0:0] icmp_ln35_reg_630;
wire   [30:0] select_ln35_fu_308_p3;
reg   [30:0] select_ln35_reg_635;
wire    ap_CS_fsm_pp0_stage1;
wire    ap_block_state2_pp0_stage1_iter0;
wire    ap_block_state10_pp0_stage1_iter1;
wire    ap_block_state18_pp0_stage1_iter2;
wire    ap_block_pp0_stage1_11001;
wire   [31:0] zext_ln35_fu_314_p1;
reg   [31:0] zext_ln35_reg_640;
wire    ap_CS_fsm_pp0_stage2;
wire    ap_block_state3_pp0_stage2_iter0;
wire    ap_block_state11_pp0_stage2_iter1;
wire    ap_block_state19_pp0_stage2_iter2;
wire    ap_block_pp0_stage2_11001;
wire   [0:0] icmp_ln35_1_fu_317_p2;
reg   [0:0] icmp_ln35_1_reg_645;
wire   [31:0] select_ln35_1_fu_322_p3;
reg   [31:0] select_ln35_1_reg_651;
wire    ap_CS_fsm_pp0_stage3;
wire    ap_block_state4_pp0_stage3_iter0;
wire    ap_block_state12_pp0_stage3_iter1;
wire    ap_block_state20_pp0_stage3_iter2;
wire    ap_block_pp0_stage3_11001;
wire   [8:0] grp_popcount_fu_210_ap_return;
reg   [8:0] dist_reg_657;
wire   [0:0] icmp_ln35_2_fu_327_p2;
reg   [0:0] icmp_ln35_2_reg_662;
wire   [31:0] zext_ln24_fu_331_p1;
reg   [31:0] zext_ln24_reg_668;
wire   [0:0] icmp_ln43_fu_339_p2;
reg   [0:0] icmp_ln43_reg_678;
wire   [2:0] add_ln44_fu_359_p2;
reg   [2:0] add_ln44_reg_682;
wire   [31:0] select_ln44_1_fu_490_p3;
reg   [31:0] select_ln44_1_reg_692;
wire   [31:0] select_ln44_2_fu_496_p3;
reg   [31:0] select_ln44_2_reg_697;
wire   [31:0] select_ln44_3_fu_502_p3;
reg   [31:0] select_ln44_3_reg_702;
wire   [31:0] select_ln44_4_fu_508_p3;
reg   [31:0] select_ln44_4_reg_707;
wire   [31:0] select_ln44_5_fu_514_p3;
reg   [31:0] select_ln44_5_reg_712;
wire   [31:0] select_ln44_6_fu_520_p3;
reg   [31:0] select_ln44_6_reg_717;
reg    ap_enable_reg_pp0_iter0_reg;
wire    ap_block_pp0_stage7_subdone;
wire    ap_block_state5_pp0_stage4_iter0;
wire    ap_block_state13_pp0_stage4_iter1;
wire    ap_block_state21_pp0_stage4_iter2;
wire    ap_block_pp0_stage4_subdone;
wire    ap_CS_fsm_pp0_stage4;
reg   [31:0] ap_port_reg_p_read;
reg   [31:0] ap_port_reg_min_distances_read;
reg   [31:0] ap_port_reg_p_read1;
reg   [31:0] ap_port_reg_min_distances12_read;
reg   [31:0] ap_port_reg_p_read2;
reg   [31:0] ap_port_reg_min_distances2_read;
reg   [31:0] ap_port_reg_p_read3;
reg   [31:0] ap_port_reg_min_distances3_read;
reg   [31:0] ap_port_reg_p_read4;
reg   [31:0] ap_port_reg_min_distances4_read;
reg   [31:0] ap_port_reg_p_read5;
reg   [31:0] ap_port_reg_min_distances5_read;
reg   [0:0] ap_port_reg_min_distances_offset;
wire    grp_popcount_fu_210_ap_start;
wire    grp_popcount_fu_210_ap_done;
wire    grp_popcount_fu_210_ap_idle;
wire    grp_popcount_fu_210_ap_ready;
reg   [31:0] ap_phi_mux_phi_ln46_phi_fu_159_p4;
reg   [31:0] ap_phi_reg_pp0_iter2_phi_ln46_reg_156;
wire    ap_block_pp0_stage4_11001;
wire   [31:0] ap_phi_reg_pp0_iter0_phi_ln46_reg_156;
reg   [31:0] ap_phi_reg_pp0_iter1_phi_ln46_reg_156;
reg   [31:0] ap_phi_mux_phi_ln46_1_phi_fu_168_p4;
reg   [31:0] ap_phi_reg_pp0_iter2_phi_ln46_1_reg_165;
wire   [31:0] ap_phi_reg_pp0_iter0_phi_ln46_1_reg_165;
reg   [31:0] ap_phi_reg_pp0_iter1_phi_ln46_1_reg_165;
reg   [31:0] ap_phi_mux_phi_ln46_2_phi_fu_177_p4;
reg   [31:0] ap_phi_reg_pp0_iter2_phi_ln46_2_reg_174;
wire   [31:0] ap_phi_reg_pp0_iter0_phi_ln46_2_reg_174;
reg   [31:0] ap_phi_reg_pp0_iter1_phi_ln46_2_reg_174;
reg   [31:0] ap_phi_mux_phi_ln46_3_phi_fu_186_p4;
reg   [31:0] ap_phi_reg_pp0_iter2_phi_ln46_3_reg_183;
wire   [31:0] ap_phi_reg_pp0_iter0_phi_ln46_3_reg_183;
reg   [31:0] ap_phi_reg_pp0_iter1_phi_ln46_3_reg_183;
reg   [31:0] ap_phi_mux_phi_ln46_4_phi_fu_195_p4;
reg   [31:0] ap_phi_reg_pp0_iter2_phi_ln46_4_reg_192;
wire   [31:0] ap_phi_reg_pp0_iter0_phi_ln46_4_reg_192;
reg   [31:0] ap_phi_reg_pp0_iter1_phi_ln46_4_reg_192;
reg   [31:0] ap_phi_mux_phi_ln46_5_phi_fu_204_p4;
reg   [31:0] ap_phi_reg_pp0_iter2_phi_ln46_5_reg_201;
wire   [31:0] ap_phi_reg_pp0_iter0_phi_ln46_5_reg_201;
reg   [31:0] ap_phi_reg_pp0_iter1_phi_ln46_5_reg_201;
reg    grp_popcount_fu_210_ap_start_reg;
wire    ap_block_pp0_stage1;
wire    ap_block_pp0_stage7;
wire   [2:0] tmp_fu_229_p7;
wire   [2:0] tmp_s_fu_259_p7;
wire   [2:0] tmp_1_fu_285_p7;
wire    ap_block_pp0_stage2;
wire    ap_block_pp0_stage3;
wire   [31:0] select_ln35_2_fu_334_p3;
wire   [1:0] zext_ln44_fu_345_p1;
wire   [1:0] select_ln44_fu_348_p3;
wire   [2:0] zext_ln44_1_fu_355_p1;
wire   [0:0] write_flag_fu_364_p10;
wire   [0:0] write_flag4_fu_427_p10;
wire   [0:0] write_flag8_fu_469_p10;
wire   [0:0] write_flag3_fu_448_p10;
wire   [0:0] write_flag2_fu_406_p10;
wire   [0:0] write_flag1_fu_385_p10;
wire    ap_block_pp0_stage4;
reg   [7:0] ap_NS_fsm;
wire    ap_block_pp0_stage0_subdone;
reg    ap_idle_pp0_1to2;
wire    ap_block_pp0_stage1_subdone;
wire    ap_block_pp0_stage2_subdone;
wire    ap_block_pp0_stage3_subdone;
reg    ap_idle_pp0_0to1;
reg    ap_reset_idle_pp0;
wire    ap_block_state6_pp0_stage5_iter0;
wire    ap_block_state14_pp0_stage5_iter1;
wire    ap_block_pp0_stage5_subdone;
wire    ap_block_state7_pp0_stage6_iter0;
wire    ap_block_state15_pp0_stage6_iter1;
wire    ap_block_pp0_stage6_subdone;
wire    ap_enable_pp0;
wire    ap_ce_reg;

// power-on initialization
initial begin
#0 ap_CS_fsm = 8'd1;
#0 ap_enable_reg_pp0_iter1 = 1'b0;
#0 ap_enable_reg_pp0_iter2 = 1'b0;
#0 ap_enable_reg_pp0_iter0_reg = 1'b0;
#0 grp_popcount_fu_210_ap_start_reg = 1'b0;
end

update_knn3_popcount grp_popcount_fu_210(
    .ap_clk(ap_clk),
    .ap_rst(ap_rst),
    .ap_start(grp_popcount_fu_210_ap_start),
    .ap_done(grp_popcount_fu_210_ap_done),
    .ap_idle(grp_popcount_fu_210_ap_idle),
    .ap_ready(grp_popcount_fu_210_ap_ready),
    .x(ret_reg_562),
    .ap_return(grp_popcount_fu_210_ap_return)
);

update_knn3_mux_63_32_1_1 #(
    .ID( 1 ),
    .NUM_STAGE( 1 ),
    .din0_WIDTH( 32 ),
    .din1_WIDTH( 32 ),
    .din2_WIDTH( 32 ),
    .din3_WIDTH( 32 ),
    .din4_WIDTH( 32 ),
    .din5_WIDTH( 32 ),
    .din6_WIDTH( 3 ),
    .dout_WIDTH( 32 ))
mux_63_32_1_1_U2(
    .din0(ap_port_reg_min_distances_read),
    .din1(ap_port_reg_min_distances12_read),
    .din2(ap_port_reg_min_distances2_read),
    .din3(ap_port_reg_min_distances3_read),
    .din4(ap_port_reg_min_distances4_read),
    .din5(ap_port_reg_min_distances5_read),
    .din6(tmp_fu_229_p7),
    .dout(tmp_fu_229_p8)
);

update_knn3_mux_63_32_1_1 #(
    .ID( 1 ),
    .NUM_STAGE( 1 ),
    .din0_WIDTH( 32 ),
    .din1_WIDTH( 32 ),
    .din2_WIDTH( 32 ),
    .din3_WIDTH( 32 ),
    .din4_WIDTH( 32 ),
    .din5_WIDTH( 32 ),
    .din6_WIDTH( 3 ),
    .dout_WIDTH( 32 ))
mux_63_32_1_1_U3(
    .din0(ap_port_reg_min_distances_read),
    .din1(ap_port_reg_min_distances12_read),
    .din2(ap_port_reg_min_distances2_read),
    .din3(ap_port_reg_min_distances3_read),
    .din4(ap_port_reg_min_distances4_read),
    .din5(ap_port_reg_min_distances5_read),
    .din6(tmp_s_fu_259_p7),
    .dout(tmp_s_fu_259_p8)
);

update_knn3_mux_63_32_1_1 #(
    .ID( 1 ),
    .NUM_STAGE( 1 ),
    .din0_WIDTH( 32 ),
    .din1_WIDTH( 32 ),
    .din2_WIDTH( 32 ),
    .din3_WIDTH( 32 ),
    .din4_WIDTH( 32 ),
    .din5_WIDTH( 32 ),
    .din6_WIDTH( 3 ),
    .dout_WIDTH( 32 ))
mux_63_32_1_1_U4(
    .din0(ap_port_reg_min_distances_read),
    .din1(ap_port_reg_min_distances12_read),
    .din2(ap_port_reg_min_distances2_read),
    .din3(ap_port_reg_min_distances3_read),
    .din4(ap_port_reg_min_distances4_read),
    .din5(ap_port_reg_min_distances5_read),
    .din6(tmp_1_fu_285_p7),
    .dout(tmp_1_fu_285_p8)
);

update_knn3_mux_83_1_1_1 #(
    .ID( 1 ),
    .NUM_STAGE( 1 ),
    .din0_WIDTH( 1 ),
    .din1_WIDTH( 1 ),
    .din2_WIDTH( 1 ),
    .din3_WIDTH( 1 ),
    .din4_WIDTH( 1 ),
    .din5_WIDTH( 1 ),
    .din6_WIDTH( 1 ),
    .din7_WIDTH( 1 ),
    .din8_WIDTH( 3 ),
    .dout_WIDTH( 1 ))
mux_83_1_1_1_U5(
    .din0(1'd1),
    .din1(1'd0),
    .din2(1'd0),
    .din3(1'd0),
    .din4(1'd0),
    .din5(1'd0),
    .din6(1'd0),
    .din7(1'd0),
    .din8(add_ln44_reg_682),
    .dout(write_flag_fu_364_p10)
);

update_knn3_mux_83_1_1_1 #(
    .ID( 1 ),
    .NUM_STAGE( 1 ),
    .din0_WIDTH( 1 ),
    .din1_WIDTH( 1 ),
    .din2_WIDTH( 1 ),
    .din3_WIDTH( 1 ),
    .din4_WIDTH( 1 ),
    .din5_WIDTH( 1 ),
    .din6_WIDTH( 1 ),
    .din7_WIDTH( 1 ),
    .din8_WIDTH( 3 ),
    .dout_WIDTH( 1 ))
mux_83_1_1_1_U6(
    .din0(1'd0),
    .din1(1'd0),
    .din2(1'd0),
    .din3(1'd0),
    .din4(1'd0),
    .din5(1'd1),
    .din6(1'd1),
    .din7(1'd1),
    .din8(add_ln44_reg_682),
    .dout(write_flag1_fu_385_p10)
);

update_knn3_mux_83_1_1_1 #(
    .ID( 1 ),
    .NUM_STAGE( 1 ),
    .din0_WIDTH( 1 ),
    .din1_WIDTH( 1 ),
    .din2_WIDTH( 1 ),
    .din3_WIDTH( 1 ),
    .din4_WIDTH( 1 ),
    .din5_WIDTH( 1 ),
    .din6_WIDTH( 1 ),
    .din7_WIDTH( 1 ),
    .din8_WIDTH( 3 ),
    .dout_WIDTH( 1 ))
mux_83_1_1_1_U7(
    .din0(1'd0),
    .din1(1'd0),
    .din2(1'd0),
    .din3(1'd0),
    .din4(1'd1),
    .din5(1'd0),
    .din6(1'd0),
    .din7(1'd0),
    .din8(add_ln44_reg_682),
    .dout(write_flag2_fu_406_p10)
);

update_knn3_mux_83_1_1_1 #(
    .ID( 1 ),
    .NUM_STAGE( 1 ),
    .din0_WIDTH( 1 ),
    .din1_WIDTH( 1 ),
    .din2_WIDTH( 1 ),
    .din3_WIDTH( 1 ),
    .din4_WIDTH( 1 ),
    .din5_WIDTH( 1 ),
    .din6_WIDTH( 1 ),
    .din7_WIDTH( 1 ),
    .din8_WIDTH( 3 ),
    .dout_WIDTH( 1 ))
mux_83_1_1_1_U8(
    .din0(1'd0),
    .din1(1'd1),
    .din2(1'd0),
    .din3(1'd0),
    .din4(1'd0),
    .din5(1'd0),
    .din6(1'd0),
    .din7(1'd0),
    .din8(add_ln44_reg_682),
    .dout(write_flag4_fu_427_p10)
);

update_knn3_mux_83_1_1_1 #(
    .ID( 1 ),
    .NUM_STAGE( 1 ),
    .din0_WIDTH( 1 ),
    .din1_WIDTH( 1 ),
    .din2_WIDTH( 1 ),
    .din3_WIDTH( 1 ),
    .din4_WIDTH( 1 ),
    .din5_WIDTH( 1 ),
    .din6_WIDTH( 1 ),
    .din7_WIDTH( 1 ),
    .din8_WIDTH( 3 ),
    .dout_WIDTH( 1 ))
mux_83_1_1_1_U9(
    .din0(1'd0),
    .din1(1'd0),
    .din2(1'd0),
    .din3(1'd1),
    .din4(1'd0),
    .din5(1'd0),
    .din6(1'd0),
    .din7(1'd0),
    .din8(add_ln44_reg_682),
    .dout(write_flag3_fu_448_p10)
);

update_knn3_mux_83_1_1_1 #(
    .ID( 1 ),
    .NUM_STAGE( 1 ),
    .din0_WIDTH( 1 ),
    .din1_WIDTH( 1 ),
    .din2_WIDTH( 1 ),
    .din3_WIDTH( 1 ),
    .din4_WIDTH( 1 ),
    .din5_WIDTH( 1 ),
    .din6_WIDTH( 1 ),
    .din7_WIDTH( 1 ),
    .din8_WIDTH( 3 ),
    .dout_WIDTH( 1 ))
mux_83_1_1_1_U10(
    .din0(1'd0),
    .din1(1'd0),
    .din2(1'd1),
    .din3(1'd0),
    .din4(1'd0),
    .din5(1'd0),
    .din6(1'd0),
    .din7(1'd0),
    .din8(add_ln44_reg_682),
    .dout(write_flag8_fu_469_p10)
);

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_CS_fsm <= ap_ST_fsm_pp0_stage0;
    end else begin
        ap_CS_fsm <= ap_NS_fsm;
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp0_iter0_reg <= 1'b0;
    end else begin
        if ((1'b1 == ap_CS_fsm_pp0_stage0)) begin
            ap_enable_reg_pp0_iter0_reg <= ap_start;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp0_iter1 <= 1'b0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage7_subdone) & (1'b1 == ap_CS_fsm_pp0_stage7))) begin
            ap_enable_reg_pp0_iter1 <= ap_enable_reg_pp0_iter0;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp0_iter2 <= 1'b0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage7_subdone) & (1'b1 == ap_CS_fsm_pp0_stage7))) begin
            ap_enable_reg_pp0_iter2 <= ap_enable_reg_pp0_iter1;
        end else if (((ap_enable_reg_pp0_iter1 == 1'b0) & (1'b0 == ap_block_pp0_stage4_subdone) & (1'b1 == ap_CS_fsm_pp0_stage4))) begin
            ap_enable_reg_pp0_iter2 <= 1'b0;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        grp_popcount_fu_210_ap_start_reg <= 1'b0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage0_11001) & (ap_enable_reg_pp0_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
            grp_popcount_fu_210_ap_start_reg <= 1'b1;
        end else if ((grp_popcount_fu_210_ap_ready == 1'b1)) begin
            grp_popcount_fu_210_ap_start_reg <= 1'b0;
        end
    end
end

always @ (posedge ap_clk) begin
    if (((ap_enable_reg_pp0_iter2 == 1'b1) & (1'b0 == ap_block_pp0_stage3_11001) & (1'b1 == ap_CS_fsm_pp0_stage3) & (icmp_ln43_reg_678 == 1'd0))) begin
        ap_phi_reg_pp0_iter2_phi_ln46_1_reg_165 <= p_read_3_reg_579_pp0_iter1_reg;
    end else if (((ap_enable_reg_pp0_iter1 == 1'b1) & (1'b0 == ap_block_pp0_stage7_11001) & (1'b1 == ap_CS_fsm_pp0_stage7))) begin
        ap_phi_reg_pp0_iter2_phi_ln46_1_reg_165 <= ap_phi_reg_pp0_iter1_phi_ln46_1_reg_165;
    end
end

always @ (posedge ap_clk) begin
    if (((ap_enable_reg_pp0_iter2 == 1'b1) & (1'b0 == ap_block_pp0_stage3_11001) & (1'b1 == ap_CS_fsm_pp0_stage3) & (icmp_ln43_reg_678 == 1'd0))) begin
        ap_phi_reg_pp0_iter2_phi_ln46_2_reg_174 <= p_read_5_reg_591_pp0_iter1_reg;
    end else if (((ap_enable_reg_pp0_iter1 == 1'b1) & (1'b0 == ap_block_pp0_stage7_11001) & (1'b1 == ap_CS_fsm_pp0_stage7))) begin
        ap_phi_reg_pp0_iter2_phi_ln46_2_reg_174 <= ap_phi_reg_pp0_iter1_phi_ln46_2_reg_174;
    end
end

always @ (posedge ap_clk) begin
    if (((ap_enable_reg_pp0_iter2 == 1'b1) & (1'b0 == ap_block_pp0_stage3_11001) & (1'b1 == ap_CS_fsm_pp0_stage3) & (icmp_ln43_reg_678 == 1'd0))) begin
        ap_phi_reg_pp0_iter2_phi_ln46_3_reg_183 <= p_read_2_reg_573_pp0_iter1_reg;
    end else if (((ap_enable_reg_pp0_iter1 == 1'b1) & (1'b0 == ap_block_pp0_stage7_11001) & (1'b1 == ap_CS_fsm_pp0_stage7))) begin
        ap_phi_reg_pp0_iter2_phi_ln46_3_reg_183 <= ap_phi_reg_pp0_iter1_phi_ln46_3_reg_183;
    end
end

always @ (posedge ap_clk) begin
    if (((ap_enable_reg_pp0_iter2 == 1'b1) & (1'b0 == ap_block_pp0_stage3_11001) & (1'b1 == ap_CS_fsm_pp0_stage3) & (icmp_ln43_reg_678 == 1'd0))) begin
        ap_phi_reg_pp0_iter2_phi_ln46_4_reg_192 <= p_read_1_reg_567_pp0_iter1_reg;
    end else if (((ap_enable_reg_pp0_iter1 == 1'b1) & (1'b0 == ap_block_pp0_stage7_11001) & (1'b1 == ap_CS_fsm_pp0_stage7))) begin
        ap_phi_reg_pp0_iter2_phi_ln46_4_reg_192 <= ap_phi_reg_pp0_iter1_phi_ln46_4_reg_192;
    end
end

always @ (posedge ap_clk) begin
    if (((ap_enable_reg_pp0_iter2 == 1'b1) & (1'b0 == ap_block_pp0_stage3_11001) & (1'b1 == ap_CS_fsm_pp0_stage3) & (icmp_ln43_reg_678 == 1'd0))) begin
        ap_phi_reg_pp0_iter2_phi_ln46_5_reg_201 <= p_read_6_reg_597_pp0_iter1_reg;
    end else if (((ap_enable_reg_pp0_iter1 == 1'b1) & (1'b0 == ap_block_pp0_stage7_11001) & (1'b1 == ap_CS_fsm_pp0_stage7))) begin
        ap_phi_reg_pp0_iter2_phi_ln46_5_reg_201 <= ap_phi_reg_pp0_iter1_phi_ln46_5_reg_201;
    end
end

always @ (posedge ap_clk) begin
    if (((ap_enable_reg_pp0_iter2 == 1'b1) & (1'b0 == ap_block_pp0_stage3_11001) & (1'b1 == ap_CS_fsm_pp0_stage3) & (icmp_ln43_reg_678 == 1'd0))) begin
        ap_phi_reg_pp0_iter2_phi_ln46_reg_156 <= p_read_4_reg_585_pp0_iter1_reg;
    end else if (((ap_enable_reg_pp0_iter1 == 1'b1) & (1'b0 == ap_block_pp0_stage7_11001) & (1'b1 == ap_CS_fsm_pp0_stage7))) begin
        ap_phi_reg_pp0_iter2_phi_ln46_reg_156 <= ap_phi_reg_pp0_iter1_phi_ln46_reg_156;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b0 == ap_block_pp0_stage2_11001) & (1'b1 == ap_CS_fsm_pp0_stage2) & (icmp_ln43_fu_339_p2 == 1'd1))) begin
        add_ln44_reg_682 <= add_ln44_fu_359_p2;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b0 == ap_block_pp0_stage7_11001) & (ap_enable_reg_pp0_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage7))) begin
        ap_phi_reg_pp0_iter1_phi_ln46_1_reg_165 <= ap_phi_reg_pp0_iter0_phi_ln46_1_reg_165;
        ap_phi_reg_pp0_iter1_phi_ln46_2_reg_174 <= ap_phi_reg_pp0_iter0_phi_ln46_2_reg_174;
        ap_phi_reg_pp0_iter1_phi_ln46_3_reg_183 <= ap_phi_reg_pp0_iter0_phi_ln46_3_reg_183;
        ap_phi_reg_pp0_iter1_phi_ln46_4_reg_192 <= ap_phi_reg_pp0_iter0_phi_ln46_4_reg_192;
        ap_phi_reg_pp0_iter1_phi_ln46_5_reg_201 <= ap_phi_reg_pp0_iter0_phi_ln46_5_reg_201;
        ap_phi_reg_pp0_iter1_phi_ln46_reg_156 <= ap_phi_reg_pp0_iter0_phi_ln46_reg_156;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b0 == ap_block_pp0_stage0_11001) & (ap_enable_reg_pp0_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
        ap_port_reg_min_distances12_read <= min_distances12_read;
        ap_port_reg_min_distances2_read <= min_distances2_read;
        ap_port_reg_min_distances3_read <= min_distances3_read;
        ap_port_reg_min_distances4_read <= min_distances4_read;
        ap_port_reg_min_distances5_read <= min_distances5_read;
        ap_port_reg_min_distances_offset <= min_distances_offset;
        ap_port_reg_min_distances_read <= min_distances_read;
        ap_port_reg_p_read <= p_read;
        ap_port_reg_p_read1 <= p_read1;
        ap_port_reg_p_read2 <= p_read2;
        ap_port_reg_p_read3 <= p_read3;
        ap_port_reg_p_read4 <= p_read4;
        ap_port_reg_p_read5 <= p_read5;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b0 == ap_block_pp0_stage1_11001) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
        dist_reg_657 <= grp_popcount_fu_210_ap_return;
        icmp_ln35_2_reg_662 <= icmp_ln35_2_fu_327_p2;
        select_ln35_reg_635 <= select_ln35_fu_308_p3;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b0 == ap_block_pp0_stage2_11001) & (1'b1 == ap_CS_fsm_pp0_stage2))) begin
        icmp_ln35_1_reg_645 <= icmp_ln35_1_fu_317_p2;
        icmp_ln43_reg_678 <= icmp_ln43_fu_339_p2;
        zext_ln24_reg_668[8 : 0] <= zext_ln24_fu_331_p1[8 : 0];
        zext_ln35_reg_640[30 : 0] <= zext_ln35_fu_314_p1[30 : 0];
    end
end

always @ (posedge ap_clk) begin
    if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
        icmp_ln35_reg_630 <= icmp_ln35_fu_303_p2;
        ret_reg_562 <= ret_fu_215_p2;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b0 == ap_block_pp0_stage7_11001) & (1'b1 == ap_CS_fsm_pp0_stage7))) begin
        p_read_1_reg_567 <= ap_port_reg_p_read5;
        p_read_1_reg_567_pp0_iter1_reg <= p_read_1_reg_567;
        p_read_2_reg_573 <= ap_port_reg_p_read4;
        p_read_2_reg_573_pp0_iter1_reg <= p_read_2_reg_573;
        p_read_3_reg_579 <= ap_port_reg_p_read3;
        p_read_3_reg_579_pp0_iter1_reg <= p_read_3_reg_579;
        p_read_4_reg_585 <= ap_port_reg_p_read2;
        p_read_4_reg_585_pp0_iter1_reg <= p_read_4_reg_585;
        p_read_5_reg_591 <= ap_port_reg_p_read1;
        p_read_5_reg_591_pp0_iter1_reg <= p_read_5_reg_591;
        p_read_6_reg_597 <= ap_port_reg_p_read;
        p_read_6_reg_597_pp0_iter1_reg <= p_read_6_reg_597;
        select_ln35_3_reg_603[1 : 0] <= select_ln35_3_fu_221_p3[1 : 0];
        select_ln35_3_reg_603_pp0_iter1_reg[1 : 0] <= select_ln35_3_reg_603[1 : 0];
        tmp_1_reg_624 <= tmp_1_fu_285_p8;
        tmp_1_reg_624_pp0_iter1_reg <= tmp_1_reg_624;
        tmp_reg_608 <= tmp_fu_229_p8;
        tmp_s_reg_618 <= tmp_s_fu_259_p8;
        trunc_ln35_reg_613 <= trunc_ln35_fu_247_p1;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b0 == ap_block_pp0_stage3_11001) & (1'b1 == ap_CS_fsm_pp0_stage3))) begin
        select_ln35_1_reg_651 <= select_ln35_1_fu_322_p3;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b0 == ap_block_pp0_stage3_11001) & (1'b1 == ap_CS_fsm_pp0_stage3) & (icmp_ln43_reg_678 == 1'd1))) begin
        select_ln44_1_reg_692 <= select_ln44_1_fu_490_p3;
        select_ln44_2_reg_697 <= select_ln44_2_fu_496_p3;
        select_ln44_3_reg_702 <= select_ln44_3_fu_502_p3;
        select_ln44_4_reg_707 <= select_ln44_4_fu_508_p3;
        select_ln44_5_reg_712 <= select_ln44_5_fu_514_p3;
        select_ln44_6_reg_717 <= select_ln44_6_fu_520_p3;
    end
end

always @ (*) begin
    if ((((1'b0 == ap_block_pp0_stage0) & (ap_enable_reg_pp0_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage0) & (ap_start == 1'b0)) | ((ap_enable_reg_pp0_iter2 == 1'b1) & (1'b0 == ap_block_pp0_stage4_11001) & (1'b1 == ap_CS_fsm_pp0_stage4)))) begin
        ap_done = 1'b1;
    end else begin
        ap_done = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_pp0_stage0)) begin
        ap_enable_reg_pp0_iter0 = ap_start;
    end else begin
        ap_enable_reg_pp0_iter0 = ap_enable_reg_pp0_iter0_reg;
    end
end

always @ (*) begin
    if (((ap_idle_pp0 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage0) & (ap_start == 1'b0))) begin
        ap_idle = 1'b1;
    end else begin
        ap_idle = 1'b0;
    end
end

always @ (*) begin
    if (((ap_enable_reg_pp0_iter2 == 1'b0) & (ap_enable_reg_pp0_iter1 == 1'b0) & (ap_enable_reg_pp0_iter0 == 1'b0))) begin
        ap_idle_pp0 = 1'b1;
    end else begin
        ap_idle_pp0 = 1'b0;
    end
end

always @ (*) begin
    if (((ap_enable_reg_pp0_iter1 == 1'b0) & (ap_enable_reg_pp0_iter0 == 1'b0))) begin
        ap_idle_pp0_0to1 = 1'b1;
    end else begin
        ap_idle_pp0_0to1 = 1'b0;
    end
end

always @ (*) begin
    if (((ap_enable_reg_pp0_iter2 == 1'b0) & (ap_enable_reg_pp0_iter1 == 1'b0))) begin
        ap_idle_pp0_1to2 = 1'b1;
    end else begin
        ap_idle_pp0_1to2 = 1'b0;
    end
end

always @ (*) begin
    if ((icmp_ln43_reg_678 == 1'd1)) begin
        ap_phi_mux_phi_ln46_1_phi_fu_168_p4 = select_ln44_4_reg_707;
    end else begin
        ap_phi_mux_phi_ln46_1_phi_fu_168_p4 = ap_phi_reg_pp0_iter2_phi_ln46_1_reg_165;
    end
end

always @ (*) begin
    if ((icmp_ln43_reg_678 == 1'd1)) begin
        ap_phi_mux_phi_ln46_2_phi_fu_177_p4 = select_ln44_2_reg_697;
    end else begin
        ap_phi_mux_phi_ln46_2_phi_fu_177_p4 = ap_phi_reg_pp0_iter2_phi_ln46_2_reg_174;
    end
end

always @ (*) begin
    if ((icmp_ln43_reg_678 == 1'd1)) begin
        ap_phi_mux_phi_ln46_3_phi_fu_186_p4 = select_ln44_5_reg_712;
    end else begin
        ap_phi_mux_phi_ln46_3_phi_fu_186_p4 = ap_phi_reg_pp0_iter2_phi_ln46_3_reg_183;
    end
end

always @ (*) begin
    if ((icmp_ln43_reg_678 == 1'd1)) begin
        ap_phi_mux_phi_ln46_4_phi_fu_195_p4 = select_ln44_6_reg_717;
    end else begin
        ap_phi_mux_phi_ln46_4_phi_fu_195_p4 = ap_phi_reg_pp0_iter2_phi_ln46_4_reg_192;
    end
end

always @ (*) begin
    if ((icmp_ln43_reg_678 == 1'd1)) begin
        ap_phi_mux_phi_ln46_5_phi_fu_204_p4 = select_ln44_1_reg_692;
    end else begin
        ap_phi_mux_phi_ln46_5_phi_fu_204_p4 = ap_phi_reg_pp0_iter2_phi_ln46_5_reg_201;
    end
end

always @ (*) begin
    if ((icmp_ln43_reg_678 == 1'd1)) begin
        ap_phi_mux_phi_ln46_phi_fu_159_p4 = select_ln44_3_reg_702;
    end else begin
        ap_phi_mux_phi_ln46_phi_fu_159_p4 = ap_phi_reg_pp0_iter2_phi_ln46_reg_156;
    end
end

always @ (*) begin
    if (((1'b0 == ap_block_pp0_stage7_11001) & (ap_enable_reg_pp0_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage7))) begin
        ap_ready = 1'b1;
    end else begin
        ap_ready = 1'b0;
    end
end

always @ (*) begin
    if (((ap_idle_pp0_0to1 == 1'b1) & (ap_start == 1'b0))) begin
        ap_reset_idle_pp0 = 1'b1;
    end else begin
        ap_reset_idle_pp0 = 1'b0;
    end
end

always @ (*) begin
    case (ap_CS_fsm)
        ap_ST_fsm_pp0_stage0 : begin
            if ((~((ap_idle_pp0_1to2 == 1'b1) & (ap_start == 1'b0)) & (1'b0 == ap_block_pp0_stage0_subdone))) begin
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
                ap_NS_fsm = ap_ST_fsm_pp0_stage4;
            end else begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage3;
            end
        end
        ap_ST_fsm_pp0_stage4 : begin
            if (((ap_reset_idle_pp0 == 1'b0) & (1'b0 == ap_block_pp0_stage4_subdone))) begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage5;
            end else if (((ap_reset_idle_pp0 == 1'b1) & (1'b0 == ap_block_pp0_stage4_subdone))) begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage0;
            end else begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage4;
            end
        end
        ap_ST_fsm_pp0_stage5 : begin
            if ((1'b0 == ap_block_pp0_stage5_subdone)) begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage6;
            end else begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage5;
            end
        end
        ap_ST_fsm_pp0_stage6 : begin
            if ((1'b0 == ap_block_pp0_stage6_subdone)) begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage7;
            end else begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage6;
            end
        end
        ap_ST_fsm_pp0_stage7 : begin
            if ((1'b0 == ap_block_pp0_stage7_subdone)) begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage0;
            end else begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage7;
            end
        end
        default : begin
            ap_NS_fsm = 'bx;
        end
    endcase
end

assign add_ln44_fu_359_p2 = (zext_ln44_1_fu_355_p1 + select_ln35_3_reg_603_pp0_iter1_reg);

assign ap_CS_fsm_pp0_stage0 = ap_CS_fsm[32'd0];

assign ap_CS_fsm_pp0_stage1 = ap_CS_fsm[32'd1];

assign ap_CS_fsm_pp0_stage2 = ap_CS_fsm[32'd2];

assign ap_CS_fsm_pp0_stage3 = ap_CS_fsm[32'd3];

assign ap_CS_fsm_pp0_stage4 = ap_CS_fsm[32'd4];

assign ap_CS_fsm_pp0_stage7 = ap_CS_fsm[32'd7];

assign ap_block_pp0_stage0 = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage0_11001 = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage0_subdone = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage1 = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage1_11001 = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage1_subdone = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage2 = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage2_11001 = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage2_subdone = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage3 = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage3_11001 = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage3_subdone = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage4 = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage4_11001 = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage4_subdone = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage5_subdone = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage6_subdone = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage7 = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage7_11001 = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage7_subdone = ~(1'b1 == 1'b1);

assign ap_block_state10_pp0_stage1_iter1 = ~(1'b1 == 1'b1);

assign ap_block_state11_pp0_stage2_iter1 = ~(1'b1 == 1'b1);

assign ap_block_state12_pp0_stage3_iter1 = ~(1'b1 == 1'b1);

assign ap_block_state13_pp0_stage4_iter1 = ~(1'b1 == 1'b1);

assign ap_block_state14_pp0_stage5_iter1 = ~(1'b1 == 1'b1);

assign ap_block_state15_pp0_stage6_iter1 = ~(1'b1 == 1'b1);

assign ap_block_state16_pp0_stage7_iter1 = ~(1'b1 == 1'b1);

assign ap_block_state17_pp0_stage0_iter2 = ~(1'b1 == 1'b1);

assign ap_block_state18_pp0_stage1_iter2 = ~(1'b1 == 1'b1);

assign ap_block_state19_pp0_stage2_iter2 = ~(1'b1 == 1'b1);

assign ap_block_state1_pp0_stage0_iter0 = ~(1'b1 == 1'b1);

assign ap_block_state20_pp0_stage3_iter2 = ~(1'b1 == 1'b1);

assign ap_block_state21_pp0_stage4_iter2 = ~(1'b1 == 1'b1);

assign ap_block_state2_pp0_stage1_iter0 = ~(1'b1 == 1'b1);

assign ap_block_state3_pp0_stage2_iter0 = ~(1'b1 == 1'b1);

assign ap_block_state4_pp0_stage3_iter0 = ~(1'b1 == 1'b1);

assign ap_block_state5_pp0_stage4_iter0 = ~(1'b1 == 1'b1);

assign ap_block_state6_pp0_stage5_iter0 = ~(1'b1 == 1'b1);

assign ap_block_state7_pp0_stage6_iter0 = ~(1'b1 == 1'b1);

assign ap_block_state8_pp0_stage7_iter0 = ~(1'b1 == 1'b1);

assign ap_block_state9_pp0_stage0_iter1 = ~(1'b1 == 1'b1);

assign ap_enable_pp0 = (ap_idle_pp0 ^ 1'b1);

assign ap_phi_reg_pp0_iter0_phi_ln46_1_reg_165 = 'bx;

assign ap_phi_reg_pp0_iter0_phi_ln46_2_reg_174 = 'bx;

assign ap_phi_reg_pp0_iter0_phi_ln46_3_reg_183 = 'bx;

assign ap_phi_reg_pp0_iter0_phi_ln46_4_reg_192 = 'bx;

assign ap_phi_reg_pp0_iter0_phi_ln46_5_reg_201 = 'bx;

assign ap_phi_reg_pp0_iter0_phi_ln46_reg_156 = 'bx;

assign ap_return_0 = ap_phi_mux_phi_ln46_5_phi_fu_204_p4;

assign ap_return_1 = ap_phi_mux_phi_ln46_2_phi_fu_177_p4;

assign ap_return_2 = ap_phi_mux_phi_ln46_phi_fu_159_p4;

assign ap_return_3 = ap_phi_mux_phi_ln46_1_phi_fu_168_p4;

assign ap_return_4 = ap_phi_mux_phi_ln46_3_phi_fu_186_p4;

assign ap_return_5 = ap_phi_mux_phi_ln46_4_phi_fu_195_p4;

assign grp_popcount_fu_210_ap_start = grp_popcount_fu_210_ap_start_reg;

assign icmp_ln35_1_fu_317_p2 = (($signed(tmp_s_reg_618) > $signed(zext_ln35_fu_314_p1)) ? 1'b1 : 1'b0);

assign icmp_ln35_2_fu_327_p2 = (($signed(tmp_1_reg_624_pp0_iter1_reg) > $signed(select_ln35_1_reg_651)) ? 1'b1 : 1'b0);

assign icmp_ln35_fu_303_p2 = (($signed(tmp_reg_608) > $signed(32'd0)) ? 1'b1 : 1'b0);

assign icmp_ln43_fu_339_p2 = (($signed(zext_ln24_fu_331_p1) < $signed(select_ln35_2_fu_334_p3)) ? 1'b1 : 1'b0);

assign ret_fu_215_p2 = (train_inst ^ test_inst);

assign select_ln35_1_fu_322_p3 = ((icmp_ln35_1_reg_645[0:0] == 1'b1) ? tmp_s_reg_618 : zext_ln35_reg_640);

assign select_ln35_2_fu_334_p3 = ((icmp_ln35_2_reg_662[0:0] == 1'b1) ? tmp_1_reg_624_pp0_iter1_reg : select_ln35_1_reg_651);

assign select_ln35_3_fu_221_p3 = ((ap_port_reg_min_distances_offset[0:0] == 1'b1) ? 3'd3 : 3'd0);

assign select_ln35_fu_308_p3 = ((icmp_ln35_reg_630[0:0] == 1'b1) ? trunc_ln35_reg_613 : 31'd0);

assign select_ln44_1_fu_490_p3 = ((write_flag_fu_364_p10[0:0] == 1'b1) ? zext_ln24_reg_668 : p_read_6_reg_597_pp0_iter1_reg);

assign select_ln44_2_fu_496_p3 = ((write_flag4_fu_427_p10[0:0] == 1'b1) ? zext_ln24_reg_668 : p_read_5_reg_591_pp0_iter1_reg);

assign select_ln44_3_fu_502_p3 = ((write_flag8_fu_469_p10[0:0] == 1'b1) ? zext_ln24_reg_668 : p_read_4_reg_585_pp0_iter1_reg);

assign select_ln44_4_fu_508_p3 = ((write_flag3_fu_448_p10[0:0] == 1'b1) ? zext_ln24_reg_668 : p_read_3_reg_579_pp0_iter1_reg);

assign select_ln44_5_fu_514_p3 = ((write_flag2_fu_406_p10[0:0] == 1'b1) ? zext_ln24_reg_668 : p_read_2_reg_573_pp0_iter1_reg);

assign select_ln44_6_fu_520_p3 = ((write_flag1_fu_385_p10[0:0] == 1'b1) ? zext_ln24_reg_668 : p_read_1_reg_567_pp0_iter1_reg);

assign select_ln44_fu_348_p3 = ((icmp_ln35_2_reg_662[0:0] == 1'b1) ? 2'd2 : zext_ln44_fu_345_p1);

assign tmp_1_fu_285_p7 = ((ap_port_reg_min_distances_offset[0:0] == 1'b1) ? 3'd5 : 3'd2);

assign tmp_fu_229_p7 = ((ap_port_reg_min_distances_offset[0:0] == 1'b1) ? 3'd3 : 3'd0);

assign tmp_s_fu_259_p7 = ((ap_port_reg_min_distances_offset[0:0] == 1'b1) ? 3'd4 : 3'd1);

assign trunc_ln35_fu_247_p1 = tmp_fu_229_p8[30:0];

assign zext_ln24_fu_331_p1 = dist_reg_657;

assign zext_ln35_fu_314_p1 = select_ln35_reg_635;

assign zext_ln44_1_fu_355_p1 = select_ln44_fu_348_p3;

assign zext_ln44_fu_345_p1 = icmp_ln35_1_reg_645;

always @ (posedge ap_clk) begin
    select_ln35_3_reg_603[2] <= 1'b0;
    select_ln35_3_reg_603_pp0_iter1_reg[2] <= 1'b0;
    zext_ln35_reg_640[31] <= 1'b0;
    zext_ln24_reg_668[31:9] <= 23'b00000000000000000000000;
end

endmodule //update_knn3_update_knn
