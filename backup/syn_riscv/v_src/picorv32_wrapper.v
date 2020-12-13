module picorv32_wrapper#(
  //parameter MEM_SIZE = 128*1024/4
  parameter MEM_SIZE = 2048
  )(
  input clk,
  input resetn,
  output reg [48:0] print_out,
  input val_in1,
  input val_in2,
  input val_in3,
  input val_in4,
  output ready_upward1,
  output ready_upward2,
  output ready_upward3,
  output ready_upward4,
  input [31:0] din1,
  input [31:0] din2,
  input [31:0] din3,
  input [31:0] din4,
  output val_out1,
  output val_out2,
  output val_out3,
  output val_out4,
  input ready_downward1,
  input ready_downward2,
  input ready_downward3,
  input ready_downward4,
  output [31:0] dout1,
  output [31:0] dout2,
  output [31:0] dout3,
  output [31:0] dout4,
  output trap
);
  wire mem_valid;
  wire mem_instr;
  wire mem_ready;
  wire [31:0] mem_addr;
  wire [31:0] mem_wdata;
  wire [3:0] mem_wstrb;
  wire [31:0] mem_rdata;
  wire [31:0] irq;



    
	picorv32 #(
	) uut (
	.clk         (clk        ),
	.resetn      (resetn     ),
	.trap        (trap       ),
	.mem_valid   (mem_valid  ),
	.mem_instr   (mem_instr  ),
	.mem_ready   (mem_ready  ),
	.mem_addr    (mem_addr   ),
	.mem_wdata   (mem_wdata  ),
	.mem_wstrb   (mem_wstrb  ),
	.mem_rdata   (mem_rdata  ),
	.irq         (irq        )
	);
	
	picorv_mem#(
        .MEM_SIZE(MEM_SIZE)
	) picorv_mem_inst (
        .clk         (clk),
        .resetn      (resetn     ),
        .mem_valid   (mem_valid  ),
        .mem_instr   (mem_instr  ),
        .mem_ready   (mem_ready  ),
        .mem_addr    (mem_addr   ),
        .mem_wdata   (mem_wdata  ),
        .mem_wstrb   (mem_wstrb  ),
        .mem_rdata   (mem_rdata  ),
        .val_out1    (val_out1    ),
        .val_out2    (val_out2    ),
        .val_out3    (val_out3    ),
        .val_out4    (val_out4    ),
        .ready_downward1(ready_downward1),
        .ready_downward2(ready_downward2),
        .ready_downward3(ready_downward3),
        .ready_downward4(ready_downward4),
        .dout1       (dout1       ),
        .dout2       (dout2       ),
        .dout3       (dout3       ),
        .dout4       (dout4       ),
        .val_in1     (val_in1   ),
        .val_in2     (val_in2   ),
        .val_in3     (val_in3   ),
        .val_in4     (val_in4   ),
        .ready_upward1(ready_upward1),
        .ready_upward2(ready_upward2),
        .ready_upward3(ready_upward3),
        .ready_upward4(ready_upward4),
        .din1        (din1      ),
        .din2        (din2      ),
        .din3        (din3      ),
        .din4        (din4      ),
        .irq         (irq        )
	); 

	
    always@(posedge clk) begin
        if(!resetn) begin
          print_out <= 0;
        end else begin
          if(mem_addr == 32'h1000_0000 && mem_ready==1)
            print_out <= {1'b1, 40'h0000000000, mem_wdata[7:0]};
          else
            print_out <= {1'b0, 48'h0000_0000_0000};
        end          
    end
    

   /* 
    fifo_stream fifo_stream_inst(
        .clk(clk),
        .reset(!resetn),
        .din(din),
        .val_in(val_in),
        .ready_upward(ready_upward),
        .dout(dout),
        .val_out(val_out),
        .ready_downward(ready_downward)
        );
     */   
        

endmodule

