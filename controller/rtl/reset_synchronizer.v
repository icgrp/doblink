`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 06/11/2020 03:31:02 PM
// Design Name: 
// Module Name: reset_synchronizer
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module reset_synchronizer(
    input clk,
    input rst_async_n,
    output rst_sync_n,
    output rst_sync
    
    );

reg rst_s1, rst_s2;

always @ (posedge clk, negedge rst_async_n)  
    if (!rst_async_n) begin   
        rst_s1 <= 1'b0;  
        rst_s2 <= 1'b0;  
    end else begin  
        rst_s1 <= 1'b1;  
        rst_s2 <= rst_s1;  
    end  
 
assign rst_sync_n = rst_s2;   
assign rst_sync = ~ rst_s2;
endmodule
