#!/usr/bin/env python
# -*- coding: utf-8 -*-   
#starting
import os  
import subprocess
import pr_flow.utils as utils
import pr_flow.gen_bft as bft
import pr_flow.gen_static as static
import pr_flow.gen_hls as hls
import pr_flow.gen_syn_leaf as syn
import pr_flow.gen_impl_leaf as impl
import pr_flow.gen_bit as bit
import pr_flow.gen_sdk as sdk
import pr_flow.gen_mono as mono
import pr_flow.gen_mono_bft as mono_bft
import pr_flow.gen_config as config
import argparse
import xml.etree.ElementTree

if __name__ == '__main__':


  # Use argparse to parse the input arguments
  parser = argparse.ArgumentParser()
  parser.add_argument('benchmark_name')
  parser.add_argument('-q', '--run_qsub', help="default: don't submit the qsub job to icgrid", action='store_true')
  parser.add_argument('-g', '--regen_overlay', help="default: don't compile the static region", action='store_true')
  parser.add_argument('-f', '--re_func', type=str, default="no_func", help="choose which function to be regenrated")

  args = parser.parse_args()
  benchmark_name = args.benchmark_name  
  input_file_name = './input_files/hls_src/' + benchmark_name + '/architecture.xml'
  prflow_params = utils.load_prflow_params(input_file_name)
  prflow_params['benchmark_name']=benchmark_name
  prflow_params['run_qsub'] = args.run_qsub
  prflow_params['gen_lib'] = args.gen_lib
  prflow_params['re_func'] = args.re_func
  prflow_params['input_file_name'] = input_file_name
  prflow_params['workspace'] = './workspace'


  # Print the basic information of this pr_flow implementation
  print "\n\n\n==========================================================================="
  print "prflow: version.2019.7 from IC group@Upenn"
  if prflow_params['run_qsub']:  
    print "Benchmark " + prflow_params['benchmark_name'] + "will be implemented on " + prflow_params['qsub_grid']
  else:
    print "The scripts for benchmark  " + prflow_params['benchmark_name'] + " will be generated."

  if prflow_params['gen_lib']:
    print "Overlay will be regenerated!"
  else:
    print "We will reuse the previous overlay!"

  if prflow_params['re_func'] == "no_func":
    print "Subfunction implementation information:"
  else:
    print "This time we only implement function: " + prflow_params['re_func'] 

  print "Place and Route mode: " + prflow_params['PR_mode']


  func_entry = 0;
  for fun_name in prflow_params['syn_fun_list']:

    if fun_name == 'user_kernel':
      pass
    else: 
      page_num = prflow_params['page_list'][func_entry]
      page_num = page_num.replace('Function', '')
      print '\t'+ fun_name.ljust(20, ' ') + ' -> page_' + page_num
    func_entry = func_entry+1;
  print "===========================================================================\n\n\n"


  # When the input command is with '-g' arguments, the workspace will be regenerated!
  if prflow_params['gen_lib'] == True:
    os.system('rm -rf '+prflow_params['workspace'])
    print 'mkdir '+prflow_params['workspace']
    os.system('mkdir '+prflow_params['workspace'])
    if prflow_params['bft_regen'] == '1':
    #generate the BFT verilog files
      bft_inst = bft.gen_bft(prflow_params)
      bft_inst.bft_gen()

    if prflow_params['static_regen'] == '1':
    #generate the static overlay
      static_inst = static.gen_static(prflow_params)
      static_inst.run()

    if prflow_params['platform_regen'] == '1':
      sdk_inst = sdk.gen_sdk(prflow_params)
      sdk_inst.sdk_gen()




  if args.re_func == 'no_func':
    if prflow_params['hls_regen'] == '1':
    #generating hls files
      hls_inst = hls.gen_hls(prflow_params)
      hls_inst.run()

    if prflow_params['leaf_syn_regen'] == '1':
    #generating leaf synthesis files
      syn_inst = syn.gen_syn_leaf_files(prflow_params)
      syn_inst.run()

    if prflow_params['leaf_impl_regen'] == '1':
    #generating leaf P&R files
      impl_inst = impl.gen_impl_leaf_files(prflow_params)
      impl_inst.run()

    #if prflow_params['gen_lib'] == True:
    #if prflow_params['gen_lib'] == False:
    if prflow_params['mono_bft_regen'] == '1':
        mono_bft_inst = mono_bft.gen_mono_bft(prflow_params)
        mono_bft_inst.run()

    if prflow_params['config_regen'] == '1':
      config_inst = config.auto_config(prflow_params)
      config_inst.generate()

    if prflow_params['bit_gen_regen'] == '1':
      bit_inst = bit.gen_bit(prflow_params)
      bit_inst.bits_gen()

    if prflow_params['mono_regen'] == '1':
      mono_inst = mono.gen_mono(prflow_params)
      mono_inst.mono_gen()

  else:
    os.chdir('./workspace/F002_hls_'+benchmark_name)
    os.system('qsub -N hls_' + args.re_func + ' -q ' + prflow_params['qsub_grid'] + ' -m abe -M \"' + \
               prflow_params['email'] + '\" -l mem=8G -cwd -pe onenode 8 ./qsub_run_' + args.re_func + '.sh')
    os.chdir('../F003_syn_'+ benchmark_name + '/' + args.re_func)
    os.system('qsub -N syn_' + args.re_func + ' -q ' + prflow_params['qsub_grid'] + ' -hold_jid hls_' + args.re_func + ' -m abe -M \"' + \
               prflow_params['email'] + '\" -l mem=8G -cwd -pe onenode 8 ./qsub_run.sh')
    i = 0
    for leaf_name in prflow_params['syn_fun_list']:
      if leaf_name == args.re_func:
        print args.re_func + ' ' +  str(i) + ' ' + leaf_name
        os.chdir('../../F004_pr_'+benchmark_name+'/leaf_' + str(prflow_params['page_list'][i].replace('Function', '')))
        os.system('qsub -N impl_' + args.re_func + ' -q ' + prflow_params['qsub_grid'] + ' -hold_jid syn_' + args.re_func + ' -m abe -M \"' + \
               prflow_params['email'] + '\" -l mem=8G -cwd -pe onenode 8 ./qsub_run.sh')
      i = i+1
    os.chdir('../../')  















