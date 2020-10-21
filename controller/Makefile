default: prog

gateware: build/gateware/nexys_video.v

build/gateware/nexys_video.v: ./rvpld-soc/nexys_video.py ./rvpld-soc/soc_core.py ./rvpld-soc/soc.py
	python3 ./rvpld-soc/nexys_video.py --cpu-type picorv32 --output-dir ./build --bus-standard axi-lite --no-compile-gateware

build: build/gateware/nexys_video.bit

build/gateware/nexys_video.bit: build/gateware/nexys_video.v
	source $$RVPLD_VIVADO && \
		python3 ./rvpld-soc/nexys_video.py --cpu-type picorv32 --output-dir ./build --bus-standard axi-lite --build

firmware: firmware/firmware.bin

firmware/firmware.bin: gateware
	cd firmware && make all

load: build/gateware/nexys_video.bit firmware/firmware.bin
	python3 ./rvpld-soc/nexys_video.py --cpu-type picorv32 --output-dir ./build --bus-standard axi-lite --load

prog: firmware/firmware.bin load
	lxterm /dev/ttyUSB0 --kernel firmware/firmware.bin

clean:
	cd firmware && make clean
	rm -rf build
	rm -rf prog
