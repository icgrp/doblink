#include "../host/typedefs.h"
#ifndef HW
#include "../Overlays/mmu.h"
#endif


void tensor_weight_x1(
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
  hls::Window<1,3,tensor_half_t> buf;
  const pixel_t TENSOR_FILTER[] = {0.3243, 0.3513, 0.3243};
  static int r=0;
  static int c=0;

      #pragma HLS pipeline II=1
      buf.shift_pixels_left();
      tensor_half_t tmp;
      if(c<MAX_WIDTH)
      {
        //widebus_t widetemp = Input_1.read();
    	bit160 widetemp;
    	widetemp(31,0)=STREAM_READ( Input_1);
    	widetemp(63,32)=STREAM_READ( Input_1);
    	widetemp(95,64)=STREAM_READ( Input_1);
    	widetemp(127,96)=STREAM_READ( Input_1);
    	widetemp(159,128)=STREAM_READ( Input_1);
        tmp.val[0].range(47,0) = widetemp.range(47,0);
        tmp.val[1].range(47,0) = widetemp.range(95,48);
        tmp.val[2].range(47,0) = widetemp.range(143,96);
      }
      else
      {
        TENSOR_WEIGHT_X_TMP_INIT: for(int i=0; i<3; i++)
          tmp.val[i] = 0;
      }
      buf.insert_pixel(tmp,0,2);

      tensor_half_t acc;
      TENSOR_WEIGHT_X_ACC_INIT: for(int k =0; k<3; k++)
        acc.val[k] = 0;
      if (c >= 2 && c < MAX_WIDTH)
      {
        TENSOR_WEIGHT_X_TMP_OUTER: for(int i=0; i<3; i++)
        {
          tmp = buf.getval(0,i);
          TENSOR_WEIGHT_X_TMP_INNER: for(int component=0; component<3; component++)
          {
            acc.val[component] += tmp.val[component]*TENSOR_FILTER[i];
          }
        }
      }
      if(c>=1)
      {
      	bit160 widetemp;
        widetemp.range(47,0) = acc.val[0].range(47,0);
        widetemp.range(95,48) = acc.val[1].range(47,0);
        widetemp.range(143,96) = acc.val[2].range(47,0);
        widetemp.range(159,144) = 0;
        STREAM_WRITE(Output_1, widetemp(31,0));
        STREAM_WRITE(Output_1, widetemp(63,32));
        STREAM_WRITE(Output_1, widetemp(95,64));
        STREAM_WRITE(Output_1, widetemp(127,96));
        STREAM_WRITE(Output_1, widetemp(159,128));
        STREAM_WRITE(Output_2, widetemp(31,0));
        STREAM_WRITE(Output_2, widetemp(63,32));
        STREAM_WRITE(Output_2, widetemp(95,64));
        STREAM_WRITE(Output_2, widetemp(127,96));
        STREAM_WRITE(Output_2, widetemp(159,128));
      }
      c++;
	if(c==MAX_WIDTH+1)
	{
	  c=0;
	  r++;
	  if(r==MAX_HEIGHT)
	  {
		  r=0;
	  }

	}
}

