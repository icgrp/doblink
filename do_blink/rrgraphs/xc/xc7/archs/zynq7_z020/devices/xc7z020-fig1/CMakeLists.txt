add_xc_device_define(
  ARCH zynq7_z020
  PART xc7z020clg484-1
  USE_ROI
  DEVICES xc7z020-fig1
)

add_xc_board(
  BOARD pynqz1-fig1
  DEVICE xc7z020-fig1
  PACKAGE test
  PART xc7z020clg400-1
  PROG_CMD "${OPENOCD} -f ${PRJXRAY_DIR}/utils/openocd/board-digilent-pynqz1.cfg -c \\\"init $<SEMICOLON> doblink load 0 \${OUT_BIN} $<SEMICOLON> exit\\\""
)