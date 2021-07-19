module rendering_mono (
        input ap_clk,
        input ap_rst_n,
        input ap_start,
        input [31:0] Input_1_V_TDATA,
        input Input_1_V_TVALID,
        output Input_1_V_TREADY,
        output [31:0] Output_1_V_TDATA,
        output Output_1_V_TVALID,
        input Output_1_V_TREADY
);

    wire [31:0] data_1;
    wire vld_1;
    wire ack_1;

    wire [31:0] data_2;
    wire vld_2;
    wire ack_2;

    // data_redir_m data_redir_m_inst(
    //     .ap_clk(ap_clk),
    //     .ap_rst_n(ap_rst_n),
    //     .ap_start(ap_start),
    //     .ap_done(),
    //     .ap_idle(),
    //     .Input_1_V_TDATA(Input_1_V_TDATA),
    //     .Input_1_V_TVALID(Input_1_V_TVALID),
    //     .Input_1_V_TREADY(Input_1_V_TREADY),
    //     .Output_1_V_TDATA(Output_1_V_TDATA),
    //     .Output_1_V_TVALID(Output_1_V_TVALID),
    //     .Output_1_V_TREADY(Output_1_V_TREADY),
    //     .ap_ready()
    //     );  

    // data_redir_m data_redir_m_inst(
    //     .ap_clk(ap_clk),
    //     .ap_rst_n(ap_rst_n),
    //     .ap_start(ap_start),
    //     .ap_done(),
    //     .ap_idle(),
    //     .Input_1_V_TDATA(Input_1_V_TDATA),
    //     .Input_1_V_TVALID(Input_1_V_TVALID),
    //     .Input_1_V_TREADY(Input_1_V_TREADY),
    //     .Output_1_V_TDATA(data_1),
    //     .Output_1_V_TVALID(vld_1),
    //     .Output_1_V_TREADY(ack_1),
    //     .ap_ready()
    //     );  

    // rasterization2_m rasterization2_m_inst(
    //     .ap_clk(ap_clk),
    //     .ap_rst_n(ap_rst_n),
    //     .ap_start(ap_start),
    //     .ap_done(),
    //     .ap_idle(),
    //     .Input_1_V_TDATA(data_1),
    //     .Input_1_V_TVALID(vld_1),
    //     .Input_1_V_TREADY(ack_1),
    //     .Output_1_V_TDATA(Output_1_V_TDATA),
    //     .Output_1_V_TVALID(Output_1_V_TVALID),
    //     .Output_1_V_TREADY(Output_1_V_TREADY),
    //     .ap_ready()
    //     );  

    data_redir_m data_redir_m_inst(
        .ap_clk(ap_clk),
        .ap_rst_n(ap_rst_n),
        .ap_start(ap_start),
        .ap_done(),
        .ap_idle(),
        .Input_1_V_TDATA(Input_1_V_TDATA),
        .Input_1_V_TVALID(Input_1_V_TVALID),
        .Input_1_V_TREADY(Input_1_V_TREADY),
        .Output_1_V_TDATA(data_1),
        .Output_1_V_TVALID(vld_1),
        .Output_1_V_TREADY(ack_1),
        .ap_ready()
        );  

    rasterization2_m rasterization2_m_inst(
        .ap_clk(ap_clk),
        .ap_rst_n(ap_rst_n),
        .ap_start(ap_start),
        .ap_done(),
        .ap_idle(),
        .Input_1_V_TDATA(data_1),
        .Input_1_V_TVALID(vld_1),
        .Input_1_V_TREADY(ack_1),
        .Output_1_V_TDATA(data_2),
        .Output_1_V_TVALID(vld_2),
        .Output_1_V_TREADY(ack_2),
        .ap_ready()
        );  

    zculling_top zculling_top_inst(
        .ap_clk(ap_clk),
        .ap_rst_n(ap_rst_n),
        .ap_start(ap_start),
        .ap_done(),
        .ap_idle(),
        .Input_1_V_TDATA(data_2),
        .Input_1_V_TVALID(vld_2),
        .Input_1_V_TREADY(ack_2),
        .Output_1_V_TDATA(Output_1_V_TDATA),
        .Output_1_V_TVALID(Output_1_V_TVALID),
        .Output_1_V_TREADY(Output_1_V_TREADY),
        .ap_ready()
        );  

    // coloringFB_bot_m coloringFB_bot_m_inst(
    //     .ap_clk(ap_clk),
    //     .ap_rst_n(ap_rst_n),
    //     .ap_start(ap_start),
    //     .ap_done(),
    //     .ap_idle(),
    //     .Input_1_V_TDATA(data_1),
    //     .Input_1_V_TVALID(vld_1),
    //     .Input_1_V_TREADY(ack_1),
    //     .Output_1_V_TDATA(Output_1_V_TDATA),
    //     .Output_1_V_TVALID(Output_1_V_TVALID),
    //     .Output_1_V_TREADY(Output_1_V_TREADY),
    //     .ap_ready()
    //     );  
endmodule
