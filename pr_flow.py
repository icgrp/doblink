#!/usr/bin/env python
# -*- coding: utf-8 -*-   
#starting
import os  
import subprocess
import pr_flow.utils as utils
import pr_flow.gen_bft as bft
import pr_flow.overlay as overlay
import pr_flow.hls as hls
import pr_flow.syn as syn
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
  parser.add_argument('-q', '--run_qsub',     help="default: don't submit the qsub job to icgrid", action='store_true')
  parser.add_argument('-g', '--gen_overlay',  help="default: don't compile the static region", action='store_true')
  parser.add_argument('-hls', '--gen_hls',    help="default: don't compile the static region", action='store_true')
  parser.add_argument('-syn', '--gen_syn',    help="default: don't perform out-of-context synthesis", action='store_true')
  parser.add_argument('-op', '--operator',    type=str, default="no_func", help="choose which function to be regenrated")

  args = parser.parse_args()
  benchmark_name = args.benchmark_name  
  input_file_name = './common/configure/configure.xml'
  prflow_params = utils.load_prflow_params(input_file_name)
  prflow_params['benchmark_name']=benchmark_name
  prflow_params['run_qsub'] = args.run_qsub
  prflow_params['gen_overlay'] = args.gen_overlay
  prflow_params['gen_hls'] = args.gen_hls
  prflow_params['gen_syn'] = args.gen_syn
  prflow_params['input_file_name'] = input_file_name
  prflow_params['workspace'] = './workspace'
  operator = args.operator

  # When the input command is with '-g' arguments, the workspace will be regenerated!
  if prflow_params['gen_overlay'] == True:
    os.system('rm -rf '+prflow_params['workspace'])
    os.system('mkdir '+prflow_params['workspace'])
    overlay_inst = overlay.overlay(prflow_params)
    overlay_inst.run()


  if prflow_params['gen_hls'] == True:
    hls_inst = hls.hls(prflow_params)
    hls_inst.run(operator)

  if prflow_params['gen_syn'] == True:
    syn_inst = syn.syn(prflow_params)
    syn_inst.run(operator)






