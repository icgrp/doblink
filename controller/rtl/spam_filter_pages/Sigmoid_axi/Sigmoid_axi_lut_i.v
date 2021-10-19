// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
`timescale 1 ns / 1 ps
module Sigmoid_axi_lut_i_rom (
addr0, ce0, q0, clk);

parameter DWIDTH = 10;
parameter AWIDTH = 11;
parameter MEM_SIZE = 2048;

input[AWIDTH-1:0] addr0;
input ce0;
output wire[DWIDTH-1:0] q0;
input clk;

reg [DWIDTH-1:0] ram[0:MEM_SIZE-1];
reg [DWIDTH-1:0] q0_t0;
reg [DWIDTH-1:0] q0_t1;

initial begin
    $readmemh("./Sigmoid_axi_lut_i_rom.dat", ram);
end

assign q0 = q0_t1;

always @(posedge clk)  
begin
    if (ce0) 
    begin
        q0_t1 <= q0_t0;
    end
end


always @(posedge clk)  
begin 
    if (ce0) 
    begin
        q0_t0 <= ram[addr0];
    end
end



endmodule

`timescale 1 ns / 1 ps
module Sigmoid_axi_lut_i(
    reset,
    clk,
    address0,
    ce0,
    q0);

parameter DataWidth = 32'd10;
parameter AddressRange = 32'd2048;
parameter AddressWidth = 32'd11;
input reset;
input clk;
input[AddressWidth - 1:0] address0;
input ce0;
output[DataWidth - 1:0] q0;



Sigmoid_axi_lut_i_rom Sigmoid_axi_lut_i_rom_U(
    .clk( clk ),
    .addr0( address0 ),
    .ce0( ce0 ),
    .q0( q0 ));

endmodule

