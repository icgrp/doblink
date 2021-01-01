#include "../host/typedefs.h"

void shift_data (
		hls::stream<ap_uint<32> > & Input_1,
		hls::stream<ap_uint<32> > & Output_1
		)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1

  bit32 input_lo;
  bit32 input_mi;
  bit32 input_hi;

  hls::stream<ap_uint<32> > Output_1_1;
  hls::stream<ap_uint<32> > Output_2_2;
  Triangle_2D triangle_2ds_1;
  Triangle_2D triangle_2ds_2;

  input_lo = Input_1.read();
  input_mi = Input_1.read();
  input_hi = Input_1.read();

  



}

