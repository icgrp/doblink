module gen_nw # (
	parameter num_leaves= 8,
	parameter payload_sz= $clog2(num_leaves) + 4,
	parameter p_sz= 1 + $clog2(num_leaves) + payload_sz, //packet size
	parameter addr= 1'b0,
	parameter level= 0
	) (
	input clk,
	input reset,
	input [p_sz*8-1:0] pe_interface,
	output [p_sz*8-1:0] interface_pe,
	output [8-1:0] resend
);
	
	wire [4*p_sz-1:0] switch_left;
	wire [4*p_sz-1:0] switch_right;
	wire [4*p_sz-1:0] left_switch;
	wire [4*p_sz-1:0] right_switch;



	pi_cluster #(
		.num_leaves(num_leaves),
		.payload_sz(payload_sz),
		.addr(addr),
		.level(level),
		.p_sz(p_sz),
		.num_switches(4))
		pi_lvl0(
			.clk(clk),
			.reset(reset),


			.l_bus_i(left_switch),
			.r_bus_i(right_switch),
			.l_bus_o(switch_left),
			.r_bus_o(switch_right));

	_22subtree #(
		.num_leaves(num_leaves),
		.payload_sz(payload_sz),
		.addr({1'b0}),
		.p_sz(p_sz))
		subtree_left(
			.clk(clk),
			.reset(reset),
			.bus_i(switch_left),
			.bus_o(left_switch),
			.pe_interface(pe_interface[p_sz*4-1:0]),
			.interface_pe(interface_pe[p_sz*4-1:0]),
			.resend(resend[4-1:0]));

	_22subtree #(
		.num_leaves(num_leaves),
		.payload_sz(payload_sz),
		.addr({1'b1}),
		.p_sz(p_sz))
		subtree_right(
			.clk(clk),
			.reset(reset),
			.bus_i(switch_right),
			.bus_o(right_switch),
			.pe_interface(pe_interface[p_sz*8-1:p_sz*4]),
			.interface_pe(interface_pe[p_sz*8-1:p_sz*4]),
			.resend(resend[8-1:4]));
endmodule
module _22subtree # (
	parameter num_leaves= 8,
	parameter payload_sz= $clog2(num_leaves) + 4,
	parameter p_sz= 1 + $clog2(num_leaves) + payload_sz, //packet size
	parameter addr= 1'b0,
	parameter level= 1
	) (
	input clk,
	input reset,
	input [p_sz*4-1:0] pe_interface,
	output [p_sz*4-1:0] interface_pe,
	output [4-1:0] resend,
	input [2*2*p_sz-1:0] bus_i,

	output [2*2*p_sz-1:0] bus_o
);
	
	wire [2*p_sz-1:0] switch_left;
	wire [2*p_sz-1:0] switch_right;
	wire [2*p_sz-1:0] left_switch;
	wire [2*p_sz-1:0] right_switch;



	pi_cluster #(
		.num_leaves(num_leaves),
		.payload_sz(payload_sz),
		.addr(addr),
		.level(level),
		.p_sz(p_sz),
		.num_switches(2))
		pi_lvl1(
			.clk(clk),
			.reset(reset),
			.u_bus_i(bus_i),
			.u_bus_o(bus_o),
			.l_bus_i(left_switch),
			.r_bus_i(right_switch),
			.l_bus_o(switch_left),
			.r_bus_o(switch_right));

	_2subtree #(
		.num_leaves(num_leaves),
		.payload_sz(payload_sz),
		.addr({addr, 1'b0}),
		.p_sz(p_sz))
		subtree_left(
			.clk(clk),
			.reset(reset),
			.bus_i(switch_left),
			.bus_o(left_switch),
			.pe_interface(pe_interface[p_sz*2-1:0]),
			.interface_pe(interface_pe[p_sz*2-1:0]),
			.resend(resend[2-1:0]));

	_2subtree #(
		.num_leaves(num_leaves),
		.payload_sz(payload_sz),
		.addr({addr, 1'b1}),
		.p_sz(p_sz))
		subtree_right(
			.clk(clk),
			.reset(reset),
			.bus_i(switch_right),
			.bus_o(right_switch),
			.pe_interface(pe_interface[p_sz*4-1:p_sz*2]),
			.interface_pe(interface_pe[p_sz*4-1:p_sz*2]),
			.resend(resend[4-1:2]));
endmodule
module _2subtree # (
	parameter num_leaves= 8,
	parameter payload_sz= $clog2(num_leaves) + 4,
	parameter p_sz= 1 + $clog2(num_leaves) + payload_sz, //packet size
	parameter addr= 2'b00,
	parameter level= 2
	) (
	input clk,
	input reset,
	input [p_sz*2-1:0] pe_interface,
	output [p_sz*2-1:0] interface_pe,
	output [2-1:0] resend,
	input [2*1*p_sz-1:0] bus_i,

	output [2*1*p_sz-1:0] bus_o
);
	
	wire [1*p_sz-1:0] switch_left;
	wire [1*p_sz-1:0] switch_right;
	wire [1*p_sz-1:0] left_switch;
	wire [1*p_sz-1:0] right_switch;



	pi_cluster #(
		.num_leaves(num_leaves),
		.payload_sz(payload_sz),
		.addr(addr),
		.level(level),
		.p_sz(p_sz),
		.num_switches(1))
		pi_lvl2(
			.clk(clk),
			.reset(reset),
			.u_bus_i(bus_i),
			.u_bus_o(bus_o),
			.l_bus_i(left_switch),
			.r_bus_i(right_switch),
			.l_bus_o(switch_left),
			.r_bus_o(switch_right));

	interface #(
		.num_leaves(num_leaves),
		.payload_sz(payload_sz),
		.addr({addr, 1'b0}),
		.p_sz(p_sz))
		subtree_left(
			.clk(clk),
			.reset(reset),
			.bus_i(switch_left),
			.bus_o(left_switch),
			.pe_interface(pe_interface[p_sz*1-1:0]),
			.interface_pe(interface_pe[p_sz*1-1:0]),
			.resend(resend[1-1:0]));

	interface #(
		.num_leaves(num_leaves),
		.payload_sz(payload_sz),
		.addr({addr, 1'b1}),
		.p_sz(p_sz))
		subtree_right(
			.clk(clk),
			.reset(reset),
			.bus_i(switch_right),
			.bus_o(right_switch),
			.pe_interface(pe_interface[p_sz*2-1:p_sz*1]),
			.interface_pe(interface_pe[p_sz*2-1:p_sz*1]),
			.resend(resend[2-1:1]));
endmodule
