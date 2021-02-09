


set_property DONT_TOUCH true [get_cells floorplan_static_i/leaf_empty_2/inst]
set_property HD.RECONFIGURABLE true [get_cells floorplan_static_i/leaf_empty_2/inst]
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



create_pblock p_2
add_cells_to_pblock [get_pblocks p_2] [get_cells -quiet [list floorplan_static_i/leaf_empty_2/inst]]
resize_pblock [get_pblocks p_2] -add {SLICE_X86Y0:SLICE_X109Y49}
resize_pblock [get_pblocks p_2] -add {DSP48_X3Y0:DSP48_X4Y19}
resize_pblock [get_pblocks p_2] -add {RAMB18_X4Y0:RAMB18_X5Y19}
resize_pblock [get_pblocks p_2] -add {RAMB36_X4Y0:RAMB36_X5Y9}
set_property SNAPPING_MODE ON [get_pblocks p_2]
create_pblock p_3
add_cells_to_pblock [get_pblocks p_3] [get_cells -quiet [list floorplan_static_i/leaf_empty_3/inst]]
resize_pblock [get_pblocks p_3] -add {SLICE_X34Y0:SLICE_X85Y49}
resize_pblock [get_pblocks p_3] -add {DSP48_X2Y0:DSP48_X2Y19}
resize_pblock [get_pblocks p_3] -add {RAMB18_X3Y0:RAMB18_X3Y19}
resize_pblock [get_pblocks p_3] -add {RAMB36_X3Y0:RAMB36_X3Y9}
set_property SNAPPING_MODE ON [get_pblocks p_3]
create_pblock p_4
add_cells_to_pblock [get_pblocks p_4] [get_cells -quiet [list floorplan_static_i/leaf_empty_4/inst]]
resize_pblock [get_pblocks p_4] -add {SLICE_X0Y0:SLICE_X33Y49}
resize_pblock [get_pblocks p_4] -add {DSP48_X0Y0:DSP48_X1Y19}
resize_pblock [get_pblocks p_4] -add {RAMB18_X0Y0:RAMB18_X2Y19}
resize_pblock [get_pblocks p_4] -add {RAMB36_X0Y0:RAMB36_X2Y9}
set_property SNAPPING_MODE ON [get_pblocks p_4]
create_pblock p_5
add_cells_to_pblock [get_pblocks p_5] [get_cells -quiet [list floorplan_static_i/leaf_empty_5/inst]]
resize_pblock [get_pblocks p_5] -add {SLICE_X86Y100:SLICE_X109Y149}
resize_pblock [get_pblocks p_5] -add {DSP48_X3Y40:DSP48_X4Y59}
resize_pblock [get_pblocks p_5] -add {RAMB18_X4Y40:RAMB18_X5Y59}
resize_pblock [get_pblocks p_5] -add {RAMB36_X4Y20:RAMB36_X5Y29}
set_property SNAPPING_MODE ON [get_pblocks p_5]
create_pblock p_6
add_cells_to_pblock [get_pblocks p_6] [get_cells -quiet [list floorplan_static_i/leaf_empty_6/inst]]
resize_pblock [get_pblocks p_6] -add {SLICE_X26Y100:SLICE_X85Y149}
resize_pblock [get_pblocks p_6] -add {DSP48_X2Y40:DSP48_X2Y59}
resize_pblock [get_pblocks p_6] -add {RAMB18_X2Y40:RAMB18_X3Y59}
resize_pblock [get_pblocks p_6] -add {RAMB36_X2Y20:RAMB36_X3Y29}
set_property SNAPPING_MODE ON [get_pblocks p_6]
create_pblock p_7
add_cells_to_pblock [get_pblocks p_7] [get_cells -quiet [list floorplan_static_i/leaf_empty_7/inst]]
resize_pblock [get_pblocks p_7] -add {SLICE_X86Y50:SLICE_X109Y99}
resize_pblock [get_pblocks p_7] -add {DSP48_X3Y20:DSP48_X4Y39}
resize_pblock [get_pblocks p_7] -add {RAMB18_X4Y20:RAMB18_X5Y39}
resize_pblock [get_pblocks p_7] -add {RAMB36_X4Y10:RAMB36_X5Y19}
set_property SNAPPING_MODE ON [get_pblocks p_7]




