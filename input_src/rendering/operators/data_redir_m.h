void data_redir_m (
		hls::stream<ap_uint<32> > & Input_1,
		hls::stream<ap_uint<32> > & Output_1,
		hls::stream<ap_uint<32> > & Output_2
		);
#pragma map_target = riscv page_num = 4
