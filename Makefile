
#prj_name=optical_flow
prj_name=rendering


src=./common/verilog_src
ws=workspace
ws_sdk=$(ws)/F007_sdk_$(prj_name)
ws_overlay=$(ws)/F001_overlay
ws_hls=$(ws)/F002_hls_$(prj_name)
ws_syn=$(ws)/F003_syn_$(prj_name)
ws_impl=$(ws)/F004_impl_$(prj_name)
ws_bit=$(ws)/F005_bits_$(prj_name)
ws_mbft=$(ws)/F007_mono_bft_$(prj_name)

operators_dir=./input_src/$(prj_name)/operators
operators_src=$(wildcard $(operators_dir)/*.cpp)
operators=$(basename $(notdir $(operators_src)))
operators_hls_targets=$(foreach n, $(operators), $(ws_hls)/runLog$(n).log)
operators_syn_targets=$(foreach n, $(operators), $(ws_syn)/$(n)/page_netlist.dcp)
operators_impl_targets=$(foreach n, $(operators), $(ws_impl)/$(n)/page_routed.dcp)
operators_bit_targets=$(foreach n, $(operators), $(ws_bit)/$(n).bit)
operators_ip_targets=$(foreach n, $(operators), $(ws_mbft)/ip_repo/$(n)/prj/floorplan_static.xpr)
mono_bft_target=$(ws_mbft)/prj/floorplan_static.runs/impl_1/floorplan_static_wrapper.bit
download_target=$(ws_bit)/download.tcl $(ws_bit)/qsub_run.sh
config_target=$(ws_mbft)/config.cpp 



#all: $(ws_overlay)/overlay.dcp  
#all: $(operators_hls_targets) 
#all: $(operators_syn_targets) 
#all: $(operators_bit_targets) 
#all: $(download_target)
#all: $(mono_bft_target)
#all: $(operators_ip_targets)
#all: $(download_target) $(mono_bft_target) 
#all: $(config_target) 


all: $(download_target)


config: $(config_target)

$(config_target): $(operators_src)
	python2 pr_flow.py $(prj_name) -cfg -op '$(basename $(notdir $^))'
	cp $(ws)/F008_sdk_$(prj_name)/cpp_src/* $(ws)/vitis/$(prj_name)/src/

download: $(download_target)
	cd $(ws_bit) && ./qsub_run.sh 

$(download_target): $(operators_bit_targets)
	python2 pr_flow.py $(prj_name) -bit -op '$(basename $(notdir $^))'

# Implementation from post-synthesis DCP to bitstreams
# generate bitstream for each operator
$(operators_bit_targets):$(ws_bit)/%.bit:$(ws_syn)/%/page_netlist.dcp $(ws_overlay)/overlay.dcp 
	python2 pr_flow.py $(prj_name) -impl -op $(basename $(notdir $@))
	cd $(ws_impl)/$(basename $(notdir $@)) && ./qsub_run.sh

syn: $(operators_syn_targets)

# Out-of-Context Synthesis from Verilog to post-synthesis DCP
$(operators_syn_targets):$(ws_syn)/%/page_netlist.dcp:$(ws_hls)/runLog%.log
	python2 pr_flow.py $(prj_name) -syn -op $(subst runLog,,$(basename $(notdir $<)))
	cd $(ws_syn)/$(subst runLog,,$(basename $(notdir $<)))/riscv && ./qsub_run.sh
	cd $(ws_syn)/$(subst runLog,,$(basename $(notdir $<))) && ./qsub_run.sh


# High-Level-Synthesis from C to Verilog
$(operators_hls_targets):$(ws_hls)/runLog%.log:$(operators_dir)/%.cpp $(operators_dir)/%.h
	python2 pr_flow.py $(prj_name) -hls -op $(basename $(notdir $<))
	cd $(ws_hls) && ./qsub_run_$(basename $(notdir $<)).sh

mono_prj: $(mono_bft_target)

# prepare the logic equivalent monolithic project 
$(mono_bft_target): $(ws_overlay)/src  $(operators_ip_targets)
	python2 pr_flow.py $(prj_name) -mbft
	cd $(ws_mbft) && ./main.sh

# prepare the ip package for monolithic project
$(operators_ip_targets):$(ws_mbft)/ip_repo/%/prj/floorplan_static.xpr:$(ws_hls)/runLog%.log
	echo $@
	python2 pr_flow.py $(prj_name) -ip -op $(subst runLog,,$(basename $(notdir $<)))
	cd $(ws_mbft)/ip_repo/$(subst runLog,,$(basename $(notdir $<))) && ./qsub_run.sh


# Overlay Generation
$(ws_overlay)/overlay.dcp: $(ws_overlay)/src 
	cd $(ws_overlay) && ./main.sh

$(ws_overlay)/src : common/verilog_src/* 
	python2 pr_flow.py $(prj_name) -g



$(ws_sdk): $(src)/*.cc $(src)/*.h 
	mkdir -p $@ 
	cp -rf  $^ $@







.PHONY: report 
report: 
	 python2 ./pr_flow.py $(prj_name) -op '$(basename $(notdir $(operators_bit_targets)))' -rpt

clean:
	rm -rf ./workspace

