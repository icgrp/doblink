// outer product
void outer_product1(
    		       hls::stream<databus_t> &Input_1,
		       hls::stream<databus_t> &Input_2,
		       hls::stream<databus_t> &Input_3,
		   hls::stream<databus_t> &Output_1
		);
#pragma map_target=HW page_num= 17 inst_mem_size = 32768
