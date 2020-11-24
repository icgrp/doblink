#include "../host/typedefs.h"
#ifndef HW
#include "../Overlays/mmu.h"
#endif



void output_fun(
#ifdef HW
		hls::stream<ap_uint<32> > & Input_1,
		hls::stream<ap_uint<32> > & Input_2,
		hls::stream<ap_uint<32> > & Output_1
#else
		pr_flow::stream & Input_1,
		pr_flow::stream & Input_2,
		pr_flow::stream & Output_1
#endif
)
{
#pragma HLS interface ap_hs port=Input_1
#pragma HLS interface ap_hs port=Output_1
#pragma HLS interface ap_hs port=Input_2
	//while (Input_1.empty());
	ap_uint<128> tmp =10;
	//tmp(31,0) = STREAM_READ(Input_1);
	//if (tmp !=10){
	static int i = 0;
	if(i==0){
		STREAM_WRITE(Output_1, MAX_HEIGHT*MAX_WIDTH*2+4);
		STREAM_WRITE(Output_1, MAX_HEIGHT*MAX_WIDTH*2+4);
		STREAM_WRITE(Output_1, MAX_HEIGHT*MAX_WIDTH*2+4);
		STREAM_WRITE(Output_1, MAX_HEIGHT*MAX_WIDTH*2+4);
	}
	//}

	//tmp(63, 32)  = STREAM_READ(Input_2);
	//tmp(95, 64)  = STREAM_READ(Input_1);
	//tmp(127, 96) = STREAM_READ(Input_2);
	//STREAM_WRITE(Output_1, tmp(31,0));
	//STREAM_WRITE(Output_1, tmp(63, 32));
	//STREAM_WRITE(Output_1, tmp(95, 64));
	//STREAM_WRITE(Output_1, tmp(127, 96));


	//OUT_CONVERT: for (int i = 0; i < MAX_HEIGHT*MAX_WIDTH/2-1; i++)
	//{
		//#pragma HLS pipeline II = 4
		tmp(31,   0) = STREAM_READ(Input_1);
		tmp(63,  32) = STREAM_READ(Input_2);
		tmp(95,  64) = STREAM_READ(Input_1);
		tmp(127, 96) = STREAM_READ(Input_2);
		STREAM_WRITE(Output_1, tmp(31,0));
		STREAM_WRITE(Output_1, tmp(63, 32));
		STREAM_WRITE(Output_1, tmp(95, 64));
		STREAM_WRITE(Output_1, tmp(127, 96));
	//}
		i++;
		if(i == MAX_HEIGHT*MAX_WIDTH/2)
		{
			i= 0;
		}
}


