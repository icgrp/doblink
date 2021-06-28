
#include "../host/typedefs.h"
//data_input_redirection
void data_1_4_1(
		    hls::stream<ap_uint<32> > & Input_1,
			hls::stream<ap_uint<32> > & Input_2,
			hls::stream<ap_uint<32> > & Input_3,
			hls::stream<ap_uint<32> > & Input_4,
			hls::stream<ap_uint<32> > & Input_5,

			hls::stream<ap_uint<32> > & Output_1,
			hls::stream<ap_uint<32> > & Output_2,
			hls::stream<ap_uint<32> > & Output_3,
			hls::stream<ap_uint<32> > & Output_4,
			hls::stream<ap_uint<32> > & Output_5
			)
{
#pragma HLS INTERFACE axis register port=Input_1
#pragma HLS INTERFACE axis register port=Input_2
#pragma HLS INTERFACE axis register port=Input_3
#pragma HLS INTERFACE axis register port=Input_4
#pragma HLS INTERFACE axis register port=Input_5
#pragma HLS INTERFACE axis register port=Output_1
#pragma HLS INTERFACE axis register port=Output_2
#pragma HLS INTERFACE axis register port=Output_3
#pragma HLS INTERFACE axis register port=Output_4
#pragma HLS INTERFACE axis register port=Output_5

	static int epoch = 0;
	bit32 tmp_data;
	bit32 tmp_label;

  if(epoch < 5)
  {
	  // main loop
	  // in each epoch, go through each training instance in sequence
	  TRAINING_INST: for( int training_id = 0; training_id < NUM_TRAINING; training_id ++ )
	  {
		tmp_label = Input_1.read();
		Output_1.write(tmp_label);
		// first reads in the training instance
		READ_TRAINING_DATA_1: for (int i = 0; i < NUM_FEATURES / D_VECTOR_SIZE / 8; i ++ )
		{
#pragma HLS pipeline II=2
		  tmp_data= Input_1.read();
		  Output_1.write(tmp_data);
		  tmp_data= Input_1.read();
		  Output_1.write(tmp_data);
		}
		Output_2.write(tmp_label);
		READ_TRAINING_DATA_2: for (int i = 0; i < NUM_FEATURES / D_VECTOR_SIZE / 8; i ++ )
		{
#pragma HLS pipeline II=2
			  tmp_data= Input_1.read();
			  Output_2.write(tmp_data);
			  tmp_data= Input_1.read();
			  Output_2.write(tmp_data);
		}
		Output_3.write(tmp_label);
		READ_TRAINING_DATA_3: for (int i = 0; i < NUM_FEATURES / D_VECTOR_SIZE / 8; i ++ )
		{
#pragma HLS pipeline II=2
			  tmp_data= Input_1.read();
			  Output_3.write(tmp_data);
			  tmp_data= Input_1.read();
			  Output_3.write(tmp_data);
		}
		Output_4.write(tmp_label);
		READ_TRAINING_DATA_4: for (int i = 0; i < NUM_FEATURES / D_VECTOR_SIZE / 8; i ++ )
		{
#pragma HLS pipeline II=2
			  tmp_data= Input_1.read();
			  Output_4.write(tmp_data);
			  tmp_data= Input_1.read();
			  Output_4.write(tmp_data);
		}
	  }
	  epoch++;
  }else{

	  STREAM_OUT_1: for (int i = 0; i < NUM_FEATURES / F_VECTOR_SIZE /8; i ++ )
	  {
	    #pragma HLS pipeline II=2
		  tmp_data= Input_2.read();
		  Output_5.write(tmp_data);
		  tmp_data= Input_2.read();
		  Output_5.write(tmp_data);
	  }
	  STREAM_OUT_2: for (int i = 0; i < NUM_FEATURES / F_VECTOR_SIZE /8; i ++ )
	  {
	    #pragma HLS pipeline II=2
		  tmp_data= Input_3.read();
		  Output_5.write(tmp_data);
		  tmp_data= Input_3.read();
		  Output_5.write(tmp_data);
	  }
	  STREAM_OUT_3: for (int i = 0; i < NUM_FEATURES / F_VECTOR_SIZE /8; i ++ )
	  {
	    #pragma HLS pipeline II=2
		  tmp_data= Input_4.read();
		  Output_5.write(tmp_data);
		  tmp_data= Input_4.read();
		  Output_5.write(tmp_data);
	  }
	  STREAM_OUT_4: for (int i = 0; i < NUM_FEATURES / F_VECTOR_SIZE /8; i ++ )
	  {
	    #pragma HLS pipeline II=2
		  tmp_data= Input_5.read();
		  Output_5.write(tmp_data);
		  tmp_data= Input_5.read();
		  Output_5.write(tmp_data);
	  }
	  epoch = 0;
  }
}
