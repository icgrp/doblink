#include "../host/typedefs.h"
void output_fun(hls::stream<stdio_t> &Input_1,
		hls::stream<stdio_t> &Input_2,
		hls::stream< ap_uint<32> > &Output_1)
{
#pragma HLS interface ap_hs port=Input_1
#pragma HLS interface ap_hs port=Output_1
#pragma HLS interface ap_hs port=Input_2
	while (Input_1.empty());
	ap_uint<128> tmp =10;
	tmp(31,0) = Input_1.read();
	if (tmp !=10){
		Output_1.write(MAX_HEIGHT*MAX_WIDTH*2+4);
		Output_1.write(MAX_HEIGHT*MAX_WIDTH*2+4);
		Output_1.write(MAX_HEIGHT*MAX_WIDTH*2+4);
		Output_1.write(MAX_HEIGHT*MAX_WIDTH*2+4);
	}

	tmp(63, 32)  = Input_2.read();
	tmp(95, 64)  = Input_1.read();
	tmp(127, 96) = Input_2.read();
	Output_1.write(tmp(31,0));
	Output_1.write(tmp(63, 32));
	Output_1.write(tmp(95, 64));
	Output_1.write(tmp(127, 96));


	OUT_CONVERT: for (int i = 0; i < MAX_HEIGHT*MAX_WIDTH/2-1; i++)
	{
		#pragma HLS pipeline II = 4
		tmp(31,   0) = Input_1.read();
		tmp(63,  32) = Input_2.read();
		tmp(95,  64) = Input_1.read();
		tmp(127, 96) = Input_2.read();
		Output_1.write(tmp(31,0));
		Output_1.write(tmp(63, 32));
		Output_1.write(tmp(95, 64));
		Output_1.write(tmp(127, 96));
	}
}


