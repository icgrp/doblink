# Goals and Requirements

Initially brainstorming.  To be refined to prioritize and set goals.

* RV
  * < 5K LUTs, 10 RAMB36s
       * multiple size/performance options a bonus)
       * RV32I minimum
       * RV64 in tight footprint interesting/stretch goal options
       * privilege levels?
          * for leaf version -- can do without (probably want to just have
            the lowest, machine level and no space or complexity for the
            higher levels)
	      * for controller, may want
	         * run linux?
* single-cycle stream read, write (pure data case)
   *   (nice to have full control case also single-cycle, but less important)
   *  ability to target one of multiple streams from native stream operation
   *    streams compatible with AXI-S, hls::stream()
   *    interface to deflection-routed PS network  (pure data link, full packet control link)
*  compile operator < 10s
* ability to load program < 1s
*  (for leaf versions) compiled program fit in 1 or 2 BRAMs? (<4K instructions)
* open-source
*  map with symbiflow
* ability to port across broad-range of FPGAs?
* run prflow/DIRC version of Rosetta benchmarks (all?) [potentially resized]

