module SynFIFO (
	clk,
	rst_n,
	rdata, 
	wfull, 
	rempty, 
	wdata,
	winc, 
	rinc
	);
	
parameter DSIZE = 8;
parameter ASIZE = 2;
parameter MEMDEPTH = 1<<ASIZE;


output [DSIZE-1:0] rdata;
output wfull;
output rempty;

input [DSIZE-1:0] wdata;
input winc, rinc, clk, rst_n;

reg [ASIZE:0] wptr;
reg [ASIZE:0] rptr;
reg [DSIZE-1:0] ex_mem [0:MEMDEPTH-1];

wire wfull_r;
wire [ASIZE:0] wptr_1;

always @(posedge clk or negedge rst_n)
	if (!rst_n) wptr <= 0;
	else if (winc && !wfull_r) begin
		ex_mem[wptr[ASIZE-1:0]] <= wdata;
		wptr <= wptr+1;
	end


always @(posedge clk or negedge rst_n)
	if (!rst_n) rptr <= 0;
	else if (rinc && !rempty) rptr <= rptr+1;

assign wptr_1 = wptr + 1;	
assign rdata = ex_mem[rptr[ASIZE-1:0]];
assign rempty = (rptr == wptr);
assign wfull = ((wptr_1[ASIZE-1:0] == rptr[ASIZE-1:0]) && (wptr_1[ASIZE] != rptr[ASIZE]) && winc) || wfull_r;
assign wfull_r = (wptr[ASIZE-1:0] == rptr[ASIZE-1:0]) && (wptr[ASIZE] != rptr[ASIZE]);
endmodule
