#include "../host/typedefs.h"
void outer_product2(//gradient_t gradient[MAX_HEIGHT][MAX_WIDTH],
    		       hls::stream<databus_t> &Input_1,
		       hls::stream<databus_t> &Input_2,
		       hls::stream<databus_t> &Input_3,
		   hls::stream<databus_t> &Output_1
			)

{
#pragma HLS interface ap_hs port=Input_1
#pragma HLS interface ap_hs port=Input_2
#pragma HLS interface ap_hs port=Input_3
#pragma HLS interface ap_hs port=Output_1
  OUTER_OUTER: for(int r=0; r<MAX_HEIGHT; r++)
  {
    OUTER_INNER: for(int c=0; c<MAX_WIDTH; c++)
    {
      #pragma HLS pipeline II=1
      //gradient_t grad = gradient[r][c];
      gradient_t grad;
      databus_t temp_x,temp_y,temp_z;
      temp_x = Input_1.read();
      temp_y = Input_2.read();
      temp_z = Input_3.read();
      grad.x.range(31,0) = temp_x.range(31,0);
      grad.y.range(31,0) = temp_y.range(31,0);
      grad.z.range(31,0) = temp_z.range(31,0);
      outer_pixel_t x = (outer_pixel_t) grad.x;
      outer_pixel_t y = (outer_pixel_t) grad.y;
      outer_pixel_t z = (outer_pixel_t) grad.z;
      outer_t out;
      out.val[3] = (z*z);
      out.val[4] = (x*z);
      out.val[5] = (y*z);
      //Output_1[r][c] = out;
      widebus_t widetemp;
      widetemp.range(47,0) = out.val[3].range(47,0);
      widetemp.range(95,48) = out.val[4].range(47,0);
      widetemp.range(143,96) = out.val[5].range(47,0);
      widetemp.range(287,144) = 0;
      //Output_1.write(widetemp);

      bit160 out_tmp;
      out_tmp(159,0) = widetemp.range(159,0);
      Output_1.write(out_tmp(31,0));
      Output_1.write(out_tmp(63,32));
      Output_1.write(out_tmp(95,64));
      Output_1.write(out_tmp(127,96));
      Output_1.write(out_tmp(159,128));
    }
  }
}

