# Reading

* GRVI/Phallanx -- http://fpga.org/grvi-phalanx/
  * inspirational compact RISC-V implementation
* Hoplite -- https://dl.acm.org/doi/10.1145/3027486
  * basic, light-weight, deflection-routed, packet-switched
network
* Hoplite BFT --
https://nachiket.github.io/publications/deflection-bft_fpl-2017.pdf
	* Butterfly-Fat Tree version that we use
* PRflow -- http://ic.ese.upenn.edu/abstracts/prflow_fpt2019.html
	* our fast, separate compilation and mapping
* [DIRC](../internal/dirc_nodist.pdf)
    * our integration using Zynq hard-core processor; for leaf pages,
      should be able to support the STREAM_READ, STREAM_WRITE interface here
* [IC86](../internal/ic86.pdf)
    * describes design of leaf interface and BFT including role of master
      control processor.  At some level, leaf pages interfaces like this.  May be uses
      AXI-stream to connect to the same leaf-interface logic; possibly
      replaces some of that leaf-interface logic.  
* BERT --
	* our implementation to load BRAMs through configuration path
    * currently only has Zynq bitstream load, but possibly adaptable (should be able to generate partial bitstreams for 7-series)

