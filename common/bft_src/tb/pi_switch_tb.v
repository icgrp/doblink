module test;
	
	integer k;
	initial 
	begin
		$dumpfile("pi_switch.vcd");
		$dumpvars(0, pi_switch_test);
		#300000
		$finish;
	end
	
	parameter num_leaves= 4;
	parameter payload_sz = 0;
	parameter addr= 1'b0;
	parameter level= 1;
	parameter p_sz= 1+$clog2(num_leaves)+payload_sz; //packet size

	reg clk;
	reg reset;
	reg [p_sz-1:0] l_bus_i;
	reg [p_sz-1:0] r_bus_i;
	reg [p_sz-1:0] ul_bus_i;
	reg [p_sz-1:0] ur_bus_i;
	wire [p_sz-1:0] l_bus_o;
	wire [p_sz-1:0] r_bus_o;
	wire [p_sz-1:0] ul_bus_o;
	wire [p_sz-1:0] ur_bus_o;
	
	pi_switch #(
				.num_leaves(num_leaves),
				.payload_sz(payload_sz),
			   	.addr(addr),
			   	.level(level),
			   	.p_sz(p_sz))
				pi_switch_test(
					.clk(clk),
					.reset(reset),
				   	.l_bus_i(l_bus_i),
				   	.r_bus_i(r_bus_i),
				   	.ul_bus_i(ul_bus_i),
				   	.ur_bus_i(ur_bus_i),
				   	.l_bus_o(l_bus_o),
				   	.r_bus_o(r_bus_o),
				   	.ul_bus_o(ul_bus_o),
				   	.ur_bus_o(ur_bus_o));
	
	integer i= 0;
	initial
   	begin
		{l_bus_i, r_bus_i, ul_bus_i,ur_bus_i, clk}= 0;
		#100	
		for ( i = 0; i < 2^(4*(1+p_sz)); i = i+1) begin
			{l_bus_i, r_bus_i, ul_bus_i, ur_bus_i, clk} <= i; 
			#1;
		end

	end
	initial begin
		reset <= 1;
	   	#102
		reset <= 0;
	end
endmodule 
