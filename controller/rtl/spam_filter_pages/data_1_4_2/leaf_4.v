module leaf_4(
    input wire clk,
    input wire [48 : 0] din_leaf_bft2interface,
    output wire [48 : 0] dout_leaf_interface2bft,
    input wire resend,
    input wire ap_start,
    input wire reset
    );

    wire [32-1 :0] dout_leaf_interface2user_3;
    wire vld_interface2user_3;
    wire ack_user2interface_3;
    wire [32-1 :0] dout_leaf_interface2user_2;
    wire vld_interface2user_2;
    wire ack_user2interface_2;
    wire [32-1 :0] dout_leaf_interface2user_1;
    wire vld_interface2user_1;
    wire ack_user2interface_1;
    wire [32-1 :0] din_leaf_user2interface_3;
    wire vld_user2interface_3;
    wire ack_interface2user_3;
    wire [32-1 :0] din_leaf_user2interface_2;
    wire vld_user2interface_2;
    wire ack_interface2user_2;
    wire [32-1 :0] din_leaf_user2interface_1;
    wire vld_user2interface_1;
    wire ack_interface2user_1;
    
    leaf_interface #(
        .PACKET_BITS(49 ),
        .PAYLOAD_BITS(32 ), 
        .NUM_LEAF_BITS(4),
        .NUM_PORT_BITS(4),
        .NUM_ADDR_BITS(7),
        .NUM_IN_PORTS(3), 
        .NUM_OUT_PORTS(3),
        .NUM_BRAM_ADDR_BITS(7),
        .FREESPACE_UPDATE_SIZE(64)
    )leaf_interface_inst(
        .clk(clk),
        .reset(reset),
        .din_leaf_bft2interface(din_leaf_bft2interface),
        .dout_leaf_interface2bft(dout_leaf_interface2bft),
        .resend(resend),
        .dout_leaf_interface2user({dout_leaf_interface2user_3,dout_leaf_interface2user_2,dout_leaf_interface2user_1}),
        .vld_interface2user({vld_interface2user_3,vld_interface2user_2,vld_interface2user_1}),
        .ack_user2interface({ack_user2interface_3,ack_user2interface_2,ack_user2interface_1}),
        .ack_interface2user({ack_interface2user_3,ack_interface2user_2,ack_interface2user_1}),
        .vld_user2interface({vld_user2interface_3,vld_user2interface_2,vld_user2interface_1}),
        .din_leaf_user2interface({din_leaf_user2interface_3,din_leaf_user2interface_2,din_leaf_user2interface_1})
    );
    
    data_1_4_2 data_1_4_2_inst(
        .ap_clk(clk),
        .ap_start(1'd1),
        .ap_done(),
        .ap_idle(),
        .ap_ready(),
        .Input_3_V_TDATA(dout_leaf_interface2user_3),
        .Input_3_V_TVALID(vld_interface2user_3),
        .Input_3_V_TREADY(ack_user2interface_3),
        .Input_2_V_TDATA(dout_leaf_interface2user_2),
        .Input_2_V_TVALID(vld_interface2user_2),
        .Input_2_V_TREADY(ack_user2interface_2),
        .Input_1_V_TDATA(dout_leaf_interface2user_1),
        .Input_1_V_TVALID(vld_interface2user_1),
        .Input_1_V_TREADY(ack_user2interface_1),
        .Output_3_V_TDATA(din_leaf_user2interface_3),
        .Output_3_V_TVALID(vld_user2interface_3),
        .Output_3_V_TREADY(ack_interface2user_3),
        .Output_2_V_TDATA(din_leaf_user2interface_2),
        .Output_2_V_TVALID(vld_user2interface_2),
        .Output_2_V_TREADY(ack_interface2user_2),
        .Output_1_V_TDATA(din_leaf_user2interface_1),
        .Output_1_V_TVALID(vld_user2interface_1),
        .Output_1_V_TREADY(ack_interface2user_1),
        .ap_rst_n(!reset)
        );  
    
endmodule
