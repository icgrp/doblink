#!/bin/bash -e
operator=data_redir_m
RISCV_GNU_TOOLCHAIN_INSTALL_PREFIX=/opt/riscv32
SHELL=bash
PYTHON=python3
#MEM_SIZE = 262144
MEM_SIZE=4096
FIRMWARE_OBJS='start.o print.o stream.o main.o '${operator}'.o' 
GCC_WARNS='-Wall -Wextra -Wshadow -Wundef -Wpointer-arith -Wcast-qual -Wcast-align -Wwrite-strings'
GCC_WARNS+=' -Wredundant-decls -pedantic'
TOOLCHAIN_PREFIX=${RISCV_GNU_TOOLCHAIN_INSTALL_PREFIX}i/bin/riscv32-unknown-elf-
#COMPRESSED_ISA=C
COMPRESSED_ISA= 
IDIR='-fno-threadsafe-statics -lstdc++' 

echo ${GCC_WARNS} 
${TOOLCHAIN_PREFIX}g++ -c -march=rv32im -o start.o start.S
${TOOLCHAIN_PREFIX}g++ -c -march=rv32i -Os ${GCC_WARNS} -ffreestanding ${IDIR} -o data_redir_m.o data_redir_m.cpp
${TOOLCHAIN_PREFIX}g++ -c -march=rv32i -Os ${GCC_WARNS} -ffreestanding -nostdlib -o main.o main.cpp
${TOOLCHAIN_PREFIX}g++ -c -march=rv32i -Os ${GCC_WARNS} -ffreestanding -nostdlib -o print.o print.cpp
${TOOLCHAIN_PREFIX}g++ -c -march=rv32i -Os ${GCC_WARNS} -ffreestanding -nostdlib -o stream.o stream.cpp
${TOOLCHAIN_PREFIX}g++ -Os -ffreestanding -o firmware.elf -Wl,-Bstatic,-T,sections.lds,-Map,firmware.map,--strip-debug main.o print.o stream.o start.o ${operator}.o -lgcc ${IDIR}
chmod -x firmware.elf
${TOOLCHAIN_PREFIX}objcopy -O binary firmware.elf firmware.bin
chmod -x firmware.bin
${PYTHON} makehex.py firmware.bin ${MEM_SIZE} > firmware.hex






