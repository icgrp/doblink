// ==============================================================
// RTL generated by Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Version: 2020.2
// Copyright (C) Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

`timescale 1 ns / 1 ps 

(* CORE_GENERATION_INFO="update_knn1_update_knn1,hls_ip_2020_2,{HLS_INPUT_TYPE=cxx,HLS_INPUT_FLOAT=0,HLS_INPUT_FIXED=0,HLS_INPUT_PART=xc7a200t-sbg484-1,HLS_INPUT_CLOCK=4.000000,HLS_INPUT_ARCH=dataflow,HLS_SYN_CLOCK=3.678000,HLS_SYN_LAT=91446,HLS_SYN_TPT=37427,HLS_SYN_MEM=32,HLS_SYN_DSP=0,HLS_SYN_FF=10548,HLS_SYN_LUT=10949,HLS_VERSION=2020_2}" *)

module update_knn1 (
        Input_1_V_TDATA,
        Output_1_V_TDATA,
        ap_clk,
        ap_rst_n,
        Input_1_V_TVALID,
        Input_1_V_TREADY,
        ap_start,
        Output_1_V_TVALID,
        Output_1_V_TREADY,
        ap_done,
        ap_ready,
        ap_idle
);


input  [31:0] Input_1_V_TDATA;
output  [31:0] Output_1_V_TDATA;
input   ap_clk;
input   ap_rst_n;
input   Input_1_V_TVALID;
output   Input_1_V_TREADY;
input   ap_start;
output   Output_1_V_TVALID;
input   Output_1_V_TREADY;
output   ap_done;
output   ap_ready;
output   ap_idle;

 reg    ap_rst_n_inv;
wire    update_knn1_sub_U0_ap_start;
wire    update_knn1_sub_U0_ap_done;
wire    update_knn1_sub_U0_ap_continue;
wire    update_knn1_sub_U0_ap_idle;
wire    update_knn1_sub_U0_ap_ready;
wire    update_knn1_sub_U0_start_out;
wire    update_knn1_sub_U0_start_write;
wire    update_knn1_sub_U0_Input_1_V_TREADY;
wire   [31:0] update_knn1_sub_U0_Output_1_din;
wire    update_knn1_sub_U0_Output_1_write;
wire    update_knn2_sub_U0_ap_start;
wire    update_knn2_sub_U0_ap_done;
wire    update_knn2_sub_U0_ap_continue;
wire    update_knn2_sub_U0_ap_idle;
wire    update_knn2_sub_U0_ap_ready;
wire    update_knn2_sub_U0_Input_1_read;
wire   [31:0] update_knn2_sub_U0_Output_1_V_TDATA;
wire    update_knn2_sub_U0_Output_1_V_TVALID;
wire    ap_sync_continue;
wire    knn_out1_full_n;
wire   [31:0] knn_out1_dout;
wire    knn_out1_empty_n;
wire    ap_sync_done;
wire    ap_sync_ready;
wire   [0:0] start_for_update_knn2_sub_U0_din;
wire    start_for_update_knn2_sub_U0_full_n;
wire   [0:0] start_for_update_knn2_sub_U0_dout;
wire    start_for_update_knn2_sub_U0_empty_n;
wire    update_knn2_sub_U0_start_full_n;
wire    update_knn2_sub_U0_start_write;

update_knn1_update_knn1_sub update_knn1_sub_U0(
    .ap_clk(ap_clk),
    .ap_rst(ap_rst_n_inv),
    .ap_start(update_knn1_sub_U0_ap_start),
    .start_full_n(start_for_update_knn2_sub_U0_full_n),
    .ap_done(update_knn1_sub_U0_ap_done),
    .ap_continue(update_knn1_sub_U0_ap_continue),
    .ap_idle(update_knn1_sub_U0_ap_idle),
    .ap_ready(update_knn1_sub_U0_ap_ready),
    .start_out(update_knn1_sub_U0_start_out),
    .start_write(update_knn1_sub_U0_start_write),
    .Input_1_V_TDATA(Input_1_V_TDATA),
    .Input_1_V_TVALID(Input_1_V_TVALID),
    .Input_1_V_TREADY(update_knn1_sub_U0_Input_1_V_TREADY),
    .Output_1_din(update_knn1_sub_U0_Output_1_din),
    .Output_1_full_n(knn_out1_full_n),
    .Output_1_write(update_knn1_sub_U0_Output_1_write)
);

update_knn1_update_knn2_sub update_knn2_sub_U0(
    .ap_clk(ap_clk),
    .ap_rst(ap_rst_n_inv),
    .ap_start(update_knn2_sub_U0_ap_start),
    .ap_done(update_knn2_sub_U0_ap_done),
    .ap_continue(update_knn2_sub_U0_ap_continue),
    .ap_idle(update_knn2_sub_U0_ap_idle),
    .ap_ready(update_knn2_sub_U0_ap_ready),
    .Input_1_dout(knn_out1_dout),
    .Input_1_empty_n(knn_out1_empty_n),
    .Input_1_read(update_knn2_sub_U0_Input_1_read),
    .Output_1_V_TDATA(update_knn2_sub_U0_Output_1_V_TDATA),
    .Output_1_V_TVALID(update_knn2_sub_U0_Output_1_V_TVALID),
    .Output_1_V_TREADY(Output_1_V_TREADY)
);

update_knn1_fifo_w32_d1024_A knn_out1_U(
    .clk(ap_clk),
    .reset(ap_rst_n_inv),
    .if_read_ce(1'b1),
    .if_write_ce(1'b1),
    .if_din(update_knn1_sub_U0_Output_1_din),
    .if_full_n(knn_out1_full_n),
    .if_write(update_knn1_sub_U0_Output_1_write),
    .if_dout(knn_out1_dout),
    .if_empty_n(knn_out1_empty_n),
    .if_read(update_knn2_sub_U0_Input_1_read)
);

update_knn1_start_for_update_knn2_sub_U0 start_for_update_knn2_sub_U0_U(
    .clk(ap_clk),
    .reset(ap_rst_n_inv),
    .if_read_ce(1'b1),
    .if_write_ce(1'b1),
    .if_din(start_for_update_knn2_sub_U0_din),
    .if_full_n(start_for_update_knn2_sub_U0_full_n),
    .if_write(update_knn1_sub_U0_start_write),
    .if_dout(start_for_update_knn2_sub_U0_dout),
    .if_empty_n(start_for_update_knn2_sub_U0_empty_n),
    .if_read(update_knn2_sub_U0_ap_ready)
);

assign Input_1_V_TREADY = update_knn1_sub_U0_Input_1_V_TREADY;

assign Output_1_V_TDATA = update_knn2_sub_U0_Output_1_V_TDATA;

assign Output_1_V_TVALID = update_knn2_sub_U0_Output_1_V_TVALID;

assign ap_done = update_knn2_sub_U0_ap_done;

assign ap_idle = (update_knn2_sub_U0_ap_idle & update_knn1_sub_U0_ap_idle);

assign ap_ready = update_knn1_sub_U0_ap_ready;

always @ (*) begin
    ap_rst_n_inv = ~ap_rst_n;
end

assign ap_sync_continue = 1'b1;

assign ap_sync_done = update_knn2_sub_U0_ap_done;

assign ap_sync_ready = update_knn1_sub_U0_ap_ready;

assign start_for_update_knn2_sub_U0_din = 1'b1;

assign update_knn1_sub_U0_ap_continue = 1'b1;

assign update_knn1_sub_U0_ap_start = ap_start;

assign update_knn2_sub_U0_ap_continue = 1'b1;

assign update_knn2_sub_U0_ap_start = start_for_update_knn2_sub_U0_empty_n;

assign update_knn2_sub_U0_start_full_n = 1'b1;

assign update_knn2_sub_U0_start_write = 1'b0;

endmodule //update_knn1
