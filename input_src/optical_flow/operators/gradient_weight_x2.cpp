#include "../host/typedefs.h"
void gradient_weight_x2(//gradient_t y_filt[MAX_HEIGHT][MAX_WIDTH],
		       hls::stream<databus_t> &Input_1,
		       hls::stream<databus_t> &Output_1,
		       hls::stream<databus_t> &Output_2)
{
#pragma HLS interface ap_hs port=Input_1
#pragma HLS interface ap_hs port=Output_1
#pragma HLS interface ap_hs port=Output_2
  hls::Window<1,7,gradient_t> buf;
  const pixel_t GRAD_FILTER[] = {0.0755, 0.133, 0.1869, 0.2903, 0.1869, 0.133, 0.0755};
  GRAD_WEIGHT_X_OUTER: for(int r=0; r<MAX_HEIGHT; r++)
  {
    GRAD_WEIGHT_X_INNER: for(int c=0; c<MAX_WIDTH+3; c++)
    {
      #pragma HLS pipeline II=1
      buf.shift_pixels_left();
      gradient_t tmp;
      tmp.y = 0;
      databus_t temp;
      if(c<MAX_WIDTH)
      {
        //tmp = y_filt[r][c];
		temp = Input_1.read();
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
		temp.range(31,0) = acc.y.range(31,0);
		Output_1.write(temp);
		Output_2.write(temp);
      }
      else if(c>=3)
      {
		temp.range(31,0) = acc.y.range(31,0);
		Output_1.write(temp);
		Output_2.write(temp);
      }
    }
  }
}

