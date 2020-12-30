
# -*- coding: utf-8 -*-   

import os  
import subprocess
from gen_basic import gen_basic



class hls(gen_basic):
 
  def get_file_name(self, file_dir):                                            
    for root, dirs, files in os.walk(file_dir):                                 
      return files  

  # create one directory for each page 
  def create_page(self, fun_name):
    map_target_exist, map_target = self.pragma.return_pragma('./input_src/'+self.prflow_params['benchmark_name']+'/operators/'+fun_name+'.h', 'map_target')
    self.shell.re_mkdir(self.hls_dir+'/'+fun_name+'_prj')
    self.shell.re_mkdir(self.hls_dir+'/'+fun_name+'_prj/'+fun_name)
        
    self.shell.write_lines(self.hls_dir+'/'+fun_name+'_prj/vivado_hls.app', self.tcl.return_hls_prj_list(fun_name))
    self.shell.write_lines(self.hls_dir+'/'+fun_name+'_prj/'+fun_name+'/script.tcl', self.tcl.return_hls_tcl_list(fun_name))
    if map_target == 'HW':
      self.shell.write_lines(self.hls_dir+'/qsub_run_'+fun_name+'.sh', self.shell.return_run_hls_sh_list(self.prflow_params['Xilinx_dir'], './'+fun_name+'_prj/'+fun_name+'/script.tcl'), True)
    else:
      self.shell.write_lines(self.hls_dir+'/qsub_run_'+fun_name+'.sh', self.shell.return_empty_sh_list(), True)
      self.shell.write_lines(self.hls_dir+'/runLogdata_redir_m.log', ['hls: 0 senconds'], False)

  # main.sh will be used for local compilation
  def return_qsub_main_sh_list_local(self):
    lines_list = []
    lines_list.append('#!/bin/bash -e')
    # compile the IP for each page
    for fun_name in self.prflow_params['hls_fun_list']:
        lines_list.append(self.shell.return_qsub_command_str('./qsub_run_'+fun_name+'.sh', 'dummy', 'hls_'+fun_name, self.prflow_params['qsub_grid'], self.prflow_params['email'], self.prflow_params['MEM'], self.prflow_params['qsub_Nodes']))
    return lines_list


  # main.sh will be used for local compilation
  def return_main_sh_list_local(self):
    lines_list = []
    lines_list.append('#!/bin/bash -e')
    lines_list.append('source '+self.prflow_params['Xilinx_dir'])
    # compile the IP for each page
    for fun_name in self.prflow_params['syn_fun_list']:
      lines_list.append('vivado_hls -f '+'./'+fun_name+'_prj/'+fun_name+'/script.tcl') 

    return lines_list


  def create_shell_file(self):
  # local run:
  #   main.sh <- |_ execute each run.sh <- syn_page.tcl
  #
  # qsub run:
  #   qsub_main.sh <-|_ Qsubmit each qsub_run.sh <- syn_page.tcl
   
    self.shell.write_lines(self.hls_dir+'/main.sh', self.return_main_sh_list_local(), True)
    self.shell.write_lines(self.hls_dir+'/qsub_main.sh', self.return_qsub_main_sh_list_local(), True)


  def run(self, operator):
    # mk work directory
    if self.prflow_params['hls_regen']=='1':
      self.shell.mkdir(self.hls_dir)
    
    # generate shell files for qsub run and local run
    self.create_shell_file() 

    # create ip directories for all the pages
    self.create_page(operator)

    
    # go to the local mono_bft directory and run the qsub command
    os.chdir(self.hls_dir)
    if self.prflow_params['run_qsub']:
      os.system('./qsub_main.sh')
    os.chdir('../../')


 



