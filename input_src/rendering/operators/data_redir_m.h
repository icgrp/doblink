void data_redir_m (
		hls::stream<ap_uint<32> > & Input_1,
		hls::stream<ap_uint<32> > & Output_1,
		hls::stream<ap_uint<32> > & Output_2
		);
#pragma map_target = riscv page_num = 3 inst_mem_size = 65536
#pragma debug_port = 3

