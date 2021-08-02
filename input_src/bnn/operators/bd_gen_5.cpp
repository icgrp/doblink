#include "../host/typedefs.h"
void bd_gen_5(hls::stream< bit32 > & Input_1, hls::stream< bit32 > & Output_1){
#pragma HLS INTERFACE axis register port=Input_1
#pragma HLS INTERFACE axis register port=Output_1
#include "../host/bd_par_5.h"
 loop_redir: for(int i=0; i<101874; i++){
#pragma HLS PIPELINE II=1
    Output_1.write(Input_1.read());
    Output_1.write(Input_1.read());
  }
 loop_0: for(int i=0; i<16384; i++){
#pragma HLS PIPELINE II=1
    Output_1.write(bd_5_0[i](31,  0));
    Output_1.write(bd_5_0[i](63, 32));
  }
 loop_1: for(int i=0; i<2048; i++){
#pragma HLS PIPELINE II=1
    Output_1.write(bd_5_1[i](31,  0));
    Output_1.write(bd_5_1[i](63, 32));
  }
}
