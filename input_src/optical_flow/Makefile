
all: 
	#g++ -I /opt/Xilinx/Vivado/2018.2/include -o Test_host  ./*.cpp  -O3 -DPROFILE
	g++ -I /opt/Xilinx/Vivado/2018.2/include -o Test_host  ./operators/*.cpp ./host/*.cpp   -O3 -DPROFILE


run:
	./Test_host  -p ~/rosetta/optical-flow/datasets/current/ -o ~/rosetta/optical-flow/datasets/current/out.flo

clean:
	rm -rf ./Test_host
