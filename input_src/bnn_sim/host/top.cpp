
#include "typedefs.h"
#include "../operators/bc0_gen_0.h"
#include "../operators/bc0_gen_1.h"

#include "../operators/bc1_gen_0.h"
#include "../operators/bc1_gen_1.h"
#include "../operators/bc1_gen_2.h"
#include "../operators/bc1_gen_3.h"
#include "../operators/bc1_gen_4.h"

#include "../operators/bc2_gen_0.h"
#include "../operators/bc2_gen_1.h"
#include "../operators/bc2_gen_2.h"
#include "../operators/bc2_gen_3.h"

#include "../operators/fp_conv.h"

#include "../operators/bin_conv_0.h"
#include "../operators/bin_conv_1.h"
#include "../operators/bin_conv_2.h"
#include "../operators/bin_dense_wrapper.h"

void top(
		hls::stream< bit32 > & Input_1,
		hls::stream< bit32 > & Input_2,
		hls::stream< bit32 > & Output_1
		)
{
	int i, j;

	hls::stream< bit32 > bin_conv_gen0_out1("bin_conv_gen0_out1");
	hls::stream< bit32 > bin_conv_gen1_out1("bin_conv_gen1_out1");
	hls::stream< bit32 > bin_conv_gen2_out1("bin_conv_gen2_out1");
	hls::stream< bit32 > fp_conv_out1("fp_conv_out1");
	hls::stream< bit32 > bin_conv0_out1("bin_conv0_out1");
	hls::stream< bit32 > bc1_gen_0_out1("bc1_gen_0_out1");
	hls::stream< bit32 > bc1_gen_1_out1("bc1_gen_1_out1");
	hls::stream< bit32 > bc1_gen_2_out1("bc1_gen_2_out1");
	hls::stream< bit32 > bc1_gen_3_out1("bc1_gen_3_out1");
	hls::stream< bit32 > bc1_gen_4_out1("bc1_gen_4_out1");
	hls::stream< bit32 > bc1_gen_5_out1("bc1_gen_5_out1");

	hls::stream< bit32 > bin_conv1_out1("bin_conv1_out1");

	hls::stream< bit32 > bc2_gen_0_out1("bc2_gen_0_out1");
	hls::stream< bit32 > bc2_gen_1_out1("bc2_gen_1_out1");
	hls::stream< bit32 > bc2_gen_2_out1("bc2_gen_2_out1");
	hls::stream< bit32 > bc2_gen_3_out1("bc2_gen_3_out1");
	hls::stream< bit32 > bc2_gen_4_out1("bc2_gen_4_out1");

	hls::stream< bit32 > bin_conv2_out1("bin_conv2_out1");







	bc0_gen_0(bin_conv_gen0_out1);
	bc0_gen_1(bin_conv_gen0_out1, bin_conv_gen1_out1);


	bc1_gen_0(bc1_gen_0_out1);
	bc1_gen_1(bc1_gen_0_out1, bc1_gen_1_out1);
	bc1_gen_2(bc1_gen_1_out1, bc1_gen_2_out1);
	bc1_gen_3(bc1_gen_2_out1, bc1_gen_3_out1);
	bc1_gen_4(bc1_gen_3_out1, bc1_gen_4_out1);



	bc2_gen_0(bc2_gen_0_out1);
	bc2_gen_1(bc2_gen_0_out1, bc2_gen_1_out1);
	bc2_gen_2(bc2_gen_1_out1, bc2_gen_2_out1);
	bc2_gen_3(bc2_gen_2_out1, bc2_gen_3_out1);





	fp_conv(Input_1,
			fp_conv_out1
			);


	for(j=0; j<3; j++){
		bin_conv_0(bin_conv_gen1_out1,
				 fp_conv_out1,
				 bin_conv0_out1);
	}

	for(j=0; j<7; j++){
		bin_conv_1(bc1_gen_4_out1,
				bin_conv0_out1,
				 bin_conv1_out1);
	}


	for(j=0; j<6; j++){
		bin_conv_2(bc2_gen_3_out1,
				bin_conv1_out1,
				 bin_conv2_out1);
	}


	for(j=0; j<37; j++){
		bin_dense_wrapper(Input_2,
				  bin_conv2_out1,
				  Output_1);
	}
}
