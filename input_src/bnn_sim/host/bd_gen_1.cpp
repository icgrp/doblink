#include "../host/typedefs.h"
void bd_gen_1(hls::stream< bit32 > & Input_1, hls::stream< bit32 > & Output_1){
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
#include "../host/bd_par_1.h"
bit32 out_tmp;
 loop_redir: for(int i=0; i<20978; i++){
	#pragma HLS PIPELINE II=2
	out_tmp = Input_1.read();
	Output_1.write(out_tmp);
	out_tmp = Input_1.read();
	Output_1.write(out_tmp);
 }
 loop_0: for(int i=0; i<16384; i++){
#pragma HLS PIPELINE II=1
	out_tmp = bd_1_0[i](63, 32);
	Output_1.write(out_tmp);
	out_tmp = bd_1_0[i](31,  0);
	Output_1.write(out_tmp);
  }
 loop_1: for(int i=0; i<4096; i++){
#pragma HLS PIPELINE II=1
	out_tmp = bd_1_1[i](63, 32);
	Output_1.write(out_tmp);
	out_tmp = bd_1_1[i](31,  0);
	Output_1.write(out_tmp);
  }
 loop_2: for(int i=0; i<2048; i++){
#pragma HLS PIPELINE II=1
	out_tmp = bd_1_2[i](63, 32);
	Output_1.write(out_tmp);
	out_tmp = bd_1_2[i](31,  0);
	Output_1.write(out_tmp);
  }
}
