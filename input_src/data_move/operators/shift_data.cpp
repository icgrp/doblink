#include "../host/typedefs.h"

void shift_data (
		hls::stream<ap_uint<32> > & Input_1,
		hls::stream<ap_uint<32> > & Output_1
		)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1


	bit8 in[1024];
	bit32 out;
	//bit32 data_array[32768];
	to_dma_label0:for(int i=0; i<32768; i++){
#pragma HLS PIPELINE II=1
		unsigned int index = i&0x3ff;
		in[index] = Input_1.read();
		in[index] = in[index] + 5;
		unsigned int tmp = in[index];
		out = tmp;
		Output_1.write(out);
	}

	return;

}

