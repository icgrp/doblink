#include "../host/typedefs.h"
void bc2_gen_0(hls::stream< bit32 > & Output_1){
#pragma HLS INTERFACE axis register port=Output_1
#include "../host/bc2_par_0.h"
 loop_0: for(int i=0; i<16384; i++){
#pragma HLS PIPELINE II=1
  Output_1.write(bc2_0_0[i](31,  0));
  Output_1.write(bc2_0_0[i](63, 32));
  }
 loop_1: for(int i=0; i<4096; i++){
#pragma HLS PIPELINE II=1
  Output_1.write(bc2_0_1[i](31,  0));
  Output_1.write(bc2_0_1[i](63, 32));
  }
}
