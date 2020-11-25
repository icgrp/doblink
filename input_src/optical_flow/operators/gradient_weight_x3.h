
void gradient_weight_x3(//gradient_t y_filt[MAX_HEIGHT][MAX_WIDTH],
#ifdef HW
		hls::stream<ap_uint<32> > & Input_1,
		hls::stream<ap_uint<32> > & Output_1,
		hls::stream<ap_uint<32> > & Output_2
#else
		pr_flow::stream & Input_1,
		pr_flow::stream & Output_1,
		pr_flow::stream & Output_2
#endif
);

#pragma map_target=HW page_num=6
