
void bin_dense_wrapper(
	hls::stream< bit32 > & Input_1,
	hls::stream< bit32 > & Input_2,
	hls::stream< bit32 > & Output_1
);
#pragma map_target = HW page_num = 20 inst_mem_size = 131072
