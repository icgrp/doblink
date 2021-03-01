#DEBUG=TRUE

CPU=vexriscv
BUS=axi-lite

ifdef DEBUG
	DEBUG_ARGS=--with-ethernet --csr-csv csr.csv
endif

LITEX_ARGS=--cpu-type $(CPU) --output-dir ./build --bus-standard $(BUS) --toolchain vivado

.PHONY: load clean firmware gateware prog

default: prog

gateware: build/gateware/nexys_video.v

build/gateware/nexys_video.v: ./rvpld-soc/nexys_video.py
	python3 ./rvpld-soc/nexys_video.py $(LITEX_ARGS) --no-compile-gateware $(DEBUG_ARGS)

build: build/gateware/nexys_video.bit

build/gateware/nexys_video.bit: ./rvpld-soc/nexys_video.py
	python3 ./rvpld-soc/nexys_video.py $(LITEX_ARGS) --build $(DEBUG_ARGS)

firmware: firmware/firmware.bin

firmware/firmware.bin: firmware/main.c
	cd firmware && make all

load: build/gateware/nexys_video.bit
	python3 ./rvpld-soc/nexys_video.py $(LITEX_ARGS) --load $(DEBUG_ARGS)

prog: firmware/firmware.bin
	lxterm /dev/ttyUSB2 --kernel firmware/firmware.bin

clean:
	-@ cd firmware && (make clean 2> /dev/null || true)
	-@ rm -rf csr.csv
	-@ rm -rf build
	-@ rm -rf prog
