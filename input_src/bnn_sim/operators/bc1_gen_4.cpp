#include "../host/typedefs.h"
void bc1_gen_4(hls::stream< bit32 > & Input_1, hls::stream< bit32 > & Output_1){
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
#include "../host/bc1_par_4.h"
bit32 out_tmp, in_tmp;

	loop_redir: for(int i=0; i<32768; i++){
	#pragma HLS PIPELINE II=2
		in_tmp = Input_1.read();
		Output_1.write(in_tmp);
		in_tmp = Input_1.read();
		Output_1.write(in_tmp);
	}
	loop_0: for(int i=0; i<1024; i++){
	#pragma HLS PIPELINE II=2
		out_tmp = bc1_4_0[i](63, 32);
		Output_1.write(out_tmp);
		out_tmp = bc1_4_0[i](31,  0);
		Output_1.write(out_tmp);
	}

	loop_1: for(int i=0; i<512; i++){
	#pragma HLS PIPELINE II=2
		out_tmp = bc1_4_1[i](63, 32);
		Output_1.write(out_tmp);
		out_tmp = bc1_4_1[i](31,  0);
		Output_1.write(out_tmp);
	}

	loop_2: for(int i=0; i<440; i++){
	#pragma HLS PIPELINE II=2
		out_tmp = bc1_4_2[i](63, 32);
		Output_1.write(out_tmp);
		out_tmp = bc1_4_2[i](31,  0);
		Output_1.write(out_tmp);
	}

}
