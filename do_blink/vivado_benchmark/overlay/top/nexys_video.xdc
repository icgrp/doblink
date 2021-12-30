################################################################################
# IO constraints
################################################################################
# serial:0.tx
set_property PACKAGE_PIN AA19 [get_ports serial_tx]
set_property IOSTANDARD LVCMOS33 [get_ports serial_tx]

# serial:0.rx
set_property PACKAGE_PIN V18 [get_ports serial_rx]
set_property IOSTANDARD LVCMOS33 [get_ports serial_rx]

# cpu_reset:0
set_property PACKAGE_PIN G4 [get_ports cpu_reset]
set_property IOSTANDARD LVCMOS15 [get_ports cpu_reset]

# clk100:0
set_property PACKAGE_PIN R4 [get_ports clk100]
set_property IOSTANDARD LVCMOS33 [get_ports clk100]

# ddram:0.a
set_property PACKAGE_PIN M2 [get_ports {ddram_a[0]}]
set_property SLEW FAST [get_ports {ddram_a[0]}]
set_property IOSTANDARD SSTL15 [get_ports {ddram_a[0]}]

# ddram:0.a
set_property PACKAGE_PIN M5 [get_ports {ddram_a[1]}]
set_property SLEW FAST [get_ports {ddram_a[1]}]
set_property IOSTANDARD SSTL15 [get_ports {ddram_a[1]}]

# ddram:0.a
set_property PACKAGE_PIN M3 [get_ports {ddram_a[2]}]
set_property SLEW FAST [get_ports {ddram_a[2]}]
set_property IOSTANDARD SSTL15 [get_ports {ddram_a[2]}]

# ddram:0.a
set_property PACKAGE_PIN M1 [get_ports {ddram_a[3]}]
set_property SLEW FAST [get_ports {ddram_a[3]}]
set_property IOSTANDARD SSTL15 [get_ports {ddram_a[3]}]

# ddram:0.a
set_property PACKAGE_PIN L6 [get_ports {ddram_a[4]}]
set_property SLEW FAST [get_ports {ddram_a[4]}]
set_property IOSTANDARD SSTL15 [get_ports {ddram_a[4]}]

# ddram:0.a
set_property PACKAGE_PIN P1 [get_ports {ddram_a[5]}]
set_property SLEW FAST [get_ports {ddram_a[5]}]
set_property IOSTANDARD SSTL15 [get_ports {ddram_a[5]}]

# ddram:0.a
set_property PACKAGE_PIN N3 [get_ports {ddram_a[6]}]
set_property SLEW FAST [get_ports {ddram_a[6]}]
set_property IOSTANDARD SSTL15 [get_ports {ddram_a[6]}]

# ddram:0.a
set_property PACKAGE_PIN N2 [get_ports {ddram_a[7]}]
set_property SLEW FAST [get_ports {ddram_a[7]}]
set_property IOSTANDARD SSTL15 [get_ports {ddram_a[7]}]

# ddram:0.a
set_property PACKAGE_PIN M6 [get_ports {ddram_a[8]}]
set_property SLEW FAST [get_ports {ddram_a[8]}]
set_property IOSTANDARD SSTL15 [get_ports {ddram_a[8]}]

# ddram:0.a
set_property PACKAGE_PIN R1 [get_ports {ddram_a[9]}]
set_property SLEW FAST [get_ports {ddram_a[9]}]
set_property IOSTANDARD SSTL15 [get_ports {ddram_a[9]}]

# ddram:0.a
set_property PACKAGE_PIN L5 [get_ports {ddram_a[10]}]
set_property SLEW FAST [get_ports {ddram_a[10]}]
set_property IOSTANDARD SSTL15 [get_ports {ddram_a[10]}]

# ddram:0.a
set_property PACKAGE_PIN N5 [get_ports {ddram_a[11]}]
set_property SLEW FAST [get_ports {ddram_a[11]}]
set_property IOSTANDARD SSTL15 [get_ports {ddram_a[11]}]

# ddram:0.a
set_property PACKAGE_PIN N4 [get_ports {ddram_a[12]}]
set_property SLEW FAST [get_ports {ddram_a[12]}]
set_property IOSTANDARD SSTL15 [get_ports {ddram_a[12]}]

# ddram:0.a
set_property PACKAGE_PIN P2 [get_ports {ddram_a[13]}]
set_property SLEW FAST [get_ports {ddram_a[13]}]
set_property IOSTANDARD SSTL15 [get_ports {ddram_a[13]}]

# ddram:0.a
set_property PACKAGE_PIN P6 [get_ports {ddram_a[14]}]
set_property SLEW FAST [get_ports {ddram_a[14]}]
set_property IOSTANDARD SSTL15 [get_ports {ddram_a[14]}]

# ddram:0.ba
set_property PACKAGE_PIN L3 [get_ports {ddram_ba[0]}]
set_property SLEW FAST [get_ports {ddram_ba[0]}]
set_property IOSTANDARD SSTL15 [get_ports {ddram_ba[0]}]

# ddram:0.ba
set_property PACKAGE_PIN K6 [get_ports {ddram_ba[1]}]
set_property SLEW FAST [get_ports {ddram_ba[1]}]
set_property IOSTANDARD SSTL15 [get_ports {ddram_ba[1]}]

# ddram:0.ba
set_property PACKAGE_PIN L4 [get_ports {ddram_ba[2]}]
set_property SLEW FAST [get_ports {ddram_ba[2]}]
set_property IOSTANDARD SSTL15 [get_ports {ddram_ba[2]}]

# ddram:0.ras_n
set_property PACKAGE_PIN J4 [get_ports ddram_ras_n]
set_property SLEW FAST [get_ports ddram_ras_n]
set_property IOSTANDARD SSTL15 [get_ports ddram_ras_n]

# ddram:0.cas_n
set_property PACKAGE_PIN K3 [get_ports ddram_cas_n]
set_property SLEW FAST [get_ports ddram_cas_n]
set_property IOSTANDARD SSTL15 [get_ports ddram_cas_n]

# ddram:0.we_n
set_property PACKAGE_PIN L1 [get_ports ddram_we_n]
set_property SLEW FAST [get_ports ddram_we_n]
set_property IOSTANDARD SSTL15 [get_ports ddram_we_n]

# ddram:0.dm
set_property PACKAGE_PIN G3 [get_ports {ddram_dm[0]}]
set_property SLEW FAST [get_ports {ddram_dm[0]}]
set_property IOSTANDARD SSTL15 [get_ports {ddram_dm[0]}]

# ddram:0.dm
set_property PACKAGE_PIN F1 [get_ports {ddram_dm[1]}]
set_property SLEW FAST [get_ports {ddram_dm[1]}]
set_property IOSTANDARD SSTL15 [get_ports {ddram_dm[1]}]

# ddram:0.dq
set_property PACKAGE_PIN G2 [get_ports {ddram_dq[0]}]
set_property SLEW FAST [get_ports {ddram_dq[0]}]
set_property IOSTANDARD SSTL15 [get_ports {ddram_dq[0]}]
set_property IN_TERM UNTUNED_SPLIT_50 [get_ports {ddram_dq[0]}]

# ddram:0.dq
set_property PACKAGE_PIN H4 [get_ports {ddram_dq[1]}]
set_property SLEW FAST [get_ports {ddram_dq[1]}]
set_property IOSTANDARD SSTL15 [get_ports {ddram_dq[1]}]
set_property IN_TERM UNTUNED_SPLIT_50 [get_ports {ddram_dq[1]}]

# ddram:0.dq
set_property PACKAGE_PIN H5 [get_ports {ddram_dq[2]}]
set_property SLEW FAST [get_ports {ddram_dq[2]}]
set_property IOSTANDARD SSTL15 [get_ports {ddram_dq[2]}]
set_property IN_TERM UNTUNED_SPLIT_50 [get_ports {ddram_dq[2]}]

# ddram:0.dq
set_property PACKAGE_PIN J1 [get_ports {ddram_dq[3]}]
set_property SLEW FAST [get_ports {ddram_dq[3]}]
set_property IOSTANDARD SSTL15 [get_ports {ddram_dq[3]}]
set_property IN_TERM UNTUNED_SPLIT_50 [get_ports {ddram_dq[3]}]

# ddram:0.dq
set_property PACKAGE_PIN K1 [get_ports {ddram_dq[4]}]
set_property SLEW FAST [get_ports {ddram_dq[4]}]
set_property IOSTANDARD SSTL15 [get_ports {ddram_dq[4]}]
set_property IN_TERM UNTUNED_SPLIT_50 [get_ports {ddram_dq[4]}]

# ddram:0.dq
set_property PACKAGE_PIN H3 [get_ports {ddram_dq[5]}]
set_property SLEW FAST [get_ports {ddram_dq[5]}]
set_property IOSTANDARD SSTL15 [get_ports {ddram_dq[5]}]
set_property IN_TERM UNTUNED_SPLIT_50 [get_ports {ddram_dq[5]}]

# ddram:0.dq
set_property PACKAGE_PIN H2 [get_ports {ddram_dq[6]}]
set_property SLEW FAST [get_ports {ddram_dq[6]}]
set_property IOSTANDARD SSTL15 [get_ports {ddram_dq[6]}]
set_property IN_TERM UNTUNED_SPLIT_50 [get_ports {ddram_dq[6]}]

# ddram:0.dq
set_property PACKAGE_PIN J5 [get_ports {ddram_dq[7]}]
set_property SLEW FAST [get_ports {ddram_dq[7]}]
set_property IOSTANDARD SSTL15 [get_ports {ddram_dq[7]}]
set_property IN_TERM UNTUNED_SPLIT_50 [get_ports {ddram_dq[7]}]

# ddram:0.dq
set_property PACKAGE_PIN E3 [get_ports {ddram_dq[8]}]
set_property SLEW FAST [get_ports {ddram_dq[8]}]
set_property IOSTANDARD SSTL15 [get_ports {ddram_dq[8]}]
set_property IN_TERM UNTUNED_SPLIT_50 [get_ports {ddram_dq[8]}]

# ddram:0.dq
set_property PACKAGE_PIN B2 [get_ports {ddram_dq[9]}]
set_property SLEW FAST [get_ports {ddram_dq[9]}]
set_property IOSTANDARD SSTL15 [get_ports {ddram_dq[9]}]
set_property IN_TERM UNTUNED_SPLIT_50 [get_ports {ddram_dq[9]}]

# ddram:0.dq
set_property PACKAGE_PIN F3 [get_ports {ddram_dq[10]}]
set_property SLEW FAST [get_ports {ddram_dq[10]}]
set_property IOSTANDARD SSTL15 [get_ports {ddram_dq[10]}]
set_property IN_TERM UNTUNED_SPLIT_50 [get_ports {ddram_dq[10]}]

# ddram:0.dq
set_property PACKAGE_PIN D2 [get_ports {ddram_dq[11]}]
set_property SLEW FAST [get_ports {ddram_dq[11]}]
set_property IOSTANDARD SSTL15 [get_ports {ddram_dq[11]}]
set_property IN_TERM UNTUNED_SPLIT_50 [get_ports {ddram_dq[11]}]

# ddram:0.dq
set_property PACKAGE_PIN C2 [get_ports {ddram_dq[12]}]
set_property SLEW FAST [get_ports {ddram_dq[12]}]
set_property IOSTANDARD SSTL15 [get_ports {ddram_dq[12]}]
set_property IN_TERM UNTUNED_SPLIT_50 [get_ports {ddram_dq[12]}]

# ddram:0.dq
set_property PACKAGE_PIN A1 [get_ports {ddram_dq[13]}]
set_property SLEW FAST [get_ports {ddram_dq[13]}]
set_property IOSTANDARD SSTL15 [get_ports {ddram_dq[13]}]
set_property IN_TERM UNTUNED_SPLIT_50 [get_ports {ddram_dq[13]}]

# ddram:0.dq
set_property PACKAGE_PIN E2 [get_ports {ddram_dq[14]}]
set_property SLEW FAST [get_ports {ddram_dq[14]}]
set_property IOSTANDARD SSTL15 [get_ports {ddram_dq[14]}]
set_property IN_TERM UNTUNED_SPLIT_50 [get_ports {ddram_dq[14]}]

# ddram:0.dq
set_property PACKAGE_PIN B1 [get_ports {ddram_dq[15]}]
set_property SLEW FAST [get_ports {ddram_dq[15]}]
set_property IOSTANDARD SSTL15 [get_ports {ddram_dq[15]}]
set_property IN_TERM UNTUNED_SPLIT_50 [get_ports {ddram_dq[15]}]

# ddram:0.dqs_p
set_property SLEW FAST [get_ports {ddram_dqs_p[0]}]
set_property IOSTANDARD DIFF_SSTL15 [get_ports {ddram_dqs_p[0]}]

# ddram:0.dqs_p
set_property SLEW FAST [get_ports {ddram_dqs_p[1]}]
set_property IOSTANDARD DIFF_SSTL15 [get_ports {ddram_dqs_p[1]}]

# ddram:0.dqs_n
set_property PACKAGE_PIN K2 [get_ports {ddram_dqs_p[0]}]
set_property PACKAGE_PIN J2 [get_ports {ddram_dqs_n[0]}]
set_property SLEW FAST [get_ports {ddram_dqs_n[0]}]
set_property IOSTANDARD DIFF_SSTL15 [get_ports {ddram_dqs_n[0]}]

# ddram:0.dqs_n
set_property PACKAGE_PIN E1 [get_ports {ddram_dqs_p[1]}]
set_property PACKAGE_PIN D1 [get_ports {ddram_dqs_n[1]}]
set_property SLEW FAST [get_ports {ddram_dqs_n[1]}]
set_property IOSTANDARD DIFF_SSTL15 [get_ports {ddram_dqs_n[1]}]

# ddram:0.clk_p
set_property SLEW FAST [get_ports ddram_clk_p]
set_property IOSTANDARD DIFF_SSTL15 [get_ports ddram_clk_p]

# ddram:0.clk_n
set_property PACKAGE_PIN P5 [get_ports ddram_clk_p]
set_property PACKAGE_PIN P4 [get_ports ddram_clk_n]
set_property SLEW FAST [get_ports ddram_clk_n]
set_property IOSTANDARD DIFF_SSTL15 [get_ports ddram_clk_n]

# ddram:0.cke
set_property PACKAGE_PIN J6 [get_ports ddram_cke]
set_property SLEW FAST [get_ports ddram_cke]
set_property IOSTANDARD SSTL15 [get_ports ddram_cke]

# ddram:0.odt
set_property PACKAGE_PIN K4 [get_ports ddram_odt]
set_property SLEW FAST [get_ports ddram_odt]
set_property IOSTANDARD SSTL15 [get_ports ddram_odt]

# ddram:0.reset_n
set_property PACKAGE_PIN G1 [get_ports ddram_reset_n]
set_property SLEW FAST [get_ports ddram_reset_n]
set_property IOSTANDARD SSTL15 [get_ports ddram_reset_n]

################################################################################
# Design constraints
################################################################################

set_property INTERNAL_VREF 0.75 [get_iobanks 35]

################################################################################
# Clock constraints
################################################################################


create_clock -period 10.000 -name clk100 [get_nets clk100]

set_clock_groups -asynchronous -group [get_clocks -of_objects [get_nets clk100]]

################################################################################
# False path constraints
################################################################################


set_false_path -through [get_nets -hierarchical -filter {mr_ff == TRUE}] -quiet

set_false_path -to [get_pins -filter {REF_PIN_NAME == PRE} -of_objects [get_cells -hierarchical -filter {ars_ff1 == TRUE || ars_ff2 == TRUE}]] -quiet

set_max_delay -from [get_pins -filter {REF_PIN_NAME == C} -of_objects [get_cells -hierarchical -filter {ars_ff1 == TRUE}]] -to [get_pins -filter {REF_PIN_NAME == D} -of_objects [get_cells -hierarchical -filter {ars_ff2 == TRUE}]] 2.000 -quiet

create_pblock p_2
add_cells_to_pblock [get_pblocks p_2] [get_cells -quiet [list floorplan_static_i/leaf_empty_2/inst]]
resize_pblock [get_pblocks p_2] -add {SLICE_X0Y200:SLICE_X49Y249}
resize_pblock [get_pblocks p_2] -add {DSP48_X0Y80:DSP48_X2Y99}
resize_pblock [get_pblocks p_2] -add {RAMB18_X0Y80:RAMB18_X2Y99}
resize_pblock [get_pblocks p_2] -add {RAMB36_X0Y40:RAMB36_X2Y49}
set_property RESET_AFTER_RECONFIG true [get_pblocks p_2]
set_property SNAPPING_MODE ROUTING [get_pblocks p_2]
create_pblock p_6
add_cells_to_pblock [get_pblocks p_6] [get_cells -quiet [list floorplan_static_i/leaf_empty_6/inst]]
resize_pblock [get_pblocks p_6] -add {SLICE_X0Y0:SLICE_X49Y49}
resize_pblock [get_pblocks p_6] -add {DSP48_X0Y0:DSP48_X2Y19}
resize_pblock [get_pblocks p_6] -add {RAMB18_X0Y0:RAMB18_X2Y19}
resize_pblock [get_pblocks p_6] -add {RAMB36_X0Y0:RAMB36_X2Y9}
set_property RESET_AFTER_RECONFIG true [get_pblocks p_6]
set_property SNAPPING_MODE ROUTING [get_pblocks p_6]
create_pblock p_9
add_cells_to_pblock [get_pblocks p_9] [get_cells -quiet [list floorplan_static_i/leaf_empty_9/inst]]
resize_pblock [get_pblocks p_9] -add {SLICE_X116Y200:SLICE_X163Y249}
resize_pblock [get_pblocks p_9] -add {DSP48_X7Y80:DSP48_X8Y99}
resize_pblock [get_pblocks p_9] -add {RAMB18_X7Y80:RAMB18_X8Y99}
resize_pblock [get_pblocks p_9] -add {RAMB36_X7Y40:RAMB36_X8Y49}
set_property RESET_AFTER_RECONFIG true [get_pblocks p_9]
set_property SNAPPING_MODE ROUTING [get_pblocks p_9]
create_pblock p_11
add_cells_to_pblock [get_pblocks p_11] [get_cells -quiet [list floorplan_static_i/leaf_empty_11/inst]]
resize_pblock [get_pblocks p_11] -add {SLICE_X116Y0:SLICE_X163Y49}
resize_pblock [get_pblocks p_11] -add {DSP48_X7Y0:DSP48_X8Y19}
resize_pblock [get_pblocks p_11] -add {RAMB18_X7Y0:RAMB18_X8Y19}
resize_pblock [get_pblocks p_11] -add {RAMB36_X7Y0:RAMB36_X8Y9}
set_property RESET_AFTER_RECONFIG true [get_pblocks p_11]
set_property SNAPPING_MODE ROUTING [get_pblocks p_11]
create_pblock p_10
add_cells_to_pblock [get_pblocks p_10] [get_cells -quiet [list floorplan_static_i/leaf_empty_10/inst]]
resize_pblock [get_pblocks p_10] -add {SLICE_X84Y50:SLICE_X143Y99}
resize_pblock [get_pblocks p_10] -add {DSP48_X5Y20:DSP48_X7Y39}
resize_pblock [get_pblocks p_10] -add {RAMB18_X5Y20:RAMB18_X7Y39}
resize_pblock [get_pblocks p_10] -add {RAMB36_X5Y10:RAMB36_X7Y19}
set_property RESET_AFTER_RECONFIG true [get_pblocks p_10]
set_property SNAPPING_MODE ROUTING [get_pblocks p_10]
create_pblock p_13
add_cells_to_pblock [get_pblocks p_13] [get_cells -quiet [list floorplan_static_i/leaf_empty_13/inst]]
resize_pblock [get_pblocks p_13] -add {SLICE_X22Y50:SLICE_X81Y99}
resize_pblock [get_pblocks p_13] -add {DSP48_X2Y20:DSP48_X4Y39}
resize_pblock [get_pblocks p_13] -add {RAMB18_X1Y20:RAMB18_X4Y39}
resize_pblock [get_pblocks p_13] -add {RAMB36_X1Y10:RAMB36_X4Y19}
set_property RESET_AFTER_RECONFIG true [get_pblocks p_13]
set_property SNAPPING_MODE ROUTING [get_pblocks p_13]

set_property DONT_TOUCH true [get_cells floorplan_static_i/leaf_empty_2/inst]
set_property HD.RECONFIGURABLE true [get_cells floorplan_static_i/leaf_empty_2/inst]
set_property DONT_TOUCH true [get_cells floorplan_static_i/leaf_empty_6/inst]
set_property HD.RECONFIGURABLE true [get_cells floorplan_static_i/leaf_empty_6/inst]
set_property DONT_TOUCH true [get_cells floorplan_static_i/leaf_empty_9/inst]
set_property HD.RECONFIGURABLE true [get_cells floorplan_static_i/leaf_empty_9/inst]
set_property DONT_TOUCH true [get_cells floorplan_static_i/leaf_empty_10/inst]
set_property HD.RECONFIGURABLE true [get_cells floorplan_static_i/leaf_empty_10/inst]
set_property DONT_TOUCH true [get_cells floorplan_static_i/leaf_empty_11/inst]
set_property HD.RECONFIGURABLE true [get_cells floorplan_static_i/leaf_empty_11/inst]
set_property DONT_TOUCH true [get_cells floorplan_static_i/leaf_empty_13/inst]
set_property HD.RECONFIGURABLE true [get_cells floorplan_static_i/leaf_empty_13/inst]