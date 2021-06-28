
#include "../host/typedefs.h"


// tensor weight
void tensor_weight_y(hls::stream< bit32> & Input_1,
		hls::stream< bit32> & Output_1)
{
#pragma HLS INTERFACE axis register port=Input_1
#pragma HLS INTERFACE axis register port=Output_1

	// 3*1024*48bits*6/8/2/1024 = 54 BRAMs
  hls::LineBuffer<3,MAX_WIDTH,outer_t> buf;
  const pixel_t TENSOR_FILTER[] = {0.3243, 0.3513, 0.3243};
  bit32 in_tmp;
  bit32 out_tmp;
  tensor_t acc;
  pixel_t k;
  outer_t tmp;

  TENSOR_WEIGHT_Y_OUTER: for(int r=0; r<MAX_HEIGHT+1; r++)
  {
#ifdef RISCV1
  print_str("r = ");
  print_dec(r);
  //print_str(", c = ");
  //print_dec(c);
  print_str("\n");
#endif
    TENSOR_WEIGHT_Y_INNER: for(int c=0; c<MAX_WIDTH; c++)
    {
      #pragma HLS pipeline II=1


      #pragma HLS data_pack variable=tmp
      #pragma HLS data_pack variable=buf.val[0]
      buf.shift_pixels_up(c);
      if(r<MAX_HEIGHT)
      {
        in_tmp = Input_1.read();
        tmp.val[0](31,  0) = in_tmp(31,  0);
        in_tmp = Input_1.read();
        tmp.val[0](47, 32) = in_tmp(15,  0);
        tmp.val[1](15,  0) = in_tmp(31, 16);
        in_tmp = Input_1.read();
        tmp.val[1](47, 16) = in_tmp(31,  0);

        in_tmp = Input_1.read();
        tmp.val[2](31,  0) = in_tmp(31,  0);
        in_tmp = Input_1.read();
        tmp.val[2](47, 32) = in_tmp(15,  0);
        tmp.val[3](15,  0) = in_tmp(31, 16);
        in_tmp = Input_1.read();
        tmp.val[3](47, 16) = in_tmp(31,  0);


        in_tmp = Input_1.read();
        tmp.val[4](31,  0) = in_tmp(31,  0);
        in_tmp = Input_1.read();
        tmp.val[4](47, 32) = in_tmp(15,  0);
        tmp.val[5](15,  0) = in_tmp(31, 16);
        in_tmp = Input_1.read();
        tmp.val[5](47, 16) = in_tmp(31,  0);


      }
      else
      {
        TENSOR_WEIGHT_Y_TMP_INIT: for(int i=0; i<6; i++)
          tmp.val[i] = 0;
      }
      buf.insert_bottom_row(tmp,c);


      TENSOR_WEIGHT_Y_ACC_INIT: for(int k =0; k<6; k++)
        acc.val[k] = 0;

      if (r >= 2 && r < MAX_HEIGHT)
      {
        TENSOR_WEIGHT_Y_TMP_OUTER: for(int i=0; i<3; i++)
        {
          tmp = buf.getval(i,c);
          k = TENSOR_FILTER[i];
          TENSOR_WEIGHT_Y_TMP_INNER: for(int component=0; component<6; component++)
          {
            acc.val[component] = acc.val[component] + tmp.val[component]*k;
          }
        }
      }
      if(r >= 1)
      {
        //tensor_y[r-1][c] = acc;
        out_tmp(31,  0) = acc.val[0](31,  0);
        Output_1.write(out_tmp);
        out_tmp(15,  0) = acc.val[0](47, 32);
        out_tmp(31, 16) = acc.val[1](15,  0);
        Output_1.write(out_tmp);
        out_tmp(31,  0) = acc.val[1](47, 16);
        Output_1.write(out_tmp);

        out_tmp(31,  0) = acc.val[2](31,  0);
        Output_1.write(out_tmp);
        out_tmp(15,  0) = acc.val[2](47, 32);
        out_tmp(31, 16) = acc.val[3](15,  0);
        Output_1.write(out_tmp);
        out_tmp(31,  0) = acc.val[3](47, 16);
        Output_1.write(out_tmp);

        out_tmp(31,  0) = acc.val[4](31,  0);
        Output_1.write(out_tmp);
        out_tmp(15,  0) = acc.val[4](47, 32);
        out_tmp(31, 16) = acc.val[5](15,  0);
        Output_1.write(out_tmp);
        out_tmp(31,  0) = acc.val[5](47, 16);
        Output_1.write(out_tmp);

      }
    }
  }
}
