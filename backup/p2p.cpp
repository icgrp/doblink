#include "../host/typedefs.h"





void p2p (
		hls::stream<ap_uint<32> > & Input_1,
		hls::stream<ap_uint<32> > & Output_1
		)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1

	Output_1.write(Input_1.read());
	Output_1.write(Input_1.read());
	Output_1.write(Input_1.read());
	Output_1.write(Input_1.read());
	Output_1.write(Input_1.read());
	Output_1.write(Input_1.read());

}

