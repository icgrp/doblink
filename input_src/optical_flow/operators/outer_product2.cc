#include "../host/typedefs.h"
#ifndef HW
#include "../Overlays/mmu.h"
#endif


void outer_product2(//gradient_t gradient[MAX_HEIGHT][MAX_WIDTH],
#ifdef HW
		hls::stream<ap_uint<32> > & Input_1,
		hls::stream<ap_uint<32> > & Input_2,
		hls::stream<ap_uint<32> > & Input_3,
		hls::stream<ap_uint<32> > & Output_1
#else
		pr_flow::stream & Input_1,
		pr_flow::stream & Input_2,
		pr_flow::stream & Input_3,
		pr_flow::stream & Output_1
#endif
			)

{
#pragma HLS interface ap_hs port=Input_1
#pragma HLS interface ap_hs port=Input_2
#pragma HLS interface ap_hs port=Input_3
#pragma HLS interface ap_hs port=Output_1
	 static int r=0;
	  static int c=0;

      #pragma HLS pipeline II=1
      //gradient_t grad = gradient[r][c];
      gradient_t grad;
      databus_t temp_x,temp_y,temp_z;
      temp_x =STREAM_READ( Input_1);
      temp_y =STREAM_READ( Input_2);
      temp_z =STREAM_READ( Input_3);
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
      STREAM_WRITE(Output_1, out_tmp(31,0));
      STREAM_WRITE(Output_1, out_tmp(63,32));
      STREAM_WRITE(Output_1, out_tmp(95,64));
      STREAM_WRITE(Output_1, out_tmp(127,96));
      STREAM_WRITE(Output_1, out_tmp(159,128));
      c++;
	if(c==MAX_WIDTH)
	{
	  c=0;
	  r++;
	  if(r==MAX_HEIGHT+1)
	  {
		  r=0;
	  }

	}
}


