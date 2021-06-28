#include "../host/typedefs.h"


// average the gradient in y direction
void gradient_weight_y(
		hls::stream< bit32> & Input_1,
		hls::stream< bit32> & Input_2,
		hls::stream< bit32> & Input_3,
		hls::stream< bit32> & Output_1)
{
#pragma HLS INTERFACE axis register port=Input_1
#pragma HLS INTERFACE axis register port=Input_2
#pragma HLS INTERFACE axis register port=Input_3
#pragma HLS INTERFACE axis register port=Output_1

  static int out1_cnt = 0;
  hls::LineBuffer<7,MAX_WIDTH,gradient_t> buf;

  bit32 out1_tmp, out2_tmp, out3_tmp;

  const pixel_t GRAD_FILTER[] = {0.0755, 0.133, 0.1869, 0.2903, 0.1869, 0.133, 0.0755};
  GRAD_WEIGHT_Y_OUTER: for(int r=0; r<MAX_HEIGHT+3; r++)
  {
#ifdef RISCV1
  print_str("r = ");
  print_dec(r);
  //print_str(", c = ");
  //print_dec(c);
  print_str("\n");
#endif
    GRAD_WEIGHT_Y_INNER: for(int c=0; c<MAX_WIDTH; c++)
    {
      #pragma HLS pipeline II=1
      #pragma HLS dependence variable=buf inter false

      if(r<MAX_HEIGHT)
      {
        buf.shift_pixels_up(c);
        gradient_t tmp;
        tmp.x(31, 0) = Input_1.read();
        //printf("leaf28_in1: %08x\n", (unsigned int) tmp.x(31, 0));
        tmp.y(31, 0) = Input_2.read();
        tmp.z(31, 0) = Input_3.read();
        buf.insert_bottom_row(tmp,c);
      }
      else
      {
        buf.shift_pixels_up(c);
        gradient_t tmp;
        tmp.x = 0;
        tmp.y = 0;
        tmp.z = 0;
        buf.insert_bottom_row(tmp,c);
      }

      gradient_t acc;
      acc.x = 0;
      acc.y = 0;
      acc.z = 0;
      if(r >= 6 && r<MAX_HEIGHT)
      {
        GRAD_WEIGHT_Y_ACC: for(int i=0; i<7; i++)
        {
          acc.x = acc.x + buf.getval(i,c).x*GRAD_FILTER[i];
          acc.y = acc.y + buf.getval(i,c).y*GRAD_FILTER[i];
          acc.z = acc.z + buf.getval(i,c).z*GRAD_FILTER[i];
        }
        out1_tmp(31, 0) = acc.x(31, 0);
        //printf("%d: %08x\n", out1_cnt++, (unsigned int) out1_tmp(31,  0));
        Output_1.write(out1_tmp);
        out1_tmp(31, 0) = acc.y(31, 0);
        //printf("%d: %08x\n", out1_cnt++, (unsigned int) out1_tmp(31,  0));
        Output_1.write(out1_tmp);
        out1_tmp(31, 0) = acc.z(31, 0);
        //printf("%d: %08x\n", out1_cnt++, (unsigned int) out1_tmp(31,  0));
        Output_1.write(out1_tmp);

        //filt_grad[r-3][c] = acc;

      }
      else if(r>=3)
      {
        //filt_grad[r-3][c] = acc;
        out1_tmp(31, 0) = acc.x(31, 0);
        //printf("%d: %08x\n", out1_cnt++, (unsigned int) out1_tmp(31,  0));
        Output_1.write(out1_tmp);
        out1_tmp(31, 0) = acc.y(31, 0);
        //printf("%d: %08x\n", out1_cnt++, (unsigned int) out1_tmp(31,  0));
        Output_1.write(out1_tmp);
        out1_tmp(31, 0) = acc.z(31, 0);
        //printf("%d: %08x\n", out1_cnt++, (unsigned int) out1_tmp(31,  0));
        Output_1.write(out1_tmp);

      }
    }
  }
}
