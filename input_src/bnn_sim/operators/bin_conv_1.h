
void bin_conv_1(
	hls::stream< bit32 > & Input_1,
	hls::stream< bit32 > & Input_2,
	hls::stream< bit32 > & Output_1
);
#pragma map_target = HW page_num = 10  inst_mem_size = 65536
