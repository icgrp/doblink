module rendering_mono (
        input ap_clk,
        input ap_rst,
        input ap_start,
        output ap_done,
        output ap_idle,
        output ap_ready,
        input [32:0] Input_1_V_V,
        input Input_1_V_V_ap_vld,
        output Input_1_V_V_ap_ack,
        output [32:0] Output_1_V_V,
        output Output_1_V_V_ap_vld,
        input Output_1_V_V_ap_ack
);

    wire [31:0] data_1;
    wire vld_1;
    wire ack_1;

    wire [31:0] data_2;
    wire vld_2;
    wire ack_2;

    wire [31:0] data_3;
    wire vld_3;
    wire ack_3;

    wire [31:0] data_4;
    wire vld_4;
    wire ack_4;

    wire [31:0] data_5;
    wire vld_5;
    wire ack_5;

    wire [31:0] data_6;
    wire vld_6;
    wire ack_6;

    wire [31:0] data_7;
    wire vld_7;
    wire ack_7;

    wire [31:0] data_8;
    wire vld_8;
    wire ack_8;

    wire [31:0] data_9;
    wire vld_9;
    wire ack_9;

    data_redir_m data_redir_m_inst(
        .ap_clk(ap_clk),
        .ap_rst(ap_rst),
        .ap_start(ap_start),
        .ap_done(),
        .ap_idle(),
        .Input_1_V_V(Input_1_V_V),
        .Input_1_V_V_ap_vld(Input_1_V_V_ap_vld),
        .Input_1_V_V_ap_ack(Input_1_V_V_ap_ack),
        .Output_1_V_V(data_1),
        .Output_1_V_V_ap_vld(vld_1),
        .Output_1_V_V_ap_ack(ack_1),
        .Output_2_V_V(data_2),
        .Output_2_V_V_ap_vld(vld_2),
        .Output_2_V_V_ap_ack(ack_2),
        .ap_ready()
        );  

    rasterization2_m rasterization2_m_inst(
        .ap_clk(ap_clk),
        .ap_rst(ap_rst),
        .ap_start(ap_start),
        .ap_done(),
        .ap_idle(),
        .Input_1_V_V(data_1),
        .Input_1_V_V_ap_vld(vld_1),
        .Input_1_V_V_ap_ack(ack_1),
        .Input_2_V_V(data_2),
        .Input_2_V_V_ap_vld(vld_2),
        .Input_2_V_V_ap_ack(ack_2),
        .Output_1_V_V(data_3),
        .Output_1_V_V_ap_vld(vld_3),
        .Output_1_V_V_ap_ack(ack_3),
        .Output_2_V_V(data_4),
        .Output_2_V_V_ap_vld(vld_4),
        .Output_2_V_V_ap_ack(ack_4),
        .Output_3_V_V(data_5),
        .Output_3_V_V_ap_vld(vld_5),
        .Output_3_V_V_ap_ack(ack_5),
        .Output_4_V_V(data_6),
        .Output_4_V_V_ap_vld(vld_6),
        .Output_4_V_V_ap_ack(ack_6),
        .ap_ready()
        );  

    zculling_bot zculling_bot_inst(
        .ap_clk(ap_clk),
        .ap_rst(ap_rst),
        .ap_start(ap_start),
        .ap_done(),
        .ap_idle(),
        .Input_1_V_V(data_4),
        .Input_1_V_V_ap_vld(vld_4),
        .Input_1_V_V_ap_ack(ack_4),
        .Input_2_V_V(data_6),
        .Input_2_V_V_ap_vld(vld_6),
        .Input_2_V_V_ap_ack(ack_6),
        .Output_1_V_V(data_7),
        .Output_1_V_V_ap_vld(vld_7),
        .Output_1_V_V_ap_ack(ack_7),
        .ap_ready()
        );  

    zculling_top zculling_top_inst(
        .ap_clk(ap_clk),
        .ap_rst(ap_rst),
        .ap_start(ap_start),
        .ap_done(),
        .ap_idle(),
        .Input_1_V_V(data_3),
        .Input_1_V_V_ap_vld(vld_3),
        .Input_1_V_V_ap_ack(ack_3),
        .Input_2_V_V(data_5),
        .Input_2_V_V_ap_vld(vld_5),
        .Input_2_V_V_ap_ack(ack_5),
        .Output_1_V_V(data_8),
        .Output_1_V_V_ap_vld(vld_8),
        .Output_1_V_V_ap_ack(ack_8),
        .ap_ready()
        );  

    coloringFB_bot_m coloringFB_bot_m_inst(
        .ap_clk(ap_clk),
        .ap_rst(ap_rst),
        .ap_start(ap_start),
        .ap_done(),
        .ap_idle(),
        .Input_1_V_V(data_7),
        .Input_1_V_V_ap_vld(vld_7),
        .Input_1_V_V_ap_ack(ack_7),
        .Output_1_V_V(data_9),
        .Output_1_V_V_ap_vld(vld_9),
        .Output_1_V_V_ap_ack(ack_9),
        .ap_ready()
        );  

    coloringFB_top_m coloringFB_top_m_inst(
        .ap_clk(ap_clk),
        .ap_rst(ap_rst),
        .ap_start(ap_start),
        .ap_done(),
        .ap_idle(),
        .Input_1_V_V(data_8),
        .Input_1_V_V_ap_vld(vld_8),
        .Input_1_V_V_ap_ack(ack_8),
        .Input_2_V_V(data_9),
        .Input_2_V_V_ap_vld(vld_9),
        .Input_2_V_V_ap_ack(ack_9),
        .Output_1_V_V(Output_1_V_V),
        .Output_1_V_V_ap_vld(Output_1_V_V_ap_vld),
        .Output_1_V_V_ap_ack(Output_1_V_V_ap_ack),
        .ap_ready()
        );  

    // assign Output_1_V_V = 32'd2;
endmodule
