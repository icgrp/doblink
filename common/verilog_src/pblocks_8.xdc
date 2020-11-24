
set_property DONT_TOUCH true [get_cells floorplan_static_i/bft_dma]
set_property HD.RECONFIGURABLE true [get_cells floorplan_static_i/bft_dma]

create_pblock p_bft
add_cells_to_pblock [get_pblocks p_bft] [get_cells -quiet [list floorplan_static_i/bft_dma]]
resize_pblock [get_pblocks p_bft] -add {CLOCKREGION_X1Y4:CLOCKREGION_X1Y5 CLOCKREGION_X0Y3:CLOCKREGION_X1Y3 CLOCKREGION_X1Y2:CLOCKREGION_X1Y2 CLOCKREGION_X1Y1:CLOCKREGION_X3Y1 CLOCKREGION_X1Y0:CLOCKREGION_X1Y0}
set_property SNAPPING_MODE ON [get_pblocks p_bft]



create_pblock p_2
add_cells_to_pblock [get_pblocks p_2] [get_cells -quiet [list floorplan_static_i/leaf_empty_2/inst]]
resize_pblock [get_pblocks p_2] -add {SLICE_X57Y120:SLICE_X96Y357}
resize_pblock [get_pblocks p_2] -add {CFGIO_SITE_X0Y0:CFGIO_SITE_X0Y0}
resize_pblock [get_pblocks p_2] -add {DSP48E2_X12Y48:DSP48E2_X17Y141}
resize_pblock [get_pblocks p_2] -add {IOB_X0Y156:IOB_X0Y243}
resize_pblock [get_pblocks p_2] -add {RAMB18_X7Y48:RAMB18_X12Y141}
resize_pblock [get_pblocks p_2] -add {RAMB36_X7Y24:RAMB36_X12Y70}
resize_pblock [get_pblocks p_2] -add {SYSMONE4_X0Y0:SYSMONE4_X0Y0}

create_pblock p_3
add_cells_to_pblock [get_pblocks p_3] [get_cells -quiet [list floorplan_static_i/leaf_empty_3/inst]]
resize_pblock [get_pblocks p_3] -add {SLICE_X56Y362:SLICE_X96Y419}
resize_pblock [get_pblocks p_3] -add {DSP48E2_X12Y146:DSP48E2_X17Y167}
resize_pblock [get_pblocks p_3] -add {IOB_X0Y268:IOB_X0Y279}
resize_pblock [get_pblocks p_3] -add {RAMB18_X7Y146:RAMB18_X12Y167}
resize_pblock [get_pblocks p_3] -add {RAMB36_X7Y73:RAMB36_X12Y83}


create_pblock p_4
add_cells_to_pblock [get_pblocks p_4] [get_cells -quiet [list floorplan_static_i/leaf_empty_4/inst]]
resize_pblock [get_pblocks p_4] -add {SLICE_X29Y365:SLICE_X55Y419}
resize_pblock [get_pblocks p_4] -add {DSP48E2_X6Y146:DSP48E2_X11Y167}
resize_pblock [get_pblocks p_4] -add {RAMB18_X4Y146:RAMB18_X6Y167}
resize_pblock [get_pblocks p_4] -add {RAMB36_X4Y73:RAMB36_X6Y83}

create_pblock p_5
add_cells_to_pblock [get_pblocks p_5] [get_cells -quiet [list floorplan_static_i/leaf_empty_5/inst]]
resize_pblock [get_pblocks p_5] -add {SLICE_X1Y365:SLICE_X28Y419}
resize_pblock [get_pblocks p_5] -add {DSP48E2_X0Y146:DSP48E2_X5Y167}
resize_pblock [get_pblocks p_5] -add {RAMB18_X0Y146:RAMB18_X3Y167}
resize_pblock [get_pblocks p_5] -add {RAMB36_X0Y73:RAMB36_X3Y83}


create_pblock p_6
add_cells_to_pblock [get_pblocks p_6] [get_cells -quiet [list floorplan_static_i/leaf_empty_6/inst]]
resize_pblock [get_pblocks p_6] -add {SLICE_X1Y303:SLICE_X28Y359}
resize_pblock [get_pblocks p_6] -add {DSP48E2_X0Y122:DSP48E2_X5Y143}
resize_pblock [get_pblocks p_6] -add {RAMB18_X0Y122:RAMB18_X3Y143}
resize_pblock [get_pblocks p_6] -add {RAMB36_X0Y61:RAMB36_X3Y71}


create_pblock p_7
add_cells_to_pblock [get_pblocks p_7] [get_cells -quiet [list floorplan_static_i/leaf_empty_7/inst]]
resize_pblock [get_pblocks p_7] -add {SLICE_X1Y245:SLICE_X28Y299}
resize_pblock [get_pblocks p_7] -add {DSP48E2_X0Y98:DSP48E2_X5Y119}
resize_pblock [get_pblocks p_7] -add {RAMB18_X0Y98:RAMB18_X3Y119}
resize_pblock [get_pblocks p_7] -add {RAMB36_X0Y49:RAMB36_X3Y59}



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

current_instance -quiet

