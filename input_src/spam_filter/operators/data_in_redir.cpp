#include "../host/typedefs.h"
//data_input_redirection
void data_in_redir( hls::stream<ap_uint<32> > & Input_1,
			hls::stream<ap_uint<32> > & Output_1,
			hls::stream<ap_uint<32> > & Output_2
			)
{
#pragma HLS INTERFACE axis register port=Input_1
#pragma HLS INTERFACE axis register port=Output_1
#pragma HLS INTERFACE axis register port=Output_2
	bit32 tmp_data;
  // intermediate variables
  // local buffer of labels
  static LabelType   label_local[4500];
  #pragma HLS array_partition variable=label_local cyclic factor=8
  // array for storing one training instance
  static DataType training_instance[NUM_FEATURES];
  static int epoch = 0;
  bit128 dump = 0;

#ifdef RISCV1
	  print_str("epoch=");
	  print_dec(epoch);
	  print_str("\n");
#endif

  if (epoch == 0)
  {
    // copy in labels
	//LABEL_CP: for (int i = 0; i < NUM_TRAINING / L_VECTOR_SIZE; i ++ )
	LABEL_CP: for (int i = 0; i < 1125; i ++ )
	{
		  bit32 tmp_label;
		  tmp_label(31,  0) = Input_1.read();
		  //printf("tmp_label: 0x%08x,\n", tmp_label.to_int());
		  label_local[i * 4 + 0](LTYPE_WIDTH-1, 0) = tmp_label( 7, 0);
	  	  label_local[i * 4 + 1](LTYPE_WIDTH-1, 0) = tmp_label(15, 8);
	  	  label_local[i * 4 + 2](LTYPE_WIDTH-1, 0) = tmp_label(23,16);
	  	  label_local[i * 4 + 3](LTYPE_WIDTH-1, 0) = tmp_label(31,24);
	}
  }

  // main loop
  // in each epoch, go through each training instance in sequence
  TRAINING_INST: for( int training_id = 0; training_id < NUM_TRAINING; training_id ++ )
  {
#ifdef RISCV1
	  print_str("i=");
	  print_dec(training_id);
	  print_str("\n");
#endif
    // get the label
    LabelType training_label;
    training_label(LTYPE_WIDTH-1, 0)= label_local[training_id].range(LTYPE_WIDTH-1, 0);
    // first reads in the training instance
    tmp_data = training_label.range(7, 0);
    Output_1.write(tmp_data);
    READ_TRAINING_DATA_top: for (int i = 0; i < NUM_FEATURES / D_VECTOR_SIZE / 4; i ++ )
    {
#pragma HLS PIPELINE II=2

      tmp_data= Input_1.read();
      Output_1.write(tmp_data);
      tmp_data= Input_1.read();
      Output_1.write(tmp_data);
      tmp_data= Input_1.read();
      Output_1.write(tmp_data);
      tmp_data= Input_1.read();
      Output_1.write(tmp_data);
    }
    tmp_data = training_label.range(7, 0);
    Output_2.write(tmp_data);
    READ_TRAINING_DATA_bot: for (int i = 0; i < NUM_FEATURES / D_VECTOR_SIZE / 4; i ++ )
    {
#ifdef RISCV1
	  print_str("i3=");
	  print_dec(i);
	  print_str("\n");
#endif
#pragma HLS PIPELINE II=2
        tmp_data= Input_1.read();
        Output_2.write(tmp_data);
        tmp_data= Input_1.read();
        Output_2.write(tmp_data);
        tmp_data= Input_1.read();
        Output_2.write(tmp_data);
        tmp_data= Input_1.read();
        Output_2.write(tmp_data);
    }

  }
  epoch = epoch+1;
}

