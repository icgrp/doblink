// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
`timescale 1 ns / 1 ps
module update_knn2_update_knn3_sub_training_set3_V_0_ram (addr0, ce0, d0, we0, q0,  clk);

parameter DWIDTH = 256;
parameter AWIDTH = 9;
parameter MEM_SIZE = 450;

input[AWIDTH-1:0] addr0;
input ce0;
input[DWIDTH-1:0] d0;
input we0;
output wire[DWIDTH-1:0] q0;
input clk;

reg [DWIDTH-1:0] ram[0:MEM_SIZE-1];
reg [DWIDTH-1:0] q0_t0;
reg [DWIDTH-1:0] q0_t1;

initial begin
    $readmemh("./update_knn2_update_knn3_sub_training_set3_V_0_ram.dat", ram);
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
    if (ce0) begin
        if (we0) 
            ram[addr0] <= d0; 
        q0_t0 <= ram[addr0];
    end
end


endmodule

`timescale 1 ns / 1 ps
module update_knn2_update_knn3_sub_training_set3_V_0(
    reset,
    clk,
    address0,
    ce0,
    we0,
    d0,
    q0);

parameter DataWidth = 32'd256;
parameter AddressRange = 32'd450;
parameter AddressWidth = 32'd9;
input reset;
input clk;
input[AddressWidth - 1:0] address0;
input ce0;
input we0;
input[DataWidth - 1:0] d0;
output[DataWidth - 1:0] q0;



update_knn2_update_knn3_sub_training_set3_V_0_ram update_knn2_update_knn3_sub_training_set3_V_0_ram_U(
    .clk( clk ),
    .addr0( address0 ),
    .ce0( ce0 ),
    .we0( we0 ),
    .d0( d0 ),
    .q0( q0 ));

endmodule

