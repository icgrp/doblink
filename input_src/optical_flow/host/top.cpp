#include "top.h"

#include "../operators/flow_calc_1.h"
#include "../operators/flow_calc_2.h"
#include "../operators/gradient_weight_x1.h"
#include "../operators/gradient_weight_x2.h"
#include "../operators/gradient_weight_x3.h"
#include "../operators/gradient_weight_y_1.h"
#include "../operators/gradient_weight_y_2.h"
#include "../operators/gradient_weight_y_3.h"
#include "../operators/gradient_xyz_calc.h"
#include "../operators/outer_product1.h"
#include "../operators/outer_product2.h"
#include "../operators/output_fun.h"
#include "../operators/tensor_weight_x1.h"
#include "../operators/tensor_weight_x2.h"
#include "../operators/tensor_weight_y1.h"
#include "../operators/tensor_weight_y2.h"








void flow_calc_3(
		hls::stream<stdio_t> &Input_1,
		hls::stream<stdio_t> &Input_2,
		hls::stream<stdio_t> &Output_1)
{
#pragma HLS interface ap_hs port=Input_1
#pragma HLS interface ap_hs port=Output_1
#pragma HLS interface ap_hs port=Input_2
  static float buf;
  FLOW_OUTER: for(int r=0; r<MAX_HEIGHT; r++)
  {
    FLOW_INNER: for(int c=0; c<MAX_WIDTH; c++)
    {
      #pragma HLS pipeline II=1
      tensor_t tmp_tensor;
      bit160 widetemp;
      widetemp(31,0)= Input_1.read();
      widetemp(63,32)= Input_1.read();
      widetemp(95,64)= Input_1.read();
      widetemp(127,96)= Input_1.read();
      widetemp(159,128)= Input_1.read();
      tmp_tensor.val[0].range(47,0) = widetemp.range(47,0);
      tmp_tensor.val[1].range(47,0) = widetemp.range(95,48);
      tmp_tensor.val[2].range(47,0) = widetemp.range(143,96);

      widetemp(31,0)= Input_2.read();
      widetemp(63,32)= Input_2.read();
      widetemp(95,64)= Input_2.read();
      widetemp(127,96)= Input_2.read();
      widetemp(159,128)= Input_2.read();
      tmp_tensor.val[3].range(47,0) = widetemp.range(47,0);
      tmp_tensor.val[4].range(47,0) = widetemp.range(95,48);
      tmp_tensor.val[5].range(47,0) = widetemp.range(143,96);

      if(r>=2 && r<MAX_HEIGHT-2 && c>=2 && c<MAX_WIDTH-2)
      {
    	  outer_pixel_t t1 = (outer_pixel_t) tmp_tensor.val[0];
	      outer_pixel_t t2 = (outer_pixel_t) tmp_tensor.val[1];
	      outer_pixel_t t3 = (outer_pixel_t) tmp_tensor.val[2];
	      outer_pixel_t t4 = (outer_pixel_t) tmp_tensor.val[3];
	      outer_pixel_t t5 = (outer_pixel_t) tmp_tensor.val[4];
	      outer_pixel_t t6 = (outer_pixel_t) tmp_tensor.val[5];
	      outer_pixel_t denom1 = t1*t1-t2*t2+t3*t3-t5*t6+t3*t4;
	      outer_pixel_t numer1 = t6*t6-t5*t5+t4*t4+t2*t1;
	      if(denom1 != 0)
              {
        	  buf = (float)numer1 / (float) denom1;
        	  //buf = (ap_fixed<64,56>) numer1 / (ap_fixed<64,56>) denom;
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
    }
  }
}




void top(//frames_t   frames[MAX_HEIGHT][MAX_WIDTH],
		 hls::stream< ap_uint<32> > &Input_1,
                  //velocity_t outputs[MAX_HEIGHT][MAX_WIDTH])
		 hls::stream< ap_uint<32> > &Output_1)
{

#pragma HLS interface ap_hs port=Input_1
#pragma HLS interface ap_hs port=Output_1
  #pragma HLS DATAFLOW

  // FIFOs connecting the stages

  //static pixel_t gradient_x[MAX_HEIGHT][MAX_WIDTH];
  static hls::stream<databus_t> gradient_x;
  #pragma HLS STREAM variable=gradient_x depth=default_depth

  //static pixel_t gradient_y[MAX_HEIGHT][MAX_WIDTH];
  static hls::stream<databus_t> gradient_y;
  #pragma HLS STREAM variable=gradient_y depth=default_depth

  //static pixel_t gradient_z[MAX_HEIGHT][MAX_WIDTH];
  static hls::stream<databus_t> gradient_z;
  #pragma HLS STREAM variable=gradient_z depth=max_width*4

  //static gradient_t y_filtered[MAX_HEIGHT][MAX_WIDTH];
  //#pragma HLS STREAM variable=y_filtered depth=default_depth
  static hls::stream<databus_t> y_filtered_x;
  static hls::stream<databus_t> y_filtered_y;
  static hls::stream<databus_t> y_filtered_z;
  #pragma HLS STREAM variable=y_filtered_x depth=default_depth
  #pragma HLS STREAM variable=y_filtered_y depth=default_depth
  #pragma HLS STREAM variable=y_filtered_z depth=default_depth

  //static gradient_t filtered_gradient[MAX_HEIGHT][MAX_WIDTH];
  //#pragma HLS STREAM variable=filtered_gradient depth=default_depth
  static hls::stream<databus_t> filtered_gradient_x1;
  static hls::stream<databus_t> filtered_gradient_y1;
  static hls::stream<databus_t> filtered_gradient_z1;
  #pragma HLS STREAM variable=filtered_gradient_x1 depth=default_depth
  #pragma HLS STREAM variable=filtered_gradient_y1 depth=default_depth
  #pragma HLS STREAM variable=filtered_gradient_z1 depth=default_depth

  static hls::stream<databus_t> filtered_gradient_x2;
  static hls::stream<databus_t> filtered_gradient_y2;
  static hls::stream<databus_t> filtered_gradient_z2;
  #pragma HLS STREAM variable=filtered_gradient_x2 depth=default_depth
  #pragma HLS STREAM variable=filtered_gradient_y2 depth=default_depth
  #pragma HLS STREAM variable=filtered_gradient_z2 depth=default_depth

  static hls::stream<databus_t> out_product1;
  #pragma HLS STREAM variable=out_product1 depth=default_depth
  static hls::stream<databus_t> out_product2;
  #pragma HLS STREAM variable=out_product2 depth=default_depth
  static hls::stream<databus_t> tensor_y1;
  #pragma HLS STREAM variable=tensor_y1 depth=default_depth
  static hls::stream<databus_t> tensor_y2;
  #pragma HLS STREAM variable=tensor_y2 depth=default_depth
  static hls::stream<databus_t> tx1_out;
  #pragma HLS STREAM variable=tx1_out depth=default_depth
  static hls::stream<databus_t> tx2_out;
  #pragma HLS STREAM variable=tx2_out depth=default_depth
  static hls::stream<databus_t> tx1_out1;
  #pragma HLS STREAM variable=tx1_out1 depth=default_depth
  static hls::stream<databus_t> tx2_out1;
  #pragma HLS STREAM variable=tx2_out1 depth=default_depth

  static hls::stream<databus_t> out_product1a;
  #pragma HLS STREAM variable=out_product1a depth=default_depth
  static hls::stream<databus_t> out_product2a;
  #pragma HLS STREAM variable=out_product2a depth=default_depth
  static hls::stream<databus_t> tensor_y1a;
  #pragma HLS STREAM variable=tensor_y1a depth=default_depth
  static hls::stream<databus_t> tensor_y2a;
  #pragma HLS STREAM variable=tensor_y2a depth=default_depth
  static hls::stream<databus_t> tx1_outa;
  #pragma HLS STREAM variable=tx1_outa depth=default_depth
  static hls::stream<databus_t> tx2_outa;
  #pragma HLS STREAM variable=tx2_outa depth=default_depth
  static hls::stream<databus_t> tx1_out1a;
  #pragma HLS STREAM variable=tx1_out1a depth=default_depth
  static hls::stream<databus_t> tx2_out1a;
  #pragma HLS STREAM variable=tx2_out1a depth=default_depth

  static hls::stream<databus_t> frame3_a;
  #pragma HLS STREAM variable=frame3_a depth=default_depth
  static hls::stream<databus_t> frame1_a;
  #pragma HLS STREAM variable=frame1_a depth=default_depth
  static hls::stream<databus_t> frame2_a;
  #pragma HLS STREAM variable=frame2_a depth=default_depth
  static hls::stream<databus_t> frame3_b;
  #pragma HLS STREAM variable=frame3_b depth=default_depth
  static hls::stream<databus_t> frame4_a;
  #pragma HLS STREAM variable=frame4_a depth=default_depth
  static hls::stream<databus_t> frame5_a;
  #pragma HLS STREAM variable=frame5_a depth=default_depth
//  static input_t frame3_b[MAX_HEIGHT][MAX_WIDTH];
//  #pragma HLS STREAM variable=frame3_b depth=default_depth
  static hls::stream<stdio_t> in;
  #pragma HLS STREAM variable=in depth=default_depth
  static hls::stream<stdio_t> in1;
  #pragma HLS STREAM variable=in1 depth=default_depth
  // stream in and organize the inputs
  //
  // compute
  //input_unpack(Input_1,frame1_a,frame2_a,frame3_a,frame3_b,frame4_a,frame5_a);
  //gradient_xy_calc(frame3_a, gradient_x, gradient_y); //17 + 32 + 32
  //gradient_z_calc(frame1_a, frame2_a, frame3_b, frame4_a, frame5_a, gradient_z); // 17 * 5 + 32
  gradient_xyz_calc(Input_1, gradient_x, gradient_y,gradient_z);
  gradient_weight_y_1(gradient_x, y_filtered_x); //y_filtered); // 32 * 3 + 32 * 3
  gradient_weight_y_2(gradient_y, y_filtered_y); //y_filtered); // 32 * 3 + 32 * 3
  gradient_weight_y_3(gradient_z, y_filtered_z); //y_filtered); // 32 * 3 + 32 * 3
  gradient_weight_x1(y_filtered_x,
		    filtered_gradient_x1,
	            filtered_gradient_x2); // 32 * 3 + 32 * 3
  gradient_weight_x2(y_filtered_y,
		     filtered_gradient_y1,
	             filtered_gradient_y2); // 32 * 3 + 32 * 3
  gradient_weight_x3(y_filtered_z,
		     filtered_gradient_z1,
	            filtered_gradient_z2); // 32 * 3 + 32 * 3
  outer_product1(filtered_gradient_x1, filtered_gradient_y1, filtered_gradient_z1, out_product1); // 32 * 3 + 3 * 48
  outer_product2(filtered_gradient_x2, filtered_gradient_y2, filtered_gradient_z2, out_product2); // 32 * 3 + 3 * 48
  tensor_weight_y1(out_product1,tensor_y1); // 6 * 48 + 6 * 48
  tensor_weight_y2(out_product2,tensor_y2); // 6 * 48 + 6 * 48
  tensor_weight_x1(tensor_y1,
		   tx1_out,tx1_out1); // 6 * 48 + 6 * 48
  tensor_weight_x2(tensor_y2,
		   tx2_out,tx2_out1); // 6 * 48 + 6 * 48
  flow_calc_1(tx1_out, tx2_out, in); // 6 * 48 + 32 * 2
  flow_calc_2(tx1_out1, tx2_out1,in1); // 6 * 48 + 32 * 2
  output_fun(in,in1,Output_1);
  printf("sbbbbb\n");
}


void data_gen(
		 hls::stream< ap_uint<32> > &Output_1)
{
#pragma HLS interface ap_hs port=Output_1


#include "./input_data.h"
#pragma HLS ARRAY_PARTITION variable=input_data cyclic factor=2 dim=1

	int i;
	for (i=0; i<446464; i++)
	{
#pragma HLS pipeline II=2
		bit128 tmp;
		tmp(127,96) = input_data[i*4];
		tmp(95,64) = input_data[i*4+1];
		tmp(63,32) = input_data[i*4+2];
		tmp(31,0) = input_data[i*4+3];

		Output_1.write(tmp(31,0));
		Output_1.write(tmp(63,32));
		//Output_1.write(tmp(95,64));
		//Output_1.write(tmp(127,96));



	}
}


