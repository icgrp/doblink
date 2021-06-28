#include "../host/typedefs.h"

void to_dma (
		hls::stream<ap_uint<32> > & Input_1,
		hls::stream<ap_uint<32> > & Output_1
		)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1

	bit32 in1;
	// 0x2000*0x10=0x20000=131072 bytes
	// 131072/4 = 32768 words
	in1 = Input_1.read();
	if(in1 == 0xdeadbeaf){
		return;
	}else{
		Output_1.write(32768);
	}
	to_dma_label0:for(int i=0; i<32767; i++){
#pragma HLS PIPELINE II=1
		in1 = Input_1.read();
		Output_1.write(in1);
	}

}

