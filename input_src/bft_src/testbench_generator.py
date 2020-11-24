#!/usr/bin/python3
from network_generator import clog2
import pdb
import random

def create_packet_creator(injection_rate, traffic_params, num_sent_per_leaf):
    import random
    from datetime import datetime
    random.seed(datetime.now())

    traffic_pattern= traffic_params['pattern']
    if traffic_pattern == 'complement':
        pattern_str= '~addr'
    elif traffic_pattern == 'random':
        pattern_str= '$random('+ str(random.randint(0, 999)) + ')[$clog2(num_leaves)-1:0]'
    elif traffic_pattern == 'uniform':
        pattern_str= 'addr + ' + str(traffic_params['offset'])
    elif traffic_pattern == 'manual':
        pattern_str= '~addr'
    else:
        print('packet creator error!')
        return ''

    return '\n'.join([
        'module packet_creator (',
        '\tinput clk, ',
        '\tinput reset,',
        '\tinput resend,',
        '\toutput reg [p_sz-1:0] bus_o',
        '\t);',
        '',
        '\tparameter num_leaves= 2;',
        '\tparameter payload_sz = 1; // contains source address',
        '\tparameter addr= 1\'b0;',
        '\tparameter p_sz= 1 + $clog2(num_leaves) + payload_sz; //packet size',
        '\tparameter num_sent_per_leaf= ' + str(num_sent_per_leaf) + ';',
        '\t',
        '\tparameter send_order_sz= $clog2(num_sent_per_leaf);',
        '\treg [send_order_sz:0] i;',
        '\treg send_out;',
        '\tinteger seed= ' + str(random.randint(0,2**32-1)) + ';',
        '\treg [p_sz-1:0] data_to_be_sent[num_leaves*num_sent_per_leaf-1:0];',
        '\tinitial begin',
	'\t\t{i , send_out} <= 0;',
	'\t\t$readmemb("./data_pattern.txt", data_to_be_sent);',
	'\tend',
	'\talways @(posedge clk) begin',
	'\t\tif (reset)',
	'\t\t\t{i, send_out, bus_o} <= 0;',
	'\t\telse if (!resend && send_out) begin',
	'\t\t\tbus_o <= data_to_be_sent[addr*num_sent_per_leaf+i];',
        '\t\t\ti <= i + 1;',
	'\t\t\tif (i < num_sent_per_leaf-1) begin',
        '\t\t\t\tsend_out <= (($random(seed) % ' + str(100 // injection_rate) + 
            ') == 1\'b0);',
        '\t\t\tend',
        '\t\t\telse',
        '\t\t\t\tsend_out <= 0;',
        '\t\tend',
        '\t\telse if (resend && send_out) begin',
        '\t\t\tbus_o <= 0;',
        '\t\tend',
        '\t\telse begin',
        '\t\t\tbus_o <= 0;',
        '\t\t\tif (i < num_sent_per_leaf) begin',
        '\t\t\t\tsend_out <= (($random(seed) % ' + str(100 // injection_rate) + 
            ') == 1\'b0);',
        '\t\t\tend',
        '\t\t\telse',
        '\t\t\t\tsend_out <= 0;',
        '\t\tend',
        '\tend',
        '\tendmodule'])

def create_pg(traffic_params, num_leaves, injection_rate, num_sent_per_leaf):
    send_order_bits= clog2(num_sent_per_leaf)
    if traffic_params['pattern'] == 'complement':
        traffic_pattern = '`define COMPLEMENT_PATTERN'
        traffic_offset = ' '
    if traffic_params['pattern'] == 'random':
        traffic_pattern = '`define RANDOM_PATTERN'
        traffic_offset = ' '
    if traffic_params['pattern'] == 'manual':
        traffic_pattern = '`define MANUAL_PATTERN'
        traffic_offset = ' '
    if traffic_params['pattern'] == 'uniform':
        traffic_pattern = '`define UNIFORM_PATTERN'
        traffic_offset = '\tparameter offset = ' + str(traffic_params['offset']) + ';'
        

    return '\n'.join([
    traffic_pattern,
    'module test;',
    '',
    '\tparameter num_leaves= ' + str(num_leaves) + ';',
    '\tparameter payload_sz= $clog2(num_leaves) + ' + str(send_order_bits) + ';',
    '\tparameter p_sz= 1 + $clog2(num_leaves) + payload_sz;',
    traffic_offset,
    '',
    'parameter num_sent_per_leaf= 10;',
    'integer fp_w;',
    'integer num_leaves_i, data_i=0;',
    'integer pattern_data, pattern_tmp;',
    '`ifdef MANUAL_PATTERN',
    '',
    '`else',
    'initial begin',
    '\tfp_w = $fopen("data_pattern.txt", "w");',
    '\tfor (num_leaves_i=0; num_leaves_i < num_leaves; num_leaves_i= num_leaves_i+1) begin',
    '\t\tfor (data_i=0; data_i < num_sent_per_leaf; data_i= data_i+1) begin',
    '\t\t\tpattern_data = 1;',
    '\t\t\t`ifdef COMPLEMENT_PATTERN',
    '\t\t\t\tpattern_tmp = ~num_leaves_i[($clog2(num_leaves)-1):0];',
    '\t\t\t`endif',
    '\t\t\t`ifdef RANDOM_PATTERN',
    '\t\t\t\tpattern_tmp = $random;',
    '\t\t\t`endif',
    '\t\t\t`ifdef UNIFORM',
    '\t\t\t\tpattern_tmp = num_leaves_i + offset;',
    '\t\t\t`endif',
    '\t\t\tpattern_data = (pattern_data << $clog2(num_leaves)) + pattern_tmp[($clog2(num_leaves)-1):0];',
    '\t\t\tpattern_tmp = num_leaves_i[($clog2(num_leaves)-1):0];',
    '\t\t\tpattern_data = (pattern_data <<  $clog2(num_leaves)) + pattern_tmp[($clog2(num_leaves)-1):0];',
    '\t\t\tpattern_data = (pattern_data << 4) + data_i;',
    '\t\t\t$fwrite(fp_w, "%b\\n", pattern_data[p_sz-1:0]);',
    '\t\tend',
    '\tend',
    '\t$fclose(fp_w);',
    'end',
    '`endif',
    'endmodule '])


def create_tb(traffic_params, num_leaves, injection_rate, num_sent_per_leaf, addr_width, data_width):
    
    if traffic_params['pattern'] == 'complement':
        traffic_pattern = '`define COMPLEMENT_PATTERN'
        traffic_offset = ' '
    if traffic_params['pattern'] == 'random':
        traffic_pattern = '`define RANDOM_PATTERN'
        traffic_offset = ' '
    if traffic_params['pattern'] == 'manual':
        traffic_pattern = '`define MANUAL_PATTERN'
        traffic_offset = ' '
    if traffic_params['pattern'] == 'uniform':
        traffic_pattern = '`define UNIFORM_PATTERN'
        traffic_offset = '\tparameter offset = ' + str(traffic_params['offset']) + ';'
        

    return '\n'.join([
    traffic_pattern,
    'module test;',
    '',
    '\tparameter num_leaves= ' + str(num_leaves) + ';',
    '\tparameter payload_sz= ' + str(addr_width) + ' + ' + str(data_width) + ';',
    '\tparameter p_sz= 1 + ' + str(addr_width) + ' + payload_sz;',
    traffic_offset,
    '',
    '\tinteger k;',
    '',
    '\tinitial begin',
    '\t\t$dumpfile("gen_nw.vcd");',
    '\t\t$dumpvars(0, gen_nw_test);',
    '\t\t$dumpvars(0, test);',
    '\t\t$dumpvars(0, gen_pe[0]);',
    '\t\tfor (k= 0; k < num_leaves; k= k + 1) begin',
    '\t\t\t$dumpvars(0, test.pe_interface_arr[k]);',
    '\t\t\t$dumpvars(0, test.interface_pe_arr[k]);',
    '\t\t\tend',
    '\t\t#' + str(50 + round(20*num_sent_per_leaf*90*100/injection_rate)), 
    '\t\t$finish;',
    '\tend',
    '',
    '\treg clk;',
    '\treg reset;',
    '\t',
    '\twire [num_leaves*p_sz-1:0] pe_interface;',
    '\twire [num_leaves*p_sz-1:0] interface_pe;',
    '\twire [p_sz-1:0] pe_interface_arr [num_leaves-1:0];',
    '\twire [p_sz-1:0] interface_pe_arr [num_leaves-1:0];',
    '\twire [num_leaves-1:0] resend;',
    '',
    'integer i;',
    '\tinitial begin',
    '\t\t{clk, reset}= 2\'b01;',
    '\t\t#50',
    '\t\tfor (i= 0; i < 2^(100); i= i + 1) begin',
    '\t\t\tif (i == 1) reset <= 0;',
    '\t\t\tclk<= ~clk;',
    '\t\t\t#10;',
    '\t\tend',
    '\tend',
    '',
    '\tgen_nw #(',
    '\t\t.num_leaves(num_leaves),',
    '\t\t.payload_sz(payload_sz),',
    '\t\t.p_sz(p_sz),',
    '\t\t.addr(1\'b0),',
    '\t\t.level(0))',
    '\t\tgen_nw_test(',
    '\t\t\t.clk(clk),',
    '\t\t\t.reset(reset),',
    '\t\t\t.pe_interface(pe_interface),',
    '\t\t\t.interface_pe(interface_pe),',
    '\t\t\t.resend(resend));',
    '',
    '\tgenvar j;',
    '\tgenerate',
    '\tfor (j= 0; j < num_leaves; j=j+1) begin : gen_pe',
    '\t\tassign pe_interface[j*p_sz+:p_sz]= pe_interface_arr[j];',
    '\t\tassign interface_pe_arr[j]=  interface_pe[j*p_sz+:p_sz];',
    '',
    '\t\tpacket_creator #(',
    '\t\t\t.num_leaves(num_leaves),',
    '\t\t\t.payload_sz(payload_sz),',
    '\t\t\t.addr(j[$clog2(num_leaves)-1:0]),',
    '\t\t\t.p_sz(p_sz))',
    '\t\t\tpc(',
    '\t\t\t\t.clk(clk),',
    '\t\t\t\t.reset(reset),',
    '\t\t\t\t.bus_o(pe_interface_arr[j]),', 
    '\t\t\t\t.resend(resend[j]));',
    '\tend',
    '\tendgenerate',
    '',
    '\tinitial $display("type\\tPE\\tpacket\\t\\ttime");',
    '\tgenvar m;',
    '\tgenerate',
    '\tfor(m= 0; m < num_leaves; m= m + 1) begin',
    '\t\talways @(posedge clk) begin',
    '\t\t\tif (pe_interface_arr[m][p_sz-1])',
    '\t\t\t\t$display("sent\\t%05d\\t%b\\t%0d", m, pe_interface_arr[m], $time);',
    '\t\t\tif (interface_pe_arr[m][p_sz-1])',
    '\t\t\t\t$display("rcvd\\t%05d\\t%b\\t%0d", m, interface_pe_arr[m], $time);',
    #'\t\t\tif (gen_nw_test.subtree_left.subtree_left.subtree_left.bus_o[p_sz-1] == 1)',
    #'\t\t\t\t$display("000_bus_o:\\t%05d\\t%b\\t%0d", m, gen_nw_test.subtree_left.subtree_left.subtree_left.bus_o, $time);',
    '\t\tend',
    '\tend',
    '\tendgenerate',
    'endmodule '])

def binary_output(width, data_in):
    char_out = ''
    for _ in range(0, width):
        if(data_in % 2):
            char_out += '1'
        else:
            char_out += '0'
        data_in = data_in >> 1
    return char_out[::-1]

def make_test_pattern(traffic_params, num_leaves,  num_sent_per_leaf, addr_width, data_width):
    traffic_pattern= traffic_params['pattern']
    if traffic_pattern != 'manual':
      with open('data_pattern.txt', 'w') as pt:
        for addr_src in range(0, num_leaves):
            for data in range(0, num_sent_per_leaf):
                if traffic_pattern == 'complement':
                    addr_des = 2**addr_width - addr_src - 1
                elif traffic_pattern == 'random':
                    addr_des = random.randint(0, (2**addr_width-1))
                elif traffic_pattern == 'uniform':
                    addr_des = (addr_src + traffic_params['offset']) % 2**addr_width
                else:
                    addr_des = 2**addr_width - addr_src - 1
                    print('packet creator error!')
                pt.write('1')
                pt.write(binary_output(addr_width, addr_des))
                pt.write(binary_output(addr_width, addr_src))
                pt.write(binary_output(data_width, data)+'\n')



