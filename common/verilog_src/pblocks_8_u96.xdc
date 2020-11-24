

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
set_property DONT_TOUCH true [get_cells floorplan_static_i/bft]
set_property HD.RECONFIGURABLE true [get_cells floorplan_static_i/bft]


create_pblock p_7
add_cells_to_pblock [get_pblocks p_7] [get_cells -quiet [list floorplan_static_i/leaf_empty_7/inst]]
resize_pblock [get_pblocks p_7] -add {SLICE_X0Y120:SLICE_X15Y179}
resize_pblock [get_pblocks p_7] -add {DSP48E2_X0Y48:DSP48E2_X0Y71}
resize_pblock [get_pblocks p_7] -add {RAMB18_X0Y48:RAMB18_X1Y71}
resize_pblock [get_pblocks p_7] -add {RAMB36_X0Y24:RAMB36_X1Y35}
set_property SNAPPING_MODE ON [get_pblocks p_7]

create_pblock p_6
add_cells_to_pblock [get_pblocks p_6] [get_cells -quiet [list floorplan_static_i/leaf_empty_6/inst]]
resize_pblock [get_pblocks p_6] -add {SLICE_X16Y120:SLICE_X28Y179}
resize_pblock [get_pblocks p_6] -add {DSP48E2_X1Y48:DSP48E2_X2Y71}
resize_pblock [get_pblocks p_6] -add {RAMB18_X2Y48:RAMB18_X2Y71}
resize_pblock [get_pblocks p_6] -add {RAMB36_X2Y24:RAMB36_X2Y35}
set_property SNAPPING_MODE ON [get_pblocks p_6]

create_pblock p_5
add_cells_to_pblock [get_pblocks p_5] [get_cells -quiet [list floorplan_static_i/leaf_empty_5/inst]]
resize_pblock [get_pblocks p_5] -add {SLICE_X29Y60:SLICE_X37Y119}
resize_pblock [get_pblocks p_5] -add {RAMB18_X3Y24:RAMB18_X4Y47}
resize_pblock [get_pblocks p_5] -add {RAMB36_X3Y12:RAMB36_X4Y23}
set_property SNAPPING_MODE ON [get_pblocks p_5]

create_pblock p_4
add_cells_to_pblock [get_pblocks p_4] [get_cells -quiet [list floorplan_static_i/leaf_empty_4/inst]]
resize_pblock [get_pblocks p_4] -add {SLICE_X29Y120:SLICE_X47Y179}
resize_pblock [get_pblocks p_4] -add {DSP48E2_X3Y48:DSP48E2_X4Y71}
resize_pblock [get_pblocks p_4] -add {RAMB18_X3Y48:RAMB18_X5Y71}
resize_pblock [get_pblocks p_4] -add {RAMB36_X3Y24:RAMB36_X5Y35}
set_property SNAPPING_MODE ON [get_pblocks p_4]

create_pblock p_3
add_cells_to_pblock [get_pblocks p_3] [get_cells -quiet [list floorplan_static_i/leaf_empty_3/inst]]
resize_pblock [get_pblocks p_3] -add {SLICE_X38Y60:SLICE_X47Y119}
resize_pblock [get_pblocks p_3] -add {DSP48E2_X3Y24:DSP48E2_X4Y47}
resize_pblock [get_pblocks p_3] -add {RAMB18_X5Y24:RAMB18_X5Y47}
resize_pblock [get_pblocks p_3] -add {RAMB36_X5Y12:RAMB36_X5Y23}
set_property SNAPPING_MODE ON [get_pblocks p_3]

create_pblock p_2
add_cells_to_pblock [get_pblocks p_2] [get_cells -quiet [list floorplan_static_i/leaf_empty_2/inst]]
resize_pblock [get_pblocks p_2] -add {SLICE_X29Y0:SLICE_X47Y59}
resize_pblock [get_pblocks p_2] -add {DSP48E2_X3Y0:DSP48E2_X4Y23}
resize_pblock [get_pblocks p_2] -add {RAMB18_X3Y0:RAMB18_X5Y23}
resize_pblock [get_pblocks p_2] -add {RAMB36_X3Y0:RAMB36_X5Y11}

create_pblock bft
add_cells_to_pblock [get_pblocks bft] [get_cells -quiet [list floorplan_static_i/bft]]
resize_pblock [get_pblocks bft] -add {CLOCKREGION_X0Y0:CLOCKREGION_X0Y1}
set_property SNAPPING_MODE ON [get_pblocks bft]
