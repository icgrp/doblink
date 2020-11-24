`timescale 1ns / 1ps

`ifndef DIRECTION_PARAMS_H
`define DIRECTION_PARAMS_H
`define VOID 2'b00
`define LEFT 2'b01
`define RIGHT 2'b10
`define UP 2'b11
// Used for pi switch
`define UPL 2'b11
`define UPR 2'b00 // replaces VOID in t_switch
`endif

`define PI_SWITCH
module pi_arbiter(
	input clk,
	input reset,
	input [1:0] d_l,
	input [1:0] d_r,
	input [1:0] d_ul,
	input [1:0] d_ur,
	input random,
	output reg rand_gen,
	output reg [1:0] sel_l,
	output reg [1:0] sel_r,
	output [1:0] sel_ul,
	output [1:0] sel_ur
	);
	
	parameter level= 1;
	/*
	*	d_l, d_r, d_u designate where the specific packet from a 
	*	certain direction would like to (ideally) go.
	*	d_{l,r,u{l,r}}=00, non-valid packet. 
	*   d_{l,r,u{l,r}}=01, packet should go left.
	*	d_{l,r,u{l,r}}=10, packet should go right.
   	*	d_{l,r,u{l,r}}=11, packet should go up.
	*/

	reg [1:0] sel_u1;
	reg [1:0] sel_u2;



	reg random_0;
	reg random_1;
	reg random_2;
	reg random_3;
	reg random_4;

	always @(posedge clk) begin
	  	if(reset) begin
			random_0 <= 0;
			random_1 <= 0;
			random_2 <= 0;
			random_3 <= 0;
			random_4 <= 0;
	  	end else begin
			random_0 <= random;
			random_1 <= random_0;
			random_2 <= random_1;
			random_3 <= random_2;
			random_4 <= random_3;
		end
			
	end


	assign sel_ul= random_4 ? sel_u1 : sel_u2;
	assign sel_ur= random_4 ? sel_u2 : sel_u1;

		
	// temp var just used to determine how to route non-valid packets
	reg [3:0] is_void; 


	// First Priority: Turnback Packets
	//pipeline 0
	reg [3:0] is_void_0;
	reg [1:0] sel_l_0;
	reg [1:0] sel_r_0;
	reg [1:0] sel_u1_0;
	reg [1:0] sel_u2_0;
	reg [1:0] d_l_0;
	reg [1:0] d_r_0;
	reg [1:0] d_ul_0;
	reg [1:0] d_ur_0;
	always @(posedge clk) begin
	  	if(reset) begin
			{sel_l_0, sel_r_0, sel_u1_0, sel_u2_0} = 8'b0101_0101;
			is_void_0 = 4'b1111;
			d_l_0 <= 2'b00;
			d_r_0 <= 2'b00;
			d_ul_0 <= 2'b00;
			d_ur_0 <= 2'b00;
	  	end else begin
			d_l_0 <= d_l;
			d_r_0 <= d_r;
			d_ul_0 <= d_ul;
			d_ur_0 <= d_ur;
			if (d_l == `LEFT)
				{sel_l_0, is_void_0[3]} = {`LEFT, 1'b0};
			else
				{sel_l_0, is_void_0[3]} = {2'b01, 1'b1};
			if (d_r == `RIGHT)
				{sel_r_0, is_void_0[2]} = {`RIGHT, 1'b0};
			else
				{sel_r_0, is_void_0[2]} = {2'b01, 1'b1};
			if (d_ul == `UP)
				{sel_u1_0, is_void_0[1]} = {`UPL, 1'b0};
			else
				{sel_u1_0, is_void_0[1]} = {2'b01, 1'b1};
			if (d_ur == `UP)
				{sel_u2_0, is_void_0[0]} = {`UPR, 1'b0};
			else
				{sel_u2_0, is_void_0[0]} = {2'b01, 1'b1};
		end
	end


	// Second Priority: Downlinks
	//pipeline 1
	reg [3:0] is_void_1;
	reg [1:0] sel_l_1;
	reg [1:0] sel_r_1;
	reg [1:0] sel_u1_1;
	reg [1:0] sel_u2_1;
	reg [1:0] d_l_1;
	reg [1:0] d_r_1;
	reg [1:0] d_ul_1;
	reg [1:0] d_ur_1;
	always @(posedge clk) begin
	  	if(reset) begin
			{sel_l_1, sel_r_1, sel_u1_1, sel_u2_1} = 8'b0101_0101;
			is_void_1 = 4'b1111;
			d_l_1 <= 2'b00;
			d_r_1 <= 2'b00;
			d_ul_1 <= 2'b00;
			d_ur_1 <= 2'b00;
	  	end else begin
			d_l_1 <= d_l_0;
			d_r_1 <= d_r_0;
			d_ul_1 <= d_ul_0;
			d_ur_1 <= d_ur_0;
			{sel_l_1, sel_r_1, sel_u1_1, sel_u2_1} = {sel_l_0, sel_r_0, sel_u1_0, sel_u2_0};
			is_void_1 = is_void_0;
			// Left Downlink
			if (d_ul_0 == `LEFT || d_ur_0 == `LEFT) begin
				if (is_void_0[3]) begin
					is_void_1[3] = 1'b0;
					if (d_ul_0 == `LEFT && d_ur_0 != `LEFT)
						sel_l_1 = `UPL;
					else if (d_ul_0 != `LEFT && d_ur_0 == `LEFT)
						sel_l_1 = `UPR;
					else if (d_ul_0 == `LEFT && d_ur_0 == `LEFT) begin
						is_void_1[1] = 1'b0;
						{sel_l_1, sel_u1_1} = {`UPL, `UPR};
					end
				end else begin
					if (d_ul_0 == `LEFT) begin
						is_void_1[1] = 1'b0;
						sel_u1_1 = `UPL;
					end
					if (d_ur_0 == `LEFT) begin
						is_void_1[0] = 1'b0;
						sel_u2_1 = `UPR;
					end
				end
			end

			// Right Downlink
			if (d_ul_0 == `RIGHT || d_ur_0 == `RIGHT) begin
				if (is_void_0[2]) begin
					is_void_1[2] = 1'b0;
					if (d_ul_0 == `RIGHT && d_ur_0 != `RIGHT)
						sel_r_1 = `UPL;
					else if (d_ul_0 != `RIGHT && d_ur_0 == `RIGHT)
						sel_r_1 = `UPR;
					else if (d_ul_0 == `RIGHT && d_ur_0 == `RIGHT) begin
						is_void_1[1] = 1'b0;
						{sel_r_1, sel_u1_1} = {`UPL, `UPR};
					end
				end else begin
					if (d_ul_0 == `RIGHT) begin
						is_void_1[1] = 1'b0;
						sel_u1_1 = `UPL;
					end
					if (d_ur_0 == `RIGHT) begin
						is_void_1[0] = 1'b0;
						sel_u2_1 = `UPR;
					end
				end
			end
		end
	end




	// Third Priority: Side Link
	//pipeline 2
	reg [3:0] is_void_2;
	reg [1:0] sel_l_2;
	reg [1:0] sel_r_2;
	reg [1:0] sel_u1_2;
	reg [1:0] sel_u2_2;
	reg [1:0] d_l_2;
	reg [1:0] d_r_2;
	reg [1:0] d_ul_2;
	reg [1:0] d_ur_2;
	always @(posedge clk) begin
	  	if(reset) begin
			{sel_l_2, sel_r_2, sel_u1_2, sel_u2_2} = 8'b0101_0101;
			is_void_2 = 4'b1111;
			d_l_2 <= 2'b00;
			d_r_2 <= 2'b00;
			d_ul_2 <= 2'b00;
			d_ur_2 <= 2'b00;
	  	end else begin
			d_l_2 <= d_l_1;
			d_r_2 <= d_r_1;
			d_ul_2 <= d_ul_1;
			d_ur_2 <= d_ur_1;
            {sel_l_2, sel_r_2, sel_u1_2, sel_u2_2} = {sel_l_1, sel_r_1, sel_u1_1, sel_u2_1};
            is_void_2 = is_void_1;
			// Left to Right (Left has priority over Right)
			if (d_l_1 == `RIGHT) begin
				if (is_void_1[2]) begin
					is_void_2[2] = 1'b0;
					sel_r_2 = `LEFT;
				end
				else if (is_void_1[3]) begin
					is_void_2[3] = 1'b0;
					sel_l_2 = `LEFT;
				end
				else if (is_void_1[1]) begin
					is_void_2[1] = 1'b0;
					sel_u1_2 = `LEFT;
				end
				else if (is_void_1[0]) begin
					is_void_2[0] = 1'b0;
					sel_u2_2 = `LEFT;
				end
			end

			// Right to Left
			if (d_r_1 == `LEFT) begin
				if (is_void_1[3]) begin
					is_void_2[3] = 1'b0;
					sel_l_2 = `RIGHT;
				end
				else if (is_void_1[2]) begin
					is_void_2[2] = 1'b0;
					sel_r_2 = `RIGHT;
				end
				else if (is_void_1[1]) begin
					is_void_2[1] = 1'b0;
					sel_u1_2 = `RIGHT;
				end
				else if (is_void_1[0]) begin
					is_void_2[0] = 1'b0;
					sel_u2_2 = `RIGHT;
				end
			end
		end
	end






	// Fourth Priority: Uplinks
	//pipeline 3
	reg [3:0] is_void_3;
	reg [1:0] sel_l_3;
	reg [1:0] sel_r_3;
	reg [1:0] sel_u1_3;
	reg [1:0] sel_u2_3;
	reg [1:0] d_l_3;
	reg [1:0] d_r_3;
	reg [1:0] d_ul_3;
	reg [1:0] d_ur_3;
	always @(posedge clk) begin
	  	if(reset) begin
			{sel_l_3, sel_r_3, sel_u1_3, sel_u2_3} = 8'b0101_0101;
			is_void_3 = 4'b1111;
			d_l_3 <= 2'b00;
			d_r_3 <= 2'b00;
			d_ul_3 <= 2'b00;
			d_ur_3 <= 2'b00;
	  	end else begin
			d_l_3 <= d_l_2;
			d_r_3 <= d_r_2;
			d_ul_3 <= d_ul_2;
			d_ur_3 <= d_ur_2;
            {sel_l_3, sel_r_3, sel_u1_3, sel_u2_3} = {sel_l_2, sel_r_2, sel_u1_2, sel_u2_2};
            is_void_3 = is_void_2;
			// Left to Up
			if (d_l_2 == `UP) begin
				if (is_void_2[1]) begin
					is_void_3[1] = 1'b0;
					sel_u1_3 = `LEFT;
				end
				else if (is_void_2[0]) begin
					is_void_3[0] = 1'b0;
					sel_u2_3 = `LEFT;
				end
				else if (is_void_2[3]) begin
					is_void_3[3] = 1'b0;
					sel_l_3 = `LEFT;
				end
				else if (is_void_2[2]) begin
					is_void_3[2] = 1'b0;
					sel_r_3 = `LEFT;
				end
			end
			// Right to UP
			if (d_r_2 == `UP) begin
				if (is_void_2[1]) begin
					is_void_3[1] = 1'b0;
					sel_u1_3 = `RIGHT;
				end
				else if (is_void_2[0]) begin
					is_void_3[0] = 1'b0;
					sel_u2_3 = `RIGHT;
				end
				else if (is_void_2[2]) begin
					is_void_3[2] = 1'b0;
					sel_r_3 = `RIGHT;
				end
				else if (is_void_2[3]) begin
					is_void_3[3] = 1'b0;
					sel_l_3 = `RIGHT;
				end
			end
		end
	end


	// Final Priority: Void 
	//pipeline 4
	always @(posedge clk) begin
	  	if(reset) begin
			{sel_l, sel_r, sel_u1, sel_u2} = 8'b0101_0101;
			rand_gen = 0;
	  	end else begin
            {sel_l, sel_r, sel_u1, sel_u2} = {sel_l_3, sel_r_3, sel_u1_3, sel_u2_3};
			// Before taking care of void case, determine whether or not a new
			// random/toggle bit should be generated
			if (is_void_3[1] == 1'b0 || is_void_3[0] == 1'b0)
				rand_gen = 1;
			else
				rand_gen = 0;
			if (d_l_3 == `VOID) begin
				if (is_void_3[3]) begin
					sel_l = `LEFT;
				end
				if (is_void_3[2]) begin
					sel_r = `LEFT;
				end
				if (is_void_3[1]) begin
					sel_u1 = `LEFT;
				end
				if (is_void_3[0]) begin
					sel_u2 = `LEFT;
				end
			end
			if (d_r_3 == `VOID) begin
				if (is_void_3[3]) begin
					sel_l = `RIGHT;
				end
				if (is_void_3[2]) begin
					sel_r = `RIGHT;
				end
				if (is_void_3[1]) begin
					sel_u1 = `RIGHT;
				end
				if (is_void_3[0]) begin
					sel_u2 = `RIGHT;
				end
			end
			if (d_ul_3 == `VOID) begin
				if (is_void_3[3]) begin
					sel_l = `UPL;
				end
				if (is_void_3[2]) begin
					sel_r = `UPL;
				end
				if (is_void_3[1]) begin
					sel_u1 = `UPL;
				end
				if (is_void_3[0]) begin
					sel_u2 = `UPL;
				end
			end
			if (d_ur_3 == `VOID) begin
				if (is_void_3[3]) begin
					sel_l = `UPR;
				end
				if (is_void_3[2]) begin
					sel_r = `UPR;
				end
				if (is_void_3[1]) begin
					sel_u1 = `UPR;
				end
				if (is_void_3[0]) begin
					sel_u2 = `UPR;
				end
			end
		end
	end

endmodule
























module test;

	initial begin
		$dumpfile("pi_arbiter.vcd");
		$dumpvars(0,pi_arbiter_test);
		#6000 $finish;
	end

	reg clk;
	reg reset;
	reg [1:0] d_l;
	reg [1:0] d_r;
	reg [1:0] d_ul;
	reg [1:0] d_ur;
	wire [1:0] sel_l;
	wire [1:0] sel_r;
	wire [1:0] sel_ul;
	wire [1:0] sel_ur;
        wire random;

	
	parameter level= 1;

	assign random = 1;
	pi_arbiter #(
				.level(level))
				pi_arbiter_test(
					.clk(clk),
					.reset(reset),
					.d_l(d_l),
					.d_r(d_r),
				   	.d_ul(d_ul),
				   	.d_ur(d_ur),
				   	.sel_l(sel_l),
				   	.sel_r(sel_r),
				   	.sel_ul(sel_ul),
				   	.sel_ur(sel_ur),
					.random(random),
					.rand_gen(rand_gen));

	
	always #10 clk = ~clk;
	integer i = 0;
	initial begin
		clk = 0;
		reset = 1;
		d_l= 0;
		d_r= 0;
		d_ul= 0;
                d_ur= 0;
		#107
		reset = 0;
		#100

		for ( i = 0; i < 2^8; i = i+1)
		begin
			{d_l, d_r, d_ur, d_ul} <= i; 
			#20;
		end

	end

	reg [48:0] string_d_l, string_d_r, string_d_ur, string_d_ul, string_sel_l, string_sel_r, 
				string_sel_ur, string_sel_ul;
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

		case (d_ur)
			2'b00: string_d_ur= "VOID";                                          
			2'b01: string_d_ur= "LEFT";
			2'b10: string_d_ur= "RIGHT"; 
			2'b11: string_d_ur= "UP";
		endcase   

		case (d_ul)
			2'b00: string_d_ul= "VOID";                                          
			2'b01: string_d_ul= "LEFT";
			2'b10: string_d_ul= "RIGHT"; 
			2'b11: string_d_ul= "UP";
		endcase   


		case (sel_l)
			2'b00: string_sel_l= "UPR";                                          
			2'b01: string_sel_l= "LEFT";
			2'b10: string_sel_l= "RIGHT"; 
			2'b11: string_sel_l= "UPL";
		endcase   

		case (sel_r)
			2'b00: string_sel_r= "UPR";                                          
			2'b01: string_sel_r= "LEFT";
			2'b10: string_sel_r= "RIGHT"; 
			2'b11: string_sel_r= "UPL";
		endcase   

		case (sel_ur)
			2'b00: string_sel_ur= "UPR";                                          
			2'b01: string_sel_ur= "LEFT";
			2'b10: string_sel_ur= "RIGHT"; 
			2'b11: string_sel_ur= "UPL";
		endcase   

		case (sel_ul)
			2'b00: string_sel_ul= "UPR";                                          
			2'b01: string_sel_ul= "LEFT";
			2'b10: string_sel_ul= "RIGHT"; 
			2'b11: string_sel_ul= "UPL";
		endcase   
	end


	initial begin
		#207
		$monitor("d_l:%s\t| d_r:%s\t| d_ur: %s\t| d_ul: %s\t| sel_l: %s\t| sel_r: %s\t| sel_ur: %s\t| sel_ul: %s",
                         string_d_l, string_d_r, string_d_ur, string_d_ul, string_sel_l, string_sel_r,
			 string_sel_ur, string_sel_ul);
	end

      
endmodule
