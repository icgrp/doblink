`timescale 1ns / 1ps
module leaf(
    input wire clk_bft,
    input wire clk_user,
    input wire [49-1 : 0] din_leaf_bft2interface,
    output wire [49-1 : 0] dout_leaf_interface2bft,
    input wire resend,
    input wire reset_bft,
    input wire ap_start,
    input wire reset
    );

    wire [32-1 :0] dout_leaf_interface2user_1;
    wire vld_interface2user_1;
    wire ack_user2interface_1;
    wire [32-1 :0] din_leaf_user2interface_2;
    wire vld_user2interface_2;
    wire ack_interface2user_2;
    wire [32-1 :0] din_leaf_user2interface_1;
    wire vld_user2interface_1;
    wire ack_interface2user_1;
    
    leaf_interface #(
        .PACKET_BITS(49 ),
        .PAYLOAD_BITS(32 ), 
        .NUM_LEAF_BITS(5),
        .NUM_PORT_BITS(4),
        .NUM_ADDR_BITS(7),
        .NUM_IN_PORTS(1), 
        .NUM_OUT_PORTS(2),
        .NUM_BRAM_ADDR_BITS(7),
        .FREESPACE_UPDATE_SIZE(64)
    )leaf_interface_inst(
        .clk_bft(clk_bft),
        .clk_user(clk_user),
        .reset(reset),
        .reset_bft(reset_bft),
        .din_leaf_bft2interface(din_leaf_bft2interface),
        .dout_leaf_interface2bft(dout_leaf_interface2bft),
        .resend(resend),
        .dout_leaf_interface2user({dout_leaf_interface2user_1}),
        .vld_interface2user({vld_interface2user_1}),
        .ack_user2interface({ack_user2interface_1}),
        .ack_interface2user({ack_interface2user_2,ack_interface2user_1}),
        .vld_user2interface({vld_user2interface_2,vld_user2interface_1}),
        .din_leaf_user2interface({din_leaf_user2interface_2,din_leaf_user2interface_1})
    );
    
    picorv32_wrapper picorv32_wrapper_inst(
        .clk(clk_user),
        .din1(dout_leaf_interface2user_1),
        .val_in1(vld_interface2user_1),
        .ready_upward1(ack_user2interface_1),
        .dout1(din_leaf_user2interface_1),
        .val_out1(vld_user2interface_1),
        .ready_downward1(ack_interface2user_1),
        .dout2(din_leaf_user2interface_2),
        .val_out2(vld_user2interface_2),
        .ready_downward2(ack_interface2user_2),
        .val_in2(0),
        .val_in3(0),
        .val_in4(0),
        .din2(0),
        .din3(0),
        .din4(0),
        .ready_downward3(0),
        .ready_downward4(0),
        .resetn(ap_start&(!reset))
        );  
    
endmodule
