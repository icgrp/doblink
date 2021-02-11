# -*- coding: utf-8 -*-   
# Company: IC group, University of Pennsylvania
# Engineer: Yuanlong Xiao
#
# Create Date: 02/11/2021
# Design Name: overlay
# Project Name: DIRC
# Versions: 1.0
# Description: This is a python script to prepare the script for Out-Context-Synthesis 
#              from verilog to DCP for PRFlow
# Dependencies: python2, gen_basic.py, config.py
# Revision:
# Revision 0.01 - File Created
#
# Additional Comments:



import os  
import subprocess
from gen_basic import gen_basic
import pr_flow.config as config
import re


class syn(gen_basic):

  # from the source header file, find the input or output number
  def return_io_num(self, io_pattern, file_list):
    max_num = 0
    for line in file_list:
      num_list = re.findall(r""+io_pattern+"\d*", line)
      if(len(num_list)>0 and int(num_list[0].replace(io_pattern,''))): max_num = int(num_list[0].replace(io_pattern,''))
    return max_num
  
  def return_bit_size(self, num):
    bit_size = 1
    num_local = int(num)
    while (True):
      if (num_local >> 1) != 0:
        num_local = num_local >> 1 
        bit_size = bit_size + 1
      else:
        return bit_size

  # create one directory for each page 
  def create_page(self, operator):
    self.shell.re_mkdir(self.syn_dir+'/'+operator)
 
    map_target, page_num, input_num, output_num =  self.return_map_target(operator)
    if map_target == 'HW': 
      # If the map target is Hardware, we need to prepare the HDL files and scripts to 
      # compile it.

      self.shell.mkdir(self.syn_dir+'/'+operator+'/src')
      file_list = [
        'src/Config_Controls.v',
        'src/converge_ctrl.v',
        'src/ExtractCtrl.v',
        'src/Input_Port_Cluster.v',
        'src/Input_Port.v',
        'src/leaf_interface.v',
        'src/Output_Port_Cluster.v',
        'src/Output_Port.v',
        'src/read_b_in.v',
        'src/instr_config.v',
        'src/rise_detect.v',
        'src/Stream_Flow_Control.v',
        'src/write_b_in.v',
        'src/write_b_out.v']
      # copy the necessary leaf interface verilog files for out-of-context compilation
      for name in file_list: self.shell.cp_file(self.overlay_dir+'/'+name, self.syn_dir+'/'+operator+'/'+name)

      # prepare the tcl files for out-of-context compilation
      self.shell.write_lines(self.syn_dir+'/'+operator+'/syn_page.tcl', self.tcl.return_syn_page_tcl_list(operator, ['./leaf.v']))

      # prepare the leaf verilog files.
      # Id depends on the IO numbers and operator name
      self.shell.write_lines(self.syn_dir+'/'+operator+'/leaf.v', self.verilog.return_page_v_list(page_num, operator, input_num, output_num, True), False)

      # Prepare the shell script to run vivado
      self.shell.write_lines(self.syn_dir+'/'+operator+'/run.sh', self.shell.return_run_sh_list(self.prflow_params['Xilinx_dir'], 'syn_page.tcl'), True)
    else:
      # prepare script files for riscv implementation.
      # As we don't need to compile any verilog files, we only need to perform 
      # RISC-V compile flow

      # extract basic information about the operator
      map_target, page_num, input_num, output_num =  self.return_map_target(operator)
      debug_exist, debug_port = self.pragma.return_pragma('./input_src/'+self.prflow_params['benchmark_name']+'/operators/'+operator+'.h', 'debug_port')
      if map_target == 'riscv':  inst_mem_exist, inst_mem_size = self.pragma.return_pragma('./input_src/'+self.prflow_params['benchmark_name']+'/operators/'+operator+'.h', 'inst_mem_size')
      if inst_mem_exist == False: inst_mem_size = 16384 
      inst_mem_bits = self.return_bit_size(inst_mem_size)
      LENGTH = '0x'+hex(int(inst_mem_size)).replace('0x', '').zfill(8)
      
      # create a riscv dirctory
      self.shell.cp_dir('./common/riscv_src/riscv/*', self.syn_dir+'/'+operator)
      self.shell.replace_lines(self.syn_dir+'/'+operator+'/run.sh', {'RISCV_GNU_TOOLCHAIN_INSTALL_PREFIX=': 'RISCV_GNU_TOOLCHAIN_INSTALL_PREFIX='+self.prflow_params['riscv_dir']}) 
      self.shell.replace_lines(self.syn_dir+'/'+operator+'/run.sh', {'operator=': 'operator='+operator}) 
      self.shell.replace_lines(self.syn_dir+'/'+operator+'/run.sh', {'MEM_SIZE=': 'MEM_SIZE='+str(int(inst_mem_size)/4)}) 
      self.shell.replace_lines(self.syn_dir+'/'+operator+'/run.sh', {'PAGE_NUM=': 'PAGE_NUM='+str(page_num)}) 
      os.system('chmod +x ' + self.syn_dir+'/'+operator+'/run.sh') 

      # Add operator instatiation into the main wrapper function  
      config_inst = config.config(self.prflow_params)
      io_argument_dict = config_inst.return_operator_io_argument_dict_local(operator)
      main_cpp_str_list = []
      for num in range(input_num): main_cpp_str_list.append('  hls::stream<ap_uint<32> > Input_'+str(num+1)+'(STREAMIN'+str(num+1)+');')
      for num in range(output_num): main_cpp_str_list.append('  hls::stream<ap_uint<32> > Output_'+str(num+1)+'(STREAMOUT'+str(num+1)+');')
      str_line = '    '+operator+'('
      for io_name in io_argument_dict[operator]:
        str_line = str_line + io_name + ','
      str_line = str_line + ')'
      str_line = str_line.replace(',)', ');')
      main_cpp_str_list.append('  while(1){')
      main_cpp_str_list.append(str_line)
      main_cpp_str_list.append('  }')
      self.shell.add_lines(self.syn_dir+'/'+operator+'/main.cpp', '//stream', main_cpp_str_list)

      # copy the typedefs.h file into out-of-context synthesis dir
      # replace the headerfile defintions
      self.shell.cp_file('input_src/'+self.prflow_params['benchmark_name']+'/host/typedefs.h', self.syn_dir+'/'+operator)
      self.shell.replace_lines(self.syn_dir+'/'+operator+'/typedefs.h', {'<hls_stream.h>': '#include "hls_stream.h"'}) 
      self.shell.replace_lines(self.syn_dir+'/'+operator+'/typedefs.h', {'<ap_fixed.h>': '#include "ap_fixed.h"'}) 
      self.shell.replace_lines(self.syn_dir+'/'+operator+'/typedefs.h', {'<ap_int.h>': '#include "ap_int.h"'}) 
      self.shell.replace_lines(self.syn_dir+'/'+operator+'/typedefs.h', {'<hls_video.h>': '#include "hls_video.h"'}) 
      self.shell.replace_lines(self.syn_dir+'/'+operator+'/typedefs.h', {'gmp': ''}) 
      self.shell.replace_lines(self.syn_dir+'/'+operator+'/typedefs.h', {'#define __TYPEDEFS_H__': '#define __TYPEDEFS_H__\n#define RISCV'}) 
      self.shell.cp_file('input_src/'+self.prflow_params['benchmark_name']+'/operators/'+operator+'.*', self.syn_dir+'/'+operator)
      self.shell.replace_lines(self.syn_dir+'/'+operator+'/'+operator+'.cpp', {'typedefs.h': '#include "typedefs.h"\n#include "firmware.h"'}) 
      self.shell.replace_lines(self.syn_dir+'/'+operator+'/firmware.h', {'// operator': '#include "'+operator+'.h"'}) 
      self.shell.replace_lines(self.syn_dir+'/'+operator+'/sections.lds', {'mem : ORIGIN': '         mem : ORIGIN = 0x00000000, LENGTH = '+LENGTH}) 
      if debug_exist: self.shell.replace_lines(self.syn_dir+'/'+operator+'/riscv/print.cpp', {'#define OUTPORT': '#define OUTPORT 0x10000028'})  
 
      # modify the run.sh shell for riscv
      self.shell.replace_lines(self.syn_dir+'/'+operator+'/run.sh', {'vivado': 'touch page_netlist.dcp\n'} )
      os.system('chmod +x '+self.syn_dir+'/'+operator+'/run.sh')
    

  # #pragma map_target=HW page_num=page_17
  def return_map_target(self, operator):
    src_list = self.shell.file_to_list('./input_src/'+self.prflow_params['benchmark_name']+'/operators/'+operator+'.h')
    input_num = self.return_io_num('Input_', src_list)
    output_num = self.return_io_num('Output_', src_list)
    HW_exist, page_num           = self.pragma.return_pragma('./input_src/'+self.prflow_params['benchmark_name']+'/operators/'+operator+'.h', 'page_num')
    map_target_exist, map_target = self.pragma.return_pragma('./input_src/'+self.prflow_params['benchmark_name']+'/operators/'+operator+'.h', 'map_target')
    return map_target, page_num, input_num, output_num
 
  def run(self, operator):
    # mk work directory
    self.shell.mkdir(self.syn_dir)
    
    # create ip directories for the operator
    self.create_page(operator)
     


