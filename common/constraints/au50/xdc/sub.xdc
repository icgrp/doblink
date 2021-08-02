create_pblock p_2
add_cells_to_pblock [get_pblocks p_2] [get_cells -quiet [list level0_i/ulp/ydma_1/inst/page2_inst]]
resize_pblock [get_pblocks p_2] -add {SLICE_X1Y0:SLICE_X20Y59}
resize_pblock [get_pblocks p_2] -add {DSP48E2_X0Y0:DSP48E2_X1Y17}
resize_pblock [get_pblocks p_2] -add {RAMB18_X0Y0:RAMB18_X1Y23}
resize_pblock [get_pblocks p_2] -add {RAMB36_X0Y0:RAMB36_X1Y11}
set_property SNAPPING_MODE ON [get_pblocks p_2]
set_property IS_SOFT FALSE [get_pblocks p_2]

create_pblock p_3
add_cells_to_pblock [get_pblocks p_3] [get_cells -quiet [list level0_i/ulp/ydma_1/inst/page3_inst]]
resize_pblock [get_pblocks p_3] -add {SLICE_X1Y60:SLICE_X20Y119}
resize_pblock [get_pblocks p_3] -add {DSP48E2_X0Y18:DSP48E2_X1Y41}
resize_pblock [get_pblocks p_3] -add {RAMB18_X0Y24:RAMB18_X1Y47}
resize_pblock [get_pblocks p_3] -add {RAMB36_X0Y12:RAMB36_X1Y23}
set_property SNAPPING_MODE ON [get_pblocks p_3]
set_property IS_SOFT FALSE [get_pblocks p_3]

create_pblock p_4
add_cells_to_pblock [get_pblocks p_4] [get_cells -quiet [list level0_i/ulp/ydma_1/inst/page4_inst]]
resize_pblock [get_pblocks p_4] -add {SLICE_X1Y120:SLICE_X20Y179}
resize_pblock [get_pblocks p_4] -add {DSP48E2_X0Y42:DSP48E2_X1Y65}
resize_pblock [get_pblocks p_4] -add {RAMB18_X0Y48:RAMB18_X1Y71}
resize_pblock [get_pblocks p_4] -add {RAMB36_X0Y24:RAMB36_X1Y35}
set_property SNAPPING_MODE ON [get_pblocks p_4]
set_property IS_SOFT FALSE [get_pblocks p_4]


create_pblock p_5
add_cells_to_pblock [get_pblocks p_5] [get_cells -quiet [list level0_i/ulp/ydma_1/inst/page5_inst]]
resize_pblock [get_pblocks p_5] -add {SLICE_X1Y180:SLICE_X20Y239}
resize_pblock [get_pblocks p_5] -add {DSP48E2_X0Y66:DSP48E2_X1Y89}
resize_pblock [get_pblocks p_5] -add {RAMB18_X0Y72:RAMB18_X1Y95}
resize_pblock [get_pblocks p_5] -add {RAMB36_X0Y36:RAMB36_X1Y47}
set_property SNAPPING_MODE ON [get_pblocks p_5]
set_property IS_SOFT FALSE [get_pblocks p_5]

create_pblock p_6
add_cells_to_pblock [get_pblocks p_6] [get_cells -quiet [list level0_i/ulp/ydma_1/inst/page6_inst]]
resize_pblock [get_pblocks p_6] -add {CLOCKREGION_X1Y3:CLOCKREGION_X1Y3}
set_property SNAPPING_MODE ON [get_pblocks p_6]
set_property IS_SOFT FALSE [get_pblocks p_6]
#
create_pblock p_7
add_cells_to_pblock [get_pblocks p_7] [get_cells -quiet [list level0_i/ulp/ydma_1/inst/page7_inst]]
resize_pblock [get_pblocks p_7] -add {CLOCKREGION_X1Y2:CLOCKREGION_X1Y2}
set_property SNAPPING_MODE ON [get_pblocks p_7]
set_property IS_SOFT FALSE [get_pblocks p_7]

create_pblock p_8
add_cells_to_pblock [get_pblocks p_8] [get_cells -quiet [list level0_i/ulp/ydma_1/inst/page8_inst]]
resize_pblock [get_pblocks p_8] -add {CLOCKREGION_X1Y1:CLOCKREGION_X1Y1}
set_property SNAPPING_MODE ON [get_pblocks p_8]
set_property IS_SOFT FALSE [get_pblocks p_8]

create_pblock p_9
add_cells_to_pblock [get_pblocks p_9] [get_cells -quiet [list level0_i/ulp/ydma_1/inst/page9_inst]]
resize_pblock [get_pblocks p_9] -add {SLICE_X71Y60:SLICE_X94Y119}
resize_pblock [get_pblocks p_9] -add {DSP48E2_X9Y18:DSP48E2_X12Y41}
resize_pblock [get_pblocks p_9] -add {RAMB18_X5Y24:RAMB18_X6Y47}
resize_pblock [get_pblocks p_9] -add {RAMB36_X5Y12:RAMB36_X6Y23}
set_property SNAPPING_MODE ON [get_pblocks p_9]
set_property IS_SOFT FALSE [get_pblocks p_9]

create_pblock p_10
add_cells_to_pblock [get_pblocks p_10] [get_cells -quiet [list level0_i/ulp/ydma_1/inst/page10_inst]]
resize_pblock [get_pblocks p_10] -add {SLICE_X71Y120:SLICE_X94Y179}
resize_pblock [get_pblocks p_10] -add {DSP48E2_X9Y42:DSP48E2_X12Y65}
resize_pblock [get_pblocks p_10] -add {RAMB18_X5Y48:RAMB18_X6Y71}
resize_pblock [get_pblocks p_10] -add {RAMB36_X5Y24:RAMB36_X6Y35}
set_property SNAPPING_MODE ON [get_pblocks p_10]
set_property IS_SOFT FALSE [get_pblocks p_10]

create_pblock p_11
add_cells_to_pblock [get_pblocks p_11] [get_cells -quiet [list level0_i/ulp/ydma_1/inst/page11_inst]]
resize_pblock [get_pblocks p_11] -add {SLICE_X71Y180:SLICE_X94Y239}
resize_pblock [get_pblocks p_11] -add {DSP48E2_X9Y66:DSP48E2_X12Y89}
resize_pblock [get_pblocks p_11] -add {RAMB18_X5Y72:RAMB18_X6Y95}
resize_pblock [get_pblocks p_11] -add {RAMB36_X5Y36:RAMB36_X6Y47}
set_property SNAPPING_MODE ON [get_pblocks p_11]
set_property IS_SOFT FALSE [get_pblocks p_11]

create_pblock p_12
add_cells_to_pblock [get_pblocks p_12] [get_cells -quiet [list level0_i/ulp/ydma_1/inst/page12_inst]]
resize_pblock [get_pblocks p_12] -add {SLICE_X118Y180:SLICE_X144Y239}
resize_pblock [get_pblocks p_12] -add {DSP48E2_X16Y66:DSP48E2_X18Y89}
resize_pblock [get_pblocks p_12] -add {RAMB18_X8Y72:RAMB18_X9Y95}
resize_pblock [get_pblocks p_12] -add {RAMB36_X8Y36:RAMB36_X9Y47}
resize_pblock [get_pblocks p_12] -add {URAM288_X2Y48:URAM288_X2Y63}
set_property SNAPPING_MODE ON [get_pblocks p_12]
set_property IS_SOFT FALSE [get_pblocks p_12]


create_pblock p_13
add_cells_to_pblock [get_pblocks p_13] [get_cells -quiet [list level0_i/ulp/ydma_1/inst/page13_inst]]
resize_pblock [get_pblocks p_13] -add {SLICE_X118Y60:SLICE_X144Y119}
resize_pblock [get_pblocks p_13] -add {DSP48E2_X16Y18:DSP48E2_X18Y41}
resize_pblock [get_pblocks p_13] -add {RAMB18_X8Y24:RAMB18_X9Y47}
resize_pblock [get_pblocks p_13] -add {RAMB36_X8Y12:RAMB36_X9Y23}
resize_pblock [get_pblocks p_13] -add {URAM288_X2Y16:URAM288_X2Y31}
set_property SNAPPING_MODE ON [get_pblocks p_13]
set_property IS_SOFT FALSE [get_pblocks p_13]

create_pblock p_14
add_cells_to_pblock [get_pblocks p_14] [get_cells -quiet [list level0_i/ulp/ydma_1/inst/page14_inst]]
resize_pblock [get_pblocks p_14] -add {SLICE_X118Y120:SLICE_X144Y179}
resize_pblock [get_pblocks p_14] -add {DSP48E2_X16Y42:DSP48E2_X18Y65}
resize_pblock [get_pblocks p_14] -add {RAMB18_X8Y48:RAMB18_X9Y71}
resize_pblock [get_pblocks p_14] -add {RAMB36_X8Y24:RAMB36_X9Y35}
resize_pblock [get_pblocks p_14] -add {URAM288_X2Y32:URAM288_X2Y47}
set_property SNAPPING_MODE ON [get_pblocks p_14]
set_property IS_SOFT FALSE [get_pblocks p_14]

create_pblock p_15
add_cells_to_pblock [get_pblocks p_15] [get_cells -quiet [list level0_i/ulp/ydma_1/inst/page15_inst]]
resize_pblock [get_pblocks p_15] -add {SLICE_X118Y300:SLICE_X144Y359}
resize_pblock [get_pblocks p_15] -add {DSP48E2_X16Y114:DSP48E2_X18Y137}
resize_pblock [get_pblocks p_15] -add {RAMB18_X8Y120:RAMB18_X9Y143}
resize_pblock [get_pblocks p_15] -add {RAMB36_X8Y60:RAMB36_X9Y71}
resize_pblock [get_pblocks p_15] -add {URAM288_X2Y80:URAM288_X2Y95}
set_property SNAPPING_MODE ON [get_pblocks p_15]
set_property IS_SOFT FALSE [get_pblocks p_15]

create_pblock p_16
add_cells_to_pblock [get_pblocks p_16] [get_cells -quiet [list level0_i/ulp/ydma_1/inst/page16_inst]]
resize_pblock [get_pblocks p_16] -add {SLICE_X118Y360:SLICE_X144Y419}
resize_pblock [get_pblocks p_16] -add {DSP48E2_X16Y138:DSP48E2_X18Y161}
resize_pblock [get_pblocks p_16] -add {RAMB18_X8Y144:RAMB18_X9Y167}
resize_pblock [get_pblocks p_16] -add {RAMB36_X8Y72:RAMB36_X9Y83}
resize_pblock [get_pblocks p_16] -add {URAM288_X2Y96:URAM288_X2Y111}
set_property SNAPPING_MODE ON [get_pblocks p_16]
set_property IS_SOFT FALSE [get_pblocks p_16]

create_pblock p_17
add_cells_to_pblock [get_pblocks p_17] [get_cells -quiet [list level0_i/ulp/ydma_1/inst/page17_inst]]
resize_pblock [get_pblocks p_17] -add {SLICE_X118Y420:SLICE_X144Y479}
resize_pblock [get_pblocks p_17] -add {DSP48E2_X16Y162:DSP48E2_X18Y185}
resize_pblock [get_pblocks p_17] -add {RAMB18_X8Y168:RAMB18_X9Y191}
resize_pblock [get_pblocks p_17] -add {RAMB36_X8Y84:RAMB36_X9Y95}
resize_pblock [get_pblocks p_17] -add {URAM288_X2Y112:URAM288_X2Y127}
set_property SNAPPING_MODE ON [get_pblocks p_17]
set_property IS_SOFT FALSE [get_pblocks p_17]

create_pblock p_18
add_cells_to_pblock [get_pblocks p_18] [get_cells -quiet [list level0_i/ulp/ydma_1/inst/page18_inst]]
resize_pblock [get_pblocks p_18] -add {SLICE_X71Y420:SLICE_X94Y479}
resize_pblock [get_pblocks p_18] -add {DSP48E2_X9Y162:DSP48E2_X12Y185}
resize_pblock [get_pblocks p_18] -add {RAMB18_X5Y168:RAMB18_X6Y191}
resize_pblock [get_pblocks p_18] -add {RAMB36_X5Y84:RAMB36_X6Y95}
set_property SNAPPING_MODE ON [get_pblocks p_18]
set_property IS_SOFT FALSE [get_pblocks p_18]

create_pblock p_19
add_cells_to_pblock [get_pblocks p_19] [get_cells -quiet [list level0_i/ulp/ydma_1/inst/page19_inst]]
resize_pblock [get_pblocks p_19] -add {SLICE_X71Y360:SLICE_X94Y419}
resize_pblock [get_pblocks p_19] -add {DSP48E2_X9Y138:DSP48E2_X12Y161}
resize_pblock [get_pblocks p_19] -add {RAMB18_X5Y144:RAMB18_X6Y167}
resize_pblock [get_pblocks p_19] -add {RAMB36_X5Y72:RAMB36_X6Y83}
set_property SNAPPING_MODE ON [get_pblocks p_19]
set_property IS_SOFT FALSE [get_pblocks p_19]

create_pblock p_20
add_cells_to_pblock [get_pblocks p_20] [get_cells -quiet [list level0_i/ulp/ydma_1/inst/page20_inst]]
resize_pblock [get_pblocks p_20] -add {SLICE_X71Y300:SLICE_X94Y359}
resize_pblock [get_pblocks p_20] -add {DSP48E2_X9Y114:DSP48E2_X12Y137}
resize_pblock [get_pblocks p_20] -add {RAMB18_X5Y120:RAMB18_X6Y143}
resize_pblock [get_pblocks p_20] -add {RAMB36_X5Y60:RAMB36_X6Y71}
set_property SNAPPING_MODE ON [get_pblocks p_20]
set_property IS_SOFT FALSE [get_pblocks p_20]

create_pblock p_21
add_cells_to_pblock [get_pblocks p_21] [get_cells -quiet [list level0_i/ulp/ydma_1/inst/page21_inst]]
resize_pblock [get_pblocks p_21] -add {CLOCKREGION_X1Y5:CLOCKREGION_X1Y5}
set_property SNAPPING_MODE ON [get_pblocks p_21]
set_property IS_SOFT FALSE [get_pblocks p_21]

create_pblock p_22
add_cells_to_pblock [get_pblocks p_22] [get_cells -quiet [list level0_i/ulp/ydma_1/inst/page22_inst]]
resize_pblock [get_pblocks p_22] -add {CLOCKREGION_X1Y6:CLOCKREGION_X1Y6}
set_property SNAPPING_MODE ON [get_pblocks p_22]
set_property IS_SOFT FALSE [get_pblocks p_22]

create_pblock p_23
add_cells_to_pblock [get_pblocks p_23] [get_cells -quiet [list level0_i/ulp/ydma_1/inst/page23_inst]]
resize_pblock [get_pblocks p_23] -add {CLOCKREGION_X1Y7:CLOCKREGION_X1Y7}
set_property SNAPPING_MODE ON [get_pblocks p_23]
set_property IS_SOFT FALSE [get_pblocks p_23]

create_pblock p_24
add_cells_to_pblock [get_pblocks p_24] [get_cells -quiet [list level0_i/ulp/ydma_1/inst/page24_inst]]
resize_pblock [get_pblocks p_24] -add {SLICE_X1Y420:SLICE_X20Y479}
resize_pblock [get_pblocks p_24] -add {DSP48E2_X0Y162:DSP48E2_X1Y185}
resize_pblock [get_pblocks p_24] -add {RAMB18_X0Y168:RAMB18_X1Y191}
resize_pblock [get_pblocks p_24] -add {RAMB36_X0Y84:RAMB36_X1Y95}
set_property SNAPPING_MODE ON [get_pblocks p_24]
set_property IS_SOFT FALSE [get_pblocks p_24]

create_pblock p_25
add_cells_to_pblock [get_pblocks p_25] [get_cells -quiet [list level0_i/ulp/ydma_1/inst/page25_inst]]
resize_pblock [get_pblocks p_25] -add {SLICE_X1Y360:SLICE_X20Y419}
resize_pblock [get_pblocks p_25] -add {DSP48E2_X0Y138:DSP48E2_X1Y161}
resize_pblock [get_pblocks p_25] -add {RAMB18_X0Y144:RAMB18_X1Y167}
resize_pblock [get_pblocks p_25] -add {RAMB36_X0Y72:RAMB36_X1Y83}
set_property SNAPPING_MODE ON [get_pblocks p_25]
set_property IS_SOFT FALSE [get_pblocks p_25]

create_pblock p_26
add_cells_to_pblock [get_pblocks p_26] [get_cells -quiet [list level0_i/ulp/ydma_1/inst/page26_inst]]
resize_pblock [get_pblocks p_26] -add {SLICE_X1Y300:SLICE_X20Y359}
resize_pblock [get_pblocks p_26] -add {DSP48E2_X0Y114:DSP48E2_X1Y137}
resize_pblock [get_pblocks p_26] -add {RAMB18_X0Y120:RAMB18_X1Y143}
resize_pblock [get_pblocks p_26] -add {RAMB36_X0Y60:RAMB36_X1Y71}
set_property SNAPPING_MODE ON [get_pblocks p_26]
set_property IS_SOFT FALSE [get_pblocks p_26]

create_pblock p_27
add_cells_to_pblock [get_pblocks p_27] [get_cells -quiet [list level0_i/ulp/ydma_1/inst/page27_inst]]
resize_pblock [get_pblocks p_27] -add {SLICE_X1Y240:SLICE_X20Y299}
resize_pblock [get_pblocks p_27] -add {DSP48E2_X0Y90:DSP48E2_X1Y113}
resize_pblock [get_pblocks p_27] -add {RAMB18_X0Y96:RAMB18_X1Y119}
resize_pblock [get_pblocks p_27] -add {RAMB36_X0Y48:RAMB36_X1Y59}
set_property SNAPPING_MODE ON [get_pblocks p_27]
set_property IS_SOFT FALSE [get_pblocks p_27]




















