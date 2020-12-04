
void gradient_weight_x2(//gradient_t y_filt[MAX_HEIGHT][MAX_WIDTH],
		       hls::stream<databus_t> &Input_1,
		       hls::stream<databus_t> &Output_1,
		       hls::stream<databus_t> &Output_2);
#pragma map_target=HW page_num=7
