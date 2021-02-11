# -*- coding: utf-8 -*-   
# Company: IC group, University of Pennsylvania
# Engineer: Yuanlong Xiao
#
# Create Date: 02/11/2021
# Design Name: overlay
# Project Name: DIRC
# Versions: 1.0
# Description: This is a python script to prepare the script for PR compilation  for PRFlow
# Dependencies: python2, gen_basic.py
# Revision:
# Revision 0.01 - File Created
#
# Additional Comments:




import os  
import subprocess
from gen_basic import gen_basic
import re

class impl(gen_basic):

  # create one directory for each page 
  def create_page(self, operator, page_num):

    self.shell.re_mkdir(self.pr_dir+'/'+operator)
   
    # prepare the tcl files
    self.shell.write_lines(self.pr_dir+'/'+operator+'/impl_'+operator+'.tcl', self.tcl.return_impl_tcl_list(operator, page_num, False))

    # prepare the shell script
    self.shell.write_lines(self.pr_dir+'/'+operator+'/run.sh', self.shell.return_run_sh_list(self.prflow_params['Xilinx_dir'], 'impl_'+operator+'.tcl'), True)

    map_target_exist, map_target = self.pragma.return_pragma('./input_src/'+self.prflow_params['benchmark_name']+'/operators/'+operator+'.h', 'map_target')
    if map_target == 'riscv':
      self.shell.replace_lines(self.pr_dir+'/'+operator+'/run.sh', {'vivado': 'touch ../../F005_bits_'+self.prflow_params['benchmark_name']+'/'+operator+'.bit\nvivado'})
      self.shell.replace_lines(self.pr_dir+'/'+operator+'/run.sh', {'vivado': 'echo read_checkpoint: 0 seconds > runLogImpl_'+operator+'.log\nvivado'})
      self.shell.replace_lines(self.pr_dir+'/'+operator+'/run.sh', {'vivado': 'echo opt: 0 seconds >> runLogImpl_'+operator+'.log\nvivado'})
      self.shell.replace_lines(self.pr_dir+'/'+operator+'/run.sh', {'vivado': 'echo place: 0 seconds >> runLogImpl_'+operator+'.log\nvivado'})
      self.shell.replace_lines(self.pr_dir+'/'+operator+'/run.sh', {'vivado': 'echo route: 0 seconds >> runLogImpl_'+operator+'.log\nvivado'})
      self.shell.replace_lines(self.pr_dir+'/'+operator+'/run.sh', {'vivado': 'echo bit_gen: 0 seconds >> runLogImpl_'+operator+'.log\n'})
      os.system('chmod +x '+self.pr_dir+'/'+operator+'/run.sh')




  def run(self, operator):
    # mk work directory
    self.shell.mkdir(self.pr_dir)
    self.shell.mkdir(self.bit_dir)
    
    # create ip directories for all the pages
    page_num_exist, page_num = self.pragma.return_pragma('./input_src/'+self.prflow_params['benchmark_name']+'/operators/'+operator+'.h', 'page_num') 
    if page_num_exist==True:
      self.create_page(operator, page_num)


