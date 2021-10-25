src=/scratch/safe/ylxiao/F190523/benchmark_prflow_full_leaf
base=$(abspath .)

symb_dir?=/scratch/safe/SymbiFlow/symbiflow-arch-defs
YOSYS = /scratch/safe/SymbiFlow/symbiflow-arch-defs/build/env/conda/bin/yosys
#YOSYS = /scratch/safe/SymbiFlow/yosys/yosys
VPR = /scratch/safe/SymbiFlow/symbiflow-arch-defs.fresh/build/env/conda/bin/vpr
VPR = /scratch/safe/SymbiFlow/vtr-verilog-to-routing/build/vpr/vpr
#VPR = /scratch/safe/SymbiFlow/vtr-symbiflow/vpr/vpr
ARCH = /scratch/safe/SymbiFlow/symbiflow-arch-defs/build/xc7/archs/artix7/devices/xc7a50t-basys3-roi-virt/arch.timing.xml
#ARCH = /scratch/safe/SymbiFlow/symbiflow-arch-defs/build/xc7/archs/artix7/devices/xc7a50t-basys3-roi-virt/arch.play.xml
DEVICE = xc7a50t-basys3-test
RR_GRAPH = /scratch/safe/SymbiFlow/symbiflow-arch-defs/build/xc7/archs/artix7/devices/rr_graph_xc7a50t-basys3_test.rr_graph.real.bin.xml
#RR_GRAPH = /scratch/safe/SymbiFlow/symbiflow-arch-defs/build/xc7/archs/artix7/devices/rr_graph_xc7a50t-basys3_test.rr_graph.play.xml
#RR_GRAPH = /scratch/safe/SymbiFlow/symbiflow-arch-defs/build/xc7/archs/artix7/devices/rr_graph_xc7a50t-basys3_test.rr_graph.real.pretty.xml
#RR_GRAPH = rr_graph.real.bin.xml
#RR_GRAPH = /scratch/safe/SymbiFlow/symbiflow-arch-defs/build/xc7/archs/artix7/devices/rr_graph_xc7a50t-basys3_test.rr_graph.real.bin.xml


YOSYS_MEMORY_PATCH = /scratch/safe/SymbiFlow/pr_flow/symbiflow/memory/yosys/yosys_memory_patch.sh
MERGE_PORTS = /scratch/safe/SymbiFlow/pr_flow/symbiflow/memory/yosys/merge_ports.perl

targets=$(notdir $(wildcard $(src)/*))
targets:=$(filter-out flow_calc_1 flow_calc_2 leaf_Interface,$(targets))
#$(info $(targets))

tmp_pref:=$(shell mktemp -u)

export symb_dir

all: $(addsuffix /out.net,$(targets)) $(addsuffix /out.place,$(targets)) $(addsuffix /out.route,$(targets))

.PRECIOUS: %.eblif %.net %.place %.route $(targets:=/out.eblif) $(targets:=/out.net) $(targets:=/out.place) $(targets:=/out.route)
.SECONDARY: %.eblif %.net %.place %.route $(targets:=/out.eblif) $(targets:=/out.net) $(targets:=/out.place) $(targets:=/out.route)

#$(targets): %: %/out.eblif
$(targets): %: %/out.net %/out.place %/out.route
#$(targets): %: %/out.route
#$(targets): %: %/out.eblif %/out.net %/out.place


$(abspath $(targets)):
	@ mkdir $@

%/out.ppr: %/out.eblif
	@echo "Running VPR Full Flow"
	-@ cd $* && /usr/bin/time --output=$(@F).time $(VPR) $(ARCH) out.eblif --device $(DEVICE) \
        --min_route_chan_width_hint 100 \
        --read_rr_graph $(RR_GRAPH) \
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
	trans_per_R \
	--fix_pins ../top_io.place


%/out.net: %/out.eblif
	@echo "Running VPR Packing Only"
	-@ cd $* && /usr/bin/time --output=$(@F).time $(VPR) $(ARCH) out.eblif --device $(DEVICE) \
        --min_route_chan_width_hint 100 \
        --read_rr_graph $(RR_GRAPH) \
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
        --pack --pack_verbosity 0 \
 	--disable_errors check_unbuffered_edges:check_route \
	--allow_dangling_combinational_nodes on \
	--suppress_warnings /tmp/noisy_warnings.log,\
	sum_pin_class:check_unbuffered_edges:\
	load_rr_indexed_data_T_values:check_rr_node:\
	trans_per_R
	- grep "BLK-TL-BRAM_L: \# blocks" $*/vpr_stdout.log | tail -1 > $*/packed_bram_l_stats
	- grep "BLK-TL-SLICEL: \# blocks" $*/vpr_stdout.log | tail -1 > $*/packed_slicel_stats
	- grep "BLK-TL-SLICEM: \# blocks" $*/vpr_stdout.log | tail -1 > $*/packed_slicem_stats
	- grep "BLK-TL-DSP_R: \# blocks" $*/vpr_stdout.log | tail -1 > $*/packed_dsp_r_stats
	- grep "# Packing took" $*/vpr_stdout.log > $*/packing_time

%/out.place: %/out.net Makefile
	@echo "Running VPR Placing Only"
	- cd $* && /usr/bin/time --output=$(@F).time $(VPR) $(ARCH) out.eblif --device $(DEVICE) \
        --min_route_chan_width_hint 100 \
        --read_rr_graph $(RR_GRAPH) \
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
        --clustering_pin_feasibility_filter off \
	--place --disable_errors check_unbuffered_edges:check_route \
	--allow_dangling_combinational_nodes on \
	--suppress_warnings /tmp/noisy_warnings.log,\
	sum_pin_class:check_unbuffered_edges:\
	load_rr_indexed_data_T_values:check_rr_node:\
	trans_per_R \
	--fix_pins ../top_io.place

%/out.route: %/out.place
	@echo "Running VPR Routing Only"
	- @ cd $* && /usr/bin/time --output=$(@F).time $(VPR) $(ARCH) out.eblif --device $(DEVICE) \
        --read_rr_graph $(RR_GRAPH) \
        --min_route_chan_width_hint 100 \
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
        --clustering_pin_feasibility_filter off \
	--disable_check_route on \
        --route --pres_fac_mult 2 \
	--initial_pres_fac 2 \
	--bb_factor 4 \
	--first_iter_pres_fac 1 --astar_fac 6 \
	--disable_errors check_unbuffered_edges:check_route \
	--allow_dangling_combinational_nodes on \
	--suppress_warnings /tmp/noisy_warnings.log,\
	sum_pin_class:check_unbuffered_edges:\
	load_rr_indexed_data_T_values:check_rr_node:\
	trans_per_R

summary:
	@ ./summary.sh

$(targets:=.clean): %.clean:
	- @ rm -rf $*

clean: $(targets:=.clean)

echo_ap_%:
	echo $(abspath $*)

echo_%:
	@ echo $($*)

-include $(targets:=/.deps)

.SECONDEXPANSION:

$(foreach d,$(wildcard $(src)/*/*.dat),$(notdir $(patsubst %/,%,$(dir $d)))/$(notdir $d)): %.dat: $(src)/%.dat | $$(abspath $$(dir %))
	@ ln -s $< $@

$(foreach d,$(wildcard $(src)/*/*.v),$(notdir $(patsubst %/,%,$(dir $d)))/$(notdir $d)): %.v: $(src)/%.v | $$(abspath $$(dir %))
	@ $(YOSYS_MEMORY_PATCH) $< $@

$(targets:=/out.eblif): %/out.eblif: $$(addprefix %/,$$(notdir $$(wildcard $(src)/%/*.dat))) $$(addprefix %/,$$(notdir $$(wildcard $(src)/%/*.v))) | $$(abspath %)
	@ echo $*
	@ cp /scratch/safe/SymbiFlow/pr_flow/symbiflow/memory/leaf_interface_components/xpm_memory_tdpram_yosys.v $(dir $@)/
	- cd $* && OUT_EBLIF=out.pre_eblif \
	OUT_SYNTH_V=synth.vout \
	/usr/bin/time --output=$(tmp_pref)_$(*).time $(symb_dir)/utils/quiet_cmd.sh \
	$(YOSYS) -E .deps -p "tcl ../synth_M18x25.tcl" -l $(tmp_pref)_$(*).log \
	*.v && ( cat $(tmp_pref)_$(*).log $(tmp_pref)_$(*).time | gzip -c - > $(*).log.gz; rm  $(tmp_pref)_$(*).log $(tmp_pref)_$(*).time ; echo $(*) Finished Successfully) \
	|| (rm  $(tmp_pref)_$(*).log $(tmp_pref)_$(*).time && false ;echo $(*) Failed)
	zcat $*/*.log.gz | grep "Number of cells:" | tail -1 > $*/num_cells
	zcat $*/*.log.gz | grep "\$lut " | tail -1 > $*/num_luts
	zcat $*/*.log.gz | grep "RAMB18E1" | tail -1 > $*/num_ramb18
	zcat $*/*.log.gz | grep "RAMB36E1" | tail -1 > $*/num_ramb36dedicated_ports
	zcat $*/*.log.gz | grep "RAMB36_TDP_RW" | tail -1 > $*/num_ramb36merge_ports
	zcat $*/*.log.gz | tail -30 | grep "M18x25" | tail -1 > $*/num_m18x25
	zcat $*/*.log.gz | tail -5 | grep "CPU" > $*/yosys_runtime
	$(MERGE_PORTS) $*/out.pre_eblif $*/out.eblif
