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
#include "../operators/update_knn6.h"
#include "../operators/update_knn7.h"
#include "../operators/update_knn8.h"
#include "../operators/update_knn9.h"
#include "../operators/update_knn10.h"

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

	hls::stream<ap_uint<32> > knn_out1("knn_out1");
	hls::stream<ap_uint<32> > knn_out2("knn_out2");
	hls::stream<ap_uint<32> > knn_out3("knn_out3");
	hls::stream<ap_uint<32> > knn_out4("knn_out4");
	hls::stream<ap_uint<32> > knn_out5("knn_out5");
	hls::stream<ap_uint<32> > knn_out6("knn_out6");
	hls::stream<ap_uint<32> > knn_out7("knn_out7");
	hls::stream<ap_uint<32> > knn_out8("knn_out8");
	hls::stream<ap_uint<32> > knn_out9("knn_out9");
	hls::stream<ap_uint<32> > knn_out10("knn_out10");
	hls::stream<ap_uint<32> > knn_out11("knn_out11");
	hls::stream<ap_uint<32> > knn_out12("knn_out12");
	hls::stream<ap_uint<32> > knn_out13("knn_out13");
	hls::stream<ap_uint<32> > knn_out14("knn_out14");
	hls::stream<ap_uint<32> > knn_out15("knn_out15");
	hls::stream<ap_uint<32> > knn_out16("knn_out16");
	hls::stream<ap_uint<32> > knn_out17("knn_out17");
	hls::stream<ap_uint<32> > knn_out18("knn_out18");
	hls::stream<ap_uint<32> > knn_out19("knn_out19");
	hls::stream<ap_uint<32> > knn_out20("knn_out20");




	for(int i=0; i<2000; i++)
	{

		//printf("i=%d\n", i);
		update_knn1(Input_1, knn_out1);
		update_knn2(knn_out1, knn_out2);
		update_knn3(knn_out2, knn_out3);
		update_knn4(knn_out3, knn_out4);
		update_knn5(knn_out4, knn_out5);
		update_knn6(knn_out5, knn_out6);
		update_knn7(knn_out6, knn_out7);
		update_knn8(knn_out7, knn_out8);
		update_knn9(knn_out8, knn_out9);
		update_knn10(knn_out9, Output_1);
	}

	printf("We can run without hanging\n");

}


