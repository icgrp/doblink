#include "../host/typedefs.h"

void page3_16bramI2O2 (
		hls::stream<ap_uint<32> > & Input_1,
		hls::stream<ap_uint<32> > & Output_1
		)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1


	ap_fixed<32, 13> fix_tmp1, fix_tmp2;
	bit32 out;
	//float f_tmp1, f_tmp2;
	int int_tmp1;
	int int_tmp2;
	fload_add_label0:for(int i=0; i<32768; i++){
#ifdef RISCV1
		if((i&0xff)==0){
			print_str("i=");
			print_dec(i);
			print_str("\n");
		}
#endif


#pragma HLS PIPELINE II=1
		out(31, 0) = Input_1.read();
		fix_tmp1(31, 0) = out(31, 0);

		fix_tmp2 = fix_tmp1 * fix_tmp1;

		out(31, 0) = fix_tmp2(31, 0);
		Output_1.write(out);
	}
	return;

}
