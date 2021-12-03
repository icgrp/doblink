// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
`timescale 1 ns / 1 ps
module zculling_bot_z_buffer_V_ram (addr0, ce0, d0, we0, addr1, ce1, d1, we1, q1,  clk);

parameter DWIDTH = 8;
parameter AWIDTH = 15;
parameter MEM_SIZE = 32768;

input[AWIDTH-1:0] addr0;
input ce0;
input[DWIDTH-1:0] d0;
input we0;
input[AWIDTH-1:0] addr1;
input ce1;
input[DWIDTH-1:0] d1;
input we1;
output wire[DWIDTH-1:0] q1;
input clk;

reg [DWIDTH-1:0] ram[0:MEM_SIZE-1];
reg [DWIDTH-1:0] q1_t0;
reg [DWIDTH-1:0] q1_t1;


assign q1 = q1_t1;

always @(posedge clk)  
begin
    if (ce1) 
    begin
        q1_t1 <= q1_t0;
    end
end


always @(posedge clk)  
begin 
    if (ce0) begin
        if (we0) 
            ram[addr0] <= d0; 
    end
end


always @(posedge clk)  
begin 
    if (ce1) begin
        if (we1) 
            ram[addr1] <= d1; 
        q1_t0 <= ram[addr1];
    end
end


endmodule

