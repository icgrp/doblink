#include "../host/typedefs.h"
#define HW
void flow_calc_1(
#ifdef HW
		hls::stream<ap_uint<32> > & Input_1,
		hls::stream<ap_uint<32> > & Input_2,
		hls::stream<ap_uint<32> > & Output_1
#else
		pr_flow::stream & Input_1,
		pr_flow::stream & Input_2,
		pr_flow::stream & Output_1
#endif
		)
{
#pragma HLS interface ap_hs port=Input_1
#pragma HLS interface ap_hs port=Output_1
#pragma HLS interface ap_hs port=Input_2
  static float_t buf;

  static int r=0;
  static int c=0;


      #pragma HLS pipeline II=1
      tensor_t tmp_tensor;
      bit160 widetemp;
      widetemp(31,0)= STREAM_READ( Input_1);
      widetemp(63,32)= STREAM_READ( Input_1);
      widetemp(95,64)= STREAM_READ( Input_1);
      widetemp(127,96)= STREAM_READ( Input_1);
      widetemp(159,128)= STREAM_READ( Input_1);
      tmp_tensor.val[0].range(47,0) = widetemp.range(47,0);
      tmp_tensor.val[1].range(47,0) = widetemp.range(95,48);
      tmp_tensor.val[2].range(47,0) = widetemp.range(143,96);

      widetemp(31,0)= STREAM_READ( Input_2);
      widetemp(63,32)=STREAM_READ( Input_2);
      widetemp(95,64)= STREAM_READ( Input_2);
      widetemp(127,96)= STREAM_READ( Input_2);
      widetemp(159,128)= STREAM_READ( Input_2);
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
	      calc_pixel_t numer0 = t6*t4-t5*t2;

	      if(denom != 0)
              {
	          buf =(float) numer0 / (float) denom;
        	  //buf = (ap_fixed<64,56>) numer0 / (ap_fixed<64,56>) denom;
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
      STREAM_WRITE(Output_1, tmpframe);

      c++;
      if(c==MAX_WIDTH)
      {
    	  c=0;
    	  r++;
    	  if(r==MAX_HEIGHT)
    	  {
    		  r=0;
    	  }

      }

}


