#!/usr/bin/env python
import re


class find_max:
  def __init__(self):
    self.N = 6
    self.max_num_list = []
    for i in range(self.N):
      self.max_num_list.append(0)

  def update(self, candidate_list):
    for i in range(self.N):
      if (self.max_num_list[i] < candidate_list[i]):
        self.max_num_list[i] = candidate_list[i]

class para_bram():
  def __init__(self):
    self.par_0_list = [[], [], [], [], [], [], [], [], [], [], [], []]
    self.par_1_list = [[], [], [], [], [], [], [], [], [], [], [], []]
    self.par_2_list = [[], [], [], [], [], [], [], [], [], [], [], []]
    self.par_3_list = [[], [], [], [], [], [], [], [], [], [], [], []]
    self.par_4_list = [[], [], [], [], [], [], [], [], [], [], [], []]

  def update(self, par_list, cand_list):
    for i in range(len(cand_list)):
        par_list[i].append(cand_list[i])

    for i in range(len(cand_list), 12):
        par_list[i].append(0)


  def update_cluster(self, cand_0_list, 
                   cand_1_list,
                   cand_2_list,
                   cand_3_list,
                   cand_4_list):

    self.update(self.par_0_list, cand_0_list)
    self.update(self.par_1_list, cand_1_list)
    self.update(self.par_2_list, cand_2_list)
    self.update(self.par_3_list, cand_3_list)
    self.update(self.par_4_list, cand_4_list)

  def print_list(self, list_in):
    print ''
    for i in list_in:
      print i

  def print_lists(self):
    self.print_list(self.par_0_list)
    self.print_list(self.par_1_list)
    self.print_list(self.par_2_list)
    self.print_list(self.par_3_list)
    self.print_list(self.par_4_list)

  def write_list(self, num, out_name, list_in):
    out_file = open(out_name, 'a')
    out_file.write('\n')
    j = 0
    for i in list_in:
      str_tmp = str(i)
      str_tmp = str_tmp.replace('[', '{')
      str_tmp = str_tmp.replace(']', '}')
      str_tmp = 'int coord_' + str(num) + '_' + str(j) + '[2861] = ' + str_tmp  + ';\n'
      out_file.write(str_tmp)
      j=j+1


  def write_lists(self, out_name):
    self.write_list(0, out_name, self.par_0_list)
    self.write_list(1, out_name, self.par_1_list)
    self.write_list(2, out_name, self.par_2_list)
    self.write_list(3, out_name, self.par_3_list)
    self.write_list(4, out_name, self.par_4_list)


class para_extract:
  def __init__(self, in_name, out_name):
    self.in_name = in_name
    self.out_name = out_name
    self.cand_0_list = [800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800]
    self.cand_1_list = [800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800]
    self.cand_2_list = [800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800]
    self.cand_3_list = [800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800]
    self.cand_4_list = [800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800]
    self.cand_5_list = [800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800]

  def init_cand_lists(self):
    self.cand_0_list = [800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800]
    self.cand_1_list = [800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800]
    self.cand_2_list = [800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800]
    self.cand_3_list = [800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800]
    self.cand_4_list = [800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800]
    self.cand_5_list = [800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800]

  def update_paras(self, para_bram):
    file_in = open(self.in_name, 'r')
    file_out = open(self.out_name, 'w')
    start = 0;
    start_num = 0;
    for line in file_in:
      if line.startswith('stage ='):
        start = 1;
        start_num = 0;
        
      if start == 1 and start_num > 0:
        num_list = re.findall(r"\d+", line)
        if int(num_list[1])<5:
          self.cand_0_list[int(num_list[0])] = int(num_list[1])*32+int(num_list[2])
        elif int(num_list[1])<10:
          self.cand_1_list[int(num_list[0])] = int(num_list[1])*32+int(num_list[2])
        elif int(num_list[1])<15:
          self.cand_2_list[int(num_list[0])] = int(num_list[1])*32+int(num_list[2])
        elif int(num_list[1])<20:
          self.cand_3_list[int(num_list[0])] = int(num_list[1])*32+int(num_list[2])
        else:
          self.cand_4_list[int(num_list[0])] = int(num_list[1])*32+int(num_list[2])
      if start == 1:
        start_num = start_num+1
        if start_num == 13:
          start = 0
          start_num = 0
         

          para_bram.update_cluster(self.cand_0_list, 
                   self.cand_1_list,
                   self.cand_2_list,
                   self.cand_3_list,
                   self.cand_4_list)
          self.init_cand_lists()
          
    #file_out.write(str(para_bram.print_lists()))

    file_in.close();
    file_out.close();


if __name__ == "__main__":
  #max_num = find_max()
  
  #count_page(max_num)

  para_bram = para_bram()

  para_extract = para_extract("strong_classifier_csim.log", "out.c")
  para_extract.update_paras(para_bram)

  #para_bram.print_lists()
  para_bram.write_lists('out.c')
  







