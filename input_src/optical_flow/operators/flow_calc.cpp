#include "../host/typedefs.h"


// compute output flow
void flow_calc(hls::stream< bit32> & Input_1,
		hls::stream< bit32> & Output_1)
{
#pragma HLS INTERFACE axis register port=Input_1
#pragma HLS INTERFACE axis register port=Output_1

  static outer_pixel_t buf[2];
  bit32 in_tmp;
  vel_pixel_t outputs;
  bit32 out_tmp;
  static int in_cnt = 0;
  static int out_cnt = 0;


  FLOW_OUTER: for(int r=0; r<MAX_HEIGHT; r++)
  {
#ifdef RISCV
      print_str("r=");
      print_dec(r);
      //print_str(", c=");
      //print_dec(c);
      print_str("\n");
#endif

    FLOW_INNER: for(int c=0; c<MAX_WIDTH; c++)
    {


      #pragma HLS pipeline II=1
      tensor_t tmp_tensor;
      in_tmp = Input_1.read();
      //printf("0x%08x,\n", (unsigned int) in_tmp(31, 0));
      tmp_tensor.val[0](31,  0) = in_tmp(31,  0);
      in_tmp = Input_1.read();
      //printf("0x%08x,\n", (unsigned int) in_tmp(31, 0));
      //printf("%d: %08x\n", in_cnt++, (unsigned int) in_tmp(31, 0));
      tmp_tensor.val[0](47, 32) = in_tmp(15,  0);
      tmp_tensor.val[1](15,  0) = in_tmp(31, 16);
      in_tmp = Input_1.read();
      //printf("0x%08x,\n", (unsigned int) in_tmp(31, 0));
      //printf("%d: %08x\n", in_cnt++, (unsigned int) in_tmp(31, 0));
      tmp_tensor.val[1](47, 16) = in_tmp(31,  0);

      in_tmp = Input_1.read();
      //printf("0x%08x,\n", (unsigned int) in_tmp(31, 0));
      //printf("%d: %08x\n", in_cnt++, (unsigned int) in_tmp(31, 0));
      tmp_tensor.val[2](31,  0) = in_tmp(31,  0);
      in_tmp = Input_1.read();
      //printf("0x%08x,\n", (unsigned int) in_tmp(31, 0));
      //printf("%d: %08x\n", in_cnt++, (unsigned int) in_tmp(31, 0));
      tmp_tensor.val[2](47, 32) = in_tmp(15,  0);
      tmp_tensor.val[3](15,  0) = in_tmp(31, 16);
      in_tmp = Input_1.read();
      //printf("0x%08x,\n", (unsigned int) in_tmp(31, 0));
      //printf("%d: %08x\n", in_cnt++, (unsigned int) in_tmp(31, 0));
      tmp_tensor.val[3](47, 16) = in_tmp(31,  0);



      in_tmp = Input_1.read();
      //printf("0x%08x,\n", (unsigned int) in_tmp(31, 0));
      //printf("%d: %08x\n", in_cnt++, (unsigned int) in_tmp(31, 0));
      tmp_tensor.val[4](31,  0) = in_tmp(31,  0);
      in_tmp = Input_1.read();
      //printf("0x%08x,\n", (unsigned int) in_tmp(31, 0));
      //printf("%d: %08x\n", in_cnt++, (unsigned int) in_tmp(31, 0));
      tmp_tensor.val[4](47, 32) = in_tmp(15,  0);
      tmp_tensor.val[5](15,  0) = in_tmp(31, 16);
      in_tmp = Input_1.read();
      //printf("0x%08x,\n", (unsigned int) in_tmp(31, 0));
      //printf("%d: %08x\n", in_cnt++, (unsigned int) in_tmp(31, 0));
      tmp_tensor.val[5](47, 16) = in_tmp(31,  0);


      if(r>=2 && r<MAX_HEIGHT-2 && c>=2 && c<MAX_WIDTH-2)
      {
	      calc_pixel_t t1 = (calc_pixel_t) tmp_tensor.val[0];
	      calc_pixel_t t2 = (calc_pixel_t) tmp_tensor.val[1];
	      calc_pixel_t t3 = (calc_pixel_t) tmp_tensor.val[2];
	      calc_pixel_t t4 = (calc_pixel_t) tmp_tensor.val[3];
	      calc_pixel_t t5 = (calc_pixel_t) tmp_tensor.val[4];
	      calc_pixel_t t6 = (calc_pixel_t) tmp_tensor.val[5];

	      calc_pixel_t denom = t1*t2-t4*t4;
	      calc_pixel_t numer0 = t6*t4-t5*t2;
	      calc_pixel_t numer1 = t5*t4-t6*t1;

	      if(denom != 0)
	      {
#ifdef SMALL_HW
	    	  float tmp1, tmp2, tmp3;;
	    	  tmp1 = numer0;
	    	  tmp2 = denom;
	    	  tmp3 = tmp1 / tmp2;
			  buf[0] = (outer_pixel_t) tmp3;
	    	  tmp1 = numer1;
	    	  tmp3 = tmp1 / tmp2;
	    	  buf[1] = (outer_pixel_t) tmp3;

#else
	    	  buf[0] = numer0 / denom;
	    	  buf[1] = numer1 / denom;
#endif
	      }
	      else
	      {
		      buf[0] = 0;
		      buf[1] = 0;
	      }
      }
      else
      {
        buf[0] = buf[1] = 0;
      }

      if(r==0 && c==0){
		Output_1.write(MAX_HEIGHT*MAX_WIDTH*2+4);
		Output_1.write(MAX_HEIGHT*MAX_WIDTH*2+4);
		Output_1.write(MAX_HEIGHT*MAX_WIDTH*2+4);
		Output_1.write(MAX_HEIGHT*MAX_WIDTH*2+4);
      }
      outputs = (vel_pixel_t)buf[0];
      out_tmp(31, 0) = outputs(31, 0);
      //printf("0x%08x,\n", (unsigned int) out_tmp(31, 0));
      Output_1.write(out_tmp);
      outputs = (vel_pixel_t)buf[1];
      out_tmp(31, 0) = outputs(31, 0);
      //printf("0x%08x,\n", (unsigned int) out_tmp(31, 0));
      Output_1.write(out_tmp);
    }
  }
}
