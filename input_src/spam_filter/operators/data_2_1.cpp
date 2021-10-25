#include "../host/typedefs.h"
void data_2_1(
			hls::stream<ap_uint<32> > & Input_1,
			hls::stream<ap_uint<32> > & Input_2,
			hls::stream<ap_uint<32> > & Output_1
			)
{
#pragma HLS INTERFACE axis register port=Input_1
#pragma HLS INTERFACE axis register port=Input_2
#pragma HLS INTERFACE axis register port=Output_1


	static unsigned int theta[NUM_FEATURES / F_VECTOR_SIZE * 2];

	  STREAM_IN_1: for (int i = 0; i < NUM_FEATURES / F_VECTOR_SIZE; i ++ )
	  {
#ifdef RISCV1
	  print_str("i1=");
	  print_dec(i);
	  print_str("\n");
#endif
	    #pragma HLS pipeline II=1
		theta[i] = Input_1.read();
	  }
	  STREAM_IN_2: for (int i = 0; i < NUM_FEATURES / F_VECTOR_SIZE; i ++ )
	  {
#ifdef RISCV1
	  print_str("i2=");
	  print_dec(i);
	  print_str("\n");
#endif
	    #pragma HLS pipeline II=1
		theta[i+NUM_FEATURES / F_VECTOR_SIZE] = Input_2.read();
	  }

	  //Output_1.write(1025);

	  STREAM_OUT: for (int i = 0; i < NUM_FEATURES / F_VECTOR_SIZE*2/4; i ++ )
	  {
#ifdef RISCV1
	  print_str("i3=");
	  print_dec(i);
	  print_str("\n");
#endif
	    #pragma HLS pipeline II=1
		ap_uint<32> Output_tmp;
		Output_tmp(31, 0) = theta[4*i];
		Output_1.write(Output_tmp);
                // printf("out:  %08x\n", Output_tmp.to_int());
		Output_tmp(31, 0) = theta[4*i+1];
		Output_1.write(Output_tmp);
                // printf("out:  %08x\n", Output_tmp.to_int());
		Output_tmp(31, 0) = theta[4*i+2];
		Output_1.write(Output_tmp);
                // printf("out:  %08x\n", Output_tmp.to_int());
		Output_tmp(31, 0) = theta[4*i+3];
		Output_1.write(Output_tmp);
                // printf("out:  %08x\n", Output_tmp.to_int());
	  }
}

