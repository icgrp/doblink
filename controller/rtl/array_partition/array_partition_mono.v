module array_mono (
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

	matmul_partition matmul_partition_inst (
        .ap_clk(ap_clk),
        .ap_start(ap_start),
        .ap_done(),
        .ap_idle(),
        .ap_ready(),
        .Input_1_V_TDATA(Input_1_V_TDATA),
        .Input_1_V_TVALID(Input_1_V_TVALID),
        .Input_1_V_TREADY(Input_1_V_TREADY),
		.Output_1_V_TDATA(Output_1_V_TDATA),
        .Output_1_V_TVALID(Output_1_V_TVALID),
        .Output_1_V_TREADY(Output_1_V_TREADY),
        .ap_rst_n(ap_rst_n)
        );  

endmodule
