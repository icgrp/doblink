#include "typedefs.h"
void data_in_gen_4(int image_num, hls::stream< Word > & Input_1, hls::stream< bit32 > & Output_1){
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
#include "data_in_par_4.h"

int counter=0;
Word data_tmp;

 loop_redir: for(int i=0; i<81920; i++){
#pragma HLS PIPELINE II=1
	if(counter < image_num*1024){
		data_tmp = Input_1.read();
		Output_1.write(data_tmp(63, 32));
		Output_1.write(data_tmp(31,  0));
	}else{
		Input_1.read();
	}
	counter++;
  }
 loop_0: for(int i=0; i<16384; i++){
#pragma HLS PIPELINE II=1
	 if(counter < image_num*1024){
		 data_tmp = data_in_4_0[i];
		 Output_1.write(data_tmp(63, 32));
		 Output_1.write(data_tmp(31,  0));
	 }
  }


 loop_1: for(int i=0; i<4096; i++){
#pragma HLS PIPELINE II=1
	 if(counter < image_num*1024){
		data_tmp = data_in_4_1[i];
		Output_1.write(data_tmp(63, 32));
		Output_1.write(data_tmp(31,  0));
	 }
  }
}
