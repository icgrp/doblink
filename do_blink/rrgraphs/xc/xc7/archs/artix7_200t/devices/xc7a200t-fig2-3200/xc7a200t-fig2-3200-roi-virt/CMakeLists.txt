if(NOT (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/definition.json"))
  gen_def_json_vivado(
    DCP ${doblink_SOURCE_DIR}/do_blink/vivado_benchmark/fig2_at200/F001_static_8_at200_3200/big_static_routed_8_48.dcp
    USE_VIVADO_PPLOCS 1
  )
  set(DEF_DIR ${CMAKE_CURRENT_BINARY_DIR})
else()
  set(DEF_DIR ${CMAKE_CURRENT_SOURCE_DIR})
endif()

add_xc_device_design_json(
  ARCH artix7_200t
  DEVICE xc7a200t-fig2-3200
  DEF_DIR ${DEF_DIR}
)

add_xc_device_define_type(
  ARCH artix7_200t
  DEVICE xc7a200t-fig2-3200
  ROI_DIR ${doblink_BINARY_DIR}/do_blink/rrgraphs/xc/xc7/archs/artix7_200t/devices/xc7a200t-fig2-3200/xc7a200t-fig2-3200-roi-virt
  TILE_XML_DIR ${symbiflow-arch-defs_BINARY_DIR}/xc/xc7/archs/artix7_200t/tiles
  TILE_TYPES
    CLBLL_L
    CLBLL_R
    CLBLM_L
    CLBLM_R
    BRAM_L
    BRAM_R
  PB_TYPES
    SLICEL
    SLICEM
    BRAM_L
    BRAM_R
)

set_target_properties(
  xc7a200t-fig2-3200-roi-virt
  PROPERTIES
    TOP_PCF
    ${CMAKE_CURRENT_SOURCE_DIR}/top.pcf
)

