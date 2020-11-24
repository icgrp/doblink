`define COMPLEMENT_PATTERN
module test;

	parameter num_leaves= 8;
	parameter payload_sz= 3 + 4;
	parameter p_sz= 1 + 3 + payload_sz;
 

	integer k;

	initial begin
		$dumpfile("gen_nw.vcd");
		$dumpvars(0, gen_nw_test);
		$dumpvars(0, test);
		$dumpvars(0, gen_pe[0]);
		for (k= 0; k < num_leaves; k= k + 1) begin
			$dumpvars(0, test.pe_interface_arr[k]);
			$dumpvars(0, test.interface_pe_arr[k]);
			end
		#360050.0
		$finish;
	end

	reg clk;
	reg reset;
	
	wire [num_leaves*p_sz-1:0] pe_interface;
	wire [num_leaves*p_sz-1:0] interface_pe;
	wire [p_sz-1:0] pe_interface_arr [num_leaves-1:0];
	wire [p_sz-1:0] interface_pe_arr [num_leaves-1:0];
	wire [num_leaves-1:0] resend;

integer i;
	initial begin
		{clk, reset}= 2'b01;
		#50
		for (i= 0; i < 2^(100); i= i + 1) begin
			if (i == 1) reset <= 0;
			clk<= ~clk;
			#10;
		end
	end

	gen_nw #(
		.num_leaves(num_leaves),
		.payload_sz(payload_sz),
		.p_sz(p_sz),
		.addr(1'b0),
		.level(0))
		gen_nw_test(
			.clk(clk),
			.reset(reset),
			.pe_interface(pe_interface),
			.interface_pe(interface_pe),
			.resend(resend));

	genvar j;
	generate
	for (j= 0; j < num_leaves; j=j+1) begin : gen_pe
		assign pe_interface[j*p_sz+:p_sz]= pe_interface_arr[j];
		assign interface_pe_arr[j]=  interface_pe[j*p_sz+:p_sz];

		packet_creator #(
			.num_leaves(num_leaves),
			.payload_sz(payload_sz),
			.addr(j[$clog2(num_leaves)-1:0]),
			.p_sz(p_sz))
			pc(
				.clk(clk),
				.reset(reset),
				.bus_o(pe_interface_arr[j]),
				.resend(resend[j]));
	end
	endgenerate

	initial $display("type\tPE\tpacket\t\ttime");
	genvar m;
	generate
	for(m= 0; m < num_leaves; m= m + 1) begin
		always @(posedge clk) begin
			if (pe_interface_arr[m][p_sz-1])
				$display("sent\t%05d\t%b\t%0d", m, pe_interface_arr[m], $time);
			if (interface_pe_arr[m][p_sz-1])
				$display("rcvd\t%05d\t%b\t%0d", m, interface_pe_arr[m], $time);
		end
	end
	endgenerate
endmodule 