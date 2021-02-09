#!/usr/bin/env python
# -*- coding: utf-8 -*-   
#starting
import os  
import subprocess
import pr_flow.utils as utils
import pr_flow.gen_bft as bft
import pr_flow.bft as bft
import pr_flow.overlay as overlay
import pr_flow.hls as hls
import pr_flow.syn as syn
import pr_flow.impl as impl
import pr_flow.bit as bit
import pr_flow.ip_repo as ip_repo
import pr_flow.mbft as mbft
import pr_flow.config as config
import pr_flow.report as report

import pr_flow.gen_sdk as sdk
import pr_flow.gen_mono_bft as mono_bft
import argparse
import xml.etree.ElementTree

if __name__ == '__main__':


  # Use argparse to parse the input arguments
  parser = argparse.ArgumentParser()
  parser.add_argument('benchmark_name')
  parser.add_argument('-q', '--run_qsub',        help="default: don't submit the qsub job to icgrid",                       action='store_true')
  parser.add_argument('-g', '--gen_overlay',     help="default: don't compile the static region",                           action='store_true')
  parser.add_argument('-hls', '--gen_hls',       help="default: don't compile the static region",                           action='store_true')
  parser.add_argument('-syn', '--gen_syn',       help="default: don't perform out-of-context synthesis",                    action='store_true')
  parser.add_argument('-impl', '--gen_impl',     help="default: don't perform placement, routing and bitstream generation", action='store_true')
  parser.add_argument('-bit', '--gen_bits',      help="default: don't update the download.tcl file for loading bitstreams", action='store_true')
  parser.add_argument('-ip', '--gen_ip_repo',    help="default: don't generate ip_repo",                                    action='store_true')
  parser.add_argument('-cfg', '--gen_config',    help="generate the configuration packets for PSNoC",                       action='store_true')
  parser.add_argument('-mbft', '--gen_mono_bft', help="default: don't generate monolithic BFT project",                     action='store_true')
  parser.add_argument('-rpt', '--gen_report',    help="default: don't generate the report",                                 action='store_true')
  parser.add_argument('-op', '--operator',       type=str, default="no_func", help="choose which function to be regenrated")

  args = parser.parse_args()
  benchmark_name = args.benchmark_name  
  input_file_name = './common/configure/configure.xml'
  prflow_params                    = utils.load_prflow_params(input_file_name)
  prflow_params['benchmark_name']  = benchmark_name
  prflow_params['run_qsub']        = args.run_qsub
  prflow_params['gen_overlay']     = args.gen_overlay
  prflow_params['gen_hls']         = args.gen_hls
  prflow_params['gen_syn']         = args.gen_syn
  prflow_params['gen_impl']        = args.gen_impl
  prflow_params['gen_bits']        = args.gen_bits
  prflow_params['gen_ip_repo']     = args.gen_ip_repo
  prflow_params['gen_mono_bft']    = args.gen_mono_bft
  prflow_params['gen_config']      = args.gen_config
  prflow_params['gen_report']      = args.gen_report
  prflow_params['input_file_name'] = input_file_name
  prflow_params['workspace']       = './workspace'
  operator = args.operator

  # When the input command is with '-g' arguments, the workspace will be regenerated!
  if prflow_params['gen_overlay'] == True:
    os.system('mkdir -p workspace')
    # generate BFT before generating the overlay
    bft_inst = bft.bft(prflow_params)
    bft_inst.run()
    overlay_inst = overlay.overlay(prflow_params)
    overlay_inst.run()


  if prflow_params['gen_hls'] == True:
    hls_inst = hls.hls(prflow_params)
    hls_inst.run(operator)

  if prflow_params['gen_syn'] == True:
    syn_inst = syn.syn(prflow_params)
    syn_inst.run(operator)

  if prflow_params['gen_impl'] == True:
    impl_inst = impl.impl(prflow_params)
    impl_inst.run(operator)

  if prflow_params['gen_bits'] == True:
    bit_inst = bit.bit(prflow_params)
    bit_inst.run(operator)

  if prflow_params['gen_ip_repo'] == True:
    ip_repo_inst = ip_repo.ip_repo(prflow_params)
    ip_repo_inst.run(operator)


  if prflow_params['gen_mono_bft'] == True:
    mbft_inst = mbft.mbft(prflow_params)
    mbft_inst.run()


  if prflow_params['gen_config'] == True:
    cfg_inst = config.config(prflow_params)
    cfg_inst.run(operator)

  print operator
  if prflow_params['gen_report'] == True:
    rpt_inst = report.report(prflow_params)
    rpt_inst.run(operator)





