
void output_fun(hls::stream<stdio_t> &Input_1,
		hls::stream<stdio_t> &Input_2,
		hls::stream< ap_uint<32> > &Output_1);
#pragma map_target=HW page_num=8 inst_mem_size = 32768
