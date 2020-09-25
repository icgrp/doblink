# Milestones

Starting with just a list of things to do.
Elaborate and break down into digestable steps.
Then we'll need to think about sequencing and timing.

* Baseline RISCV 
   * Have RISCV compiler tools installed and building code for vanilla RISCV
   * Build a RISCV implementation through to FPGA
   * Compile code and run on RISCV on FPGA
* add any (tutorial) instruction to RISCV
   * compiler
   * RISCV hardware
   * run together
* select RISCV core (or sequence of course) to use
* serial (maybe comes with whatever core or SoC we start with, but probably need to see working...print debug info)   
* add stream instruction to selected RISCV
   * start with data-only, single-stream version?
   * compiler integration
   * RISCV hardware integration
   * use loopback
   * use with two RISCV cores
   * integrate with BFT
       * use with existing leaf interface
   * raw/header version
       * use to configure leaf interfaces
   * expand to multiple stream version
* DMA
   * integrate MM2S with DRAM controller
   * integrate S2MM
   * test for data move
   * test feeding operator over BFT
* compiler configuration and support to compile minimal version for leaf pages
* support to load processor instruction memories
    * leaf page (definitely loading BRAMs)
    * main page (maybe loading BRAMS, but could be loading into main memory)
* master control processor run designs
	* simple overlay to support 
    * simple 2-hardware page design with DMA
    * 6-hardware page rendering
	* one-hardware, one softcore page design with DMA
	* 6-softcore page rendering
* Make build flow for applications	
* overlay for larger benchmark set
    * add benchmarks from Rosetta Benchmark set (milestone for each)

   
    
   

 


