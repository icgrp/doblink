#include "../host/typedefs.h"

void gradient_xy_calc(
		hls::stream< bit32 > & Input_1,
		hls::stream< bit32 > & Output_1,
		hls::stream< bit32 > & Output_2)
{
#pragma HLS INTERFACE axis register port=Input_1
#pragma HLS INTERFACE axis register port=Output_1
#pragma HLS INTERFACE axis register port=Output_2


  pixel_t gradient_x, gradient_y;
  bit32 out1_tmp, out2_tmp;
  // our own line buffer
  static pixel_t buf[5][MAX_WIDTH+2];
  #pragma HLS array_partition variable=buf complete dim=1

  // small buffer
  pixel_t smallbuf[5];
  #pragma HLS array_partition variable=smallbuf complete dim=0

  // window buffer
  xf::cv::Window<5,5,input_t> window;
  bit32 in_tmp;

  pixel_t GRAD_WEIGHTS[] =  {1,-8,0,8,-1};

  GRAD_XY_OUTER: for(int r=0; r<MAX_HEIGHT+2; r++)
  {
#ifdef RISCV1
  print_str("r = ");
  print_dec(r);
  //print_str(", c = ");
  //print_dec(c);
  print_str("\n");
#endif
    GRAD_XY_INNER: for(int c=0; c<MAX_WIDTH+2; c++)
    {

      #pragma HLS pipeline II=1
      // read out values from current line buffer
      for (int i = 0; i < 4; i ++ )
        smallbuf[i] = buf[i+1][c];
      // the new value is either 0 or read from frame
      if (r<MAX_HEIGHT && c<MAX_WIDTH){
    	  input_t frame;
    	  in_tmp = Input_1.read();
    	  //printf("leaf28_in1: %08x\n", (unsigned int) in_tmp(31, 0));
    	  in_tmp = Input_1.read();
    	  //printf("leaf28_in1: %08x\n", (unsigned int) in_tmp(31, 0));
    	  in_tmp = Input_1.read();
    	  //printf("leaf28_in1: %08x\n", (unsigned int) in_tmp(31, 0));
    	  in_tmp = Input_1.read();
    	  //printf("leaf28_in1: %08x\n", (unsigned int) in_tmp(31, 0));
    	  in_tmp = Input_1.read();
    	  //printf("leaf28_in1: %08x\n", (unsigned int) in_tmp(31, 0));
    	  frame(16, 0) = in_tmp(16, 0);
    	  smallbuf[4] = (pixel_t)(frame);
      } else if (c < MAX_WIDTH)
        smallbuf[4] = 0;
      // update line buffer
      if(r<MAX_HEIGHT && c<MAX_WIDTH)
      {
        for (int i = 0; i < 4; i ++ )
          buf[i][c] = smallbuf[i];
        buf[4][c] = smallbuf[4];
      }
      else if(c<MAX_WIDTH)
      {
        for (int i = 0; i < 4; i ++ )
          buf[i][c] = smallbuf[i];
        buf[4][c] = smallbuf[4];
      }

      // manage window buffer
      if(r<MAX_HEIGHT && c<MAX_WIDTH)
      {
        window.shift_pixels_left();

        for (int i = 0; i < 5; i ++ )
          window.insert_pixel(smallbuf[i],i,4);
      }
      else
      {
        window.shift_pixels_left();
        window.insert_pixel(0,0,4);
        window.insert_pixel(0,1,4);
        window.insert_pixel(0,2,4);
        window.insert_pixel(0,3,4);
        window.insert_pixel(0,4,4);
      }

      // compute gradient
      pixel_t x_grad = 0;
      pixel_t y_grad = 0;
      if(r>=4 && r<MAX_HEIGHT && c>=4 && c<MAX_WIDTH)
      {
        GRAD_XY_XYGRAD: for(int i=0; i<5; i++)
        {
          x_grad = x_grad + window.getval(2,i)*GRAD_WEIGHTS[i];
          y_grad = y_grad + window.getval(i,2)*GRAD_WEIGHTS[i];
        }

        //unsigned int avg_num = 12;
        gradient_x = x_grad/12;
        out1_tmp(31, 0) = gradient_x(31, 0);
        Output_1.write(out1_tmp);
        //printf("leaf28_out1: %08x\n", (unsigned int) out1_tmp(31, 0));
        gradient_y = y_grad/12;
        out2_tmp(31, 0) = gradient_y(31, 0);
        Output_2.write(out2_tmp);
      }
      else if(r>=2 && c>=2)
      {
        gradient_x = 0;
        out1_tmp(31, 0) = gradient_x(31, 0);
        Output_1.write(out1_tmp);
        //printf("leaf28_out1: %08x\n", (unsigned int) out1_tmp(31, 0));
        gradient_y = 0;
        out2_tmp(31, 0) = gradient_y(31, 0);
        Output_2.write(out2_tmp);
      }
    }
  }
}
