
void gradient_weight_x2(
		       hls::stream<databus_t> &Input_1,
		       hls::stream<databus_t> &Output_1,
		       hls::stream<databus_t> &Output_2);
#pragma map_target=HW page_num=12 inst_mem_size = 65536
