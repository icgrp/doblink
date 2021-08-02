#include "../host/typedefs.h"
void flow_calc_2(
		hls::stream<stdio_t> &Input_1,
		hls::stream<stdio_t> &Input_2,
		hls::stream<stdio_t> &Output_1)
{
#pragma HLS interface axis register port=Input_1
#pragma HLS interface axis register port=Output_1
#pragma HLS interface axis register port=Input_2
  static float buf;
  FLOW_OUTER: for(int r=0; r<MAX_HEIGHT; r++)
  {
#ifdef RISCV
	  print_str("r=");
	  print_dec(r);
	  print_str("\n");
#endif
    FLOW_INNER: for(int c=0; c<MAX_WIDTH; c++)
    {
#ifdef RISCV1
	  print_str("r=");
	  print_dec(r);
	  print_str(", c=");
	  print_dec(c);
	  print_str("\n");
#endif
	#pragma HLS pipeline II=1
	tensor_t tmp_tensor;
	stdio_t widetemp1, widetemp2, widetemp3, widetemp4, widetemp5;
	widetemp1(31, 0) = Input_1.read();
	widetemp2(31, 0) = Input_1.read();
	widetemp3(31, 0) = Input_1.read();
	widetemp4(31, 0) = Input_1.read();
	widetemp5(31, 0) = Input_1.read();

	//printf("0x%08x,\n", widetemp1.to_int());
	//printf("0x%08x,\n", widetemp2.to_int());
	//printf("0x%08x,\n", widetemp3.to_int());
	//printf("0x%08x,\n", widetemp4.to_int());
	//printf("0x%08x,\n", widetemp5.to_int());

	tmp_tensor.val[0](31, 0) = widetemp1(31, 0);
	tmp_tensor.val[0](47,32) = widetemp2(15, 0);
	tmp_tensor.val[1](15, 0) = widetemp2(31,16);
	tmp_tensor.val[1](47,16) = widetemp3(31, 0);
	tmp_tensor.val[2](31, 0) = widetemp4(31, 0);
	tmp_tensor.val[2](47,32) = widetemp5(15, 0);


	widetemp1(31, 0) = Input_2.read();
	widetemp2(31, 0) = Input_2.read();
	widetemp3(31, 0) = Input_2.read();
	widetemp4(31, 0) = Input_2.read();
	widetemp5(31, 0) = Input_2.read();

	//printf("0x%08x,\n", widetemp1.to_int());
	//printf("0x%08x,\n", widetemp2.to_int());
	//printf("0x%08x,\n", widetemp3.to_int());
	//printf("0x%08x,\n", widetemp4.to_int());
	//printf("0x%08x,\n", widetemp5.to_int());


	tmp_tensor.val[3](31, 0) = widetemp1(31, 0);
	tmp_tensor.val[3](47,32) = widetemp2(15, 0);
	tmp_tensor.val[4](15, 0) = widetemp2(31,16);
	tmp_tensor.val[4](47,16) = widetemp3(31, 0);
	tmp_tensor.val[5](31, 0) = widetemp4(31, 0);
	tmp_tensor.val[5](47,32) = widetemp5(15, 0);

      if(r>=2 && r<MAX_HEIGHT-2 && c>=2 && c<MAX_WIDTH-2)
      {
	      calc_pixel_t t1 = (calc_pixel_t) tmp_tensor.val[0];
	      calc_pixel_t t2 = (calc_pixel_t) tmp_tensor.val[1];
	      calc_pixel_t t4 = (calc_pixel_t) tmp_tensor.val[2];
	      calc_pixel_t t5 = (calc_pixel_t) tmp_tensor.val[4];
	      calc_pixel_t t6 = (calc_pixel_t) tmp_tensor.val[5];
	      calc_pixel_t denom = t1*t2-t4*t4;
	      calc_pixel_t numer1 = t5*t4-t6*t1;

	      if(denom != 0)
              {
        	  buf = (float) numer1 / (float) denom;
        	  //buf = numer1 /  denom;
	      }
	      else
	      {
		      buf = 0;
	      }
      }
      else
      {
        buf = 0;
      }
      stdio_t tmpframe;
      vel_pixel_t tmpvel;
      tmpvel = (vel_pixel_t)buf;
      tmpframe(31,0) = tmpvel(31,0);
      Output_1.write(tmpframe);
      //printf("0x%08x,\n", tmpframe.to_int());
    }
  }
}


