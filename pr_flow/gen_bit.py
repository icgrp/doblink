# -*- coding: utf-8 -*-   

import os  
import subprocess

class gen_bit:
  def __init__(self, prflow_params):
    self.prflow_params = prflow_params
    self.bits_dir = self.prflow_params['workspace']+'/F005_bits_'+self.prflow_params['benchmark_name']


  def bits_gen(self):
    os.system('rm -rf ' + self.bits_dir)
    os.system('mkdir ' + self.bits_dir)

    run_file=open(self.bits_dir + '/run.sh', 'w')
    run_file.write('#!/bin/bash -e\n')
    run_file.write('source ' + self.prflow_params['Xilinx_dir'] + '\n')
    run_file.write('vivado -mode batch -source download.tcl\n')
    run_file.close()
    os.system('chmod +x ' + self.bits_dir + '/run.sh')

    qsub_run_file=open(self.bits_dir + '/qsub_run.sh', 'w')
    qsub_run_file.write('#!/bin/bash -e\n')
    qsub_run_file.write('source ' + self.prflow_params['qsub_Xilinx_dir'] + '\n')
    qsub_run_file.write('vivado -mode batch -source download.tcl\n')
    qsub_run_file.close()
    os.system('chmod +x ' + self.bits_dir + '/qsub_run.sh')



    tcl_file=open(self.bits_dir + '/download.tcl', 'w')
    tcl_file.write('open_hw\n')
    tcl_file.write('connect_hw_server\n')
    tcl_file.write('open_hw_target\n')
    tcl_file.write('current_hw_device [get_hw_devices '+self.prflow_params['device']+']\n')
    tcl_file.write('set_property PROBES.FILE {} [get_hw_devices '+self.prflow_params['device']+']\n')
    tcl_file.write('set_property FULL_PROBES.FILE {} [get_hw_devices '+self.prflow_params['device']+']\n')
    tcl_file.write('set_property PROGRAM.FILE {../F001_static_' + self.prflow_params['nl'] + '_leaves/main.bit} [get_hw_devices '+self.prflow_params['device']+']\n')
    tcl_file.write('program_hw_devices [get_hw_devices '+self.prflow_params['device']+']\n')
    tcl_file.write('refresh_hw_device [lindex [get_hw_devices '+self.prflow_params['device']+'] 0]\n\n')
    func_entry = 0;
    for fun_name in self.prflow_params['syn_fun_list']:
      if fun_name == 'user_kernel':
        pass
      else:
        page_num = self.prflow_params['page_list'][func_entry]
        page_num = page_num.replace('Function', '')
        tcl_file.write('set_property PROBES.FILE {} [get_hw_devices '+self.prflow_params['device']+']\n')
        tcl_file.write('set_property FULL_PROBES.FILE {} [get_hw_devices '+self.prflow_params['device']+']\n')
        tcl_file.write('set_property PROGRAM.FILE {./leaf_' + str(page_num) + '.bit} [get_hw_devices '+self.prflow_params['device']+']\n')
        tcl_file.write('program_hw_devices [get_hw_devices '+self.prflow_params['device']+']\n')
        tcl_file.write('refresh_hw_device [lindex [get_hw_devices '+self.prflow_params['device']+'] 0]\n\n')
      func_entry = func_entry + 1



    tcl_file.write('exit\n')
    
 
    tcl_file.close()

    main_sh = open(self.bits_dir + '/main.sh', 'w')
    main_sh.write('#!/bin/bash -e\n')
    main_sh.write('rm -rf ./vivado*\n')
    main_sh.write('./run.sh\n')
    main_sh.close()
    os.system('chmod +x ' + self.bits_dir + '/main.sh')


    qsub_main_sh = open(self.bits_dir + '/qsub_main.sh', 'w')
    qsub_main_sh.write('#!/bin/bash -e\n') 
    qsub_main_sh.write('emailAddr=\"'+ self.prflow_params['email'] +'\"\n\n')
    qsub_main_sh.write('qsub -N mk_overlay -q ' + self.prflow_params['qsub_grid'] + ' -m abe -M $emailAddr -cwd ./qsub_run.sh\n')
    qsub_main_sh.close()
    os.system('chmod +x ' + self.bits_dir + '/qsub_main.sh')































