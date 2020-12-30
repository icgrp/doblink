# -*- coding: utf-8 -*-   

import os  
import subprocess
from gen_basic import gen_basic
import re


class syn(gen_basic):

  # from the source header file, find the input or output number
  def return_io_num(self, io_pattern, file_list):
    max_num = 0
    for line in file_list:
      num_list = re.findall(r""+io_pattern+"\d*", line)
      if(len(num_list)>0 and int(num_list[0].replace(io_pattern,''))): max_num = int(num_list[0].replace(io_pattern,''))
    return max_num

  # create one directory for each page 
  def create_page(self, operator):
    map_target, page_num, input_num, output_num =  self.return_map_target(operator)
    num_bram_addr_bits =int(self.prflow_params['bram_addr_bits'])
    self.shell.re_mkdir(self.syn_dir+'/'+operator)
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
      'src/Stream_Flow_Control.v',
      'src/write_b_in.v',
      'src/write_b_out.v'
    ]
    for name in file_list: self.shell.cp_file(self.overlay_dir+'/'+name, self.syn_dir+'/'+operator+'/'+name)

    if map_target == 'riscv': 
      self.shell.cp_dir('./common/riscv_src/riscv/', self.syn_dir+'/'+operator)
      print map_target
      riscv_file_list = [
        'src/picorv32.v',
        'src/picorv32_wrapper.v', 
        'src/picorv_mem.v', 
        'src/ram0.v', 
        'src/rise_detect.v'
      ] 
      file_list.extend(riscv_file_list)
      for name in riscv_file_list: self.shell.cp_file('./common/riscv_src/'+name, self.syn_dir+'/'+operator+'/'+name)
      self.shell.replace_lines(self.syn_dir+'/'+operator+'/riscv/qsub_run.sh', {'operator=': 'operator='+operator}) 
      os.system('chmod +x ' + self.syn_dir+'/'+operator+'/riscv/qsub_run.sh') 
      self.shell.replace_lines(self.syn_dir+'/'+operator+'/riscv/main.cpp', {'data_redir': operator+'(s_in1, s_out1, s_out2);'}) 
      self.shell.write_lines(self.syn_dir+'/'+operator+'/leaf.v', self.verilog.return_page_v_list(page_num, operator, input_num, output_num, True, True), False)
    else:
      self.shell.mkdir(self.syn_dir+'/'+operator+'/riscv')
      self.shell.write_lines(self.syn_dir+'/'+operator+'/riscv/qsub_run.sh', self.shell.return_empty_sh_list(), True)
      self.shell.write_lines(self.syn_dir+'/'+operator+'/leaf.v', self.verilog.return_page_v_list(page_num, operator, input_num, output_num, True), False)

    file_list=['./leaf.v']

 
    self.shell.write_lines(self.syn_dir+'/'+operator+'/syn_page.tcl', self.tcl.return_syn_page_tcl_list(operator, file_list))
    self.shell.write_lines(self.syn_dir+'/'+operator+'/qsub_run.sh', self.shell.return_run_sh_list(self.prflow_params['Xilinx_dir'], 'syn_page.tcl'), True)
   


  # main.sh will be used for local compilation
  def return_qsub_main_sh_list_local(self):
    lines_list = []
    lines_list.append('#!/bin/bash -e')
    # compile the IP for each page
    for fun_name in self.prflow_params['syn_fun_list']:
      if (fun_name !='user_kernel'): 
        lines_list.append('cd ./' + fun_name) 
        lines_list.append(self.shell.return_qsub_command_str('./qsub_run.sh', 'hls_'+fun_name, 'syn_'+fun_name, self.prflow_params['qsub_grid'], self.prflow_params['email'], self.prflow_params['MEM'], self.prflow_params['qsub_Nodes']))
        lines_list.append('cd -') 
    return lines_list


  # main.sh will be used for local compilation
  def return_main_sh_list_local(self):
    lines_list = []
    lines_list.append('#!/bin/bash -e')
    lines_list.append('source '+self.prflow_params['Xilinx_dir'])
    # compile the IP for each page
    for fun_name in self.prflow_params['syn_fun_list']:
      if (fun_name !='user_kernel'): 
        lines_list.append('cd ./' + fun_name) 
        lines_list.append('vivado -mode batch -source ./syn_page.tcl') 
        lines_list.append('cd -') 
    return lines_list


  def create_shell_file(self):
  # local run:
  #   main.sh <- |_ execute each run.sh <- syn_page.tcl
  #
  # qsub run:
  #   qsub_main.sh <-|_ Qsubmit each qsub_run.sh <- syn_page.tcl
   
    self.shell.write_lines(self.syn_dir+'/main.sh', self.return_main_sh_list_local(), True)
    self.shell.write_lines(self.syn_dir+'/qsub_main.sh', self.return_qsub_main_sh_list_local(), True)

    
  #pragma map_target=HW page_num=page_17
  def return_map_target(self, operator):
    src_list = self.shell.file_to_list('./input_src/'+self.prflow_params['benchmark_name']+'/operators/'+operator+'.h')
    input_num = self.return_io_num('Input_', src_list)
    output_num = self.return_io_num('Output_', src_list)
    HW_exist, page_num           = self.pragma.return_pragma('./input_src/'+self.prflow_params['benchmark_name']+'/operators/'+operator+'.h', 'page_num')
    map_target_exist, map_target = self.pragma.return_pragma('./input_src/'+self.prflow_params['benchmark_name']+'/operators/'+operator+'.h', 'map_target')
    return map_target, page_num, input_num, output_num
 
  def run(self, operator):
    # mk work directory
    if self.prflow_params['gen_syn']=='1':
      self.shell.mkdir(self.syn_dir)
    
    # generate shell files for qsub run and local run
    self.create_shell_file() 


    # create ip directories for the operator
    #if map_target=='HW':
    self.create_page(operator)
     

    # go to the local mono_bft directory and run the qsub command
    os.chdir(self.syn_dir)
    if self.prflow_params['run_qsub']:
      os.system('./qsub_main.sh')
    os.chdir('../../')


 



