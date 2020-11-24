void gradient_weight_y_3(//pixel_t gradient_x[MAX_HEIGHT][MAX_WIDTH],
#ifdef HW
		hls::stream<ap_uint<32> > & Input_1,
		hls::stream<ap_uint<32> > & Output_1
#else
		pr_flow::stream & Input_1,
		pr_flow::stream & Output_1
#endif
);
#pragma map_target=HW page_num=page_9
