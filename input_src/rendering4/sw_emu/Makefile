PRJ_NAME=ydma
SRC_DIR=..

all: app.exe emconfig.json $(PRJ_NAME).xclbin

app.exe: $(SRC_DIR)/host/host.cpp
	g++ -Wall -g -std=c++11 $^ -o app.exe \
		-I${XILINX_XRT}/include/ \
		-I${XILINX_VIVADO}/include/ \
		-L${XILINX_XRT}/lib/ -lOpenCL -lpthread -lrt -lstdc++
	
$(PRJ_NAME).xo: $(SRC_DIR)/host/top.cpp $(SRC_DIR)/host/typedefs.h $(SRC_DIR)/operators/data_redir_m.cpp $(SRC_DIR)/operators/rasterization2_m.cpp $(SRC_DIR)/operators/zculling_top.cpp $(SRC_DIR)/operators/coloringFB_bot_m.cpp
	v++ -c -t ${TARGET} --config $(SRC_DIR)/cfg/u50.cfg -k $(PRJ_NAME) \
		-I${XILINX_VIVADO}/include/ \
		-I$(SRC_DIR)/ \
		-I$(SRC_DIR)/host \
		$^ -o $(PRJ_NAME).xo 

$(PRJ_NAME).xclbin: ./$(PRJ_NAME).xo
	v++ -l -t ${TARGET} --config $(SRC_DIR)/cfg/u50.cfg -I$(SRC_DIR)/ $^ -o $(PRJ_NAME).xclbin

emconfig.json:
	emconfigutil --platform xilinx_u50_gen3x16_xdma_201920_3 --nd 1

clean:
	rm -rf $(PRJ_NAME)* app.exe *json *csv *log *summary _x xilinx* .run .Xil .ipcache *.jou

# Unless specified, use the current directory name as the v++ build target
TARGET ?= $(notdir $(CURDIR))
