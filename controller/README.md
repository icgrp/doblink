# RVPLD SoC

### Required Software

- LiteX: Follow guide for install at https://github.com/enjoy-digital/litex
- Vivado: Using Vivado for now, will switch to symbiflow eventually
- OpenOCD: Install using package manager

### Environment Variable

- SOC_DIR should be the soc directory in litex repo (e.g. ./litex/litex/soc)
- RVPLD_VIVADO should be the settings64.sh for your vivado installation

### Random Notes

- Explanation of LiteX CSRs: https://github.com/enjoy-digital/litex/wiki/CSR-Bus
- Verilog Wrapper Example: https://github.com/im-tomu/foboot/blob/985de5bde8056ce49bfdbcf1e01daf73a0b98e9b/hw/foboot-bitstream.py#L408
- Example dma mm2s: https://github.com/enjoy-digital/litex/blob/master/litex/soc/integration/soc.py#L1411
- Potential symbiflow 200t tarball: https://console.cloud.google.com/storage/browser/_details/symbiflow-arch-defs/artifacts/prod/foss-fpga-tools/symbiflow-arch-defs/continuous/install-200t/23/20201020-195721/symbiflow-arch-defs-install-200t-2f55fb8f.tar.xz
