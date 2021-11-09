add_xc_device_define(
  ARCH artix7
  PART xc7a200tsbg484-1
  USE_OVERLAY
  DEVICES xc7a200t-doblink-12-overlay
)

add_xc_board(
  BOARD nexys_video-doblink-12-overlay
  DEVICE xc7a200t-doblink-12-overlay
  PACKAGE test
  PART xc7a200tsbg484-1
  PROG_CMD "${OPENOCD} -f board/digilent_nexys_video.cfg -c \\\"init $<SEMICOLON> doblink load 0 \${OUT_BIN} $<SEMICOLON> exit\\\""
)
