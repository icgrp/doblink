#!/usr/bin/env python
# -*- coding: utf-8 -*-   
#starting
import os  
import subprocess
import argparse
import xml.etree.ElementTree

def gen_parameters(file_in_name, file_out_name, bram_dict):
  file_in = open(file_in_name, 'r')
  file_out = open(file_out_name, 'w') 

  lines_list = []
  for line in file_in:
    lines_list.append(line)
  
  keys_list = bram_dict.keys()
  keys_list.sort()

  line_num = 0 
  for key in keys_list:
    for num, size  in enumerate(bram_dict[key]):
      lines_list[line_num-1] = lines_list[line_num-1].replace(',', '};')
      lines_list[line_num] = key + '_' + str(num) + '[' + str(size) + '] = {' + lines_list[line_num]
      line_num += size 

  for line in lines_list:
    file_out.write(line)

  file_in.close()
  file_out.close()


if __name__ == '__main__':
  # 146784

  print 1
  bram_dict = {
               'const int32_t bin_conv_par_0_0': [32768, 4096],
               'const int32_t bin_conv_par_0_1': [32768, 4096],
               'const int32_t bin_conv_par_0_2': [32768, 4096],
               'const int32_t bin_conv_par_0_3': [32768, 3424]
              }

  gen_parameters('./input/bin_conv_para.h', './output/bin_conv_para.h', bram_dict)

  print 2
  # 147616
  bram_dict = {
               'const unsigned int bin_dense_par_0_0': [16384, 8192, 4096],
               'const unsigned int bin_dense_par_0_1': [16384, 8192, 4096],
               'const unsigned int bin_dense_par_0_2': [32768, 4096],
               'const unsigned int bin_dense_par_0_3': [32768, 4096],
               'const unsigned int bin_dense_par_0_4': [16384, 160]
              }

  gen_parameters('./input/bin_dense_para_0.h', './output/bin_dense_para_0.h', bram_dict)


  print 3
  # 147616
  bram_dict = {
               'const unsigned int bin_dense_par_1_0': [16384, 4096],
               'const unsigned int bin_dense_par_1_1': [16384, 4096],
               'const unsigned int bin_dense_par_1_2': [16384, 4096],
               'const unsigned int bin_dense_par_1_3': [32768, 4096],
               'const unsigned int bin_dense_par_1_4': [32768, 4096],
               'const unsigned int bin_dense_par_1_5': [12448] 
              }

  gen_parameters('./input/bin_dense_para_1.h', './output/bin_dense_para_1.h', bram_dict)





