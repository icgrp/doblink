/*===============================================================*/
/*                                                               */
/*                        rendering.cpp                          */
/*                                                               */
/*                 C++ kernel for 3D Rendering                   */
/*                                                               */
/*===============================================================*/

#include "../host/typedefs.h"
#include "../operators/shift_data.h"
#include "../operators/to_dma.h"
#include "../operators/float_add.h"

void data_gen(hls::stream<ap_uint<32> > & Output_1){
#pragma HLS INTERFACE ap_hs port=Output_1
	for(int i=0; i<32768; i++){
#pragma HLS PIPELINE II=1
		Output_1.write(i+9);
	}
}

void top (
		  hls::stream<ap_uint<32> > & Input_1,
		  hls::stream<ap_uint<32> > & Output_1
		)

//( bit32 input[3*NUM_3D_TRI], bit32 output[NUM_FB])
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
	hls::stream< ap_uint<32> > shf_out;
	hls::stream< ap_uint<32> > float_out;

	shift_data(Input_1, shf_out);
	float_add(shf_out, float_out);
	to_dma(float_out, Output_1);
}


