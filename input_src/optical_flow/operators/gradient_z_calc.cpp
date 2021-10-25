#include "../host/typedefs.h"


// calculate gradient in the z direction
void gradient_z_calc(
	hls::stream< bit32 > & Input_1,
	hls::stream< bit32 > & Output_1
	)
{
#pragma HLS INTERFACE axis register port=Input_1
#pragma HLS INTERFACE axis register port=Output_1

	input_t frame1, frame2, frame3, frame4, frame5;
	bit32 in1_tmp, in2_tmp, in3_tmp, in4_tmp, in5_tmp;
	pixel_t gradient_z;
	bit32 out_tmp;

#ifdef RISCV
	hls::stream_local< bit32 > gradient_z_buffer;
#else
	hls::stream<bit32> gradient_z_buffer;
	#pragma HLS STREAM variable=gradient_z_buffer depth=3*MAX_WIDTH
#endif

  input_t GRAD_WEIGHTS[] =  {1,-8,0,8,-1};
  GRAD_Z_OUTER: for(int r=0; r<MAX_HEIGHT+2; r++)
  {
#ifdef RISCV1
  print_str("r = ");
  print_dec(r);
  //print_str(", c = ");
  //print_dec(c);
  print_str("\n");
#endif
    GRAD_Z_INNER: for(int c=0; c<MAX_WIDTH+2; c++)
    {
      if(r<MAX_HEIGHT && c<MAX_WIDTH){
		  #pragma HLS pipeline II=1
		  in1_tmp = Input_1.read();
		  frame1(16, 0) = in1_tmp(16, 0);
		  in2_tmp = Input_1.read();
		  frame2(16, 0) = in2_tmp(16, 0);
		  in3_tmp = Input_1.read();
		  frame3(16, 0) = in3_tmp(16, 0);
		  in4_tmp = Input_1.read();
		  frame4(16, 0) = in4_tmp(16, 0);
		  in5_tmp = Input_1.read();
		  frame5(16, 0) = in5_tmp(16, 0);
		  gradient_z =((pixel_t)(frame1*GRAD_WEIGHTS[0]
							+ frame2*GRAD_WEIGHTS[1]
							+ frame3*GRAD_WEIGHTS[2]
							+ frame4*GRAD_WEIGHTS[3]
							+ frame5*GRAD_WEIGHTS[4]))/12;
		  out_tmp(31, 0) = gradient_z(31, 0);
		  gradient_z_buffer.write(out_tmp);
      }

      if(r>=2 && c>=2){
    	  out_tmp = gradient_z_buffer.read();
    	  Output_1.write(out_tmp);
      }

    }
  }
}
