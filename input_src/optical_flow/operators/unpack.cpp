#include "../host/typedefs.h"

void unpack(
		hls::stream< bit32 > & Input_1,
		hls::stream< bit32 > & Output_1,
		hls::stream< bit32 > & Output_2
									 )
{
#pragma HLS INTERFACE axis register port=Input_1
#pragma HLS INTERFACE axis register port=Output_1
#pragma HLS INTERFACE axis register port=Output_2
	static int in_cnt=0;
	static int out1_cnt=0;
	static int out2_cnt=0;

	static frames_t buf;
	input_t frame1_a, frame2_a, frame3_a, frame4_a, frame5_a, frame3_b;
	bit32 out_tmp;
	out_tmp = 0;
	FRAMES_CP_OUTER: for (int r=0; r<MAX_HEIGHT; r++)
	  {
#ifdef RISCV1
  print_str("r = ");
  print_dec(r);
  print_str("\n");
#endif

		FRAMES_CP_INNER: for (int c=0; c<MAX_WIDTH; c++)
		{
		  #pragma HLS pipeline II=1

		  // one wide read
		  buf(31,  0) = Input_1.read();
		  //printf("leaf3_in1: %08x\n", (unsigned int) buf(31,  0));
		  buf(63, 32) = Input_1.read();
		  //printf("leaf3_in1: %08x\n", (unsigned int) buf(63, 32));
		  //printf("0x%08x\n",(unsigned int) buf(63, 32));
		  //printf("0x%08x\n",(unsigned int) buf(31,  0));
		  // assign values to the FIFOs


		  //frame1_a = ((input_t)(buf(7 ,  0)) >> 8);
		  out_tmp(7, 0) = buf(7, 0);
		  //printf("leaf3_out1: %08x\n", (unsigned int) out_tmp(31,  0));
		  //printf("%d: %08x\n", out1_cnt++, (unsigned int) out_tmp(31,  0));
		  Output_1.write(out_tmp);


		  //frame2_a = ((input_t)(buf(15,  8)) >> 8);
		  out_tmp(7, 0) = buf(15,  8);
		  //printf("leaf3_out1: %08x\n", (unsigned int) out_tmp(31,  0));
		  //printf("%d: %08x\n", out1_cnt++, (unsigned int) out_tmp(31,  0));
		  Output_1.write(out_tmp);

		  //frame3_b = ((input_t)(buf(23, 16)) >> 8);
		  out_tmp(7, 0) = buf(23, 16);
		  //printf("leaf3_out1: %08x\n", (unsigned int) out_tmp(31,  0));
		  //printf("%d: %08x\n", out1_cnt++, (unsigned int) out_tmp(31,  0));
		  Output_1.write(out_tmp);


		  //frame4_a = ((input_t)(buf(31, 24)) >> 8);
		  out_tmp(7, 0) = buf(31, 24);
		  //printf("leaf3_out1: %08x\n", (unsigned int) out_tmp(31,  0));
		  //printf("%d: %08x\n", out1_cnt++, (unsigned int) out_tmp(31,  0));
		  Output_1.write(out_tmp);


		  //frame5_a = ((input_t)(buf(39, 32)) >> 8);
		  out_tmp(7, 0) = buf(39, 32);
		  //printf("leaf3_out1: %08x\n", (unsigned int) out_tmp(31,  0));
		  //printf("%d: %08x\n", out1_cnt++, (unsigned int) out_tmp(31,  0));
		  Output_1.write(out_tmp);



		  //frame3_a = ((input_t)(buf(23, 16)) >> 8);
		  out_tmp(7, 0) = buf(23, 16);
		  Output_2.write(out_tmp);
		  Output_2.write(out_tmp);
		  Output_2.write(out_tmp);
		  Output_2.write(out_tmp);
		  Output_2.write(out_tmp);
		  //printf("leaf3_out2: %08x\n", (unsigned int) out_tmp(31,  0));
		  //printf("leaf3_out2: %08x\n", (unsigned int) out_tmp(31,  0));
		  //printf("leaf3_out2: %08x\n", (unsigned int) out_tmp(31,  0));
		  //printf("leaf3_out2: %08x\n", (unsigned int) out_tmp(31,  0));
		  //printf("leaf3_out2: %08x\n", (unsigned int) out_tmp(31,  0));




		}
	  }

}
