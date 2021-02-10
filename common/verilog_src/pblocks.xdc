
#set_property DONT_TOUCH true [get_cells floorplan_static_i/bft_dma]
#set_property HD.RECONFIGURABLE true [get_cells floorplan_static_i/bft_dma]


set_property DONT_TOUCH true [get_cells floorplan_static_i/leaf_empty_8/inst]
set_property HD.RECONFIGURABLE true [get_cells floorplan_static_i/leaf_empty_8/inst]
set_property DONT_TOUCH true [get_cells floorplan_static_i/leaf_empty_3/inst]
set_property HD.RECONFIGURABLE true [get_cells floorplan_static_i/leaf_empty_3/inst]
set_property DONT_TOUCH true [get_cells floorplan_static_i/leaf_empty_4/inst]
set_property HD.RECONFIGURABLE true [get_cells floorplan_static_i/leaf_empty_4/inst]
set_property DONT_TOUCH true [get_cells floorplan_static_i/leaf_empty_5/inst]
set_property HD.RECONFIGURABLE true [get_cells floorplan_static_i/leaf_empty_5/inst]
set_property DONT_TOUCH true [get_cells floorplan_static_i/leaf_empty_6/inst]
set_property HD.RECONFIGURABLE true [get_cells floorplan_static_i/leaf_empty_6/inst]
set_property DONT_TOUCH true [get_cells floorplan_static_i/leaf_empty_7/inst]
set_property HD.RECONFIGURABLE true [get_cells floorplan_static_i/leaf_empty_7/inst]

#current_instance -quiet


create_pblock p_3
add_cells_to_pblock [get_pblocks p_3] [get_cells -quiet [list floorplan_static_i/leaf_empty_3/inst]]
resize_pblock [get_pblocks p_3] -add {SLICE_X29Y0:SLICE_X47Y59}
resize_pblock [get_pblocks p_3] -add {DSP48E2_X3Y0:DSP48E2_X4Y23}
resize_pblock [get_pblocks p_3] -add {IOB_X1Y0:IOB_X1Y37}
resize_pblock [get_pblocks p_3] -add {RAMB18_X3Y0:RAMB18_X5Y23}
resize_pblock [get_pblocks p_3] -add {RAMB36_X3Y0:RAMB36_X5Y11}
set_property SNAPPING_MODE ON [get_pblocks p_3]
create_pblock p_4
add_cells_to_pblock [get_pblocks p_4] [get_cells -quiet [list floorplan_static_i/leaf_empty_4/inst]]
resize_pblock [get_pblocks p_4] -add {SLICE_X29Y60:SLICE_X38Y119}
resize_pblock [get_pblocks p_4] -add {CONFIG_SITE_X0Y0:CONFIG_SITE_X0Y0}
resize_pblock [get_pblocks p_4] -add {RAMB18_X3Y24:RAMB18_X4Y47}
resize_pblock [get_pblocks p_4] -add {RAMB36_X3Y12:RAMB36_X4Y23}
set_property SNAPPING_MODE ON [get_pblocks p_4]
create_pblock p_5
add_cells_to_pblock [get_pblocks p_5] [get_cells -quiet [list floorplan_static_i/leaf_empty_5/inst]]
resize_pblock [get_pblocks p_5] -add {SLICE_X39Y60:SLICE_X47Y179}
resize_pblock [get_pblocks p_5] -add {DSP48E2_X3Y24:DSP48E2_X4Y71}
resize_pblock [get_pblocks p_5] -add {RAMB18_X5Y24:RAMB18_X5Y71}
resize_pblock [get_pblocks p_5] -add {RAMB36_X5Y12:RAMB36_X5Y35}
set_property SNAPPING_MODE ON [get_pblocks p_5]
create_pblock p_6
add_cells_to_pblock [get_pblocks p_6] [get_cells -quiet [list floorplan_static_i/leaf_empty_6/inst]]
resize_pblock [get_pblocks p_6] -add {SLICE_X29Y120:SLICE_X38Y179}
resize_pblock [get_pblocks p_6] -add {CFGIO_SITE_X0Y0:CFGIO_SITE_X0Y0}
resize_pblock [get_pblocks p_6] -add {RAMB18_X3Y48:RAMB18_X4Y71}
resize_pblock [get_pblocks p_6] -add {RAMB36_X3Y24:RAMB36_X4Y35}
resize_pblock [get_pblocks p_6] -add {SYSMONE4_X0Y0:SYSMONE4_X0Y0}
set_property SNAPPING_MODE ON [get_pblocks p_6]
create_pblock p_7
add_cells_to_pblock [get_pblocks p_7] [get_cells -quiet [list floorplan_static_i/leaf_empty_7/inst]]
resize_pblock [get_pblocks p_7] -add {SLICE_X9Y60:SLICE_X23Y119}
resize_pblock [get_pblocks p_7] -add {DSP48E2_X1Y24:DSP48E2_X1Y47}
resize_pblock [get_pblocks p_7] -add {IOB_X0Y52:IOB_X0Y89}
resize_pblock [get_pblocks p_7] -add {RAMB18_X1Y24:RAMB18_X2Y47}
resize_pblock [get_pblocks p_7] -add {RAMB36_X1Y12:RAMB36_X2Y23}
set_property SNAPPING_MODE ON [get_pblocks p_7]
create_pblock p_8
add_cells_to_pblock [get_pblocks p_8] [get_cells -quiet [list floorplan_static_i/leaf_empty_8/inst]]
resize_pblock [get_pblocks p_8] -add {SLICE_X9Y120:SLICE_X28Y179}
resize_pblock [get_pblocks p_8] -add {DSP48E2_X1Y48:DSP48E2_X2Y71}
resize_pblock [get_pblocks p_8] -add {IOB_X0Y104:IOB_X0Y141}
resize_pblock [get_pblocks p_8] -add {RAMB18_X1Y48:RAMB18_X2Y71}
resize_pblock [get_pblocks p_8] -add {RAMB36_X1Y24:RAMB36_X2Y35}
set_property SNAPPING_MODE ON [get_pblocks p_8]

