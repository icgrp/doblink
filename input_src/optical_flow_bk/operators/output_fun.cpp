#include "../host/typedefs.h"
void output_fun(hls::stream<stdio_t> &Input_1,
		hls::stream<stdio_t> &Input_2,
		hls::stream< ap_uint<32> > &Output_1)
{
#pragma HLS interface axis register port=Input_1
#pragma HLS interface axis register port=Output_1
#pragma HLS interface axis register port=Input_2
	//while (Input_1.empty());

	OUT_CONVERT: for (int i = 0; i < MAX_HEIGHT*MAX_WIDTH/2; i++)
	{
#ifdef RISCV1
	if((i & 0x000003ff) == 0){
	  print_str("i=");
	  print_dec(i);
	  print_str("\n");
	}
#endif
	  stdio_t tmpframe;
		#pragma HLS pipeline II = 4
	  tmpframe = Input_1.read();
	  Output_1.write(tmpframe);
	  tmpframe = Input_2.read();
	  Output_1.write(tmpframe);
	  tmpframe = Input_1.read();
	  Output_1.write(tmpframe);
	  tmpframe = Input_2.read();
	  Output_1.write(tmpframe);
	}
}


