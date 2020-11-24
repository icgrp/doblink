#!/usr/bin/env python
import re


def gen_coeff(func_num):

  c_file = open('./sdsoc/face_detect.cpp', 'r')
  
  enter = 0
  coord_dict = {}
  coeff_0_list = []
  coeff_1_list = []
  coeff_2_list = []
  coeff_3_list = []
  coeff_4_list = []



  for line in c_file:
    if line.startswith('int classifier'+str(func_num)+ '('):
      enter = 1
    if line.startswith('}'):
      enter = 0
      
    if enter == 1:
      if(line.startswith('  coord[')):
        num_list = re.findall(r"\d+", line)
        coord_dict[num_list[0]] = num_list
      
      if(line.startswith('  sum')):
        num_list = re.findall(r"\d+", line)
        line = line.replace(';', '')
        line_list = line.split()
        coord_list = coord_dict[num_list[1]]
        if(len(coord_list) == 2):
          pass
        else:
          if int(coord_list[1]) < 5:
            coeff_0_list.append('II_0[' + str(coord_list[1]) + '][' + coord_list[2] + '] * (' + line_list[-1] + ')')
          elif int(coord_list[1]) < 10:
            coeff_1_list.append('II_1[' + str(int(coord_list[1])-5) + '][' + coord_list[2] + '] * (' + line_list[-1] + ')')
          elif int(coord_list[1]) < 15:
            coeff_2_list.append('II_2[' + str(int(coord_list[1])-10) + '][' + coord_list[2] + '] * (' + line_list[-1] + ')')
          elif int(coord_list[1]) < 20:
            coeff_3_list.append('II_3[' + str(int(coord_list[1])-15) + '][' + coord_list[2] + '] * (' + line_list[-1] + ')')
          else:
            coeff_4_list.append('II_4[' + str(int(coord_list[1])-20) + '][' + coord_list[2] + '] * (' + line_list[-1] + ')')

        coord_list = coord_dict[num_list[2]]
        if(len(coord_list) == 2):
          pass
        else:
          if int(coord_list[1]) < 5:
            coeff_0_list.append(line_list[3] + 'II_0[' + str(coord_list[1]) + '][' + coord_list[2] + '] * (' + line_list[-1] + ')')
          elif int(coord_list[1]) < 10:
            coeff_1_list.append(line_list[3] + 'II_1[' + str(int(coord_list[1])-5) + '][' + coord_list[2] + '] * (' + line_list[-1] + ')')
          elif int(coord_list[1]) < 15:
            coeff_2_list.append(line_list[3] + 'II_2[' + str(int(coord_list[1])-10) + '][' + coord_list[2] + '] * (' + line_list[-1] + ')')
          elif int(coord_list[1]) < 20:
            coeff_3_list.append(line_list[3] + 'II_3[' + str(int(coord_list[1])-15) + '][' + coord_list[2] + '] * (' + line_list[-1] + ')')
          else:
            coeff_4_list.append(line_list[3] + 'II_4[' + str(int(coord_list[1])-20) + '][' + coord_list[2] + '] * (' + line_list[-1] + ')')

        coord_list = coord_dict[num_list[3]]
        if(len(coord_list) == 2):
          pass
        else:
          if int(coord_list[1]) < 5:
            coeff_0_list.append(line_list[5] + 'II_0[' + str(coord_list[1]) + '][' + coord_list[2] + '] * (' + line_list[-1] + ')')
          elif int(coord_list[1]) < 10:
            coeff_1_list.append(line_list[5] + 'II_1[' + str(int(coord_list[1])-5) + '][' + coord_list[2] + '] * (' + line_list[-1] + ')')
          elif int(coord_list[1]) < 15:
            coeff_2_list.append(line_list[5] + 'II_2[' + str(int(coord_list[1])-10) + '][' + coord_list[2] + '] * (' + line_list[-1] + ')')
          elif int(coord_list[1]) < 20:
            coeff_3_list.append(line_list[5] + 'II_3[' + str(int(coord_list[1])-15) + '][' + coord_list[2] + '] * (' + line_list[-1] + ')')
          else:
            coeff_4_list.append(line_list[5] + 'II_4[' + str(int(coord_list[1])-20) + '][' + coord_list[2] + '] * (' + line_list[-1] + ')')


        coord_list = coord_dict[num_list[4]]
        if(len(coord_list) == 2):
          pass
        else:
          if int(coord_list[1]) < 5:
            coeff_0_list.append(line_list[7] + 'II_0[' + str(coord_list[1]) + '][' + coord_list[2] + '] * (' + line_list[-1] + ')')
          elif int(coord_list[1]) < 10:
            coeff_1_list.append(line_list[7] + 'II_1[' + str(int(coord_list[1])-5) + '][' + coord_list[2] + '] * (' + line_list[-1] + ')')
          elif int(coord_list[1]) < 15:
            coeff_2_list.append(line_list[7] + 'II_2[' + str(int(coord_list[1])-10) + '][' + coord_list[2] + '] * (' + line_list[-1] + ')')
          elif int(coord_list[1]) < 20:
            coeff_3_list.append(line_list[7] + 'II_3[' + str(int(coord_list[1])-15) + '][' + coord_list[2] + '] * (' + line_list[-1] + ')')
          else:
            coeff_4_list.append(line_list[7] + 'II_4[' + str(int(coord_list[1])-20) + '][' + coord_list[2] + '] * (' + line_list[-1] + ')')

  c_file.close()
  

  
  #write_list('./out.c', func_num, 0, coeff_0_list)
  #write_list('./out.c', func_num, 1, coeff_1_list)
  #write_list('./out.c', func_num, 2, coeff_2_list)
  #write_list('./out.c', func_num, 3, coeff_3_list)
  write_list('./out.c', func_num, 4, coeff_4_list)


def gen_guard(func_num):

  c_file = open('./sdsoc/face_detect.cpp', 'r')
  out_file = open('./out.c', 'a')

  enter = 0
  coord_dict = {}
  coeff_0_list = []
  coeff_1_list = []
  coeff_2_list = []
  coeff_3_list = []
  coeff_4_list = []



  for line in c_file:
    if line.startswith('int classifier'+str(func_num)+ '('):
      enter = 1
    if line.startswith('}'):
      enter = 0
      
    if enter == 1:
      if(line.startswith('  if(final_sum')):
        line = line.replace('final_sum', 'final_sum_' + str(func_num))
        out_file.write('\n//classifier' + str(func_num) + '\n')
        out_file.write(line)
      if(line.startswith('     return_value')):
        line = line.replace('return_value', 'ss[' + str(func_num) + ']')
        out_file.write(line)
      if(line.startswith('  else')):
        out_file.write(line)




  c_file.close()
  out_file.close()  

  
def print_dict(foo_dict):
  key_list = foo_dict.keys()
  key_list.sort()
  for i in key_list:
    print str(i) + ' -> ' + str(foo_dict[i])

def print_list(foo_list):
  for i in foo_list:
    print str(i) + ','

  print '\n' 

def write_list(file_name, func_num, par_num, foo_list):
  out_file = open(file_name, 'a')
  out_file.write('\n//' + str(par_num*5) + '-' + str((par_num+1)*5-1) + '\n')
  out_file.write('int sum_' + str(func_num) + '_' + str(par_num) + '=0;\n') 
  for i in foo_list:
    out_file.write('sum_' + str(func_num) + '_' + str(par_num) + ' = sum_' + str(func_num) + '_' + str(par_num) + ' + ' + str(i) + ';\n')

  out_file.close()


def write_final_sum(file_name):
  out_file = open(file_name, 'a')
  for i in range(52):
    out_file.write('int final_sum_' + str(i) + ' = 0;\n')
    for j in range(1):
      out_file.write('final_sum_' + str(i) + ' = final_sum_' + str(i) + ' + sum_' + str(i) + '_' + str(j) + ';\n')

  out_file.close()



if __name__ == "__main__":
  tmp_file = open("./out.c", 'w')
  tmp_file.close()
  for i in range(52):
    tmp_file = open("./out.c", 'a')
    tmp_file.write("\n\n\n//classifier" + str(i) + "\n")
    tmp_file.close()
    gen_coeff(i)
  write_final_sum('./out.c')

  for i in range(52):
    gen_guard(i)














