#include "../host/typedefs.h"
void data_1_4_3(
			hls::stream<ap_uint<32> > & Input_1,
			hls::stream<ap_uint<32> > & Input_2,
			hls::stream<ap_uint<32> > & Input_3,
			hls::stream<ap_uint<32> > & Output_1,
			hls::stream<ap_uint<32> > & Output_2,
			hls::stream<ap_uint<32> > & Output_3
			)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Input_2
#pragma HLS INTERFACE ap_hs port=Input_3
#pragma HLS INTERFACE ap_hs port=Output_1
#pragma HLS INTERFACE ap_hs port=Output_2
#pragma HLS INTERFACE ap_hs port=Output_3

	static char ExecuteAdd = 1;

	if(ExecuteAdd == 1)
	{
		FeatureType a1;
		FeatureType a2;
		FeatureType c;
		a1(31,0) = Input_1.read();
		a2(31,0) = Input_2.read();
		c = a1+a2;
		bit32 out_tmp;
		out_tmp(31,0) = c.range(31,0);
		Output_1.write(out_tmp);
		ExecuteAdd = 0;
	}else{
		bit32 tmp;
		tmp(31, 0) = Input_3.read();
		Output_2.write(tmp);
		Output_3.write(tmp);
		ExecuteAdd = 1;
	}
}
