#include "../host/typedefs.h"





void p2p (
		hls::stream<ap_uint<32> > & Input_1,
		hls::stream<ap_uint<32> > & Output_1
		)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
	unsigned int buffer[9576];
	int i;
	dma_buffer_label1:for(i=0; i<9576; i++){
#pragma HLS PIPELINE
		buffer[i] = Input_1.read();
	}

	dma_buffer_label0:for(i=0; i<9576; i++){
#pragma HLS PIPELINE
		Output_1.write(buffer[i]);
	}
}

