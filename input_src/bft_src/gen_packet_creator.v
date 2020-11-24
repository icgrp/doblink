module packet_creator (
	input clk, 
	input reset,
	input resend,
	output reg [p_sz-1:0] bus_o
	);

	parameter num_leaves= 2;
	parameter payload_sz = 1; // contains source address
	parameter addr= 1'b0;
	parameter p_sz= 1 + $clog2(num_leaves) + payload_sz; //packet size
	parameter num_sent_per_leaf= 10;
	
	parameter send_order_sz= $clog2(num_sent_per_leaf);
	reg [send_order_sz:0] i;
	reg send_out;
	integer seed= 2939986475;
	reg [p_sz-1:0] data_to_be_sent[num_leaves*num_sent_per_leaf-1:0];
	initial begin
		{i , send_out} <= 0;
		$readmemb("./data_pattern.txt", data_to_be_sent);
	end
	always @(posedge clk) begin
		if (reset)
			{i, send_out, bus_o} <= 0;
		else if (!resend && send_out) begin
			bus_o <= data_to_be_sent[addr*num_sent_per_leaf+i];
			i <= i + 1;
			if (i < num_sent_per_leaf-1) begin
				send_out <= (($random(seed) % 20) == 1'b0);
			end
			else
				send_out <= 0;
		end
		else if (resend && send_out) begin
			bus_o <= 0;
		end
		else begin
			bus_o <= 0;
			if (i < num_sent_per_leaf) begin
				send_out <= (($random(seed) % 20) == 1'b0);
			end
			else
				send_out <= 0;
		end
	end
	endmodule