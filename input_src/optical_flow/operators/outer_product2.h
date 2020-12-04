void outer_product2(//gradient_t gradient[MAX_HEIGHT][MAX_WIDTH],
    		       hls::stream<databus_t> &Input_1,
		       hls::stream<databus_t> &Input_2,
		       hls::stream<databus_t> &Input_3,
		   hls::stream<databus_t> &Output_1
			);
#pragma map_target=HW page_num =14
