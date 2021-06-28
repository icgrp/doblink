module picorv_mem#(
  //parameter MEM_SIZE=128*1024/4,
  parameter MEM_SIZE=2048,
  parameter ADDR_BITS=11,
  parameter RAM_TYPE = "block"
  )(
  input clk,
  input resetn,
  input mem_valid,
  input mem_instr,
  output reg mem_ready,
  input [31:0] mem_addr,
  input [31:0] mem_wdata,
  input [3:0] mem_wstrb,
  output reg [31:0] mem_rdata,
  output val_out1,
  output val_out2,
  output val_out3,
  output val_out4,
  output [31:0] dout,
  output [31:0] dout1,
  output [31:0] dout2,
  output [31:0] dout3,
  output [31:0] dout4,
  input ready_downward,
  input ready_downward1,
  input ready_downward2,
  input ready_downward3,
  input ready_downward4,
  input [31:0] din1,
  input [31:0] din2,
  input [31:0] din3,
  input [31:0] din4,
  input val_in1,
  input val_in2,
  input val_in3,
  input val_in4,
  output reg ready_upward1,
  output reg ready_upward2,
  output reg ready_upward3,
  output reg ready_upward4,
  output reg [31:0] irq
  ); 
  


	wire val_out_tmp;
	wire stream2riscv_vld1;
	wire stream2riscv_vld2;
	wire stream2riscv_vld3;
	wire stream2riscv_vld4;

    
    reg [15:0] count_cycle;
    always @(posedge clk) count_cycle <= resetn ? count_cycle + 1 : 0;

    always @* begin
        irq = 0;
        irq[4] = &count_cycle[12:0];
        irq[5] = &count_cycle[15:0];
    end	

    
    assign val_out1 = (mem_addr == 32'h10000008) ? val_out_tmp : 1'b0;
    assign val_out2 = (mem_addr == 32'h10000010) ? val_out_tmp : 1'b0;
    assign val_out3 = (mem_addr == 32'h10000018) ? val_out_tmp : 1'b0;
    assign val_out4 = (mem_addr == 32'h10000020) ? val_out_tmp : 1'b0;
    assign stream2riscv_vld1 =  (mem_addr == 32'h10000004) ? 1'b1 : 1'b0;
    assign stream2riscv_vld2 =  (mem_addr == 32'h1000000c) ? 1'b1 : 1'b0;
    assign stream2riscv_vld3 =  (mem_addr == 32'h10000014) ? 1'b1 : 1'b0;
    assign stream2riscv_vld4 =  (mem_addr == 32'h1000001c) ? 1'b1 : 1'b0;
    

    reg [7:0] ready_upward_cnt1;
    reg [7:0] ready_upward_cnt2;
    reg [7:0] ready_upward_cnt3;
    reg [7:0] ready_upward_cnt4;
    wire see_read_addr_cnt_en1;
    wire see_read_addr_cnt_en2;
    wire see_read_addr_cnt_en3;
    wire see_read_addr_cnt_en4;
    reg [7:0]  see_read_addr_cnt1;
    reg [7:0]  see_read_addr_cnt2;
    reg [7:0]  see_read_addr_cnt3;
    reg [7:0]  see_read_addr_cnt4;
        
    always@(posedge clk) begin
        if(!resetn) begin
            ready_upward1 <= 0;
        end else if((ready_upward_cnt1 != see_read_addr_cnt1) && val_in1) begin
            ready_upward1 <= 1;
        end else begin
            ready_upward1 <= 0;
        end
    end    
    
    always@(posedge clk) begin
        if(!resetn) begin
            ready_upward2 <= 0;
        end else if((ready_upward_cnt2 != see_read_addr_cnt2) && val_in2) begin
            ready_upward2 <= 1;
        end else begin
            ready_upward2 <= 0;
        end
    end  
    
    always@(posedge clk) begin
        if(!resetn) begin
            ready_upward3 <= 0;
        end else if((ready_upward_cnt3 != see_read_addr_cnt3) && val_in3) begin
            ready_upward3 <= 1;
        end else begin
            ready_upward3 <= 0;
        end
    end  
    
    always@(posedge clk) begin
        if(!resetn) begin
            ready_upward4 <= 0;
        end else if((ready_upward_cnt4 != see_read_addr_cnt4) && val_in4) begin
            ready_upward4 <= 1;
        end else begin
            ready_upward4 <= 0;
        end
    end  
    
    
    
        
    always@(posedge clk) begin
        if(!resetn) begin
            ready_upward_cnt1 <= 0;
        end else if((ready_upward_cnt1 != see_read_addr_cnt1) && val_in1) begin
            ready_upward_cnt1 <= ready_upward_cnt1 + 1;
        end else begin
            ready_upward_cnt1 <= ready_upward_cnt1;
        end
    end    

        
    always@(posedge clk) begin
        if(!resetn) begin
            ready_upward_cnt2 <= 0;
        end else if((ready_upward_cnt2 != see_read_addr_cnt2) && val_in2) begin
            ready_upward_cnt2 <= ready_upward_cnt2 + 1;
        end else begin
            ready_upward_cnt2 <= ready_upward_cnt2;
        end
    end  
    
        
    always@(posedge clk) begin
        if(!resetn) begin
            ready_upward_cnt3 <= 0;
        end else if((ready_upward_cnt3 != see_read_addr_cnt3) && val_in3) begin
            ready_upward_cnt3 <= ready_upward_cnt3 + 1;
        end else begin
            ready_upward_cnt3 <= ready_upward_cnt3;
        end
    end          


        
    always@(posedge clk) begin
        if(!resetn) begin
            ready_upward_cnt4 <= 0;
        end else if((ready_upward_cnt4 != see_read_addr_cnt4) && val_in4) begin
            ready_upward_cnt4 <= ready_upward_cnt4 + 1;
        end else begin
            ready_upward_cnt4 <= ready_upward_cnt4;
        end
    end  
    
        
    
    always@(posedge clk) begin
        if(!resetn) begin
            see_read_addr_cnt1 <= 0;
        end else if(see_read_addr_cnt_en1) begin
            see_read_addr_cnt1 <= see_read_addr_cnt1 + 1;
        end
    end        
    
    always@(posedge clk) begin
        if(!resetn) begin
            see_read_addr_cnt2 <= 0;
        end else if(see_read_addr_cnt_en2) begin
            see_read_addr_cnt2 <= see_read_addr_cnt2 + 1;
        end
    end  

    always@(posedge clk) begin
        if(!resetn) begin
            see_read_addr_cnt3 <= 0;
        end else if(see_read_addr_cnt_en3) begin
            see_read_addr_cnt3 <= see_read_addr_cnt3 + 1;
        end
    end  

    always@(posedge clk) begin
        if(!resetn) begin
            see_read_addr_cnt4 <= 0;
        end else if(see_read_addr_cnt_en4) begin
            see_read_addr_cnt4 <= see_read_addr_cnt4 + 1;
        end
    end  
    
                    
    rise_detect #(
        .data_width(1)
    )i1(
        .data_out(val_out_tmp),
        .data_in(mem_valid),
        .clk(clk),
        .reset(!resetn)
    );
        
    rise_detect #(
        .data_width(1)
    )rise1(
        .data_out(see_read_addr_cnt_en1),
        .data_in(stream2riscv_vld1),
        .clk(clk),
        .reset(!resetn)
    );        

    rise_detect #(
        .data_width(1)
    )rise2(
        .data_out(see_read_addr_cnt_en2),
        .data_in(stream2riscv_vld2),
        .clk(clk),
        .reset(!resetn)
    );        
    
    rise_detect #(
        .data_width(1)
    )rise3(
        .data_out(see_read_addr_cnt_en3),
        .data_in(stream2riscv_vld3),
        .clk(clk),
        .reset(!resetn)
    );        
    
    rise_detect #(
        .data_width(1)
    )rise4(
        .data_out(see_read_addr_cnt_en4),
        .data_in(stream2riscv_vld4),
        .clk(clk),
        .reset(!resetn)
    );        
    
    reg [2:0] mem_rdata_sel;
    wire [ADDR_BITS-1:0] true_addr;
    assign true_addr = mem_addr[ADDR_BITS+1:2];
    assign dout1 = mem_wdata;
    assign dout2 = mem_wdata;
    assign dout3 = mem_wdata;
    assign dout4 = mem_wdata;
	always @(posedge clk) begin
		mem_ready <= 0;
		if (mem_valid && !mem_ready) begin
				if(mem_addr == 32'h10000008) begin
				    mem_ready <= ready_downward1;
				end else if(mem_addr == 32'h10000010) begin
				    mem_ready <= ready_downward2;
				end else if(mem_addr == 32'h10000018) begin
				    mem_ready <= ready_downward3;
				end else if(mem_addr == 32'h10000020) begin
				    mem_ready <= ready_downward4;
				end else if(mem_addr == 32'h10000004) begin
				    mem_ready <= val_in1;
				end else if(mem_addr == 32'h1000000c) begin
				    mem_ready <= val_in2;
				end else if(mem_addr == 32'h10000014) begin
				    mem_ready <= val_in3;
				end else if(mem_addr == 32'h1000001c) begin
				    mem_ready <= val_in4;
				end else begin
				    mem_ready <= 1'b1;
				end
				
				if(    mem_addr == 32'h10000004) begin
				    mem_rdata_sel <= 1;
				end else if(mem_addr == 32'h1000000c) begin
				    mem_rdata_sel <= 2;
				end else if(mem_addr == 32'h10000014) begin
				    mem_rdata_sel <= 3;
				end else if(mem_addr == 32'h1000001c) begin
				    mem_rdata_sel <= 4;   
				end else begin
				    mem_rdata_sel <= 0;
				end
				
        end
	end


wire [31:0] do;
always@(*) begin
    case(mem_rdata_sel)
        3'b001: mem_rdata = din1;
        3'b010: mem_rdata = din2;
        3'b011: mem_rdata = din3;
        3'b100: mem_rdata = din4;
        default: mem_rdata = do;
    endcase
end
    

ram0#(
    .DWIDTH(8),
    .AWIDTH(11),
    .RAM_TYPE("block"),
    .INIT_VALUE("./firmware0.hex")
    )ram_inst_0(                                                          
    // Write port                                                     
    .clk(clk),                                                      
    .di(mem_wdata[ 7: 0]),                                                  
    .wren((mem_valid && !mem_ready)&&(mem_wstrb[0])),                                                       
    .wraddr(true_addr),                                               
    // Read port                                                                                                           
    .rden(mem_valid && !mem_ready),                                                       
    .rdaddr(true_addr),                                               
    .do(do[7:0])
    );   

ram0#(
    .DWIDTH(8),
    .AWIDTH(11),
    .RAM_TYPE("block"),
    .INIT_VALUE("./firmware1.hex")
    )ram_inst_1(                                                          
    // Write port                                                     
    .clk(clk),                                                      
    .di(mem_wdata[ 15: 8]),                                                  
    .wren((mem_valid && !mem_ready)&&(mem_wstrb[1])),                                                       
    .wraddr(true_addr),                                               
    // Read port                                                                                                           
    .rden(mem_valid && !mem_ready),                                                       
    .rdaddr(true_addr),                                               
    .do(do[15:8])
    ); 

ram0#(
    .DWIDTH(8),
    .AWIDTH(11),
    .RAM_TYPE("block"),
    .INIT_VALUE("./firmware2.hex")
    )ram_inst_2(                                                          
    // Write port                                                     
    .clk(clk),                                                      
    .di(mem_wdata[ 23: 16]),                                                  
    .wren((mem_valid && !mem_ready)&&(mem_wstrb[2])),                                                       
    .wraddr(true_addr),                                               
    // Read port                                                                                                           
    .rden(mem_valid && !mem_ready),                                                       
    .rdaddr(true_addr),                                               
    .do(do[23:16])
    ); 
    
ram0#(
    .DWIDTH(8),
    .AWIDTH(11),
    .RAM_TYPE("block"),
    .INIT_VALUE("./firmware3.hex")
    )ram_inst_3(                                                          
    // Write port                                                     
    .clk(clk),                                                      
    .di(mem_wdata[ 31: 24]),                                                  
    .wren((mem_valid && !mem_ready)&&(mem_wstrb[3])),                                                       
    .wraddr(true_addr),                                               
    // Read port                                                                                                           
    .rden(mem_valid && !mem_ready),                                                       
    .rdaddr(true_addr),                                               
    .do(do[31:24])
    );   
endmodule

