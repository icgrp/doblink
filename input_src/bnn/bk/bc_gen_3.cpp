#include "Typedefs.h"
void bc_gen_3(hls::stream< Word > & Input_1, hls::stream< Word > & Output_1){
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
#include "bc_par_3.h"
 loop_redir: for(int i=0; i<61440; i++){
#pragma HLS PIPELINE II=1
    Output_1.write(Input_1.read());
  }
 loop_0: for(int i=0; i<8192; i++){
#pragma HLS PIPELINE II=1
  Output_1.write(bc_3_0[i]);
  }
 loop_1: for(int i=0; i<4096; i++){
#pragma HLS PIPELINE II=1
  Output_1.write(bc_3_1[i]);
  }
 loop_2: for(int i=0; i<2048; i++){
#pragma HLS PIPELINE II=1
  Output_1.write(bc_3_2[i]);
  }
 loop_3: for(int i=0; i<1024; i++){
#pragma HLS PIPELINE II=1
  Output_1.write(bc_3_3[i]);
  }
 loop_4: for(int i=0; i<92; i++){
#pragma HLS PIPELINE II=1
  Output_1.write(bc_3_4[i]);
  }
}
