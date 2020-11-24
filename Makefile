
prj_name=optical_flow


src=./common/verilog_src
ws=workspace
ws_sdk=$(ws)/F007_sdk_$(prj_name)
ws_overlay=$(ws)/F001_overlay
ws_hls=$(ws)/F002_hls_$(prj_name)
ws_syn=$(ws)/F003_syn_$(prj_name)

operators_dir=./input_src/$(prj_name)/operators
operators_src=$(wildcard $(operators_dir)/*.cc)
operators=$(basename $(notdir $(wildcard $(operators_dir)/*.cc)))
operators_hls_targets=$(foreach n, $(operators), $(ws_hls)/runLog$(n).log)
operators_syn_targets=$(foreach n, $(operators), $(ws_syn)/$(n)/page_netlist.dcp)




#all: $(ws_overlay)/overlay.dcp 
#all: $(operators_hls_targets) 
all: $(operators_syn_targets) 


# Overlay Generation
$(ws_overlay)/overlay.dcp: $(ws_overlay)/src $(ws_overlay)/dirc_ip 
	cd $(ws_overlay) && ./main.sh

$(ws_overlay)/src $(ws_overlay)/dirc_ip: common/verilog_src/*
	python pr_flow.py $(prj_name) -g



# Out-of-Context Synthesis from Verilog to post-synthesis DCP
$(operators_syn_targets):$(ws_syn)/%/page_netlist.dcp:$(ws_hls)/runLog%.log
	python pr_flow.py $(prj_name) -syn -op $(subst runLog, ,$(basename $(notdir $<)))
	cd $(ws_syn)/$(subst runLog,,$(basename $(notdir $<))) && ./qsub_run.sh










# High-Level-Synthesis from C to Verilog
$(operators_hls_targets):$(ws_hls)/runLog%.log:$(operators_dir)/%.cc
	python pr_flow.py $(prj_name) -hls -op $(basename $(notdir $<))
	cd $(ws_hls) && ./qsub_run_$(basename $(notdir $<)).sh







$(ws_sdk): $(src)/*.cc $(src)/*.h 
	mkdir -p $@ 
	cp -rf  $^ $@






.PHONY: report 
report:
	 python2 ./pr_flow/gen_report.py rendering
	 python2 ./pr_flow/gen_report.py dg_reg
	 python2 ./pr_flow/gen_report.py spam_filter
	 python2 ./pr_flow/gen_report.py bnn
	 python2 ./pr_flow/gen_report.py face_detection
	 python2 ./pr_flow/gen_report.py optical_flow

clean:

	rm -rf ./workspace/F003*
