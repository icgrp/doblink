`timescale 1ns / 1ps

// NUM_LEAF_BITS + NUM_PORT_BITS + NUM_ADDR_BITS == ADDR_TOTAL
// NUM_BRAM_ADDR_BITS =< NUM_ADDR_BITS
// NUM_BRAM_ADDR_BITS = NUM_BRAM_ADDR_BITS + NUM_ADDR_REMAINDER_BITS
// port values == 0,1 reserved for initialization packets
// in thise case, port values == 2,3,4,5,6,7,8 are BRAM_IN
// port values == 9,10,11,12,13,14,15 are BRAM_OUT


module leaf_interface #(
    
    parameter PACKET_BITS = 49,
    parameter PAYLOAD_BITS = 32, 
    parameter NUM_LEAF_BITS = 3,
    parameter NUM_PORT_BITS = 4,
    parameter NUM_ADDR_BITS = 7,
    parameter NUM_IN_PORTS = 1, 
    parameter NUM_OUT_PORTS = 1,
    parameter NUM_BRAM_ADDR_BITS = 7,
    parameter FREESPACE_UPDATE_SIZE = 64,
    localparam OUT_PORTS_REG_BITS = NUM_LEAF_BITS+NUM_PORT_BITS+NUM_ADDR_BITS+NUM_BRAM_ADDR_BITS+3,
    localparam IN_PORTS_REG_BITS = NUM_LEAF_BITS+NUM_PORT_BITS,
    localparam REG_CONTROL_BITS = OUT_PORTS_REG_BITS*NUM_OUT_PORTS+IN_PORTS_REG_BITS*NUM_IN_PORTS
    )(
    input clk,
    input reset,
    
    //data from BFT
    input [PACKET_BITS-1:0] din_leaf_bft2interface,
    
    //data to BFT
    output [PACKET_BITS-1:0] dout_leaf_interface2bft,
    input resend,

    //data to USER
    output [PAYLOAD_BITS*NUM_IN_PORTS-1:0] dout_leaf_interface2user,
    output [NUM_IN_PORTS-1:0] vld_interface2user,
    input [NUM_IN_PORTS-1:0] ack_user2interface,
    
    //data from USER
    output [NUM_OUT_PORTS-1:0] ack_interface2user,
    input [NUM_OUT_PORTS-1:0] vld_user2interface,
    input [PAYLOAD_BITS*NUM_OUT_PORTS-1:0] din_leaf_user2interface
    );
   
    
    wire [PACKET_BITS-1:0] stream_ExCtrl2sfc;
    wire [PACKET_BITS-1:0] stream_sfc2ExCtrl;
    wire [PACKET_BITS-1:0] configure_ExCtrl2ConCtrl;
    wire [REG_CONTROL_BITS-1:0] control_reg;
    wire resend_ExCtrl2sfc; 
    
    Extract_Control # (
        .PACKET_BITS(PACKET_BITS),
        .NUM_LEAF_BITS(NUM_LEAF_BITS),
        .NUM_PORT_BITS(NUM_PORT_BITS)
    )ExCtrl(
        .clk(clk),
        .reset(reset),
        .din_leaf_bft2interface(din_leaf_bft2interface),
        .dout_leaf_interface2bft(dout_leaf_interface2bft),
        .resend(resend),
        .resend_out(resend_ExCtrl2sfc),
        .stream_in(stream_sfc2ExCtrl),
        .stream_out(stream_ExCtrl2sfc),
        .configure_out(configure_ExCtrl2ConCtrl)
    );


    Config_Controls # (
        .PACKET_BITS(PACKET_BITS),
        .NUM_LEAF_BITS(NUM_LEAF_BITS),
        .NUM_PORT_BITS(NUM_PORT_BITS),
        .NUM_ADDR_BITS(NUM_ADDR_BITS),
        .PAYLOAD_BITS(PAYLOAD_BITS),
        .NUM_IN_PORTS(NUM_IN_PORTS),
        .NUM_OUT_PORTS(NUM_OUT_PORTS),
        .NUM_BRAM_ADDR_BITS(NUM_BRAM_ADDR_BITS)
    )ConCtrl(
        .control_reg(control_reg),
        .clk(clk),
        .reset(reset),
        .configure_in(configure_ExCtrl2ConCtrl)
    );
    

    
    
    Stream_Flow_Control#(
        .PACKET_BITS(PACKET_BITS),
        .NUM_LEAF_BITS(NUM_LEAF_BITS),
        .NUM_PORT_BITS(NUM_PORT_BITS),
        .NUM_ADDR_BITS(NUM_ADDR_BITS),
        .PAYLOAD_BITS(PAYLOAD_BITS),
        .NUM_IN_PORTS(NUM_IN_PORTS),
        .NUM_OUT_PORTS(NUM_OUT_PORTS),
        .NUM_BRAM_ADDR_BITS(NUM_BRAM_ADDR_BITS),
        .FREESPACE_UPDATE_SIZE(FREESPACE_UPDATE_SIZE)
    )sfc(
        .resend(resend_ExCtrl2sfc),
        .clk(clk),
        .reset(reset),
        .stream_in(stream_ExCtrl2sfc),
        .stream_out(stream_sfc2ExCtrl),
        .control_reg(control_reg),
        .dout_leaf_interface2user(dout_leaf_interface2user),
        .vld_interface2user(vld_interface2user),
        .ack_user2interface(ack_user2interface),
        .ack_interface2user(ack_interface2user),
        .vld_user2interface(vld_user2interface),
        .din_leaf_user2interface(din_leaf_user2interface)
    );
    
endmodule
