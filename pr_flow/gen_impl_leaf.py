# -*- coding: utf-8 -*-   

import os  
import subprocess
from gen_basic import gen_basic


class gen_impl_leaf_files(gen_basic):

  # create one directory for each page 
  def create_page(self):
    for fun_num, fun_name in enumerate(self.prflow_params['syn_fun_list']):
      if fun_name != 'user_kernel':
        page_num = self.prflow_params['page_list'][fun_num].replace('Function','')
        input_num = self.prflow_params['input_num_list'][fun_num]
        output_num = self.prflow_params['output_num_list'][fun_num]
        num_bram_addr_bits =int(self.prflow_params['bram_addr_bits'])

        self.shell.re_mkdir(self.pr_dir+'/page_'+str(page_num))
        self.shell.write_lines(self.pr_dir+'/page_'+str(page_num)+'/impl_'+fun_name+'.tcl', self.tcl.return_impl_tcl_list(fun_name, page_num, False))
        self.shell.write_lines(self.pr_dir+'/page_'+str(page_num)+'/qsub_run.sh', self.shell.return_run_sh_list(self.prflow_params['qsub_Xilinx_dir'], 'impl_'+fun_name+'.tcl'), True)


  # main.sh will be used for local compilation
  def return_qsub_main_sh_list_local(self):
    lines_list = []
    lines_list.append('#!/bin/bash -e')
    # compile the IP for each page
    for func_entry, fun_name in enumerate(self.prflow_params['syn_fun_list']):
      if (fun_name !='user_kernel'): 
        page_num = self.prflow_params['page_list'][func_entry].replace('Function', '')
        lines_list.append('cd ./page_'+str(page_num)) 
        lines_list.append(self.shell.return_qsub_command_str('./qsub_run.sh', 'syn_'+fun_name, 'impl_'+fun_name, self.prflow_params['qsub_grid'], self.prflow_params['email'], self.prflow_params['MEM'], self.prflow_params['qsub_Nodes']))
        lines_list.append('cd -') 
    return lines_list


  # main.sh will be used for local compilation
  def return_main_sh_list_local(self):
    lines_list = []
    lines_list.append('#!/bin/bash -e')
    lines_list.append('source '+self.prflow_params['Xilinx_dir'])

    # compile the IP for each page
    for func_entry, fun_name in enumerate(self.prflow_params['syn_fun_list']):
      if (fun_name !='user_kernel'): 
        page_num = self.prflow_params['page_list'][func_entry].replace('Function', '')
        lines_list.append('cd ./page_'+str(page_num)) 
        lines_list.append('vivado -mode batch -source ./impl_'+fun_name+'.tcl') 
        lines_list.append('cd -') 
    return lines_list



  def create_shell_file(self):
  # local run:
  #   main.sh <- |_ execute each impl_page.tcl
  #
  # qsub run:
  #   qsub_main.sh <-|_ Qsubmit each qsub_run.sh <- impl_page.tcl
   
    self.shell.write_lines(self.pr_dir+'/main.sh', self.return_main_sh_list_local(), True)
    self.shell.write_lines(self.pr_dir+'/qsub_main.sh', self.return_qsub_main_sh_list_local(), True)



  def run(self):
    # mk work directory
    if self.prflow_params['leaf_impl_regen']=='1':
      self.shell.re_mkdir(self.pr_dir)
    
    # generate shell files for qsub run and local run
    self.create_shell_file() 

    # create ip directories for all the pages
    self.create_page()


    # go to the local mono_bft directory and run the qsub command
    os.chdir(self.pr_dir)
    if self.prflow_params['run_qsub']:
      if self.prflow_params['gen_lib'] != True:
        os.system('./qsub_main.sh')
    os.chdir('../../')

   

