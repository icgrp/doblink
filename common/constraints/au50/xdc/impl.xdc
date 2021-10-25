# # SLR pblocks
# create_pblock pblock_dynamic_SLR0
# create_pblock pblock_dynamic_SLR1
# 
# # SLR0
# resize_pblock [get_pblocks pblock_dynamic_SLR0] -add {SLICE_X229Y0:SLICE_X229Y29 SLICE_X216Y0:SLICE_X217Y29 SLICE_X118Y60:SLICE_X145Y119}
# resize_pblock [get_pblocks pblock_dynamic_SLR0] -add {BLI_HBM_APB_INTF_X30Y0:BLI_HBM_APB_INTF_X31Y0}
# resize_pblock [get_pblocks pblock_dynamic_SLR0] -add {BLI_HBM_AXI_INTF_X30Y0:BLI_HBM_AXI_INTF_X31Y0}
# resize_pblock [get_pblocks pblock_dynamic_SLR0] -add {DSP48E2_X30Y0:DSP48E2_X31Y5 DSP48E2_X16Y18:DSP48E2_X19Y41}
# resize_pblock [get_pblocks pblock_dynamic_SLR0] -add {RAMB18_X8Y24:RAMB18_X9Y47}
# resize_pblock [get_pblocks pblock_dynamic_SLR0] -add {RAMB36_X8Y12:RAMB36_X9Y23}
# resize_pblock [get_pblocks pblock_dynamic_SLR0] -add {URAM288_X2Y16:URAM288_X2Y31}
# resize_pblock [get_pblocks pblock_dynamic_SLR0] -add {CLOCKREGION_X0Y3:CLOCKREGION_X5Y3 CLOCKREGION_X0Y2:CLOCKREGION_X6Y2 CLOCKREGION_X5Y1:CLOCKREGION_X6Y1 CLOCKREGION_X0Y1:CLOCKREGION_X3Y1 CLOCKREGION_X0Y0:CLOCKREGION_X6Y0}
# resize_pblock pblock_dynamic_SLR0 -remove {IOB_X0Y208:IOB_X0Y259}
# resize_pblock pblock_dynamic_SLR0 -remove {IOB_X0Y52:IOB_X0Y103}
# 
# set_property SNAPPING_MODE ON [get_pblocks pblock_dynamic_SLR0]
# set_property PARENT pblock_dynamic_region  [get_pblocks pblock_dynamic_SLR0]  -quiet
# 
# # SLR1
# resize_pblock [get_pblocks pblock_dynamic_SLR1] -add {SLICE_X220Y300:SLICE_X221Y359 SLICE_X118Y240:SLICE_X145Y299}
# resize_pblock [get_pblocks pblock_dynamic_SLR1] -add {CONFIG_SITE_X0Y1:CONFIG_SITE_X0Y1}
# resize_pblock [get_pblocks pblock_dynamic_SLR1] -add {DSP48E2_X16Y90:DSP48E2_X19Y113}
# resize_pblock [get_pblocks pblock_dynamic_SLR1] -add {LAGUNA_X16Y120:LAGUNA_X19Y239}
# resize_pblock [get_pblocks pblock_dynamic_SLR1] -add {RAMB18_X8Y96:RAMB18_X9Y119}
# resize_pblock [get_pblocks pblock_dynamic_SLR1] -add {RAMB36_X8Y48:RAMB36_X9Y59}
# resize_pblock [get_pblocks pblock_dynamic_SLR1] -add {URAM288_X2Y64:URAM288_X2Y79}
# resize_pblock [get_pblocks pblock_dynamic_SLR1] -add {CLOCKREGION_X0Y5:CLOCKREGION_X6Y7 CLOCKREGION_X5Y4:CLOCKREGION_X5Y4 CLOCKREGION_X0Y4:CLOCKREGION_X3Y4}
# resize_pblock pblock_dynamic_SLR1 -remove {IOB_X0Y208:IOB_X0Y259}
# resize_pblock pblock_dynamic_SLR1 -remove {IOB_X0Y52:IOB_X0Y103}
# set_property PROHIBIT 1 [get_sites -range SLICE_X220Y300:SLICE_X221Y359]
# 
# set_property SNAPPING_MODE ON [get_pblocks pblock_dynamic_SLR1]
# set_property PARENT pblock_dynamic_region  [get_pblocks pblock_dynamic_SLR1]  -quiet
# 
# 
# add_cells_to_pblock [get_pblocks pblock_dynamic_SLR0] [get_cells level0_i/ulp/SLR0]
# add_cells_to_pblock [get_pblocks pblock_dynamic_SLR0] [get_cells level0_i/ulp/memory_subsystem/inst/memory/plram_mem00] -quiet
# add_cells_to_pblock [get_pblocks pblock_dynamic_SLR0] [get_cells level0_i/ulp/memory_subsystem/inst/memory/plram_mem01] -quiet
# add_cells_to_pblock [get_pblocks pblock_dynamic_SLR0] [get_cells level0_i/ulp/memory_subsystem/inst/memory/plram_mem00_bram] -quiet
# add_cells_to_pblock [get_pblocks pblock_dynamic_SLR0] [get_cells level0_i/ulp/memory_subsystem/inst/memory/plram_mem01_bram] -quiet
# 
# add_cells_to_pblock [get_pblocks pblock_dynamic_SLR1] [get_cells level0_i/ulp/SLR1]
# add_cells_to_pblock [get_pblocks pblock_dynamic_SLR1] [get_cells level0_i/ulp/memory_subsystem/inst/memory/plram_mem02] -quiet
# add_cells_to_pblock [get_pblocks pblock_dynamic_SLR1] [get_cells level0_i/ulp/memory_subsystem/inst/memory/plram_mem03] -quiet
# add_cells_to_pblock [get_pblocks pblock_dynamic_SLR1] [get_cells level0_i/ulp/memory_subsystem/inst/memory/plram_mem02_bram] -quiet
# add_cells_to_pblock [get_pblocks pblock_dynamic_SLR1] [get_cells level0_i/ulp/memory_subsystem/inst/memory/plram_mem03_bram] -quiet


# #######################################################################
# WARNING: WORKAROUND!
# #######################################################################
#
# These constraints are added as a workaround to CR-1038346 
# Remove these constraints when CR is resolved.
#
# Error codes: ERROR: [VPL 30-1112] 
#
# set_property CONTAIN_ROUTING 0 [get_pblocks pblock_dynamic_SLR0]
# set_property EXCLUDE_PLACEMENT 0 [get_pblocks pblock_dynamic_SLR0]
# set_property CONTAIN_ROUTING 0 [get_pblocks pblock_dynamic_SLR1]
# set_property EXCLUDE_PLACEMENT 0 [get_pblocks pblock_dynamic_SLR1]


set_false_path -through  [get_pins -hierarchical -filter {NAME=~level0_i/ulp/*lp_s_irq_cu_00*}]
set_false_path -through  [get_pins -hier -regexp .*mss_0/inst/hbm_inst/inst/.*_STACK.*/AXI_.*_ARESET_N.*]

# Need to Confirm that this BACKBONE constraint is needed in ulp's impl.xdc
set_property CLOCK_DEDICATED_ROUTE BACKBONE [get_nets level0_i/blp/blp_i/freerun_clk_bufg/U0/BUFG_O[0]]

set_property LOC MMCM_X0Y0 [get_cells level0_i/ulp/ulp_ucs/inst/clkwiz_hbm/inst/CLK_CORE_DRP_I/clk_inst/mmcme4_adv_inst]


# Prohibit the use of Logic & DSPs in HBM tap islands in X7Y0 - routing issues can occur if ULP logic is placed here.
# In these islands, All DSP sites & All Slice sites (bar 1) are prohibited. 
# One slice (SLICE_X217Y0) is left available for 4 HBM LUTs which need to be close enough to the HBM_SNGLBLI_INTF_AXI's to meet timing @ 450MHz
set_property PROHIBIT 1 [get_sites -range SLICE_X216Y1:SLICE_X216Y29]
set_property PROHIBIT 1 [get_sites -range SLICE_X217Y0:SLICE_X217Y29]
set_property PROHIBIT 1 [get_sites -range DSP48E2_X30Y0:DSP48E2_X30Y5]
set_property PROHIBIT 1 [get_sites -range SLICE_X229Y1:SLICE_X229Y29]
set_property PROHIBIT 1 [get_sites -range DSP48E2_X31Y0:DSP48E2_X31Y5]
# Locking down the 4 HBM LUTs
set_property LOC SLICE_X216Y0 [get_cells level0_i/ulp/hmss_0/inst/hbm_inst/inst/TWO_STACK.u_hbm_top/TWO_STACK_HBM.hbm_two_stack_intf_i_67] -quiet
set_property LOC SLICE_X216Y0 [get_cells level0_i/ulp/hmss_0/inst/hbm_inst/inst/TWO_STACK.u_hbm_top/TWO_STACK_HBM.hbm_two_stack_intf_i_68] -quiet
set_property LOC SLICE_X229Y0 [get_cells level0_i/ulp/hmss_0/inst/hbm_inst/inst/TWO_STACK.u_hbm_top/TWO_STACK_HBM.hbm_two_stack_intf_i_69] -quiet
set_property LOC SLICE_X229Y0 [get_cells level0_i/ulp/hmss_0/inst/hbm_inst/inst/TWO_STACK.u_hbm_top/TWO_STACK_HBM.hbm_two_stack_intf_i_70] -quiet


