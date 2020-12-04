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
  def create_page(self, operator, input_num, output_num, page_num):
    num_bram_addr_bits =int(self.prflow_params['bram_addr_bits'])
    self.shell.re_mkdir(self.syn_dir+'/'+operator)
    file_list = [
      '../../F001_overlay/src/Config_Controls.v',
      '../../F001_overlay/src/converge_ctrl.v',
      '../../F001_overlay/src/ExtractCtrl.v',
      '../../F001_overlay/src/Input_Port_Cluster.v',
      '../../F001_overlay/src/Input_Port.v',
      '../../F001_overlay/src/leaf_interface.v',
      '../../F001_overlay/src/Output_Port_Cluster.v',
      '../../F001_overlay/src/Output_Port.v',
      '../../F001_overlay/src/read_b_in.v',
      '../../F001_overlay/src/Stream_Flow_Control.v',
      '../../F001_overlay/src/write_b_in.v',
      '../../F001_overlay/src/write_b_out.v',
      './leaf.v'
    ]
    self.shell.write_lines(self.syn_dir+'/'+operator+'/syn_page.tcl', self.tcl.return_syn_page_tcl_list(operator, file_list))
    self.shell.write_lines(self.syn_dir+'/'+operator+'/qsub_run.sh', self.shell.return_run_sh_list(self.prflow_params['Xilinx_dir'], 'syn_page.tcl'), True)
    self.shell.write_lines(self.syn_dir+'/'+operator+'/leaf.v', self.verilog.return_page_v_list(page_num, operator, input_num, output_num, True), False)


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
    HW, page_num = self.pragma.return_pragma('./input_src/'+self.prflow_params['benchmark_name']+'/operators/'+operator+'.h', 'page_num')
    return HW, page_num, input_num, output_num
 
  def run(self, operator):
    # mk work directory
    if self.prflow_params['leaf_syn_regen']=='1':
      self.shell.mkdir(self.syn_dir)
    
    # generate shell files for qsub run and local run
    self.create_shell_file() 


    # create ip directories for the operator
    HW, page_num, input_num, output_num =  self.return_map_target(operator)
    if HW==True:
      self.create_page(operator, input_num, output_num, page_num)
     

    # go to the local mono_bft directory and run the qsub command
    os.chdir(self.syn_dir)
    if self.prflow_params['run_qsub']:
      os.system('./qsub_main.sh')
    os.chdir('../../')


 



