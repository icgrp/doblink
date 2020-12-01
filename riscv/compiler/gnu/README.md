# Patches to GNU RISC-V Toolchain

This directory contains files that need to replace the corresponding files in the source 
code pulled form the [RISC-V toolchain](https://github.com/riscv/riscv-gnu-toolchain).

(At some point in the future we should generate that actual patches properly to make this easier)

Specifically they are
- riscv-binutils/include/opcode/riscv-opc.h (Line 24)
- riscv-binutils/opcodes/riscv-opc.c (Line 202)

(Note these were generated as per instructions [here](https://nitish2112.github.io/post/adding-instruction-riscv/))

You can then compile for newlib targets, with multilib enabled as per the instructions there.

Patched binaries built for Ubuntu 18.04.3 x86_64 can be found as a github release.
This should be extracted and the bin sub-directory placed in your PATH before any other toolchains.