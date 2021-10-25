

#include "../host/typedefs.h"

// outer product
void outer_product(hls::stream< bit32> & Input_1,
		hls::stream< bit32> & Output_1)
{
#pragma HLS INTERFACE axis register port=Input_1
#pragma HLS INTERFACE axis register port=Output_1
  bit32 out_tmp;

  OUTER_OUTER: for(int r=0; r<MAX_HEIGHT; r++)
  {
#ifdef RISCV1
  print_str("r = ");
  print_dec(r);
  //print_str(", c = ");
  //print_dec(c);
  print_str("\n");
#endif
    OUTER_INNER: for(int c=0; c<MAX_WIDTH; c++)
    {
      #pragma HLS pipeline II=1
      gradient_t grad;
      grad.x(31, 0) = Input_1.read();
      grad.y(31, 0) = Input_1.read();
      grad.z(31, 0) = Input_1.read();

      outer_pixel_t x = (outer_pixel_t) grad.x;
      outer_pixel_t y = (outer_pixel_t) grad.y;
      outer_pixel_t z = (outer_pixel_t) grad.z;
      outer_t out;
      out.val[0] = (x*x);
      out.val[1] = (y*y);
      out.val[2] = (z*z);
      out.val[3] = (x*y);
      out.val[4] = (x*z);
      out.val[5] = (y*z);

      out_tmp(31,  0) = out.val[0](31,  0);
      Output_1.write(out_tmp);
      out_tmp(15,  0) = out.val[0](47, 32);
      out_tmp(31, 16) = out.val[1](15,  0);
      Output_1.write(out_tmp);
      out_tmp(31,  0) = out.val[1](47, 16);
      Output_1.write(out_tmp);

      out_tmp(31,  0) = out.val[2](31,  0);
      Output_1.write(out_tmp);
      out_tmp(15,  0) = out.val[2](47, 32);
      out_tmp(31, 16) = out.val[3](15,  0);
      Output_1.write(out_tmp);
      out_tmp(31,  0) = out.val[3](47, 16);
      Output_1.write(out_tmp);

      out_tmp(31,  0) = out.val[4](31,  0);
      Output_1.write(out_tmp);
      out_tmp(15,  0) = out.val[4](47, 32);
      out_tmp(31, 16) = out.val[5](15,  0);
      Output_1.write(out_tmp);
      out_tmp(31,  0) = out.val[5](47, 16);
      Output_1.write(out_tmp);
    }
  }
}
