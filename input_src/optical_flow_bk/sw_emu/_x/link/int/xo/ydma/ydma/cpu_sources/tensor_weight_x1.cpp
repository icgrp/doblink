#include "../host/typedefs.h"
void tensor_weight_x1(hls::stream<databus_t> &Input_1,
		     hls::stream<databus_t> &Output_1,
		     hls::stream<databus_t> &Output_2)
{
#pragma HLS interface axis register port=Input_1
#pragma HLS interface axis register port=Output_1
#pragma HLS interface axis register port=Output_2
  xf::cv::Window<1,3,tensor_half_t> buf;
  const pixel_t TENSOR_FILTER[] = {0.3243, 0.3513, 0.3243};
  TENSOR_WEIGHT_X_OUTER: for(int r=0; r<MAX_HEIGHT; r++)
  {
#ifdef RISCV
	  print_str("r=");
	  print_dec(r);
	  print_str("\n");
#endif
    TENSOR_WEIGHT_X_INNER: for(int c=0; c<MAX_WIDTH+1; c++)
    {
      #pragma HLS pipeline II=1
      buf.shift_pixels_left();
      tensor_half_t tmp;
      if(c<MAX_WIDTH)
      {
        //widebus_t widetemp = Input_1.read();
    	databus_t widetemp1, widetemp2, widetemp3, widetemp4, widetemp5;
    	widetemp1(31,0)= Input_1.read();
    	widetemp2(31,0)= Input_1.read();
    	widetemp3(31,0)= Input_1.read();
    	widetemp4(31,0)= Input_1.read();
    	widetemp5(31,0)= Input_1.read();
        tmp.val[0](31, 0) = widetemp1(31, 0);
        tmp.val[0](47,32) = widetemp2(15, 0);
        tmp.val[1](15, 0) = widetemp2(31,16);
        tmp.val[1](47,16) = widetemp3(31, 0);
        tmp.val[2](31, 0) = widetemp4(31, 0);
        tmp.val[2](47,32) = widetemp5(15, 0);
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
            acc.val[component] = acc.val[component] + tmp.val[component]*TENSOR_FILTER[i];
          }
        }
      }
      if(c>=1)
      {
    	databus_t widetemp1, widetemp2, widetemp3, widetemp4, widetemp5;
        widetemp1(31, 0) = acc.val[0](31, 0);
        widetemp2(15, 0) = acc.val[0](47,32);
        widetemp2(31,16) = acc.val[1](15, 0);
        widetemp3(31, 0) = acc.val[1](47,16);
        widetemp4(31, 0) = acc.val[2](31, 0);
        widetemp5(15, 0) = acc.val[2](47,32);
        widetemp5(31,16) = 0;

        Output_1.write(widetemp1);
        Output_1.write(widetemp2);
        Output_1.write(widetemp3);
        Output_1.write(widetemp4);
        Output_1.write(widetemp5);


        Output_2.write(widetemp1);
        Output_2.write(widetemp2);
        Output_2.write(widetemp3);
        Output_2.write(widetemp4);
        Output_2.write(widetemp5);
      }
    }
  }
}

