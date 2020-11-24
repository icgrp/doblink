############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2018 Xilinx, Inc. All Rights Reserved.
############################################################
open_project dirc
set_top circ_buff_read_many128
add_files hls_src/circ_buff_read_many_128.cpp
add_files hls_src/circ_buff_write_many_128.cpp
add_files hls_src/consumer.cpp
add_files hls_src/producer.cpp
open_solution "write6"
set_part {xczu9eg-ffvb1156-2-i}
create_clock -period 4 -name default
config_export -format ip_catalog -rtl verilog
#source "./dirc/write6/directives.tcl"
#csim_design
csynth_design
#cosim_design
export_design -rtl verilog -format ip_catalog
