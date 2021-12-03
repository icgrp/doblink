// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================

`timescale 1ns/1ps

module zculling_top_z_buffer_V
#(parameter
    DataWidth    = 8,
    AddressWidth = 15,
    AddressRange = 32768
)(
    input  wire                    clk,
    input  wire                    reset,
    input  wire [AddressWidth-1:0] address0,
    input  wire                    ce0,
    input  wire                    we0,
    input  wire [DataWidth-1:0]    d0,
    input  wire [AddressWidth-1:0] address1,
    input  wire                    ce1,
    input  wire                    we1,
    input  wire [DataWidth-1:0]    d1,
    output wire [DataWidth-1:0]    q1
);
//------------------------Local signal-------------------
reg  [AddressRange-1:0] written = {AddressRange{1'b0}};
wire [DataWidth-1:0]    q1_ram;
wire [DataWidth-1:0]    q1_rom;
wire                    q1_sel;
reg  [1:0]              sel1_sr;
//------------------------Instantiation------------------
zculling_top_z_buffer_V_ram zculling_top_z_buffer_V_ram_u (
    .clk   ( clk ),
    .ce0   ( ce0 ),
    .addr0 ( address0 ),
    .we0   ( we0 ),
    .d0    ( d0 ),
    .ce1   ( ce1 ),
    .addr1 ( address1 ),
    .we1   ( we1 ),
    .d1    ( d1 ),
    .q1    ( q1_ram )
);
//------------------------Body---------------------------
assign q1     = q1_sel? q1_ram : q1_rom;
assign q1_sel = sel1_sr[1];
assign q1_rom = 8'b00000000;

always @(posedge clk) begin
    if (reset)
        written <= 1'b0;
    else begin
        if (ce0 & we0) begin
            written[address0] <= 1'b1;
        end
        if (ce1 & we1) begin
            written[address1] <= 1'b1;
        end
    end
end

always @(posedge clk) begin
    if (ce1) begin
        sel1_sr[0] <= written[address1];
    end
    sel1_sr[1:1] <= sel1_sr[0:0];
end

endmodule
