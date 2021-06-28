/*===============================================================*/
/*                                                               */
/*                      optical_flow.cpp                         */
/*                                                               */
/*             Hardware function for optical flow                */
/*                                                               */
/*===============================================================*/

// use HLS video library
#include "../host/typedefs.h"
// use HLS fixed point

#include "../operators/flow_calc.h"
#include "../operators/gradient_weight_x.h"
#include "../operators/gradient_weight_y.h"
#include "../operators/gradient_xy_calc.h"
#include "../operators/gradient_z_calc.h"
#include "../operators/outer_product.h"
#include "../operators/tensor_weight_x.h"
#include "../operators/tensor_weight_y.h"
#include "../operators/unpack.h"

// define these constants so they can be used in pragma
const int max_width = MAX_WIDTH; 
const int default_depth = MAX_WIDTH;


// convolution filters
//const int GRAD_WEIGHTS[] =  {1,-8,0,8,-1};
//const pixel_t GRAD_FILTER[] = {0.0755, 0.133, 0.1869, 0.2903, 0.1869, 0.133, 0.0755};
//const pixel_t TENSOR_FILTER[] = {0.3243, 0.3513, 0.3243};

void data_gen(
		hls::stream< bit32 > &Output_1)
{
#pragma HLS interface ap_hs port=Output_1


	#include "./input_data.h"
	#pragma HLS ARRAY_PARTITION variable=input_data cyclic factor=2 dim=1

	int i;
	for (i=0; i<446464; i++)
	{
#pragma HLS pipeline II=2
		bit32 tmp;
		tmp = input_data[i*2+1];
		Output_1.write(tmp);
		tmp = input_data[i*2];
		Output_1.write(tmp);
		//Output_1.write(tmp(95,64));
		//Output_1.write(tmp(127,96));
	}
}




// top-level kernel function
void top(hls::stream<bit32 > & Input_1,
		hls::stream< bit32 > & Output_1)
{
  #pragma HLS data_pack variable=outputs

  #pragma HLS DATAFLOW

  //Need to duplicate frame3 for the two calculations
  hls::stream< bit32 > frame3_a;
  hls::stream< bit32 > frame1_a;
  hls::stream< bit32 > frame2_a;
  hls::stream< bit32 > frame4_a;
  hls::stream< bit32 > frame5_a;
  hls::stream< bit32 > frame3_b;
  hls::stream< bit32 > gradient_x;
  hls::stream< bit32 > gradient_y;
  hls::stream< bit32 > gradient_z;
  hls::stream< bit32 > y_filtered;
  hls::stream< bit32 > filtered_gradient;
  hls::stream< bit32 > out_product;
  hls::stream< bit32 > tensor_y;
  hls::stream< bit32 > tensor;

  unpack(Input_1, frame1_a, frame3_a);
  //
  // compute
  gradient_z_calc(frame1_a, gradient_z);
  gradient_xy_calc(frame3_a, gradient_x, gradient_y);
  gradient_weight_y(gradient_x, gradient_y, gradient_z, y_filtered);
  gradient_weight_x(y_filtered, filtered_gradient);
  outer_product(filtered_gradient, out_product);
  tensor_weight_y(out_product, tensor_y);
  tensor_weight_x(tensor_y, tensor);
  flow_calc(tensor, Output_1);

}
