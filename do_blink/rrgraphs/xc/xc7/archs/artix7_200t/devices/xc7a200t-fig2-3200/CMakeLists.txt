add_xc_device_define(
  ARCH artix7_200t
  PART xc7a200tffg1156-1
  USE_ROI
  DEVICES xc7a200t-fig2-3200
)

add_xc_board(
  BOARD nexys_video-fig2-3200
  DEVICE xc7a200t-fig2-3200
  PACKAGE test
  PART xc7a200tffg1156-1
  PROG_CMD "${OPENOCD} -f board/digilent_nexys_video.cfg -c \\\"init $<SEMICOLON> doblink load 0 \${OUT_BIN} $<SEMICOLON> exit\\\""
)
