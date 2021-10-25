
#include "../host/typedefs.h"


void tensor_weight_x(hls::stream< bit32> & Input_1,
		hls::stream< bit32> & Output_1)
{
#pragma HLS INTERFACE axis register port=Input_1
#pragma HLS INTERFACE axis register port=Output_1
  static int in_cnt = 0;

  bit32 in_tmp, out_tmp;
  hls::Window<1,3,tensor_t> buf;
  const pixel_t TENSOR_FILTER[] = {0.3243, 0.3513, 0.3243};
  //const float TENSOR_FILTER[] = {0.3243, 0.3513, 0.3243};
  TENSOR_WEIGHT_X_OUTER: for(int r=0; r<MAX_HEIGHT; r++)
  {
#ifdef RISCV1
  print_str("r = ");
  print_dec(r);
  //print_str(", c = ");
  //print_dec(c);
  print_str("\n");
#endif
    TENSOR_WEIGHT_X_INNER: for(int c=0; c<MAX_WIDTH+1; c++)
    {
      #pragma HLS pipeline II=1
      buf.shift_pixels_left();
      tensor_t tmp;
      if(c<MAX_WIDTH)
      {
        //tmp = tensor_y[r][c];
          in_tmp = Input_1.read();
          //printf("%d: %08x\n", in_cnt++, (unsigned int) in_tmp(31, 0));
          tmp.val[0](31,  0) = in_tmp(31,  0);
          in_tmp = Input_1.read();
          //printf("%d: %08x\n", in_cnt++, (unsigned int) in_tmp(31, 0));
          tmp.val[0](47, 32) = in_tmp(15,  0);
          tmp.val[1](15,  0) = in_tmp(31, 16);
          in_tmp = Input_1.read();
          //printf("%d: %08x\n", in_cnt++, (unsigned int) in_tmp(31, 0));
          tmp.val[1](47, 16) = in_tmp(31,  0);

          in_tmp = Input_1.read();
          //printf("%d: %08x\n", in_cnt++, (unsigned int) in_tmp(31, 0));
          tmp.val[2](31,  0) = in_tmp(31,  0);
          in_tmp = Input_1.read();
          //printf("%d: %08x\n", in_cnt++, (unsigned int) in_tmp(31, 0));
          tmp.val[2](47, 32) = in_tmp(15,  0);
          tmp.val[3](15,  0) = in_tmp(31, 16);
          in_tmp = Input_1.read();
          //printf("%d: %08x\n", in_cnt++, (unsigned int) in_tmp(31, 0));
          tmp.val[3](47, 16) = in_tmp(31,  0);


          in_tmp = Input_1.read();
          //printf("%d: %08x\n", in_cnt++, (unsigned int) in_tmp(31, 0));
          tmp.val[4](31,  0) = in_tmp(31,  0);
          in_tmp = Input_1.read();
          //printf("%d: %08x\n", in_cnt++, (unsigned int) in_tmp(31, 0));
          tmp.val[4](47, 32) = in_tmp(15,  0);
          tmp.val[5](15,  0) = in_tmp(31, 16);
          in_tmp = Input_1.read();
          //printf("%d: %08x\n", in_cnt++, (unsigned int) in_tmp(31, 0));
          tmp.val[5](47, 16) = in_tmp(31,  0);
      }
      else
      {
        TENSOR_WEIGHT_X_TMP_INIT: for(int i=0; i<6; i++)
          tmp.val[i] = 0;
      }
      buf.insert_pixel(tmp,0,2);

      tensor_t acc;
      TENSOR_WEIGHT_X_ACC_INIT: for(int k =0; k<6; k++)
        acc.val[k] = 0;
      if (c >= 2 && c < MAX_WIDTH)
      {
        TENSOR_WEIGHT_X_TMP_OUTER: for(int i=0; i<3; i++)
        {
          tmp = buf.getval(0,i);
          TENSOR_WEIGHT_X_TMP_INNER: for(int component=0; component<6; component++)
          {
            acc.val[component] = acc.val[component] + tmp.val[component]*TENSOR_FILTER[i];
          }
        }
      }
      if(c>=1)
      {
        //tensor[r][c-1] = acc;
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
