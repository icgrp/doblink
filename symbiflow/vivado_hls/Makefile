base=$(abspath .)

symb_dir?=/scratch/unsafe/pld/symbiflow-arch-defs.new
YOSYS = $(symb_dir)/env/conda/envs/symbiflow_arch_def_base/bin/yosys
VPR = $(symb_dir)/env/conda/envs/symbiflow_arch_def_base/bin/vpr
PYTHON = $(symb_dir)/env/conda/envs/symbiflow_arch_def_base/bin/python
#VPR = /scratch/safe/SymbiFlow/vtr-verilog-to-routing/vpr/vpr

SYNTH_TCL = $(symb_dir)/xc/xc7/yosys/conv.tcl

ARCH = $(symb_dir)/build/xc/xc7/archs/zynq7_z020/devices/xc7z020-virt/arch.timing.xml
DEVICE = xc7z020-test
PART = xc7z020clg400-1
RR_GRAPH = $(symb_dir)/build/xc/xc7/archs/zynq7_z020/devices/rr_graph_xc7a50t_test.rr_graph.real.bin.xml
RR_GRAPH_BIN = $(symb_dir)/build/xc/xc7/archs/zynq7_z020/devices/rr_graph_xc7z020_test.rr_graph.real.bin

device_dir?=$(symb_dir)/build/xc/xc7/archs/zynq7_z020/devices/

YOSYS_MEMORY_PATCH = /scratch/safe/SymbiFlow/pr_flow/symbiflow/memory/yosys/yosys_memory_patch.sh
MERGE_PORTS = /scratch/safe/SymbiFlow/pr_flow/symbiflow/memory/yosys/merge_ports.perl
CLOCK_PATCH = /scratch/safe/SymbiFlow/pr_flow/symbiflow/clk/2clkto1clk.sh

targets=$(notdir $(wildcard $(src)/*))
targets:=$(filter-out flow_calc_1 flow_calc_2 leaf_Interface,$(targets))
#$(info $(targets))

tmp_pref:=$(shell mktemp -u)

export symb_dir

all: $(addsuffix /out.route.wrap,$(targets))


%.wrap:
	- $(MAKE) $*


.PRECIOUS: %.eblif %.net %.place %.route %.fasm $(targets:=/out.eblif) $(targets:=/out.net) $(targets:=/out.place) $(targets:=/out.route) $(targets:=/top.fasm)
.SECONDARY: %.eblif %.net %.place %.route %.fasm $(targets:=/out.eblif) $(targets:=/out.net) $(targets:=/out.place) $(targets:=/out.route) $(targets:=/top.fasm)

#$(targets): %: %/out.eblif
#$(targets): %: %/out.eblif %/out.net %/out.place %/out.route
#$(targets): %: %/out.route
#$(targets): %: %/out.eblif %/out.net %/out.place

#/tmp/arch.timing.xml: $(ARCH)
#	@ cp $(ARCH) /tmp/arch.timing.xml

#/tmp/rr_graph.real.bin: $(RR_GRAPH_BIN)
#	@ cp $(RR_GRAPH_BIN) /tmp/rr_graph.real.bin

$(abspath $(targets)):
	@ mkdir $@

#%/out.ppr: %/out.eblif
#	@echo "Running VPR Full Flow"
#	-@ cd $* && /usr/bin/time --output=$(@F).time $(VPR) /tmp/arch.timing.xml out.eblif --device $(DEVICE) \
        --min_route_chan_width_hint 100 \
        --read_rr_graph /tmp/rr_graph.real.bin \
        --max_criticality 0.0 \
        --max_router_iterations 500 \
        --routing_failure_predictor off \
        --router_high_fanout_threshold -1 \
        --constant_net_method route \
        --route_chan_width 500 \
        --clock_modeling route \
        --place_algorithm bounding_box \
        --enable_timing_computations off \
        --allow_unrelated_clustering on \
        --clustering_pin_feasibility_filter on \
	--balance_block_type_utilization on \
	--target_ext_pin_util BLK-TL-SLICEL:0.7 BLK-TL-SLICEM:0.7 BLK-TL-DSP_R:0 \
        --pack --place --route --pack_verbosity 0 \
	--pres_fac_mult 2 --initial_pres_fac 2 \
	--bb_factor 4 \
	--disable_check_route on \
	--first_iter_pres_fac 1 --astar_fac 6 \
	--disable_errors check_unbuffered_edges:check_route \
	--allow_dangling_combinational_nodes on \
	--suppress_warnings /tmp/noisy_warnings.log,\
	sum_pin_class:check_unbuffered_edges:\
	load_rr_indexed_data_T_values:check_rr_node:\
	trans_per_R
#\
#	--fix_pins ../top_io.place

#        --min_route_chan_width_hint 100 \
        --read_rr_graph $(RR_GRAPH_BIN) \
        --max_criticality 0.0 \
        --max_router_iterations 500 \
        --routing_failure_predictor off \
	--place_chan_width -1 \
        --router_high_fanout_threshold -1 \
        --constant_net_method route \
        --route_chan_width 500 \
        --clock_modeling route \
        --place_algorithm bounding_box \
        --enable_timing_computations off \
        --allow_unrelated_clustering on \
        --clustering_pin_feasibility_filter on \
	--balance_block_type_utilization on \
	--target_ext_pin_util BLK-TL-SLICEL:0.7 BLK-TL-SLICEM:0.7 BLK-TL-DSP_R:0 \
        --pack --pack_verbosity 0 \
	--disable_errors check_unbuffered_edges:check_route \
	--allow_dangling_combinational_nodes on \
	--suppress_warnings /tmp/noisy_warnings.log,\
	sum_pin_class:check_unbuffered_edges:\
	load_rr_indexed_data_T_values:check_rr_node:\
	trans_per_R


%/top_io.place: %/out.eblif %/out.net %/top.pcf
	cd $* && PYTHONPATH=$(symb_dir)/utils \
	  $(PYTHON) \
	  $(symb_dir)/xc/common/utils/prjxray_create_ioplace.py \
	  --map $(symb_dir)/build/xc/xc7/pynqz1-full_pinmap.csv \
	  --blif out.eblif \
	  --pcf top.pcf \
	  --net out.net \
	  --out top_io.place

%/out.gui: %/out.eblif
	@echo "Running VPR Packing Only"
	-@ cd $* && $(VPR) $(ARCH) out.eblif --device $(DEVICE) \
	 --read_rr_graph $(RR_GRAPH_BIN) \
	 --max_router_iterations 500 \
	 --routing_failure_predictor off \
	 --router_high_fanout_threshold -1 \
	 --constant_net_method route \
	 --route_chan_width 500 \
	 --router_heap bucket \
	 --clock_modeling route \
	 --place_delta_delay_matrix_calculation_method dijkstra \
	 --place_delay_model delta_override \
         --clustering_pin_feasibility_filter on \
	 --check_route quick \
	 --strict_checks off \
	 --allow_dangling_combinational_nodes on \
	 --disable_errors check_unbuffered_edges:check_route \
	 --congested_routing_iteration_threshold 0.8 \
	 --incremental_reroute_delay_ripup off \
	 --base_cost_type delay_normalized_length_bounded \
	 --bb_factor 10 \
	 --initial_pres_fac  4.0 \
	 --check_rr_graph off \
	 --suppress_warnings noisy_warnings.log,sum_pin_class:check_unbuffered_edges:load_rr_indexed_data_T_values:check_rr_node:trans_per_R:check_route \
	 --read_placement_delay_lookup $(device_dir)/rr_graph_xc7z020_test.place_delay.bin \
	 --disp on --save_graphics on 
	 #--balance_block_type_utilization off \

%/out.net: %/out.eblif
	@echo "Running VPR Packing Only"
	-@ cd $* && /usr/bin/time --output=$(@F).time $(VPR) $(ARCH) out.eblif --device $(DEVICE) \
	 --read_rr_graph $(RR_GRAPH_BIN) \
	 --max_router_iterations 500 \
	 --routing_failure_predictor off \
	 --router_high_fanout_threshold -1 \
	 --constant_net_method route \
	 --route_chan_width 500 \
	 --router_heap bucket \
	 --clock_modeling route \
	 --place_delta_delay_matrix_calculation_method dijkstra \
	 --place_delay_model delta_override \
	 --router_lookahead connection_box_map \
         --clustering_pin_feasibility_filter on \
	 --check_route quick \
	 --strict_checks off \
	 --allow_dangling_combinational_nodes on \
	 --disable_errors check_unbuffered_edges:check_route \
	 --congested_routing_iteration_threshold 0.8 \
	 --incremental_reroute_delay_ripup off \
	 --base_cost_type delay_normalized_length_bounded \
	 --bb_factor 10 \
	 --initial_pres_fac  4.0 \
	 --check_rr_graph off \
	 --suppress_warnings noisy_warnings.log,sum_pin_class:check_unbuffered_edges:load_rr_indexed_data_T_values:check_rr_node:trans_per_R:check_route \
	 --read_router_lookahead $(device_dir)/rr_graph_xc7z020_test.lookahead.bin \
	 --read_placement_delay_lookup $(device_dir)/rr_graph_xc7z020_test.place_delay.bin \
	 --balance_block_type_utilization off \
	 --pack

%/out.place: %/out.net %/top_io.place
	@echo "Running VPR Placing Only"
	-@ cd $* && /usr/bin/time --output=$(@F).time $(VPR) $(ARCH) out.eblif --device $(DEVICE) \
	 --read_rr_graph $(RR_GRAPH_BIN) \
	 --max_router_iterations 500 \
	 --routing_failure_predictor off \
	 --router_high_fanout_threshold -1 \
	 --constant_net_method route \
	 --route_chan_width 500 \
	 --router_heap bucket \
	 --clock_modeling route \
	 --timing_tradeoff 0.9 \
	 --place_delta_delay_matrix_calculation_method dijkstra \
	 --place_delay_model delta_override \
	 --router_lookahead connection_box_map \
	 --check_route quick \
	 --strict_checks off \
	 --allow_dangling_combinational_nodes on \
	 --disable_errors check_unbuffered_edges:check_route \
	 --congested_routing_iteration_threshold 0.8 \
	 --incremental_reroute_delay_ripup off \
	 --base_cost_type delay_normalized_length_bounded \
	 --bb_factor 3 \
	 --initial_pres_fac  4.0 \
	 --check_rr_graph off \
	 --read_router_lookahead $(device_dir)/rr_graph_xc7z020_test.lookahead.bin \
	 --read_placement_delay_lookup $(device_dir)/rr_graph_xc7z020_test.place_delay.bin \
	 --suppress_warnings noisy_warnings.log,sum_pin_class:check_unbuffered_edges:load_rr_indexed_data_T_values:check_rr_node:trans_per_R:check_route \
	 --balance_block_type_utilization off \
	 --fix_clusters top_io.place \
	 --place


%/out.route: %/out.place
	@echo "Running VPR Routing Only"
	-@ cd $* && /usr/bin/time --output=$(@F).time $(VPR) $(ARCH) out.eblif --device $(DEVICE) \
	 --read_rr_graph $(RR_GRAPH_BIN) \
	 --max_router_iterations 500 \
	 --routing_failure_predictor off \
	 --router_high_fanout_threshold -1 \
	 --constant_net_method route \
	 --route_chan_width 500 \
	 --timing_tradeoff 0.9 \
	 --router_heap bucket \
	 --clock_modeling route \
	 --place_delta_delay_matrix_calculation_method dijkstra \
	 --place_delay_model delta_override \
	 --router_lookahead connection_box_map \
	 --check_route quick \
	 --strict_checks off \
	 --allow_dangling_combinational_nodes on \
	 --disable_errors check_unbuffered_edges:check_route \
	 --congested_routing_iteration_threshold 0.8 \
	 --incremental_reroute_delay_ripup on \
	 --base_cost_type delay_normalized_length_bounded \
	 --bb_factor 3 \
	 --initial_pres_fac  4.0 \
	 --check_rr_graph off \
	 --suppress_warnings noisy_warnings.log,sum_pin_class:check_unbuffered_edges:load_rr_indexed_data_T_values:check_rr_node:trans_per_R:check_route \
	 --read_router_lookahead $(device_dir)/rr_graph_xc7z020_test.lookahead.bin \
	 --read_placement_delay_lookup $(device_dir)/rr_graph_xc7z020_test.place_delay.bin \
	 --balance_block_type_utilization off \
	 --route

%/top.fasm: %/out.route
	@ echo "Generating FASM"
	- cd $* && $(symb_dir)/build/env/conda/bin/genfasm $(ARCH) out.eblif \
		--device xc7z020-test \
		--read_rr_graph $(RR_GRAPH_BIN) \
		--max_router_iterations 500 \
		--routing_failure_predictor off \
		--router_high_fanout_threshold -1 \
		--constant_net_method route \
		--route_chan_width   500 \
		--router_heap bucket \
		--clock_modeling route \
		--place_delta_delay_matrix_calculation_method dijkstra \
		--place_delay_model delta_override \
		--router_lookahead connection_box_map \
		--check_route quick \
		--strict_checks off \
		--allow_dangling_combinational_nodes on \
		--disable_errors check_unbuffered_edges:check_route \
		--congested_routing_iteration_threshold 0.8 \
		--incremental_reroute_delay_ripup off \
		--base_cost_type delay_normalized_length_bounded \
		--bb_factor 10 \
		--initial_pres_fac 4.0 \
		--check_rr_graph off \
		--suppress_warnings noisy_warnings.log,sum_pin_class:check_unbuffered_edges:load_rr_indexed_data_T_values:check_rr_node:trans_per_R:check_route
	- cd $* && /usr/bin/cmake -E copy top.fasm genfasm.fasm
	- cd $* && cat top.fasm top_fasm_extra.fasm > top.concat.fasm
	- cd $* && /usr/bin/cmake -E rename top.concat.fasm top.fasm

%/top.frames: %/top.fasm
	- cd $* && PYTHONPATH=$(symb_dir)/build/env/conda/lib/python3.7/site-packages:$(symb_dir)/third_party/prjxray:$(symb_dir)/third_party/prjxray/third_party/fasm \
		$(symb_dir)/build/env/conda/bin/python3 \
		$(symb_dir)/third_party/prjxray/utils/fasm2frames.py \
		--db-root $(symb_dir)/third_party/prjxray-db/zynq7 \
		--sparse \
		--emit_pudc_b_pullup \
		--part  $(PART) \
		top.fasm \
		top.frames \
		--part $(PART)
%/top.bit: %/top.frames
	- cd $* && $(symb_dir)/build/third_party/prjxray/tools/xc7frames2bit \
		--frm_file top.frames \
		--output_file top.bit \
		--part_name $(PART) \
		--part_file $(symb_dir)/third_party/prjxray-db/zynq7/$(PART)/part.yaml

%/top_bit.v: %/top.bit %/top.pcf
	- cd $* && PYTHONPATH=$(symb_dir)/build/env/conda/lib/python3.7/site-packages:$(symb_dir)/third_party/prjxray:$(symb_dir)/third_party/prjxray/third_party/fasm:$(symb_dir)/utils \
                $(PYTHON) -mfasm2bels \
                --db_root $(symb_dir)/third_party/prjxray-db/zynq7 \
                --rr_graph $(RR_GRAPH_BIN) \
                --vpr_capnp_schema_dir $(symb_dir)/env/conda/envs/symbiflow_arch_def_base/capnp \
                --route out.route \
                --bitread $(symb_dir)/build/third_party/prjxray/tools/bitread \
                --bit_file top.bit \
                --fasm_file top.bit.fasm \
                --iostandard LVCMOS33 \
                --drive 12 \
                --pcf top.pcf \
                --eblif out.eblif \
                --top top \
                top_bit.v \
                top_bit.v.xdc \
                --part xc7z020clg400-1 \
                --connection_database $(symb_dir)/build/xc/xc7/archs/zynq7_z020/devices/xc7z020-virt/channels.db \
                --vpr_grid_map $(symb_dir)/build/xc/xc7/archs/zynq7_z020/devices/xc7z020-virt/vpr_grid_map.csv

%/runme.tcl: %/top_bit.v
	-cd $* && $(PYTHON) $(symb_dir)/xc/common/utils/vivado_create_runme.py \
                --name rendering_pynqz1_vivado \
                --verilog top_bit.v \
                --routing_xdc top_bit.v.xdc \
                --top top \
                --part xc7z020clg400-1 \
                --output_tcl runme.tcl \
                --clock_pins clk \
                --clock_periods 10.0

summary:
	@ ./summary.sh

%/out.eblif: %/top_synth.json
	- cd $* && $(PYTHON) $(symb_dir)/utils/split_inouts.py -i top_synth.json -o top.json
	- cd $* && OUT_EBLIF=out.pre_eblif \
	OUT_SYNTH_V=synth.vout \
	$(symb_dir)/utils/quiet_cmd.sh \
	$(YOSYS) -p "read_json top.json ; tcl $(SYNTH_TCL)" -l out.eblif.log
	- $(MERGE_PORTS) $*/out.pre_eblif $*/out.eblif > merge_ports.log 2> merge_ports_stderr.log
	
%/splitio: %/top_synth.json
	- cd $* && $(PYTHON) $(symb_dir)/utils/split_inouts.py -i top_synth.json -o top.json

$(targets:=.clean): %.clean:
	- @ rm -rf $*/out.eblif $*/out.net $*/out.place $*/out.route

clean: $(targets:=.clean)

echo_ap_%:
	echo $(abspath $*)

echo_%:
	@ echo $($*)

-include $(targets:=/.deps)

.SECONDEXPANSION:

# normally: -l $(tmp_pref)_$(*).log
# /usr/bin/cmake -E env TECHMAP_PATH=techmap symbiflow-arch-defs_SOURCE_DIR=fs.7020.rebase symbiflow-arch-defs_BINARY_DIR=020.rebase/build OUT_JSON=top_synth.json  OUT_SYNTH_V=top_synth.v OUT_FASM_EXTRA=top_fasm_extra.fasm PART_JSON= INPUT_XDC_FILE= USE_ROI=FALSE PCF_FILE=common/pynqz1.pcf PINMAP_FILE=/pynqz1-full_pinmap.csv yosys -p \
	# "tcl synth.tcl" -l top_synth.json.log buttons_pynqz1.v


#$(foreach d,$(wildcard $(src)/*/*.vhd),$(notdir $(patsubst %/,%,$(dir $d)))/$(notdir $d)): %.vhd: $(src)/%.vhd | $$(abspath $$(dir %))
#	- cp $< $(@D)

%/top.pcf: $(src)/%/top.pcf | $$(abspath $$(dir %))
	- cp $< $(@D) 

$(foreach d,$(wildcard $(src)/*/*.dat),$(notdir $(patsubst %/,%,$(dir $d)))/$(notdir $d)): %.dat: $(src)/%.dat | $$(abspath $$(dir %))
	- cp $< $@

$(foreach d,$(wildcard $(src)/*/*.sv),$(notdir $(patsubst %/,%,$(dir $d)))/$(notdir $d)): %.sv: $(src)/%.sv | $$(abspath $$(dir %))
	- cp $< $@

$(foreach d,$(wildcard $(src)/*/*.vh),$(notdir $(patsubst %/,%,$(dir $d)))/$(notdir $d)): %.vh: $(src)/%.vh | $$(abspath $$(dir %))
	- cp $< $@

$(foreach d,$(wildcard $(src)/*/*.v),$(notdir $(patsubst %/,%,$(dir $d)))/$(notdir $d)): %.v: $(src)/%.v | $$(abspath $$(dir %))
	- $(YOSYS_MEMORY_PATCH) $< $@

$(targets:=/top_synth.json): %/top_synth.json: $$(addprefix %/,$$(notdir $$(wildcard $(src)/%/*.dat))) $$(addprefix %/,$$(notdir $$(wildcard $(src)/%/*.v))) $$(addprefix %/,$$(notdir $$(wildcard $(src)/%/*.sv))) $$(addprefix %/,$$(notdir $$(wildcard $(src)/%/*.vh))) %/top.pcf | $$(abspath %)
	@ echo $*
	- cd $* && /usr/bin/cmake -E env TECHMAP_PATH=$(symb_dir)/xc/xc7/techmap symbiflow-arch-defs_SOURCE_DIR=$(symb_dir) symbiflow-arch-defs_BINARY_DIR=$(symb_dir)/build OUT_JSON=top_synth.json OUT_SYNTH_V=top_synth.vout OUT_FASM_EXTRA=top_fasm_extra.fasm PART_JSON= INPUT_XDC_FILE= USE_ROI=FALSE PCF_FILE=$*.pcf PINMAP_FILE=$(symb_dir)/build/xc/xc7/pynqz1-full_pinmap.csv $(YOSYS) -p "tcl ../synth.tcl" -l top_synth.json.log *.v
	- cd $* && /usr/bin/cmake -E touch top_fasm_extra.fasm
	- cd $* && /usr/bin/cmake -E touch_nocreate top_fasm_extra.fasm
	- cd $* && mv top_synth.vout.premap.v top_synth.vout.premap.vout
