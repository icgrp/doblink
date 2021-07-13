# DEBUG=TRUE

CPU=vexriscv
BUS=axi-lite
# TOOLCHAIN=vivado
TOOLCHAIN=vivado --synth-mode yosys
# TOOLCHAIN=symbiflow

ifdef DEBUG
	DEBUG_ARGS=--with-ethernet --csr-csv csr.csv
endif

LITEX_ARGS=--cpu-type $(CPU) --output-dir ./build --bus-standard $(BUS) --toolchain $(TOOLCHAIN) $(DEBUG_ARGS)

.PHONY: load clean firmware gateware prog

default: prog

gateware: build/gateware/nexys_video.v

build/gateware/nexys_video.v: ./rvpld-soc/nexys_video.py
	python3 ./rvpld-soc/nexys_video.py $(LITEX_ARGS) --no-compile-gateware

build: build/gateware/nexys_video.bit

build/gateware/nexys_video.bit: ./rvpld-soc/nexys_video.py
	python3 ./rvpld-soc/nexys_video.py $(LITEX_ARGS) --build

firmware: firmware/firmware.bin

firmware/firmware.bin: firmware/*.c
	cd firmware && make all

load: build/gateware/nexys_video.bit
	python3 ./rvpld-soc/nexys_video.py $(LITEX_ARGS) --load

prog: firmware/firmware.bin
	lxterm /dev/ttyUSB0 --kernel firmware/firmware.bin

clean:
	-@ cd firmware && (make clean 2> /dev/null || true)
	-@ rm -rf csr.csv
	-@ rm -rf build
	-@ rm -rf prog
