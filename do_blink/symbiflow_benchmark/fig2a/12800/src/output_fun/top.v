`timescale 1ns / 1ps
module top(
    input wire clk,
    input wire [49-1 : 0] din_leaf_bft2interface,
    output wire [49-1 : 0] dout_leaf_interface2bft,
    input wire resend,
    input wire ap_start,
    input wire reset
    );


    wire [32-1 :0] dout_leaf_interface2user_1;
    wire vld_interface2user_1;
    wire ack_user2interface_1;
    
    wire [32-1 :0] dout_leaf_interface2user_2;
    wire vld_interface2user_2;
    wire ack_user2interface_2;

    wire [32-1 :0] dout_leaf_interface2user_3;
    wire vld_interface2user_3;
    wire ack_user2interface_3;

    wire [32-1 :0] dout_leaf_interface2user_4;
    wire vld_interface2user_4;
    wire ack_user2interface_4;

    wire [32-1 :0] dout_leaf_interface2user_5;
    wire vld_interface2user_5;
    wire ack_user2interface_5;

    wire [32-1 :0] dout_leaf_interface2user_6;
    wire vld_interface2user_6;
    wire ack_user2interface_6;

    wire [32-1 :0] dout_leaf_interface2user_7;
    wire vld_interface2user_7;
    wire ack_user2interface_7;
    
    wire [32-1 :0] dout_leaf_interface2user_8;
    wire vld_interface2user_8;
    wire ack_user2interface_8;
    
    wire  [49-1 : 0] dout_leaf_interface2bft1;
    wire  [49-1 : 0] dout_leaf_interface2bft2;
    wire  [49-1 : 0] dout_leaf_interface2bft3;
    wire  [49-1 : 0] dout_leaf_interface2bft4;
    wire  [49-1 : 0] dout_leaf_interface2bft5;
    wire  [49-1 : 0] dout_leaf_interface2bft6;
    wire  [49-1 : 0] dout_leaf_interface2bft7;
        
    
/*    
    leaf_interface #(
        .PACKET_BITS(49 ),
        .PAYLOAD_BITS(32 ), 
        .NUM_LEAF_BITS(5),
        .NUM_PORT_BITS(4),
        .NUM_ADDR_BITS(7),
        .NUM_IN_PORTS(2), 
        .NUM_OUT_PORTS(1),
        .NUM_BRAM_ADDR_BITS(7),
        .FREESPACE_UPDATE_SIZE(64)
    )leaf_interface_inst(
        .clk(clk),
        .reset(reset),
        .din_leaf_bft2interface(din_leaf_bft2interface),
        .dout_leaf_interface2bft(dout_leaf_interface2bft),
        .resend(resend),
        .dout_leaf_interface2user({dout_leaf_interface2user_2,dout_leaf_interface2user_1}),
        .vld_interface2user({vld_interface2user_2,vld_interface2user_1}),
        .ack_user2interface({ack_user2interface_2,ack_user2interface_1}),
        .ack_interface2user({ack_interface2user_1}),
        .vld_user2interface({vld_user2interface_1}),
        .din_leaf_user2interface({din_leaf_user2interface_1})
    );
    
    output_fun output_fun_inst(
        .ap_clk(clk),
        .ap_start(ap_start),
        .ap_done(),
        .ap_idle(),
        .ap_ready(),
        .Input_2_V_V(dout_leaf_interface2user_2),
        .Input_2_V_V_ap_vld(vld_interface2user_2),
        .Input_2_V_V_ap_ack(ack_user2interface_2),
        .Input_1_V_V(dout_leaf_interface2user_1),
        .Input_1_V_V_ap_vld(vld_interface2user_1),
        .Input_1_V_V_ap_ack(ack_user2interface_1),
        .Output_1_V_V(din_leaf_user2interface_1),
        .Output_1_V_V_ap_vld(vld_user2interface_1),
        .Output_1_V_V_ap_ack(ack_interface2user_1),
        .ap_rst(reset)
        );  
*/


    leaf_interface #(
        .PACKET_BITS(49 ),
        .PAYLOAD_BITS(32 ), 
        .NUM_LEAF_BITS(5),
        .NUM_PORT_BITS(4),
        .NUM_ADDR_BITS(7),
        .NUM_IN_PORTS(1), 
        .NUM_OUT_PORTS(1),
        .NUM_BRAM_ADDR_BITS(7),
        .FREESPACE_UPDATE_SIZE(64)
    )leaf_interface_inst1(
        .clk(clk),
        .reset(reset),
        .din_leaf_bft2interface(din_leaf_bft2interface),
        .dout_leaf_interface2bft(dout_leaf_interface2bft1),
        .resend(resend),
        .dout_leaf_interface2user({dout_leaf_interface2user_1}),
        .vld_interface2user({vld_interface2user_1}),
        .ack_user2interface({ack_user2interface_1}),
        .ack_interface2user({ack_user2interface_1}),
        .vld_user2interface({vld_interface2user_1}),
        .din_leaf_user2interface({dout_leaf_interface2user_1})
    );
    
        leaf_interface #(
        .PACKET_BITS(49 ),
        .PAYLOAD_BITS(32 ), 
        .NUM_LEAF_BITS(5),
        .NUM_PORT_BITS(4),
        .NUM_ADDR_BITS(7),
        .NUM_IN_PORTS(1), 
        .NUM_OUT_PORTS(1),
        .NUM_BRAM_ADDR_BITS(7),
        .FREESPACE_UPDATE_SIZE(64)
    )leaf_interface_inst2(
        .clk(clk),
        .reset(reset),
        .din_leaf_bft2interface(dout_leaf_interface2bft1),
        .dout_leaf_interface2bft(dout_leaf_interface2bft2),
        .resend(resend),
        .dout_leaf_interface2user({dout_leaf_interface2user_2}),
        .vld_interface2user({vld_interface2user_2}),
        .ack_user2interface({ack_user2interface_2}),
        .ack_interface2user({ack_user2interface_2}),
        .vld_user2interface({vld_interface2user_2}),
        .din_leaf_user2interface({dout_leaf_interface2user_2})
    );
 
        leaf_interface #(
    .PACKET_BITS(49 ),
    .PAYLOAD_BITS(32 ), 
    .NUM_LEAF_BITS(5),
    .NUM_PORT_BITS(4),
    .NUM_ADDR_BITS(7),
    .NUM_IN_PORTS(1), 
    .NUM_OUT_PORTS(1),
    .NUM_BRAM_ADDR_BITS(7),
    .FREESPACE_UPDATE_SIZE(64)
)leaf_interface_inst3(
    .clk(clk),
    .reset(reset),
    .din_leaf_bft2interface(dout_leaf_interface2bft2),
    .dout_leaf_interface2bft(dout_leaf_interface2bft3),
    .resend(resend),
    .dout_leaf_interface2user({dout_leaf_interface2user_3}),
    .vld_interface2user({vld_interface2user_3}),
    .ack_user2interface({ack_user2interface_3}),
    .ack_interface2user({ack_user2interface_3}),
    .vld_user2interface({vld_interface2user_3}),
    .din_leaf_user2interface({dout_leaf_interface2user_3})
);

        leaf_interface #(
        .PACKET_BITS(49 ),
        .PAYLOAD_BITS(32 ), 
        .NUM_LEAF_BITS(5),
        .NUM_PORT_BITS(4),
        .NUM_ADDR_BITS(7),
        .NUM_IN_PORTS(1), 
        .NUM_OUT_PORTS(1),
        .NUM_BRAM_ADDR_BITS(7),
        .FREESPACE_UPDATE_SIZE(64)
    )leaf_interface_inst4(
        .clk(clk),
        .reset(reset),
        .din_leaf_bft2interface(dout_leaf_interface2bft3),
        .dout_leaf_interface2bft(dout_leaf_interface2bft4),
        .resend(resend),
        .dout_leaf_interface2user({dout_leaf_interface2user_4}),
        .vld_interface2user({vld_interface2user_4}),
        .ack_user2interface({ack_user2interface_4}),
        .ack_interface2user({ack_user2interface_4}),
        .vld_user2interface({vld_interface2user_4}),
        .din_leaf_user2interface({dout_leaf_interface2user_4})
    );
    
    
        leaf_interface #(
    .PACKET_BITS(49 ),
    .PAYLOAD_BITS(32 ), 
    .NUM_LEAF_BITS(5),
    .NUM_PORT_BITS(4),
    .NUM_ADDR_BITS(7),
    .NUM_IN_PORTS(1), 
    .NUM_OUT_PORTS(1),
    .NUM_BRAM_ADDR_BITS(7),
    .FREESPACE_UPDATE_SIZE(64)
)leaf_interface_inst5(
    .clk(clk),
    .reset(reset),
    .din_leaf_bft2interface(dout_leaf_interface2bft4),
    .dout_leaf_interface2bft(dout_leaf_interface2bft5),
    .resend(resend),
    .dout_leaf_interface2user({dout_leaf_interface2user_5}),
    .vld_interface2user({vld_interface2user_5}),
    .ack_user2interface({ack_user2interface_5}),
    .ack_interface2user({ack_user2interface_5}),
    .vld_user2interface({vld_interface2user_5}),
    .din_leaf_user2interface({dout_leaf_interface2user_5})
);


        leaf_interface #(
        .PACKET_BITS(49 ),
        .PAYLOAD_BITS(32 ), 
        .NUM_LEAF_BITS(5),
        .NUM_PORT_BITS(4),
        .NUM_ADDR_BITS(7),
        .NUM_IN_PORTS(1), 
        .NUM_OUT_PORTS(1),
        .NUM_BRAM_ADDR_BITS(7),
        .FREESPACE_UPDATE_SIZE(64)
    )leaf_interface_inst6(
        .clk(clk),
        .reset(reset),
        .din_leaf_bft2interface(dout_leaf_interface2bft5),
        .dout_leaf_interface2bft(dout_leaf_interface2bft6),
        .resend(resend),
        .dout_leaf_interface2user({dout_leaf_interface2user_6}),
        .vld_interface2user({vld_interface2user_6}),
        .ack_user2interface({ack_user2interface_6}),
        .ack_interface2user({ack_user2interface_6}),
        .vld_user2interface({vld_interface2user_6}),
        .din_leaf_user2interface({dout_leaf_interface2user_6})
    );
    
    
        leaf_interface #(
    .PACKET_BITS(49 ),
    .PAYLOAD_BITS(32 ), 
    .NUM_LEAF_BITS(5),
    .NUM_PORT_BITS(4),
    .NUM_ADDR_BITS(7),
    .NUM_IN_PORTS(1), 
    .NUM_OUT_PORTS(1),
    .NUM_BRAM_ADDR_BITS(7),
    .FREESPACE_UPDATE_SIZE(64)
)leaf_interface_inst7(
    .clk(clk),
    .reset(reset),
    .din_leaf_bft2interface(dout_leaf_interface2bft6),
    .dout_leaf_interface2bft(dout_leaf_interface2bft7),
    .resend(resend),
    .dout_leaf_interface2user({dout_leaf_interface2user_7}),
    .vld_interface2user({vld_interface2user_7}),
    .ack_user2interface({ack_user2interface_7}),
    .ack_interface2user({ack_user2interface_7}),
    .vld_user2interface({vld_interface2user_7}),
    .din_leaf_user2interface({dout_leaf_interface2user_7})
);


        leaf_interface #(
        .PACKET_BITS(49 ),
        .PAYLOAD_BITS(32 ), 
        .NUM_LEAF_BITS(5),
        .NUM_PORT_BITS(4),
        .NUM_ADDR_BITS(7),
        .NUM_IN_PORTS(1), 
        .NUM_OUT_PORTS(1),
        .NUM_BRAM_ADDR_BITS(7),
        .FREESPACE_UPDATE_SIZE(64)
    )leaf_interface_inst8(
        .clk(clk),
        .reset(reset),
        .din_leaf_bft2interface(dout_leaf_interface2bft7),
        .dout_leaf_interface2bft(dout_leaf_interface2bft),
        .resend(resend),
        .dout_leaf_interface2user({dout_leaf_interface2user_8}),
        .vld_interface2user({vld_interface2user_8}),
        .ack_user2interface({ack_user2interface_8}),
        .ack_interface2user({ack_user2interface_8}),
        .vld_user2interface({vld_interface2user_8}),
        .din_leaf_user2interface({dout_leaf_interface2user_8})
    );
           
endmodule
