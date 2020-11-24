module test;

	initial 
	begin
		$dumpfile("direction_determiner.vcd");
		$dumpvars(0, direction_determiner_test);
		#(100+40*num_leaves)
		$finish;
	end

	reg [48:0] String;

	reg valid;
	reg [$clog2(num_leaves)-1:0] addr;
	wire [1:0] d;	

	parameter num_leaves= 128;
	parameter module_addr= 1'b0;
	parameter level= 0;
	direction_determiner #(.num_leaves(num_leaves),  .level(level))  
						direction_determiner_test(valid, addr, d);

	integer i = 0;
	initial begin
		{valid, addr}= 0;
		#100;
		
		for ( i = 0; i < 2^(2+$clog2(num_leaves)); i = i+1) begin
			{valid, addr} <= i; 
			#20;
		end

	end

	always@*
		case (d)
			2'b00: String= "VOID";
			2'b01: String= "LEFT";
			2'b10: String= "RIGHT";
			2'b11: String= "UP";
		endcase

	initial begin
		#100
		$display("Num Leaves: %3d\t| Node Addr: %b\t| Node Level: %2d",
					num_leaves, module_addr, $bits(module_addr));

		$monitor("%d]\tvalid: %b\t| addr: %b\t| Output: %s",
              i, valid, addr, String);
	end

      
endmodule
