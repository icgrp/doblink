
// filter hidden pixels
void zculling_top (
		hls::stream<ap_uint<32> > & Input_1,
		hls::stream<ap_uint<32> > & Input_2,
		hls::stream<ap_uint<32> > & Output_1
	  );
#pragma map_target = riscv  page_num = 6 inst_mem_size = 262144

