/*===============================================================*/
/*                                                               */
/*                        rendering.cpp                          */
/*                                                               */
/*                 C++ kernel for 3D Rendering                   */
/*                                                               */
/*===============================================================*/
#include "typedefs.h"

#include "../operators/data_redir_m.h"
#include "../operators/rasterization2_m.h"
#include "../operators/zculling_top.h"
#include "../operators/coloringFB_bot_m.h"

/*======================UTILITY FUNCTIONS========================*/
const int default_depth = 128;


void data_gen(
		  hls::stream<ap_uint<32> > & Output_1
		)

//( bit32 input[3*NUM_3D_TRI], bit32 output[NUM_FB])
{
#pragma HLS INTERFACE axis register_mode=both register port=Output_1
#include "input_data.h"
    // create space for input and output
    bit32 input_tmp;
    bit32 input[3 * NUM_3D_TRI];
    bit32 output[NUM_FB];

    // pack input data for better performance
    for ( int i = 0; i < NUM_3D_TRI; i++)
    {
        input_tmp(7,   0) = triangle_3ds[i].x0;
        input_tmp(15,  8) = triangle_3ds[i].y0;
        input_tmp(23, 16) = triangle_3ds[i].z0;
        input_tmp(31, 24) = triangle_3ds[i].x1;
        Output_1.write(input_tmp);

        input_tmp(7, 0) = triangle_3ds[i].y1;
        input_tmp(15, 8) = triangle_3ds[i].z1;
        input_tmp(23, 16) = triangle_3ds[i].x2;
        input_tmp(31, 24) = triangle_3ds[i].y2;
        Output_1.write(input_tmp);

        input_tmp(7, 0) = triangle_3ds[i].z2;
        input_tmp(31, 8) = 0;
        Output_1.write(input_tmp);
    }
}

void top (
		  hls::stream<ap_uint<32> > & Input_1,
		  hls::stream<ap_uint<32> > & Output_1
		)

//( bit32 input[3*NUM_3D_TRI], bit32 output[NUM_FB])
{
#pragma HLS INTERFACE axis register both port=Input_1
#pragma HLS INTERFACE axis register both port=Output_1
#pragma HLS DATAFLOW
  // local variables
  Triangle_2D triangle_2ds;
  Triangle_2D triangle_2ds_same;

  bit16 size_fragment;
  CandidatePixel fragment[500];

  bit16 size_pixels;
  Pixel pixels[500];

  bit8 frame_buffer[MAX_X][MAX_Y];
  bit2 angle = 0;

  bit8 max_min[5];
  bit16 max_index[1];
  bit2 flag;
  hls::stream<ap_uint<32> > Output_redir_odd("Output_redir_odd");
#pragma HLS STREAM variable=Output_redir_odd depth=1024


  hls::stream<ap_uint<32> > Output_r2_odd_top("Output_r2_odd_top");
#pragma HLS STREAM variable=Output_r2_odd_top depth=1024

  hls::stream<ap_uint<32> > Output_zcu_top("Output_zcu_top");
#pragma HLS STREAM variable=Output_zcu_top depth=1024


  // processing NUM_3D_TRI 3D triangles
  TRIANGLES: for (bit16 i = 0; i < NUM_3D_TRI; i++)
  {



    // five stages for processing each 3D triangle
	data_redir_m(Input_1, Output_redir_odd);
    rasterization2_m(Output_redir_odd, Output_r2_odd_top);
    zculling_top( Output_r2_odd_top, Output_zcu_top);
    coloringFB_bot_m(Output_zcu_top, Output_1);

  }

  // output values: frame buffer
  //output_FB_dul(Output_cfb_top, Output_cfb_bot,Output_1);
}



extern "C" {
	void ydma (
			bit64 * input1,
			bit32 * input2,
			bit64 * output1,
			bit32 * output2,
			int config_size,
			int input_size,
			int output_size
			)
	{
#pragma HLS INTERFACE m_axi port=input1 bundle=aximm1
#pragma HLS INTERFACE m_axi port=input2 bundle=aximm2
#pragma HLS INTERFACE m_axi port=output1 bundle=aximm1
#pragma HLS INTERFACE m_axi port=output2 bundle=aximm2
	#pragma HLS DATAFLOW

	  bit64 v1_buffer[256];   // Local memory to store vector1
	  //hls::stream< unsigned int > v1_buffer;
	  #pragma HLS STREAM variable=v1_buffer depth=256

          hls::stream<ap_uint<32> > Input_1("Input_1_str");
          hls::stream<ap_uint<32> > Output_1("Output_str");

          for(int i=0; i<config_size; i++){ v1_buffer[i] = input1[i]; }
          for(int i=0; i<config_size; i++){ output1[i] = v1_buffer[i]; }

	  for(int i=0; i<input_size;  i++){ Input_1.write(input2[i]); }
	  
          top(Input_1, Output_1);
 
          for(int i=0; i<output_size; i++){ output2[i] = Output_1.read(); }
	}

}

void config_parser(
		hls::stream< bit64 > & input1,
		hls::stream< bit32 > & input2,
		hls::stream< bit64 > & output1,
		hls::stream< bit32 > & output2,
		hls::stream< bit64 > & output3

		)
{
#pragma HLS INTERFACE axis register_mode=both register port=input1
#pragma HLS INTERFACE axis register_mode=both register port=input2
#pragma HLS INTERFACE axis register_mode=both register port=output1
#pragma HLS INTERFACE axis register_mode=both register port=output2
#pragma HLS INTERFACE axis register_mode=both register port=output3

	bit64 v1_buffer[256];
	unsigned int config_num;
	unsigned int data_num;

	config_num = input1.read();
	data_num = input1.read();


	// read the configuration packets
	for(int i=0; i<config_num; i++){
#pragma HLS PIPELINE II=1
		v1_buffer[i] = input1.read();
	}

	// send the configuration packets to the BFT
	for(int i=0; i<config_num; i++){
#pragma HLS PIPELINE II=1
		output1.write(v1_buffer[i]);
	}

	// send the configuration packets back to the host
	output3.write(config_num);
	output3.write(data_num);
	for(int i=0; i<config_num; i++){
#pragma HLS PIPELINE II=1
		output3.write(i);
	}

	// transfer the data to the kernel
	for(int i=0; i<data_num; i++){
#pragma HLS PIPELINE II=1
		output2.write(input2.read());
	}
}

void config_collector(
		hls::stream< bit64 > & input1,
		hls::stream< bit64 > & input2,
		hls::stream< bit64 > & output1
		)
{
#pragma HLS INTERFACE axis register_mode=both register port=input1
#pragma HLS INTERFACE axis register_mode=both register port=input2
#pragma HLS INTERFACE axis register_mode=both register port=output1

	bit64 v1_buffer[256];

	for(int i=0; i<10; i++){
#pragma HLS PIPELINE II=1
		v1_buffer[i] = input1.read();
	}

	for(int i=0; i<12; i++){
#pragma HLS PIPELINE II=1
		bit64 tmp;
		tmp = v1_buffer[i] + input2.read();
		output1.write(tmp);
	}

}

