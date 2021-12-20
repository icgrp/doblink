module digit_mono (
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

    wire [31:0] data_3;
    wire vld_3;
    wire ack_3;

	wire [31:0] data_4;
    wire vld_4;
    wire ack_4;

    wire [31:0] data_5;
    wire vld_5;
    wire ack_5;

	update_knn1 update_knn1_inst(
        .ap_clk(ap_clk),
        .ap_start(ap_start),
        .ap_done(),
        .ap_idle(),
        .ap_ready(),
        .Input_1_V_TDATA(Input_1_V_TDATA),
        .Input_1_V_TVALID(Input_1_V_TVALID),
        .Input_1_V_TREADY(Input_1_V_TREADY),
		.Output_1_V_TDATA(data_1),
        .Output_1_V_TVALID(vld_1),
        .Output_1_V_TREADY(ack_1),
        .ap_rst_n(ap_rst_n)
        );  

    update_knn2 update_knn2_inst(
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

    update_knn3 update_knn3_inst(
        .ap_clk(ap_clk),
        .ap_rst_n(ap_rst_n),
        .ap_start(ap_start),
        .ap_done(),
        .ap_idle(),
        .Input_1_V_TDATA(data_2),
        .Input_1_V_TVALID(vld_2),
        .Input_1_V_TREADY(ack_2),
        .Output_1_V_TDATA(data_3),
        .Output_1_V_TVALID(vld_3),
        .Output_1_V_TREADY(ack_3),
        .ap_ready()
        );  

    update_knn4 update_knn4_inst(
        .ap_clk(ap_clk),
        .ap_rst_n(ap_rst_n),
        .ap_start(ap_start),
        .ap_done(),
        .ap_idle(),
        .Input_1_V_TDATA(data_3),
        .Input_1_V_TVALID(vld_3),
        .Input_1_V_TREADY(ack_3),
        .Output_1_V_TDATA(data_4),
        .Output_1_V_TVALID(vld_4),
        .Output_1_V_TREADY(ack_4),
        .ap_ready()
        );  
	
	update_knn5 update_knn5_inst(
        .ap_clk(ap_clk),
        .ap_rst_n(ap_rst_n),
        .ap_start(ap_start),
        .ap_done(),
        .ap_idle(),
        .Input_1_V_TDATA(data_4),
        .Input_1_V_TVALID(vld_4),
        .Input_1_V_TREADY(ack_4),
        .Output_1_V_TDATA(data_5),
        .Output_1_V_TVALID(vld_5),
        .Output_1_V_TREADY(ack_5),
        .ap_ready()
        ); 

    update_knn6 update_knn6_inst(
        .ap_clk(ap_clk),
        .ap_rst_n(ap_rst_n),
        .ap_start(ap_start),
        .ap_done(),
        .ap_idle(),
        .Input_1_V_TDATA(data_5),
        .Input_1_V_TVALID(vld_5),
        .Input_1_V_TREADY(ack_5),
        .Output_1_V_TDATA(Output_1_V_TDATA),
        .Output_1_V_TVALID(Output_1_V_TVALID),
        .Output_1_V_TREADY(Output_1_V_TREADY),
        .ap_ready()
        );  
endmodule
