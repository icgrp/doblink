module write_b_out#(
    parameter PAYLOAD_BITS = 64
    )(
    input vld_user2b_out,
    input [PAYLOAD_BITS-1:0] din_leaf_user2interface,
    input full,
    
    output reg wr_en,
    output reg [PAYLOAD_BITS-1:0] din);
    
    initial wr_en = 0;
    initial din = 0;

    always@(*) begin
        if(full) begin // can't push in to fifo
            wr_en = 0;
            din = 42; // random, because this data won't be written anyway
        end
        else begin
            if(vld_user2b_out) begin
                wr_en = 1;
                din = din_leaf_user2interface;
            end
            else begin
                wr_en = 0;
                din = 42; // random, because this data won't be written anyway
            end                
        end
    end

endmodule
