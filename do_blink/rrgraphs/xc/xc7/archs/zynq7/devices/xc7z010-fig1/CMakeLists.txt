add_xc_device_define(
  ARCH zynq7
  PART xc7z010clg400-1
  USE_ROI
  DEVICES xc7z010-fig1
)

add_xc_board(
  BOARD zybo-fig1
  DEVICE xc7z010-fig1
  PACKAGE test
  PART xc7z010clg400-1
  PROG_CMD "${OPENOCD} -f ${PRJXRAY_DIR}/utils/openocd/board-digilent-pynqz1.cfg -c \\\"init $<SEMICOLON> doblink load 0 \${OUT_BIN} $<SEMICOLON> exit\\\""
)
