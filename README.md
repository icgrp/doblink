# DIRC based on PicoRV32
This is a temporary repo for DIRC with [picorv32](https://github.com/cliffordwolf/picorv32) support.


## 1 Tool Setup

### 1.1 Vitis Preparation
The demo is developed with [Vitis 2020.1](https://www.xilinx.com/support/download/index.html/content/xilinx/en/downloadNav/vivado-design-tools/2020-1.html) 
and [Ultra96v2 board](https://www.96boards.org/product/ultra96/).
The default Vitis does not include Ultra96v2 BSP. You can copy the dir **ultra96v2**
under [BSP](./BSP) to \<Vitis Installation DIR\>/Vivado/2020.1/data/boards/board_files.

### 1.2 RISCV Tool Praparation

We are based on picorv32 repo. You can install the RISC-V toolchain with 
certain commit tag (411d134).
We copy the installation guide from [picorv32](https://github.com/cliffordwolf/picorv32) 
as below.

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


## 2 Benchmark Preparation
1. As our [Makefile](./Makefile) certain directory hierarchy. We take 
**Rendering** as an example.
2. You can create the directory [rendering](./input_src) with the same 
name as the benchmark.
3. We create one cpp file and one header file for each operator. In 
[./input_src/rendering/operators](./input_src/rendering/operators), we
can see 6 operators to be mapped to partial reconfigurable pages.
4. We can set the page number and target (HW or riscv) in the header file
for each [operator](input_src/rendering/operators/data_redir_m.h).

```c
    #pragma map_target = HW page_num = 3 inst_mem_size = 65536
```

5. Currently, we use a **top** function in [./input_src/rendering/host/top.cpp](./input_src/rendering/host/top.cpp)
to show how to connect different operators together. Our python script 
([config.py](./pr_flow/config.py)) will
parse the top.cpp and operator header files to extract the interconnection,
and generate the configuration packets.
 


## Tutorial 1: Map all Operators to Hardware
1. After you set up all the necessary tools, you need set the directory 
for Vitis and RISC-V toolchain in [configure.xml](./common/configure/configure.xml).
```c
    <spec name = "Xilinx_dir" value = "/scratch/unsafe/SDSoC/Vivado/2020.1/settings64.sh" />
    <spec name = "riscv_dir"  value = "/scratch/unsafe/RISCV/riscv32" />
```
2. In the [Makefile](./Makefile), change the **prj_name** to **rendering**.
```c
    prj_name=rendering
```
3. Type **Make -j$(nproc)**. It will generate all the necessary DCP and 
bitstream files automatically. Different operators can be compiled in 
parallel according to the thread number of your local machine. Be carefull
with the memory requirements, when you use multi-threads to compile the 
project. When I use 8 threads to compile, I at least needs 32 GB DDR 
memory.

4. Type **Make mono_prj -j$(nproc)**, it will generate floorplan_staitc.xda
file for Vitis project under ./workspace/F007_mono_bft_rendering/prj/.
This is a one-time compilation to get the xda file for Vitis. You don't 
need to compile the xda when you make changes to the operators later.
To save time, you can also copy the floorplan_staitc.xda under [here](./BSP).

5.  















 


 

















