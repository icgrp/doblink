add_xc_device_define(
  ARCH artix7_200t
  PART xc7a200tsbg484-1
  USE_ROI
  DEVICES xc7a200t-doblink-pblock-7
)

add_xc_board(
  BOARD nexys_video-doblink-pblock-7
  DEVICE xc7a200t-doblink-pblock-7
  PACKAGE test
  PART xc7a200tsbg484-1
  PROG_CMD "${OPENOCD} -f board/digilent_nexys_video.cfg -c \\\"init $<SEMICOLON> doblink load 0 \${OUT_BIN} $<SEMICOLON> exit\\\""
)
