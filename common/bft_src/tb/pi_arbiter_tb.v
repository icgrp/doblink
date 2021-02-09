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

	assign sel_ul= random ? sel_u1 : sel_u2;
	assign sel_ur= random ? sel_u2 : sel_u1;

		
	// temp var just used to determine how to route non-valid packets
	reg [3:0] is_void; 
    reg [3:0] is_void_0_comb;
    reg [1:0] sel_l_0_comb;
    reg [1:0] sel_r_0_comb;
    reg [1:0] sel_u1_0_comb;
    reg [1:0] sel_u2_0_comb;
    
	always @* begin
		is_void_0_comb = 4'b1111; // local var, order is L, R, U1, U2;
        {sel_l_0_comb,sel_r_0_comb,sel_u1_0_comb,sel_u2_0_comb} = 8'b01010101;
		// First Priority: Turnback Packets
		if (d_l == `LEFT)
			{sel_l_0_comb, is_void_0_comb[3]}= {`LEFT, 1'b0};
		if (d_r == `RIGHT)
			{sel_r_0_comb, is_void_0_comb[2]}= {`RIGHT, 1'b0};
		if (d_ul == `UP)
			{sel_u1_0_comb, is_void_0_comb[1]}= {`UPL, 1'b0};
		if (d_ur == `UP)
			{sel_u2_0_comb, is_void_0_comb[0]}= {`UPR, 1'b0};
    end

    reg [3:0] is_void_0;
    reg [1:0] sel_l_0;
    reg [1:0] sel_r_0;
    reg [1:0] sel_u1_0;
    reg [1:0] sel_u2_0;
    reg [1:0] d_l_0;
    reg [1:0] d_r_0;
    reg [1:0] d_ul_0;
    reg [1:0] d_ur_0;
        
    always@(posedge clk) begin
        if(reset) begin
            is_void_0 <= 4'b1111;
            {sel_l_0,sel_r_0,sel_u1_0,sel_u2_0} <= 8'b01010101;
            {d_l_0, d_r_0, d_ul_0, d_ul_0} <= 8'b0000_0000;  
        end else begin
            is_void_0 <= is_void_0_comb;
            {sel_l_0,sel_r_0,sel_u1_0,sel_u2_0} <= {sel_l_0_comb,sel_r_0_comb,sel_u1_0_comb,sel_u2_0_comb}; 
            {d_l_0, d_r_0, d_ul_0, d_ur_0} <= {d_l, d_r, d_ul, d_ur};
        end
    end               



    reg [3:0] is_void_1_comb;
    reg [1:0] sel_l_1_comb;
    reg [1:0] sel_r_1_comb;
    reg [1:0] sel_u1_1_comb;
    reg [1:0] sel_u2_1_comb;
	always @* begin
		is_void_1_comb = is_void_0;
        {sel_l_1_comb,sel_r_1_comb,sel_u1_1_comb,sel_u2_1_comb} = {sel_l_0,sel_r_0,sel_u1_0,sel_u2_0};
		// Second Priority: Downlinks
		// Left Downlink
		if (d_ul_0 == `LEFT || d_ur_0 == `LEFT) begin
			if (is_void_1_comb[3]) begin
				is_void_1_comb[3]= 1'b0;
				if (d_ul_0 == `LEFT && d_ur_0 != `LEFT)
					sel_l_1_comb= `UPL;
				else if (d_ul_0 != `LEFT && d_ur_0 == `LEFT)
					sel_l_1_comb= `UPR;
				else if (d_ul_0 == `LEFT && d_ur_0 == `LEFT) begin
					is_void_1_comb[1]= 1'b0;
					{sel_l_1_comb, sel_u1_1_comb}= {`UPL, `UPR};
				end
			end
			else begin
				if (d_ul_0 == `LEFT) begin
					is_void_1_comb[1]= 1'b0;
					sel_u1_1_comb= `UPL;
				end
				if (d_ur_0 == `LEFT) begin
					is_void_1_comb[0]= 1'b0;
					sel_u2_1_comb= `UPR;
				end
			end
		end

		// Right Downlink
		if (d_ul_0 == `RIGHT || d_ur_0 == `RIGHT) begin
			if (is_void_1_comb[2]) begin
				is_void_1_comb[2]= 1'b0;
				if (d_ul_0 == `RIGHT && d_ur_0 != `RIGHT)
					sel_r_1_comb= `UPL;
				else if (d_ul_0 != `RIGHT && d_ur_0 == `RIGHT)
					sel_r_1_comb= `UPR;
				else if (d_ul_0 == `RIGHT && d_ur_0 == `RIGHT) begin
					is_void_1_comb[1]= 1'b0;
					{sel_r_1_comb, sel_u1_1_comb}= {`UPL, `UPR};
				end
			end
			else begin
				if (d_ul_0 == `RIGHT) begin
					is_void_1_comb[1]= 1'b0;
					sel_u1_1_comb= `UPL;
				end
				if (d_ur_0 == `RIGHT) begin
					is_void_1_comb[0]= 1'b0;
					sel_u2_1_comb= `UPR;
				end
			end
		end
    end

    reg [3:0] is_void_1;
    reg [1:0] sel_l_1;
    reg [1:0] sel_r_1;
    reg [1:0] sel_u1_1;
    reg [1:0] sel_u2_1;
    reg [1:0] d_l_1;
    reg [1:0] d_r_1;
    reg [1:0] d_ul_1;
    reg [1:0] d_ur_1;
        
    always@(posedge clk) begin
        if(reset) begin
            is_void_1 <= 4'b1111;
            {sel_l_1,sel_r_1,sel_u1_1,sel_u2_1} <= 8'b01010101;
            {d_l_1, d_r_1, d_ul_1, d_ul_1} <= 8'b0000_0000;  
        end else begin
            is_void_1 <= is_void_1_comb;
            {sel_l_1,sel_r_1,sel_u1_1,sel_u2_1} <= {sel_l_1_comb,sel_r_1_comb,sel_u1_1_comb,sel_u2_1_comb}; 
            {d_l_1, d_r_1, d_ul_1, d_ur_1} <= {d_l_0, d_r_0, d_ul_0, d_ur_0};
        end
    end               

    reg [3:0] is_void_2_comb;
    reg [1:0] sel_l_2_comb;
    reg [1:0] sel_r_2_comb;
    reg [1:0] sel_u1_2_comb;
    reg [1:0] sel_u2_2_comb;
    
	always @* begin
		is_void_2_comb = is_void_1;
        {sel_l_2_comb,sel_r_2_comb,sel_u1_2_comb,sel_u2_2_comb} = {sel_l_1,sel_r_1,sel_u1_1,sel_u2_1};
		// Third Priority: Side Link
		// Left to Right (Left has priority over Right)
		if (d_l_1 == `RIGHT) begin
			if (is_void_2_comb[2]) begin
				is_void_2_comb[2]= 1'b0;
				sel_r_2_comb= `LEFT;
			end
			else if (is_void_2_comb[3]) begin
				is_void_2_comb[3]= 1'b0;
				sel_l_2_comb= `LEFT;
			end
			else if (is_void_2_comb[1]) begin
				is_void_2_comb[1]= 1'b0;
				sel_u1_2_comb= `LEFT;
			end
			else if (is_void_2_comb[0]) begin
				is_void_2_comb[0]= 1'b0;
				sel_u2_2_comb= `LEFT;
			end
		end

		// Right to Left
		if (d_r_1 == `LEFT) begin
			if (is_void_2_comb[3]) begin
				is_void_2_comb[3]= 1'b0;
				sel_l_2_comb= `RIGHT;
			end
			else if (is_void_2_comb[2]) begin
				is_void_2_comb[2]= 1'b0;
				sel_r_2_comb= `RIGHT;
			end
			else if (is_void_2_comb[1]) begin
				is_void_2_comb[1]= 1'b0;
				sel_u1_2_comb= `RIGHT;
			end
			else if (is_void_2_comb[0]) begin
				is_void_2_comb[0]= 1'b0;
				sel_u2_2_comb= `RIGHT;
			end
		end
    end
		
    reg [3:0] is_void_2;
    reg [1:0] sel_l_2;
    reg [1:0] sel_r_2;
    reg [1:0] sel_u1_2;
    reg [1:0] sel_u2_2;
    reg [1:0] d_l_2;
    reg [1:0] d_r_2;
    reg [1:0] d_ul_2;
    reg [1:0] d_ur_2;
        
    always@(posedge clk) begin
        if(reset) begin
            is_void_2 <= 4'b1111;
            {sel_l_2,sel_r_2,sel_u1_2,sel_u2_2} <= 8'b01010101;
            {d_l_2, d_r_2, d_ul_2, d_ul_2} <= 8'b0000_0000;  
        end else begin
            is_void_2 <= is_void_2_comb;
            {sel_l_2,sel_r_2,sel_u1_2,sel_u2_2} <= {sel_l_2_comb,sel_r_2_comb,sel_u1_2_comb,sel_u2_2_comb}; 
            {d_l_2, d_r_2, d_ul_2, d_ur_2} <= {d_l_1, d_r_1, d_ul_1, d_ur_1};
        end
    end               		
		
		
    reg [3:0] is_void_3_comb;
    reg [1:0] sel_l_3_comb;
    reg [1:0] sel_r_3_comb;
    reg [1:0] sel_u1_3_comb;
    reg [1:0] sel_u2_3_comb;
    
    always @* begin
        is_void_3_comb = is_void_2;
        {sel_l_3_comb,sel_r_3_comb,sel_u1_3_comb,sel_u2_3_comb} = {sel_l_2,sel_r_2,sel_u1_2,sel_u2_2};		
		// Fourth Priority: Uplinks
		// Left to Up
		if (d_l_2 == `UP) begin
			if (is_void_3_comb[1]) begin
				is_void_3_comb[1]= 1'b0;
				sel_u1_3_comb= `LEFT;
			end
			else if (is_void_3_comb[0]) begin
				is_void_3_comb[0]= 1'b0;
				sel_u2_3_comb= `LEFT;
			end
			else if (is_void_3_comb[3]) begin
				is_void_3_comb[3]= 1'b0;
				sel_l_3_comb= `LEFT;
			end
			else if (is_void_3_comb[2]) begin
				is_void_3_comb[2]= 1'b0;
				sel_r_3_comb= `LEFT;
			end
		end
		// Right to UP
		if (d_r_2 == `UP) begin
			if (is_void_3_comb[1]) begin
				is_void_3_comb[1]= 1'b0;
				sel_u1_3_comb= `RIGHT;
			end
			else if (is_void_3_comb[0]) begin
				is_void_3_comb[0]= 1'b0;
				sel_u2_3_comb= `RIGHT;
			end
			else if (is_void_3_comb[2]) begin
				is_void_3_comb[2]= 1'b0;
				sel_r_3_comb= `RIGHT;
			end
			else if (is_void_3_comb[3]) begin
				is_void_3_comb[3]= 1'b0;
				sel_l_3_comb= `RIGHT;
			end
		end
    end


    reg [3:0] is_void_3;
    reg [1:0] sel_l_3;
    reg [1:0] sel_r_3;
    reg [1:0] sel_u1_3;
    reg [1:0] sel_u2_3;
    reg [1:0] d_l_3;
    reg [1:0] d_r_3;
    reg [1:0] d_ul_3;
    reg [1:0] d_ur_3;
        
    always@(posedge clk) begin
        if(reset) begin
            is_void_3 <= 4'b1111;
            {sel_l_3,sel_r_3,sel_u1_3,sel_u2_3} <= 8'b01010101;
            {d_l_3, d_r_3, d_ul_3, d_ul_3} <= 8'b0000_0000;  
        end else begin
            is_void_3 <= is_void_3_comb;
            {sel_l_3,sel_r_3,sel_u1_3,sel_u2_3} <= {sel_l_3_comb,sel_r_3_comb,sel_u1_3_comb,sel_u2_3_comb}; 
            {d_l_3, d_r_3, d_ul_3, d_ur_3} <= {d_l_2, d_r_2, d_ul_2, d_ur_2};
        end
    end   


    reg [3:0] is_void_4_comb;
    reg [1:0] sel_l_4_comb;
    reg [1:0] sel_r_4_comb;
    reg [1:0] sel_u1_4_comb;
    reg [1:0] sel_u2_4_comb;
    reg rand_gen_4_comb;
    always @* begin
        is_void_4_comb = is_void_3;
        {sel_l_4_comb,sel_r_4_comb,sel_u1_4_comb,sel_u2_4_comb} = {sel_l_3,sel_r_3,sel_u1_3,sel_u2_3};		
		// Before taking care of void case, determine whether or not a new
		// random/toggle bit should be generated
		if (is_void_4_comb[1] == 1'b0 || is_void_4_comb[0] == 1'b0)
			rand_gen_4_comb= 1;
		else 
		    rand_gen_4_comb= 0;

		// Final Priority: Void 
		if (d_l_3 == `VOID) begin
			if (is_void_4_comb[3]) begin
				is_void_4_comb[3]= 1'b0;
				sel_l_4_comb= `LEFT;
			end
			if (is_void_4_comb[2]) begin
				is_void_4_comb[2]= 1'b0;
				sel_r_4_comb= `LEFT;
			end
			if (is_void_4_comb[1]) begin
				is_void_4_comb[1]= 1'b0;
				sel_u1_4_comb= `LEFT;
			end
			if (is_void_4_comb[0]) begin
				is_void_4_comb[0]= 1'b0;
				sel_u2_4_comb= `LEFT;
			end
		end
		if (d_r_3 == `VOID) begin
			if (is_void_4_comb[3]) begin
				is_void_4_comb[3]= 1'b0;
				sel_l_4_comb= `RIGHT;
			end
			if (is_void_4_comb[2]) begin
				is_void_4_comb[2]= 1'b0;
				sel_r_4_comb= `RIGHT;
			end
			if (is_void_4_comb[1]) begin
				is_void_4_comb[1]= 1'b0;
				sel_u1_4_comb= `RIGHT;
			end
			if (is_void_4_comb[0]) begin
				is_void_4_comb[0]= 1'b0;
				sel_u2_4_comb= `RIGHT;
			end
		end
		if (d_ul_3 == `VOID) begin
			if (is_void_4_comb[3]) begin
				is_void_4_comb[3]= 1'b0;
				sel_l_4_comb= `UPL;
			end
			if (is_void_4_comb[2]) begin
				is_void_4_comb[2]= 1'b0;
				sel_r_4_comb= `UPL;
			end
			if (is_void_4_comb[1]) begin
				is_void_4_comb[1]= 1'b0;
				sel_u1_4_comb= `UPL;
			end
			if (is_void_4_comb[0]) begin
				is_void_4_comb[0]= 1'b0;
				sel_u2_4_comb= `UPL;
			end
		end
		if (d_ur_3 == `VOID) begin
			if (is_void_4_comb[3]) begin
				is_void_4_comb[3]= 1'b0;
				sel_l_4_comb= `UPR;
			end
			if (is_void_4_comb[2]) begin
				is_void_4_comb[2]= 1'b0;
				sel_r_4_comb= `UPR;
			end
			if (is_void_4_comb[1]) begin
				is_void_4_comb[1]= 1'b0;
				sel_u1_4_comb= `UPR;
			end
			if (is_void_4_comb[0]) begin
				is_void_4_comb[0]= 1'b0;
				sel_u2_4_comb= `UPR;
			end
		end
	end

    always@(posedge clk) begin
        if(reset) begin
            {sel_l,sel_r,sel_u1,sel_u2} <= 8'b01010101;
            rand_gen <= 1'b0;
        end else begin
            rand_gen <= rand_gen_4_comb;
            {sel_l,sel_r,sel_u1,sel_u2} <= {sel_l_4_comb,sel_r_4_comb,sel_u1_4_comb,sel_u2_4_comb}; 
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
