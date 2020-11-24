// outer product
// outer product
void outer_product1(//gradient_t gradient[MAX_HEIGHT][MAX_WIDTH],
#ifdef HW
		hls::stream<ap_uint<32> > & Input_1,
		hls::stream<ap_uint<32> > & Input_2,
		hls::stream<ap_uint<32> > & Input_3,
		hls::stream<ap_uint<32> > & Output_1
#else
		pr_flow::stream & Input_1,
		pr_flow::stream & Input_2,
		pr_flow::stream & Input_3,
		pr_flow::stream & Output_1
#endif
		);
