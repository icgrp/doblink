#include "../host/typedefs.h"
#ifndef HW
#include "../Overlays/mmu.h"
#endif


// average the gradient in y direction
void gradient_weight_y_3(//pixel_t gradient_x[MAX_HEIGHT][MAX_WIDTH],
#ifdef HW
		hls::stream<ap_uint<32> > & Input_1,
		hls::stream<ap_uint<32> > & Output_1
#else
		pr_flow::stream & Input_1,
		pr_flow::stream & Output_1
#endif
)
{
#pragma HLS interface ap_hs port=Input_1
#pragma HLS interface ap_hs port=Output_1
  hls::LineBuffer<7,MAX_WIDTH,pixel_t> buf;


  const pixel_t GRAD_FILTER[] = {0.0755, 0.133, 0.1869, 0.2903, 0.1869, 0.133, 0.0755};
  static int r = 0;
  static int c = 0;

      #pragma HLS pipeline II=1
      #pragma HLS dependence variable=buf inter false

      if(r<MAX_HEIGHT)
      {
        buf.shift_pixels_up(c);
        pixel_t tmp = 0;
	databus_t temp;
	temp = STREAM_READ(Input_1);
	tmp(31,0) = temp(31,0);
        buf.insert_bottom_row(tmp,c);
      }
      else
      {
        buf.shift_pixels_up(c);
        pixel_t tmp;
        tmp = 0;
        buf.insert_bottom_row(tmp,c);
      }

      pixel_t acc;
      databus_t temp = 0;
      acc = 0;
      if(r >= 6 && r<MAX_HEIGHT)
      {
        GRAD_WEIGHT_Y_ACC: for(int i=0; i<7; i++)
        {
          acc+= buf.getval(i,c)*GRAD_FILTER[i];
        }
        bit32 temp_in;
		temp_in.range(31,0) = acc.range(31,0);
		STREAM_WRITE(Output_1, temp_in);
      }
      else if(r>=3)
      {
    	bit32 temp_in;
		temp_in.range(31,0) = acc.range(31,0);
		STREAM_WRITE(Output_1, temp_in);
      }
      c++;
      if(c==MAX_WIDTH)
      {
    	  c=0;
    	  r++;
    	  if(r==MAX_HEIGHT+3)
    	  {
    		  r=0;
    	  }
      }
}

