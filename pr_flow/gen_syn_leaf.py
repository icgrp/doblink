# -*- coding: utf-8 -*-   

import os  
import subprocess
from gen_basic import gen_basic



class gen_syn_leaf_files(gen_basic):
 
  # create one directory for each page 
  def create_page(self):
    for fun_num, fun_name in enumerate(self.prflow_params['syn_fun_list']):
      if fun_name != 'user_kernel':
        page_num = self.prflow_params['page_list'][fun_num].replace('Function','')
        input_num = self.prflow_params['input_num_list'][fun_num]
        output_num = self.prflow_params['output_num_list'][fun_num]
        num_bram_addr_bits =int(self.prflow_params['bram_addr_bits'])
        self.shell.re_mkdir(self.syn_dir+'/'+fun_name)
        file_list = [
                  '../../F001_static_'+self.prflow_params['nl']+'_leaves/src/Config_Controls.v',
                  '../../F001_static_'+self.prflow_params['nl']+'_leaves/src/converge_ctrl.v',
                  '../../F001_static_'+self.prflow_params['nl']+'_leaves/src/ExtractCtrl.v',
                  '../../F001_static_'+self.prflow_params['nl']+'_leaves/src/Input_Port_Cluster.v',
                  '../../F001_static_'+self.prflow_params['nl']+'_leaves/src/Input_Port.v',
                  '../../F001_static_'+self.prflow_params['nl']+'_leaves/src/leaf_interface.v',
                  '../../F001_static_'+self.prflow_params['nl']+'_leaves/src/Output_Port_Cluster.v',
                  '../../F001_static_'+self.prflow_params['nl']+'_leaves/src/Output_Port.v',
                  '../../F001_static_'+self.prflow_params['nl']+'_leaves/src/read_b_in.v',
                  '../../F001_static_'+self.prflow_params['nl']+'_leaves/src/Stream_Flow_Control.v',
                  '../../F001_static_'+self.prflow_params['nl']+'_leaves/src/write_b_in.v',
                  '../../F001_static_'+self.prflow_params['nl']+'_leaves/src/write_b_out.v',
                  './leaf.v'
                ]
        self.shell.write_lines(self.syn_dir+'/'+fun_name+'/syn_page.tcl', self.tcl.return_syn_page_tcl_list(fun_name, file_list))
        self.shell.write_lines(self.syn_dir+'/'+fun_name+'/qsub_run.sh', self.shell.return_run_sh_list(self.prflow_params['qsub_Xilinx_dir'], 'syn_page.tcl'), True)
        self.shell.write_lines(self.syn_dir+'/'+fun_name+'/leaf.v', self.verilog.return_page_v_list(page_num, fun_name, input_num, output_num, True), False)


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



  def run(self):
    # mk work directory
    if self.prflow_params['leaf_syn_regen']=='1':
      self.shell.re_mkdir(self.syn_dir)
    
    # generate shell files for qsub run and local run
    self.create_shell_file() 

    # create ip directories for all the pages
    self.create_page()

    # go to the local mono_bft directory and run the qsub command
    os.chdir(self.syn_dir)
    if self.prflow_params['run_qsub']:
      os.system('./qsub_main.sh')
    os.chdir('../../')


 



