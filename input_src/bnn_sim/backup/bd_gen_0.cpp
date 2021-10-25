#include "../host/typedefs.h"
void bd_gen_0(hls::stream< bit32 > & Output_1){
#pragma HLS INTERFACE ap_hs port=Output_1
#include "../host/bd_par_0.h"
bit32 out_tmp;
 loop_0: for(int i=0; i<16384; i++){
#pragma HLS PIPELINE II=1
  out_tmp = bd_0_0[i](63, 32);
  Output_1.write(out_tmp);
  out_tmp = bd_0_0[i](31,  0);
  Output_1.write(out_tmp);
  }
 loop_1: for(int i=0; i<4096; i++){
#pragma HLS PIPELINE II=1
	  out_tmp = bd_0_1[i](63, 32);
	  Output_1.write(out_tmp);
	  out_tmp = bd_0_1[i](31,  0);
	  Output_1.write(out_tmp);
  }
 loop_2: for(int i=0; i<498; i++){
#pragma HLS PIPELINE II=1
	  out_tmp = bd_0_2[i](63, 32);
	  Output_1.write(out_tmp);
	  out_tmp = bd_0_2[i](31,  0);
	  Output_1.write(out_tmp);
  }
}
