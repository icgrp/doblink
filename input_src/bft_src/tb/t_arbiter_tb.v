`timescale 1ns / 1ps
`include "../common/direction_params.vh"
module t_arbiter(
	input [1:0] d_l,
	input [1:0] d_r,
	input [1:0] d_u,
	output reg [1:0] sel_l,
	output reg [1:0] sel_r,
	output reg [1:0] sel_u
	);
	
	parameter level= 1;
	/*
	*	d_l, d_r, d_u designate where the specific packet from a certain
	*	direction would like to (ideally go).
	*	d_{l,r,u}=00, non-valid packet. 
	*   d_{l,r,u}=01, packet should go left.
	*	d_{l,r,u}=10, packet should go right.
   	*	d_{l,r,u}=11, packet should go up.
	*/

	generate
		if (level == 0)
			always @* begin
				sel_l= `VOID;
				sel_r= `VOID;
				sel_u= `VOID;
				if (d_l == `LEFT)
					sel_l= `LEFT;
				if (d_r == `RIGHT)
					sel_r= `RIGHT;
				if (sel_l == `VOID && d_r == `LEFT)
					sel_l= `RIGHT;
                                if (sel_l == `LEFT && d_r == `LEFT)
					sel_r= `RIGHT;			//return back
				if (sel_r == `VOID && d_l == `RIGHT)
					sel_r= `LEFT;			
				if (sel_r == `RIGHT && d_l == `RIGHT)
					sel_l= `LEFT;			//return back
			end
		else 
			/* 
			* select lines are for the MUX's that actually route the packets to the
			`UP* neighboring nodes. 
			*/
			always @* begin
				sel_l= `VOID;
				sel_r= `VOID;
				sel_u= `VOID;
				// First Priority: Turnback (When a packet has already been deflected
				// and needs to turn back within one level)
				if (d_l == `LEFT)
					sel_l= `LEFT;
				if (d_r == `RIGHT)
					sel_r= `RIGHT;
				if (d_u == `UP)
					sel_u= `UP;
				// Second Priority: Downlinks (When a packet wants to go from Up to
				// Left or Right-- must check if bus is already used by Turnbacked
				// packets)
				else if (d_u == `LEFT)
					if (d_l != `LEFT)
						sel_l= `UP;
					// If left bus is already used by turnback packet, deflect up
					// packet back up
					else
						sel_u= `UP;
				else if (d_u == `RIGHT)
					if (d_r != `RIGHT)
						sel_r= `UP;
					// If right bus is already used by turnback packet, deflect up
					// packet back up
					else
						sel_u= `UP;
				// Third Priority: `UP/Side Link
				// Left to Right
				if (d_l == `RIGHT)
					// if right bus is not already used by either a turnback packet or
					// a downlink packet, send left packet there
					if (sel_r == `VOID)
						sel_r= `LEFT;
					// otherwise, deflect left packet 
						// If downlink is already using left bus, deflect packet up
					else if (d_u == `LEFT)
						sel_u= `LEFT;
						// Last remaining option is deflection in direction of arrival
						// (must be correct, via deduction)
					else
						sel_l= `LEFT;
				// Left to Up
				else if (d_l == `UP)
					// if up bus is not occupied by turnback packet, send uplink up
					if (sel_u == `VOID)
						sel_u= `LEFT;
					// otherwise, deflect left packet
					// deflect back in direction of arrival if possible
					else if (sel_l == `VOID)
						sel_l= `LEFT;
					// otherwise, deflect to the right
					else
						sel_r= `LEFT;
				// Right to Left
				if (d_r == `LEFT)
					// if left bus is not occupied by turnback packet or downlink
					// paket, send right packet there
					if (sel_l == `VOID)
						sel_l= `RIGHT;
					// otherwise, deflect packet
					else if (sel_r == `VOID)
						sel_r= `RIGHT;
					else
						sel_u= `RIGHT;
				// Right to Up
				else if (d_r == `UP)
					// if up bus is not occupied by turnback packet or other uplink
					// packet, send right uplink packet up
					if (sel_u == `VOID)
						sel_u= `RIGHT;
					// else deflect right packet
					else if (sel_r == `VOID)
						sel_r= `RIGHT;
					// last possible option is to send packet to the left
					else
						sel_l= `RIGHT;
				`ifdef OPTIMIZED
				// Makes exception to when left and right packets swap, up packet gets
				// deflected up
				if (d_l == `RIGHT && d_r == `LEFT && d_u != `VOID) begin
					sel_l= `RIGHT;
					sel_r= `LEFT;
					sel_u= `UP;
				end
				`endif
			end
	endgenerate
endmodule
module test;

	initial begin
		$dumpfile("t_arbiter.vcd");
		$dumpvars(0,t_arbiter_test);
		#1385 $finish;
	end

	reg [1:0] d_l;
	reg [1:0] d_r;
	reg [1:0] d_u;
	wire [1:0] sel_l;
	wire [1:0] sel_r;
	wire [1:0]sel_u;
	parameter this_level= 0;
	t_arbiter #(.level(this_level))
	t_arbiter_test(d_l, d_r, d_u, sel_l, sel_r, sel_u);

	integer i = 0;
	initial begin
		d_l= 0;
		d_r= 0;
		d_u= 0;
		#100;
		
		for ( i = 0; i < 2^6; i = i+1)
		begin
			{d_l, d_r, d_u} <= i; 
			#20;
		end

	end

	reg [48:0] string_d_l, string_d_r, string_d_u, string_sel_l, string_sel_r, 
				string_sel_u;
	always @*
	begin
		case (d_l)
			2'b00: string_d_l= "VOID";                                          
			2'b01: string_d_l= "LEFT";
			2'b10: string_d_l= "RIGHT"; 
			2'b11: string_d_l= "UP";
		endcase   

		case (d_r)
			2'b00: string_d_r= "VOID";                                          
			2'b01: string_d_r= "LEFT";
			2'b10: string_d_r= "RIGHT"; 
			2'b11: string_d_r= "UP";
		endcase   

		case (d_u)
			2'b00: string_d_u= "VOID";                                          
			2'b01: string_d_u= "LEFT";
			2'b10: string_d_u= "RIGHT"; 
			2'b11: string_d_u= "UP";
		endcase   

		case (sel_l)
			2'b00: string_sel_l= "VOID";                                          
			2'b01: string_sel_l= "LEFT";
			2'b10: string_sel_l= "RIGHT"; 
			2'b11: string_sel_l= "UP";
		endcase   

		case (sel_r)
			2'b00: string_sel_r= "VOID";                                          
			2'b01: string_sel_r= "LEFT";
			2'b10: string_sel_r= "RIGHT"; 
			2'b11: string_sel_r= "UP";
		endcase   

		case (sel_u)
			2'b00: string_sel_u= "VOID";                                          
			2'b01: string_sel_u= "LEFT";
			2'b10: string_sel_u= "RIGHT"; 
			2'b11: string_sel_u= "UP";
		endcase   
	end


	initial begin
		#100
		$monitor("d_l:%s\t| d_r:%s\t| d_u: %s\t| sel_l: %s\t| sel_r: %s\t sel_u: %s",
              string_d_l, string_d_r, string_d_u, string_sel_l, string_sel_r,
			 string_sel_u);
	end

      
endmodule
