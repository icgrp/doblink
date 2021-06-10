This is the files we add to make Vivado HLS verilog map through yosys.
Solutions are dependent on how Vivado HLS writes the verilog,
  so likely brittle and not general solutions for any verilog.

Makefile -- copy the files that need to be in specific places into the
                    yosys tree (brams_map.v, brams.txt)
brams.txt -- yosys receipe for mapping brams;
                     augmented to have version with 2 read and 2 write
                    ports
brams_map.v -- mapping of abstract RAMs to Xilinx primitives, not actually
                    changed, yet
yosys_memory_patch.sh -- converts memory idioms that yosys has problems
                    with to ones that it can handle
merge_ports.perl -- merges read/write ports back together;
                    also changes names on RAMB36E1 to match what vpr  expects;
		    also maps DFFSR_PPP


		     
		    
