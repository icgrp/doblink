//Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2020.2 (lin64) Build 3064766 Wed Nov 18 09:12:47 MST 2020
//Date        : Mon Jun 21 12:36:32 2021
//Host        : stingy running 64-bit Ubuntu 20.04.1 LTS
//Command     : generate_target top.bd
//Design      : top
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CORE_GENERATION_INFO = "top,IP_Integrator,{x_ipVendor=xilinx.com,x_ipLibrary=BlockDiagram,x_ipName=top,x_ipVersion=1.00.a,x_ipLanguage=VERILOG,numBlks=2,numReposBlks=2,numNonXlnxBlks=0,numHierBlks=0,maxHierDepth=0,numSysgenBlks=0,numHlsBlks=0,numHdlrefBlks=2,numPkgbdBlks=0,bdsource=USER,synth_mode=OOC_per_IP}" *) (* HW_HANDOFF = "top.hwdef" *) 
module top
   (clk100,
    clk_bft_3,
     clk_bft_4,
     clk_bft_5,
     clk_bft_6,
     clk_bft_7,
     clk_bft_8,
     clk_bft_9,
     clk_bft_10,
     clk_bft_11,
     clk_bft_12,
     clk_bft_13,
     clk_bft_14,
    cpu_reset,
    ddram_a,
    ddram_ba,
    ddram_cas_n,
    ddram_cke,
    ddram_clk_n,
    ddram_clk_p,
    ddram_dm,
    ddram_dq,
    ddram_dqs_n,
    ddram_dqs_p,
    ddram_odt,
    ddram_ras_n,
    ddram_reset_n,
    ddram_we_n,
    din_leaf_10,
    din_leaf_11,
    din_leaf_12,
    din_leaf_13,
    din_leaf_14,
    din_leaf_3,
    din_leaf_4,
    din_leaf_5,
    din_leaf_6,
    din_leaf_7,
    din_leaf_8,
    din_leaf_9,
    dout_leaf_10,
    dout_leaf_11,
    dout_leaf_12,
    dout_leaf_13,
    dout_leaf_14,
    dout_leaf_15,
    dout_leaf_3,
    dout_leaf_4,
    dout_leaf_5,
    dout_leaf_6,
    dout_leaf_7,
    dout_leaf_8,
    dout_leaf_9,
    resend_10,
    resend_11,
    resend_12,
    resend_13,
    resend_14,
    resend_3,
    resend_4,
    resend_5,
    resend_6,
    resend_7,
    resend_8,
    resend_9,
    rst_bft_3,
     rst_bft_4,
     rst_bft_5,
     rst_bft_6,
     rst_bft_7,
     rst_bft_8,
     rst_bft_9,
     rst_bft_10,
     rst_bft_11,
     rst_bft_12,
     rst_bft_13,
     rst_bft_14,
     start_signal_3,
     start_signal_4,
     start_signal_5,
     start_signal_6,
     start_signal_7,
     start_signal_8,
     start_signal_9,
     start_signal_10,
     start_signal_11,
     start_signal_12,
     start_signal_13,
     start_signal_14,
    serial_rx,
    serial_tx,
    user_led0,
    user_led1,
    user_sw0,
    user_sw1);
  (* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 CLK.CLK100 CLK" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME CLK.CLK100, CLK_DOMAIN floorplan_static_clk100, FREQ_HZ 100000000, FREQ_TOLERANCE_HZ 0, INSERT_VIP 0, PHASE 0.000" *) input clk100;
  
  output clk_bft_3;
     output clk_bft_4;
     output clk_bft_5;
     output clk_bft_6;
     output clk_bft_7;
     output clk_bft_8;
     output clk_bft_9;
     output clk_bft_10;
     output clk_bft_11;
     output clk_bft_12;
     output clk_bft_13;
     output clk_bft_14;
  (* X_INTERFACE_INFO = "xilinx.com:signal:reset:1.0 RST.CPU_RESET RST" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME RST.CPU_RESET, INSERT_VIP 0, POLARITY ACTIVE_LOW" *) input cpu_reset;
  output [14:0]ddram_a;
  output [2:0]ddram_ba;
  output ddram_cas_n;
  output ddram_cke;
  (* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 CLK.DDRAM_CLK_N CLK" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME CLK.DDRAM_CLK_N, CLK_DOMAIN top_nexys_video_0_0_ddram_clk_n, FREQ_HZ 100000000, FREQ_TOLERANCE_HZ 0, INSERT_VIP 0, PHASE 0.000" *) output ddram_clk_n;
  (* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 CLK.DDRAM_CLK_P CLK" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME CLK.DDRAM_CLK_P, CLK_DOMAIN top_nexys_video_0_0_ddram_clk_p, FREQ_HZ 100000000, FREQ_TOLERANCE_HZ 0, INSERT_VIP 0, PHASE 0.000" *) output ddram_clk_p;
  output [1:0]ddram_dm;
  inout [15:0]ddram_dq;
  inout [1:0]ddram_dqs_n;
  inout [1:0]ddram_dqs_p;
  output ddram_odt;
  output ddram_ras_n;
  output ddram_reset_n;
  output ddram_we_n;
  output [48:0]din_leaf_10;
  output [48:0]din_leaf_11;
  output [48:0]din_leaf_12;
  output [48:0]din_leaf_13;
  output [48:0]din_leaf_14;
  output [48:0]din_leaf_3;
  output [48:0]din_leaf_4;
  output [48:0]din_leaf_5;
  output [48:0]din_leaf_6;
  output [48:0]din_leaf_7;
  output [48:0]din_leaf_8;
  output [48:0]din_leaf_9;
  input [48:0]dout_leaf_10;
  input [48:0]dout_leaf_11;
  input [48:0]dout_leaf_12;
  input [48:0]dout_leaf_13;
  input [48:0]dout_leaf_14;
  input [48:0]dout_leaf_15;
  input [48:0]dout_leaf_3;
  input [48:0]dout_leaf_4;
  input [48:0]dout_leaf_5;
  input [48:0]dout_leaf_6;
  input [48:0]dout_leaf_7;
  input [48:0]dout_leaf_8;
  input [48:0]dout_leaf_9;
  output resend_10;
  output resend_11;
  output resend_12;
  output resend_13;
  output resend_14;
  output resend_3;
  output resend_4;
  output resend_5;
  output resend_6;
  output resend_7;
  output resend_8;
  output resend_9;
  output rst_bft_3;
     output rst_bft_4;
     output rst_bft_5;
     output rst_bft_6;
     output rst_bft_7;
     output rst_bft_8;
     output rst_bft_9;
     output rst_bft_10;
     output rst_bft_11;
     output rst_bft_12;
     output rst_bft_13;
     output rst_bft_14;
     output start_signal_3;
     output start_signal_4;
     output start_signal_5;
     output start_signal_6;
     output start_signal_7;
     output start_signal_8;
     output start_signal_9;
     output start_signal_10;
     output start_signal_11;
     output start_signal_12;
     output start_signal_13;
     output start_signal_14;
  input serial_rx;
  output serial_tx;
  output user_led0;
  output user_led1;
  input user_sw0;
  input user_sw1;

  wire [1:0]Net;
  wire [1:0]Net1;
  wire [15:0]Net2;
  wire [48:0]bft_0_din_leaf_0;
  wire [48:0]bft_0_din_leaf_1;
  wire [48:0]bft_0_din_leaf_10;
  wire [48:0]bft_0_din_leaf_11;
  wire [48:0]bft_0_din_leaf_12;
  wire [48:0]bft_0_din_leaf_13;
  wire [48:0]bft_0_din_leaf_14;
  wire [48:0]bft_0_din_leaf_3;
  wire [48:0]bft_0_din_leaf_4;
  wire [48:0]bft_0_din_leaf_5;
  wire [48:0]bft_0_din_leaf_6;
  wire [48:0]bft_0_din_leaf_7;
  wire [48:0]bft_0_din_leaf_8;
  wire [48:0]bft_0_din_leaf_9;
  wire bft_0_resend_0;
  wire bft_0_resend_1;
  wire bft_0_resend_10;
  wire bft_0_resend_11;
  wire bft_0_resend_12;
  wire bft_0_resend_13;
  wire bft_0_resend_14;
  wire bft_0_resend_3;
  wire bft_0_resend_4;
  wire bft_0_resend_5;
  wire bft_0_resend_6;
  wire bft_0_resend_7;
  wire bft_0_resend_8;
  wire bft_0_resend_9;
  wire clk_1;
  wire clk_wiz_1_clk_out2;
  wire [48:0]leaf_10_dout_leaf_interface2bft;
  wire [48:0]leaf_11_dout_leaf_interface2bft;
  wire [48:0]leaf_12_dout_leaf_interface2bft;
  wire [48:0]leaf_13_dout_leaf_interface2bft;
  wire [48:0]leaf_14_dout_leaf_interface2bft;
  wire [48:0]leaf_3_dout_leaf_interface2bft;
  wire [48:0]leaf_4_dout_leaf_interface2bft;
  wire [48:0]leaf_5_dout_leaf_interface2bft;
  wire [48:0]leaf_6_dout_leaf_interface2bft;
  wire [48:0]leaf_7_dout_leaf_interface2bft;
  wire [48:0]leaf_8_dout_leaf_interface2bft;
  wire [48:0]leaf_9_dout_leaf_interface2bft;
  wire [48:0]nexys_video_0_axilite2bft_host_interface2bft;
  wire [14:0]nexys_video_0_ddram_a;
  wire [2:0]nexys_video_0_ddram_ba;
  wire nexys_video_0_ddram_cas_n;
  wire nexys_video_0_ddram_cke;
  wire nexys_video_0_ddram_clk_n;
  wire nexys_video_0_ddram_clk_p;
  wire [1:0]nexys_video_0_ddram_dm;
  wire nexys_video_0_ddram_odt;
  wire nexys_video_0_ddram_ras_n;
  wire nexys_video_0_ddram_reset_n;
  wire nexys_video_0_ddram_we_n;
  wire [48:0]nexys_video_0_interface_wrapper_dout_leaf_interface2bft;
  wire nexys_video_0_serial_tx;
  wire nexys_video_0_start_signal;
  wire nexys_video_0_user_led0;
  wire nexys_video_0_user_led1;
  wire reset_1;
  wire reset_bft_peripheral_reset;
  wire serial_rx_0_1;
  wire user_sw0_0_1;
  wire user_sw1_0_1;
  wire [48:0]xlconstant_0_dout1;
  wire clk_bft, rst_bft, start_signal;
assign clk_bft_3 = clk_bft;
     assign clk_bft_4 = clk_bft;
     assign clk_bft_5 = clk_bft;
     assign clk_bft_6 = clk_bft;
     assign clk_bft_7 = clk_bft;
     assign clk_bft_8 = clk_bft;
     assign clk_bft_9 = clk_bft;
     assign clk_bft_10 = clk_bft;
     assign clk_bft_11 = clk_bft;
     assign clk_bft_12 = clk_bft;
     assign clk_bft_13 = clk_bft;
     assign clk_bft_14 = clk_bft;
     assign start_signal_3 = start_signal;
     assign start_signal_4 = start_signal;
     assign start_signal_5 = start_signal;
     assign start_signal_6 = start_signal;
     assign start_signal_7 = start_signal;
     assign start_signal_8 = start_signal;
     assign start_signal_9 = start_signal;
     assign start_signal_10 = start_signal;
     assign start_signal_11 = start_signal;
     assign start_signal_12 = start_signal;
     assign start_signal_13 = start_signal;
     assign start_signal_14 = start_signal;
     assign rst_bft_3 = rst_bft;
     assign rst_bft_4 = rst_bft;
     assign rst_bft_5 = rst_bft;
     assign rst_bft_6 = rst_bft;
     assign rst_bft_7 = rst_bft;
     assign rst_bft_8 = rst_bft;
     assign rst_bft_9 = rst_bft;
     assign rst_bft_10 = rst_bft;
     assign rst_bft_11 = rst_bft;
     assign rst_bft_12 = rst_bft;
     assign rst_bft_13 = rst_bft;
     assign rst_bft_14 = rst_bft;
  assign clk_1 = clk100;
  assign clk_bft = clk_wiz_1_clk_out2;
  assign ddram_a[14:0] = nexys_video_0_ddram_a;
  assign ddram_ba[2:0] = nexys_video_0_ddram_ba;
  assign ddram_cas_n = nexys_video_0_ddram_cas_n;
  assign ddram_cke = nexys_video_0_ddram_cke;
  assign ddram_clk_n = nexys_video_0_ddram_clk_n;
  assign ddram_clk_p = nexys_video_0_ddram_clk_p;
  assign ddram_dm[1:0] = nexys_video_0_ddram_dm;
  assign ddram_odt = nexys_video_0_ddram_odt;
  assign ddram_ras_n = nexys_video_0_ddram_ras_n;
  assign ddram_reset_n = nexys_video_0_ddram_reset_n;
  assign ddram_we_n = nexys_video_0_ddram_we_n;
  assign din_leaf_10[48:0] = bft_0_din_leaf_10;
  assign din_leaf_11[48:0] = bft_0_din_leaf_11;
  assign din_leaf_12[48:0] = bft_0_din_leaf_12;
  assign din_leaf_13[48:0] = bft_0_din_leaf_13;
  assign din_leaf_14[48:0] = bft_0_din_leaf_14;
  assign din_leaf_3[48:0] = bft_0_din_leaf_3;
  assign din_leaf_4[48:0] = bft_0_din_leaf_4;
  assign din_leaf_5[48:0] = bft_0_din_leaf_5;
  assign din_leaf_6[48:0] = bft_0_din_leaf_6;
  assign din_leaf_7[48:0] = bft_0_din_leaf_7;
  assign din_leaf_8[48:0] = bft_0_din_leaf_8;
  assign din_leaf_9[48:0] = bft_0_din_leaf_9;
  assign leaf_10_dout_leaf_interface2bft = dout_leaf_10[48:0];
  assign leaf_11_dout_leaf_interface2bft = dout_leaf_11[48:0];
  assign leaf_12_dout_leaf_interface2bft = dout_leaf_12[48:0];
  assign leaf_13_dout_leaf_interface2bft = dout_leaf_13[48:0];
  assign leaf_14_dout_leaf_interface2bft = dout_leaf_14[48:0];
  assign leaf_3_dout_leaf_interface2bft = dout_leaf_3[48:0];
  assign leaf_4_dout_leaf_interface2bft = dout_leaf_4[48:0];
  assign leaf_5_dout_leaf_interface2bft = dout_leaf_5[48:0];
  assign leaf_6_dout_leaf_interface2bft = dout_leaf_6[48:0];
  assign leaf_7_dout_leaf_interface2bft = dout_leaf_7[48:0];
  assign leaf_8_dout_leaf_interface2bft = dout_leaf_8[48:0];
  assign leaf_9_dout_leaf_interface2bft = dout_leaf_9[48:0];
  assign resend_10 = bft_0_resend_10;
  assign resend_11 = bft_0_resend_11;
  assign resend_12 = bft_0_resend_12;
  assign resend_13 = bft_0_resend_13;
  assign resend_14 = bft_0_resend_14;
  assign resend_3 = bft_0_resend_3;
  assign resend_4 = bft_0_resend_4;
  assign resend_5 = bft_0_resend_5;
  assign resend_6 = bft_0_resend_6;
  assign resend_7 = bft_0_resend_7;
  assign resend_8 = bft_0_resend_8;
  assign resend_9 = bft_0_resend_9;
  assign reset_1 = cpu_reset;
  assign rst_bft = reset_bft_peripheral_reset;
  assign serial_rx_0_1 = serial_rx;
  assign serial_tx = nexys_video_0_serial_tx;
  assign start_signal = nexys_video_0_start_signal;
  assign user_led0 = nexys_video_0_user_led0;
  assign user_led1 = nexys_video_0_user_led1;
  assign user_sw0_0_1 = user_sw0;
  assign user_sw1_0_1 = user_sw1;
  assign xlconstant_0_dout1 = dout_leaf_15[48:0];
  top_bft_0_0 bft_0
       (.clk(clk_wiz_1_clk_out2),
        .din_leaf_0(bft_0_din_leaf_0),
        .din_leaf_1(bft_0_din_leaf_1),
        .din_leaf_10(bft_0_din_leaf_10),
        .din_leaf_11(bft_0_din_leaf_11),
        .din_leaf_12(bft_0_din_leaf_12),
        .din_leaf_13(bft_0_din_leaf_13),
        .din_leaf_14(bft_0_din_leaf_14),
        .din_leaf_3(bft_0_din_leaf_3),
        .din_leaf_4(bft_0_din_leaf_4),
        .din_leaf_5(bft_0_din_leaf_5),
        .din_leaf_6(bft_0_din_leaf_6),
        .din_leaf_7(bft_0_din_leaf_7),
        .din_leaf_8(bft_0_din_leaf_8),
        .din_leaf_9(bft_0_din_leaf_9),
        .dout_leaf_0(nexys_video_0_axilite2bft_host_interface2bft),
        .dout_leaf_1(nexys_video_0_interface_wrapper_dout_leaf_interface2bft),
        .dout_leaf_10(leaf_10_dout_leaf_interface2bft),
        .dout_leaf_11(leaf_11_dout_leaf_interface2bft),
        .dout_leaf_12(leaf_12_dout_leaf_interface2bft),
        .dout_leaf_13(leaf_13_dout_leaf_interface2bft),
        .dout_leaf_14(leaf_14_dout_leaf_interface2bft),
        .dout_leaf_15(xlconstant_0_dout1),
        .dout_leaf_2(xlconstant_0_dout1),
        .dout_leaf_3(leaf_3_dout_leaf_interface2bft),
        .dout_leaf_4(leaf_4_dout_leaf_interface2bft),
        .dout_leaf_5(leaf_5_dout_leaf_interface2bft),
        .dout_leaf_6(leaf_6_dout_leaf_interface2bft),
        .dout_leaf_7(leaf_7_dout_leaf_interface2bft),
        .dout_leaf_8(leaf_8_dout_leaf_interface2bft),
        .dout_leaf_9(leaf_9_dout_leaf_interface2bft),
        .resend_0(bft_0_resend_0),
        .resend_1(bft_0_resend_1),
        .resend_10(bft_0_resend_10),
        .resend_11(bft_0_resend_11),
        .resend_12(bft_0_resend_12),
        .resend_13(bft_0_resend_13),
        .resend_14(bft_0_resend_14),
        .resend_3(bft_0_resend_3),
        .resend_4(bft_0_resend_4),
        .resend_5(bft_0_resend_5),
        .resend_6(bft_0_resend_6),
        .resend_7(bft_0_resend_7),
        .resend_8(bft_0_resend_8),
        .resend_9(bft_0_resend_9),
        .reset(reset_bft_peripheral_reset));
  top_nexys_video_0_0 nexys_video_0
       (.axilite2bft_host_bft2interface(bft_0_din_leaf_0),
        .axilite2bft_host_interface2bft(nexys_video_0_axilite2bft_host_interface2bft),
        .axilite2bft_resend_0(bft_0_resend_0),
        .clk100(clk_1),
        .clk_bft(clk_wiz_1_clk_out2),
        .cpu_reset(reset_1),
        .ddram_a(nexys_video_0_ddram_a),
        .ddram_ba(nexys_video_0_ddram_ba),
        .ddram_cas_n(nexys_video_0_ddram_cas_n),
        .ddram_cke(nexys_video_0_ddram_cke),
        .ddram_clk_n(nexys_video_0_ddram_clk_n),
        .ddram_clk_p(nexys_video_0_ddram_clk_p),
        .ddram_dm(nexys_video_0_ddram_dm),
        .ddram_dq(ddram_dq[15:0]),
        .ddram_dqs_n(ddram_dqs_n[1:0]),
        .ddram_dqs_p(ddram_dqs_p[1:0]),
        .ddram_odt(nexys_video_0_ddram_odt),
        .ddram_ras_n(nexys_video_0_ddram_ras_n),
        .ddram_reset_n(nexys_video_0_ddram_reset_n),
        .ddram_we_n(nexys_video_0_ddram_we_n),
        .interface_wrapper_din_leaf_bft2interface(bft_0_din_leaf_1),
        .interface_wrapper_dout_leaf_interface2bft(nexys_video_0_interface_wrapper_dout_leaf_interface2bft),
        .interface_wrapper_resend_1(bft_0_resend_1),
        .rst_bft(reset_bft_peripheral_reset),
        .serial_rx(serial_rx_0_1),
        .serial_tx(nexys_video_0_serial_tx),
        .start_signal(nexys_video_0_start_signal),
        .user_led0(nexys_video_0_user_led0),
        .user_led1(nexys_video_0_user_led1),
        .user_sw0(user_sw0_0_1),
        .user_sw1(user_sw1_0_1));
endmodule
