#!/bin/bash -e
source vivado_setup
source xrt_setup
g++ -Wall -g -std=c++11 host.cpp check_result.cpp -o app.exe -I${XILINX_XRT}/include/ -I${XILINX_VIVADO}/include/ -L${XILINX_XRT}/lib/ -lOpenCL -lpthread -lrt -lstdc++
