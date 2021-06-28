#include "../host/typedefs.h"

void bd_gen_8(hls::stream< bit32 > & Input_1, hls::stream< bit32 > & Output_1){
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
#include "../host/bd_par_8.h"
	Word in_tmp;
	bit32 out_tmp;
	loop_redir: for(int i=0; i<158706; i++){
		#pragma HLS PIPELINE II=2
		out_tmp = Input_1.read();
		//printf("0x%08x,\n", (unsigned int) out_tmp);
		Output_1.write(out_tmp);
		out_tmp = Input_1.read();
		//printf("0x%08x,\n", (unsigned int) out_tmp);
		Output_1.write(out_tmp);
	}

	loop_0: for(int i=0; i<16384; i++){
		#pragma HLS PIPELINE II=1
		out_tmp = bd_8_0[i](63, 32);
		//printf("0x%08x,\n", (unsigned int) out_tmp);
		Output_1.write(out_tmp);
		out_tmp = bd_8_0[i](31,  0);
		//printf("0x%08x,\n", (unsigned int) out_tmp);
		Output_1.write(out_tmp);
	}

	loop_1: for(int i=0; i<512; i++){
		#pragma HLS PIPELINE II=1
		out_tmp = bd_8_1[i](63, 32);
		//printf("0x%08x,\n", (unsigned int) out_tmp);
		Output_1.write(out_tmp);
		out_tmp = bd_8_1[i](31,  0);
		//printf("0x%08x,\n", (unsigned int) out_tmp);
		Output_1.write(out_tmp);
	}
}
