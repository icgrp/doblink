# Learning

## Tutorials

* RV getting started
	 *  https://riscv.org/wp-content/uploads/2015/02/riscv-intro-tutorial-hpca2015.pdf
	 *   https://riscv.org/wp-content/uploads/2015/02/riscv-software-stack-tutorial-hpca2015.pdf
*	adding instruction to RV (these probably dated, but gives flavor, at least)
  	  *  https://www.youtube.com/watch?v=64nsYJJqNvI&feature=youtu.be
	  * https://nitish2112.github.io/post/adding-instruction-riscv/


## Components to explore

* RV implementation
  * Probably don't want to use Rocket (see Guy talk on ORCA)
	  * ORCA/Guy -- https://github.com/riscveval/orca-1
	     * maybe a distribution of ORCA: https://riscv.org/wp-content/uploads/2016/01/Wed1200-2016-01-05-VectorBlox-ORCA-RISC-V-DEMO.pdf
	 * Clifford Wolf https://github.com/cliffordwolf/picorv32
	     * by yosys author, so probably works with symbiflow
	     * Symbiflow Example: https://github.com/SymbiFlow/symbiflow-examples/tree/master/xc7/picosoc_demo
	 * Vex https://github.com/SpinalHDL/VexRiscv
	     * runs linux
	     * known to work with Symbiflow
		 * written in  unusual HDL? so maybe not easiest to work with
* AXI
     * ZipCPU https://github.com/ZipCPU/wb2axip
        * used this summer (we fixed a few bugs, so get those)
* DRAM controller
	* liteDRAM https://github.com/enjoy-digital/litedram
* UART
    * ZipCPU https://github.com/ZipCPU/wbuart32




