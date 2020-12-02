#DEBUG=TRUE

CPU=picorv32
BUS=axi-lite

DEBUG_ARGS=--l2-size 8192

ifdef DEBUG
	DEBUG_ARGS=--with-ethernet --csr-csv csr.csv
endif

default: prog

gateware: build/gateware/nexys_video.v

build/gateware/nexys_video.v: ./rvpld-soc/nexys_video.py ./rvpld-soc/soc_core.py ./rvpld-soc/soc.py
	python3 ./rvpld-soc/nexys_video.py --cpu-type $(CPU) --output-dir ./build --bus-standard $(BUS) --no-compile-gateware $(DEBUG_ARGS)

build: build/gateware/nexys_video.bit

build/gateware/nexys_video.bit: ./rvpld-soc/nexys_video.py ./rvpld-soc/soc_core.py ./rvpld-soc/soc.py
	source $$RVPLD_VIVADO && \
		python3 ./rvpld-soc/nexys_video.py --cpu-type $(CPU) --output-dir ./build --bus-standard $(BUS) --build $(DEBUG_ARGS)

firmware: firmware/firmware.bin

firmware/firmware.bin: gateware
	cd firmware && make all

load: build/gateware/nexys_video.bit
	python3 ./rvpld-soc/nexys_video.py --cpu-type $(CPU) --output-dir ./build --bus-standard $(BUS) --load $(DEBUG_ARGS)

prog: firmware/firmware.bin
	lxterm /dev/ttyUSB2 --kernel firmware/firmware.bin

clean:
	-@ cd firmware && (make clean 2> /dev/null || true)
	-@ rm -rf csr.csv
	-@ rm -rf build
	-@ rm -rf prog
