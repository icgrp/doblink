module test;
	
	integer k;
	initial 
	begin
		$dumpfile("t_switch.vcd");
		$dumpvars(0, t_switch_test);
		#300000
		$finish;
	end
	
	parameter num_leaves= 2;
	parameter payload_sz = 1;
	parameter this_addr= 1'b0;
	parameter this_level= 0;
	parameter p_sz= 1+$clog2(num_leaves)+payload_sz; //packet size

	reg clk;
	reg [p_sz-1:0] l_bus_i;
	reg [p_sz-1:0] r_bus_i;
	reg [p_sz-1:0] u_bus_i;
	wire [p_sz-1:0] l_bus_o;
	wire [p_sz-1:0] r_bus_o;
	wire [p_sz-1:0] u_bus_o;
	
	t_switch #(.num_leaves(num_leaves),.payload_sz(payload_sz), .this_addr(this_addr), .this_level(this_level), .p_sz(p_sz))
	t_switch_test(.clk(clk), .l_bus_i(l_bus_i), .r_bus_i(r_bus_i), .u_bus_i(u_bus_i), .l_bus_o(l_bus_o), .r_bus_o(r_bus_o), .u_bus_o(u_bus_o));
	
	integer i= 0;
	initial
   	begin
		{l_bus_i, r_bus_i, u_bus_i, clk}= 0;
		#100	
		for ( i = 0; i < 2^(3*(1+p_sz)); i = i+1) begin
			{l_bus_i, r_bus_i, u_bus_i, clk} <= i; 
			#1;
		end

	end
endmodule 
