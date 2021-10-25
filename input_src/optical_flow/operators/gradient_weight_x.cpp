
#include "../host/typedefs.h"

// average gradient in the x direction
void gradient_weight_x(hls::stream< bit32> & Input_1,
		hls::stream< bit32> & Output_1)
{
#pragma HLS INTERFACE axis register port=Input_1
#pragma HLS INTERFACE axis register port=Output_1


  hls::Window<1,7,gradient_t> buf;
  bit32 out1_tmp;

  const pixel_t GRAD_FILTER[] = {0.0755, 0.133, 0.1869, 0.2903, 0.1869, 0.133, 0.0755};
  GRAD_WEIGHT_X_OUTER: for(int r=0; r<MAX_HEIGHT; r++)
  {
#ifdef RISCV1
  print_str("r = ");
  print_dec(r);
  //print_str(", c = ");
  //print_dec(c);
  print_str("\n");
#endif
    GRAD_WEIGHT_X_INNER: for(int c=0; c<MAX_WIDTH+3; c++)
    {


      #pragma HLS pipeline II=1
      buf.shift_pixels_left();
      gradient_t tmp;
      if(c<MAX_WIDTH)
      {
        //tmp = y_filt[r][c];
        tmp.x(31, 0) = Input_1.read();
        tmp.y(31, 0) = Input_1.read();
        tmp.z(31, 0) = Input_1.read();
      }
      else
      {
        tmp.x = 0;
        tmp.y = 0;
        tmp.z = 0;
      }
      buf.insert_pixel(tmp,0,6);

      gradient_t acc;
      acc.x = 0;
      acc.y = 0;
      acc.z = 0;
      if(c >= 6 && c<MAX_WIDTH)
      {
        GRAD_WEIGHT_X_ACC: for(int i=0; i<7; i++)
        {
          acc.x = acc.x + buf.getval(0,i).x*GRAD_FILTER[i];
          acc.y = acc.y + buf.getval(0,i).y*GRAD_FILTER[i];
          acc.z = acc.z + buf.getval(0,i).z*GRAD_FILTER[i];
        }
        //filt_grad[r][c-3] = acc;
        out1_tmp(31, 0) = acc.x(31, 0);
		Output_1.write(out1_tmp);
		out1_tmp(31, 0) = acc.y(31, 0);
		Output_1.write(out1_tmp);
		out1_tmp(31, 0) = acc.z(31, 0);
		Output_1.write(out1_tmp);
      }
      else if(c>=3)
      {
        //filt_grad[r][c-3] = acc;
        out1_tmp(31, 0) = acc.x(31, 0);
		Output_1.write(out1_tmp);
		out1_tmp(31, 0) = acc.y(31, 0);
		Output_1.write(out1_tmp);
		out1_tmp(31, 0) = acc.z(31, 0);
		Output_1.write(out1_tmp);
      }
    }
  }
}
