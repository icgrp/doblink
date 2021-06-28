# Makefile for BNN of Rosetta benchmarks
#
# Author: Yuanlong Xiao (ylxiao@seas.upenn.edu)
#
# Targets:
#   all   - Builds hardware and software in SDSoC.


OPERATORS_OBJ=$(addsuffix .o, $(notdir $(basename $(wildcard operators/*.cpp))))
#HOST_OBJ=$(addsuffix .o, $(notdir $(basename $(wildcard host/*.cpp))))
HOST_OBJ=./check_result.o  ./face_detect_host.o  ./image.o    ./top_sim.o  ./utils.o



INCLUDE=-I /opt/Xilinx/Vivado/2018.2/include 
OPT_LEVEL=-O3
CFLAGS=$(INCLUDE) $(OPT_LEVEL)
CXX=g++
VPATH=src

all: main

main:$(OPERATORS_OBJ) $(HOST_OBJ)
	$(CXX) $(CFLAGS) -o main $^ 
	./main

$(HOST_OBJ):%.o:./host/%.cpp
	$(CXX) $(CFLAGS) -o $@ -c $^


$(OPERATORS_OBJ):%.o:./operators/%.cpp
	$(CXX) $(CFLAGS) -o $@ -c $^

run:
	./main 

install:
	echo hello

print: 
	ls ./src

tar:
	tar -czvf ./src.tar.gz ./src/ 


try:
	echo $(notdir $(wildcard ./src)) 



clean:
	rm -rf ./*.o main


















