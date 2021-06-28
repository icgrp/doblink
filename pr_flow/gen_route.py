#!/usr/bin/env python
import os
import xml.etree.ElementTree

class direct_int:
  def __init__(self, prflow_params):
    self.prflow_params = prflow_params
  
  def gen_routing(self):
    os.system("rm -rf "+self.prflow_params['dest_dir'])
    os.system("mkdir "+self.prflow_params['dest_dir'])
    os.system("cp ./input/RelayStation.v " + self.prflow_params['dest_dir'])
    sw_level_0 = open(self.prflow_params["dest_dir"] + '/switch_level_0_0_route.v', 'w')
    sw_level_1_list = []
    for i in range(4):
      sw_level_1_list.append(open(self.prflow_params["dest_dir"]+ '/switch_level_1_'+str(i)+'_route.v', 'w'))
    
    sw_level_0.write('module switch_level_0_0_route#(\n')
    sw_level_0.write('  parameter PAYLOAD_BITS = '+self.prflow_params['payload_bits']+',\n')
    sw_level_0.write('  parameter NUM_IN_PORTS = '+self.prflow_params['num_in_ports']+',\n')
    sw_level_0.write('	parameter NUM_OUT_PORTS = '+self.prflow_params['num_out_ports']+',\n')
    sw_level_0.write('	parameter NUM_UP = '+self.prflow_params['l1_up_num']+'\n')
    sw_level_0.write('	)(\n')
    sw_level_0.write('  input clk,\n')
    sw_level_0.write('  input reset,\n')
    sw_level_0.write('  \n')
    sw_level_0.write('  input [PAYLOAD_BITS*NUM_UP-1:0] din_0,\n')
    sw_level_0.write('  input [PAYLOAD_BITS*NUM_UP-1:0] din_1,\n')
    sw_level_0.write('  input [PAYLOAD_BITS*NUM_UP-1:0] din_2,\n')
    sw_level_0.write('  input [PAYLOAD_BITS*NUM_UP-1:0] din_3,\n')
    sw_level_0.write('  \n')
    sw_level_0.write('  input [NUM_UP-1:0] val_in_0,\n')
    sw_level_0.write('  input [NUM_UP-1:0] val_in_1,\n')
    sw_level_0.write('  input [NUM_UP-1:0] val_in_2,\n')
    sw_level_0.write('  input [NUM_UP-1:0] val_in_3,\n')
    sw_level_0.write('  \n')
    sw_level_0.write('  output [NUM_UP-1:0] ready_upward_0,\n')
    sw_level_0.write('  output [NUM_UP-1:0] ready_upward_1,\n')
    sw_level_0.write('  output [NUM_UP-1:0] ready_upward_2,\n')
    sw_level_0.write('  output [NUM_UP-1:0] ready_upward_3,\n')
    sw_level_0.write('  \n')
    sw_level_0.write('  output [PAYLOAD_BITS*NUM_UP-1:0] dout_0,\n')
    sw_level_0.write('  output [PAYLOAD_BITS*NUM_UP-1:0] dout_1,\n')
    sw_level_0.write('  output [PAYLOAD_BITS*NUM_UP-1:0] dout_2,\n')
    sw_level_0.write('  output [PAYLOAD_BITS*NUM_UP-1:0] dout_3,\n')
    sw_level_0.write('  \n')
    sw_level_0.write('  output [NUM_UP-1:0] val_out_0,\n')
    sw_level_0.write('  output [NUM_UP-1:0] val_out_1,\n')
    sw_level_0.write('  output [NUM_UP-1:0] val_out_2,\n')
    sw_level_0.write('  output [NUM_UP-1:0] val_out_3,\n')
    sw_level_0.write('  \n')
    sw_level_0.write('  input [NUM_UP-1:0] ready_downward_0,\n')
    sw_level_0.write('  input [NUM_UP-1:0] ready_downward_1,\n')
    sw_level_0.write('  input [NUM_UP-1:0] ready_downward_2,\n')
    sw_level_0.write('  input [NUM_UP-1:0] ready_downward_3  \n')
    sw_level_0.write('  );\n')
  
    for i in range(4):
      sw_level_1_list[i].write('module switch_level_1_'+str(i)+'_route # (\n')
      sw_level_1_list[i].write('	parameter PAYLOAD_BITS = '+self.prflow_params['payload_bits']+',\n')
      sw_level_1_list[i].write('	parameter NUM_IN_PORTS = '+self.prflow_params['num_in_ports']+',\n')
      sw_level_1_list[i].write('	parameter NUM_OUT_PORTS = '+self.prflow_params['num_out_ports']+',\n')
      sw_level_1_list[i].write('	parameter NUM_UP = '+self.prflow_params['l1_up_num']+'\n')
      sw_level_1_list[i].write('	)(\n')
      sw_level_1_list[i].write('  input clk,\n')
      sw_level_1_list[i].write('  input reset,\n')
      sw_level_1_list[i].write('  \n')
      sw_level_1_list[i].write('  input [NUM_IN_PORTS*PAYLOAD_BITS-1:0] din_0,\n')
      sw_level_1_list[i].write('  input [NUM_IN_PORTS*PAYLOAD_BITS-1:0] din_1,\n')
      sw_level_1_list[i].write('  input [NUM_IN_PORTS*PAYLOAD_BITS-1:0] din_2,\n')
      sw_level_1_list[i].write('  input [NUM_IN_PORTS*PAYLOAD_BITS-1:0] din_3,\n')
      sw_level_1_list[i].write('  input [NUM_IN_PORTS*PAYLOAD_BITS-1:0] din_4,\n')
      sw_level_1_list[i].write('  input [NUM_IN_PORTS*PAYLOAD_BITS-1:0] din_5,\n')
      sw_level_1_list[i].write('  input [NUM_IN_PORTS*PAYLOAD_BITS-1:0] din_6,\n')
      sw_level_1_list[i].write('  input [NUM_IN_PORTS*PAYLOAD_BITS-1:0] din_7,\n')
      sw_level_1_list[i].write('  \n')
      sw_level_1_list[i].write('  input [NUM_IN_PORTS-1:0] val_in_0,\n')
      sw_level_1_list[i].write('  input [NUM_IN_PORTS-1:0] val_in_1,\n')
      sw_level_1_list[i].write('  input [NUM_IN_PORTS-1:0] val_in_2,\n')
      sw_level_1_list[i].write('  input [NUM_IN_PORTS-1:0] val_in_3,\n')
      sw_level_1_list[i].write('  input [NUM_IN_PORTS-1:0] val_in_4,\n')
      sw_level_1_list[i].write('  input [NUM_IN_PORTS-1:0] val_in_5,\n')
      sw_level_1_list[i].write('  input [NUM_IN_PORTS-1:0] val_in_6,\n')
      sw_level_1_list[i].write('  input [NUM_IN_PORTS-1:0] val_in_7,\n')
      sw_level_1_list[i].write('  \n')
      sw_level_1_list[i].write('  output [NUM_IN_PORTS-1:0] ready_upward_0,\n')
      sw_level_1_list[i].write('  output [NUM_IN_PORTS-1:0] ready_upward_1,\n')
      sw_level_1_list[i].write('  output [NUM_IN_PORTS-1:0] ready_upward_2,\n')
      sw_level_1_list[i].write('  output [NUM_IN_PORTS-1:0] ready_upward_3,\n')
      sw_level_1_list[i].write('  output [NUM_IN_PORTS-1:0] ready_upward_4,\n')
      sw_level_1_list[i].write('  output [NUM_IN_PORTS-1:0] ready_upward_5,\n')
      sw_level_1_list[i].write('  output [NUM_IN_PORTS-1:0] ready_upward_6,\n')
      sw_level_1_list[i].write('  output [NUM_IN_PORTS-1:0] ready_upward_7,\n')
      sw_level_1_list[i].write('  \n')
      sw_level_1_list[i].write('  output [NUM_OUT_PORTS*PAYLOAD_BITS-1:0] dout_0,\n')
      sw_level_1_list[i].write('  output [NUM_OUT_PORTS*PAYLOAD_BITS-1:0] dout_1,\n')
      sw_level_1_list[i].write('  output [NUM_OUT_PORTS*PAYLOAD_BITS-1:0] dout_2,\n')
      sw_level_1_list[i].write('  output [NUM_OUT_PORTS*PAYLOAD_BITS-1:0] dout_3,\n')
      sw_level_1_list[i].write('  output [NUM_OUT_PORTS*PAYLOAD_BITS-1:0] dout_4,\n')
      sw_level_1_list[i].write('  output [NUM_OUT_PORTS*PAYLOAD_BITS-1:0] dout_5,\n')
      sw_level_1_list[i].write('  output [NUM_OUT_PORTS*PAYLOAD_BITS-1:0] dout_6,\n')
      sw_level_1_list[i].write('  output [NUM_OUT_PORTS*PAYLOAD_BITS-1:0] dout_7,\n')
      sw_level_1_list[i].write('  \n')
      sw_level_1_list[i].write('  output [NUM_OUT_PORTS-1:0] val_out_0,\n')
      sw_level_1_list[i].write('  output [NUM_OUT_PORTS-1:0] val_out_1,\n')
      sw_level_1_list[i].write('  output [NUM_OUT_PORTS-1:0] val_out_2,\n')
      sw_level_1_list[i].write('  output [NUM_OUT_PORTS-1:0] val_out_3,\n')
      sw_level_1_list[i].write('  output [NUM_OUT_PORTS-1:0] val_out_4,\n')
      sw_level_1_list[i].write('  output [NUM_OUT_PORTS-1:0] val_out_5,\n')
      sw_level_1_list[i].write('  output [NUM_OUT_PORTS-1:0] val_out_6,\n')
      sw_level_1_list[i].write('  output [NUM_OUT_PORTS-1:0] val_out_7,\n')
      sw_level_1_list[i].write('  \n')
      sw_level_1_list[i].write('  input [NUM_OUT_PORTS-1:0] ready_downward_0,\n')
      sw_level_1_list[i].write('  input [NUM_OUT_PORTS-1:0] ready_downward_1,\n')
      sw_level_1_list[i].write('  input [NUM_OUT_PORTS-1:0] ready_downward_2,\n')
      sw_level_1_list[i].write('  input [NUM_OUT_PORTS-1:0] ready_downward_3,\n')
      sw_level_1_list[i].write('  input [NUM_OUT_PORTS-1:0] ready_downward_4,\n')
      sw_level_1_list[i].write('  input [NUM_OUT_PORTS-1:0] ready_downward_5,\n')
      sw_level_1_list[i].write('  input [NUM_OUT_PORTS-1:0] ready_downward_6,\n')
      sw_level_1_list[i].write('  input [NUM_OUT_PORTS-1:0] ready_downward_7,\n')
      sw_level_1_list[i].write('\n')
      sw_level_1_list[i].write('  input [NUM_UP*PAYLOAD_BITS-1:0] up_din,  \n')
      sw_level_1_list[i].write('  input [NUM_UP-1:0] up_val_in,  \n')
      sw_level_1_list[i].write('  output [NUM_UP-1:0] up_ready_upward,\n')
      sw_level_1_list[i].write('  \n')
      sw_level_1_list[i].write('  output [NUM_UP*PAYLOAD_BITS-1:0] up_dout,\n')
      sw_level_1_list[i].write('  output [NUM_UP-1:0] up_val_out,\n')
      sw_level_1_list[i].write('  input [NUM_UP-1:0] up_ready_downward\n')
      sw_level_1_list[i].write('  \n')
      sw_level_1_list[i].write('  );\n')
  
  
    root = xml.etree.ElementTree.parse(self.prflow_params['input_file_name'])
    links = root.findall('link')
    pp_level_1_num = [0 for index in range(int(self.prflow_params['sub_tree_num']))]
    pp_level_1_unit = int(self.prflow_params['l1_pp'])
    pp_level_0_num = 0
    pp_level_0_unit = int(self.prflow_params['l0_pp'])
    in_port_used_level_1 = [0 for index in range(int(self.prflow_params['sub_tree_num']))]
    out_port_used_level_1 = [0 for index in range(int(self.prflow_params['sub_tree_num']))]
    in_port_used_level_0 = [0 for index in range(int(self.prflow_params['sub_tree_num']))]
    out_port_used_level_0 = [0 for index in range(int(self.prflow_params['sub_tree_num']))]
    in_page_ports_used = [0 for index in range(2**int(self.prflow_params['addr_bits']))]
    out_page_ports_used = [0 for index in range(2**int(self.prflow_params['addr_bits']))]
  
    for child in links:
      src = child.get('source')
      dest =  child.get('destination')
      src_page_num = int(src.split('.')[0].replace('Function', ''))
      src_port_num = int(src.split('.')[1])
      dest_page_num = int(dest.split('.')[0].replace('Function', ''))
      dest_port_num = int(dest.split('.')[1])
      
      sub_tree_src =  int(src_page_num)/8
      sub_tree_dest = int(dest_page_num)/8
      same_sub_tree = (sub_tree_src == sub_tree_dest)
      
      in_page_ports_used[src_page_num] += 1
      out_page_ports_used[dest_page_num] += 1
  
  
      if same_sub_tree:
      # if source and dest are in the same sub_tree
      # we do not need to go up level
        sw_level_1_list[sub_tree_src].write('\n\n// ' + src + '=>' + dest + '\n')
        for i in range(pp_level_1_num[sub_tree_src], pp_level_1_num[sub_tree_src] + pp_level_1_unit):
          sw_level_1_list[sub_tree_src].write('\n\n  wire ready_downward'+str(i)+';\n')
          sw_level_1_list[sub_tree_src].write('  wire val_out'+str(i)+';\n')
          sw_level_1_list[sub_tree_src].write('  wire ready_upward'+str(i)+';\n')
          sw_level_1_list[sub_tree_src].write('  wire val_in'+str(i)+';\n')
          sw_level_1_list[sub_tree_src].write('  wire [PAYLOAD_BITS-1:0] din'+str(i)+';\n')
          sw_level_1_list[sub_tree_src].write('  wire [PAYLOAD_BITS-1:0] dout'+str(i)+';\n')
          sw_level_1_list[sub_tree_src].write('  \n')
          if (i == pp_level_1_num[sub_tree_src]):
            sw_level_1_list[sub_tree_src].write('  assign din'+str(i)+' = din_'+ str(src_page_num%8) + '['\
                                                + str(int(self.prflow_params['payload_bits'])*(src_port_num+1)-1)\
                                                + ':'\
                                                + str(int(self.prflow_params['payload_bits'])*src_port_num) + '];\n')
            sw_level_1_list[sub_tree_src].write('  assign val_in'+str(i)+' = val_in_' + str(src_page_num%8) + '['\
                                                + str(src_port_num)+'];\n')
            sw_level_1_list[sub_tree_src].write('  assign ready_upward_' + str(src_page_num%8) + '['\
                                                + str(src_port_num)+'] = ready_upward'+str(i)+';\n')
          else:
            sw_level_1_list[sub_tree_src].write('  assign din'+str(i)+' = dout'+str(i-1)+';\n')
            sw_level_1_list[sub_tree_src].write('  assign val_in'+str(i)+' = val_out'+str(i-1)+';\n')
            sw_level_1_list[sub_tree_src].write('  assign ready_downward'+str(i-1)+' = ready_upward'+str(i)+';\n')
          sw_level_1_list[sub_tree_src].write('  \n')
          sw_level_1_list[sub_tree_src].write('  RelayStation #(\n')
          sw_level_1_list[sub_tree_src].write('      .PAYLOAD_BITS(PAYLOAD_BITS)\n')
          sw_level_1_list[sub_tree_src].write('      )RelayStation'+str(i)+'(\n')
          sw_level_1_list[sub_tree_src].write('      .clk(clk),\n')
          sw_level_1_list[sub_tree_src].write('      .reset(reset),\n')
          sw_level_1_list[sub_tree_src].write('      .ready_downward(ready_downward'+str(i)+'),\n')
          sw_level_1_list[sub_tree_src].write('      .val_out(val_out'+str(i)+'),\n')
          sw_level_1_list[sub_tree_src].write('      .ready_upward(ready_upward'+str(i)+'),\n')
          sw_level_1_list[sub_tree_src].write('      .val_in(val_in'+str(i)+'),\n')
          sw_level_1_list[sub_tree_src].write('      .din(din'+str(i)+'),\n')
          sw_level_1_list[sub_tree_src].write('      .dout(dout'+str(i)+')\n')
          sw_level_1_list[sub_tree_src].write('      );\n')
        sw_level_1_list[sub_tree_src].write('  assign dout_'+ str(dest_page_num%8) + '['\
                                                + str(int(self.prflow_params['payload_bits'])*(dest_port_num+1)-1)\
                                                + ':'\
                                                + str(int(self.prflow_params['payload_bits'])*dest_port_num) + '] = dout'+str(i)+';\n')
        sw_level_1_list[sub_tree_src].write('  assign val_out_' + str(dest_page_num%8) + '['\
                                                + str(dest_port_num)+'] = val_out'+str(i)+';\n')
        sw_level_1_list[sub_tree_src].write('  assign ready_downward'+str(i)+' = ready_downward_' + str(dest_page_num%8) + '['\
                                                + str(dest_port_num)+'];\n')
  
  
        # update pipeline number
        pp_level_1_num[sub_tree_src] += pp_level_1_unit
      else:
        # construct relay stations for source sub_tree input
        sw_level_1_list[sub_tree_src].write('\n\n// ' + src + '=>' + dest + '\n')
        for i in range(pp_level_1_num[sub_tree_src], pp_level_1_num[sub_tree_src] + pp_level_1_unit):
          sw_level_1_list[sub_tree_src].write('\n\n  wire ready_downward'+str(i)+';\n')
          sw_level_1_list[sub_tree_src].write('  wire val_out'+str(i)+';\n')
          sw_level_1_list[sub_tree_src].write('  wire ready_upward'+str(i)+';\n')
          sw_level_1_list[sub_tree_src].write('  wire val_in'+str(i)+';\n')
          sw_level_1_list[sub_tree_src].write('  wire [PAYLOAD_BITS-1:0] din'+str(i)+';\n')
          sw_level_1_list[sub_tree_src].write('  wire [PAYLOAD_BITS-1:0] dout'+str(i)+';\n')
          sw_level_1_list[sub_tree_src].write('  \n')
          if (i == pp_level_1_num[sub_tree_src]):
            sw_level_1_list[sub_tree_src].write('  assign din'+str(i)+' = din_'+ str(src_page_num%8) + '['\
                                                + str(int(self.prflow_params['payload_bits'])*(src_port_num+1)-1)\
                                                + ':'\
                                                + str(int(self.prflow_params['payload_bits'])*src_port_num) + '];\n')
            sw_level_1_list[sub_tree_src].write('  assign val_in'+str(i)+' = val_in_' + str(src_page_num%8) + '['\
                                                + str(src_port_num)+'];\n')
            sw_level_1_list[sub_tree_src].write('  assign ready_upward_' + str(src_page_num%8) + '['\
                                                + str(src_port_num)+'] = ready_upward'+str(i)+';\n')
          else:
            sw_level_1_list[sub_tree_src].write('  assign din'+str(i)+' = dout'+str(i-1)+';\n')
            sw_level_1_list[sub_tree_src].write('  assign val_in'+str(i)+' = val_out'+str(i-1)+';\n')
            sw_level_1_list[sub_tree_src].write('  assign ready_downward'+str(i-1)+' = ready_upward'+str(i)+';\n')
          sw_level_1_list[sub_tree_src].write('  \n')
          sw_level_1_list[sub_tree_src].write('  RelayStation #(\n')
          sw_level_1_list[sub_tree_src].write('      .PAYLOAD_BITS(PAYLOAD_BITS)\n')
          sw_level_1_list[sub_tree_src].write('      )RelayStation'+str(i)+'(\n')
          sw_level_1_list[sub_tree_src].write('      .clk(clk),\n')
          sw_level_1_list[sub_tree_src].write('      .reset(reset),\n')
          sw_level_1_list[sub_tree_src].write('      .ready_downward(ready_downward'+str(i)+'),\n')
          sw_level_1_list[sub_tree_src].write('      .val_out(val_out'+str(i)+'),\n')
          sw_level_1_list[sub_tree_src].write('      .ready_upward(ready_upward'+str(i)+'),\n')
          sw_level_1_list[sub_tree_src].write('      .val_in(val_in'+str(i)+'),\n')
          sw_level_1_list[sub_tree_src].write('      .din(din'+str(i)+'),\n')
          sw_level_1_list[sub_tree_src].write('      .dout(dout'+str(i)+')\n')
          sw_level_1_list[sub_tree_src].write('      );\n')
        sw_level_1_list[sub_tree_src].write('  assign up_dout['\
                                                + str(int(self.prflow_params['payload_bits'])*(out_port_used_level_1[sub_tree_src]+1)-1)\
                                                + ':'\
                                                + str(int(self.prflow_params['payload_bits'])*out_port_used_level_1[sub_tree_src]) + '] = dout'+str(i)+';\n')
        sw_level_1_list[sub_tree_src].write('  assign up_val_out['\
                                                + str(out_port_used_level_1[sub_tree_src])+'] = val_out'+str(i)+';\n')
        sw_level_1_list[sub_tree_src].write('  assign ready_downward'+str(i)+' = up_ready_downward['\
                                                + str(out_port_used_level_1[sub_tree_src])+'];\n')
  
  
  
        # construct relay_station for destination sub_tree
        sw_level_1_list[sub_tree_dest].write('\n\n// ' + src + '=>' + dest + '\n')
        for i in range(pp_level_1_num[sub_tree_dest], pp_level_1_num[sub_tree_dest] + pp_level_1_unit):
          sw_level_1_list[sub_tree_dest].write('\n\n  wire ready_downward'+str(i)+';\n')
          sw_level_1_list[sub_tree_dest].write('  wire val_out'+str(i)+';\n')
          sw_level_1_list[sub_tree_dest].write('  wire ready_upward'+str(i)+';\n')
          sw_level_1_list[sub_tree_dest].write('  wire val_in'+str(i)+';\n')
          sw_level_1_list[sub_tree_dest].write('  wire [PAYLOAD_BITS-1:0] din'+str(i)+';\n')
          sw_level_1_list[sub_tree_dest].write('  wire [PAYLOAD_BITS-1:0] dout'+str(i)+';\n')
          sw_level_1_list[sub_tree_dest].write('  \n')
          if (i == pp_level_1_num[sub_tree_dest]):
            sw_level_1_list[sub_tree_dest].write('  assign din'+str(i)+' = up_din['\
                                                + str(int(self.prflow_params['payload_bits'])*(in_port_used_level_1[sub_tree_dest]+1)-1)\
                                                + ':'\
                                                + str(int(self.prflow_params['payload_bits'])*in_port_used_level_1[sub_tree_dest]) + '];\n')
            sw_level_1_list[sub_tree_dest].write('  assign val_in'+str(i)+' = up_val_in['\
                                                + str(in_port_used_level_1[sub_tree_dest])+'];\n')
            sw_level_1_list[sub_tree_dest].write('  assign up_ready_upward['\
                                                + str(in_port_used_level_1[sub_tree_dest])+'] = ready_upward'+str(i)+';\n')
          else:
            sw_level_1_list[sub_tree_dest].write('  assign din'+str(i)+' = dout'+str(i-1)+';\n')
            sw_level_1_list[sub_tree_dest].write('  assign val_in'+str(i)+' = val_out'+str(i-1)+';\n')
            sw_level_1_list[sub_tree_dest].write('  assign ready_downward'+str(i-1)+' = ready_upward'+str(i)+';\n')
          sw_level_1_list[sub_tree_dest].write('  \n')
          sw_level_1_list[sub_tree_dest].write('  RelayStation #(\n')
          sw_level_1_list[sub_tree_dest].write('      .PAYLOAD_BITS(PAYLOAD_BITS)\n')
          sw_level_1_list[sub_tree_dest].write('      )RelayStation'+str(i)+'(\n')
          sw_level_1_list[sub_tree_dest].write('      .clk(clk),\n')
          sw_level_1_list[sub_tree_dest].write('      .reset(reset),\n')
          sw_level_1_list[sub_tree_dest].write('      .ready_downward(ready_downward'+str(i)+'),\n')
          sw_level_1_list[sub_tree_dest].write('      .val_out(val_out'+str(i)+'),\n')
          sw_level_1_list[sub_tree_dest].write('      .ready_upward(ready_upward'+str(i)+'),\n')
          sw_level_1_list[sub_tree_dest].write('      .val_in(val_in'+str(i)+'),\n')
          sw_level_1_list[sub_tree_dest].write('      .din(din'+str(i)+'),\n')
          sw_level_1_list[sub_tree_dest].write('      .dout(dout'+str(i)+')\n')
          sw_level_1_list[sub_tree_dest].write('      );\n')
        sw_level_1_list[sub_tree_dest].write('  assign dout_'+ str(dest_page_num%8) + '['\
                                                + str(int(self.prflow_params['payload_bits'])*(dest_port_num+1)-1)\
                                                + ':'\
                                                + str(int(self.prflow_params['payload_bits'])*dest_port_num) + '] = dout'+str(i)+';\n')
        sw_level_1_list[sub_tree_dest].write('  assign val_out_' + str(dest_page_num%8) + '['\
                                                + str(dest_port_num)+'] = val_out'+str(i)+';\n')
        sw_level_1_list[sub_tree_dest].write('  assign ready_downward'+str(i)+' = ready_downward_' + str(dest_page_num%8) + '['\
                                                + str(dest_port_num)+'];\n')
  
  
        # construct relay_station for swtich box level 0
        sw_level_0.write('\n\n// ' + src + '=>' + dest + '\n')
        for i in range(pp_level_0_num, pp_level_0_num + pp_level_0_unit):
          sw_level_0.write('\n\n  wire ready_downward'+str(i)+';\n')
          sw_level_0.write('  wire val_out'+str(i)+';\n')
          sw_level_0.write('  wire ready_upward'+str(i)+';\n')
          sw_level_0.write('  wire val_in'+str(i)+';\n')
          sw_level_0.write('  wire [PAYLOAD_BITS-1:0] din'+str(i)+';\n')
          sw_level_0.write('  wire [PAYLOAD_BITS-1:0] dout'+str(i)+';\n')
          sw_level_0.write('  \n')
          if (i == pp_level_0_num):
            sw_level_0.write('  assign din'+str(i)+' = din_'+str(sub_tree_src)+'['\
                                                + str(int(self.prflow_params['payload_bits'])*(in_port_used_level_0[sub_tree_src]+1)-1)\
                                                + ':'\
                                                + str(int(self.prflow_params['payload_bits'])*in_port_used_level_0[sub_tree_src]) + '];\n')
            sw_level_0.write('  assign val_in'+str(i)+' = val_in_'+str(sub_tree_src)+'['\
                                                + str(in_port_used_level_0[sub_tree_src])+'];\n')
            sw_level_0.write('  assign ready_upward_'+str(sub_tree_src)+'['\
                                                + str(in_port_used_level_0[sub_tree_src])+'] = ready_upward'+str(i)+';\n')
          else:
            sw_level_0.write('  assign din'+str(i)+' = dout'+str(i-1)+';\n')
            sw_level_0.write('  assign val_in'+str(i)+' = val_out'+str(i-1)+';\n')
            sw_level_0.write('  assign ready_downward'+str(i-1)+' = ready_upward'+str(i)+';\n')
          sw_level_0.write('  \n')
          sw_level_0.write('  RelayStation #(\n')
          sw_level_0.write('      .PAYLOAD_BITS(PAYLOAD_BITS)\n')
          sw_level_0.write('      )RelayStation'+str(i)+'(\n')
          sw_level_0.write('      .clk(clk),\n')
          sw_level_0.write('      .reset(reset),\n')
          sw_level_0.write('      .ready_downward(ready_downward'+str(i)+'),\n')
          sw_level_0.write('      .val_out(val_out'+str(i)+'),\n')
          sw_level_0.write('      .ready_upward(ready_upward'+str(i)+'),\n')
          sw_level_0.write('      .val_in(val_in'+str(i)+'),\n')
          sw_level_0.write('      .din(din'+str(i)+'),\n')
          sw_level_0.write('      .dout(dout'+str(i)+')\n')
          sw_level_0.write('      );\n')
        sw_level_0.write('  assign dout_'+ str(sub_tree_dest) + '['\
                                                + str(int(self.prflow_params['payload_bits'])*(out_port_used_level_0[sub_tree_dest]+1)-1)\
                                                + ':'\
                                                + str(int(self.prflow_params['payload_bits'])*out_port_used_level_0[sub_tree_dest]) + '] = dout'+str(i)+';\n')
        sw_level_0.write('  assign val_out_' + str(sub_tree_dest) + '['\
                                                + str(out_port_used_level_0[sub_tree_dest])+'] = val_out'+str(i)+';\n')
        sw_level_0.write('  assign ready_downward'+str(i)+' = ready_downward_' + str(sub_tree_dest) + '['\
                                                + str(out_port_used_level_0[sub_tree_dest])+'];\n')
  
        # update pipeline number and used port number
        pp_level_0_num += pp_level_0_unit
        pp_level_1_num[sub_tree_src] += pp_level_1_unit
        pp_level_1_num[sub_tree_dest] += pp_level_1_unit
        out_port_used_level_0[sub_tree_dest] += 1
        in_port_used_level_0[sub_tree_src] += 1
        out_port_used_level_1[sub_tree_src] += 1
        in_port_used_level_1[sub_tree_dest] += 1
  
    sw_level_0.write('\n\n// assignment for used pins in switch_level_0_route.v\n')
    for i in range(len(in_port_used_level_0)):
      sw_level_0.write('\n')
      for j in range(in_port_used_level_0[i], int(self.prflow_params['l1_up_num'])):      
        sw_level_0.write('  assign ready_upward_'+str(i)+'['+str(j)+'] = 0;\n')
      for j in range(out_port_used_level_0[i], int(self.prflow_params['l1_up_num'])):      
        sw_level_0.write('  assign dout_'+str(i)+'['\
                         + str((j+1)*(int(self.prflow_params['payload_bits']))-1)+':'\
                         + str(j*int(self.prflow_params['payload_bits']))+ '] = 0;\n')
        sw_level_0.write('  assign val_out_'+str(i)+'['+str(j)+']=0;\n')
  
    for i in range(len(in_port_used_level_1)):
      sw_level_1_list[i].write('\n')
      for j in range(in_port_used_level_1[i], int(self.prflow_params['l1_up_num'])):      
        sw_level_1_list[i].write('  assign up_ready_upward['+str(j)+'] = 0;\n')
      for j in range(out_port_used_level_1[i], int(self.prflow_params['l1_up_num'])):      
        sw_level_1_list[i].write('  assign up_dout['\
                         + str((j+1)*(int(self.prflow_params['payload_bits']))-1)+':'\
                         + str(j*int(self.prflow_params['payload_bits']))+ '] = 0;\n')
        sw_level_1_list[i].write('  assign up_val_out['+str(j)+']=0;\n')
  
    # assign used ports connected to pages to 0
    for i in range(len(in_page_ports_used)):
      sub_tree_num = i/8
      # for switch_level 1, input and output are conversed to page
      for j in range(in_page_ports_used[i], int(self.prflow_params['num_out_ports'])):  
      # find all unused input ports in switch_level_1 
        sw_level_1_list[sub_tree_num].write('  assign ready_upward_'+str(i%8)+'['+str(j)+'] = 0;\n')
      for j in range(out_page_ports_used[i], int(self.prflow_params['num_in_ports'])):   
      # find all unused output ports in switch_level_1
        sw_level_1_list[sub_tree_num].write('  assign dout_'+str(i%8)+'['\
                         + str((j+1)*(int(self.prflow_params['payload_bits']))-1)+':'\
                         + str(j*int(self.prflow_params['payload_bits']))+ '] = 0;\n')
        sw_level_1_list[sub_tree_num].write('  assign val_out_'+str(i%8)+'['+str(j)+']=0;\n')
  
  
    sw_level_0.write('\n\nendmodule\n')
    sw_level_0.close()
    for i in range(4):
      sw_level_1_list[i].write('\n\nendmodule\n')
      sw_level_1_list[i].close()
  
  
if __name__ == '__main__':
  prflow_params = {
          "dest_dir": "./output",
          "input_file_name": "./input/architecture.xml",
          "sub_tree_num": "4",
          "num_in_ports": '2',
          "num_out_ports": '2',
          "l1_up_num": '4',
          "l0_pp": "8",
          "l1_pp": "4",
          "payload_bits": '32',
          "addr_bits": '5'
          }
  
  direc_inst = direct_int(prflow_params)
  direc_inst.gen_routing()
  print "The output verilog files are under ./output" 
