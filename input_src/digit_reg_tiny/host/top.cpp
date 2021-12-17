/*                                                               */
/*                          digitrec.cpp                         */
/*                                                               */
/*             Hardware function for digit recognition           */
/*                                                               */
/*===============================================================*/

#include "../host/typedefs.h"
#include "../operators/update_knn1.h"
#include "../operators/update_knn2.h"
#include "../operators/update_knn3.h"
#include "../operators/update_knn4.h"
#include "../operators/update_knn5.h"

void data_gen(
		  hls::stream<ap_uint<32> > & Output_1
		)

//( bit32 input[3*NUM_3D_TRI], bit32 output[NUM_FB])
{
#pragma HLS INTERFACE ap_hs port=Output_1
#include "../host/input1.h"

    // pack input data for better performance
    for ( int i = 0; i < 88000; i++)
    {
#pragma HLS PIPELINE
        Output_1.write(input1[i]);
    }
}

void top(hls::stream<ap_uint<32> > & Input_1, hls::stream<ap_uint<32> > & Output_1)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1

	bit128 input_tmp1, input_tmp2;
	int min_distance_list[3];
	int  label_list[3];

	hls::stream<ap_uint<32> > knn_out2("knn_out2");
	hls::stream<ap_uint<32> > knn_out4("knn_out4");
	hls::stream<ap_uint<32> > knn_out6("knn_out6");
	hls::stream<ap_uint<32> > knn_out8("knn_out8");
	hls::stream<ap_uint<32> > knn_out9("knn_out9");
	




	for(int i=0; i<2000; i++)
	{

		//printf("i=%d\n", i);
		update_knn1(Input_1, knn_out2);
		update_knn2(knn_out2, knn_out4);
		update_knn3(knn_out4, knn_out6);
		update_knn4(knn_out6, knn_out8);
		update_knn5(knn_out8, Output_1);
	}

	printf("We can run without hanging\n");

}


