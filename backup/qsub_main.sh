#!/bin/bash -e
emailAddr="(youemail)@seas.upenn.edu"
qsub -N dirc32cores -q 70s_nick@icgrid43 -m abe -M $emailAddr  -l mem=120G -pe onenode 1  -cwd ./qsub_run.sh
