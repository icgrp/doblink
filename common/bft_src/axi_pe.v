module gen_nw_top # (
	parameter arm_data_width = 96,
	parameter num_leaves= 8,
	parameter payload_sz= $clog2(num_leaves) + 4,
	parameter p_sz= 1 + $clog2(num_leaves) + payload_sz, //packet size
	parameter addr= 3'b000,
	parameter level= 0
	)(
	input clk,
	input [arm_data_width-1:0] data_in,
	output reg [arm_data_width-1:0] data_out,
	input start,
	input reset
);
	wire [p_sz*8-1:0] pe_interface;
	wire [p_sz*8-1:0] interface_pe;
	wire [8-1:0] resend;
	wire [p_sz-1:0] data_out_wire;
	always@(*)begin
		data_out = 0;
		if(data_out_wire[p_sz-1])
			data_out[p_sz-2:0] = data_out_wire[p_sz-2:0];
	end
	pe_start #(
		.addr(0),
		.p_sz(p_sz)
		)pe_0(
		.clk(clk),
		.reset(reset),
		.pe_interface(pe_interface[p_sz-1:0]),
		.interface_pe(interface_pe[p_sz-1:0]),
		.resend(resend[0]),
		.start(start),
		.data_in(data_in),
		.data_out(data_out_wire)
		);
	genvar i;
	generate
	for (i= 1; i < 8; i= i + 1) begin
		pe_shift #(
		.addr(i),
		.p_sz(p_sz)
		)pe_1(
		.clk(clk),
		.reset(reset),
		.pe_interface(pe_interface[i*p_sz+:p_sz]),
		.interface_pe(interface_pe[i*p_sz+:p_sz]),
		.resend(resend[i])
		);
	end
	endgenerate
	gen_nw #(
		.num_leaves(num_leaves),
		.payload_sz(payload_sz),
		.p_sz(p_sz),
		.addr(1'b0),
		.level(0)
	)gen_nw_1(
		.clk(clk),
		.reset(reset),
		.pe_interface(pe_interface),
		.interface_pe(interface_pe),
		.resend(resend)
	);
endmodule

module pe_shift(
	input clk,
	input reset,
	output reg [p_sz-1:0] pe_interface,
	input [p_sz-1:0]interface_pe,
	input resend
	);
	parameter num_leaves= 8;
	parameter payload_sz= $clog2(num_leaves) + 4;
	parameter p_sz= 1 + $clog2(num_leaves) + payload_sz; //packet size
	parameter addr=1;
	parameter level= 0;
	always@(posedge clk or posedge reset) begin
		if(reset) begin
			pe_interface <= 0;
		end else begin
				if (resend) begin
					pe_interface <= 0;
				end else begin   
					pe_interface[p_sz-2-2*$clog2(num_leaves):0] <= interface_pe[p_sz-2-2*$clog2(num_leaves):0] + 1;
					pe_interface[p_sz-2-$clog2(num_leaves):p_sz-1-2*$clog2(num_leaves)] <= interface_pe[p_sz-2-$clog2(num_leaves):p_sz-1-2*$clog2(num_leaves)] + 1;
					pe_interface[p_sz-2:p_sz-1-$clog2(num_leaves)] <= interface_pe[p_sz-2:p_sz-1-$clog2(num_leaves)] + 1;
					pe_interface[p_sz-1] <= interface_pe[p_sz-1];
				end
			end
		end
endmodule

module pe_start(
	input clk,
	input reset,
	output reg [p_sz-1:0] pe_interface,
	input [p_sz-1:0]interface_pe,
	input resend,
	input start,
	input [p_sz-1:0] data_in,
	output reg [p_sz-1:0] data_out
);
	parameter num_leaves= 8;
	parameter payload_sz= $clog2(num_leaves) + 4;
	parameter p_sz= 1 + $clog2(num_leaves) + payload_sz;
	parameter addr= 3'b000;
	parameter level= 0;
	reg start_1, start_2;
	always@(posedge clk or posedge reset) begin
		if(reset) begin
			start_1 <= 0;
			start_2 <= 0;
			pe_interface <= 0;
		end else begin
			{start_2, start_1} <= {start_1, start};
			pe_interface[p_sz-1] <= start_2 ^ start_1;
			pe_interface[p_sz-2:0] <= data_in[p_sz-2:0];
		end
	end

	always@(posedge clk or posedge reset) begin
		if(reset) begin
			data_out <= 0;
		end else begin
			if(interface_pe[p_sz-1]) data_out <= interface_pe;
		end
	end 
endmodule