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
#include "../operators/update_knn11.h"
#include "../operators/update_knn12.h"
#include "../operators/update_knn13.h"
#include "../operators/update_knn14.h"
#include "../operators/update_knn15.h"
#include "../operators/update_knn16.h"
#include "../operators/update_knn17.h"
#include "../operators/update_knn18.h"
#include "../operators/update_knn19.h"
#include "../operators/update_knn20.h"

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
		update_knn10(knn_out9, knn_out10);
		update_knn11(knn_out10, knn_out11);
		update_knn12(knn_out11, knn_out12);
		update_knn13(knn_out12, knn_out13);
		update_knn14(knn_out13, knn_out14);
		update_knn15(knn_out14, knn_out15);
		update_knn16(knn_out15, knn_out16);
		update_knn17(knn_out16, knn_out17);
		update_knn18(knn_out17, knn_out18);
		update_knn19(knn_out18, knn_out19);
		update_knn20(knn_out19, Output_1);
	}

	printf("We can run without hanging\n");

}


