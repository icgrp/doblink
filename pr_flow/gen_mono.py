# -*- coding: utf-8 -*-   


import os  
import subprocess

class gen_mono:
  def __init__(self, prflow_params):
    self.prflow_params = prflow_params
    self.static_dir = self.prflow_params['workspace']+'/F001_static_' + self.prflow_params['nl'] + '_leaves'
    self.hls_dir = self.prflow_params['workspace']+'/F002_hls_'+self.prflow_params['benchmark_name']
    self.syn_dir = self.prflow_params['workspace']+'/F003_syn_'+self.prflow_params['benchmark_name']
    self.pr_dir = self.prflow_params['workspace']+'/F004_pr_'+self.prflow_params['benchmark_name']
    self.mono_dir = self.prflow_params['workspace']+'/F008_mono_'+self.prflow_params['benchmark_name']

  def get_file_name(self, file_dir):   
    for root, dirs, files in os.walk(file_dir):
      return files


  def modify_parameters(self):

    #uncomment the leaf logic
    leaf_file_src = open(self.static_dir + '/src/leaf_empty.v', 'r')
    leaf_file_dst = open(self.mono_dir+'/src/leaf_empty.v', 'w')
    for line in  leaf_file_src:
      if line.startswith('/*') or line.startswith("*/"):
        pass
      else:
        leaf_file_dst.write(line)
    leaf_file_src.close()
    leaf_file_dst.close()
    
    bd_gen_in = open('./input_files/script_src/project_syn_gen_mono.tcl', 'r')
    bd_gen_out = open(self.mono_dir + '/project_syn_gen.tcl', 'w')
    for line in bd_gen_in:
      if line.startswith('  # Create address segments'):

        bd_gen_out.write('  # Set IP repository paths\n')
        bd_gen_out.write('  set obj [get_filesets sources_1]\n')
        bd_gen_out.write('  set_property "ip_repo_paths" "[file normalize ../F002_hls_'+self.prflow_params['benchmark_name']+'/'+self.prflow_params['mono_function']+'_prj/'+self.prflow_params['mono_function']+'/impl/ip]" $obj\n')
        bd_gen_out.write('  update_ip_catalog\n') 
        bd_gen_out.write('  # Create ports\n')
        bd_gen_out.write('  # Create instance: '+self.prflow_params['mono_function']+'_0, and set properties\n')
        bd_gen_out.write('  set '+self.prflow_params['mono_function']+'_0 [ create_bd_cell -type ip -vlnv xilinx.com:hls:'+self.prflow_params['mono_function']+':1.0 '+self.prflow_params['mono_function']+'_0 ]\n')
        bd_gen_out.write('  connect_bd_net -net xlconstant_1_dout [get_bd_pins '+self.prflow_params['mono_function']+'_0/ap_start] [get_bd_pins xlconstant_1/dout]\n')
        bd_gen_out.write('  connect_bd_net -net '+self.prflow_params['mono_function']+'_0_Input_1_V_V_ap_ack [get_bd_pins '+self.prflow_params['mono_function']+'_0/Input_1_V_V_ap_ack] [get_bd_pins axi_dma_0/m_axis_mm2s_tready]\n')
        bd_gen_out.write('  connect_bd_net -net axi_dma_0_m_axis_mm2s_tdata [get_bd_pins '+self.prflow_params['mono_function']+'_0/Input_1_V_V] [get_bd_pins axi_dma_0/m_axis_mm2s_tdata]\n')
        bd_gen_out.write('  connect_bd_net -net axi_dma_0_m_axis_mm2s_tvalid [get_bd_pins '+self.prflow_params['mono_function']+'_0/Input_1_V_V_ap_vld] [get_bd_pins axi_dma_0/m_axis_mm2s_tvalid]\n')
        bd_gen_out.write('  connect_bd_net -net axi_dma_1_s_axis_s2mm_tready [get_bd_pins '+self.prflow_params['mono_function']+'_0/Output_1_V_V_ap_ack] [get_bd_pins axi_dma_1/s_axis_s2mm_tready] [get_bd_pins dma_converter_0/ready]\n')
        bd_gen_out.write('  connect_bd_net -net leaf_interface_1_dout_leaf_interface2user [get_bd_pins '+self.prflow_params['mono_function']+'_0/Output_1_V_V] [get_bd_pins axi_dma_1/s_axis_s2mm_tdata] [get_bd_pins dma_converter_0/dout]\n')
        bd_gen_out.write('  connect_bd_net -net leaf_interface_1_vld_interface2user [get_bd_pins '+self.prflow_params['mono_function']+'_0/Output_1_V_V_ap_vld] [get_bd_pins axi_dma_1/s_axis_s2mm_tvalid] [get_bd_pins dma_converter_0/valid]\n')

        bd_gen_out.write('  connect_bd_net -net rst_ps8_0_99M_peripheral_reset [get_bd_pins '+self.prflow_params['mono_function']+'_0/ap_rst] [get_bd_pins dma_converter_0/reset] [get_bd_pins rst_ps8_0_99M/peripheral_reset]\n')

        bd_gen_out.write('  connect_bd_net -net zynq_ultra_ps_e_0_pl_clk0 [get_bd_pins '+self.prflow_params['mono_function']+'_0/ap_clk] [get_bd_pins axi_dma_0/m_axi_mm2s_aclk] [get_bd_pins axi_dma_0/m_axi_sg_aclk] [get_bd_pins axi_dma_0/s_axi_lite_aclk]\n')


        bd_gen_out.write(line)
      
      else:
            bd_gen_out.write(line)
      #clear the xdc files out
      xdc_file = open(self.mono_dir+'/src/pblocks_' + self.prflow_params['nl'] + '.xdc', 'w')
      xdc_file.close()
      
    bd_gen_in.close()
    bd_gen_out.close()



  def project_syn_impl_gen(self):

    #open project_syn_impl.tcl
    tcl_file_dst = open(self.mono_dir+'/project_syn_impl.tcl', 'w')
    tcl_file_dst.write('open_project ./prj/floorplan_static.xpr\n')
    tcl_file_dst.write('reset_run synth_1\n')
    tcl_file_dst.write('launch_runs synth_1\n')
    tcl_file_dst.write('wait_on_run synth_1\n')
    tcl_file_dst.write('launch_runs impl_1 -to_step write_bitstream\n')
    tcl_file_dst.write('wait_on_run impl_1\n')
    tcl_file_dst.write('file mkdir ./prj/floorplan_static.sdk\n')
    tcl_file_dst.write('file copy -force ./prj/floorplan_static.runs/impl_1/floorplan_static_wrapper.sysdef ./prj/floorplan_static.sdk/floorplan_static_wrapper.hdf\n')
    tcl_file_dst.close()



  def mono_gen(self):
    mono_dir = self.mono_dir
    static_dir = self.static_dir
    if self.prflow_params['mono_regen']=='1':
      os.system('rm -rf ' + mono_dir)
      os.system('mkdir ' + mono_dir)

    #self.project_syn_gen_gen()
    self.project_syn_impl_gen()
     
    os.system('cp -rf ' + self.static_dir + '/src ' + self.mono_dir)

    self.modify_parameters()

    mk_file=open('./' + self.mono_dir + '/run.sh', 'w')
    mk_file.write('#!/bin/bash -e\n')
    mk_file.write('source ' + self.prflow_params['Xilinx_dir'] + '\n')
    mk_file.write('vivado -mode batch -source project_syn_gen.tcl\n')
    mk_file.write('vivado -mode batch -source project_syn_impl.tcl\n')
    mk_file.close()
    os.system('chmod +x ' + './' + mono_dir + '/run.sh')

    mk_file=open('./' + mono_dir + '/qsub_run.sh', 'w')
    mk_file.write('#!/bin/bash -e\n')
    mk_file.write('source ' + self.prflow_params['qsub_Xilinx_dir'] + '\n')
    mk_file.write('vivado -mode batch -source project_syn_gen.tcl\n')
    mk_file.close()
    os.system('chmod +x ' + './' + mono_dir + '/qsub_run.sh')


    mk_file=open('./' + mono_dir + '/qsub_sub_syn.sh', 'w')
    mk_file.write('#!/bin/bash -e\n')
    mk_file.write('source ' + self.prflow_params['qsub_Xilinx_dir'] + '\n')
    mk_file.write('emailAddr="' + self.prflow_params['email'] + '"\n')
    mk_file.write('for file in $(ls ./prj/floorplan_static.runs)\n')
    mk_file.write('do\n')
    mk_file.write('    cd \'./prj/floorplan_static.runs/\'$file\n')
    mk_file.write('    qsub -N \'mono_\'$file -q ' + self.prflow_params['qsub_grid'] + ' -m abe -M $emailAddr -l mem=8G  -cwd ./runme.sh\n')
    mk_file.write('    cd ../../../\n')
    mk_file.write('done\n')
    mk_file.write('file_list=\'synth_1\'\n')
    mk_file.write('for file in $(ls ./prj/floorplan_static.runs)\n')
    mk_file.write('do\n')
    mk_file.write('    file_list=$file_list\',mono_\'$file\n')
    mk_file.write('done\n')
    mk_file.write('qsub -N mono_syn_impl -hold_jid $file_list -q ' + self.prflow_params['qsub_grid'] + ' -m abe -M $emailAddr -l mem=8G  -cwd ./qsub_syn_impl.sh\n')
    mk_file.close()
    os.system('chmod +x ' + './' + mono_dir + '/qsub_sub_syn.sh')

    mk_file=open('./' + mono_dir + '/qsub_syn_impl.sh', 'w')
    mk_file.write('#!/bin/bash -e\n')
    mk_file.write('source ' + self.prflow_params['qsub_Xilinx_dir'] + '\n')
    mk_file.write('vivado -mode batch -source project_syn_impl.tcl\n')
    mk_file.close()
    os.system('chmod +x ' + './' + mono_dir + '/qsub_syn_impl.sh')



    mk_file=open('./' + mono_dir + '/main.sh', 'w')
    mk_file.write('#!/bin/bash -e\n')
    mk_file.write('./run.sh\n')
    mk_file.close()
    os.system('chmod +x ' + './' + mono_dir + '/main.sh')

    mk_file=open('./' + mono_dir + '/qsub_main.sh', 'w')
    mk_file.write('#!/bin/bash -e\n')
    mk_file.write('emailAddr="'+ self.prflow_params['email']+'"\n')
    mk_file.write('qsub -N mono_project_syn_gen -hold_jid hls_'+self.prflow_params['mono_function']+' -q ' + self.prflow_params['qsub_grid'] + ' -m abe -M $emailAddr -l mem=8G  -cwd ./qsub_run.sh\n')
    mk_file.write('qsub -N mono_sub_syn -hold_jid mono_project_syn_gen  -q ' + self.prflow_params['qsub_grid'] + ' -m abe -M $emailAddr -l mem=8G  -cwd ./qsub_sub_syn.sh\n')
    mk_file.close()
    os.system('chmod +x ' + './' + mono_dir + '/qsub_main.sh')



    os.chdir(mono_dir)
    main_sh = open('./main.sh', 'w')
    qsub_main_sh = open('./qsub_ip.sh', 'w')
    main_sh.write('#!/bin/bash -e\n')
    qsub_main_sh.write('#!/bin/bash -e\n') 
    qsub_main_sh.write('emailAddr=\"'+self.prflow_params['email']+'\"\n\n')
    fun_num = 0;
    main_sh.close()
    qsub_main_sh.close()
    os.system('chmod +x main.sh')
    os.system('chmod +x qsub_ip.sh')
    if self.prflow_params['run_qsub']:
        os.system('./qsub_main.sh')
    os.chdir('../../')
