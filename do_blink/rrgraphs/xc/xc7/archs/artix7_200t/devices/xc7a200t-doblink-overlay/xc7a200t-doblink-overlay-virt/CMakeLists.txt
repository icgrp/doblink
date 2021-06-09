add_xc_device_define_type(
  ARCH artix7_200t
  DEVICE xc7a200t-doblink-overlay
  OVERLAY_DIR ${doblink_SOURCE_DIR}/do_blink/rrgraphs/xc/xc7/archs/artix7_200t/devices/xc7a200t-doblink-overlay/xc7a200t-doblink-overlay-virt
  TILE_XML_DIR ${symbiflow-arch-defs_BINARY_DIR}/xc/xc7/archs/artix7_200t/tiles
  TILE_TYPES
    CLBLL_L
    CLBLL_R
    CLBLM_L
    CLBLM_R
    BRAM_R
    BRAM_L
    LIOPAD_M
    LIOPAD_S
    LIOPAD_SING
    RIOPAD_M
    RIOPAD_S
    RIOPAD_SING
    CLK_BUFG_BOT_R
    CLK_BUFG_TOP_R
    CMT_TOP_L_UPPER_T
    CMT_TOP_R_UPPER_T
    HCLK_IOI3
  PB_TYPES
    SLICEL
    SLICEM
    BRAM_L
    IOPAD
    IOPAD_M
    IOPAD_S
    BUFGCTRL
    PLLE2_ADV
    HCLK_IOI3
)
