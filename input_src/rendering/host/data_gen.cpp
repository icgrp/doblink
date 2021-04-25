#include "typedefs.h"

void data_gen(
		  hls::stream<ap_uint<32> > & Output_1
		)
{
#pragma HLS INTERFACE axis register port=Output_1
#include "../host/input_data.h"
    // create space for input and output
    bit32 input_tmp;
    bit32 input[3 * NUM_3D_TRI];
    bit32 output[NUM_FB];

    // pack input data for better performance
    for ( int i = 0; i < NUM_3D_TRI; i++)
    {
#pragma HLS PIPELINE
        input_tmp(7,   0) = triangle_3ds[i].x0;
        input_tmp(15,  8) = triangle_3ds[i].y0;
        input_tmp(23, 16) = triangle_3ds[i].z0;
        input_tmp(31, 24) = triangle_3ds[i].x1;
        Output_1.write(input_tmp);
        input_tmp(7,   0) = triangle_3ds[i].y1;
        input_tmp(15,  8) = triangle_3ds[i].z1;
        input_tmp(23, 16) = triangle_3ds[i].x2;
        input_tmp(31, 24) = triangle_3ds[i].y2;
        Output_1.write(input_tmp);
        input_tmp(7,   0) = triangle_3ds[i].z2;
        input_tmp(31,  8)  = 0;
        Output_1.write(input_tmp);
    }




}
