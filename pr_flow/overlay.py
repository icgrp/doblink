# -*- coding: utf-8 -*-   

import os  
import subprocess
from gen_basic import gen_basic

class overlay(gen_basic):
  def __init__(self, prflow_params):
    gen_basic.__init__(self, prflow_params)

  # create dummy directory for each empty block
  def create_place_holder(self):
    fun_name = 'user_kernel'
    self.shell.mkdir(self.overlay_dir+'/dummy_repo')
    self.shell.mkdir(self.overlay_dir+'/dummy_repo/'+fun_name)
    file_list = [
                  '../../src/Config_Controls.v',
                  '../../src/converge_ctrl.v',
                  '../../src/ExtractCtrl.v',
                  '../../src/Input_Port_Cluster.v',
                  '../../src/Input_Port.v',
                  '../../src/leaf_interface.v',
                  '../../src/Output_Port_Cluster.v',
                  '../../src/Output_Port.v',
                  '../../src/read_b_in.v',
                  '../../src/Stream_Flow_Control.v',
                  '../../src/write_b_in.v',
                  '../../src/write_b_out.v',
                  '../../src/user_kernel.v',
                  './leaf.v'
                ]
    self.shell.write_lines(self.overlay_dir+'/dummy_repo/'+fun_name+'/dummy.tcl', self.tcl.return_syn_page_tcl_list(fun_name, file_list))
    self.shell.write_lines(self.overlay_dir+'/dummy_repo/'+fun_name+'/run.sh',      self.shell.return_run_sh_list(self.prflow_params['Xilinx_dir'], 'dummy.tcl'), True)
    self.shell.write_lines(self.overlay_dir+'/dummy_repo/'+fun_name+'/qsub_run.sh', self.shell.return_run_sh_list(self.prflow_params['qsub_Xilinx_dir'], 'dummy.tcl'), True)
    self.shell.write_lines(self.overlay_dir+'/dummy_repo/'+fun_name+'/'+'leaf.v', self.verilog.return_page_v_list(0, fun_name, 1, 1, True))


  # main.sh will be used for local compilation
  def return_main_sh_list_local(self):
    lines_list = []
    lines_list.append('#!/bin/bash -e')
    lines_list.append('source '+self.prflow_params['Xilinx_dir'])
    # compile the dummy logic for each page
    lines_list.append('cd ./dummy_repo/user_kernel')
    lines_list.append('./run.sh')
    lines_list.append('cd -')
    lines_list.append('vivado -mode batch -source project_syn2gen.tcl')
    lines_list.append('vivado -mode batch -source project_syn2dcp.tcl')
    lines_list.append('vivado -mode batch -source mk_overlay.tcl')
    return lines_list


  # qsub_main.sh will be used for qsub compilation  
  def return_qsub_main_sh_list_local(self):
    # go through all the files and qsub the ip compilation tasks
    lines_list = self.shell.return_qsub_scan_sh_list('./dummy_repo', 'qsub_run.sh',  '', 'dummy_')
    hold_jid = 'dummy'

    # after the ip compilation is done, we can construct the vivado momo bft project
    lines_list.append(self.shell.return_qsub_command_str('./qsub_project_syn2gen.sh', hold_jid, 'overlay_syn2gen'))

    # we can accelerate the synthesis by compile each out-of-context modules in parallel
    lines_list.append(self.shell.return_qsub_command_str('./qsub_sub_syn.sh', 'overlay_syn2gen', 'overlay_sub_syn'))
    return lines_list


  # qsub_sub_syn.sh will go through all the out-of-context module directories and qsub each 
  # task by executing thn runme.sh, which is generated by vivado 
  def return_sub_syn_sh_list_local(self):
    lines_list = self.shell.return_qsub_scan_sh_list('./prj/floorplan_overlay.runs', 'runme.sh', '', 'overlay_sub_')
    hold_jid = '$file_list'

    # after all the out-of-context compilations are done, we reopen the project and compile it to overlay synthesis.
    # After overlay synthesis, the overlay will be implemented with dummy logic
    lines_list.append(self.shell.return_qsub_command_str('./qsub_project_syn2dcp.sh', hold_jid, 'syn2dcp'))
    lines_list.append(self.shell.return_qsub_command_str('./qsub_mk_overlay.sh', 'syn2dcp', 'mk_overlay'))
    lines_list.append('cd ../..')
    lines_list.append('cd ' + self.pr_dir)
    lines_list.append(self.shell.return_qsub_command_str('./qsub_main.sh', 'mk_overlay', 'submit_pr'))
    return lines_list

  def create_tcl_shell_file(self):
  # local run:
  #   main.sh <- |_ vivado each dummy.tcl
  #              |_ vivado project_syn2gen.tcl
  #              |_ vivado project_syn2dcp.tcl
  #              |_ vivado mk_overlay.tcl
  #
  # qsub run:
  #   qsub_main.sh <-|_ qsubmit each qsub_run.sh <- dummy.tcl
  #                  |_ qsub_project_syn2gen.sh <- project_syn2gen.tcl  
  #                  |_ qsub_sub_syn.sh <-|_ go through very synthesis directies and Qsubmmit job
  #                                       |_ qsub_project_syn2dcp.sh <- project_syn2dcp.tcl
  #                                       |_ qsub_mk_overlay.sh <- mk_overlay.tcl
  #                                       |_ go to F004 ./qsub_main.sh

    #generate tcl file to create the overlay region vivado project
    #we use existed files instead
    self.shell.cp_dir('./common/script_src/project_syn_gen_'+self.prflow_params['board']+'.tcl ', self.overlay_dir +'/project_syn2gen.tcl')
    self.shell.write_lines(self.overlay_dir+'/project_syn2dcp.tcl', self.tcl.return_syn2dcp_tcl_list(), False)
    self.shell.write_lines(self.overlay_dir+'/mk_overlay.tcl', self.tcl.return_mk_overlay_tcl_list(), False)

    self.shell.write_lines(self.overlay_dir+'/main.sh', self.return_main_sh_list_local(), True)
    self.shell.write_lines(self.overlay_dir+'/qsub_main.sh', self.return_qsub_main_sh_list_local(), True)
    self.shell.write_lines(self.overlay_dir+'/qsub_project_syn2gen.sh', self.shell.return_run_sh_list(self.prflow_params['qsub_Xilinx_dir'], 'project_syn2gen.tcl'), True)
    self.shell.write_lines(self.overlay_dir+'/qsub_sub_syn.sh', self.return_sub_syn_sh_list_local(), True)
    self.shell.write_lines(self.overlay_dir+'/qsub_project_syn2dcp.sh', self.shell.return_run_sh_list(self.prflow_params['qsub_Xilinx_dir'], 'project_syn2dcp.tcl'), True)
    self.shell.write_lines(self.overlay_dir+'/qsub_mk_overlay.sh', self.shell.return_run_sh_list(self.prflow_params['qsub_Xilinx_dir'], 'mk_overlay.tcl'), True)



  def run(self):
    # make work directory
    self.shell.mkdir(self.prflow_params['workspace'])
    self.shell.re_mkdir(self.overlay_dir)
    
    # copy the hld/xdc files from input source directory
    self.shell.cp_dir('./common/verilog_src', self.overlay_dir+'/src')
    self.shell.cp_dir('./common/dirc_ip', self.overlay_dir+'/dirc_ip')

    # generate tcl and shell files for qsub run and local run
    self.create_tcl_shell_file()

    self.create_place_holder()

    #if self.prflow_params['run_qsub']:
    #    os.chdir(self.overlay_dir)
    #    os.system('./qsub_main.sh')
    #    os.chdir('../../')




