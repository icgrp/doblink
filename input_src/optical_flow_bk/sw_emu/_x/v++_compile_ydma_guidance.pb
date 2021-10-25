
½	
v++_compile_ydma$c98cd384-673e-451f-b583-499b75ead579±v++  -c -t sw_emu --config ../cfg/u50.cfg -k ydma -I/opt/Xilinx/Vivado/2021.1/include/ -I../ -I../host ../host/top.cpp ../host/typedefs.h ../operators/gradient_weight_y_1.cpp ../operators/gradient_xyz_calc.cpp ../operators/flow_calc_2.cpp ../operators/outer_product1.cpp ../operators/gradient_weight_y_2.cpp ../operators/tensor_weight_y1.cpp ../operators/tensor_weight_x1.cpp ../operators/output_fun.cpp ../operators/tensor_weight_y2.cpp ../operators/tensor_weight_x2.cpp ../operators/gradient_weight_x3.cpp ../operators/gradient_weight_y_3.cpp ../operators/gradient_weight_x1.cpp ../operators/flow_calc_1.cpp ../operators/outer_product2.cpp ../operators/gradient_weight_x2.cpp -o ydma.xo *t"p/home/ylxiao/ws_211/prflow_riscv/input_src/optical_flow_bk/sw_emu/_x/reports/ydma/v++_compile_ydma_guidance.html2e"a/home/ylxiao/ws_211/prflow_riscv/input_src/optical_flow_bk/sw_emu/_x/v++_compile_ydma_guidance.pbBñ
../cfg/u50.cfgÞplatform=xilinx_u50_gen3x16_xdma_201920_3
debug=1
save-temps=1

[connectivity]
nk=ydma:1:ydma_1
sp=ydma_1.input1:HBM[0]
sp=ydma_1.input2:HBM[1]
sp=ydma_1.output1:HBM[0]
sp=ydma_1.output2:HBM[1]

[profile]
data=all:all:all
