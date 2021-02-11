# DIRC based on PicoRV32
This is a temporary repo for DIRC with [picorv32](https://github.com/cliffordwolf/picorv32) support.


## Tool Setup

### Vitis Preparation
The demo is developed with [Vitis 2020.1](https://www.xilinx.com/support/download/index.html/content/xilinx/en/downloadNav/vivado-design-tools/2020-1.html) 
and [Ultra96v2 board](https://www.96boards.org/product/ultra96/).
The default Vitis does not include Ultra96v2 BSP. You can copy the dir **ultra96v2**
under [BSP](./BSP) to \<Vitis Installation DIR\>/Vivado/2020.1/data/boards/board_files.

### RISCV Tool Praparation

We are based on picorv32 repo. You can install the RISC-V toolchain 
certain commit tag (411d134) as below.
We copy the installation guide from [picorv32](https://github.com/cliffordwolf/picorv32) 

    # Ubuntu packages needed:
    sudo apt-get install autoconf automake autotools-dev curl libmpc-dev \
            libmpfr-dev libgmp-dev gawk build-essential bison flex texinfo \
	    gperf libtool patchutils bc zlib1g-dev git libexpat1-dev

    sudo mkdir /opt/riscv32i
    sudo chown $USER /opt/riscv32i

    git clone https://github.com/riscv/riscv-gnu-toolchain riscv-gnu-toolchain-rv32i
    cd riscv-gnu-toolchain-rv32i
    git checkout 411d134
    git submodule update --init --recursive

    mkdir build; cd build
    ../configure --with-arch=rv32i --prefix=/opt/riscv32i
    make -j$(nproc)



 

















