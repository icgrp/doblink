### config_gen: generate the config_<benchmark_name>.cpp and config_<benchmark.h files for PrFlow
# Created by: Yuanlong Xiao (yuanlongxiao24@gmail.com)
#         at: University of Pennsylvania
#         in: 2018       
           
#
# The big picture:
# config_gen will generate files by using different parameters
# How it works (in a nutshell):
# Run command "python config_gen.py"
# [1] D. Park, Y. Xiao and A. DeHon, "Case for Acceleration of FPGA Compilation using Partial Reconfiguration", FPL2018
# [2] Y. Xiao, D. Park, A. Butt, H. Giesen, Z. Han, R. Ding, N. Magnezi, R. Rubin and A. DeHon. "Reducing FPGA compile time with separate compilation for FPGA building blocks", FPT2019
# [3] Y. Xiao, S. Ahmed and A. DeHon. "Fast Linking of Separately-Compiled FPGA Blockswithout a NoC", FPT2020


import time
from gen_basic import gen_basic
import re

class config(gen_basic):
  def __init__(self, prflow_params):
    gen_basic.__init__(self, prflow_params)
    self.packet_bits        = int(self.prflow_params['packet_bits'])
    self.addr_bits          = int(self.prflow_params['addr_bits']) 
    self.port_bits          = int(self.prflow_params['port_bits'])
    self.payload_bits       = int(self.prflow_params['payload_bits'])
    self.bram_addr_bits     = int(self.prflow_params['bram_addr_bits'])
    self.freespace          = int(self.prflow_params['freespace'])
    self.page_addr_offset   = self.packet_bits - 1 - self.addr_bits
    self.port_offset        = self.packet_bits - 1 - self.addr_bits - self.port_bits
    self.config_port_offset = self.payload_bits - self.port_bits
    self.dest_page_offset   = self.payload_bits - self.port_bits - self.addr_bits
    self.dest_port_offset   = self.payload_bits - self.port_bits - self.addr_bits - self.port_bits
    self.src_page_offset    = self.payload_bits - self.port_bits - self.addr_bits
    self.src_port_offset    = self.payload_bits - self.port_bits - self.addr_bits - self.port_bits
    self.freespace_offset   = self.payload_bits - self.port_bits - self.addr_bits - self.port_bits - self.bram_addr_bits - self.bram_addr_bits
  # find all the operators page num  
  def return_page_num_dict_local(self, operators):
    operator_list = operators.split()
    page_num_dict = {'DMA':1, 'ARM':0}
    for operator in operator_list:
      HW_exist, target = self.pragma.return_pragma('./input_src/'+self.prflow_params['benchmark_name']+'/operators/'+operator+'.h', 'map_target')
      page_exist, page_num = self.pragma.return_pragma('./input_src/'+self.prflow_params['benchmark_name']+'/operators/'+operator+'.h', 'page_num')
      if HW_exist and target=='HW' and page_exist:
        page_num_dict[operator] = page_num
    return page_num_dict 

  # find all the operators arguments order
  # in case the user define the input and output arguments out of order 
  def return_operator_io_argument_dict_local(self, operators):
    operator_list = operators.split()
    operator_arg_dict = {}
    for operator in operator_list:
      file_list = self.shell.file_to_list('./input_src/'+self.prflow_params['benchmark_name']+'/operators/'+operator+'.h')
      arguments_list = [] 
      def_valid = False # Ture if function definition begins
      def_str = ''
      for line in file_list:
        if self.shell.have_target_string(line, '('): def_valid = True
        if def_valid: 
          line_str=re.sub('\s+', '', line)
          line_str=re.sub('\t+', '', line_str)
          def_str=def_str+line_str
        if self.shell.have_target_string(line, ')'): def_valid = False

      # a list for the stream arguments functions
      arg_str_list = def_str.split(',')
      for arg_str in arg_str_list:
        input_str_list = re.findall(r"Input_\d+", arg_str)
        output_str_list = re.findall(r"Output_\d+", arg_str)
        input_str_list.extend(output_str_list)
        io_str = input_str_list
        arguments_list.append(io_str[0])
       
      operator_arg_dict[operator] = arguments_list
    
    return operator_arg_dict 


  # find all the operators instantiation in the top function
  def return_operator_inst_dict_local(self, operators):
    operator_list = operators.split()
    operator_var_dict = {}
    file_list = self.shell.file_to_list('./input_src/'+self.prflow_params['benchmark_name']+'/host/top.cpp')
    for operator in operator_list:
      arguments_list = [] 
      inst_valid = False # Ture if function definition begins
      inst_str = ''
      for line in file_list:
        if self.shell.have_target_string(line, operator+'('): inst_valid = True
        if inst_valid: 
          line_str=re.sub('\s+', '', line)
          line_str=re.sub('\t+', '', line_str)
          line_str=re.sub('//.*', '', line_str)
          inst_str=inst_str+line_str
        if self.shell.have_target_string(line, ')'): inst_valid = False
      inst_str = inst_str.replace(operator+'(','')
      inst_str = inst_str.replace(');','')
      var_str_list = inst_str.split(',')
      operator_var_dict[operator] = var_str_list
    
    return operator_var_dict 


  def return_operator_connect_list_local(self, operator_arg_dict, operator_var_dict):
    connection_list = []
    for key_a in operator_var_dict:
      for i_a, var_value_a in enumerate(operator_var_dict[key_a]):
        if var_value_a == 'Input_1': 
          tmp_str='DMA.Output_1->'+key_a+'.Input_1' 
          connection_list.append(tmp_str)
        if var_value_a == 'Output_1': 
          tmp_str=key_a+'.Output_1->'+'DMA.Input_1'
          connection_list.append(tmp_str)
        for key_b in operator_var_dict:
          for i_b, var_value_b in enumerate(operator_var_dict[key_b]):
            if var_value_a==var_value_b and key_a!=key_b:
              if self.shell.have_target_string(operator_arg_dict[key_a][i_a], 'Input'):
                tmp_str = key_b+'.'+operator_arg_dict[key_b][i_b]+'->'+key_a+'.'+operator_arg_dict[key_a][i_a]
              else:
                tmp_str = key_a+'.'+operator_arg_dict[key_a][i_a]+'->'+key_b+'.'+operator_arg_dict[key_b][i_b]
              connection_list.append(tmp_str)
    connection_list = set(connection_list)
    return connection_list


  def return_config_packet_list_local(self, page_num_dict, connection_list):
    packet_list = []
    for str_value in connection_list:
      packet_list.append('//'+str_value)
      str_list = str_value.split('->')
      [src_operator, src_output] = str_list[0].split('.')
      [dest_operator, dest_input] = str_list[1].split('.')
      src_page = int(page_num_dict[src_operator])
      src_port = int(src_output.replace('Output_',''))+int(self.prflow_params['output_port_base'])-1
      dest_page = int(page_num_dict[dest_operator])
      dest_port = int(dest_input.replace('Input_',''))+int(self.prflow_params['input_port_base'])-1
      print src_page,src_port,'->',dest_page,dest_port 
      src_page_packet =                   (src_page  << self.page_addr_offset)
      src_page_packet = src_page_packet + (       0  << self.port_offset)
      src_page_packet = src_page_packet + (src_port  << self.config_port_offset)
      src_page_packet = src_page_packet + (dest_page << self.dest_page_offset)
      src_page_packet = src_page_packet + (dest_port << self.dest_port_offset)
      src_page_packet = src_page_packet + ((2**self.bram_addr_bits-1) << self.freespace_offset)
      value_low  =  (src_page_packet      ) & 0xffffffff
      value_high =  (src_page_packet >> 32) & 0xffffffff
      #print 'src_page_packet: ', str(hex(value_high)).replace('L', ''), str(hex(value_low)).replace('L', '') 
      packet_list.append("  write_to_fifo(" + str(hex(value_high)).replace('L', '') + ', ' + str(hex(value_low)).replace('L', '') + ", &ctrl_reg);")

      dest_page_packet =                    (dest_page  << self.page_addr_offset)
      dest_page_packet = dest_page_packet + (        1  << self.port_offset)
      dest_page_packet = dest_page_packet + (dest_port  << self.config_port_offset)
      dest_page_packet = dest_page_packet + (src_page   << self.src_page_offset)
      dest_page_packet = dest_page_packet + (src_port   << self.src_port_offset)
      value_low  =  (dest_page_packet      ) & 0xffffffff
      value_high =  (dest_page_packet >> 32) & 0xffffffff
      #print 'src_page_packet: ', str(hex(value_high)).replace('L', ''), str(hex(value_low)).replace('L', '') 
      packet_list.append("  write_to_fifo(" + str(hex(value_high)).replace('L', '') + ', ' + str(hex(value_low)).replace('L', '') + ", &ctrl_reg);")

    return packet_list

  def return_run_sdk_sh_list_local(self, vivado_dir, tcl_file):
    return ([
      '#!/bin/bash -e',
      'source ' + vivado_dir,
      'xsdk -batch -source ' + tcl_file,
      ''])


 
  def run(self, operators):
    self.shell.re_mkdir(self.sdk_dir+'/')
    self.shell.re_mkdir(self.sdk_dir+'/cpp_src')
    self.shell.cp_dir('./common/driver_src/config.cpp', self.sdk_dir+'/cpp_src/config_'+self.prflow_params['benchmark_name']+'.cpp')
    self.shell.cp_dir(self.mono_bft_dir+'/prj/floorplan_static.sdk/floorplan_static_wrapper.hdf', self.sdk_dir)
    self.shell.cp_dir('./common/driver_src/config.h', self.sdk_dir+'/cpp_src/config_'+self.prflow_params['benchmark_name']+'.h')
    self.shell.cp_dir('./common/script_src/project_xsdk_core.tcl', self.sdk_dir)
    self.shell.cp_dir('./input_src/'+self.prflow_params['benchmark_name']+'/sdk/*', self.sdk_dir+'/cpp_src')

    page_num_dict = self.return_page_num_dict_local(operators)
    operator_arg_dict = self.return_operator_io_argument_dict_local(operators)
    operator_var_dict = self.return_operator_inst_dict_local(operators)
    connection_list=self.return_operator_connect_list_local(operator_arg_dict, operator_var_dict)
    packet_list = self.return_config_packet_list_local(page_num_dict, connection_list)
    self.shell.add_lines(self.sdk_dir+'/cpp_src/config_'+self.prflow_params['benchmark_name']+'.cpp', '//packet anchor', packet_list) 

    replace_dict={'set Benchmark_name': "set Benchmark_name " + self.prflow_params['benchmark_name']}
    self.shell.replace_lines(self.sdk_dir+'/project_xsdk_core.tcl', replace_dict)

    self.shell.write_lines(self.sdk_dir+'/run_project_xsdk.sh', self.return_run_sdk_sh_list_local(self.prflow_params['Xilinx_dir'], 'project_xsdk_core.tcl'), True)    
    self.shell.write_lines(self.sdk_dir+'/main.sh', self.shell.return_main_sh_list('run_project_xsdk.sh'), True)
    

