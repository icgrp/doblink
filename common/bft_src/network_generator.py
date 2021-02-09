#!/usr/bin/python3
from math import ceil, log
import pdb
def clog2(num):
    return int(ceil(log(num, 2)))

def create_subtrees(args, num_leaves, pattern, num_sent_per_leaf= 10, 
                     level= 0):
    if pattern == '':
        return ''
    switch_type= 't' if pattern[-1] == '1' else 'pi'
   
    num_switches_in_cluster= 1
    for c in [int(c) for c in pattern[0:-1]]:
        num_switches_in_cluster *= c
    
    num_leaves_in_subtree= num_leaves // (2**level)
    
    subtree_name= '_' + pattern[:-1] + 'subtree' if int(pattern) > 2 else 'interface'
    if level > 0:
        addr_str=  str(level) + '\'b'+ level*'0';
        extra_io= '\n'.join([
            ',',
            '\tinput [' + pattern[-1] + '*' + str(num_switches_in_cluster) + 
            '*p_sz-1:0] bus_i,\n',
            '\toutput [' + pattern[-1] + '*' + str(num_switches_in_cluster) + '*p_sz-1:0] bus_o'])
        module_name= '_' + pattern + 'subtree'
    else:
        addr_str= '1\'b0' 
        extra_io= ''
        module_name= 'gen_nw'

    wire_def_pipe = ''
    inst_def_pipe = ''
    for pipe_i in range(args.pipeline):
        wire_def_pipe = wire_def_pipe + '\twire [' + str(num_switches_in_cluster) + '*p_sz-1:0] switch_left_' + str(pipe_i) + ';\n'
        wire_def_pipe = wire_def_pipe + '\twire [' + str(num_switches_in_cluster) + '*p_sz-1:0] switch_right_' + str(pipe_i) + ';\n'
        wire_def_pipe = wire_def_pipe + '\twire [' + str(num_switches_in_cluster) + '*p_sz-1:0] left_switch_' + str(pipe_i) + ';\n'
        wire_def_pipe = wire_def_pipe + '\twire [' + str(num_switches_in_cluster) + '*p_sz-1:0] right_switch_' + str(pipe_i) + ';\n\n\n'
        inst_def_pipe = inst_def_pipe + '\tpipe_ff #(\n'
        inst_def_pipe = inst_def_pipe + '\t\t.data_width(' + str(num_switches_in_cluster) + '*p_sz)\n'
        inst_def_pipe = inst_def_pipe + '\t\t)pipe_ff_inst_sl_' + str(pipe_i) + '(\n'
        inst_def_pipe = inst_def_pipe + '\t\t.clk(clk),\n'
        inst_def_pipe = inst_def_pipe + '\t\t.din(switch_left_' + str(pipe_i) +'),\n'
        if pipe_i < args.pipeline-1:
            inst_def_pipe = inst_def_pipe + '\t\t.dout(switch_left_' + str(pipe_i+1) +'));\n'
        else:
            inst_def_pipe = inst_def_pipe + '\t\t.dout(switch_left));\n'
        inst_def_pipe = inst_def_pipe + '\tpipe_ff #(\n'
        inst_def_pipe = inst_def_pipe + '\t\t.data_width(' + str(num_switches_in_cluster) + '*p_sz)\n'
        inst_def_pipe = inst_def_pipe + '\t\t)pipe_ff_inst_sr_' + str(pipe_i) + '(\n'
        inst_def_pipe = inst_def_pipe + '\t\t.clk(clk),\n'
        inst_def_pipe = inst_def_pipe + '\t\t.reset(reset),\n'
        inst_def_pipe = inst_def_pipe + '\t\t.din(switch_right_' + str(pipe_i) +'),\n'
        if pipe_i < args.pipeline-1:
            inst_def_pipe = inst_def_pipe + '\t\t.dout(switch_right_' + str(pipe_i+1) +'));\n'
        else:
            inst_def_pipe = inst_def_pipe + '\t\t.dout(switch_right));\n'
        inst_def_pipe = inst_def_pipe + '\tpipe_ff #(\n'
        inst_def_pipe = inst_def_pipe + '\t\t.data_width(' + str(num_switches_in_cluster) + '*p_sz)\n'
        inst_def_pipe = inst_def_pipe + '\t\t)pipe_ff_inst_ls_' + str(pipe_i) + '(\n'
        inst_def_pipe = inst_def_pipe + '\t\t.clk(clk),\n'
        inst_def_pipe = inst_def_pipe + '\t\t.reset(reset),\n'
        inst_def_pipe = inst_def_pipe + '\t\t.din(left_switch_' + str(pipe_i) +'),\n'
        if pipe_i < args.pipeline-1:
            inst_def_pipe = inst_def_pipe + '\t\t.dout(left_switch_' + str(pipe_i+1) +'));\n'
        else:  
            inst_def_pipe = inst_def_pipe + '\t\t.dout(left_switch));\n'
        inst_def_pipe = inst_def_pipe + '\tpipe_ff #(\n'
        inst_def_pipe = inst_def_pipe + '\t\t.data_width(' + str(num_switches_in_cluster) + '*p_sz)\n'
        inst_def_pipe = inst_def_pipe + '\t\t)pipe_ff_inst_rs_' + str(pipe_i) + '(\n'
        inst_def_pipe = inst_def_pipe + '\t\t.clk(clk),\n'
        inst_def_pipe = inst_def_pipe + '\t\t.reset(reset),\n'
        inst_def_pipe = inst_def_pipe + '\t\t.din(right_switch_' + str(pipe_i) +'),\n'
        if pipe_i < args.pipeline-1:
            inst_def_pipe = inst_def_pipe + '\t\t.dout(right_switch_' + str(pipe_i+1) +'));\n\n\n'
        else:  
            inst_def_pipe = inst_def_pipe + '\t\t.dout(right_switch));\n\n\n'
    
    return '\n'.join([
    'module ' + module_name + ' # (',
    '\tparameter num_leaves= ' + str(num_leaves) + ',',
    '\tparameter payload_sz= $clog2(num_leaves) + ' + 
        str(clog2(num_sent_per_leaf)) + ',',
    '\tparameter p_sz= 1 + $clog2(num_leaves) + payload_sz, //packet size',
    '\tparameter addr= ' + addr_str + ',',
    '\tparameter level= ' + str(level),
    '\t) (',
    '\tinput clk,',
    '\tinput reset,',
    '\tinput [p_sz*' + str(num_leaves_in_subtree) + '-1:0] pe_interface,',
    '\toutput [p_sz*' + str(num_leaves_in_subtree) + '-1:0] interface_pe,',
    '\toutput [' + str(num_leaves_in_subtree) + '-1:0] resend' + extra_io,
    ');',
    '\t',
    '\twire [' + str(num_switches_in_cluster) + '*p_sz-1:0] switch_left;',
    '\twire [' + str(num_switches_in_cluster) + '*p_sz-1:0] switch_right;',
    '\twire [' + str(num_switches_in_cluster) + '*p_sz-1:0] left_switch;',
    '\twire [' + str(num_switches_in_cluster) + '*p_sz-1:0] right_switch;',
    wire_def_pipe,
    inst_def_pipe,
    '',
    '\t' + switch_type + '_cluster #(',
    '\t\t.num_leaves(num_leaves),',
    '\t\t.payload_sz(payload_sz),',
    '\t\t.addr(addr),',
    '\t\t.level(level),',
    '\t\t.p_sz(p_sz),',
    '\t\t.num_switches(' + str(num_switches_in_cluster) + '))',
    '\t\t' + switch_type + '_lvl' + str(level) + '(',
    '\t\t\t.clk(clk),',
    '\t\t\t.reset(reset),',
    '\t\t\t.u_bus_i(bus_i),' if level > 0 else '',
    '\t\t\t.u_bus_o(bus_o),' if level > 0 else '',
    '\t\t\t.l_bus_i(left_switch),',
    '\t\t\t.r_bus_i(right_switch),',
    '\t\t\t.l_bus_o(switch_left_0),' if (args.pipeline) else '\t\t\t.l_bus_o(switch_left),',
    '\t\t\t.r_bus_o(switch_right_0));' if (args.pipeline) else '\t\t\t.r_bus_o(switch_right));',
    '',
    '\t' + subtree_name + ' #(',
    '\t\t.num_leaves(num_leaves),',
    '\t\t.payload_sz(payload_sz),',
    '\t\t.addr({' + ('addr, ' if level > 0 else '') +  '1\'b0}),',
    '\t\t.p_sz(p_sz))',
    '\t\tsubtree_left(',
    '\t\t\t.clk(clk),',
    '\t\t\t.reset(reset),',
    '\t\t\t.bus_i(switch_left),',
    '\t\t\t.bus_o(left_switch_0),' if (args.pipeline) else '\t\t\t.bus_o(left_switch),',
    '\t\t\t.pe_interface(pe_interface[p_sz*' + 
        str(num_leaves_in_subtree // 2) + '-1:0]),',
    '\t\t\t.interface_pe(interface_pe[p_sz*' + 
        str(num_leaves_in_subtree // 2) + '-1:0]),',
    '\t\t\t.resend(resend[' + str(num_leaves_in_subtree //2 ) + '-1:0]));',
    '',
    '\t' + subtree_name+ ' #(',
    '\t\t.num_leaves(num_leaves),',
    '\t\t.payload_sz(payload_sz),',
    '\t\t.addr({' + ('addr, ' if level > 0 else '') +  '1\'b1}),',
    '\t\t.p_sz(p_sz))',
    '\t\tsubtree_right(',
    '\t\t\t.clk(clk),',
    '\t\t\t.reset(reset),',
    '\t\t\t.bus_i(switch_right),',
    '\t\t\t.bus_o(right_switch_0),' if (args.pipeline) else '\t\t\t.bus_o(right_switch),',
    '\t\t\t.pe_interface(pe_interface[p_sz*' + str(num_leaves_in_subtree) + 
        '-1:p_sz*' + str(num_leaves_in_subtree // 2) + ']),',
    '\t\t\t.interface_pe(interface_pe[p_sz*' + str(num_leaves_in_subtree) + 
        '-1:p_sz*' + str(num_leaves_in_subtree // 2) + ']),',
    '\t\t\t.resend(resend[' + str(num_leaves_in_subtree) + '-1:' + 
        str(num_leaves_in_subtree // 2) + ']));',
    'endmodule',
    create_subtrees(args, num_leaves, pattern[0:-1], level= level + 1)])

def eval_pattern(pattern):
    pattern_list= [int(c) for c in list(pattern)]
    return (sum(list(pattern_list)) / len(pattern_list)) - 1

def create_pattern(num_leaves, p):
    pattern_sz= clog2(num_leaves)
    pattern= ''
    
    for _ in range(0, pattern_sz):
        if eval_pattern(pattern + '1') < p:
            pattern += '2'
        else:
            pattern += '1'
    return pattern
    
def create_leafless_network(num_leaves, p, num_sent_per_leaf, args):
    pattern= create_pattern(num_leaves, p)
    if (args.flatten):
        return create_flat(args, num_leaves, pattern, num_sent_per_leaf)
    else:
        return create_subtrees(args, num_leaves, pattern, num_sent_per_leaf)

def generate_axi_pe(num_leaves, p, num_sent_per_leaf, args):
    pattern= create_pattern(num_leaves, p)
    print("patter"+str(pattern))



    return '\n'.join([
    'module gen_nw_top # (',
    '\tparameter arm_data_width = 96,',
    '\tparameter num_leaves= 8,',
    '\tparameter payload_sz= $clog2(num_leaves) + 4,',
    '\tparameter p_sz= 1 + $clog2(num_leaves) + payload_sz, //packet size',
    '\tparameter addr= 3\'b000,',
    '\tparameter level= 0',
    '\t)(',
    '\tinput clk,',
    '\tinput [arm_data_width-1:0] data_in,',
    '\toutput reg [arm_data_width-1:0] data_out,',
    '\tinput start,',
    '\tinput reset',
    ');',
    '\twire [p_sz*' + str(num_leaves) +'-1:0] pe_interface;',
    '\twire [p_sz*' + str(num_leaves) +'-1:0] interface_pe;',
    '\twire [' + str(num_leaves) + '-1:0] resend;',
    '\twire [p_sz-1:0] data_out_wire;',
    '\talways@(*)begin',
    '\t\tdata_out = 0;',
    '\t\tif(data_out_wire[p_sz-1])',
    '\t\t\tdata_out[p_sz-2:0] = data_out_wire[p_sz-2:0];',
    '\tend',
    '\tpe_start #(',
    '\t\t.addr(0),',
    '\t\t.p_sz(p_sz)',
    '\t\t)pe_0(',
    '\t\t.clk(clk),',
    '\t\t.reset(reset),',
    '\t\t.pe_interface(pe_interface[p_sz-1:0]),',
    '\t\t.interface_pe(interface_pe[p_sz-1:0]),',
    '\t\t.resend(resend[0]),',
    '\t\t.start(start),',
    '\t\t.data_in(data_in),',
    '\t\t.data_out(data_out_wire)',
    '\t\t);',
    '\tgenvar i;',
    '\tgenerate',
    '\tfor (i= 1; i < ' + str(num_leaves) + '; i= i + 1) begin',
    '\t\tpe_shift #(',
    '\t\t.addr(i),',
    '\t\t.p_sz(p_sz)',
    '\t\t)pe_1(',
    '\t\t.clk(clk),',
    '\t\t.reset(reset),',
    '\t\t.pe_interface(pe_interface[i*p_sz+:p_sz]),',
    '\t\t.interface_pe(interface_pe[i*p_sz+:p_sz]),',
    '\t\t.resend(resend[i])',
    '\t\t);',
    '\tend',
    '\tendgenerate',
    '\tgen_nw #(',
    '\t\t.num_leaves(num_leaves),',
    '\t\t.payload_sz(payload_sz),',
    '\t\t.p_sz(p_sz),',
    '\t\t.addr(1\'b0),',
    '\t\t.level(0)',
    '\t)gen_nw_1(',
    '\t\t.clk(clk),',
    '\t\t.reset(reset),',
    '\t\t.pe_interface(pe_interface),',
    '\t\t.interface_pe(interface_pe),',
    '\t\t.resend(resend)',
    '\t);',
    'endmodule',
    '',
    'module pe_shift(',
    '\tinput clk,',
    '\tinput reset,',
    '\toutput reg [p_sz-1:0] pe_interface,',
    '\tinput [p_sz-1:0]interface_pe,',
    '\tinput resend',
    '\t);',
    '\tparameter num_leaves= 8;',
    '\tparameter payload_sz= $clog2(num_leaves) + ' + str(args.package_size - clog2(args.num_leaves) * 2 - 1) + ';',
    '\tparameter p_sz= 1 + $clog2(num_leaves) + payload_sz; //packet size',
    '\tparameter addr=1;',
    '\tparameter level= 0;',
    '\talways@(posedge clk or posedge reset) begin',
    '\t\tif(reset) begin',
    '\t\t\tpe_interface <= 0;',
    '\t\tend else begin',
    '\t\t\t\tif (resend) begin',
    '\t\t\t\t\tpe_interface <= 0;',
    '\t\t\t\tend else begin   ',
    '\t\t\t\t\tpe_interface[p_sz-2-2*$clog2(num_leaves):0] <= interface_pe[p_sz-2-2*$clog2(num_leaves):0] + 1;',
    '\t\t\t\t\tpe_interface[p_sz-2-$clog2(num_leaves):p_sz-1-2*$clog2(num_leaves)] <= interface_pe[p_sz-2-$clog2(num_leaves):p_sz-1-2*$clog2(num_leaves)] + 1;',
    '\t\t\t\t\tpe_interface[p_sz-2:p_sz-1-$clog2(num_leaves)] <= interface_pe[p_sz-2:p_sz-1-$clog2(num_leaves)] + 1;',
    '\t\t\t\t\tpe_interface[p_sz-1] <= interface_pe[p_sz-1];',
    '\t\t\t\tend',
    '\t\t\tend',
    '\t\tend',
    'endmodule',
    '',
    'module pe_start(',
    '\tinput clk,',
    '\tinput reset,',
    '\toutput reg [p_sz-1:0] pe_interface,',
    '\tinput [p_sz-1:0]interface_pe,',
    '\tinput resend,',
    '\tinput start,',
    '\tinput [p_sz-1:0] data_in,',
    '\toutput reg [p_sz-1:0] data_out',
    ');',
    '\tparameter num_leaves= 8;',
    '\tparameter payload_sz= $clog2(num_leaves) + 4;',
    '\tparameter p_sz= 1 + $clog2(num_leaves) + payload_sz;',
    '\tparameter addr= 3\'b000;',
    '\tparameter level= 0;',
    '\treg start_1, start_2;',
    '\talways@(posedge clk or posedge reset) begin',
    '\t\tif(reset) begin',
    '\t\t\tstart_1 <= 0;',
    '\t\t\tstart_2 <= 0;',
    '\t\t\tpe_interface <= 0;',
    '\t\tend else begin',
    '\t\t\t{start_2, start_1} <= {start_1, start};',
    '\t\t\tpe_interface[p_sz-1] <= start_2 ^ start_1;',
    '\t\t\tpe_interface[p_sz-2:0] <= data_in[p_sz-2:0];',
    '\t\tend',
    '\tend',
    '',
    '\talways@(posedge clk or posedge reset) begin',
    '\t\tif(reset) begin',
    '\t\t\tdata_out <= 0;',
    '\t\tend else begin',
    '\t\t\tif(interface_pe[p_sz-1]) data_out <= interface_pe;',
    '\t\tend',
    '\tend ',
    'endmodule'])


def create_flat(args, num_leaves, pattern, num_sent_per_leaf= 10, 
                     level= 0):
    str_to_return = '//--------level=' + str(level) + '--------------\n' 
    if pattern == '':
        for leaf_num in range(num_leaves//2):
            str_to_return = str_to_return + '\tinterface #(\n'
            str_to_return = str_to_return + '\t\t.num_leaves(num_leaves),\n' 
            str_to_return = str_to_return + '\t\t.payload_sz(payload_sz),\n'
            str_to_return = str_to_return + '\t\t.addr(' + str(leaf_num*2) + '),\n'
            str_to_return = str_to_return + '\t\t.p_sz(p_sz)\n'
            str_to_return = str_to_return + '\t\t)interface_' + str(leaf_num*2) + '(\n'
            str_to_return = str_to_return + '\t\t.clk(clk),\n' 
            str_to_return = str_to_return + '\t\t.reset(reset),\n'
            str_to_return = str_to_return + '\t\t.bus_i(switch_left_' + str(level-1) + '_' + str(leaf_num) +'),\n'
            str_to_return = str_to_return + '\t\t.bus_o(left_switch_' + str(level-1) + '_' + str(leaf_num) +'),\n'
            str_to_return = str_to_return + '\t\t.pe_interface(pe_interface[p_sz*' + str(leaf_num*2+1) + '-1:p_sz*' + str(leaf_num*2) + ']),\n'
            str_to_return = str_to_return + '\t\t.interface_pe(interface_pe[p_sz*' + str(leaf_num*2+1) + '-1:p_sz*' + str(leaf_num*2) + ']),\n'
            str_to_return = str_to_return + '\t\t.resend(resend['+ str(leaf_num*2) + ']));\n'
            str_to_return = str_to_return + '\n'
            str_to_return = str_to_return + '\tinterface #(\n'
            str_to_return = str_to_return + '\t\t.num_leaves(num_leaves),\n' 
            str_to_return = str_to_return + '\t\t.payload_sz(payload_sz),\n'
            str_to_return = str_to_return + '\t\t.addr(' + str(leaf_num*2+1) + '),\n'
            str_to_return = str_to_return + '\t\t.p_sz(p_sz)\n'
            str_to_return = str_to_return + '\t\t)interface_' + str(leaf_num*2+1) + '(\n'
            str_to_return = str_to_return + '\t\t.clk(clk),\n' 
            str_to_return = str_to_return + '\t\t.reset(reset),\n'
            str_to_return = str_to_return + '\t\t.bus_i(switch_right_' + str(level-1) + '_' + str(leaf_num) +'),\n'
            str_to_return = str_to_return + '\t\t.bus_o(right_switch_' + str(level-1) + '_' + str(leaf_num) +'),\n'
            str_to_return = str_to_return + '\t\t.pe_interface(pe_interface[p_sz*' + str(leaf_num*2+2) + '-1:p_sz*' + str(leaf_num*2+1) + ']),\n'
            str_to_return = str_to_return + '\t\t.interface_pe(interface_pe[p_sz*' + str(leaf_num*2+2) + '-1:p_sz*' + str(leaf_num*2+1) + ']),\n'
            str_to_return = str_to_return + '\t\t.resend(resend['+ str(leaf_num*2+1) + ']));\n'
        str_to_return = str_to_return + 'endmodule\n'
        return str_to_return
    else:
        switch_type= 't' if pattern[-1] == '1' else 'pi'
   
        num_switches_in_cluster= 1
        for c in [int(c) for c in pattern[0:-1]]:
            num_switches_in_cluster *= c
        num_leaves_in_subtree= num_leaves // (2**level)
        num_switches = 2**level
        addr_str= '1\'b0' 
        if num_switches > 1:
            for switch_num in range(num_switches):
                str_to_return = str_to_return + '\twire [p_sz*' + str(num_switches_in_cluster) + '-1:0] left_switch_' + str(level) + '_' + str(switch_num) + ';\n'
                str_to_return = str_to_return + '\twire [p_sz*' + str(num_switches_in_cluster) + '-1:0] right_switch_' + str(level) + '_' + str(switch_num) + ';\n'
                str_to_return = str_to_return + '\twire [p_sz*' + str(num_switches_in_cluster) + '-1:0] switch_left_' + str(level) + '_' + str(switch_num) + ';\n'
                str_to_return = str_to_return + '\twire [p_sz*' + str(num_switches_in_cluster) + '-1:0] switch_right_' + str(level) + '_' + str(switch_num) + ';\n'

        if num_switches == 1:
            str_to_return = str_to_return + 'module  gen_nw # (\n'
            str_to_return = str_to_return + '\tparameter num_leaves= ' + str(num_leaves) + ',\n'
            str_to_return = str_to_return + '\tparameter payload_sz= $clog2(num_leaves) + ' + str(clog2(num_sent_per_leaf)) + ',\n'
            str_to_return = str_to_return + '\tparameter p_sz= 1 + $clog2(num_leaves) + payload_sz, //packet size\n'
            str_to_return = str_to_return + '\tparameter addr= 0,\n'
            str_to_return = str_to_return + '\tparameter level= 0\n'
            str_to_return = str_to_return + '\t) (\n'
            str_to_return = str_to_return + '\tinput clk,\n'
            str_to_return = str_to_return + '\tinput reset,\n'
            str_to_return = str_to_return + '\tinput [p_sz*' + str(num_leaves_in_subtree) + '-1:0] pe_interface,\n'
            str_to_return = str_to_return + '\toutput [p_sz*' + str(num_leaves_in_subtree) + '-1:0] interface_pe,\n'
            str_to_return = str_to_return + '\toutput [' + str(num_leaves_in_subtree) + '-1:0] resend\n'
            str_to_return = str_to_return + '\t);\n'
            str_to_return = str_to_return + '\twire [p_sz*' + str(num_switches_in_cluster) + '-1:0] left_switch_0_0;\n'
            str_to_return = str_to_return + '\twire [p_sz*' + str(num_switches_in_cluster) + '-1:0] right_switch_0_0;\n'
            str_to_return = str_to_return + '\twire [p_sz*' + str(num_switches_in_cluster) + '-1:0] switch_left_0_0;\n'
            str_to_return = str_to_return + '\twire [p_sz*' + str(num_switches_in_cluster) + '-1:0] switch_right_0_0;\n'
            str_to_return = str_to_return + '\t' + switch_type + '_cluster #(\n'
            str_to_return = str_to_return + '\t\t.num_leaves(num_leaves),\n'
            str_to_return = str_to_return + '\t\t.payload_sz(payload_sz),\n'
            str_to_return = str_to_return + '\t\t.addr(addr),\n'
            str_to_return = str_to_return + '\t\t.level(level),\n'
            str_to_return = str_to_return + '\t\t.p_sz(p_sz),\n'
            str_to_return = str_to_return + '\t\t.num_switches(' + str(num_switches_in_cluster) + '))\n'
            str_to_return = str_to_return + '\t\t' + switch_type + '_lvl' + str(level) + '(\n'
            str_to_return = str_to_return + '\t\t.clk(clk),\n'
            str_to_return = str_to_return + '\t\t.reset(reset),\n'
            str_to_return = str_to_return + '\t\t.l_bus_i(left_switch_0_0),\n'
            str_to_return = str_to_return + '\t\t.r_bus_i(right_switch_0_0),\n'
            str_to_return = str_to_return + '\t\t.l_bus_o(switch_left_0_0),\n'
            str_to_return = str_to_return + '\t\t.r_bus_o(switch_right_0_0));\n'
            str_to_return = str_to_return + '\n'
        else:
            for switch_num in range(num_switches//2):
                str_to_return = str_to_return + '\t' + switch_type + '_cluster #(\n'
                str_to_return = str_to_return + '\t\t.num_leaves(num_leaves),\n'
                str_to_return = str_to_return + '\t\t.payload_sz(payload_sz),\n'
                str_to_return = str_to_return + '\t\t.addr(' + str(2*switch_num) + '),\n'
                str_to_return = str_to_return + '\t\t.level(' + str(level) + '),\n'
                str_to_return = str_to_return + '\t\t.p_sz(p_sz),\n'
                str_to_return = str_to_return + '\t\t.num_switches(' + str(num_switches_in_cluster) + ')\n'
                str_to_return = str_to_return + '\t\t)' + switch_type + '_lvl_' + str(level) + '_' + str(switch_num*2) + '(\n'
                str_to_return = str_to_return + '\t\t.clk(clk),\n'
                str_to_return = str_to_return + '\t\t.reset(reset),\n'
                str_to_return = str_to_return + '\t\t.u_bus_o(left_switch_' + str(level-1) + '_' + str(switch_num) +'),\n'
                str_to_return = str_to_return + '\t\t.u_bus_i(switch_left_' + str(level-1) + '_' + str(switch_num) +'),\n'
                str_to_return = str_to_return + '\t\t.l_bus_i(left_switch_' + str(level) + '_' + str(switch_num*2) + '),\n'
                str_to_return = str_to_return + '\t\t.r_bus_i(right_switch_' + str(level) + '_' + str(switch_num*2) + '),\n'
                str_to_return = str_to_return + '\t\t.l_bus_o(switch_left_' + str(level) + '_' + str(switch_num*2) + '),\n'
                str_to_return = str_to_return + '\t\t.r_bus_o(switch_right_' + str(level) + '_' + str(switch_num*2) + '));\n'
                str_to_return = str_to_return + '\n'
                str_to_return = str_to_return + '\t' + switch_type + '_cluster #(\n'
                str_to_return = str_to_return + '\t\t.num_leaves(num_leaves),\n'
                str_to_return = str_to_return + '\t\t.payload_sz(payload_sz),\n'
                str_to_return = str_to_return + '\t\t.addr(' + str(2*switch_num+1) + '),\n'
                str_to_return = str_to_return + '\t\t.level(' + str(level) + '),\n'
                str_to_return = str_to_return + '\t\t.p_sz(p_sz),\n'
                str_to_return = str_to_return + '\t\t.num_switches(' + str(num_switches_in_cluster) + ')\n'
                str_to_return = str_to_return + '\t\t)' + switch_type + '_lvl_' + str(level) + '_' + str(switch_num*2+1) + '(\n'
                str_to_return = str_to_return + '\t\t.clk(clk),\n'
                str_to_return = str_to_return + '\t\t.reset(reset),\n'
                str_to_return = str_to_return + '\t\t.u_bus_o(right_switch_' + str(level-1) + '_' + str(switch_num) +'),\n'
                str_to_return = str_to_return + '\t\t.u_bus_i(switch_right_' + str(level-1) + '_' + str(switch_num) +'),\n'
                str_to_return = str_to_return + '\t\t.l_bus_i(left_switch_' + str(level) + '_' + str(switch_num*2+1) + '),\n'
                str_to_return = str_to_return + '\t\t.r_bus_i(right_switch_' + str(level) + '_' + str(switch_num*2+1) + '),\n'
                str_to_return = str_to_return + '\t\t.l_bus_o(switch_left_' + str(level) + '_' + str(switch_num*2+1) + '),\n'
                str_to_return = str_to_return + '\t\t.r_bus_o(switch_right_' + str(level) + '_' + str(switch_num*2+1) + '));\n'
                str_to_return = str_to_return + '\n'    


    
    
    return '\n'.join([str_to_return,
    create_flat(args, num_leaves, pattern[0:-1], level= level + 1)])


       
