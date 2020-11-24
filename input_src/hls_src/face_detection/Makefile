# Makefile for BNN of Rosetta benchmarks
#
# Author: Yuanlong Xiao (ylxiao@seas.upenn.edu)
#
# Targets:
#   all   - Builds hardware and software in SDSoC.
#   host  - Compiles for local host (for debugging purposes).
#   hls   - Performs only HLS (for debugging purposes).
#   clean - Removes all build products.


.PHONY: all clean hls local

all:
	g++ -I /scratch/safe/SDSoC/Vivado/2018.2/include -o Test_host  ./host/*.cpp ./sdsoc/*.cpp  -O3
	./Test_host
	rm ./Test_host


clean:
	rm -rf ./Test


















