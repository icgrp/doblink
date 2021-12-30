# DEBUG=TRUE

CPU=vexriscv
BUS=axi-lite
TOOLCHAIN=vivado
# TOOLCHAIN=vivado --synth-mode yosys
#TOOLCHAIN=symbiflow
BENCHMARK=rendering

ifdef DEBUG
	DEBUG_ARGS=--with-ethernet --csr-csv csr.csv
endif

LITEX_ARGS=--bench $(BENCHMARK) --cpu-type $(CPU) --output-dir ./build --bus-standard $(BUS) --toolchain $(TOOLCHAIN) $(DEBUG_ARGS) --uart-baudrate 921600

.PHONY: load clean firmware gateware prog

default: prog

gateware: build/gateware/nexys_video.v

build/gateware/nexys_video.v: ./rvpld-soc/nexys_video.py
	python3 ./rvpld-soc/nexys_video.py $(LITEX_ARGS) --no-compile-gateware

build: build/gateware/nexys_video.bit

build/gateware/nexys_video.bit: ./rvpld-soc/nexys_video.py
	python3 ./rvpld-soc/nexys_video.py $(LITEX_ARGS) --build

firmware: firmware/$(BENCHMARK)/firmware.bin

firmware/$(BENCHMARK)/firmware.bin: firmware/$(BENCHMARK)/*.c
	cd firmware/$(BENCHMARK) && make all

load:
	python3 ./rvpld-soc/nexys_video.py $(LITEX_ARGS) --load

prog: firmware/$(BENCHMARK)/firmware.bin
	lxterm /dev/ttyUSB0 --kernel firmware/$(BENCHMARK)/firmware.bin

clean:
	-@ cd firmware && (make clean 2> /dev/null || true)
	-@ rm -rf csr.csv
	-@ rm -rf build
	-@ rm -rf prog
