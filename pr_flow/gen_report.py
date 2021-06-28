#!/usr/bin/env python
import sys
import os
import xml.etree.ElementTree
import argparse
import re
import math

    
def load_prflow_params(filename):
  prflow_params = {
    'nl': -1,
    'p': -1,
    'pks': -1,
    'bft_gen': 0,
    'static_run': 0
  }

  root = xml.etree.ElementTree.parse(filename).getroot()
  specs = root.findall('spec')
  network = root.findall('network')
  functions = root.findall('function')
  links = root.findall('link')	
  clock =root.findall('clock')
  datawidth_in=root.findall('datawidth_in')
  datawidth_out=root.findall('datawidth_out')


  hls_fun_list = []
  syn_fun_list = []
  input_num_list = []
  output_num_list = []
  page_list = []
  ram_type_list = ['block']
  for child in functions:
    hls_fun_list.append(child.get('name'))
    syn_fun_list.append(child.get('name'))
    input_num_list.append(child.get('inputs'))
    output_num_list.append(child.get('outputs'))
    page_list.append(child.get('page'))
    ram_type_list.append(child.get('ramtype'))


  datawidth_in_list =[[32 for j in range(8)] for i in range(32)]
  datawidth_out_list =[[32 for j in range(8)] for i in range(32)]

  for child in datawidth_in:
    func_name, port_num = child.get('port').split('.')
    if func_name == 'DMA':
      page_num = '1'
    else:
      page_num = page_list[syn_fun_list.index(func_name)].replace('Function', '')
    datawidth_in_list[int(page_num)][int(port_num)] = int(child.get('value'))


  for child in datawidth_out:
    func_name, port_num = child.get('port').split('.')
    if func_name == 'DMA':
      page_num = '1'
    else:
      page_num = page_list[syn_fun_list.index(func_name)].replace('Function', '')
    datawidth_out_list[int(page_num)][int(port_num)] = int(child.get('value'))


  for child in specs:
    prflow_params[child.get('name')] = child.get('value')
    
  for child in clock:
    prflow_params[child.get('name')] = child.get('period')



  prflow_params['hls_fun_list'] = hls_fun_list
  prflow_params['syn_fun_list'] = syn_fun_list
  prflow_params['input_num_list'] = input_num_list
  prflow_params['output_num_list'] = output_num_list
  prflow_params['page_list'] = page_list
  prflow_params['ram_type_list'] = ram_type_list
  prflow_params['datawidth_in_list'] = datawidth_in_list
  prflow_params['datawidth_out_list'] = datawidth_out_list




  return prflow_params




    


if __name__ == "__main__":

  os.system('mkdir -p ./workspace/report')
  parser = argparse.ArgumentParser()
  parser.add_argument('benchmark_name')
 
  args = parser.parse_args()
  benchmark_name = args.benchmark_name  
  input_file_name = './input_files/hls_src/' + benchmark_name + '/architecture.xml'
  prflow_params = load_prflow_params(input_file_name)
  

  hls_fun_list = prflow_params['hls_fun_list']
  syn_fun_list = prflow_params['syn_fun_list']
  page_list = prflow_params['page_list']


 
  resource_report_file = open('./workspace/report/resource_report_'+benchmark_name+'.csv', 'w')
  time_report_file = open('./workspace/report/time_report_'+benchmark_name+'.csv', 'w')
#####################################################################################
#process hls timing
  hls_mat = []
  for fun_name in hls_fun_list:
    try:
      file_name = './workspace/F002_hls_'+benchmark_name+'/runLog' + fun_name + '.log'
      file_in = open(file_name, 'r')
      for line in file_in:
        run_time = re.findall(r"\d+", line)
        time_report_file.write('hls\t' + fun_name + '\t' + run_time[0] + '\n')
        hls_mat.append(int(run_time[0]))
      file_in.close()
    except:
      print ('No '+file_name) 


#####################################################################################
#process syn timing
  time_report_file.write('\n------------------------------------------------------------------------------' + '\n')
  syn_mat = []
  for fun_name in syn_fun_list:
    if fun_name != 'user_kernel': 
      try:
        file_name = './workspace/F003_syn_'+benchmark_name+'/' + fun_name + '/runLog_' + fun_name + '.log'
        file_in = open(file_name, 'r')
        for line in file_in:
          run_time = re.findall(r"\d+", line)
          time_report_file.write('syn\t' + fun_name + '\t' + run_time[0] + '\n')
          if fun_name != 'user_kernel':
            syn_mat.append(int(run_time[0]))
        file_in.close()
      except:
        print ('No '+file_name) 

  time_report_file.write('\n------------------------------------------------------------------------------' + '\n')
  fun_entry = 0;


  LUTs_list = []
  FFs_list = []
  BRAMs_list = []
  DSPs_list = []
  
  rdchk_mat = []
  opt_mat = []
  place_mat = []
  route_mat = []
  bitgen_mat = []
  for fun_name in syn_fun_list:
    if fun_name == 'user_kernel':
      pass
    else:
      #####################################################################################
      #process resource utilization
      page_num = page_list[fun_entry].replace('Function', '')
      try:
        file_name = './workspace/F003_syn_'+benchmark_name+'/' + fun_name + '/utilization.rpt'
        file_in = open(file_name, 'r')
        for line in file_in:
          if line.startswith('| leaf'):
            luts =  re.findall(r"\d+", line)
            #str_tmp = fun_name + '\tpage_' + page_num + '\t' + luts[3] + ' / ' + luts[5]
            str_tmp = fun_name + '\tpage_' + page_num + '\t' + luts[0]
            LUTs_list.append(str_tmp)
  
          if line.startswith('| leaf'):
            FFs =  re.findall(r"\d+", line)
            #str_tmp = fun_name + '\tpage_' + page_num + '\t' + FFs[3] + ' / ' + FFs[5]
            str_tmp = fun_name + '\tpage_' + page_num + '\t' + FFs[4]
            FFs_list.append(str_tmp)
  
          if line.startswith('| leaf'):
            brams =  re.findall(r"\d+", line)
            #str_tmp = fun_name + '\tpage_' + page_num + '\t' + brams[3] + ' / ' + brams[5]
            str_tmp = fun_name + '\tpage_' + page_num + '\t' + str(int(brams[5])*2+int(brams[6]))
            BRAMs_list.append(str_tmp)
  
          if line.startswith('| leaf'):
            dsps =  re.findall(r"\d+", line)
            #str_tmp = fun_name + '\tpage_' + page_num + '\t' + dsps[3] + ' / ' + dsps[5]
            str_tmp = fun_name + '\tpage_' + page_num + '\t' + dsps[8]
            DSPs_list.append(str_tmp)
        file_in.close()
      except:
        print ('No '+file_name) 
    fun_entry = fun_entry + 1


  fun_entry = 0
  for fun_name in syn_fun_list:
    if fun_name == 'user_kernel':
      pass
    else:
      #####################################################################################
      #process impl timing
      page_num = page_list[fun_entry].replace('Function', '')
      file_name = './workspace/F004_pr_'+benchmark_name+'/page_' + page_num + '/runLogImpl_' + fun_name + '.log'
      try: 
        file_in = open(file_name, 'r')
        run_time_list = []
        for line in file_in:
          run_time = re.findall(r"\d+", line)
          run_time_list.append(run_time[0]) 
        file_in.close()
        str_tmp = fun_name + '->\tpage_' + page_num + '\t'
        for i in run_time_list:
          str_tmp = str_tmp + i + '\t'
        time_report_file.write(str_tmp + '\n')
        if len(run_time_list) > 2:
          rdchk_mat.append(int(run_time_list[0]))
          opt_mat.append(int(run_time_list[1]))
          place_mat.append(int(run_time_list[2]))
          route_mat.append(int(run_time_list[3]))
          #bitgen_mat.append(int(run_time_list[4]))
        file_in.close()
      except:
        print "No "+file_name
    fun_entry = fun_entry + 1



#####################################################################################

  resource_report_file.write('LUTs-----------------------------------------\n')
  for ele in LUTs_list:
    resource_report_file.write(ele + '\n')
  resource_report_file.write('FFs-----------------------------------------\n')
  for ele in FFs_list:
    resource_report_file.write(ele + '\n')
  resource_report_file.write('BRAMs-----------------------------------------\n')
  for ele in BRAMs_list:
    resource_report_file.write(ele + '\n')
  resource_report_file.write('DSPs-----------------------------------------\n')
  for ele in DSPs_list:
    resource_report_file.write(ele + '\n')

  resource_report_file.close()
  time_report_file.close()


 
  print("You can find the report under ./workspace/report")






