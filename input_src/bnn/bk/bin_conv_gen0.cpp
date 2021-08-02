#include "Typedefs.h"
void bin_conv_gen0(hls::stream< Word > & Output_1){
#pragma HLS INTERFACE ap_hs port=Output_1
#include "bin_conv_par0.h"
 loop_0: for(int i=0; i<12916; i++){
#pragma HLS PIPELINE II=1
  Output_1.write(bc0[i]);
  }
}
