#include "../host/typedefs.h"
// tensor weight
void tensor_weight_y1(
		hls::stream<databus_t> &Input_1,
		hls::stream<databus_t> &Output_1)
{
#pragma HLS interface ap_hs port=Input_1
#pragma HLS interface ap_hs port=Output_1
  hls::LineBuffer<3,MAX_WIDTH,outer_half_t> buf;
  const pixel_t TENSOR_FILTER[] = {0.3243, 0.3513, 0.3243};
  TENSOR_WEIGHT_Y_OUTER: for(int r=0; r<MAX_HEIGHT+1; r++)
  {
    TENSOR_WEIGHT_Y_INNER: for(int c=0; c<MAX_WIDTH; c++)
    {
      #pragma HLS pipeline II=1

      outer_half_t tmp;
      #pragma HLS data_pack variable=tmp
      #pragma HLS data_pack variable=buf.val[0]
      buf.shift_pixels_up(c);
      if(r<MAX_HEIGHT)
      {
        bit160 widetemp;
        widetemp(31,0) = Input_1.read();
        widetemp(63,32) = Input_1.read();
        widetemp(95,64) = Input_1.read();
        widetemp(127,96) = Input_1.read();
        widetemp(159,128) = Input_1.read();

        tmp.val[0].range(47,0) = widetemp.range(47,0);
        tmp.val[1].range(47,0) = widetemp.range(95,48);
        tmp.val[2].range(47,0) = widetemp.range(143,96);
      }
      else
      {
        TENSOR_WEIGHT_Y_TMP_INIT: for(int i=0; i<3; i++)
          tmp.val[i] = 0;
      }
      buf.insert_bottom_row(tmp,c);

      tensor_half_t acc;
      TENSOR_WEIGHT_Y_ACC_INIT: for(int k =0; k<3; k++)
        acc.val[k] = 0;

      if (r >= 2 && r < MAX_HEIGHT)
      {
        TENSOR_WEIGHT_Y_TMP_OUTER: for(int i=0; i<3; i++)
        {
          tmp = buf.getval(i,c);
          pixel_t k = TENSOR_FILTER[i];
          TENSOR_WEIGHT_Y_TMP_INNER: for(int component=0; component<3; component++)
          {
            acc.val[component] += tmp.val[component]*k;
          }
        }
      }
      if(r >= 1)
      {
      	bit160 widetemp;
        widetemp.range(47,0) = acc.val[0].range(47,0);
        widetemp.range(95,48) = acc.val[1].range(47,0);
        widetemp.range(143,96) = acc.val[2].range(47,0);
        widetemp.range(159,144) = 0;
        Output_1.write(widetemp(31,0));
        Output_1.write(widetemp(63,32));
        Output_1.write(widetemp(95,64));
        Output_1.write(widetemp(127,96));
        Output_1.write(widetemp(159,128));
      }
    }
  }
}

