### config_gen: generate the config_<benchmark_name>.cpp and config_<benchmark.h files for PrFlow
# Created by: Yuanlong Xiao (yuanlongxiao24@gmail.com)
#         at: University of Pennsylvania
#         in: 2018       
           
#
# The big picture:
# config_gen will generate files by using different parameters
# How it works (in a nutshell):
# Run command "python config_gen.py"
# [1] D. Park, Y. Xiao and A. DeHon, "Case for Acceleration of FPGA Compilation using Partial Reconfiguration", FPL2018
# [2] Y. Xiao,  D. Park, A. Butt, H. Giesen, Z. Han, R. Ding, N. Magnezi, R. Rubin and A. DeHon. "Reducing FPGA compile time with separate compilation for FPGA building blocks", FPT2019
# [3] Y. Xiao, S. Ahmed and A. DeHon. "Fast Linking of Separately-Compiled FPGA Blockswithout a NoC", FPT2020


import time
from gen_basic import gen_basic
import re

class config(gen_config):

