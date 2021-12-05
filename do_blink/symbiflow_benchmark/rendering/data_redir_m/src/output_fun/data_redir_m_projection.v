// ==============================================================
// RTL generated by Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Version: 2020.2
// Copyright (C) Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

`timescale 1 ns / 1 ps 

module data_redir_m_projection (
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
        ap_return_6,
        grp_fu_187_p_din0,
        grp_fu_187_p_din1,
        grp_fu_187_p_dout0,
        grp_fu_187_p_ce,
        grp_fu_191_p_din0,
        grp_fu_191_p_din1,
        grp_fu_191_p_dout0,
        grp_fu_191_p_ce,
        grp_fu_195_p_din0,
        grp_fu_195_p_din1,
        grp_fu_195_p_dout0,
        grp_fu_195_p_ce
);

parameter    ap_ST_fsm_state1 = 5'd1;
parameter    ap_ST_fsm_state2 = 5'd2;
parameter    ap_ST_fsm_state3 = 5'd4;
parameter    ap_ST_fsm_state4 = 5'd8;
parameter    ap_ST_fsm_state5 = 5'd16;

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
output  [7:0] grp_fu_187_p_din0;
output  [9:0] grp_fu_187_p_din1;
input  [16:0] grp_fu_187_p_dout0;
output   grp_fu_187_p_ce;
output  [7:0] grp_fu_191_p_din0;
output  [9:0] grp_fu_191_p_din1;
input  [16:0] grp_fu_191_p_dout0;
output   grp_fu_191_p_ce;
output  [7:0] grp_fu_195_p_din0;
output  [9:0] grp_fu_195_p_din1;
input  [16:0] grp_fu_195_p_dout0;
output   grp_fu_195_p_ce;

reg ap_done;
reg ap_idle;
reg ap_ready;

(* fsm_encoding = "none" *) reg   [4:0] ap_CS_fsm;
wire    ap_CS_fsm_state1;
wire   [7:0] triangle_3d_x0_V_fu_50_p1;
reg   [7:0] triangle_3d_x0_V_reg_235;
reg   [7:0] triangle_3d_y0_V_reg_240;
reg   [7:0] triangle_3d_x1_V_reg_245;
wire   [7:0] triangle_3d_y1_V_fu_84_p1;
reg   [7:0] triangle_3d_y1_V_reg_250;
reg   [7:0] triangle_3d_x2_V_reg_255;
reg   [7:0] triangle_3d_y2_V_reg_260;
wire   [16:0] zext_ln1364_fu_118_p1;
wire   [16:0] zext_ln1364_2_fu_128_p1;
wire   [16:0] zext_ln1364_4_fu_138_p1;
reg   [6:0] tmp_reg_280;
wire    ap_CS_fsm_state4;
reg   [6:0] tmp_1_reg_285;
reg   [6:0] tmp_2_reg_290;
wire   [7:0] triangle_3d_z0_V_fu_64_p4;
wire   [7:0] grp_fu_122_p0;
wire   [9:0] grp_fu_122_p1;
wire   [7:0] triangle_3d_z1_V_fu_88_p4;
wire   [7:0] grp_fu_132_p0;
wire   [9:0] grp_fu_132_p1;
wire   [7:0] grp_fu_142_p0;
wire   [9:0] grp_fu_142_p1;
wire   [16:0] grp_fu_122_p2;
wire   [16:0] grp_fu_132_p2;
wire   [16:0] grp_fu_142_p2;
wire    ap_CS_fsm_state5;
wire   [7:0] zext_ln1364_1_fu_178_p1;
wire   [7:0] zext_ln1364_5_fu_184_p1;
wire   [7:0] add_ln213_fu_187_p2;
wire   [7:0] zext_ln1364_3_fu_181_p1;
wire   [7:0] add_ln213_1_fu_193_p2;
wire    grp_fu_122_ce;
wire    grp_fu_132_ce;
wire    grp_fu_142_ce;
reg   [4:0] ap_NS_fsm;
wire    ap_ce_reg;

// power-on initialization
initial begin
#0 ap_CS_fsm = 5'd1;
#0 triangle_3d_x0_V_reg_235 = 8'd0;
#0 triangle_3d_y0_V_reg_240 = 8'd0;
#0 triangle_3d_x1_V_reg_245 = 8'd0;
#0 triangle_3d_y1_V_reg_250 = 8'd0;
#0 triangle_3d_x2_V_reg_255 = 8'd0;
#0 triangle_3d_y2_V_reg_260 = 8'd0;
#0 tmp_reg_280 = 7'd0;
#0 tmp_1_reg_285 = 7'd0;
#0 tmp_2_reg_290 = 7'd0;
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_CS_fsm <= ap_ST_fsm_state1;
    end else begin
        ap_CS_fsm <= ap_NS_fsm;
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        tmp_1_reg_285 <= 7'd0;
    end else begin
        if ((1'b1 == ap_CS_fsm_state4)) begin
            tmp_1_reg_285 <= {{grp_fu_191_p_dout0[16:10]}};
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        tmp_2_reg_290 <= 7'd0;
    end else begin
        if ((1'b1 == ap_CS_fsm_state4)) begin
            tmp_2_reg_290 <= {{grp_fu_195_p_dout0[16:10]}};
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        tmp_reg_280 <= 7'd0;
    end else begin
        if ((1'b1 == ap_CS_fsm_state4)) begin
            tmp_reg_280 <= {{grp_fu_187_p_dout0[16:10]}};
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        triangle_3d_x0_V_reg_235 <= 8'd0;
    end else begin
        if ((1'b1 == ap_CS_fsm_state1)) begin
            triangle_3d_x0_V_reg_235 <= triangle_3d_x0_V_fu_50_p1;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        triangle_3d_x1_V_reg_245 <= 8'd0;
    end else begin
        if ((1'b1 == ap_CS_fsm_state1)) begin
            triangle_3d_x1_V_reg_245 <= {{input_lo[31:24]}};
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        triangle_3d_x2_V_reg_255 <= 8'd0;
    end else begin
        if ((1'b1 == ap_CS_fsm_state1)) begin
            triangle_3d_x2_V_reg_255 <= {{input_mi[23:16]}};
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        triangle_3d_y0_V_reg_240 <= 8'd0;
    end else begin
        if ((1'b1 == ap_CS_fsm_state1)) begin
            triangle_3d_y0_V_reg_240 <= {{input_lo[15:8]}};
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        triangle_3d_y1_V_reg_250 <= 8'd0;
    end else begin
        if ((1'b1 == ap_CS_fsm_state1)) begin
            triangle_3d_y1_V_reg_250 <= triangle_3d_y1_V_fu_84_p1;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        triangle_3d_y2_V_reg_260 <= 8'd0;
    end else begin
        if ((1'b1 == ap_CS_fsm_state1)) begin
            triangle_3d_y2_V_reg_260 <= {{input_mi[31:24]}};
        end
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state5) | ((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b0)))) begin
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
    if ((1'b1 == ap_CS_fsm_state5)) begin
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
            ap_NS_fsm = ap_ST_fsm_state3;
        end
        ap_ST_fsm_state3 : begin
            ap_NS_fsm = ap_ST_fsm_state4;
        end
        ap_ST_fsm_state4 : begin
            ap_NS_fsm = ap_ST_fsm_state5;
        end
        ap_ST_fsm_state5 : begin
            ap_NS_fsm = ap_ST_fsm_state1;
        end
        default : begin
            ap_NS_fsm = 'bx;
        end
    endcase
end

assign add_ln213_1_fu_193_p2 = (add_ln213_fu_187_p2 + zext_ln1364_3_fu_181_p1);

assign add_ln213_fu_187_p2 = (zext_ln1364_1_fu_178_p1 + zext_ln1364_5_fu_184_p1);

assign ap_CS_fsm_state1 = ap_CS_fsm[32'd0];

assign ap_CS_fsm_state4 = ap_CS_fsm[32'd3];

assign ap_CS_fsm_state5 = ap_CS_fsm[32'd4];

assign ap_return_0 = triangle_3d_x0_V_reg_235;

assign ap_return_1 = triangle_3d_y0_V_reg_240;

assign ap_return_2 = triangle_3d_x1_V_reg_245;

assign ap_return_3 = triangle_3d_y1_V_reg_250;

assign ap_return_4 = triangle_3d_x2_V_reg_255;

assign ap_return_5 = triangle_3d_y2_V_reg_260;

assign ap_return_6 = add_ln213_1_fu_193_p2;

assign grp_fu_122_ce = 1'b1;

assign grp_fu_122_p0 = zext_ln1364_fu_118_p1;

assign grp_fu_122_p1 = 17'd342;

assign grp_fu_122_p2 = grp_fu_187_p_dout0;

assign grp_fu_132_ce = 1'b1;

assign grp_fu_132_p0 = zext_ln1364_2_fu_128_p1;

assign grp_fu_132_p1 = 17'd342;

assign grp_fu_132_p2 = grp_fu_191_p_dout0;

assign grp_fu_142_ce = 1'b1;

assign grp_fu_142_p0 = zext_ln1364_4_fu_138_p1;

assign grp_fu_142_p1 = 17'd342;

assign grp_fu_142_p2 = grp_fu_195_p_dout0;

assign grp_fu_187_p_ce = 1'b1;

assign grp_fu_187_p_din0 = zext_ln1364_fu_118_p1;

assign grp_fu_187_p_din1 = 17'd342;

assign grp_fu_191_p_ce = 1'b1;

assign grp_fu_191_p_din0 = zext_ln1364_2_fu_128_p1;

assign grp_fu_191_p_din1 = 17'd342;

assign grp_fu_195_p_ce = 1'b1;

assign grp_fu_195_p_din0 = zext_ln1364_4_fu_138_p1;

assign grp_fu_195_p_din1 = 17'd342;

assign triangle_3d_x0_V_fu_50_p1 = input_lo[7:0];

assign triangle_3d_y1_V_fu_84_p1 = input_mi[7:0];

assign triangle_3d_z0_V_fu_64_p4 = {{input_lo[23:16]}};

assign triangle_3d_z1_V_fu_88_p4 = {{input_mi[15:8]}};

assign zext_ln1364_1_fu_178_p1 = tmp_reg_280;

assign zext_ln1364_2_fu_128_p1 = triangle_3d_z1_V_fu_88_p4;

assign zext_ln1364_3_fu_181_p1 = tmp_1_reg_285;

assign zext_ln1364_4_fu_138_p1 = input_hi;

assign zext_ln1364_5_fu_184_p1 = tmp_2_reg_290;

assign zext_ln1364_fu_118_p1 = triangle_3d_z0_V_fu_64_p4;

endmodule //data_redir_m_projection