#include "../host/typedefs.h"
void bc2_gen_3(hls::stream< bit32 > & Input_1, hls::stream< bit32 > & Output_1){
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
#include "../host/bc2_par_3.h"
bit32 out_tmp, in_tmp;

	loop_redir: for(int i=0; i<24576; i++){
	#pragma HLS PIPELINE II=2
		in_tmp = Input_1.read();
		Output_1.write(in_tmp);
		in_tmp = Input_1.read();
		Output_1.write(in_tmp);
	}
	loop_0: for(int i=0; i<4096; i++){
	#pragma HLS PIPELINE II=2
		out_tmp = bc2_3_0[i](63, 32);
		Output_1.write(out_tmp);
		out_tmp = bc2_3_0[i](31,  0);
		Output_1.write(out_tmp);
	}

	loop_1: for(int i=0; i<512; i++){
	#pragma HLS PIPELINE II=2
		out_tmp = bc2_3_1[i](63, 32);
		Output_1.write(out_tmp);
		out_tmp = bc2_3_1[i](31,  0);
		Output_1.write(out_tmp);
	}

	loop_2: for(int i=0; i<48; i++){
	#pragma HLS PIPELINE II=2
		out_tmp = bc2_3_2[i](63, 32);
		Output_1.write(out_tmp);
		out_tmp = bc2_3_2[i](31,  0);
		Output_1.write(out_tmp);
	}

}
