#include "../host/typedefs.h"
#ifndef HW
#include "../Overlays/mmu.h"
#endif


void gradient_weight_x2(//gradient_t y_filt[MAX_HEIGHT][MAX_WIDTH],
#ifdef HW
		hls::stream<ap_uint<32> > & Input_1,
		hls::stream<ap_uint<32> > & Output_1,
		hls::stream<ap_uint<32> > & Output_2
#else
		pr_flow::stream & Input_1,
		pr_flow::stream & Output_1,
		pr_flow::stream & Output_2
#endif
			   )
{
#pragma HLS interface ap_hs port=Input_1
#pragma HLS interface ap_hs port=Output_1
#pragma HLS interface ap_hs port=Output_2
  hls::Window<1,7,gradient_t> buf;
  const pixel_t GRAD_FILTER[] = {0.0755, 0.133, 0.1869, 0.2903, 0.1869, 0.133, 0.0755};
  static int r = 0;
    static int c = 0;

      #pragma HLS pipeline II=1
      buf.shift_pixels_left();
      gradient_t tmp;
      tmp.y = 0;
      databus_t temp;
      if(c<MAX_WIDTH)
      {
        //tmp = y_filt[r][c];
		temp = STREAM_READ(Input_1);
		tmp.y.range(31,0) = temp.range(31,0);
      }
      else
      {
        tmp.y = 0;
      }
      buf.insert_pixel(tmp,0,6);

      gradient_t acc;
      acc.y = 0;
      if(c >= 6 && c<MAX_WIDTH)
      {
        GRAD_WEIGHT_X_ACC: for(int i=0; i<7; i++)
        {
          acc.y += buf.getval(0,i).y*GRAD_FILTER[i];
        }
        //filt_grad[r][c-3] = acc;
        bit32 temp_in;
		temp_in.range(31,0) = acc.y.range(31,0);
        STREAM_WRITE(Output_1, temp_in);
        STREAM_WRITE(Output_2, temp_in);
      }
      else if(c>=3)
      {
    	bit32 temp_in;
		temp_in.range(31,0) = acc.y.range(31,0);
		STREAM_WRITE(Output_1, temp_in);
		STREAM_WRITE(Output_2, temp_in);
      }
      c++;
	   if(c==MAX_WIDTH+3)
	  {
		c=0;
		r++;
		if(r==MAX_HEIGHT)
		{
			r=0;
		}
	  }
}

