module interface (
	input clk, 
	input reset, 
	input [p_sz-1:0] bus_i,
	output reg [p_sz-1:0] bus_o, 
	input [p_sz-1:0] pe_interface,
	output reg [p_sz-1:0] interface_pe,
	output resend
	);

	parameter num_leaves= 2;
	parameter payload_sz= 1;
	parameter addr= 1'b0;
	parameter p_sz= 1 + $clog2(num_leaves) + payload_sz; //packet size

	wire accept_packet;
	wire send_packet;
	assign accept_packet= bus_i[p_sz-1] && 
			(bus_i[p_sz-2:payload_sz] == addr);
	assign send_packet= !(bus_i[p_sz-1] && 
		addr != bus_i[p_sz-2:payload_sz]);

	reg winc, rinc;
	wire [p_sz-1:0] wdata, rdata;
	wire rempty;

	SynFIFO #(
		.DSIZE(p_sz),
		.ASIZE(2))
		FIFI_u (
		.clk(clk),
		.rst_n(~reset),
		.rdata(rdata), 
		.wfull(resend), 
		.rempty(rempty), 
		.wdata(pe_interface),
		.winc(pe_interface[p_sz-1]), 
		.rinc(send_packet && ~rempty) 
		);

	always @(posedge clk) begin
	//	cache_o <= pe_interface;
		if (reset)
			{interface_pe, bus_o} <= 0;
		else begin
			if (accept_packet)
				interface_pe <= bus_i;
			else
				interface_pe <= 0;
			if (send_packet) begin			
				if (rempty)
					bus_o <= 0;
				else
					bus_o <=  rdata;
				
			end
			else begin
				bus_o <= bus_i;
			end
		end
	end
	
endmodule

module pipe_ff (
	input clk, 
	input reset, 
	input [data_width-1:0] din,
	output reg [data_width-1:0] dout 
	);

	parameter data_width= 2;


	always @(posedge clk) begin
		if (reset)
			dout <= 0;
		else
			dout <=din;
	end
	
endmodule
