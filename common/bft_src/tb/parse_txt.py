#!/usr/bin/python3

import subprocess
import pdb
import argparse



in_file = open('pi_out.txt', 'r')
out_file = open('pi_out_1.txt', 'w')

num = 0
for line in in_file:
  if (num == 0) | (num==1):
    out_file.write(line)
    num += 1
    continue

  if num % 2 == 0:
    num += 1
    out_file.write(line)
  else:
    num += 1

