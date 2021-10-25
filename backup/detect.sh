#!/bin/bash

for i in {1..10000}
do
  echo ''
  echo ''
  make report
  #squeue
  echo 'Current time is :'$(date "+%Y-%m-%d %H:%M:%S")
  sleep 10
done
