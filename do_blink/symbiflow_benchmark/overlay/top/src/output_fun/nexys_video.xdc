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

# user_led:0
set_property PACKAGE_PIN T14 [get_ports user_led0]
set_property IOSTANDARD LVCMOS25 [get_ports user_led0]

# user_led:1
set_property PACKAGE_PIN T15 [get_ports user_led1]
set_property IOSTANDARD LVCMOS25 [get_ports user_led1]

# user_sw:0
set_property PACKAGE_PIN E22 [get_ports user_sw0]
set_property IOSTANDARD LVCMOS25 [get_ports user_sw0]

# user_sw:1
set_property PACKAGE_PIN F21 [get_ports user_sw1]
set_property IOSTANDARD LVCMOS25 [get_ports user_sw1]

################################################################################
# Design constraints
################################################################################

set_property INTERNAL_VREF 0.75 [get_iobanks 35]

################################################################################
# Clock constraints
################################################################################


create_clock -name clk100 -period 10.0 [get_nets clk100]

set_clock_groups -group [get_clocks -include_generated_clocks -of [get_nets sys_clk]] -group [get_clocks -include_generated_clocks -of [get_nets main_crg_clkin]] -asynchronous

################################################################################
# False path constraints
################################################################################


set_false_path -through [get_nets -hierarchical -filter {mr_ff == TRUE}] -quiet

set_false_path -to [get_pins -filter {REF_PIN_NAME == PRE} -of_objects [get_cells -hierarchical -filter {ars_ff1 == TRUE || ars_ff2 == TRUE}]] -quiet

set_max_delay -from [get_pins -filter {REF_PIN_NAME == C} -of_objects [get_cells -hierarchical -filter {ars_ff1 == TRUE}]] -to [get_pins -filter {REF_PIN_NAME == D} -of_objects [get_cells -hierarchical -filter {ars_ff2 == TRUE}]] 2.000 -quiet

create_pblock pblock_11
add_cells_to_pblock [get_pblocks pblock_11] [get_cells -quiet [list floorplan_static_i/leaf_11/inst]]
resize_pblock [get_pblocks pblock_11] -add {SLICE_X84Y50:SLICE_X115Y99}
resize_pblock [get_pblocks pblock_11] -add {DSP48_X5Y20:DSP48_X6Y39}
resize_pblock [get_pblocks pblock_11] -add {RAMB18_X5Y20:RAMB18_X6Y39}
resize_pblock [get_pblocks pblock_11] -add {RAMB36_X5Y10:RAMB36_X6Y19}
set_property SNAPPING_MODE ON [get_pblocks pblock_11]
set_property RESET_AFTER_RECONFIG true [get_pblocks pblock_11]


create_pblock pblock_9
add_cells_to_pblock [get_pblocks pblock_9] [get_cells -quiet [list floorplan_static_i/leaf_9/inst]]
resize_pblock [get_pblocks pblock_9] -add {SLICE_X116Y200:SLICE_X163Y249}
resize_pblock [get_pblocks pblock_9] -add {DSP48_X7Y80:DSP48_X8Y99}
resize_pblock [get_pblocks pblock_9] -add {RAMB18_X7Y80:RAMB18_X8Y99}
resize_pblock [get_pblocks pblock_9] -add {RAMB36_X7Y40:RAMB36_X8Y49}
set_property SNAPPING_MODE ON [get_pblocks pblock_9]
set_property RESET_AFTER_RECONFIG true [get_pblocks pblock_9]



create_pblock pblock_3
add_cells_to_pblock [get_pblocks pblock_3] [get_cells -quiet [list floorplan_static_i/leaf_3/inst]]
resize_pblock [get_pblocks pblock_3] -add {SLICE_X84Y150:SLICE_X115Y199}
resize_pblock [get_pblocks pblock_3] -add {DSP48_X5Y60:DSP48_X6Y79}
resize_pblock [get_pblocks pblock_3] -add {RAMB18_X5Y60:RAMB18_X6Y79}
resize_pblock [get_pblocks pblock_3] -add {RAMB36_X5Y30:RAMB36_X6Y39}
set_property SNAPPING_MODE ON [get_pblocks pblock_3]
set_property RESET_AFTER_RECONFIG true [get_pblocks pblock_3]


create_pblock pblock_4
add_cells_to_pblock [get_pblocks pblock_4] [get_cells -quiet [list floorplan_static_i/leaf_4/inst]]
resize_pblock [get_pblocks pblock_4] -add {SLICE_X50Y150:SLICE_X81Y199}
resize_pblock [get_pblocks pblock_4] -add {DSP48_X3Y60:DSP48_X4Y79}
resize_pblock [get_pblocks pblock_4] -add {RAMB18_X3Y60:RAMB18_X4Y79}
resize_pblock [get_pblocks pblock_4] -add {RAMB36_X3Y30:RAMB36_X4Y39}
set_property SNAPPING_MODE ON [get_pblocks pblock_4]
set_property RESET_AFTER_RECONFIG true [get_pblocks pblock_4]


create_pblock pblock_2
add_cells_to_pblock [get_pblocks pblock_2] [get_cells -quiet [list floorplan_static_i/leaf_14/inst]]
resize_pblock [get_pblocks pblock_2] -add {SLICE_X0Y200:SLICE_X49Y249}
resize_pblock [get_pblocks pblock_2] -add {DSP48_X0Y80:DSP48_X2Y99}
resize_pblock [get_pblocks pblock_2] -add {RAMB18_X0Y80:RAMB18_X2Y99}
resize_pblock [get_pblocks pblock_2] -add {RAMB36_X0Y40:RAMB36_X2Y49}
set_property SNAPPING_MODE ON [get_pblocks pblock_2]
set_property RESET_AFTER_RECONFIG true [get_pblocks pblock_2]


create_pblock pblock_6
add_cells_to_pblock [get_pblocks pblock_6] [get_cells -quiet [list floorplan_static_i/leaf_6/inst]]
resize_pblock [get_pblocks pblock_6] -add {SLICE_X50Y50:SLICE_X81Y99}
resize_pblock [get_pblocks pblock_6] -add {DSP48_X3Y20:DSP48_X4Y39}
resize_pblock [get_pblocks pblock_6] -add {RAMB18_X3Y20:RAMB18_X4Y39}
resize_pblock [get_pblocks pblock_6] -add {RAMB36_X3Y10:RAMB36_X4Y19}
set_property SNAPPING_MODE ON [get_pblocks pblock_6]
set_property RESET_AFTER_RECONFIG true [get_pblocks pblock_6]




set_property DONT_TOUCH true [get_cells floorplan_static_i/leaf_14/inst]
set_property HD.RECONFIGURABLE true [get_cells floorplan_static_i/leaf_14/inst]
set_property DONT_TOUCH true [get_cells floorplan_static_i/leaf_3/inst]
set_property HD.RECONFIGURABLE true [get_cells floorplan_static_i/leaf_3/inst]
set_property DONT_TOUCH true [get_cells floorplan_static_i/leaf_4/inst]
set_property HD.RECONFIGURABLE true [get_cells floorplan_static_i/leaf_4/inst]
set_property DONT_TOUCH true [get_cells floorplan_static_i/leaf_5/inst]
set_property HD.RECONFIGURABLE true [get_cells floorplan_static_i/leaf_5/inst]
set_property DONT_TOUCH true [get_cells floorplan_static_i/leaf_6/inst]
set_property HD.RECONFIGURABLE true [get_cells floorplan_static_i/leaf_6/inst]
set_property DONT_TOUCH true [get_cells floorplan_static_i/leaf_7/inst]
set_property HD.RECONFIGURABLE true [get_cells floorplan_static_i/leaf_7/inst]
set_property DONT_TOUCH true [get_cells floorplan_static_i/leaf_8/inst]
set_property HD.RECONFIGURABLE true [get_cells floorplan_static_i/leaf_8/inst]

set_property DONT_TOUCH true [get_cells floorplan_static_i/leaf_9/inst]
set_property HD.RECONFIGURABLE true [get_cells floorplan_static_i/leaf_9/inst]
set_property DONT_TOUCH true [get_cells floorplan_static_i/leaf_10/inst]
set_property HD.RECONFIGURABLE true [get_cells floorplan_static_i/leaf_10/inst]
set_property DONT_TOUCH true [get_cells floorplan_static_i/leaf_11/inst]
set_property HD.RECONFIGURABLE true [get_cells floorplan_static_i/leaf_11/inst]
set_property DONT_TOUCH true [get_cells floorplan_static_i/leaf_12/inst]
set_property HD.RECONFIGURABLE true [get_cells floorplan_static_i/leaf_12/inst]
set_property DONT_TOUCH true [get_cells floorplan_static_i/leaf_13/inst]
set_property HD.RECONFIGURABLE true [get_cells floorplan_static_i/leaf_13/inst]

set_property HD.RECONFIGURABLE true [get_cells floorplan_static_i/bft/inst]

create_pblock pblock_7
add_cells_to_pblock [get_pblocks pblock_7] [get_cells -quiet [list floorplan_static_i/leaf_7/inst]]
resize_pblock [get_pblocks pblock_7] -add {SLICE_X0Y0:SLICE_X49Y49}
resize_pblock [get_pblocks pblock_7] -add {DSP48_X0Y0:DSP48_X2Y19}
resize_pblock [get_pblocks pblock_7] -add {RAMB18_X0Y0:RAMB18_X2Y19}
resize_pblock [get_pblocks pblock_7] -add {RAMB36_X0Y0:RAMB36_X2Y9}
set_property SNAPPING_MODE ON [get_pblocks pblock_7]
set_property RESET_AFTER_RECONFIG true [get_pblocks pblock_7]

create_pblock pblock_8
add_cells_to_pblock [get_pblocks pblock_8] [get_cells -quiet [list floorplan_static_i/leaf_8/inst]]
resize_pblock [get_pblocks pblock_8] -add {SLICE_X116Y0:SLICE_X163Y49}
resize_pblock [get_pblocks pblock_8] -add {DSP48_X7Y0:DSP48_X8Y19}
resize_pblock [get_pblocks pblock_8] -add {RAMB18_X7Y0:RAMB18_X8Y19}
resize_pblock [get_pblocks pblock_8] -add {RAMB36_X7Y0:RAMB36_X8Y9}
set_property SNAPPING_MODE ON [get_pblocks pblock_8]
set_property RESET_AFTER_RECONFIG true [get_pblocks pblock_8]

create_pblock pblock_bft
add_cells_to_pblock [get_pblocks pblock_bft] [get_cells -quiet [list floorplan_static_i/bft/inst]]
resize_pblock [get_pblocks pblock_bft] -add {SLICE_X116Y50:SLICE_X139Y199 SLICE_X50Y100:SLICE_X115Y149 SLICE_X36Y50:SLICE_X49Y199}
resize_pblock [get_pblocks pblock_bft] -add {DSP48_X3Y40:DSP48_X6Y59 DSP48_X2Y20:DSP48_X2Y79}
resize_pblock [get_pblocks pblock_bft] -add {RAMB18_X3Y40:RAMB18_X6Y59 RAMB18_X2Y20:RAMB18_X2Y79}
resize_pblock [get_pblocks pblock_bft] -add {RAMB36_X3Y20:RAMB36_X6Y29 RAMB36_X2Y10:RAMB36_X2Y39}
set_property SNAPPING_MODE ON [get_pblocks pblock_bft]

create_pblock pblock_5
add_cells_to_pblock [get_pblocks pblock_5] [get_cells -quiet [list floorplan_static_i/leaf_5/inst]]
resize_pblock [get_pblocks pblock_5] -add {SLICE_X0Y150:SLICE_X23Y199}
resize_pblock [get_pblocks pblock_5] -add {DSP48_X0Y60:DSP48_X1Y79}
resize_pblock [get_pblocks pblock_5] -add {RAMB18_X0Y60:RAMB18_X1Y79}
resize_pblock [get_pblocks pblock_5] -add {RAMB36_X0Y30:RAMB36_X1Y39}
set_property SNAPPING_MODE ON [get_pblocks pblock_5]
set_property RESET_AFTER_RECONFIG true [get_pblocks pblock_5]

create_pblock pblock_10
add_cells_to_pblock [get_pblocks pblock_10] [get_cells -quiet [list floorplan_static_i/leaf_10/inst]]
resize_pblock [get_pblocks pblock_10] -add {SLICE_X140Y50:SLICE_X163Y99}
resize_pblock [get_pblocks pblock_10] -add {DSP48_X7Y20:DSP48_X8Y39}
resize_pblock [get_pblocks pblock_10] -add {RAMB18_X7Y20:RAMB18_X8Y39}
resize_pblock [get_pblocks pblock_10] -add {RAMB36_X7Y10:RAMB36_X8Y19}
set_property SNAPPING_MODE ON [get_pblocks pblock_10]
set_property RESET_AFTER_RECONFIG true [get_pblocks pblock_10]

create_pblock pblock_12
add_cells_to_pblock [get_pblocks pblock_12] [get_cells -quiet [list floorplan_static_i/leaf_12/inst]]
resize_pblock [get_pblocks pblock_12] -add {SLICE_X0Y100:SLICE_X23Y149}
resize_pblock [get_pblocks pblock_12] -add {DSP48_X0Y40:DSP48_X1Y59}
resize_pblock [get_pblocks pblock_12] -add {RAMB18_X0Y40:RAMB18_X1Y59}
resize_pblock [get_pblocks pblock_12] -add {RAMB36_X0Y20:RAMB36_X1Y29}
set_property SNAPPING_MODE ON [get_pblocks pblock_12]
set_property RESET_AFTER_RECONFIG true [get_pblocks pblock_12]

create_pblock pblock_13
add_cells_to_pblock [get_pblocks pblock_13] [get_cells -quiet [list floorplan_static_i/leaf_13/inst]]
resize_pblock [get_pblocks pblock_13] -add {SLICE_X0Y50:SLICE_X23Y99}
resize_pblock [get_pblocks pblock_13] -add {DSP48_X0Y20:DSP48_X1Y39}
resize_pblock [get_pblocks pblock_13] -add {RAMB18_X0Y20:RAMB18_X1Y39}
resize_pblock [get_pblocks pblock_13] -add {RAMB36_X0Y10:RAMB36_X1Y19}
set_property SNAPPING_MODE ON [get_pblocks pblock_13]
set_property RESET_AFTER_RECONFIG true [get_pblocks pblock_13]




create_pblock pblock_controller
add_cells_to_pblock [get_pblocks pblock_controller] [get_cells -quiet [list floorplan_static_i/nexys_video_0/inst]]
resize_pblock [get_pblocks pblock_controller] -add {SLICE_X140Y100:SLICE_X163Y199}
resize_pblock [get_pblocks pblock_controller] -add {DSP48_X7Y40:DSP48_X8Y79}
resize_pblock [get_pblocks pblock_controller] -add {RAMB18_X7Y40:RAMB18_X8Y79}
resize_pblock [get_pblocks pblock_controller] -add {RAMB36_X7Y20:RAMB36_X8Y39}
set_property SNAPPING_MODE ON [get_pblocks pblock_controller]

