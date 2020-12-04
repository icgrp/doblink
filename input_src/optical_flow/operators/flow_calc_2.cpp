#include "../host/typedefs.h"
void flow_calc_2(
		hls::stream<stdio_t> &Input_1,
		hls::stream<stdio_t> &Input_2,
		hls::stream<stdio_t> &Output_1)
{
#pragma HLS interface ap_hs port=Input_1
#pragma HLS interface ap_hs port=Output_1
#pragma HLS interface ap_hs port=Input_2
  static float buf;
  FLOW_OUTER: for(int r=0; r<MAX_HEIGHT; r++)
  {
    FLOW_INNER: for(int c=0; c<MAX_WIDTH; c++)
    {
      #pragma HLS pipeline II=1
      tensor_t tmp_tensor;
      bit160 widetemp;
      widetemp(31,0)= Input_1.read();
      widetemp(63,32)= Input_1.read();
      widetemp(95,64)= Input_1.read();
      widetemp(127,96)= Input_1.read();
      widetemp(159,128)= Input_1.read();
      tmp_tensor.val[0].range(47,0) = widetemp.range(47,0);
      tmp_tensor.val[1].range(47,0) = widetemp.range(95,48);
      tmp_tensor.val[2].range(47,0) = widetemp.range(143,96);

      widetemp(31,0)= Input_2.read();
      widetemp(63,32)= Input_2.read();
      widetemp(95,64)= Input_2.read();
      widetemp(127,96)= Input_2.read();
      widetemp(159,128)= Input_2.read();
      tmp_tensor.val[3].range(47,0) = widetemp.range(47,0);
      tmp_tensor.val[4].range(47,0) = widetemp.range(95,48);
      tmp_tensor.val[5].range(47,0) = widetemp.range(143,96);

      if(r>=2 && r<MAX_HEIGHT-2 && c>=2 && c<MAX_WIDTH-2)
      {
	      calc_pixel_t t1 = (calc_pixel_t) tmp_tensor.val[0];
	      calc_pixel_t t2 = (calc_pixel_t) tmp_tensor.val[1];
	      calc_pixel_t t4 = (calc_pixel_t) tmp_tensor.val[2];
	      calc_pixel_t t5 = (calc_pixel_t) tmp_tensor.val[4];
	      calc_pixel_t t6 = (calc_pixel_t) tmp_tensor.val[5];
	      calc_pixel_t denom = t1*t2-t4*t4;
	      calc_pixel_t numer1 = t5*t4-t6*t1;

	      if(denom != 0)
              {
        	  buf = (float) numer1 / (float) denom;
        	  //buf = (ap_fixed<64,56>) numer1 / (ap_fixed<64,56>) denom;
	      }
	      else
	      {
		      buf = 0;
	      }
      }
      else
      {
        buf = 0;
      }
      stdio_t tmpframe;
      vel_pixel_t tmpvel;
      tmpvel = (vel_pixel_t)buf;
      tmpframe(31,0) = tmpvel(31,0);
      Output_1.write(tmpframe);
    }
  }
}


