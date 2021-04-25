# -*- coding: utf-8 -*-   
# Company: IC group, University of Pennsylvania
# Engineer: Yuanlong Xiao
#
# Create Date: 02/11/2021
# Design Name: overlay
# Project Name: DIRC
# Versions: 1.0
# Description: This is a python script to prepare the script for static region 
#              compile for PRflow.
# Dependencies: python2, gen_basic
# Revision:
# Revision 0.01 - File Created
#
# Additional Comments:


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
    self.shell.write_lines(self.overlay_dir+'/dummy_repo/'+fun_name+'/'+'leaf.v', self.verilog.return_page_v_list(0, fun_name, 1, 1, True))
    
    # temporarily only copy the synthesis files for RISC-V core syntheis
    # We use this RISC-V post-syn dcp to pre-load somes pages.
    # When an operator is mapped to RISC-V, we can use the pre-compiled RISC-V, instead of re-compilation
    self.shell.cp_dir('common/riscv_32bram', self.overlay_dir+'/dummy_repo/')
    self.shell.write_lines(self.overlay_dir+'/dummy_repo/riscv_32bram/run.sh',      self.shell.return_run_sh_list(self.prflow_params['Xilinx_dir'], 'dummy.tcl'), True)


  # main.sh will be used for local compilation
  def return_main_sh_list_local(self):
    lines_list = []
    lines_list.append('#!/bin/bash -e')
    lines_list.append('source '+self.prflow_params['Xilinx_dir'])
    # compile the dummy logic for each page
    lines_list.append('cd ./dummy_repo/user_kernel')
    lines_list.append('./run.sh')
    lines_list.append('cd -')
    #lines_list.append('cd ./dummy_repo/riscv_32bram')
    #lines_list.append('./run.sh')
    #lines_list.append('cd -')
    lines_list.append('vivado -mode batch -source project_syn2gen.tcl')
    lines_list.append('vivado -mode batch -source project_syn2dcp.tcl')
    lines_list.append('vivado -mode batch -source mk_overlay.tcl')
    return lines_list


  def create_tcl_shell_file(self):
  # local run:
  #   main.sh <- |_ vivado each dummy.tcl
  #              |_ vivado project_syn2gen.tcl
  #              |_ vivado project_syn2dcp.tcl
  #              |_ vivado mk_overlay.tcl

    #generate tcl file to create the overlay region vivado project
    #we use existed files instead
    self.shell.cp_dir('./common/script_src/project_syn_gen_'+self.prflow_params['board']+'.tcl ', self.overlay_dir +'/project_syn2gen.tcl')
    self.shell.write_lines(self.overlay_dir+'/project_syn2dcp.tcl', self.tcl.return_syn2dcp_tcl_list(), False)
    self.shell.write_lines(self.overlay_dir+'/mk_overlay.tcl', self.tcl.return_mk_overlay_tcl_list(), False)

    self.shell.write_lines(self.overlay_dir+'/main.sh', self.return_main_sh_list_local(), True)
    self.shell.write_lines(self.overlay_dir+'/qsub_project_syn2gen.sh', self.shell.return_run_sh_list(self.prflow_params['Xilinx_dir'], 'project_syn2gen.tcl'), True)
    self.shell.write_lines(self.overlay_dir+'/qsub_project_syn2dcp.sh', self.shell.return_run_sh_list(self.prflow_params['Xilinx_dir'], 'project_syn2dcp.tcl'), True)
    self.shell.write_lines(self.overlay_dir+'/qsub_mk_overlay.sh', self.shell.return_run_sh_list(self.prflow_params['Xilinx_dir'], 'mk_overlay.tcl'), True)



  def run(self):
    # make work directory
    self.shell.mkdir(self.prflow_params['workspace'])
    self.shell.re_mkdir(self.overlay_dir)
    
    # copy the hld/xdc files from input source directory
    self.shell.cp_dir('./common/verilog_src', self.overlay_dir+'/src')
    
    # copy the verilog file for the BFT from bft generate directory
    self.shell.cp_file('./workspace/F000_bft_gen/gen_nw_vivado.v', self.overlay_dir+'/src')

    # create a bft wrapper
    self.shell.write_lines(self.overlay_dir+'/src/bft.v', self.verilog.return_bft_wrapper_v_list(int(self.prflow_params['nl']), int(self.prflow_params['addr_bits']), int(self.prflow_params['packet_bits'])))

    # generate tcl and shell files for local run
    self.create_tcl_shell_file()

    # create dummy logic place and route the overlay.dcp
    self.create_place_holder()


