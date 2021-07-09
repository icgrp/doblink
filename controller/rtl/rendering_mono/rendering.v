// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.1 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================

`timescale 1ns/1ps

module regslice_both
#(parameter 
    DataWidth=32
)(
    input ap_clk ,
    input ap_rst,

    input [DataWidth-1:0] data_in , 
    input vld_in , 
    output ack_in ,
    output [DataWidth-1:0] data_out, 
    output vld_out,
    input ack_out,
    output apdone_blk
);
 

reg   [1:0] B_V_data_1_state;
wire   [DataWidth-1:0] B_V_data_1_data_in;
reg   [DataWidth-1:0] B_V_data_1_data_out;
wire    B_V_data_1_vld_reg;
wire    B_V_data_1_vld_in;
wire    B_V_data_1_vld_out;
reg   [DataWidth-1:0] B_V_data_1_payload_A;
reg   [DataWidth-1:0] B_V_data_1_payload_B;
reg    B_V_data_1_sel_rd;
reg    B_V_data_1_sel_wr;
wire    B_V_data_1_sel;
wire    B_V_data_1_load_A;
wire    B_V_data_1_load_B;
wire    B_V_data_1_state_cmp_full;
wire    B_V_data_1_ack_in;
wire    B_V_data_1_ack_out;

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        B_V_data_1_sel_rd <= 1'b0;
    end else begin
        if (((1'b1 == B_V_data_1_vld_out) & (1'b1 == B_V_data_1_ack_out))) begin
            B_V_data_1_sel_rd <= ~B_V_data_1_sel_rd;
        end else begin
            B_V_data_1_sel_rd <= B_V_data_1_sel_rd;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        B_V_data_1_sel_wr <= 1'b0;
    end else begin
        if (((1'b1 == B_V_data_1_vld_in) & (1'b1 == B_V_data_1_ack_in))) begin
            B_V_data_1_sel_wr <= ~B_V_data_1_sel_wr;
        end else begin
            B_V_data_1_sel_wr <= B_V_data_1_sel_wr;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        B_V_data_1_state <= 2'd0;
    end else begin
        if ((((2'd3 == B_V_data_1_state) & (1'b0 == B_V_data_1_vld_in) & (1'b1 == B_V_data_1_ack_out)) | ((2'd2 == B_V_data_1_state) & (1'b0 == B_V_data_1_vld_in)))) begin
            B_V_data_1_state <= 2'd2;
        end else if ((((2'd1 == B_V_data_1_state) & (1'b0 == B_V_data_1_ack_out)) | ((2'd3 == B_V_data_1_state) & (1'b0 == B_V_data_1_ack_out) & (1'b1 == B_V_data_1_vld_in)))) begin
            B_V_data_1_state <= 2'd1;
        end else if ((((2'd1 == B_V_data_1_state) & (1'b1 == B_V_data_1_ack_out)) | (~((1'b0 == B_V_data_1_ack_out) & (1'b1 == B_V_data_1_vld_in)) & ~((1'b0 == B_V_data_1_vld_in) & (1'b1 == B_V_data_1_ack_out)) & (2'd3 == B_V_data_1_state)) | ((2'd2 == B_V_data_1_state) & (1'b1 == B_V_data_1_vld_in)))) begin
            B_V_data_1_state <= 2'd3;
        end else begin
            B_V_data_1_state <= 2'd2;
        end
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == B_V_data_1_load_A)) begin
        B_V_data_1_payload_A <= B_V_data_1_data_in;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == B_V_data_1_load_B)) begin
        B_V_data_1_payload_B <= B_V_data_1_data_in;
    end
end

always @ (*) begin
    if ((1'b1 == B_V_data_1_sel)) begin
        B_V_data_1_data_out = B_V_data_1_payload_B;
    end else begin
        B_V_data_1_data_out = B_V_data_1_payload_A;
    end
end

assign B_V_data_1_ack_in = B_V_data_1_state[1'd1];
assign B_V_data_1_load_A = (~B_V_data_1_sel_wr & B_V_data_1_state_cmp_full);
assign B_V_data_1_load_B = (B_V_data_1_state_cmp_full & B_V_data_1_sel_wr);
assign B_V_data_1_sel = B_V_data_1_sel_rd;
assign B_V_data_1_state_cmp_full = ((B_V_data_1_state != 2'd1) ? 1'b1 : 1'b0);
assign B_V_data_1_vld_out = B_V_data_1_state[1'd0];

assign ack_in = B_V_data_1_ack_in;
assign B_V_data_1_data_in = data_in;
assign B_V_data_1_vld_in = vld_in;

assign vld_out = B_V_data_1_vld_out;
assign data_out = B_V_data_1_data_out;
assign B_V_data_1_ack_out = ack_out;

assign apdone_blk = ((B_V_data_1_state == 2'd3 && ack_out == 1'b0) | (B_V_data_1_state == 2'd1));

endmodule // both


module regslice_forward 
#(parameter 
    DataWidth=32
)(
    input ap_clk ,
    input ap_rst,

    input [DataWidth-1:0] data_in , 
    input vld_in , 
    output ack_in ,
    output [DataWidth-1:0] data_out, 
    output vld_out,
    input ack_out,
    output apdone_blk
);
 
localparam W = DataWidth+1;

wire [W-1:0] cdata;
wire cstop;
wire [W-1:0] idata;
wire istop;
wire [W-1:0] odata;
wire ostop;

obuf #(
  .W(W)
)
obuf_inst(
  .clk(ap_clk),
  .reset(ap_rst),
  .cdata(idata),
  .cstop(istop),
  .odata(odata),
  .ostop(ostop)
);

assign idata = {vld_in, data_in};
assign ack_in = ~istop;

assign vld_out = odata[W-1];
assign data_out = odata[W-2:0];
assign ostop = ~ack_out;

assign apdone_blk = ((ap_rst == 1'b0)&(1'b0 == ack_out)&(1'b1 == vld_out));

endmodule //forward


module regslice_reverse 
#(parameter 
    DataWidth=32
)(
    input ap_clk ,
    input ap_rst,

    input [DataWidth-1:0] data_in , 
    input vld_in , 
    output ack_in ,
    output [DataWidth-1:0] data_out, 
    output vld_out,
    input ack_out,
    output apdone_blk
);
 
localparam W = DataWidth+1;

wire [W-1:0] cdata;
wire cstop;
wire [W-1:0] idata;
wire istop;
wire [W-1:0] odata;
wire ostop;

ibuf #(
  .W(W)
)
ibuf_inst(
  .clk(ap_clk),
  .reset(ap_rst),
  .idata(idata),
  .istop(istop),
  .cdata(odata),
  .cstop(ostop)
);
 
assign idata = {vld_in, data_in};
assign ack_in = ~istop;

assign vld_out = odata[W-1];
assign data_out = odata[W-2:0];
assign ostop = ~ack_out;

assign apdone_blk = ((ap_rst == 1'b0)&(ack_in == 1'b0));

endmodule //reverse

module regslice_both_w1 
#(parameter 
    DataWidth=1
)(
    input ap_clk ,
    input ap_rst,

    input data_in , 
    input vld_in , 
    output ack_in ,
    output data_out, 
    output vld_out,
    input ack_out,
    output apdone_blk
);

reg     [1:0] B_V_data_1_state;
wire    B_V_data_1_data_in;
reg     B_V_data_1_data_out;
wire    B_V_data_1_vld_reg;
wire    B_V_data_1_vld_in;
wire    B_V_data_1_vld_out;
reg     B_V_data_1_payload_A;
reg     B_V_data_1_payload_B;
reg     B_V_data_1_sel_rd;
reg     B_V_data_1_sel_wr;
wire    B_V_data_1_sel;
wire    B_V_data_1_load_A;
wire    B_V_data_1_load_B;
wire    B_V_data_1_state_cmp_full;
wire    B_V_data_1_ack_in;
wire    B_V_data_1_ack_out;

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        B_V_data_1_sel_rd <= 1'b0;
    end else begin
        if (((1'b1 == B_V_data_1_vld_out) & (1'b1 == B_V_data_1_ack_out))) begin
            B_V_data_1_sel_rd <= ~B_V_data_1_sel_rd;
        end else begin
            B_V_data_1_sel_rd <= B_V_data_1_sel_rd;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        B_V_data_1_sel_wr <= 1'b0;
    end else begin
        if (((1'b1 == B_V_data_1_vld_in) & (1'b1 == B_V_data_1_ack_in))) begin
            B_V_data_1_sel_wr <= ~B_V_data_1_sel_wr;
        end else begin
            B_V_data_1_sel_wr <= B_V_data_1_sel_wr;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        B_V_data_1_state <= 2'd0;
    end else begin
        if ((((2'd3 == B_V_data_1_state) & (1'b0 == B_V_data_1_vld_in) & (1'b1 == B_V_data_1_ack_out)) | ((2'd2 == B_V_data_1_state) & (1'b0 == B_V_data_1_vld_in)))) begin
            B_V_data_1_state <= 2'd2;
        end else if ((((2'd1 == B_V_data_1_state) & (1'b0 == B_V_data_1_ack_out)) | ((2'd3 == B_V_data_1_state) & (1'b0 == B_V_data_1_ack_out) & (1'b1 == B_V_data_1_vld_in)))) begin
            B_V_data_1_state <= 2'd1;
        end else if ((((2'd1 == B_V_data_1_state) & (1'b1 == B_V_data_1_ack_out)) | (~((1'b0 == B_V_data_1_ack_out) & (1'b1 == B_V_data_1_vld_in)) & ~((1'b0 == B_V_data_1_vld_in) & (1'b1 == B_V_data_1_ack_out)) & (2'd3 == B_V_data_1_state)) | ((2'd2 == B_V_data_1_state) & (1'b1 == B_V_data_1_vld_in)))) begin
            B_V_data_1_state <= 2'd3;
        end else begin
            B_V_data_1_state <= 2'd2;
        end
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == B_V_data_1_load_A)) begin
        B_V_data_1_payload_A <= B_V_data_1_data_in;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == B_V_data_1_load_B)) begin
        B_V_data_1_payload_B <= B_V_data_1_data_in;
    end
end

always @ (*) begin
    if ((1'b1 == B_V_data_1_sel)) begin
        B_V_data_1_data_out = B_V_data_1_payload_B;
    end else begin
        B_V_data_1_data_out = B_V_data_1_payload_A;
    end
end

assign B_V_data_1_ack_in = B_V_data_1_state[1'd1];
assign B_V_data_1_load_A = (~B_V_data_1_sel_wr & B_V_data_1_state_cmp_full);
assign B_V_data_1_load_B = (B_V_data_1_state_cmp_full & B_V_data_1_sel_wr);
assign B_V_data_1_sel = B_V_data_1_sel_rd;
assign B_V_data_1_state_cmp_full = ((B_V_data_1_state != 2'd1) ? 1'b1 : 1'b0);
assign B_V_data_1_vld_out = B_V_data_1_state[1'd0];

assign ack_in = B_V_data_1_ack_in;
assign B_V_data_1_data_in = data_in;
assign B_V_data_1_vld_in = vld_in;

assign vld_out = B_V_data_1_vld_out;
assign data_out = B_V_data_1_data_out;
assign B_V_data_1_ack_out = ack_out;

assign apdone_blk = ((B_V_data_1_state == 2'd3 && ack_out == 1'b0) | (B_V_data_1_state == 2'd1));

endmodule // both


module regslice_forward_w1 
#(parameter 
    DataWidth=1
)(
    input ap_clk ,
    input ap_rst,

    input data_in , 
    input vld_in , 
    output ack_in ,
    output data_out, 
    output vld_out,
    input ack_out,
    output apdone_blk
);
 
localparam W = 2;

wire [W-1:0] cdata;
wire cstop;
wire [W-1:0] idata;
wire istop;
wire [W-1:0] odata;
wire ostop;

obuf #(
  .W(W)
)
obuf_inst(
  .clk(ap_clk),
  .reset(ap_rst),
  .cdata(idata),
  .cstop(istop),
  .odata(odata),
  .ostop(ostop)
);

assign idata = {vld_in, data_in};
assign ack_in = ~istop;

assign vld_out = odata[W-1];
assign data_out = odata[W-2:0];
assign ostop = ~ack_out;

assign apdone_blk = ((ap_rst == 1'b0)&(1'b0 == ack_out)&(1'b1 == vld_out));

endmodule //forward


module regslice_reverse_w1 
#(parameter 
    DataWidth=1
)(
    input ap_clk ,
    input ap_rst,

    input data_in , 
    input vld_in , 
    output ack_in ,
    output data_out, 
    output vld_out,
    input ack_out,
    output apdone_blk
);
 
localparam W = 2;

wire [W-1:0] cdata;
wire cstop;
wire [W-1:0] idata;
wire istop;
wire [W-1:0] odata;
wire ostop;

ibuf #(
  .W(W)
)
ibuf_inst(
  .clk(ap_clk),
  .reset(ap_rst),
  .idata(idata),
  .istop(istop),
  .cdata(odata),
  .cstop(ostop)
);
 
assign idata = {vld_in, data_in};
assign ack_in = ~istop;

assign vld_out = odata[W-1];
assign data_out = odata[W-2:0];
assign ostop = ~ack_out;

assign apdone_blk = ((ap_rst == 1'b0)&(ack_in == 1'b0));

endmodule //reverse


module ibuf 
#(
    parameter W=32
)(
    input clk ,
    input reset,
    input [W-1:0] idata, 
    output istop ,
    output [W-1:0] cdata, 
    input cstop 
);
 
reg [W-1:0] ireg = {1'b0, {{W-1}{1'b0}}}; // Empty
 
assign istop = reset ? 1'b1 : ireg[W-1]; // Stop if buffering
assign cdata = istop ? ireg : idata ; // Send buffered
 
always @(posedge clk)
    if(reset)
        ireg <= {1'b0, {{W-1}{1'b0}}}; // Empty 
    else begin
        if (!cstop && ireg [W-1]) // Will core consume?
            ireg <= {1'b0, {{W-1}{1'b0}}}; // Yes: empty buffer
        else if ( cstop && !ireg[W-1]) // Core stop, empty?
            ireg <= idata; // Yes: load buffer
    end
 
endmodule

// Forward mode
module obuf 
#(
    parameter W=32
)(
    input clk ,
    input reset,
    input [W-1:0] cdata ,
    output cstop ,
    output reg [W-1:0] odata,
    input ostop 
);

// Stop the core when buffer full and output not ready
assign cstop = reset? 1'b1 : (odata[W-1] & ostop);
 
always @(posedge clk)
    if(reset)
        odata <= {1'b0, {{W-1}{1'b0}}};
    else
        if (!cstop) begin// Can we accept more data?
            odata <= cdata; // Yes: load the buffer
        end

endmodule

    
// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.1 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
`timescale 1 ns / 1 ps
module rendering_m_coloringFB_bot_m_frame_buffer_V_ram (addr0, ce0, d0, we0, q0, addr1, ce1, d1, we1, q1,  clk);

parameter DWIDTH = 8;
parameter AWIDTH = 16;
parameter MEM_SIZE = 65536;

input[AWIDTH-1:0] addr0;
input ce0;
input[DWIDTH-1:0] d0;
input we0;
output reg[DWIDTH-1:0] q0;
input[AWIDTH-1:0] addr1;
input ce1;
input[DWIDTH-1:0] d1;
input we1;
output reg[DWIDTH-1:0] q1;
input clk;

(* ram_style = "block" *)reg [DWIDTH-1:0] ram[0:MEM_SIZE-1];

initial begin
    $readmemh("./rendering_m_coloringFB_bot_m_frame_buffer_V_ram.dat", ram);
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
    if (ce0 & ~we0) begin
        q0 <= ram[addr0];
    end
end


always @(posedge clk)  
begin 
    if (ce1) begin
        if (we1) 
            ram[addr1] <= d1; 
    end
end

always @(posedge clk)  
begin 
    if (ce1 & ~we1) begin
        q1 <= ram[addr1];
    end
end


endmodule

`timescale 1 ns / 1 ps
module rendering_m_coloringFB_bot_m_frame_buffer_V(
    reset,
    clk,
    address0,
    ce0,
    we0,
    d0,
    q0,
    address1,
    ce1,
    we1,
    d1,
    q1);

parameter DataWidth = 32'd8;
parameter AddressRange = 32'd65536;
parameter AddressWidth = 32'd16;
input reset;
input clk;
input[AddressWidth - 1:0] address0;
input ce0;
input we0;
input[DataWidth - 1:0] d0;
output[DataWidth - 1:0] q0;
input[AddressWidth - 1:0] address1;
input ce1;
input we1;
input[DataWidth - 1:0] d1;
output[DataWidth - 1:0] q1;



rendering_m_coloringFB_bot_m_frame_buffer_V_ram rendering_m_coloringFB_bot_m_frame_buffer_V_ram_U(
    .clk( clk ),
    .addr0( address0 ),
    .ce0( ce0 ),
    .we0( we0 ),
    .d0( d0 ),
    .q0( q0 ),
    .addr1( address1 ),
    .ce1( ce1 ),
    .we1( we1 ),
    .d1( d1 ),
    .q1( q1 ));

endmodule

// ==============================================================
// RTL generated by Vitis HLS - High-Level Synthesis from C, C++ and OpenCL
// Version: 2020.1
// Copyright (C) 1986-2020 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

`timescale 1 ns / 1 ps 

module rendering_m_coloringFB_bot_m (
        ap_clk,
        ap_rst,
        ap_start,
        ap_done,
        ap_idle,
        ap_ready,
        Input_1_dout,
        Input_1_empty_n,
        Input_1_read,
        Output_1_V_TDATA,
        Output_1_V_TVALID,
        Output_1_V_TREADY
);

parameter    ap_ST_fsm_state1 = 136'd1;
parameter    ap_ST_fsm_state2 = 136'd2;
parameter    ap_ST_fsm_state3 = 136'd4;
parameter    ap_ST_fsm_state4 = 136'd8;
parameter    ap_ST_fsm_state5 = 136'd16;
parameter    ap_ST_fsm_state6 = 136'd32;
parameter    ap_ST_fsm_state7 = 136'd64;
parameter    ap_ST_fsm_state8 = 136'd128;
parameter    ap_ST_fsm_state9 = 136'd256;
parameter    ap_ST_fsm_state10 = 136'd512;
parameter    ap_ST_fsm_state11 = 136'd1024;
parameter    ap_ST_fsm_state12 = 136'd2048;
parameter    ap_ST_fsm_state13 = 136'd4096;
parameter    ap_ST_fsm_state14 = 136'd8192;
parameter    ap_ST_fsm_state15 = 136'd16384;
parameter    ap_ST_fsm_state16 = 136'd32768;
parameter    ap_ST_fsm_state17 = 136'd65536;
parameter    ap_ST_fsm_state18 = 136'd131072;
parameter    ap_ST_fsm_state19 = 136'd262144;
parameter    ap_ST_fsm_state20 = 136'd524288;
parameter    ap_ST_fsm_state21 = 136'd1048576;
parameter    ap_ST_fsm_state22 = 136'd2097152;
parameter    ap_ST_fsm_state23 = 136'd4194304;
parameter    ap_ST_fsm_state24 = 136'd8388608;
parameter    ap_ST_fsm_state25 = 136'd16777216;
parameter    ap_ST_fsm_state26 = 136'd33554432;
parameter    ap_ST_fsm_state27 = 136'd67108864;
parameter    ap_ST_fsm_state28 = 136'd134217728;
parameter    ap_ST_fsm_state29 = 136'd268435456;
parameter    ap_ST_fsm_state30 = 136'd536870912;
parameter    ap_ST_fsm_state31 = 136'd1073741824;
parameter    ap_ST_fsm_state32 = 136'd2147483648;
parameter    ap_ST_fsm_state33 = 136'd4294967296;
parameter    ap_ST_fsm_state34 = 136'd8589934592;
parameter    ap_ST_fsm_state35 = 136'd17179869184;
parameter    ap_ST_fsm_state36 = 136'd34359738368;
parameter    ap_ST_fsm_state37 = 136'd68719476736;
parameter    ap_ST_fsm_state38 = 136'd137438953472;
parameter    ap_ST_fsm_state39 = 136'd274877906944;
parameter    ap_ST_fsm_state40 = 136'd549755813888;
parameter    ap_ST_fsm_state41 = 136'd1099511627776;
parameter    ap_ST_fsm_state42 = 136'd2199023255552;
parameter    ap_ST_fsm_state43 = 136'd4398046511104;
parameter    ap_ST_fsm_state44 = 136'd8796093022208;
parameter    ap_ST_fsm_state45 = 136'd17592186044416;
parameter    ap_ST_fsm_state46 = 136'd35184372088832;
parameter    ap_ST_fsm_state47 = 136'd70368744177664;
parameter    ap_ST_fsm_state48 = 136'd140737488355328;
parameter    ap_ST_fsm_state49 = 136'd281474976710656;
parameter    ap_ST_fsm_state50 = 136'd562949953421312;
parameter    ap_ST_fsm_state51 = 136'd1125899906842624;
parameter    ap_ST_fsm_state52 = 136'd2251799813685248;
parameter    ap_ST_fsm_state53 = 136'd4503599627370496;
parameter    ap_ST_fsm_state54 = 136'd9007199254740992;
parameter    ap_ST_fsm_state55 = 136'd18014398509481984;
parameter    ap_ST_fsm_state56 = 136'd36028797018963968;
parameter    ap_ST_fsm_state57 = 136'd72057594037927936;
parameter    ap_ST_fsm_state58 = 136'd144115188075855872;
parameter    ap_ST_fsm_state59 = 136'd288230376151711744;
parameter    ap_ST_fsm_state60 = 136'd576460752303423488;
parameter    ap_ST_fsm_state61 = 136'd1152921504606846976;
parameter    ap_ST_fsm_state62 = 136'd2305843009213693952;
parameter    ap_ST_fsm_state63 = 136'd4611686018427387904;
parameter    ap_ST_fsm_state64 = 136'd9223372036854775808;
parameter    ap_ST_fsm_state65 = 136'd18446744073709551616;
parameter    ap_ST_fsm_state66 = 136'd36893488147419103232;
parameter    ap_ST_fsm_state67 = 136'd73786976294838206464;
parameter    ap_ST_fsm_state68 = 136'd147573952589676412928;
parameter    ap_ST_fsm_state69 = 136'd295147905179352825856;
parameter    ap_ST_fsm_state70 = 136'd590295810358705651712;
parameter    ap_ST_fsm_state71 = 136'd1180591620717411303424;
parameter    ap_ST_fsm_state72 = 136'd2361183241434822606848;
parameter    ap_ST_fsm_state73 = 136'd4722366482869645213696;
parameter    ap_ST_fsm_state74 = 136'd9444732965739290427392;
parameter    ap_ST_fsm_state75 = 136'd18889465931478580854784;
parameter    ap_ST_fsm_state76 = 136'd37778931862957161709568;
parameter    ap_ST_fsm_state77 = 136'd75557863725914323419136;
parameter    ap_ST_fsm_state78 = 136'd151115727451828646838272;
parameter    ap_ST_fsm_state79 = 136'd302231454903657293676544;
parameter    ap_ST_fsm_state80 = 136'd604462909807314587353088;
parameter    ap_ST_fsm_state81 = 136'd1208925819614629174706176;
parameter    ap_ST_fsm_state82 = 136'd2417851639229258349412352;
parameter    ap_ST_fsm_state83 = 136'd4835703278458516698824704;
parameter    ap_ST_fsm_state84 = 136'd9671406556917033397649408;
parameter    ap_ST_fsm_state85 = 136'd19342813113834066795298816;
parameter    ap_ST_fsm_state86 = 136'd38685626227668133590597632;
parameter    ap_ST_fsm_state87 = 136'd77371252455336267181195264;
parameter    ap_ST_fsm_state88 = 136'd154742504910672534362390528;
parameter    ap_ST_fsm_state89 = 136'd309485009821345068724781056;
parameter    ap_ST_fsm_state90 = 136'd618970019642690137449562112;
parameter    ap_ST_fsm_state91 = 136'd1237940039285380274899124224;
parameter    ap_ST_fsm_state92 = 136'd2475880078570760549798248448;
parameter    ap_ST_fsm_state93 = 136'd4951760157141521099596496896;
parameter    ap_ST_fsm_state94 = 136'd9903520314283042199192993792;
parameter    ap_ST_fsm_state95 = 136'd19807040628566084398385987584;
parameter    ap_ST_fsm_state96 = 136'd39614081257132168796771975168;
parameter    ap_ST_fsm_state97 = 136'd79228162514264337593543950336;
parameter    ap_ST_fsm_state98 = 136'd158456325028528675187087900672;
parameter    ap_ST_fsm_state99 = 136'd316912650057057350374175801344;
parameter    ap_ST_fsm_state100 = 136'd633825300114114700748351602688;
parameter    ap_ST_fsm_state101 = 136'd1267650600228229401496703205376;
parameter    ap_ST_fsm_state102 = 136'd2535301200456458802993406410752;
parameter    ap_ST_fsm_state103 = 136'd5070602400912917605986812821504;
parameter    ap_ST_fsm_state104 = 136'd10141204801825835211973625643008;
parameter    ap_ST_fsm_state105 = 136'd20282409603651670423947251286016;
parameter    ap_ST_fsm_state106 = 136'd40564819207303340847894502572032;
parameter    ap_ST_fsm_state107 = 136'd81129638414606681695789005144064;
parameter    ap_ST_fsm_state108 = 136'd162259276829213363391578010288128;
parameter    ap_ST_fsm_state109 = 136'd324518553658426726783156020576256;
parameter    ap_ST_fsm_state110 = 136'd649037107316853453566312041152512;
parameter    ap_ST_fsm_state111 = 136'd1298074214633706907132624082305024;
parameter    ap_ST_fsm_state112 = 136'd2596148429267413814265248164610048;
parameter    ap_ST_fsm_state113 = 136'd5192296858534827628530496329220096;
parameter    ap_ST_fsm_state114 = 136'd10384593717069655257060992658440192;
parameter    ap_ST_fsm_state115 = 136'd20769187434139310514121985316880384;
parameter    ap_ST_fsm_state116 = 136'd41538374868278621028243970633760768;
parameter    ap_ST_fsm_state117 = 136'd83076749736557242056487941267521536;
parameter    ap_ST_fsm_state118 = 136'd166153499473114484112975882535043072;
parameter    ap_ST_fsm_state119 = 136'd332306998946228968225951765070086144;
parameter    ap_ST_fsm_state120 = 136'd664613997892457936451903530140172288;
parameter    ap_ST_fsm_state121 = 136'd1329227995784915872903807060280344576;
parameter    ap_ST_fsm_state122 = 136'd2658455991569831745807614120560689152;
parameter    ap_ST_fsm_state123 = 136'd5316911983139663491615228241121378304;
parameter    ap_ST_fsm_state124 = 136'd10633823966279326983230456482242756608;
parameter    ap_ST_fsm_state125 = 136'd21267647932558653966460912964485513216;
parameter    ap_ST_fsm_state126 = 136'd42535295865117307932921825928971026432;
parameter    ap_ST_fsm_state127 = 136'd85070591730234615865843651857942052864;
parameter    ap_ST_fsm_state128 = 136'd170141183460469231731687303715884105728;
parameter    ap_ST_fsm_state129 = 136'd340282366920938463463374607431768211456;
parameter    ap_ST_fsm_state130 = 136'd680564733841876926926749214863536422912;
parameter    ap_ST_fsm_pp1_stage0 = 136'd1361129467683753853853498429727072845824;
parameter    ap_ST_fsm_state133 = 136'd2722258935367507707706996859454145691648;
parameter    ap_ST_fsm_pp2_stage0 = 136'd5444517870735015415413993718908291383296;
parameter    ap_ST_fsm_pp2_stage1 = 136'd10889035741470030830827987437816582766592;
parameter    ap_ST_fsm_state138 = 136'd21778071482940061661655974875633165533184;
parameter    ap_ST_fsm_state139 = 136'd43556142965880123323311949751266331066368;

input   ap_clk;
input   ap_rst;
input   ap_start;
output   ap_done;
output   ap_idle;
output   ap_ready;
input  [31:0] Input_1_dout;
input   Input_1_empty_n;
output   Input_1_read;
output  [31:0] Output_1_V_TDATA;
output   Output_1_V_TVALID;
input   Output_1_V_TREADY;

reg ap_done;
reg ap_idle;
reg ap_ready;
reg Input_1_read;

(* fsm_encoding = "none" *) reg   [135:0] ap_CS_fsm;
wire    ap_CS_fsm_state1;
reg   [15:0] counter_1;
reg   [15:0] frame_buffer_V_address0;
reg    frame_buffer_V_ce0;
reg    frame_buffer_V_we0;
reg   [7:0] frame_buffer_V_d0;
wire   [7:0] frame_buffer_V_q0;
reg   [15:0] frame_buffer_V_address1;
reg    frame_buffer_V_ce1;
reg    frame_buffer_V_we1;
wire   [7:0] frame_buffer_V_q1;
reg    Input_1_blk_n;
wire    ap_CS_fsm_pp1_stage0;
reg    ap_enable_reg_pp1_iter1;
wire    ap_block_pp1_stage0;
reg   [0:0] icmp_ln515_reg_6886;
reg    Output_1_V_TDATA_blk_n;
wire    ap_CS_fsm_pp2_stage0;
reg    ap_enable_reg_pp2_iter1;
wire    ap_block_pp2_stage0;
reg   [0:0] icmp_ln527_reg_6904;
wire    ap_CS_fsm_pp2_stage1;
wire    ap_block_pp2_stage1;
reg   [0:0] icmp_ln527_reg_6904_pp2_iter1_reg;
reg   [15:0] empty_28_reg_2729;
reg   [14:0] indvar_flatten_reg_2740;
reg   [8:0] i_reg_2751;
reg   [8:0] j_reg_2762;
reg   [31:0] tmp_V_reg_6601;
reg    ap_block_state1;
reg   [15:0] t_V_reg_6606;
wire   [0:0] icmp_ln874_fu_2788_p2;
wire   [8:0] add_ln695_fu_2800_p2;
reg   [8:0] add_ln695_reg_6618;
wire    ap_CS_fsm_state2;
wire   [16:0] tmp_fu_2806_p3;
reg   [16:0] tmp_reg_6623;
wire   [0:0] icmp_ln882_fu_2794_p2;
wire   [15:0] empty_27_fu_6390_p1;
reg   [15:0] empty_27_reg_6881;
wire    ap_CS_fsm_state130;
wire   [0:0] icmp_ln515_fu_6393_p2;
wire    ap_block_state131_pp1_stage0_iter0;
reg    ap_block_state132_pp1_stage0_iter1;
reg    ap_block_pp1_stage0_11001;
wire   [15:0] add_ln695_7_fu_6398_p2;
reg    ap_enable_reg_pp1_iter0;
wire   [15:0] add_ln695_6_fu_6442_p2;
wire    ap_CS_fsm_state133;
wire   [0:0] icmp_ln874_2_fu_6447_p2;
wire   [0:0] icmp_ln527_fu_6453_p2;
wire    ap_block_state134_pp2_stage0_iter0;
wire    ap_block_state136_pp2_stage0_iter1;
reg    ap_block_state136_io;
reg    ap_block_pp2_stage0_11001;
wire   [14:0] add_ln527_1_fu_6459_p2;
reg   [14:0] add_ln527_1_reg_6908;
reg    ap_enable_reg_pp2_iter0;
wire   [8:0] select_ln527_fu_6479_p3;
reg   [8:0] select_ln527_reg_6913;
wire   [8:0] select_ln527_1_fu_6487_p3;
reg   [8:0] select_ln527_1_reg_6919;
wire   [7:0] trunc_ln215_fu_6495_p1;
reg   [7:0] trunc_ln215_reg_6925;
wire   [7:0] trunc_ln528_fu_6499_p1;
reg   [7:0] trunc_ln528_reg_6930;
wire    ap_block_state135_pp2_stage1_iter0;
wire    ap_block_state137_pp2_stage1_iter1;
reg    ap_block_state137_io;
reg    ap_block_pp2_stage1_11001;
reg   [7:0] frame_buffer_V_load_1_reg_6950;
reg   [7:0] frame_buffer_V_load_2_reg_6955;
wire   [8:0] add_ln528_fu_6579_p2;
reg   [8:0] add_ln528_reg_6965;
reg    ap_block_pp1_stage0_subdone;
reg    ap_condition_pp1_exit_iter0_state131;
reg    ap_block_pp2_stage0_subdone;
reg    ap_condition_pp2_exit_iter0_state134;
reg    ap_block_pp2_stage1_subdone;
reg   [8:0] empty_reg_2718;
wire    ap_CS_fsm_state129;
reg   [14:0] ap_phi_mux_indvar_flatten_phi_fu_2744_p4;
reg   [8:0] ap_phi_mux_i_phi_fu_2755_p4;
reg   [8:0] ap_phi_mux_j_phi_fu_2766_p4;
reg   [15:0] counter_1_new_0_reg_2773;
wire    ap_CS_fsm_state138;
wire   [63:0] zext_ln324_fu_2814_p1;
wire   [63:0] tmp_s_fu_2825_p3;
wire   [63:0] tmp_255_fu_2839_p3;
wire    ap_CS_fsm_state3;
wire   [63:0] tmp_256_fu_2853_p3;
wire   [63:0] tmp_257_fu_2867_p3;
wire    ap_CS_fsm_state4;
wire   [63:0] tmp_258_fu_2881_p3;
wire   [63:0] tmp_259_fu_2895_p3;
wire    ap_CS_fsm_state5;
wire   [63:0] tmp_260_fu_2909_p3;
wire   [63:0] tmp_261_fu_2923_p3;
wire    ap_CS_fsm_state6;
wire   [63:0] tmp_262_fu_2937_p3;
wire   [63:0] tmp_263_fu_2951_p3;
wire    ap_CS_fsm_state7;
wire   [63:0] tmp_264_fu_2965_p3;
wire   [63:0] tmp_265_fu_2979_p3;
wire    ap_CS_fsm_state8;
wire   [63:0] tmp_266_fu_2993_p3;
wire   [63:0] tmp_267_fu_3007_p3;
wire    ap_CS_fsm_state9;
wire   [63:0] tmp_268_fu_3021_p3;
wire   [63:0] tmp_269_fu_3035_p3;
wire    ap_CS_fsm_state10;
wire   [63:0] tmp_270_fu_3049_p3;
wire   [63:0] tmp_271_fu_3063_p3;
wire    ap_CS_fsm_state11;
wire   [63:0] tmp_272_fu_3077_p3;
wire   [63:0] tmp_273_fu_3091_p3;
wire    ap_CS_fsm_state12;
wire   [63:0] tmp_274_fu_3105_p3;
wire   [63:0] tmp_275_fu_3119_p3;
wire    ap_CS_fsm_state13;
wire   [63:0] tmp_276_fu_3133_p3;
wire   [63:0] tmp_277_fu_3147_p3;
wire    ap_CS_fsm_state14;
wire   [63:0] tmp_278_fu_3161_p3;
wire   [63:0] tmp_279_fu_3175_p3;
wire    ap_CS_fsm_state15;
wire   [63:0] tmp_280_fu_3189_p3;
wire   [63:0] tmp_281_fu_3203_p3;
wire    ap_CS_fsm_state16;
wire   [63:0] tmp_282_fu_3217_p3;
wire   [63:0] tmp_283_fu_3231_p3;
wire    ap_CS_fsm_state17;
wire   [63:0] tmp_284_fu_3245_p3;
wire   [63:0] tmp_285_fu_3259_p3;
wire    ap_CS_fsm_state18;
wire   [63:0] tmp_286_fu_3273_p3;
wire   [63:0] tmp_287_fu_3287_p3;
wire    ap_CS_fsm_state19;
wire   [63:0] tmp_288_fu_3301_p3;
wire   [63:0] tmp_289_fu_3315_p3;
wire    ap_CS_fsm_state20;
wire   [63:0] tmp_290_fu_3329_p3;
wire   [63:0] tmp_291_fu_3343_p3;
wire    ap_CS_fsm_state21;
wire   [63:0] tmp_292_fu_3357_p3;
wire   [63:0] tmp_293_fu_3371_p3;
wire    ap_CS_fsm_state22;
wire   [63:0] tmp_294_fu_3385_p3;
wire   [63:0] tmp_295_fu_3399_p3;
wire    ap_CS_fsm_state23;
wire   [63:0] tmp_296_fu_3413_p3;
wire   [63:0] tmp_297_fu_3427_p3;
wire    ap_CS_fsm_state24;
wire   [63:0] tmp_298_fu_3441_p3;
wire   [63:0] tmp_299_fu_3455_p3;
wire    ap_CS_fsm_state25;
wire   [63:0] tmp_300_fu_3469_p3;
wire   [63:0] tmp_301_fu_3483_p3;
wire    ap_CS_fsm_state26;
wire   [63:0] tmp_302_fu_3497_p3;
wire   [63:0] tmp_303_fu_3511_p3;
wire    ap_CS_fsm_state27;
wire   [63:0] tmp_304_fu_3525_p3;
wire   [63:0] tmp_305_fu_3539_p3;
wire    ap_CS_fsm_state28;
wire   [63:0] tmp_306_fu_3553_p3;
wire   [63:0] tmp_307_fu_3567_p3;
wire    ap_CS_fsm_state29;
wire   [63:0] tmp_308_fu_3581_p3;
wire   [63:0] tmp_309_fu_3595_p3;
wire    ap_CS_fsm_state30;
wire   [63:0] tmp_310_fu_3609_p3;
wire   [63:0] tmp_311_fu_3623_p3;
wire    ap_CS_fsm_state31;
wire   [63:0] tmp_312_fu_3637_p3;
wire   [63:0] tmp_313_fu_3651_p3;
wire    ap_CS_fsm_state32;
wire   [63:0] tmp_314_fu_3665_p3;
wire   [63:0] tmp_315_fu_3679_p3;
wire    ap_CS_fsm_state33;
wire   [63:0] tmp_316_fu_3693_p3;
wire   [63:0] tmp_317_fu_3707_p3;
wire    ap_CS_fsm_state34;
wire   [63:0] tmp_318_fu_3721_p3;
wire   [63:0] tmp_319_fu_3735_p3;
wire    ap_CS_fsm_state35;
wire   [63:0] tmp_320_fu_3749_p3;
wire   [63:0] tmp_321_fu_3763_p3;
wire    ap_CS_fsm_state36;
wire   [63:0] tmp_322_fu_3777_p3;
wire   [63:0] tmp_323_fu_3791_p3;
wire    ap_CS_fsm_state37;
wire   [63:0] tmp_324_fu_3805_p3;
wire   [63:0] tmp_325_fu_3819_p3;
wire    ap_CS_fsm_state38;
wire   [63:0] tmp_326_fu_3833_p3;
wire   [63:0] tmp_327_fu_3847_p3;
wire    ap_CS_fsm_state39;
wire   [63:0] tmp_328_fu_3861_p3;
wire   [63:0] tmp_329_fu_3875_p3;
wire    ap_CS_fsm_state40;
wire   [63:0] tmp_330_fu_3889_p3;
wire   [63:0] tmp_331_fu_3903_p3;
wire    ap_CS_fsm_state41;
wire   [63:0] tmp_332_fu_3917_p3;
wire   [63:0] tmp_333_fu_3931_p3;
wire    ap_CS_fsm_state42;
wire   [63:0] tmp_334_fu_3945_p3;
wire   [63:0] tmp_335_fu_3959_p3;
wire    ap_CS_fsm_state43;
wire   [63:0] tmp_336_fu_3973_p3;
wire   [63:0] tmp_337_fu_3987_p3;
wire    ap_CS_fsm_state44;
wire   [63:0] tmp_338_fu_4001_p3;
wire   [63:0] tmp_339_fu_4015_p3;
wire    ap_CS_fsm_state45;
wire   [63:0] tmp_340_fu_4029_p3;
wire   [63:0] tmp_341_fu_4043_p3;
wire    ap_CS_fsm_state46;
wire   [63:0] tmp_342_fu_4057_p3;
wire   [63:0] tmp_343_fu_4071_p3;
wire    ap_CS_fsm_state47;
wire   [63:0] tmp_344_fu_4085_p3;
wire   [63:0] tmp_345_fu_4099_p3;
wire    ap_CS_fsm_state48;
wire   [63:0] tmp_346_fu_4113_p3;
wire   [63:0] tmp_347_fu_4127_p3;
wire    ap_CS_fsm_state49;
wire   [63:0] tmp_348_fu_4141_p3;
wire   [63:0] tmp_349_fu_4155_p3;
wire    ap_CS_fsm_state50;
wire   [63:0] tmp_350_fu_4169_p3;
wire   [63:0] tmp_351_fu_4183_p3;
wire    ap_CS_fsm_state51;
wire   [63:0] tmp_352_fu_4197_p3;
wire   [63:0] tmp_353_fu_4211_p3;
wire    ap_CS_fsm_state52;
wire   [63:0] tmp_354_fu_4225_p3;
wire   [63:0] tmp_355_fu_4239_p3;
wire    ap_CS_fsm_state53;
wire   [63:0] tmp_356_fu_4253_p3;
wire   [63:0] tmp_357_fu_4267_p3;
wire    ap_CS_fsm_state54;
wire   [63:0] tmp_358_fu_4281_p3;
wire   [63:0] tmp_359_fu_4295_p3;
wire    ap_CS_fsm_state55;
wire   [63:0] tmp_360_fu_4309_p3;
wire   [63:0] tmp_361_fu_4323_p3;
wire    ap_CS_fsm_state56;
wire   [63:0] tmp_362_fu_4337_p3;
wire   [63:0] tmp_363_fu_4351_p3;
wire    ap_CS_fsm_state57;
wire   [63:0] tmp_364_fu_4365_p3;
wire   [63:0] tmp_365_fu_4379_p3;
wire    ap_CS_fsm_state58;
wire   [63:0] tmp_366_fu_4393_p3;
wire   [63:0] tmp_367_fu_4407_p3;
wire    ap_CS_fsm_state59;
wire   [63:0] tmp_368_fu_4421_p3;
wire   [63:0] tmp_369_fu_4435_p3;
wire    ap_CS_fsm_state60;
wire   [63:0] tmp_370_fu_4449_p3;
wire   [63:0] tmp_371_fu_4463_p3;
wire    ap_CS_fsm_state61;
wire   [63:0] tmp_372_fu_4477_p3;
wire   [63:0] tmp_373_fu_4491_p3;
wire    ap_CS_fsm_state62;
wire   [63:0] tmp_374_fu_4505_p3;
wire   [63:0] tmp_375_fu_4519_p3;
wire    ap_CS_fsm_state63;
wire   [63:0] tmp_376_fu_4533_p3;
wire   [63:0] tmp_377_fu_4547_p3;
wire    ap_CS_fsm_state64;
wire   [63:0] tmp_378_fu_4561_p3;
wire   [63:0] tmp_379_fu_4575_p3;
wire    ap_CS_fsm_state65;
wire   [63:0] tmp_380_fu_4589_p3;
wire   [63:0] tmp_381_fu_4603_p3;
wire    ap_CS_fsm_state66;
wire   [63:0] tmp_382_fu_4617_p3;
wire   [63:0] tmp_383_fu_4631_p3;
wire    ap_CS_fsm_state67;
wire   [63:0] tmp_384_fu_4645_p3;
wire   [63:0] tmp_385_fu_4659_p3;
wire    ap_CS_fsm_state68;
wire   [63:0] tmp_386_fu_4673_p3;
wire   [63:0] tmp_387_fu_4687_p3;
wire    ap_CS_fsm_state69;
wire   [63:0] tmp_388_fu_4701_p3;
wire   [63:0] tmp_389_fu_4715_p3;
wire    ap_CS_fsm_state70;
wire   [63:0] tmp_390_fu_4729_p3;
wire   [63:0] tmp_391_fu_4743_p3;
wire    ap_CS_fsm_state71;
wire   [63:0] tmp_392_fu_4757_p3;
wire   [63:0] tmp_393_fu_4771_p3;
wire    ap_CS_fsm_state72;
wire   [63:0] tmp_394_fu_4785_p3;
wire   [63:0] tmp_395_fu_4799_p3;
wire    ap_CS_fsm_state73;
wire   [63:0] tmp_396_fu_4813_p3;
wire   [63:0] tmp_397_fu_4827_p3;
wire    ap_CS_fsm_state74;
wire   [63:0] tmp_398_fu_4841_p3;
wire   [63:0] tmp_399_fu_4855_p3;
wire    ap_CS_fsm_state75;
wire   [63:0] tmp_400_fu_4869_p3;
wire   [63:0] tmp_401_fu_4883_p3;
wire    ap_CS_fsm_state76;
wire   [63:0] tmp_402_fu_4897_p3;
wire   [63:0] tmp_403_fu_4911_p3;
wire    ap_CS_fsm_state77;
wire   [63:0] tmp_404_fu_4925_p3;
wire   [63:0] tmp_405_fu_4939_p3;
wire    ap_CS_fsm_state78;
wire   [63:0] tmp_406_fu_4953_p3;
wire   [63:0] tmp_407_fu_4967_p3;
wire    ap_CS_fsm_state79;
wire   [63:0] tmp_408_fu_4981_p3;
wire   [63:0] tmp_409_fu_4995_p3;
wire    ap_CS_fsm_state80;
wire   [63:0] tmp_410_fu_5009_p3;
wire   [63:0] tmp_411_fu_5023_p3;
wire    ap_CS_fsm_state81;
wire   [63:0] tmp_412_fu_5037_p3;
wire   [63:0] tmp_413_fu_5051_p3;
wire    ap_CS_fsm_state82;
wire   [63:0] tmp_414_fu_5065_p3;
wire   [63:0] tmp_415_fu_5079_p3;
wire    ap_CS_fsm_state83;
wire   [63:0] tmp_416_fu_5093_p3;
wire   [63:0] tmp_417_fu_5107_p3;
wire    ap_CS_fsm_state84;
wire   [63:0] tmp_418_fu_5121_p3;
wire   [63:0] tmp_419_fu_5135_p3;
wire    ap_CS_fsm_state85;
wire   [63:0] tmp_420_fu_5149_p3;
wire   [63:0] tmp_421_fu_5163_p3;
wire    ap_CS_fsm_state86;
wire   [63:0] tmp_422_fu_5177_p3;
wire   [63:0] tmp_423_fu_5191_p3;
wire    ap_CS_fsm_state87;
wire   [63:0] tmp_424_fu_5205_p3;
wire   [63:0] tmp_425_fu_5219_p3;
wire    ap_CS_fsm_state88;
wire   [63:0] tmp_426_fu_5233_p3;
wire   [63:0] tmp_427_fu_5247_p3;
wire    ap_CS_fsm_state89;
wire   [63:0] tmp_428_fu_5261_p3;
wire   [63:0] tmp_429_fu_5275_p3;
wire    ap_CS_fsm_state90;
wire   [63:0] tmp_430_fu_5289_p3;
wire   [63:0] tmp_431_fu_5303_p3;
wire    ap_CS_fsm_state91;
wire   [63:0] tmp_432_fu_5317_p3;
wire   [63:0] tmp_433_fu_5331_p3;
wire    ap_CS_fsm_state92;
wire   [63:0] tmp_434_fu_5345_p3;
wire   [63:0] tmp_435_fu_5359_p3;
wire    ap_CS_fsm_state93;
wire   [63:0] tmp_436_fu_5373_p3;
wire   [63:0] tmp_437_fu_5387_p3;
wire    ap_CS_fsm_state94;
wire   [63:0] tmp_438_fu_5401_p3;
wire   [63:0] tmp_439_fu_5415_p3;
wire    ap_CS_fsm_state95;
wire   [63:0] tmp_440_fu_5429_p3;
wire   [63:0] tmp_441_fu_5443_p3;
wire    ap_CS_fsm_state96;
wire   [63:0] tmp_442_fu_5457_p3;
wire   [63:0] tmp_443_fu_5471_p3;
wire    ap_CS_fsm_state97;
wire   [63:0] tmp_444_fu_5485_p3;
wire   [63:0] tmp_445_fu_5499_p3;
wire    ap_CS_fsm_state98;
wire   [63:0] tmp_446_fu_5513_p3;
wire   [63:0] tmp_447_fu_5527_p3;
wire    ap_CS_fsm_state99;
wire   [63:0] tmp_448_fu_5541_p3;
wire   [63:0] tmp_449_fu_5555_p3;
wire    ap_CS_fsm_state100;
wire   [63:0] tmp_450_fu_5569_p3;
wire   [63:0] tmp_451_fu_5583_p3;
wire    ap_CS_fsm_state101;
wire   [63:0] tmp_452_fu_5597_p3;
wire   [63:0] tmp_453_fu_5611_p3;
wire    ap_CS_fsm_state102;
wire   [63:0] tmp_454_fu_5625_p3;
wire   [63:0] tmp_455_fu_5639_p3;
wire    ap_CS_fsm_state103;
wire   [63:0] tmp_456_fu_5653_p3;
wire   [63:0] tmp_457_fu_5667_p3;
wire    ap_CS_fsm_state104;
wire   [63:0] tmp_458_fu_5681_p3;
wire   [63:0] tmp_459_fu_5695_p3;
wire    ap_CS_fsm_state105;
wire   [63:0] tmp_460_fu_5709_p3;
wire   [63:0] tmp_461_fu_5723_p3;
wire    ap_CS_fsm_state106;
wire   [63:0] tmp_462_fu_5737_p3;
wire   [63:0] tmp_463_fu_5751_p3;
wire    ap_CS_fsm_state107;
wire   [63:0] tmp_464_fu_5765_p3;
wire   [63:0] tmp_465_fu_5779_p3;
wire    ap_CS_fsm_state108;
wire   [63:0] tmp_466_fu_5793_p3;
wire   [63:0] tmp_467_fu_5807_p3;
wire    ap_CS_fsm_state109;
wire   [63:0] tmp_468_fu_5821_p3;
wire   [63:0] tmp_469_fu_5835_p3;
wire    ap_CS_fsm_state110;
wire   [63:0] tmp_470_fu_5849_p3;
wire   [63:0] tmp_471_fu_5863_p3;
wire    ap_CS_fsm_state111;
wire   [63:0] tmp_472_fu_5877_p3;
wire   [63:0] tmp_473_fu_5891_p3;
wire    ap_CS_fsm_state112;
wire   [63:0] tmp_474_fu_5905_p3;
wire   [63:0] tmp_475_fu_5919_p3;
wire    ap_CS_fsm_state113;
wire   [63:0] tmp_476_fu_5933_p3;
wire   [63:0] tmp_477_fu_5947_p3;
wire    ap_CS_fsm_state114;
wire   [63:0] tmp_478_fu_5961_p3;
wire   [63:0] tmp_479_fu_5975_p3;
wire    ap_CS_fsm_state115;
wire   [63:0] tmp_480_fu_5989_p3;
wire   [63:0] tmp_481_fu_6003_p3;
wire    ap_CS_fsm_state116;
wire   [63:0] tmp_482_fu_6017_p3;
wire   [63:0] tmp_483_fu_6031_p3;
wire    ap_CS_fsm_state117;
wire   [63:0] tmp_484_fu_6045_p3;
wire   [63:0] tmp_485_fu_6059_p3;
wire    ap_CS_fsm_state118;
wire   [63:0] tmp_486_fu_6073_p3;
wire   [63:0] tmp_487_fu_6087_p3;
wire    ap_CS_fsm_state119;
wire   [63:0] tmp_488_fu_6101_p3;
wire   [63:0] tmp_489_fu_6115_p3;
wire    ap_CS_fsm_state120;
wire   [63:0] tmp_490_fu_6129_p3;
wire   [63:0] tmp_491_fu_6143_p3;
wire    ap_CS_fsm_state121;
wire   [63:0] tmp_492_fu_6157_p3;
wire   [63:0] tmp_493_fu_6171_p3;
wire    ap_CS_fsm_state122;
wire   [63:0] tmp_494_fu_6185_p3;
wire   [63:0] tmp_495_fu_6199_p3;
wire    ap_CS_fsm_state123;
wire   [63:0] tmp_496_fu_6213_p3;
wire   [63:0] tmp_497_fu_6227_p3;
wire    ap_CS_fsm_state124;
wire   [63:0] tmp_498_fu_6241_p3;
wire   [63:0] tmp_499_fu_6255_p3;
wire    ap_CS_fsm_state125;
wire   [63:0] tmp_500_fu_6269_p3;
wire   [63:0] tmp_501_fu_6283_p3;
wire    ap_CS_fsm_state126;
wire   [63:0] tmp_502_fu_6297_p3;
wire   [63:0] tmp_503_fu_6311_p3;
wire    ap_CS_fsm_state127;
wire   [63:0] tmp_504_fu_6325_p3;
wire   [63:0] tmp_505_fu_6339_p3;
wire    ap_CS_fsm_state128;
wire   [63:0] tmp_506_fu_6353_p3;
wire   [63:0] tmp_507_fu_6367_p3;
wire   [63:0] tmp_508_fu_6381_p3;
wire   [63:0] zext_ln324_1_fu_6437_p1;
wire   [63:0] zext_ln215_6_fu_6517_p1;
wire   [63:0] zext_ln215_7_fu_6536_p1;
wire   [63:0] zext_ln215_9_fu_6557_p1;
wire   [63:0] zext_ln215_8_fu_6574_p1;
wire    ap_CS_fsm_state139;
wire    regslice_both_Output_1_V_U_apdone_blk;
wire    ap_block_pp2_stage0_01001;
wire   [16:0] or_ln324_fu_2819_p2;
wire   [16:0] or_ln324_255_fu_2834_p2;
wire   [16:0] or_ln324_256_fu_2848_p2;
wire   [16:0] or_ln324_257_fu_2862_p2;
wire   [16:0] or_ln324_258_fu_2876_p2;
wire   [16:0] or_ln324_259_fu_2890_p2;
wire   [16:0] or_ln324_260_fu_2904_p2;
wire   [16:0] or_ln324_261_fu_2918_p2;
wire   [16:0] or_ln324_262_fu_2932_p2;
wire   [16:0] or_ln324_263_fu_2946_p2;
wire   [16:0] or_ln324_264_fu_2960_p2;
wire   [16:0] or_ln324_265_fu_2974_p2;
wire   [16:0] or_ln324_266_fu_2988_p2;
wire   [16:0] or_ln324_267_fu_3002_p2;
wire   [16:0] or_ln324_268_fu_3016_p2;
wire   [16:0] or_ln324_269_fu_3030_p2;
wire   [16:0] or_ln324_270_fu_3044_p2;
wire   [16:0] or_ln324_271_fu_3058_p2;
wire   [16:0] or_ln324_272_fu_3072_p2;
wire   [16:0] or_ln324_273_fu_3086_p2;
wire   [16:0] or_ln324_274_fu_3100_p2;
wire   [16:0] or_ln324_275_fu_3114_p2;
wire   [16:0] or_ln324_276_fu_3128_p2;
wire   [16:0] or_ln324_277_fu_3142_p2;
wire   [16:0] or_ln324_278_fu_3156_p2;
wire   [16:0] or_ln324_279_fu_3170_p2;
wire   [16:0] or_ln324_280_fu_3184_p2;
wire   [16:0] or_ln324_281_fu_3198_p2;
wire   [16:0] or_ln324_282_fu_3212_p2;
wire   [16:0] or_ln324_283_fu_3226_p2;
wire   [16:0] or_ln324_284_fu_3240_p2;
wire   [16:0] or_ln324_285_fu_3254_p2;
wire   [16:0] or_ln324_286_fu_3268_p2;
wire   [16:0] or_ln324_287_fu_3282_p2;
wire   [16:0] or_ln324_288_fu_3296_p2;
wire   [16:0] or_ln324_289_fu_3310_p2;
wire   [16:0] or_ln324_290_fu_3324_p2;
wire   [16:0] or_ln324_291_fu_3338_p2;
wire   [16:0] or_ln324_292_fu_3352_p2;
wire   [16:0] or_ln324_293_fu_3366_p2;
wire   [16:0] or_ln324_294_fu_3380_p2;
wire   [16:0] or_ln324_295_fu_3394_p2;
wire   [16:0] or_ln324_296_fu_3408_p2;
wire   [16:0] or_ln324_297_fu_3422_p2;
wire   [16:0] or_ln324_298_fu_3436_p2;
wire   [16:0] or_ln324_299_fu_3450_p2;
wire   [16:0] or_ln324_300_fu_3464_p2;
wire   [16:0] or_ln324_301_fu_3478_p2;
wire   [16:0] or_ln324_302_fu_3492_p2;
wire   [16:0] or_ln324_303_fu_3506_p2;
wire   [16:0] or_ln324_304_fu_3520_p2;
wire   [16:0] or_ln324_305_fu_3534_p2;
wire   [16:0] or_ln324_306_fu_3548_p2;
wire   [16:0] or_ln324_307_fu_3562_p2;
wire   [16:0] or_ln324_308_fu_3576_p2;
wire   [16:0] or_ln324_309_fu_3590_p2;
wire   [16:0] or_ln324_310_fu_3604_p2;
wire   [16:0] or_ln324_311_fu_3618_p2;
wire   [16:0] or_ln324_312_fu_3632_p2;
wire   [16:0] or_ln324_313_fu_3646_p2;
wire   [16:0] or_ln324_314_fu_3660_p2;
wire   [16:0] or_ln324_315_fu_3674_p2;
wire   [16:0] or_ln324_316_fu_3688_p2;
wire   [16:0] or_ln324_317_fu_3702_p2;
wire   [16:0] or_ln324_318_fu_3716_p2;
wire   [16:0] or_ln324_319_fu_3730_p2;
wire   [16:0] or_ln324_320_fu_3744_p2;
wire   [16:0] or_ln324_321_fu_3758_p2;
wire   [16:0] or_ln324_322_fu_3772_p2;
wire   [16:0] or_ln324_323_fu_3786_p2;
wire   [16:0] or_ln324_324_fu_3800_p2;
wire   [16:0] or_ln324_325_fu_3814_p2;
wire   [16:0] or_ln324_326_fu_3828_p2;
wire   [16:0] or_ln324_327_fu_3842_p2;
wire   [16:0] or_ln324_328_fu_3856_p2;
wire   [16:0] or_ln324_329_fu_3870_p2;
wire   [16:0] or_ln324_330_fu_3884_p2;
wire   [16:0] or_ln324_331_fu_3898_p2;
wire   [16:0] or_ln324_332_fu_3912_p2;
wire   [16:0] or_ln324_333_fu_3926_p2;
wire   [16:0] or_ln324_334_fu_3940_p2;
wire   [16:0] or_ln324_335_fu_3954_p2;
wire   [16:0] or_ln324_336_fu_3968_p2;
wire   [16:0] or_ln324_337_fu_3982_p2;
wire   [16:0] or_ln324_338_fu_3996_p2;
wire   [16:0] or_ln324_339_fu_4010_p2;
wire   [16:0] or_ln324_340_fu_4024_p2;
wire   [16:0] or_ln324_341_fu_4038_p2;
wire   [16:0] or_ln324_342_fu_4052_p2;
wire   [16:0] or_ln324_343_fu_4066_p2;
wire   [16:0] or_ln324_344_fu_4080_p2;
wire   [16:0] or_ln324_345_fu_4094_p2;
wire   [16:0] or_ln324_346_fu_4108_p2;
wire   [16:0] or_ln324_347_fu_4122_p2;
wire   [16:0] or_ln324_348_fu_4136_p2;
wire   [16:0] or_ln324_349_fu_4150_p2;
wire   [16:0] or_ln324_350_fu_4164_p2;
wire   [16:0] or_ln324_351_fu_4178_p2;
wire   [16:0] or_ln324_352_fu_4192_p2;
wire   [16:0] or_ln324_353_fu_4206_p2;
wire   [16:0] or_ln324_354_fu_4220_p2;
wire   [16:0] or_ln324_355_fu_4234_p2;
wire   [16:0] or_ln324_356_fu_4248_p2;
wire   [16:0] or_ln324_357_fu_4262_p2;
wire   [16:0] or_ln324_358_fu_4276_p2;
wire   [16:0] or_ln324_359_fu_4290_p2;
wire   [16:0] or_ln324_360_fu_4304_p2;
wire   [16:0] or_ln324_361_fu_4318_p2;
wire   [16:0] or_ln324_362_fu_4332_p2;
wire   [16:0] or_ln324_363_fu_4346_p2;
wire   [16:0] or_ln324_364_fu_4360_p2;
wire   [16:0] or_ln324_365_fu_4374_p2;
wire   [16:0] or_ln324_366_fu_4388_p2;
wire   [16:0] or_ln324_367_fu_4402_p2;
wire   [16:0] or_ln324_368_fu_4416_p2;
wire   [16:0] or_ln324_369_fu_4430_p2;
wire   [16:0] or_ln324_370_fu_4444_p2;
wire   [16:0] or_ln324_371_fu_4458_p2;
wire   [16:0] or_ln324_372_fu_4472_p2;
wire   [16:0] or_ln324_373_fu_4486_p2;
wire   [16:0] or_ln324_374_fu_4500_p2;
wire   [16:0] or_ln324_375_fu_4514_p2;
wire   [16:0] or_ln324_376_fu_4528_p2;
wire   [16:0] or_ln324_377_fu_4542_p2;
wire   [16:0] or_ln324_378_fu_4556_p2;
wire   [16:0] or_ln324_379_fu_4570_p2;
wire   [16:0] or_ln324_380_fu_4584_p2;
wire   [16:0] or_ln324_381_fu_4598_p2;
wire   [16:0] or_ln324_382_fu_4612_p2;
wire   [16:0] or_ln324_383_fu_4626_p2;
wire   [16:0] or_ln324_384_fu_4640_p2;
wire   [16:0] or_ln324_385_fu_4654_p2;
wire   [16:0] or_ln324_386_fu_4668_p2;
wire   [16:0] or_ln324_387_fu_4682_p2;
wire   [16:0] or_ln324_388_fu_4696_p2;
wire   [16:0] or_ln324_389_fu_4710_p2;
wire   [16:0] or_ln324_390_fu_4724_p2;
wire   [16:0] or_ln324_391_fu_4738_p2;
wire   [16:0] or_ln324_392_fu_4752_p2;
wire   [16:0] or_ln324_393_fu_4766_p2;
wire   [16:0] or_ln324_394_fu_4780_p2;
wire   [16:0] or_ln324_395_fu_4794_p2;
wire   [16:0] or_ln324_396_fu_4808_p2;
wire   [16:0] or_ln324_397_fu_4822_p2;
wire   [16:0] or_ln324_398_fu_4836_p2;
wire   [16:0] or_ln324_399_fu_4850_p2;
wire   [16:0] or_ln324_400_fu_4864_p2;
wire   [16:0] or_ln324_401_fu_4878_p2;
wire   [16:0] or_ln324_402_fu_4892_p2;
wire   [16:0] or_ln324_403_fu_4906_p2;
wire   [16:0] or_ln324_404_fu_4920_p2;
wire   [16:0] or_ln324_405_fu_4934_p2;
wire   [16:0] or_ln324_406_fu_4948_p2;
wire   [16:0] or_ln324_407_fu_4962_p2;
wire   [16:0] or_ln324_408_fu_4976_p2;
wire   [16:0] or_ln324_409_fu_4990_p2;
wire   [16:0] or_ln324_410_fu_5004_p2;
wire   [16:0] or_ln324_411_fu_5018_p2;
wire   [16:0] or_ln324_412_fu_5032_p2;
wire   [16:0] or_ln324_413_fu_5046_p2;
wire   [16:0] or_ln324_414_fu_5060_p2;
wire   [16:0] or_ln324_415_fu_5074_p2;
wire   [16:0] or_ln324_416_fu_5088_p2;
wire   [16:0] or_ln324_417_fu_5102_p2;
wire   [16:0] or_ln324_418_fu_5116_p2;
wire   [16:0] or_ln324_419_fu_5130_p2;
wire   [16:0] or_ln324_420_fu_5144_p2;
wire   [16:0] or_ln324_421_fu_5158_p2;
wire   [16:0] or_ln324_422_fu_5172_p2;
wire   [16:0] or_ln324_423_fu_5186_p2;
wire   [16:0] or_ln324_424_fu_5200_p2;
wire   [16:0] or_ln324_425_fu_5214_p2;
wire   [16:0] or_ln324_426_fu_5228_p2;
wire   [16:0] or_ln324_427_fu_5242_p2;
wire   [16:0] or_ln324_428_fu_5256_p2;
wire   [16:0] or_ln324_429_fu_5270_p2;
wire   [16:0] or_ln324_430_fu_5284_p2;
wire   [16:0] or_ln324_431_fu_5298_p2;
wire   [16:0] or_ln324_432_fu_5312_p2;
wire   [16:0] or_ln324_433_fu_5326_p2;
wire   [16:0] or_ln324_434_fu_5340_p2;
wire   [16:0] or_ln324_435_fu_5354_p2;
wire   [16:0] or_ln324_436_fu_5368_p2;
wire   [16:0] or_ln324_437_fu_5382_p2;
wire   [16:0] or_ln324_438_fu_5396_p2;
wire   [16:0] or_ln324_439_fu_5410_p2;
wire   [16:0] or_ln324_440_fu_5424_p2;
wire   [16:0] or_ln324_441_fu_5438_p2;
wire   [16:0] or_ln324_442_fu_5452_p2;
wire   [16:0] or_ln324_443_fu_5466_p2;
wire   [16:0] or_ln324_444_fu_5480_p2;
wire   [16:0] or_ln324_445_fu_5494_p2;
wire   [16:0] or_ln324_446_fu_5508_p2;
wire   [16:0] or_ln324_447_fu_5522_p2;
wire   [16:0] or_ln324_448_fu_5536_p2;
wire   [16:0] or_ln324_449_fu_5550_p2;
wire   [16:0] or_ln324_450_fu_5564_p2;
wire   [16:0] or_ln324_451_fu_5578_p2;
wire   [16:0] or_ln324_452_fu_5592_p2;
wire   [16:0] or_ln324_453_fu_5606_p2;
wire   [16:0] or_ln324_454_fu_5620_p2;
wire   [16:0] or_ln324_455_fu_5634_p2;
wire   [16:0] or_ln324_456_fu_5648_p2;
wire   [16:0] or_ln324_457_fu_5662_p2;
wire   [16:0] or_ln324_458_fu_5676_p2;
wire   [16:0] or_ln324_459_fu_5690_p2;
wire   [16:0] or_ln324_460_fu_5704_p2;
wire   [16:0] or_ln324_461_fu_5718_p2;
wire   [16:0] or_ln324_462_fu_5732_p2;
wire   [16:0] or_ln324_463_fu_5746_p2;
wire   [16:0] or_ln324_464_fu_5760_p2;
wire   [16:0] or_ln324_465_fu_5774_p2;
wire   [16:0] or_ln324_466_fu_5788_p2;
wire   [16:0] or_ln324_467_fu_5802_p2;
wire   [16:0] or_ln324_468_fu_5816_p2;
wire   [16:0] or_ln324_469_fu_5830_p2;
wire   [16:0] or_ln324_470_fu_5844_p2;
wire   [16:0] or_ln324_471_fu_5858_p2;
wire   [16:0] or_ln324_472_fu_5872_p2;
wire   [16:0] or_ln324_473_fu_5886_p2;
wire   [16:0] or_ln324_474_fu_5900_p2;
wire   [16:0] or_ln324_475_fu_5914_p2;
wire   [16:0] or_ln324_476_fu_5928_p2;
wire   [16:0] or_ln324_477_fu_5942_p2;
wire   [16:0] or_ln324_478_fu_5956_p2;
wire   [16:0] or_ln324_479_fu_5970_p2;
wire   [16:0] or_ln324_480_fu_5984_p2;
wire   [16:0] or_ln324_481_fu_5998_p2;
wire   [16:0] or_ln324_482_fu_6012_p2;
wire   [16:0] or_ln324_483_fu_6026_p2;
wire   [16:0] or_ln324_484_fu_6040_p2;
wire   [16:0] or_ln324_485_fu_6054_p2;
wire   [16:0] or_ln324_486_fu_6068_p2;
wire   [16:0] or_ln324_487_fu_6082_p2;
wire   [16:0] or_ln324_488_fu_6096_p2;
wire   [16:0] or_ln324_489_fu_6110_p2;
wire   [16:0] or_ln324_490_fu_6124_p2;
wire   [16:0] or_ln324_491_fu_6138_p2;
wire   [16:0] or_ln324_492_fu_6152_p2;
wire   [16:0] or_ln324_493_fu_6166_p2;
wire   [16:0] or_ln324_494_fu_6180_p2;
wire   [16:0] or_ln324_495_fu_6194_p2;
wire   [16:0] or_ln324_496_fu_6208_p2;
wire   [16:0] or_ln324_497_fu_6222_p2;
wire   [16:0] or_ln324_498_fu_6236_p2;
wire   [16:0] or_ln324_499_fu_6250_p2;
wire   [16:0] or_ln324_500_fu_6264_p2;
wire   [16:0] or_ln324_501_fu_6278_p2;
wire   [16:0] or_ln324_502_fu_6292_p2;
wire   [16:0] or_ln324_503_fu_6306_p2;
wire   [16:0] or_ln324_504_fu_6320_p2;
wire   [16:0] or_ln324_505_fu_6334_p2;
wire   [16:0] or_ln324_506_fu_6348_p2;
wire   [16:0] or_ln324_507_fu_6362_p2;
wire   [16:0] or_ln324_508_fu_6376_p2;
wire   [7:0] trunc_ln324_fu_6425_p1;
wire   [7:0] p_Result_s_fu_6404_p4;
wire   [15:0] tmp_509_fu_6429_p3;
wire   [0:0] tmp_5_fu_6471_p3;
wire   [8:0] add_ln527_fu_6465_p2;
wire   [7:0] or_ln531_fu_6503_p2;
wire   [16:0] tmp_510_fu_6509_p3;
wire   [7:0] or_ln531_1_fu_6522_p2;
wire   [16:0] tmp_511_fu_6528_p3;
wire   [15:0] zext_ln215_fu_6548_p1;
wire   [15:0] tmp_514_cast_fu_6541_p3;
wire   [15:0] add_ln215_fu_6551_p2;
wire   [7:0] or_ln531_2_fu_6562_p2;
wire   [16:0] tmp_512_fu_6567_p3;
reg   [135:0] ap_NS_fsm;
reg    ap_idle_pp1;
wire    ap_enable_pp1;
reg    ap_idle_pp2;
wire    ap_enable_pp2;
wire   [31:0] Output_1_V_TDATA_int_regslice;
reg    Output_1_V_TVALID_int_regslice;
wire    Output_1_V_TREADY_int_regslice;
wire    regslice_both_Output_1_V_U_vld_out;

// power-on initialization
initial begin
#0 ap_CS_fsm = 136'd1;
#0 counter_1 = 16'd0;
#0 ap_enable_reg_pp1_iter1 = 1'b0;
#0 ap_enable_reg_pp2_iter1 = 1'b0;
#0 ap_enable_reg_pp1_iter0 = 1'b0;
#0 ap_enable_reg_pp2_iter0 = 1'b0;
end

rendering_m_coloringFB_bot_m_frame_buffer_V #(
    .DataWidth( 8 ),
    .AddressRange( 65536 ),
    .AddressWidth( 16 ))
frame_buffer_V_U(
    .clk(ap_clk),
    .reset(ap_rst),
    .address0(frame_buffer_V_address0),
    .ce0(frame_buffer_V_ce0),
    .we0(frame_buffer_V_we0),
    .d0(frame_buffer_V_d0),
    .q0(frame_buffer_V_q0),
    .address1(frame_buffer_V_address1),
    .ce1(frame_buffer_V_ce1),
    .we1(frame_buffer_V_we1),
    .d1(8'd0),
    .q1(frame_buffer_V_q1)
);

regslice_both #(
    .DataWidth( 32 ))
regslice_both_Output_1_V_U(
    .ap_clk(ap_clk),
    .ap_rst(ap_rst),
    .data_in(Output_1_V_TDATA_int_regslice),
    .vld_in(Output_1_V_TVALID_int_regslice),
    .ack_in(Output_1_V_TREADY_int_regslice),
    .data_out(Output_1_V_TDATA),
    .vld_out(regslice_both_Output_1_V_U_vld_out),
    .ack_out(Output_1_V_TREADY),
    .apdone_blk(regslice_both_Output_1_V_U_apdone_blk)
);

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_CS_fsm <= ap_ST_fsm_state1;
    end else begin
        ap_CS_fsm <= ap_NS_fsm;
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp1_iter0 <= 1'b0;
    end else begin
        if (((1'b1 == ap_condition_pp1_exit_iter0_state131) & (1'b1 == ap_CS_fsm_pp1_stage0) & (1'b0 == ap_block_pp1_stage0_subdone))) begin
            ap_enable_reg_pp1_iter0 <= 1'b0;
        end else if ((1'b1 == ap_CS_fsm_state130)) begin
            ap_enable_reg_pp1_iter0 <= 1'b1;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp1_iter1 <= 1'b0;
    end else begin
        if (((1'b1 == ap_condition_pp1_exit_iter0_state131) & (1'b0 == ap_block_pp1_stage0_subdone))) begin
            ap_enable_reg_pp1_iter1 <= (1'b1 ^ ap_condition_pp1_exit_iter0_state131);
        end else if ((1'b0 == ap_block_pp1_stage0_subdone)) begin
            ap_enable_reg_pp1_iter1 <= ap_enable_reg_pp1_iter0;
        end else if ((1'b1 == ap_CS_fsm_state130)) begin
            ap_enable_reg_pp1_iter1 <= 1'b0;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp2_iter0 <= 1'b0;
    end else begin
        if (((1'b1 == ap_condition_pp2_exit_iter0_state134) & (1'b1 == ap_CS_fsm_pp2_stage0) & (1'b0 == ap_block_pp2_stage0_subdone))) begin
            ap_enable_reg_pp2_iter0 <= 1'b0;
        end else if (((icmp_ln874_2_fu_6447_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state133))) begin
            ap_enable_reg_pp2_iter0 <= 1'b1;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp2_iter1 <= 1'b0;
    end else begin
        if (((1'b1 == ap_CS_fsm_pp2_stage1) & (1'b0 == ap_block_pp2_stage1_subdone))) begin
            ap_enable_reg_pp2_iter1 <= ap_enable_reg_pp2_iter0;
        end else if (((icmp_ln874_2_fu_6447_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state133))) begin
            ap_enable_reg_pp2_iter1 <= 1'b0;
        end
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state138)) begin
        counter_1_new_0_reg_2773 <= 16'd0;
    end else if (((icmp_ln874_2_fu_6447_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state133))) begin
        counter_1_new_0_reg_2773 <= add_ln695_6_fu_6442_p2;
    end
end

always @ (posedge ap_clk) begin
    if (((ap_enable_reg_pp1_iter0 == 1'b1) & (icmp_ln515_fu_6393_p2 == 1'd0) & (1'b1 == ap_CS_fsm_pp1_stage0) & (1'b0 == ap_block_pp1_stage0_11001))) begin
        empty_28_reg_2729 <= add_ln695_7_fu_6398_p2;
    end else if ((1'b1 == ap_CS_fsm_state130)) begin
        empty_28_reg_2729 <= 16'd0;
    end
end

always @ (posedge ap_clk) begin
    if ((~((1'b0 == Input_1_empty_n) | (ap_start == 1'b0)) & (icmp_ln874_fu_2788_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state1))) begin
        empty_reg_2718 <= 9'd0;
    end else if ((1'b1 == ap_CS_fsm_state129)) begin
        empty_reg_2718 <= add_ln695_reg_6618;
    end
end

always @ (posedge ap_clk) begin
    if (((icmp_ln874_2_fu_6447_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state133))) begin
        i_reg_2751 <= 9'd0;
    end else if (((icmp_ln527_reg_6904 == 1'd0) & (ap_enable_reg_pp2_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp2_stage0) & (1'b0 == ap_block_pp2_stage0_11001))) begin
        i_reg_2751 <= select_ln527_1_reg_6919;
    end
end

always @ (posedge ap_clk) begin
    if (((icmp_ln874_2_fu_6447_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state133))) begin
        indvar_flatten_reg_2740 <= 15'd0;
    end else if (((icmp_ln527_reg_6904 == 1'd0) & (ap_enable_reg_pp2_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp2_stage0) & (1'b0 == ap_block_pp2_stage0_11001))) begin
        indvar_flatten_reg_2740 <= add_ln527_1_reg_6908;
    end
end

always @ (posedge ap_clk) begin
    if (((icmp_ln874_2_fu_6447_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state133))) begin
        j_reg_2762 <= 9'd0;
    end else if (((icmp_ln527_reg_6904 == 1'd0) & (ap_enable_reg_pp2_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp2_stage0) & (1'b0 == ap_block_pp2_stage0_11001))) begin
        j_reg_2762 <= add_ln528_reg_6965;
    end
end

always @ (posedge ap_clk) begin
    if (((ap_enable_reg_pp2_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp2_stage0) & (1'b0 == ap_block_pp2_stage0_11001))) begin
        add_ln527_1_reg_6908 <= add_ln527_1_fu_6459_p2;
    end
end

always @ (posedge ap_clk) begin
    if (((ap_enable_reg_pp2_iter0 == 1'b1) & (icmp_ln527_reg_6904 == 1'd0) & (1'b1 == ap_CS_fsm_pp2_stage1) & (1'b0 == ap_block_pp2_stage1_11001))) begin
        add_ln528_reg_6965 <= add_ln528_fu_6579_p2;
        frame_buffer_V_load_1_reg_6950 <= frame_buffer_V_q0;
        frame_buffer_V_load_2_reg_6955 <= frame_buffer_V_q1;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state2)) begin
        add_ln695_reg_6618 <= add_ln695_fu_2800_p2;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == ap_CS_fsm_state139) & (regslice_both_Output_1_V_U_apdone_blk == 1'b0))) begin
        counter_1 <= counter_1_new_0_reg_2773;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state130)) begin
        empty_27_reg_6881 <= empty_27_fu_6390_p1;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == ap_CS_fsm_pp1_stage0) & (1'b0 == ap_block_pp1_stage0_11001))) begin
        icmp_ln515_reg_6886 <= icmp_ln515_fu_6393_p2;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == ap_CS_fsm_pp2_stage0) & (1'b0 == ap_block_pp2_stage0_11001))) begin
        icmp_ln527_reg_6904 <= icmp_ln527_fu_6453_p2;
        icmp_ln527_reg_6904_pp2_iter1_reg <= icmp_ln527_reg_6904;
    end
end

always @ (posedge ap_clk) begin
    if (((ap_enable_reg_pp2_iter0 == 1'b1) & (icmp_ln527_fu_6453_p2 == 1'd0) & (1'b1 == ap_CS_fsm_pp2_stage0) & (1'b0 == ap_block_pp2_stage0_11001))) begin
        select_ln527_1_reg_6919 <= select_ln527_1_fu_6487_p3;
    end
end

always @ (posedge ap_clk) begin
    if (((icmp_ln527_fu_6453_p2 == 1'd0) & (1'b1 == ap_CS_fsm_pp2_stage0) & (1'b0 == ap_block_pp2_stage0_11001))) begin
        select_ln527_reg_6913 <= select_ln527_fu_6479_p3;
        trunc_ln215_reg_6925 <= trunc_ln215_fu_6495_p1;
        trunc_ln528_reg_6930 <= trunc_ln528_fu_6499_p1;
    end
end

always @ (posedge ap_clk) begin
    if ((~((1'b0 == Input_1_empty_n) | (ap_start == 1'b0)) & (1'b1 == ap_CS_fsm_state1))) begin
        t_V_reg_6606 <= counter_1;
        tmp_V_reg_6601 <= Input_1_dout;
    end
end

always @ (posedge ap_clk) begin
    if (((icmp_ln882_fu_2794_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state2))) begin
        tmp_reg_6623[16 : 8] <= tmp_fu_2806_p3[16 : 8];
    end
end

always @ (*) begin
    if ((((1'b1 == ap_CS_fsm_pp1_stage0) & (icmp_ln515_reg_6886 == 1'd0) & (1'b0 == ap_block_pp1_stage0) & (ap_enable_reg_pp1_iter1 == 1'b1)) | ((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b1)))) begin
        Input_1_blk_n = Input_1_empty_n;
    end else begin
        Input_1_blk_n = 1'b1;
    end
end

always @ (*) begin
    if (((~((1'b0 == Input_1_empty_n) | (ap_start == 1'b0)) & (1'b1 == ap_CS_fsm_state1)) | ((1'b1 == ap_CS_fsm_pp1_stage0) & (icmp_ln515_reg_6886 == 1'd0) & (1'b0 == ap_block_pp1_stage0_11001) & (ap_enable_reg_pp1_iter1 == 1'b1)))) begin
        Input_1_read = 1'b1;
    end else begin
        Input_1_read = 1'b0;
    end
end

always @ (*) begin
    if ((((icmp_ln527_reg_6904_pp2_iter1_reg == 1'd0) & (ap_enable_reg_pp2_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp2_stage1) & (1'b0 == ap_block_pp2_stage1)) | ((icmp_ln527_reg_6904 == 1'd0) & (ap_enable_reg_pp2_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp2_stage0) & (1'b0 == ap_block_pp2_stage0)))) begin
        Output_1_V_TDATA_blk_n = Output_1_V_TREADY_int_regslice;
    end else begin
        Output_1_V_TDATA_blk_n = 1'b1;
    end
end

always @ (*) begin
    if (((icmp_ln527_reg_6904 == 1'd0) & (ap_enable_reg_pp2_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp2_stage0) & (1'b0 == ap_block_pp2_stage0_11001))) begin
        Output_1_V_TVALID_int_regslice = 1'b1;
    end else begin
        Output_1_V_TVALID_int_regslice = 1'b0;
    end
end

always @ (*) begin
    if ((icmp_ln515_fu_6393_p2 == 1'd1)) begin
        ap_condition_pp1_exit_iter0_state131 = 1'b1;
    end else begin
        ap_condition_pp1_exit_iter0_state131 = 1'b0;
    end
end

always @ (*) begin
    if ((icmp_ln527_fu_6453_p2 == 1'd1)) begin
        ap_condition_pp2_exit_iter0_state134 = 1'b1;
    end else begin
        ap_condition_pp2_exit_iter0_state134 = 1'b0;
    end
end

always @ (*) begin
    if ((((1'b1 == ap_CS_fsm_state139) & (regslice_both_Output_1_V_U_apdone_blk == 1'b0)) | ((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b0)))) begin
        ap_done = 1'b1;
    end else begin
        ap_done = 1'b0;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b0))) begin
        ap_idle = 1'b1;
    end else begin
        ap_idle = 1'b0;
    end
end

always @ (*) begin
    if (((ap_enable_reg_pp1_iter0 == 1'b0) & (ap_enable_reg_pp1_iter1 == 1'b0))) begin
        ap_idle_pp1 = 1'b1;
    end else begin
        ap_idle_pp1 = 1'b0;
    end
end

always @ (*) begin
    if (((ap_enable_reg_pp2_iter0 == 1'b0) & (ap_enable_reg_pp2_iter1 == 1'b0))) begin
        ap_idle_pp2 = 1'b1;
    end else begin
        ap_idle_pp2 = 1'b0;
    end
end

always @ (*) begin
    if (((icmp_ln527_reg_6904 == 1'd0) & (ap_enable_reg_pp2_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp2_stage0) & (1'b0 == ap_block_pp2_stage0))) begin
        ap_phi_mux_i_phi_fu_2755_p4 = select_ln527_1_reg_6919;
    end else begin
        ap_phi_mux_i_phi_fu_2755_p4 = i_reg_2751;
    end
end

always @ (*) begin
    if (((icmp_ln527_reg_6904 == 1'd0) & (ap_enable_reg_pp2_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp2_stage0) & (1'b0 == ap_block_pp2_stage0))) begin
        ap_phi_mux_indvar_flatten_phi_fu_2744_p4 = add_ln527_1_reg_6908;
    end else begin
        ap_phi_mux_indvar_flatten_phi_fu_2744_p4 = indvar_flatten_reg_2740;
    end
end

always @ (*) begin
    if (((icmp_ln527_reg_6904 == 1'd0) & (ap_enable_reg_pp2_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp2_stage0) & (1'b0 == ap_block_pp2_stage0))) begin
        ap_phi_mux_j_phi_fu_2766_p4 = add_ln528_reg_6965;
    end else begin
        ap_phi_mux_j_phi_fu_2766_p4 = j_reg_2762;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state139) & (regslice_both_Output_1_V_U_apdone_blk == 1'b0))) begin
        ap_ready = 1'b1;
    end else begin
        ap_ready = 1'b0;
    end
end

always @ (*) begin
    if (((ap_enable_reg_pp2_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp2_stage1) & (1'b0 == ap_block_pp2_stage1))) begin
        frame_buffer_V_address0 = zext_ln215_9_fu_6557_p1;
    end else if (((ap_enable_reg_pp2_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp2_stage0) & (1'b0 == ap_block_pp2_stage0))) begin
        frame_buffer_V_address0 = zext_ln215_6_fu_6517_p1;
    end else if (((1'b1 == ap_CS_fsm_pp1_stage0) & (1'b0 == ap_block_pp1_stage0) & (ap_enable_reg_pp1_iter1 == 1'b1))) begin
        frame_buffer_V_address0 = zext_ln324_1_fu_6437_p1;
    end else if ((1'b1 == ap_CS_fsm_state129)) begin
        frame_buffer_V_address0 = tmp_508_fu_6381_p3;
    end else if ((1'b1 == ap_CS_fsm_state128)) begin
        frame_buffer_V_address0 = tmp_506_fu_6353_p3;
    end else if ((1'b1 == ap_CS_fsm_state127)) begin
        frame_buffer_V_address0 = tmp_504_fu_6325_p3;
    end else if ((1'b1 == ap_CS_fsm_state126)) begin
        frame_buffer_V_address0 = tmp_502_fu_6297_p3;
    end else if ((1'b1 == ap_CS_fsm_state125)) begin
        frame_buffer_V_address0 = tmp_500_fu_6269_p3;
    end else if ((1'b1 == ap_CS_fsm_state124)) begin
        frame_buffer_V_address0 = tmp_498_fu_6241_p3;
    end else if ((1'b1 == ap_CS_fsm_state123)) begin
        frame_buffer_V_address0 = tmp_496_fu_6213_p3;
    end else if ((1'b1 == ap_CS_fsm_state122)) begin
        frame_buffer_V_address0 = tmp_494_fu_6185_p3;
    end else if ((1'b1 == ap_CS_fsm_state121)) begin
        frame_buffer_V_address0 = tmp_492_fu_6157_p3;
    end else if ((1'b1 == ap_CS_fsm_state120)) begin
        frame_buffer_V_address0 = tmp_490_fu_6129_p3;
    end else if ((1'b1 == ap_CS_fsm_state119)) begin
        frame_buffer_V_address0 = tmp_488_fu_6101_p3;
    end else if ((1'b1 == ap_CS_fsm_state118)) begin
        frame_buffer_V_address0 = tmp_486_fu_6073_p3;
    end else if ((1'b1 == ap_CS_fsm_state117)) begin
        frame_buffer_V_address0 = tmp_484_fu_6045_p3;
    end else if ((1'b1 == ap_CS_fsm_state116)) begin
        frame_buffer_V_address0 = tmp_482_fu_6017_p3;
    end else if ((1'b1 == ap_CS_fsm_state115)) begin
        frame_buffer_V_address0 = tmp_480_fu_5989_p3;
    end else if ((1'b1 == ap_CS_fsm_state114)) begin
        frame_buffer_V_address0 = tmp_478_fu_5961_p3;
    end else if ((1'b1 == ap_CS_fsm_state113)) begin
        frame_buffer_V_address0 = tmp_476_fu_5933_p3;
    end else if ((1'b1 == ap_CS_fsm_state112)) begin
        frame_buffer_V_address0 = tmp_474_fu_5905_p3;
    end else if ((1'b1 == ap_CS_fsm_state111)) begin
        frame_buffer_V_address0 = tmp_472_fu_5877_p3;
    end else if ((1'b1 == ap_CS_fsm_state110)) begin
        frame_buffer_V_address0 = tmp_470_fu_5849_p3;
    end else if ((1'b1 == ap_CS_fsm_state109)) begin
        frame_buffer_V_address0 = tmp_468_fu_5821_p3;
    end else if ((1'b1 == ap_CS_fsm_state108)) begin
        frame_buffer_V_address0 = tmp_466_fu_5793_p3;
    end else if ((1'b1 == ap_CS_fsm_state107)) begin
        frame_buffer_V_address0 = tmp_464_fu_5765_p3;
    end else if ((1'b1 == ap_CS_fsm_state106)) begin
        frame_buffer_V_address0 = tmp_462_fu_5737_p3;
    end else if ((1'b1 == ap_CS_fsm_state105)) begin
        frame_buffer_V_address0 = tmp_460_fu_5709_p3;
    end else if ((1'b1 == ap_CS_fsm_state104)) begin
        frame_buffer_V_address0 = tmp_458_fu_5681_p3;
    end else if ((1'b1 == ap_CS_fsm_state103)) begin
        frame_buffer_V_address0 = tmp_456_fu_5653_p3;
    end else if ((1'b1 == ap_CS_fsm_state102)) begin
        frame_buffer_V_address0 = tmp_454_fu_5625_p3;
    end else if ((1'b1 == ap_CS_fsm_state101)) begin
        frame_buffer_V_address0 = tmp_452_fu_5597_p3;
    end else if ((1'b1 == ap_CS_fsm_state100)) begin
        frame_buffer_V_address0 = tmp_450_fu_5569_p3;
    end else if ((1'b1 == ap_CS_fsm_state99)) begin
        frame_buffer_V_address0 = tmp_448_fu_5541_p3;
    end else if ((1'b1 == ap_CS_fsm_state98)) begin
        frame_buffer_V_address0 = tmp_446_fu_5513_p3;
    end else if ((1'b1 == ap_CS_fsm_state97)) begin
        frame_buffer_V_address0 = tmp_444_fu_5485_p3;
    end else if ((1'b1 == ap_CS_fsm_state96)) begin
        frame_buffer_V_address0 = tmp_442_fu_5457_p3;
    end else if ((1'b1 == ap_CS_fsm_state95)) begin
        frame_buffer_V_address0 = tmp_440_fu_5429_p3;
    end else if ((1'b1 == ap_CS_fsm_state94)) begin
        frame_buffer_V_address0 = tmp_438_fu_5401_p3;
    end else if ((1'b1 == ap_CS_fsm_state93)) begin
        frame_buffer_V_address0 = tmp_436_fu_5373_p3;
    end else if ((1'b1 == ap_CS_fsm_state92)) begin
        frame_buffer_V_address0 = tmp_434_fu_5345_p3;
    end else if ((1'b1 == ap_CS_fsm_state91)) begin
        frame_buffer_V_address0 = tmp_432_fu_5317_p3;
    end else if ((1'b1 == ap_CS_fsm_state90)) begin
        frame_buffer_V_address0 = tmp_430_fu_5289_p3;
    end else if ((1'b1 == ap_CS_fsm_state89)) begin
        frame_buffer_V_address0 = tmp_428_fu_5261_p3;
    end else if ((1'b1 == ap_CS_fsm_state88)) begin
        frame_buffer_V_address0 = tmp_426_fu_5233_p3;
    end else if ((1'b1 == ap_CS_fsm_state87)) begin
        frame_buffer_V_address0 = tmp_424_fu_5205_p3;
    end else if ((1'b1 == ap_CS_fsm_state86)) begin
        frame_buffer_V_address0 = tmp_422_fu_5177_p3;
    end else if ((1'b1 == ap_CS_fsm_state85)) begin
        frame_buffer_V_address0 = tmp_420_fu_5149_p3;
    end else if ((1'b1 == ap_CS_fsm_state84)) begin
        frame_buffer_V_address0 = tmp_418_fu_5121_p3;
    end else if ((1'b1 == ap_CS_fsm_state83)) begin
        frame_buffer_V_address0 = tmp_416_fu_5093_p3;
    end else if ((1'b1 == ap_CS_fsm_state82)) begin
        frame_buffer_V_address0 = tmp_414_fu_5065_p3;
    end else if ((1'b1 == ap_CS_fsm_state81)) begin
        frame_buffer_V_address0 = tmp_412_fu_5037_p3;
    end else if ((1'b1 == ap_CS_fsm_state80)) begin
        frame_buffer_V_address0 = tmp_410_fu_5009_p3;
    end else if ((1'b1 == ap_CS_fsm_state79)) begin
        frame_buffer_V_address0 = tmp_408_fu_4981_p3;
    end else if ((1'b1 == ap_CS_fsm_state78)) begin
        frame_buffer_V_address0 = tmp_406_fu_4953_p3;
    end else if ((1'b1 == ap_CS_fsm_state77)) begin
        frame_buffer_V_address0 = tmp_404_fu_4925_p3;
    end else if ((1'b1 == ap_CS_fsm_state76)) begin
        frame_buffer_V_address0 = tmp_402_fu_4897_p3;
    end else if ((1'b1 == ap_CS_fsm_state75)) begin
        frame_buffer_V_address0 = tmp_400_fu_4869_p3;
    end else if ((1'b1 == ap_CS_fsm_state74)) begin
        frame_buffer_V_address0 = tmp_398_fu_4841_p3;
    end else if ((1'b1 == ap_CS_fsm_state73)) begin
        frame_buffer_V_address0 = tmp_396_fu_4813_p3;
    end else if ((1'b1 == ap_CS_fsm_state72)) begin
        frame_buffer_V_address0 = tmp_394_fu_4785_p3;
    end else if ((1'b1 == ap_CS_fsm_state71)) begin
        frame_buffer_V_address0 = tmp_392_fu_4757_p3;
    end else if ((1'b1 == ap_CS_fsm_state70)) begin
        frame_buffer_V_address0 = tmp_390_fu_4729_p3;
    end else if ((1'b1 == ap_CS_fsm_state69)) begin
        frame_buffer_V_address0 = tmp_388_fu_4701_p3;
    end else if ((1'b1 == ap_CS_fsm_state68)) begin
        frame_buffer_V_address0 = tmp_386_fu_4673_p3;
    end else if ((1'b1 == ap_CS_fsm_state67)) begin
        frame_buffer_V_address0 = tmp_384_fu_4645_p3;
    end else if ((1'b1 == ap_CS_fsm_state66)) begin
        frame_buffer_V_address0 = tmp_382_fu_4617_p3;
    end else if ((1'b1 == ap_CS_fsm_state65)) begin
        frame_buffer_V_address0 = tmp_380_fu_4589_p3;
    end else if ((1'b1 == ap_CS_fsm_state64)) begin
        frame_buffer_V_address0 = tmp_378_fu_4561_p3;
    end else if ((1'b1 == ap_CS_fsm_state63)) begin
        frame_buffer_V_address0 = tmp_376_fu_4533_p3;
    end else if ((1'b1 == ap_CS_fsm_state62)) begin
        frame_buffer_V_address0 = tmp_374_fu_4505_p3;
    end else if ((1'b1 == ap_CS_fsm_state61)) begin
        frame_buffer_V_address0 = tmp_372_fu_4477_p3;
    end else if ((1'b1 == ap_CS_fsm_state60)) begin
        frame_buffer_V_address0 = tmp_370_fu_4449_p3;
    end else if ((1'b1 == ap_CS_fsm_state59)) begin
        frame_buffer_V_address0 = tmp_368_fu_4421_p3;
    end else if ((1'b1 == ap_CS_fsm_state58)) begin
        frame_buffer_V_address0 = tmp_366_fu_4393_p3;
    end else if ((1'b1 == ap_CS_fsm_state57)) begin
        frame_buffer_V_address0 = tmp_364_fu_4365_p3;
    end else if ((1'b1 == ap_CS_fsm_state56)) begin
        frame_buffer_V_address0 = tmp_362_fu_4337_p3;
    end else if ((1'b1 == ap_CS_fsm_state55)) begin
        frame_buffer_V_address0 = tmp_360_fu_4309_p3;
    end else if ((1'b1 == ap_CS_fsm_state54)) begin
        frame_buffer_V_address0 = tmp_358_fu_4281_p3;
    end else if ((1'b1 == ap_CS_fsm_state53)) begin
        frame_buffer_V_address0 = tmp_356_fu_4253_p3;
    end else if ((1'b1 == ap_CS_fsm_state52)) begin
        frame_buffer_V_address0 = tmp_354_fu_4225_p3;
    end else if ((1'b1 == ap_CS_fsm_state51)) begin
        frame_buffer_V_address0 = tmp_352_fu_4197_p3;
    end else if ((1'b1 == ap_CS_fsm_state50)) begin
        frame_buffer_V_address0 = tmp_350_fu_4169_p3;
    end else if ((1'b1 == ap_CS_fsm_state49)) begin
        frame_buffer_V_address0 = tmp_348_fu_4141_p3;
    end else if ((1'b1 == ap_CS_fsm_state48)) begin
        frame_buffer_V_address0 = tmp_346_fu_4113_p3;
    end else if ((1'b1 == ap_CS_fsm_state47)) begin
        frame_buffer_V_address0 = tmp_344_fu_4085_p3;
    end else if ((1'b1 == ap_CS_fsm_state46)) begin
        frame_buffer_V_address0 = tmp_342_fu_4057_p3;
    end else if ((1'b1 == ap_CS_fsm_state45)) begin
        frame_buffer_V_address0 = tmp_340_fu_4029_p3;
    end else if ((1'b1 == ap_CS_fsm_state44)) begin
        frame_buffer_V_address0 = tmp_338_fu_4001_p3;
    end else if ((1'b1 == ap_CS_fsm_state43)) begin
        frame_buffer_V_address0 = tmp_336_fu_3973_p3;
    end else if ((1'b1 == ap_CS_fsm_state42)) begin
        frame_buffer_V_address0 = tmp_334_fu_3945_p3;
    end else if ((1'b1 == ap_CS_fsm_state41)) begin
        frame_buffer_V_address0 = tmp_332_fu_3917_p3;
    end else if ((1'b1 == ap_CS_fsm_state40)) begin
        frame_buffer_V_address0 = tmp_330_fu_3889_p3;
    end else if ((1'b1 == ap_CS_fsm_state39)) begin
        frame_buffer_V_address0 = tmp_328_fu_3861_p3;
    end else if ((1'b1 == ap_CS_fsm_state38)) begin
        frame_buffer_V_address0 = tmp_326_fu_3833_p3;
    end else if ((1'b1 == ap_CS_fsm_state37)) begin
        frame_buffer_V_address0 = tmp_324_fu_3805_p3;
    end else if ((1'b1 == ap_CS_fsm_state36)) begin
        frame_buffer_V_address0 = tmp_322_fu_3777_p3;
    end else if ((1'b1 == ap_CS_fsm_state35)) begin
        frame_buffer_V_address0 = tmp_320_fu_3749_p3;
    end else if ((1'b1 == ap_CS_fsm_state34)) begin
        frame_buffer_V_address0 = tmp_318_fu_3721_p3;
    end else if ((1'b1 == ap_CS_fsm_state33)) begin
        frame_buffer_V_address0 = tmp_316_fu_3693_p3;
    end else if ((1'b1 == ap_CS_fsm_state32)) begin
        frame_buffer_V_address0 = tmp_314_fu_3665_p3;
    end else if ((1'b1 == ap_CS_fsm_state31)) begin
        frame_buffer_V_address0 = tmp_312_fu_3637_p3;
    end else if ((1'b1 == ap_CS_fsm_state30)) begin
        frame_buffer_V_address0 = tmp_310_fu_3609_p3;
    end else if ((1'b1 == ap_CS_fsm_state29)) begin
        frame_buffer_V_address0 = tmp_308_fu_3581_p3;
    end else if ((1'b1 == ap_CS_fsm_state28)) begin
        frame_buffer_V_address0 = tmp_306_fu_3553_p3;
    end else if ((1'b1 == ap_CS_fsm_state27)) begin
        frame_buffer_V_address0 = tmp_304_fu_3525_p3;
    end else if ((1'b1 == ap_CS_fsm_state26)) begin
        frame_buffer_V_address0 = tmp_302_fu_3497_p3;
    end else if ((1'b1 == ap_CS_fsm_state25)) begin
        frame_buffer_V_address0 = tmp_300_fu_3469_p3;
    end else if ((1'b1 == ap_CS_fsm_state24)) begin
        frame_buffer_V_address0 = tmp_298_fu_3441_p3;
    end else if ((1'b1 == ap_CS_fsm_state23)) begin
        frame_buffer_V_address0 = tmp_296_fu_3413_p3;
    end else if ((1'b1 == ap_CS_fsm_state22)) begin
        frame_buffer_V_address0 = tmp_294_fu_3385_p3;
    end else if ((1'b1 == ap_CS_fsm_state21)) begin
        frame_buffer_V_address0 = tmp_292_fu_3357_p3;
    end else if ((1'b1 == ap_CS_fsm_state20)) begin
        frame_buffer_V_address0 = tmp_290_fu_3329_p3;
    end else if ((1'b1 == ap_CS_fsm_state19)) begin
        frame_buffer_V_address0 = tmp_288_fu_3301_p3;
    end else if ((1'b1 == ap_CS_fsm_state18)) begin
        frame_buffer_V_address0 = tmp_286_fu_3273_p3;
    end else if ((1'b1 == ap_CS_fsm_state17)) begin
        frame_buffer_V_address0 = tmp_284_fu_3245_p3;
    end else if ((1'b1 == ap_CS_fsm_state16)) begin
        frame_buffer_V_address0 = tmp_282_fu_3217_p3;
    end else if ((1'b1 == ap_CS_fsm_state15)) begin
        frame_buffer_V_address0 = tmp_280_fu_3189_p3;
    end else if ((1'b1 == ap_CS_fsm_state14)) begin
        frame_buffer_V_address0 = tmp_278_fu_3161_p3;
    end else if ((1'b1 == ap_CS_fsm_state13)) begin
        frame_buffer_V_address0 = tmp_276_fu_3133_p3;
    end else if ((1'b1 == ap_CS_fsm_state12)) begin
        frame_buffer_V_address0 = tmp_274_fu_3105_p3;
    end else if ((1'b1 == ap_CS_fsm_state11)) begin
        frame_buffer_V_address0 = tmp_272_fu_3077_p3;
    end else if ((1'b1 == ap_CS_fsm_state10)) begin
        frame_buffer_V_address0 = tmp_270_fu_3049_p3;
    end else if ((1'b1 == ap_CS_fsm_state9)) begin
        frame_buffer_V_address0 = tmp_268_fu_3021_p3;
    end else if ((1'b1 == ap_CS_fsm_state8)) begin
        frame_buffer_V_address0 = tmp_266_fu_2993_p3;
    end else if ((1'b1 == ap_CS_fsm_state7)) begin
        frame_buffer_V_address0 = tmp_264_fu_2965_p3;
    end else if ((1'b1 == ap_CS_fsm_state6)) begin
        frame_buffer_V_address0 = tmp_262_fu_2937_p3;
    end else if ((1'b1 == ap_CS_fsm_state5)) begin
        frame_buffer_V_address0 = tmp_260_fu_2909_p3;
    end else if ((1'b1 == ap_CS_fsm_state4)) begin
        frame_buffer_V_address0 = tmp_258_fu_2881_p3;
    end else if ((1'b1 == ap_CS_fsm_state3)) begin
        frame_buffer_V_address0 = tmp_256_fu_2853_p3;
    end else if ((1'b1 == ap_CS_fsm_state2)) begin
        frame_buffer_V_address0 = tmp_s_fu_2825_p3;
    end else begin
        frame_buffer_V_address0 = 'bx;
    end
end

always @ (*) begin
    if (((ap_enable_reg_pp2_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp2_stage1) & (1'b0 == ap_block_pp2_stage1))) begin
        frame_buffer_V_address1 = zext_ln215_8_fu_6574_p1;
    end else if (((ap_enable_reg_pp2_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp2_stage0) & (1'b0 == ap_block_pp2_stage0))) begin
        frame_buffer_V_address1 = zext_ln215_7_fu_6536_p1;
    end else if ((1'b1 == ap_CS_fsm_state129)) begin
        frame_buffer_V_address1 = tmp_507_fu_6367_p3;
    end else if ((1'b1 == ap_CS_fsm_state128)) begin
        frame_buffer_V_address1 = tmp_505_fu_6339_p3;
    end else if ((1'b1 == ap_CS_fsm_state127)) begin
        frame_buffer_V_address1 = tmp_503_fu_6311_p3;
    end else if ((1'b1 == ap_CS_fsm_state126)) begin
        frame_buffer_V_address1 = tmp_501_fu_6283_p3;
    end else if ((1'b1 == ap_CS_fsm_state125)) begin
        frame_buffer_V_address1 = tmp_499_fu_6255_p3;
    end else if ((1'b1 == ap_CS_fsm_state124)) begin
        frame_buffer_V_address1 = tmp_497_fu_6227_p3;
    end else if ((1'b1 == ap_CS_fsm_state123)) begin
        frame_buffer_V_address1 = tmp_495_fu_6199_p3;
    end else if ((1'b1 == ap_CS_fsm_state122)) begin
        frame_buffer_V_address1 = tmp_493_fu_6171_p3;
    end else if ((1'b1 == ap_CS_fsm_state121)) begin
        frame_buffer_V_address1 = tmp_491_fu_6143_p3;
    end else if ((1'b1 == ap_CS_fsm_state120)) begin
        frame_buffer_V_address1 = tmp_489_fu_6115_p3;
    end else if ((1'b1 == ap_CS_fsm_state119)) begin
        frame_buffer_V_address1 = tmp_487_fu_6087_p3;
    end else if ((1'b1 == ap_CS_fsm_state118)) begin
        frame_buffer_V_address1 = tmp_485_fu_6059_p3;
    end else if ((1'b1 == ap_CS_fsm_state117)) begin
        frame_buffer_V_address1 = tmp_483_fu_6031_p3;
    end else if ((1'b1 == ap_CS_fsm_state116)) begin
        frame_buffer_V_address1 = tmp_481_fu_6003_p3;
    end else if ((1'b1 == ap_CS_fsm_state115)) begin
        frame_buffer_V_address1 = tmp_479_fu_5975_p3;
    end else if ((1'b1 == ap_CS_fsm_state114)) begin
        frame_buffer_V_address1 = tmp_477_fu_5947_p3;
    end else if ((1'b1 == ap_CS_fsm_state113)) begin
        frame_buffer_V_address1 = tmp_475_fu_5919_p3;
    end else if ((1'b1 == ap_CS_fsm_state112)) begin
        frame_buffer_V_address1 = tmp_473_fu_5891_p3;
    end else if ((1'b1 == ap_CS_fsm_state111)) begin
        frame_buffer_V_address1 = tmp_471_fu_5863_p3;
    end else if ((1'b1 == ap_CS_fsm_state110)) begin
        frame_buffer_V_address1 = tmp_469_fu_5835_p3;
    end else if ((1'b1 == ap_CS_fsm_state109)) begin
        frame_buffer_V_address1 = tmp_467_fu_5807_p3;
    end else if ((1'b1 == ap_CS_fsm_state108)) begin
        frame_buffer_V_address1 = tmp_465_fu_5779_p3;
    end else if ((1'b1 == ap_CS_fsm_state107)) begin
        frame_buffer_V_address1 = tmp_463_fu_5751_p3;
    end else if ((1'b1 == ap_CS_fsm_state106)) begin
        frame_buffer_V_address1 = tmp_461_fu_5723_p3;
    end else if ((1'b1 == ap_CS_fsm_state105)) begin
        frame_buffer_V_address1 = tmp_459_fu_5695_p3;
    end else if ((1'b1 == ap_CS_fsm_state104)) begin
        frame_buffer_V_address1 = tmp_457_fu_5667_p3;
    end else if ((1'b1 == ap_CS_fsm_state103)) begin
        frame_buffer_V_address1 = tmp_455_fu_5639_p3;
    end else if ((1'b1 == ap_CS_fsm_state102)) begin
        frame_buffer_V_address1 = tmp_453_fu_5611_p3;
    end else if ((1'b1 == ap_CS_fsm_state101)) begin
        frame_buffer_V_address1 = tmp_451_fu_5583_p3;
    end else if ((1'b1 == ap_CS_fsm_state100)) begin
        frame_buffer_V_address1 = tmp_449_fu_5555_p3;
    end else if ((1'b1 == ap_CS_fsm_state99)) begin
        frame_buffer_V_address1 = tmp_447_fu_5527_p3;
    end else if ((1'b1 == ap_CS_fsm_state98)) begin
        frame_buffer_V_address1 = tmp_445_fu_5499_p3;
    end else if ((1'b1 == ap_CS_fsm_state97)) begin
        frame_buffer_V_address1 = tmp_443_fu_5471_p3;
    end else if ((1'b1 == ap_CS_fsm_state96)) begin
        frame_buffer_V_address1 = tmp_441_fu_5443_p3;
    end else if ((1'b1 == ap_CS_fsm_state95)) begin
        frame_buffer_V_address1 = tmp_439_fu_5415_p3;
    end else if ((1'b1 == ap_CS_fsm_state94)) begin
        frame_buffer_V_address1 = tmp_437_fu_5387_p3;
    end else if ((1'b1 == ap_CS_fsm_state93)) begin
        frame_buffer_V_address1 = tmp_435_fu_5359_p3;
    end else if ((1'b1 == ap_CS_fsm_state92)) begin
        frame_buffer_V_address1 = tmp_433_fu_5331_p3;
    end else if ((1'b1 == ap_CS_fsm_state91)) begin
        frame_buffer_V_address1 = tmp_431_fu_5303_p3;
    end else if ((1'b1 == ap_CS_fsm_state90)) begin
        frame_buffer_V_address1 = tmp_429_fu_5275_p3;
    end else if ((1'b1 == ap_CS_fsm_state89)) begin
        frame_buffer_V_address1 = tmp_427_fu_5247_p3;
    end else if ((1'b1 == ap_CS_fsm_state88)) begin
        frame_buffer_V_address1 = tmp_425_fu_5219_p3;
    end else if ((1'b1 == ap_CS_fsm_state87)) begin
        frame_buffer_V_address1 = tmp_423_fu_5191_p3;
    end else if ((1'b1 == ap_CS_fsm_state86)) begin
        frame_buffer_V_address1 = tmp_421_fu_5163_p3;
    end else if ((1'b1 == ap_CS_fsm_state85)) begin
        frame_buffer_V_address1 = tmp_419_fu_5135_p3;
    end else if ((1'b1 == ap_CS_fsm_state84)) begin
        frame_buffer_V_address1 = tmp_417_fu_5107_p3;
    end else if ((1'b1 == ap_CS_fsm_state83)) begin
        frame_buffer_V_address1 = tmp_415_fu_5079_p3;
    end else if ((1'b1 == ap_CS_fsm_state82)) begin
        frame_buffer_V_address1 = tmp_413_fu_5051_p3;
    end else if ((1'b1 == ap_CS_fsm_state81)) begin
        frame_buffer_V_address1 = tmp_411_fu_5023_p3;
    end else if ((1'b1 == ap_CS_fsm_state80)) begin
        frame_buffer_V_address1 = tmp_409_fu_4995_p3;
    end else if ((1'b1 == ap_CS_fsm_state79)) begin
        frame_buffer_V_address1 = tmp_407_fu_4967_p3;
    end else if ((1'b1 == ap_CS_fsm_state78)) begin
        frame_buffer_V_address1 = tmp_405_fu_4939_p3;
    end else if ((1'b1 == ap_CS_fsm_state77)) begin
        frame_buffer_V_address1 = tmp_403_fu_4911_p3;
    end else if ((1'b1 == ap_CS_fsm_state76)) begin
        frame_buffer_V_address1 = tmp_401_fu_4883_p3;
    end else if ((1'b1 == ap_CS_fsm_state75)) begin
        frame_buffer_V_address1 = tmp_399_fu_4855_p3;
    end else if ((1'b1 == ap_CS_fsm_state74)) begin
        frame_buffer_V_address1 = tmp_397_fu_4827_p3;
    end else if ((1'b1 == ap_CS_fsm_state73)) begin
        frame_buffer_V_address1 = tmp_395_fu_4799_p3;
    end else if ((1'b1 == ap_CS_fsm_state72)) begin
        frame_buffer_V_address1 = tmp_393_fu_4771_p3;
    end else if ((1'b1 == ap_CS_fsm_state71)) begin
        frame_buffer_V_address1 = tmp_391_fu_4743_p3;
    end else if ((1'b1 == ap_CS_fsm_state70)) begin
        frame_buffer_V_address1 = tmp_389_fu_4715_p3;
    end else if ((1'b1 == ap_CS_fsm_state69)) begin
        frame_buffer_V_address1 = tmp_387_fu_4687_p3;
    end else if ((1'b1 == ap_CS_fsm_state68)) begin
        frame_buffer_V_address1 = tmp_385_fu_4659_p3;
    end else if ((1'b1 == ap_CS_fsm_state67)) begin
        frame_buffer_V_address1 = tmp_383_fu_4631_p3;
    end else if ((1'b1 == ap_CS_fsm_state66)) begin
        frame_buffer_V_address1 = tmp_381_fu_4603_p3;
    end else if ((1'b1 == ap_CS_fsm_state65)) begin
        frame_buffer_V_address1 = tmp_379_fu_4575_p3;
    end else if ((1'b1 == ap_CS_fsm_state64)) begin
        frame_buffer_V_address1 = tmp_377_fu_4547_p3;
    end else if ((1'b1 == ap_CS_fsm_state63)) begin
        frame_buffer_V_address1 = tmp_375_fu_4519_p3;
    end else if ((1'b1 == ap_CS_fsm_state62)) begin
        frame_buffer_V_address1 = tmp_373_fu_4491_p3;
    end else if ((1'b1 == ap_CS_fsm_state61)) begin
        frame_buffer_V_address1 = tmp_371_fu_4463_p3;
    end else if ((1'b1 == ap_CS_fsm_state60)) begin
        frame_buffer_V_address1 = tmp_369_fu_4435_p3;
    end else if ((1'b1 == ap_CS_fsm_state59)) begin
        frame_buffer_V_address1 = tmp_367_fu_4407_p3;
    end else if ((1'b1 == ap_CS_fsm_state58)) begin
        frame_buffer_V_address1 = tmp_365_fu_4379_p3;
    end else if ((1'b1 == ap_CS_fsm_state57)) begin
        frame_buffer_V_address1 = tmp_363_fu_4351_p3;
    end else if ((1'b1 == ap_CS_fsm_state56)) begin
        frame_buffer_V_address1 = tmp_361_fu_4323_p3;
    end else if ((1'b1 == ap_CS_fsm_state55)) begin
        frame_buffer_V_address1 = tmp_359_fu_4295_p3;
    end else if ((1'b1 == ap_CS_fsm_state54)) begin
        frame_buffer_V_address1 = tmp_357_fu_4267_p3;
    end else if ((1'b1 == ap_CS_fsm_state53)) begin
        frame_buffer_V_address1 = tmp_355_fu_4239_p3;
    end else if ((1'b1 == ap_CS_fsm_state52)) begin
        frame_buffer_V_address1 = tmp_353_fu_4211_p3;
    end else if ((1'b1 == ap_CS_fsm_state51)) begin
        frame_buffer_V_address1 = tmp_351_fu_4183_p3;
    end else if ((1'b1 == ap_CS_fsm_state50)) begin
        frame_buffer_V_address1 = tmp_349_fu_4155_p3;
    end else if ((1'b1 == ap_CS_fsm_state49)) begin
        frame_buffer_V_address1 = tmp_347_fu_4127_p3;
    end else if ((1'b1 == ap_CS_fsm_state48)) begin
        frame_buffer_V_address1 = tmp_345_fu_4099_p3;
    end else if ((1'b1 == ap_CS_fsm_state47)) begin
        frame_buffer_V_address1 = tmp_343_fu_4071_p3;
    end else if ((1'b1 == ap_CS_fsm_state46)) begin
        frame_buffer_V_address1 = tmp_341_fu_4043_p3;
    end else if ((1'b1 == ap_CS_fsm_state45)) begin
        frame_buffer_V_address1 = tmp_339_fu_4015_p3;
    end else if ((1'b1 == ap_CS_fsm_state44)) begin
        frame_buffer_V_address1 = tmp_337_fu_3987_p3;
    end else if ((1'b1 == ap_CS_fsm_state43)) begin
        frame_buffer_V_address1 = tmp_335_fu_3959_p3;
    end else if ((1'b1 == ap_CS_fsm_state42)) begin
        frame_buffer_V_address1 = tmp_333_fu_3931_p3;
    end else if ((1'b1 == ap_CS_fsm_state41)) begin
        frame_buffer_V_address1 = tmp_331_fu_3903_p3;
    end else if ((1'b1 == ap_CS_fsm_state40)) begin
        frame_buffer_V_address1 = tmp_329_fu_3875_p3;
    end else if ((1'b1 == ap_CS_fsm_state39)) begin
        frame_buffer_V_address1 = tmp_327_fu_3847_p3;
    end else if ((1'b1 == ap_CS_fsm_state38)) begin
        frame_buffer_V_address1 = tmp_325_fu_3819_p3;
    end else if ((1'b1 == ap_CS_fsm_state37)) begin
        frame_buffer_V_address1 = tmp_323_fu_3791_p3;
    end else if ((1'b1 == ap_CS_fsm_state36)) begin
        frame_buffer_V_address1 = tmp_321_fu_3763_p3;
    end else if ((1'b1 == ap_CS_fsm_state35)) begin
        frame_buffer_V_address1 = tmp_319_fu_3735_p3;
    end else if ((1'b1 == ap_CS_fsm_state34)) begin
        frame_buffer_V_address1 = tmp_317_fu_3707_p3;
    end else if ((1'b1 == ap_CS_fsm_state33)) begin
        frame_buffer_V_address1 = tmp_315_fu_3679_p3;
    end else if ((1'b1 == ap_CS_fsm_state32)) begin
        frame_buffer_V_address1 = tmp_313_fu_3651_p3;
    end else if ((1'b1 == ap_CS_fsm_state31)) begin
        frame_buffer_V_address1 = tmp_311_fu_3623_p3;
    end else if ((1'b1 == ap_CS_fsm_state30)) begin
        frame_buffer_V_address1 = tmp_309_fu_3595_p3;
    end else if ((1'b1 == ap_CS_fsm_state29)) begin
        frame_buffer_V_address1 = tmp_307_fu_3567_p3;
    end else if ((1'b1 == ap_CS_fsm_state28)) begin
        frame_buffer_V_address1 = tmp_305_fu_3539_p3;
    end else if ((1'b1 == ap_CS_fsm_state27)) begin
        frame_buffer_V_address1 = tmp_303_fu_3511_p3;
    end else if ((1'b1 == ap_CS_fsm_state26)) begin
        frame_buffer_V_address1 = tmp_301_fu_3483_p3;
    end else if ((1'b1 == ap_CS_fsm_state25)) begin
        frame_buffer_V_address1 = tmp_299_fu_3455_p3;
    end else if ((1'b1 == ap_CS_fsm_state24)) begin
        frame_buffer_V_address1 = tmp_297_fu_3427_p3;
    end else if ((1'b1 == ap_CS_fsm_state23)) begin
        frame_buffer_V_address1 = tmp_295_fu_3399_p3;
    end else if ((1'b1 == ap_CS_fsm_state22)) begin
        frame_buffer_V_address1 = tmp_293_fu_3371_p3;
    end else if ((1'b1 == ap_CS_fsm_state21)) begin
        frame_buffer_V_address1 = tmp_291_fu_3343_p3;
    end else if ((1'b1 == ap_CS_fsm_state20)) begin
        frame_buffer_V_address1 = tmp_289_fu_3315_p3;
    end else if ((1'b1 == ap_CS_fsm_state19)) begin
        frame_buffer_V_address1 = tmp_287_fu_3287_p3;
    end else if ((1'b1 == ap_CS_fsm_state18)) begin
        frame_buffer_V_address1 = tmp_285_fu_3259_p3;
    end else if ((1'b1 == ap_CS_fsm_state17)) begin
        frame_buffer_V_address1 = tmp_283_fu_3231_p3;
    end else if ((1'b1 == ap_CS_fsm_state16)) begin
        frame_buffer_V_address1 = tmp_281_fu_3203_p3;
    end else if ((1'b1 == ap_CS_fsm_state15)) begin
        frame_buffer_V_address1 = tmp_279_fu_3175_p3;
    end else if ((1'b1 == ap_CS_fsm_state14)) begin
        frame_buffer_V_address1 = tmp_277_fu_3147_p3;
    end else if ((1'b1 == ap_CS_fsm_state13)) begin
        frame_buffer_V_address1 = tmp_275_fu_3119_p3;
    end else if ((1'b1 == ap_CS_fsm_state12)) begin
        frame_buffer_V_address1 = tmp_273_fu_3091_p3;
    end else if ((1'b1 == ap_CS_fsm_state11)) begin
        frame_buffer_V_address1 = tmp_271_fu_3063_p3;
    end else if ((1'b1 == ap_CS_fsm_state10)) begin
        frame_buffer_V_address1 = tmp_269_fu_3035_p3;
    end else if ((1'b1 == ap_CS_fsm_state9)) begin
        frame_buffer_V_address1 = tmp_267_fu_3007_p3;
    end else if ((1'b1 == ap_CS_fsm_state8)) begin
        frame_buffer_V_address1 = tmp_265_fu_2979_p3;
    end else if ((1'b1 == ap_CS_fsm_state7)) begin
        frame_buffer_V_address1 = tmp_263_fu_2951_p3;
    end else if ((1'b1 == ap_CS_fsm_state6)) begin
        frame_buffer_V_address1 = tmp_261_fu_2923_p3;
    end else if ((1'b1 == ap_CS_fsm_state5)) begin
        frame_buffer_V_address1 = tmp_259_fu_2895_p3;
    end else if ((1'b1 == ap_CS_fsm_state4)) begin
        frame_buffer_V_address1 = tmp_257_fu_2867_p3;
    end else if ((1'b1 == ap_CS_fsm_state3)) begin
        frame_buffer_V_address1 = tmp_255_fu_2839_p3;
    end else if ((1'b1 == ap_CS_fsm_state2)) begin
        frame_buffer_V_address1 = zext_ln324_fu_2814_p1;
    end else begin
        frame_buffer_V_address1 = 'bx;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state67) | (1'b1 == ap_CS_fsm_state66) | (1'b1 == ap_CS_fsm_state65) | (1'b1 == ap_CS_fsm_state64) | (1'b1 == ap_CS_fsm_state63) | (1'b1 == ap_CS_fsm_state62) | (1'b1 == ap_CS_fsm_state61) | (1'b1 == ap_CS_fsm_state60) | (1'b1 == ap_CS_fsm_state59) | (1'b1 == ap_CS_fsm_state58) | (1'b1 == ap_CS_fsm_state57) | (1'b1 == ap_CS_fsm_state56) | (1'b1 == ap_CS_fsm_state55) | (1'b1 == ap_CS_fsm_state54) | (1'b1 == ap_CS_fsm_state53) | (1'b1 == ap_CS_fsm_state52) | (1'b1 == ap_CS_fsm_state51) | (1'b1 == ap_CS_fsm_state50) | (1'b1 == ap_CS_fsm_state49) | (1'b1 == ap_CS_fsm_state48) | (1'b1 == ap_CS_fsm_state47) | (1'b1 == ap_CS_fsm_state46) | (1'b1 == ap_CS_fsm_state45) | (1'b1 == ap_CS_fsm_state44) | (1'b1 == ap_CS_fsm_state43) | (1'b1 == ap_CS_fsm_state42) | (1'b1 == ap_CS_fsm_state41) | (1'b1 == ap_CS_fsm_state40) | (1'b1 == ap_CS_fsm_state39) | (1'b1 == ap_CS_fsm_state38) | (1'b1 == ap_CS_fsm_state37) | (1'b1 == ap_CS_fsm_state36) | (1'b1 == ap_CS_fsm_state35) | (1'b1 == ap_CS_fsm_state34) | (1'b1 == ap_CS_fsm_state33) | (1'b1 == ap_CS_fsm_state32) | (1'b1 == ap_CS_fsm_state31) | (1'b1 == ap_CS_fsm_state30) | (1'b1 == ap_CS_fsm_state29) | (1'b1 == ap_CS_fsm_state28) | (1'b1 == ap_CS_fsm_state27) | (1'b1 == ap_CS_fsm_state26) | (1'b1 == ap_CS_fsm_state25) | (1'b1 == ap_CS_fsm_state24) | (1'b1 == ap_CS_fsm_state23) | (1'b1 == ap_CS_fsm_state22) | (1'b1 == ap_CS_fsm_state21) | (1'b1 == ap_CS_fsm_state20) | (1'b1 == ap_CS_fsm_state19) | (1'b1 == ap_CS_fsm_state18) | (1'b1 == ap_CS_fsm_state17) | (1'b1 == ap_CS_fsm_state16) | (1'b1 == ap_CS_fsm_state15) | (1'b1 == ap_CS_fsm_state14) | (1'b1 == ap_CS_fsm_state13) | (1'b1 == ap_CS_fsm_state12) | (1'b1 == ap_CS_fsm_state11) | (1'b1 == ap_CS_fsm_state10) | (1'b1 == ap_CS_fsm_state9) | (1'b1 == ap_CS_fsm_state8) | (1'b1 == ap_CS_fsm_state7) | (1'b1 == ap_CS_fsm_state6) | (1'b1 == ap_CS_fsm_state5) | (1'b1 == ap_CS_fsm_state4) | (1'b1 == ap_CS_fsm_state3) | (1'b1 == ap_CS_fsm_state129) | (1'b1 == ap_CS_fsm_state2) | (1'b1 == ap_CS_fsm_state128) | (1'b1 == ap_CS_fsm_state127) | (1'b1 == ap_CS_fsm_state126) | (1'b1 == ap_CS_fsm_state125) | (1'b1 == ap_CS_fsm_state124) | (1'b1 == ap_CS_fsm_state123) | (1'b1 == ap_CS_fsm_state122) | (1'b1 == ap_CS_fsm_state121) | (1'b1 == ap_CS_fsm_state120) | (1'b1 == ap_CS_fsm_state119) | (1'b1 == ap_CS_fsm_state118) | (1'b1 == ap_CS_fsm_state117) | (1'b1 == ap_CS_fsm_state116) | (1'b1 == ap_CS_fsm_state115) | (1'b1 == ap_CS_fsm_state114) | (1'b1 == ap_CS_fsm_state113) | (1'b1 == ap_CS_fsm_state112) | (1'b1 == ap_CS_fsm_state111) | (1'b1 == ap_CS_fsm_state110) | (1'b1 == ap_CS_fsm_state109) | (1'b1 == ap_CS_fsm_state108) | (1'b1 == ap_CS_fsm_state107) | (1'b1 == ap_CS_fsm_state106) | (1'b1 == ap_CS_fsm_state105) | (1'b1 == ap_CS_fsm_state104) | (1'b1 == ap_CS_fsm_state103) | (1'b1 == ap_CS_fsm_state102) | (1'b1 == ap_CS_fsm_state101) | (1'b1 == ap_CS_fsm_state100) | (1'b1 == ap_CS_fsm_state99) | (1'b1 == ap_CS_fsm_state98) | (1'b1 == ap_CS_fsm_state97) | (1'b1 == ap_CS_fsm_state96) | (1'b1 == ap_CS_fsm_state95) | (1'b1 == ap_CS_fsm_state94) | (1'b1 == ap_CS_fsm_state93) | (1'b1 == ap_CS_fsm_state92) | (1'b1 == ap_CS_fsm_state91) | (1'b1 == ap_CS_fsm_state90) | (1'b1 == ap_CS_fsm_state89) | (1'b1 == ap_CS_fsm_state88) | (1'b1 == ap_CS_fsm_state87) | (1'b1 == ap_CS_fsm_state86) | (1'b1 == ap_CS_fsm_state85) | (1'b1 == ap_CS_fsm_state84) | (1'b1 == ap_CS_fsm_state83) | (1'b1 == ap_CS_fsm_state82) | (1'b1 == ap_CS_fsm_state81) | (1'b1 == ap_CS_fsm_state80) | (1'b1 == ap_CS_fsm_state79) | (1'b1 == ap_CS_fsm_state78) | (1'b1 == ap_CS_fsm_state77) | (1'b1 == ap_CS_fsm_state76) | (1'b1 == ap_CS_fsm_state75) | (1'b1 == ap_CS_fsm_state74) | (1'b1 == ap_CS_fsm_state73) | (1'b1 == ap_CS_fsm_state72) | (1'b1 == ap_CS_fsm_state71) | (1'b1 == ap_CS_fsm_state70) | (1'b1 == ap_CS_fsm_state69) | (1'b1 == ap_CS_fsm_state68) | ((ap_enable_reg_pp2_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp2_stage1) & (1'b0 == ap_block_pp2_stage1_11001)) | ((ap_enable_reg_pp2_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp2_stage0) & (1'b0 == ap_block_pp2_stage0_11001)) | ((1'b1 == ap_CS_fsm_pp1_stage0) & (1'b0 == ap_block_pp1_stage0_11001) & (ap_enable_reg_pp1_iter1 == 1'b1)))) begin
        frame_buffer_V_ce0 = 1'b1;
    end else begin
        frame_buffer_V_ce0 = 1'b0;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state67) | (1'b1 == ap_CS_fsm_state66) | (1'b1 == ap_CS_fsm_state65) | (1'b1 == ap_CS_fsm_state64) | (1'b1 == ap_CS_fsm_state63) | (1'b1 == ap_CS_fsm_state62) | (1'b1 == ap_CS_fsm_state61) | (1'b1 == ap_CS_fsm_state60) | (1'b1 == ap_CS_fsm_state59) | (1'b1 == ap_CS_fsm_state58) | (1'b1 == ap_CS_fsm_state57) | (1'b1 == ap_CS_fsm_state56) | (1'b1 == ap_CS_fsm_state55) | (1'b1 == ap_CS_fsm_state54) | (1'b1 == ap_CS_fsm_state53) | (1'b1 == ap_CS_fsm_state52) | (1'b1 == ap_CS_fsm_state51) | (1'b1 == ap_CS_fsm_state50) | (1'b1 == ap_CS_fsm_state49) | (1'b1 == ap_CS_fsm_state48) | (1'b1 == ap_CS_fsm_state47) | (1'b1 == ap_CS_fsm_state46) | (1'b1 == ap_CS_fsm_state45) | (1'b1 == ap_CS_fsm_state44) | (1'b1 == ap_CS_fsm_state43) | (1'b1 == ap_CS_fsm_state42) | (1'b1 == ap_CS_fsm_state41) | (1'b1 == ap_CS_fsm_state40) | (1'b1 == ap_CS_fsm_state39) | (1'b1 == ap_CS_fsm_state38) | (1'b1 == ap_CS_fsm_state37) | (1'b1 == ap_CS_fsm_state36) | (1'b1 == ap_CS_fsm_state35) | (1'b1 == ap_CS_fsm_state34) | (1'b1 == ap_CS_fsm_state33) | (1'b1 == ap_CS_fsm_state32) | (1'b1 == ap_CS_fsm_state31) | (1'b1 == ap_CS_fsm_state30) | (1'b1 == ap_CS_fsm_state29) | (1'b1 == ap_CS_fsm_state28) | (1'b1 == ap_CS_fsm_state27) | (1'b1 == ap_CS_fsm_state26) | (1'b1 == ap_CS_fsm_state25) | (1'b1 == ap_CS_fsm_state24) | (1'b1 == ap_CS_fsm_state23) | (1'b1 == ap_CS_fsm_state22) | (1'b1 == ap_CS_fsm_state21) | (1'b1 == ap_CS_fsm_state20) | (1'b1 == ap_CS_fsm_state19) | (1'b1 == ap_CS_fsm_state18) | (1'b1 == ap_CS_fsm_state17) | (1'b1 == ap_CS_fsm_state16) | (1'b1 == ap_CS_fsm_state15) | (1'b1 == ap_CS_fsm_state14) | (1'b1 == ap_CS_fsm_state13) | (1'b1 == ap_CS_fsm_state12) | (1'b1 == ap_CS_fsm_state11) | (1'b1 == ap_CS_fsm_state10) | (1'b1 == ap_CS_fsm_state9) | (1'b1 == ap_CS_fsm_state8) | (1'b1 == ap_CS_fsm_state7) | (1'b1 == ap_CS_fsm_state6) | (1'b1 == ap_CS_fsm_state5) | (1'b1 == ap_CS_fsm_state4) | (1'b1 == ap_CS_fsm_state3) | (1'b1 == ap_CS_fsm_state129) | (1'b1 == ap_CS_fsm_state2) | (1'b1 == ap_CS_fsm_state128) | (1'b1 == ap_CS_fsm_state127) | (1'b1 == ap_CS_fsm_state126) | (1'b1 == ap_CS_fsm_state125) | (1'b1 == ap_CS_fsm_state124) | (1'b1 == ap_CS_fsm_state123) | (1'b1 == ap_CS_fsm_state122) | (1'b1 == ap_CS_fsm_state121) | (1'b1 == ap_CS_fsm_state120) | (1'b1 == ap_CS_fsm_state119) | (1'b1 == ap_CS_fsm_state118) | (1'b1 == ap_CS_fsm_state117) | (1'b1 == ap_CS_fsm_state116) | (1'b1 == ap_CS_fsm_state115) | (1'b1 == ap_CS_fsm_state114) | (1'b1 == ap_CS_fsm_state113) | (1'b1 == ap_CS_fsm_state112) | (1'b1 == ap_CS_fsm_state111) | (1'b1 == ap_CS_fsm_state110) | (1'b1 == ap_CS_fsm_state109) | (1'b1 == ap_CS_fsm_state108) | (1'b1 == ap_CS_fsm_state107) | (1'b1 == ap_CS_fsm_state106) | (1'b1 == ap_CS_fsm_state105) | (1'b1 == ap_CS_fsm_state104) | (1'b1 == ap_CS_fsm_state103) | (1'b1 == ap_CS_fsm_state102) | (1'b1 == ap_CS_fsm_state101) | (1'b1 == ap_CS_fsm_state100) | (1'b1 == ap_CS_fsm_state99) | (1'b1 == ap_CS_fsm_state98) | (1'b1 == ap_CS_fsm_state97) | (1'b1 == ap_CS_fsm_state96) | (1'b1 == ap_CS_fsm_state95) | (1'b1 == ap_CS_fsm_state94) | (1'b1 == ap_CS_fsm_state93) | (1'b1 == ap_CS_fsm_state92) | (1'b1 == ap_CS_fsm_state91) | (1'b1 == ap_CS_fsm_state90) | (1'b1 == ap_CS_fsm_state89) | (1'b1 == ap_CS_fsm_state88) | (1'b1 == ap_CS_fsm_state87) | (1'b1 == ap_CS_fsm_state86) | (1'b1 == ap_CS_fsm_state85) | (1'b1 == ap_CS_fsm_state84) | (1'b1 == ap_CS_fsm_state83) | (1'b1 == ap_CS_fsm_state82) | (1'b1 == ap_CS_fsm_state81) | (1'b1 == ap_CS_fsm_state80) | (1'b1 == ap_CS_fsm_state79) | (1'b1 == ap_CS_fsm_state78) | (1'b1 == ap_CS_fsm_state77) | (1'b1 == ap_CS_fsm_state76) | (1'b1 == ap_CS_fsm_state75) | (1'b1 == ap_CS_fsm_state74) | (1'b1 == ap_CS_fsm_state73) | (1'b1 == ap_CS_fsm_state72) | (1'b1 == ap_CS_fsm_state71) | (1'b1 == ap_CS_fsm_state70) | (1'b1 == ap_CS_fsm_state69) | (1'b1 == ap_CS_fsm_state68) | ((ap_enable_reg_pp2_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp2_stage1) & (1'b0 == ap_block_pp2_stage1_11001)) | ((ap_enable_reg_pp2_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp2_stage0) & (1'b0 == ap_block_pp2_stage0_11001)))) begin
        frame_buffer_V_ce1 = 1'b1;
    end else begin
        frame_buffer_V_ce1 = 1'b0;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_pp1_stage0) & (1'b0 == ap_block_pp1_stage0) & (ap_enable_reg_pp1_iter1 == 1'b1))) begin
        frame_buffer_V_d0 = {{Input_1_dout[23:16]}};
    end else if (((1'b1 == ap_CS_fsm_state67) | (1'b1 == ap_CS_fsm_state66) | (1'b1 == ap_CS_fsm_state65) | (1'b1 == ap_CS_fsm_state64) | (1'b1 == ap_CS_fsm_state63) | (1'b1 == ap_CS_fsm_state62) | (1'b1 == ap_CS_fsm_state61) | (1'b1 == ap_CS_fsm_state60) | (1'b1 == ap_CS_fsm_state59) | (1'b1 == ap_CS_fsm_state58) | (1'b1 == ap_CS_fsm_state57) | (1'b1 == ap_CS_fsm_state56) | (1'b1 == ap_CS_fsm_state55) | (1'b1 == ap_CS_fsm_state54) | (1'b1 == ap_CS_fsm_state53) | (1'b1 == ap_CS_fsm_state52) | (1'b1 == ap_CS_fsm_state51) | (1'b1 == ap_CS_fsm_state50) | (1'b1 == ap_CS_fsm_state49) | (1'b1 == ap_CS_fsm_state48) | (1'b1 == ap_CS_fsm_state47) | (1'b1 == ap_CS_fsm_state46) | (1'b1 == ap_CS_fsm_state45) | (1'b1 == ap_CS_fsm_state44) | (1'b1 == ap_CS_fsm_state43) | (1'b1 == ap_CS_fsm_state42) | (1'b1 == ap_CS_fsm_state41) | (1'b1 == ap_CS_fsm_state40) | (1'b1 == ap_CS_fsm_state39) | (1'b1 == ap_CS_fsm_state38) | (1'b1 == ap_CS_fsm_state37) | (1'b1 == ap_CS_fsm_state36) | (1'b1 == ap_CS_fsm_state35) | (1'b1 == ap_CS_fsm_state34) | (1'b1 == ap_CS_fsm_state33) | (1'b1 == ap_CS_fsm_state32) | (1'b1 == ap_CS_fsm_state31) | (1'b1 == ap_CS_fsm_state30) | (1'b1 == ap_CS_fsm_state29) | (1'b1 == ap_CS_fsm_state28) | (1'b1 == ap_CS_fsm_state27) | (1'b1 == ap_CS_fsm_state26) | (1'b1 == ap_CS_fsm_state25) | (1'b1 == ap_CS_fsm_state24) | (1'b1 == ap_CS_fsm_state23) | (1'b1 == ap_CS_fsm_state22) | (1'b1 == ap_CS_fsm_state21) | (1'b1 == ap_CS_fsm_state20) | (1'b1 == ap_CS_fsm_state19) | (1'b1 == ap_CS_fsm_state18) | (1'b1 == ap_CS_fsm_state17) | (1'b1 == ap_CS_fsm_state16) | (1'b1 == ap_CS_fsm_state15) | (1'b1 == ap_CS_fsm_state14) | (1'b1 == ap_CS_fsm_state13) | (1'b1 == ap_CS_fsm_state12) | (1'b1 == ap_CS_fsm_state11) | (1'b1 == ap_CS_fsm_state10) | (1'b1 == ap_CS_fsm_state9) | (1'b1 == ap_CS_fsm_state8) | (1'b1 == ap_CS_fsm_state7) | (1'b1 == ap_CS_fsm_state6) | (1'b1 == ap_CS_fsm_state5) | (1'b1 == ap_CS_fsm_state4) | (1'b1 == ap_CS_fsm_state3) | (1'b1 == ap_CS_fsm_state129) | (1'b1 == ap_CS_fsm_state2) | (1'b1 == ap_CS_fsm_state128) | (1'b1 == ap_CS_fsm_state127) | (1'b1 == ap_CS_fsm_state126) | (1'b1 == ap_CS_fsm_state125) | (1'b1 == ap_CS_fsm_state124) | (1'b1 == ap_CS_fsm_state123) | (1'b1 == ap_CS_fsm_state122) | (1'b1 == ap_CS_fsm_state121) | (1'b1 == ap_CS_fsm_state120) | (1'b1 == ap_CS_fsm_state119) | (1'b1 == ap_CS_fsm_state118) | (1'b1 == ap_CS_fsm_state117) | (1'b1 == ap_CS_fsm_state116) | (1'b1 == ap_CS_fsm_state115) | (1'b1 == ap_CS_fsm_state114) | (1'b1 == ap_CS_fsm_state113) | (1'b1 == ap_CS_fsm_state112) | (1'b1 == ap_CS_fsm_state111) | (1'b1 == ap_CS_fsm_state110) | (1'b1 == ap_CS_fsm_state109) | (1'b1 == ap_CS_fsm_state108) | (1'b1 == ap_CS_fsm_state107) | (1'b1 == ap_CS_fsm_state106) | (1'b1 == ap_CS_fsm_state105) | (1'b1 == ap_CS_fsm_state104) | (1'b1 == ap_CS_fsm_state103) | (1'b1 == ap_CS_fsm_state102) | (1'b1 == ap_CS_fsm_state101) | (1'b1 == ap_CS_fsm_state100) | (1'b1 == ap_CS_fsm_state99) | (1'b1 == ap_CS_fsm_state98) | (1'b1 == ap_CS_fsm_state97) | (1'b1 == ap_CS_fsm_state96) | (1'b1 == ap_CS_fsm_state95) | (1'b1 == ap_CS_fsm_state94) | (1'b1 == ap_CS_fsm_state93) | (1'b1 == ap_CS_fsm_state92) | (1'b1 == ap_CS_fsm_state91) | (1'b1 == ap_CS_fsm_state90) | (1'b1 == ap_CS_fsm_state89) | (1'b1 == ap_CS_fsm_state88) | (1'b1 == ap_CS_fsm_state87) | (1'b1 == ap_CS_fsm_state86) | (1'b1 == ap_CS_fsm_state85) | (1'b1 == ap_CS_fsm_state84) | (1'b1 == ap_CS_fsm_state83) | (1'b1 == ap_CS_fsm_state82) | (1'b1 == ap_CS_fsm_state81) | (1'b1 == ap_CS_fsm_state80) | (1'b1 == ap_CS_fsm_state79) | (1'b1 == ap_CS_fsm_state78) | (1'b1 == ap_CS_fsm_state77) | (1'b1 == ap_CS_fsm_state76) | (1'b1 == ap_CS_fsm_state75) | (1'b1 == ap_CS_fsm_state74) | (1'b1 == ap_CS_fsm_state73) | (1'b1 == ap_CS_fsm_state72) | (1'b1 == ap_CS_fsm_state71) | (1'b1 == ap_CS_fsm_state70) | (1'b1 == ap_CS_fsm_state69) | (1'b1 == ap_CS_fsm_state68))) begin
        frame_buffer_V_d0 = 8'd0;
    end else begin
        frame_buffer_V_d0 = 'bx;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state67) | (1'b1 == ap_CS_fsm_state66) | (1'b1 == ap_CS_fsm_state65) | (1'b1 == ap_CS_fsm_state64) | (1'b1 == ap_CS_fsm_state63) | (1'b1 == ap_CS_fsm_state62) | (1'b1 == ap_CS_fsm_state61) | (1'b1 == ap_CS_fsm_state60) | (1'b1 == ap_CS_fsm_state59) | (1'b1 == ap_CS_fsm_state58) | (1'b1 == ap_CS_fsm_state57) | (1'b1 == ap_CS_fsm_state56) | (1'b1 == ap_CS_fsm_state55) | (1'b1 == ap_CS_fsm_state54) | (1'b1 == ap_CS_fsm_state53) | (1'b1 == ap_CS_fsm_state52) | (1'b1 == ap_CS_fsm_state51) | (1'b1 == ap_CS_fsm_state50) | (1'b1 == ap_CS_fsm_state49) | (1'b1 == ap_CS_fsm_state48) | (1'b1 == ap_CS_fsm_state47) | (1'b1 == ap_CS_fsm_state46) | (1'b1 == ap_CS_fsm_state45) | (1'b1 == ap_CS_fsm_state44) | (1'b1 == ap_CS_fsm_state43) | (1'b1 == ap_CS_fsm_state42) | (1'b1 == ap_CS_fsm_state41) | (1'b1 == ap_CS_fsm_state40) | (1'b1 == ap_CS_fsm_state39) | (1'b1 == ap_CS_fsm_state38) | (1'b1 == ap_CS_fsm_state37) | (1'b1 == ap_CS_fsm_state36) | (1'b1 == ap_CS_fsm_state35) | (1'b1 == ap_CS_fsm_state34) | (1'b1 == ap_CS_fsm_state33) | (1'b1 == ap_CS_fsm_state32) | (1'b1 == ap_CS_fsm_state31) | (1'b1 == ap_CS_fsm_state30) | (1'b1 == ap_CS_fsm_state29) | (1'b1 == ap_CS_fsm_state28) | (1'b1 == ap_CS_fsm_state27) | (1'b1 == ap_CS_fsm_state26) | (1'b1 == ap_CS_fsm_state25) | (1'b1 == ap_CS_fsm_state24) | (1'b1 == ap_CS_fsm_state23) | (1'b1 == ap_CS_fsm_state22) | (1'b1 == ap_CS_fsm_state21) | (1'b1 == ap_CS_fsm_state20) | (1'b1 == ap_CS_fsm_state19) | (1'b1 == ap_CS_fsm_state18) | (1'b1 == ap_CS_fsm_state17) | (1'b1 == ap_CS_fsm_state16) | (1'b1 == ap_CS_fsm_state15) | (1'b1 == ap_CS_fsm_state14) | (1'b1 == ap_CS_fsm_state13) | (1'b1 == ap_CS_fsm_state12) | (1'b1 == ap_CS_fsm_state11) | (1'b1 == ap_CS_fsm_state10) | (1'b1 == ap_CS_fsm_state9) | (1'b1 == ap_CS_fsm_state8) | (1'b1 == ap_CS_fsm_state7) | (1'b1 == ap_CS_fsm_state6) | (1'b1 == ap_CS_fsm_state5) | (1'b1 == ap_CS_fsm_state4) | (1'b1 == ap_CS_fsm_state3) | (1'b1 == ap_CS_fsm_state129) | (1'b1 == ap_CS_fsm_state128) | (1'b1 == ap_CS_fsm_state127) | (1'b1 == ap_CS_fsm_state126) | (1'b1 == ap_CS_fsm_state125) | (1'b1 == ap_CS_fsm_state124) | (1'b1 == ap_CS_fsm_state123) | (1'b1 == ap_CS_fsm_state122) | (1'b1 == ap_CS_fsm_state121) | (1'b1 == ap_CS_fsm_state120) | (1'b1 == ap_CS_fsm_state119) | (1'b1 == ap_CS_fsm_state118) | (1'b1 == ap_CS_fsm_state117) | (1'b1 == ap_CS_fsm_state116) | (1'b1 == ap_CS_fsm_state115) | (1'b1 == ap_CS_fsm_state114) | (1'b1 == ap_CS_fsm_state113) | (1'b1 == ap_CS_fsm_state112) | (1'b1 == ap_CS_fsm_state111) | (1'b1 == ap_CS_fsm_state110) | (1'b1 == ap_CS_fsm_state109) | (1'b1 == ap_CS_fsm_state108) | (1'b1 == ap_CS_fsm_state107) | (1'b1 == ap_CS_fsm_state106) | (1'b1 == ap_CS_fsm_state105) | (1'b1 == ap_CS_fsm_state104) | (1'b1 == ap_CS_fsm_state103) | (1'b1 == ap_CS_fsm_state102) | (1'b1 == ap_CS_fsm_state101) | (1'b1 == ap_CS_fsm_state100) | (1'b1 == ap_CS_fsm_state99) | (1'b1 == ap_CS_fsm_state98) | (1'b1 == ap_CS_fsm_state97) | (1'b1 == ap_CS_fsm_state96) | (1'b1 == ap_CS_fsm_state95) | (1'b1 == ap_CS_fsm_state94) | (1'b1 == ap_CS_fsm_state93) | (1'b1 == ap_CS_fsm_state92) | (1'b1 == ap_CS_fsm_state91) | (1'b1 == ap_CS_fsm_state90) | (1'b1 == ap_CS_fsm_state89) | (1'b1 == ap_CS_fsm_state88) | (1'b1 == ap_CS_fsm_state87) | (1'b1 == ap_CS_fsm_state86) | (1'b1 == ap_CS_fsm_state85) | (1'b1 == ap_CS_fsm_state84) | (1'b1 == ap_CS_fsm_state83) | (1'b1 == ap_CS_fsm_state82) | (1'b1 == ap_CS_fsm_state81) | (1'b1 == ap_CS_fsm_state80) | (1'b1 == ap_CS_fsm_state79) | (1'b1 == ap_CS_fsm_state78) | (1'b1 == ap_CS_fsm_state77) | (1'b1 == ap_CS_fsm_state76) | (1'b1 == ap_CS_fsm_state75) | (1'b1 == ap_CS_fsm_state74) | (1'b1 == ap_CS_fsm_state73) | (1'b1 == ap_CS_fsm_state72) | (1'b1 == ap_CS_fsm_state71) | (1'b1 == ap_CS_fsm_state70) | (1'b1 == ap_CS_fsm_state69) | (1'b1 == ap_CS_fsm_state68) | ((icmp_ln882_fu_2794_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state2)) | ((1'b1 == ap_CS_fsm_pp1_stage0) & (icmp_ln515_reg_6886 == 1'd0) & (1'b0 == ap_block_pp1_stage0_11001) & (ap_enable_reg_pp1_iter1 == 1'b1)))) begin
        frame_buffer_V_we0 = 1'b1;
    end else begin
        frame_buffer_V_we0 = 1'b0;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state67) | (1'b1 == ap_CS_fsm_state66) | (1'b1 == ap_CS_fsm_state65) | (1'b1 == ap_CS_fsm_state64) | (1'b1 == ap_CS_fsm_state63) | (1'b1 == ap_CS_fsm_state62) | (1'b1 == ap_CS_fsm_state61) | (1'b1 == ap_CS_fsm_state60) | (1'b1 == ap_CS_fsm_state59) | (1'b1 == ap_CS_fsm_state58) | (1'b1 == ap_CS_fsm_state57) | (1'b1 == ap_CS_fsm_state56) | (1'b1 == ap_CS_fsm_state55) | (1'b1 == ap_CS_fsm_state54) | (1'b1 == ap_CS_fsm_state53) | (1'b1 == ap_CS_fsm_state52) | (1'b1 == ap_CS_fsm_state51) | (1'b1 == ap_CS_fsm_state50) | (1'b1 == ap_CS_fsm_state49) | (1'b1 == ap_CS_fsm_state48) | (1'b1 == ap_CS_fsm_state47) | (1'b1 == ap_CS_fsm_state46) | (1'b1 == ap_CS_fsm_state45) | (1'b1 == ap_CS_fsm_state44) | (1'b1 == ap_CS_fsm_state43) | (1'b1 == ap_CS_fsm_state42) | (1'b1 == ap_CS_fsm_state41) | (1'b1 == ap_CS_fsm_state40) | (1'b1 == ap_CS_fsm_state39) | (1'b1 == ap_CS_fsm_state38) | (1'b1 == ap_CS_fsm_state37) | (1'b1 == ap_CS_fsm_state36) | (1'b1 == ap_CS_fsm_state35) | (1'b1 == ap_CS_fsm_state34) | (1'b1 == ap_CS_fsm_state33) | (1'b1 == ap_CS_fsm_state32) | (1'b1 == ap_CS_fsm_state31) | (1'b1 == ap_CS_fsm_state30) | (1'b1 == ap_CS_fsm_state29) | (1'b1 == ap_CS_fsm_state28) | (1'b1 == ap_CS_fsm_state27) | (1'b1 == ap_CS_fsm_state26) | (1'b1 == ap_CS_fsm_state25) | (1'b1 == ap_CS_fsm_state24) | (1'b1 == ap_CS_fsm_state23) | (1'b1 == ap_CS_fsm_state22) | (1'b1 == ap_CS_fsm_state21) | (1'b1 == ap_CS_fsm_state20) | (1'b1 == ap_CS_fsm_state19) | (1'b1 == ap_CS_fsm_state18) | (1'b1 == ap_CS_fsm_state17) | (1'b1 == ap_CS_fsm_state16) | (1'b1 == ap_CS_fsm_state15) | (1'b1 == ap_CS_fsm_state14) | (1'b1 == ap_CS_fsm_state13) | (1'b1 == ap_CS_fsm_state12) | (1'b1 == ap_CS_fsm_state11) | (1'b1 == ap_CS_fsm_state10) | (1'b1 == ap_CS_fsm_state9) | (1'b1 == ap_CS_fsm_state8) | (1'b1 == ap_CS_fsm_state7) | (1'b1 == ap_CS_fsm_state6) | (1'b1 == ap_CS_fsm_state5) | (1'b1 == ap_CS_fsm_state4) | (1'b1 == ap_CS_fsm_state3) | (1'b1 == ap_CS_fsm_state129) | (1'b1 == ap_CS_fsm_state128) | (1'b1 == ap_CS_fsm_state127) | (1'b1 == ap_CS_fsm_state126) | (1'b1 == ap_CS_fsm_state125) | (1'b1 == ap_CS_fsm_state124) | (1'b1 == ap_CS_fsm_state123) | (1'b1 == ap_CS_fsm_state122) | (1'b1 == ap_CS_fsm_state121) | (1'b1 == ap_CS_fsm_state120) | (1'b1 == ap_CS_fsm_state119) | (1'b1 == ap_CS_fsm_state118) | (1'b1 == ap_CS_fsm_state117) | (1'b1 == ap_CS_fsm_state116) | (1'b1 == ap_CS_fsm_state115) | (1'b1 == ap_CS_fsm_state114) | (1'b1 == ap_CS_fsm_state113) | (1'b1 == ap_CS_fsm_state112) | (1'b1 == ap_CS_fsm_state111) | (1'b1 == ap_CS_fsm_state110) | (1'b1 == ap_CS_fsm_state109) | (1'b1 == ap_CS_fsm_state108) | (1'b1 == ap_CS_fsm_state107) | (1'b1 == ap_CS_fsm_state106) | (1'b1 == ap_CS_fsm_state105) | (1'b1 == ap_CS_fsm_state104) | (1'b1 == ap_CS_fsm_state103) | (1'b1 == ap_CS_fsm_state102) | (1'b1 == ap_CS_fsm_state101) | (1'b1 == ap_CS_fsm_state100) | (1'b1 == ap_CS_fsm_state99) | (1'b1 == ap_CS_fsm_state98) | (1'b1 == ap_CS_fsm_state97) | (1'b1 == ap_CS_fsm_state96) | (1'b1 == ap_CS_fsm_state95) | (1'b1 == ap_CS_fsm_state94) | (1'b1 == ap_CS_fsm_state93) | (1'b1 == ap_CS_fsm_state92) | (1'b1 == ap_CS_fsm_state91) | (1'b1 == ap_CS_fsm_state90) | (1'b1 == ap_CS_fsm_state89) | (1'b1 == ap_CS_fsm_state88) | (1'b1 == ap_CS_fsm_state87) | (1'b1 == ap_CS_fsm_state86) | (1'b1 == ap_CS_fsm_state85) | (1'b1 == ap_CS_fsm_state84) | (1'b1 == ap_CS_fsm_state83) | (1'b1 == ap_CS_fsm_state82) | (1'b1 == ap_CS_fsm_state81) | (1'b1 == ap_CS_fsm_state80) | (1'b1 == ap_CS_fsm_state79) | (1'b1 == ap_CS_fsm_state78) | (1'b1 == ap_CS_fsm_state77) | (1'b1 == ap_CS_fsm_state76) | (1'b1 == ap_CS_fsm_state75) | (1'b1 == ap_CS_fsm_state74) | (1'b1 == ap_CS_fsm_state73) | (1'b1 == ap_CS_fsm_state72) | (1'b1 == ap_CS_fsm_state71) | (1'b1 == ap_CS_fsm_state70) | (1'b1 == ap_CS_fsm_state69) | (1'b1 == ap_CS_fsm_state68) | ((icmp_ln882_fu_2794_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state2)))) begin
        frame_buffer_V_we1 = 1'b1;
    end else begin
        frame_buffer_V_we1 = 1'b0;
    end
end

always @ (*) begin
    case (ap_CS_fsm)
        ap_ST_fsm_state1 : begin
            if ((~((1'b0 == Input_1_empty_n) | (ap_start == 1'b0)) & (icmp_ln874_fu_2788_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state1))) begin
                ap_NS_fsm = ap_ST_fsm_state2;
            end else if ((~((1'b0 == Input_1_empty_n) | (ap_start == 1'b0)) & (icmp_ln874_fu_2788_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state1))) begin
                ap_NS_fsm = ap_ST_fsm_state130;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state1;
            end
        end
        ap_ST_fsm_state2 : begin
            if (((icmp_ln882_fu_2794_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state2))) begin
                ap_NS_fsm = ap_ST_fsm_state3;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state130;
            end
        end
        ap_ST_fsm_state3 : begin
            ap_NS_fsm = ap_ST_fsm_state4;
        end
        ap_ST_fsm_state4 : begin
            ap_NS_fsm = ap_ST_fsm_state5;
        end
        ap_ST_fsm_state5 : begin
            ap_NS_fsm = ap_ST_fsm_state6;
        end
        ap_ST_fsm_state6 : begin
            ap_NS_fsm = ap_ST_fsm_state7;
        end
        ap_ST_fsm_state7 : begin
            ap_NS_fsm = ap_ST_fsm_state8;
        end
        ap_ST_fsm_state8 : begin
            ap_NS_fsm = ap_ST_fsm_state9;
        end
        ap_ST_fsm_state9 : begin
            ap_NS_fsm = ap_ST_fsm_state10;
        end
        ap_ST_fsm_state10 : begin
            ap_NS_fsm = ap_ST_fsm_state11;
        end
        ap_ST_fsm_state11 : begin
            ap_NS_fsm = ap_ST_fsm_state12;
        end
        ap_ST_fsm_state12 : begin
            ap_NS_fsm = ap_ST_fsm_state13;
        end
        ap_ST_fsm_state13 : begin
            ap_NS_fsm = ap_ST_fsm_state14;
        end
        ap_ST_fsm_state14 : begin
            ap_NS_fsm = ap_ST_fsm_state15;
        end
        ap_ST_fsm_state15 : begin
            ap_NS_fsm = ap_ST_fsm_state16;
        end
        ap_ST_fsm_state16 : begin
            ap_NS_fsm = ap_ST_fsm_state17;
        end
        ap_ST_fsm_state17 : begin
            ap_NS_fsm = ap_ST_fsm_state18;
        end
        ap_ST_fsm_state18 : begin
            ap_NS_fsm = ap_ST_fsm_state19;
        end
        ap_ST_fsm_state19 : begin
            ap_NS_fsm = ap_ST_fsm_state20;
        end
        ap_ST_fsm_state20 : begin
            ap_NS_fsm = ap_ST_fsm_state21;
        end
        ap_ST_fsm_state21 : begin
            ap_NS_fsm = ap_ST_fsm_state22;
        end
        ap_ST_fsm_state22 : begin
            ap_NS_fsm = ap_ST_fsm_state23;
        end
        ap_ST_fsm_state23 : begin
            ap_NS_fsm = ap_ST_fsm_state24;
        end
        ap_ST_fsm_state24 : begin
            ap_NS_fsm = ap_ST_fsm_state25;
        end
        ap_ST_fsm_state25 : begin
            ap_NS_fsm = ap_ST_fsm_state26;
        end
        ap_ST_fsm_state26 : begin
            ap_NS_fsm = ap_ST_fsm_state27;
        end
        ap_ST_fsm_state27 : begin
            ap_NS_fsm = ap_ST_fsm_state28;
        end
        ap_ST_fsm_state28 : begin
            ap_NS_fsm = ap_ST_fsm_state29;
        end
        ap_ST_fsm_state29 : begin
            ap_NS_fsm = ap_ST_fsm_state30;
        end
        ap_ST_fsm_state30 : begin
            ap_NS_fsm = ap_ST_fsm_state31;
        end
        ap_ST_fsm_state31 : begin
            ap_NS_fsm = ap_ST_fsm_state32;
        end
        ap_ST_fsm_state32 : begin
            ap_NS_fsm = ap_ST_fsm_state33;
        end
        ap_ST_fsm_state33 : begin
            ap_NS_fsm = ap_ST_fsm_state34;
        end
        ap_ST_fsm_state34 : begin
            ap_NS_fsm = ap_ST_fsm_state35;
        end
        ap_ST_fsm_state35 : begin
            ap_NS_fsm = ap_ST_fsm_state36;
        end
        ap_ST_fsm_state36 : begin
            ap_NS_fsm = ap_ST_fsm_state37;
        end
        ap_ST_fsm_state37 : begin
            ap_NS_fsm = ap_ST_fsm_state38;
        end
        ap_ST_fsm_state38 : begin
            ap_NS_fsm = ap_ST_fsm_state39;
        end
        ap_ST_fsm_state39 : begin
            ap_NS_fsm = ap_ST_fsm_state40;
        end
        ap_ST_fsm_state40 : begin
            ap_NS_fsm = ap_ST_fsm_state41;
        end
        ap_ST_fsm_state41 : begin
            ap_NS_fsm = ap_ST_fsm_state42;
        end
        ap_ST_fsm_state42 : begin
            ap_NS_fsm = ap_ST_fsm_state43;
        end
        ap_ST_fsm_state43 : begin
            ap_NS_fsm = ap_ST_fsm_state44;
        end
        ap_ST_fsm_state44 : begin
            ap_NS_fsm = ap_ST_fsm_state45;
        end
        ap_ST_fsm_state45 : begin
            ap_NS_fsm = ap_ST_fsm_state46;
        end
        ap_ST_fsm_state46 : begin
            ap_NS_fsm = ap_ST_fsm_state47;
        end
        ap_ST_fsm_state47 : begin
            ap_NS_fsm = ap_ST_fsm_state48;
        end
        ap_ST_fsm_state48 : begin
            ap_NS_fsm = ap_ST_fsm_state49;
        end
        ap_ST_fsm_state49 : begin
            ap_NS_fsm = ap_ST_fsm_state50;
        end
        ap_ST_fsm_state50 : begin
            ap_NS_fsm = ap_ST_fsm_state51;
        end
        ap_ST_fsm_state51 : begin
            ap_NS_fsm = ap_ST_fsm_state52;
        end
        ap_ST_fsm_state52 : begin
            ap_NS_fsm = ap_ST_fsm_state53;
        end
        ap_ST_fsm_state53 : begin
            ap_NS_fsm = ap_ST_fsm_state54;
        end
        ap_ST_fsm_state54 : begin
            ap_NS_fsm = ap_ST_fsm_state55;
        end
        ap_ST_fsm_state55 : begin
            ap_NS_fsm = ap_ST_fsm_state56;
        end
        ap_ST_fsm_state56 : begin
            ap_NS_fsm = ap_ST_fsm_state57;
        end
        ap_ST_fsm_state57 : begin
            ap_NS_fsm = ap_ST_fsm_state58;
        end
        ap_ST_fsm_state58 : begin
            ap_NS_fsm = ap_ST_fsm_state59;
        end
        ap_ST_fsm_state59 : begin
            ap_NS_fsm = ap_ST_fsm_state60;
        end
        ap_ST_fsm_state60 : begin
            ap_NS_fsm = ap_ST_fsm_state61;
        end
        ap_ST_fsm_state61 : begin
            ap_NS_fsm = ap_ST_fsm_state62;
        end
        ap_ST_fsm_state62 : begin
            ap_NS_fsm = ap_ST_fsm_state63;
        end
        ap_ST_fsm_state63 : begin
            ap_NS_fsm = ap_ST_fsm_state64;
        end
        ap_ST_fsm_state64 : begin
            ap_NS_fsm = ap_ST_fsm_state65;
        end
        ap_ST_fsm_state65 : begin
            ap_NS_fsm = ap_ST_fsm_state66;
        end
        ap_ST_fsm_state66 : begin
            ap_NS_fsm = ap_ST_fsm_state67;
        end
        ap_ST_fsm_state67 : begin
            ap_NS_fsm = ap_ST_fsm_state68;
        end
        ap_ST_fsm_state68 : begin
            ap_NS_fsm = ap_ST_fsm_state69;
        end
        ap_ST_fsm_state69 : begin
            ap_NS_fsm = ap_ST_fsm_state70;
        end
        ap_ST_fsm_state70 : begin
            ap_NS_fsm = ap_ST_fsm_state71;
        end
        ap_ST_fsm_state71 : begin
            ap_NS_fsm = ap_ST_fsm_state72;
        end
        ap_ST_fsm_state72 : begin
            ap_NS_fsm = ap_ST_fsm_state73;
        end
        ap_ST_fsm_state73 : begin
            ap_NS_fsm = ap_ST_fsm_state74;
        end
        ap_ST_fsm_state74 : begin
            ap_NS_fsm = ap_ST_fsm_state75;
        end
        ap_ST_fsm_state75 : begin
            ap_NS_fsm = ap_ST_fsm_state76;
        end
        ap_ST_fsm_state76 : begin
            ap_NS_fsm = ap_ST_fsm_state77;
        end
        ap_ST_fsm_state77 : begin
            ap_NS_fsm = ap_ST_fsm_state78;
        end
        ap_ST_fsm_state78 : begin
            ap_NS_fsm = ap_ST_fsm_state79;
        end
        ap_ST_fsm_state79 : begin
            ap_NS_fsm = ap_ST_fsm_state80;
        end
        ap_ST_fsm_state80 : begin
            ap_NS_fsm = ap_ST_fsm_state81;
        end
        ap_ST_fsm_state81 : begin
            ap_NS_fsm = ap_ST_fsm_state82;
        end
        ap_ST_fsm_state82 : begin
            ap_NS_fsm = ap_ST_fsm_state83;
        end
        ap_ST_fsm_state83 : begin
            ap_NS_fsm = ap_ST_fsm_state84;
        end
        ap_ST_fsm_state84 : begin
            ap_NS_fsm = ap_ST_fsm_state85;
        end
        ap_ST_fsm_state85 : begin
            ap_NS_fsm = ap_ST_fsm_state86;
        end
        ap_ST_fsm_state86 : begin
            ap_NS_fsm = ap_ST_fsm_state87;
        end
        ap_ST_fsm_state87 : begin
            ap_NS_fsm = ap_ST_fsm_state88;
        end
        ap_ST_fsm_state88 : begin
            ap_NS_fsm = ap_ST_fsm_state89;
        end
        ap_ST_fsm_state89 : begin
            ap_NS_fsm = ap_ST_fsm_state90;
        end
        ap_ST_fsm_state90 : begin
            ap_NS_fsm = ap_ST_fsm_state91;
        end
        ap_ST_fsm_state91 : begin
            ap_NS_fsm = ap_ST_fsm_state92;
        end
        ap_ST_fsm_state92 : begin
            ap_NS_fsm = ap_ST_fsm_state93;
        end
        ap_ST_fsm_state93 : begin
            ap_NS_fsm = ap_ST_fsm_state94;
        end
        ap_ST_fsm_state94 : begin
            ap_NS_fsm = ap_ST_fsm_state95;
        end
        ap_ST_fsm_state95 : begin
            ap_NS_fsm = ap_ST_fsm_state96;
        end
        ap_ST_fsm_state96 : begin
            ap_NS_fsm = ap_ST_fsm_state97;
        end
        ap_ST_fsm_state97 : begin
            ap_NS_fsm = ap_ST_fsm_state98;
        end
        ap_ST_fsm_state98 : begin
            ap_NS_fsm = ap_ST_fsm_state99;
        end
        ap_ST_fsm_state99 : begin
            ap_NS_fsm = ap_ST_fsm_state100;
        end
        ap_ST_fsm_state100 : begin
            ap_NS_fsm = ap_ST_fsm_state101;
        end
        ap_ST_fsm_state101 : begin
            ap_NS_fsm = ap_ST_fsm_state102;
        end
        ap_ST_fsm_state102 : begin
            ap_NS_fsm = ap_ST_fsm_state103;
        end
        ap_ST_fsm_state103 : begin
            ap_NS_fsm = ap_ST_fsm_state104;
        end
        ap_ST_fsm_state104 : begin
            ap_NS_fsm = ap_ST_fsm_state105;
        end
        ap_ST_fsm_state105 : begin
            ap_NS_fsm = ap_ST_fsm_state106;
        end
        ap_ST_fsm_state106 : begin
            ap_NS_fsm = ap_ST_fsm_state107;
        end
        ap_ST_fsm_state107 : begin
            ap_NS_fsm = ap_ST_fsm_state108;
        end
        ap_ST_fsm_state108 : begin
            ap_NS_fsm = ap_ST_fsm_state109;
        end
        ap_ST_fsm_state109 : begin
            ap_NS_fsm = ap_ST_fsm_state110;
        end
        ap_ST_fsm_state110 : begin
            ap_NS_fsm = ap_ST_fsm_state111;
        end
        ap_ST_fsm_state111 : begin
            ap_NS_fsm = ap_ST_fsm_state112;
        end
        ap_ST_fsm_state112 : begin
            ap_NS_fsm = ap_ST_fsm_state113;
        end
        ap_ST_fsm_state113 : begin
            ap_NS_fsm = ap_ST_fsm_state114;
        end
        ap_ST_fsm_state114 : begin
            ap_NS_fsm = ap_ST_fsm_state115;
        end
        ap_ST_fsm_state115 : begin
            ap_NS_fsm = ap_ST_fsm_state116;
        end
        ap_ST_fsm_state116 : begin
            ap_NS_fsm = ap_ST_fsm_state117;
        end
        ap_ST_fsm_state117 : begin
            ap_NS_fsm = ap_ST_fsm_state118;
        end
        ap_ST_fsm_state118 : begin
            ap_NS_fsm = ap_ST_fsm_state119;
        end
        ap_ST_fsm_state119 : begin
            ap_NS_fsm = ap_ST_fsm_state120;
        end
        ap_ST_fsm_state120 : begin
            ap_NS_fsm = ap_ST_fsm_state121;
        end
        ap_ST_fsm_state121 : begin
            ap_NS_fsm = ap_ST_fsm_state122;
        end
        ap_ST_fsm_state122 : begin
            ap_NS_fsm = ap_ST_fsm_state123;
        end
        ap_ST_fsm_state123 : begin
            ap_NS_fsm = ap_ST_fsm_state124;
        end
        ap_ST_fsm_state124 : begin
            ap_NS_fsm = ap_ST_fsm_state125;
        end
        ap_ST_fsm_state125 : begin
            ap_NS_fsm = ap_ST_fsm_state126;
        end
        ap_ST_fsm_state126 : begin
            ap_NS_fsm = ap_ST_fsm_state127;
        end
        ap_ST_fsm_state127 : begin
            ap_NS_fsm = ap_ST_fsm_state128;
        end
        ap_ST_fsm_state128 : begin
            ap_NS_fsm = ap_ST_fsm_state129;
        end
        ap_ST_fsm_state129 : begin
            ap_NS_fsm = ap_ST_fsm_state2;
        end
        ap_ST_fsm_state130 : begin
            ap_NS_fsm = ap_ST_fsm_pp1_stage0;
        end
        ap_ST_fsm_pp1_stage0 : begin
            if (~((ap_enable_reg_pp1_iter0 == 1'b1) & (icmp_ln515_fu_6393_p2 == 1'd1) & (1'b0 == ap_block_pp1_stage0_subdone))) begin
                ap_NS_fsm = ap_ST_fsm_pp1_stage0;
            end else if (((ap_enable_reg_pp1_iter0 == 1'b1) & (icmp_ln515_fu_6393_p2 == 1'd1) & (1'b0 == ap_block_pp1_stage0_subdone))) begin
                ap_NS_fsm = ap_ST_fsm_state133;
            end else begin
                ap_NS_fsm = ap_ST_fsm_pp1_stage0;
            end
        end
        ap_ST_fsm_state133 : begin
            if (((icmp_ln874_2_fu_6447_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state133))) begin
                ap_NS_fsm = ap_ST_fsm_pp2_stage0;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state139;
            end
        end
        ap_ST_fsm_pp2_stage0 : begin
            if ((~((ap_enable_reg_pp2_iter0 == 1'b1) & (icmp_ln527_fu_6453_p2 == 1'd1) & (ap_enable_reg_pp2_iter1 == 1'b0) & (1'b0 == ap_block_pp2_stage0_subdone)) & (1'b0 == ap_block_pp2_stage0_subdone))) begin
                ap_NS_fsm = ap_ST_fsm_pp2_stage1;
            end else if (((ap_enable_reg_pp2_iter0 == 1'b1) & (icmp_ln527_fu_6453_p2 == 1'd1) & (ap_enable_reg_pp2_iter1 == 1'b0) & (1'b0 == ap_block_pp2_stage0_subdone))) begin
                ap_NS_fsm = ap_ST_fsm_state138;
            end else begin
                ap_NS_fsm = ap_ST_fsm_pp2_stage0;
            end
        end
        ap_ST_fsm_pp2_stage1 : begin
            if ((~((ap_enable_reg_pp2_iter0 == 1'b0) & (ap_enable_reg_pp2_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp2_stage1) & (1'b0 == ap_block_pp2_stage1_subdone)) & (1'b0 == ap_block_pp2_stage1_subdone))) begin
                ap_NS_fsm = ap_ST_fsm_pp2_stage0;
            end else if (((ap_enable_reg_pp2_iter0 == 1'b0) & (ap_enable_reg_pp2_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp2_stage1) & (1'b0 == ap_block_pp2_stage1_subdone))) begin
                ap_NS_fsm = ap_ST_fsm_state138;
            end else begin
                ap_NS_fsm = ap_ST_fsm_pp2_stage1;
            end
        end
        ap_ST_fsm_state138 : begin
            ap_NS_fsm = ap_ST_fsm_state139;
        end
        ap_ST_fsm_state139 : begin
            if (((1'b1 == ap_CS_fsm_state139) & (regslice_both_Output_1_V_U_apdone_blk == 1'b0))) begin
                ap_NS_fsm = ap_ST_fsm_state1;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state139;
            end
        end
        default : begin
            ap_NS_fsm = 'bx;
        end
    endcase
end

assign Output_1_V_TDATA_int_regslice = {{{{frame_buffer_V_q1}, {frame_buffer_V_load_2_reg_6955}}, {frame_buffer_V_load_1_reg_6950}}, {frame_buffer_V_q0}};

assign Output_1_V_TVALID = regslice_both_Output_1_V_U_vld_out;

assign add_ln215_fu_6551_p2 = (zext_ln215_fu_6548_p1 + tmp_514_cast_fu_6541_p3);

assign add_ln527_1_fu_6459_p2 = (ap_phi_mux_indvar_flatten_phi_fu_2744_p4 + 15'd1);

assign add_ln527_fu_6465_p2 = (9'd1 + ap_phi_mux_i_phi_fu_2755_p4);

assign add_ln528_fu_6579_p2 = (9'd4 + select_ln527_reg_6913);

assign add_ln695_6_fu_6442_p2 = (t_V_reg_6606 + 16'd1);

assign add_ln695_7_fu_6398_p2 = (empty_28_reg_2729 + 16'd1);

assign add_ln695_fu_2800_p2 = (empty_reg_2718 + 9'd1);

assign ap_CS_fsm_pp1_stage0 = ap_CS_fsm[32'd130];

assign ap_CS_fsm_pp2_stage0 = ap_CS_fsm[32'd132];

assign ap_CS_fsm_pp2_stage1 = ap_CS_fsm[32'd133];

assign ap_CS_fsm_state1 = ap_CS_fsm[32'd0];

assign ap_CS_fsm_state10 = ap_CS_fsm[32'd9];

assign ap_CS_fsm_state100 = ap_CS_fsm[32'd99];

assign ap_CS_fsm_state101 = ap_CS_fsm[32'd100];

assign ap_CS_fsm_state102 = ap_CS_fsm[32'd101];

assign ap_CS_fsm_state103 = ap_CS_fsm[32'd102];

assign ap_CS_fsm_state104 = ap_CS_fsm[32'd103];

assign ap_CS_fsm_state105 = ap_CS_fsm[32'd104];

assign ap_CS_fsm_state106 = ap_CS_fsm[32'd105];

assign ap_CS_fsm_state107 = ap_CS_fsm[32'd106];

assign ap_CS_fsm_state108 = ap_CS_fsm[32'd107];

assign ap_CS_fsm_state109 = ap_CS_fsm[32'd108];

assign ap_CS_fsm_state11 = ap_CS_fsm[32'd10];

assign ap_CS_fsm_state110 = ap_CS_fsm[32'd109];

assign ap_CS_fsm_state111 = ap_CS_fsm[32'd110];

assign ap_CS_fsm_state112 = ap_CS_fsm[32'd111];

assign ap_CS_fsm_state113 = ap_CS_fsm[32'd112];

assign ap_CS_fsm_state114 = ap_CS_fsm[32'd113];

assign ap_CS_fsm_state115 = ap_CS_fsm[32'd114];

assign ap_CS_fsm_state116 = ap_CS_fsm[32'd115];

assign ap_CS_fsm_state117 = ap_CS_fsm[32'd116];

assign ap_CS_fsm_state118 = ap_CS_fsm[32'd117];

assign ap_CS_fsm_state119 = ap_CS_fsm[32'd118];

assign ap_CS_fsm_state12 = ap_CS_fsm[32'd11];

assign ap_CS_fsm_state120 = ap_CS_fsm[32'd119];

assign ap_CS_fsm_state121 = ap_CS_fsm[32'd120];

assign ap_CS_fsm_state122 = ap_CS_fsm[32'd121];

assign ap_CS_fsm_state123 = ap_CS_fsm[32'd122];

assign ap_CS_fsm_state124 = ap_CS_fsm[32'd123];

assign ap_CS_fsm_state125 = ap_CS_fsm[32'd124];

assign ap_CS_fsm_state126 = ap_CS_fsm[32'd125];

assign ap_CS_fsm_state127 = ap_CS_fsm[32'd126];

assign ap_CS_fsm_state128 = ap_CS_fsm[32'd127];

assign ap_CS_fsm_state129 = ap_CS_fsm[32'd128];

assign ap_CS_fsm_state13 = ap_CS_fsm[32'd12];

assign ap_CS_fsm_state130 = ap_CS_fsm[32'd129];

assign ap_CS_fsm_state133 = ap_CS_fsm[32'd131];

assign ap_CS_fsm_state138 = ap_CS_fsm[32'd134];

assign ap_CS_fsm_state139 = ap_CS_fsm[32'd135];

assign ap_CS_fsm_state14 = ap_CS_fsm[32'd13];

assign ap_CS_fsm_state15 = ap_CS_fsm[32'd14];

assign ap_CS_fsm_state16 = ap_CS_fsm[32'd15];

assign ap_CS_fsm_state17 = ap_CS_fsm[32'd16];

assign ap_CS_fsm_state18 = ap_CS_fsm[32'd17];

assign ap_CS_fsm_state19 = ap_CS_fsm[32'd18];

assign ap_CS_fsm_state2 = ap_CS_fsm[32'd1];

assign ap_CS_fsm_state20 = ap_CS_fsm[32'd19];

assign ap_CS_fsm_state21 = ap_CS_fsm[32'd20];

assign ap_CS_fsm_state22 = ap_CS_fsm[32'd21];

assign ap_CS_fsm_state23 = ap_CS_fsm[32'd22];

assign ap_CS_fsm_state24 = ap_CS_fsm[32'd23];

assign ap_CS_fsm_state25 = ap_CS_fsm[32'd24];

assign ap_CS_fsm_state26 = ap_CS_fsm[32'd25];

assign ap_CS_fsm_state27 = ap_CS_fsm[32'd26];

assign ap_CS_fsm_state28 = ap_CS_fsm[32'd27];

assign ap_CS_fsm_state29 = ap_CS_fsm[32'd28];

assign ap_CS_fsm_state3 = ap_CS_fsm[32'd2];

assign ap_CS_fsm_state30 = ap_CS_fsm[32'd29];

assign ap_CS_fsm_state31 = ap_CS_fsm[32'd30];

assign ap_CS_fsm_state32 = ap_CS_fsm[32'd31];

assign ap_CS_fsm_state33 = ap_CS_fsm[32'd32];

assign ap_CS_fsm_state34 = ap_CS_fsm[32'd33];

assign ap_CS_fsm_state35 = ap_CS_fsm[32'd34];

assign ap_CS_fsm_state36 = ap_CS_fsm[32'd35];

assign ap_CS_fsm_state37 = ap_CS_fsm[32'd36];

assign ap_CS_fsm_state38 = ap_CS_fsm[32'd37];

assign ap_CS_fsm_state39 = ap_CS_fsm[32'd38];

assign ap_CS_fsm_state4 = ap_CS_fsm[32'd3];

assign ap_CS_fsm_state40 = ap_CS_fsm[32'd39];

assign ap_CS_fsm_state41 = ap_CS_fsm[32'd40];

assign ap_CS_fsm_state42 = ap_CS_fsm[32'd41];

assign ap_CS_fsm_state43 = ap_CS_fsm[32'd42];

assign ap_CS_fsm_state44 = ap_CS_fsm[32'd43];

assign ap_CS_fsm_state45 = ap_CS_fsm[32'd44];

assign ap_CS_fsm_state46 = ap_CS_fsm[32'd45];

assign ap_CS_fsm_state47 = ap_CS_fsm[32'd46];

assign ap_CS_fsm_state48 = ap_CS_fsm[32'd47];

assign ap_CS_fsm_state49 = ap_CS_fsm[32'd48];

assign ap_CS_fsm_state5 = ap_CS_fsm[32'd4];

assign ap_CS_fsm_state50 = ap_CS_fsm[32'd49];

assign ap_CS_fsm_state51 = ap_CS_fsm[32'd50];

assign ap_CS_fsm_state52 = ap_CS_fsm[32'd51];

assign ap_CS_fsm_state53 = ap_CS_fsm[32'd52];

assign ap_CS_fsm_state54 = ap_CS_fsm[32'd53];

assign ap_CS_fsm_state55 = ap_CS_fsm[32'd54];

assign ap_CS_fsm_state56 = ap_CS_fsm[32'd55];

assign ap_CS_fsm_state57 = ap_CS_fsm[32'd56];

assign ap_CS_fsm_state58 = ap_CS_fsm[32'd57];

assign ap_CS_fsm_state59 = ap_CS_fsm[32'd58];

assign ap_CS_fsm_state6 = ap_CS_fsm[32'd5];

assign ap_CS_fsm_state60 = ap_CS_fsm[32'd59];

assign ap_CS_fsm_state61 = ap_CS_fsm[32'd60];

assign ap_CS_fsm_state62 = ap_CS_fsm[32'd61];

assign ap_CS_fsm_state63 = ap_CS_fsm[32'd62];

assign ap_CS_fsm_state64 = ap_CS_fsm[32'd63];

assign ap_CS_fsm_state65 = ap_CS_fsm[32'd64];

assign ap_CS_fsm_state66 = ap_CS_fsm[32'd65];

assign ap_CS_fsm_state67 = ap_CS_fsm[32'd66];

assign ap_CS_fsm_state68 = ap_CS_fsm[32'd67];

assign ap_CS_fsm_state69 = ap_CS_fsm[32'd68];

assign ap_CS_fsm_state7 = ap_CS_fsm[32'd6];

assign ap_CS_fsm_state70 = ap_CS_fsm[32'd69];

assign ap_CS_fsm_state71 = ap_CS_fsm[32'd70];

assign ap_CS_fsm_state72 = ap_CS_fsm[32'd71];

assign ap_CS_fsm_state73 = ap_CS_fsm[32'd72];

assign ap_CS_fsm_state74 = ap_CS_fsm[32'd73];

assign ap_CS_fsm_state75 = ap_CS_fsm[32'd74];

assign ap_CS_fsm_state76 = ap_CS_fsm[32'd75];

assign ap_CS_fsm_state77 = ap_CS_fsm[32'd76];

assign ap_CS_fsm_state78 = ap_CS_fsm[32'd77];

assign ap_CS_fsm_state79 = ap_CS_fsm[32'd78];

assign ap_CS_fsm_state8 = ap_CS_fsm[32'd7];

assign ap_CS_fsm_state80 = ap_CS_fsm[32'd79];

assign ap_CS_fsm_state81 = ap_CS_fsm[32'd80];

assign ap_CS_fsm_state82 = ap_CS_fsm[32'd81];

assign ap_CS_fsm_state83 = ap_CS_fsm[32'd82];

assign ap_CS_fsm_state84 = ap_CS_fsm[32'd83];

assign ap_CS_fsm_state85 = ap_CS_fsm[32'd84];

assign ap_CS_fsm_state86 = ap_CS_fsm[32'd85];

assign ap_CS_fsm_state87 = ap_CS_fsm[32'd86];

assign ap_CS_fsm_state88 = ap_CS_fsm[32'd87];

assign ap_CS_fsm_state89 = ap_CS_fsm[32'd88];

assign ap_CS_fsm_state9 = ap_CS_fsm[32'd8];

assign ap_CS_fsm_state90 = ap_CS_fsm[32'd89];

assign ap_CS_fsm_state91 = ap_CS_fsm[32'd90];

assign ap_CS_fsm_state92 = ap_CS_fsm[32'd91];

assign ap_CS_fsm_state93 = ap_CS_fsm[32'd92];

assign ap_CS_fsm_state94 = ap_CS_fsm[32'd93];

assign ap_CS_fsm_state95 = ap_CS_fsm[32'd94];

assign ap_CS_fsm_state96 = ap_CS_fsm[32'd95];

assign ap_CS_fsm_state97 = ap_CS_fsm[32'd96];

assign ap_CS_fsm_state98 = ap_CS_fsm[32'd97];

assign ap_CS_fsm_state99 = ap_CS_fsm[32'd98];

assign ap_block_pp1_stage0 = ~(1'b1 == 1'b1);

always @ (*) begin
    ap_block_pp1_stage0_11001 = ((1'b0 == Input_1_empty_n) & (icmp_ln515_reg_6886 == 1'd0) & (ap_enable_reg_pp1_iter1 == 1'b1));
end

always @ (*) begin
    ap_block_pp1_stage0_subdone = ((1'b0 == Input_1_empty_n) & (icmp_ln515_reg_6886 == 1'd0) & (ap_enable_reg_pp1_iter1 == 1'b1));
end

assign ap_block_pp2_stage0 = ~(1'b1 == 1'b1);

assign ap_block_pp2_stage0_01001 = ~(1'b1 == 1'b1);

always @ (*) begin
    ap_block_pp2_stage0_11001 = ((ap_enable_reg_pp2_iter1 == 1'b1) & (1'b1 == ap_block_state136_io));
end

always @ (*) begin
    ap_block_pp2_stage0_subdone = ((ap_enable_reg_pp2_iter1 == 1'b1) & (1'b1 == ap_block_state136_io));
end

assign ap_block_pp2_stage1 = ~(1'b1 == 1'b1);

always @ (*) begin
    ap_block_pp2_stage1_11001 = ((ap_enable_reg_pp2_iter1 == 1'b1) & (1'b1 == ap_block_state137_io));
end

always @ (*) begin
    ap_block_pp2_stage1_subdone = ((ap_enable_reg_pp2_iter1 == 1'b1) & (1'b1 == ap_block_state137_io));
end

always @ (*) begin
    ap_block_state1 = ((1'b0 == Input_1_empty_n) | (ap_start == 1'b0));
end

assign ap_block_state131_pp1_stage0_iter0 = ~(1'b1 == 1'b1);

always @ (*) begin
    ap_block_state132_pp1_stage0_iter1 = ((1'b0 == Input_1_empty_n) & (icmp_ln515_reg_6886 == 1'd0));
end

assign ap_block_state134_pp2_stage0_iter0 = ~(1'b1 == 1'b1);

assign ap_block_state135_pp2_stage1_iter0 = ~(1'b1 == 1'b1);

always @ (*) begin
    ap_block_state136_io = ((1'b0 == Output_1_V_TREADY_int_regslice) & (icmp_ln527_reg_6904 == 1'd0));
end

assign ap_block_state136_pp2_stage0_iter1 = ~(1'b1 == 1'b1);

always @ (*) begin
    ap_block_state137_io = ((1'b0 == Output_1_V_TREADY_int_regslice) & (icmp_ln527_reg_6904_pp2_iter1_reg == 1'd0));
end

assign ap_block_state137_pp2_stage1_iter1 = ~(1'b1 == 1'b1);

assign ap_enable_pp1 = (ap_idle_pp1 ^ 1'b1);

assign ap_enable_pp2 = (ap_idle_pp2 ^ 1'b1);

assign empty_27_fu_6390_p1 = tmp_V_reg_6601[15:0];

assign icmp_ln515_fu_6393_p2 = ((empty_28_reg_2729 == empty_27_reg_6881) ? 1'b1 : 1'b0);

assign icmp_ln527_fu_6453_p2 = ((ap_phi_mux_indvar_flatten_phi_fu_2744_p4 == 15'd16384) ? 1'b1 : 1'b0);

assign icmp_ln874_2_fu_6447_p2 = ((add_ln695_6_fu_6442_p2 == 16'd3192) ? 1'b1 : 1'b0);

assign icmp_ln874_fu_2788_p2 = ((counter_1 == 16'd0) ? 1'b1 : 1'b0);

assign icmp_ln882_fu_2794_p2 = ((empty_reg_2718 == 9'd256) ? 1'b1 : 1'b0);

assign or_ln324_255_fu_2834_p2 = (tmp_reg_6623 | 17'd2);

assign or_ln324_256_fu_2848_p2 = (tmp_reg_6623 | 17'd3);

assign or_ln324_257_fu_2862_p2 = (tmp_reg_6623 | 17'd4);

assign or_ln324_258_fu_2876_p2 = (tmp_reg_6623 | 17'd5);

assign or_ln324_259_fu_2890_p2 = (tmp_reg_6623 | 17'd6);

assign or_ln324_260_fu_2904_p2 = (tmp_reg_6623 | 17'd7);

assign or_ln324_261_fu_2918_p2 = (tmp_reg_6623 | 17'd8);

assign or_ln324_262_fu_2932_p2 = (tmp_reg_6623 | 17'd9);

assign or_ln324_263_fu_2946_p2 = (tmp_reg_6623 | 17'd10);

assign or_ln324_264_fu_2960_p2 = (tmp_reg_6623 | 17'd11);

assign or_ln324_265_fu_2974_p2 = (tmp_reg_6623 | 17'd12);

assign or_ln324_266_fu_2988_p2 = (tmp_reg_6623 | 17'd13);

assign or_ln324_267_fu_3002_p2 = (tmp_reg_6623 | 17'd14);

assign or_ln324_268_fu_3016_p2 = (tmp_reg_6623 | 17'd15);

assign or_ln324_269_fu_3030_p2 = (tmp_reg_6623 | 17'd16);

assign or_ln324_270_fu_3044_p2 = (tmp_reg_6623 | 17'd17);

assign or_ln324_271_fu_3058_p2 = (tmp_reg_6623 | 17'd18);

assign or_ln324_272_fu_3072_p2 = (tmp_reg_6623 | 17'd19);

assign or_ln324_273_fu_3086_p2 = (tmp_reg_6623 | 17'd20);

assign or_ln324_274_fu_3100_p2 = (tmp_reg_6623 | 17'd21);

assign or_ln324_275_fu_3114_p2 = (tmp_reg_6623 | 17'd22);

assign or_ln324_276_fu_3128_p2 = (tmp_reg_6623 | 17'd23);

assign or_ln324_277_fu_3142_p2 = (tmp_reg_6623 | 17'd24);

assign or_ln324_278_fu_3156_p2 = (tmp_reg_6623 | 17'd25);

assign or_ln324_279_fu_3170_p2 = (tmp_reg_6623 | 17'd26);

assign or_ln324_280_fu_3184_p2 = (tmp_reg_6623 | 17'd27);

assign or_ln324_281_fu_3198_p2 = (tmp_reg_6623 | 17'd28);

assign or_ln324_282_fu_3212_p2 = (tmp_reg_6623 | 17'd29);

assign or_ln324_283_fu_3226_p2 = (tmp_reg_6623 | 17'd30);

assign or_ln324_284_fu_3240_p2 = (tmp_reg_6623 | 17'd31);

assign or_ln324_285_fu_3254_p2 = (tmp_reg_6623 | 17'd32);

assign or_ln324_286_fu_3268_p2 = (tmp_reg_6623 | 17'd33);

assign or_ln324_287_fu_3282_p2 = (tmp_reg_6623 | 17'd34);

assign or_ln324_288_fu_3296_p2 = (tmp_reg_6623 | 17'd35);

assign or_ln324_289_fu_3310_p2 = (tmp_reg_6623 | 17'd36);

assign or_ln324_290_fu_3324_p2 = (tmp_reg_6623 | 17'd37);

assign or_ln324_291_fu_3338_p2 = (tmp_reg_6623 | 17'd38);

assign or_ln324_292_fu_3352_p2 = (tmp_reg_6623 | 17'd39);

assign or_ln324_293_fu_3366_p2 = (tmp_reg_6623 | 17'd40);

assign or_ln324_294_fu_3380_p2 = (tmp_reg_6623 | 17'd41);

assign or_ln324_295_fu_3394_p2 = (tmp_reg_6623 | 17'd42);

assign or_ln324_296_fu_3408_p2 = (tmp_reg_6623 | 17'd43);

assign or_ln324_297_fu_3422_p2 = (tmp_reg_6623 | 17'd44);

assign or_ln324_298_fu_3436_p2 = (tmp_reg_6623 | 17'd45);

assign or_ln324_299_fu_3450_p2 = (tmp_reg_6623 | 17'd46);

assign or_ln324_300_fu_3464_p2 = (tmp_reg_6623 | 17'd47);

assign or_ln324_301_fu_3478_p2 = (tmp_reg_6623 | 17'd48);

assign or_ln324_302_fu_3492_p2 = (tmp_reg_6623 | 17'd49);

assign or_ln324_303_fu_3506_p2 = (tmp_reg_6623 | 17'd50);

assign or_ln324_304_fu_3520_p2 = (tmp_reg_6623 | 17'd51);

assign or_ln324_305_fu_3534_p2 = (tmp_reg_6623 | 17'd52);

assign or_ln324_306_fu_3548_p2 = (tmp_reg_6623 | 17'd53);

assign or_ln324_307_fu_3562_p2 = (tmp_reg_6623 | 17'd54);

assign or_ln324_308_fu_3576_p2 = (tmp_reg_6623 | 17'd55);

assign or_ln324_309_fu_3590_p2 = (tmp_reg_6623 | 17'd56);

assign or_ln324_310_fu_3604_p2 = (tmp_reg_6623 | 17'd57);

assign or_ln324_311_fu_3618_p2 = (tmp_reg_6623 | 17'd58);

assign or_ln324_312_fu_3632_p2 = (tmp_reg_6623 | 17'd59);

assign or_ln324_313_fu_3646_p2 = (tmp_reg_6623 | 17'd60);

assign or_ln324_314_fu_3660_p2 = (tmp_reg_6623 | 17'd61);

assign or_ln324_315_fu_3674_p2 = (tmp_reg_6623 | 17'd62);

assign or_ln324_316_fu_3688_p2 = (tmp_reg_6623 | 17'd63);

assign or_ln324_317_fu_3702_p2 = (tmp_reg_6623 | 17'd64);

assign or_ln324_318_fu_3716_p2 = (tmp_reg_6623 | 17'd65);

assign or_ln324_319_fu_3730_p2 = (tmp_reg_6623 | 17'd66);

assign or_ln324_320_fu_3744_p2 = (tmp_reg_6623 | 17'd67);

assign or_ln324_321_fu_3758_p2 = (tmp_reg_6623 | 17'd68);

assign or_ln324_322_fu_3772_p2 = (tmp_reg_6623 | 17'd69);

assign or_ln324_323_fu_3786_p2 = (tmp_reg_6623 | 17'd70);

assign or_ln324_324_fu_3800_p2 = (tmp_reg_6623 | 17'd71);

assign or_ln324_325_fu_3814_p2 = (tmp_reg_6623 | 17'd72);

assign or_ln324_326_fu_3828_p2 = (tmp_reg_6623 | 17'd73);

assign or_ln324_327_fu_3842_p2 = (tmp_reg_6623 | 17'd74);

assign or_ln324_328_fu_3856_p2 = (tmp_reg_6623 | 17'd75);

assign or_ln324_329_fu_3870_p2 = (tmp_reg_6623 | 17'd76);

assign or_ln324_330_fu_3884_p2 = (tmp_reg_6623 | 17'd77);

assign or_ln324_331_fu_3898_p2 = (tmp_reg_6623 | 17'd78);

assign or_ln324_332_fu_3912_p2 = (tmp_reg_6623 | 17'd79);

assign or_ln324_333_fu_3926_p2 = (tmp_reg_6623 | 17'd80);

assign or_ln324_334_fu_3940_p2 = (tmp_reg_6623 | 17'd81);

assign or_ln324_335_fu_3954_p2 = (tmp_reg_6623 | 17'd82);

assign or_ln324_336_fu_3968_p2 = (tmp_reg_6623 | 17'd83);

assign or_ln324_337_fu_3982_p2 = (tmp_reg_6623 | 17'd84);

assign or_ln324_338_fu_3996_p2 = (tmp_reg_6623 | 17'd85);

assign or_ln324_339_fu_4010_p2 = (tmp_reg_6623 | 17'd86);

assign or_ln324_340_fu_4024_p2 = (tmp_reg_6623 | 17'd87);

assign or_ln324_341_fu_4038_p2 = (tmp_reg_6623 | 17'd88);

assign or_ln324_342_fu_4052_p2 = (tmp_reg_6623 | 17'd89);

assign or_ln324_343_fu_4066_p2 = (tmp_reg_6623 | 17'd90);

assign or_ln324_344_fu_4080_p2 = (tmp_reg_6623 | 17'd91);

assign or_ln324_345_fu_4094_p2 = (tmp_reg_6623 | 17'd92);

assign or_ln324_346_fu_4108_p2 = (tmp_reg_6623 | 17'd93);

assign or_ln324_347_fu_4122_p2 = (tmp_reg_6623 | 17'd94);

assign or_ln324_348_fu_4136_p2 = (tmp_reg_6623 | 17'd95);

assign or_ln324_349_fu_4150_p2 = (tmp_reg_6623 | 17'd96);

assign or_ln324_350_fu_4164_p2 = (tmp_reg_6623 | 17'd97);

assign or_ln324_351_fu_4178_p2 = (tmp_reg_6623 | 17'd98);

assign or_ln324_352_fu_4192_p2 = (tmp_reg_6623 | 17'd99);

assign or_ln324_353_fu_4206_p2 = (tmp_reg_6623 | 17'd100);

assign or_ln324_354_fu_4220_p2 = (tmp_reg_6623 | 17'd101);

assign or_ln324_355_fu_4234_p2 = (tmp_reg_6623 | 17'd102);

assign or_ln324_356_fu_4248_p2 = (tmp_reg_6623 | 17'd103);

assign or_ln324_357_fu_4262_p2 = (tmp_reg_6623 | 17'd104);

assign or_ln324_358_fu_4276_p2 = (tmp_reg_6623 | 17'd105);

assign or_ln324_359_fu_4290_p2 = (tmp_reg_6623 | 17'd106);

assign or_ln324_360_fu_4304_p2 = (tmp_reg_6623 | 17'd107);

assign or_ln324_361_fu_4318_p2 = (tmp_reg_6623 | 17'd108);

assign or_ln324_362_fu_4332_p2 = (tmp_reg_6623 | 17'd109);

assign or_ln324_363_fu_4346_p2 = (tmp_reg_6623 | 17'd110);

assign or_ln324_364_fu_4360_p2 = (tmp_reg_6623 | 17'd111);

assign or_ln324_365_fu_4374_p2 = (tmp_reg_6623 | 17'd112);

assign or_ln324_366_fu_4388_p2 = (tmp_reg_6623 | 17'd113);

assign or_ln324_367_fu_4402_p2 = (tmp_reg_6623 | 17'd114);

assign or_ln324_368_fu_4416_p2 = (tmp_reg_6623 | 17'd115);

assign or_ln324_369_fu_4430_p2 = (tmp_reg_6623 | 17'd116);

assign or_ln324_370_fu_4444_p2 = (tmp_reg_6623 | 17'd117);

assign or_ln324_371_fu_4458_p2 = (tmp_reg_6623 | 17'd118);

assign or_ln324_372_fu_4472_p2 = (tmp_reg_6623 | 17'd119);

assign or_ln324_373_fu_4486_p2 = (tmp_reg_6623 | 17'd120);

assign or_ln324_374_fu_4500_p2 = (tmp_reg_6623 | 17'd121);

assign or_ln324_375_fu_4514_p2 = (tmp_reg_6623 | 17'd122);

assign or_ln324_376_fu_4528_p2 = (tmp_reg_6623 | 17'd123);

assign or_ln324_377_fu_4542_p2 = (tmp_reg_6623 | 17'd124);

assign or_ln324_378_fu_4556_p2 = (tmp_reg_6623 | 17'd125);

assign or_ln324_379_fu_4570_p2 = (tmp_reg_6623 | 17'd126);

assign or_ln324_380_fu_4584_p2 = (tmp_reg_6623 | 17'd127);

assign or_ln324_381_fu_4598_p2 = (tmp_reg_6623 | 17'd128);

assign or_ln324_382_fu_4612_p2 = (tmp_reg_6623 | 17'd129);

assign or_ln324_383_fu_4626_p2 = (tmp_reg_6623 | 17'd130);

assign or_ln324_384_fu_4640_p2 = (tmp_reg_6623 | 17'd131);

assign or_ln324_385_fu_4654_p2 = (tmp_reg_6623 | 17'd132);

assign or_ln324_386_fu_4668_p2 = (tmp_reg_6623 | 17'd133);

assign or_ln324_387_fu_4682_p2 = (tmp_reg_6623 | 17'd134);

assign or_ln324_388_fu_4696_p2 = (tmp_reg_6623 | 17'd135);

assign or_ln324_389_fu_4710_p2 = (tmp_reg_6623 | 17'd136);

assign or_ln324_390_fu_4724_p2 = (tmp_reg_6623 | 17'd137);

assign or_ln324_391_fu_4738_p2 = (tmp_reg_6623 | 17'd138);

assign or_ln324_392_fu_4752_p2 = (tmp_reg_6623 | 17'd139);

assign or_ln324_393_fu_4766_p2 = (tmp_reg_6623 | 17'd140);

assign or_ln324_394_fu_4780_p2 = (tmp_reg_6623 | 17'd141);

assign or_ln324_395_fu_4794_p2 = (tmp_reg_6623 | 17'd142);

assign or_ln324_396_fu_4808_p2 = (tmp_reg_6623 | 17'd143);

assign or_ln324_397_fu_4822_p2 = (tmp_reg_6623 | 17'd144);

assign or_ln324_398_fu_4836_p2 = (tmp_reg_6623 | 17'd145);

assign or_ln324_399_fu_4850_p2 = (tmp_reg_6623 | 17'd146);

assign or_ln324_400_fu_4864_p2 = (tmp_reg_6623 | 17'd147);

assign or_ln324_401_fu_4878_p2 = (tmp_reg_6623 | 17'd148);

assign or_ln324_402_fu_4892_p2 = (tmp_reg_6623 | 17'd149);

assign or_ln324_403_fu_4906_p2 = (tmp_reg_6623 | 17'd150);

assign or_ln324_404_fu_4920_p2 = (tmp_reg_6623 | 17'd151);

assign or_ln324_405_fu_4934_p2 = (tmp_reg_6623 | 17'd152);

assign or_ln324_406_fu_4948_p2 = (tmp_reg_6623 | 17'd153);

assign or_ln324_407_fu_4962_p2 = (tmp_reg_6623 | 17'd154);

assign or_ln324_408_fu_4976_p2 = (tmp_reg_6623 | 17'd155);

assign or_ln324_409_fu_4990_p2 = (tmp_reg_6623 | 17'd156);

assign or_ln324_410_fu_5004_p2 = (tmp_reg_6623 | 17'd157);

assign or_ln324_411_fu_5018_p2 = (tmp_reg_6623 | 17'd158);

assign or_ln324_412_fu_5032_p2 = (tmp_reg_6623 | 17'd159);

assign or_ln324_413_fu_5046_p2 = (tmp_reg_6623 | 17'd160);

assign or_ln324_414_fu_5060_p2 = (tmp_reg_6623 | 17'd161);

assign or_ln324_415_fu_5074_p2 = (tmp_reg_6623 | 17'd162);

assign or_ln324_416_fu_5088_p2 = (tmp_reg_6623 | 17'd163);

assign or_ln324_417_fu_5102_p2 = (tmp_reg_6623 | 17'd164);

assign or_ln324_418_fu_5116_p2 = (tmp_reg_6623 | 17'd165);

assign or_ln324_419_fu_5130_p2 = (tmp_reg_6623 | 17'd166);

assign or_ln324_420_fu_5144_p2 = (tmp_reg_6623 | 17'd167);

assign or_ln324_421_fu_5158_p2 = (tmp_reg_6623 | 17'd168);

assign or_ln324_422_fu_5172_p2 = (tmp_reg_6623 | 17'd169);

assign or_ln324_423_fu_5186_p2 = (tmp_reg_6623 | 17'd170);

assign or_ln324_424_fu_5200_p2 = (tmp_reg_6623 | 17'd171);

assign or_ln324_425_fu_5214_p2 = (tmp_reg_6623 | 17'd172);

assign or_ln324_426_fu_5228_p2 = (tmp_reg_6623 | 17'd173);

assign or_ln324_427_fu_5242_p2 = (tmp_reg_6623 | 17'd174);

assign or_ln324_428_fu_5256_p2 = (tmp_reg_6623 | 17'd175);

assign or_ln324_429_fu_5270_p2 = (tmp_reg_6623 | 17'd176);

assign or_ln324_430_fu_5284_p2 = (tmp_reg_6623 | 17'd177);

assign or_ln324_431_fu_5298_p2 = (tmp_reg_6623 | 17'd178);

assign or_ln324_432_fu_5312_p2 = (tmp_reg_6623 | 17'd179);

assign or_ln324_433_fu_5326_p2 = (tmp_reg_6623 | 17'd180);

assign or_ln324_434_fu_5340_p2 = (tmp_reg_6623 | 17'd181);

assign or_ln324_435_fu_5354_p2 = (tmp_reg_6623 | 17'd182);

assign or_ln324_436_fu_5368_p2 = (tmp_reg_6623 | 17'd183);

assign or_ln324_437_fu_5382_p2 = (tmp_reg_6623 | 17'd184);

assign or_ln324_438_fu_5396_p2 = (tmp_reg_6623 | 17'd185);

assign or_ln324_439_fu_5410_p2 = (tmp_reg_6623 | 17'd186);

assign or_ln324_440_fu_5424_p2 = (tmp_reg_6623 | 17'd187);

assign or_ln324_441_fu_5438_p2 = (tmp_reg_6623 | 17'd188);

assign or_ln324_442_fu_5452_p2 = (tmp_reg_6623 | 17'd189);

assign or_ln324_443_fu_5466_p2 = (tmp_reg_6623 | 17'd190);

assign or_ln324_444_fu_5480_p2 = (tmp_reg_6623 | 17'd191);

assign or_ln324_445_fu_5494_p2 = (tmp_reg_6623 | 17'd192);

assign or_ln324_446_fu_5508_p2 = (tmp_reg_6623 | 17'd193);

assign or_ln324_447_fu_5522_p2 = (tmp_reg_6623 | 17'd194);

assign or_ln324_448_fu_5536_p2 = (tmp_reg_6623 | 17'd195);

assign or_ln324_449_fu_5550_p2 = (tmp_reg_6623 | 17'd196);

assign or_ln324_450_fu_5564_p2 = (tmp_reg_6623 | 17'd197);

assign or_ln324_451_fu_5578_p2 = (tmp_reg_6623 | 17'd198);

assign or_ln324_452_fu_5592_p2 = (tmp_reg_6623 | 17'd199);

assign or_ln324_453_fu_5606_p2 = (tmp_reg_6623 | 17'd200);

assign or_ln324_454_fu_5620_p2 = (tmp_reg_6623 | 17'd201);

assign or_ln324_455_fu_5634_p2 = (tmp_reg_6623 | 17'd202);

assign or_ln324_456_fu_5648_p2 = (tmp_reg_6623 | 17'd203);

assign or_ln324_457_fu_5662_p2 = (tmp_reg_6623 | 17'd204);

assign or_ln324_458_fu_5676_p2 = (tmp_reg_6623 | 17'd205);

assign or_ln324_459_fu_5690_p2 = (tmp_reg_6623 | 17'd206);

assign or_ln324_460_fu_5704_p2 = (tmp_reg_6623 | 17'd207);

assign or_ln324_461_fu_5718_p2 = (tmp_reg_6623 | 17'd208);

assign or_ln324_462_fu_5732_p2 = (tmp_reg_6623 | 17'd209);

assign or_ln324_463_fu_5746_p2 = (tmp_reg_6623 | 17'd210);

assign or_ln324_464_fu_5760_p2 = (tmp_reg_6623 | 17'd211);

assign or_ln324_465_fu_5774_p2 = (tmp_reg_6623 | 17'd212);

assign or_ln324_466_fu_5788_p2 = (tmp_reg_6623 | 17'd213);

assign or_ln324_467_fu_5802_p2 = (tmp_reg_6623 | 17'd214);

assign or_ln324_468_fu_5816_p2 = (tmp_reg_6623 | 17'd215);

assign or_ln324_469_fu_5830_p2 = (tmp_reg_6623 | 17'd216);

assign or_ln324_470_fu_5844_p2 = (tmp_reg_6623 | 17'd217);

assign or_ln324_471_fu_5858_p2 = (tmp_reg_6623 | 17'd218);

assign or_ln324_472_fu_5872_p2 = (tmp_reg_6623 | 17'd219);

assign or_ln324_473_fu_5886_p2 = (tmp_reg_6623 | 17'd220);

assign or_ln324_474_fu_5900_p2 = (tmp_reg_6623 | 17'd221);

assign or_ln324_475_fu_5914_p2 = (tmp_reg_6623 | 17'd222);

assign or_ln324_476_fu_5928_p2 = (tmp_reg_6623 | 17'd223);

assign or_ln324_477_fu_5942_p2 = (tmp_reg_6623 | 17'd224);

assign or_ln324_478_fu_5956_p2 = (tmp_reg_6623 | 17'd225);

assign or_ln324_479_fu_5970_p2 = (tmp_reg_6623 | 17'd226);

assign or_ln324_480_fu_5984_p2 = (tmp_reg_6623 | 17'd227);

assign or_ln324_481_fu_5998_p2 = (tmp_reg_6623 | 17'd228);

assign or_ln324_482_fu_6012_p2 = (tmp_reg_6623 | 17'd229);

assign or_ln324_483_fu_6026_p2 = (tmp_reg_6623 | 17'd230);

assign or_ln324_484_fu_6040_p2 = (tmp_reg_6623 | 17'd231);

assign or_ln324_485_fu_6054_p2 = (tmp_reg_6623 | 17'd232);

assign or_ln324_486_fu_6068_p2 = (tmp_reg_6623 | 17'd233);

assign or_ln324_487_fu_6082_p2 = (tmp_reg_6623 | 17'd234);

assign or_ln324_488_fu_6096_p2 = (tmp_reg_6623 | 17'd235);

assign or_ln324_489_fu_6110_p2 = (tmp_reg_6623 | 17'd236);

assign or_ln324_490_fu_6124_p2 = (tmp_reg_6623 | 17'd237);

assign or_ln324_491_fu_6138_p2 = (tmp_reg_6623 | 17'd238);

assign or_ln324_492_fu_6152_p2 = (tmp_reg_6623 | 17'd239);

assign or_ln324_493_fu_6166_p2 = (tmp_reg_6623 | 17'd240);

assign or_ln324_494_fu_6180_p2 = (tmp_reg_6623 | 17'd241);

assign or_ln324_495_fu_6194_p2 = (tmp_reg_6623 | 17'd242);

assign or_ln324_496_fu_6208_p2 = (tmp_reg_6623 | 17'd243);

assign or_ln324_497_fu_6222_p2 = (tmp_reg_6623 | 17'd244);

assign or_ln324_498_fu_6236_p2 = (tmp_reg_6623 | 17'd245);

assign or_ln324_499_fu_6250_p2 = (tmp_reg_6623 | 17'd246);

assign or_ln324_500_fu_6264_p2 = (tmp_reg_6623 | 17'd247);

assign or_ln324_501_fu_6278_p2 = (tmp_reg_6623 | 17'd248);

assign or_ln324_502_fu_6292_p2 = (tmp_reg_6623 | 17'd249);

assign or_ln324_503_fu_6306_p2 = (tmp_reg_6623 | 17'd250);

assign or_ln324_504_fu_6320_p2 = (tmp_reg_6623 | 17'd251);

assign or_ln324_505_fu_6334_p2 = (tmp_reg_6623 | 17'd252);

assign or_ln324_506_fu_6348_p2 = (tmp_reg_6623 | 17'd253);

assign or_ln324_507_fu_6362_p2 = (tmp_reg_6623 | 17'd254);

assign or_ln324_508_fu_6376_p2 = (tmp_reg_6623 | 17'd255);

assign or_ln324_fu_2819_p2 = (tmp_fu_2806_p3 | 17'd1);

assign or_ln531_1_fu_6522_p2 = (trunc_ln528_fu_6499_p1 | 8'd2);

assign or_ln531_2_fu_6562_p2 = (trunc_ln528_reg_6930 | 8'd3);

assign or_ln531_fu_6503_p2 = (trunc_ln528_fu_6499_p1 | 8'd1);

assign p_Result_s_fu_6404_p4 = {{Input_1_dout[15:8]}};

assign select_ln527_1_fu_6487_p3 = ((tmp_5_fu_6471_p3[0:0] === 1'b1) ? add_ln527_fu_6465_p2 : ap_phi_mux_i_phi_fu_2755_p4);

assign select_ln527_fu_6479_p3 = ((tmp_5_fu_6471_p3[0:0] === 1'b1) ? 9'd0 : ap_phi_mux_j_phi_fu_2766_p4);

assign tmp_255_fu_2839_p3 = {{47'd0}, {or_ln324_255_fu_2834_p2}};

assign tmp_256_fu_2853_p3 = {{47'd0}, {or_ln324_256_fu_2848_p2}};

assign tmp_257_fu_2867_p3 = {{47'd0}, {or_ln324_257_fu_2862_p2}};

assign tmp_258_fu_2881_p3 = {{47'd0}, {or_ln324_258_fu_2876_p2}};

assign tmp_259_fu_2895_p3 = {{47'd0}, {or_ln324_259_fu_2890_p2}};

assign tmp_260_fu_2909_p3 = {{47'd0}, {or_ln324_260_fu_2904_p2}};

assign tmp_261_fu_2923_p3 = {{47'd0}, {or_ln324_261_fu_2918_p2}};

assign tmp_262_fu_2937_p3 = {{47'd0}, {or_ln324_262_fu_2932_p2}};

assign tmp_263_fu_2951_p3 = {{47'd0}, {or_ln324_263_fu_2946_p2}};

assign tmp_264_fu_2965_p3 = {{47'd0}, {or_ln324_264_fu_2960_p2}};

assign tmp_265_fu_2979_p3 = {{47'd0}, {or_ln324_265_fu_2974_p2}};

assign tmp_266_fu_2993_p3 = {{47'd0}, {or_ln324_266_fu_2988_p2}};

assign tmp_267_fu_3007_p3 = {{47'd0}, {or_ln324_267_fu_3002_p2}};

assign tmp_268_fu_3021_p3 = {{47'd0}, {or_ln324_268_fu_3016_p2}};

assign tmp_269_fu_3035_p3 = {{47'd0}, {or_ln324_269_fu_3030_p2}};

assign tmp_270_fu_3049_p3 = {{47'd0}, {or_ln324_270_fu_3044_p2}};

assign tmp_271_fu_3063_p3 = {{47'd0}, {or_ln324_271_fu_3058_p2}};

assign tmp_272_fu_3077_p3 = {{47'd0}, {or_ln324_272_fu_3072_p2}};

assign tmp_273_fu_3091_p3 = {{47'd0}, {or_ln324_273_fu_3086_p2}};

assign tmp_274_fu_3105_p3 = {{47'd0}, {or_ln324_274_fu_3100_p2}};

assign tmp_275_fu_3119_p3 = {{47'd0}, {or_ln324_275_fu_3114_p2}};

assign tmp_276_fu_3133_p3 = {{47'd0}, {or_ln324_276_fu_3128_p2}};

assign tmp_277_fu_3147_p3 = {{47'd0}, {or_ln324_277_fu_3142_p2}};

assign tmp_278_fu_3161_p3 = {{47'd0}, {or_ln324_278_fu_3156_p2}};

assign tmp_279_fu_3175_p3 = {{47'd0}, {or_ln324_279_fu_3170_p2}};

assign tmp_280_fu_3189_p3 = {{47'd0}, {or_ln324_280_fu_3184_p2}};

assign tmp_281_fu_3203_p3 = {{47'd0}, {or_ln324_281_fu_3198_p2}};

assign tmp_282_fu_3217_p3 = {{47'd0}, {or_ln324_282_fu_3212_p2}};

assign tmp_283_fu_3231_p3 = {{47'd0}, {or_ln324_283_fu_3226_p2}};

assign tmp_284_fu_3245_p3 = {{47'd0}, {or_ln324_284_fu_3240_p2}};

assign tmp_285_fu_3259_p3 = {{47'd0}, {or_ln324_285_fu_3254_p2}};

assign tmp_286_fu_3273_p3 = {{47'd0}, {or_ln324_286_fu_3268_p2}};

assign tmp_287_fu_3287_p3 = {{47'd0}, {or_ln324_287_fu_3282_p2}};

assign tmp_288_fu_3301_p3 = {{47'd0}, {or_ln324_288_fu_3296_p2}};

assign tmp_289_fu_3315_p3 = {{47'd0}, {or_ln324_289_fu_3310_p2}};

assign tmp_290_fu_3329_p3 = {{47'd0}, {or_ln324_290_fu_3324_p2}};

assign tmp_291_fu_3343_p3 = {{47'd0}, {or_ln324_291_fu_3338_p2}};

assign tmp_292_fu_3357_p3 = {{47'd0}, {or_ln324_292_fu_3352_p2}};

assign tmp_293_fu_3371_p3 = {{47'd0}, {or_ln324_293_fu_3366_p2}};

assign tmp_294_fu_3385_p3 = {{47'd0}, {or_ln324_294_fu_3380_p2}};

assign tmp_295_fu_3399_p3 = {{47'd0}, {or_ln324_295_fu_3394_p2}};

assign tmp_296_fu_3413_p3 = {{47'd0}, {or_ln324_296_fu_3408_p2}};

assign tmp_297_fu_3427_p3 = {{47'd0}, {or_ln324_297_fu_3422_p2}};

assign tmp_298_fu_3441_p3 = {{47'd0}, {or_ln324_298_fu_3436_p2}};

assign tmp_299_fu_3455_p3 = {{47'd0}, {or_ln324_299_fu_3450_p2}};

assign tmp_300_fu_3469_p3 = {{47'd0}, {or_ln324_300_fu_3464_p2}};

assign tmp_301_fu_3483_p3 = {{47'd0}, {or_ln324_301_fu_3478_p2}};

assign tmp_302_fu_3497_p3 = {{47'd0}, {or_ln324_302_fu_3492_p2}};

assign tmp_303_fu_3511_p3 = {{47'd0}, {or_ln324_303_fu_3506_p2}};

assign tmp_304_fu_3525_p3 = {{47'd0}, {or_ln324_304_fu_3520_p2}};

assign tmp_305_fu_3539_p3 = {{47'd0}, {or_ln324_305_fu_3534_p2}};

assign tmp_306_fu_3553_p3 = {{47'd0}, {or_ln324_306_fu_3548_p2}};

assign tmp_307_fu_3567_p3 = {{47'd0}, {or_ln324_307_fu_3562_p2}};

assign tmp_308_fu_3581_p3 = {{47'd0}, {or_ln324_308_fu_3576_p2}};

assign tmp_309_fu_3595_p3 = {{47'd0}, {or_ln324_309_fu_3590_p2}};

assign tmp_310_fu_3609_p3 = {{47'd0}, {or_ln324_310_fu_3604_p2}};

assign tmp_311_fu_3623_p3 = {{47'd0}, {or_ln324_311_fu_3618_p2}};

assign tmp_312_fu_3637_p3 = {{47'd0}, {or_ln324_312_fu_3632_p2}};

assign tmp_313_fu_3651_p3 = {{47'd0}, {or_ln324_313_fu_3646_p2}};

assign tmp_314_fu_3665_p3 = {{47'd0}, {or_ln324_314_fu_3660_p2}};

assign tmp_315_fu_3679_p3 = {{47'd0}, {or_ln324_315_fu_3674_p2}};

assign tmp_316_fu_3693_p3 = {{47'd0}, {or_ln324_316_fu_3688_p2}};

assign tmp_317_fu_3707_p3 = {{47'd0}, {or_ln324_317_fu_3702_p2}};

assign tmp_318_fu_3721_p3 = {{47'd0}, {or_ln324_318_fu_3716_p2}};

assign tmp_319_fu_3735_p3 = {{47'd0}, {or_ln324_319_fu_3730_p2}};

assign tmp_320_fu_3749_p3 = {{47'd0}, {or_ln324_320_fu_3744_p2}};

assign tmp_321_fu_3763_p3 = {{47'd0}, {or_ln324_321_fu_3758_p2}};

assign tmp_322_fu_3777_p3 = {{47'd0}, {or_ln324_322_fu_3772_p2}};

assign tmp_323_fu_3791_p3 = {{47'd0}, {or_ln324_323_fu_3786_p2}};

assign tmp_324_fu_3805_p3 = {{47'd0}, {or_ln324_324_fu_3800_p2}};

assign tmp_325_fu_3819_p3 = {{47'd0}, {or_ln324_325_fu_3814_p2}};

assign tmp_326_fu_3833_p3 = {{47'd0}, {or_ln324_326_fu_3828_p2}};

assign tmp_327_fu_3847_p3 = {{47'd0}, {or_ln324_327_fu_3842_p2}};

assign tmp_328_fu_3861_p3 = {{47'd0}, {or_ln324_328_fu_3856_p2}};

assign tmp_329_fu_3875_p3 = {{47'd0}, {or_ln324_329_fu_3870_p2}};

assign tmp_330_fu_3889_p3 = {{47'd0}, {or_ln324_330_fu_3884_p2}};

assign tmp_331_fu_3903_p3 = {{47'd0}, {or_ln324_331_fu_3898_p2}};

assign tmp_332_fu_3917_p3 = {{47'd0}, {or_ln324_332_fu_3912_p2}};

assign tmp_333_fu_3931_p3 = {{47'd0}, {or_ln324_333_fu_3926_p2}};

assign tmp_334_fu_3945_p3 = {{47'd0}, {or_ln324_334_fu_3940_p2}};

assign tmp_335_fu_3959_p3 = {{47'd0}, {or_ln324_335_fu_3954_p2}};

assign tmp_336_fu_3973_p3 = {{47'd0}, {or_ln324_336_fu_3968_p2}};

assign tmp_337_fu_3987_p3 = {{47'd0}, {or_ln324_337_fu_3982_p2}};

assign tmp_338_fu_4001_p3 = {{47'd0}, {or_ln324_338_fu_3996_p2}};

assign tmp_339_fu_4015_p3 = {{47'd0}, {or_ln324_339_fu_4010_p2}};

assign tmp_340_fu_4029_p3 = {{47'd0}, {or_ln324_340_fu_4024_p2}};

assign tmp_341_fu_4043_p3 = {{47'd0}, {or_ln324_341_fu_4038_p2}};

assign tmp_342_fu_4057_p3 = {{47'd0}, {or_ln324_342_fu_4052_p2}};

assign tmp_343_fu_4071_p3 = {{47'd0}, {or_ln324_343_fu_4066_p2}};

assign tmp_344_fu_4085_p3 = {{47'd0}, {or_ln324_344_fu_4080_p2}};

assign tmp_345_fu_4099_p3 = {{47'd0}, {or_ln324_345_fu_4094_p2}};

assign tmp_346_fu_4113_p3 = {{47'd0}, {or_ln324_346_fu_4108_p2}};

assign tmp_347_fu_4127_p3 = {{47'd0}, {or_ln324_347_fu_4122_p2}};

assign tmp_348_fu_4141_p3 = {{47'd0}, {or_ln324_348_fu_4136_p2}};

assign tmp_349_fu_4155_p3 = {{47'd0}, {or_ln324_349_fu_4150_p2}};

assign tmp_350_fu_4169_p3 = {{47'd0}, {or_ln324_350_fu_4164_p2}};

assign tmp_351_fu_4183_p3 = {{47'd0}, {or_ln324_351_fu_4178_p2}};

assign tmp_352_fu_4197_p3 = {{47'd0}, {or_ln324_352_fu_4192_p2}};

assign tmp_353_fu_4211_p3 = {{47'd0}, {or_ln324_353_fu_4206_p2}};

assign tmp_354_fu_4225_p3 = {{47'd0}, {or_ln324_354_fu_4220_p2}};

assign tmp_355_fu_4239_p3 = {{47'd0}, {or_ln324_355_fu_4234_p2}};

assign tmp_356_fu_4253_p3 = {{47'd0}, {or_ln324_356_fu_4248_p2}};

assign tmp_357_fu_4267_p3 = {{47'd0}, {or_ln324_357_fu_4262_p2}};

assign tmp_358_fu_4281_p3 = {{47'd0}, {or_ln324_358_fu_4276_p2}};

assign tmp_359_fu_4295_p3 = {{47'd0}, {or_ln324_359_fu_4290_p2}};

assign tmp_360_fu_4309_p3 = {{47'd0}, {or_ln324_360_fu_4304_p2}};

assign tmp_361_fu_4323_p3 = {{47'd0}, {or_ln324_361_fu_4318_p2}};

assign tmp_362_fu_4337_p3 = {{47'd0}, {or_ln324_362_fu_4332_p2}};

assign tmp_363_fu_4351_p3 = {{47'd0}, {or_ln324_363_fu_4346_p2}};

assign tmp_364_fu_4365_p3 = {{47'd0}, {or_ln324_364_fu_4360_p2}};

assign tmp_365_fu_4379_p3 = {{47'd0}, {or_ln324_365_fu_4374_p2}};

assign tmp_366_fu_4393_p3 = {{47'd0}, {or_ln324_366_fu_4388_p2}};

assign tmp_367_fu_4407_p3 = {{47'd0}, {or_ln324_367_fu_4402_p2}};

assign tmp_368_fu_4421_p3 = {{47'd0}, {or_ln324_368_fu_4416_p2}};

assign tmp_369_fu_4435_p3 = {{47'd0}, {or_ln324_369_fu_4430_p2}};

assign tmp_370_fu_4449_p3 = {{47'd0}, {or_ln324_370_fu_4444_p2}};

assign tmp_371_fu_4463_p3 = {{47'd0}, {or_ln324_371_fu_4458_p2}};

assign tmp_372_fu_4477_p3 = {{47'd0}, {or_ln324_372_fu_4472_p2}};

assign tmp_373_fu_4491_p3 = {{47'd0}, {or_ln324_373_fu_4486_p2}};

assign tmp_374_fu_4505_p3 = {{47'd0}, {or_ln324_374_fu_4500_p2}};

assign tmp_375_fu_4519_p3 = {{47'd0}, {or_ln324_375_fu_4514_p2}};

assign tmp_376_fu_4533_p3 = {{47'd0}, {or_ln324_376_fu_4528_p2}};

assign tmp_377_fu_4547_p3 = {{47'd0}, {or_ln324_377_fu_4542_p2}};

assign tmp_378_fu_4561_p3 = {{47'd0}, {or_ln324_378_fu_4556_p2}};

assign tmp_379_fu_4575_p3 = {{47'd0}, {or_ln324_379_fu_4570_p2}};

assign tmp_380_fu_4589_p3 = {{47'd0}, {or_ln324_380_fu_4584_p2}};

assign tmp_381_fu_4603_p3 = {{47'd0}, {or_ln324_381_fu_4598_p2}};

assign tmp_382_fu_4617_p3 = {{47'd0}, {or_ln324_382_fu_4612_p2}};

assign tmp_383_fu_4631_p3 = {{47'd0}, {or_ln324_383_fu_4626_p2}};

assign tmp_384_fu_4645_p3 = {{47'd0}, {or_ln324_384_fu_4640_p2}};

assign tmp_385_fu_4659_p3 = {{47'd0}, {or_ln324_385_fu_4654_p2}};

assign tmp_386_fu_4673_p3 = {{47'd0}, {or_ln324_386_fu_4668_p2}};

assign tmp_387_fu_4687_p3 = {{47'd0}, {or_ln324_387_fu_4682_p2}};

assign tmp_388_fu_4701_p3 = {{47'd0}, {or_ln324_388_fu_4696_p2}};

assign tmp_389_fu_4715_p3 = {{47'd0}, {or_ln324_389_fu_4710_p2}};

assign tmp_390_fu_4729_p3 = {{47'd0}, {or_ln324_390_fu_4724_p2}};

assign tmp_391_fu_4743_p3 = {{47'd0}, {or_ln324_391_fu_4738_p2}};

assign tmp_392_fu_4757_p3 = {{47'd0}, {or_ln324_392_fu_4752_p2}};

assign tmp_393_fu_4771_p3 = {{47'd0}, {or_ln324_393_fu_4766_p2}};

assign tmp_394_fu_4785_p3 = {{47'd0}, {or_ln324_394_fu_4780_p2}};

assign tmp_395_fu_4799_p3 = {{47'd0}, {or_ln324_395_fu_4794_p2}};

assign tmp_396_fu_4813_p3 = {{47'd0}, {or_ln324_396_fu_4808_p2}};

assign tmp_397_fu_4827_p3 = {{47'd0}, {or_ln324_397_fu_4822_p2}};

assign tmp_398_fu_4841_p3 = {{47'd0}, {or_ln324_398_fu_4836_p2}};

assign tmp_399_fu_4855_p3 = {{47'd0}, {or_ln324_399_fu_4850_p2}};

assign tmp_400_fu_4869_p3 = {{47'd0}, {or_ln324_400_fu_4864_p2}};

assign tmp_401_fu_4883_p3 = {{47'd0}, {or_ln324_401_fu_4878_p2}};

assign tmp_402_fu_4897_p3 = {{47'd0}, {or_ln324_402_fu_4892_p2}};

assign tmp_403_fu_4911_p3 = {{47'd0}, {or_ln324_403_fu_4906_p2}};

assign tmp_404_fu_4925_p3 = {{47'd0}, {or_ln324_404_fu_4920_p2}};

assign tmp_405_fu_4939_p3 = {{47'd0}, {or_ln324_405_fu_4934_p2}};

assign tmp_406_fu_4953_p3 = {{47'd0}, {or_ln324_406_fu_4948_p2}};

assign tmp_407_fu_4967_p3 = {{47'd0}, {or_ln324_407_fu_4962_p2}};

assign tmp_408_fu_4981_p3 = {{47'd0}, {or_ln324_408_fu_4976_p2}};

assign tmp_409_fu_4995_p3 = {{47'd0}, {or_ln324_409_fu_4990_p2}};

assign tmp_410_fu_5009_p3 = {{47'd0}, {or_ln324_410_fu_5004_p2}};

assign tmp_411_fu_5023_p3 = {{47'd0}, {or_ln324_411_fu_5018_p2}};

assign tmp_412_fu_5037_p3 = {{47'd0}, {or_ln324_412_fu_5032_p2}};

assign tmp_413_fu_5051_p3 = {{47'd0}, {or_ln324_413_fu_5046_p2}};

assign tmp_414_fu_5065_p3 = {{47'd0}, {or_ln324_414_fu_5060_p2}};

assign tmp_415_fu_5079_p3 = {{47'd0}, {or_ln324_415_fu_5074_p2}};

assign tmp_416_fu_5093_p3 = {{47'd0}, {or_ln324_416_fu_5088_p2}};

assign tmp_417_fu_5107_p3 = {{47'd0}, {or_ln324_417_fu_5102_p2}};

assign tmp_418_fu_5121_p3 = {{47'd0}, {or_ln324_418_fu_5116_p2}};

assign tmp_419_fu_5135_p3 = {{47'd0}, {or_ln324_419_fu_5130_p2}};

assign tmp_420_fu_5149_p3 = {{47'd0}, {or_ln324_420_fu_5144_p2}};

assign tmp_421_fu_5163_p3 = {{47'd0}, {or_ln324_421_fu_5158_p2}};

assign tmp_422_fu_5177_p3 = {{47'd0}, {or_ln324_422_fu_5172_p2}};

assign tmp_423_fu_5191_p3 = {{47'd0}, {or_ln324_423_fu_5186_p2}};

assign tmp_424_fu_5205_p3 = {{47'd0}, {or_ln324_424_fu_5200_p2}};

assign tmp_425_fu_5219_p3 = {{47'd0}, {or_ln324_425_fu_5214_p2}};

assign tmp_426_fu_5233_p3 = {{47'd0}, {or_ln324_426_fu_5228_p2}};

assign tmp_427_fu_5247_p3 = {{47'd0}, {or_ln324_427_fu_5242_p2}};

assign tmp_428_fu_5261_p3 = {{47'd0}, {or_ln324_428_fu_5256_p2}};

assign tmp_429_fu_5275_p3 = {{47'd0}, {or_ln324_429_fu_5270_p2}};

assign tmp_430_fu_5289_p3 = {{47'd0}, {or_ln324_430_fu_5284_p2}};

assign tmp_431_fu_5303_p3 = {{47'd0}, {or_ln324_431_fu_5298_p2}};

assign tmp_432_fu_5317_p3 = {{47'd0}, {or_ln324_432_fu_5312_p2}};

assign tmp_433_fu_5331_p3 = {{47'd0}, {or_ln324_433_fu_5326_p2}};

assign tmp_434_fu_5345_p3 = {{47'd0}, {or_ln324_434_fu_5340_p2}};

assign tmp_435_fu_5359_p3 = {{47'd0}, {or_ln324_435_fu_5354_p2}};

assign tmp_436_fu_5373_p3 = {{47'd0}, {or_ln324_436_fu_5368_p2}};

assign tmp_437_fu_5387_p3 = {{47'd0}, {or_ln324_437_fu_5382_p2}};

assign tmp_438_fu_5401_p3 = {{47'd0}, {or_ln324_438_fu_5396_p2}};

assign tmp_439_fu_5415_p3 = {{47'd0}, {or_ln324_439_fu_5410_p2}};

assign tmp_440_fu_5429_p3 = {{47'd0}, {or_ln324_440_fu_5424_p2}};

assign tmp_441_fu_5443_p3 = {{47'd0}, {or_ln324_441_fu_5438_p2}};

assign tmp_442_fu_5457_p3 = {{47'd0}, {or_ln324_442_fu_5452_p2}};

assign tmp_443_fu_5471_p3 = {{47'd0}, {or_ln324_443_fu_5466_p2}};

assign tmp_444_fu_5485_p3 = {{47'd0}, {or_ln324_444_fu_5480_p2}};

assign tmp_445_fu_5499_p3 = {{47'd0}, {or_ln324_445_fu_5494_p2}};

assign tmp_446_fu_5513_p3 = {{47'd0}, {or_ln324_446_fu_5508_p2}};

assign tmp_447_fu_5527_p3 = {{47'd0}, {or_ln324_447_fu_5522_p2}};

assign tmp_448_fu_5541_p3 = {{47'd0}, {or_ln324_448_fu_5536_p2}};

assign tmp_449_fu_5555_p3 = {{47'd0}, {or_ln324_449_fu_5550_p2}};

assign tmp_450_fu_5569_p3 = {{47'd0}, {or_ln324_450_fu_5564_p2}};

assign tmp_451_fu_5583_p3 = {{47'd0}, {or_ln324_451_fu_5578_p2}};

assign tmp_452_fu_5597_p3 = {{47'd0}, {or_ln324_452_fu_5592_p2}};

assign tmp_453_fu_5611_p3 = {{47'd0}, {or_ln324_453_fu_5606_p2}};

assign tmp_454_fu_5625_p3 = {{47'd0}, {or_ln324_454_fu_5620_p2}};

assign tmp_455_fu_5639_p3 = {{47'd0}, {or_ln324_455_fu_5634_p2}};

assign tmp_456_fu_5653_p3 = {{47'd0}, {or_ln324_456_fu_5648_p2}};

assign tmp_457_fu_5667_p3 = {{47'd0}, {or_ln324_457_fu_5662_p2}};

assign tmp_458_fu_5681_p3 = {{47'd0}, {or_ln324_458_fu_5676_p2}};

assign tmp_459_fu_5695_p3 = {{47'd0}, {or_ln324_459_fu_5690_p2}};

assign tmp_460_fu_5709_p3 = {{47'd0}, {or_ln324_460_fu_5704_p2}};

assign tmp_461_fu_5723_p3 = {{47'd0}, {or_ln324_461_fu_5718_p2}};

assign tmp_462_fu_5737_p3 = {{47'd0}, {or_ln324_462_fu_5732_p2}};

assign tmp_463_fu_5751_p3 = {{47'd0}, {or_ln324_463_fu_5746_p2}};

assign tmp_464_fu_5765_p3 = {{47'd0}, {or_ln324_464_fu_5760_p2}};

assign tmp_465_fu_5779_p3 = {{47'd0}, {or_ln324_465_fu_5774_p2}};

assign tmp_466_fu_5793_p3 = {{47'd0}, {or_ln324_466_fu_5788_p2}};

assign tmp_467_fu_5807_p3 = {{47'd0}, {or_ln324_467_fu_5802_p2}};

assign tmp_468_fu_5821_p3 = {{47'd0}, {or_ln324_468_fu_5816_p2}};

assign tmp_469_fu_5835_p3 = {{47'd0}, {or_ln324_469_fu_5830_p2}};

assign tmp_470_fu_5849_p3 = {{47'd0}, {or_ln324_470_fu_5844_p2}};

assign tmp_471_fu_5863_p3 = {{47'd0}, {or_ln324_471_fu_5858_p2}};

assign tmp_472_fu_5877_p3 = {{47'd0}, {or_ln324_472_fu_5872_p2}};

assign tmp_473_fu_5891_p3 = {{47'd0}, {or_ln324_473_fu_5886_p2}};

assign tmp_474_fu_5905_p3 = {{47'd0}, {or_ln324_474_fu_5900_p2}};

assign tmp_475_fu_5919_p3 = {{47'd0}, {or_ln324_475_fu_5914_p2}};

assign tmp_476_fu_5933_p3 = {{47'd0}, {or_ln324_476_fu_5928_p2}};

assign tmp_477_fu_5947_p3 = {{47'd0}, {or_ln324_477_fu_5942_p2}};

assign tmp_478_fu_5961_p3 = {{47'd0}, {or_ln324_478_fu_5956_p2}};

assign tmp_479_fu_5975_p3 = {{47'd0}, {or_ln324_479_fu_5970_p2}};

assign tmp_480_fu_5989_p3 = {{47'd0}, {or_ln324_480_fu_5984_p2}};

assign tmp_481_fu_6003_p3 = {{47'd0}, {or_ln324_481_fu_5998_p2}};

assign tmp_482_fu_6017_p3 = {{47'd0}, {or_ln324_482_fu_6012_p2}};

assign tmp_483_fu_6031_p3 = {{47'd0}, {or_ln324_483_fu_6026_p2}};

assign tmp_484_fu_6045_p3 = {{47'd0}, {or_ln324_484_fu_6040_p2}};

assign tmp_485_fu_6059_p3 = {{47'd0}, {or_ln324_485_fu_6054_p2}};

assign tmp_486_fu_6073_p3 = {{47'd0}, {or_ln324_486_fu_6068_p2}};

assign tmp_487_fu_6087_p3 = {{47'd0}, {or_ln324_487_fu_6082_p2}};

assign tmp_488_fu_6101_p3 = {{47'd0}, {or_ln324_488_fu_6096_p2}};

assign tmp_489_fu_6115_p3 = {{47'd0}, {or_ln324_489_fu_6110_p2}};

assign tmp_490_fu_6129_p3 = {{47'd0}, {or_ln324_490_fu_6124_p2}};

assign tmp_491_fu_6143_p3 = {{47'd0}, {or_ln324_491_fu_6138_p2}};

assign tmp_492_fu_6157_p3 = {{47'd0}, {or_ln324_492_fu_6152_p2}};

assign tmp_493_fu_6171_p3 = {{47'd0}, {or_ln324_493_fu_6166_p2}};

assign tmp_494_fu_6185_p3 = {{47'd0}, {or_ln324_494_fu_6180_p2}};

assign tmp_495_fu_6199_p3 = {{47'd0}, {or_ln324_495_fu_6194_p2}};

assign tmp_496_fu_6213_p3 = {{47'd0}, {or_ln324_496_fu_6208_p2}};

assign tmp_497_fu_6227_p3 = {{47'd0}, {or_ln324_497_fu_6222_p2}};

assign tmp_498_fu_6241_p3 = {{47'd0}, {or_ln324_498_fu_6236_p2}};

assign tmp_499_fu_6255_p3 = {{47'd0}, {or_ln324_499_fu_6250_p2}};

assign tmp_500_fu_6269_p3 = {{47'd0}, {or_ln324_500_fu_6264_p2}};

assign tmp_501_fu_6283_p3 = {{47'd0}, {or_ln324_501_fu_6278_p2}};

assign tmp_502_fu_6297_p3 = {{47'd0}, {or_ln324_502_fu_6292_p2}};

assign tmp_503_fu_6311_p3 = {{47'd0}, {or_ln324_503_fu_6306_p2}};

assign tmp_504_fu_6325_p3 = {{47'd0}, {or_ln324_504_fu_6320_p2}};

assign tmp_505_fu_6339_p3 = {{47'd0}, {or_ln324_505_fu_6334_p2}};

assign tmp_506_fu_6353_p3 = {{47'd0}, {or_ln324_506_fu_6348_p2}};

assign tmp_507_fu_6367_p3 = {{47'd0}, {or_ln324_507_fu_6362_p2}};

assign tmp_508_fu_6381_p3 = {{47'd0}, {or_ln324_508_fu_6376_p2}};

assign tmp_509_fu_6429_p3 = {{trunc_ln324_fu_6425_p1}, {p_Result_s_fu_6404_p4}};

assign tmp_510_fu_6509_p3 = {{select_ln527_1_fu_6487_p3}, {or_ln531_fu_6503_p2}};

assign tmp_511_fu_6528_p3 = {{select_ln527_1_fu_6487_p3}, {or_ln531_1_fu_6522_p2}};

assign tmp_512_fu_6567_p3 = {{select_ln527_1_reg_6919}, {or_ln531_2_fu_6562_p2}};

assign tmp_514_cast_fu_6541_p3 = {{trunc_ln215_reg_6925}, {8'd0}};

assign tmp_5_fu_6471_p3 = ap_phi_mux_j_phi_fu_2766_p4[32'd8];

assign tmp_fu_2806_p3 = {{empty_reg_2718}, {8'd0}};

assign tmp_s_fu_2825_p3 = {{47'd0}, {or_ln324_fu_2819_p2}};

assign trunc_ln215_fu_6495_p1 = select_ln527_1_fu_6487_p3[7:0];

assign trunc_ln324_fu_6425_p1 = Input_1_dout[7:0];

assign trunc_ln528_fu_6499_p1 = select_ln527_fu_6479_p3[7:0];

assign zext_ln215_6_fu_6517_p1 = tmp_510_fu_6509_p3;

assign zext_ln215_7_fu_6536_p1 = tmp_511_fu_6528_p3;

assign zext_ln215_8_fu_6574_p1 = tmp_512_fu_6567_p3;

assign zext_ln215_9_fu_6557_p1 = add_ln215_fu_6551_p2;

assign zext_ln215_fu_6548_p1 = select_ln527_reg_6913;

assign zext_ln324_1_fu_6437_p1 = tmp_509_fu_6429_p3;

assign zext_ln324_fu_2814_p1 = tmp_fu_2806_p3;

always @ (posedge ap_clk) begin
    tmp_reg_6623[7:0] <= 8'b00000000;
end

endmodule //rendering_m_coloringFB_bot_m
// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.1 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================

`timescale 1ns/1ps

module rendering_m_fifo_w32_d1024_A
#(parameter
    DATA_WIDTH  = 32,
    ADDR_WIDTH  = 10,
    DEPTH       = 1023
)
(
    // system signal
    input  wire                  clk,
    input  wire                  reset,

    // write
    output wire                  if_full_n,
    input  wire                  if_write_ce,
    input  wire                  if_write,
    input  wire [DATA_WIDTH-1:0] if_din,

    // read
    output wire                  if_empty_n,
    input  wire                  if_read_ce,
    input  wire                  if_read,
    output wire [DATA_WIDTH-1:0] if_dout
);
//------------------------Parameter----------------------

//------------------------Local signal-------------------
reg  [DATA_WIDTH-1:0] mem[0:DEPTH-1];
reg  [DATA_WIDTH-1:0] q_buf = 1'b0;
reg  [ADDR_WIDTH-1:0] waddr = 1'b0;
reg  [ADDR_WIDTH-1:0] raddr = 1'b0;
wire [ADDR_WIDTH-1:0] wnext;
wire [ADDR_WIDTH-1:0] rnext;
wire                  push;
wire                  pop;
reg  [ADDR_WIDTH-1:0] usedw = 1'b0;
reg                   full_n = 1'b1;
reg                   empty_n = 1'b0;
reg  [DATA_WIDTH-1:0] q_tmp = 1'b0;
reg                   show_ahead = 1'b0;
reg  [DATA_WIDTH-1:0] dout_buf = 1'b0;
reg                   dout_valid = 1'b0;


//------------------------Instantiation------------------

//------------------------Task and function--------------

//------------------------Body---------------------------
assign if_full_n  = full_n;
assign if_empty_n = dout_valid;
assign if_dout    = dout_buf;
assign push       = full_n & if_write_ce & if_write;
assign pop        = empty_n & if_read_ce & (~dout_valid | if_read);
assign wnext      = !push                ? waddr :
                    (waddr == DEPTH - 1) ? 1'b0  :
                    waddr + 1'b1;
assign rnext      = !pop                 ? raddr :
                    (raddr == DEPTH - 1) ? 1'b0  :
                    raddr + 1'b1;

// waddr
always @(posedge clk) begin
    if (reset == 1'b1)
        waddr <= 1'b0;
    else
        waddr <= wnext;
end

// raddr
always @(posedge clk) begin
    if (reset == 1'b1)
        raddr <= 1'b0;
    else
        raddr <= rnext;
end

// usedw
always @(posedge clk) begin
    if (reset == 1'b1)
        usedw <= 1'b0;
    else if (push & ~pop)
        usedw <= usedw + 1'b1;
    else if (~push & pop)
        usedw <= usedw - 1'b1;
end

// full_n
always @(posedge clk) begin
    if (reset == 1'b1)
        full_n <= 1'b1;
    else if (push & ~pop)
        full_n <= (usedw != DEPTH - 1);
    else if (~push & pop)
        full_n <= 1'b1;
end

// empty_n
always @(posedge clk) begin
    if (reset == 1'b1)
        empty_n <= 1'b0;
    else if (push & ~pop)
        empty_n <= 1'b1;
    else if (~push & pop)
        empty_n <= (usedw != 1'b1);
end

// mem
always @(posedge clk) begin
    if (push)
        mem[waddr] <= if_din;
// q_buf
    q_buf <= mem[rnext];
end

// q_tmp
always @(posedge clk) begin
    if (reset == 1'b1)
        q_tmp <= 1'b0;
    else if (push)
        q_tmp <= if_din;
end

// show_ahead
always @(posedge clk) begin
    if (reset == 1'b1)
        show_ahead <= 1'b0;
    else if (push && usedw == pop)
        show_ahead <= 1'b1;
    else
        show_ahead <= 1'b0;
end

// dout_buf
always @(posedge clk) begin
    if (reset == 1'b1)
        dout_buf <= 1'b0;
    else if (pop)
        dout_buf <= show_ahead? q_tmp : q_buf;
end

// dout_valid
always @(posedge clk) begin
    if (reset == 1'b1)
        dout_valid <= 1'b0;
    else if (pop)
        dout_valid <= 1'b1;
    else if (if_read_ce & if_read)
        dout_valid <= 1'b0;
end

endmodule

// ==============================================================
// RTL generated by Vitis HLS - High-Level Synthesis from C, C++ and OpenCL
// Version: 2020.1
// Copyright (C) 1986-2020 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

`timescale 1 ns / 1 ps 

module rendering_m_Loop_TRIANGLES_proc27 (
        ap_clk,
        ap_rst,
        ap_start,
        ap_done,
        ap_continue,
        ap_idle,
        ap_ready,
        Input_1_V_TDATA,
        Input_1_V_TVALID,
        Input_1_V_TREADY,
        Output_1_V_TDATA,
        Output_1_V_TVALID,
        Output_1_V_TREADY
);

parameter    ap_ST_fsm_state1 = 14'd1;
parameter    ap_ST_fsm_state2 = 14'd2;
parameter    ap_ST_fsm_state3 = 14'd4;
parameter    ap_ST_fsm_state4 = 14'd8;
parameter    ap_ST_fsm_state5 = 14'd16;
parameter    ap_ST_fsm_state6 = 14'd32;
parameter    ap_ST_fsm_state7 = 14'd64;
parameter    ap_ST_fsm_state8 = 14'd128;
parameter    ap_ST_fsm_state9 = 14'd256;
parameter    ap_ST_fsm_state10 = 14'd512;
parameter    ap_ST_fsm_state11 = 14'd1024;
parameter    ap_ST_fsm_state12 = 14'd2048;
parameter    ap_ST_fsm_state13 = 14'd4096;
parameter    ap_ST_fsm_state14 = 14'd8192;

input   ap_clk;
input   ap_rst;
input   ap_start;
output   ap_done;
input   ap_continue;
output   ap_idle;
output   ap_ready;
input  [31:0] Input_1_V_TDATA;
input   Input_1_V_TVALID;
output   Input_1_V_TREADY;
output  [31:0] Output_1_V_TDATA;
output   Output_1_V_TVALID;
input   Output_1_V_TREADY;

reg ap_done;
reg ap_idle;
reg ap_ready;

reg    ap_done_reg;
(* fsm_encoding = "none" *) reg   [13:0] ap_CS_fsm;
wire    ap_CS_fsm_state1;
reg    Input_1_V_TDATA_blk_n;
wire    ap_CS_fsm_state2;
wire   [0:0] icmp_ln882_fu_181_p2;
wire    ap_CS_fsm_state3;
wire    ap_CS_fsm_state4;
wire   [11:0] add_ln695_fu_187_p2;
reg   [11:0] add_ln695_reg_247;
reg    ap_block_state2;
reg   [31:0] Input_1_V_read_reg_252;
reg   [31:0] Input_1_V_read_1_reg_257;
wire   [7:0] trunc_ln302_fu_193_p1;
reg   [7:0] trunc_ln302_reg_262;
reg   [7:0] triangle_2ds_1_x0_V_reg_267;
wire    ap_CS_fsm_state5;
wire    grp_projection_odd_m_fu_174_ap_ready;
wire    grp_projection_odd_m_fu_174_ap_done;
reg   [7:0] triangle_2ds_1_y0_V_reg_272;
reg   [7:0] triangle_2ds_1_x1_V_reg_277;
reg   [7:0] triangle_2ds_1_y1_V_reg_282;
reg   [7:0] triangle_2ds_1_x2_V_reg_287;
reg   [7:0] triangle_2ds_1_y2_V_reg_292;
reg   [7:0] triangle_2ds_1_z_V_reg_297;
wire    grp_coloringFB_bot_m_fu_115_ap_start;
wire    grp_coloringFB_bot_m_fu_115_ap_done;
wire    grp_coloringFB_bot_m_fu_115_ap_idle;
wire    grp_coloringFB_bot_m_fu_115_ap_ready;
wire    grp_coloringFB_bot_m_fu_115_Input_1_read;
wire   [31:0] grp_coloringFB_bot_m_fu_115_Output_1_V_TDATA;
wire    grp_coloringFB_bot_m_fu_115_Output_1_V_TVALID;
wire    grp_coloringFB_bot_m_fu_115_Output_1_V_TREADY;
wire    grp_zculling_top_fu_126_ap_start;
wire    grp_zculling_top_fu_126_ap_done;
wire    grp_zculling_top_fu_126_ap_idle;
wire    grp_zculling_top_fu_126_ap_ready;
wire    grp_zculling_top_fu_126_Input_1_read;
wire   [31:0] grp_zculling_top_fu_126_Output_1_din;
wire    grp_zculling_top_fu_126_Output_1_write;
wire    grp_rasterization2_odd_fu_136_ap_start;
wire    grp_rasterization2_odd_fu_136_ap_done;
wire    grp_rasterization2_odd_fu_136_ap_idle;
wire    grp_rasterization2_odd_fu_136_ap_ready;
wire    grp_rasterization2_odd_fu_136_Input_1_read;
wire   [31:0] grp_rasterization2_odd_fu_136_Output_1_din;
wire    grp_rasterization2_odd_fu_136_Output_1_write;
wire    grp_rasterization1_odd_m_fu_150_ap_start;
wire    grp_rasterization1_odd_m_fu_150_ap_done;
wire    grp_rasterization1_odd_m_fu_150_ap_idle;
wire    grp_rasterization1_odd_m_fu_150_ap_ready;
wire   [31:0] grp_rasterization1_odd_m_fu_150_Output_redir_odd25_din;
wire    grp_rasterization1_odd_m_fu_150_Output_redir_odd25_write;
wire    grp_projection_odd_m_fu_174_ap_start;
wire    grp_projection_odd_m_fu_174_ap_idle;
wire   [7:0] grp_projection_odd_m_fu_174_ap_return_0;
wire   [7:0] grp_projection_odd_m_fu_174_ap_return_1;
wire   [7:0] grp_projection_odd_m_fu_174_ap_return_2;
wire   [7:0] grp_projection_odd_m_fu_174_ap_return_3;
wire   [7:0] grp_projection_odd_m_fu_174_ap_return_4;
wire   [7:0] grp_projection_odd_m_fu_174_ap_return_5;
wire   [7:0] grp_projection_odd_m_fu_174_ap_return_6;
reg   [11:0] empty_78_reg_104;
reg    ap_block_state1;
wire    ap_CS_fsm_state13;
reg    grp_coloringFB_bot_m_fu_115_ap_start_reg;
wire    ap_CS_fsm_state12;
wire   [31:0] Output_zcu_top_dout;
wire    Output_zcu_top_empty_n;
reg    Output_zcu_top_read;
reg    grp_zculling_top_fu_126_ap_start_reg;
wire    ap_CS_fsm_state10;
wire   [31:0] Output_r2_odd_top_dout;
wire    Output_r2_odd_top_empty_n;
reg    Output_r2_odd_top_read;
wire    ap_CS_fsm_state11;
wire    Output_zcu_top_full_n;
reg    Output_zcu_top_write;
reg    grp_rasterization2_odd_fu_136_ap_start_reg;
wire    ap_CS_fsm_state8;
wire   [31:0] Output_redir_odd_dout;
wire    Output_redir_odd_empty_n;
reg    Output_redir_odd_read;
wire    ap_CS_fsm_state9;
wire    Output_r2_odd_top_full_n;
reg    Output_r2_odd_top_write;
reg    grp_rasterization1_odd_m_fu_150_ap_start_reg;
wire    ap_CS_fsm_state6;
wire    Output_redir_odd_full_n;
reg    Output_redir_odd_write;
wire    ap_CS_fsm_state7;
reg    grp_projection_odd_m_fu_174_ap_start_reg;
wire    ap_CS_fsm_state14;
wire    regslice_both_Output_1_V_U_apdone_blk;
reg   [13:0] ap_NS_fsm;
wire    regslice_both_Input_1_V_U_apdone_blk;
wire   [31:0] Input_1_V_TDATA_int_regslice;
wire    Input_1_V_TVALID_int_regslice;
reg    Input_1_V_TREADY_int_regslice;
wire    regslice_both_Input_1_V_U_ack_in;
wire    Output_1_V_TREADY_int_regslice;
wire    regslice_both_Output_1_V_U_vld_out;

// power-on initialization
initial begin
#0 ap_done_reg = 1'b0;
#0 ap_CS_fsm = 14'd1;
#0 grp_coloringFB_bot_m_fu_115_ap_start_reg = 1'b0;
#0 grp_zculling_top_fu_126_ap_start_reg = 1'b0;
#0 grp_rasterization2_odd_fu_136_ap_start_reg = 1'b0;
#0 grp_rasterization1_odd_m_fu_150_ap_start_reg = 1'b0;
#0 grp_projection_odd_m_fu_174_ap_start_reg = 1'b0;
end

rendering_m_coloringFB_bot_m grp_coloringFB_bot_m_fu_115(
    .ap_clk(ap_clk),
    .ap_rst(ap_rst),
    .ap_start(grp_coloringFB_bot_m_fu_115_ap_start),
    .ap_done(grp_coloringFB_bot_m_fu_115_ap_done),
    .ap_idle(grp_coloringFB_bot_m_fu_115_ap_idle),
    .ap_ready(grp_coloringFB_bot_m_fu_115_ap_ready),
    .Input_1_dout(Output_zcu_top_dout),
    .Input_1_empty_n(Output_zcu_top_empty_n),
    .Input_1_read(grp_coloringFB_bot_m_fu_115_Input_1_read),
    .Output_1_V_TDATA(grp_coloringFB_bot_m_fu_115_Output_1_V_TDATA),
    .Output_1_V_TVALID(grp_coloringFB_bot_m_fu_115_Output_1_V_TVALID),
    .Output_1_V_TREADY(grp_coloringFB_bot_m_fu_115_Output_1_V_TREADY)
);

rendering_m_zculling_top grp_zculling_top_fu_126(
    .ap_clk(ap_clk),
    .ap_rst(ap_rst),
    .ap_start(grp_zculling_top_fu_126_ap_start),
    .ap_done(grp_zculling_top_fu_126_ap_done),
    .ap_idle(grp_zculling_top_fu_126_ap_idle),
    .ap_ready(grp_zculling_top_fu_126_ap_ready),
    .Input_1_dout(Output_r2_odd_top_dout),
    .Input_1_empty_n(Output_r2_odd_top_empty_n),
    .Input_1_read(grp_zculling_top_fu_126_Input_1_read),
    .Output_1_din(grp_zculling_top_fu_126_Output_1_din),
    .Output_1_full_n(Output_zcu_top_full_n),
    .Output_1_write(grp_zculling_top_fu_126_Output_1_write)
);

rendering_m_rasterization2_odd grp_rasterization2_odd_fu_136(
    .ap_clk(ap_clk),
    .ap_rst(ap_rst),
    .ap_start(grp_rasterization2_odd_fu_136_ap_start),
    .ap_done(grp_rasterization2_odd_fu_136_ap_done),
    .ap_idle(grp_rasterization2_odd_fu_136_ap_idle),
    .ap_ready(grp_rasterization2_odd_fu_136_ap_ready),
    .Input_1_dout(Output_redir_odd_dout),
    .Input_1_empty_n(Output_redir_odd_empty_n),
    .Input_1_read(grp_rasterization2_odd_fu_136_Input_1_read),
    .Output_1_din(grp_rasterization2_odd_fu_136_Output_1_din),
    .Output_1_full_n(Output_r2_odd_top_full_n),
    .Output_1_write(grp_rasterization2_odd_fu_136_Output_1_write)
);

rendering_m_rasterization1_odd_m grp_rasterization1_odd_m_fu_150(
    .ap_clk(ap_clk),
    .ap_rst(ap_rst),
    .ap_start(grp_rasterization1_odd_m_fu_150_ap_start),
    .ap_done(grp_rasterization1_odd_m_fu_150_ap_done),
    .ap_idle(grp_rasterization1_odd_m_fu_150_ap_idle),
    .ap_ready(grp_rasterization1_odd_m_fu_150_ap_ready),
    .Output_redir_odd25_din(grp_rasterization1_odd_m_fu_150_Output_redir_odd25_din),
    .Output_redir_odd25_full_n(Output_redir_odd_full_n),
    .Output_redir_odd25_write(grp_rasterization1_odd_m_fu_150_Output_redir_odd25_write),
    .triangle_2d_0(triangle_2ds_1_x0_V_reg_267),
    .triangle_2d_1(triangle_2ds_1_y0_V_reg_272),
    .triangle_2d_2(triangle_2ds_1_x1_V_reg_277),
    .triangle_2d_3(triangle_2ds_1_y1_V_reg_282),
    .triangle_2d_4(triangle_2ds_1_x2_V_reg_287),
    .triangle_2d_5(triangle_2ds_1_y2_V_reg_292),
    .triangle_2d_6(triangle_2ds_1_z_V_reg_297)
);

rendering_m_projection_odd_m grp_projection_odd_m_fu_174(
    .ap_clk(ap_clk),
    .ap_rst(ap_rst),
    .ap_start(grp_projection_odd_m_fu_174_ap_start),
    .ap_done(grp_projection_odd_m_fu_174_ap_done),
    .ap_idle(grp_projection_odd_m_fu_174_ap_idle),
    .ap_ready(grp_projection_odd_m_fu_174_ap_ready),
    .input_lo(Input_1_V_read_reg_252),
    .input_mi(Input_1_V_read_1_reg_257),
    .input_hi(trunc_ln302_reg_262),
    .ap_return_0(grp_projection_odd_m_fu_174_ap_return_0),
    .ap_return_1(grp_projection_odd_m_fu_174_ap_return_1),
    .ap_return_2(grp_projection_odd_m_fu_174_ap_return_2),
    .ap_return_3(grp_projection_odd_m_fu_174_ap_return_3),
    .ap_return_4(grp_projection_odd_m_fu_174_ap_return_4),
    .ap_return_5(grp_projection_odd_m_fu_174_ap_return_5),
    .ap_return_6(grp_projection_odd_m_fu_174_ap_return_6)
);

rendering_m_fifo_w32_d1024_A Output_redir_odd_fifo_U(
    .clk(ap_clk),
    .reset(ap_rst),
    .if_read_ce(1'b1),
    .if_write_ce(1'b1),
    .if_din(grp_rasterization1_odd_m_fu_150_Output_redir_odd25_din),
    .if_full_n(Output_redir_odd_full_n),
    .if_write(Output_redir_odd_write),
    .if_dout(Output_redir_odd_dout),
    .if_empty_n(Output_redir_odd_empty_n),
    .if_read(Output_redir_odd_read)
);

rendering_m_fifo_w32_d1024_A Output_r2_odd_top_fifo_U(
    .clk(ap_clk),
    .reset(ap_rst),
    .if_read_ce(1'b1),
    .if_write_ce(1'b1),
    .if_din(grp_rasterization2_odd_fu_136_Output_1_din),
    .if_full_n(Output_r2_odd_top_full_n),
    .if_write(Output_r2_odd_top_write),
    .if_dout(Output_r2_odd_top_dout),
    .if_empty_n(Output_r2_odd_top_empty_n),
    .if_read(Output_r2_odd_top_read)
);

rendering_m_fifo_w32_d1024_A Output_zcu_top_fifo_U(
    .clk(ap_clk),
    .reset(ap_rst),
    .if_read_ce(1'b1),
    .if_write_ce(1'b1),
    .if_din(grp_zculling_top_fu_126_Output_1_din),
    .if_full_n(Output_zcu_top_full_n),
    .if_write(Output_zcu_top_write),
    .if_dout(Output_zcu_top_dout),
    .if_empty_n(Output_zcu_top_empty_n),
    .if_read(Output_zcu_top_read)
);

regslice_both #(
    .DataWidth( 32 ))
regslice_both_Input_1_V_U(
    .ap_clk(ap_clk),
    .ap_rst(ap_rst),
    .data_in(Input_1_V_TDATA),
    .vld_in(Input_1_V_TVALID),
    .ack_in(regslice_both_Input_1_V_U_ack_in),
    .data_out(Input_1_V_TDATA_int_regslice),
    .vld_out(Input_1_V_TVALID_int_regslice),
    .ack_out(Input_1_V_TREADY_int_regslice),
    .apdone_blk(regslice_both_Input_1_V_U_apdone_blk)
);

regslice_both #(
    .DataWidth( 32 ))
regslice_both_Output_1_V_U(
    .ap_clk(ap_clk),
    .ap_rst(ap_rst),
    .data_in(grp_coloringFB_bot_m_fu_115_Output_1_V_TDATA),
    .vld_in(grp_coloringFB_bot_m_fu_115_Output_1_V_TVALID),
    .ack_in(Output_1_V_TREADY_int_regslice),
    .data_out(Output_1_V_TDATA),
    .vld_out(regslice_both_Output_1_V_U_vld_out),
    .ack_out(Output_1_V_TREADY),
    .apdone_blk(regslice_both_Output_1_V_U_apdone_blk)
);

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_CS_fsm <= ap_ST_fsm_state1;
    end else begin
        ap_CS_fsm <= ap_NS_fsm;
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_done_reg <= 1'b0;
    end else begin
        if ((ap_continue == 1'b1)) begin
            ap_done_reg <= 1'b0;
        end else if (((regslice_both_Output_1_V_U_apdone_blk == 1'b0) & (1'b1 == ap_CS_fsm_state14))) begin
            ap_done_reg <= 1'b1;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        grp_coloringFB_bot_m_fu_115_ap_start_reg <= 1'b0;
    end else begin
        if ((1'b1 == ap_CS_fsm_state12)) begin
            grp_coloringFB_bot_m_fu_115_ap_start_reg <= 1'b1;
        end else if ((grp_coloringFB_bot_m_fu_115_ap_ready == 1'b1)) begin
            grp_coloringFB_bot_m_fu_115_ap_start_reg <= 1'b0;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        grp_projection_odd_m_fu_174_ap_start_reg <= 1'b0;
    end else begin
        if (((1'b1 == ap_CS_fsm_state4) & (1'b1 == Input_1_V_TVALID_int_regslice))) begin
            grp_projection_odd_m_fu_174_ap_start_reg <= 1'b1;
        end else if ((grp_projection_odd_m_fu_174_ap_ready == 1'b1)) begin
            grp_projection_odd_m_fu_174_ap_start_reg <= 1'b0;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        grp_rasterization1_odd_m_fu_150_ap_start_reg <= 1'b0;
    end else begin
        if ((1'b1 == ap_CS_fsm_state6)) begin
            grp_rasterization1_odd_m_fu_150_ap_start_reg <= 1'b1;
        end else if ((grp_rasterization1_odd_m_fu_150_ap_ready == 1'b1)) begin
            grp_rasterization1_odd_m_fu_150_ap_start_reg <= 1'b0;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        grp_rasterization2_odd_fu_136_ap_start_reg <= 1'b0;
    end else begin
        if ((1'b1 == ap_CS_fsm_state8)) begin
            grp_rasterization2_odd_fu_136_ap_start_reg <= 1'b1;
        end else if ((grp_rasterization2_odd_fu_136_ap_ready == 1'b1)) begin
            grp_rasterization2_odd_fu_136_ap_start_reg <= 1'b0;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        grp_zculling_top_fu_126_ap_start_reg <= 1'b0;
    end else begin
        if ((1'b1 == ap_CS_fsm_state10)) begin
            grp_zculling_top_fu_126_ap_start_reg <= 1'b1;
        end else if ((grp_zculling_top_fu_126_ap_ready == 1'b1)) begin
            grp_zculling_top_fu_126_ap_start_reg <= 1'b0;
        end
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == ap_CS_fsm_state13) & (grp_coloringFB_bot_m_fu_115_ap_done == 1'b1))) begin
        empty_78_reg_104 <= add_ln695_reg_247;
    end else if ((~((ap_done_reg == 1'b1) | (ap_start == 1'b0)) & (1'b1 == ap_CS_fsm_state1))) begin
        empty_78_reg_104 <= 12'd0;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == ap_CS_fsm_state3) & (1'b1 == Input_1_V_TVALID_int_regslice))) begin
        Input_1_V_read_1_reg_257 <= Input_1_V_TDATA_int_regslice;
    end
end

always @ (posedge ap_clk) begin
    if ((~((icmp_ln882_fu_181_p2 == 1'd0) & (1'b0 == Input_1_V_TVALID_int_regslice)) & (icmp_ln882_fu_181_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state2))) begin
        Input_1_V_read_reg_252 <= Input_1_V_TDATA_int_regslice;
    end
end

always @ (posedge ap_clk) begin
    if ((~((icmp_ln882_fu_181_p2 == 1'd0) & (1'b0 == Input_1_V_TVALID_int_regslice)) & (1'b1 == ap_CS_fsm_state2))) begin
        add_ln695_reg_247 <= add_ln695_fu_187_p2;
    end
end

always @ (posedge ap_clk) begin
    if (((grp_projection_odd_m_fu_174_ap_done == 1'b1) & (1'b1 == ap_CS_fsm_state5))) begin
        triangle_2ds_1_x0_V_reg_267 <= grp_projection_odd_m_fu_174_ap_return_0;
        triangle_2ds_1_x1_V_reg_277 <= grp_projection_odd_m_fu_174_ap_return_2;
        triangle_2ds_1_x2_V_reg_287 <= grp_projection_odd_m_fu_174_ap_return_4;
        triangle_2ds_1_y0_V_reg_272 <= grp_projection_odd_m_fu_174_ap_return_1;
        triangle_2ds_1_y1_V_reg_282 <= grp_projection_odd_m_fu_174_ap_return_3;
        triangle_2ds_1_y2_V_reg_292 <= grp_projection_odd_m_fu_174_ap_return_5;
        triangle_2ds_1_z_V_reg_297 <= grp_projection_odd_m_fu_174_ap_return_6;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == ap_CS_fsm_state4) & (1'b1 == Input_1_V_TVALID_int_regslice))) begin
        trunc_ln302_reg_262 <= trunc_ln302_fu_193_p1;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state4) | (1'b1 == ap_CS_fsm_state3) | ((icmp_ln882_fu_181_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state2)))) begin
        Input_1_V_TDATA_blk_n = Input_1_V_TVALID_int_regslice;
    end else begin
        Input_1_V_TDATA_blk_n = 1'b1;
    end
end

always @ (*) begin
    if ((((1'b1 == ap_CS_fsm_state4) & (1'b1 == Input_1_V_TVALID_int_regslice)) | ((1'b1 == ap_CS_fsm_state3) & (1'b1 == Input_1_V_TVALID_int_regslice)) | (~((icmp_ln882_fu_181_p2 == 1'd0) & (1'b0 == Input_1_V_TVALID_int_regslice)) & (icmp_ln882_fu_181_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state2)))) begin
        Input_1_V_TREADY_int_regslice = 1'b1;
    end else begin
        Input_1_V_TREADY_int_regslice = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state11)) begin
        Output_r2_odd_top_read = grp_zculling_top_fu_126_Input_1_read;
    end else begin
        Output_r2_odd_top_read = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state9)) begin
        Output_r2_odd_top_write = grp_rasterization2_odd_fu_136_Output_1_write;
    end else begin
        Output_r2_odd_top_write = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state9)) begin
        Output_redir_odd_read = grp_rasterization2_odd_fu_136_Input_1_read;
    end else begin
        Output_redir_odd_read = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state7)) begin
        Output_redir_odd_write = grp_rasterization1_odd_m_fu_150_Output_redir_odd25_write;
    end else begin
        Output_redir_odd_write = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state13)) begin
        Output_zcu_top_read = grp_coloringFB_bot_m_fu_115_Input_1_read;
    end else begin
        Output_zcu_top_read = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state11)) begin
        Output_zcu_top_write = grp_zculling_top_fu_126_Output_1_write;
    end else begin
        Output_zcu_top_write = 1'b0;
    end
end

always @ (*) begin
    if (((regslice_both_Output_1_V_U_apdone_blk == 1'b0) & (1'b1 == ap_CS_fsm_state14))) begin
        ap_done = 1'b1;
    end else begin
        ap_done = ap_done_reg;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b0))) begin
        ap_idle = 1'b1;
    end else begin
        ap_idle = 1'b0;
    end
end

always @ (*) begin
    if (((regslice_both_Output_1_V_U_apdone_blk == 1'b0) & (1'b1 == ap_CS_fsm_state14))) begin
        ap_ready = 1'b1;
    end else begin
        ap_ready = 1'b0;
    end
end

always @ (*) begin
    case (ap_CS_fsm)
        ap_ST_fsm_state1 : begin
            if ((~((ap_done_reg == 1'b1) | (ap_start == 1'b0)) & (1'b1 == ap_CS_fsm_state1))) begin
                ap_NS_fsm = ap_ST_fsm_state2;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state1;
            end
        end
        ap_ST_fsm_state2 : begin
            if ((~((icmp_ln882_fu_181_p2 == 1'd0) & (1'b0 == Input_1_V_TVALID_int_regslice)) & (icmp_ln882_fu_181_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state2))) begin
                ap_NS_fsm = ap_ST_fsm_state14;
            end else if ((~((icmp_ln882_fu_181_p2 == 1'd0) & (1'b0 == Input_1_V_TVALID_int_regslice)) & (icmp_ln882_fu_181_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state2))) begin
                ap_NS_fsm = ap_ST_fsm_state3;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state2;
            end
        end
        ap_ST_fsm_state3 : begin
            if (((1'b1 == ap_CS_fsm_state3) & (1'b1 == Input_1_V_TVALID_int_regslice))) begin
                ap_NS_fsm = ap_ST_fsm_state4;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state3;
            end
        end
        ap_ST_fsm_state4 : begin
            if (((1'b1 == ap_CS_fsm_state4) & (1'b1 == Input_1_V_TVALID_int_regslice))) begin
                ap_NS_fsm = ap_ST_fsm_state5;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state4;
            end
        end
        ap_ST_fsm_state5 : begin
            if (((grp_projection_odd_m_fu_174_ap_done == 1'b1) & (1'b1 == ap_CS_fsm_state5))) begin
                ap_NS_fsm = ap_ST_fsm_state6;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state5;
            end
        end
        ap_ST_fsm_state6 : begin
            ap_NS_fsm = ap_ST_fsm_state7;
        end
        ap_ST_fsm_state7 : begin
            if (((1'b1 == ap_CS_fsm_state7) & (grp_rasterization1_odd_m_fu_150_ap_done == 1'b1))) begin
                ap_NS_fsm = ap_ST_fsm_state8;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state7;
            end
        end
        ap_ST_fsm_state8 : begin
            ap_NS_fsm = ap_ST_fsm_state9;
        end
        ap_ST_fsm_state9 : begin
            if (((1'b1 == ap_CS_fsm_state9) & (grp_rasterization2_odd_fu_136_ap_done == 1'b1))) begin
                ap_NS_fsm = ap_ST_fsm_state10;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state9;
            end
        end
        ap_ST_fsm_state10 : begin
            ap_NS_fsm = ap_ST_fsm_state11;
        end
        ap_ST_fsm_state11 : begin
            if (((1'b1 == ap_CS_fsm_state11) & (grp_zculling_top_fu_126_ap_done == 1'b1))) begin
                ap_NS_fsm = ap_ST_fsm_state12;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state11;
            end
        end
        ap_ST_fsm_state12 : begin
            ap_NS_fsm = ap_ST_fsm_state13;
        end
        ap_ST_fsm_state13 : begin
            if (((1'b1 == ap_CS_fsm_state13) & (grp_coloringFB_bot_m_fu_115_ap_done == 1'b1))) begin
                ap_NS_fsm = ap_ST_fsm_state2;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state13;
            end
        end
        ap_ST_fsm_state14 : begin
            if (((regslice_both_Output_1_V_U_apdone_blk == 1'b0) & (1'b1 == ap_CS_fsm_state14))) begin
                ap_NS_fsm = ap_ST_fsm_state1;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state14;
            end
        end
        default : begin
            ap_NS_fsm = 'bx;
        end
    endcase
end

assign Input_1_V_TREADY = regslice_both_Input_1_V_U_ack_in;

assign Output_1_V_TVALID = regslice_both_Output_1_V_U_vld_out;

assign add_ln695_fu_187_p2 = (empty_78_reg_104 + 12'd1);

assign ap_CS_fsm_state1 = ap_CS_fsm[32'd0];

assign ap_CS_fsm_state10 = ap_CS_fsm[32'd9];

assign ap_CS_fsm_state11 = ap_CS_fsm[32'd10];

assign ap_CS_fsm_state12 = ap_CS_fsm[32'd11];

assign ap_CS_fsm_state13 = ap_CS_fsm[32'd12];

assign ap_CS_fsm_state14 = ap_CS_fsm[32'd13];

assign ap_CS_fsm_state2 = ap_CS_fsm[32'd1];

assign ap_CS_fsm_state3 = ap_CS_fsm[32'd2];

assign ap_CS_fsm_state4 = ap_CS_fsm[32'd3];

assign ap_CS_fsm_state5 = ap_CS_fsm[32'd4];

assign ap_CS_fsm_state6 = ap_CS_fsm[32'd5];

assign ap_CS_fsm_state7 = ap_CS_fsm[32'd6];

assign ap_CS_fsm_state8 = ap_CS_fsm[32'd7];

assign ap_CS_fsm_state9 = ap_CS_fsm[32'd8];

always @ (*) begin
    ap_block_state1 = ((ap_done_reg == 1'b1) | (ap_start == 1'b0));
end

always @ (*) begin
    ap_block_state2 = ((icmp_ln882_fu_181_p2 == 1'd0) & (1'b0 == Input_1_V_TVALID_int_regslice));
end

assign grp_coloringFB_bot_m_fu_115_Output_1_V_TREADY = (ap_CS_fsm_state13 & Output_1_V_TREADY_int_regslice);

assign grp_coloringFB_bot_m_fu_115_ap_start = grp_coloringFB_bot_m_fu_115_ap_start_reg;

assign grp_projection_odd_m_fu_174_ap_start = grp_projection_odd_m_fu_174_ap_start_reg;

assign grp_rasterization1_odd_m_fu_150_ap_start = grp_rasterization1_odd_m_fu_150_ap_start_reg;

assign grp_rasterization2_odd_fu_136_ap_start = grp_rasterization2_odd_fu_136_ap_start_reg;

assign grp_zculling_top_fu_126_ap_start = grp_zculling_top_fu_126_ap_start_reg;

assign icmp_ln882_fu_181_p2 = ((empty_78_reg_104 == 12'd3192) ? 1'b1 : 1'b0);

assign trunc_ln302_fu_193_p1 = Input_1_V_TDATA_int_regslice[7:0];

endmodule //rendering_m_Loop_TRIANGLES_proc27
// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.1 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
`timescale 1 ns / 1 ps

(* use_dsp = "yes" *) module rendering_m_mac_mulsub_9s_9s_18ns_18_4_1_DSP48_0(
    input clk,
    input rst,
    input ce,
    input  [9 - 1:0] in0,
    input  [9 - 1:0] in1,
    input  [18 - 1:0] in2,
    output [18 - 1:0]  dout);

wire signed [25 - 1:0]     a;
wire signed [18 - 1:0]     b;
wire signed [48 - 1:0]     c;
wire signed [43 - 1:0]     m;
wire signed [48 - 1:0]     p;
reg  signed [43 - 1:0]     m_reg;
reg  signed [25 - 1:0]     a_reg;
reg  signed [18 - 1:0]     b_reg;
reg  signed [48 - 1:0]     p_reg;

assign a  = $signed(in0);
assign b  = $signed(in1);
assign c  = $unsigned(in2);

assign m  = a_reg * b_reg;
assign p  = c - m_reg;

always @(posedge clk) begin
    if (ce) begin
        m_reg  <= m;
        a_reg  <= a;
        b_reg  <= b;
        p_reg  <= p;
    end
end

assign dout = p_reg;

endmodule
`timescale 1 ns / 1 ps
module rendering_m_mac_mulsub_9s_9s_18ns_18_4_1(
    clk,
    reset,
    ce,
    din0,
    din1,
    din2,
    dout);

parameter ID = 32'd1;
parameter NUM_STAGE = 32'd1;
parameter din0_WIDTH = 32'd1;
parameter din1_WIDTH = 32'd1;
parameter din2_WIDTH = 32'd1;
parameter dout_WIDTH = 32'd1;
input clk;
input reset;
input ce;
input[din0_WIDTH - 1:0] din0;
input[din1_WIDTH - 1:0] din1;
input[din2_WIDTH - 1:0] din2;
output[dout_WIDTH - 1:0] dout;



rendering_m_mac_mulsub_9s_9s_18ns_18_4_1_DSP48_0 rendering_m_mac_mulsub_9s_9s_18ns_18_4_1_DSP48_0_U(
    .clk( clk ),
    .rst( reset ),
    .ce( ce ),
    .in0( din0 ),
    .in1( din1 ),
    .in2( din2 ),
    .dout( dout ));

endmodule

// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.1 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================

`timescale 1 ns / 1 ps

module rendering_m_mul_10ns_8ns_17_1_1_Multiplier_0(a, b, p);
input[10 - 1 : 0] a; 
input[8 - 1 : 0] b; 
output[17 - 1 : 0] p;

assign p = $signed({1'b0, a}) * $signed({1'b0, b});
endmodule
`timescale 1 ns / 1 ps
module rendering_m_mul_10ns_8ns_17_1_1(
    din0,
    din1,
    dout);

parameter ID = 32'd1;
parameter NUM_STAGE = 32'd1;
parameter din0_WIDTH = 32'd1;
parameter din1_WIDTH = 32'd1;
parameter dout_WIDTH = 32'd1;
input[din0_WIDTH - 1:0] din0;
input[din1_WIDTH - 1:0] din1;
output[dout_WIDTH - 1:0] dout;



rendering_m_mul_10ns_8ns_17_1_1_Multiplier_0 rendering_m_mul_10ns_8ns_17_1_1_Multiplier_0_U(
    .a( din0 ),
    .b( din1 ),
    .p( dout ));

endmodule

// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.1 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================

`timescale 1 ns / 1 ps

module rendering_m_mul_9s_9s_16_1_1_Multiplier_2(a, b, p);
input[9 - 1 : 0] a; 
input[9 - 1 : 0] b; 
output[16 - 1 : 0] p;

assign p = $signed(a) * $signed(b);
endmodule
`timescale 1 ns / 1 ps
module rendering_m_mul_9s_9s_16_1_1(
    din0,
    din1,
    dout);

parameter ID = 32'd1;
parameter NUM_STAGE = 32'd1;
parameter din0_WIDTH = 32'd1;
parameter din1_WIDTH = 32'd1;
parameter dout_WIDTH = 32'd1;
input[din0_WIDTH - 1:0] din0;
input[din1_WIDTH - 1:0] din1;
output[dout_WIDTH - 1:0] dout;



rendering_m_mul_9s_9s_16_1_1_Multiplier_2 rendering_m_mul_9s_9s_16_1_1_Multiplier_2_U(
    .a( din0 ),
    .b( din1 ),
    .p( dout ));

endmodule

// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.1 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================

`timescale 1 ns / 1 ps

module rendering_m_mul_9s_9s_18_1_1_Multiplier_1(a, b, p);
input[9 - 1 : 0] a; 
input[9 - 1 : 0] b; 
output[18 - 1 : 0] p;

assign p = $signed(a) * $signed(b);
endmodule
`timescale 1 ns / 1 ps
module rendering_m_mul_9s_9s_18_1_1(
    din0,
    din1,
    dout);

parameter ID = 32'd1;
parameter NUM_STAGE = 32'd1;
parameter din0_WIDTH = 32'd1;
parameter din1_WIDTH = 32'd1;
parameter dout_WIDTH = 32'd1;
input[din0_WIDTH - 1:0] din0;
input[din1_WIDTH - 1:0] din1;
output[dout_WIDTH - 1:0] dout;



rendering_m_mul_9s_9s_18_1_1_Multiplier_1 rendering_m_mul_9s_9s_18_1_1_Multiplier_1_U(
    .a( din0 ),
    .b( din1 ),
    .p( dout ));

endmodule

// ==============================================================
// RTL generated by Vitis HLS - High-Level Synthesis from C, C++ and OpenCL
// Version: 2020.1
// Copyright (C) 1986-2020 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

`timescale 1 ns / 1 ps 

module rendering_m_projection_odd_m (
        ap_clk,
        ap_rst,
        ap_start,
        ap_done,
        ap_idle,
        ap_ready,
        input_lo,
        input_mi,
        input_hi,
        ap_return_0,
        ap_return_1,
        ap_return_2,
        ap_return_3,
        ap_return_4,
        ap_return_5,
        ap_return_6
);

parameter    ap_ST_fsm_state1 = 2'd1;
parameter    ap_ST_fsm_state2 = 2'd2;

input   ap_clk;
input   ap_rst;
input   ap_start;
output   ap_done;
output   ap_idle;
output   ap_ready;
input  [31:0] input_lo;
input  [31:0] input_mi;
input  [7:0] input_hi;
output  [7:0] ap_return_0;
output  [7:0] ap_return_1;
output  [7:0] ap_return_2;
output  [7:0] ap_return_3;
output  [7:0] ap_return_4;
output  [7:0] ap_return_5;
output  [7:0] ap_return_6;

reg ap_done;
reg ap_idle;
reg ap_ready;

(* fsm_encoding = "none" *) reg   [1:0] ap_CS_fsm;
wire    ap_CS_fsm_state1;
wire   [7:0] trunc_ln674_fu_50_p1;
reg   [7:0] trunc_ln674_reg_235;
reg   [7:0] p_Result_s_reg_240;
reg   [7:0] p_Result_5_reg_245;
wire   [7:0] trunc_ln674_2_fu_84_p1;
reg   [7:0] trunc_ln674_2_reg_250;
reg   [7:0] p_Result_8_reg_255;
reg   [7:0] p_Result_9_reg_260;
reg   [6:0] tmp_reg_265;
reg   [6:0] tmp_3_reg_270;
reg   [6:0] tmp_4_reg_275;
wire   [7:0] p_Result_4_fu_64_p4;
wire   [9:0] mul_ln1368_fu_122_p0;
wire   [7:0] mul_ln1368_fu_122_p1;
wire   [16:0] mul_ln1368_fu_122_p2;
wire   [7:0] p_Result_7_fu_88_p4;
wire   [9:0] mul_ln1368_1_fu_142_p0;
wire   [7:0] mul_ln1368_1_fu_142_p1;
wire   [16:0] mul_ln1368_1_fu_142_p2;
wire   [9:0] mul_ln1368_2_fu_162_p0;
wire   [7:0] mul_ln1368_2_fu_162_p1;
wire   [16:0] mul_ln1368_2_fu_162_p2;
wire    ap_CS_fsm_state2;
wire   [7:0] zext_ln1368_5_fu_184_p1;
wire   [7:0] zext_ln1368_1_fu_178_p1;
wire   [7:0] zext_ln1368_3_fu_181_p1;
wire   [7:0] add_ln216_1_fu_187_p2;
wire   [7:0] add_ln216_fu_193_p2;
reg   [1:0] ap_NS_fsm;
wire   [16:0] mul_ln1368_1_fu_142_p10;
wire   [16:0] mul_ln1368_2_fu_162_p10;
wire   [16:0] mul_ln1368_fu_122_p10;

// power-on initialization
initial begin
#0 ap_CS_fsm = 2'd1;
end

rendering_m_mul_10ns_8ns_17_1_1 #(
    .ID( 1 ),
    .NUM_STAGE( 1 ),
    .din0_WIDTH( 10 ),
    .din1_WIDTH( 8 ),
    .dout_WIDTH( 17 ))
mul_10ns_8ns_17_1_1_U1(
    .din0(mul_ln1368_fu_122_p0),
    .din1(mul_ln1368_fu_122_p1),
    .dout(mul_ln1368_fu_122_p2)
);

rendering_m_mul_10ns_8ns_17_1_1 #(
    .ID( 1 ),
    .NUM_STAGE( 1 ),
    .din0_WIDTH( 10 ),
    .din1_WIDTH( 8 ),
    .dout_WIDTH( 17 ))
mul_10ns_8ns_17_1_1_U2(
    .din0(mul_ln1368_1_fu_142_p0),
    .din1(mul_ln1368_1_fu_142_p1),
    .dout(mul_ln1368_1_fu_142_p2)
);

rendering_m_mul_10ns_8ns_17_1_1 #(
    .ID( 1 ),
    .NUM_STAGE( 1 ),
    .din0_WIDTH( 10 ),
    .din1_WIDTH( 8 ),
    .dout_WIDTH( 17 ))
mul_10ns_8ns_17_1_1_U3(
    .din0(mul_ln1368_2_fu_162_p0),
    .din1(mul_ln1368_2_fu_162_p1),
    .dout(mul_ln1368_2_fu_162_p2)
);

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_CS_fsm <= ap_ST_fsm_state1;
    end else begin
        ap_CS_fsm <= ap_NS_fsm;
    end
end

always @ (posedge ap_clk) begin
    if (((ap_start == 1'b1) & (1'b1 == ap_CS_fsm_state1))) begin
        p_Result_5_reg_245 <= {{input_lo[31:24]}};
        p_Result_8_reg_255 <= {{input_mi[23:16]}};
        p_Result_9_reg_260 <= {{input_mi[31:24]}};
        p_Result_s_reg_240 <= {{input_lo[15:8]}};
        tmp_3_reg_270 <= {{mul_ln1368_1_fu_142_p2[16:10]}};
        tmp_4_reg_275 <= {{mul_ln1368_2_fu_162_p2[16:10]}};
        tmp_reg_265 <= {{mul_ln1368_fu_122_p2[16:10]}};
        trunc_ln674_2_reg_250 <= trunc_ln674_2_fu_84_p1;
        trunc_ln674_reg_235 <= trunc_ln674_fu_50_p1;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state2) | ((ap_start == 1'b0) & (1'b1 == ap_CS_fsm_state1)))) begin
        ap_done = 1'b1;
    end else begin
        ap_done = 1'b0;
    end
end

always @ (*) begin
    if (((ap_start == 1'b0) & (1'b1 == ap_CS_fsm_state1))) begin
        ap_idle = 1'b1;
    end else begin
        ap_idle = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state2)) begin
        ap_ready = 1'b1;
    end else begin
        ap_ready = 1'b0;
    end
end

always @ (*) begin
    case (ap_CS_fsm)
        ap_ST_fsm_state1 : begin
            if (((ap_start == 1'b1) & (1'b1 == ap_CS_fsm_state1))) begin
                ap_NS_fsm = ap_ST_fsm_state2;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state1;
            end
        end
        ap_ST_fsm_state2 : begin
            ap_NS_fsm = ap_ST_fsm_state1;
        end
        default : begin
            ap_NS_fsm = 'bx;
        end
    endcase
end

assign add_ln216_1_fu_187_p2 = (zext_ln1368_5_fu_184_p1 + zext_ln1368_1_fu_178_p1);

assign add_ln216_fu_193_p2 = (zext_ln1368_3_fu_181_p1 + add_ln216_1_fu_187_p2);

assign ap_CS_fsm_state1 = ap_CS_fsm[32'd0];

assign ap_CS_fsm_state2 = ap_CS_fsm[32'd1];

assign ap_return_0 = trunc_ln674_reg_235;

assign ap_return_1 = p_Result_s_reg_240;

assign ap_return_2 = p_Result_5_reg_245;

assign ap_return_3 = trunc_ln674_2_reg_250;

assign ap_return_4 = p_Result_8_reg_255;

assign ap_return_5 = p_Result_9_reg_260;

assign ap_return_6 = add_ln216_fu_193_p2;

assign mul_ln1368_1_fu_142_p0 = 17'd342;

assign mul_ln1368_1_fu_142_p1 = mul_ln1368_1_fu_142_p10;

assign mul_ln1368_1_fu_142_p10 = p_Result_7_fu_88_p4;

assign mul_ln1368_2_fu_162_p0 = 17'd342;

assign mul_ln1368_2_fu_162_p1 = mul_ln1368_2_fu_162_p10;

assign mul_ln1368_2_fu_162_p10 = input_hi;

assign mul_ln1368_fu_122_p0 = 17'd342;

assign mul_ln1368_fu_122_p1 = mul_ln1368_fu_122_p10;

assign mul_ln1368_fu_122_p10 = p_Result_4_fu_64_p4;

assign p_Result_4_fu_64_p4 = {{input_lo[23:16]}};

assign p_Result_7_fu_88_p4 = {{input_mi[15:8]}};

assign trunc_ln674_2_fu_84_p1 = input_mi[7:0];

assign trunc_ln674_fu_50_p1 = input_lo[7:0];

assign zext_ln1368_1_fu_178_p1 = tmp_reg_265;

assign zext_ln1368_3_fu_181_p1 = tmp_3_reg_270;

assign zext_ln1368_5_fu_184_p1 = tmp_4_reg_275;

endmodule //rendering_m_projection_odd_m
// ==============================================================
// RTL generated by Vitis HLS - High-Level Synthesis from C, C++ and OpenCL
// Version: 2020.1
// Copyright (C) 1986-2020 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

`timescale 1 ns / 1 ps 

module rendering_m_rasterization1_odd_m (
        ap_clk,
        ap_rst,
        ap_start,
        ap_done,
        ap_idle,
        ap_ready,
        Output_redir_odd25_din,
        Output_redir_odd25_full_n,
        Output_redir_odd25_write,
        triangle_2d_0,
        triangle_2d_1,
        triangle_2d_2,
        triangle_2d_3,
        triangle_2d_4,
        triangle_2d_5,
        triangle_2d_6
);

parameter    ap_ST_fsm_state1 = 7'd1;
parameter    ap_ST_fsm_state2 = 7'd2;
parameter    ap_ST_fsm_state3 = 7'd4;
parameter    ap_ST_fsm_state4 = 7'd8;
parameter    ap_ST_fsm_state5 = 7'd16;
parameter    ap_ST_fsm_state6 = 7'd32;
parameter    ap_ST_fsm_state7 = 7'd64;

input   ap_clk;
input   ap_rst;
input   ap_start;
output   ap_done;
output   ap_idle;
output   ap_ready;
output  [31:0] Output_redir_odd25_din;
input   Output_redir_odd25_full_n;
output   Output_redir_odd25_write;
input  [7:0] triangle_2d_0;
input  [7:0] triangle_2d_1;
input  [7:0] triangle_2d_2;
input  [7:0] triangle_2d_3;
input  [7:0] triangle_2d_4;
input  [7:0] triangle_2d_5;
input  [7:0] triangle_2d_6;

reg ap_done;
reg ap_idle;
reg ap_ready;
reg[31:0] Output_redir_odd25_din;
reg Output_redir_odd25_write;

(* fsm_encoding = "none" *) reg   [6:0] ap_CS_fsm;
wire    ap_CS_fsm_state1;
reg   [15:0] max_index;
reg   [7:0] max_min_0;
reg   [7:0] max_min_1;
reg   [7:0] max_min_2;
reg   [7:0] max_min_3;
reg   [7:0] max_min_4;
reg    Output_redir_odd25_blk_n;
wire    ap_CS_fsm_state2;
wire   [0:0] icmp_ln208_fu_183_p2;
wire    ap_CS_fsm_state6;
wire    ap_CS_fsm_state7;
wire    ap_CS_fsm_state5;
reg   [0:0] icmp_ln208_reg_604;
wire    ap_CS_fsm_state3;
wire    ap_CS_fsm_state4;
wire   [17:0] mul_ln1349_fu_139_p2;
reg   [17:0] mul_ln1349_reg_587;
wire   [17:0] mul_ln1349_1_fu_173_p2;
reg   [17:0] mul_ln1349_1_reg_593;
reg    ap_block_state2;
wire   [7:0] triangle_2d_same_y1_V_fu_195_p3;
reg   [7:0] triangle_2d_same_y1_V_reg_608;
wire   [7:0] rhs_V_fu_249_p3;
reg   [7:0] rhs_V_reg_613;
wire   [7:0] lhs_V_fu_293_p3;
reg   [7:0] lhs_V_reg_619;
wire   [7:0] rhs_V_9_fu_337_p3;
reg   [7:0] rhs_V_9_reg_625;
wire   [7:0] lhs_V_9_fu_381_p3;
reg   [7:0] lhs_V_9_reg_631;
wire   [7:0] trunc_ln216_fu_420_p1;
reg   [7:0] trunc_ln216_reg_637;
wire   [15:0] mul_ln216_fu_450_p2;
reg   [15:0] mul_ln216_reg_642;
wire   [31:0] p_Result_6_fu_395_p5;
wire   [31:0] p_Result_7_fu_462_p5;
wire   [31:0] p_Result_8_fu_471_p4;
wire   [31:0] p_Result_9_fu_479_p5;
reg    ap_block_state5;
wire   [31:0] p_Result_s_fu_501_p5;
wire   [31:0] p_Result_5_fu_526_p4;
wire   [8:0] zext_ln215_fu_103_p1;
wire   [8:0] zext_ln1351_fu_107_p1;
wire   [8:0] zext_ln215_1_fu_117_p1;
wire   [8:0] zext_ln1351_1_fu_121_p1;
wire  signed [8:0] sub_ln1351_fu_111_p2;
wire  signed [8:0] sub_ln1351_1_fu_125_p2;
wire   [8:0] zext_ln1351_2_fu_145_p1;
wire   [8:0] zext_ln1351_3_fu_155_p1;
wire  signed [8:0] sub_ln1351_2_fu_149_p2;
wire  signed [8:0] sub_ln1351_3_fu_159_p2;
wire   [17:0] sub_ln1351_4_fu_179_p2;
wire   [0:0] tmp_fu_187_p3;
wire   [7:0] triangle_2d_same_x0_V_fu_213_p3;
wire   [7:0] triangle_2d_same_x1_V_fu_201_p3;
wire   [0:0] icmp_ln882_4_fu_225_p2;
wire   [0:0] icmp_ln882_5_fu_237_p2;
wire   [0:0] icmp_ln882_fu_219_p2;
wire   [7:0] select_ln119_fu_230_p3;
wire   [7:0] select_ln126_fu_242_p3;
wire   [0:0] icmp_ln890_1_fu_269_p2;
wire   [0:0] icmp_ln890_2_fu_281_p2;
wire   [0:0] icmp_ln890_fu_263_p2;
wire   [7:0] select_ln100_fu_274_p3;
wire   [7:0] select_ln107_fu_286_p3;
wire   [7:0] triangle_2d_same_y0_V_fu_207_p3;
wire   [0:0] icmp_ln882_7_fu_313_p2;
wire   [0:0] icmp_ln882_8_fu_325_p2;
wire   [0:0] icmp_ln882_6_fu_307_p2;
wire   [7:0] select_ln119_1_fu_318_p3;
wire   [7:0] select_ln126_1_fu_330_p3;
wire   [0:0] icmp_ln890_4_fu_357_p2;
wire   [0:0] icmp_ln890_5_fu_369_p2;
wire   [0:0] icmp_ln890_3_fu_351_p2;
wire   [7:0] select_ln100_1_fu_362_p3;
wire   [7:0] select_ln107_1_fu_374_p3;
wire   [8:0] zext_ln215_2_fu_408_p1;
wire   [8:0] zext_ln215_3_fu_411_p1;
wire  signed [8:0] ret_V_fu_414_p2;
wire   [8:0] zext_ln215_4_fu_430_p1;
wire   [8:0] zext_ln215_5_fu_433_p1;
wire  signed [8:0] ret_V_37_fu_436_p2;
reg   [6:0] ap_NS_fsm;

// power-on initialization
initial begin
#0 ap_CS_fsm = 7'd1;
#0 max_index = 16'd0;
#0 max_min_0 = 8'd0;
#0 max_min_1 = 8'd0;
#0 max_min_2 = 8'd0;
#0 max_min_3 = 8'd0;
#0 max_min_4 = 8'd0;
end

rendering_m_mul_9s_9s_18_1_1 #(
    .ID( 1 ),
    .NUM_STAGE( 1 ),
    .din0_WIDTH( 9 ),
    .din1_WIDTH( 9 ),
    .dout_WIDTH( 18 ))
mul_9s_9s_18_1_1_U8(
    .din0(sub_ln1351_fu_111_p2),
    .din1(sub_ln1351_1_fu_125_p2),
    .dout(mul_ln1349_fu_139_p2)
);

rendering_m_mul_9s_9s_18_1_1 #(
    .ID( 1 ),
    .NUM_STAGE( 1 ),
    .din0_WIDTH( 9 ),
    .din1_WIDTH( 9 ),
    .dout_WIDTH( 18 ))
mul_9s_9s_18_1_1_U9(
    .din0(sub_ln1351_2_fu_149_p2),
    .din1(sub_ln1351_3_fu_159_p2),
    .dout(mul_ln1349_1_fu_173_p2)
);

rendering_m_mul_9s_9s_16_1_1 #(
    .ID( 1 ),
    .NUM_STAGE( 1 ),
    .din0_WIDTH( 9 ),
    .din1_WIDTH( 9 ),
    .dout_WIDTH( 16 ))
mul_9s_9s_16_1_1_U10(
    .din0(ret_V_fu_414_p2),
    .din1(ret_V_37_fu_436_p2),
    .dout(mul_ln216_fu_450_p2)
);

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_CS_fsm <= ap_ST_fsm_state1;
    end else begin
        ap_CS_fsm <= ap_NS_fsm;
    end
end

always @ (posedge ap_clk) begin
    if ((~(((icmp_ln208_fu_183_p2 == 1'd0) & (1'b0 == Output_redir_odd25_full_n)) | ((icmp_ln208_fu_183_p2 == 1'd1) & (1'b0 == Output_redir_odd25_full_n))) & (1'b1 == ap_CS_fsm_state2))) begin
        icmp_ln208_reg_604 <= icmp_ln208_fu_183_p2;
    end
end

always @ (posedge ap_clk) begin
    if ((~(((icmp_ln208_fu_183_p2 == 1'd0) & (1'b0 == Output_redir_odd25_full_n)) | ((icmp_ln208_fu_183_p2 == 1'd1) & (1'b0 == Output_redir_odd25_full_n))) & (icmp_ln208_fu_183_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state2))) begin
        lhs_V_9_reg_631 <= lhs_V_9_fu_381_p3;
        lhs_V_reg_619 <= lhs_V_fu_293_p3;
        max_min_0 <= rhs_V_fu_249_p3;
        max_min_1 <= lhs_V_fu_293_p3;
        max_min_2 <= rhs_V_9_fu_337_p3;
        max_min_3 <= lhs_V_9_fu_381_p3;
        rhs_V_9_reg_625 <= rhs_V_9_fu_337_p3;
        rhs_V_reg_613 <= rhs_V_fu_249_p3;
        triangle_2d_same_y1_V_reg_608 <= triangle_2d_same_y1_V_fu_195_p3;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == ap_CS_fsm_state3) & (1'b1 == Output_redir_odd25_full_n))) begin
        max_index <= mul_ln216_fu_450_p2;
        max_min_4 <= trunc_ln216_fu_420_p1;
        mul_ln216_reg_642 <= mul_ln216_fu_450_p2;
        trunc_ln216_reg_637 <= trunc_ln216_fu_420_p1;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b1))) begin
        mul_ln1349_1_reg_593 <= mul_ln1349_1_fu_173_p2;
        mul_ln1349_reg_587 <= mul_ln1349_fu_139_p2;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state4) | (1'b1 == ap_CS_fsm_state3) | (1'b1 == ap_CS_fsm_state7) | (1'b1 == ap_CS_fsm_state6) | ((icmp_ln208_reg_604 == 1'd0) & (1'b1 == ap_CS_fsm_state5)) | ((icmp_ln208_fu_183_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state2)) | ((icmp_ln208_reg_604 == 1'd1) & (1'b1 == ap_CS_fsm_state5)) | ((icmp_ln208_fu_183_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state2)))) begin
        Output_redir_odd25_blk_n = Output_redir_odd25_full_n;
    end else begin
        Output_redir_odd25_blk_n = 1'b1;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state7) & (1'b1 == Output_redir_odd25_full_n))) begin
        Output_redir_odd25_din = p_Result_5_fu_526_p4;
    end else if (((1'b1 == ap_CS_fsm_state6) & (1'b1 == Output_redir_odd25_full_n))) begin
        Output_redir_odd25_din = 32'd0;
    end else if ((~(((icmp_ln208_reg_604 == 1'd0) & (1'b0 == Output_redir_odd25_full_n)) | ((icmp_ln208_reg_604 == 1'd1) & (1'b0 == Output_redir_odd25_full_n))) & (icmp_ln208_reg_604 == 1'd1) & (1'b1 == ap_CS_fsm_state5))) begin
        Output_redir_odd25_din = p_Result_s_fu_501_p5;
    end else if ((~(((icmp_ln208_reg_604 == 1'd0) & (1'b0 == Output_redir_odd25_full_n)) | ((icmp_ln208_reg_604 == 1'd1) & (1'b0 == Output_redir_odd25_full_n))) & (icmp_ln208_reg_604 == 1'd0) & (1'b1 == ap_CS_fsm_state5))) begin
        Output_redir_odd25_din = p_Result_9_fu_479_p5;
    end else if (((1'b1 == ap_CS_fsm_state4) & (1'b1 == Output_redir_odd25_full_n))) begin
        Output_redir_odd25_din = p_Result_8_fu_471_p4;
    end else if (((1'b1 == ap_CS_fsm_state3) & (1'b1 == Output_redir_odd25_full_n))) begin
        Output_redir_odd25_din = p_Result_7_fu_462_p5;
    end else if ((~(((icmp_ln208_fu_183_p2 == 1'd0) & (1'b0 == Output_redir_odd25_full_n)) | ((icmp_ln208_fu_183_p2 == 1'd1) & (1'b0 == Output_redir_odd25_full_n))) & (icmp_ln208_fu_183_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state2))) begin
        Output_redir_odd25_din = 32'd1;
    end else if ((~(((icmp_ln208_fu_183_p2 == 1'd0) & (1'b0 == Output_redir_odd25_full_n)) | ((icmp_ln208_fu_183_p2 == 1'd1) & (1'b0 == Output_redir_odd25_full_n))) & (icmp_ln208_fu_183_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state2))) begin
        Output_redir_odd25_din = p_Result_6_fu_395_p5;
    end else begin
        Output_redir_odd25_din = 'bx;
    end
end

always @ (*) begin
    if ((((1'b1 == ap_CS_fsm_state4) & (1'b1 == Output_redir_odd25_full_n)) | ((1'b1 == ap_CS_fsm_state3) & (1'b1 == Output_redir_odd25_full_n)) | ((1'b1 == ap_CS_fsm_state7) & (1'b1 == Output_redir_odd25_full_n)) | ((1'b1 == ap_CS_fsm_state6) & (1'b1 == Output_redir_odd25_full_n)) | (~(((icmp_ln208_reg_604 == 1'd0) & (1'b0 == Output_redir_odd25_full_n)) | ((icmp_ln208_reg_604 == 1'd1) & (1'b0 == Output_redir_odd25_full_n))) & (icmp_ln208_reg_604 == 1'd0) & (1'b1 == ap_CS_fsm_state5)) | (~(((icmp_ln208_reg_604 == 1'd0) & (1'b0 == Output_redir_odd25_full_n)) | ((icmp_ln208_reg_604 == 1'd1) & (1'b0 == Output_redir_odd25_full_n))) & (icmp_ln208_reg_604 == 1'd1) & (1'b1 == ap_CS_fsm_state5)) | (~(((icmp_ln208_fu_183_p2 == 1'd0) & (1'b0 == Output_redir_odd25_full_n)) | ((icmp_ln208_fu_183_p2 == 1'd1) & (1'b0 == Output_redir_odd25_full_n))) & (icmp_ln208_fu_183_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state2)) | (~(((icmp_ln208_fu_183_p2 == 1'd0) & (1'b0 == Output_redir_odd25_full_n)) | ((icmp_ln208_fu_183_p2 == 1'd1) & (1'b0 == Output_redir_odd25_full_n))) & (icmp_ln208_fu_183_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state2)))) begin
        Output_redir_odd25_write = 1'b1;
    end else begin
        Output_redir_odd25_write = 1'b0;
    end
end

always @ (*) begin
    if ((((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b0)) | (~(((icmp_ln208_reg_604 == 1'd0) & (1'b0 == Output_redir_odd25_full_n)) | ((icmp_ln208_reg_604 == 1'd1) & (1'b0 == Output_redir_odd25_full_n))) & (1'b1 == ap_CS_fsm_state5)))) begin
        ap_done = 1'b1;
    end else begin
        ap_done = 1'b0;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b0))) begin
        ap_idle = 1'b1;
    end else begin
        ap_idle = 1'b0;
    end
end

always @ (*) begin
    if ((~(((icmp_ln208_reg_604 == 1'd0) & (1'b0 == Output_redir_odd25_full_n)) | ((icmp_ln208_reg_604 == 1'd1) & (1'b0 == Output_redir_odd25_full_n))) & (1'b1 == ap_CS_fsm_state5))) begin
        ap_ready = 1'b1;
    end else begin
        ap_ready = 1'b0;
    end
end

always @ (*) begin
    case (ap_CS_fsm)
        ap_ST_fsm_state1 : begin
            if (((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b1))) begin
                ap_NS_fsm = ap_ST_fsm_state2;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state1;
            end
        end
        ap_ST_fsm_state2 : begin
            if ((~(((icmp_ln208_fu_183_p2 == 1'd0) & (1'b0 == Output_redir_odd25_full_n)) | ((icmp_ln208_fu_183_p2 == 1'd1) & (1'b0 == Output_redir_odd25_full_n))) & (icmp_ln208_fu_183_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state2))) begin
                ap_NS_fsm = ap_ST_fsm_state6;
            end else if ((~(((icmp_ln208_fu_183_p2 == 1'd0) & (1'b0 == Output_redir_odd25_full_n)) | ((icmp_ln208_fu_183_p2 == 1'd1) & (1'b0 == Output_redir_odd25_full_n))) & (icmp_ln208_fu_183_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state2))) begin
                ap_NS_fsm = ap_ST_fsm_state3;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state2;
            end
        end
        ap_ST_fsm_state3 : begin
            if (((1'b1 == ap_CS_fsm_state3) & (1'b1 == Output_redir_odd25_full_n))) begin
                ap_NS_fsm = ap_ST_fsm_state4;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state3;
            end
        end
        ap_ST_fsm_state4 : begin
            if (((1'b1 == ap_CS_fsm_state4) & (1'b1 == Output_redir_odd25_full_n))) begin
                ap_NS_fsm = ap_ST_fsm_state5;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state4;
            end
        end
        ap_ST_fsm_state5 : begin
            if ((~(((icmp_ln208_reg_604 == 1'd0) & (1'b0 == Output_redir_odd25_full_n)) | ((icmp_ln208_reg_604 == 1'd1) & (1'b0 == Output_redir_odd25_full_n))) & (1'b1 == ap_CS_fsm_state5))) begin
                ap_NS_fsm = ap_ST_fsm_state1;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state5;
            end
        end
        ap_ST_fsm_state6 : begin
            if (((1'b1 == ap_CS_fsm_state6) & (1'b1 == Output_redir_odd25_full_n))) begin
                ap_NS_fsm = ap_ST_fsm_state7;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state6;
            end
        end
        ap_ST_fsm_state7 : begin
            if (((1'b1 == ap_CS_fsm_state7) & (1'b1 == Output_redir_odd25_full_n))) begin
                ap_NS_fsm = ap_ST_fsm_state5;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state7;
            end
        end
        default : begin
            ap_NS_fsm = 'bx;
        end
    endcase
end

assign ap_CS_fsm_state1 = ap_CS_fsm[32'd0];

assign ap_CS_fsm_state2 = ap_CS_fsm[32'd1];

assign ap_CS_fsm_state3 = ap_CS_fsm[32'd2];

assign ap_CS_fsm_state4 = ap_CS_fsm[32'd3];

assign ap_CS_fsm_state5 = ap_CS_fsm[32'd4];

assign ap_CS_fsm_state6 = ap_CS_fsm[32'd5];

assign ap_CS_fsm_state7 = ap_CS_fsm[32'd6];

always @ (*) begin
    ap_block_state2 = (((icmp_ln208_fu_183_p2 == 1'd0) & (1'b0 == Output_redir_odd25_full_n)) | ((icmp_ln208_fu_183_p2 == 1'd1) & (1'b0 == Output_redir_odd25_full_n)));
end

always @ (*) begin
    ap_block_state5 = (((icmp_ln208_reg_604 == 1'd0) & (1'b0 == Output_redir_odd25_full_n)) | ((icmp_ln208_reg_604 == 1'd1) & (1'b0 == Output_redir_odd25_full_n)));
end

assign icmp_ln208_fu_183_p2 = ((mul_ln1349_reg_587 == mul_ln1349_1_reg_593) ? 1'b1 : 1'b0);

assign icmp_ln882_4_fu_225_p2 = ((triangle_2d_same_x0_V_fu_213_p3 < triangle_2d_4) ? 1'b1 : 1'b0);

assign icmp_ln882_5_fu_237_p2 = ((triangle_2d_same_x1_V_fu_201_p3 < triangle_2d_4) ? 1'b1 : 1'b0);

assign icmp_ln882_6_fu_307_p2 = ((triangle_2d_same_y0_V_fu_207_p3 < triangle_2d_same_y1_V_fu_195_p3) ? 1'b1 : 1'b0);

assign icmp_ln882_7_fu_313_p2 = ((triangle_2d_same_y0_V_fu_207_p3 < triangle_2d_5) ? 1'b1 : 1'b0);

assign icmp_ln882_8_fu_325_p2 = ((triangle_2d_same_y1_V_fu_195_p3 < triangle_2d_5) ? 1'b1 : 1'b0);

assign icmp_ln882_fu_219_p2 = ((triangle_2d_same_x0_V_fu_213_p3 < triangle_2d_same_x1_V_fu_201_p3) ? 1'b1 : 1'b0);

assign icmp_ln890_1_fu_269_p2 = ((triangle_2d_same_x0_V_fu_213_p3 > triangle_2d_4) ? 1'b1 : 1'b0);

assign icmp_ln890_2_fu_281_p2 = ((triangle_2d_same_x1_V_fu_201_p3 > triangle_2d_4) ? 1'b1 : 1'b0);

assign icmp_ln890_3_fu_351_p2 = ((triangle_2d_same_y0_V_fu_207_p3 > triangle_2d_same_y1_V_fu_195_p3) ? 1'b1 : 1'b0);

assign icmp_ln890_4_fu_357_p2 = ((triangle_2d_same_y0_V_fu_207_p3 > triangle_2d_5) ? 1'b1 : 1'b0);

assign icmp_ln890_5_fu_369_p2 = ((triangle_2d_same_y1_V_fu_195_p3 > triangle_2d_5) ? 1'b1 : 1'b0);

assign icmp_ln890_fu_263_p2 = ((triangle_2d_same_x0_V_fu_213_p3 > triangle_2d_same_x1_V_fu_201_p3) ? 1'b1 : 1'b0);

assign lhs_V_9_fu_381_p3 = ((icmp_ln890_3_fu_351_p2[0:0] === 1'b1) ? select_ln100_1_fu_362_p3 : select_ln107_1_fu_374_p3);

assign lhs_V_fu_293_p3 = ((icmp_ln890_fu_263_p2[0:0] === 1'b1) ? select_ln100_fu_274_p3 : select_ln107_fu_286_p3);

assign p_Result_5_fu_526_p4 = {{{max_min_1}, {max_min_0}}, {max_index}};

assign p_Result_6_fu_395_p5 = {{{{triangle_2d_same_x1_V_fu_201_p3}, {triangle_2d_same_y0_V_fu_207_p3}}, {triangle_2d_same_x0_V_fu_213_p3}}, {8'd0}};

assign p_Result_7_fu_462_p5 = {{{{triangle_2d_6}, {triangle_2d_5}}, {triangle_2d_4}}, {triangle_2d_same_y1_V_reg_608}};

assign p_Result_8_fu_471_p4 = {{{lhs_V_reg_619}, {rhs_V_reg_613}}, {mul_ln216_reg_642}};

assign p_Result_9_fu_479_p5 = {{{{{{8'd0}, {trunc_ln216_reg_637}}}, {lhs_V_9_reg_631}}}, {rhs_V_9_reg_625}};

assign p_Result_s_fu_501_p5 = {{{{{{8'd0}, {max_min_4}}}, {max_min_3}}}, {max_min_2}};

assign ret_V_37_fu_436_p2 = (zext_ln215_4_fu_430_p1 - zext_ln215_5_fu_433_p1);

assign ret_V_fu_414_p2 = (zext_ln215_2_fu_408_p1 - zext_ln215_3_fu_411_p1);

assign rhs_V_9_fu_337_p3 = ((icmp_ln882_6_fu_307_p2[0:0] === 1'b1) ? select_ln119_1_fu_318_p3 : select_ln126_1_fu_330_p3);

assign rhs_V_fu_249_p3 = ((icmp_ln882_fu_219_p2[0:0] === 1'b1) ? select_ln119_fu_230_p3 : select_ln126_fu_242_p3);

assign select_ln100_1_fu_362_p3 = ((icmp_ln890_4_fu_357_p2[0:0] === 1'b1) ? triangle_2d_same_y0_V_fu_207_p3 : triangle_2d_5);

assign select_ln100_fu_274_p3 = ((icmp_ln890_1_fu_269_p2[0:0] === 1'b1) ? triangle_2d_same_x0_V_fu_213_p3 : triangle_2d_4);

assign select_ln107_1_fu_374_p3 = ((icmp_ln890_5_fu_369_p2[0:0] === 1'b1) ? triangle_2d_same_y1_V_fu_195_p3 : triangle_2d_5);

assign select_ln107_fu_286_p3 = ((icmp_ln890_2_fu_281_p2[0:0] === 1'b1) ? triangle_2d_same_x1_V_fu_201_p3 : triangle_2d_4);

assign select_ln119_1_fu_318_p3 = ((icmp_ln882_7_fu_313_p2[0:0] === 1'b1) ? triangle_2d_same_y0_V_fu_207_p3 : triangle_2d_5);

assign select_ln119_fu_230_p3 = ((icmp_ln882_4_fu_225_p2[0:0] === 1'b1) ? triangle_2d_same_x0_V_fu_213_p3 : triangle_2d_4);

assign select_ln126_1_fu_330_p3 = ((icmp_ln882_8_fu_325_p2[0:0] === 1'b1) ? triangle_2d_same_y1_V_fu_195_p3 : triangle_2d_5);

assign select_ln126_fu_242_p3 = ((icmp_ln882_5_fu_237_p2[0:0] === 1'b1) ? triangle_2d_same_x1_V_fu_201_p3 : triangle_2d_4);

assign sub_ln1351_1_fu_125_p2 = (zext_ln215_1_fu_117_p1 - zext_ln1351_1_fu_121_p1);

assign sub_ln1351_2_fu_149_p2 = (zext_ln1351_2_fu_145_p1 - zext_ln1351_1_fu_121_p1);

assign sub_ln1351_3_fu_159_p2 = (zext_ln1351_3_fu_155_p1 - zext_ln1351_fu_107_p1);

assign sub_ln1351_4_fu_179_p2 = (mul_ln1349_reg_587 - mul_ln1349_1_reg_593);

assign sub_ln1351_fu_111_p2 = (zext_ln215_fu_103_p1 - zext_ln1351_fu_107_p1);

assign tmp_fu_187_p3 = sub_ln1351_4_fu_179_p2[32'd17];

assign triangle_2d_same_x0_V_fu_213_p3 = ((tmp_fu_187_p3[0:0] === 1'b1) ? triangle_2d_2 : triangle_2d_0);

assign triangle_2d_same_x1_V_fu_201_p3 = ((tmp_fu_187_p3[0:0] === 1'b1) ? triangle_2d_0 : triangle_2d_2);

assign triangle_2d_same_y0_V_fu_207_p3 = ((tmp_fu_187_p3[0:0] === 1'b1) ? triangle_2d_3 : triangle_2d_1);

assign triangle_2d_same_y1_V_fu_195_p3 = ((tmp_fu_187_p3[0:0] === 1'b1) ? triangle_2d_1 : triangle_2d_3);

assign trunc_ln216_fu_420_p1 = ret_V_fu_414_p2[7:0];

assign zext_ln1351_1_fu_121_p1 = triangle_2d_1;

assign zext_ln1351_2_fu_145_p1 = triangle_2d_5;

assign zext_ln1351_3_fu_155_p1 = triangle_2d_2;

assign zext_ln1351_fu_107_p1 = triangle_2d_0;

assign zext_ln215_1_fu_117_p1 = triangle_2d_3;

assign zext_ln215_2_fu_408_p1 = lhs_V_reg_619;

assign zext_ln215_3_fu_411_p1 = rhs_V_reg_613;

assign zext_ln215_4_fu_430_p1 = lhs_V_9_reg_631;

assign zext_ln215_5_fu_433_p1 = rhs_V_9_reg_625;

assign zext_ln215_fu_103_p1 = triangle_2d_4;

endmodule //rendering_m_rasterization1_odd_m
// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.1 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
`timescale 1 ns / 1 ps
module rendering_m_rasterization2_odd_fragment_color_V_ram (addr0, ce0, d0, we0, q0,  clk);

parameter DWIDTH = 6;
parameter AWIDTH = 9;
parameter MEM_SIZE = 500;

input[AWIDTH-1:0] addr0;
input ce0;
input[DWIDTH-1:0] d0;
input we0;
output reg[DWIDTH-1:0] q0;
input clk;

(* ram_style = "block" *)reg [DWIDTH-1:0] ram[0:MEM_SIZE-1];

initial begin
    $readmemh("./rendering_m_rasterization2_odd_fragment_color_V_ram.dat", ram);
end



always @(posedge clk)  
begin 
    if (ce0) begin
        if (we0) 
            ram[addr0] <= d0; 
        q0 <= ram[addr0];
    end
end


endmodule

`timescale 1 ns / 1 ps
module rendering_m_rasterization2_odd_fragment_color_V(
    reset,
    clk,
    address0,
    ce0,
    we0,
    d0,
    q0);

parameter DataWidth = 32'd6;
parameter AddressRange = 32'd500;
parameter AddressWidth = 32'd9;
input reset;
input clk;
input[AddressWidth - 1:0] address0;
input ce0;
input we0;
input[DataWidth - 1:0] d0;
output[DataWidth - 1:0] q0;



rendering_m_rasterization2_odd_fragment_color_V_ram rendering_m_rasterization2_odd_fragment_color_V_ram_U(
    .clk( clk ),
    .addr0( address0 ),
    .ce0( ce0 ),
    .we0( we0 ),
    .d0( d0 ),
    .q0( q0 ));

endmodule

// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.1 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
`timescale 1 ns / 1 ps
module rendering_m_rasterization2_odd_fragment_x_V_ram (addr0, ce0, d0, we0, q0,  clk);

parameter DWIDTH = 8;
parameter AWIDTH = 9;
parameter MEM_SIZE = 500;

input[AWIDTH-1:0] addr0;
input ce0;
input[DWIDTH-1:0] d0;
input we0;
output reg[DWIDTH-1:0] q0;
input clk;

(* ram_style = "block" *)reg [DWIDTH-1:0] ram[0:MEM_SIZE-1];

initial begin
    $readmemh("./rendering_m_rasterization2_odd_fragment_x_V_ram.dat", ram);
end



always @(posedge clk)  
begin 
    if (ce0) begin
        if (we0) 
            ram[addr0] <= d0; 
        q0 <= ram[addr0];
    end
end


endmodule

`timescale 1 ns / 1 ps
module rendering_m_rasterization2_odd_fragment_x_V(
    reset,
    clk,
    address0,
    ce0,
    we0,
    d0,
    q0);

parameter DataWidth = 32'd8;
parameter AddressRange = 32'd500;
parameter AddressWidth = 32'd9;
input reset;
input clk;
input[AddressWidth - 1:0] address0;
input ce0;
input we0;
input[DataWidth - 1:0] d0;
output[DataWidth - 1:0] q0;



rendering_m_rasterization2_odd_fragment_x_V_ram rendering_m_rasterization2_odd_fragment_x_V_ram_U(
    .clk( clk ),
    .addr0( address0 ),
    .ce0( ce0 ),
    .we0( we0 ),
    .d0( d0 ),
    .q0( q0 ));

endmodule

// ==============================================================
// RTL generated by Vitis HLS - High-Level Synthesis from C, C++ and OpenCL
// Version: 2020.1
// Copyright (C) 1986-2020 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

`timescale 1 ns / 1 ps 

module rendering_m_rasterization2_odd (
        ap_clk,
        ap_rst,
        ap_start,
        ap_done,
        ap_idle,
        ap_ready,
        Input_1_dout,
        Input_1_empty_n,
        Input_1_read,
        Output_1_din,
        Output_1_full_n,
        Output_1_write
);

parameter    ap_ST_fsm_state1 = 8'd1;
parameter    ap_ST_fsm_state2 = 8'd2;
parameter    ap_ST_fsm_state3 = 8'd4;
parameter    ap_ST_fsm_state4 = 8'd8;
parameter    ap_ST_fsm_pp0_stage0 = 8'd16;
parameter    ap_ST_fsm_state29 = 8'd32;
parameter    ap_ST_fsm_pp1_stage0 = 8'd64;
parameter    ap_ST_fsm_state32 = 8'd128;

input   ap_clk;
input   ap_rst;
input   ap_start;
output   ap_done;
output   ap_idle;
output   ap_ready;
input  [31:0] Input_1_dout;
input   Input_1_empty_n;
output   Input_1_read;
output  [31:0] Output_1_din;
input   Output_1_full_n;
output   Output_1_write;

reg ap_done;
reg ap_idle;
reg ap_ready;
reg Input_1_read;
reg[31:0] Output_1_din;
reg Output_1_write;

(* fsm_encoding = "none" *) reg   [7:0] ap_CS_fsm;
wire    ap_CS_fsm_state1;
reg   [8:0] fragment_x_V_address0;
reg    fragment_x_V_ce0;
reg    fragment_x_V_we0;
wire   [7:0] fragment_x_V_q0;
reg   [8:0] fragment_y_V_address0;
reg    fragment_y_V_ce0;
reg    fragment_y_V_we0;
wire   [7:0] fragment_y_V_q0;
reg   [8:0] fragment_z_V_address0;
reg    fragment_z_V_ce0;
reg    fragment_z_V_we0;
wire   [7:0] fragment_z_V_q0;
reg   [8:0] fragment_color_V_address0;
reg    fragment_color_V_ce0;
reg    fragment_color_V_we0;
wire   [5:0] fragment_color_V_q0;
reg    Input_1_blk_n;
wire    ap_CS_fsm_state2;
wire    ap_CS_fsm_state3;
wire    ap_CS_fsm_state4;
reg    Output_1_blk_n;
reg   [0:0] icmp_ln358_reg_597;
wire    ap_CS_fsm_state29;
wire    ap_CS_fsm_pp1_stage0;
reg    ap_enable_reg_pp1_iter1;
wire    ap_block_pp1_stage0;
reg   [0:0] icmp_ln882_3_reg_789;
reg   [15:0] empty_reg_175;
wire    ap_CS_fsm_pp0_stage0;
wire    ap_block_state5_pp0_stage0_iter0;
wire    ap_block_state6_pp0_stage0_iter1;
wire    ap_block_state7_pp0_stage0_iter2;
wire    ap_block_state8_pp0_stage0_iter3;
wire    ap_block_state9_pp0_stage0_iter4;
wire    ap_block_state10_pp0_stage0_iter5;
wire    ap_block_state11_pp0_stage0_iter6;
wire    ap_block_state12_pp0_stage0_iter7;
wire    ap_block_state13_pp0_stage0_iter8;
wire    ap_block_state14_pp0_stage0_iter9;
wire    ap_block_state15_pp0_stage0_iter10;
wire    ap_block_state16_pp0_stage0_iter11;
wire    ap_block_state17_pp0_stage0_iter12;
wire    ap_block_state18_pp0_stage0_iter13;
wire    ap_block_state19_pp0_stage0_iter14;
wire    ap_block_state20_pp0_stage0_iter15;
wire    ap_block_state21_pp0_stage0_iter16;
wire    ap_block_state22_pp0_stage0_iter17;
wire    ap_block_state23_pp0_stage0_iter18;
wire    ap_block_state24_pp0_stage0_iter19;
wire    ap_block_state25_pp0_stage0_iter20;
wire    ap_block_state26_pp0_stage0_iter21;
wire    ap_block_state27_pp0_stage0_iter22;
wire    ap_block_state28_pp0_stage0_iter23;
wire    ap_block_pp0_stage0_11001;
reg   [15:0] j_reg_187;
reg   [7:0] triangle_2d_same_x0_V_reg_582;
reg    ap_block_state1;
wire   [7:0] grp_fu_208_p4;
reg   [7:0] triangle_2d_same_y0_V_reg_587;
reg   [7:0] triangle_2d_same_x1_V_reg_592;
wire   [0:0] icmp_ln358_fu_238_p2;
wire   [7:0] triangle_2d_same_y1_V_fu_244_p1;
reg   [7:0] triangle_2d_same_y1_V_reg_601;
reg   [7:0] triangle_2d_same_x2_V_reg_606;
reg   [7:0] triangle_2d_same_y2_V_reg_611;
reg   [7:0] triangle_2d_same_z_V_reg_616;
wire   [15:0] trunc_ln674_fu_248_p1;
reg   [15:0] trunc_ln674_reg_621;
reg   [7:0] max_min_V_reg_626;
wire   [7:0] max_min_V_1_fu_252_p1;
reg   [7:0] max_min_V_1_reg_631;
reg    ap_block_state4;
wire   [15:0] zext_ln1368_fu_256_p1;
reg   [15:0] zext_ln1368_reg_650;
wire   [8:0] zext_ln1351_fu_260_p1;
reg   [8:0] zext_ln1351_reg_656;
wire   [8:0] zext_ln1351_1_fu_263_p1;
reg   [8:0] zext_ln1351_1_reg_661;
wire   [8:0] zext_ln1351_2_fu_266_p1;
reg   [8:0] zext_ln1351_2_reg_666;
wire  signed [17:0] sext_ln215_fu_275_p1;
reg  signed [17:0] sext_ln215_reg_671;
wire   [8:0] zext_ln1351_3_fu_279_p1;
reg   [8:0] zext_ln1351_3_reg_676;
wire  signed [17:0] sext_ln215_1_fu_288_p1;
reg  signed [17:0] sext_ln215_1_reg_681;
wire   [8:0] zext_ln1351_4_fu_292_p1;
reg   [8:0] zext_ln1351_4_reg_686;
wire  signed [17:0] sext_ln215_2_fu_301_p1;
reg  signed [17:0] sext_ln215_2_reg_691;
wire   [8:0] zext_ln1351_5_fu_305_p1;
reg   [8:0] zext_ln1351_5_reg_696;
wire  signed [17:0] sext_ln215_3_fu_314_p1;
reg  signed [17:0] sext_ln215_3_reg_701;
wire  signed [17:0] sext_ln215_4_fu_324_p1;
reg  signed [17:0] sext_ln215_4_reg_706;
wire  signed [17:0] sext_ln215_5_fu_334_p1;
reg  signed [17:0] sext_ln215_5_reg_711;
wire   [0:0] icmp_ln366_fu_348_p2;
reg   [0:0] icmp_ln366_reg_716;
wire   [15:0] add_ln695_5_fu_353_p2;
reg   [15:0] add_ln695_5_reg_720;
reg    ap_enable_reg_pp0_iter0;
wire   [7:0] add_ln211_fu_373_p2;
reg   [7:0] add_ln211_reg_725;
reg   [7:0] add_ln211_reg_725_pp0_iter20_reg;
reg   [7:0] add_ln211_reg_725_pp0_iter21_reg;
reg   [7:0] add_ln211_reg_725_pp0_iter22_reg;
wire   [7:0] add_ln211_1_fu_382_p2;
reg   [7:0] add_ln211_1_reg_731;
reg   [7:0] add_ln211_1_reg_731_pp0_iter20_reg;
reg   [7:0] add_ln211_1_reg_731_pp0_iter21_reg;
reg   [7:0] add_ln211_1_reg_731_pp0_iter22_reg;
wire   [8:0] ret_V_19_fu_420_p2;
reg  signed [8:0] ret_V_19_reg_752;
wire   [8:0] ret_V_25_fu_425_p2;
reg  signed [8:0] ret_V_25_reg_757;
wire   [8:0] ret_V_31_fu_430_p2;
reg  signed [8:0] ret_V_31_reg_762;
wire   [17:0] ret_V_21_fu_438_p2;
wire   [17:0] ret_V_27_fu_446_p2;
wire   [17:0] ret_V_33_fu_454_p2;
wire   [0:0] icmp_ln882_fu_511_p2;
wire   [0:0] icmp_ln882_3_fu_517_p2;
wire    ap_block_state30_pp1_stage0_iter0;
reg    ap_block_state31_pp1_stage0_iter1;
reg    ap_block_pp1_stage0_11001;
wire   [15:0] add_ln384_fu_523_p2;
reg    ap_enable_reg_pp1_iter0;
wire    ap_block_pp0_stage0_subdone;
reg    ap_condition_pp0_exit_iter0_state5;
reg    ap_enable_reg_pp0_iter1;
reg    ap_enable_reg_pp0_iter2;
reg    ap_enable_reg_pp0_iter3;
reg    ap_enable_reg_pp0_iter4;
reg    ap_enable_reg_pp0_iter5;
reg    ap_enable_reg_pp0_iter6;
reg    ap_enable_reg_pp0_iter7;
reg    ap_enable_reg_pp0_iter8;
reg    ap_enable_reg_pp0_iter9;
reg    ap_enable_reg_pp0_iter10;
reg    ap_enable_reg_pp0_iter11;
reg    ap_enable_reg_pp0_iter12;
reg    ap_enable_reg_pp0_iter13;
reg    ap_enable_reg_pp0_iter14;
reg    ap_enable_reg_pp0_iter15;
reg    ap_enable_reg_pp0_iter16;
reg    ap_enable_reg_pp0_iter17;
reg    ap_enable_reg_pp0_iter18;
reg    ap_enable_reg_pp0_iter19;
reg    ap_enable_reg_pp0_iter20;
reg    ap_enable_reg_pp0_iter21;
reg    ap_enable_reg_pp0_iter22;
reg    ap_enable_reg_pp0_iter23;
reg    ap_block_pp1_stage0_subdone;
reg    ap_condition_pp1_exit_iter0_state30;
reg   [15:0] ap_phi_mux_empty_phi_fu_179_p4;
wire    ap_block_pp0_stage0;
wire   [63:0] zext_ln538_fu_476_p1;
wire   [0:0] tmp_fu_468_p3;
wire   [63:0] zext_ln882_fu_529_p1;
reg   [15:0] i_top_V_fu_68;
wire   [15:0] add_ln695_4_fu_490_p2;
reg   [15:0] i_V_fu_72;
wire   [15:0] add_ln695_fu_484_p2;
wire   [31:0] zext_ln211_fu_506_p1;
wire   [31:0] zext_ln414_fu_553_p1;
reg    ap_block_pp1_stage0_01001;
wire   [1:0] flag_V_fu_234_p1;
wire   [8:0] ret_V_20_fu_269_p2;
wire   [8:0] ret_V_23_fu_282_p2;
wire   [8:0] ret_V_26_fu_295_p2;
wire   [8:0] ret_V_29_fu_308_p2;
wire   [8:0] ret_V_32_fu_318_p2;
wire   [8:0] ret_V_35_fu_328_p2;
wire   [7:0] grp_fu_359_p1;
wire   [7:0] grp_fu_364_p1;
wire   [7:0] grp_fu_359_p2;
wire   [7:0] trunc_ln1369_fu_369_p1;
wire   [7:0] grp_fu_364_p2;
wire   [7:0] trunc_ln211_fu_378_p1;
wire   [8:0] zext_ln1351_7_fu_387_p1;
wire  signed [8:0] ret_V_22_fu_390_p2;
wire  signed [8:0] ret_V_28_fu_399_p2;
wire  signed [8:0] ret_V_34_fu_408_p2;
wire   [8:0] zext_ln1351_6_fu_417_p1;
wire  signed [8:0] ret_V_21_fu_438_p0;
wire  signed [8:0] ret_V_27_fu_446_p0;
wire  signed [8:0] ret_V_33_fu_454_p1;
wire  signed [17:0] grp_fu_558_p3;
wire  signed [17:0] grp_fu_574_p3;
wire   [17:0] or_ln91_fu_459_p2;
wire  signed [17:0] grp_fu_566_p3;
wire   [17:0] or_ln91_1_fu_463_p2;
wire   [29:0] p_Result_s_fu_537_p5;
wire  signed [30:0] sext_ln414_fu_549_p1;
wire  signed [8:0] grp_fu_558_p0;
wire  signed [8:0] grp_fu_566_p0;
wire  signed [8:0] grp_fu_574_p0;
wire    ap_CS_fsm_state32;
reg   [7:0] ap_NS_fsm;
reg    ap_idle_pp0;
wire    ap_enable_pp0;
reg    ap_idle_pp1;
wire    ap_enable_pp1;

// power-on initialization
initial begin
#0 ap_CS_fsm = 8'd1;
#0 ap_enable_reg_pp1_iter1 = 1'b0;
#0 ap_enable_reg_pp0_iter0 = 1'b0;
#0 ap_enable_reg_pp1_iter0 = 1'b0;
#0 ap_enable_reg_pp0_iter1 = 1'b0;
#0 ap_enable_reg_pp0_iter2 = 1'b0;
#0 ap_enable_reg_pp0_iter3 = 1'b0;
#0 ap_enable_reg_pp0_iter4 = 1'b0;
#0 ap_enable_reg_pp0_iter5 = 1'b0;
#0 ap_enable_reg_pp0_iter6 = 1'b0;
#0 ap_enable_reg_pp0_iter7 = 1'b0;
#0 ap_enable_reg_pp0_iter8 = 1'b0;
#0 ap_enable_reg_pp0_iter9 = 1'b0;
#0 ap_enable_reg_pp0_iter10 = 1'b0;
#0 ap_enable_reg_pp0_iter11 = 1'b0;
#0 ap_enable_reg_pp0_iter12 = 1'b0;
#0 ap_enable_reg_pp0_iter13 = 1'b0;
#0 ap_enable_reg_pp0_iter14 = 1'b0;
#0 ap_enable_reg_pp0_iter15 = 1'b0;
#0 ap_enable_reg_pp0_iter16 = 1'b0;
#0 ap_enable_reg_pp0_iter17 = 1'b0;
#0 ap_enable_reg_pp0_iter18 = 1'b0;
#0 ap_enable_reg_pp0_iter19 = 1'b0;
#0 ap_enable_reg_pp0_iter20 = 1'b0;
#0 ap_enable_reg_pp0_iter21 = 1'b0;
#0 ap_enable_reg_pp0_iter22 = 1'b0;
#0 ap_enable_reg_pp0_iter23 = 1'b0;
end

rendering_m_rasterization2_odd_fragment_x_V #(
    .DataWidth( 8 ),
    .AddressRange( 500 ),
    .AddressWidth( 9 ))
fragment_x_V_U(
    .clk(ap_clk),
    .reset(ap_rst),
    .address0(fragment_x_V_address0),
    .ce0(fragment_x_V_ce0),
    .we0(fragment_x_V_we0),
    .d0(add_ln211_reg_725_pp0_iter22_reg),
    .q0(fragment_x_V_q0)
);

rendering_m_rasterization2_odd_fragment_x_V #(
    .DataWidth( 8 ),
    .AddressRange( 500 ),
    .AddressWidth( 9 ))
fragment_y_V_U(
    .clk(ap_clk),
    .reset(ap_rst),
    .address0(fragment_y_V_address0),
    .ce0(fragment_y_V_ce0),
    .we0(fragment_y_V_we0),
    .d0(add_ln211_1_reg_731_pp0_iter22_reg),
    .q0(fragment_y_V_q0)
);

rendering_m_rasterization2_odd_fragment_x_V #(
    .DataWidth( 8 ),
    .AddressRange( 500 ),
    .AddressWidth( 9 ))
fragment_z_V_U(
    .clk(ap_clk),
    .reset(ap_rst),
    .address0(fragment_z_V_address0),
    .ce0(fragment_z_V_ce0),
    .we0(fragment_z_V_we0),
    .d0(triangle_2d_same_z_V_reg_616),
    .q0(fragment_z_V_q0)
);

rendering_m_rasterization2_odd_fragment_color_V #(
    .DataWidth( 6 ),
    .AddressRange( 500 ),
    .AddressWidth( 9 ))
fragment_color_V_U(
    .clk(ap_clk),
    .reset(ap_rst),
    .address0(fragment_color_V_address0),
    .ce0(fragment_color_V_ce0),
    .we0(fragment_color_V_we0),
    .d0(6'd36),
    .q0(fragment_color_V_q0)
);

rendering_m_urem_16ns_8ns_8_20_1 #(
    .ID( 1 ),
    .NUM_STAGE( 20 ),
    .din0_WIDTH( 16 ),
    .din1_WIDTH( 8 ),
    .dout_WIDTH( 8 ))
urem_16ns_8ns_8_20_1_U21(
    .clk(ap_clk),
    .reset(ap_rst),
    .din0(ap_phi_mux_empty_phi_fu_179_p4),
    .din1(grp_fu_359_p1),
    .ce(1'b1),
    .dout(grp_fu_359_p2)
);

rendering_m_udiv_16ns_8ns_8_20_1 #(
    .ID( 1 ),
    .NUM_STAGE( 20 ),
    .din0_WIDTH( 16 ),
    .din1_WIDTH( 8 ),
    .dout_WIDTH( 8 ))
udiv_16ns_8ns_8_20_1_U22(
    .clk(ap_clk),
    .reset(ap_rst),
    .din0(ap_phi_mux_empty_phi_fu_179_p4),
    .din1(grp_fu_364_p1),
    .ce(1'b1),
    .dout(grp_fu_364_p2)
);

rendering_m_mul_9s_9s_18_1_1 #(
    .ID( 1 ),
    .NUM_STAGE( 1 ),
    .din0_WIDTH( 9 ),
    .din1_WIDTH( 9 ),
    .dout_WIDTH( 18 ))
mul_9s_9s_18_1_1_U23(
    .din0(ret_V_21_fu_438_p0),
    .din1(ret_V_19_reg_752),
    .dout(ret_V_21_fu_438_p2)
);

rendering_m_mul_9s_9s_18_1_1 #(
    .ID( 1 ),
    .NUM_STAGE( 1 ),
    .din0_WIDTH( 9 ),
    .din1_WIDTH( 9 ),
    .dout_WIDTH( 18 ))
mul_9s_9s_18_1_1_U24(
    .din0(ret_V_27_fu_446_p0),
    .din1(ret_V_25_reg_757),
    .dout(ret_V_27_fu_446_p2)
);

rendering_m_mul_9s_9s_18_1_1 #(
    .ID( 1 ),
    .NUM_STAGE( 1 ),
    .din0_WIDTH( 9 ),
    .din1_WIDTH( 9 ),
    .dout_WIDTH( 18 ))
mul_9s_9s_18_1_1_U25(
    .din0(ret_V_31_reg_762),
    .din1(ret_V_33_fu_454_p1),
    .dout(ret_V_33_fu_454_p2)
);

rendering_m_mac_mulsub_9s_9s_18ns_18_4_1 #(
    .ID( 1 ),
    .NUM_STAGE( 4 ),
    .din0_WIDTH( 9 ),
    .din1_WIDTH( 9 ),
    .din2_WIDTH( 18 ),
    .dout_WIDTH( 18 ))
mac_mulsub_9s_9s_18ns_18_4_1_U26(
    .clk(ap_clk),
    .reset(ap_rst),
    .din0(grp_fu_558_p0),
    .din1(ret_V_22_fu_390_p2),
    .din2(ret_V_21_fu_438_p2),
    .ce(1'b1),
    .dout(grp_fu_558_p3)
);

rendering_m_mac_mulsub_9s_9s_18ns_18_4_1 #(
    .ID( 1 ),
    .NUM_STAGE( 4 ),
    .din0_WIDTH( 9 ),
    .din1_WIDTH( 9 ),
    .din2_WIDTH( 18 ),
    .dout_WIDTH( 18 ))
mac_mulsub_9s_9s_18ns_18_4_1_U27(
    .clk(ap_clk),
    .reset(ap_rst),
    .din0(grp_fu_566_p0),
    .din1(ret_V_28_fu_399_p2),
    .din2(ret_V_27_fu_446_p2),
    .ce(1'b1),
    .dout(grp_fu_566_p3)
);

rendering_m_mac_mulsub_9s_9s_18ns_18_4_1 #(
    .ID( 1 ),
    .NUM_STAGE( 4 ),
    .din0_WIDTH( 9 ),
    .din1_WIDTH( 9 ),
    .din2_WIDTH( 18 ),
    .dout_WIDTH( 18 ))
mac_mulsub_9s_9s_18ns_18_4_1_U28(
    .clk(ap_clk),
    .reset(ap_rst),
    .din0(grp_fu_574_p0),
    .din1(ret_V_34_fu_408_p2),
    .din2(ret_V_33_fu_454_p2),
    .ce(1'b1),
    .dout(grp_fu_574_p3)
);

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_CS_fsm <= ap_ST_fsm_state1;
    end else begin
        ap_CS_fsm <= ap_NS_fsm;
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp0_iter0 <= 1'b0;
    end else begin
        if (((1'b1 == ap_condition_pp0_exit_iter0_state5) & (1'b1 == ap_CS_fsm_pp0_stage0) & (1'b0 == ap_block_pp0_stage0_subdone))) begin
            ap_enable_reg_pp0_iter0 <= 1'b0;
        end else if ((~((1'b0 == Input_1_empty_n) | ((icmp_ln358_reg_597 == 1'd0) & (1'b0 == Output_1_full_n))) & (icmp_ln358_reg_597 == 1'd1) & (1'b1 == ap_CS_fsm_state4))) begin
            ap_enable_reg_pp0_iter0 <= 1'b1;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp0_iter1 <= 1'b0;
    end else begin
        if ((1'b0 == ap_block_pp0_stage0_subdone)) begin
            if ((1'b1 == ap_condition_pp0_exit_iter0_state5)) begin
                ap_enable_reg_pp0_iter1 <= (1'b1 ^ ap_condition_pp0_exit_iter0_state5);
            end else if ((1'b1 == 1'b1)) begin
                ap_enable_reg_pp0_iter1 <= ap_enable_reg_pp0_iter0;
            end
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp0_iter10 <= 1'b0;
    end else begin
        if ((1'b0 == ap_block_pp0_stage0_subdone)) begin
            ap_enable_reg_pp0_iter10 <= ap_enable_reg_pp0_iter9;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp0_iter11 <= 1'b0;
    end else begin
        if ((1'b0 == ap_block_pp0_stage0_subdone)) begin
            ap_enable_reg_pp0_iter11 <= ap_enable_reg_pp0_iter10;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp0_iter12 <= 1'b0;
    end else begin
        if ((1'b0 == ap_block_pp0_stage0_subdone)) begin
            ap_enable_reg_pp0_iter12 <= ap_enable_reg_pp0_iter11;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp0_iter13 <= 1'b0;
    end else begin
        if ((1'b0 == ap_block_pp0_stage0_subdone)) begin
            ap_enable_reg_pp0_iter13 <= ap_enable_reg_pp0_iter12;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp0_iter14 <= 1'b0;
    end else begin
        if ((1'b0 == ap_block_pp0_stage0_subdone)) begin
            ap_enable_reg_pp0_iter14 <= ap_enable_reg_pp0_iter13;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp0_iter15 <= 1'b0;
    end else begin
        if ((1'b0 == ap_block_pp0_stage0_subdone)) begin
            ap_enable_reg_pp0_iter15 <= ap_enable_reg_pp0_iter14;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp0_iter16 <= 1'b0;
    end else begin
        if ((1'b0 == ap_block_pp0_stage0_subdone)) begin
            ap_enable_reg_pp0_iter16 <= ap_enable_reg_pp0_iter15;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp0_iter17 <= 1'b0;
    end else begin
        if ((1'b0 == ap_block_pp0_stage0_subdone)) begin
            ap_enable_reg_pp0_iter17 <= ap_enable_reg_pp0_iter16;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp0_iter18 <= 1'b0;
    end else begin
        if ((1'b0 == ap_block_pp0_stage0_subdone)) begin
            ap_enable_reg_pp0_iter18 <= ap_enable_reg_pp0_iter17;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp0_iter19 <= 1'b0;
    end else begin
        if ((1'b0 == ap_block_pp0_stage0_subdone)) begin
            ap_enable_reg_pp0_iter19 <= ap_enable_reg_pp0_iter18;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp0_iter2 <= 1'b0;
    end else begin
        if ((1'b0 == ap_block_pp0_stage0_subdone)) begin
            ap_enable_reg_pp0_iter2 <= ap_enable_reg_pp0_iter1;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp0_iter20 <= 1'b0;
    end else begin
        if ((1'b0 == ap_block_pp0_stage0_subdone)) begin
            ap_enable_reg_pp0_iter20 <= ap_enable_reg_pp0_iter19;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp0_iter21 <= 1'b0;
    end else begin
        if ((1'b0 == ap_block_pp0_stage0_subdone)) begin
            ap_enable_reg_pp0_iter21 <= ap_enable_reg_pp0_iter20;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp0_iter22 <= 1'b0;
    end else begin
        if ((1'b0 == ap_block_pp0_stage0_subdone)) begin
            ap_enable_reg_pp0_iter22 <= ap_enable_reg_pp0_iter21;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp0_iter23 <= 1'b0;
    end else begin
        if ((1'b0 == ap_block_pp0_stage0_subdone)) begin
            ap_enable_reg_pp0_iter23 <= ap_enable_reg_pp0_iter22;
        end else if ((~((1'b0 == Input_1_empty_n) | ((icmp_ln358_reg_597 == 1'd0) & (1'b0 == Output_1_full_n))) & (icmp_ln358_reg_597 == 1'd1) & (1'b1 == ap_CS_fsm_state4))) begin
            ap_enable_reg_pp0_iter23 <= 1'b0;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp0_iter3 <= 1'b0;
    end else begin
        if ((1'b0 == ap_block_pp0_stage0_subdone)) begin
            ap_enable_reg_pp0_iter3 <= ap_enable_reg_pp0_iter2;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp0_iter4 <= 1'b0;
    end else begin
        if ((1'b0 == ap_block_pp0_stage0_subdone)) begin
            ap_enable_reg_pp0_iter4 <= ap_enable_reg_pp0_iter3;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp0_iter5 <= 1'b0;
    end else begin
        if ((1'b0 == ap_block_pp0_stage0_subdone)) begin
            ap_enable_reg_pp0_iter5 <= ap_enable_reg_pp0_iter4;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp0_iter6 <= 1'b0;
    end else begin
        if ((1'b0 == ap_block_pp0_stage0_subdone)) begin
            ap_enable_reg_pp0_iter6 <= ap_enable_reg_pp0_iter5;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp0_iter7 <= 1'b0;
    end else begin
        if ((1'b0 == ap_block_pp0_stage0_subdone)) begin
            ap_enable_reg_pp0_iter7 <= ap_enable_reg_pp0_iter6;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp0_iter8 <= 1'b0;
    end else begin
        if ((1'b0 == ap_block_pp0_stage0_subdone)) begin
            ap_enable_reg_pp0_iter8 <= ap_enable_reg_pp0_iter7;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp0_iter9 <= 1'b0;
    end else begin
        if ((1'b0 == ap_block_pp0_stage0_subdone)) begin
            ap_enable_reg_pp0_iter9 <= ap_enable_reg_pp0_iter8;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp1_iter0 <= 1'b0;
    end else begin
        if (((1'b1 == ap_condition_pp1_exit_iter0_state30) & (1'b1 == ap_CS_fsm_pp1_stage0) & (1'b0 == ap_block_pp1_stage0_subdone))) begin
            ap_enable_reg_pp1_iter0 <= 1'b0;
        end else if (((icmp_ln882_fu_511_p2 == 1'd0) & (1'b1 == Output_1_full_n) & (1'b1 == ap_CS_fsm_state29))) begin
            ap_enable_reg_pp1_iter0 <= 1'b1;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp1_iter1 <= 1'b0;
    end else begin
        if (((1'b1 == ap_condition_pp1_exit_iter0_state30) & (1'b0 == ap_block_pp1_stage0_subdone))) begin
            ap_enable_reg_pp1_iter1 <= (1'b1 ^ ap_condition_pp1_exit_iter0_state30);
        end else if ((1'b0 == ap_block_pp1_stage0_subdone)) begin
            ap_enable_reg_pp1_iter1 <= ap_enable_reg_pp1_iter0;
        end else if (((icmp_ln882_fu_511_p2 == 1'd0) & (1'b1 == Output_1_full_n) & (1'b1 == ap_CS_fsm_state29))) begin
            ap_enable_reg_pp1_iter1 <= 1'b0;
        end
    end
end

always @ (posedge ap_clk) begin
    if (((ap_enable_reg_pp0_iter1 == 1'b1) & (icmp_ln366_reg_716 == 1'd0) & (1'b1 == ap_CS_fsm_pp0_stage0) & (1'b0 == ap_block_pp0_stage0_11001))) begin
        empty_reg_175 <= add_ln695_5_reg_720;
    end else if ((~((1'b0 == Input_1_empty_n) | ((icmp_ln358_reg_597 == 1'd0) & (1'b0 == Output_1_full_n))) & (icmp_ln358_reg_597 == 1'd1) & (1'b1 == ap_CS_fsm_state4))) begin
        empty_reg_175 <= 16'd0;
    end
end

always @ (posedge ap_clk) begin
    if (((tmp_fu_468_p3 == 1'd0) & (ap_enable_reg_pp0_iter23 == 1'b1) & (1'b0 == ap_block_pp0_stage0_11001))) begin
        i_V_fu_72 <= add_ln695_fu_484_p2;
    end else if ((~((1'b0 == Input_1_empty_n) | ((icmp_ln358_reg_597 == 1'd0) & (1'b0 == Output_1_full_n))) & (icmp_ln358_reg_597 == 1'd1) & (1'b1 == ap_CS_fsm_state4))) begin
        i_V_fu_72 <= 16'd0;
    end
end

always @ (posedge ap_clk) begin
    if (((tmp_fu_468_p3 == 1'd0) & (ap_enable_reg_pp0_iter23 == 1'b1) & (1'b0 == ap_block_pp0_stage0_11001))) begin
        i_top_V_fu_68 <= add_ln695_4_fu_490_p2;
    end else if ((~((1'b0 == Input_1_empty_n) | ((icmp_ln358_reg_597 == 1'd0) & (1'b0 == Output_1_full_n))) & (icmp_ln358_reg_597 == 1'd1) & (1'b1 == ap_CS_fsm_state4))) begin
        i_top_V_fu_68 <= 16'd0;
    end
end

always @ (posedge ap_clk) begin
    if (((icmp_ln882_fu_511_p2 == 1'd0) & (1'b1 == Output_1_full_n) & (1'b1 == ap_CS_fsm_state29))) begin
        j_reg_187 <= 16'd0;
    end else if (((ap_enable_reg_pp1_iter0 == 1'b1) & (icmp_ln882_3_fu_517_p2 == 1'd0) & (1'b1 == ap_CS_fsm_pp1_stage0) & (1'b0 == ap_block_pp1_stage0_11001))) begin
        j_reg_187 <= add_ln384_fu_523_p2;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b0 == ap_block_pp0_stage0_11001)) begin
        add_ln211_1_reg_731 <= add_ln211_1_fu_382_p2;
        add_ln211_1_reg_731_pp0_iter20_reg <= add_ln211_1_reg_731;
        add_ln211_1_reg_731_pp0_iter21_reg <= add_ln211_1_reg_731_pp0_iter20_reg;
        add_ln211_1_reg_731_pp0_iter22_reg <= add_ln211_1_reg_731_pp0_iter21_reg;
        add_ln211_reg_725 <= add_ln211_fu_373_p2;
        add_ln211_reg_725_pp0_iter20_reg <= add_ln211_reg_725;
        add_ln211_reg_725_pp0_iter21_reg <= add_ln211_reg_725_pp0_iter20_reg;
        add_ln211_reg_725_pp0_iter22_reg <= add_ln211_reg_725_pp0_iter21_reg;
        ret_V_19_reg_752 <= ret_V_19_fu_420_p2;
        ret_V_25_reg_757 <= ret_V_25_fu_425_p2;
        ret_V_31_reg_762 <= ret_V_31_fu_430_p2;
    end
end

always @ (posedge ap_clk) begin
    if (((ap_enable_reg_pp0_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage0) & (1'b0 == ap_block_pp0_stage0_11001))) begin
        add_ln695_5_reg_720 <= add_ln695_5_fu_353_p2;
    end
end

always @ (posedge ap_clk) begin
    if ((~((1'b0 == Input_1_empty_n) | (ap_start == 1'b0)) & (1'b1 == ap_CS_fsm_state1))) begin
        icmp_ln358_reg_597 <= icmp_ln358_fu_238_p2;
        triangle_2d_same_x0_V_reg_582 <= {{Input_1_dout[15:8]}};
        triangle_2d_same_x1_V_reg_592 <= {{Input_1_dout[31:24]}};
        triangle_2d_same_y0_V_reg_587 <= {{Input_1_dout[23:16]}};
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == ap_CS_fsm_pp0_stage0) & (1'b0 == ap_block_pp0_stage0_11001))) begin
        icmp_ln366_reg_716 <= icmp_ln366_fu_348_p2;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == ap_CS_fsm_pp1_stage0) & (1'b0 == ap_block_pp1_stage0_11001))) begin
        icmp_ln882_3_reg_789 <= icmp_ln882_3_fu_517_p2;
    end
end

always @ (posedge ap_clk) begin
    if ((~((1'b0 == Input_1_empty_n) | ((icmp_ln358_reg_597 == 1'd0) & (1'b0 == Output_1_full_n))) & (1'b1 == ap_CS_fsm_state4))) begin
        max_min_V_1_reg_631 <= max_min_V_1_fu_252_p1;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == ap_CS_fsm_state3) & (1'b1 == Input_1_empty_n))) begin
        max_min_V_reg_626 <= {{Input_1_dout[23:16]}};
        trunc_ln674_reg_621 <= trunc_ln674_fu_248_p1;
    end
end

always @ (posedge ap_clk) begin
    if ((~((1'b0 == Input_1_empty_n) | ((icmp_ln358_reg_597 == 1'd0) & (1'b0 == Output_1_full_n))) & (icmp_ln358_reg_597 == 1'd1) & (1'b1 == ap_CS_fsm_state4))) begin
        sext_ln215_1_reg_681 <= sext_ln215_1_fu_288_p1;
        sext_ln215_2_reg_691 <= sext_ln215_2_fu_301_p1;
        sext_ln215_3_reg_701 <= sext_ln215_3_fu_314_p1;
        sext_ln215_4_reg_706 <= sext_ln215_4_fu_324_p1;
        sext_ln215_5_reg_711 <= sext_ln215_5_fu_334_p1;
        sext_ln215_reg_671 <= sext_ln215_fu_275_p1;
        zext_ln1351_1_reg_661[7 : 0] <= zext_ln1351_1_fu_263_p1[7 : 0];
        zext_ln1351_2_reg_666[7 : 0] <= zext_ln1351_2_fu_266_p1[7 : 0];
        zext_ln1351_3_reg_676[7 : 0] <= zext_ln1351_3_fu_279_p1[7 : 0];
        zext_ln1351_4_reg_686[7 : 0] <= zext_ln1351_4_fu_292_p1[7 : 0];
        zext_ln1351_5_reg_696[7 : 0] <= zext_ln1351_5_fu_305_p1[7 : 0];
        zext_ln1351_reg_656[7 : 0] <= zext_ln1351_fu_260_p1[7 : 0];
        zext_ln1368_reg_650[7 : 0] <= zext_ln1368_fu_256_p1[7 : 0];
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == ap_CS_fsm_state2) & (1'b1 == Input_1_empty_n))) begin
        triangle_2d_same_x2_V_reg_606 <= {{Input_1_dout[15:8]}};
        triangle_2d_same_y1_V_reg_601 <= triangle_2d_same_y1_V_fu_244_p1;
        triangle_2d_same_y2_V_reg_611 <= {{Input_1_dout[23:16]}};
        triangle_2d_same_z_V_reg_616 <= {{Input_1_dout[31:24]}};
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state4) | (1'b1 == ap_CS_fsm_state3) | (1'b1 == ap_CS_fsm_state2) | ((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b1)))) begin
        Input_1_blk_n = Input_1_empty_n;
    end else begin
        Input_1_blk_n = 1'b1;
    end
end

always @ (*) begin
    if ((((1'b1 == ap_CS_fsm_state3) & (1'b1 == Input_1_empty_n)) | ((1'b1 == ap_CS_fsm_state2) & (1'b1 == Input_1_empty_n)) | (~((1'b0 == Input_1_empty_n) | ((icmp_ln358_reg_597 == 1'd0) & (1'b0 == Output_1_full_n))) & (1'b1 == ap_CS_fsm_state4)) | (~((1'b0 == Input_1_empty_n) | (ap_start == 1'b0)) & (1'b1 == ap_CS_fsm_state1)))) begin
        Input_1_read = 1'b1;
    end else begin
        Input_1_read = 1'b0;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state29) | ((icmp_ln358_reg_597 == 1'd0) & (1'b1 == ap_CS_fsm_state4)) | ((1'b1 == ap_CS_fsm_pp1_stage0) & (icmp_ln882_3_reg_789 == 1'd0) & (1'b0 == ap_block_pp1_stage0) & (ap_enable_reg_pp1_iter1 == 1'b1)))) begin
        Output_1_blk_n = Output_1_full_n;
    end else begin
        Output_1_blk_n = 1'b1;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_pp1_stage0) & (icmp_ln882_3_reg_789 == 1'd0) & (1'b0 == ap_block_pp1_stage0_01001) & (ap_enable_reg_pp1_iter1 == 1'b1))) begin
        Output_1_din = zext_ln414_fu_553_p1;
    end else if (((1'b1 == Output_1_full_n) & (1'b1 == ap_CS_fsm_state29))) begin
        Output_1_din = zext_ln211_fu_506_p1;
    end else if ((~((1'b0 == Input_1_empty_n) | ((icmp_ln358_reg_597 == 1'd0) & (1'b0 == Output_1_full_n))) & (icmp_ln358_reg_597 == 1'd0) & (1'b1 == ap_CS_fsm_state4))) begin
        Output_1_din = 32'd0;
    end else begin
        Output_1_din = 'bx;
    end
end

always @ (*) begin
    if ((((1'b1 == Output_1_full_n) & (1'b1 == ap_CS_fsm_state29)) | (~((1'b0 == Input_1_empty_n) | ((icmp_ln358_reg_597 == 1'd0) & (1'b0 == Output_1_full_n))) & (icmp_ln358_reg_597 == 1'd0) & (1'b1 == ap_CS_fsm_state4)) | ((1'b1 == ap_CS_fsm_pp1_stage0) & (icmp_ln882_3_reg_789 == 1'd0) & (1'b0 == ap_block_pp1_stage0_11001) & (ap_enable_reg_pp1_iter1 == 1'b1)))) begin
        Output_1_write = 1'b1;
    end else begin
        Output_1_write = 1'b0;
    end
end

always @ (*) begin
    if ((icmp_ln366_fu_348_p2 == 1'd1)) begin
        ap_condition_pp0_exit_iter0_state5 = 1'b1;
    end else begin
        ap_condition_pp0_exit_iter0_state5 = 1'b0;
    end
end

always @ (*) begin
    if ((icmp_ln882_3_fu_517_p2 == 1'd1)) begin
        ap_condition_pp1_exit_iter0_state30 = 1'b1;
    end else begin
        ap_condition_pp1_exit_iter0_state30 = 1'b0;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state32) | ((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b0)))) begin
        ap_done = 1'b1;
    end else begin
        ap_done = 1'b0;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b0))) begin
        ap_idle = 1'b1;
    end else begin
        ap_idle = 1'b0;
    end
end

always @ (*) begin
    if (((ap_enable_reg_pp0_iter23 == 1'b0) & (ap_enable_reg_pp0_iter22 == 1'b0) & (ap_enable_reg_pp0_iter21 == 1'b0) & (ap_enable_reg_pp0_iter20 == 1'b0) & (ap_enable_reg_pp0_iter19 == 1'b0) & (ap_enable_reg_pp0_iter18 == 1'b0) & (ap_enable_reg_pp0_iter17 == 1'b0) & (ap_enable_reg_pp0_iter16 == 1'b0) & (ap_enable_reg_pp0_iter15 == 1'b0) & (ap_enable_reg_pp0_iter14 == 1'b0) & (ap_enable_reg_pp0_iter13 == 1'b0) & (ap_enable_reg_pp0_iter12 == 1'b0) & (ap_enable_reg_pp0_iter11 == 1'b0) & (ap_enable_reg_pp0_iter10 == 1'b0) & (ap_enable_reg_pp0_iter9 == 1'b0) & (ap_enable_reg_pp0_iter8 == 1'b0) & (ap_enable_reg_pp0_iter7 == 1'b0) & (ap_enable_reg_pp0_iter6 == 1'b0) & (ap_enable_reg_pp0_iter5 == 1'b0) & (ap_enable_reg_pp0_iter4 == 1'b0) & (ap_enable_reg_pp0_iter3 == 1'b0) & (ap_enable_reg_pp0_iter2 == 1'b0) & (ap_enable_reg_pp0_iter1 == 1'b0) & (ap_enable_reg_pp0_iter0 == 1'b0))) begin
        ap_idle_pp0 = 1'b1;
    end else begin
        ap_idle_pp0 = 1'b0;
    end
end

always @ (*) begin
    if (((ap_enable_reg_pp1_iter0 == 1'b0) & (ap_enable_reg_pp1_iter1 == 1'b0))) begin
        ap_idle_pp1 = 1'b1;
    end else begin
        ap_idle_pp1 = 1'b0;
    end
end

always @ (*) begin
    if (((ap_enable_reg_pp0_iter1 == 1'b1) & (icmp_ln366_reg_716 == 1'd0) & (1'b1 == ap_CS_fsm_pp0_stage0) & (1'b0 == ap_block_pp0_stage0))) begin
        ap_phi_mux_empty_phi_fu_179_p4 = add_ln695_5_reg_720;
    end else begin
        ap_phi_mux_empty_phi_fu_179_p4 = empty_reg_175;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state32)) begin
        ap_ready = 1'b1;
    end else begin
        ap_ready = 1'b0;
    end
end

always @ (*) begin
    if (((ap_enable_reg_pp1_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp1_stage0) & (1'b0 == ap_block_pp1_stage0))) begin
        fragment_color_V_address0 = zext_ln882_fu_529_p1;
    end else if (((ap_enable_reg_pp0_iter23 == 1'b1) & (1'b0 == ap_block_pp0_stage0))) begin
        fragment_color_V_address0 = zext_ln538_fu_476_p1;
    end else begin
        fragment_color_V_address0 = 'bx;
    end
end

always @ (*) begin
    if ((((ap_enable_reg_pp0_iter23 == 1'b1) & (1'b0 == ap_block_pp0_stage0_11001)) | ((ap_enable_reg_pp1_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp1_stage0) & (1'b0 == ap_block_pp1_stage0_11001)))) begin
        fragment_color_V_ce0 = 1'b1;
    end else begin
        fragment_color_V_ce0 = 1'b0;
    end
end

always @ (*) begin
    if (((tmp_fu_468_p3 == 1'd0) & (ap_enable_reg_pp0_iter23 == 1'b1) & (1'b0 == ap_block_pp0_stage0_11001))) begin
        fragment_color_V_we0 = 1'b1;
    end else begin
        fragment_color_V_we0 = 1'b0;
    end
end

always @ (*) begin
    if (((ap_enable_reg_pp1_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp1_stage0) & (1'b0 == ap_block_pp1_stage0))) begin
        fragment_x_V_address0 = zext_ln882_fu_529_p1;
    end else if (((ap_enable_reg_pp0_iter23 == 1'b1) & (1'b0 == ap_block_pp0_stage0))) begin
        fragment_x_V_address0 = zext_ln538_fu_476_p1;
    end else begin
        fragment_x_V_address0 = 'bx;
    end
end

always @ (*) begin
    if ((((ap_enable_reg_pp0_iter23 == 1'b1) & (1'b0 == ap_block_pp0_stage0_11001)) | ((ap_enable_reg_pp1_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp1_stage0) & (1'b0 == ap_block_pp1_stage0_11001)))) begin
        fragment_x_V_ce0 = 1'b1;
    end else begin
        fragment_x_V_ce0 = 1'b0;
    end
end

always @ (*) begin
    if (((tmp_fu_468_p3 == 1'd0) & (ap_enable_reg_pp0_iter23 == 1'b1) & (1'b0 == ap_block_pp0_stage0_11001))) begin
        fragment_x_V_we0 = 1'b1;
    end else begin
        fragment_x_V_we0 = 1'b0;
    end
end

always @ (*) begin
    if (((ap_enable_reg_pp1_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp1_stage0) & (1'b0 == ap_block_pp1_stage0))) begin
        fragment_y_V_address0 = zext_ln882_fu_529_p1;
    end else if (((ap_enable_reg_pp0_iter23 == 1'b1) & (1'b0 == ap_block_pp0_stage0))) begin
        fragment_y_V_address0 = zext_ln538_fu_476_p1;
    end else begin
        fragment_y_V_address0 = 'bx;
    end
end

always @ (*) begin
    if ((((ap_enable_reg_pp0_iter23 == 1'b1) & (1'b0 == ap_block_pp0_stage0_11001)) | ((ap_enable_reg_pp1_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp1_stage0) & (1'b0 == ap_block_pp1_stage0_11001)))) begin
        fragment_y_V_ce0 = 1'b1;
    end else begin
        fragment_y_V_ce0 = 1'b0;
    end
end

always @ (*) begin
    if (((tmp_fu_468_p3 == 1'd0) & (ap_enable_reg_pp0_iter23 == 1'b1) & (1'b0 == ap_block_pp0_stage0_11001))) begin
        fragment_y_V_we0 = 1'b1;
    end else begin
        fragment_y_V_we0 = 1'b0;
    end
end

always @ (*) begin
    if (((ap_enable_reg_pp1_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp1_stage0) & (1'b0 == ap_block_pp1_stage0))) begin
        fragment_z_V_address0 = zext_ln882_fu_529_p1;
    end else if (((ap_enable_reg_pp0_iter23 == 1'b1) & (1'b0 == ap_block_pp0_stage0))) begin
        fragment_z_V_address0 = zext_ln538_fu_476_p1;
    end else begin
        fragment_z_V_address0 = 'bx;
    end
end

always @ (*) begin
    if ((((ap_enable_reg_pp0_iter23 == 1'b1) & (1'b0 == ap_block_pp0_stage0_11001)) | ((ap_enable_reg_pp1_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp1_stage0) & (1'b0 == ap_block_pp1_stage0_11001)))) begin
        fragment_z_V_ce0 = 1'b1;
    end else begin
        fragment_z_V_ce0 = 1'b0;
    end
end

always @ (*) begin
    if (((tmp_fu_468_p3 == 1'd0) & (ap_enable_reg_pp0_iter23 == 1'b1) & (1'b0 == ap_block_pp0_stage0_11001))) begin
        fragment_z_V_we0 = 1'b1;
    end else begin
        fragment_z_V_we0 = 1'b0;
    end
end

always @ (*) begin
    case (ap_CS_fsm)
        ap_ST_fsm_state1 : begin
            if ((~((1'b0 == Input_1_empty_n) | (ap_start == 1'b0)) & (1'b1 == ap_CS_fsm_state1))) begin
                ap_NS_fsm = ap_ST_fsm_state2;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state1;
            end
        end
        ap_ST_fsm_state2 : begin
            if (((1'b1 == ap_CS_fsm_state2) & (1'b1 == Input_1_empty_n))) begin
                ap_NS_fsm = ap_ST_fsm_state3;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state2;
            end
        end
        ap_ST_fsm_state3 : begin
            if (((1'b1 == ap_CS_fsm_state3) & (1'b1 == Input_1_empty_n))) begin
                ap_NS_fsm = ap_ST_fsm_state4;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state3;
            end
        end
        ap_ST_fsm_state4 : begin
            if ((~((1'b0 == Input_1_empty_n) | ((icmp_ln358_reg_597 == 1'd0) & (1'b0 == Output_1_full_n))) & (icmp_ln358_reg_597 == 1'd1) & (1'b1 == ap_CS_fsm_state4))) begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage0;
            end else if ((~((1'b0 == Input_1_empty_n) | ((icmp_ln358_reg_597 == 1'd0) & (1'b0 == Output_1_full_n))) & (icmp_ln358_reg_597 == 1'd0) & (1'b1 == ap_CS_fsm_state4))) begin
                ap_NS_fsm = ap_ST_fsm_state32;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state4;
            end
        end
        ap_ST_fsm_pp0_stage0 : begin
            if ((~((ap_enable_reg_pp0_iter1 == 1'b0) & (ap_enable_reg_pp0_iter0 == 1'b1) & (icmp_ln366_fu_348_p2 == 1'd1) & (1'b0 == ap_block_pp0_stage0_subdone)) & ~((ap_enable_reg_pp0_iter23 == 1'b1) & (ap_enable_reg_pp0_iter22 == 1'b0) & (1'b0 == ap_block_pp0_stage0_subdone)))) begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage0;
            end else if ((((ap_enable_reg_pp0_iter23 == 1'b1) & (ap_enable_reg_pp0_iter22 == 1'b0) & (1'b0 == ap_block_pp0_stage0_subdone)) | ((ap_enable_reg_pp0_iter1 == 1'b0) & (ap_enable_reg_pp0_iter0 == 1'b1) & (icmp_ln366_fu_348_p2 == 1'd1) & (1'b0 == ap_block_pp0_stage0_subdone)))) begin
                ap_NS_fsm = ap_ST_fsm_state29;
            end else begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage0;
            end
        end
        ap_ST_fsm_state29 : begin
            if (((icmp_ln882_fu_511_p2 == 1'd0) & (1'b1 == Output_1_full_n) & (1'b1 == ap_CS_fsm_state29))) begin
                ap_NS_fsm = ap_ST_fsm_pp1_stage0;
            end else if (((icmp_ln882_fu_511_p2 == 1'd1) & (1'b1 == Output_1_full_n) & (1'b1 == ap_CS_fsm_state29))) begin
                ap_NS_fsm = ap_ST_fsm_state32;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state29;
            end
        end
        ap_ST_fsm_pp1_stage0 : begin
            if (~((ap_enable_reg_pp1_iter0 == 1'b1) & (icmp_ln882_3_fu_517_p2 == 1'd1) & (1'b0 == ap_block_pp1_stage0_subdone))) begin
                ap_NS_fsm = ap_ST_fsm_pp1_stage0;
            end else if (((ap_enable_reg_pp1_iter0 == 1'b1) & (icmp_ln882_3_fu_517_p2 == 1'd1) & (1'b0 == ap_block_pp1_stage0_subdone))) begin
                ap_NS_fsm = ap_ST_fsm_state32;
            end else begin
                ap_NS_fsm = ap_ST_fsm_pp1_stage0;
            end
        end
        ap_ST_fsm_state32 : begin
            ap_NS_fsm = ap_ST_fsm_state1;
        end
        default : begin
            ap_NS_fsm = 'bx;
        end
    endcase
end

assign add_ln211_1_fu_382_p2 = (trunc_ln211_fu_378_p1 + max_min_V_1_reg_631);

assign add_ln211_fu_373_p2 = (trunc_ln1369_fu_369_p1 + max_min_V_reg_626);

assign add_ln384_fu_523_p2 = (j_reg_187 + 16'd1);

assign add_ln695_4_fu_490_p2 = (i_top_V_fu_68 + 16'd1);

assign add_ln695_5_fu_353_p2 = (ap_phi_mux_empty_phi_fu_179_p4 + 16'd1);

assign add_ln695_fu_484_p2 = (i_V_fu_72 + 16'd1);

assign ap_CS_fsm_pp0_stage0 = ap_CS_fsm[32'd4];

assign ap_CS_fsm_pp1_stage0 = ap_CS_fsm[32'd6];

assign ap_CS_fsm_state1 = ap_CS_fsm[32'd0];

assign ap_CS_fsm_state2 = ap_CS_fsm[32'd1];

assign ap_CS_fsm_state29 = ap_CS_fsm[32'd5];

assign ap_CS_fsm_state3 = ap_CS_fsm[32'd2];

assign ap_CS_fsm_state32 = ap_CS_fsm[32'd7];

assign ap_CS_fsm_state4 = ap_CS_fsm[32'd3];

assign ap_block_pp0_stage0 = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage0_11001 = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage0_subdone = ~(1'b1 == 1'b1);

assign ap_block_pp1_stage0 = ~(1'b1 == 1'b1);

always @ (*) begin
    ap_block_pp1_stage0_01001 = ((1'b0 == Output_1_full_n) & (icmp_ln882_3_reg_789 == 1'd0) & (ap_enable_reg_pp1_iter1 == 1'b1));
end

always @ (*) begin
    ap_block_pp1_stage0_11001 = ((1'b0 == Output_1_full_n) & (icmp_ln882_3_reg_789 == 1'd0) & (ap_enable_reg_pp1_iter1 == 1'b1));
end

always @ (*) begin
    ap_block_pp1_stage0_subdone = ((1'b0 == Output_1_full_n) & (icmp_ln882_3_reg_789 == 1'd0) & (ap_enable_reg_pp1_iter1 == 1'b1));
end

always @ (*) begin
    ap_block_state1 = ((1'b0 == Input_1_empty_n) | (ap_start == 1'b0));
end

assign ap_block_state10_pp0_stage0_iter5 = ~(1'b1 == 1'b1);

assign ap_block_state11_pp0_stage0_iter6 = ~(1'b1 == 1'b1);

assign ap_block_state12_pp0_stage0_iter7 = ~(1'b1 == 1'b1);

assign ap_block_state13_pp0_stage0_iter8 = ~(1'b1 == 1'b1);

assign ap_block_state14_pp0_stage0_iter9 = ~(1'b1 == 1'b1);

assign ap_block_state15_pp0_stage0_iter10 = ~(1'b1 == 1'b1);

assign ap_block_state16_pp0_stage0_iter11 = ~(1'b1 == 1'b1);

assign ap_block_state17_pp0_stage0_iter12 = ~(1'b1 == 1'b1);

assign ap_block_state18_pp0_stage0_iter13 = ~(1'b1 == 1'b1);

assign ap_block_state19_pp0_stage0_iter14 = ~(1'b1 == 1'b1);

assign ap_block_state20_pp0_stage0_iter15 = ~(1'b1 == 1'b1);

assign ap_block_state21_pp0_stage0_iter16 = ~(1'b1 == 1'b1);

assign ap_block_state22_pp0_stage0_iter17 = ~(1'b1 == 1'b1);

assign ap_block_state23_pp0_stage0_iter18 = ~(1'b1 == 1'b1);

assign ap_block_state24_pp0_stage0_iter19 = ~(1'b1 == 1'b1);

assign ap_block_state25_pp0_stage0_iter20 = ~(1'b1 == 1'b1);

assign ap_block_state26_pp0_stage0_iter21 = ~(1'b1 == 1'b1);

assign ap_block_state27_pp0_stage0_iter22 = ~(1'b1 == 1'b1);

assign ap_block_state28_pp0_stage0_iter23 = ~(1'b1 == 1'b1);

assign ap_block_state30_pp1_stage0_iter0 = ~(1'b1 == 1'b1);

always @ (*) begin
    ap_block_state31_pp1_stage0_iter1 = ((1'b0 == Output_1_full_n) & (icmp_ln882_3_reg_789 == 1'd0));
end

always @ (*) begin
    ap_block_state4 = ((1'b0 == Input_1_empty_n) | ((icmp_ln358_reg_597 == 1'd0) & (1'b0 == Output_1_full_n)));
end

assign ap_block_state5_pp0_stage0_iter0 = ~(1'b1 == 1'b1);

assign ap_block_state6_pp0_stage0_iter1 = ~(1'b1 == 1'b1);

assign ap_block_state7_pp0_stage0_iter2 = ~(1'b1 == 1'b1);

assign ap_block_state8_pp0_stage0_iter3 = ~(1'b1 == 1'b1);

assign ap_block_state9_pp0_stage0_iter4 = ~(1'b1 == 1'b1);

assign ap_enable_pp0 = (ap_idle_pp0 ^ 1'b1);

assign ap_enable_pp1 = (ap_idle_pp1 ^ 1'b1);

assign flag_V_fu_234_p1 = Input_1_dout[1:0];

assign grp_fu_208_p4 = {{Input_1_dout[23:16]}};

assign grp_fu_359_p1 = zext_ln1368_reg_650;

assign grp_fu_364_p1 = zext_ln1368_reg_650;

assign grp_fu_558_p0 = sext_ln215_1_reg_681;

assign grp_fu_566_p0 = sext_ln215_3_reg_701;

assign grp_fu_574_p0 = sext_ln215_5_reg_711;

assign icmp_ln358_fu_238_p2 = ((flag_V_fu_234_p1 == 2'd0) ? 1'b1 : 1'b0);

assign icmp_ln366_fu_348_p2 = ((ap_phi_mux_empty_phi_fu_179_p4 == trunc_ln674_reg_621) ? 1'b1 : 1'b0);

assign icmp_ln882_3_fu_517_p2 = ((j_reg_187 == i_V_fu_72) ? 1'b1 : 1'b0);

assign icmp_ln882_fu_511_p2 = ((i_V_fu_72 == 16'd0) ? 1'b1 : 1'b0);

assign max_min_V_1_fu_252_p1 = Input_1_dout[7:0];

assign or_ln91_1_fu_463_p2 = (or_ln91_fu_459_p2 | grp_fu_566_p3);

assign or_ln91_fu_459_p2 = (grp_fu_574_p3 | grp_fu_558_p3);

assign p_Result_s_fu_537_p5 = {{{{fragment_color_V_q0}, {fragment_z_V_q0}}, {fragment_y_V_q0}}, {fragment_x_V_q0}};

assign ret_V_19_fu_420_p2 = (zext_ln1351_6_fu_417_p1 - zext_ln1351_reg_656);

assign ret_V_20_fu_269_p2 = (zext_ln1351_1_fu_263_p1 - zext_ln1351_2_fu_266_p1);

assign ret_V_21_fu_438_p0 = sext_ln215_reg_671;

assign ret_V_22_fu_390_p2 = (zext_ln1351_7_fu_387_p1 - zext_ln1351_2_reg_666);

assign ret_V_23_fu_282_p2 = (zext_ln1351_3_fu_279_p1 - zext_ln1351_fu_260_p1);

assign ret_V_25_fu_425_p2 = (zext_ln1351_6_fu_417_p1 - zext_ln1351_3_reg_676);

assign ret_V_26_fu_295_p2 = (zext_ln1351_4_fu_292_p1 - zext_ln1351_1_fu_263_p1);

assign ret_V_27_fu_446_p0 = sext_ln215_2_reg_691;

assign ret_V_28_fu_399_p2 = (zext_ln1351_7_fu_387_p1 - zext_ln1351_1_reg_661);

assign ret_V_29_fu_308_p2 = (zext_ln1351_5_fu_305_p1 - zext_ln1351_3_fu_279_p1);

assign ret_V_31_fu_430_p2 = (zext_ln1351_6_fu_417_p1 - zext_ln1351_5_reg_696);

assign ret_V_32_fu_318_p2 = (zext_ln1351_2_fu_266_p1 - zext_ln1351_4_fu_292_p1);

assign ret_V_33_fu_454_p1 = sext_ln215_4_reg_706;

assign ret_V_34_fu_408_p2 = (zext_ln1351_7_fu_387_p1 - zext_ln1351_4_reg_686);

assign ret_V_35_fu_328_p2 = (zext_ln1351_fu_260_p1 - zext_ln1351_5_fu_305_p1);

assign sext_ln215_1_fu_288_p1 = $signed(ret_V_23_fu_282_p2);

assign sext_ln215_2_fu_301_p1 = $signed(ret_V_26_fu_295_p2);

assign sext_ln215_3_fu_314_p1 = $signed(ret_V_29_fu_308_p2);

assign sext_ln215_4_fu_324_p1 = $signed(ret_V_32_fu_318_p2);

assign sext_ln215_5_fu_334_p1 = $signed(ret_V_35_fu_328_p2);

assign sext_ln215_fu_275_p1 = $signed(ret_V_20_fu_269_p2);

assign sext_ln414_fu_549_p1 = $signed(p_Result_s_fu_537_p5);

assign tmp_fu_468_p3 = or_ln91_1_fu_463_p2[32'd17];

assign triangle_2d_same_y1_V_fu_244_p1 = Input_1_dout[7:0];

assign trunc_ln1369_fu_369_p1 = grp_fu_359_p2[7:0];

assign trunc_ln211_fu_378_p1 = grp_fu_364_p2[7:0];

assign trunc_ln674_fu_248_p1 = Input_1_dout[15:0];

assign zext_ln1351_1_fu_263_p1 = triangle_2d_same_y1_V_reg_601;

assign zext_ln1351_2_fu_266_p1 = triangle_2d_same_y0_V_reg_587;

assign zext_ln1351_3_fu_279_p1 = triangle_2d_same_x1_V_reg_592;

assign zext_ln1351_4_fu_292_p1 = triangle_2d_same_y2_V_reg_611;

assign zext_ln1351_5_fu_305_p1 = triangle_2d_same_x2_V_reg_606;

assign zext_ln1351_6_fu_417_p1 = add_ln211_reg_725_pp0_iter20_reg;

assign zext_ln1351_7_fu_387_p1 = add_ln211_1_reg_731;

assign zext_ln1351_fu_260_p1 = triangle_2d_same_x0_V_reg_582;

assign zext_ln1368_fu_256_p1 = grp_fu_208_p4;

assign zext_ln211_fu_506_p1 = i_top_V_fu_68;

assign zext_ln414_fu_553_p1 = $unsigned(sext_ln414_fu_549_p1);

assign zext_ln538_fu_476_p1 = i_V_fu_72;

assign zext_ln882_fu_529_p1 = j_reg_187;

always @ (posedge ap_clk) begin
    zext_ln1368_reg_650[15:8] <= 8'b00000000;
    zext_ln1351_reg_656[8] <= 1'b0;
    zext_ln1351_1_reg_661[8] <= 1'b0;
    zext_ln1351_2_reg_666[8] <= 1'b0;
    zext_ln1351_3_reg_676[8] <= 1'b0;
    zext_ln1351_4_reg_686[8] <= 1'b0;
    zext_ln1351_5_reg_696[8] <= 1'b0;
end

endmodule //rendering_m_rasterization2_odd
// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.1 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
`timescale 1 ns / 1 ps

module rendering_m_udiv_16ns_8ns_8_20_1_div_u
#(parameter
    in0_WIDTH = 32,
    in1_WIDTH = 32,
    out_WIDTH = 32
)
(
    input                       clk,
    input                       reset,
    input                       ce,
    input       [in0_WIDTH-1:0] dividend,
    input       [in1_WIDTH-1:0] divisor,
    output wire [out_WIDTH-1:0] quot,
    output wire [out_WIDTH-1:0] remd
);

localparam cal_WIDTH = (in0_WIDTH > in1_WIDTH)? in0_WIDTH : in1_WIDTH;

//------------------------Local signal-------------------
reg  [in0_WIDTH-1:0] dividend_tmp[0:in0_WIDTH];
reg  [in1_WIDTH-1:0] divisor_tmp[0:in0_WIDTH];
reg  [in0_WIDTH-1:0] remd_tmp[0:in0_WIDTH];
wire [in0_WIDTH-1:0] comb_tmp[0:in0_WIDTH-1];
wire [cal_WIDTH:0]   cal_tmp[0:in0_WIDTH-1];
//------------------------Body---------------------------
assign  quot    = dividend_tmp[in0_WIDTH];
assign  remd    = remd_tmp[in0_WIDTH];

// dividend_tmp[0], divisor_tmp[0], remd_tmp[0]
always @(posedge clk)
begin
    if (ce) begin
        dividend_tmp[0] <= dividend;
        divisor_tmp[0]  <= divisor;
        remd_tmp[0]     <= 1'b0;
    end
end

genvar i;
generate 
    for (i = 0; i < in0_WIDTH; i = i + 1)
    begin : loop
        if (in0_WIDTH == 1) assign  comb_tmp[i]     = dividend_tmp[i][0];
        else                assign  comb_tmp[i]     = {remd_tmp[i][in0_WIDTH-2:0], dividend_tmp[i][in0_WIDTH-1]};
        assign  cal_tmp[i]      = {1'b0, comb_tmp[i]} - {1'b0, divisor_tmp[i]};

        always @(posedge clk)
        begin
            if (ce) begin
                if (in0_WIDTH == 1) dividend_tmp[i+1] <= ~cal_tmp[i][cal_WIDTH];
                else                dividend_tmp[i+1] <= {dividend_tmp[i][in0_WIDTH-2:0], ~cal_tmp[i][cal_WIDTH]};
                divisor_tmp[i+1]  <= divisor_tmp[i];
                remd_tmp[i+1]     <= cal_tmp[i][cal_WIDTH]? comb_tmp[i] : cal_tmp[i][in0_WIDTH-1:0];
            end
        end
    end
endgenerate

endmodule

module rendering_m_udiv_16ns_8ns_8_20_1_div
#(parameter
        in0_WIDTH   = 32,
        in1_WIDTH   = 32,
        out_WIDTH   = 32
)
(
        input                           clk,
        input                           reset,
        input                           ce,
        input           [in0_WIDTH-1:0] dividend,
        input           [in1_WIDTH-1:0] divisor,
        output  reg     [out_WIDTH-1:0] quot,
        output  reg     [out_WIDTH-1:0] remd
);
//------------------------Local signal-------------------
reg     [in0_WIDTH-1:0] dividend0;
reg     [in1_WIDTH-1:0] divisor0;
wire    [in0_WIDTH-1:0] dividend_u;
wire    [in1_WIDTH-1:0] divisor_u;
wire    [out_WIDTH-1:0] quot_u;
wire    [out_WIDTH-1:0] remd_u;
//------------------------Instantiation------------------
rendering_m_udiv_16ns_8ns_8_20_1_div_u #(
    .in0_WIDTH      ( in0_WIDTH ),
    .in1_WIDTH      ( in1_WIDTH ),
    .out_WIDTH      ( out_WIDTH )
) rendering_m_udiv_16ns_8ns_8_20_1_div_u_0 (
    .clk      ( clk ),
    .reset    ( reset ),
    .ce       ( ce ),
    .dividend ( dividend_u ),
    .divisor  ( divisor_u ),
    .quot     ( quot_u ),
    .remd     ( remd_u )
);
//------------------------Body---------------------------
assign dividend_u = dividend0;
assign divisor_u = divisor0;

always @(posedge clk)
begin
    if (ce) begin
        dividend0 <= dividend;
        divisor0  <= divisor;
    end
end

always @(posedge clk)
begin
    if (ce) begin
        quot <= quot_u;
        remd <= remd_u;
    end
end

endmodule


`timescale 1 ns / 1 ps
module rendering_m_udiv_16ns_8ns_8_20_1(
    clk,
    reset,
    ce,
    din0,
    din1,
    dout);

parameter ID = 32'd1;
parameter NUM_STAGE = 32'd1;
parameter din0_WIDTH = 32'd1;
parameter din1_WIDTH = 32'd1;
parameter dout_WIDTH = 32'd1;
input clk;
input reset;
input ce;
input[din0_WIDTH - 1:0] din0;
input[din1_WIDTH - 1:0] din1;
output[dout_WIDTH - 1:0] dout;

wire[dout_WIDTH - 1:0] sig_remd;


rendering_m_udiv_16ns_8ns_8_20_1_div #(
.in0_WIDTH( din0_WIDTH ),
.in1_WIDTH( din1_WIDTH ),
.out_WIDTH( dout_WIDTH ))
rendering_m_udiv_16ns_8ns_8_20_1_div_U(
    .dividend( din0 ),
    .divisor( din1 ),
    .quot( dout ),
    .remd( sig_remd ),
    .clk( clk ),
    .ce( ce ),
    .reset( reset ));

endmodule

// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.1 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
`timescale 1 ns / 1 ps

module rendering_m_urem_16ns_8ns_8_20_1_div_u
#(parameter
    in0_WIDTH = 32,
    in1_WIDTH = 32,
    out_WIDTH = 32
)
(
    input                       clk,
    input                       reset,
    input                       ce,
    input       [in0_WIDTH-1:0] dividend,
    input       [in1_WIDTH-1:0] divisor,
    output wire [out_WIDTH-1:0] quot,
    output wire [out_WIDTH-1:0] remd
);

localparam cal_WIDTH = (in0_WIDTH > in1_WIDTH)? in0_WIDTH : in1_WIDTH;

//------------------------Local signal-------------------
reg  [in0_WIDTH-1:0] dividend_tmp[0:in0_WIDTH];
reg  [in1_WIDTH-1:0] divisor_tmp[0:in0_WIDTH];
reg  [in0_WIDTH-1:0] remd_tmp[0:in0_WIDTH];
wire [in0_WIDTH-1:0] comb_tmp[0:in0_WIDTH-1];
wire [cal_WIDTH:0]   cal_tmp[0:in0_WIDTH-1];
//------------------------Body---------------------------
assign  quot    = dividend_tmp[in0_WIDTH];
assign  remd    = remd_tmp[in0_WIDTH];

// dividend_tmp[0], divisor_tmp[0], remd_tmp[0]
always @(posedge clk)
begin
    if (ce) begin
        dividend_tmp[0] <= dividend;
        divisor_tmp[0]  <= divisor;
        remd_tmp[0]     <= 1'b0;
    end
end

genvar i;
generate 
    for (i = 0; i < in0_WIDTH; i = i + 1)
    begin : loop
        if (in0_WIDTH == 1) assign  comb_tmp[i]     = dividend_tmp[i][0];
        else                assign  comb_tmp[i]     = {remd_tmp[i][in0_WIDTH-2:0], dividend_tmp[i][in0_WIDTH-1]};
        assign  cal_tmp[i]      = {1'b0, comb_tmp[i]} - {1'b0, divisor_tmp[i]};

        always @(posedge clk)
        begin
            if (ce) begin
                if (in0_WIDTH == 1) dividend_tmp[i+1] <= ~cal_tmp[i][cal_WIDTH];
                else                dividend_tmp[i+1] <= {dividend_tmp[i][in0_WIDTH-2:0], ~cal_tmp[i][cal_WIDTH]};
                divisor_tmp[i+1]  <= divisor_tmp[i];
                remd_tmp[i+1]     <= cal_tmp[i][cal_WIDTH]? comb_tmp[i] : cal_tmp[i][in0_WIDTH-1:0];
            end
        end
    end
endgenerate

endmodule

module rendering_m_urem_16ns_8ns_8_20_1_div
#(parameter
        in0_WIDTH   = 32,
        in1_WIDTH   = 32,
        out_WIDTH   = 32
)
(
        input                           clk,
        input                           reset,
        input                           ce,
        input           [in0_WIDTH-1:0] dividend,
        input           [in1_WIDTH-1:0] divisor,
        output  reg     [out_WIDTH-1:0] quot,
        output  reg     [out_WIDTH-1:0] remd
);
//------------------------Local signal-------------------
reg     [in0_WIDTH-1:0] dividend0;
reg     [in1_WIDTH-1:0] divisor0;
wire    [in0_WIDTH-1:0] dividend_u;
wire    [in1_WIDTH-1:0] divisor_u;
wire    [out_WIDTH-1:0] quot_u;
wire    [out_WIDTH-1:0] remd_u;
//------------------------Instantiation------------------
rendering_m_urem_16ns_8ns_8_20_1_div_u #(
    .in0_WIDTH      ( in0_WIDTH ),
    .in1_WIDTH      ( in1_WIDTH ),
    .out_WIDTH      ( out_WIDTH )
) rendering_m_urem_16ns_8ns_8_20_1_div_u_0 (
    .clk      ( clk ),
    .reset    ( reset ),
    .ce       ( ce ),
    .dividend ( dividend_u ),
    .divisor  ( divisor_u ),
    .quot     ( quot_u ),
    .remd     ( remd_u )
);
//------------------------Body---------------------------
assign dividend_u = dividend0;
assign divisor_u = divisor0;

always @(posedge clk)
begin
    if (ce) begin
        dividend0 <= dividend;
        divisor0  <= divisor;
    end
end

always @(posedge clk)
begin
    if (ce) begin
        quot <= quot_u;
        remd <= remd_u;
    end
end

endmodule


`timescale 1 ns / 1 ps
module rendering_m_urem_16ns_8ns_8_20_1(
    clk,
    reset,
    ce,
    din0,
    din1,
    dout);

parameter ID = 32'd1;
parameter NUM_STAGE = 32'd1;
parameter din0_WIDTH = 32'd1;
parameter din1_WIDTH = 32'd1;
parameter dout_WIDTH = 32'd1;
input clk;
input reset;
input ce;
input[din0_WIDTH - 1:0] din0;
input[din1_WIDTH - 1:0] din1;
output[dout_WIDTH - 1:0] dout;

wire[dout_WIDTH - 1:0] sig_quot;


rendering_m_urem_16ns_8ns_8_20_1_div #(
.in0_WIDTH( din0_WIDTH ),
.in1_WIDTH( din1_WIDTH ),
.out_WIDTH( dout_WIDTH ))
rendering_m_urem_16ns_8ns_8_20_1_div_U(
    .dividend( din0 ),
    .divisor( din1 ),
    .remd( dout ),
    .quot( sig_quot ),
    .clk( clk ),
    .ce( ce ),
    .reset( reset ));

endmodule

// ==============================================================
// RTL generated by Vitis HLS - High-Level Synthesis from C, C++ and OpenCL
// Version: 2020.1
// Copyright (C) 1986-2020 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

`timescale 1 ns / 1 ps 

(* CORE_GENERATION_INFO="rendering_m_rendering_m,hls_ip_2020_1,{HLS_INPUT_TYPE=cxx,HLS_INPUT_FLOAT=0,HLS_INPUT_FIXED=0,HLS_INPUT_PART=xc7a200t-fbv484-1,HLS_INPUT_CLOCK=10.000000,HLS_INPUT_ARCH=dataflow,HLS_SYN_CLOCK=8.981500,HLS_SYN_LAT=-1,HLS_SYN_TPT=-1,HLS_SYN_MEM=77,HLS_SYN_DSP=0,HLS_SYN_FF=2186,HLS_SYN_LUT=15174,HLS_VERSION=2020_1}" *)

module rendering_m (
        Input_1_V_TDATA,
        Output_1_V_TDATA,
        ap_clk,
        ap_rst_n,
        Input_1_V_TVALID,
        Input_1_V_TREADY,
        Output_1_V_TVALID,
        Output_1_V_TREADY,
        ap_start,
        ap_done,
        ap_ready,
        ap_idle
);


input  [31:0] Input_1_V_TDATA;
output  [31:0] Output_1_V_TDATA;
input   ap_clk;
input   ap_rst_n;
input   Input_1_V_TVALID;
output   Input_1_V_TREADY;
output   Output_1_V_TVALID;
input   Output_1_V_TREADY;
input   ap_start;
output   ap_done;
output   ap_ready;
output   ap_idle;

 reg    ap_rst_n_inv;
wire    Loop_TRIANGLES_proc27_U0_ap_start;
wire    Loop_TRIANGLES_proc27_U0_ap_done;
wire    Loop_TRIANGLES_proc27_U0_ap_continue;
wire    Loop_TRIANGLES_proc27_U0_ap_idle;
wire    Loop_TRIANGLES_proc27_U0_ap_ready;
wire    Loop_TRIANGLES_proc27_U0_Input_1_V_TREADY;
wire   [31:0] Loop_TRIANGLES_proc27_U0_Output_1_V_TDATA;
wire    Loop_TRIANGLES_proc27_U0_Output_1_V_TVALID;
wire    ap_sync_continue;
wire    ap_sync_done;
wire    ap_sync_ready;
wire    Loop_TRIANGLES_proc27_U0_start_full_n;
wire    Loop_TRIANGLES_proc27_U0_start_write;

rendering_m_Loop_TRIANGLES_proc27 Loop_TRIANGLES_proc27_U0(
    .ap_clk(ap_clk),
    .ap_rst(ap_rst_n_inv),
    .ap_start(Loop_TRIANGLES_proc27_U0_ap_start),
    .ap_done(Loop_TRIANGLES_proc27_U0_ap_done),
    .ap_continue(Loop_TRIANGLES_proc27_U0_ap_continue),
    .ap_idle(Loop_TRIANGLES_proc27_U0_ap_idle),
    .ap_ready(Loop_TRIANGLES_proc27_U0_ap_ready),
    .Input_1_V_TDATA(Input_1_V_TDATA),
    .Input_1_V_TVALID(Input_1_V_TVALID),
    .Input_1_V_TREADY(Loop_TRIANGLES_proc27_U0_Input_1_V_TREADY),
    .Output_1_V_TDATA(Loop_TRIANGLES_proc27_U0_Output_1_V_TDATA),
    .Output_1_V_TVALID(Loop_TRIANGLES_proc27_U0_Output_1_V_TVALID),
    .Output_1_V_TREADY(Output_1_V_TREADY)
);

assign Input_1_V_TREADY = Loop_TRIANGLES_proc27_U0_Input_1_V_TREADY;

assign Loop_TRIANGLES_proc27_U0_ap_continue = 1'b1;

assign Loop_TRIANGLES_proc27_U0_ap_start = ap_start;

assign Loop_TRIANGLES_proc27_U0_start_full_n = 1'b1;

assign Loop_TRIANGLES_proc27_U0_start_write = 1'b0;

assign Output_1_V_TDATA = Loop_TRIANGLES_proc27_U0_Output_1_V_TDATA;

assign Output_1_V_TVALID = Loop_TRIANGLES_proc27_U0_Output_1_V_TVALID;

assign ap_done = Loop_TRIANGLES_proc27_U0_ap_done;

assign ap_idle = Loop_TRIANGLES_proc27_U0_ap_idle;

assign ap_ready = Loop_TRIANGLES_proc27_U0_ap_ready;

always @ (*) begin
    ap_rst_n_inv = ~ap_rst_n;
end

assign ap_sync_continue = 1'b1;

assign ap_sync_done = Loop_TRIANGLES_proc27_U0_ap_done;

assign ap_sync_ready = Loop_TRIANGLES_proc27_U0_ap_ready;

endmodule //rendering_m
// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.1 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
`timescale 1 ns / 1 ps
module rendering_m_zculling_top_pixels_x_V_ram (addr0, ce0, d0, we0, q0,  clk);

parameter DWIDTH = 8;
parameter AWIDTH = 9;
parameter MEM_SIZE = 500;

input[AWIDTH-1:0] addr0;
input ce0;
input[DWIDTH-1:0] d0;
input we0;
output reg[DWIDTH-1:0] q0;
input clk;

(* ram_style = "block" *)reg [DWIDTH-1:0] ram[0:MEM_SIZE-1];




always @(posedge clk)  
begin 
    if (ce0) begin
        if (we0) 
            ram[addr0] <= d0; 
        q0 <= ram[addr0];
    end
end


endmodule

`timescale 1 ns / 1 ps
module rendering_m_zculling_top_pixels_x_V(
    reset,
    clk,
    address0,
    ce0,
    we0,
    d0,
    q0);

parameter DataWidth = 32'd8;
parameter AddressRange = 32'd500;
parameter AddressWidth = 32'd9;
input reset;
input clk;
input[AddressWidth - 1:0] address0;
input ce0;
input we0;
input[DataWidth - 1:0] d0;
output[DataWidth - 1:0] q0;



rendering_m_zculling_top_pixels_x_V_ram rendering_m_zculling_top_pixels_x_V_ram_U(
    .clk( clk ),
    .addr0( address0 ),
    .ce0( ce0 ),
    .we0( we0 ),
    .d0( d0 ),
    .q0( q0 ));

endmodule

// ==============================================================
// RTL generated by Vitis HLS - High-Level Synthesis from C, C++ and OpenCL
// Version: 2020.1
// Copyright (C) 1986-2020 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

`timescale 1 ns / 1 ps 

module rendering_m_zculling_top (
        ap_clk,
        ap_rst,
        ap_start,
        ap_done,
        ap_idle,
        ap_ready,
        Input_1_dout,
        Input_1_empty_n,
        Input_1_read,
        Output_1_din,
        Output_1_full_n,
        Output_1_write
);

parameter    ap_ST_fsm_state1 = 135'd1;
parameter    ap_ST_fsm_state2 = 135'd2;
parameter    ap_ST_fsm_state3 = 135'd4;
parameter    ap_ST_fsm_state4 = 135'd8;
parameter    ap_ST_fsm_state5 = 135'd16;
parameter    ap_ST_fsm_state6 = 135'd32;
parameter    ap_ST_fsm_state7 = 135'd64;
parameter    ap_ST_fsm_state8 = 135'd128;
parameter    ap_ST_fsm_state9 = 135'd256;
parameter    ap_ST_fsm_state10 = 135'd512;
parameter    ap_ST_fsm_state11 = 135'd1024;
parameter    ap_ST_fsm_state12 = 135'd2048;
parameter    ap_ST_fsm_state13 = 135'd4096;
parameter    ap_ST_fsm_state14 = 135'd8192;
parameter    ap_ST_fsm_state15 = 135'd16384;
parameter    ap_ST_fsm_state16 = 135'd32768;
parameter    ap_ST_fsm_state17 = 135'd65536;
parameter    ap_ST_fsm_state18 = 135'd131072;
parameter    ap_ST_fsm_state19 = 135'd262144;
parameter    ap_ST_fsm_state20 = 135'd524288;
parameter    ap_ST_fsm_state21 = 135'd1048576;
parameter    ap_ST_fsm_state22 = 135'd2097152;
parameter    ap_ST_fsm_state23 = 135'd4194304;
parameter    ap_ST_fsm_state24 = 135'd8388608;
parameter    ap_ST_fsm_state25 = 135'd16777216;
parameter    ap_ST_fsm_state26 = 135'd33554432;
parameter    ap_ST_fsm_state27 = 135'd67108864;
parameter    ap_ST_fsm_state28 = 135'd134217728;
parameter    ap_ST_fsm_state29 = 135'd268435456;
parameter    ap_ST_fsm_state30 = 135'd536870912;
parameter    ap_ST_fsm_state31 = 135'd1073741824;
parameter    ap_ST_fsm_state32 = 135'd2147483648;
parameter    ap_ST_fsm_state33 = 135'd4294967296;
parameter    ap_ST_fsm_state34 = 135'd8589934592;
parameter    ap_ST_fsm_state35 = 135'd17179869184;
parameter    ap_ST_fsm_state36 = 135'd34359738368;
parameter    ap_ST_fsm_state37 = 135'd68719476736;
parameter    ap_ST_fsm_state38 = 135'd137438953472;
parameter    ap_ST_fsm_state39 = 135'd274877906944;
parameter    ap_ST_fsm_state40 = 135'd549755813888;
parameter    ap_ST_fsm_state41 = 135'd1099511627776;
parameter    ap_ST_fsm_state42 = 135'd2199023255552;
parameter    ap_ST_fsm_state43 = 135'd4398046511104;
parameter    ap_ST_fsm_state44 = 135'd8796093022208;
parameter    ap_ST_fsm_state45 = 135'd17592186044416;
parameter    ap_ST_fsm_state46 = 135'd35184372088832;
parameter    ap_ST_fsm_state47 = 135'd70368744177664;
parameter    ap_ST_fsm_state48 = 135'd140737488355328;
parameter    ap_ST_fsm_state49 = 135'd281474976710656;
parameter    ap_ST_fsm_state50 = 135'd562949953421312;
parameter    ap_ST_fsm_state51 = 135'd1125899906842624;
parameter    ap_ST_fsm_state52 = 135'd2251799813685248;
parameter    ap_ST_fsm_state53 = 135'd4503599627370496;
parameter    ap_ST_fsm_state54 = 135'd9007199254740992;
parameter    ap_ST_fsm_state55 = 135'd18014398509481984;
parameter    ap_ST_fsm_state56 = 135'd36028797018963968;
parameter    ap_ST_fsm_state57 = 135'd72057594037927936;
parameter    ap_ST_fsm_state58 = 135'd144115188075855872;
parameter    ap_ST_fsm_state59 = 135'd288230376151711744;
parameter    ap_ST_fsm_state60 = 135'd576460752303423488;
parameter    ap_ST_fsm_state61 = 135'd1152921504606846976;
parameter    ap_ST_fsm_state62 = 135'd2305843009213693952;
parameter    ap_ST_fsm_state63 = 135'd4611686018427387904;
parameter    ap_ST_fsm_state64 = 135'd9223372036854775808;
parameter    ap_ST_fsm_state65 = 135'd18446744073709551616;
parameter    ap_ST_fsm_state66 = 135'd36893488147419103232;
parameter    ap_ST_fsm_state67 = 135'd73786976294838206464;
parameter    ap_ST_fsm_state68 = 135'd147573952589676412928;
parameter    ap_ST_fsm_state69 = 135'd295147905179352825856;
parameter    ap_ST_fsm_state70 = 135'd590295810358705651712;
parameter    ap_ST_fsm_state71 = 135'd1180591620717411303424;
parameter    ap_ST_fsm_state72 = 135'd2361183241434822606848;
parameter    ap_ST_fsm_state73 = 135'd4722366482869645213696;
parameter    ap_ST_fsm_state74 = 135'd9444732965739290427392;
parameter    ap_ST_fsm_state75 = 135'd18889465931478580854784;
parameter    ap_ST_fsm_state76 = 135'd37778931862957161709568;
parameter    ap_ST_fsm_state77 = 135'd75557863725914323419136;
parameter    ap_ST_fsm_state78 = 135'd151115727451828646838272;
parameter    ap_ST_fsm_state79 = 135'd302231454903657293676544;
parameter    ap_ST_fsm_state80 = 135'd604462909807314587353088;
parameter    ap_ST_fsm_state81 = 135'd1208925819614629174706176;
parameter    ap_ST_fsm_state82 = 135'd2417851639229258349412352;
parameter    ap_ST_fsm_state83 = 135'd4835703278458516698824704;
parameter    ap_ST_fsm_state84 = 135'd9671406556917033397649408;
parameter    ap_ST_fsm_state85 = 135'd19342813113834066795298816;
parameter    ap_ST_fsm_state86 = 135'd38685626227668133590597632;
parameter    ap_ST_fsm_state87 = 135'd77371252455336267181195264;
parameter    ap_ST_fsm_state88 = 135'd154742504910672534362390528;
parameter    ap_ST_fsm_state89 = 135'd309485009821345068724781056;
parameter    ap_ST_fsm_state90 = 135'd618970019642690137449562112;
parameter    ap_ST_fsm_state91 = 135'd1237940039285380274899124224;
parameter    ap_ST_fsm_state92 = 135'd2475880078570760549798248448;
parameter    ap_ST_fsm_state93 = 135'd4951760157141521099596496896;
parameter    ap_ST_fsm_state94 = 135'd9903520314283042199192993792;
parameter    ap_ST_fsm_state95 = 135'd19807040628566084398385987584;
parameter    ap_ST_fsm_state96 = 135'd39614081257132168796771975168;
parameter    ap_ST_fsm_state97 = 135'd79228162514264337593543950336;
parameter    ap_ST_fsm_state98 = 135'd158456325028528675187087900672;
parameter    ap_ST_fsm_state99 = 135'd316912650057057350374175801344;
parameter    ap_ST_fsm_state100 = 135'd633825300114114700748351602688;
parameter    ap_ST_fsm_state101 = 135'd1267650600228229401496703205376;
parameter    ap_ST_fsm_state102 = 135'd2535301200456458802993406410752;
parameter    ap_ST_fsm_state103 = 135'd5070602400912917605986812821504;
parameter    ap_ST_fsm_state104 = 135'd10141204801825835211973625643008;
parameter    ap_ST_fsm_state105 = 135'd20282409603651670423947251286016;
parameter    ap_ST_fsm_state106 = 135'd40564819207303340847894502572032;
parameter    ap_ST_fsm_state107 = 135'd81129638414606681695789005144064;
parameter    ap_ST_fsm_state108 = 135'd162259276829213363391578010288128;
parameter    ap_ST_fsm_state109 = 135'd324518553658426726783156020576256;
parameter    ap_ST_fsm_state110 = 135'd649037107316853453566312041152512;
parameter    ap_ST_fsm_state111 = 135'd1298074214633706907132624082305024;
parameter    ap_ST_fsm_state112 = 135'd2596148429267413814265248164610048;
parameter    ap_ST_fsm_state113 = 135'd5192296858534827628530496329220096;
parameter    ap_ST_fsm_state114 = 135'd10384593717069655257060992658440192;
parameter    ap_ST_fsm_state115 = 135'd20769187434139310514121985316880384;
parameter    ap_ST_fsm_state116 = 135'd41538374868278621028243970633760768;
parameter    ap_ST_fsm_state117 = 135'd83076749736557242056487941267521536;
parameter    ap_ST_fsm_state118 = 135'd166153499473114484112975882535043072;
parameter    ap_ST_fsm_state119 = 135'd332306998946228968225951765070086144;
parameter    ap_ST_fsm_state120 = 135'd664613997892457936451903530140172288;
parameter    ap_ST_fsm_state121 = 135'd1329227995784915872903807060280344576;
parameter    ap_ST_fsm_state122 = 135'd2658455991569831745807614120560689152;
parameter    ap_ST_fsm_state123 = 135'd5316911983139663491615228241121378304;
parameter    ap_ST_fsm_state124 = 135'd10633823966279326983230456482242756608;
parameter    ap_ST_fsm_state125 = 135'd21267647932558653966460912964485513216;
parameter    ap_ST_fsm_state126 = 135'd42535295865117307932921825928971026432;
parameter    ap_ST_fsm_state127 = 135'd85070591730234615865843651857942052864;
parameter    ap_ST_fsm_state128 = 135'd170141183460469231731687303715884105728;
parameter    ap_ST_fsm_state129 = 135'd340282366920938463463374607431768211456;
parameter    ap_ST_fsm_state130 = 135'd680564733841876926926749214863536422912;
parameter    ap_ST_fsm_pp1_stage0 = 135'd1361129467683753853853498429727072845824;
parameter    ap_ST_fsm_pp1_stage1 = 135'd2722258935367507707706996859454145691648;
parameter    ap_ST_fsm_state135 = 135'd5444517870735015415413993718908291383296;
parameter    ap_ST_fsm_pp2_stage0 = 135'd10889035741470030830827987437816582766592;
parameter    ap_ST_fsm_state138 = 135'd21778071482940061661655974875633165533184;

input   ap_clk;
input   ap_rst;
input   ap_start;
output   ap_done;
output   ap_idle;
output   ap_ready;
input  [31:0] Input_1_dout;
input   Input_1_empty_n;
output   Input_1_read;
output  [31:0] Output_1_din;
input   Output_1_full_n;
output   Output_1_write;

reg ap_done;
reg ap_idle;
reg ap_ready;
reg Input_1_read;
reg[31:0] Output_1_din;
reg Output_1_write;

(* fsm_encoding = "none" *) reg   [134:0] ap_CS_fsm;
wire    ap_CS_fsm_state1;
reg   [15:0] counter;
reg   [15:0] z_buffer_V_address0;
reg    z_buffer_V_ce0;
reg    z_buffer_V_we0;
reg   [7:0] z_buffer_V_d0;
reg   [15:0] z_buffer_V_address1;
reg    z_buffer_V_ce1;
reg    z_buffer_V_we1;
wire   [7:0] z_buffer_V_q1;
reg    Input_1_blk_n;
wire    ap_CS_fsm_pp1_stage1;
reg    ap_enable_reg_pp1_iter0;
wire    ap_block_pp1_stage1;
reg   [0:0] icmp_ln449_reg_6824;
reg    Output_1_blk_n;
wire    ap_CS_fsm_state135;
wire    ap_CS_fsm_pp2_stage0;
reg    ap_enable_reg_pp2_iter1;
wire    ap_block_pp2_stage0;
reg   [0:0] icmp_ln882_2_reg_6864;
reg   [15:0] empty_23_reg_2754;
reg   [15:0] j_reg_2765;
reg   [31:0] tmp_V_reg_6532;
reg    ap_block_state1;
reg   [15:0] t_V_reg_6537;
wire   [0:0] icmp_ln874_fu_2783_p2;
wire   [8:0] add_ln695_fu_2795_p2;
reg   [8:0] add_ln695_reg_6549;
wire    ap_CS_fsm_state2;
wire   [16:0] tmp_fu_2801_p3;
reg   [16:0] tmp_reg_6554;
wire   [0:0] icmp_ln882_fu_2789_p2;
wire   [15:0] empty_22_fu_6385_p1;
reg   [15:0] empty_22_reg_6819;
wire    ap_CS_fsm_state130;
wire   [0:0] icmp_ln449_fu_6393_p2;
wire    ap_CS_fsm_pp1_stage0;
wire    ap_block_state131_pp1_stage0_iter0;
wire    ap_block_state133_pp1_stage0_iter1;
wire    ap_block_pp1_stage0_11001;
wire   [15:0] add_ln695_2_fu_6398_p2;
reg   [15:0] add_ln695_2_reg_6828;
wire   [7:0] trunc_ln674_fu_6404_p1;
reg   [7:0] trunc_ln674_reg_6833;
reg    ap_block_state132_pp1_stage1_iter0;
wire    ap_block_state134_pp1_stage1_iter1;
reg    ap_block_pp1_stage1_11001;
reg   [7:0] p_Result_1_reg_6838;
reg   [7:0] p_Result_2_reg_6843;
reg   [7:0] p_Result_3_reg_6849;
reg   [15:0] z_buffer_V_addr_1_reg_6854;
wire   [0:0] icmp_ln882_1_fu_6447_p2;
reg   [0:0] icmp_ln882_1_reg_6860;
wire   [0:0] icmp_ln882_2_fu_6475_p2;
wire    ap_block_state136_pp2_stage0_iter0;
reg    ap_block_state137_pp2_stage0_iter1;
reg    ap_block_pp2_stage0_11001;
wire   [15:0] add_ln469_fu_6481_p2;
reg    ap_enable_reg_pp2_iter0;
wire    ap_block_pp1_stage0_subdone;
reg    ap_condition_pp1_exit_iter0_state131;
reg    ap_enable_reg_pp1_iter1;
reg    ap_block_pp1_stage1_subdone;
reg    ap_block_pp2_stage0_subdone;
reg    ap_condition_pp2_exit_iter0_state136;
reg   [8:0] pixels_x_V_address0;
reg    pixels_x_V_ce0;
reg    pixels_x_V_we0;
wire   [7:0] pixels_x_V_q0;
reg   [8:0] pixels_y_V_address0;
reg    pixels_y_V_ce0;
reg    pixels_y_V_we0;
wire   [7:0] pixels_y_V_q0;
reg   [8:0] pixels_color_V_address0;
reg    pixels_color_V_ce0;
reg    pixels_color_V_we0;
wire   [7:0] pixels_color_V_q0;
reg   [8:0] empty_reg_2743;
wire    ap_CS_fsm_state129;
reg   [15:0] ap_phi_mux_empty_23_phi_fu_2758_p4;
wire    ap_block_pp1_stage0;
wire   [63:0] zext_ln324_fu_2809_p1;
wire   [63:0] tmp_1_fu_2820_p3;
wire   [63:0] tmp_2_fu_2834_p3;
wire    ap_CS_fsm_state3;
wire   [63:0] tmp_3_fu_2848_p3;
wire   [63:0] tmp_4_fu_2862_p3;
wire    ap_CS_fsm_state4;
wire   [63:0] tmp_5_fu_2876_p3;
wire   [63:0] tmp_6_fu_2890_p3;
wire    ap_CS_fsm_state5;
wire   [63:0] tmp_7_fu_2904_p3;
wire   [63:0] tmp_8_fu_2918_p3;
wire    ap_CS_fsm_state6;
wire   [63:0] tmp_9_fu_2932_p3;
wire   [63:0] tmp_s_fu_2946_p3;
wire    ap_CS_fsm_state7;
wire   [63:0] tmp_10_fu_2960_p3;
wire   [63:0] tmp_11_fu_2974_p3;
wire    ap_CS_fsm_state8;
wire   [63:0] tmp_12_fu_2988_p3;
wire   [63:0] tmp_13_fu_3002_p3;
wire    ap_CS_fsm_state9;
wire   [63:0] tmp_14_fu_3016_p3;
wire   [63:0] tmp_15_fu_3030_p3;
wire    ap_CS_fsm_state10;
wire   [63:0] tmp_16_fu_3044_p3;
wire   [63:0] tmp_17_fu_3058_p3;
wire    ap_CS_fsm_state11;
wire   [63:0] tmp_18_fu_3072_p3;
wire   [63:0] tmp_19_fu_3086_p3;
wire    ap_CS_fsm_state12;
wire   [63:0] tmp_20_fu_3100_p3;
wire   [63:0] tmp_21_fu_3114_p3;
wire    ap_CS_fsm_state13;
wire   [63:0] tmp_22_fu_3128_p3;
wire   [63:0] tmp_23_fu_3142_p3;
wire    ap_CS_fsm_state14;
wire   [63:0] tmp_24_fu_3156_p3;
wire   [63:0] tmp_25_fu_3170_p3;
wire    ap_CS_fsm_state15;
wire   [63:0] tmp_26_fu_3184_p3;
wire   [63:0] tmp_27_fu_3198_p3;
wire    ap_CS_fsm_state16;
wire   [63:0] tmp_28_fu_3212_p3;
wire   [63:0] tmp_29_fu_3226_p3;
wire    ap_CS_fsm_state17;
wire   [63:0] tmp_30_fu_3240_p3;
wire   [63:0] tmp_31_fu_3254_p3;
wire    ap_CS_fsm_state18;
wire   [63:0] tmp_32_fu_3268_p3;
wire   [63:0] tmp_33_fu_3282_p3;
wire    ap_CS_fsm_state19;
wire   [63:0] tmp_34_fu_3296_p3;
wire   [63:0] tmp_35_fu_3310_p3;
wire    ap_CS_fsm_state20;
wire   [63:0] tmp_36_fu_3324_p3;
wire   [63:0] tmp_37_fu_3338_p3;
wire    ap_CS_fsm_state21;
wire   [63:0] tmp_38_fu_3352_p3;
wire   [63:0] tmp_39_fu_3366_p3;
wire    ap_CS_fsm_state22;
wire   [63:0] tmp_40_fu_3380_p3;
wire   [63:0] tmp_41_fu_3394_p3;
wire    ap_CS_fsm_state23;
wire   [63:0] tmp_42_fu_3408_p3;
wire   [63:0] tmp_43_fu_3422_p3;
wire    ap_CS_fsm_state24;
wire   [63:0] tmp_44_fu_3436_p3;
wire   [63:0] tmp_45_fu_3450_p3;
wire    ap_CS_fsm_state25;
wire   [63:0] tmp_46_fu_3464_p3;
wire   [63:0] tmp_47_fu_3478_p3;
wire    ap_CS_fsm_state26;
wire   [63:0] tmp_48_fu_3492_p3;
wire   [63:0] tmp_49_fu_3506_p3;
wire    ap_CS_fsm_state27;
wire   [63:0] tmp_50_fu_3520_p3;
wire   [63:0] tmp_51_fu_3534_p3;
wire    ap_CS_fsm_state28;
wire   [63:0] tmp_52_fu_3548_p3;
wire   [63:0] tmp_53_fu_3562_p3;
wire    ap_CS_fsm_state29;
wire   [63:0] tmp_54_fu_3576_p3;
wire   [63:0] tmp_55_fu_3590_p3;
wire    ap_CS_fsm_state30;
wire   [63:0] tmp_56_fu_3604_p3;
wire   [63:0] tmp_57_fu_3618_p3;
wire    ap_CS_fsm_state31;
wire   [63:0] tmp_58_fu_3632_p3;
wire   [63:0] tmp_59_fu_3646_p3;
wire    ap_CS_fsm_state32;
wire   [63:0] tmp_60_fu_3660_p3;
wire   [63:0] tmp_61_fu_3674_p3;
wire    ap_CS_fsm_state33;
wire   [63:0] tmp_62_fu_3688_p3;
wire   [63:0] tmp_63_fu_3702_p3;
wire    ap_CS_fsm_state34;
wire   [63:0] tmp_64_fu_3716_p3;
wire   [63:0] tmp_65_fu_3730_p3;
wire    ap_CS_fsm_state35;
wire   [63:0] tmp_66_fu_3744_p3;
wire   [63:0] tmp_67_fu_3758_p3;
wire    ap_CS_fsm_state36;
wire   [63:0] tmp_68_fu_3772_p3;
wire   [63:0] tmp_69_fu_3786_p3;
wire    ap_CS_fsm_state37;
wire   [63:0] tmp_70_fu_3800_p3;
wire   [63:0] tmp_71_fu_3814_p3;
wire    ap_CS_fsm_state38;
wire   [63:0] tmp_72_fu_3828_p3;
wire   [63:0] tmp_73_fu_3842_p3;
wire    ap_CS_fsm_state39;
wire   [63:0] tmp_74_fu_3856_p3;
wire   [63:0] tmp_75_fu_3870_p3;
wire    ap_CS_fsm_state40;
wire   [63:0] tmp_76_fu_3884_p3;
wire   [63:0] tmp_77_fu_3898_p3;
wire    ap_CS_fsm_state41;
wire   [63:0] tmp_78_fu_3912_p3;
wire   [63:0] tmp_79_fu_3926_p3;
wire    ap_CS_fsm_state42;
wire   [63:0] tmp_80_fu_3940_p3;
wire   [63:0] tmp_81_fu_3954_p3;
wire    ap_CS_fsm_state43;
wire   [63:0] tmp_82_fu_3968_p3;
wire   [63:0] tmp_83_fu_3982_p3;
wire    ap_CS_fsm_state44;
wire   [63:0] tmp_84_fu_3996_p3;
wire   [63:0] tmp_85_fu_4010_p3;
wire    ap_CS_fsm_state45;
wire   [63:0] tmp_86_fu_4024_p3;
wire   [63:0] tmp_87_fu_4038_p3;
wire    ap_CS_fsm_state46;
wire   [63:0] tmp_88_fu_4052_p3;
wire   [63:0] tmp_89_fu_4066_p3;
wire    ap_CS_fsm_state47;
wire   [63:0] tmp_90_fu_4080_p3;
wire   [63:0] tmp_91_fu_4094_p3;
wire    ap_CS_fsm_state48;
wire   [63:0] tmp_92_fu_4108_p3;
wire   [63:0] tmp_93_fu_4122_p3;
wire    ap_CS_fsm_state49;
wire   [63:0] tmp_94_fu_4136_p3;
wire   [63:0] tmp_95_fu_4150_p3;
wire    ap_CS_fsm_state50;
wire   [63:0] tmp_96_fu_4164_p3;
wire   [63:0] tmp_97_fu_4178_p3;
wire    ap_CS_fsm_state51;
wire   [63:0] tmp_98_fu_4192_p3;
wire   [63:0] tmp_99_fu_4206_p3;
wire    ap_CS_fsm_state52;
wire   [63:0] tmp_100_fu_4220_p3;
wire   [63:0] tmp_101_fu_4234_p3;
wire    ap_CS_fsm_state53;
wire   [63:0] tmp_102_fu_4248_p3;
wire   [63:0] tmp_103_fu_4262_p3;
wire    ap_CS_fsm_state54;
wire   [63:0] tmp_104_fu_4276_p3;
wire   [63:0] tmp_105_fu_4290_p3;
wire    ap_CS_fsm_state55;
wire   [63:0] tmp_106_fu_4304_p3;
wire   [63:0] tmp_107_fu_4318_p3;
wire    ap_CS_fsm_state56;
wire   [63:0] tmp_108_fu_4332_p3;
wire   [63:0] tmp_109_fu_4346_p3;
wire    ap_CS_fsm_state57;
wire   [63:0] tmp_110_fu_4360_p3;
wire   [63:0] tmp_111_fu_4374_p3;
wire    ap_CS_fsm_state58;
wire   [63:0] tmp_112_fu_4388_p3;
wire   [63:0] tmp_113_fu_4402_p3;
wire    ap_CS_fsm_state59;
wire   [63:0] tmp_114_fu_4416_p3;
wire   [63:0] tmp_115_fu_4430_p3;
wire    ap_CS_fsm_state60;
wire   [63:0] tmp_116_fu_4444_p3;
wire   [63:0] tmp_117_fu_4458_p3;
wire    ap_CS_fsm_state61;
wire   [63:0] tmp_118_fu_4472_p3;
wire   [63:0] tmp_119_fu_4486_p3;
wire    ap_CS_fsm_state62;
wire   [63:0] tmp_120_fu_4500_p3;
wire   [63:0] tmp_121_fu_4514_p3;
wire    ap_CS_fsm_state63;
wire   [63:0] tmp_122_fu_4528_p3;
wire   [63:0] tmp_123_fu_4542_p3;
wire    ap_CS_fsm_state64;
wire   [63:0] tmp_124_fu_4556_p3;
wire   [63:0] tmp_125_fu_4570_p3;
wire    ap_CS_fsm_state65;
wire   [63:0] tmp_126_fu_4584_p3;
wire   [63:0] tmp_127_fu_4598_p3;
wire    ap_CS_fsm_state66;
wire   [63:0] tmp_128_fu_4612_p3;
wire   [63:0] tmp_129_fu_4626_p3;
wire    ap_CS_fsm_state67;
wire   [63:0] tmp_130_fu_4640_p3;
wire   [63:0] tmp_131_fu_4654_p3;
wire    ap_CS_fsm_state68;
wire   [63:0] tmp_132_fu_4668_p3;
wire   [63:0] tmp_133_fu_4682_p3;
wire    ap_CS_fsm_state69;
wire   [63:0] tmp_134_fu_4696_p3;
wire   [63:0] tmp_135_fu_4710_p3;
wire    ap_CS_fsm_state70;
wire   [63:0] tmp_136_fu_4724_p3;
wire   [63:0] tmp_137_fu_4738_p3;
wire    ap_CS_fsm_state71;
wire   [63:0] tmp_138_fu_4752_p3;
wire   [63:0] tmp_139_fu_4766_p3;
wire    ap_CS_fsm_state72;
wire   [63:0] tmp_140_fu_4780_p3;
wire   [63:0] tmp_141_fu_4794_p3;
wire    ap_CS_fsm_state73;
wire   [63:0] tmp_142_fu_4808_p3;
wire   [63:0] tmp_143_fu_4822_p3;
wire    ap_CS_fsm_state74;
wire   [63:0] tmp_144_fu_4836_p3;
wire   [63:0] tmp_145_fu_4850_p3;
wire    ap_CS_fsm_state75;
wire   [63:0] tmp_146_fu_4864_p3;
wire   [63:0] tmp_147_fu_4878_p3;
wire    ap_CS_fsm_state76;
wire   [63:0] tmp_148_fu_4892_p3;
wire   [63:0] tmp_149_fu_4906_p3;
wire    ap_CS_fsm_state77;
wire   [63:0] tmp_150_fu_4920_p3;
wire   [63:0] tmp_151_fu_4934_p3;
wire    ap_CS_fsm_state78;
wire   [63:0] tmp_152_fu_4948_p3;
wire   [63:0] tmp_153_fu_4962_p3;
wire    ap_CS_fsm_state79;
wire   [63:0] tmp_154_fu_4976_p3;
wire   [63:0] tmp_155_fu_4990_p3;
wire    ap_CS_fsm_state80;
wire   [63:0] tmp_156_fu_5004_p3;
wire   [63:0] tmp_157_fu_5018_p3;
wire    ap_CS_fsm_state81;
wire   [63:0] tmp_158_fu_5032_p3;
wire   [63:0] tmp_159_fu_5046_p3;
wire    ap_CS_fsm_state82;
wire   [63:0] tmp_160_fu_5060_p3;
wire   [63:0] tmp_161_fu_5074_p3;
wire    ap_CS_fsm_state83;
wire   [63:0] tmp_162_fu_5088_p3;
wire   [63:0] tmp_163_fu_5102_p3;
wire    ap_CS_fsm_state84;
wire   [63:0] tmp_164_fu_5116_p3;
wire   [63:0] tmp_165_fu_5130_p3;
wire    ap_CS_fsm_state85;
wire   [63:0] tmp_166_fu_5144_p3;
wire   [63:0] tmp_167_fu_5158_p3;
wire    ap_CS_fsm_state86;
wire   [63:0] tmp_168_fu_5172_p3;
wire   [63:0] tmp_169_fu_5186_p3;
wire    ap_CS_fsm_state87;
wire   [63:0] tmp_170_fu_5200_p3;
wire   [63:0] tmp_171_fu_5214_p3;
wire    ap_CS_fsm_state88;
wire   [63:0] tmp_172_fu_5228_p3;
wire   [63:0] tmp_173_fu_5242_p3;
wire    ap_CS_fsm_state89;
wire   [63:0] tmp_174_fu_5256_p3;
wire   [63:0] tmp_175_fu_5270_p3;
wire    ap_CS_fsm_state90;
wire   [63:0] tmp_176_fu_5284_p3;
wire   [63:0] tmp_177_fu_5298_p3;
wire    ap_CS_fsm_state91;
wire   [63:0] tmp_178_fu_5312_p3;
wire   [63:0] tmp_179_fu_5326_p3;
wire    ap_CS_fsm_state92;
wire   [63:0] tmp_180_fu_5340_p3;
wire   [63:0] tmp_181_fu_5354_p3;
wire    ap_CS_fsm_state93;
wire   [63:0] tmp_182_fu_5368_p3;
wire   [63:0] tmp_183_fu_5382_p3;
wire    ap_CS_fsm_state94;
wire   [63:0] tmp_184_fu_5396_p3;
wire   [63:0] tmp_185_fu_5410_p3;
wire    ap_CS_fsm_state95;
wire   [63:0] tmp_186_fu_5424_p3;
wire   [63:0] tmp_187_fu_5438_p3;
wire    ap_CS_fsm_state96;
wire   [63:0] tmp_188_fu_5452_p3;
wire   [63:0] tmp_189_fu_5466_p3;
wire    ap_CS_fsm_state97;
wire   [63:0] tmp_190_fu_5480_p3;
wire   [63:0] tmp_191_fu_5494_p3;
wire    ap_CS_fsm_state98;
wire   [63:0] tmp_192_fu_5508_p3;
wire   [63:0] tmp_193_fu_5522_p3;
wire    ap_CS_fsm_state99;
wire   [63:0] tmp_194_fu_5536_p3;
wire   [63:0] tmp_195_fu_5550_p3;
wire    ap_CS_fsm_state100;
wire   [63:0] tmp_196_fu_5564_p3;
wire   [63:0] tmp_197_fu_5578_p3;
wire    ap_CS_fsm_state101;
wire   [63:0] tmp_198_fu_5592_p3;
wire   [63:0] tmp_199_fu_5606_p3;
wire    ap_CS_fsm_state102;
wire   [63:0] tmp_200_fu_5620_p3;
wire   [63:0] tmp_201_fu_5634_p3;
wire    ap_CS_fsm_state103;
wire   [63:0] tmp_202_fu_5648_p3;
wire   [63:0] tmp_203_fu_5662_p3;
wire    ap_CS_fsm_state104;
wire   [63:0] tmp_204_fu_5676_p3;
wire   [63:0] tmp_205_fu_5690_p3;
wire    ap_CS_fsm_state105;
wire   [63:0] tmp_206_fu_5704_p3;
wire   [63:0] tmp_207_fu_5718_p3;
wire    ap_CS_fsm_state106;
wire   [63:0] tmp_208_fu_5732_p3;
wire   [63:0] tmp_209_fu_5746_p3;
wire    ap_CS_fsm_state107;
wire   [63:0] tmp_210_fu_5760_p3;
wire   [63:0] tmp_211_fu_5774_p3;
wire    ap_CS_fsm_state108;
wire   [63:0] tmp_212_fu_5788_p3;
wire   [63:0] tmp_213_fu_5802_p3;
wire    ap_CS_fsm_state109;
wire   [63:0] tmp_214_fu_5816_p3;
wire   [63:0] tmp_215_fu_5830_p3;
wire    ap_CS_fsm_state110;
wire   [63:0] tmp_216_fu_5844_p3;
wire   [63:0] tmp_217_fu_5858_p3;
wire    ap_CS_fsm_state111;
wire   [63:0] tmp_218_fu_5872_p3;
wire   [63:0] tmp_219_fu_5886_p3;
wire    ap_CS_fsm_state112;
wire   [63:0] tmp_220_fu_5900_p3;
wire   [63:0] tmp_221_fu_5914_p3;
wire    ap_CS_fsm_state113;
wire   [63:0] tmp_222_fu_5928_p3;
wire   [63:0] tmp_223_fu_5942_p3;
wire    ap_CS_fsm_state114;
wire   [63:0] tmp_224_fu_5956_p3;
wire   [63:0] tmp_225_fu_5970_p3;
wire    ap_CS_fsm_state115;
wire   [63:0] tmp_226_fu_5984_p3;
wire   [63:0] tmp_227_fu_5998_p3;
wire    ap_CS_fsm_state116;
wire   [63:0] tmp_228_fu_6012_p3;
wire   [63:0] tmp_229_fu_6026_p3;
wire    ap_CS_fsm_state117;
wire   [63:0] tmp_230_fu_6040_p3;
wire   [63:0] tmp_231_fu_6054_p3;
wire    ap_CS_fsm_state118;
wire   [63:0] tmp_232_fu_6068_p3;
wire   [63:0] tmp_233_fu_6082_p3;
wire    ap_CS_fsm_state119;
wire   [63:0] tmp_234_fu_6096_p3;
wire   [63:0] tmp_235_fu_6110_p3;
wire    ap_CS_fsm_state120;
wire   [63:0] tmp_236_fu_6124_p3;
wire   [63:0] tmp_237_fu_6138_p3;
wire    ap_CS_fsm_state121;
wire   [63:0] tmp_238_fu_6152_p3;
wire   [63:0] tmp_239_fu_6166_p3;
wire    ap_CS_fsm_state122;
wire   [63:0] tmp_240_fu_6180_p3;
wire   [63:0] tmp_241_fu_6194_p3;
wire    ap_CS_fsm_state123;
wire   [63:0] tmp_242_fu_6208_p3;
wire   [63:0] tmp_243_fu_6222_p3;
wire    ap_CS_fsm_state124;
wire   [63:0] tmp_244_fu_6236_p3;
wire   [63:0] tmp_245_fu_6250_p3;
wire    ap_CS_fsm_state125;
wire   [63:0] tmp_246_fu_6264_p3;
wire   [63:0] tmp_247_fu_6278_p3;
wire    ap_CS_fsm_state126;
wire   [63:0] tmp_248_fu_6292_p3;
wire   [63:0] tmp_249_fu_6306_p3;
wire    ap_CS_fsm_state127;
wire   [63:0] tmp_250_fu_6320_p3;
wire   [63:0] tmp_251_fu_6334_p3;
wire    ap_CS_fsm_state128;
wire   [63:0] tmp_252_fu_6348_p3;
wire   [63:0] tmp_253_fu_6362_p3;
wire   [63:0] tmp_254_fu_6376_p3;
wire   [63:0] zext_ln882_1_fu_6442_p1;
wire   [63:0] zext_ln538_fu_6452_p1;
wire   [63:0] zext_ln882_fu_6487_p1;
wire   [15:0] select_ln480_fu_6518_p3;
wire    ap_CS_fsm_state138;
reg   [15:0] pixel_cntr_V_fu_602;
wire   [15:0] add_ln695_1_fu_6459_p2;
wire   [31:0] zext_ln211_fu_6470_p1;
wire   [31:0] p_Result_s_fu_6494_p5;
reg    ap_block_pp2_stage0_01001;
wire   [16:0] or_ln324_fu_2814_p2;
wire   [16:0] or_ln324_1_fu_2829_p2;
wire   [16:0] or_ln324_2_fu_2843_p2;
wire   [16:0] or_ln324_3_fu_2857_p2;
wire   [16:0] or_ln324_4_fu_2871_p2;
wire   [16:0] or_ln324_5_fu_2885_p2;
wire   [16:0] or_ln324_6_fu_2899_p2;
wire   [16:0] or_ln324_7_fu_2913_p2;
wire   [16:0] or_ln324_8_fu_2927_p2;
wire   [16:0] or_ln324_9_fu_2941_p2;
wire   [16:0] or_ln324_10_fu_2955_p2;
wire   [16:0] or_ln324_11_fu_2969_p2;
wire   [16:0] or_ln324_12_fu_2983_p2;
wire   [16:0] or_ln324_13_fu_2997_p2;
wire   [16:0] or_ln324_14_fu_3011_p2;
wire   [16:0] or_ln324_15_fu_3025_p2;
wire   [16:0] or_ln324_16_fu_3039_p2;
wire   [16:0] or_ln324_17_fu_3053_p2;
wire   [16:0] or_ln324_18_fu_3067_p2;
wire   [16:0] or_ln324_19_fu_3081_p2;
wire   [16:0] or_ln324_20_fu_3095_p2;
wire   [16:0] or_ln324_21_fu_3109_p2;
wire   [16:0] or_ln324_22_fu_3123_p2;
wire   [16:0] or_ln324_23_fu_3137_p2;
wire   [16:0] or_ln324_24_fu_3151_p2;
wire   [16:0] or_ln324_25_fu_3165_p2;
wire   [16:0] or_ln324_26_fu_3179_p2;
wire   [16:0] or_ln324_27_fu_3193_p2;
wire   [16:0] or_ln324_28_fu_3207_p2;
wire   [16:0] or_ln324_29_fu_3221_p2;
wire   [16:0] or_ln324_30_fu_3235_p2;
wire   [16:0] or_ln324_31_fu_3249_p2;
wire   [16:0] or_ln324_32_fu_3263_p2;
wire   [16:0] or_ln324_33_fu_3277_p2;
wire   [16:0] or_ln324_34_fu_3291_p2;
wire   [16:0] or_ln324_35_fu_3305_p2;
wire   [16:0] or_ln324_36_fu_3319_p2;
wire   [16:0] or_ln324_37_fu_3333_p2;
wire   [16:0] or_ln324_38_fu_3347_p2;
wire   [16:0] or_ln324_39_fu_3361_p2;
wire   [16:0] or_ln324_40_fu_3375_p2;
wire   [16:0] or_ln324_41_fu_3389_p2;
wire   [16:0] or_ln324_42_fu_3403_p2;
wire   [16:0] or_ln324_43_fu_3417_p2;
wire   [16:0] or_ln324_44_fu_3431_p2;
wire   [16:0] or_ln324_45_fu_3445_p2;
wire   [16:0] or_ln324_46_fu_3459_p2;
wire   [16:0] or_ln324_47_fu_3473_p2;
wire   [16:0] or_ln324_48_fu_3487_p2;
wire   [16:0] or_ln324_49_fu_3501_p2;
wire   [16:0] or_ln324_50_fu_3515_p2;
wire   [16:0] or_ln324_51_fu_3529_p2;
wire   [16:0] or_ln324_52_fu_3543_p2;
wire   [16:0] or_ln324_53_fu_3557_p2;
wire   [16:0] or_ln324_54_fu_3571_p2;
wire   [16:0] or_ln324_55_fu_3585_p2;
wire   [16:0] or_ln324_56_fu_3599_p2;
wire   [16:0] or_ln324_57_fu_3613_p2;
wire   [16:0] or_ln324_58_fu_3627_p2;
wire   [16:0] or_ln324_59_fu_3641_p2;
wire   [16:0] or_ln324_60_fu_3655_p2;
wire   [16:0] or_ln324_61_fu_3669_p2;
wire   [16:0] or_ln324_62_fu_3683_p2;
wire   [16:0] or_ln324_63_fu_3697_p2;
wire   [16:0] or_ln324_64_fu_3711_p2;
wire   [16:0] or_ln324_65_fu_3725_p2;
wire   [16:0] or_ln324_66_fu_3739_p2;
wire   [16:0] or_ln324_67_fu_3753_p2;
wire   [16:0] or_ln324_68_fu_3767_p2;
wire   [16:0] or_ln324_69_fu_3781_p2;
wire   [16:0] or_ln324_70_fu_3795_p2;
wire   [16:0] or_ln324_71_fu_3809_p2;
wire   [16:0] or_ln324_72_fu_3823_p2;
wire   [16:0] or_ln324_73_fu_3837_p2;
wire   [16:0] or_ln324_74_fu_3851_p2;
wire   [16:0] or_ln324_75_fu_3865_p2;
wire   [16:0] or_ln324_76_fu_3879_p2;
wire   [16:0] or_ln324_77_fu_3893_p2;
wire   [16:0] or_ln324_78_fu_3907_p2;
wire   [16:0] or_ln324_79_fu_3921_p2;
wire   [16:0] or_ln324_80_fu_3935_p2;
wire   [16:0] or_ln324_81_fu_3949_p2;
wire   [16:0] or_ln324_82_fu_3963_p2;
wire   [16:0] or_ln324_83_fu_3977_p2;
wire   [16:0] or_ln324_84_fu_3991_p2;
wire   [16:0] or_ln324_85_fu_4005_p2;
wire   [16:0] or_ln324_86_fu_4019_p2;
wire   [16:0] or_ln324_87_fu_4033_p2;
wire   [16:0] or_ln324_88_fu_4047_p2;
wire   [16:0] or_ln324_89_fu_4061_p2;
wire   [16:0] or_ln324_90_fu_4075_p2;
wire   [16:0] or_ln324_91_fu_4089_p2;
wire   [16:0] or_ln324_92_fu_4103_p2;
wire   [16:0] or_ln324_93_fu_4117_p2;
wire   [16:0] or_ln324_94_fu_4131_p2;
wire   [16:0] or_ln324_95_fu_4145_p2;
wire   [16:0] or_ln324_96_fu_4159_p2;
wire   [16:0] or_ln324_97_fu_4173_p2;
wire   [16:0] or_ln324_98_fu_4187_p2;
wire   [16:0] or_ln324_99_fu_4201_p2;
wire   [16:0] or_ln324_100_fu_4215_p2;
wire   [16:0] or_ln324_101_fu_4229_p2;
wire   [16:0] or_ln324_102_fu_4243_p2;
wire   [16:0] or_ln324_103_fu_4257_p2;
wire   [16:0] or_ln324_104_fu_4271_p2;
wire   [16:0] or_ln324_105_fu_4285_p2;
wire   [16:0] or_ln324_106_fu_4299_p2;
wire   [16:0] or_ln324_107_fu_4313_p2;
wire   [16:0] or_ln324_108_fu_4327_p2;
wire   [16:0] or_ln324_109_fu_4341_p2;
wire   [16:0] or_ln324_110_fu_4355_p2;
wire   [16:0] or_ln324_111_fu_4369_p2;
wire   [16:0] or_ln324_112_fu_4383_p2;
wire   [16:0] or_ln324_113_fu_4397_p2;
wire   [16:0] or_ln324_114_fu_4411_p2;
wire   [16:0] or_ln324_115_fu_4425_p2;
wire   [16:0] or_ln324_116_fu_4439_p2;
wire   [16:0] or_ln324_117_fu_4453_p2;
wire   [16:0] or_ln324_118_fu_4467_p2;
wire   [16:0] or_ln324_119_fu_4481_p2;
wire   [16:0] or_ln324_120_fu_4495_p2;
wire   [16:0] or_ln324_121_fu_4509_p2;
wire   [16:0] or_ln324_122_fu_4523_p2;
wire   [16:0] or_ln324_123_fu_4537_p2;
wire   [16:0] or_ln324_124_fu_4551_p2;
wire   [16:0] or_ln324_125_fu_4565_p2;
wire   [16:0] or_ln324_126_fu_4579_p2;
wire   [16:0] or_ln324_127_fu_4593_p2;
wire   [16:0] or_ln324_128_fu_4607_p2;
wire   [16:0] or_ln324_129_fu_4621_p2;
wire   [16:0] or_ln324_130_fu_4635_p2;
wire   [16:0] or_ln324_131_fu_4649_p2;
wire   [16:0] or_ln324_132_fu_4663_p2;
wire   [16:0] or_ln324_133_fu_4677_p2;
wire   [16:0] or_ln324_134_fu_4691_p2;
wire   [16:0] or_ln324_135_fu_4705_p2;
wire   [16:0] or_ln324_136_fu_4719_p2;
wire   [16:0] or_ln324_137_fu_4733_p2;
wire   [16:0] or_ln324_138_fu_4747_p2;
wire   [16:0] or_ln324_139_fu_4761_p2;
wire   [16:0] or_ln324_140_fu_4775_p2;
wire   [16:0] or_ln324_141_fu_4789_p2;
wire   [16:0] or_ln324_142_fu_4803_p2;
wire   [16:0] or_ln324_143_fu_4817_p2;
wire   [16:0] or_ln324_144_fu_4831_p2;
wire   [16:0] or_ln324_145_fu_4845_p2;
wire   [16:0] or_ln324_146_fu_4859_p2;
wire   [16:0] or_ln324_147_fu_4873_p2;
wire   [16:0] or_ln324_148_fu_4887_p2;
wire   [16:0] or_ln324_149_fu_4901_p2;
wire   [16:0] or_ln324_150_fu_4915_p2;
wire   [16:0] or_ln324_151_fu_4929_p2;
wire   [16:0] or_ln324_152_fu_4943_p2;
wire   [16:0] or_ln324_153_fu_4957_p2;
wire   [16:0] or_ln324_154_fu_4971_p2;
wire   [16:0] or_ln324_155_fu_4985_p2;
wire   [16:0] or_ln324_156_fu_4999_p2;
wire   [16:0] or_ln324_157_fu_5013_p2;
wire   [16:0] or_ln324_158_fu_5027_p2;
wire   [16:0] or_ln324_159_fu_5041_p2;
wire   [16:0] or_ln324_160_fu_5055_p2;
wire   [16:0] or_ln324_161_fu_5069_p2;
wire   [16:0] or_ln324_162_fu_5083_p2;
wire   [16:0] or_ln324_163_fu_5097_p2;
wire   [16:0] or_ln324_164_fu_5111_p2;
wire   [16:0] or_ln324_165_fu_5125_p2;
wire   [16:0] or_ln324_166_fu_5139_p2;
wire   [16:0] or_ln324_167_fu_5153_p2;
wire   [16:0] or_ln324_168_fu_5167_p2;
wire   [16:0] or_ln324_169_fu_5181_p2;
wire   [16:0] or_ln324_170_fu_5195_p2;
wire   [16:0] or_ln324_171_fu_5209_p2;
wire   [16:0] or_ln324_172_fu_5223_p2;
wire   [16:0] or_ln324_173_fu_5237_p2;
wire   [16:0] or_ln324_174_fu_5251_p2;
wire   [16:0] or_ln324_175_fu_5265_p2;
wire   [16:0] or_ln324_176_fu_5279_p2;
wire   [16:0] or_ln324_177_fu_5293_p2;
wire   [16:0] or_ln324_178_fu_5307_p2;
wire   [16:0] or_ln324_179_fu_5321_p2;
wire   [16:0] or_ln324_180_fu_5335_p2;
wire   [16:0] or_ln324_181_fu_5349_p2;
wire   [16:0] or_ln324_182_fu_5363_p2;
wire   [16:0] or_ln324_183_fu_5377_p2;
wire   [16:0] or_ln324_184_fu_5391_p2;
wire   [16:0] or_ln324_185_fu_5405_p2;
wire   [16:0] or_ln324_186_fu_5419_p2;
wire   [16:0] or_ln324_187_fu_5433_p2;
wire   [16:0] or_ln324_188_fu_5447_p2;
wire   [16:0] or_ln324_189_fu_5461_p2;
wire   [16:0] or_ln324_190_fu_5475_p2;
wire   [16:0] or_ln324_191_fu_5489_p2;
wire   [16:0] or_ln324_192_fu_5503_p2;
wire   [16:0] or_ln324_193_fu_5517_p2;
wire   [16:0] or_ln324_194_fu_5531_p2;
wire   [16:0] or_ln324_195_fu_5545_p2;
wire   [16:0] or_ln324_196_fu_5559_p2;
wire   [16:0] or_ln324_197_fu_5573_p2;
wire   [16:0] or_ln324_198_fu_5587_p2;
wire   [16:0] or_ln324_199_fu_5601_p2;
wire   [16:0] or_ln324_200_fu_5615_p2;
wire   [16:0] or_ln324_201_fu_5629_p2;
wire   [16:0] or_ln324_202_fu_5643_p2;
wire   [16:0] or_ln324_203_fu_5657_p2;
wire   [16:0] or_ln324_204_fu_5671_p2;
wire   [16:0] or_ln324_205_fu_5685_p2;
wire   [16:0] or_ln324_206_fu_5699_p2;
wire   [16:0] or_ln324_207_fu_5713_p2;
wire   [16:0] or_ln324_208_fu_5727_p2;
wire   [16:0] or_ln324_209_fu_5741_p2;
wire   [16:0] or_ln324_210_fu_5755_p2;
wire   [16:0] or_ln324_211_fu_5769_p2;
wire   [16:0] or_ln324_212_fu_5783_p2;
wire   [16:0] or_ln324_213_fu_5797_p2;
wire   [16:0] or_ln324_214_fu_5811_p2;
wire   [16:0] or_ln324_215_fu_5825_p2;
wire   [16:0] or_ln324_216_fu_5839_p2;
wire   [16:0] or_ln324_217_fu_5853_p2;
wire   [16:0] or_ln324_218_fu_5867_p2;
wire   [16:0] or_ln324_219_fu_5881_p2;
wire   [16:0] or_ln324_220_fu_5895_p2;
wire   [16:0] or_ln324_221_fu_5909_p2;
wire   [16:0] or_ln324_222_fu_5923_p2;
wire   [16:0] or_ln324_223_fu_5937_p2;
wire   [16:0] or_ln324_224_fu_5951_p2;
wire   [16:0] or_ln324_225_fu_5965_p2;
wire   [16:0] or_ln324_226_fu_5979_p2;
wire   [16:0] or_ln324_227_fu_5993_p2;
wire   [16:0] or_ln324_228_fu_6007_p2;
wire   [16:0] or_ln324_229_fu_6021_p2;
wire   [16:0] or_ln324_230_fu_6035_p2;
wire   [16:0] or_ln324_231_fu_6049_p2;
wire   [16:0] or_ln324_232_fu_6063_p2;
wire   [16:0] or_ln324_233_fu_6077_p2;
wire   [16:0] or_ln324_234_fu_6091_p2;
wire   [16:0] or_ln324_235_fu_6105_p2;
wire   [16:0] or_ln324_236_fu_6119_p2;
wire   [16:0] or_ln324_237_fu_6133_p2;
wire   [16:0] or_ln324_238_fu_6147_p2;
wire   [16:0] or_ln324_239_fu_6161_p2;
wire   [16:0] or_ln324_240_fu_6175_p2;
wire   [16:0] or_ln324_241_fu_6189_p2;
wire   [16:0] or_ln324_242_fu_6203_p2;
wire   [16:0] or_ln324_243_fu_6217_p2;
wire   [16:0] or_ln324_244_fu_6231_p2;
wire   [16:0] or_ln324_245_fu_6245_p2;
wire   [16:0] or_ln324_246_fu_6259_p2;
wire   [16:0] or_ln324_247_fu_6273_p2;
wire   [16:0] or_ln324_248_fu_6287_p2;
wire   [16:0] or_ln324_249_fu_6301_p2;
wire   [16:0] or_ln324_250_fu_6315_p2;
wire   [16:0] or_ln324_251_fu_6329_p2;
wire   [16:0] or_ln324_252_fu_6343_p2;
wire   [16:0] or_ln324_253_fu_6357_p2;
wire   [16:0] or_ln324_254_fu_6371_p2;
wire   [15:0] trunc_ln882_fu_6438_p1;
wire   [15:0] add_ln695_3_fu_6507_p2;
wire   [0:0] icmp_ln874_1_fu_6512_p2;
reg   [134:0] ap_NS_fsm;
reg    ap_idle_pp1;
wire    ap_enable_pp1;
reg    ap_idle_pp2;
wire    ap_enable_pp2;

// power-on initialization
initial begin
#0 ap_CS_fsm = 135'd1;
#0 counter = 16'd0;
#0 ap_enable_reg_pp1_iter0 = 1'b0;
#0 ap_enable_reg_pp2_iter1 = 1'b0;
#0 ap_enable_reg_pp2_iter0 = 1'b0;
#0 ap_enable_reg_pp1_iter1 = 1'b0;
end

rendering_m_zculling_top_z_buffer_V #(
    .DataWidth( 8 ),
    .AddressRange( 65536 ),
    .AddressWidth( 16 ))
z_buffer_V_U(
    .clk(ap_clk),
    .reset(ap_rst),
    .address0(z_buffer_V_address0),
    .ce0(z_buffer_V_ce0),
    .we0(z_buffer_V_we0),
    .d0(z_buffer_V_d0),
    .address1(z_buffer_V_address1),
    .ce1(z_buffer_V_ce1),
    .we1(z_buffer_V_we1),
    .d1(8'd255),
    .q1(z_buffer_V_q1)
);

rendering_m_zculling_top_pixels_x_V #(
    .DataWidth( 8 ),
    .AddressRange( 500 ),
    .AddressWidth( 9 ))
pixels_x_V_U(
    .clk(ap_clk),
    .reset(ap_rst),
    .address0(pixels_x_V_address0),
    .ce0(pixels_x_V_ce0),
    .we0(pixels_x_V_we0),
    .d0(trunc_ln674_reg_6833),
    .q0(pixels_x_V_q0)
);

rendering_m_zculling_top_pixels_x_V #(
    .DataWidth( 8 ),
    .AddressRange( 500 ),
    .AddressWidth( 9 ))
pixels_y_V_U(
    .clk(ap_clk),
    .reset(ap_rst),
    .address0(pixels_y_V_address0),
    .ce0(pixels_y_V_ce0),
    .we0(pixels_y_V_we0),
    .d0(p_Result_1_reg_6838),
    .q0(pixels_y_V_q0)
);

rendering_m_zculling_top_pixels_x_V #(
    .DataWidth( 8 ),
    .AddressRange( 500 ),
    .AddressWidth( 9 ))
pixels_color_V_U(
    .clk(ap_clk),
    .reset(ap_rst),
    .address0(pixels_color_V_address0),
    .ce0(pixels_color_V_ce0),
    .we0(pixels_color_V_we0),
    .d0(p_Result_3_reg_6849),
    .q0(pixels_color_V_q0)
);

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_CS_fsm <= ap_ST_fsm_state1;
    end else begin
        ap_CS_fsm <= ap_NS_fsm;
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp1_iter0 <= 1'b0;
    end else begin
        if (((1'b1 == ap_condition_pp1_exit_iter0_state131) & (1'b1 == ap_CS_fsm_pp1_stage0) & (1'b0 == ap_block_pp1_stage0_subdone))) begin
            ap_enable_reg_pp1_iter0 <= 1'b0;
        end else if ((1'b1 == ap_CS_fsm_state130)) begin
            ap_enable_reg_pp1_iter0 <= 1'b1;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp1_iter1 <= 1'b0;
    end else begin
        if (((1'b1 == ap_CS_fsm_pp1_stage1) & (1'b0 == ap_block_pp1_stage1_subdone))) begin
            ap_enable_reg_pp1_iter1 <= ap_enable_reg_pp1_iter0;
        end else if ((1'b1 == ap_CS_fsm_state130)) begin
            ap_enable_reg_pp1_iter1 <= 1'b0;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp2_iter0 <= 1'b0;
    end else begin
        if (((1'b1 == ap_condition_pp2_exit_iter0_state136) & (1'b1 == ap_CS_fsm_pp2_stage0) & (1'b0 == ap_block_pp2_stage0_subdone))) begin
            ap_enable_reg_pp2_iter0 <= 1'b0;
        end else if (((1'b1 == ap_CS_fsm_state135) & (1'b1 == Output_1_full_n))) begin
            ap_enable_reg_pp2_iter0 <= 1'b1;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp2_iter1 <= 1'b0;
    end else begin
        if (((1'b1 == ap_condition_pp2_exit_iter0_state136) & (1'b0 == ap_block_pp2_stage0_subdone))) begin
            ap_enable_reg_pp2_iter1 <= (1'b1 ^ ap_condition_pp2_exit_iter0_state136);
        end else if ((1'b0 == ap_block_pp2_stage0_subdone)) begin
            ap_enable_reg_pp2_iter1 <= ap_enable_reg_pp2_iter0;
        end else if (((1'b1 == ap_CS_fsm_state135) & (1'b1 == Output_1_full_n))) begin
            ap_enable_reg_pp2_iter1 <= 1'b0;
        end
    end
end

always @ (posedge ap_clk) begin
    if (((ap_enable_reg_pp1_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp1_stage0) & (icmp_ln449_reg_6824 == 1'd0) & (1'b0 == ap_block_pp1_stage0_11001))) begin
        empty_23_reg_2754 <= add_ln695_2_reg_6828;
    end else if ((1'b1 == ap_CS_fsm_state130)) begin
        empty_23_reg_2754 <= 16'd0;
    end
end

always @ (posedge ap_clk) begin
    if ((~((1'b0 == Input_1_empty_n) | (ap_start == 1'b0)) & (icmp_ln874_fu_2783_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state1))) begin
        empty_reg_2743 <= 9'd0;
    end else if ((1'b1 == ap_CS_fsm_state129)) begin
        empty_reg_2743 <= add_ln695_reg_6549;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == ap_CS_fsm_state135) & (1'b1 == Output_1_full_n))) begin
        j_reg_2765 <= 16'd0;
    end else if (((ap_enable_reg_pp2_iter0 == 1'b1) & (icmp_ln882_2_fu_6475_p2 == 1'd0) & (1'b1 == ap_CS_fsm_pp2_stage0) & (1'b0 == ap_block_pp2_stage0_11001))) begin
        j_reg_2765 <= add_ln469_fu_6481_p2;
    end
end

always @ (posedge ap_clk) begin
    if (((ap_enable_reg_pp1_iter1 == 1'b1) & (icmp_ln882_1_reg_6860 == 1'd1) & (1'b1 == ap_CS_fsm_pp1_stage1) & (1'b0 == ap_block_pp1_stage1_11001))) begin
        pixel_cntr_V_fu_602 <= add_ln695_1_fu_6459_p2;
    end else if ((1'b1 == ap_CS_fsm_state130)) begin
        pixel_cntr_V_fu_602 <= 16'd0;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == ap_CS_fsm_pp1_stage0) & (1'b0 == ap_block_pp1_stage0_11001) & (ap_enable_reg_pp1_iter0 == 1'b1))) begin
        add_ln695_2_reg_6828 <= add_ln695_2_fu_6398_p2;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state2)) begin
        add_ln695_reg_6549 <= add_ln695_fu_2795_p2;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state138)) begin
        counter <= select_ln480_fu_6518_p3;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state130)) begin
        empty_22_reg_6819 <= empty_22_fu_6385_p1;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == ap_CS_fsm_pp1_stage0) & (1'b0 == ap_block_pp1_stage0_11001))) begin
        icmp_ln449_reg_6824 <= icmp_ln449_fu_6393_p2;
        icmp_ln882_1_reg_6860 <= icmp_ln882_1_fu_6447_p2;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == ap_CS_fsm_pp2_stage0) & (1'b0 == ap_block_pp2_stage0_11001))) begin
        icmp_ln882_2_reg_6864 <= icmp_ln882_2_fu_6475_p2;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == ap_CS_fsm_pp1_stage1) & (icmp_ln449_reg_6824 == 1'd0) & (1'b0 == ap_block_pp1_stage1_11001))) begin
        p_Result_1_reg_6838 <= {{Input_1_dout[15:8]}};
        p_Result_2_reg_6843 <= {{Input_1_dout[23:16]}};
        p_Result_3_reg_6849 <= {{Input_1_dout[31:24]}};
        trunc_ln674_reg_6833 <= trunc_ln674_fu_6404_p1;
        z_buffer_V_addr_1_reg_6854 <= zext_ln882_1_fu_6442_p1;
    end
end

always @ (posedge ap_clk) begin
    if ((~((1'b0 == Input_1_empty_n) | (ap_start == 1'b0)) & (1'b1 == ap_CS_fsm_state1))) begin
        t_V_reg_6537 <= counter;
        tmp_V_reg_6532 <= Input_1_dout;
    end
end

always @ (posedge ap_clk) begin
    if (((icmp_ln882_fu_2789_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state2))) begin
        tmp_reg_6554[16 : 8] <= tmp_fu_2801_p3[16 : 8];
    end
end

always @ (*) begin
    if ((((1'b1 == ap_CS_fsm_pp1_stage1) & (icmp_ln449_reg_6824 == 1'd0) & (1'b0 == ap_block_pp1_stage1) & (ap_enable_reg_pp1_iter0 == 1'b1)) | ((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b1)))) begin
        Input_1_blk_n = Input_1_empty_n;
    end else begin
        Input_1_blk_n = 1'b1;
    end
end

always @ (*) begin
    if (((~((1'b0 == Input_1_empty_n) | (ap_start == 1'b0)) & (1'b1 == ap_CS_fsm_state1)) | ((1'b1 == ap_CS_fsm_pp1_stage1) & (icmp_ln449_reg_6824 == 1'd0) & (1'b0 == ap_block_pp1_stage1_11001) & (ap_enable_reg_pp1_iter0 == 1'b1)))) begin
        Input_1_read = 1'b1;
    end else begin
        Input_1_read = 1'b0;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state135) | ((icmp_ln882_2_reg_6864 == 1'd0) & (ap_enable_reg_pp2_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp2_stage0) & (1'b0 == ap_block_pp2_stage0)))) begin
        Output_1_blk_n = Output_1_full_n;
    end else begin
        Output_1_blk_n = 1'b1;
    end
end

always @ (*) begin
    if (((icmp_ln882_2_reg_6864 == 1'd0) & (ap_enable_reg_pp2_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp2_stage0) & (1'b0 == ap_block_pp2_stage0_01001))) begin
        Output_1_din = p_Result_s_fu_6494_p5;
    end else if (((1'b1 == ap_CS_fsm_state135) & (1'b1 == Output_1_full_n))) begin
        Output_1_din = zext_ln211_fu_6470_p1;
    end else begin
        Output_1_din = 'bx;
    end
end

always @ (*) begin
    if ((((icmp_ln882_2_reg_6864 == 1'd0) & (ap_enable_reg_pp2_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp2_stage0) & (1'b0 == ap_block_pp2_stage0_11001)) | ((1'b1 == ap_CS_fsm_state135) & (1'b1 == Output_1_full_n)))) begin
        Output_1_write = 1'b1;
    end else begin
        Output_1_write = 1'b0;
    end
end

always @ (*) begin
    if ((icmp_ln449_fu_6393_p2 == 1'd1)) begin
        ap_condition_pp1_exit_iter0_state131 = 1'b1;
    end else begin
        ap_condition_pp1_exit_iter0_state131 = 1'b0;
    end
end

always @ (*) begin
    if ((icmp_ln882_2_fu_6475_p2 == 1'd1)) begin
        ap_condition_pp2_exit_iter0_state136 = 1'b1;
    end else begin
        ap_condition_pp2_exit_iter0_state136 = 1'b0;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state138) | ((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b0)))) begin
        ap_done = 1'b1;
    end else begin
        ap_done = 1'b0;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b0))) begin
        ap_idle = 1'b1;
    end else begin
        ap_idle = 1'b0;
    end
end

always @ (*) begin
    if (((ap_enable_reg_pp1_iter1 == 1'b0) & (ap_enable_reg_pp1_iter0 == 1'b0))) begin
        ap_idle_pp1 = 1'b1;
    end else begin
        ap_idle_pp1 = 1'b0;
    end
end

always @ (*) begin
    if (((ap_enable_reg_pp2_iter0 == 1'b0) & (ap_enable_reg_pp2_iter1 == 1'b0))) begin
        ap_idle_pp2 = 1'b1;
    end else begin
        ap_idle_pp2 = 1'b0;
    end
end

always @ (*) begin
    if (((ap_enable_reg_pp1_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp1_stage0) & (icmp_ln449_reg_6824 == 1'd0) & (1'b0 == ap_block_pp1_stage0))) begin
        ap_phi_mux_empty_23_phi_fu_2758_p4 = add_ln695_2_reg_6828;
    end else begin
        ap_phi_mux_empty_23_phi_fu_2758_p4 = empty_23_reg_2754;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state138)) begin
        ap_ready = 1'b1;
    end else begin
        ap_ready = 1'b0;
    end
end

always @ (*) begin
    if (((ap_enable_reg_pp2_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp2_stage0) & (1'b0 == ap_block_pp2_stage0))) begin
        pixels_color_V_address0 = zext_ln882_fu_6487_p1;
    end else if (((ap_enable_reg_pp1_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp1_stage1) & (1'b0 == ap_block_pp1_stage1))) begin
        pixels_color_V_address0 = zext_ln538_fu_6452_p1;
    end else begin
        pixels_color_V_address0 = 'bx;
    end
end

always @ (*) begin
    if ((((ap_enable_reg_pp1_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp1_stage1) & (1'b0 == ap_block_pp1_stage1_11001)) | ((ap_enable_reg_pp2_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp2_stage0) & (1'b0 == ap_block_pp2_stage0_11001)))) begin
        pixels_color_V_ce0 = 1'b1;
    end else begin
        pixels_color_V_ce0 = 1'b0;
    end
end

always @ (*) begin
    if (((ap_enable_reg_pp1_iter1 == 1'b1) & (icmp_ln882_1_reg_6860 == 1'd1) & (1'b1 == ap_CS_fsm_pp1_stage1) & (1'b0 == ap_block_pp1_stage1_11001))) begin
        pixels_color_V_we0 = 1'b1;
    end else begin
        pixels_color_V_we0 = 1'b0;
    end
end

always @ (*) begin
    if (((ap_enable_reg_pp2_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp2_stage0) & (1'b0 == ap_block_pp2_stage0))) begin
        pixels_x_V_address0 = zext_ln882_fu_6487_p1;
    end else if (((ap_enable_reg_pp1_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp1_stage1) & (1'b0 == ap_block_pp1_stage1))) begin
        pixels_x_V_address0 = zext_ln538_fu_6452_p1;
    end else begin
        pixels_x_V_address0 = 'bx;
    end
end

always @ (*) begin
    if ((((ap_enable_reg_pp1_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp1_stage1) & (1'b0 == ap_block_pp1_stage1_11001)) | ((ap_enable_reg_pp2_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp2_stage0) & (1'b0 == ap_block_pp2_stage0_11001)))) begin
        pixels_x_V_ce0 = 1'b1;
    end else begin
        pixels_x_V_ce0 = 1'b0;
    end
end

always @ (*) begin
    if (((ap_enable_reg_pp1_iter1 == 1'b1) & (icmp_ln882_1_reg_6860 == 1'd1) & (1'b1 == ap_CS_fsm_pp1_stage1) & (1'b0 == ap_block_pp1_stage1_11001))) begin
        pixels_x_V_we0 = 1'b1;
    end else begin
        pixels_x_V_we0 = 1'b0;
    end
end

always @ (*) begin
    if (((ap_enable_reg_pp2_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp2_stage0) & (1'b0 == ap_block_pp2_stage0))) begin
        pixels_y_V_address0 = zext_ln882_fu_6487_p1;
    end else if (((ap_enable_reg_pp1_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp1_stage1) & (1'b0 == ap_block_pp1_stage1))) begin
        pixels_y_V_address0 = zext_ln538_fu_6452_p1;
    end else begin
        pixels_y_V_address0 = 'bx;
    end
end

always @ (*) begin
    if ((((ap_enable_reg_pp1_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp1_stage1) & (1'b0 == ap_block_pp1_stage1_11001)) | ((ap_enable_reg_pp2_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp2_stage0) & (1'b0 == ap_block_pp2_stage0_11001)))) begin
        pixels_y_V_ce0 = 1'b1;
    end else begin
        pixels_y_V_ce0 = 1'b0;
    end
end

always @ (*) begin
    if (((ap_enable_reg_pp1_iter1 == 1'b1) & (icmp_ln882_1_reg_6860 == 1'd1) & (1'b1 == ap_CS_fsm_pp1_stage1) & (1'b0 == ap_block_pp1_stage1_11001))) begin
        pixels_y_V_we0 = 1'b1;
    end else begin
        pixels_y_V_we0 = 1'b0;
    end
end

always @ (*) begin
    if (((ap_enable_reg_pp1_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp1_stage0) & (1'b0 == ap_block_pp1_stage0))) begin
        z_buffer_V_address0 = z_buffer_V_addr_1_reg_6854;
    end else if ((1'b1 == ap_CS_fsm_state129)) begin
        z_buffer_V_address0 = tmp_254_fu_6376_p3;
    end else if ((1'b1 == ap_CS_fsm_state128)) begin
        z_buffer_V_address0 = tmp_252_fu_6348_p3;
    end else if ((1'b1 == ap_CS_fsm_state127)) begin
        z_buffer_V_address0 = tmp_250_fu_6320_p3;
    end else if ((1'b1 == ap_CS_fsm_state126)) begin
        z_buffer_V_address0 = tmp_248_fu_6292_p3;
    end else if ((1'b1 == ap_CS_fsm_state125)) begin
        z_buffer_V_address0 = tmp_246_fu_6264_p3;
    end else if ((1'b1 == ap_CS_fsm_state124)) begin
        z_buffer_V_address0 = tmp_244_fu_6236_p3;
    end else if ((1'b1 == ap_CS_fsm_state123)) begin
        z_buffer_V_address0 = tmp_242_fu_6208_p3;
    end else if ((1'b1 == ap_CS_fsm_state122)) begin
        z_buffer_V_address0 = tmp_240_fu_6180_p3;
    end else if ((1'b1 == ap_CS_fsm_state121)) begin
        z_buffer_V_address0 = tmp_238_fu_6152_p3;
    end else if ((1'b1 == ap_CS_fsm_state120)) begin
        z_buffer_V_address0 = tmp_236_fu_6124_p3;
    end else if ((1'b1 == ap_CS_fsm_state119)) begin
        z_buffer_V_address0 = tmp_234_fu_6096_p3;
    end else if ((1'b1 == ap_CS_fsm_state118)) begin
        z_buffer_V_address0 = tmp_232_fu_6068_p3;
    end else if ((1'b1 == ap_CS_fsm_state117)) begin
        z_buffer_V_address0 = tmp_230_fu_6040_p3;
    end else if ((1'b1 == ap_CS_fsm_state116)) begin
        z_buffer_V_address0 = tmp_228_fu_6012_p3;
    end else if ((1'b1 == ap_CS_fsm_state115)) begin
        z_buffer_V_address0 = tmp_226_fu_5984_p3;
    end else if ((1'b1 == ap_CS_fsm_state114)) begin
        z_buffer_V_address0 = tmp_224_fu_5956_p3;
    end else if ((1'b1 == ap_CS_fsm_state113)) begin
        z_buffer_V_address0 = tmp_222_fu_5928_p3;
    end else if ((1'b1 == ap_CS_fsm_state112)) begin
        z_buffer_V_address0 = tmp_220_fu_5900_p3;
    end else if ((1'b1 == ap_CS_fsm_state111)) begin
        z_buffer_V_address0 = tmp_218_fu_5872_p3;
    end else if ((1'b1 == ap_CS_fsm_state110)) begin
        z_buffer_V_address0 = tmp_216_fu_5844_p3;
    end else if ((1'b1 == ap_CS_fsm_state109)) begin
        z_buffer_V_address0 = tmp_214_fu_5816_p3;
    end else if ((1'b1 == ap_CS_fsm_state108)) begin
        z_buffer_V_address0 = tmp_212_fu_5788_p3;
    end else if ((1'b1 == ap_CS_fsm_state107)) begin
        z_buffer_V_address0 = tmp_210_fu_5760_p3;
    end else if ((1'b1 == ap_CS_fsm_state106)) begin
        z_buffer_V_address0 = tmp_208_fu_5732_p3;
    end else if ((1'b1 == ap_CS_fsm_state105)) begin
        z_buffer_V_address0 = tmp_206_fu_5704_p3;
    end else if ((1'b1 == ap_CS_fsm_state104)) begin
        z_buffer_V_address0 = tmp_204_fu_5676_p3;
    end else if ((1'b1 == ap_CS_fsm_state103)) begin
        z_buffer_V_address0 = tmp_202_fu_5648_p3;
    end else if ((1'b1 == ap_CS_fsm_state102)) begin
        z_buffer_V_address0 = tmp_200_fu_5620_p3;
    end else if ((1'b1 == ap_CS_fsm_state101)) begin
        z_buffer_V_address0 = tmp_198_fu_5592_p3;
    end else if ((1'b1 == ap_CS_fsm_state100)) begin
        z_buffer_V_address0 = tmp_196_fu_5564_p3;
    end else if ((1'b1 == ap_CS_fsm_state99)) begin
        z_buffer_V_address0 = tmp_194_fu_5536_p3;
    end else if ((1'b1 == ap_CS_fsm_state98)) begin
        z_buffer_V_address0 = tmp_192_fu_5508_p3;
    end else if ((1'b1 == ap_CS_fsm_state97)) begin
        z_buffer_V_address0 = tmp_190_fu_5480_p3;
    end else if ((1'b1 == ap_CS_fsm_state96)) begin
        z_buffer_V_address0 = tmp_188_fu_5452_p3;
    end else if ((1'b1 == ap_CS_fsm_state95)) begin
        z_buffer_V_address0 = tmp_186_fu_5424_p3;
    end else if ((1'b1 == ap_CS_fsm_state94)) begin
        z_buffer_V_address0 = tmp_184_fu_5396_p3;
    end else if ((1'b1 == ap_CS_fsm_state93)) begin
        z_buffer_V_address0 = tmp_182_fu_5368_p3;
    end else if ((1'b1 == ap_CS_fsm_state92)) begin
        z_buffer_V_address0 = tmp_180_fu_5340_p3;
    end else if ((1'b1 == ap_CS_fsm_state91)) begin
        z_buffer_V_address0 = tmp_178_fu_5312_p3;
    end else if ((1'b1 == ap_CS_fsm_state90)) begin
        z_buffer_V_address0 = tmp_176_fu_5284_p3;
    end else if ((1'b1 == ap_CS_fsm_state89)) begin
        z_buffer_V_address0 = tmp_174_fu_5256_p3;
    end else if ((1'b1 == ap_CS_fsm_state88)) begin
        z_buffer_V_address0 = tmp_172_fu_5228_p3;
    end else if ((1'b1 == ap_CS_fsm_state87)) begin
        z_buffer_V_address0 = tmp_170_fu_5200_p3;
    end else if ((1'b1 == ap_CS_fsm_state86)) begin
        z_buffer_V_address0 = tmp_168_fu_5172_p3;
    end else if ((1'b1 == ap_CS_fsm_state85)) begin
        z_buffer_V_address0 = tmp_166_fu_5144_p3;
    end else if ((1'b1 == ap_CS_fsm_state84)) begin
        z_buffer_V_address0 = tmp_164_fu_5116_p3;
    end else if ((1'b1 == ap_CS_fsm_state83)) begin
        z_buffer_V_address0 = tmp_162_fu_5088_p3;
    end else if ((1'b1 == ap_CS_fsm_state82)) begin
        z_buffer_V_address0 = tmp_160_fu_5060_p3;
    end else if ((1'b1 == ap_CS_fsm_state81)) begin
        z_buffer_V_address0 = tmp_158_fu_5032_p3;
    end else if ((1'b1 == ap_CS_fsm_state80)) begin
        z_buffer_V_address0 = tmp_156_fu_5004_p3;
    end else if ((1'b1 == ap_CS_fsm_state79)) begin
        z_buffer_V_address0 = tmp_154_fu_4976_p3;
    end else if ((1'b1 == ap_CS_fsm_state78)) begin
        z_buffer_V_address0 = tmp_152_fu_4948_p3;
    end else if ((1'b1 == ap_CS_fsm_state77)) begin
        z_buffer_V_address0 = tmp_150_fu_4920_p3;
    end else if ((1'b1 == ap_CS_fsm_state76)) begin
        z_buffer_V_address0 = tmp_148_fu_4892_p3;
    end else if ((1'b1 == ap_CS_fsm_state75)) begin
        z_buffer_V_address0 = tmp_146_fu_4864_p3;
    end else if ((1'b1 == ap_CS_fsm_state74)) begin
        z_buffer_V_address0 = tmp_144_fu_4836_p3;
    end else if ((1'b1 == ap_CS_fsm_state73)) begin
        z_buffer_V_address0 = tmp_142_fu_4808_p3;
    end else if ((1'b1 == ap_CS_fsm_state72)) begin
        z_buffer_V_address0 = tmp_140_fu_4780_p3;
    end else if ((1'b1 == ap_CS_fsm_state71)) begin
        z_buffer_V_address0 = tmp_138_fu_4752_p3;
    end else if ((1'b1 == ap_CS_fsm_state70)) begin
        z_buffer_V_address0 = tmp_136_fu_4724_p3;
    end else if ((1'b1 == ap_CS_fsm_state69)) begin
        z_buffer_V_address0 = tmp_134_fu_4696_p3;
    end else if ((1'b1 == ap_CS_fsm_state68)) begin
        z_buffer_V_address0 = tmp_132_fu_4668_p3;
    end else if ((1'b1 == ap_CS_fsm_state67)) begin
        z_buffer_V_address0 = tmp_130_fu_4640_p3;
    end else if ((1'b1 == ap_CS_fsm_state66)) begin
        z_buffer_V_address0 = tmp_128_fu_4612_p3;
    end else if ((1'b1 == ap_CS_fsm_state65)) begin
        z_buffer_V_address0 = tmp_126_fu_4584_p3;
    end else if ((1'b1 == ap_CS_fsm_state64)) begin
        z_buffer_V_address0 = tmp_124_fu_4556_p3;
    end else if ((1'b1 == ap_CS_fsm_state63)) begin
        z_buffer_V_address0 = tmp_122_fu_4528_p3;
    end else if ((1'b1 == ap_CS_fsm_state62)) begin
        z_buffer_V_address0 = tmp_120_fu_4500_p3;
    end else if ((1'b1 == ap_CS_fsm_state61)) begin
        z_buffer_V_address0 = tmp_118_fu_4472_p3;
    end else if ((1'b1 == ap_CS_fsm_state60)) begin
        z_buffer_V_address0 = tmp_116_fu_4444_p3;
    end else if ((1'b1 == ap_CS_fsm_state59)) begin
        z_buffer_V_address0 = tmp_114_fu_4416_p3;
    end else if ((1'b1 == ap_CS_fsm_state58)) begin
        z_buffer_V_address0 = tmp_112_fu_4388_p3;
    end else if ((1'b1 == ap_CS_fsm_state57)) begin
        z_buffer_V_address0 = tmp_110_fu_4360_p3;
    end else if ((1'b1 == ap_CS_fsm_state56)) begin
        z_buffer_V_address0 = tmp_108_fu_4332_p3;
    end else if ((1'b1 == ap_CS_fsm_state55)) begin
        z_buffer_V_address0 = tmp_106_fu_4304_p3;
    end else if ((1'b1 == ap_CS_fsm_state54)) begin
        z_buffer_V_address0 = tmp_104_fu_4276_p3;
    end else if ((1'b1 == ap_CS_fsm_state53)) begin
        z_buffer_V_address0 = tmp_102_fu_4248_p3;
    end else if ((1'b1 == ap_CS_fsm_state52)) begin
        z_buffer_V_address0 = tmp_100_fu_4220_p3;
    end else if ((1'b1 == ap_CS_fsm_state51)) begin
        z_buffer_V_address0 = tmp_98_fu_4192_p3;
    end else if ((1'b1 == ap_CS_fsm_state50)) begin
        z_buffer_V_address0 = tmp_96_fu_4164_p3;
    end else if ((1'b1 == ap_CS_fsm_state49)) begin
        z_buffer_V_address0 = tmp_94_fu_4136_p3;
    end else if ((1'b1 == ap_CS_fsm_state48)) begin
        z_buffer_V_address0 = tmp_92_fu_4108_p3;
    end else if ((1'b1 == ap_CS_fsm_state47)) begin
        z_buffer_V_address0 = tmp_90_fu_4080_p3;
    end else if ((1'b1 == ap_CS_fsm_state46)) begin
        z_buffer_V_address0 = tmp_88_fu_4052_p3;
    end else if ((1'b1 == ap_CS_fsm_state45)) begin
        z_buffer_V_address0 = tmp_86_fu_4024_p3;
    end else if ((1'b1 == ap_CS_fsm_state44)) begin
        z_buffer_V_address0 = tmp_84_fu_3996_p3;
    end else if ((1'b1 == ap_CS_fsm_state43)) begin
        z_buffer_V_address0 = tmp_82_fu_3968_p3;
    end else if ((1'b1 == ap_CS_fsm_state42)) begin
        z_buffer_V_address0 = tmp_80_fu_3940_p3;
    end else if ((1'b1 == ap_CS_fsm_state41)) begin
        z_buffer_V_address0 = tmp_78_fu_3912_p3;
    end else if ((1'b1 == ap_CS_fsm_state40)) begin
        z_buffer_V_address0 = tmp_76_fu_3884_p3;
    end else if ((1'b1 == ap_CS_fsm_state39)) begin
        z_buffer_V_address0 = tmp_74_fu_3856_p3;
    end else if ((1'b1 == ap_CS_fsm_state38)) begin
        z_buffer_V_address0 = tmp_72_fu_3828_p3;
    end else if ((1'b1 == ap_CS_fsm_state37)) begin
        z_buffer_V_address0 = tmp_70_fu_3800_p3;
    end else if ((1'b1 == ap_CS_fsm_state36)) begin
        z_buffer_V_address0 = tmp_68_fu_3772_p3;
    end else if ((1'b1 == ap_CS_fsm_state35)) begin
        z_buffer_V_address0 = tmp_66_fu_3744_p3;
    end else if ((1'b1 == ap_CS_fsm_state34)) begin
        z_buffer_V_address0 = tmp_64_fu_3716_p3;
    end else if ((1'b1 == ap_CS_fsm_state33)) begin
        z_buffer_V_address0 = tmp_62_fu_3688_p3;
    end else if ((1'b1 == ap_CS_fsm_state32)) begin
        z_buffer_V_address0 = tmp_60_fu_3660_p3;
    end else if ((1'b1 == ap_CS_fsm_state31)) begin
        z_buffer_V_address0 = tmp_58_fu_3632_p3;
    end else if ((1'b1 == ap_CS_fsm_state30)) begin
        z_buffer_V_address0 = tmp_56_fu_3604_p3;
    end else if ((1'b1 == ap_CS_fsm_state29)) begin
        z_buffer_V_address0 = tmp_54_fu_3576_p3;
    end else if ((1'b1 == ap_CS_fsm_state28)) begin
        z_buffer_V_address0 = tmp_52_fu_3548_p3;
    end else if ((1'b1 == ap_CS_fsm_state27)) begin
        z_buffer_V_address0 = tmp_50_fu_3520_p3;
    end else if ((1'b1 == ap_CS_fsm_state26)) begin
        z_buffer_V_address0 = tmp_48_fu_3492_p3;
    end else if ((1'b1 == ap_CS_fsm_state25)) begin
        z_buffer_V_address0 = tmp_46_fu_3464_p3;
    end else if ((1'b1 == ap_CS_fsm_state24)) begin
        z_buffer_V_address0 = tmp_44_fu_3436_p3;
    end else if ((1'b1 == ap_CS_fsm_state23)) begin
        z_buffer_V_address0 = tmp_42_fu_3408_p3;
    end else if ((1'b1 == ap_CS_fsm_state22)) begin
        z_buffer_V_address0 = tmp_40_fu_3380_p3;
    end else if ((1'b1 == ap_CS_fsm_state21)) begin
        z_buffer_V_address0 = tmp_38_fu_3352_p3;
    end else if ((1'b1 == ap_CS_fsm_state20)) begin
        z_buffer_V_address0 = tmp_36_fu_3324_p3;
    end else if ((1'b1 == ap_CS_fsm_state19)) begin
        z_buffer_V_address0 = tmp_34_fu_3296_p3;
    end else if ((1'b1 == ap_CS_fsm_state18)) begin
        z_buffer_V_address0 = tmp_32_fu_3268_p3;
    end else if ((1'b1 == ap_CS_fsm_state17)) begin
        z_buffer_V_address0 = tmp_30_fu_3240_p3;
    end else if ((1'b1 == ap_CS_fsm_state16)) begin
        z_buffer_V_address0 = tmp_28_fu_3212_p3;
    end else if ((1'b1 == ap_CS_fsm_state15)) begin
        z_buffer_V_address0 = tmp_26_fu_3184_p3;
    end else if ((1'b1 == ap_CS_fsm_state14)) begin
        z_buffer_V_address0 = tmp_24_fu_3156_p3;
    end else if ((1'b1 == ap_CS_fsm_state13)) begin
        z_buffer_V_address0 = tmp_22_fu_3128_p3;
    end else if ((1'b1 == ap_CS_fsm_state12)) begin
        z_buffer_V_address0 = tmp_20_fu_3100_p3;
    end else if ((1'b1 == ap_CS_fsm_state11)) begin
        z_buffer_V_address0 = tmp_18_fu_3072_p3;
    end else if ((1'b1 == ap_CS_fsm_state10)) begin
        z_buffer_V_address0 = tmp_16_fu_3044_p3;
    end else if ((1'b1 == ap_CS_fsm_state9)) begin
        z_buffer_V_address0 = tmp_14_fu_3016_p3;
    end else if ((1'b1 == ap_CS_fsm_state8)) begin
        z_buffer_V_address0 = tmp_12_fu_2988_p3;
    end else if ((1'b1 == ap_CS_fsm_state7)) begin
        z_buffer_V_address0 = tmp_10_fu_2960_p3;
    end else if ((1'b1 == ap_CS_fsm_state6)) begin
        z_buffer_V_address0 = tmp_9_fu_2932_p3;
    end else if ((1'b1 == ap_CS_fsm_state5)) begin
        z_buffer_V_address0 = tmp_7_fu_2904_p3;
    end else if ((1'b1 == ap_CS_fsm_state4)) begin
        z_buffer_V_address0 = tmp_5_fu_2876_p3;
    end else if ((1'b1 == ap_CS_fsm_state3)) begin
        z_buffer_V_address0 = tmp_3_fu_2848_p3;
    end else if ((1'b1 == ap_CS_fsm_state2)) begin
        z_buffer_V_address0 = tmp_1_fu_2820_p3;
    end else begin
        z_buffer_V_address0 = 'bx;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_pp1_stage1) & (1'b0 == ap_block_pp1_stage1) & (ap_enable_reg_pp1_iter0 == 1'b1))) begin
        z_buffer_V_address1 = zext_ln882_1_fu_6442_p1;
    end else if ((1'b1 == ap_CS_fsm_state129)) begin
        z_buffer_V_address1 = tmp_253_fu_6362_p3;
    end else if ((1'b1 == ap_CS_fsm_state128)) begin
        z_buffer_V_address1 = tmp_251_fu_6334_p3;
    end else if ((1'b1 == ap_CS_fsm_state127)) begin
        z_buffer_V_address1 = tmp_249_fu_6306_p3;
    end else if ((1'b1 == ap_CS_fsm_state126)) begin
        z_buffer_V_address1 = tmp_247_fu_6278_p3;
    end else if ((1'b1 == ap_CS_fsm_state125)) begin
        z_buffer_V_address1 = tmp_245_fu_6250_p3;
    end else if ((1'b1 == ap_CS_fsm_state124)) begin
        z_buffer_V_address1 = tmp_243_fu_6222_p3;
    end else if ((1'b1 == ap_CS_fsm_state123)) begin
        z_buffer_V_address1 = tmp_241_fu_6194_p3;
    end else if ((1'b1 == ap_CS_fsm_state122)) begin
        z_buffer_V_address1 = tmp_239_fu_6166_p3;
    end else if ((1'b1 == ap_CS_fsm_state121)) begin
        z_buffer_V_address1 = tmp_237_fu_6138_p3;
    end else if ((1'b1 == ap_CS_fsm_state120)) begin
        z_buffer_V_address1 = tmp_235_fu_6110_p3;
    end else if ((1'b1 == ap_CS_fsm_state119)) begin
        z_buffer_V_address1 = tmp_233_fu_6082_p3;
    end else if ((1'b1 == ap_CS_fsm_state118)) begin
        z_buffer_V_address1 = tmp_231_fu_6054_p3;
    end else if ((1'b1 == ap_CS_fsm_state117)) begin
        z_buffer_V_address1 = tmp_229_fu_6026_p3;
    end else if ((1'b1 == ap_CS_fsm_state116)) begin
        z_buffer_V_address1 = tmp_227_fu_5998_p3;
    end else if ((1'b1 == ap_CS_fsm_state115)) begin
        z_buffer_V_address1 = tmp_225_fu_5970_p3;
    end else if ((1'b1 == ap_CS_fsm_state114)) begin
        z_buffer_V_address1 = tmp_223_fu_5942_p3;
    end else if ((1'b1 == ap_CS_fsm_state113)) begin
        z_buffer_V_address1 = tmp_221_fu_5914_p3;
    end else if ((1'b1 == ap_CS_fsm_state112)) begin
        z_buffer_V_address1 = tmp_219_fu_5886_p3;
    end else if ((1'b1 == ap_CS_fsm_state111)) begin
        z_buffer_V_address1 = tmp_217_fu_5858_p3;
    end else if ((1'b1 == ap_CS_fsm_state110)) begin
        z_buffer_V_address1 = tmp_215_fu_5830_p3;
    end else if ((1'b1 == ap_CS_fsm_state109)) begin
        z_buffer_V_address1 = tmp_213_fu_5802_p3;
    end else if ((1'b1 == ap_CS_fsm_state108)) begin
        z_buffer_V_address1 = tmp_211_fu_5774_p3;
    end else if ((1'b1 == ap_CS_fsm_state107)) begin
        z_buffer_V_address1 = tmp_209_fu_5746_p3;
    end else if ((1'b1 == ap_CS_fsm_state106)) begin
        z_buffer_V_address1 = tmp_207_fu_5718_p3;
    end else if ((1'b1 == ap_CS_fsm_state105)) begin
        z_buffer_V_address1 = tmp_205_fu_5690_p3;
    end else if ((1'b1 == ap_CS_fsm_state104)) begin
        z_buffer_V_address1 = tmp_203_fu_5662_p3;
    end else if ((1'b1 == ap_CS_fsm_state103)) begin
        z_buffer_V_address1 = tmp_201_fu_5634_p3;
    end else if ((1'b1 == ap_CS_fsm_state102)) begin
        z_buffer_V_address1 = tmp_199_fu_5606_p3;
    end else if ((1'b1 == ap_CS_fsm_state101)) begin
        z_buffer_V_address1 = tmp_197_fu_5578_p3;
    end else if ((1'b1 == ap_CS_fsm_state100)) begin
        z_buffer_V_address1 = tmp_195_fu_5550_p3;
    end else if ((1'b1 == ap_CS_fsm_state99)) begin
        z_buffer_V_address1 = tmp_193_fu_5522_p3;
    end else if ((1'b1 == ap_CS_fsm_state98)) begin
        z_buffer_V_address1 = tmp_191_fu_5494_p3;
    end else if ((1'b1 == ap_CS_fsm_state97)) begin
        z_buffer_V_address1 = tmp_189_fu_5466_p3;
    end else if ((1'b1 == ap_CS_fsm_state96)) begin
        z_buffer_V_address1 = tmp_187_fu_5438_p3;
    end else if ((1'b1 == ap_CS_fsm_state95)) begin
        z_buffer_V_address1 = tmp_185_fu_5410_p3;
    end else if ((1'b1 == ap_CS_fsm_state94)) begin
        z_buffer_V_address1 = tmp_183_fu_5382_p3;
    end else if ((1'b1 == ap_CS_fsm_state93)) begin
        z_buffer_V_address1 = tmp_181_fu_5354_p3;
    end else if ((1'b1 == ap_CS_fsm_state92)) begin
        z_buffer_V_address1 = tmp_179_fu_5326_p3;
    end else if ((1'b1 == ap_CS_fsm_state91)) begin
        z_buffer_V_address1 = tmp_177_fu_5298_p3;
    end else if ((1'b1 == ap_CS_fsm_state90)) begin
        z_buffer_V_address1 = tmp_175_fu_5270_p3;
    end else if ((1'b1 == ap_CS_fsm_state89)) begin
        z_buffer_V_address1 = tmp_173_fu_5242_p3;
    end else if ((1'b1 == ap_CS_fsm_state88)) begin
        z_buffer_V_address1 = tmp_171_fu_5214_p3;
    end else if ((1'b1 == ap_CS_fsm_state87)) begin
        z_buffer_V_address1 = tmp_169_fu_5186_p3;
    end else if ((1'b1 == ap_CS_fsm_state86)) begin
        z_buffer_V_address1 = tmp_167_fu_5158_p3;
    end else if ((1'b1 == ap_CS_fsm_state85)) begin
        z_buffer_V_address1 = tmp_165_fu_5130_p3;
    end else if ((1'b1 == ap_CS_fsm_state84)) begin
        z_buffer_V_address1 = tmp_163_fu_5102_p3;
    end else if ((1'b1 == ap_CS_fsm_state83)) begin
        z_buffer_V_address1 = tmp_161_fu_5074_p3;
    end else if ((1'b1 == ap_CS_fsm_state82)) begin
        z_buffer_V_address1 = tmp_159_fu_5046_p3;
    end else if ((1'b1 == ap_CS_fsm_state81)) begin
        z_buffer_V_address1 = tmp_157_fu_5018_p3;
    end else if ((1'b1 == ap_CS_fsm_state80)) begin
        z_buffer_V_address1 = tmp_155_fu_4990_p3;
    end else if ((1'b1 == ap_CS_fsm_state79)) begin
        z_buffer_V_address1 = tmp_153_fu_4962_p3;
    end else if ((1'b1 == ap_CS_fsm_state78)) begin
        z_buffer_V_address1 = tmp_151_fu_4934_p3;
    end else if ((1'b1 == ap_CS_fsm_state77)) begin
        z_buffer_V_address1 = tmp_149_fu_4906_p3;
    end else if ((1'b1 == ap_CS_fsm_state76)) begin
        z_buffer_V_address1 = tmp_147_fu_4878_p3;
    end else if ((1'b1 == ap_CS_fsm_state75)) begin
        z_buffer_V_address1 = tmp_145_fu_4850_p3;
    end else if ((1'b1 == ap_CS_fsm_state74)) begin
        z_buffer_V_address1 = tmp_143_fu_4822_p3;
    end else if ((1'b1 == ap_CS_fsm_state73)) begin
        z_buffer_V_address1 = tmp_141_fu_4794_p3;
    end else if ((1'b1 == ap_CS_fsm_state72)) begin
        z_buffer_V_address1 = tmp_139_fu_4766_p3;
    end else if ((1'b1 == ap_CS_fsm_state71)) begin
        z_buffer_V_address1 = tmp_137_fu_4738_p3;
    end else if ((1'b1 == ap_CS_fsm_state70)) begin
        z_buffer_V_address1 = tmp_135_fu_4710_p3;
    end else if ((1'b1 == ap_CS_fsm_state69)) begin
        z_buffer_V_address1 = tmp_133_fu_4682_p3;
    end else if ((1'b1 == ap_CS_fsm_state68)) begin
        z_buffer_V_address1 = tmp_131_fu_4654_p3;
    end else if ((1'b1 == ap_CS_fsm_state67)) begin
        z_buffer_V_address1 = tmp_129_fu_4626_p3;
    end else if ((1'b1 == ap_CS_fsm_state66)) begin
        z_buffer_V_address1 = tmp_127_fu_4598_p3;
    end else if ((1'b1 == ap_CS_fsm_state65)) begin
        z_buffer_V_address1 = tmp_125_fu_4570_p3;
    end else if ((1'b1 == ap_CS_fsm_state64)) begin
        z_buffer_V_address1 = tmp_123_fu_4542_p3;
    end else if ((1'b1 == ap_CS_fsm_state63)) begin
        z_buffer_V_address1 = tmp_121_fu_4514_p3;
    end else if ((1'b1 == ap_CS_fsm_state62)) begin
        z_buffer_V_address1 = tmp_119_fu_4486_p3;
    end else if ((1'b1 == ap_CS_fsm_state61)) begin
        z_buffer_V_address1 = tmp_117_fu_4458_p3;
    end else if ((1'b1 == ap_CS_fsm_state60)) begin
        z_buffer_V_address1 = tmp_115_fu_4430_p3;
    end else if ((1'b1 == ap_CS_fsm_state59)) begin
        z_buffer_V_address1 = tmp_113_fu_4402_p3;
    end else if ((1'b1 == ap_CS_fsm_state58)) begin
        z_buffer_V_address1 = tmp_111_fu_4374_p3;
    end else if ((1'b1 == ap_CS_fsm_state57)) begin
        z_buffer_V_address1 = tmp_109_fu_4346_p3;
    end else if ((1'b1 == ap_CS_fsm_state56)) begin
        z_buffer_V_address1 = tmp_107_fu_4318_p3;
    end else if ((1'b1 == ap_CS_fsm_state55)) begin
        z_buffer_V_address1 = tmp_105_fu_4290_p3;
    end else if ((1'b1 == ap_CS_fsm_state54)) begin
        z_buffer_V_address1 = tmp_103_fu_4262_p3;
    end else if ((1'b1 == ap_CS_fsm_state53)) begin
        z_buffer_V_address1 = tmp_101_fu_4234_p3;
    end else if ((1'b1 == ap_CS_fsm_state52)) begin
        z_buffer_V_address1 = tmp_99_fu_4206_p3;
    end else if ((1'b1 == ap_CS_fsm_state51)) begin
        z_buffer_V_address1 = tmp_97_fu_4178_p3;
    end else if ((1'b1 == ap_CS_fsm_state50)) begin
        z_buffer_V_address1 = tmp_95_fu_4150_p3;
    end else if ((1'b1 == ap_CS_fsm_state49)) begin
        z_buffer_V_address1 = tmp_93_fu_4122_p3;
    end else if ((1'b1 == ap_CS_fsm_state48)) begin
        z_buffer_V_address1 = tmp_91_fu_4094_p3;
    end else if ((1'b1 == ap_CS_fsm_state47)) begin
        z_buffer_V_address1 = tmp_89_fu_4066_p3;
    end else if ((1'b1 == ap_CS_fsm_state46)) begin
        z_buffer_V_address1 = tmp_87_fu_4038_p3;
    end else if ((1'b1 == ap_CS_fsm_state45)) begin
        z_buffer_V_address1 = tmp_85_fu_4010_p3;
    end else if ((1'b1 == ap_CS_fsm_state44)) begin
        z_buffer_V_address1 = tmp_83_fu_3982_p3;
    end else if ((1'b1 == ap_CS_fsm_state43)) begin
        z_buffer_V_address1 = tmp_81_fu_3954_p3;
    end else if ((1'b1 == ap_CS_fsm_state42)) begin
        z_buffer_V_address1 = tmp_79_fu_3926_p3;
    end else if ((1'b1 == ap_CS_fsm_state41)) begin
        z_buffer_V_address1 = tmp_77_fu_3898_p3;
    end else if ((1'b1 == ap_CS_fsm_state40)) begin
        z_buffer_V_address1 = tmp_75_fu_3870_p3;
    end else if ((1'b1 == ap_CS_fsm_state39)) begin
        z_buffer_V_address1 = tmp_73_fu_3842_p3;
    end else if ((1'b1 == ap_CS_fsm_state38)) begin
        z_buffer_V_address1 = tmp_71_fu_3814_p3;
    end else if ((1'b1 == ap_CS_fsm_state37)) begin
        z_buffer_V_address1 = tmp_69_fu_3786_p3;
    end else if ((1'b1 == ap_CS_fsm_state36)) begin
        z_buffer_V_address1 = tmp_67_fu_3758_p3;
    end else if ((1'b1 == ap_CS_fsm_state35)) begin
        z_buffer_V_address1 = tmp_65_fu_3730_p3;
    end else if ((1'b1 == ap_CS_fsm_state34)) begin
        z_buffer_V_address1 = tmp_63_fu_3702_p3;
    end else if ((1'b1 == ap_CS_fsm_state33)) begin
        z_buffer_V_address1 = tmp_61_fu_3674_p3;
    end else if ((1'b1 == ap_CS_fsm_state32)) begin
        z_buffer_V_address1 = tmp_59_fu_3646_p3;
    end else if ((1'b1 == ap_CS_fsm_state31)) begin
        z_buffer_V_address1 = tmp_57_fu_3618_p3;
    end else if ((1'b1 == ap_CS_fsm_state30)) begin
        z_buffer_V_address1 = tmp_55_fu_3590_p3;
    end else if ((1'b1 == ap_CS_fsm_state29)) begin
        z_buffer_V_address1 = tmp_53_fu_3562_p3;
    end else if ((1'b1 == ap_CS_fsm_state28)) begin
        z_buffer_V_address1 = tmp_51_fu_3534_p3;
    end else if ((1'b1 == ap_CS_fsm_state27)) begin
        z_buffer_V_address1 = tmp_49_fu_3506_p3;
    end else if ((1'b1 == ap_CS_fsm_state26)) begin
        z_buffer_V_address1 = tmp_47_fu_3478_p3;
    end else if ((1'b1 == ap_CS_fsm_state25)) begin
        z_buffer_V_address1 = tmp_45_fu_3450_p3;
    end else if ((1'b1 == ap_CS_fsm_state24)) begin
        z_buffer_V_address1 = tmp_43_fu_3422_p3;
    end else if ((1'b1 == ap_CS_fsm_state23)) begin
        z_buffer_V_address1 = tmp_41_fu_3394_p3;
    end else if ((1'b1 == ap_CS_fsm_state22)) begin
        z_buffer_V_address1 = tmp_39_fu_3366_p3;
    end else if ((1'b1 == ap_CS_fsm_state21)) begin
        z_buffer_V_address1 = tmp_37_fu_3338_p3;
    end else if ((1'b1 == ap_CS_fsm_state20)) begin
        z_buffer_V_address1 = tmp_35_fu_3310_p3;
    end else if ((1'b1 == ap_CS_fsm_state19)) begin
        z_buffer_V_address1 = tmp_33_fu_3282_p3;
    end else if ((1'b1 == ap_CS_fsm_state18)) begin
        z_buffer_V_address1 = tmp_31_fu_3254_p3;
    end else if ((1'b1 == ap_CS_fsm_state17)) begin
        z_buffer_V_address1 = tmp_29_fu_3226_p3;
    end else if ((1'b1 == ap_CS_fsm_state16)) begin
        z_buffer_V_address1 = tmp_27_fu_3198_p3;
    end else if ((1'b1 == ap_CS_fsm_state15)) begin
        z_buffer_V_address1 = tmp_25_fu_3170_p3;
    end else if ((1'b1 == ap_CS_fsm_state14)) begin
        z_buffer_V_address1 = tmp_23_fu_3142_p3;
    end else if ((1'b1 == ap_CS_fsm_state13)) begin
        z_buffer_V_address1 = tmp_21_fu_3114_p3;
    end else if ((1'b1 == ap_CS_fsm_state12)) begin
        z_buffer_V_address1 = tmp_19_fu_3086_p3;
    end else if ((1'b1 == ap_CS_fsm_state11)) begin
        z_buffer_V_address1 = tmp_17_fu_3058_p3;
    end else if ((1'b1 == ap_CS_fsm_state10)) begin
        z_buffer_V_address1 = tmp_15_fu_3030_p3;
    end else if ((1'b1 == ap_CS_fsm_state9)) begin
        z_buffer_V_address1 = tmp_13_fu_3002_p3;
    end else if ((1'b1 == ap_CS_fsm_state8)) begin
        z_buffer_V_address1 = tmp_11_fu_2974_p3;
    end else if ((1'b1 == ap_CS_fsm_state7)) begin
        z_buffer_V_address1 = tmp_s_fu_2946_p3;
    end else if ((1'b1 == ap_CS_fsm_state6)) begin
        z_buffer_V_address1 = tmp_8_fu_2918_p3;
    end else if ((1'b1 == ap_CS_fsm_state5)) begin
        z_buffer_V_address1 = tmp_6_fu_2890_p3;
    end else if ((1'b1 == ap_CS_fsm_state4)) begin
        z_buffer_V_address1 = tmp_4_fu_2862_p3;
    end else if ((1'b1 == ap_CS_fsm_state3)) begin
        z_buffer_V_address1 = tmp_2_fu_2834_p3;
    end else if ((1'b1 == ap_CS_fsm_state2)) begin
        z_buffer_V_address1 = zext_ln324_fu_2809_p1;
    end else begin
        z_buffer_V_address1 = 'bx;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state68) | (1'b1 == ap_CS_fsm_state67) | (1'b1 == ap_CS_fsm_state66) | (1'b1 == ap_CS_fsm_state65) | (1'b1 == ap_CS_fsm_state64) | (1'b1 == ap_CS_fsm_state63) | (1'b1 == ap_CS_fsm_state62) | (1'b1 == ap_CS_fsm_state61) | (1'b1 == ap_CS_fsm_state60) | (1'b1 == ap_CS_fsm_state59) | (1'b1 == ap_CS_fsm_state58) | (1'b1 == ap_CS_fsm_state57) | (1'b1 == ap_CS_fsm_state56) | (1'b1 == ap_CS_fsm_state55) | (1'b1 == ap_CS_fsm_state54) | (1'b1 == ap_CS_fsm_state53) | (1'b1 == ap_CS_fsm_state52) | (1'b1 == ap_CS_fsm_state51) | (1'b1 == ap_CS_fsm_state50) | (1'b1 == ap_CS_fsm_state49) | (1'b1 == ap_CS_fsm_state48) | (1'b1 == ap_CS_fsm_state47) | (1'b1 == ap_CS_fsm_state46) | (1'b1 == ap_CS_fsm_state45) | (1'b1 == ap_CS_fsm_state44) | (1'b1 == ap_CS_fsm_state43) | (1'b1 == ap_CS_fsm_state42) | (1'b1 == ap_CS_fsm_state41) | (1'b1 == ap_CS_fsm_state40) | (1'b1 == ap_CS_fsm_state39) | (1'b1 == ap_CS_fsm_state38) | (1'b1 == ap_CS_fsm_state37) | (1'b1 == ap_CS_fsm_state36) | (1'b1 == ap_CS_fsm_state35) | (1'b1 == ap_CS_fsm_state34) | (1'b1 == ap_CS_fsm_state33) | (1'b1 == ap_CS_fsm_state32) | (1'b1 == ap_CS_fsm_state31) | (1'b1 == ap_CS_fsm_state30) | (1'b1 == ap_CS_fsm_state29) | (1'b1 == ap_CS_fsm_state28) | (1'b1 == ap_CS_fsm_state27) | (1'b1 == ap_CS_fsm_state26) | (1'b1 == ap_CS_fsm_state25) | (1'b1 == ap_CS_fsm_state24) | (1'b1 == ap_CS_fsm_state23) | (1'b1 == ap_CS_fsm_state22) | (1'b1 == ap_CS_fsm_state21) | (1'b1 == ap_CS_fsm_state20) | (1'b1 == ap_CS_fsm_state19) | (1'b1 == ap_CS_fsm_state18) | (1'b1 == ap_CS_fsm_state17) | (1'b1 == ap_CS_fsm_state16) | (1'b1 == ap_CS_fsm_state15) | (1'b1 == ap_CS_fsm_state14) | (1'b1 == ap_CS_fsm_state13) | (1'b1 == ap_CS_fsm_state12) | (1'b1 == ap_CS_fsm_state11) | (1'b1 == ap_CS_fsm_state10) | (1'b1 == ap_CS_fsm_state9) | (1'b1 == ap_CS_fsm_state8) | (1'b1 == ap_CS_fsm_state7) | (1'b1 == ap_CS_fsm_state6) | (1'b1 == ap_CS_fsm_state5) | (1'b1 == ap_CS_fsm_state4) | (1'b1 == ap_CS_fsm_state3) | (1'b1 == ap_CS_fsm_state129) | (1'b1 == ap_CS_fsm_state2) | (1'b1 == ap_CS_fsm_state128) | (1'b1 == ap_CS_fsm_state127) | (1'b1 == ap_CS_fsm_state126) | (1'b1 == ap_CS_fsm_state125) | (1'b1 == ap_CS_fsm_state124) | (1'b1 == ap_CS_fsm_state123) | (1'b1 == ap_CS_fsm_state122) | (1'b1 == ap_CS_fsm_state121) | (1'b1 == ap_CS_fsm_state120) | (1'b1 == ap_CS_fsm_state119) | (1'b1 == ap_CS_fsm_state118) | (1'b1 == ap_CS_fsm_state117) | (1'b1 == ap_CS_fsm_state116) | (1'b1 == ap_CS_fsm_state115) | (1'b1 == ap_CS_fsm_state114) | (1'b1 == ap_CS_fsm_state113) | (1'b1 == ap_CS_fsm_state112) | (1'b1 == ap_CS_fsm_state111) | (1'b1 == ap_CS_fsm_state110) | (1'b1 == ap_CS_fsm_state109) | (1'b1 == ap_CS_fsm_state108) | (1'b1 == ap_CS_fsm_state107) | (1'b1 == ap_CS_fsm_state106) | (1'b1 == ap_CS_fsm_state105) | (1'b1 == ap_CS_fsm_state104) | (1'b1 == ap_CS_fsm_state103) | (1'b1 == ap_CS_fsm_state102) | (1'b1 == ap_CS_fsm_state101) | (1'b1 == ap_CS_fsm_state100) | (1'b1 == ap_CS_fsm_state99) | (1'b1 == ap_CS_fsm_state98) | (1'b1 == ap_CS_fsm_state97) | (1'b1 == ap_CS_fsm_state96) | (1'b1 == ap_CS_fsm_state95) | (1'b1 == ap_CS_fsm_state94) | (1'b1 == ap_CS_fsm_state93) | (1'b1 == ap_CS_fsm_state92) | (1'b1 == ap_CS_fsm_state91) | (1'b1 == ap_CS_fsm_state90) | (1'b1 == ap_CS_fsm_state89) | (1'b1 == ap_CS_fsm_state88) | (1'b1 == ap_CS_fsm_state87) | (1'b1 == ap_CS_fsm_state86) | (1'b1 == ap_CS_fsm_state85) | (1'b1 == ap_CS_fsm_state84) | (1'b1 == ap_CS_fsm_state83) | (1'b1 == ap_CS_fsm_state82) | (1'b1 == ap_CS_fsm_state81) | (1'b1 == ap_CS_fsm_state80) | (1'b1 == ap_CS_fsm_state79) | (1'b1 == ap_CS_fsm_state78) | (1'b1 == ap_CS_fsm_state77) | (1'b1 == ap_CS_fsm_state76) | (1'b1 == ap_CS_fsm_state75) | (1'b1 == ap_CS_fsm_state74) | (1'b1 == ap_CS_fsm_state73) | (1'b1 == ap_CS_fsm_state72) | (1'b1 == ap_CS_fsm_state71) | (1'b1 == ap_CS_fsm_state70) | (1'b1 == ap_CS_fsm_state69) | ((ap_enable_reg_pp1_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp1_stage0) & (1'b0 == ap_block_pp1_stage0_11001)))) begin
        z_buffer_V_ce0 = 1'b1;
    end else begin
        z_buffer_V_ce0 = 1'b0;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state68) | (1'b1 == ap_CS_fsm_state67) | (1'b1 == ap_CS_fsm_state66) | (1'b1 == ap_CS_fsm_state65) | (1'b1 == ap_CS_fsm_state64) | (1'b1 == ap_CS_fsm_state63) | (1'b1 == ap_CS_fsm_state62) | (1'b1 == ap_CS_fsm_state61) | (1'b1 == ap_CS_fsm_state60) | (1'b1 == ap_CS_fsm_state59) | (1'b1 == ap_CS_fsm_state58) | (1'b1 == ap_CS_fsm_state57) | (1'b1 == ap_CS_fsm_state56) | (1'b1 == ap_CS_fsm_state55) | (1'b1 == ap_CS_fsm_state54) | (1'b1 == ap_CS_fsm_state53) | (1'b1 == ap_CS_fsm_state52) | (1'b1 == ap_CS_fsm_state51) | (1'b1 == ap_CS_fsm_state50) | (1'b1 == ap_CS_fsm_state49) | (1'b1 == ap_CS_fsm_state48) | (1'b1 == ap_CS_fsm_state47) | (1'b1 == ap_CS_fsm_state46) | (1'b1 == ap_CS_fsm_state45) | (1'b1 == ap_CS_fsm_state44) | (1'b1 == ap_CS_fsm_state43) | (1'b1 == ap_CS_fsm_state42) | (1'b1 == ap_CS_fsm_state41) | (1'b1 == ap_CS_fsm_state40) | (1'b1 == ap_CS_fsm_state39) | (1'b1 == ap_CS_fsm_state38) | (1'b1 == ap_CS_fsm_state37) | (1'b1 == ap_CS_fsm_state36) | (1'b1 == ap_CS_fsm_state35) | (1'b1 == ap_CS_fsm_state34) | (1'b1 == ap_CS_fsm_state33) | (1'b1 == ap_CS_fsm_state32) | (1'b1 == ap_CS_fsm_state31) | (1'b1 == ap_CS_fsm_state30) | (1'b1 == ap_CS_fsm_state29) | (1'b1 == ap_CS_fsm_state28) | (1'b1 == ap_CS_fsm_state27) | (1'b1 == ap_CS_fsm_state26) | (1'b1 == ap_CS_fsm_state25) | (1'b1 == ap_CS_fsm_state24) | (1'b1 == ap_CS_fsm_state23) | (1'b1 == ap_CS_fsm_state22) | (1'b1 == ap_CS_fsm_state21) | (1'b1 == ap_CS_fsm_state20) | (1'b1 == ap_CS_fsm_state19) | (1'b1 == ap_CS_fsm_state18) | (1'b1 == ap_CS_fsm_state17) | (1'b1 == ap_CS_fsm_state16) | (1'b1 == ap_CS_fsm_state15) | (1'b1 == ap_CS_fsm_state14) | (1'b1 == ap_CS_fsm_state13) | (1'b1 == ap_CS_fsm_state12) | (1'b1 == ap_CS_fsm_state11) | (1'b1 == ap_CS_fsm_state10) | (1'b1 == ap_CS_fsm_state9) | (1'b1 == ap_CS_fsm_state8) | (1'b1 == ap_CS_fsm_state7) | (1'b1 == ap_CS_fsm_state6) | (1'b1 == ap_CS_fsm_state5) | (1'b1 == ap_CS_fsm_state4) | (1'b1 == ap_CS_fsm_state3) | (1'b1 == ap_CS_fsm_state129) | (1'b1 == ap_CS_fsm_state2) | (1'b1 == ap_CS_fsm_state128) | (1'b1 == ap_CS_fsm_state127) | (1'b1 == ap_CS_fsm_state126) | (1'b1 == ap_CS_fsm_state125) | (1'b1 == ap_CS_fsm_state124) | (1'b1 == ap_CS_fsm_state123) | (1'b1 == ap_CS_fsm_state122) | (1'b1 == ap_CS_fsm_state121) | (1'b1 == ap_CS_fsm_state120) | (1'b1 == ap_CS_fsm_state119) | (1'b1 == ap_CS_fsm_state118) | (1'b1 == ap_CS_fsm_state117) | (1'b1 == ap_CS_fsm_state116) | (1'b1 == ap_CS_fsm_state115) | (1'b1 == ap_CS_fsm_state114) | (1'b1 == ap_CS_fsm_state113) | (1'b1 == ap_CS_fsm_state112) | (1'b1 == ap_CS_fsm_state111) | (1'b1 == ap_CS_fsm_state110) | (1'b1 == ap_CS_fsm_state109) | (1'b1 == ap_CS_fsm_state108) | (1'b1 == ap_CS_fsm_state107) | (1'b1 == ap_CS_fsm_state106) | (1'b1 == ap_CS_fsm_state105) | (1'b1 == ap_CS_fsm_state104) | (1'b1 == ap_CS_fsm_state103) | (1'b1 == ap_CS_fsm_state102) | (1'b1 == ap_CS_fsm_state101) | (1'b1 == ap_CS_fsm_state100) | (1'b1 == ap_CS_fsm_state99) | (1'b1 == ap_CS_fsm_state98) | (1'b1 == ap_CS_fsm_state97) | (1'b1 == ap_CS_fsm_state96) | (1'b1 == ap_CS_fsm_state95) | (1'b1 == ap_CS_fsm_state94) | (1'b1 == ap_CS_fsm_state93) | (1'b1 == ap_CS_fsm_state92) | (1'b1 == ap_CS_fsm_state91) | (1'b1 == ap_CS_fsm_state90) | (1'b1 == ap_CS_fsm_state89) | (1'b1 == ap_CS_fsm_state88) | (1'b1 == ap_CS_fsm_state87) | (1'b1 == ap_CS_fsm_state86) | (1'b1 == ap_CS_fsm_state85) | (1'b1 == ap_CS_fsm_state84) | (1'b1 == ap_CS_fsm_state83) | (1'b1 == ap_CS_fsm_state82) | (1'b1 == ap_CS_fsm_state81) | (1'b1 == ap_CS_fsm_state80) | (1'b1 == ap_CS_fsm_state79) | (1'b1 == ap_CS_fsm_state78) | (1'b1 == ap_CS_fsm_state77) | (1'b1 == ap_CS_fsm_state76) | (1'b1 == ap_CS_fsm_state75) | (1'b1 == ap_CS_fsm_state74) | (1'b1 == ap_CS_fsm_state73) | (1'b1 == ap_CS_fsm_state72) | (1'b1 == ap_CS_fsm_state71) | (1'b1 == ap_CS_fsm_state70) | (1'b1 == ap_CS_fsm_state69) | ((1'b1 == ap_CS_fsm_pp1_stage1) & (1'b0 == ap_block_pp1_stage1_11001) & (ap_enable_reg_pp1_iter0 == 1'b1)))) begin
        z_buffer_V_ce1 = 1'b1;
    end else begin
        z_buffer_V_ce1 = 1'b0;
    end
end

always @ (*) begin
    if (((ap_enable_reg_pp1_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp1_stage0) & (1'b0 == ap_block_pp1_stage0))) begin
        z_buffer_V_d0 = p_Result_2_reg_6843;
    end else if (((1'b1 == ap_CS_fsm_state68) | (1'b1 == ap_CS_fsm_state67) | (1'b1 == ap_CS_fsm_state66) | (1'b1 == ap_CS_fsm_state65) | (1'b1 == ap_CS_fsm_state64) | (1'b1 == ap_CS_fsm_state63) | (1'b1 == ap_CS_fsm_state62) | (1'b1 == ap_CS_fsm_state61) | (1'b1 == ap_CS_fsm_state60) | (1'b1 == ap_CS_fsm_state59) | (1'b1 == ap_CS_fsm_state58) | (1'b1 == ap_CS_fsm_state57) | (1'b1 == ap_CS_fsm_state56) | (1'b1 == ap_CS_fsm_state55) | (1'b1 == ap_CS_fsm_state54) | (1'b1 == ap_CS_fsm_state53) | (1'b1 == ap_CS_fsm_state52) | (1'b1 == ap_CS_fsm_state51) | (1'b1 == ap_CS_fsm_state50) | (1'b1 == ap_CS_fsm_state49) | (1'b1 == ap_CS_fsm_state48) | (1'b1 == ap_CS_fsm_state47) | (1'b1 == ap_CS_fsm_state46) | (1'b1 == ap_CS_fsm_state45) | (1'b1 == ap_CS_fsm_state44) | (1'b1 == ap_CS_fsm_state43) | (1'b1 == ap_CS_fsm_state42) | (1'b1 == ap_CS_fsm_state41) | (1'b1 == ap_CS_fsm_state40) | (1'b1 == ap_CS_fsm_state39) | (1'b1 == ap_CS_fsm_state38) | (1'b1 == ap_CS_fsm_state37) | (1'b1 == ap_CS_fsm_state36) | (1'b1 == ap_CS_fsm_state35) | (1'b1 == ap_CS_fsm_state34) | (1'b1 == ap_CS_fsm_state33) | (1'b1 == ap_CS_fsm_state32) | (1'b1 == ap_CS_fsm_state31) | (1'b1 == ap_CS_fsm_state30) | (1'b1 == ap_CS_fsm_state29) | (1'b1 == ap_CS_fsm_state28) | (1'b1 == ap_CS_fsm_state27) | (1'b1 == ap_CS_fsm_state26) | (1'b1 == ap_CS_fsm_state25) | (1'b1 == ap_CS_fsm_state24) | (1'b1 == ap_CS_fsm_state23) | (1'b1 == ap_CS_fsm_state22) | (1'b1 == ap_CS_fsm_state21) | (1'b1 == ap_CS_fsm_state20) | (1'b1 == ap_CS_fsm_state19) | (1'b1 == ap_CS_fsm_state18) | (1'b1 == ap_CS_fsm_state17) | (1'b1 == ap_CS_fsm_state16) | (1'b1 == ap_CS_fsm_state15) | (1'b1 == ap_CS_fsm_state14) | (1'b1 == ap_CS_fsm_state13) | (1'b1 == ap_CS_fsm_state12) | (1'b1 == ap_CS_fsm_state11) | (1'b1 == ap_CS_fsm_state10) | (1'b1 == ap_CS_fsm_state9) | (1'b1 == ap_CS_fsm_state8) | (1'b1 == ap_CS_fsm_state7) | (1'b1 == ap_CS_fsm_state6) | (1'b1 == ap_CS_fsm_state5) | (1'b1 == ap_CS_fsm_state4) | (1'b1 == ap_CS_fsm_state3) | (1'b1 == ap_CS_fsm_state129) | (1'b1 == ap_CS_fsm_state2) | (1'b1 == ap_CS_fsm_state128) | (1'b1 == ap_CS_fsm_state127) | (1'b1 == ap_CS_fsm_state126) | (1'b1 == ap_CS_fsm_state125) | (1'b1 == ap_CS_fsm_state124) | (1'b1 == ap_CS_fsm_state123) | (1'b1 == ap_CS_fsm_state122) | (1'b1 == ap_CS_fsm_state121) | (1'b1 == ap_CS_fsm_state120) | (1'b1 == ap_CS_fsm_state119) | (1'b1 == ap_CS_fsm_state118) | (1'b1 == ap_CS_fsm_state117) | (1'b1 == ap_CS_fsm_state116) | (1'b1 == ap_CS_fsm_state115) | (1'b1 == ap_CS_fsm_state114) | (1'b1 == ap_CS_fsm_state113) | (1'b1 == ap_CS_fsm_state112) | (1'b1 == ap_CS_fsm_state111) | (1'b1 == ap_CS_fsm_state110) | (1'b1 == ap_CS_fsm_state109) | (1'b1 == ap_CS_fsm_state108) | (1'b1 == ap_CS_fsm_state107) | (1'b1 == ap_CS_fsm_state106) | (1'b1 == ap_CS_fsm_state105) | (1'b1 == ap_CS_fsm_state104) | (1'b1 == ap_CS_fsm_state103) | (1'b1 == ap_CS_fsm_state102) | (1'b1 == ap_CS_fsm_state101) | (1'b1 == ap_CS_fsm_state100) | (1'b1 == ap_CS_fsm_state99) | (1'b1 == ap_CS_fsm_state98) | (1'b1 == ap_CS_fsm_state97) | (1'b1 == ap_CS_fsm_state96) | (1'b1 == ap_CS_fsm_state95) | (1'b1 == ap_CS_fsm_state94) | (1'b1 == ap_CS_fsm_state93) | (1'b1 == ap_CS_fsm_state92) | (1'b1 == ap_CS_fsm_state91) | (1'b1 == ap_CS_fsm_state90) | (1'b1 == ap_CS_fsm_state89) | (1'b1 == ap_CS_fsm_state88) | (1'b1 == ap_CS_fsm_state87) | (1'b1 == ap_CS_fsm_state86) | (1'b1 == ap_CS_fsm_state85) | (1'b1 == ap_CS_fsm_state84) | (1'b1 == ap_CS_fsm_state83) | (1'b1 == ap_CS_fsm_state82) | (1'b1 == ap_CS_fsm_state81) | (1'b1 == ap_CS_fsm_state80) | (1'b1 == ap_CS_fsm_state79) | (1'b1 == ap_CS_fsm_state78) | (1'b1 == ap_CS_fsm_state77) | (1'b1 == ap_CS_fsm_state76) | (1'b1 == ap_CS_fsm_state75) | (1'b1 == ap_CS_fsm_state74) | (1'b1 == ap_CS_fsm_state73) | (1'b1 == ap_CS_fsm_state72) | (1'b1 == ap_CS_fsm_state71) | (1'b1 == ap_CS_fsm_state70) | (1'b1 == ap_CS_fsm_state69))) begin
        z_buffer_V_d0 = 8'd255;
    end else begin
        z_buffer_V_d0 = 'bx;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state68) | (1'b1 == ap_CS_fsm_state67) | (1'b1 == ap_CS_fsm_state66) | (1'b1 == ap_CS_fsm_state65) | (1'b1 == ap_CS_fsm_state64) | (1'b1 == ap_CS_fsm_state63) | (1'b1 == ap_CS_fsm_state62) | (1'b1 == ap_CS_fsm_state61) | (1'b1 == ap_CS_fsm_state60) | (1'b1 == ap_CS_fsm_state59) | (1'b1 == ap_CS_fsm_state58) | (1'b1 == ap_CS_fsm_state57) | (1'b1 == ap_CS_fsm_state56) | (1'b1 == ap_CS_fsm_state55) | (1'b1 == ap_CS_fsm_state54) | (1'b1 == ap_CS_fsm_state53) | (1'b1 == ap_CS_fsm_state52) | (1'b1 == ap_CS_fsm_state51) | (1'b1 == ap_CS_fsm_state50) | (1'b1 == ap_CS_fsm_state49) | (1'b1 == ap_CS_fsm_state48) | (1'b1 == ap_CS_fsm_state47) | (1'b1 == ap_CS_fsm_state46) | (1'b1 == ap_CS_fsm_state45) | (1'b1 == ap_CS_fsm_state44) | (1'b1 == ap_CS_fsm_state43) | (1'b1 == ap_CS_fsm_state42) | (1'b1 == ap_CS_fsm_state41) | (1'b1 == ap_CS_fsm_state40) | (1'b1 == ap_CS_fsm_state39) | (1'b1 == ap_CS_fsm_state38) | (1'b1 == ap_CS_fsm_state37) | (1'b1 == ap_CS_fsm_state36) | (1'b1 == ap_CS_fsm_state35) | (1'b1 == ap_CS_fsm_state34) | (1'b1 == ap_CS_fsm_state33) | (1'b1 == ap_CS_fsm_state32) | (1'b1 == ap_CS_fsm_state31) | (1'b1 == ap_CS_fsm_state30) | (1'b1 == ap_CS_fsm_state29) | (1'b1 == ap_CS_fsm_state28) | (1'b1 == ap_CS_fsm_state27) | (1'b1 == ap_CS_fsm_state26) | (1'b1 == ap_CS_fsm_state25) | (1'b1 == ap_CS_fsm_state24) | (1'b1 == ap_CS_fsm_state23) | (1'b1 == ap_CS_fsm_state22) | (1'b1 == ap_CS_fsm_state21) | (1'b1 == ap_CS_fsm_state20) | (1'b1 == ap_CS_fsm_state19) | (1'b1 == ap_CS_fsm_state18) | (1'b1 == ap_CS_fsm_state17) | (1'b1 == ap_CS_fsm_state16) | (1'b1 == ap_CS_fsm_state15) | (1'b1 == ap_CS_fsm_state14) | (1'b1 == ap_CS_fsm_state13) | (1'b1 == ap_CS_fsm_state12) | (1'b1 == ap_CS_fsm_state11) | (1'b1 == ap_CS_fsm_state10) | (1'b1 == ap_CS_fsm_state9) | (1'b1 == ap_CS_fsm_state8) | (1'b1 == ap_CS_fsm_state7) | (1'b1 == ap_CS_fsm_state6) | (1'b1 == ap_CS_fsm_state5) | (1'b1 == ap_CS_fsm_state4) | (1'b1 == ap_CS_fsm_state3) | (1'b1 == ap_CS_fsm_state129) | (1'b1 == ap_CS_fsm_state128) | (1'b1 == ap_CS_fsm_state127) | (1'b1 == ap_CS_fsm_state126) | (1'b1 == ap_CS_fsm_state125) | (1'b1 == ap_CS_fsm_state124) | (1'b1 == ap_CS_fsm_state123) | (1'b1 == ap_CS_fsm_state122) | (1'b1 == ap_CS_fsm_state121) | (1'b1 == ap_CS_fsm_state120) | (1'b1 == ap_CS_fsm_state119) | (1'b1 == ap_CS_fsm_state118) | (1'b1 == ap_CS_fsm_state117) | (1'b1 == ap_CS_fsm_state116) | (1'b1 == ap_CS_fsm_state115) | (1'b1 == ap_CS_fsm_state114) | (1'b1 == ap_CS_fsm_state113) | (1'b1 == ap_CS_fsm_state112) | (1'b1 == ap_CS_fsm_state111) | (1'b1 == ap_CS_fsm_state110) | (1'b1 == ap_CS_fsm_state109) | (1'b1 == ap_CS_fsm_state108) | (1'b1 == ap_CS_fsm_state107) | (1'b1 == ap_CS_fsm_state106) | (1'b1 == ap_CS_fsm_state105) | (1'b1 == ap_CS_fsm_state104) | (1'b1 == ap_CS_fsm_state103) | (1'b1 == ap_CS_fsm_state102) | (1'b1 == ap_CS_fsm_state101) | (1'b1 == ap_CS_fsm_state100) | (1'b1 == ap_CS_fsm_state99) | (1'b1 == ap_CS_fsm_state98) | (1'b1 == ap_CS_fsm_state97) | (1'b1 == ap_CS_fsm_state96) | (1'b1 == ap_CS_fsm_state95) | (1'b1 == ap_CS_fsm_state94) | (1'b1 == ap_CS_fsm_state93) | (1'b1 == ap_CS_fsm_state92) | (1'b1 == ap_CS_fsm_state91) | (1'b1 == ap_CS_fsm_state90) | (1'b1 == ap_CS_fsm_state89) | (1'b1 == ap_CS_fsm_state88) | (1'b1 == ap_CS_fsm_state87) | (1'b1 == ap_CS_fsm_state86) | (1'b1 == ap_CS_fsm_state85) | (1'b1 == ap_CS_fsm_state84) | (1'b1 == ap_CS_fsm_state83) | (1'b1 == ap_CS_fsm_state82) | (1'b1 == ap_CS_fsm_state81) | (1'b1 == ap_CS_fsm_state80) | (1'b1 == ap_CS_fsm_state79) | (1'b1 == ap_CS_fsm_state78) | (1'b1 == ap_CS_fsm_state77) | (1'b1 == ap_CS_fsm_state76) | (1'b1 == ap_CS_fsm_state75) | (1'b1 == ap_CS_fsm_state74) | (1'b1 == ap_CS_fsm_state73) | (1'b1 == ap_CS_fsm_state72) | (1'b1 == ap_CS_fsm_state71) | (1'b1 == ap_CS_fsm_state70) | (1'b1 == ap_CS_fsm_state69) | ((ap_enable_reg_pp1_iter1 == 1'b1) & (icmp_ln882_1_fu_6447_p2 == 1'd1) & (1'b1 == ap_CS_fsm_pp1_stage0) & (1'b0 == ap_block_pp1_stage0_11001)) | ((icmp_ln882_fu_2789_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state2)))) begin
        z_buffer_V_we0 = 1'b1;
    end else begin
        z_buffer_V_we0 = 1'b0;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state68) | (1'b1 == ap_CS_fsm_state67) | (1'b1 == ap_CS_fsm_state66) | (1'b1 == ap_CS_fsm_state65) | (1'b1 == ap_CS_fsm_state64) | (1'b1 == ap_CS_fsm_state63) | (1'b1 == ap_CS_fsm_state62) | (1'b1 == ap_CS_fsm_state61) | (1'b1 == ap_CS_fsm_state60) | (1'b1 == ap_CS_fsm_state59) | (1'b1 == ap_CS_fsm_state58) | (1'b1 == ap_CS_fsm_state57) | (1'b1 == ap_CS_fsm_state56) | (1'b1 == ap_CS_fsm_state55) | (1'b1 == ap_CS_fsm_state54) | (1'b1 == ap_CS_fsm_state53) | (1'b1 == ap_CS_fsm_state52) | (1'b1 == ap_CS_fsm_state51) | (1'b1 == ap_CS_fsm_state50) | (1'b1 == ap_CS_fsm_state49) | (1'b1 == ap_CS_fsm_state48) | (1'b1 == ap_CS_fsm_state47) | (1'b1 == ap_CS_fsm_state46) | (1'b1 == ap_CS_fsm_state45) | (1'b1 == ap_CS_fsm_state44) | (1'b1 == ap_CS_fsm_state43) | (1'b1 == ap_CS_fsm_state42) | (1'b1 == ap_CS_fsm_state41) | (1'b1 == ap_CS_fsm_state40) | (1'b1 == ap_CS_fsm_state39) | (1'b1 == ap_CS_fsm_state38) | (1'b1 == ap_CS_fsm_state37) | (1'b1 == ap_CS_fsm_state36) | (1'b1 == ap_CS_fsm_state35) | (1'b1 == ap_CS_fsm_state34) | (1'b1 == ap_CS_fsm_state33) | (1'b1 == ap_CS_fsm_state32) | (1'b1 == ap_CS_fsm_state31) | (1'b1 == ap_CS_fsm_state30) | (1'b1 == ap_CS_fsm_state29) | (1'b1 == ap_CS_fsm_state28) | (1'b1 == ap_CS_fsm_state27) | (1'b1 == ap_CS_fsm_state26) | (1'b1 == ap_CS_fsm_state25) | (1'b1 == ap_CS_fsm_state24) | (1'b1 == ap_CS_fsm_state23) | (1'b1 == ap_CS_fsm_state22) | (1'b1 == ap_CS_fsm_state21) | (1'b1 == ap_CS_fsm_state20) | (1'b1 == ap_CS_fsm_state19) | (1'b1 == ap_CS_fsm_state18) | (1'b1 == ap_CS_fsm_state17) | (1'b1 == ap_CS_fsm_state16) | (1'b1 == ap_CS_fsm_state15) | (1'b1 == ap_CS_fsm_state14) | (1'b1 == ap_CS_fsm_state13) | (1'b1 == ap_CS_fsm_state12) | (1'b1 == ap_CS_fsm_state11) | (1'b1 == ap_CS_fsm_state10) | (1'b1 == ap_CS_fsm_state9) | (1'b1 == ap_CS_fsm_state8) | (1'b1 == ap_CS_fsm_state7) | (1'b1 == ap_CS_fsm_state6) | (1'b1 == ap_CS_fsm_state5) | (1'b1 == ap_CS_fsm_state4) | (1'b1 == ap_CS_fsm_state3) | (1'b1 == ap_CS_fsm_state129) | (1'b1 == ap_CS_fsm_state128) | (1'b1 == ap_CS_fsm_state127) | (1'b1 == ap_CS_fsm_state126) | (1'b1 == ap_CS_fsm_state125) | (1'b1 == ap_CS_fsm_state124) | (1'b1 == ap_CS_fsm_state123) | (1'b1 == ap_CS_fsm_state122) | (1'b1 == ap_CS_fsm_state121) | (1'b1 == ap_CS_fsm_state120) | (1'b1 == ap_CS_fsm_state119) | (1'b1 == ap_CS_fsm_state118) | (1'b1 == ap_CS_fsm_state117) | (1'b1 == ap_CS_fsm_state116) | (1'b1 == ap_CS_fsm_state115) | (1'b1 == ap_CS_fsm_state114) | (1'b1 == ap_CS_fsm_state113) | (1'b1 == ap_CS_fsm_state112) | (1'b1 == ap_CS_fsm_state111) | (1'b1 == ap_CS_fsm_state110) | (1'b1 == ap_CS_fsm_state109) | (1'b1 == ap_CS_fsm_state108) | (1'b1 == ap_CS_fsm_state107) | (1'b1 == ap_CS_fsm_state106) | (1'b1 == ap_CS_fsm_state105) | (1'b1 == ap_CS_fsm_state104) | (1'b1 == ap_CS_fsm_state103) | (1'b1 == ap_CS_fsm_state102) | (1'b1 == ap_CS_fsm_state101) | (1'b1 == ap_CS_fsm_state100) | (1'b1 == ap_CS_fsm_state99) | (1'b1 == ap_CS_fsm_state98) | (1'b1 == ap_CS_fsm_state97) | (1'b1 == ap_CS_fsm_state96) | (1'b1 == ap_CS_fsm_state95) | (1'b1 == ap_CS_fsm_state94) | (1'b1 == ap_CS_fsm_state93) | (1'b1 == ap_CS_fsm_state92) | (1'b1 == ap_CS_fsm_state91) | (1'b1 == ap_CS_fsm_state90) | (1'b1 == ap_CS_fsm_state89) | (1'b1 == ap_CS_fsm_state88) | (1'b1 == ap_CS_fsm_state87) | (1'b1 == ap_CS_fsm_state86) | (1'b1 == ap_CS_fsm_state85) | (1'b1 == ap_CS_fsm_state84) | (1'b1 == ap_CS_fsm_state83) | (1'b1 == ap_CS_fsm_state82) | (1'b1 == ap_CS_fsm_state81) | (1'b1 == ap_CS_fsm_state80) | (1'b1 == ap_CS_fsm_state79) | (1'b1 == ap_CS_fsm_state78) | (1'b1 == ap_CS_fsm_state77) | (1'b1 == ap_CS_fsm_state76) | (1'b1 == ap_CS_fsm_state75) | (1'b1 == ap_CS_fsm_state74) | (1'b1 == ap_CS_fsm_state73) | (1'b1 == ap_CS_fsm_state72) | (1'b1 == ap_CS_fsm_state71) | (1'b1 == ap_CS_fsm_state70) | (1'b1 == ap_CS_fsm_state69) | ((icmp_ln882_fu_2789_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state2)))) begin
        z_buffer_V_we1 = 1'b1;
    end else begin
        z_buffer_V_we1 = 1'b0;
    end
end

always @ (*) begin
    case (ap_CS_fsm)
        ap_ST_fsm_state1 : begin
            if ((~((1'b0 == Input_1_empty_n) | (ap_start == 1'b0)) & (icmp_ln874_fu_2783_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state1))) begin
                ap_NS_fsm = ap_ST_fsm_state2;
            end else if ((~((1'b0 == Input_1_empty_n) | (ap_start == 1'b0)) & (icmp_ln874_fu_2783_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state1))) begin
                ap_NS_fsm = ap_ST_fsm_state130;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state1;
            end
        end
        ap_ST_fsm_state2 : begin
            if (((icmp_ln882_fu_2789_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state2))) begin
                ap_NS_fsm = ap_ST_fsm_state3;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state130;
            end
        end
        ap_ST_fsm_state3 : begin
            ap_NS_fsm = ap_ST_fsm_state4;
        end
        ap_ST_fsm_state4 : begin
            ap_NS_fsm = ap_ST_fsm_state5;
        end
        ap_ST_fsm_state5 : begin
            ap_NS_fsm = ap_ST_fsm_state6;
        end
        ap_ST_fsm_state6 : begin
            ap_NS_fsm = ap_ST_fsm_state7;
        end
        ap_ST_fsm_state7 : begin
            ap_NS_fsm = ap_ST_fsm_state8;
        end
        ap_ST_fsm_state8 : begin
            ap_NS_fsm = ap_ST_fsm_state9;
        end
        ap_ST_fsm_state9 : begin
            ap_NS_fsm = ap_ST_fsm_state10;
        end
        ap_ST_fsm_state10 : begin
            ap_NS_fsm = ap_ST_fsm_state11;
        end
        ap_ST_fsm_state11 : begin
            ap_NS_fsm = ap_ST_fsm_state12;
        end
        ap_ST_fsm_state12 : begin
            ap_NS_fsm = ap_ST_fsm_state13;
        end
        ap_ST_fsm_state13 : begin
            ap_NS_fsm = ap_ST_fsm_state14;
        end
        ap_ST_fsm_state14 : begin
            ap_NS_fsm = ap_ST_fsm_state15;
        end
        ap_ST_fsm_state15 : begin
            ap_NS_fsm = ap_ST_fsm_state16;
        end
        ap_ST_fsm_state16 : begin
            ap_NS_fsm = ap_ST_fsm_state17;
        end
        ap_ST_fsm_state17 : begin
            ap_NS_fsm = ap_ST_fsm_state18;
        end
        ap_ST_fsm_state18 : begin
            ap_NS_fsm = ap_ST_fsm_state19;
        end
        ap_ST_fsm_state19 : begin
            ap_NS_fsm = ap_ST_fsm_state20;
        end
        ap_ST_fsm_state20 : begin
            ap_NS_fsm = ap_ST_fsm_state21;
        end
        ap_ST_fsm_state21 : begin
            ap_NS_fsm = ap_ST_fsm_state22;
        end
        ap_ST_fsm_state22 : begin
            ap_NS_fsm = ap_ST_fsm_state23;
        end
        ap_ST_fsm_state23 : begin
            ap_NS_fsm = ap_ST_fsm_state24;
        end
        ap_ST_fsm_state24 : begin
            ap_NS_fsm = ap_ST_fsm_state25;
        end
        ap_ST_fsm_state25 : begin
            ap_NS_fsm = ap_ST_fsm_state26;
        end
        ap_ST_fsm_state26 : begin
            ap_NS_fsm = ap_ST_fsm_state27;
        end
        ap_ST_fsm_state27 : begin
            ap_NS_fsm = ap_ST_fsm_state28;
        end
        ap_ST_fsm_state28 : begin
            ap_NS_fsm = ap_ST_fsm_state29;
        end
        ap_ST_fsm_state29 : begin
            ap_NS_fsm = ap_ST_fsm_state30;
        end
        ap_ST_fsm_state30 : begin
            ap_NS_fsm = ap_ST_fsm_state31;
        end
        ap_ST_fsm_state31 : begin
            ap_NS_fsm = ap_ST_fsm_state32;
        end
        ap_ST_fsm_state32 : begin
            ap_NS_fsm = ap_ST_fsm_state33;
        end
        ap_ST_fsm_state33 : begin
            ap_NS_fsm = ap_ST_fsm_state34;
        end
        ap_ST_fsm_state34 : begin
            ap_NS_fsm = ap_ST_fsm_state35;
        end
        ap_ST_fsm_state35 : begin
            ap_NS_fsm = ap_ST_fsm_state36;
        end
        ap_ST_fsm_state36 : begin
            ap_NS_fsm = ap_ST_fsm_state37;
        end
        ap_ST_fsm_state37 : begin
            ap_NS_fsm = ap_ST_fsm_state38;
        end
        ap_ST_fsm_state38 : begin
            ap_NS_fsm = ap_ST_fsm_state39;
        end
        ap_ST_fsm_state39 : begin
            ap_NS_fsm = ap_ST_fsm_state40;
        end
        ap_ST_fsm_state40 : begin
            ap_NS_fsm = ap_ST_fsm_state41;
        end
        ap_ST_fsm_state41 : begin
            ap_NS_fsm = ap_ST_fsm_state42;
        end
        ap_ST_fsm_state42 : begin
            ap_NS_fsm = ap_ST_fsm_state43;
        end
        ap_ST_fsm_state43 : begin
            ap_NS_fsm = ap_ST_fsm_state44;
        end
        ap_ST_fsm_state44 : begin
            ap_NS_fsm = ap_ST_fsm_state45;
        end
        ap_ST_fsm_state45 : begin
            ap_NS_fsm = ap_ST_fsm_state46;
        end
        ap_ST_fsm_state46 : begin
            ap_NS_fsm = ap_ST_fsm_state47;
        end
        ap_ST_fsm_state47 : begin
            ap_NS_fsm = ap_ST_fsm_state48;
        end
        ap_ST_fsm_state48 : begin
            ap_NS_fsm = ap_ST_fsm_state49;
        end
        ap_ST_fsm_state49 : begin
            ap_NS_fsm = ap_ST_fsm_state50;
        end
        ap_ST_fsm_state50 : begin
            ap_NS_fsm = ap_ST_fsm_state51;
        end
        ap_ST_fsm_state51 : begin
            ap_NS_fsm = ap_ST_fsm_state52;
        end
        ap_ST_fsm_state52 : begin
            ap_NS_fsm = ap_ST_fsm_state53;
        end
        ap_ST_fsm_state53 : begin
            ap_NS_fsm = ap_ST_fsm_state54;
        end
        ap_ST_fsm_state54 : begin
            ap_NS_fsm = ap_ST_fsm_state55;
        end
        ap_ST_fsm_state55 : begin
            ap_NS_fsm = ap_ST_fsm_state56;
        end
        ap_ST_fsm_state56 : begin
            ap_NS_fsm = ap_ST_fsm_state57;
        end
        ap_ST_fsm_state57 : begin
            ap_NS_fsm = ap_ST_fsm_state58;
        end
        ap_ST_fsm_state58 : begin
            ap_NS_fsm = ap_ST_fsm_state59;
        end
        ap_ST_fsm_state59 : begin
            ap_NS_fsm = ap_ST_fsm_state60;
        end
        ap_ST_fsm_state60 : begin
            ap_NS_fsm = ap_ST_fsm_state61;
        end
        ap_ST_fsm_state61 : begin
            ap_NS_fsm = ap_ST_fsm_state62;
        end
        ap_ST_fsm_state62 : begin
            ap_NS_fsm = ap_ST_fsm_state63;
        end
        ap_ST_fsm_state63 : begin
            ap_NS_fsm = ap_ST_fsm_state64;
        end
        ap_ST_fsm_state64 : begin
            ap_NS_fsm = ap_ST_fsm_state65;
        end
        ap_ST_fsm_state65 : begin
            ap_NS_fsm = ap_ST_fsm_state66;
        end
        ap_ST_fsm_state66 : begin
            ap_NS_fsm = ap_ST_fsm_state67;
        end
        ap_ST_fsm_state67 : begin
            ap_NS_fsm = ap_ST_fsm_state68;
        end
        ap_ST_fsm_state68 : begin
            ap_NS_fsm = ap_ST_fsm_state69;
        end
        ap_ST_fsm_state69 : begin
            ap_NS_fsm = ap_ST_fsm_state70;
        end
        ap_ST_fsm_state70 : begin
            ap_NS_fsm = ap_ST_fsm_state71;
        end
        ap_ST_fsm_state71 : begin
            ap_NS_fsm = ap_ST_fsm_state72;
        end
        ap_ST_fsm_state72 : begin
            ap_NS_fsm = ap_ST_fsm_state73;
        end
        ap_ST_fsm_state73 : begin
            ap_NS_fsm = ap_ST_fsm_state74;
        end
        ap_ST_fsm_state74 : begin
            ap_NS_fsm = ap_ST_fsm_state75;
        end
        ap_ST_fsm_state75 : begin
            ap_NS_fsm = ap_ST_fsm_state76;
        end
        ap_ST_fsm_state76 : begin
            ap_NS_fsm = ap_ST_fsm_state77;
        end
        ap_ST_fsm_state77 : begin
            ap_NS_fsm = ap_ST_fsm_state78;
        end
        ap_ST_fsm_state78 : begin
            ap_NS_fsm = ap_ST_fsm_state79;
        end
        ap_ST_fsm_state79 : begin
            ap_NS_fsm = ap_ST_fsm_state80;
        end
        ap_ST_fsm_state80 : begin
            ap_NS_fsm = ap_ST_fsm_state81;
        end
        ap_ST_fsm_state81 : begin
            ap_NS_fsm = ap_ST_fsm_state82;
        end
        ap_ST_fsm_state82 : begin
            ap_NS_fsm = ap_ST_fsm_state83;
        end
        ap_ST_fsm_state83 : begin
            ap_NS_fsm = ap_ST_fsm_state84;
        end
        ap_ST_fsm_state84 : begin
            ap_NS_fsm = ap_ST_fsm_state85;
        end
        ap_ST_fsm_state85 : begin
            ap_NS_fsm = ap_ST_fsm_state86;
        end
        ap_ST_fsm_state86 : begin
            ap_NS_fsm = ap_ST_fsm_state87;
        end
        ap_ST_fsm_state87 : begin
            ap_NS_fsm = ap_ST_fsm_state88;
        end
        ap_ST_fsm_state88 : begin
            ap_NS_fsm = ap_ST_fsm_state89;
        end
        ap_ST_fsm_state89 : begin
            ap_NS_fsm = ap_ST_fsm_state90;
        end
        ap_ST_fsm_state90 : begin
            ap_NS_fsm = ap_ST_fsm_state91;
        end
        ap_ST_fsm_state91 : begin
            ap_NS_fsm = ap_ST_fsm_state92;
        end
        ap_ST_fsm_state92 : begin
            ap_NS_fsm = ap_ST_fsm_state93;
        end
        ap_ST_fsm_state93 : begin
            ap_NS_fsm = ap_ST_fsm_state94;
        end
        ap_ST_fsm_state94 : begin
            ap_NS_fsm = ap_ST_fsm_state95;
        end
        ap_ST_fsm_state95 : begin
            ap_NS_fsm = ap_ST_fsm_state96;
        end
        ap_ST_fsm_state96 : begin
            ap_NS_fsm = ap_ST_fsm_state97;
        end
        ap_ST_fsm_state97 : begin
            ap_NS_fsm = ap_ST_fsm_state98;
        end
        ap_ST_fsm_state98 : begin
            ap_NS_fsm = ap_ST_fsm_state99;
        end
        ap_ST_fsm_state99 : begin
            ap_NS_fsm = ap_ST_fsm_state100;
        end
        ap_ST_fsm_state100 : begin
            ap_NS_fsm = ap_ST_fsm_state101;
        end
        ap_ST_fsm_state101 : begin
            ap_NS_fsm = ap_ST_fsm_state102;
        end
        ap_ST_fsm_state102 : begin
            ap_NS_fsm = ap_ST_fsm_state103;
        end
        ap_ST_fsm_state103 : begin
            ap_NS_fsm = ap_ST_fsm_state104;
        end
        ap_ST_fsm_state104 : begin
            ap_NS_fsm = ap_ST_fsm_state105;
        end
        ap_ST_fsm_state105 : begin
            ap_NS_fsm = ap_ST_fsm_state106;
        end
        ap_ST_fsm_state106 : begin
            ap_NS_fsm = ap_ST_fsm_state107;
        end
        ap_ST_fsm_state107 : begin
            ap_NS_fsm = ap_ST_fsm_state108;
        end
        ap_ST_fsm_state108 : begin
            ap_NS_fsm = ap_ST_fsm_state109;
        end
        ap_ST_fsm_state109 : begin
            ap_NS_fsm = ap_ST_fsm_state110;
        end
        ap_ST_fsm_state110 : begin
            ap_NS_fsm = ap_ST_fsm_state111;
        end
        ap_ST_fsm_state111 : begin
            ap_NS_fsm = ap_ST_fsm_state112;
        end
        ap_ST_fsm_state112 : begin
            ap_NS_fsm = ap_ST_fsm_state113;
        end
        ap_ST_fsm_state113 : begin
            ap_NS_fsm = ap_ST_fsm_state114;
        end
        ap_ST_fsm_state114 : begin
            ap_NS_fsm = ap_ST_fsm_state115;
        end
        ap_ST_fsm_state115 : begin
            ap_NS_fsm = ap_ST_fsm_state116;
        end
        ap_ST_fsm_state116 : begin
            ap_NS_fsm = ap_ST_fsm_state117;
        end
        ap_ST_fsm_state117 : begin
            ap_NS_fsm = ap_ST_fsm_state118;
        end
        ap_ST_fsm_state118 : begin
            ap_NS_fsm = ap_ST_fsm_state119;
        end
        ap_ST_fsm_state119 : begin
            ap_NS_fsm = ap_ST_fsm_state120;
        end
        ap_ST_fsm_state120 : begin
            ap_NS_fsm = ap_ST_fsm_state121;
        end
        ap_ST_fsm_state121 : begin
            ap_NS_fsm = ap_ST_fsm_state122;
        end
        ap_ST_fsm_state122 : begin
            ap_NS_fsm = ap_ST_fsm_state123;
        end
        ap_ST_fsm_state123 : begin
            ap_NS_fsm = ap_ST_fsm_state124;
        end
        ap_ST_fsm_state124 : begin
            ap_NS_fsm = ap_ST_fsm_state125;
        end
        ap_ST_fsm_state125 : begin
            ap_NS_fsm = ap_ST_fsm_state126;
        end
        ap_ST_fsm_state126 : begin
            ap_NS_fsm = ap_ST_fsm_state127;
        end
        ap_ST_fsm_state127 : begin
            ap_NS_fsm = ap_ST_fsm_state128;
        end
        ap_ST_fsm_state128 : begin
            ap_NS_fsm = ap_ST_fsm_state129;
        end
        ap_ST_fsm_state129 : begin
            ap_NS_fsm = ap_ST_fsm_state2;
        end
        ap_ST_fsm_state130 : begin
            ap_NS_fsm = ap_ST_fsm_pp1_stage0;
        end
        ap_ST_fsm_pp1_stage0 : begin
            if ((~((ap_enable_reg_pp1_iter1 == 1'b0) & (icmp_ln449_fu_6393_p2 == 1'd1) & (1'b0 == ap_block_pp1_stage0_subdone) & (ap_enable_reg_pp1_iter0 == 1'b1)) & (1'b0 == ap_block_pp1_stage0_subdone))) begin
                ap_NS_fsm = ap_ST_fsm_pp1_stage1;
            end else if (((ap_enable_reg_pp1_iter1 == 1'b0) & (icmp_ln449_fu_6393_p2 == 1'd1) & (1'b0 == ap_block_pp1_stage0_subdone) & (ap_enable_reg_pp1_iter0 == 1'b1))) begin
                ap_NS_fsm = ap_ST_fsm_state135;
            end else begin
                ap_NS_fsm = ap_ST_fsm_pp1_stage0;
            end
        end
        ap_ST_fsm_pp1_stage1 : begin
            if ((~((ap_enable_reg_pp1_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp1_stage1) & (1'b0 == ap_block_pp1_stage1_subdone) & (ap_enable_reg_pp1_iter0 == 1'b0)) & (1'b0 == ap_block_pp1_stage1_subdone))) begin
                ap_NS_fsm = ap_ST_fsm_pp1_stage0;
            end else if (((ap_enable_reg_pp1_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp1_stage1) & (1'b0 == ap_block_pp1_stage1_subdone) & (ap_enable_reg_pp1_iter0 == 1'b0))) begin
                ap_NS_fsm = ap_ST_fsm_state135;
            end else begin
                ap_NS_fsm = ap_ST_fsm_pp1_stage1;
            end
        end
        ap_ST_fsm_state135 : begin
            if (((1'b1 == ap_CS_fsm_state135) & (1'b1 == Output_1_full_n))) begin
                ap_NS_fsm = ap_ST_fsm_pp2_stage0;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state135;
            end
        end
        ap_ST_fsm_pp2_stage0 : begin
            if (~((ap_enable_reg_pp2_iter0 == 1'b1) & (icmp_ln882_2_fu_6475_p2 == 1'd1) & (1'b0 == ap_block_pp2_stage0_subdone))) begin
                ap_NS_fsm = ap_ST_fsm_pp2_stage0;
            end else if (((ap_enable_reg_pp2_iter0 == 1'b1) & (icmp_ln882_2_fu_6475_p2 == 1'd1) & (1'b0 == ap_block_pp2_stage0_subdone))) begin
                ap_NS_fsm = ap_ST_fsm_state138;
            end else begin
                ap_NS_fsm = ap_ST_fsm_pp2_stage0;
            end
        end
        ap_ST_fsm_state138 : begin
            ap_NS_fsm = ap_ST_fsm_state1;
        end
        default : begin
            ap_NS_fsm = 'bx;
        end
    endcase
end

assign add_ln469_fu_6481_p2 = (j_reg_2765 + 16'd1);

assign add_ln695_1_fu_6459_p2 = (pixel_cntr_V_fu_602 + 16'd1);

assign add_ln695_2_fu_6398_p2 = (ap_phi_mux_empty_23_phi_fu_2758_p4 + 16'd1);

assign add_ln695_3_fu_6507_p2 = (t_V_reg_6537 + 16'd1);

assign add_ln695_fu_2795_p2 = (empty_reg_2743 + 9'd1);

assign ap_CS_fsm_pp1_stage0 = ap_CS_fsm[32'd130];

assign ap_CS_fsm_pp1_stage1 = ap_CS_fsm[32'd131];

assign ap_CS_fsm_pp2_stage0 = ap_CS_fsm[32'd133];

assign ap_CS_fsm_state1 = ap_CS_fsm[32'd0];

assign ap_CS_fsm_state10 = ap_CS_fsm[32'd9];

assign ap_CS_fsm_state100 = ap_CS_fsm[32'd99];

assign ap_CS_fsm_state101 = ap_CS_fsm[32'd100];

assign ap_CS_fsm_state102 = ap_CS_fsm[32'd101];

assign ap_CS_fsm_state103 = ap_CS_fsm[32'd102];

assign ap_CS_fsm_state104 = ap_CS_fsm[32'd103];

assign ap_CS_fsm_state105 = ap_CS_fsm[32'd104];

assign ap_CS_fsm_state106 = ap_CS_fsm[32'd105];

assign ap_CS_fsm_state107 = ap_CS_fsm[32'd106];

assign ap_CS_fsm_state108 = ap_CS_fsm[32'd107];

assign ap_CS_fsm_state109 = ap_CS_fsm[32'd108];

assign ap_CS_fsm_state11 = ap_CS_fsm[32'd10];

assign ap_CS_fsm_state110 = ap_CS_fsm[32'd109];

assign ap_CS_fsm_state111 = ap_CS_fsm[32'd110];

assign ap_CS_fsm_state112 = ap_CS_fsm[32'd111];

assign ap_CS_fsm_state113 = ap_CS_fsm[32'd112];

assign ap_CS_fsm_state114 = ap_CS_fsm[32'd113];

assign ap_CS_fsm_state115 = ap_CS_fsm[32'd114];

assign ap_CS_fsm_state116 = ap_CS_fsm[32'd115];

assign ap_CS_fsm_state117 = ap_CS_fsm[32'd116];

assign ap_CS_fsm_state118 = ap_CS_fsm[32'd117];

assign ap_CS_fsm_state119 = ap_CS_fsm[32'd118];

assign ap_CS_fsm_state12 = ap_CS_fsm[32'd11];

assign ap_CS_fsm_state120 = ap_CS_fsm[32'd119];

assign ap_CS_fsm_state121 = ap_CS_fsm[32'd120];

assign ap_CS_fsm_state122 = ap_CS_fsm[32'd121];

assign ap_CS_fsm_state123 = ap_CS_fsm[32'd122];

assign ap_CS_fsm_state124 = ap_CS_fsm[32'd123];

assign ap_CS_fsm_state125 = ap_CS_fsm[32'd124];

assign ap_CS_fsm_state126 = ap_CS_fsm[32'd125];

assign ap_CS_fsm_state127 = ap_CS_fsm[32'd126];

assign ap_CS_fsm_state128 = ap_CS_fsm[32'd127];

assign ap_CS_fsm_state129 = ap_CS_fsm[32'd128];

assign ap_CS_fsm_state13 = ap_CS_fsm[32'd12];

assign ap_CS_fsm_state130 = ap_CS_fsm[32'd129];

assign ap_CS_fsm_state135 = ap_CS_fsm[32'd132];

assign ap_CS_fsm_state138 = ap_CS_fsm[32'd134];

assign ap_CS_fsm_state14 = ap_CS_fsm[32'd13];

assign ap_CS_fsm_state15 = ap_CS_fsm[32'd14];

assign ap_CS_fsm_state16 = ap_CS_fsm[32'd15];

assign ap_CS_fsm_state17 = ap_CS_fsm[32'd16];

assign ap_CS_fsm_state18 = ap_CS_fsm[32'd17];

assign ap_CS_fsm_state19 = ap_CS_fsm[32'd18];

assign ap_CS_fsm_state2 = ap_CS_fsm[32'd1];

assign ap_CS_fsm_state20 = ap_CS_fsm[32'd19];

assign ap_CS_fsm_state21 = ap_CS_fsm[32'd20];

assign ap_CS_fsm_state22 = ap_CS_fsm[32'd21];

assign ap_CS_fsm_state23 = ap_CS_fsm[32'd22];

assign ap_CS_fsm_state24 = ap_CS_fsm[32'd23];

assign ap_CS_fsm_state25 = ap_CS_fsm[32'd24];

assign ap_CS_fsm_state26 = ap_CS_fsm[32'd25];

assign ap_CS_fsm_state27 = ap_CS_fsm[32'd26];

assign ap_CS_fsm_state28 = ap_CS_fsm[32'd27];

assign ap_CS_fsm_state29 = ap_CS_fsm[32'd28];

assign ap_CS_fsm_state3 = ap_CS_fsm[32'd2];

assign ap_CS_fsm_state30 = ap_CS_fsm[32'd29];

assign ap_CS_fsm_state31 = ap_CS_fsm[32'd30];

assign ap_CS_fsm_state32 = ap_CS_fsm[32'd31];

assign ap_CS_fsm_state33 = ap_CS_fsm[32'd32];

assign ap_CS_fsm_state34 = ap_CS_fsm[32'd33];

assign ap_CS_fsm_state35 = ap_CS_fsm[32'd34];

assign ap_CS_fsm_state36 = ap_CS_fsm[32'd35];

assign ap_CS_fsm_state37 = ap_CS_fsm[32'd36];

assign ap_CS_fsm_state38 = ap_CS_fsm[32'd37];

assign ap_CS_fsm_state39 = ap_CS_fsm[32'd38];

assign ap_CS_fsm_state4 = ap_CS_fsm[32'd3];

assign ap_CS_fsm_state40 = ap_CS_fsm[32'd39];

assign ap_CS_fsm_state41 = ap_CS_fsm[32'd40];

assign ap_CS_fsm_state42 = ap_CS_fsm[32'd41];

assign ap_CS_fsm_state43 = ap_CS_fsm[32'd42];

assign ap_CS_fsm_state44 = ap_CS_fsm[32'd43];

assign ap_CS_fsm_state45 = ap_CS_fsm[32'd44];

assign ap_CS_fsm_state46 = ap_CS_fsm[32'd45];

assign ap_CS_fsm_state47 = ap_CS_fsm[32'd46];

assign ap_CS_fsm_state48 = ap_CS_fsm[32'd47];

assign ap_CS_fsm_state49 = ap_CS_fsm[32'd48];

assign ap_CS_fsm_state5 = ap_CS_fsm[32'd4];

assign ap_CS_fsm_state50 = ap_CS_fsm[32'd49];

assign ap_CS_fsm_state51 = ap_CS_fsm[32'd50];

assign ap_CS_fsm_state52 = ap_CS_fsm[32'd51];

assign ap_CS_fsm_state53 = ap_CS_fsm[32'd52];

assign ap_CS_fsm_state54 = ap_CS_fsm[32'd53];

assign ap_CS_fsm_state55 = ap_CS_fsm[32'd54];

assign ap_CS_fsm_state56 = ap_CS_fsm[32'd55];

assign ap_CS_fsm_state57 = ap_CS_fsm[32'd56];

assign ap_CS_fsm_state58 = ap_CS_fsm[32'd57];

assign ap_CS_fsm_state59 = ap_CS_fsm[32'd58];

assign ap_CS_fsm_state6 = ap_CS_fsm[32'd5];

assign ap_CS_fsm_state60 = ap_CS_fsm[32'd59];

assign ap_CS_fsm_state61 = ap_CS_fsm[32'd60];

assign ap_CS_fsm_state62 = ap_CS_fsm[32'd61];

assign ap_CS_fsm_state63 = ap_CS_fsm[32'd62];

assign ap_CS_fsm_state64 = ap_CS_fsm[32'd63];

assign ap_CS_fsm_state65 = ap_CS_fsm[32'd64];

assign ap_CS_fsm_state66 = ap_CS_fsm[32'd65];

assign ap_CS_fsm_state67 = ap_CS_fsm[32'd66];

assign ap_CS_fsm_state68 = ap_CS_fsm[32'd67];

assign ap_CS_fsm_state69 = ap_CS_fsm[32'd68];

assign ap_CS_fsm_state7 = ap_CS_fsm[32'd6];

assign ap_CS_fsm_state70 = ap_CS_fsm[32'd69];

assign ap_CS_fsm_state71 = ap_CS_fsm[32'd70];

assign ap_CS_fsm_state72 = ap_CS_fsm[32'd71];

assign ap_CS_fsm_state73 = ap_CS_fsm[32'd72];

assign ap_CS_fsm_state74 = ap_CS_fsm[32'd73];

assign ap_CS_fsm_state75 = ap_CS_fsm[32'd74];

assign ap_CS_fsm_state76 = ap_CS_fsm[32'd75];

assign ap_CS_fsm_state77 = ap_CS_fsm[32'd76];

assign ap_CS_fsm_state78 = ap_CS_fsm[32'd77];

assign ap_CS_fsm_state79 = ap_CS_fsm[32'd78];

assign ap_CS_fsm_state8 = ap_CS_fsm[32'd7];

assign ap_CS_fsm_state80 = ap_CS_fsm[32'd79];

assign ap_CS_fsm_state81 = ap_CS_fsm[32'd80];

assign ap_CS_fsm_state82 = ap_CS_fsm[32'd81];

assign ap_CS_fsm_state83 = ap_CS_fsm[32'd82];

assign ap_CS_fsm_state84 = ap_CS_fsm[32'd83];

assign ap_CS_fsm_state85 = ap_CS_fsm[32'd84];

assign ap_CS_fsm_state86 = ap_CS_fsm[32'd85];

assign ap_CS_fsm_state87 = ap_CS_fsm[32'd86];

assign ap_CS_fsm_state88 = ap_CS_fsm[32'd87];

assign ap_CS_fsm_state89 = ap_CS_fsm[32'd88];

assign ap_CS_fsm_state9 = ap_CS_fsm[32'd8];

assign ap_CS_fsm_state90 = ap_CS_fsm[32'd89];

assign ap_CS_fsm_state91 = ap_CS_fsm[32'd90];

assign ap_CS_fsm_state92 = ap_CS_fsm[32'd91];

assign ap_CS_fsm_state93 = ap_CS_fsm[32'd92];

assign ap_CS_fsm_state94 = ap_CS_fsm[32'd93];

assign ap_CS_fsm_state95 = ap_CS_fsm[32'd94];

assign ap_CS_fsm_state96 = ap_CS_fsm[32'd95];

assign ap_CS_fsm_state97 = ap_CS_fsm[32'd96];

assign ap_CS_fsm_state98 = ap_CS_fsm[32'd97];

assign ap_CS_fsm_state99 = ap_CS_fsm[32'd98];

assign ap_block_pp1_stage0 = ~(1'b1 == 1'b1);

assign ap_block_pp1_stage0_11001 = ~(1'b1 == 1'b1);

assign ap_block_pp1_stage0_subdone = ~(1'b1 == 1'b1);

assign ap_block_pp1_stage1 = ~(1'b1 == 1'b1);

always @ (*) begin
    ap_block_pp1_stage1_11001 = ((1'b0 == Input_1_empty_n) & (icmp_ln449_reg_6824 == 1'd0) & (ap_enable_reg_pp1_iter0 == 1'b1));
end

always @ (*) begin
    ap_block_pp1_stage1_subdone = ((1'b0 == Input_1_empty_n) & (icmp_ln449_reg_6824 == 1'd0) & (ap_enable_reg_pp1_iter0 == 1'b1));
end

assign ap_block_pp2_stage0 = ~(1'b1 == 1'b1);

always @ (*) begin
    ap_block_pp2_stage0_01001 = ((1'b0 == Output_1_full_n) & (icmp_ln882_2_reg_6864 == 1'd0) & (ap_enable_reg_pp2_iter1 == 1'b1));
end

always @ (*) begin
    ap_block_pp2_stage0_11001 = ((1'b0 == Output_1_full_n) & (icmp_ln882_2_reg_6864 == 1'd0) & (ap_enable_reg_pp2_iter1 == 1'b1));
end

always @ (*) begin
    ap_block_pp2_stage0_subdone = ((1'b0 == Output_1_full_n) & (icmp_ln882_2_reg_6864 == 1'd0) & (ap_enable_reg_pp2_iter1 == 1'b1));
end

always @ (*) begin
    ap_block_state1 = ((1'b0 == Input_1_empty_n) | (ap_start == 1'b0));
end

assign ap_block_state131_pp1_stage0_iter0 = ~(1'b1 == 1'b1);

always @ (*) begin
    ap_block_state132_pp1_stage1_iter0 = ((1'b0 == Input_1_empty_n) & (icmp_ln449_reg_6824 == 1'd0));
end

assign ap_block_state133_pp1_stage0_iter1 = ~(1'b1 == 1'b1);

assign ap_block_state134_pp1_stage1_iter1 = ~(1'b1 == 1'b1);

assign ap_block_state136_pp2_stage0_iter0 = ~(1'b1 == 1'b1);

always @ (*) begin
    ap_block_state137_pp2_stage0_iter1 = ((1'b0 == Output_1_full_n) & (icmp_ln882_2_reg_6864 == 1'd0));
end

assign ap_enable_pp1 = (ap_idle_pp1 ^ 1'b1);

assign ap_enable_pp2 = (ap_idle_pp2 ^ 1'b1);

assign empty_22_fu_6385_p1 = tmp_V_reg_6532[15:0];

assign icmp_ln449_fu_6393_p2 = ((ap_phi_mux_empty_23_phi_fu_2758_p4 == empty_22_reg_6819) ? 1'b1 : 1'b0);

assign icmp_ln874_1_fu_6512_p2 = ((add_ln695_3_fu_6507_p2 == 16'd3192) ? 1'b1 : 1'b0);

assign icmp_ln874_fu_2783_p2 = ((counter == 16'd0) ? 1'b1 : 1'b0);

assign icmp_ln882_1_fu_6447_p2 = ((p_Result_2_reg_6843 < z_buffer_V_q1) ? 1'b1 : 1'b0);

assign icmp_ln882_2_fu_6475_p2 = ((j_reg_2765 == pixel_cntr_V_fu_602) ? 1'b1 : 1'b0);

assign icmp_ln882_fu_2789_p2 = ((empty_reg_2743 == 9'd256) ? 1'b1 : 1'b0);

assign or_ln324_100_fu_4215_p2 = (tmp_reg_6554 | 17'd101);

assign or_ln324_101_fu_4229_p2 = (tmp_reg_6554 | 17'd102);

assign or_ln324_102_fu_4243_p2 = (tmp_reg_6554 | 17'd103);

assign or_ln324_103_fu_4257_p2 = (tmp_reg_6554 | 17'd104);

assign or_ln324_104_fu_4271_p2 = (tmp_reg_6554 | 17'd105);

assign or_ln324_105_fu_4285_p2 = (tmp_reg_6554 | 17'd106);

assign or_ln324_106_fu_4299_p2 = (tmp_reg_6554 | 17'd107);

assign or_ln324_107_fu_4313_p2 = (tmp_reg_6554 | 17'd108);

assign or_ln324_108_fu_4327_p2 = (tmp_reg_6554 | 17'd109);

assign or_ln324_109_fu_4341_p2 = (tmp_reg_6554 | 17'd110);

assign or_ln324_10_fu_2955_p2 = (tmp_reg_6554 | 17'd11);

assign or_ln324_110_fu_4355_p2 = (tmp_reg_6554 | 17'd111);

assign or_ln324_111_fu_4369_p2 = (tmp_reg_6554 | 17'd112);

assign or_ln324_112_fu_4383_p2 = (tmp_reg_6554 | 17'd113);

assign or_ln324_113_fu_4397_p2 = (tmp_reg_6554 | 17'd114);

assign or_ln324_114_fu_4411_p2 = (tmp_reg_6554 | 17'd115);

assign or_ln324_115_fu_4425_p2 = (tmp_reg_6554 | 17'd116);

assign or_ln324_116_fu_4439_p2 = (tmp_reg_6554 | 17'd117);

assign or_ln324_117_fu_4453_p2 = (tmp_reg_6554 | 17'd118);

assign or_ln324_118_fu_4467_p2 = (tmp_reg_6554 | 17'd119);

assign or_ln324_119_fu_4481_p2 = (tmp_reg_6554 | 17'd120);

assign or_ln324_11_fu_2969_p2 = (tmp_reg_6554 | 17'd12);

assign or_ln324_120_fu_4495_p2 = (tmp_reg_6554 | 17'd121);

assign or_ln324_121_fu_4509_p2 = (tmp_reg_6554 | 17'd122);

assign or_ln324_122_fu_4523_p2 = (tmp_reg_6554 | 17'd123);

assign or_ln324_123_fu_4537_p2 = (tmp_reg_6554 | 17'd124);

assign or_ln324_124_fu_4551_p2 = (tmp_reg_6554 | 17'd125);

assign or_ln324_125_fu_4565_p2 = (tmp_reg_6554 | 17'd126);

assign or_ln324_126_fu_4579_p2 = (tmp_reg_6554 | 17'd127);

assign or_ln324_127_fu_4593_p2 = (tmp_reg_6554 | 17'd128);

assign or_ln324_128_fu_4607_p2 = (tmp_reg_6554 | 17'd129);

assign or_ln324_129_fu_4621_p2 = (tmp_reg_6554 | 17'd130);

assign or_ln324_12_fu_2983_p2 = (tmp_reg_6554 | 17'd13);

assign or_ln324_130_fu_4635_p2 = (tmp_reg_6554 | 17'd131);

assign or_ln324_131_fu_4649_p2 = (tmp_reg_6554 | 17'd132);

assign or_ln324_132_fu_4663_p2 = (tmp_reg_6554 | 17'd133);

assign or_ln324_133_fu_4677_p2 = (tmp_reg_6554 | 17'd134);

assign or_ln324_134_fu_4691_p2 = (tmp_reg_6554 | 17'd135);

assign or_ln324_135_fu_4705_p2 = (tmp_reg_6554 | 17'd136);

assign or_ln324_136_fu_4719_p2 = (tmp_reg_6554 | 17'd137);

assign or_ln324_137_fu_4733_p2 = (tmp_reg_6554 | 17'd138);

assign or_ln324_138_fu_4747_p2 = (tmp_reg_6554 | 17'd139);

assign or_ln324_139_fu_4761_p2 = (tmp_reg_6554 | 17'd140);

assign or_ln324_13_fu_2997_p2 = (tmp_reg_6554 | 17'd14);

assign or_ln324_140_fu_4775_p2 = (tmp_reg_6554 | 17'd141);

assign or_ln324_141_fu_4789_p2 = (tmp_reg_6554 | 17'd142);

assign or_ln324_142_fu_4803_p2 = (tmp_reg_6554 | 17'd143);

assign or_ln324_143_fu_4817_p2 = (tmp_reg_6554 | 17'd144);

assign or_ln324_144_fu_4831_p2 = (tmp_reg_6554 | 17'd145);

assign or_ln324_145_fu_4845_p2 = (tmp_reg_6554 | 17'd146);

assign or_ln324_146_fu_4859_p2 = (tmp_reg_6554 | 17'd147);

assign or_ln324_147_fu_4873_p2 = (tmp_reg_6554 | 17'd148);

assign or_ln324_148_fu_4887_p2 = (tmp_reg_6554 | 17'd149);

assign or_ln324_149_fu_4901_p2 = (tmp_reg_6554 | 17'd150);

assign or_ln324_14_fu_3011_p2 = (tmp_reg_6554 | 17'd15);

assign or_ln324_150_fu_4915_p2 = (tmp_reg_6554 | 17'd151);

assign or_ln324_151_fu_4929_p2 = (tmp_reg_6554 | 17'd152);

assign or_ln324_152_fu_4943_p2 = (tmp_reg_6554 | 17'd153);

assign or_ln324_153_fu_4957_p2 = (tmp_reg_6554 | 17'd154);

assign or_ln324_154_fu_4971_p2 = (tmp_reg_6554 | 17'd155);

assign or_ln324_155_fu_4985_p2 = (tmp_reg_6554 | 17'd156);

assign or_ln324_156_fu_4999_p2 = (tmp_reg_6554 | 17'd157);

assign or_ln324_157_fu_5013_p2 = (tmp_reg_6554 | 17'd158);

assign or_ln324_158_fu_5027_p2 = (tmp_reg_6554 | 17'd159);

assign or_ln324_159_fu_5041_p2 = (tmp_reg_6554 | 17'd160);

assign or_ln324_15_fu_3025_p2 = (tmp_reg_6554 | 17'd16);

assign or_ln324_160_fu_5055_p2 = (tmp_reg_6554 | 17'd161);

assign or_ln324_161_fu_5069_p2 = (tmp_reg_6554 | 17'd162);

assign or_ln324_162_fu_5083_p2 = (tmp_reg_6554 | 17'd163);

assign or_ln324_163_fu_5097_p2 = (tmp_reg_6554 | 17'd164);

assign or_ln324_164_fu_5111_p2 = (tmp_reg_6554 | 17'd165);

assign or_ln324_165_fu_5125_p2 = (tmp_reg_6554 | 17'd166);

assign or_ln324_166_fu_5139_p2 = (tmp_reg_6554 | 17'd167);

assign or_ln324_167_fu_5153_p2 = (tmp_reg_6554 | 17'd168);

assign or_ln324_168_fu_5167_p2 = (tmp_reg_6554 | 17'd169);

assign or_ln324_169_fu_5181_p2 = (tmp_reg_6554 | 17'd170);

assign or_ln324_16_fu_3039_p2 = (tmp_reg_6554 | 17'd17);

assign or_ln324_170_fu_5195_p2 = (tmp_reg_6554 | 17'd171);

assign or_ln324_171_fu_5209_p2 = (tmp_reg_6554 | 17'd172);

assign or_ln324_172_fu_5223_p2 = (tmp_reg_6554 | 17'd173);

assign or_ln324_173_fu_5237_p2 = (tmp_reg_6554 | 17'd174);

assign or_ln324_174_fu_5251_p2 = (tmp_reg_6554 | 17'd175);

assign or_ln324_175_fu_5265_p2 = (tmp_reg_6554 | 17'd176);

assign or_ln324_176_fu_5279_p2 = (tmp_reg_6554 | 17'd177);

assign or_ln324_177_fu_5293_p2 = (tmp_reg_6554 | 17'd178);

assign or_ln324_178_fu_5307_p2 = (tmp_reg_6554 | 17'd179);

assign or_ln324_179_fu_5321_p2 = (tmp_reg_6554 | 17'd180);

assign or_ln324_17_fu_3053_p2 = (tmp_reg_6554 | 17'd18);

assign or_ln324_180_fu_5335_p2 = (tmp_reg_6554 | 17'd181);

assign or_ln324_181_fu_5349_p2 = (tmp_reg_6554 | 17'd182);

assign or_ln324_182_fu_5363_p2 = (tmp_reg_6554 | 17'd183);

assign or_ln324_183_fu_5377_p2 = (tmp_reg_6554 | 17'd184);

assign or_ln324_184_fu_5391_p2 = (tmp_reg_6554 | 17'd185);

assign or_ln324_185_fu_5405_p2 = (tmp_reg_6554 | 17'd186);

assign or_ln324_186_fu_5419_p2 = (tmp_reg_6554 | 17'd187);

assign or_ln324_187_fu_5433_p2 = (tmp_reg_6554 | 17'd188);

assign or_ln324_188_fu_5447_p2 = (tmp_reg_6554 | 17'd189);

assign or_ln324_189_fu_5461_p2 = (tmp_reg_6554 | 17'd190);

assign or_ln324_18_fu_3067_p2 = (tmp_reg_6554 | 17'd19);

assign or_ln324_190_fu_5475_p2 = (tmp_reg_6554 | 17'd191);

assign or_ln324_191_fu_5489_p2 = (tmp_reg_6554 | 17'd192);

assign or_ln324_192_fu_5503_p2 = (tmp_reg_6554 | 17'd193);

assign or_ln324_193_fu_5517_p2 = (tmp_reg_6554 | 17'd194);

assign or_ln324_194_fu_5531_p2 = (tmp_reg_6554 | 17'd195);

assign or_ln324_195_fu_5545_p2 = (tmp_reg_6554 | 17'd196);

assign or_ln324_196_fu_5559_p2 = (tmp_reg_6554 | 17'd197);

assign or_ln324_197_fu_5573_p2 = (tmp_reg_6554 | 17'd198);

assign or_ln324_198_fu_5587_p2 = (tmp_reg_6554 | 17'd199);

assign or_ln324_199_fu_5601_p2 = (tmp_reg_6554 | 17'd200);

assign or_ln324_19_fu_3081_p2 = (tmp_reg_6554 | 17'd20);

assign or_ln324_1_fu_2829_p2 = (tmp_reg_6554 | 17'd2);

assign or_ln324_200_fu_5615_p2 = (tmp_reg_6554 | 17'd201);

assign or_ln324_201_fu_5629_p2 = (tmp_reg_6554 | 17'd202);

assign or_ln324_202_fu_5643_p2 = (tmp_reg_6554 | 17'd203);

assign or_ln324_203_fu_5657_p2 = (tmp_reg_6554 | 17'd204);

assign or_ln324_204_fu_5671_p2 = (tmp_reg_6554 | 17'd205);

assign or_ln324_205_fu_5685_p2 = (tmp_reg_6554 | 17'd206);

assign or_ln324_206_fu_5699_p2 = (tmp_reg_6554 | 17'd207);

assign or_ln324_207_fu_5713_p2 = (tmp_reg_6554 | 17'd208);

assign or_ln324_208_fu_5727_p2 = (tmp_reg_6554 | 17'd209);

assign or_ln324_209_fu_5741_p2 = (tmp_reg_6554 | 17'd210);

assign or_ln324_20_fu_3095_p2 = (tmp_reg_6554 | 17'd21);

assign or_ln324_210_fu_5755_p2 = (tmp_reg_6554 | 17'd211);

assign or_ln324_211_fu_5769_p2 = (tmp_reg_6554 | 17'd212);

assign or_ln324_212_fu_5783_p2 = (tmp_reg_6554 | 17'd213);

assign or_ln324_213_fu_5797_p2 = (tmp_reg_6554 | 17'd214);

assign or_ln324_214_fu_5811_p2 = (tmp_reg_6554 | 17'd215);

assign or_ln324_215_fu_5825_p2 = (tmp_reg_6554 | 17'd216);

assign or_ln324_216_fu_5839_p2 = (tmp_reg_6554 | 17'd217);

assign or_ln324_217_fu_5853_p2 = (tmp_reg_6554 | 17'd218);

assign or_ln324_218_fu_5867_p2 = (tmp_reg_6554 | 17'd219);

assign or_ln324_219_fu_5881_p2 = (tmp_reg_6554 | 17'd220);

assign or_ln324_21_fu_3109_p2 = (tmp_reg_6554 | 17'd22);

assign or_ln324_220_fu_5895_p2 = (tmp_reg_6554 | 17'd221);

assign or_ln324_221_fu_5909_p2 = (tmp_reg_6554 | 17'd222);

assign or_ln324_222_fu_5923_p2 = (tmp_reg_6554 | 17'd223);

assign or_ln324_223_fu_5937_p2 = (tmp_reg_6554 | 17'd224);

assign or_ln324_224_fu_5951_p2 = (tmp_reg_6554 | 17'd225);

assign or_ln324_225_fu_5965_p2 = (tmp_reg_6554 | 17'd226);

assign or_ln324_226_fu_5979_p2 = (tmp_reg_6554 | 17'd227);

assign or_ln324_227_fu_5993_p2 = (tmp_reg_6554 | 17'd228);

assign or_ln324_228_fu_6007_p2 = (tmp_reg_6554 | 17'd229);

assign or_ln324_229_fu_6021_p2 = (tmp_reg_6554 | 17'd230);

assign or_ln324_22_fu_3123_p2 = (tmp_reg_6554 | 17'd23);

assign or_ln324_230_fu_6035_p2 = (tmp_reg_6554 | 17'd231);

assign or_ln324_231_fu_6049_p2 = (tmp_reg_6554 | 17'd232);

assign or_ln324_232_fu_6063_p2 = (tmp_reg_6554 | 17'd233);

assign or_ln324_233_fu_6077_p2 = (tmp_reg_6554 | 17'd234);

assign or_ln324_234_fu_6091_p2 = (tmp_reg_6554 | 17'd235);

assign or_ln324_235_fu_6105_p2 = (tmp_reg_6554 | 17'd236);

assign or_ln324_236_fu_6119_p2 = (tmp_reg_6554 | 17'd237);

assign or_ln324_237_fu_6133_p2 = (tmp_reg_6554 | 17'd238);

assign or_ln324_238_fu_6147_p2 = (tmp_reg_6554 | 17'd239);

assign or_ln324_239_fu_6161_p2 = (tmp_reg_6554 | 17'd240);

assign or_ln324_23_fu_3137_p2 = (tmp_reg_6554 | 17'd24);

assign or_ln324_240_fu_6175_p2 = (tmp_reg_6554 | 17'd241);

assign or_ln324_241_fu_6189_p2 = (tmp_reg_6554 | 17'd242);

assign or_ln324_242_fu_6203_p2 = (tmp_reg_6554 | 17'd243);

assign or_ln324_243_fu_6217_p2 = (tmp_reg_6554 | 17'd244);

assign or_ln324_244_fu_6231_p2 = (tmp_reg_6554 | 17'd245);

assign or_ln324_245_fu_6245_p2 = (tmp_reg_6554 | 17'd246);

assign or_ln324_246_fu_6259_p2 = (tmp_reg_6554 | 17'd247);

assign or_ln324_247_fu_6273_p2 = (tmp_reg_6554 | 17'd248);

assign or_ln324_248_fu_6287_p2 = (tmp_reg_6554 | 17'd249);

assign or_ln324_249_fu_6301_p2 = (tmp_reg_6554 | 17'd250);

assign or_ln324_24_fu_3151_p2 = (tmp_reg_6554 | 17'd25);

assign or_ln324_250_fu_6315_p2 = (tmp_reg_6554 | 17'd251);

assign or_ln324_251_fu_6329_p2 = (tmp_reg_6554 | 17'd252);

assign or_ln324_252_fu_6343_p2 = (tmp_reg_6554 | 17'd253);

assign or_ln324_253_fu_6357_p2 = (tmp_reg_6554 | 17'd254);

assign or_ln324_254_fu_6371_p2 = (tmp_reg_6554 | 17'd255);

assign or_ln324_25_fu_3165_p2 = (tmp_reg_6554 | 17'd26);

assign or_ln324_26_fu_3179_p2 = (tmp_reg_6554 | 17'd27);

assign or_ln324_27_fu_3193_p2 = (tmp_reg_6554 | 17'd28);

assign or_ln324_28_fu_3207_p2 = (tmp_reg_6554 | 17'd29);

assign or_ln324_29_fu_3221_p2 = (tmp_reg_6554 | 17'd30);

assign or_ln324_2_fu_2843_p2 = (tmp_reg_6554 | 17'd3);

assign or_ln324_30_fu_3235_p2 = (tmp_reg_6554 | 17'd31);

assign or_ln324_31_fu_3249_p2 = (tmp_reg_6554 | 17'd32);

assign or_ln324_32_fu_3263_p2 = (tmp_reg_6554 | 17'd33);

assign or_ln324_33_fu_3277_p2 = (tmp_reg_6554 | 17'd34);

assign or_ln324_34_fu_3291_p2 = (tmp_reg_6554 | 17'd35);

assign or_ln324_35_fu_3305_p2 = (tmp_reg_6554 | 17'd36);

assign or_ln324_36_fu_3319_p2 = (tmp_reg_6554 | 17'd37);

assign or_ln324_37_fu_3333_p2 = (tmp_reg_6554 | 17'd38);

assign or_ln324_38_fu_3347_p2 = (tmp_reg_6554 | 17'd39);

assign or_ln324_39_fu_3361_p2 = (tmp_reg_6554 | 17'd40);

assign or_ln324_3_fu_2857_p2 = (tmp_reg_6554 | 17'd4);

assign or_ln324_40_fu_3375_p2 = (tmp_reg_6554 | 17'd41);

assign or_ln324_41_fu_3389_p2 = (tmp_reg_6554 | 17'd42);

assign or_ln324_42_fu_3403_p2 = (tmp_reg_6554 | 17'd43);

assign or_ln324_43_fu_3417_p2 = (tmp_reg_6554 | 17'd44);

assign or_ln324_44_fu_3431_p2 = (tmp_reg_6554 | 17'd45);

assign or_ln324_45_fu_3445_p2 = (tmp_reg_6554 | 17'd46);

assign or_ln324_46_fu_3459_p2 = (tmp_reg_6554 | 17'd47);

assign or_ln324_47_fu_3473_p2 = (tmp_reg_6554 | 17'd48);

assign or_ln324_48_fu_3487_p2 = (tmp_reg_6554 | 17'd49);

assign or_ln324_49_fu_3501_p2 = (tmp_reg_6554 | 17'd50);

assign or_ln324_4_fu_2871_p2 = (tmp_reg_6554 | 17'd5);

assign or_ln324_50_fu_3515_p2 = (tmp_reg_6554 | 17'd51);

assign or_ln324_51_fu_3529_p2 = (tmp_reg_6554 | 17'd52);

assign or_ln324_52_fu_3543_p2 = (tmp_reg_6554 | 17'd53);

assign or_ln324_53_fu_3557_p2 = (tmp_reg_6554 | 17'd54);

assign or_ln324_54_fu_3571_p2 = (tmp_reg_6554 | 17'd55);

assign or_ln324_55_fu_3585_p2 = (tmp_reg_6554 | 17'd56);

assign or_ln324_56_fu_3599_p2 = (tmp_reg_6554 | 17'd57);

assign or_ln324_57_fu_3613_p2 = (tmp_reg_6554 | 17'd58);

assign or_ln324_58_fu_3627_p2 = (tmp_reg_6554 | 17'd59);

assign or_ln324_59_fu_3641_p2 = (tmp_reg_6554 | 17'd60);

assign or_ln324_5_fu_2885_p2 = (tmp_reg_6554 | 17'd6);

assign or_ln324_60_fu_3655_p2 = (tmp_reg_6554 | 17'd61);

assign or_ln324_61_fu_3669_p2 = (tmp_reg_6554 | 17'd62);

assign or_ln324_62_fu_3683_p2 = (tmp_reg_6554 | 17'd63);

assign or_ln324_63_fu_3697_p2 = (tmp_reg_6554 | 17'd64);

assign or_ln324_64_fu_3711_p2 = (tmp_reg_6554 | 17'd65);

assign or_ln324_65_fu_3725_p2 = (tmp_reg_6554 | 17'd66);

assign or_ln324_66_fu_3739_p2 = (tmp_reg_6554 | 17'd67);

assign or_ln324_67_fu_3753_p2 = (tmp_reg_6554 | 17'd68);

assign or_ln324_68_fu_3767_p2 = (tmp_reg_6554 | 17'd69);

assign or_ln324_69_fu_3781_p2 = (tmp_reg_6554 | 17'd70);

assign or_ln324_6_fu_2899_p2 = (tmp_reg_6554 | 17'd7);

assign or_ln324_70_fu_3795_p2 = (tmp_reg_6554 | 17'd71);

assign or_ln324_71_fu_3809_p2 = (tmp_reg_6554 | 17'd72);

assign or_ln324_72_fu_3823_p2 = (tmp_reg_6554 | 17'd73);

assign or_ln324_73_fu_3837_p2 = (tmp_reg_6554 | 17'd74);

assign or_ln324_74_fu_3851_p2 = (tmp_reg_6554 | 17'd75);

assign or_ln324_75_fu_3865_p2 = (tmp_reg_6554 | 17'd76);

assign or_ln324_76_fu_3879_p2 = (tmp_reg_6554 | 17'd77);

assign or_ln324_77_fu_3893_p2 = (tmp_reg_6554 | 17'd78);

assign or_ln324_78_fu_3907_p2 = (tmp_reg_6554 | 17'd79);

assign or_ln324_79_fu_3921_p2 = (tmp_reg_6554 | 17'd80);

assign or_ln324_7_fu_2913_p2 = (tmp_reg_6554 | 17'd8);

assign or_ln324_80_fu_3935_p2 = (tmp_reg_6554 | 17'd81);

assign or_ln324_81_fu_3949_p2 = (tmp_reg_6554 | 17'd82);

assign or_ln324_82_fu_3963_p2 = (tmp_reg_6554 | 17'd83);

assign or_ln324_83_fu_3977_p2 = (tmp_reg_6554 | 17'd84);

assign or_ln324_84_fu_3991_p2 = (tmp_reg_6554 | 17'd85);

assign or_ln324_85_fu_4005_p2 = (tmp_reg_6554 | 17'd86);

assign or_ln324_86_fu_4019_p2 = (tmp_reg_6554 | 17'd87);

assign or_ln324_87_fu_4033_p2 = (tmp_reg_6554 | 17'd88);

assign or_ln324_88_fu_4047_p2 = (tmp_reg_6554 | 17'd89);

assign or_ln324_89_fu_4061_p2 = (tmp_reg_6554 | 17'd90);

assign or_ln324_8_fu_2927_p2 = (tmp_reg_6554 | 17'd9);

assign or_ln324_90_fu_4075_p2 = (tmp_reg_6554 | 17'd91);

assign or_ln324_91_fu_4089_p2 = (tmp_reg_6554 | 17'd92);

assign or_ln324_92_fu_4103_p2 = (tmp_reg_6554 | 17'd93);

assign or_ln324_93_fu_4117_p2 = (tmp_reg_6554 | 17'd94);

assign or_ln324_94_fu_4131_p2 = (tmp_reg_6554 | 17'd95);

assign or_ln324_95_fu_4145_p2 = (tmp_reg_6554 | 17'd96);

assign or_ln324_96_fu_4159_p2 = (tmp_reg_6554 | 17'd97);

assign or_ln324_97_fu_4173_p2 = (tmp_reg_6554 | 17'd98);

assign or_ln324_98_fu_4187_p2 = (tmp_reg_6554 | 17'd99);

assign or_ln324_99_fu_4201_p2 = (tmp_reg_6554 | 17'd100);

assign or_ln324_9_fu_2941_p2 = (tmp_reg_6554 | 17'd10);

assign or_ln324_fu_2814_p2 = (tmp_fu_2801_p3 | 17'd1);

assign p_Result_s_fu_6494_p5 = {{{{{{8'd0}, {pixels_color_V_q0}}}, {pixels_y_V_q0}}}, {pixels_x_V_q0}};

assign select_ln480_fu_6518_p3 = ((icmp_ln874_1_fu_6512_p2[0:0] === 1'b1) ? 16'd0 : add_ln695_3_fu_6507_p2);

assign tmp_100_fu_4220_p3 = {{47'd0}, {or_ln324_100_fu_4215_p2}};

assign tmp_101_fu_4234_p3 = {{47'd0}, {or_ln324_101_fu_4229_p2}};

assign tmp_102_fu_4248_p3 = {{47'd0}, {or_ln324_102_fu_4243_p2}};

assign tmp_103_fu_4262_p3 = {{47'd0}, {or_ln324_103_fu_4257_p2}};

assign tmp_104_fu_4276_p3 = {{47'd0}, {or_ln324_104_fu_4271_p2}};

assign tmp_105_fu_4290_p3 = {{47'd0}, {or_ln324_105_fu_4285_p2}};

assign tmp_106_fu_4304_p3 = {{47'd0}, {or_ln324_106_fu_4299_p2}};

assign tmp_107_fu_4318_p3 = {{47'd0}, {or_ln324_107_fu_4313_p2}};

assign tmp_108_fu_4332_p3 = {{47'd0}, {or_ln324_108_fu_4327_p2}};

assign tmp_109_fu_4346_p3 = {{47'd0}, {or_ln324_109_fu_4341_p2}};

assign tmp_10_fu_2960_p3 = {{47'd0}, {or_ln324_10_fu_2955_p2}};

assign tmp_110_fu_4360_p3 = {{47'd0}, {or_ln324_110_fu_4355_p2}};

assign tmp_111_fu_4374_p3 = {{47'd0}, {or_ln324_111_fu_4369_p2}};

assign tmp_112_fu_4388_p3 = {{47'd0}, {or_ln324_112_fu_4383_p2}};

assign tmp_113_fu_4402_p3 = {{47'd0}, {or_ln324_113_fu_4397_p2}};

assign tmp_114_fu_4416_p3 = {{47'd0}, {or_ln324_114_fu_4411_p2}};

assign tmp_115_fu_4430_p3 = {{47'd0}, {or_ln324_115_fu_4425_p2}};

assign tmp_116_fu_4444_p3 = {{47'd0}, {or_ln324_116_fu_4439_p2}};

assign tmp_117_fu_4458_p3 = {{47'd0}, {or_ln324_117_fu_4453_p2}};

assign tmp_118_fu_4472_p3 = {{47'd0}, {or_ln324_118_fu_4467_p2}};

assign tmp_119_fu_4486_p3 = {{47'd0}, {or_ln324_119_fu_4481_p2}};

assign tmp_11_fu_2974_p3 = {{47'd0}, {or_ln324_11_fu_2969_p2}};

assign tmp_120_fu_4500_p3 = {{47'd0}, {or_ln324_120_fu_4495_p2}};

assign tmp_121_fu_4514_p3 = {{47'd0}, {or_ln324_121_fu_4509_p2}};

assign tmp_122_fu_4528_p3 = {{47'd0}, {or_ln324_122_fu_4523_p2}};

assign tmp_123_fu_4542_p3 = {{47'd0}, {or_ln324_123_fu_4537_p2}};

assign tmp_124_fu_4556_p3 = {{47'd0}, {or_ln324_124_fu_4551_p2}};

assign tmp_125_fu_4570_p3 = {{47'd0}, {or_ln324_125_fu_4565_p2}};

assign tmp_126_fu_4584_p3 = {{47'd0}, {or_ln324_126_fu_4579_p2}};

assign tmp_127_fu_4598_p3 = {{47'd0}, {or_ln324_127_fu_4593_p2}};

assign tmp_128_fu_4612_p3 = {{47'd0}, {or_ln324_128_fu_4607_p2}};

assign tmp_129_fu_4626_p3 = {{47'd0}, {or_ln324_129_fu_4621_p2}};

assign tmp_12_fu_2988_p3 = {{47'd0}, {or_ln324_12_fu_2983_p2}};

assign tmp_130_fu_4640_p3 = {{47'd0}, {or_ln324_130_fu_4635_p2}};

assign tmp_131_fu_4654_p3 = {{47'd0}, {or_ln324_131_fu_4649_p2}};

assign tmp_132_fu_4668_p3 = {{47'd0}, {or_ln324_132_fu_4663_p2}};

assign tmp_133_fu_4682_p3 = {{47'd0}, {or_ln324_133_fu_4677_p2}};

assign tmp_134_fu_4696_p3 = {{47'd0}, {or_ln324_134_fu_4691_p2}};

assign tmp_135_fu_4710_p3 = {{47'd0}, {or_ln324_135_fu_4705_p2}};

assign tmp_136_fu_4724_p3 = {{47'd0}, {or_ln324_136_fu_4719_p2}};

assign tmp_137_fu_4738_p3 = {{47'd0}, {or_ln324_137_fu_4733_p2}};

assign tmp_138_fu_4752_p3 = {{47'd0}, {or_ln324_138_fu_4747_p2}};

assign tmp_139_fu_4766_p3 = {{47'd0}, {or_ln324_139_fu_4761_p2}};

assign tmp_13_fu_3002_p3 = {{47'd0}, {or_ln324_13_fu_2997_p2}};

assign tmp_140_fu_4780_p3 = {{47'd0}, {or_ln324_140_fu_4775_p2}};

assign tmp_141_fu_4794_p3 = {{47'd0}, {or_ln324_141_fu_4789_p2}};

assign tmp_142_fu_4808_p3 = {{47'd0}, {or_ln324_142_fu_4803_p2}};

assign tmp_143_fu_4822_p3 = {{47'd0}, {or_ln324_143_fu_4817_p2}};

assign tmp_144_fu_4836_p3 = {{47'd0}, {or_ln324_144_fu_4831_p2}};

assign tmp_145_fu_4850_p3 = {{47'd0}, {or_ln324_145_fu_4845_p2}};

assign tmp_146_fu_4864_p3 = {{47'd0}, {or_ln324_146_fu_4859_p2}};

assign tmp_147_fu_4878_p3 = {{47'd0}, {or_ln324_147_fu_4873_p2}};

assign tmp_148_fu_4892_p3 = {{47'd0}, {or_ln324_148_fu_4887_p2}};

assign tmp_149_fu_4906_p3 = {{47'd0}, {or_ln324_149_fu_4901_p2}};

assign tmp_14_fu_3016_p3 = {{47'd0}, {or_ln324_14_fu_3011_p2}};

assign tmp_150_fu_4920_p3 = {{47'd0}, {or_ln324_150_fu_4915_p2}};

assign tmp_151_fu_4934_p3 = {{47'd0}, {or_ln324_151_fu_4929_p2}};

assign tmp_152_fu_4948_p3 = {{47'd0}, {or_ln324_152_fu_4943_p2}};

assign tmp_153_fu_4962_p3 = {{47'd0}, {or_ln324_153_fu_4957_p2}};

assign tmp_154_fu_4976_p3 = {{47'd0}, {or_ln324_154_fu_4971_p2}};

assign tmp_155_fu_4990_p3 = {{47'd0}, {or_ln324_155_fu_4985_p2}};

assign tmp_156_fu_5004_p3 = {{47'd0}, {or_ln324_156_fu_4999_p2}};

assign tmp_157_fu_5018_p3 = {{47'd0}, {or_ln324_157_fu_5013_p2}};

assign tmp_158_fu_5032_p3 = {{47'd0}, {or_ln324_158_fu_5027_p2}};

assign tmp_159_fu_5046_p3 = {{47'd0}, {or_ln324_159_fu_5041_p2}};

assign tmp_15_fu_3030_p3 = {{47'd0}, {or_ln324_15_fu_3025_p2}};

assign tmp_160_fu_5060_p3 = {{47'd0}, {or_ln324_160_fu_5055_p2}};

assign tmp_161_fu_5074_p3 = {{47'd0}, {or_ln324_161_fu_5069_p2}};

assign tmp_162_fu_5088_p3 = {{47'd0}, {or_ln324_162_fu_5083_p2}};

assign tmp_163_fu_5102_p3 = {{47'd0}, {or_ln324_163_fu_5097_p2}};

assign tmp_164_fu_5116_p3 = {{47'd0}, {or_ln324_164_fu_5111_p2}};

assign tmp_165_fu_5130_p3 = {{47'd0}, {or_ln324_165_fu_5125_p2}};

assign tmp_166_fu_5144_p3 = {{47'd0}, {or_ln324_166_fu_5139_p2}};

assign tmp_167_fu_5158_p3 = {{47'd0}, {or_ln324_167_fu_5153_p2}};

assign tmp_168_fu_5172_p3 = {{47'd0}, {or_ln324_168_fu_5167_p2}};

assign tmp_169_fu_5186_p3 = {{47'd0}, {or_ln324_169_fu_5181_p2}};

assign tmp_16_fu_3044_p3 = {{47'd0}, {or_ln324_16_fu_3039_p2}};

assign tmp_170_fu_5200_p3 = {{47'd0}, {or_ln324_170_fu_5195_p2}};

assign tmp_171_fu_5214_p3 = {{47'd0}, {or_ln324_171_fu_5209_p2}};

assign tmp_172_fu_5228_p3 = {{47'd0}, {or_ln324_172_fu_5223_p2}};

assign tmp_173_fu_5242_p3 = {{47'd0}, {or_ln324_173_fu_5237_p2}};

assign tmp_174_fu_5256_p3 = {{47'd0}, {or_ln324_174_fu_5251_p2}};

assign tmp_175_fu_5270_p3 = {{47'd0}, {or_ln324_175_fu_5265_p2}};

assign tmp_176_fu_5284_p3 = {{47'd0}, {or_ln324_176_fu_5279_p2}};

assign tmp_177_fu_5298_p3 = {{47'd0}, {or_ln324_177_fu_5293_p2}};

assign tmp_178_fu_5312_p3 = {{47'd0}, {or_ln324_178_fu_5307_p2}};

assign tmp_179_fu_5326_p3 = {{47'd0}, {or_ln324_179_fu_5321_p2}};

assign tmp_17_fu_3058_p3 = {{47'd0}, {or_ln324_17_fu_3053_p2}};

assign tmp_180_fu_5340_p3 = {{47'd0}, {or_ln324_180_fu_5335_p2}};

assign tmp_181_fu_5354_p3 = {{47'd0}, {or_ln324_181_fu_5349_p2}};

assign tmp_182_fu_5368_p3 = {{47'd0}, {or_ln324_182_fu_5363_p2}};

assign tmp_183_fu_5382_p3 = {{47'd0}, {or_ln324_183_fu_5377_p2}};

assign tmp_184_fu_5396_p3 = {{47'd0}, {or_ln324_184_fu_5391_p2}};

assign tmp_185_fu_5410_p3 = {{47'd0}, {or_ln324_185_fu_5405_p2}};

assign tmp_186_fu_5424_p3 = {{47'd0}, {or_ln324_186_fu_5419_p2}};

assign tmp_187_fu_5438_p3 = {{47'd0}, {or_ln324_187_fu_5433_p2}};

assign tmp_188_fu_5452_p3 = {{47'd0}, {or_ln324_188_fu_5447_p2}};

assign tmp_189_fu_5466_p3 = {{47'd0}, {or_ln324_189_fu_5461_p2}};

assign tmp_18_fu_3072_p3 = {{47'd0}, {or_ln324_18_fu_3067_p2}};

assign tmp_190_fu_5480_p3 = {{47'd0}, {or_ln324_190_fu_5475_p2}};

assign tmp_191_fu_5494_p3 = {{47'd0}, {or_ln324_191_fu_5489_p2}};

assign tmp_192_fu_5508_p3 = {{47'd0}, {or_ln324_192_fu_5503_p2}};

assign tmp_193_fu_5522_p3 = {{47'd0}, {or_ln324_193_fu_5517_p2}};

assign tmp_194_fu_5536_p3 = {{47'd0}, {or_ln324_194_fu_5531_p2}};

assign tmp_195_fu_5550_p3 = {{47'd0}, {or_ln324_195_fu_5545_p2}};

assign tmp_196_fu_5564_p3 = {{47'd0}, {or_ln324_196_fu_5559_p2}};

assign tmp_197_fu_5578_p3 = {{47'd0}, {or_ln324_197_fu_5573_p2}};

assign tmp_198_fu_5592_p3 = {{47'd0}, {or_ln324_198_fu_5587_p2}};

assign tmp_199_fu_5606_p3 = {{47'd0}, {or_ln324_199_fu_5601_p2}};

assign tmp_19_fu_3086_p3 = {{47'd0}, {or_ln324_19_fu_3081_p2}};

assign tmp_1_fu_2820_p3 = {{47'd0}, {or_ln324_fu_2814_p2}};

assign tmp_200_fu_5620_p3 = {{47'd0}, {or_ln324_200_fu_5615_p2}};

assign tmp_201_fu_5634_p3 = {{47'd0}, {or_ln324_201_fu_5629_p2}};

assign tmp_202_fu_5648_p3 = {{47'd0}, {or_ln324_202_fu_5643_p2}};

assign tmp_203_fu_5662_p3 = {{47'd0}, {or_ln324_203_fu_5657_p2}};

assign tmp_204_fu_5676_p3 = {{47'd0}, {or_ln324_204_fu_5671_p2}};

assign tmp_205_fu_5690_p3 = {{47'd0}, {or_ln324_205_fu_5685_p2}};

assign tmp_206_fu_5704_p3 = {{47'd0}, {or_ln324_206_fu_5699_p2}};

assign tmp_207_fu_5718_p3 = {{47'd0}, {or_ln324_207_fu_5713_p2}};

assign tmp_208_fu_5732_p3 = {{47'd0}, {or_ln324_208_fu_5727_p2}};

assign tmp_209_fu_5746_p3 = {{47'd0}, {or_ln324_209_fu_5741_p2}};

assign tmp_20_fu_3100_p3 = {{47'd0}, {or_ln324_20_fu_3095_p2}};

assign tmp_210_fu_5760_p3 = {{47'd0}, {or_ln324_210_fu_5755_p2}};

assign tmp_211_fu_5774_p3 = {{47'd0}, {or_ln324_211_fu_5769_p2}};

assign tmp_212_fu_5788_p3 = {{47'd0}, {or_ln324_212_fu_5783_p2}};

assign tmp_213_fu_5802_p3 = {{47'd0}, {or_ln324_213_fu_5797_p2}};

assign tmp_214_fu_5816_p3 = {{47'd0}, {or_ln324_214_fu_5811_p2}};

assign tmp_215_fu_5830_p3 = {{47'd0}, {or_ln324_215_fu_5825_p2}};

assign tmp_216_fu_5844_p3 = {{47'd0}, {or_ln324_216_fu_5839_p2}};

assign tmp_217_fu_5858_p3 = {{47'd0}, {or_ln324_217_fu_5853_p2}};

assign tmp_218_fu_5872_p3 = {{47'd0}, {or_ln324_218_fu_5867_p2}};

assign tmp_219_fu_5886_p3 = {{47'd0}, {or_ln324_219_fu_5881_p2}};

assign tmp_21_fu_3114_p3 = {{47'd0}, {or_ln324_21_fu_3109_p2}};

assign tmp_220_fu_5900_p3 = {{47'd0}, {or_ln324_220_fu_5895_p2}};

assign tmp_221_fu_5914_p3 = {{47'd0}, {or_ln324_221_fu_5909_p2}};

assign tmp_222_fu_5928_p3 = {{47'd0}, {or_ln324_222_fu_5923_p2}};

assign tmp_223_fu_5942_p3 = {{47'd0}, {or_ln324_223_fu_5937_p2}};

assign tmp_224_fu_5956_p3 = {{47'd0}, {or_ln324_224_fu_5951_p2}};

assign tmp_225_fu_5970_p3 = {{47'd0}, {or_ln324_225_fu_5965_p2}};

assign tmp_226_fu_5984_p3 = {{47'd0}, {or_ln324_226_fu_5979_p2}};

assign tmp_227_fu_5998_p3 = {{47'd0}, {or_ln324_227_fu_5993_p2}};

assign tmp_228_fu_6012_p3 = {{47'd0}, {or_ln324_228_fu_6007_p2}};

assign tmp_229_fu_6026_p3 = {{47'd0}, {or_ln324_229_fu_6021_p2}};

assign tmp_22_fu_3128_p3 = {{47'd0}, {or_ln324_22_fu_3123_p2}};

assign tmp_230_fu_6040_p3 = {{47'd0}, {or_ln324_230_fu_6035_p2}};

assign tmp_231_fu_6054_p3 = {{47'd0}, {or_ln324_231_fu_6049_p2}};

assign tmp_232_fu_6068_p3 = {{47'd0}, {or_ln324_232_fu_6063_p2}};

assign tmp_233_fu_6082_p3 = {{47'd0}, {or_ln324_233_fu_6077_p2}};

assign tmp_234_fu_6096_p3 = {{47'd0}, {or_ln324_234_fu_6091_p2}};

assign tmp_235_fu_6110_p3 = {{47'd0}, {or_ln324_235_fu_6105_p2}};

assign tmp_236_fu_6124_p3 = {{47'd0}, {or_ln324_236_fu_6119_p2}};

assign tmp_237_fu_6138_p3 = {{47'd0}, {or_ln324_237_fu_6133_p2}};

assign tmp_238_fu_6152_p3 = {{47'd0}, {or_ln324_238_fu_6147_p2}};

assign tmp_239_fu_6166_p3 = {{47'd0}, {or_ln324_239_fu_6161_p2}};

assign tmp_23_fu_3142_p3 = {{47'd0}, {or_ln324_23_fu_3137_p2}};

assign tmp_240_fu_6180_p3 = {{47'd0}, {or_ln324_240_fu_6175_p2}};

assign tmp_241_fu_6194_p3 = {{47'd0}, {or_ln324_241_fu_6189_p2}};

assign tmp_242_fu_6208_p3 = {{47'd0}, {or_ln324_242_fu_6203_p2}};

assign tmp_243_fu_6222_p3 = {{47'd0}, {or_ln324_243_fu_6217_p2}};

assign tmp_244_fu_6236_p3 = {{47'd0}, {or_ln324_244_fu_6231_p2}};

assign tmp_245_fu_6250_p3 = {{47'd0}, {or_ln324_245_fu_6245_p2}};

assign tmp_246_fu_6264_p3 = {{47'd0}, {or_ln324_246_fu_6259_p2}};

assign tmp_247_fu_6278_p3 = {{47'd0}, {or_ln324_247_fu_6273_p2}};

assign tmp_248_fu_6292_p3 = {{47'd0}, {or_ln324_248_fu_6287_p2}};

assign tmp_249_fu_6306_p3 = {{47'd0}, {or_ln324_249_fu_6301_p2}};

assign tmp_24_fu_3156_p3 = {{47'd0}, {or_ln324_24_fu_3151_p2}};

assign tmp_250_fu_6320_p3 = {{47'd0}, {or_ln324_250_fu_6315_p2}};

assign tmp_251_fu_6334_p3 = {{47'd0}, {or_ln324_251_fu_6329_p2}};

assign tmp_252_fu_6348_p3 = {{47'd0}, {or_ln324_252_fu_6343_p2}};

assign tmp_253_fu_6362_p3 = {{47'd0}, {or_ln324_253_fu_6357_p2}};

assign tmp_254_fu_6376_p3 = {{47'd0}, {or_ln324_254_fu_6371_p2}};

assign tmp_25_fu_3170_p3 = {{47'd0}, {or_ln324_25_fu_3165_p2}};

assign tmp_26_fu_3184_p3 = {{47'd0}, {or_ln324_26_fu_3179_p2}};

assign tmp_27_fu_3198_p3 = {{47'd0}, {or_ln324_27_fu_3193_p2}};

assign tmp_28_fu_3212_p3 = {{47'd0}, {or_ln324_28_fu_3207_p2}};

assign tmp_29_fu_3226_p3 = {{47'd0}, {or_ln324_29_fu_3221_p2}};

assign tmp_2_fu_2834_p3 = {{47'd0}, {or_ln324_1_fu_2829_p2}};

assign tmp_30_fu_3240_p3 = {{47'd0}, {or_ln324_30_fu_3235_p2}};

assign tmp_31_fu_3254_p3 = {{47'd0}, {or_ln324_31_fu_3249_p2}};

assign tmp_32_fu_3268_p3 = {{47'd0}, {or_ln324_32_fu_3263_p2}};

assign tmp_33_fu_3282_p3 = {{47'd0}, {or_ln324_33_fu_3277_p2}};

assign tmp_34_fu_3296_p3 = {{47'd0}, {or_ln324_34_fu_3291_p2}};

assign tmp_35_fu_3310_p3 = {{47'd0}, {or_ln324_35_fu_3305_p2}};

assign tmp_36_fu_3324_p3 = {{47'd0}, {or_ln324_36_fu_3319_p2}};

assign tmp_37_fu_3338_p3 = {{47'd0}, {or_ln324_37_fu_3333_p2}};

assign tmp_38_fu_3352_p3 = {{47'd0}, {or_ln324_38_fu_3347_p2}};

assign tmp_39_fu_3366_p3 = {{47'd0}, {or_ln324_39_fu_3361_p2}};

assign tmp_3_fu_2848_p3 = {{47'd0}, {or_ln324_2_fu_2843_p2}};

assign tmp_40_fu_3380_p3 = {{47'd0}, {or_ln324_40_fu_3375_p2}};

assign tmp_41_fu_3394_p3 = {{47'd0}, {or_ln324_41_fu_3389_p2}};

assign tmp_42_fu_3408_p3 = {{47'd0}, {or_ln324_42_fu_3403_p2}};

assign tmp_43_fu_3422_p3 = {{47'd0}, {or_ln324_43_fu_3417_p2}};

assign tmp_44_fu_3436_p3 = {{47'd0}, {or_ln324_44_fu_3431_p2}};

assign tmp_45_fu_3450_p3 = {{47'd0}, {or_ln324_45_fu_3445_p2}};

assign tmp_46_fu_3464_p3 = {{47'd0}, {or_ln324_46_fu_3459_p2}};

assign tmp_47_fu_3478_p3 = {{47'd0}, {or_ln324_47_fu_3473_p2}};

assign tmp_48_fu_3492_p3 = {{47'd0}, {or_ln324_48_fu_3487_p2}};

assign tmp_49_fu_3506_p3 = {{47'd0}, {or_ln324_49_fu_3501_p2}};

assign tmp_4_fu_2862_p3 = {{47'd0}, {or_ln324_3_fu_2857_p2}};

assign tmp_50_fu_3520_p3 = {{47'd0}, {or_ln324_50_fu_3515_p2}};

assign tmp_51_fu_3534_p3 = {{47'd0}, {or_ln324_51_fu_3529_p2}};

assign tmp_52_fu_3548_p3 = {{47'd0}, {or_ln324_52_fu_3543_p2}};

assign tmp_53_fu_3562_p3 = {{47'd0}, {or_ln324_53_fu_3557_p2}};

assign tmp_54_fu_3576_p3 = {{47'd0}, {or_ln324_54_fu_3571_p2}};

assign tmp_55_fu_3590_p3 = {{47'd0}, {or_ln324_55_fu_3585_p2}};

assign tmp_56_fu_3604_p3 = {{47'd0}, {or_ln324_56_fu_3599_p2}};

assign tmp_57_fu_3618_p3 = {{47'd0}, {or_ln324_57_fu_3613_p2}};

assign tmp_58_fu_3632_p3 = {{47'd0}, {or_ln324_58_fu_3627_p2}};

assign tmp_59_fu_3646_p3 = {{47'd0}, {or_ln324_59_fu_3641_p2}};

assign tmp_5_fu_2876_p3 = {{47'd0}, {or_ln324_4_fu_2871_p2}};

assign tmp_60_fu_3660_p3 = {{47'd0}, {or_ln324_60_fu_3655_p2}};

assign tmp_61_fu_3674_p3 = {{47'd0}, {or_ln324_61_fu_3669_p2}};

assign tmp_62_fu_3688_p3 = {{47'd0}, {or_ln324_62_fu_3683_p2}};

assign tmp_63_fu_3702_p3 = {{47'd0}, {or_ln324_63_fu_3697_p2}};

assign tmp_64_fu_3716_p3 = {{47'd0}, {or_ln324_64_fu_3711_p2}};

assign tmp_65_fu_3730_p3 = {{47'd0}, {or_ln324_65_fu_3725_p2}};

assign tmp_66_fu_3744_p3 = {{47'd0}, {or_ln324_66_fu_3739_p2}};

assign tmp_67_fu_3758_p3 = {{47'd0}, {or_ln324_67_fu_3753_p2}};

assign tmp_68_fu_3772_p3 = {{47'd0}, {or_ln324_68_fu_3767_p2}};

assign tmp_69_fu_3786_p3 = {{47'd0}, {or_ln324_69_fu_3781_p2}};

assign tmp_6_fu_2890_p3 = {{47'd0}, {or_ln324_5_fu_2885_p2}};

assign tmp_70_fu_3800_p3 = {{47'd0}, {or_ln324_70_fu_3795_p2}};

assign tmp_71_fu_3814_p3 = {{47'd0}, {or_ln324_71_fu_3809_p2}};

assign tmp_72_fu_3828_p3 = {{47'd0}, {or_ln324_72_fu_3823_p2}};

assign tmp_73_fu_3842_p3 = {{47'd0}, {or_ln324_73_fu_3837_p2}};

assign tmp_74_fu_3856_p3 = {{47'd0}, {or_ln324_74_fu_3851_p2}};

assign tmp_75_fu_3870_p3 = {{47'd0}, {or_ln324_75_fu_3865_p2}};

assign tmp_76_fu_3884_p3 = {{47'd0}, {or_ln324_76_fu_3879_p2}};

assign tmp_77_fu_3898_p3 = {{47'd0}, {or_ln324_77_fu_3893_p2}};

assign tmp_78_fu_3912_p3 = {{47'd0}, {or_ln324_78_fu_3907_p2}};

assign tmp_79_fu_3926_p3 = {{47'd0}, {or_ln324_79_fu_3921_p2}};

assign tmp_7_fu_2904_p3 = {{47'd0}, {or_ln324_6_fu_2899_p2}};

assign tmp_80_fu_3940_p3 = {{47'd0}, {or_ln324_80_fu_3935_p2}};

assign tmp_81_fu_3954_p3 = {{47'd0}, {or_ln324_81_fu_3949_p2}};

assign tmp_82_fu_3968_p3 = {{47'd0}, {or_ln324_82_fu_3963_p2}};

assign tmp_83_fu_3982_p3 = {{47'd0}, {or_ln324_83_fu_3977_p2}};

assign tmp_84_fu_3996_p3 = {{47'd0}, {or_ln324_84_fu_3991_p2}};

assign tmp_85_fu_4010_p3 = {{47'd0}, {or_ln324_85_fu_4005_p2}};

assign tmp_86_fu_4024_p3 = {{47'd0}, {or_ln324_86_fu_4019_p2}};

assign tmp_87_fu_4038_p3 = {{47'd0}, {or_ln324_87_fu_4033_p2}};

assign tmp_88_fu_4052_p3 = {{47'd0}, {or_ln324_88_fu_4047_p2}};

assign tmp_89_fu_4066_p3 = {{47'd0}, {or_ln324_89_fu_4061_p2}};

assign tmp_8_fu_2918_p3 = {{47'd0}, {or_ln324_7_fu_2913_p2}};

assign tmp_90_fu_4080_p3 = {{47'd0}, {or_ln324_90_fu_4075_p2}};

assign tmp_91_fu_4094_p3 = {{47'd0}, {or_ln324_91_fu_4089_p2}};

assign tmp_92_fu_4108_p3 = {{47'd0}, {or_ln324_92_fu_4103_p2}};

assign tmp_93_fu_4122_p3 = {{47'd0}, {or_ln324_93_fu_4117_p2}};

assign tmp_94_fu_4136_p3 = {{47'd0}, {or_ln324_94_fu_4131_p2}};

assign tmp_95_fu_4150_p3 = {{47'd0}, {or_ln324_95_fu_4145_p2}};

assign tmp_96_fu_4164_p3 = {{47'd0}, {or_ln324_96_fu_4159_p2}};

assign tmp_97_fu_4178_p3 = {{47'd0}, {or_ln324_97_fu_4173_p2}};

assign tmp_98_fu_4192_p3 = {{47'd0}, {or_ln324_98_fu_4187_p2}};

assign tmp_99_fu_4206_p3 = {{47'd0}, {or_ln324_99_fu_4201_p2}};

assign tmp_9_fu_2932_p3 = {{47'd0}, {or_ln324_8_fu_2927_p2}};

assign tmp_fu_2801_p3 = {{empty_reg_2743}, {8'd0}};

assign tmp_s_fu_2946_p3 = {{47'd0}, {or_ln324_9_fu_2941_p2}};

assign trunc_ln674_fu_6404_p1 = Input_1_dout[7:0];

assign trunc_ln882_fu_6438_p1 = Input_1_dout[15:0];

assign zext_ln211_fu_6470_p1 = pixel_cntr_V_fu_602;

assign zext_ln324_fu_2809_p1 = tmp_fu_2801_p3;

assign zext_ln538_fu_6452_p1 = pixel_cntr_V_fu_602;

assign zext_ln882_1_fu_6442_p1 = trunc_ln882_fu_6438_p1;

assign zext_ln882_fu_6487_p1 = j_reg_2765;

always @ (posedge ap_clk) begin
    tmp_reg_6554[7:0] <= 8'b00000000;
end

endmodule //rendering_m_zculling_top
// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.1 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
`timescale 1 ns / 1 ps
module rendering_m_zculling_top_z_buffer_V_ram (addr0, ce0, d0, we0, addr1, ce1, d1, we1, q1,  clk);

parameter DWIDTH = 8;
parameter AWIDTH = 16;
parameter MEM_SIZE = 65536;

input[AWIDTH-1:0] addr0;
input ce0;
input[DWIDTH-1:0] d0;
input we0;
input[AWIDTH-1:0] addr1;
input ce1;
input[DWIDTH-1:0] d1;
input we1;
output reg[DWIDTH-1:0] q1;
input clk;

(* ram_style = "block" *)reg [DWIDTH-1:0] ram[0:MEM_SIZE-1];

initial begin
    $readmemh("./rendering_m_zculling_top_z_buffer_V_ram.dat", ram);
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
        q1 <= ram[addr1];
    end
end


endmodule

`timescale 1 ns / 1 ps
module rendering_m_zculling_top_z_buffer_V(
    reset,
    clk,
    address0,
    ce0,
    we0,
    d0,
    address1,
    ce1,
    we1,
    d1,
    q1);

parameter DataWidth = 32'd8;
parameter AddressRange = 32'd65536;
parameter AddressWidth = 32'd16;
input reset;
input clk;
input[AddressWidth - 1:0] address0;
input ce0;
input we0;
input[DataWidth - 1:0] d0;
input[AddressWidth - 1:0] address1;
input ce1;
input we1;
input[DataWidth - 1:0] d1;
output[DataWidth - 1:0] q1;



rendering_m_zculling_top_z_buffer_V_ram rendering_m_zculling_top_z_buffer_V_ram_U(
    .clk( clk ),
    .addr0( address0 ),
    .ce0( ce0 ),
    .we0( we0 ),
    .d0( d0 ),
    .addr1( address1 ),
    .ce1( ce1 ),
    .we1( we1 ),
    .d1( d1 ),
    .q1( q1 ));

endmodule

