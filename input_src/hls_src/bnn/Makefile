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
	cp ./host/* ./
	cp ./sdsoc/* ./
	g++ -I /scratch/safe/SDSoC/Vivado/2018.2/include -o Test_host  ./*.cpp -O3
	rm ./*.cpp
	rm ./*.h
	./Test_host
	rm ./Test_host


clean:
	rm -rf ./Test


















