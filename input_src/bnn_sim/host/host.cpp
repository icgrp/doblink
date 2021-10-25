#include "stdio.h"
#include "label.h"
#include "typedefs.h"


#include "data_in_gen_0.h"
#include "data_in_gen_1.h"
#include "data_in_gen_2.h"
#include "data_in_gen_3.h"
#include "data_in_gen_4.h"
#include "top.h"
#include "../host/bd_gen_0.h"
#include "../host/bd_gen_1.h"
#include "../host/bd_gen_2.h"
#include "../host/bd_gen_3.h"
#include "../host/bd_gen_4.h"
#include "../host/bd_gen_5.h"
#include "../host/bd_gen_6.h"
#include "../host/bd_gen_7.h"
#include "../host/bd_gen_8.h"


int main(int argc, char** argv) {
	hls::stream< Word > data_gen_out0("data_gen_out0");
	hls::stream< Word > data_gen_out1("data_gen_out1");
	hls::stream< Word > data_gen_out2("data_gen_out2");
	hls::stream< Word > data_gen_out3("data_gen_out3");
	hls::stream< bit32 > data_gen_out4("data_gen_out4");

	hls::stream< bit32 > bd_gen_0_out1("bd_gen_0_out1");
	hls::stream< bit32 > bd_gen_1_out1("bd_gen_1_out1");
	hls::stream< bit32 > bd_gen_2_out1("bd_gen_2_out1");
	hls::stream< bit32 > bd_gen_3_out1("bd_gen_3_out1");
	hls::stream< bit32 > bd_gen_4_out1("bd_gen_4_out1");
	hls::stream< bit32 > bd_gen_5_out1("bd_gen_5_out1");
	hls::stream< bit32 > bd_gen_6_out1("bd_gen_6_out1");
	hls::stream< bit32 > bd_gen_7_out1("bd_gen_7_out1");
	hls::stream< bit32 > bd_gen_8_out1("bd_gen_8_out1");


	hls::stream< bit32 > bin_dense_out1("bin_dense_out1");

	Word dmem_o[2*2*64];
	int i, j;
	int err_cnt = 0;
	unsigned N_IMG;
	if (argc < 2) {
		printf ("We will use default N_IMG = 1\n");
		N_IMG  = 1;
	}else{
		N_IMG  = std::stoi(argv[1]);
	}

	printf("Hello world\n");


	data_in_gen_0(data_gen_out0);
	data_in_gen_1(data_gen_out0, data_gen_out1);
	data_in_gen_2(data_gen_out1, data_gen_out2);
	data_in_gen_3(data_gen_out2, data_gen_out3);
	data_in_gen_4(N_IMG, data_gen_out3, data_gen_out4);


	for(i=0; i<N_IMG; i++)
	{
		printf("We are processing %d images\n", i);

		bd_gen_0(bd_gen_0_out1);
		bd_gen_1(bd_gen_0_out1, bd_gen_1_out1);
		bd_gen_2(bd_gen_1_out1, bd_gen_2_out1);
		bd_gen_3(bd_gen_2_out1, bd_gen_3_out1);
		bd_gen_4(bd_gen_3_out1, bd_gen_4_out1);
		bd_gen_5(bd_gen_4_out1, bd_gen_5_out1);
		bd_gen_6(bd_gen_5_out1, bd_gen_6_out1);
		bd_gen_7(bd_gen_6_out1, bd_gen_7_out1);
		bd_gen_8(bd_gen_7_out1, bd_gen_8_out1);


		top(data_gen_out4,
			bd_gen_8_out1,
			bin_dense_out1);



		for(j=0; j<2*2*64; j++)
		{
			dmem_o[j](63, 32) = bin_dense_out1.read();
			dmem_o[j](31,  0) = bin_dense_out1.read();
		}

		int recv_cnt = 0;
		recv_cnt = (int) dmem_o[0](31,0);

		printf("We will receive %d\n", recv_cnt);

		ap_int<8> p = 0;
        p(7,0) = dmem_o[1](7,0);

        int prediction = p.to_int();
        if(prediction == y[i]){
        	printf("Pred/Label: %d/%d [ OK ]\n", prediction, y[i]);
        }else{
        	printf("Pred/Label: %d/%d [FAIL]\n", prediction, y[i]);
        	err_cnt++;
        }


	}

	printf("We got %d/%d errors\nDone\n", err_cnt, N_IMG);

	return 0;
}
