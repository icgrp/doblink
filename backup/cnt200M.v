module cnt200M(
  input clk,
  input reset,
  output reg start
  );


  reg [31:0] cnt;
  always(posedge clk) begin
    if(reset) begin
      start <= 0;
      cnt <= 0;
    end else begin
      if(cnt == 200_000_000) begin
        cnt <= 0;
        start <= 1;
      else begin 
        cnt <= cnt + 1;
        start <= 0;
      end
    end
  end


endmodule
