// ==============================================================
// RTL generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and OpenCL
// Version: 2020.1
// Copyright (C) 1986-2020 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

`timescale 1 ns / 1 ps 

(* CORE_GENERATION_INFO="zculling_top,hls_ip_2020_1,{HLS_INPUT_TYPE=cxx,HLS_INPUT_FLOAT=0,HLS_INPUT_FIXED=1,HLS_INPUT_PART=xc7a200t-sbg484-1,HLS_INPUT_CLOCK=10.000000,HLS_INPUT_ARCH=others,HLS_SYN_CLOCK=8.559000,HLS_SYN_LAT=-1,HLS_SYN_TPT=none,HLS_SYN_MEM=19,HLS_SYN_DSP=0,HLS_SYN_FF=243,HLS_SYN_LUT=616,HLS_VERSION=2020_1}" *)

module zculling_top (
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

parameter    ap_ST_fsm_state1 = 9'd1;
parameter    ap_ST_fsm_state2 = 9'd2;
parameter    ap_ST_fsm_state3 = 9'd4;
parameter    ap_ST_fsm_pp1_stage0 = 9'd8;
parameter    ap_ST_fsm_pp1_stage1 = 9'd16;
parameter    ap_ST_fsm_state7 = 9'd32;
parameter    ap_ST_fsm_state8 = 9'd64;
parameter    ap_ST_fsm_pp2_stage0 = 9'd128;
parameter    ap_ST_fsm_state12 = 9'd256;

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

(* fsm_encoding = "none" *) reg   [8:0] ap_CS_fsm;
wire    ap_CS_fsm_state1;
reg   [0:0] odd_even_V;
reg   [15:0] counter_V;
reg   [14:0] z_buffer_V_address0;
reg    z_buffer_V_ce0;
reg    z_buffer_V_we0;
reg   [7:0] z_buffer_V_d0;
wire   [7:0] z_buffer_V_q0;
reg    Input_1_V_V_blk_n;
wire    ap_CS_fsm_pp1_stage1;
reg    ap_enable_reg_pp1_iter0;
wire    ap_block_pp1_stage1;
reg   [0:0] odd_even_V_load_reg_551;
reg   [0:0] icmp_ln1134_reg_595;
reg    Input_2_V_V_blk_n;
reg    Output_1_V_V_blk_n;
wire    ap_CS_fsm_state7;
wire    ap_CS_fsm_state8;
wire    ap_CS_fsm_pp2_stage0;
reg    ap_enable_reg_pp2_iter1;
wire    ap_block_pp2_stage0;
reg   [0:0] icmp_ln1155_reg_638;
reg    ap_enable_reg_pp2_iter2;
reg   [0:0] icmp_ln1155_reg_638_pp2_iter1_reg;
reg   [15:0] t_V_4_reg_259;
reg   [15:0] i_op_assign_reg_281;
reg    ap_block_state1;
reg   [15:0] t_V_3_reg_556;
wire   [0:0] icmp_ln879_fu_303_p2;
wire   [15:0] add_ln887_fu_315_p2;
wire    ap_CS_fsm_state2;
wire   [7:0] select_ln544_1_fu_341_p3;
wire   [0:0] icmp_ln887_fu_309_p2;
wire   [8:0] j_V_fu_376_p2;
wire   [15:0] empty_6_fu_382_p1;
reg   [15:0] empty_6_reg_590;
wire    ap_CS_fsm_state3;
wire   [0:0] icmp_ln1134_fu_391_p2;
wire    ap_CS_fsm_pp1_stage0;
wire    ap_block_state4_pp1_stage0_iter0;
wire    ap_block_state5_pp1_stage0_iter1;
wire    ap_block_pp1_stage0_11001;
wire   [15:0] n_V_fu_396_p2;
reg   [15:0] n_V_reg_599;
wire   [7:0] fragment_x_V_fu_425_p1;
reg   [7:0] fragment_x_V_reg_607;
reg    ap_predicate_op89_read_state6;
reg    ap_predicate_op91_read_state6;
reg    ap_block_state6_pp1_stage1_iter0;
reg    ap_block_pp1_stage1_11001;
wire   [7:0] fragment_y_V_fu_429_p4;
reg   [7:0] fragment_y_V_reg_612;
reg   [7:0] fragment_z_V_reg_617;
reg   [7:0] fragment_color_V_reg_623;
reg   [14:0] z_buffer_V_addr_1_reg_628;
wire   [31:0] tmp_V_2_fu_478_p1;
wire   [0:0] icmp_ln1155_fu_483_p2;
wire    ap_block_state9_pp2_stage0_iter0;
wire    ap_block_state10_pp2_stage0_iter1;
reg    ap_block_state10_io;
wire    ap_block_state11_pp2_stage0_iter2;
reg    ap_block_state11_io;
reg    ap_block_pp2_stage0_11001;
wire   [15:0] j_fu_489_p2;
reg    ap_enable_reg_pp2_iter0;
wire   [31:0] p_Result_s_fu_502_p5;
wire    ap_block_pp1_stage0_subdone;
reg    ap_condition_pp1_exit_iter0_state4;
reg    ap_enable_reg_pp1_iter1;
reg    ap_block_pp1_stage1_subdone;
reg    ap_block_pp2_stage0_subdone;
reg    ap_condition_pp2_exit_iter0_state9;
reg   [8:0] pixels_x_V_address0;
reg    pixels_x_V_ce0;
reg    pixels_x_V_we0;
wire   [7:0] pixels_x_V_q0;
reg   [8:0] pixels_y_V_address0;
reg    pixels_y_V_ce0;
reg    pixels_y_V_we0;
wire   [7:0] pixels_y_V_q0;
reg   [8:0] pixels_color_V_address0;
reg    pixels_color_V_ce0;
reg    pixels_color_V_we0;
wire   [7:0] pixels_color_V_q0;
reg   [31:0] p_0344_0_in_reg_214;
reg   [15:0] indvar_flatten_reg_226;
reg   [7:0] t_V_reg_237;
reg   [8:0] t_V_1_reg_248;
reg   [15:0] ap_phi_mux_t_V_4_phi_fu_263_p4;
wire    ap_block_pp1_stage0;
reg   [31:0] ap_phi_mux_p_Val2_s_phi_fu_273_p4;
wire   [31:0] ap_phi_reg_pp1_iter0_p_Val2_s_reg_270;
wire   [63:0] zext_ln321_1_fu_371_p1;
wire   [63:0] zext_ln544_fu_407_p1;
wire   [0:0] icmp_ln887_2_fu_402_p2;
wire  signed [63:0] sext_ln887_fu_473_p1;
wire   [63:0] zext_ln1157_fu_495_p1;
wire   [0:0] r_V_fu_520_p2;
wire    ap_CS_fsm_state12;
wire    regslice_forward_Output_1_V_V_U_apdone_blk;
wire   [15:0] select_ln1167_fu_537_p3;
reg   [15:0] t_V_2_fu_112;
wire   [15:0] pixel_cntr_V_fu_414_p2;
wire    ap_block_pp2_stage0_01001;
wire   [0:0] icmp_ln887_1_fu_327_p2;
wire   [7:0] i_V_fu_321_p2;
wire   [15:0] tmp_fu_349_p3;
wire   [8:0] select_ln544_fu_333_p3;
wire   [16:0] zext_ln321_fu_361_p1;
wire   [16:0] zext_ln1122_fu_357_p1;
wire   [16:0] add_ln321_fu_365_p2;
wire   [7:0] ret_V_fu_459_p2;
wire   [15:0] tmp_5_fu_465_p3;
wire   [15:0] add_ln700_fu_515_p2;
wire   [0:0] icmp_ln879_1_fu_531_p2;
reg   [8:0] ap_NS_fsm;
reg    ap_idle_pp1;
wire    ap_enable_pp1;
reg    ap_idle_pp2;
wire    ap_enable_pp2;
reg   [31:0] Output_1_V_V_int;
reg    Output_1_V_V_ap_vld_int;
wire    Output_1_V_V_ap_ack_int;
wire    regslice_forward_Output_1_V_V_U_vld_out;
reg    ap_condition_136;

// power-on initialization
initial begin
#0 ap_CS_fsm = 9'd1;
#0 odd_even_V = 1'd0;
#0 counter_V = 16'd0;
#0 ap_enable_reg_pp1_iter0 = 1'b0;
#0 ap_enable_reg_pp2_iter1 = 1'b0;
#0 ap_enable_reg_pp2_iter2 = 1'b0;
#0 ap_enable_reg_pp2_iter0 = 1'b0;
#0 ap_enable_reg_pp1_iter1 = 1'b0;
end

zculling_top_z_bubkb #(
    .DataWidth( 8 ),
    .AddressRange( 32768 ),
    .AddressWidth( 15 ))
z_buffer_V_U(
    .clk(ap_clk),
    .reset(ap_rst),
    .address0(z_buffer_V_address0),
    .ce0(z_buffer_V_ce0),
    .we0(z_buffer_V_we0),
    .d0(z_buffer_V_d0),
    .q0(z_buffer_V_q0)
);

zculling_top_pixecud #(
    .DataWidth( 8 ),
    .AddressRange( 500 ),
    .AddressWidth( 9 ))
pixels_x_V_U(
    .clk(ap_clk),
    .reset(ap_rst),
    .address0(pixels_x_V_address0),
    .ce0(pixels_x_V_ce0),
    .we0(pixels_x_V_we0),
    .d0(fragment_x_V_reg_607),
    .q0(pixels_x_V_q0)
);

zculling_top_pixecud #(
    .DataWidth( 8 ),
    .AddressRange( 500 ),
    .AddressWidth( 9 ))
pixels_y_V_U(
    .clk(ap_clk),
    .reset(ap_rst),
    .address0(pixels_y_V_address0),
    .ce0(pixels_y_V_ce0),
    .we0(pixels_y_V_we0),
    .d0(fragment_y_V_reg_612),
    .q0(pixels_y_V_q0)
);

zculling_top_pixecud #(
    .DataWidth( 8 ),
    .AddressRange( 500 ),
    .AddressWidth( 9 ))
pixels_color_V_U(
    .clk(ap_clk),
    .reset(ap_rst),
    .address0(pixels_color_V_address0),
    .ce0(pixels_color_V_ce0),
    .we0(pixels_color_V_we0),
    .d0(fragment_color_V_reg_623),
    .q0(pixels_color_V_q0)
);

regslice_forward #(
    .DataWidth( 32 ))
regslice_forward_Output_1_V_V_U(
    .ap_clk(ap_clk),
    .ap_rst(ap_rst),
    .data_in(Output_1_V_V_int),
    .vld_in(Output_1_V_V_ap_vld_int),
    .ack_in(Output_1_V_V_ap_ack_int),
    .data_out(Output_1_V_V),
    .vld_out(regslice_forward_Output_1_V_V_U_vld_out),
    .ack_out(Output_1_V_V_ap_ack),
    .apdone_blk(regslice_forward_Output_1_V_V_U_apdone_blk)
);

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_CS_fsm <= ap_ST_fsm_state1;
    end else begin
        ap_CS_fsm <= ap_NS_fsm;
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp1_iter0 <= 1'b0;
    end else begin
        if (((1'b0 == ap_block_pp1_stage0_subdone) & (1'b1 == ap_condition_pp1_exit_iter0_state4) & (1'b1 == ap_CS_fsm_pp1_stage0))) begin
            ap_enable_reg_pp1_iter0 <= 1'b0;
        end else if ((1'b1 == ap_CS_fsm_state3)) begin
            ap_enable_reg_pp1_iter0 <= 1'b1;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp1_iter1 <= 1'b0;
    end else begin
        if ((((1'b0 == ap_block_pp1_stage1_subdone) & (1'b1 == ap_CS_fsm_pp1_stage1)) | ((1'b0 == ap_block_pp1_stage0_subdone) & (1'b1 == ap_CS_fsm_pp1_stage0)))) begin
            ap_enable_reg_pp1_iter1 <= ap_enable_reg_pp1_iter0;
        end else if ((1'b1 == ap_CS_fsm_state3)) begin
            ap_enable_reg_pp1_iter1 <= 1'b0;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp2_iter0 <= 1'b0;
    end else begin
        if (((1'b0 == ap_block_pp2_stage0_subdone) & (1'b1 == ap_condition_pp2_exit_iter0_state9) & (1'b1 == ap_CS_fsm_pp2_stage0))) begin
            ap_enable_reg_pp2_iter0 <= 1'b0;
        end else if (((1'b1 == Output_1_V_V_ap_ack_int) & (1'b1 == ap_CS_fsm_state8))) begin
            ap_enable_reg_pp2_iter0 <= 1'b1;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp2_iter1 <= 1'b0;
    end else begin
        if ((1'b0 == ap_block_pp2_stage0_subdone)) begin
            if ((1'b1 == ap_condition_pp2_exit_iter0_state9)) begin
                ap_enable_reg_pp2_iter1 <= (1'b1 ^ ap_condition_pp2_exit_iter0_state9);
            end else if ((1'b1 == 1'b1)) begin
                ap_enable_reg_pp2_iter1 <= ap_enable_reg_pp2_iter0;
            end
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp2_iter2 <= 1'b0;
    end else begin
        if ((1'b0 == ap_block_pp2_stage0_subdone)) begin
            ap_enable_reg_pp2_iter2 <= ap_enable_reg_pp2_iter1;
        end else if (((1'b1 == Output_1_V_V_ap_ack_int) & (1'b1 == ap_CS_fsm_state8))) begin
            ap_enable_reg_pp2_iter2 <= 1'b0;
        end
    end
end

always @ (posedge ap_clk) begin
    if (((icmp_ln1155_fu_483_p2 == 1'd0) & (1'b0 == ap_block_pp2_stage0_11001) & (ap_enable_reg_pp2_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp2_stage0))) begin
        i_op_assign_reg_281 <= j_fu_489_p2;
    end else if (((1'b1 == Output_1_V_V_ap_ack_int) & (1'b1 == ap_CS_fsm_state8))) begin
        i_op_assign_reg_281 <= 16'd0;
    end
end

always @ (posedge ap_clk) begin
    if ((~((ap_start == 1'b0) | ((odd_even_V == 1'd1) & (1'b0 == Input_2_V_V_ap_vld)) | ((odd_even_V == 1'd0) & (1'b0 == Input_1_V_V_ap_vld))) & (icmp_ln879_fu_303_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state1))) begin
        indvar_flatten_reg_226 <= 16'd0;
    end else if (((icmp_ln887_fu_309_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state2))) begin
        indvar_flatten_reg_226 <= add_ln887_fu_315_p2;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_condition_136)) begin
        if ((odd_even_V == 1'd1)) begin
            p_0344_0_in_reg_214 <= Input_2_V_V;
        end else if ((odd_even_V == 1'd0)) begin
            p_0344_0_in_reg_214 <= Input_1_V_V;
        end
    end
end

always @ (posedge ap_clk) begin
    if ((~((ap_start == 1'b0) | ((odd_even_V == 1'd1) & (1'b0 == Input_2_V_V_ap_vld)) | ((odd_even_V == 1'd0) & (1'b0 == Input_1_V_V_ap_vld))) & (icmp_ln879_fu_303_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state1))) begin
        t_V_1_reg_248 <= 9'd0;
    end else if (((icmp_ln887_fu_309_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state2))) begin
        t_V_1_reg_248 <= j_V_fu_376_p2;
    end
end

always @ (posedge ap_clk) begin
    if (((icmp_ln887_2_fu_402_p2 == 1'd1) & (icmp_ln1134_reg_595 == 1'd0) & (ap_enable_reg_pp1_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp1_stage0) & (1'b0 == ap_block_pp1_stage0_11001))) begin
        t_V_2_fu_112 <= pixel_cntr_V_fu_414_p2;
    end else if ((1'b1 == ap_CS_fsm_state3)) begin
        t_V_2_fu_112 <= 16'd0;
    end
end

always @ (posedge ap_clk) begin
    if (((icmp_ln1134_reg_595 == 1'd0) & (ap_enable_reg_pp1_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp1_stage0) & (1'b0 == ap_block_pp1_stage0_11001))) begin
        t_V_4_reg_259 <= n_V_reg_599;
    end else if ((1'b1 == ap_CS_fsm_state3)) begin
        t_V_4_reg_259 <= 16'd0;
    end
end

always @ (posedge ap_clk) begin
    if ((~((ap_start == 1'b0) | ((odd_even_V == 1'd1) & (1'b0 == Input_2_V_V_ap_vld)) | ((odd_even_V == 1'd0) & (1'b0 == Input_1_V_V_ap_vld))) & (icmp_ln879_fu_303_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state1))) begin
        t_V_reg_237 <= 8'd0;
    end else if (((icmp_ln887_fu_309_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state2))) begin
        t_V_reg_237 <= select_ln544_1_fu_341_p3;
    end
end

always @ (posedge ap_clk) begin
    if (((regslice_forward_Output_1_V_V_U_apdone_blk == 1'b0) & (1'b1 == ap_CS_fsm_state12))) begin
        counter_V <= select_ln1167_fu_537_p3;
        odd_even_V <= r_V_fu_520_p2;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state3)) begin
        empty_6_reg_590 <= empty_6_fu_382_p1;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == ap_CS_fsm_pp1_stage1) & (1'b0 == ap_block_pp1_stage1_11001))) begin
        fragment_color_V_reg_623 <= {{ap_phi_mux_p_Val2_s_phi_fu_273_p4[31:24]}};
        fragment_x_V_reg_607 <= fragment_x_V_fu_425_p1;
        fragment_y_V_reg_612 <= {{ap_phi_mux_p_Val2_s_phi_fu_273_p4[15:8]}};
        fragment_z_V_reg_617 <= {{ap_phi_mux_p_Val2_s_phi_fu_273_p4[23:16]}};
        z_buffer_V_addr_1_reg_628 <= sext_ln887_fu_473_p1;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == ap_CS_fsm_pp1_stage0) & (1'b0 == ap_block_pp1_stage0_11001))) begin
        icmp_ln1134_reg_595 <= icmp_ln1134_fu_391_p2;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b0 == ap_block_pp2_stage0_11001) & (1'b1 == ap_CS_fsm_pp2_stage0))) begin
        icmp_ln1155_reg_638 <= icmp_ln1155_fu_483_p2;
        icmp_ln1155_reg_638_pp2_iter1_reg <= icmp_ln1155_reg_638;
    end
end

always @ (posedge ap_clk) begin
    if (((ap_enable_reg_pp1_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp1_stage0) & (1'b0 == ap_block_pp1_stage0_11001))) begin
        n_V_reg_599 <= n_V_fu_396_p2;
    end
end

always @ (posedge ap_clk) begin
    if ((~((ap_start == 1'b0) | ((odd_even_V == 1'd1) & (1'b0 == Input_2_V_V_ap_vld)) | ((odd_even_V == 1'd0) & (1'b0 == Input_1_V_V_ap_vld))) & (1'b1 == ap_CS_fsm_state1))) begin
        odd_even_V_load_reg_551 <= odd_even_V;
        t_V_3_reg_556 <= counter_V;
    end
end

always @ (*) begin
    if ((((ap_predicate_op89_read_state6 == 1'b1) & (ap_enable_reg_pp1_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp1_stage1) & (1'b0 == ap_block_pp1_stage1_11001)) | (~((ap_start == 1'b0) | ((odd_even_V == 1'd1) & (1'b0 == Input_2_V_V_ap_vld)) | ((odd_even_V == 1'd0) & (1'b0 == Input_1_V_V_ap_vld))) & (odd_even_V == 1'd0) & (1'b1 == ap_CS_fsm_state1)))) begin
        Input_1_V_V_ap_ack = 1'b1;
    end else begin
        Input_1_V_V_ap_ack = 1'b0;
    end
end

always @ (*) begin
    if ((((1'b0 == ap_block_pp1_stage1) & (icmp_ln1134_reg_595 == 1'd0) & (odd_even_V_load_reg_551 == 1'd0) & (ap_enable_reg_pp1_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp1_stage1)) | ((odd_even_V == 1'd0) & (1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b1)))) begin
        Input_1_V_V_blk_n = Input_1_V_V_ap_vld;
    end else begin
        Input_1_V_V_blk_n = 1'b1;
    end
end

always @ (*) begin
    if ((((ap_predicate_op91_read_state6 == 1'b1) & (ap_enable_reg_pp1_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp1_stage1) & (1'b0 == ap_block_pp1_stage1_11001)) | (~((ap_start == 1'b0) | ((odd_even_V == 1'd1) & (1'b0 == Input_2_V_V_ap_vld)) | ((odd_even_V == 1'd0) & (1'b0 == Input_1_V_V_ap_vld))) & (odd_even_V == 1'd1) & (1'b1 == ap_CS_fsm_state1)))) begin
        Input_2_V_V_ap_ack = 1'b1;
    end else begin
        Input_2_V_V_ap_ack = 1'b0;
    end
end

always @ (*) begin
    if ((((odd_even_V_load_reg_551 == 1'd1) & (1'b0 == ap_block_pp1_stage1) & (icmp_ln1134_reg_595 == 1'd0) & (ap_enable_reg_pp1_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp1_stage1)) | ((odd_even_V == 1'd1) & (1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b1)))) begin
        Input_2_V_V_blk_n = Input_2_V_V_ap_vld;
    end else begin
        Input_2_V_V_blk_n = 1'b1;
    end
end

always @ (*) begin
    if ((((1'b1 == Output_1_V_V_ap_ack_int) & (1'b1 == ap_CS_fsm_state7)) | ((icmp_ln1155_reg_638 == 1'd0) & (1'b0 == ap_block_pp2_stage0_11001) & (ap_enable_reg_pp2_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp2_stage0)))) begin
        Output_1_V_V_ap_vld_int = 1'b1;
    end else begin
        Output_1_V_V_ap_vld_int = 1'b0;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state8) | (1'b1 == ap_CS_fsm_state7) | ((icmp_ln1155_reg_638_pp2_iter1_reg == 1'd0) & (ap_enable_reg_pp2_iter2 == 1'b1) & (1'b0 == ap_block_pp2_stage0)) | ((icmp_ln1155_reg_638 == 1'd0) & (ap_enable_reg_pp2_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp2_stage0) & (1'b0 == ap_block_pp2_stage0)))) begin
        Output_1_V_V_blk_n = Output_1_V_V_ap_ack_int;
    end else begin
        Output_1_V_V_blk_n = 1'b1;
    end
end

always @ (*) begin
    if (((icmp_ln1155_reg_638 == 1'd0) & (1'b0 == ap_block_pp2_stage0_01001) & (ap_enable_reg_pp2_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp2_stage0))) begin
        Output_1_V_V_int = p_Result_s_fu_502_p5;
    end else if ((1'b1 == ap_CS_fsm_state7)) begin
        Output_1_V_V_int = tmp_V_2_fu_478_p1;
    end else begin
        Output_1_V_V_int = 'bx;
    end
end

always @ (*) begin
    if ((icmp_ln1134_fu_391_p2 == 1'd1)) begin
        ap_condition_pp1_exit_iter0_state4 = 1'b1;
    end else begin
        ap_condition_pp1_exit_iter0_state4 = 1'b0;
    end
end

always @ (*) begin
    if ((icmp_ln1155_fu_483_p2 == 1'd1)) begin
        ap_condition_pp2_exit_iter0_state9 = 1'b1;
    end else begin
        ap_condition_pp2_exit_iter0_state9 = 1'b0;
    end
end

always @ (*) begin
    if (((regslice_forward_Output_1_V_V_U_apdone_blk == 1'b0) & (1'b1 == ap_CS_fsm_state12))) begin
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
    if (((ap_enable_reg_pp1_iter0 == 1'b0) & (ap_enable_reg_pp1_iter1 == 1'b0))) begin
        ap_idle_pp1 = 1'b1;
    end else begin
        ap_idle_pp1 = 1'b0;
    end
end

always @ (*) begin
    if (((ap_enable_reg_pp2_iter0 == 1'b0) & (ap_enable_reg_pp2_iter2 == 1'b0) & (ap_enable_reg_pp2_iter1 == 1'b0))) begin
        ap_idle_pp2 = 1'b1;
    end else begin
        ap_idle_pp2 = 1'b0;
    end
end

always @ (*) begin
    if ((icmp_ln1134_reg_595 == 1'd0)) begin
        if ((odd_even_V_load_reg_551 == 1'd1)) begin
            ap_phi_mux_p_Val2_s_phi_fu_273_p4 = Input_2_V_V;
        end else if ((odd_even_V_load_reg_551 == 1'd0)) begin
            ap_phi_mux_p_Val2_s_phi_fu_273_p4 = Input_1_V_V;
        end else begin
            ap_phi_mux_p_Val2_s_phi_fu_273_p4 = ap_phi_reg_pp1_iter0_p_Val2_s_reg_270;
        end
    end else begin
        ap_phi_mux_p_Val2_s_phi_fu_273_p4 = ap_phi_reg_pp1_iter0_p_Val2_s_reg_270;
    end
end

always @ (*) begin
    if (((icmp_ln1134_reg_595 == 1'd0) & (1'b0 == ap_block_pp1_stage0) & (ap_enable_reg_pp1_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp1_stage0))) begin
        ap_phi_mux_t_V_4_phi_fu_263_p4 = n_V_reg_599;
    end else begin
        ap_phi_mux_t_V_4_phi_fu_263_p4 = t_V_4_reg_259;
    end
end

always @ (*) begin
    if (((regslice_forward_Output_1_V_V_U_apdone_blk == 1'b0) & (1'b1 == ap_CS_fsm_state12))) begin
        ap_ready = 1'b1;
    end else begin
        ap_ready = 1'b0;
    end
end

always @ (*) begin
    if (((ap_enable_reg_pp2_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp2_stage0) & (1'b0 == ap_block_pp2_stage0))) begin
        pixels_color_V_address0 = zext_ln1157_fu_495_p1;
    end else if (((1'b0 == ap_block_pp1_stage0) & (ap_enable_reg_pp1_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp1_stage0))) begin
        pixels_color_V_address0 = zext_ln544_fu_407_p1;
    end else begin
        pixels_color_V_address0 = 'bx;
    end
end

always @ (*) begin
    if ((((ap_enable_reg_pp1_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp1_stage0) & (1'b0 == ap_block_pp1_stage0_11001)) | ((1'b0 == ap_block_pp2_stage0_11001) & (ap_enable_reg_pp2_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp2_stage0)))) begin
        pixels_color_V_ce0 = 1'b1;
    end else begin
        pixels_color_V_ce0 = 1'b0;
    end
end

always @ (*) begin
    if (((icmp_ln887_2_fu_402_p2 == 1'd1) & (icmp_ln1134_reg_595 == 1'd0) & (ap_enable_reg_pp1_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp1_stage0) & (1'b0 == ap_block_pp1_stage0_11001))) begin
        pixels_color_V_we0 = 1'b1;
    end else begin
        pixels_color_V_we0 = 1'b0;
    end
end

always @ (*) begin
    if (((ap_enable_reg_pp2_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp2_stage0) & (1'b0 == ap_block_pp2_stage0))) begin
        pixels_x_V_address0 = zext_ln1157_fu_495_p1;
    end else if (((1'b0 == ap_block_pp1_stage0) & (ap_enable_reg_pp1_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp1_stage0))) begin
        pixels_x_V_address0 = zext_ln544_fu_407_p1;
    end else begin
        pixels_x_V_address0 = 'bx;
    end
end

always @ (*) begin
    if ((((ap_enable_reg_pp1_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp1_stage0) & (1'b0 == ap_block_pp1_stage0_11001)) | ((1'b0 == ap_block_pp2_stage0_11001) & (ap_enable_reg_pp2_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp2_stage0)))) begin
        pixels_x_V_ce0 = 1'b1;
    end else begin
        pixels_x_V_ce0 = 1'b0;
    end
end

always @ (*) begin
    if (((icmp_ln887_2_fu_402_p2 == 1'd1) & (icmp_ln1134_reg_595 == 1'd0) & (ap_enable_reg_pp1_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp1_stage0) & (1'b0 == ap_block_pp1_stage0_11001))) begin
        pixels_x_V_we0 = 1'b1;
    end else begin
        pixels_x_V_we0 = 1'b0;
    end
end

always @ (*) begin
    if (((ap_enable_reg_pp2_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp2_stage0) & (1'b0 == ap_block_pp2_stage0))) begin
        pixels_y_V_address0 = zext_ln1157_fu_495_p1;
    end else if (((1'b0 == ap_block_pp1_stage0) & (ap_enable_reg_pp1_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp1_stage0))) begin
        pixels_y_V_address0 = zext_ln544_fu_407_p1;
    end else begin
        pixels_y_V_address0 = 'bx;
    end
end

always @ (*) begin
    if ((((ap_enable_reg_pp1_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp1_stage0) & (1'b0 == ap_block_pp1_stage0_11001)) | ((1'b0 == ap_block_pp2_stage0_11001) & (ap_enable_reg_pp2_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp2_stage0)))) begin
        pixels_y_V_ce0 = 1'b1;
    end else begin
        pixels_y_V_ce0 = 1'b0;
    end
end

always @ (*) begin
    if (((icmp_ln887_2_fu_402_p2 == 1'd1) & (icmp_ln1134_reg_595 == 1'd0) & (ap_enable_reg_pp1_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp1_stage0) & (1'b0 == ap_block_pp1_stage0_11001))) begin
        pixels_y_V_we0 = 1'b1;
    end else begin
        pixels_y_V_we0 = 1'b0;
    end
end

always @ (*) begin
    if (((1'b0 == ap_block_pp1_stage1) & (ap_enable_reg_pp1_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp1_stage1))) begin
        z_buffer_V_address0 = sext_ln887_fu_473_p1;
    end else if (((1'b0 == ap_block_pp1_stage0) & (ap_enable_reg_pp1_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp1_stage0))) begin
        z_buffer_V_address0 = z_buffer_V_addr_1_reg_628;
    end else if ((1'b1 == ap_CS_fsm_state2)) begin
        z_buffer_V_address0 = zext_ln321_1_fu_371_p1;
    end else begin
        z_buffer_V_address0 = 'bx;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state2) | ((ap_enable_reg_pp1_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp1_stage1) & (1'b0 == ap_block_pp1_stage1_11001)) | ((ap_enable_reg_pp1_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp1_stage0) & (1'b0 == ap_block_pp1_stage0_11001)))) begin
        z_buffer_V_ce0 = 1'b1;
    end else begin
        z_buffer_V_ce0 = 1'b0;
    end
end

always @ (*) begin
    if (((1'b0 == ap_block_pp1_stage0) & (ap_enable_reg_pp1_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp1_stage0))) begin
        z_buffer_V_d0 = fragment_z_V_reg_617;
    end else if ((1'b1 == ap_CS_fsm_state2)) begin
        z_buffer_V_d0 = 8'd255;
    end else begin
        z_buffer_V_d0 = 'bx;
    end
end

always @ (*) begin
    if ((((icmp_ln887_2_fu_402_p2 == 1'd1) & (icmp_ln1134_reg_595 == 1'd0) & (ap_enable_reg_pp1_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp1_stage0) & (1'b0 == ap_block_pp1_stage0_11001)) | ((icmp_ln887_fu_309_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state2)))) begin
        z_buffer_V_we0 = 1'b1;
    end else begin
        z_buffer_V_we0 = 1'b0;
    end
end

always @ (*) begin
    case (ap_CS_fsm)
        ap_ST_fsm_state1 : begin
            if ((~((ap_start == 1'b0) | ((odd_even_V == 1'd1) & (1'b0 == Input_2_V_V_ap_vld)) | ((odd_even_V == 1'd0) & (1'b0 == Input_1_V_V_ap_vld))) & (icmp_ln879_fu_303_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state1))) begin
                ap_NS_fsm = ap_ST_fsm_state2;
            end else if ((~((ap_start == 1'b0) | ((odd_even_V == 1'd1) & (1'b0 == Input_2_V_V_ap_vld)) | ((odd_even_V == 1'd0) & (1'b0 == Input_1_V_V_ap_vld))) & (icmp_ln879_fu_303_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state1))) begin
                ap_NS_fsm = ap_ST_fsm_state3;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state1;
            end
        end
        ap_ST_fsm_state2 : begin
            if (((icmp_ln887_fu_309_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state2))) begin
                ap_NS_fsm = ap_ST_fsm_state2;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state3;
            end
        end
        ap_ST_fsm_state3 : begin
            ap_NS_fsm = ap_ST_fsm_pp1_stage0;
        end
        ap_ST_fsm_pp1_stage0 : begin
            if ((~((icmp_ln1134_fu_391_p2 == 1'd1) & (1'b0 == ap_block_pp1_stage0_subdone) & (ap_enable_reg_pp1_iter0 == 1'b1)) & (1'b0 == ap_block_pp1_stage0_subdone))) begin
                ap_NS_fsm = ap_ST_fsm_pp1_stage1;
            end else if (((icmp_ln1134_fu_391_p2 == 1'd1) & (1'b0 == ap_block_pp1_stage0_subdone) & (ap_enable_reg_pp1_iter0 == 1'b1))) begin
                ap_NS_fsm = ap_ST_fsm_state7;
            end else begin
                ap_NS_fsm = ap_ST_fsm_pp1_stage0;
            end
        end
        ap_ST_fsm_pp1_stage1 : begin
            if ((1'b0 == ap_block_pp1_stage1_subdone)) begin
                ap_NS_fsm = ap_ST_fsm_pp1_stage0;
            end else begin
                ap_NS_fsm = ap_ST_fsm_pp1_stage1;
            end
        end
        ap_ST_fsm_state7 : begin
            if (((1'b1 == Output_1_V_V_ap_ack_int) & (1'b1 == ap_CS_fsm_state7))) begin
                ap_NS_fsm = ap_ST_fsm_state8;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state7;
            end
        end
        ap_ST_fsm_state8 : begin
            if (((1'b1 == Output_1_V_V_ap_ack_int) & (1'b1 == ap_CS_fsm_state8))) begin
                ap_NS_fsm = ap_ST_fsm_pp2_stage0;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state8;
            end
        end
        ap_ST_fsm_pp2_stage0 : begin
            if ((~((icmp_ln1155_fu_483_p2 == 1'd1) & (1'b0 == ap_block_pp2_stage0_subdone) & (ap_enable_reg_pp2_iter0 == 1'b1) & (ap_enable_reg_pp2_iter1 == 1'b0)) & ~((1'b0 == ap_block_pp2_stage0_subdone) & (ap_enable_reg_pp2_iter2 == 1'b1) & (ap_enable_reg_pp2_iter1 == 1'b0)))) begin
                ap_NS_fsm = ap_ST_fsm_pp2_stage0;
            end else if ((((icmp_ln1155_fu_483_p2 == 1'd1) & (1'b0 == ap_block_pp2_stage0_subdone) & (ap_enable_reg_pp2_iter0 == 1'b1) & (ap_enable_reg_pp2_iter1 == 1'b0)) | ((1'b0 == ap_block_pp2_stage0_subdone) & (ap_enable_reg_pp2_iter2 == 1'b1) & (ap_enable_reg_pp2_iter1 == 1'b0)))) begin
                ap_NS_fsm = ap_ST_fsm_state12;
            end else begin
                ap_NS_fsm = ap_ST_fsm_pp2_stage0;
            end
        end
        ap_ST_fsm_state12 : begin
            if (((regslice_forward_Output_1_V_V_U_apdone_blk == 1'b0) & (1'b1 == ap_CS_fsm_state12))) begin
                ap_NS_fsm = ap_ST_fsm_state1;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state12;
            end
        end
        default : begin
            ap_NS_fsm = 'bx;
        end
    endcase
end

assign Output_1_V_V_ap_vld = regslice_forward_Output_1_V_V_U_vld_out;

assign add_ln321_fu_365_p2 = (zext_ln321_fu_361_p1 + zext_ln1122_fu_357_p1);

assign add_ln700_fu_515_p2 = (t_V_3_reg_556 + 16'd1);

assign add_ln887_fu_315_p2 = (indvar_flatten_reg_226 + 16'd1);

assign ap_CS_fsm_pp1_stage0 = ap_CS_fsm[32'd3];

assign ap_CS_fsm_pp1_stage1 = ap_CS_fsm[32'd4];

assign ap_CS_fsm_pp2_stage0 = ap_CS_fsm[32'd7];

assign ap_CS_fsm_state1 = ap_CS_fsm[32'd0];

assign ap_CS_fsm_state12 = ap_CS_fsm[32'd8];

assign ap_CS_fsm_state2 = ap_CS_fsm[32'd1];

assign ap_CS_fsm_state3 = ap_CS_fsm[32'd2];

assign ap_CS_fsm_state7 = ap_CS_fsm[32'd5];

assign ap_CS_fsm_state8 = ap_CS_fsm[32'd6];

assign ap_block_pp1_stage0 = ~(1'b1 == 1'b1);

assign ap_block_pp1_stage0_11001 = ~(1'b1 == 1'b1);

assign ap_block_pp1_stage0_subdone = ~(1'b1 == 1'b1);

assign ap_block_pp1_stage1 = ~(1'b1 == 1'b1);

always @ (*) begin
    ap_block_pp1_stage1_11001 = ((ap_enable_reg_pp1_iter0 == 1'b1) & (((1'b0 == Input_2_V_V_ap_vld) & (ap_predicate_op91_read_state6 == 1'b1)) | ((1'b0 == Input_1_V_V_ap_vld) & (ap_predicate_op89_read_state6 == 1'b1))));
end

always @ (*) begin
    ap_block_pp1_stage1_subdone = ((ap_enable_reg_pp1_iter0 == 1'b1) & (((1'b0 == Input_2_V_V_ap_vld) & (ap_predicate_op91_read_state6 == 1'b1)) | ((1'b0 == Input_1_V_V_ap_vld) & (ap_predicate_op89_read_state6 == 1'b1))));
end

assign ap_block_pp2_stage0 = ~(1'b1 == 1'b1);

assign ap_block_pp2_stage0_01001 = ~(1'b1 == 1'b1);

always @ (*) begin
    ap_block_pp2_stage0_11001 = (((1'b1 == ap_block_state11_io) & (ap_enable_reg_pp2_iter2 == 1'b1)) | ((1'b1 == ap_block_state10_io) & (ap_enable_reg_pp2_iter1 == 1'b1)));
end

always @ (*) begin
    ap_block_pp2_stage0_subdone = (((1'b1 == ap_block_state11_io) & (ap_enable_reg_pp2_iter2 == 1'b1)) | ((1'b1 == ap_block_state10_io) & (ap_enable_reg_pp2_iter1 == 1'b1)));
end

always @ (*) begin
    ap_block_state1 = ((ap_start == 1'b0) | ((odd_even_V == 1'd1) & (1'b0 == Input_2_V_V_ap_vld)) | ((odd_even_V == 1'd0) & (1'b0 == Input_1_V_V_ap_vld)));
end

always @ (*) begin
    ap_block_state10_io = ((icmp_ln1155_reg_638 == 1'd0) & (1'b0 == Output_1_V_V_ap_ack_int));
end

assign ap_block_state10_pp2_stage0_iter1 = ~(1'b1 == 1'b1);

always @ (*) begin
    ap_block_state11_io = ((icmp_ln1155_reg_638_pp2_iter1_reg == 1'd0) & (1'b0 == Output_1_V_V_ap_ack_int));
end

assign ap_block_state11_pp2_stage0_iter2 = ~(1'b1 == 1'b1);

assign ap_block_state4_pp1_stage0_iter0 = ~(1'b1 == 1'b1);

assign ap_block_state5_pp1_stage0_iter1 = ~(1'b1 == 1'b1);

always @ (*) begin
    ap_block_state6_pp1_stage1_iter0 = (((1'b0 == Input_2_V_V_ap_vld) & (ap_predicate_op91_read_state6 == 1'b1)) | ((1'b0 == Input_1_V_V_ap_vld) & (ap_predicate_op89_read_state6 == 1'b1)));
end

assign ap_block_state9_pp2_stage0_iter0 = ~(1'b1 == 1'b1);

always @ (*) begin
    ap_condition_136 = (~((ap_start == 1'b0) | ((odd_even_V == 1'd1) & (1'b0 == Input_2_V_V_ap_vld)) | ((odd_even_V == 1'd0) & (1'b0 == Input_1_V_V_ap_vld))) & (1'b1 == ap_CS_fsm_state1));
end

assign ap_enable_pp1 = (ap_idle_pp1 ^ 1'b1);

assign ap_enable_pp2 = (ap_idle_pp2 ^ 1'b1);

assign ap_phi_reg_pp1_iter0_p_Val2_s_reg_270 = 'bx;

always @ (*) begin
    ap_predicate_op89_read_state6 = ((icmp_ln1134_reg_595 == 1'd0) & (odd_even_V_load_reg_551 == 1'd0));
end

always @ (*) begin
    ap_predicate_op91_read_state6 = ((odd_even_V_load_reg_551 == 1'd1) & (icmp_ln1134_reg_595 == 1'd0));
end

assign empty_6_fu_382_p1 = p_0344_0_in_reg_214[15:0];

assign fragment_x_V_fu_425_p1 = ap_phi_mux_p_Val2_s_phi_fu_273_p4[7:0];

assign fragment_y_V_fu_429_p4 = {{ap_phi_mux_p_Val2_s_phi_fu_273_p4[15:8]}};

assign i_V_fu_321_p2 = (t_V_reg_237 + 8'd1);

assign icmp_ln1134_fu_391_p2 = ((ap_phi_mux_t_V_4_phi_fu_263_p4 == empty_6_reg_590) ? 1'b1 : 1'b0);

assign icmp_ln1155_fu_483_p2 = ((i_op_assign_reg_281 == t_V_2_fu_112) ? 1'b1 : 1'b0);

assign icmp_ln879_1_fu_531_p2 = ((add_ln700_fu_515_p2 == 16'd3192) ? 1'b1 : 1'b0);

assign icmp_ln879_fu_303_p2 = ((counter_V == 16'd0) ? 1'b1 : 1'b0);

assign icmp_ln887_1_fu_327_p2 = ((t_V_1_reg_248 == 9'd256) ? 1'b1 : 1'b0);

assign icmp_ln887_2_fu_402_p2 = ((fragment_z_V_reg_617 < z_buffer_V_q0) ? 1'b1 : 1'b0);

assign icmp_ln887_fu_309_p2 = ((indvar_flatten_reg_226 == 16'd32768) ? 1'b1 : 1'b0);

assign j_V_fu_376_p2 = (select_ln544_fu_333_p3 + 9'd1);

assign j_fu_489_p2 = (i_op_assign_reg_281 + 16'd1);

assign n_V_fu_396_p2 = (ap_phi_mux_t_V_4_phi_fu_263_p4 + 16'd1);

assign p_Result_s_fu_502_p5 = {{{{{{8'd0}, {pixels_color_V_q0}}}, {pixels_y_V_q0}}}, {pixels_x_V_q0}};

assign pixel_cntr_V_fu_414_p2 = (t_V_2_fu_112 + 16'd1);

assign r_V_fu_520_p2 = (odd_even_V_load_reg_551 ^ 1'd1);

assign ret_V_fu_459_p2 = (fragment_y_V_fu_429_p4 ^ 8'd128);

assign select_ln1167_fu_537_p3 = ((icmp_ln879_1_fu_531_p2[0:0] === 1'b1) ? 16'd0 : add_ln700_fu_515_p2);

assign select_ln544_1_fu_341_p3 = ((icmp_ln887_1_fu_327_p2[0:0] === 1'b1) ? i_V_fu_321_p2 : t_V_reg_237);

assign select_ln544_fu_333_p3 = ((icmp_ln887_1_fu_327_p2[0:0] === 1'b1) ? 9'd0 : t_V_1_reg_248);

assign sext_ln887_fu_473_p1 = $signed(tmp_5_fu_465_p3);

assign tmp_5_fu_465_p3 = {{ret_V_fu_459_p2}, {fragment_x_V_fu_425_p1}};

assign tmp_V_2_fu_478_p1 = t_V_2_fu_112;

assign tmp_fu_349_p3 = {{select_ln544_1_fu_341_p3}, {8'd0}};

assign zext_ln1122_fu_357_p1 = tmp_fu_349_p3;

assign zext_ln1157_fu_495_p1 = i_op_assign_reg_281;

assign zext_ln321_1_fu_371_p1 = add_ln321_fu_365_p2;

assign zext_ln321_fu_361_p1 = select_ln544_fu_333_p3;

assign zext_ln544_fu_407_p1 = t_V_2_fu_112;

endmodule //zculling_top
