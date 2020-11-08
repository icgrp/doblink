# Learning

## Tutorials

* RV getting started
	 *  https://riscv.org/wp-content/uploads/2015/02/riscv-intro-tutorial-hpca2015.pdf
	 *  https://riscv.org/wp-content/uploads/2015/02/riscv-software-stack-tutorial-hpca2015.pdf
	 *  https://inst.eecs.berkeley.edu//~cs61c/fa17/img/riscvcard.pdf (2 page instruction reference)
*	adding instruction to RV (these probably dated, but gives flavor, at least)
  	  *  https://www.youtube.com/watch?v=64nsYJJqNvI&feature=youtu.be
	  * https://nitish2112.github.io/post/adding-instruction-riscv/


## Components to explore

* RV implementation
  * Probably don't want to use Rocket (see Guy talk on ORCA)
	  * ORCA/Guy Lemieux-- https://github.com/riscveval/orca-1
	     * maybe a distribution of ORCA: https://riscv.org/wp-content/uploads/2016/01/Wed1200-2016-01-05-VectorBlox-ORCA-RISC-V-DEMO.pdf
	 * Clifford Wolf https://github.com/cliffordwolf/picorv32
	     * by yosys author, so probably works with symbiflow
         * has version with integrated AXI interface 
	     * Symbiflow Example: https://github.com/SymbiFlow/symbiflow-examples/tree/master/xc7/picosoc_demo

* Vex https://github.com/SpinalHDL/VexRiscv
	     * runs linux
	     * known to work with Symbiflow
		 * written in  unusual HDL? so maybe not easiest to work with
	 * PULP https://pulp-platform.org/implementation.html
         * several cores here, including a PULPino (under microcontrollers)
	     * heard good things about them, but from people who are doing ASICs
		 * may have the problems Guy Lemieux complains about for not being FPGA-friendly
* AXI
     * ZipCPU https://github.com/ZipCPU/wb2axip
     	* Axi-lite Crossbar https://github.com/ZipCPU/wb2axip/blob/master/rtl/axilxbar.v
        * used this summer (we fixed a few bugs, so get those)
* DRAM controller
	* liteDRAM https://github.com/enjoy-digital/litedram
* UART
    * ZipCPU https://github.com/ZipCPU/wbuart32

* BYU code to replace memory in a bitstream
  * patch ram https://github.com/SymbiFlow/prjxray-bram-patch

* ZyCAP -- Fast DMA load through ICAP port -- maybe can use for devices that do not have PCAP (non-Zynq devices)
   * ZyCAP source https://github.com/warclab/zycap
   * ZyCAP paper https://ieeexplore.ieee.org/document/6780588



