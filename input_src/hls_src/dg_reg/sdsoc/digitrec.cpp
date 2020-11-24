/*===============================================================*/
/*                                                               */
/*                          digitrec.cpp                         */
/*                                                               */
/*             Hardware function for digit recognition           */
/*                                                               */
/*===============================================================*/

#include "../host/typedefs.h"

#include <hls_stream.h>

// popcount function
int popcount(WholeDigitType x)
{
  // most straightforward implementation
  // actually not bad on FPGA
  int cnt = 0;
  for (int i = 0; i < 256; i ++ )
  {
#pragma HLS unroll
    cnt = cnt + x[i];
  }
  return cnt;
}

// Given the test instance and a (new) training instance, this
// function maintains/updates an array of K minimum
// distances per training set.

void update_knn_cluster_0(hls::stream<ap_uint<128> > & Input_1, hls::stream<ap_uint<32> > & Output_1, hls::stream<ap_uint<32> > & Input_2, hls::stream<ap_uint<32> > & Output_2)
{
  #pragma HLS inline
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
#pragma HLS INTERFACE ap_hs port=Input_2
#pragma HLS INTERFACE ap_hs port=Output_2
  static int knn_set0[K_CONST];
  static int knn_set1[K_CONST];
#pragma HLS array_partition variable=knn_set0 complete dim=0
#pragma HLS array_partition variable=knn_set1 complete dim=0
  // Store 900 training data and pass all rest training data
  static WholeDigitType training_set0 [NUM_TRAINING / PAR_FACTOR];
  static WholeDigitType training_set1 [NUM_TRAINING / PAR_FACTOR];
  const int unroll_factor = PAR_FACTOR;
#pragma HLS array_partition variable=training_set0 block factor=unroll_factor dim=0
#pragma HLS array_partition variable=training_set1 block factor=unroll_factor dim=0
  WholeDigitType data_temp;
  static int index = 0;
  // read training data if index = 0
  // turn index to 1, then return
  if (index == 0)
  {
	  for(int i = 0; i < NUM_TRAINING / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		training_set0[i].range(255, 128) =Input_1.read();
		training_set0[i].range(127, 0) =Input_1.read();
	  }
	  for(int i = 0; i < NUM_TRAINING / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		training_set1[i].range(255, 128) =Input_1.read();
		training_set1[i].range(127, 0) =Input_1.read();
	  }
	  for(int i = 0; i < NUM_TRAINING * (PAR_FACTOR - 2 * 1) / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		data_temp.range(255, 128) =Input_1.read();
		data_temp.range(127, 0) =Input_1.read();
		Output_1.write(data_temp.range(255, 224));
		Output_1.write(data_temp.range(223, 192));
		Output_1.write(data_temp.range(191, 160));
		Output_1.write(data_temp.range(159, 128));
		Output_1.write(data_temp.range(127, 96 ));
		Output_1.write(data_temp.range(95 , 64 ));
		Output_1.write(data_temp.range(63 , 32 ));
		Output_1.write(data_temp.range(31 , 0  ));
	  }
	  index = 1;
	  return;
  }



  // get a test data and update knn value if index = 1
  // turn index to 2, then return
  if (index == 1)
  {
    WholeDigitType test_inst;
	// Get testing data
	test_inst.range(255, 128) =Input_1.read();
	test_inst.range(127, 0) =Input_1.read();
	// Pass it to the next kernel
	Output_1.write(test_inst.range(255, 224));
	Output_1.write(test_inst.range(223, 192));
	Output_1.write(test_inst.range(191, 160));
	Output_1.write(test_inst.range(159, 128));
	Output_1.write(test_inst.range(127, 96 ));
	Output_1.write(test_inst.range(95 , 64 ));
	Output_1.write(test_inst.range(63 , 32 ));
	Output_1.write(test_inst.range(31 , 0  ));
	// Preset knn_set
	for(int i = 0; i < K_CONST; i++)
	{
		#pragma HLS unroll
		knn_set0[i] = 256;
		knn_set1[i] = 256;
	}

	TRAINING_LOOP_0 : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
	{
	  #pragma HLS pipeline
	  // Update the KNN set
	  // Compute the difference using XOR
	  WholeDigitType diff = test_inst ^ training_set0[i];
	  int dist = 0;

	  dist = popcount(diff);

	  int max_dist = 0;
	  int max_dist_id = K_CONST+1;
	  int k = 0;

	  // Find the max distance
	  FIND_MAX_DIST_0: for ( int k = 0; k < K_CONST; ++k )
	  {
		if ( knn_set0[k] > max_dist )
		{
		  max_dist = knn_set0[k];
		  max_dist_id = k;
		}
	  }

	  // Replace the entry with the max distance
	  if ( dist < max_dist )
		knn_set0[max_dist_id] = dist;
	}

	// Output knn_set
	for(int i = 0; i < K_CONST; i++)
	{
		Output_2.write(knn_set0[i]);
	}

	TRAINING_LOOP_1 : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
	{
	  #pragma HLS pipeline
	  // Update the KNN set
	  // Compute the difference using XOR
	  WholeDigitType diff = test_inst ^ training_set1[i];
	  int dist = 0;

	  dist = popcount(diff);

	  int max_dist = 0;
	  int max_dist_id = K_CONST+1;
	  int k = 0;

	  // Find the max distance
	  FIND_MAX_DIST_1: for ( int k = 0; k < K_CONST; ++k )
	  {
		if ( knn_set1[k] > max_dist )
		{
		  max_dist = knn_set1[k];
		  max_dist_id = k;
		}
	  }

	  // Replace the entry with the max distance
	  if ( dist < max_dist )
		knn_set1[max_dist_id] = dist;
	}
    index = 2;
    return;
  }


    // Output knn_set if index = 2
	// turn index to 1, then return
	if (index == 2){
	    for(int i = 0; i < K_CONST; i++)
	    {
	        Output_2.write(knn_set1[i]);
	    }

	    for(int i = 0; i < K_CONST * (PAR_FACTOR - 2 * 1); i ++)
	    {
	    	Output_2.write(Input_2.read());
	    }
	    index = 1;
	    return;
	}

  return;
}
void update_knn_cluster_1(hls::stream<ap_uint<32> > & Input_1, hls::stream<ap_uint<32> > & Output_1, hls::stream<ap_uint<32> > & Input_2, hls::stream<ap_uint<32> > & Output_2)
{
  #pragma HLS inline
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
#pragma HLS INTERFACE ap_hs port=Input_2
#pragma HLS INTERFACE ap_hs port=Output_2
  static int knn_set0[K_CONST];
  static int knn_set1[K_CONST];
#pragma HLS array_partition variable=knn_set0 complete dim=0
#pragma HLS array_partition variable=knn_set1 complete dim=0
  // Store 900 training data and pass all rest training data
  static WholeDigitType training_set0 [NUM_TRAINING / PAR_FACTOR];
  static WholeDigitType training_set1 [NUM_TRAINING / PAR_FACTOR];
  const int unroll_factor = PAR_FACTOR;
#pragma HLS array_partition variable=training_set0 block factor=unroll_factor dim=0
#pragma HLS array_partition variable=training_set1 block factor=unroll_factor dim=0
  WholeDigitType data_temp;
  static int index = 0;
  // read training data if index = 0
  // turn index to 1, then return
  if (index == 0)
  {
	  for(int i = 0; i < NUM_TRAINING / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		training_set0[i].range(255, 224) =Input_1.read();
		training_set0[i].range(223, 192) =Input_1.read();
		training_set0[i].range(191, 160) =Input_1.read();
		training_set0[i].range(159, 128) =Input_1.read();
		training_set0[i].range(127, 96 ) =Input_1.read();
		training_set0[i].range(95 , 64 ) =Input_1.read();
		training_set0[i].range(63 , 32 ) =Input_1.read();
		training_set0[i].range(31 , 0  ) =Input_1.read();
	  }
	  for(int i = 0; i < NUM_TRAINING / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		training_set1[i].range(255, 224) =Input_1.read();
		training_set1[i].range(223, 192) =Input_1.read();
		training_set1[i].range(191, 160) =Input_1.read();
		training_set1[i].range(159, 128) =Input_1.read();
		training_set1[i].range(127, 96 ) =Input_1.read();
		training_set1[i].range(95 , 64 ) =Input_1.read();
		training_set1[i].range(63 , 32 ) =Input_1.read();
		training_set1[i].range(31 , 0  ) =Input_1.read();
	  }
	  for(int i = 0; i < NUM_TRAINING * (PAR_FACTOR - 2 * 2) / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		data_temp.range(255, 224) =Input_1.read();
		data_temp.range(223, 192) =Input_1.read();
		data_temp.range(191, 160) =Input_1.read();
		data_temp.range(159, 128) =Input_1.read();
		data_temp.range(127, 96 ) =Input_1.read();
		data_temp.range(95 , 64 ) =Input_1.read();
		data_temp.range(63 , 32 ) =Input_1.read();
		data_temp.range(31 , 0  ) =Input_1.read();
		Output_1.write(data_temp.range(255, 224));
		Output_1.write(data_temp.range(223, 192));
		Output_1.write(data_temp.range(191, 160));
		Output_1.write(data_temp.range(159, 128));
		Output_1.write(data_temp.range(127, 96 ));
		Output_1.write(data_temp.range(95 , 64 ));
		Output_1.write(data_temp.range(63 , 32 ));
		Output_1.write(data_temp.range(31 , 0  ));
	  }
	  index = 1;
	  return;
  }



  // get a test data and update knn value if index = 1
  // turn index to 2, then return
  if (index == 1)
  {
    WholeDigitType test_inst;
	// Get testing data
	test_inst.range(255, 224) =Input_1.read();
	test_inst.range(223, 192) =Input_1.read();
	test_inst.range(191, 160) =Input_1.read();
	test_inst.range(159, 128) =Input_1.read();
	test_inst.range(127, 96 ) =Input_1.read();
	test_inst.range(95 , 64 ) =Input_1.read();
	test_inst.range(63 , 32 ) =Input_1.read();
	test_inst.range(31 , 0  ) =Input_1.read();
	// Pass it to the next kernel
	Output_1.write(test_inst.range(255, 224));
	Output_1.write(test_inst.range(223, 192));
	Output_1.write(test_inst.range(191, 160));
	Output_1.write(test_inst.range(159, 128));
	Output_1.write(test_inst.range(127, 96 ));
	Output_1.write(test_inst.range(95 , 64 ));
	Output_1.write(test_inst.range(63 , 32 ));
	Output_1.write(test_inst.range(31 , 0  ));
	// Preset knn_set
	for(int i = 0; i < K_CONST; i++)
	{
		#pragma HLS unroll
		knn_set0[i] = 256;
		knn_set1[i] = 256;
	}

	TRAINING_LOOP_0 : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
	{
	  #pragma HLS pipeline
	  // Update the KNN set
	  // Compute the difference using XOR
	  WholeDigitType diff = test_inst ^ training_set0[i];
	  int dist = 0;

	  dist = popcount(diff);

	  int max_dist = 0;
	  int max_dist_id = K_CONST+1;
	  int k = 0;

	  // Find the max distance
	  FIND_MAX_DIST_0: for ( int k = 0; k < K_CONST; ++k )
	  {
		if ( knn_set0[k] > max_dist )
		{
		  max_dist = knn_set0[k];
		  max_dist_id = k;
		}
	  }

	  // Replace the entry with the max distance
	  if ( dist < max_dist )
		knn_set0[max_dist_id] = dist;
	}

	// Output knn_set
	for(int i = 0; i < K_CONST; i++)
	{
		Output_2.write(knn_set0[i]);
	}

	TRAINING_LOOP_1 : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
	{
	  #pragma HLS pipeline
	  // Update the KNN set
	  // Compute the difference using XOR
	  WholeDigitType diff = test_inst ^ training_set1[i];
	  int dist = 0;

	  dist = popcount(diff);

	  int max_dist = 0;
	  int max_dist_id = K_CONST+1;
	  int k = 0;

	  // Find the max distance
	  FIND_MAX_DIST_1: for ( int k = 0; k < K_CONST; ++k )
	  {
		if ( knn_set1[k] > max_dist )
		{
		  max_dist = knn_set1[k];
		  max_dist_id = k;
		}
	  }

	  // Replace the entry with the max distance
	  if ( dist < max_dist )
		knn_set1[max_dist_id] = dist;
	}
    index = 2;
    return;
  }


    // Output knn_set if index = 2
	// turn index to 1, then return
	if (index == 2){
	    for(int i = 0; i < K_CONST; i++)
	    {
	        Output_2.write(knn_set1[i]);
	    }

	    for(int i = 0; i < K_CONST * (PAR_FACTOR - 2 * 2); i ++)
	    {
	    	Output_2.write(Input_2.read());
	    }
	    index = 1;
	    return;
	}

  return;
}
void update_knn_cluster_2(hls::stream<ap_uint<32> > & Input_1, hls::stream<ap_uint<32> > & Output_1, hls::stream<ap_uint<32> > & Input_2, hls::stream<ap_uint<32> > & Output_2)
{
  #pragma HLS inline
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
#pragma HLS INTERFACE ap_hs port=Input_2
#pragma HLS INTERFACE ap_hs port=Output_2
  static int knn_set0[K_CONST];
  static int knn_set1[K_CONST];
#pragma HLS array_partition variable=knn_set0 complete dim=0
#pragma HLS array_partition variable=knn_set1 complete dim=0
  // Store 900 training data and pass all rest training data
  static WholeDigitType training_set0 [NUM_TRAINING / PAR_FACTOR];
  static WholeDigitType training_set1 [NUM_TRAINING / PAR_FACTOR];
  const int unroll_factor = PAR_FACTOR;
#pragma HLS array_partition variable=training_set0 block factor=unroll_factor dim=0
#pragma HLS array_partition variable=training_set1 block factor=unroll_factor dim=0
  WholeDigitType data_temp;
  static int index = 0;
  // read training data if index = 0
  // turn index to 1, then return
  if (index == 0)
  {
	  for(int i = 0; i < NUM_TRAINING / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		training_set0[i].range(255, 224) =Input_1.read();
		training_set0[i].range(223, 192) =Input_1.read();
		training_set0[i].range(191, 160) =Input_1.read();
		training_set0[i].range(159, 128) =Input_1.read();
		training_set0[i].range(127, 96 ) =Input_1.read();
		training_set0[i].range(95 , 64 ) =Input_1.read();
		training_set0[i].range(63 , 32 ) =Input_1.read();
		training_set0[i].range(31 , 0  ) =Input_1.read();
	  }
	  for(int i = 0; i < NUM_TRAINING / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		training_set1[i].range(255, 224) =Input_1.read();
		training_set1[i].range(223, 192) =Input_1.read();
		training_set1[i].range(191, 160) =Input_1.read();
		training_set1[i].range(159, 128) =Input_1.read();
		training_set1[i].range(127, 96 ) =Input_1.read();
		training_set1[i].range(95 , 64 ) =Input_1.read();
		training_set1[i].range(63 , 32 ) =Input_1.read();
		training_set1[i].range(31 , 0  ) =Input_1.read();
	  }
	  for(int i = 0; i < NUM_TRAINING * (PAR_FACTOR - 2 * 3) / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		data_temp.range(255, 224) =Input_1.read();
		data_temp.range(223, 192) =Input_1.read();
		data_temp.range(191, 160) =Input_1.read();
		data_temp.range(159, 128) =Input_1.read();
		data_temp.range(127, 96 ) =Input_1.read();
		data_temp.range(95 , 64 ) =Input_1.read();
		data_temp.range(63 , 32 ) =Input_1.read();
		data_temp.range(31 , 0  ) =Input_1.read();
		Output_1.write(data_temp.range(255, 224));
		Output_1.write(data_temp.range(223, 192));
		Output_1.write(data_temp.range(191, 160));
		Output_1.write(data_temp.range(159, 128));
		Output_1.write(data_temp.range(127, 96 ));
		Output_1.write(data_temp.range(95 , 64 ));
		Output_1.write(data_temp.range(63 , 32 ));
		Output_1.write(data_temp.range(31 , 0  ));
	  }
	  index = 1;
	  return;
  }



  // get a test data and update knn value if index = 1
  // turn index to 2, then return
  if (index == 1)
  {
    WholeDigitType test_inst;
	// Get testing data
	test_inst.range(255, 224) =Input_1.read();
	test_inst.range(223, 192) =Input_1.read();
	test_inst.range(191, 160) =Input_1.read();
	test_inst.range(159, 128) =Input_1.read();
	test_inst.range(127, 96 ) =Input_1.read();
	test_inst.range(95 , 64 ) =Input_1.read();
	test_inst.range(63 , 32 ) =Input_1.read();
	test_inst.range(31 , 0  ) =Input_1.read();
	// Pass it to the next kernel
	Output_1.write(test_inst.range(255, 224));
	Output_1.write(test_inst.range(223, 192));
	Output_1.write(test_inst.range(191, 160));
	Output_1.write(test_inst.range(159, 128));
	Output_1.write(test_inst.range(127, 96 ));
	Output_1.write(test_inst.range(95 , 64 ));
	Output_1.write(test_inst.range(63 , 32 ));
	Output_1.write(test_inst.range(31 , 0  ));
	// Preset knn_set
	for(int i = 0; i < K_CONST; i++)
	{
		#pragma HLS unroll
		knn_set0[i] = 256;
		knn_set1[i] = 256;
	}

	TRAINING_LOOP_0 : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
	{
	  #pragma HLS pipeline
	  // Update the KNN set
	  // Compute the difference using XOR
	  WholeDigitType diff = test_inst ^ training_set0[i];
	  int dist = 0;

	  dist = popcount(diff);

	  int max_dist = 0;
	  int max_dist_id = K_CONST+1;
	  int k = 0;

	  // Find the max distance
	  FIND_MAX_DIST_0: for ( int k = 0; k < K_CONST; ++k )
	  {
		if ( knn_set0[k] > max_dist )
		{
		  max_dist = knn_set0[k];
		  max_dist_id = k;
		}
	  }

	  // Replace the entry with the max distance
	  if ( dist < max_dist )
		knn_set0[max_dist_id] = dist;
	}

	// Output knn_set
	for(int i = 0; i < K_CONST; i++)
	{
		Output_2.write(knn_set0[i]);
	}

	TRAINING_LOOP_1 : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
	{
	  #pragma HLS pipeline
	  // Update the KNN set
	  // Compute the difference using XOR
	  WholeDigitType diff = test_inst ^ training_set1[i];
	  int dist = 0;

	  dist = popcount(diff);

	  int max_dist = 0;
	  int max_dist_id = K_CONST+1;
	  int k = 0;

	  // Find the max distance
	  FIND_MAX_DIST_1: for ( int k = 0; k < K_CONST; ++k )
	  {
		if ( knn_set1[k] > max_dist )
		{
		  max_dist = knn_set1[k];
		  max_dist_id = k;
		}
	  }

	  // Replace the entry with the max distance
	  if ( dist < max_dist )
		knn_set1[max_dist_id] = dist;
	}
    index = 2;
    return;
  }


    // Output knn_set if index = 2
	// turn index to 1, then return
	if (index == 2){
	    for(int i = 0; i < K_CONST; i++)
	    {
	        Output_2.write(knn_set1[i]);
	    }

	    for(int i = 0; i < K_CONST * (PAR_FACTOR - 2 * 3); i ++)
	    {
	    	Output_2.write(Input_2.read());
	    }
	    index = 1;
	    return;
	}

  return;
}



void update_knn_cluster_3(hls::stream<ap_uint<32> > & Input_1, hls::stream<ap_uint<32> > & Output_1, hls::stream<ap_uint<32> > & Input_2, hls::stream<ap_uint<32> > & Output_2)
{
  #pragma HLS inline
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
#pragma HLS INTERFACE ap_hs port=Input_2
#pragma HLS INTERFACE ap_hs port=Output_2
  static int knn_set0[K_CONST];
  static int knn_set1[K_CONST];
#pragma HLS array_partition variable=knn_set0 complete dim=0
#pragma HLS array_partition variable=knn_set1 complete dim=0
  // Store 900 training data and pass all rest training data
  static WholeDigitType training_set0 [NUM_TRAINING / PAR_FACTOR];
  static WholeDigitType training_set1 [NUM_TRAINING / PAR_FACTOR];
  const int unroll_factor = PAR_FACTOR;
#pragma HLS array_partition variable=training_set0 block factor=unroll_factor dim=0
#pragma HLS array_partition variable=training_set1 block factor=unroll_factor dim=0
  WholeDigitType data_temp;
  static int index = 0;
  // read training data if index = 0
  // turn index to 1, then return
  if (index == 0)
  {
	  for(int i = 0; i < NUM_TRAINING / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		training_set0[i].range(255, 224) =Input_1.read();
		training_set0[i].range(223, 192) =Input_1.read();
		training_set0[i].range(191, 160) =Input_1.read();
		training_set0[i].range(159, 128) =Input_1.read();
		training_set0[i].range(127, 96 ) =Input_1.read();
		training_set0[i].range(95 , 64 ) =Input_1.read();
		training_set0[i].range(63 , 32 ) =Input_1.read();
		training_set0[i].range(31 , 0  ) =Input_1.read();
	  }
	  for(int i = 0; i < NUM_TRAINING / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		training_set1[i].range(255, 224) =Input_1.read();
		training_set1[i].range(223, 192) =Input_1.read();
		training_set1[i].range(191, 160) =Input_1.read();
		training_set1[i].range(159, 128) =Input_1.read();
		training_set1[i].range(127, 96 ) =Input_1.read();
		training_set1[i].range(95 , 64 ) =Input_1.read();
		training_set1[i].range(63 , 32 ) =Input_1.read();
		training_set1[i].range(31 , 0  ) =Input_1.read();
	  }
	  for(int i = 0; i < NUM_TRAINING * (PAR_FACTOR - 2 * 4) / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		data_temp.range(255, 224) =Input_1.read();
		data_temp.range(223, 192) =Input_1.read();
		data_temp.range(191, 160) =Input_1.read();
		data_temp.range(159, 128) =Input_1.read();
		data_temp.range(127, 96 ) =Input_1.read();
		data_temp.range(95 , 64 ) =Input_1.read();
		data_temp.range(63 , 32 ) =Input_1.read();
		data_temp.range(31 , 0  ) =Input_1.read();
		Output_1.write(data_temp.range(255, 224));
		Output_1.write(data_temp.range(223, 192));
		Output_1.write(data_temp.range(191, 160));
		Output_1.write(data_temp.range(159, 128));
		Output_1.write(data_temp.range(127, 96 ));
		Output_1.write(data_temp.range(95 , 64 ));
		Output_1.write(data_temp.range(63 , 32 ));
		Output_1.write(data_temp.range(31 , 0  ));
	  }
	  index = 1;
	  return;
  }



  // get a test data and update knn value if index = 1
  // turn index to 2, then return
  if (index == 1)
  {
    WholeDigitType test_inst;
	// Get testing data
	test_inst.range(255, 224) =Input_1.read();
	test_inst.range(223, 192) =Input_1.read();
	test_inst.range(191, 160) =Input_1.read();
	test_inst.range(159, 128) =Input_1.read();
	test_inst.range(127, 96 ) =Input_1.read();
	test_inst.range(95 , 64 ) =Input_1.read();
	test_inst.range(63 , 32 ) =Input_1.read();
	test_inst.range(31 , 0  ) =Input_1.read();
	// Pass it to the next kernel
	Output_1.write(test_inst.range(255, 224));
	Output_1.write(test_inst.range(223, 192));
	Output_1.write(test_inst.range(191, 160));
	Output_1.write(test_inst.range(159, 128));
	Output_1.write(test_inst.range(127, 96 ));
	Output_1.write(test_inst.range(95 , 64 ));
	Output_1.write(test_inst.range(63 , 32 ));
	Output_1.write(test_inst.range(31 , 0  ));
	// Preset knn_set
	for(int i = 0; i < K_CONST; i++)
	{
		#pragma HLS unroll
		knn_set0[i] = 256;
		knn_set1[i] = 256;
	}

	TRAINING_LOOP_0 : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
	{
	  #pragma HLS pipeline
	  // Update the KNN set
	  // Compute the difference using XOR
	  WholeDigitType diff = test_inst ^ training_set0[i];
	  int dist = 0;

	  dist = popcount(diff);

	  int max_dist = 0;
	  int max_dist_id = K_CONST+1;
	  int k = 0;

	  // Find the max distance
	  FIND_MAX_DIST_0: for ( int k = 0; k < K_CONST; ++k )
	  {
		if ( knn_set0[k] > max_dist )
		{
		  max_dist = knn_set0[k];
		  max_dist_id = k;
		}
	  }

	  // Replace the entry with the max distance
	  if ( dist < max_dist )
		knn_set0[max_dist_id] = dist;
	}

	// Output knn_set
	for(int i = 0; i < K_CONST; i++)
	{
		Output_2.write(knn_set0[i]);
	}

	TRAINING_LOOP_1 : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
	{
	  #pragma HLS pipeline
	  // Update the KNN set
	  // Compute the difference using XOR
	  WholeDigitType diff = test_inst ^ training_set1[i];
	  int dist = 0;

	  dist = popcount(diff);

	  int max_dist = 0;
	  int max_dist_id = K_CONST+1;
	  int k = 0;

	  // Find the max distance
	  FIND_MAX_DIST_1: for ( int k = 0; k < K_CONST; ++k )
	  {
		if ( knn_set1[k] > max_dist )
		{
		  max_dist = knn_set1[k];
		  max_dist_id = k;
		}
	  }

	  // Replace the entry with the max distance
	  if ( dist < max_dist )
		knn_set1[max_dist_id] = dist;
	}
    index = 2;
    return;
  }


    // Output knn_set if index = 2
	// turn index to 1, then return
	if (index == 2){
	    for(int i = 0; i < K_CONST; i++)
	    {
	        Output_2.write(knn_set1[i]);
	    }

	    for(int i = 0; i < K_CONST * (PAR_FACTOR - 2 * 4); i ++)
	    {
	    	Output_2.write(Input_2.read());
	    }
	    index = 1;
	    return;
	}

  return;
}
void update_knn_cluster_4(hls::stream<ap_uint<32> > & Input_1, hls::stream<ap_uint<32> > & Output_1, hls::stream<ap_uint<32> > & Input_2, hls::stream<ap_uint<32> > & Output_2)
{
  #pragma HLS inline
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
#pragma HLS INTERFACE ap_hs port=Input_2
#pragma HLS INTERFACE ap_hs port=Output_2
  static int knn_set0[K_CONST];
  static int knn_set1[K_CONST];
#pragma HLS array_partition variable=knn_set0 complete dim=0
#pragma HLS array_partition variable=knn_set1 complete dim=0
  // Store 900 training data and pass all rest training data
  static WholeDigitType training_set0 [NUM_TRAINING / PAR_FACTOR];
  static WholeDigitType training_set1 [NUM_TRAINING / PAR_FACTOR];
  const int unroll_factor = PAR_FACTOR;
#pragma HLS array_partition variable=training_set0 block factor=unroll_factor dim=0
#pragma HLS array_partition variable=training_set1 block factor=unroll_factor dim=0
  WholeDigitType data_temp;
  static int index = 0;
  // read training data if index = 0
  // turn index to 1, then return
  if (index == 0)
  {
	  for(int i = 0; i < NUM_TRAINING / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		training_set0[i].range(255, 224) =Input_1.read();
		training_set0[i].range(223, 192) =Input_1.read();
		training_set0[i].range(191, 160) =Input_1.read();
		training_set0[i].range(159, 128) =Input_1.read();
		training_set0[i].range(127, 96 ) =Input_1.read();
		training_set0[i].range(95 , 64 ) =Input_1.read();
		training_set0[i].range(63 , 32 ) =Input_1.read();
		training_set0[i].range(31 , 0  ) =Input_1.read();
	  }
	  for(int i = 0; i < NUM_TRAINING / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		training_set1[i].range(255, 224) =Input_1.read();
		training_set1[i].range(223, 192) =Input_1.read();
		training_set1[i].range(191, 160) =Input_1.read();
		training_set1[i].range(159, 128) =Input_1.read();
		training_set1[i].range(127, 96 ) =Input_1.read();
		training_set1[i].range(95 , 64 ) =Input_1.read();
		training_set1[i].range(63 , 32 ) =Input_1.read();
		training_set1[i].range(31 , 0  ) =Input_1.read();
	  }
	  for(int i = 0; i < NUM_TRAINING * (PAR_FACTOR - 2 * 5) / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		data_temp.range(255, 224) =Input_1.read();
		data_temp.range(223, 192) =Input_1.read();
		data_temp.range(191, 160) =Input_1.read();
		data_temp.range(159, 128) =Input_1.read();
		data_temp.range(127, 96 ) =Input_1.read();
		data_temp.range(95 , 64 ) =Input_1.read();
		data_temp.range(63 , 32 ) =Input_1.read();
		data_temp.range(31 , 0  ) =Input_1.read();
		Output_1.write(data_temp.range(255, 224));
		Output_1.write(data_temp.range(223, 192));
		Output_1.write(data_temp.range(191, 160));
		Output_1.write(data_temp.range(159, 128));
		Output_1.write(data_temp.range(127, 96 ));
		Output_1.write(data_temp.range(95 , 64 ));
		Output_1.write(data_temp.range(63 , 32 ));
		Output_1.write(data_temp.range(31 , 0  ));
	  }
	  index = 1;
	  return;
  }



  // get a test data and update knn value if index = 1
  // turn index to 2, then return
  if (index == 1)
  {
    WholeDigitType test_inst;
	// Get testing data
	test_inst.range(255, 224) =Input_1.read();
	test_inst.range(223, 192) =Input_1.read();
	test_inst.range(191, 160) =Input_1.read();
	test_inst.range(159, 128) =Input_1.read();
	test_inst.range(127, 96 ) =Input_1.read();
	test_inst.range(95 , 64 ) =Input_1.read();
	test_inst.range(63 , 32 ) =Input_1.read();
	test_inst.range(31 , 0  ) =Input_1.read();
	// Pass it to the next kernel
	Output_1.write(test_inst.range(255, 224));
	Output_1.write(test_inst.range(223, 192));
	Output_1.write(test_inst.range(191, 160));
	Output_1.write(test_inst.range(159, 128));
	Output_1.write(test_inst.range(127, 96 ));
	Output_1.write(test_inst.range(95 , 64 ));
	Output_1.write(test_inst.range(63 , 32 ));
	Output_1.write(test_inst.range(31 , 0  ));
	// Preset knn_set
	for(int i = 0; i < K_CONST; i++)
	{
		#pragma HLS unroll
		knn_set0[i] = 256;
		knn_set1[i] = 256;
	}

	TRAINING_LOOP_0 : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
	{
	  #pragma HLS pipeline
	  // Update the KNN set
	  // Compute the difference using XOR
	  WholeDigitType diff = test_inst ^ training_set0[i];
	  int dist = 0;

	  dist = popcount(diff);

	  int max_dist = 0;
	  int max_dist_id = K_CONST+1;
	  int k = 0;

	  // Find the max distance
	  FIND_MAX_DIST_0: for ( int k = 0; k < K_CONST; ++k )
	  {
		if ( knn_set0[k] > max_dist )
		{
		  max_dist = knn_set0[k];
		  max_dist_id = k;
		}
	  }

	  // Replace the entry with the max distance
	  if ( dist < max_dist )
		knn_set0[max_dist_id] = dist;
	}

	// Output knn_set
	for(int i = 0; i < K_CONST; i++)
	{
		Output_2.write(knn_set0[i]);
	}

	TRAINING_LOOP_1 : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
	{
	  #pragma HLS pipeline
	  // Update the KNN set
	  // Compute the difference using XOR
	  WholeDigitType diff = test_inst ^ training_set1[i];
	  int dist = 0;

	  dist = popcount(diff);

	  int max_dist = 0;
	  int max_dist_id = K_CONST+1;
	  int k = 0;

	  // Find the max distance
	  FIND_MAX_DIST_1: for ( int k = 0; k < K_CONST; ++k )
	  {
		if ( knn_set1[k] > max_dist )
		{
		  max_dist = knn_set1[k];
		  max_dist_id = k;
		}
	  }

	  // Replace the entry with the max distance
	  if ( dist < max_dist )
		knn_set1[max_dist_id] = dist;
	}
    index = 2;
    return;
  }


    // Output knn_set if index = 2
	// turn index to 1, then return
	if (index == 2){
	    for(int i = 0; i < K_CONST; i++)
	    {
	        Output_2.write(knn_set1[i]);
	    }

	    for(int i = 0; i < K_CONST * (PAR_FACTOR - 2 * 5); i ++)
	    {
	    	Output_2.write(Input_2.read());
	    }
	    index = 1;
	    return;
	}

  return;
}
void update_knn_cluster_5(hls::stream<ap_uint<32> > & Input_1, hls::stream<ap_uint<32> > & Output_1, hls::stream<ap_uint<32> > & Input_2, hls::stream<ap_uint<32> > & Output_2)
{
  #pragma HLS inline
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
#pragma HLS INTERFACE ap_hs port=Input_2
#pragma HLS INTERFACE ap_hs port=Output_2
  static int knn_set0[K_CONST];
  static int knn_set1[K_CONST];
#pragma HLS array_partition variable=knn_set0 complete dim=0
#pragma HLS array_partition variable=knn_set1 complete dim=0
  // Store 900 training data and pass all rest training data
  static WholeDigitType training_set0 [NUM_TRAINING / PAR_FACTOR];
  static WholeDigitType training_set1 [NUM_TRAINING / PAR_FACTOR];
  const int unroll_factor = PAR_FACTOR;
#pragma HLS array_partition variable=training_set0 block factor=unroll_factor dim=0
#pragma HLS array_partition variable=training_set1 block factor=unroll_factor dim=0
  WholeDigitType data_temp;
  static int index = 0;
  // read training data if index = 0
  // turn index to 1, then return
  if (index == 0)
  {
	  for(int i = 0; i < NUM_TRAINING / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		training_set0[i].range(255, 224) =Input_1.read();
		training_set0[i].range(223, 192) =Input_1.read();
		training_set0[i].range(191, 160) =Input_1.read();
		training_set0[i].range(159, 128) =Input_1.read();
		training_set0[i].range(127, 96 ) =Input_1.read();
		training_set0[i].range(95 , 64 ) =Input_1.read();
		training_set0[i].range(63 , 32 ) =Input_1.read();
		training_set0[i].range(31 , 0  ) =Input_1.read();
	  }
	  for(int i = 0; i < NUM_TRAINING / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		training_set1[i].range(255, 224) =Input_1.read();
		training_set1[i].range(223, 192) =Input_1.read();
		training_set1[i].range(191, 160) =Input_1.read();
		training_set1[i].range(159, 128) =Input_1.read();
		training_set1[i].range(127, 96 ) =Input_1.read();
		training_set1[i].range(95 , 64 ) =Input_1.read();
		training_set1[i].range(63 , 32 ) =Input_1.read();
		training_set1[i].range(31 , 0  ) =Input_1.read();
	  }
	  for(int i = 0; i < NUM_TRAINING * (PAR_FACTOR - 2 * 6) / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		data_temp.range(255, 224) =Input_1.read();
		data_temp.range(223, 192) =Input_1.read();
		data_temp.range(191, 160) =Input_1.read();
		data_temp.range(159, 128) =Input_1.read();
		data_temp.range(127, 96 ) =Input_1.read();
		data_temp.range(95 , 64 ) =Input_1.read();
		data_temp.range(63 , 32 ) =Input_1.read();
		data_temp.range(31 , 0  ) =Input_1.read();
		Output_1.write(data_temp.range(255, 224));
		Output_1.write(data_temp.range(223, 192));
		Output_1.write(data_temp.range(191, 160));
		Output_1.write(data_temp.range(159, 128));
		Output_1.write(data_temp.range(127, 96 ));
		Output_1.write(data_temp.range(95 , 64 ));
		Output_1.write(data_temp.range(63 , 32 ));
		Output_1.write(data_temp.range(31 , 0  ));
	  }
	  index = 1;
	  return;
  }



  // get a test data and update knn value if index = 1
  // turn index to 2, then return
  if (index == 1)
  {
    WholeDigitType test_inst;
	// Get testing data
	test_inst.range(255, 224) =Input_1.read();
	test_inst.range(223, 192) =Input_1.read();
	test_inst.range(191, 160) =Input_1.read();
	test_inst.range(159, 128) =Input_1.read();
	test_inst.range(127, 96 ) =Input_1.read();
	test_inst.range(95 , 64 ) =Input_1.read();
	test_inst.range(63 , 32 ) =Input_1.read();
	test_inst.range(31 , 0  ) =Input_1.read();
	// Pass it to the next kernel
	Output_1.write(test_inst.range(255, 224));
	Output_1.write(test_inst.range(223, 192));
	Output_1.write(test_inst.range(191, 160));
	Output_1.write(test_inst.range(159, 128));
	Output_1.write(test_inst.range(127, 96 ));
	Output_1.write(test_inst.range(95 , 64 ));
	Output_1.write(test_inst.range(63 , 32 ));
	Output_1.write(test_inst.range(31 , 0  ));
	// Preset knn_set
	for(int i = 0; i < K_CONST; i++)
	{
		#pragma HLS unroll
		knn_set0[i] = 256;
		knn_set1[i] = 256;
	}

	TRAINING_LOOP_0 : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
	{
	  #pragma HLS pipeline
	  // Update the KNN set
	  // Compute the difference using XOR
	  WholeDigitType diff = test_inst ^ training_set0[i];
	  int dist = 0;

	  dist = popcount(diff);

	  int max_dist = 0;
	  int max_dist_id = K_CONST+1;
	  int k = 0;

	  // Find the max distance
	  FIND_MAX_DIST_0: for ( int k = 0; k < K_CONST; ++k )
	  {
		if ( knn_set0[k] > max_dist )
		{
		  max_dist = knn_set0[k];
		  max_dist_id = k;
		}
	  }

	  // Replace the entry with the max distance
	  if ( dist < max_dist )
		knn_set0[max_dist_id] = dist;
	}

	// Output knn_set
	for(int i = 0; i < K_CONST; i++)
	{
		Output_2.write(knn_set0[i]);
	}

	TRAINING_LOOP_1 : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
	{
	  #pragma HLS pipeline
	  // Update the KNN set
	  // Compute the difference using XOR
	  WholeDigitType diff = test_inst ^ training_set1[i];
	  int dist = 0;

	  dist = popcount(diff);

	  int max_dist = 0;
	  int max_dist_id = K_CONST+1;
	  int k = 0;

	  // Find the max distance
	  FIND_MAX_DIST_1: for ( int k = 0; k < K_CONST; ++k )
	  {
		if ( knn_set1[k] > max_dist )
		{
		  max_dist = knn_set1[k];
		  max_dist_id = k;
		}
	  }

	  // Replace the entry with the max distance
	  if ( dist < max_dist )
		knn_set1[max_dist_id] = dist;
	}
    index = 2;
    return;
  }


    // Output knn_set if index = 2
	// turn index to 1, then return
	if (index == 2){
	    for(int i = 0; i < K_CONST; i++)
	    {
	        Output_2.write(knn_set1[i]);
	    }

	    for(int i = 0; i < K_CONST * (PAR_FACTOR - 2 * 6); i ++)
	    {
	    	Output_2.write(Input_2.read());
	    }
	    index = 1;
	    return;
	}

  return;
}
void update_knn_cluster_6(hls::stream<ap_uint<32> > & Input_1, hls::stream<ap_uint<32> > & Output_1, hls::stream<ap_uint<32> > & Input_2, hls::stream<ap_uint<32> > & Output_2)
{
  #pragma HLS inline
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
#pragma HLS INTERFACE ap_hs port=Input_2
#pragma HLS INTERFACE ap_hs port=Output_2
  static int knn_set0[K_CONST];
  static int knn_set1[K_CONST];
#pragma HLS array_partition variable=knn_set0 complete dim=0
#pragma HLS array_partition variable=knn_set1 complete dim=0
  // Store 900 training data and pass all rest training data
  static WholeDigitType training_set0 [NUM_TRAINING / PAR_FACTOR];
  static WholeDigitType training_set1 [NUM_TRAINING / PAR_FACTOR];
  const int unroll_factor = PAR_FACTOR;
#pragma HLS array_partition variable=training_set0 block factor=unroll_factor dim=0
#pragma HLS array_partition variable=training_set1 block factor=unroll_factor dim=0
  WholeDigitType data_temp;
  static int index = 0;
  // read training data if index = 0
  // turn index to 1, then return
  if (index == 0)
  {
	  for(int i = 0; i < NUM_TRAINING / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		training_set0[i].range(255, 224) =Input_1.read();
		training_set0[i].range(223, 192) =Input_1.read();
		training_set0[i].range(191, 160) =Input_1.read();
		training_set0[i].range(159, 128) =Input_1.read();
		training_set0[i].range(127, 96 ) =Input_1.read();
		training_set0[i].range(95 , 64 ) =Input_1.read();
		training_set0[i].range(63 , 32 ) =Input_1.read();
		training_set0[i].range(31 , 0  ) =Input_1.read();
	  }
	  for(int i = 0; i < NUM_TRAINING / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		training_set1[i].range(255, 224) =Input_1.read();
		training_set1[i].range(223, 192) =Input_1.read();
		training_set1[i].range(191, 160) =Input_1.read();
		training_set1[i].range(159, 128) =Input_1.read();
		training_set1[i].range(127, 96 ) =Input_1.read();
		training_set1[i].range(95 , 64 ) =Input_1.read();
		training_set1[i].range(63 , 32 ) =Input_1.read();
		training_set1[i].range(31 , 0  ) =Input_1.read();
	  }
	  for(int i = 0; i < NUM_TRAINING * (PAR_FACTOR - 2 * 7) / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		data_temp.range(255, 224) =Input_1.read();
		data_temp.range(223, 192) =Input_1.read();
		data_temp.range(191, 160) =Input_1.read();
		data_temp.range(159, 128) =Input_1.read();
		data_temp.range(127, 96 ) =Input_1.read();
		data_temp.range(95 , 64 ) =Input_1.read();
		data_temp.range(63 , 32 ) =Input_1.read();
		data_temp.range(31 , 0  ) =Input_1.read();
		Output_1.write(data_temp.range(255, 224));
		Output_1.write(data_temp.range(223, 192));
		Output_1.write(data_temp.range(191, 160));
		Output_1.write(data_temp.range(159, 128));
		Output_1.write(data_temp.range(127, 96 ));
		Output_1.write(data_temp.range(95 , 64 ));
		Output_1.write(data_temp.range(63 , 32 ));
		Output_1.write(data_temp.range(31 , 0  ));
	  }
	  index = 1;
	  return;
  }



  // get a test data and update knn value if index = 1
  // turn index to 2, then return
  if (index == 1)
  {
    WholeDigitType test_inst;
	// Get testing data
	test_inst.range(255, 224) =Input_1.read();
	test_inst.range(223, 192) =Input_1.read();
	test_inst.range(191, 160) =Input_1.read();
	test_inst.range(159, 128) =Input_1.read();
	test_inst.range(127, 96 ) =Input_1.read();
	test_inst.range(95 , 64 ) =Input_1.read();
	test_inst.range(63 , 32 ) =Input_1.read();
	test_inst.range(31 , 0  ) =Input_1.read();
	// Pass it to the next kernel
	Output_1.write(test_inst.range(255, 224));
	Output_1.write(test_inst.range(223, 192));
	Output_1.write(test_inst.range(191, 160));
	Output_1.write(test_inst.range(159, 128));
	Output_1.write(test_inst.range(127, 96 ));
	Output_1.write(test_inst.range(95 , 64 ));
	Output_1.write(test_inst.range(63 , 32 ));
	Output_1.write(test_inst.range(31 , 0  ));
	// Preset knn_set
	for(int i = 0; i < K_CONST; i++)
	{
		#pragma HLS unroll
		knn_set0[i] = 256;
		knn_set1[i] = 256;
	}

	TRAINING_LOOP_0 : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
	{
	  #pragma HLS pipeline
	  // Update the KNN set
	  // Compute the difference using XOR
	  WholeDigitType diff = test_inst ^ training_set0[i];
	  int dist = 0;

	  dist = popcount(diff);

	  int max_dist = 0;
	  int max_dist_id = K_CONST+1;
	  int k = 0;

	  // Find the max distance
	  FIND_MAX_DIST_0: for ( int k = 0; k < K_CONST; ++k )
	  {
		if ( knn_set0[k] > max_dist )
		{
		  max_dist = knn_set0[k];
		  max_dist_id = k;
		}
	  }

	  // Replace the entry with the max distance
	  if ( dist < max_dist )
		knn_set0[max_dist_id] = dist;
	}

	// Output knn_set
	for(int i = 0; i < K_CONST; i++)
	{
		Output_2.write(knn_set0[i]);
	}

	TRAINING_LOOP_1 : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
	{
	  #pragma HLS pipeline
	  // Update the KNN set
	  // Compute the difference using XOR
	  WholeDigitType diff = test_inst ^ training_set1[i];
	  int dist = 0;

	  dist = popcount(diff);

	  int max_dist = 0;
	  int max_dist_id = K_CONST+1;
	  int k = 0;

	  // Find the max distance
	  FIND_MAX_DIST_1: for ( int k = 0; k < K_CONST; ++k )
	  {
		if ( knn_set1[k] > max_dist )
		{
		  max_dist = knn_set1[k];
		  max_dist_id = k;
		}
	  }

	  // Replace the entry with the max distance
	  if ( dist < max_dist )
		knn_set1[max_dist_id] = dist;
	}
    index = 2;
    return;
  }


    // Output knn_set if index = 2
	// turn index to 1, then return
	if (index == 2){
	    for(int i = 0; i < K_CONST; i++)
	    {
	        Output_2.write(knn_set1[i]);
	    }

	    for(int i = 0; i < K_CONST * (PAR_FACTOR - 2 * 7); i ++)
	    {
	    	Output_2.write(Input_2.read());
	    }
	    index = 1;
	    return;
	}

  return;
}
void update_knn_cluster_7(hls::stream<ap_uint<32> > & Input_1, hls::stream<ap_uint<32> > & Output_1, hls::stream<ap_uint<32> > & Input_2, hls::stream<ap_uint<32> > & Output_2)
{
  #pragma HLS inline
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
#pragma HLS INTERFACE ap_hs port=Input_2
#pragma HLS INTERFACE ap_hs port=Output_2
  static int knn_set0[K_CONST];
  static int knn_set1[K_CONST];
#pragma HLS array_partition variable=knn_set0 complete dim=0
#pragma HLS array_partition variable=knn_set1 complete dim=0
  // Store 900 training data and pass all rest training data
  static WholeDigitType training_set0 [NUM_TRAINING / PAR_FACTOR];
  static WholeDigitType training_set1 [NUM_TRAINING / PAR_FACTOR];
  const int unroll_factor = PAR_FACTOR;
#pragma HLS array_partition variable=training_set0 block factor=unroll_factor dim=0
#pragma HLS array_partition variable=training_set1 block factor=unroll_factor dim=0
  WholeDigitType data_temp;
  static int index = 0;
  // read training data if index = 0
  // turn index to 1, then return
  if (index == 0)
  {
	  for(int i = 0; i < NUM_TRAINING / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		training_set0[i].range(255, 224) =Input_1.read();
		training_set0[i].range(223, 192) =Input_1.read();
		training_set0[i].range(191, 160) =Input_1.read();
		training_set0[i].range(159, 128) =Input_1.read();
		training_set0[i].range(127, 96 ) =Input_1.read();
		training_set0[i].range(95 , 64 ) =Input_1.read();
		training_set0[i].range(63 , 32 ) =Input_1.read();
		training_set0[i].range(31 , 0  ) =Input_1.read();
	  }
	  for(int i = 0; i < NUM_TRAINING / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		training_set1[i].range(255, 224) =Input_1.read();
		training_set1[i].range(223, 192) =Input_1.read();
		training_set1[i].range(191, 160) =Input_1.read();
		training_set1[i].range(159, 128) =Input_1.read();
		training_set1[i].range(127, 96 ) =Input_1.read();
		training_set1[i].range(95 , 64 ) =Input_1.read();
		training_set1[i].range(63 , 32 ) =Input_1.read();
		training_set1[i].range(31 , 0  ) =Input_1.read();
	  }
	  for(int i = 0; i < NUM_TRAINING * (PAR_FACTOR - 2 * 8) / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		data_temp.range(255, 224) =Input_1.read();
		data_temp.range(223, 192) =Input_1.read();
		data_temp.range(191, 160) =Input_1.read();
		data_temp.range(159, 128) =Input_1.read();
		data_temp.range(127, 96 ) =Input_1.read();
		data_temp.range(95 , 64 ) =Input_1.read();
		data_temp.range(63 , 32 ) =Input_1.read();
		data_temp.range(31 , 0  ) =Input_1.read();
		Output_1.write(data_temp.range(255, 224));
		Output_1.write(data_temp.range(223, 192));
		Output_1.write(data_temp.range(191, 160));
		Output_1.write(data_temp.range(159, 128));
		Output_1.write(data_temp.range(127, 96 ));
		Output_1.write(data_temp.range(95 , 64 ));
		Output_1.write(data_temp.range(63 , 32 ));
		Output_1.write(data_temp.range(31 , 0  ));
	  }
	  index = 1;
	  return;
  }



  // get a test data and update knn value if index = 1
  // turn index to 2, then return
  if (index == 1)
  {
    WholeDigitType test_inst;
	// Get testing data
	test_inst.range(255, 224) =Input_1.read();
	test_inst.range(223, 192) =Input_1.read();
	test_inst.range(191, 160) =Input_1.read();
	test_inst.range(159, 128) =Input_1.read();
	test_inst.range(127, 96 ) =Input_1.read();
	test_inst.range(95 , 64 ) =Input_1.read();
	test_inst.range(63 , 32 ) =Input_1.read();
	test_inst.range(31 , 0  ) =Input_1.read();
	// Pass it to the next kernel
	Output_1.write(test_inst.range(255, 224));
	Output_1.write(test_inst.range(223, 192));
	Output_1.write(test_inst.range(191, 160));
	Output_1.write(test_inst.range(159, 128));
	Output_1.write(test_inst.range(127, 96 ));
	Output_1.write(test_inst.range(95 , 64 ));
	Output_1.write(test_inst.range(63 , 32 ));
	Output_1.write(test_inst.range(31 , 0  ));
	// Preset knn_set
	for(int i = 0; i < K_CONST; i++)
	{
		#pragma HLS unroll
		knn_set0[i] = 256;
		knn_set1[i] = 256;
	}

	TRAINING_LOOP_0 : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
	{
	  #pragma HLS pipeline
	  // Update the KNN set
	  // Compute the difference using XOR
	  WholeDigitType diff = test_inst ^ training_set0[i];
	  int dist = 0;

	  dist = popcount(diff);

	  int max_dist = 0;
	  int max_dist_id = K_CONST+1;
	  int k = 0;

	  // Find the max distance
	  FIND_MAX_DIST_0: for ( int k = 0; k < K_CONST; ++k )
	  {
		if ( knn_set0[k] > max_dist )
		{
		  max_dist = knn_set0[k];
		  max_dist_id = k;
		}
	  }

	  // Replace the entry with the max distance
	  if ( dist < max_dist )
		knn_set0[max_dist_id] = dist;
	}

	// Output knn_set
	for(int i = 0; i < K_CONST; i++)
	{
		Output_2.write(knn_set0[i]);
	}

	TRAINING_LOOP_1 : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
	{
	  #pragma HLS pipeline
	  // Update the KNN set
	  // Compute the difference using XOR
	  WholeDigitType diff = test_inst ^ training_set1[i];
	  int dist = 0;

	  dist = popcount(diff);

	  int max_dist = 0;
	  int max_dist_id = K_CONST+1;
	  int k = 0;

	  // Find the max distance
	  FIND_MAX_DIST_1: for ( int k = 0; k < K_CONST; ++k )
	  {
		if ( knn_set1[k] > max_dist )
		{
		  max_dist = knn_set1[k];
		  max_dist_id = k;
		}
	  }

	  // Replace the entry with the max distance
	  if ( dist < max_dist )
		knn_set1[max_dist_id] = dist;
	}
    index = 2;
    return;
  }


    // Output knn_set if index = 2
	// turn index to 1, then return
	if (index == 2){
	    for(int i = 0; i < K_CONST; i++)
	    {
	        Output_2.write(knn_set1[i]);
	    }

	    for(int i = 0; i < K_CONST * (PAR_FACTOR - 2 * 8); i ++)
	    {
	    	Output_2.write(Input_2.read());
	    }
	    index = 1;
	    return;
	}

  return;
}
void update_knn_cluster_8(hls::stream<ap_uint<32> > & Input_1, hls::stream<ap_uint<32> > & Output_1, hls::stream<ap_uint<32> > & Input_2, hls::stream<ap_uint<32> > & Output_2)
{
  #pragma HLS inline
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
#pragma HLS INTERFACE ap_hs port=Input_2
#pragma HLS INTERFACE ap_hs port=Output_2
  static int knn_set0[K_CONST];
  static int knn_set1[K_CONST];
#pragma HLS array_partition variable=knn_set0 complete dim=0
#pragma HLS array_partition variable=knn_set1 complete dim=0
  // Store 900 training data and pass all rest training data
  static WholeDigitType training_set0 [NUM_TRAINING / PAR_FACTOR];
  static WholeDigitType training_set1 [NUM_TRAINING / PAR_FACTOR];
  const int unroll_factor = PAR_FACTOR;
#pragma HLS array_partition variable=training_set0 block factor=unroll_factor dim=0
#pragma HLS array_partition variable=training_set1 block factor=unroll_factor dim=0
  WholeDigitType data_temp;
  static int index = 0;
  // read training data if index = 0
  // turn index to 1, then return
  if (index == 0)
  {
	  for(int i = 0; i < NUM_TRAINING / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		training_set0[i].range(255, 224) =Input_1.read();
		training_set0[i].range(223, 192) =Input_1.read();
		training_set0[i].range(191, 160) =Input_1.read();
		training_set0[i].range(159, 128) =Input_1.read();
		training_set0[i].range(127, 96 ) =Input_1.read();
		training_set0[i].range(95 , 64 ) =Input_1.read();
		training_set0[i].range(63 , 32 ) =Input_1.read();
		training_set0[i].range(31 , 0  ) =Input_1.read();
	  }
	  for(int i = 0; i < NUM_TRAINING / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		training_set1[i].range(255, 224) =Input_1.read();
		training_set1[i].range(223, 192) =Input_1.read();
		training_set1[i].range(191, 160) =Input_1.read();
		training_set1[i].range(159, 128) =Input_1.read();
		training_set1[i].range(127, 96 ) =Input_1.read();
		training_set1[i].range(95 , 64 ) =Input_1.read();
		training_set1[i].range(63 , 32 ) =Input_1.read();
		training_set1[i].range(31 , 0  ) =Input_1.read();
	  }
	  for(int i = 0; i < NUM_TRAINING * (PAR_FACTOR - 2 * 9) / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		data_temp.range(255, 224) =Input_1.read();
		data_temp.range(223, 192) =Input_1.read();
		data_temp.range(191, 160) =Input_1.read();
		data_temp.range(159, 128) =Input_1.read();
		data_temp.range(127, 96 ) =Input_1.read();
		data_temp.range(95 , 64 ) =Input_1.read();
		data_temp.range(63 , 32 ) =Input_1.read();
		data_temp.range(31 , 0  ) =Input_1.read();
		Output_1.write(data_temp.range(255, 224));
		Output_1.write(data_temp.range(223, 192));
		Output_1.write(data_temp.range(191, 160));
		Output_1.write(data_temp.range(159, 128));
		Output_1.write(data_temp.range(127, 96 ));
		Output_1.write(data_temp.range(95 , 64 ));
		Output_1.write(data_temp.range(63 , 32 ));
		Output_1.write(data_temp.range(31 , 0  ));
	  }
	  index = 1;
	  return;
  }



  // get a test data and update knn value if index = 1
  // turn index to 2, then return
  if (index == 1)
  {
    WholeDigitType test_inst;
	// Get testing data
	test_inst.range(255, 224) =Input_1.read();
	test_inst.range(223, 192) =Input_1.read();
	test_inst.range(191, 160) =Input_1.read();
	test_inst.range(159, 128) =Input_1.read();
	test_inst.range(127, 96 ) =Input_1.read();
	test_inst.range(95 , 64 ) =Input_1.read();
	test_inst.range(63 , 32 ) =Input_1.read();
	test_inst.range(31 , 0  ) =Input_1.read();
	// Pass it to the next kernel
	Output_1.write(test_inst.range(255, 224));
	Output_1.write(test_inst.range(223, 192));
	Output_1.write(test_inst.range(191, 160));
	Output_1.write(test_inst.range(159, 128));
	Output_1.write(test_inst.range(127, 96 ));
	Output_1.write(test_inst.range(95 , 64 ));
	Output_1.write(test_inst.range(63 , 32 ));
	Output_1.write(test_inst.range(31 , 0  ));
	// Preset knn_set
	for(int i = 0; i < K_CONST; i++)
	{
		#pragma HLS unroll
		knn_set0[i] = 256;
		knn_set1[i] = 256;
	}

	TRAINING_LOOP_0 : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
	{
	  #pragma HLS pipeline
	  // Update the KNN set
	  // Compute the difference using XOR
	  WholeDigitType diff = test_inst ^ training_set0[i];
	  int dist = 0;

	  dist = popcount(diff);

	  int max_dist = 0;
	  int max_dist_id = K_CONST+1;
	  int k = 0;

	  // Find the max distance
	  FIND_MAX_DIST_0: for ( int k = 0; k < K_CONST; ++k )
	  {
		if ( knn_set0[k] > max_dist )
		{
		  max_dist = knn_set0[k];
		  max_dist_id = k;
		}
	  }

	  // Replace the entry with the max distance
	  if ( dist < max_dist )
		knn_set0[max_dist_id] = dist;
	}

	// Output knn_set
	for(int i = 0; i < K_CONST; i++)
	{
		Output_2.write(knn_set0[i]);
	}

	TRAINING_LOOP_1 : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
	{
	  #pragma HLS pipeline
	  // Update the KNN set
	  // Compute the difference using XOR
	  WholeDigitType diff = test_inst ^ training_set1[i];
	  int dist = 0;

	  dist = popcount(diff);

	  int max_dist = 0;
	  int max_dist_id = K_CONST+1;
	  int k = 0;

	  // Find the max distance
	  FIND_MAX_DIST_1: for ( int k = 0; k < K_CONST; ++k )
	  {
		if ( knn_set1[k] > max_dist )
		{
		  max_dist = knn_set1[k];
		  max_dist_id = k;
		}
	  }

	  // Replace the entry with the max distance
	  if ( dist < max_dist )
		knn_set1[max_dist_id] = dist;
	}
    index = 2;
    return;
  }


    // Output knn_set if index = 2
	// turn index to 1, then return
	if (index == 2){
	    for(int i = 0; i < K_CONST; i++)
	    {
	        Output_2.write(knn_set1[i]);
	    }

	    for(int i = 0; i < K_CONST * (PAR_FACTOR - 2 * 9); i ++)
	    {
	    	Output_2.write(Input_2.read());
	    }
	    index = 1;
	    return;
	}

  return;
}
void update_knn_cluster_9(hls::stream<ap_uint<32> > & Input_1, hls::stream<ap_uint<32> > & Output_1, hls::stream<ap_uint<32> > & Input_2, hls::stream<ap_uint<32> > & Output_2)
{
  #pragma HLS inline
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
#pragma HLS INTERFACE ap_hs port=Input_2
#pragma HLS INTERFACE ap_hs port=Output_2
  static int knn_set0[K_CONST];
  static int knn_set1[K_CONST];
#pragma HLS array_partition variable=knn_set0 complete dim=0
#pragma HLS array_partition variable=knn_set1 complete dim=0
  // Store 900 training data and pass all rest training data
  static WholeDigitType training_set0 [NUM_TRAINING / PAR_FACTOR];
  static WholeDigitType training_set1 [NUM_TRAINING / PAR_FACTOR];
  const int unroll_factor = PAR_FACTOR;
#pragma HLS array_partition variable=training_set0 block factor=unroll_factor dim=0
#pragma HLS array_partition variable=training_set1 block factor=unroll_factor dim=0
  WholeDigitType data_temp;
  static int index = 0;
  // read training data if index = 0
  // turn index to 1, then return
  if (index == 0)
  {
	  for(int i = 0; i < NUM_TRAINING / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		training_set0[i].range(255, 224) =Input_1.read();
		training_set0[i].range(223, 192) =Input_1.read();
		training_set0[i].range(191, 160) =Input_1.read();
		training_set0[i].range(159, 128) =Input_1.read();
		training_set0[i].range(127, 96 ) =Input_1.read();
		training_set0[i].range(95 , 64 ) =Input_1.read();
		training_set0[i].range(63 , 32 ) =Input_1.read();
		training_set0[i].range(31 , 0  ) =Input_1.read();
	  }
	  for(int i = 0; i < NUM_TRAINING / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		training_set1[i].range(255, 224) =Input_1.read();
		training_set1[i].range(223, 192) =Input_1.read();
		training_set1[i].range(191, 160) =Input_1.read();
		training_set1[i].range(159, 128) =Input_1.read();
		training_set1[i].range(127, 96 ) =Input_1.read();
		training_set1[i].range(95 , 64 ) =Input_1.read();
		training_set1[i].range(63 , 32 ) =Input_1.read();
		training_set1[i].range(31 , 0  ) =Input_1.read();
	  }
	  for(int i = 0; i < NUM_TRAINING * (PAR_FACTOR - 2 * 10) / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		data_temp.range(255, 224) =Input_1.read();
		data_temp.range(223, 192) =Input_1.read();
		data_temp.range(191, 160) =Input_1.read();
		data_temp.range(159, 128) =Input_1.read();
		data_temp.range(127, 96 ) =Input_1.read();
		data_temp.range(95 , 64 ) =Input_1.read();
		data_temp.range(63 , 32 ) =Input_1.read();
		data_temp.range(31 , 0  ) =Input_1.read();
		Output_1.write(data_temp.range(255, 224));
		Output_1.write(data_temp.range(223, 192));
		Output_1.write(data_temp.range(191, 160));
		Output_1.write(data_temp.range(159, 128));
		Output_1.write(data_temp.range(127, 96 ));
		Output_1.write(data_temp.range(95 , 64 ));
		Output_1.write(data_temp.range(63 , 32 ));
		Output_1.write(data_temp.range(31 , 0  ));
	  }
	  index = 1;
	  return;
  }



  // get a test data and update knn value if index = 1
  // turn index to 2, then return
  if (index == 1)
  {
    WholeDigitType test_inst;
	// Get testing data
	test_inst.range(255, 224) =Input_1.read();
	test_inst.range(223, 192) =Input_1.read();
	test_inst.range(191, 160) =Input_1.read();
	test_inst.range(159, 128) =Input_1.read();
	test_inst.range(127, 96 ) =Input_1.read();
	test_inst.range(95 , 64 ) =Input_1.read();
	test_inst.range(63 , 32 ) =Input_1.read();
	test_inst.range(31 , 0  ) =Input_1.read();
	// Pass it to the next kernel
	Output_1.write(test_inst.range(255, 224));
	Output_1.write(test_inst.range(223, 192));
	Output_1.write(test_inst.range(191, 160));
	Output_1.write(test_inst.range(159, 128));
	Output_1.write(test_inst.range(127, 96 ));
	Output_1.write(test_inst.range(95 , 64 ));
	Output_1.write(test_inst.range(63 , 32 ));
	Output_1.write(test_inst.range(31 , 0  ));
	// Preset knn_set
	for(int i = 0; i < K_CONST; i++)
	{
		#pragma HLS unroll
		knn_set0[i] = 256;
		knn_set1[i] = 256;
	}

	TRAINING_LOOP_0 : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
	{
	  #pragma HLS pipeline
	  // Update the KNN set
	  // Compute the difference using XOR
	  WholeDigitType diff = test_inst ^ training_set0[i];
	  int dist = 0;

	  dist = popcount(diff);

	  int max_dist = 0;
	  int max_dist_id = K_CONST+1;
	  int k = 0;

	  // Find the max distance
	  FIND_MAX_DIST_0: for ( int k = 0; k < K_CONST; ++k )
	  {
		if ( knn_set0[k] > max_dist )
		{
		  max_dist = knn_set0[k];
		  max_dist_id = k;
		}
	  }

	  // Replace the entry with the max distance
	  if ( dist < max_dist )
		knn_set0[max_dist_id] = dist;
	}

	// Output knn_set
	for(int i = 0; i < K_CONST; i++)
	{
		Output_2.write(knn_set0[i]);
	}

	TRAINING_LOOP_1 : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
	{
	  #pragma HLS pipeline
	  // Update the KNN set
	  // Compute the difference using XOR
	  WholeDigitType diff = test_inst ^ training_set1[i];
	  int dist = 0;

	  dist = popcount(diff);

	  int max_dist = 0;
	  int max_dist_id = K_CONST+1;
	  int k = 0;

	  // Find the max distance
	  FIND_MAX_DIST_1: for ( int k = 0; k < K_CONST; ++k )
	  {
		if ( knn_set1[k] > max_dist )
		{
		  max_dist = knn_set1[k];
		  max_dist_id = k;
		}
	  }

	  // Replace the entry with the max distance
	  if ( dist < max_dist )
		knn_set1[max_dist_id] = dist;
	}
    index = 2;
    return;
  }


    // Output knn_set if index = 2
	// turn index to 1, then return
	if (index == 2){
	    for(int i = 0; i < K_CONST; i++)
	    {
	        Output_2.write(knn_set1[i]);
	    }

	    for(int i = 0; i < K_CONST * (PAR_FACTOR - 2 * 10); i ++)
	    {
	    	Output_2.write(Input_2.read());
	    }
	    index = 1;
	    return;
	}

  return;
}
void update_knn_cluster_10(hls::stream<ap_uint<32> > & Input_1, hls::stream<ap_uint<32> > & Output_1, hls::stream<ap_uint<32> > & Input_2, hls::stream<ap_uint<32> > & Output_2)
{
  #pragma HLS inline
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
#pragma HLS INTERFACE ap_hs port=Input_2
#pragma HLS INTERFACE ap_hs port=Output_2
  static int knn_set0[K_CONST];
  static int knn_set1[K_CONST];
#pragma HLS array_partition variable=knn_set0 complete dim=0
#pragma HLS array_partition variable=knn_set1 complete dim=0
  // Store 900 training data and pass all rest training data
  static WholeDigitType training_set0 [NUM_TRAINING / PAR_FACTOR];
  static WholeDigitType training_set1 [NUM_TRAINING / PAR_FACTOR];
  const int unroll_factor = PAR_FACTOR;
#pragma HLS array_partition variable=training_set0 block factor=unroll_factor dim=0
#pragma HLS array_partition variable=training_set1 block factor=unroll_factor dim=0
  WholeDigitType data_temp;
  static int index = 0;
  // read training data if index = 0
  // turn index to 1, then return
  if (index == 0)
  {
	  for(int i = 0; i < NUM_TRAINING / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		training_set0[i].range(255, 224) =Input_1.read();
		training_set0[i].range(223, 192) =Input_1.read();
		training_set0[i].range(191, 160) =Input_1.read();
		training_set0[i].range(159, 128) =Input_1.read();
		training_set0[i].range(127, 96 ) =Input_1.read();
		training_set0[i].range(95 , 64 ) =Input_1.read();
		training_set0[i].range(63 , 32 ) =Input_1.read();
		training_set0[i].range(31 , 0  ) =Input_1.read();
	  }
	  for(int i = 0; i < NUM_TRAINING / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		training_set1[i].range(255, 224) =Input_1.read();
		training_set1[i].range(223, 192) =Input_1.read();
		training_set1[i].range(191, 160) =Input_1.read();
		training_set1[i].range(159, 128) =Input_1.read();
		training_set1[i].range(127, 96 ) =Input_1.read();
		training_set1[i].range(95 , 64 ) =Input_1.read();
		training_set1[i].range(63 , 32 ) =Input_1.read();
		training_set1[i].range(31 , 0  ) =Input_1.read();
	  }
	  for(int i = 0; i < NUM_TRAINING * (PAR_FACTOR - 2 * 11) / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		data_temp.range(255, 224) =Input_1.read();
		data_temp.range(223, 192) =Input_1.read();
		data_temp.range(191, 160) =Input_1.read();
		data_temp.range(159, 128) =Input_1.read();
		data_temp.range(127, 96 ) =Input_1.read();
		data_temp.range(95 , 64 ) =Input_1.read();
		data_temp.range(63 , 32 ) =Input_1.read();
		data_temp.range(31 , 0  ) =Input_1.read();
		Output_1.write(data_temp.range(255, 224));
		Output_1.write(data_temp.range(223, 192));
		Output_1.write(data_temp.range(191, 160));
		Output_1.write(data_temp.range(159, 128));
		Output_1.write(data_temp.range(127, 96 ));
		Output_1.write(data_temp.range(95 , 64 ));
		Output_1.write(data_temp.range(63 , 32 ));
		Output_1.write(data_temp.range(31 , 0  ));
	  }
	  index = 1;
	  return;
  }



  // get a test data and update knn value if index = 1
  // turn index to 2, then return
  if (index == 1)
  {
    WholeDigitType test_inst;
	// Get testing data
	test_inst.range(255, 224) =Input_1.read();
	test_inst.range(223, 192) =Input_1.read();
	test_inst.range(191, 160) =Input_1.read();
	test_inst.range(159, 128) =Input_1.read();
	test_inst.range(127, 96 ) =Input_1.read();
	test_inst.range(95 , 64 ) =Input_1.read();
	test_inst.range(63 , 32 ) =Input_1.read();
	test_inst.range(31 , 0  ) =Input_1.read();
	// Pass it to the next kernel
	Output_1.write(test_inst.range(255, 224));
	Output_1.write(test_inst.range(223, 192));
	Output_1.write(test_inst.range(191, 160));
	Output_1.write(test_inst.range(159, 128));
	Output_1.write(test_inst.range(127, 96 ));
	Output_1.write(test_inst.range(95 , 64 ));
	Output_1.write(test_inst.range(63 , 32 ));
	Output_1.write(test_inst.range(31 , 0  ));
	// Preset knn_set
	for(int i = 0; i < K_CONST; i++)
	{
		#pragma HLS unroll
		knn_set0[i] = 256;
		knn_set1[i] = 256;
	}

	TRAINING_LOOP_0 : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
	{
	  #pragma HLS pipeline
	  // Update the KNN set
	  // Compute the difference using XOR
	  WholeDigitType diff = test_inst ^ training_set0[i];
	  int dist = 0;

	  dist = popcount(diff);

	  int max_dist = 0;
	  int max_dist_id = K_CONST+1;
	  int k = 0;

	  // Find the max distance
	  FIND_MAX_DIST_0: for ( int k = 0; k < K_CONST; ++k )
	  {
		if ( knn_set0[k] > max_dist )
		{
		  max_dist = knn_set0[k];
		  max_dist_id = k;
		}
	  }

	  // Replace the entry with the max distance
	  if ( dist < max_dist )
		knn_set0[max_dist_id] = dist;
	}

	// Output knn_set
	for(int i = 0; i < K_CONST; i++)
	{
		Output_2.write(knn_set0[i]);
	}

	TRAINING_LOOP_1 : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
	{
	  #pragma HLS pipeline
	  // Update the KNN set
	  // Compute the difference using XOR
	  WholeDigitType diff = test_inst ^ training_set1[i];
	  int dist = 0;

	  dist = popcount(diff);

	  int max_dist = 0;
	  int max_dist_id = K_CONST+1;
	  int k = 0;

	  // Find the max distance
	  FIND_MAX_DIST_1: for ( int k = 0; k < K_CONST; ++k )
	  {
		if ( knn_set1[k] > max_dist )
		{
		  max_dist = knn_set1[k];
		  max_dist_id = k;
		}
	  }

	  // Replace the entry with the max distance
	  if ( dist < max_dist )
		knn_set1[max_dist_id] = dist;
	}
    index = 2;
    return;
  }


    // Output knn_set if index = 2
	// turn index to 1, then return
	if (index == 2){
	    for(int i = 0; i < K_CONST; i++)
	    {
	        Output_2.write(knn_set1[i]);
	    }

	    for(int i = 0; i < K_CONST * (PAR_FACTOR - 2 * 11); i ++)
	    {
	    	Output_2.write(Input_2.read());
	    }
	    index = 1;
	    return;
	}

  return;
}
void update_knn_cluster_11(hls::stream<ap_uint<32> > & Input_1, hls::stream<ap_uint<32> > & Output_1, hls::stream<ap_uint<32> > & Input_2, hls::stream<ap_uint<32> > & Output_2)
{
  #pragma HLS inline
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
#pragma HLS INTERFACE ap_hs port=Input_2
#pragma HLS INTERFACE ap_hs port=Output_2
  static int knn_set0[K_CONST];
  static int knn_set1[K_CONST];
#pragma HLS array_partition variable=knn_set0 complete dim=0
#pragma HLS array_partition variable=knn_set1 complete dim=0
  // Store 900 training data and pass all rest training data
  static WholeDigitType training_set0 [NUM_TRAINING / PAR_FACTOR];
  static WholeDigitType training_set1 [NUM_TRAINING / PAR_FACTOR];
  const int unroll_factor = PAR_FACTOR;
#pragma HLS array_partition variable=training_set0 block factor=unroll_factor dim=0
#pragma HLS array_partition variable=training_set1 block factor=unroll_factor dim=0
  WholeDigitType data_temp;
  static int index = 0;
  // read training data if index = 0
  // turn index to 1, then return
  if (index == 0)
  {
	  for(int i = 0; i < NUM_TRAINING / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		training_set0[i].range(255, 224) =Input_1.read();
		training_set0[i].range(223, 192) =Input_1.read();
		training_set0[i].range(191, 160) =Input_1.read();
		training_set0[i].range(159, 128) =Input_1.read();
		training_set0[i].range(127, 96 ) =Input_1.read();
		training_set0[i].range(95 , 64 ) =Input_1.read();
		training_set0[i].range(63 , 32 ) =Input_1.read();
		training_set0[i].range(31 , 0  ) =Input_1.read();
	  }
	  for(int i = 0; i < NUM_TRAINING / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		training_set1[i].range(255, 224) =Input_1.read();
		training_set1[i].range(223, 192) =Input_1.read();
		training_set1[i].range(191, 160) =Input_1.read();
		training_set1[i].range(159, 128) =Input_1.read();
		training_set1[i].range(127, 96 ) =Input_1.read();
		training_set1[i].range(95 , 64 ) =Input_1.read();
		training_set1[i].range(63 , 32 ) =Input_1.read();
		training_set1[i].range(31 , 0  ) =Input_1.read();
	  }
	  for(int i = 0; i < NUM_TRAINING * (PAR_FACTOR - 2 * 12) / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		data_temp.range(255, 224) =Input_1.read();
		data_temp.range(223, 192) =Input_1.read();
		data_temp.range(191, 160) =Input_1.read();
		data_temp.range(159, 128) =Input_1.read();
		data_temp.range(127, 96 ) =Input_1.read();
		data_temp.range(95 , 64 ) =Input_1.read();
		data_temp.range(63 , 32 ) =Input_1.read();
		data_temp.range(31 , 0  ) =Input_1.read();
		Output_1.write(data_temp.range(255, 224));
		Output_1.write(data_temp.range(223, 192));
		Output_1.write(data_temp.range(191, 160));
		Output_1.write(data_temp.range(159, 128));
		Output_1.write(data_temp.range(127, 96 ));
		Output_1.write(data_temp.range(95 , 64 ));
		Output_1.write(data_temp.range(63 , 32 ));
		Output_1.write(data_temp.range(31 , 0  ));
	  }
	  index = 1;
	  return;
  }



  // get a test data and update knn value if index = 1
  // turn index to 2, then return
  if (index == 1)
  {
    WholeDigitType test_inst;
	// Get testing data
	test_inst.range(255, 224) =Input_1.read();
	test_inst.range(223, 192) =Input_1.read();
	test_inst.range(191, 160) =Input_1.read();
	test_inst.range(159, 128) =Input_1.read();
	test_inst.range(127, 96 ) =Input_1.read();
	test_inst.range(95 , 64 ) =Input_1.read();
	test_inst.range(63 , 32 ) =Input_1.read();
	test_inst.range(31 , 0  ) =Input_1.read();
	// Pass it to the next kernel
	Output_1.write(test_inst.range(255, 224));
	Output_1.write(test_inst.range(223, 192));
	Output_1.write(test_inst.range(191, 160));
	Output_1.write(test_inst.range(159, 128));
	Output_1.write(test_inst.range(127, 96 ));
	Output_1.write(test_inst.range(95 , 64 ));
	Output_1.write(test_inst.range(63 , 32 ));
	Output_1.write(test_inst.range(31 , 0  ));
	// Preset knn_set
	for(int i = 0; i < K_CONST; i++)
	{
		#pragma HLS unroll
		knn_set0[i] = 256;
		knn_set1[i] = 256;
	}

	TRAINING_LOOP_0 : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
	{
	  #pragma HLS pipeline
	  // Update the KNN set
	  // Compute the difference using XOR
	  WholeDigitType diff = test_inst ^ training_set0[i];
	  int dist = 0;

	  dist = popcount(diff);

	  int max_dist = 0;
	  int max_dist_id = K_CONST+1;
	  int k = 0;

	  // Find the max distance
	  FIND_MAX_DIST_0: for ( int k = 0; k < K_CONST; ++k )
	  {
		if ( knn_set0[k] > max_dist )
		{
		  max_dist = knn_set0[k];
		  max_dist_id = k;
		}
	  }

	  // Replace the entry with the max distance
	  if ( dist < max_dist )
		knn_set0[max_dist_id] = dist;
	}

	// Output knn_set
	for(int i = 0; i < K_CONST; i++)
	{
		Output_2.write(knn_set0[i]);
	}

	TRAINING_LOOP_1 : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
	{
	  #pragma HLS pipeline
	  // Update the KNN set
	  // Compute the difference using XOR
	  WholeDigitType diff = test_inst ^ training_set1[i];
	  int dist = 0;

	  dist = popcount(diff);

	  int max_dist = 0;
	  int max_dist_id = K_CONST+1;
	  int k = 0;

	  // Find the max distance
	  FIND_MAX_DIST_1: for ( int k = 0; k < K_CONST; ++k )
	  {
		if ( knn_set1[k] > max_dist )
		{
		  max_dist = knn_set1[k];
		  max_dist_id = k;
		}
	  }

	  // Replace the entry with the max distance
	  if ( dist < max_dist )
		knn_set1[max_dist_id] = dist;
	}
    index = 2;
    return;
  }


    // Output knn_set if index = 2
	// turn index to 1, then return
	if (index == 2){
	    for(int i = 0; i < K_CONST; i++)
	    {
	        Output_2.write(knn_set1[i]);
	    }

	    for(int i = 0; i < K_CONST * (PAR_FACTOR - 2 * 12); i ++)
	    {
	    	Output_2.write(Input_2.read());
	    }
	    index = 1;
	    return;
	}

  return;
}
void update_knn_cluster_12(hls::stream<ap_uint<32> > & Input_1, hls::stream<ap_uint<32> > & Output_1, hls::stream<ap_uint<32> > & Input_2, hls::stream<ap_uint<32> > & Output_2)
{
  #pragma HLS inline
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
#pragma HLS INTERFACE ap_hs port=Input_2
#pragma HLS INTERFACE ap_hs port=Output_2
  static int knn_set0[K_CONST];
  static int knn_set1[K_CONST];
#pragma HLS array_partition variable=knn_set0 complete dim=0
#pragma HLS array_partition variable=knn_set1 complete dim=0
  // Store 900 training data and pass all rest training data
  static WholeDigitType training_set0 [NUM_TRAINING / PAR_FACTOR];
  static WholeDigitType training_set1 [NUM_TRAINING / PAR_FACTOR];
  const int unroll_factor = PAR_FACTOR;
#pragma HLS array_partition variable=training_set0 block factor=unroll_factor dim=0
#pragma HLS array_partition variable=training_set1 block factor=unroll_factor dim=0
  WholeDigitType data_temp;
  static int index = 0;
  // read training data if index = 0
  // turn index to 1, then return
  if (index == 0)
  {
	  for(int i = 0; i < NUM_TRAINING / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		training_set0[i].range(255, 224) =Input_1.read();
		training_set0[i].range(223, 192) =Input_1.read();
		training_set0[i].range(191, 160) =Input_1.read();
		training_set0[i].range(159, 128) =Input_1.read();
		training_set0[i].range(127, 96 ) =Input_1.read();
		training_set0[i].range(95 , 64 ) =Input_1.read();
		training_set0[i].range(63 , 32 ) =Input_1.read();
		training_set0[i].range(31 , 0  ) =Input_1.read();
	  }
	  for(int i = 0; i < NUM_TRAINING / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		training_set1[i].range(255, 224) =Input_1.read();
		training_set1[i].range(223, 192) =Input_1.read();
		training_set1[i].range(191, 160) =Input_1.read();
		training_set1[i].range(159, 128) =Input_1.read();
		training_set1[i].range(127, 96 ) =Input_1.read();
		training_set1[i].range(95 , 64 ) =Input_1.read();
		training_set1[i].range(63 , 32 ) =Input_1.read();
		training_set1[i].range(31 , 0  ) =Input_1.read();
	  }
	  for(int i = 0; i < NUM_TRAINING * (PAR_FACTOR - 2 * 13) / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		data_temp.range(255, 224) =Input_1.read();
		data_temp.range(223, 192) =Input_1.read();
		data_temp.range(191, 160) =Input_1.read();
		data_temp.range(159, 128) =Input_1.read();
		data_temp.range(127, 96 ) =Input_1.read();
		data_temp.range(95 , 64 ) =Input_1.read();
		data_temp.range(63 , 32 ) =Input_1.read();
		data_temp.range(31 , 0  ) =Input_1.read();
		Output_1.write(data_temp.range(255, 224));
		Output_1.write(data_temp.range(223, 192));
		Output_1.write(data_temp.range(191, 160));
		Output_1.write(data_temp.range(159, 128));
		Output_1.write(data_temp.range(127, 96 ));
		Output_1.write(data_temp.range(95 , 64 ));
		Output_1.write(data_temp.range(63 , 32 ));
		Output_1.write(data_temp.range(31 , 0  ));
	  }
	  index = 1;
	  return;
  }



  // get a test data and update knn value if index = 1
  // turn index to 2, then return
  if (index == 1)
  {
    WholeDigitType test_inst;
	// Get testing data
	test_inst.range(255, 224) =Input_1.read();
	test_inst.range(223, 192) =Input_1.read();
	test_inst.range(191, 160) =Input_1.read();
	test_inst.range(159, 128) =Input_1.read();
	test_inst.range(127, 96 ) =Input_1.read();
	test_inst.range(95 , 64 ) =Input_1.read();
	test_inst.range(63 , 32 ) =Input_1.read();
	test_inst.range(31 , 0  ) =Input_1.read();
	// Pass it to the next kernel
	Output_1.write(test_inst.range(255, 224));
	Output_1.write(test_inst.range(223, 192));
	Output_1.write(test_inst.range(191, 160));
	Output_1.write(test_inst.range(159, 128));
	Output_1.write(test_inst.range(127, 96 ));
	Output_1.write(test_inst.range(95 , 64 ));
	Output_1.write(test_inst.range(63 , 32 ));
	Output_1.write(test_inst.range(31 , 0  ));
	// Preset knn_set
	for(int i = 0; i < K_CONST; i++)
	{
		#pragma HLS unroll
		knn_set0[i] = 256;
		knn_set1[i] = 256;
	}

	TRAINING_LOOP_0 : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
	{
	  #pragma HLS pipeline
	  // Update the KNN set
	  // Compute the difference using XOR
	  WholeDigitType diff = test_inst ^ training_set0[i];
	  int dist = 0;

	  dist = popcount(diff);

	  int max_dist = 0;
	  int max_dist_id = K_CONST+1;
	  int k = 0;

	  // Find the max distance
	  FIND_MAX_DIST_0: for ( int k = 0; k < K_CONST; ++k )
	  {
		if ( knn_set0[k] > max_dist )
		{
		  max_dist = knn_set0[k];
		  max_dist_id = k;
		}
	  }

	  // Replace the entry with the max distance
	  if ( dist < max_dist )
		knn_set0[max_dist_id] = dist;
	}

	// Output knn_set
	for(int i = 0; i < K_CONST; i++)
	{
		Output_2.write(knn_set0[i]);
	}

	TRAINING_LOOP_1 : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
	{
	  #pragma HLS pipeline
	  // Update the KNN set
	  // Compute the difference using XOR
	  WholeDigitType diff = test_inst ^ training_set1[i];
	  int dist = 0;

	  dist = popcount(diff);

	  int max_dist = 0;
	  int max_dist_id = K_CONST+1;
	  int k = 0;

	  // Find the max distance
	  FIND_MAX_DIST_1: for ( int k = 0; k < K_CONST; ++k )
	  {
		if ( knn_set1[k] > max_dist )
		{
		  max_dist = knn_set1[k];
		  max_dist_id = k;
		}
	  }

	  // Replace the entry with the max distance
	  if ( dist < max_dist )
		knn_set1[max_dist_id] = dist;
	}
    index = 2;
    return;
  }


    // Output knn_set if index = 2
	// turn index to 1, then return
	if (index == 2){
	    for(int i = 0; i < K_CONST; i++)
	    {
	        Output_2.write(knn_set1[i]);
	    }

	    for(int i = 0; i < K_CONST * (PAR_FACTOR - 2 * 13); i ++)
	    {
	    	Output_2.write(Input_2.read());
	    }
	    index = 1;
	    return;
	}

  return;
}
void update_knn_cluster_13(hls::stream<ap_uint<32> > & Input_1, hls::stream<ap_uint<32> > & Output_1, hls::stream<ap_uint<32> > & Input_2, hls::stream<ap_uint<32> > & Output_2)
{
  #pragma HLS inline
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
#pragma HLS INTERFACE ap_hs port=Input_2
#pragma HLS INTERFACE ap_hs port=Output_2
  static int knn_set0[K_CONST];
  static int knn_set1[K_CONST];
#pragma HLS array_partition variable=knn_set0 complete dim=0
#pragma HLS array_partition variable=knn_set1 complete dim=0
  // Store 900 training data and pass all rest training data
  static WholeDigitType training_set0 [NUM_TRAINING / PAR_FACTOR];
  static WholeDigitType training_set1 [NUM_TRAINING / PAR_FACTOR];
  const int unroll_factor = PAR_FACTOR;
#pragma HLS array_partition variable=training_set0 block factor=unroll_factor dim=0
#pragma HLS array_partition variable=training_set1 block factor=unroll_factor dim=0
  WholeDigitType data_temp;
  static int index = 0;
  // read training data if index = 0
  // turn index to 1, then return
  if (index == 0)
  {
	  for(int i = 0; i < NUM_TRAINING / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		training_set0[i].range(255, 224) =Input_1.read();
		training_set0[i].range(223, 192) =Input_1.read();
		training_set0[i].range(191, 160) =Input_1.read();
		training_set0[i].range(159, 128) =Input_1.read();
		training_set0[i].range(127, 96 ) =Input_1.read();
		training_set0[i].range(95 , 64 ) =Input_1.read();
		training_set0[i].range(63 , 32 ) =Input_1.read();
		training_set0[i].range(31 , 0  ) =Input_1.read();
	  }
	  for(int i = 0; i < NUM_TRAINING / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		training_set1[i].range(255, 224) =Input_1.read();
		training_set1[i].range(223, 192) =Input_1.read();
		training_set1[i].range(191, 160) =Input_1.read();
		training_set1[i].range(159, 128) =Input_1.read();
		training_set1[i].range(127, 96 ) =Input_1.read();
		training_set1[i].range(95 , 64 ) =Input_1.read();
		training_set1[i].range(63 , 32 ) =Input_1.read();
		training_set1[i].range(31 , 0  ) =Input_1.read();
	  }
	  for(int i = 0; i < NUM_TRAINING * (PAR_FACTOR - 2 * 14) / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		data_temp.range(255, 224) =Input_1.read();
		data_temp.range(223, 192) =Input_1.read();
		data_temp.range(191, 160) =Input_1.read();
		data_temp.range(159, 128) =Input_1.read();
		data_temp.range(127, 96 ) =Input_1.read();
		data_temp.range(95 , 64 ) =Input_1.read();
		data_temp.range(63 , 32 ) =Input_1.read();
		data_temp.range(31 , 0  ) =Input_1.read();
		Output_1.write(data_temp.range(255, 224));
		Output_1.write(data_temp.range(223, 192));
		Output_1.write(data_temp.range(191, 160));
		Output_1.write(data_temp.range(159, 128));
		Output_1.write(data_temp.range(127, 96 ));
		Output_1.write(data_temp.range(95 , 64 ));
		Output_1.write(data_temp.range(63 , 32 ));
		Output_1.write(data_temp.range(31 , 0  ));
	  }
	  index = 1;
	  return;
  }



  // get a test data and update knn value if index = 1
  // turn index to 2, then return
  if (index == 1)
  {
    WholeDigitType test_inst;
	// Get testing data
	test_inst.range(255, 224) =Input_1.read();
	test_inst.range(223, 192) =Input_1.read();
	test_inst.range(191, 160) =Input_1.read();
	test_inst.range(159, 128) =Input_1.read();
	test_inst.range(127, 96 ) =Input_1.read();
	test_inst.range(95 , 64 ) =Input_1.read();
	test_inst.range(63 , 32 ) =Input_1.read();
	test_inst.range(31 , 0  ) =Input_1.read();
	// Pass it to the next kernel
	Output_1.write(test_inst.range(255, 224));
	Output_1.write(test_inst.range(223, 192));
	Output_1.write(test_inst.range(191, 160));
	Output_1.write(test_inst.range(159, 128));
	Output_1.write(test_inst.range(127, 96 ));
	Output_1.write(test_inst.range(95 , 64 ));
	Output_1.write(test_inst.range(63 , 32 ));
	Output_1.write(test_inst.range(31 , 0  ));
	// Preset knn_set
	for(int i = 0; i < K_CONST; i++)
	{
		#pragma HLS unroll
		knn_set0[i] = 256;
		knn_set1[i] = 256;
	}

	TRAINING_LOOP_0 : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
	{
	  #pragma HLS pipeline
	  // Update the KNN set
	  // Compute the difference using XOR
	  WholeDigitType diff = test_inst ^ training_set0[i];
	  int dist = 0;

	  dist = popcount(diff);

	  int max_dist = 0;
	  int max_dist_id = K_CONST+1;
	  int k = 0;

	  // Find the max distance
	  FIND_MAX_DIST_0: for ( int k = 0; k < K_CONST; ++k )
	  {
		if ( knn_set0[k] > max_dist )
		{
		  max_dist = knn_set0[k];
		  max_dist_id = k;
		}
	  }

	  // Replace the entry with the max distance
	  if ( dist < max_dist )
		knn_set0[max_dist_id] = dist;
	}

	// Output knn_set
	for(int i = 0; i < K_CONST; i++)
	{
		Output_2.write(knn_set0[i]);
	}

	TRAINING_LOOP_1 : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
	{
	  #pragma HLS pipeline
	  // Update the KNN set
	  // Compute the difference using XOR
	  WholeDigitType diff = test_inst ^ training_set1[i];
	  int dist = 0;

	  dist = popcount(diff);

	  int max_dist = 0;
	  int max_dist_id = K_CONST+1;
	  int k = 0;

	  // Find the max distance
	  FIND_MAX_DIST_1: for ( int k = 0; k < K_CONST; ++k )
	  {
		if ( knn_set1[k] > max_dist )
		{
		  max_dist = knn_set1[k];
		  max_dist_id = k;
		}
	  }

	  // Replace the entry with the max distance
	  if ( dist < max_dist )
		knn_set1[max_dist_id] = dist;
	}
    index = 2;
    return;
  }


    // Output knn_set if index = 2
	// turn index to 1, then return
	if (index == 2){
	    for(int i = 0; i < K_CONST; i++)
	    {
	        Output_2.write(knn_set1[i]);
	    }

	    for(int i = 0; i < K_CONST * (PAR_FACTOR - 2 * 14); i ++)
	    {
	    	Output_2.write(Input_2.read());
	    }
	    index = 1;
	    return;
	}

  return;
}
void update_knn_cluster_14(hls::stream<ap_uint<32> > & Input_1, hls::stream<ap_uint<32> > & Output_1, hls::stream<ap_uint<32> > & Input_2, hls::stream<ap_uint<32> > & Output_2)
{
  #pragma HLS inline
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
#pragma HLS INTERFACE ap_hs port=Input_2
#pragma HLS INTERFACE ap_hs port=Output_2
  static int knn_set0[K_CONST];
  static int knn_set1[K_CONST];
#pragma HLS array_partition variable=knn_set0 complete dim=0
#pragma HLS array_partition variable=knn_set1 complete dim=0
  // Store 900 training data and pass all rest training data
  static WholeDigitType training_set0 [NUM_TRAINING / PAR_FACTOR];
  static WholeDigitType training_set1 [NUM_TRAINING / PAR_FACTOR];
  const int unroll_factor = PAR_FACTOR;
#pragma HLS array_partition variable=training_set0 block factor=unroll_factor dim=0
#pragma HLS array_partition variable=training_set1 block factor=unroll_factor dim=0
  WholeDigitType data_temp;
  static int index = 0;
  // read training data if index = 0
  // turn index to 1, then return
  if (index == 0)
  {
	  for(int i = 0; i < NUM_TRAINING / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		training_set0[i].range(255, 224) =Input_1.read();
		training_set0[i].range(223, 192) =Input_1.read();
		training_set0[i].range(191, 160) =Input_1.read();
		training_set0[i].range(159, 128) =Input_1.read();
		training_set0[i].range(127, 96 ) =Input_1.read();
		training_set0[i].range(95 , 64 ) =Input_1.read();
		training_set0[i].range(63 , 32 ) =Input_1.read();
		training_set0[i].range(31 , 0  ) =Input_1.read();
	  }
	  for(int i = 0; i < NUM_TRAINING / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		training_set1[i].range(255, 224) =Input_1.read();
		training_set1[i].range(223, 192) =Input_1.read();
		training_set1[i].range(191, 160) =Input_1.read();
		training_set1[i].range(159, 128) =Input_1.read();
		training_set1[i].range(127, 96 ) =Input_1.read();
		training_set1[i].range(95 , 64 ) =Input_1.read();
		training_set1[i].range(63 , 32 ) =Input_1.read();
		training_set1[i].range(31 , 0  ) =Input_1.read();
	  }
	  for(int i = 0; i < NUM_TRAINING * (PAR_FACTOR - 2 * 15) / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		data_temp.range(255, 224) =Input_1.read();
		data_temp.range(223, 192) =Input_1.read();
		data_temp.range(191, 160) =Input_1.read();
		data_temp.range(159, 128) =Input_1.read();
		data_temp.range(127, 96 ) =Input_1.read();
		data_temp.range(95 , 64 ) =Input_1.read();
		data_temp.range(63 , 32 ) =Input_1.read();
		data_temp.range(31 , 0  ) =Input_1.read();
		Output_1.write(data_temp.range(255, 224));
		Output_1.write(data_temp.range(223, 192));
		Output_1.write(data_temp.range(191, 160));
		Output_1.write(data_temp.range(159, 128));
		Output_1.write(data_temp.range(127, 96 ));
		Output_1.write(data_temp.range(95 , 64 ));
		Output_1.write(data_temp.range(63 , 32 ));
		Output_1.write(data_temp.range(31 , 0  ));
	  }
	  index = 1;
	  return;
  }



  // get a test data and update knn value if index = 1
  // turn index to 2, then return
  if (index == 1)
  {
    WholeDigitType test_inst;
	// Get testing data
	test_inst.range(255, 224) =Input_1.read();
	test_inst.range(223, 192) =Input_1.read();
	test_inst.range(191, 160) =Input_1.read();
	test_inst.range(159, 128) =Input_1.read();
	test_inst.range(127, 96 ) =Input_1.read();
	test_inst.range(95 , 64 ) =Input_1.read();
	test_inst.range(63 , 32 ) =Input_1.read();
	test_inst.range(31 , 0  ) =Input_1.read();
	// Pass it to the next kernel
	Output_1.write(test_inst.range(255, 224));
	Output_1.write(test_inst.range(223, 192));
	Output_1.write(test_inst.range(191, 160));
	Output_1.write(test_inst.range(159, 128));
	Output_1.write(test_inst.range(127, 96 ));
	Output_1.write(test_inst.range(95 , 64 ));
	Output_1.write(test_inst.range(63 , 32 ));
	Output_1.write(test_inst.range(31 , 0  ));
	// Preset knn_set
	for(int i = 0; i < K_CONST; i++)
	{
		#pragma HLS unroll
		knn_set0[i] = 256;
		knn_set1[i] = 256;
	}

	TRAINING_LOOP_0 : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
	{
	  #pragma HLS pipeline
	  // Update the KNN set
	  // Compute the difference using XOR
	  WholeDigitType diff = test_inst ^ training_set0[i];
	  int dist = 0;

	  dist = popcount(diff);

	  int max_dist = 0;
	  int max_dist_id = K_CONST+1;
	  int k = 0;

	  // Find the max distance
	  FIND_MAX_DIST_0: for ( int k = 0; k < K_CONST; ++k )
	  {
		if ( knn_set0[k] > max_dist )
		{
		  max_dist = knn_set0[k];
		  max_dist_id = k;
		}
	  }

	  // Replace the entry with the max distance
	  if ( dist < max_dist )
		knn_set0[max_dist_id] = dist;
	}

	// Output knn_set
	for(int i = 0; i < K_CONST; i++)
	{
		Output_2.write(knn_set0[i]);
	}

	TRAINING_LOOP_1 : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
	{
	  #pragma HLS pipeline
	  // Update the KNN set
	  // Compute the difference using XOR
	  WholeDigitType diff = test_inst ^ training_set1[i];
	  int dist = 0;

	  dist = popcount(diff);

	  int max_dist = 0;
	  int max_dist_id = K_CONST+1;
	  int k = 0;

	  // Find the max distance
	  FIND_MAX_DIST_1: for ( int k = 0; k < K_CONST; ++k )
	  {
		if ( knn_set1[k] > max_dist )
		{
		  max_dist = knn_set1[k];
		  max_dist_id = k;
		}
	  }

	  // Replace the entry with the max distance
	  if ( dist < max_dist )
		knn_set1[max_dist_id] = dist;
	}
    index = 2;
    return;
  }


    // Output knn_set if index = 2
	// turn index to 1, then return
	if (index == 2){
	    for(int i = 0; i < K_CONST; i++)
	    {
	        Output_2.write(knn_set1[i]);
	    }

	    for(int i = 0; i < K_CONST * (PAR_FACTOR - 2 * 15); i ++)
	    {
	    	Output_2.write(Input_2.read());
	    }
	    index = 1;
	    return;
	}

  return;
}
void update_knn_cluster_15(hls::stream<ap_uint<32> > & Input_1, hls::stream<ap_uint<32> > & Output_1, hls::stream<ap_uint<32> > & Input_2, hls::stream<ap_uint<32> > & Output_2)
{
  #pragma HLS inline
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
#pragma HLS INTERFACE ap_hs port=Input_2
#pragma HLS INTERFACE ap_hs port=Output_2
  static int knn_set0[K_CONST];
  static int knn_set1[K_CONST];
#pragma HLS array_partition variable=knn_set0 complete dim=0
#pragma HLS array_partition variable=knn_set1 complete dim=0
  // Store 900 training data and pass all rest training data
  static WholeDigitType training_set0 [NUM_TRAINING / PAR_FACTOR];
  static WholeDigitType training_set1 [NUM_TRAINING / PAR_FACTOR];
  const int unroll_factor = PAR_FACTOR;
#pragma HLS array_partition variable=training_set0 block factor=unroll_factor dim=0
#pragma HLS array_partition variable=training_set1 block factor=unroll_factor dim=0
  WholeDigitType data_temp;
  static int index = 0;
  // read training data if index = 0
  // turn index to 1, then return
  if (index == 0)
  {
	  for(int i = 0; i < NUM_TRAINING / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		training_set0[i].range(255, 224) =Input_1.read();
		training_set0[i].range(223, 192) =Input_1.read();
		training_set0[i].range(191, 160) =Input_1.read();
		training_set0[i].range(159, 128) =Input_1.read();
		training_set0[i].range(127, 96 ) =Input_1.read();
		training_set0[i].range(95 , 64 ) =Input_1.read();
		training_set0[i].range(63 , 32 ) =Input_1.read();
		training_set0[i].range(31 , 0  ) =Input_1.read();
	  }
	  for(int i = 0; i < NUM_TRAINING / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		training_set1[i].range(255, 224) =Input_1.read();
		training_set1[i].range(223, 192) =Input_1.read();
		training_set1[i].range(191, 160) =Input_1.read();
		training_set1[i].range(159, 128) =Input_1.read();
		training_set1[i].range(127, 96 ) =Input_1.read();
		training_set1[i].range(95 , 64 ) =Input_1.read();
		training_set1[i].range(63 , 32 ) =Input_1.read();
		training_set1[i].range(31 , 0  ) =Input_1.read();
	  }
	  for(int i = 0; i < NUM_TRAINING * (PAR_FACTOR - 2 * 16) / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		data_temp.range(255, 224) =Input_1.read();
		data_temp.range(223, 192) =Input_1.read();
		data_temp.range(191, 160) =Input_1.read();
		data_temp.range(159, 128) =Input_1.read();
		data_temp.range(127, 96 ) =Input_1.read();
		data_temp.range(95 , 64 ) =Input_1.read();
		data_temp.range(63 , 32 ) =Input_1.read();
		data_temp.range(31 , 0  ) =Input_1.read();
		Output_1.write(data_temp.range(255, 224));
		Output_1.write(data_temp.range(223, 192));
		Output_1.write(data_temp.range(191, 160));
		Output_1.write(data_temp.range(159, 128));
		Output_1.write(data_temp.range(127, 96 ));
		Output_1.write(data_temp.range(95 , 64 ));
		Output_1.write(data_temp.range(63 , 32 ));
		Output_1.write(data_temp.range(31 , 0  ));
	  }
	  index = 1;
	  return;
  }



  // get a test data and update knn value if index = 1
  // turn index to 2, then return
  if (index == 1)
  {
    WholeDigitType test_inst;
	// Get testing data
	test_inst.range(255, 224) =Input_1.read();
	test_inst.range(223, 192) =Input_1.read();
	test_inst.range(191, 160) =Input_1.read();
	test_inst.range(159, 128) =Input_1.read();
	test_inst.range(127, 96 ) =Input_1.read();
	test_inst.range(95 , 64 ) =Input_1.read();
	test_inst.range(63 , 32 ) =Input_1.read();
	test_inst.range(31 , 0  ) =Input_1.read();
	// Pass it to the next kernel
	Output_1.write(test_inst.range(255, 224));
	Output_1.write(test_inst.range(223, 192));
	Output_1.write(test_inst.range(191, 160));
	Output_1.write(test_inst.range(159, 128));
	Output_1.write(test_inst.range(127, 96 ));
	Output_1.write(test_inst.range(95 , 64 ));
	Output_1.write(test_inst.range(63 , 32 ));
	Output_1.write(test_inst.range(31 , 0  ));
	// Preset knn_set
	for(int i = 0; i < K_CONST; i++)
	{
		#pragma HLS unroll
		knn_set0[i] = 256;
		knn_set1[i] = 256;
	}

	TRAINING_LOOP_0 : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
	{
	  #pragma HLS pipeline
	  // Update the KNN set
	  // Compute the difference using XOR
	  WholeDigitType diff = test_inst ^ training_set0[i];
	  int dist = 0;

	  dist = popcount(diff);

	  int max_dist = 0;
	  int max_dist_id = K_CONST+1;
	  int k = 0;

	  // Find the max distance
	  FIND_MAX_DIST_0: for ( int k = 0; k < K_CONST; ++k )
	  {
		if ( knn_set0[k] > max_dist )
		{
		  max_dist = knn_set0[k];
		  max_dist_id = k;
		}
	  }

	  // Replace the entry with the max distance
	  if ( dist < max_dist )
		knn_set0[max_dist_id] = dist;
	}

	// Output knn_set
	for(int i = 0; i < K_CONST; i++)
	{
		Output_2.write(knn_set0[i]);
	}

	TRAINING_LOOP_1 : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
	{
	  #pragma HLS pipeline
	  // Update the KNN set
	  // Compute the difference using XOR
	  WholeDigitType diff = test_inst ^ training_set1[i];
	  int dist = 0;

	  dist = popcount(diff);

	  int max_dist = 0;
	  int max_dist_id = K_CONST+1;
	  int k = 0;

	  // Find the max distance
	  FIND_MAX_DIST_1: for ( int k = 0; k < K_CONST; ++k )
	  {
		if ( knn_set1[k] > max_dist )
		{
		  max_dist = knn_set1[k];
		  max_dist_id = k;
		}
	  }

	  // Replace the entry with the max distance
	  if ( dist < max_dist )
		knn_set1[max_dist_id] = dist;
	}
    index = 2;
    return;
  }


    // Output knn_set if index = 2
	// turn index to 1, then return
	if (index == 2){
	    for(int i = 0; i < K_CONST; i++)
	    {
	        Output_2.write(knn_set1[i]);
	    }

	    for(int i = 0; i < K_CONST * (PAR_FACTOR - 2 * 16); i ++)
	    {
	    	Output_2.write(Input_2.read());
	    }
	    index = 1;
	    return;
	}

  return;
}
void update_knn_cluster_16(hls::stream<ap_uint<32> > & Input_1, hls::stream<ap_uint<32> > & Output_1, hls::stream<ap_uint<32> > & Input_2, hls::stream<ap_uint<32> > & Output_2)
{
  #pragma HLS inline
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
#pragma HLS INTERFACE ap_hs port=Input_2
#pragma HLS INTERFACE ap_hs port=Output_2
  static int knn_set0[K_CONST];
  static int knn_set1[K_CONST];
#pragma HLS array_partition variable=knn_set0 complete dim=0
#pragma HLS array_partition variable=knn_set1 complete dim=0
  // Store 900 training data and pass all rest training data
  static WholeDigitType training_set0 [NUM_TRAINING / PAR_FACTOR];
  static WholeDigitType training_set1 [NUM_TRAINING / PAR_FACTOR];
  const int unroll_factor = PAR_FACTOR;
#pragma HLS array_partition variable=training_set0 block factor=unroll_factor dim=0
#pragma HLS array_partition variable=training_set1 block factor=unroll_factor dim=0
  WholeDigitType data_temp;
  static int index = 0;
  // read training data if index = 0
  // turn index to 1, then return
  if (index == 0)
  {
	  for(int i = 0; i < NUM_TRAINING / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		training_set0[i].range(255, 224) =Input_1.read();
		training_set0[i].range(223, 192) =Input_1.read();
		training_set0[i].range(191, 160) =Input_1.read();
		training_set0[i].range(159, 128) =Input_1.read();
		training_set0[i].range(127, 96 ) =Input_1.read();
		training_set0[i].range(95 , 64 ) =Input_1.read();
		training_set0[i].range(63 , 32 ) =Input_1.read();
		training_set0[i].range(31 , 0  ) =Input_1.read();
	  }
	  for(int i = 0; i < NUM_TRAINING / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		training_set1[i].range(255, 224) =Input_1.read();
		training_set1[i].range(223, 192) =Input_1.read();
		training_set1[i].range(191, 160) =Input_1.read();
		training_set1[i].range(159, 128) =Input_1.read();
		training_set1[i].range(127, 96 ) =Input_1.read();
		training_set1[i].range(95 , 64 ) =Input_1.read();
		training_set1[i].range(63 , 32 ) =Input_1.read();
		training_set1[i].range(31 , 0  ) =Input_1.read();
	  }
	  for(int i = 0; i < NUM_TRAINING * (PAR_FACTOR - 2 * 17) / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		data_temp.range(255, 224) =Input_1.read();
		data_temp.range(223, 192) =Input_1.read();
		data_temp.range(191, 160) =Input_1.read();
		data_temp.range(159, 128) =Input_1.read();
		data_temp.range(127, 96 ) =Input_1.read();
		data_temp.range(95 , 64 ) =Input_1.read();
		data_temp.range(63 , 32 ) =Input_1.read();
		data_temp.range(31 , 0  ) =Input_1.read();
		Output_1.write(data_temp.range(255, 224));
		Output_1.write(data_temp.range(223, 192));
		Output_1.write(data_temp.range(191, 160));
		Output_1.write(data_temp.range(159, 128));
		Output_1.write(data_temp.range(127, 96 ));
		Output_1.write(data_temp.range(95 , 64 ));
		Output_1.write(data_temp.range(63 , 32 ));
		Output_1.write(data_temp.range(31 , 0  ));
	  }
	  index = 1;
	  return;
  }



  // get a test data and update knn value if index = 1
  // turn index to 2, then return
  if (index == 1)
  {
    WholeDigitType test_inst;
	// Get testing data
	test_inst.range(255, 224) =Input_1.read();
	test_inst.range(223, 192) =Input_1.read();
	test_inst.range(191, 160) =Input_1.read();
	test_inst.range(159, 128) =Input_1.read();
	test_inst.range(127, 96 ) =Input_1.read();
	test_inst.range(95 , 64 ) =Input_1.read();
	test_inst.range(63 , 32 ) =Input_1.read();
	test_inst.range(31 , 0  ) =Input_1.read();
	// Pass it to the next kernel
	Output_1.write(test_inst.range(255, 224));
	Output_1.write(test_inst.range(223, 192));
	Output_1.write(test_inst.range(191, 160));
	Output_1.write(test_inst.range(159, 128));
	Output_1.write(test_inst.range(127, 96 ));
	Output_1.write(test_inst.range(95 , 64 ));
	Output_1.write(test_inst.range(63 , 32 ));
	Output_1.write(test_inst.range(31 , 0  ));
	// Preset knn_set
	for(int i = 0; i < K_CONST; i++)
	{
		#pragma HLS unroll
		knn_set0[i] = 256;
		knn_set1[i] = 256;
	}

	TRAINING_LOOP_0 : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
	{
	  #pragma HLS pipeline
	  // Update the KNN set
	  // Compute the difference using XOR
	  WholeDigitType diff = test_inst ^ training_set0[i];
	  int dist = 0;

	  dist = popcount(diff);

	  int max_dist = 0;
	  int max_dist_id = K_CONST+1;
	  int k = 0;

	  // Find the max distance
	  FIND_MAX_DIST_0: for ( int k = 0; k < K_CONST; ++k )
	  {
		if ( knn_set0[k] > max_dist )
		{
		  max_dist = knn_set0[k];
		  max_dist_id = k;
		}
	  }

	  // Replace the entry with the max distance
	  if ( dist < max_dist )
		knn_set0[max_dist_id] = dist;
	}

	// Output knn_set
	for(int i = 0; i < K_CONST; i++)
	{
		Output_2.write(knn_set0[i]);
	}

	TRAINING_LOOP_1 : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
	{
	  #pragma HLS pipeline
	  // Update the KNN set
	  // Compute the difference using XOR
	  WholeDigitType diff = test_inst ^ training_set1[i];
	  int dist = 0;

	  dist = popcount(diff);

	  int max_dist = 0;
	  int max_dist_id = K_CONST+1;
	  int k = 0;

	  // Find the max distance
	  FIND_MAX_DIST_1: for ( int k = 0; k < K_CONST; ++k )
	  {
		if ( knn_set1[k] > max_dist )
		{
		  max_dist = knn_set1[k];
		  max_dist_id = k;
		}
	  }

	  // Replace the entry with the max distance
	  if ( dist < max_dist )
		knn_set1[max_dist_id] = dist;
	}
    index = 2;
    return;
  }


    // Output knn_set if index = 2
	// turn index to 1, then return
	if (index == 2){
	    for(int i = 0; i < K_CONST; i++)
	    {
	        Output_2.write(knn_set1[i]);
	    }

	    for(int i = 0; i < K_CONST * (PAR_FACTOR - 2 * 17); i ++)
	    {
	    	Output_2.write(Input_2.read());
	    }
	    index = 1;
	    return;
	}

  return;
}
void update_knn_cluster_17(hls::stream<ap_uint<32> > & Input_1, hls::stream<ap_uint<32> > & Output_1, hls::stream<ap_uint<32> > & Input_2, hls::stream<ap_uint<32> > & Output_2)
{
  #pragma HLS inline
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
#pragma HLS INTERFACE ap_hs port=Input_2
#pragma HLS INTERFACE ap_hs port=Output_2
  static int knn_set0[K_CONST];
  static int knn_set1[K_CONST];
#pragma HLS array_partition variable=knn_set0 complete dim=0
#pragma HLS array_partition variable=knn_set1 complete dim=0
  // Store 900 training data and pass all rest training data
  static WholeDigitType training_set0 [NUM_TRAINING / PAR_FACTOR];
  static WholeDigitType training_set1 [NUM_TRAINING / PAR_FACTOR];
  const int unroll_factor = PAR_FACTOR;
#pragma HLS array_partition variable=training_set0 block factor=unroll_factor dim=0
#pragma HLS array_partition variable=training_set1 block factor=unroll_factor dim=0
  WholeDigitType data_temp;
  static int index = 0;
  // read training data if index = 0
  // turn index to 1, then return
  if (index == 0)
  {
	  for(int i = 0; i < NUM_TRAINING / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		training_set0[i].range(255, 224) =Input_1.read();
		training_set0[i].range(223, 192) =Input_1.read();
		training_set0[i].range(191, 160) =Input_1.read();
		training_set0[i].range(159, 128) =Input_1.read();
		training_set0[i].range(127, 96 ) =Input_1.read();
		training_set0[i].range(95 , 64 ) =Input_1.read();
		training_set0[i].range(63 , 32 ) =Input_1.read();
		training_set0[i].range(31 , 0  ) =Input_1.read();
	  }
	  for(int i = 0; i < NUM_TRAINING / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		training_set1[i].range(255, 224) =Input_1.read();
		training_set1[i].range(223, 192) =Input_1.read();
		training_set1[i].range(191, 160) =Input_1.read();
		training_set1[i].range(159, 128) =Input_1.read();
		training_set1[i].range(127, 96 ) =Input_1.read();
		training_set1[i].range(95 , 64 ) =Input_1.read();
		training_set1[i].range(63 , 32 ) =Input_1.read();
		training_set1[i].range(31 , 0  ) =Input_1.read();
	  }
	  for(int i = 0; i < NUM_TRAINING * (PAR_FACTOR - 2 * 18) / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		data_temp.range(255, 224) =Input_1.read();
		data_temp.range(223, 192) =Input_1.read();
		data_temp.range(191, 160) =Input_1.read();
		data_temp.range(159, 128) =Input_1.read();
		data_temp.range(127, 96 ) =Input_1.read();
		data_temp.range(95 , 64 ) =Input_1.read();
		data_temp.range(63 , 32 ) =Input_1.read();
		data_temp.range(31 , 0  ) =Input_1.read();
		Output_1.write(data_temp.range(255, 224));
		Output_1.write(data_temp.range(223, 192));
		Output_1.write(data_temp.range(191, 160));
		Output_1.write(data_temp.range(159, 128));
		Output_1.write(data_temp.range(127, 96 ));
		Output_1.write(data_temp.range(95 , 64 ));
		Output_1.write(data_temp.range(63 , 32 ));
		Output_1.write(data_temp.range(31 , 0  ));
	  }
	  index = 1;
	  return;
  }



  // get a test data and update knn value if index = 1
  // turn index to 2, then return
  if (index == 1)
  {
    WholeDigitType test_inst;
	// Get testing data
	test_inst.range(255, 224) =Input_1.read();
	test_inst.range(223, 192) =Input_1.read();
	test_inst.range(191, 160) =Input_1.read();
	test_inst.range(159, 128) =Input_1.read();
	test_inst.range(127, 96 ) =Input_1.read();
	test_inst.range(95 , 64 ) =Input_1.read();
	test_inst.range(63 , 32 ) =Input_1.read();
	test_inst.range(31 , 0  ) =Input_1.read();
	// Pass it to the next kernel
	Output_1.write(test_inst.range(255, 224));
	Output_1.write(test_inst.range(223, 192));
	Output_1.write(test_inst.range(191, 160));
	Output_1.write(test_inst.range(159, 128));
	Output_1.write(test_inst.range(127, 96 ));
	Output_1.write(test_inst.range(95 , 64 ));
	Output_1.write(test_inst.range(63 , 32 ));
	Output_1.write(test_inst.range(31 , 0  ));
	// Preset knn_set
	for(int i = 0; i < K_CONST; i++)
	{
		#pragma HLS unroll
		knn_set0[i] = 256;
		knn_set1[i] = 256;
	}

	TRAINING_LOOP_0 : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
	{
	  #pragma HLS pipeline
	  // Update the KNN set
	  // Compute the difference using XOR
	  WholeDigitType diff = test_inst ^ training_set0[i];
	  int dist = 0;

	  dist = popcount(diff);

	  int max_dist = 0;
	  int max_dist_id = K_CONST+1;
	  int k = 0;

	  // Find the max distance
	  FIND_MAX_DIST_0: for ( int k = 0; k < K_CONST; ++k )
	  {
		if ( knn_set0[k] > max_dist )
		{
		  max_dist = knn_set0[k];
		  max_dist_id = k;
		}
	  }

	  // Replace the entry with the max distance
	  if ( dist < max_dist )
		knn_set0[max_dist_id] = dist;
	}

	// Output knn_set
	for(int i = 0; i < K_CONST; i++)
	{
		Output_2.write(knn_set0[i]);
	}

	TRAINING_LOOP_1 : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
	{
	  #pragma HLS pipeline
	  // Update the KNN set
	  // Compute the difference using XOR
	  WholeDigitType diff = test_inst ^ training_set1[i];
	  int dist = 0;

	  dist = popcount(diff);

	  int max_dist = 0;
	  int max_dist_id = K_CONST+1;
	  int k = 0;

	  // Find the max distance
	  FIND_MAX_DIST_1: for ( int k = 0; k < K_CONST; ++k )
	  {
		if ( knn_set1[k] > max_dist )
		{
		  max_dist = knn_set1[k];
		  max_dist_id = k;
		}
	  }

	  // Replace the entry with the max distance
	  if ( dist < max_dist )
		knn_set1[max_dist_id] = dist;
	}
    index = 2;
    return;
  }


    // Output knn_set if index = 2
	// turn index to 1, then return
	if (index == 2){
	    for(int i = 0; i < K_CONST; i++)
	    {
	        Output_2.write(knn_set1[i]);
	    }

	    for(int i = 0; i < K_CONST * (PAR_FACTOR - 2 * 18); i ++)
	    {
	    	Output_2.write(Input_2.read());
	    }
	    index = 1;
	    return;
	}

  return;
}
void update_knn_cluster_18(hls::stream<ap_uint<32> > & Input_1, hls::stream<ap_uint<32> > & Output_1, hls::stream<ap_uint<32> > & Input_2, hls::stream<ap_uint<32> > & Output_2)
{
  #pragma HLS inline
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
#pragma HLS INTERFACE ap_hs port=Input_2
#pragma HLS INTERFACE ap_hs port=Output_2
  static int knn_set0[K_CONST];
  static int knn_set1[K_CONST];
#pragma HLS array_partition variable=knn_set0 complete dim=0
#pragma HLS array_partition variable=knn_set1 complete dim=0
  // Store 900 training data and pass all rest training data
  static WholeDigitType training_set0 [NUM_TRAINING / PAR_FACTOR];
  static WholeDigitType training_set1 [NUM_TRAINING / PAR_FACTOR];
  const int unroll_factor = PAR_FACTOR;
#pragma HLS array_partition variable=training_set0 block factor=unroll_factor dim=0
#pragma HLS array_partition variable=training_set1 block factor=unroll_factor dim=0
  WholeDigitType data_temp;
  static int index = 0;
  // read training data if index = 0
  // turn index to 1, then return
  if (index == 0)
  {
	  for(int i = 0; i < NUM_TRAINING / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		training_set0[i].range(255, 224) =Input_1.read();
		training_set0[i].range(223, 192) =Input_1.read();
		training_set0[i].range(191, 160) =Input_1.read();
		training_set0[i].range(159, 128) =Input_1.read();
		training_set0[i].range(127, 96 ) =Input_1.read();
		training_set0[i].range(95 , 64 ) =Input_1.read();
		training_set0[i].range(63 , 32 ) =Input_1.read();
		training_set0[i].range(31 , 0  ) =Input_1.read();
	  }
	  for(int i = 0; i < NUM_TRAINING / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		training_set1[i].range(255, 224) =Input_1.read();
		training_set1[i].range(223, 192) =Input_1.read();
		training_set1[i].range(191, 160) =Input_1.read();
		training_set1[i].range(159, 128) =Input_1.read();
		training_set1[i].range(127, 96 ) =Input_1.read();
		training_set1[i].range(95 , 64 ) =Input_1.read();
		training_set1[i].range(63 , 32 ) =Input_1.read();
		training_set1[i].range(31 , 0  ) =Input_1.read();
	  }
	  for(int i = 0; i < NUM_TRAINING * (PAR_FACTOR - 2 * 19) / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		data_temp.range(255, 224) =Input_1.read();
		data_temp.range(223, 192) =Input_1.read();
		data_temp.range(191, 160) =Input_1.read();
		data_temp.range(159, 128) =Input_1.read();
		data_temp.range(127, 96 ) =Input_1.read();
		data_temp.range(95 , 64 ) =Input_1.read();
		data_temp.range(63 , 32 ) =Input_1.read();
		data_temp.range(31 , 0  ) =Input_1.read();
		Output_1.write(data_temp.range(255, 224));
		Output_1.write(data_temp.range(223, 192));
		Output_1.write(data_temp.range(191, 160));
		Output_1.write(data_temp.range(159, 128));
		Output_1.write(data_temp.range(127, 96 ));
		Output_1.write(data_temp.range(95 , 64 ));
		Output_1.write(data_temp.range(63 , 32 ));
		Output_1.write(data_temp.range(31 , 0  ));
	  }
	  index = 1;
	  return;
  }



  // get a test data and update knn value if index = 1
  // turn index to 2, then return
  if (index == 1)
  {
    WholeDigitType test_inst;
	// Get testing data
	test_inst.range(255, 224) =Input_1.read();
	test_inst.range(223, 192) =Input_1.read();
	test_inst.range(191, 160) =Input_1.read();
	test_inst.range(159, 128) =Input_1.read();
	test_inst.range(127, 96 ) =Input_1.read();
	test_inst.range(95 , 64 ) =Input_1.read();
	test_inst.range(63 , 32 ) =Input_1.read();
	test_inst.range(31 , 0  ) =Input_1.read();
	// Pass it to the next kernel
	Output_1.write(test_inst.range(255, 224));
	Output_1.write(test_inst.range(223, 192));
	Output_1.write(test_inst.range(191, 160));
	Output_1.write(test_inst.range(159, 128));
	Output_1.write(test_inst.range(127, 96 ));
	Output_1.write(test_inst.range(95 , 64 ));
	Output_1.write(test_inst.range(63 , 32 ));
	Output_1.write(test_inst.range(31 , 0  ));
	// Preset knn_set
	for(int i = 0; i < K_CONST; i++)
	{
		#pragma HLS unroll
		knn_set0[i] = 256;
		knn_set1[i] = 256;
	}

	TRAINING_LOOP_0 : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
	{
	  #pragma HLS pipeline
	  // Update the KNN set
	  // Compute the difference using XOR
	  WholeDigitType diff = test_inst ^ training_set0[i];
	  int dist = 0;

	  dist = popcount(diff);

	  int max_dist = 0;
	  int max_dist_id = K_CONST+1;
	  int k = 0;

	  // Find the max distance
	  FIND_MAX_DIST_0: for ( int k = 0; k < K_CONST; ++k )
	  {
		if ( knn_set0[k] > max_dist )
		{
		  max_dist = knn_set0[k];
		  max_dist_id = k;
		}
	  }

	  // Replace the entry with the max distance
	  if ( dist < max_dist )
		knn_set0[max_dist_id] = dist;
	}

	// Output knn_set
	for(int i = 0; i < K_CONST; i++)
	{
		Output_2.write(knn_set0[i]);
	}

	TRAINING_LOOP_1 : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
	{
	  #pragma HLS pipeline
	  // Update the KNN set
	  // Compute the difference using XOR
	  WholeDigitType diff = test_inst ^ training_set1[i];
	  int dist = 0;

	  dist = popcount(diff);

	  int max_dist = 0;
	  int max_dist_id = K_CONST+1;
	  int k = 0;

	  // Find the max distance
	  FIND_MAX_DIST_1: for ( int k = 0; k < K_CONST; ++k )
	  {
		if ( knn_set1[k] > max_dist )
		{
		  max_dist = knn_set1[k];
		  max_dist_id = k;
		}
	  }

	  // Replace the entry with the max distance
	  if ( dist < max_dist )
		knn_set1[max_dist_id] = dist;
	}
    index = 2;
    return;
  }


    // Output knn_set if index = 2
	// turn index to 1, then return
	if (index == 2){
	    for(int i = 0; i < K_CONST; i++)
	    {
	        Output_2.write(knn_set1[i]);
	    }

	    for(int i = 0; i < K_CONST * (PAR_FACTOR - 2 * 19); i ++)
	    {
	    	Output_2.write(Input_2.read());
	    }
	    index = 1;
	    return;
	}

  return;
}
void update_knn_cluster_19(hls::stream<ap_uint<32> > & Input_1 , hls::stream<ap_uint<32> > & Output_1)
{
  #pragma HLS inline
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
  static int knn_set0[K_CONST];
  static int knn_set1[K_CONST];
#pragma HLS array_partition variable=knn_set0 complete dim=0
#pragma HLS array_partition variable=knn_set1 complete dim=0
  // Store 900 training data and pass all rest training data
  static WholeDigitType training_set0 [NUM_TRAINING / PAR_FACTOR];
  static WholeDigitType training_set1 [NUM_TRAINING / PAR_FACTOR];
  const int unroll_factor = PAR_FACTOR;
#pragma HLS array_partition variable=training_set0 block factor=unroll_factor dim=0
#pragma HLS array_partition variable=training_set1 block factor=unroll_factor dim=0
  WholeDigitType data_temp;
  static int index = 0;
  // read training data if index = 0
  // turn index to 1, then return
  if (index == 0)
  {
	  for(int i = 0; i < NUM_TRAINING / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		training_set0[i].range(255, 224) =Input_1.read();
		training_set0[i].range(223, 192) =Input_1.read();
		training_set0[i].range(191, 160) =Input_1.read();
		training_set0[i].range(159, 128) =Input_1.read();
		training_set0[i].range(127, 96 ) =Input_1.read();
		training_set0[i].range(95 , 64 ) =Input_1.read();
		training_set0[i].range(63 , 32 ) =Input_1.read();
		training_set0[i].range(31 , 0  ) =Input_1.read();
	  }
	  for(int i = 0; i < NUM_TRAINING / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		training_set1[i].range(255, 224) =Input_1.read();
		training_set1[i].range(223, 192) =Input_1.read();
		training_set1[i].range(191, 160) =Input_1.read();
		training_set1[i].range(159, 128) =Input_1.read();
		training_set1[i].range(127, 96 ) =Input_1.read();
		training_set1[i].range(95 , 64 ) =Input_1.read();
		training_set1[i].range(63 , 32 ) =Input_1.read();
		training_set1[i].range(31 , 0  ) =Input_1.read();
	  }
	  /*for(int i = 0; i < NUM_TRAINING * (PAR_FACTOR - 2 * 20) / PAR_FACTOR; i++)
	  {
		#pragma HLS pipeline
		data_temp.range(255, 224) =Input_1.read();
		data_temp.range(223, 192) =Input_1.read();
		data_temp.range(191, 160) =Input_1.read();
		data_temp.range(159, 128) =Input_1.read();
		data_temp.range(127, 96 ) =Input_1.read();
		data_temp.range(95 , 64 ) =Input_1.read();
		data_temp.range(63 , 32 ) =Input_1.read();
		data_temp.range(31 , 0  ) =Input_1.read();
		Output_1.write(data_temp.range(255, 224));
		Output_1.write(data_temp.range(223, 192));
		Output_1.write(data_temp.range(191, 160));
		Output_1.write(data_temp.range(159, 128));
		Output_1.write(data_temp.range(127, 96 ));
		Output_1.write(data_temp.range(95 , 64 ));
		Output_1.write(data_temp.range(63 , 32 ));
		Output_1.write(data_temp.range(31 , 0  ));
	  }*/
	  index = 1;
	  return;
  }



  // get a test data and update knn value if index = 1
  // turn index to 2, then return
  if (index == 1)
  {
    WholeDigitType test_inst;
	// Get testing data
	test_inst.range(255, 224) =Input_1.read();
	test_inst.range(223, 192) =Input_1.read();
	test_inst.range(191, 160) =Input_1.read();
	test_inst.range(159, 128) =Input_1.read();
	test_inst.range(127, 96 ) =Input_1.read();
	test_inst.range(95 , 64 ) =Input_1.read();
	test_inst.range(63 , 32 ) =Input_1.read();
	test_inst.range(31 , 0  ) =Input_1.read();
	// Pass it to the next kernel
	/*Output_1.write(test_inst.range(255, 224));
	Output_1.write(test_inst.range(223, 192));
	Output_1.write(test_inst.range(191, 160));
	Output_1.write(test_inst.range(159, 128));
	Output_1.write(test_inst.range(127, 96 ));
	Output_1.write(test_inst.range(95 , 64 ));
	Output_1.write(test_inst.range(63 , 32 ));
	Output_1.write(test_inst.range(31 , 0  ));*/
	// Preset knn_set
	for(int i = 0; i < K_CONST; i++)
	{
		#pragma HLS unroll
		knn_set0[i] = 256;
		knn_set1[i] = 256;
	}

	TRAINING_LOOP_0 : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
	{
	  #pragma HLS pipeline
	  // Update the KNN set
	  // Compute the difference using XOR
	  WholeDigitType diff = test_inst ^ training_set0[i];
	  int dist = 0;

	  dist = popcount(diff);

	  int max_dist = 0;
	  int max_dist_id = K_CONST+1;
	  int k = 0;

	  // Find the max distance
	  FIND_MAX_DIST_0: for ( int k = 0; k < K_CONST; ++k )
	  {
		if ( knn_set0[k] > max_dist )
		{
		  max_dist = knn_set0[k];
		  max_dist_id = k;
		}
	  }

	  // Replace the entry with the max distance
	  if ( dist < max_dist )
		knn_set0[max_dist_id] = dist;
	}

	// Output knn_set
	for(int i = 0; i < K_CONST; i++)
	{
		Output_1.write(knn_set0[i]);
	}

	TRAINING_LOOP_1 : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
	{
	  #pragma HLS pipeline
	  // Update the KNN set
	  // Compute the difference using XOR
	  WholeDigitType diff = test_inst ^ training_set1[i];
	  int dist = 0;

	  dist = popcount(diff);

	  int max_dist = 0;
	  int max_dist_id = K_CONST+1;
	  int k = 0;

	  // Find the max distance
	  FIND_MAX_DIST_1: for ( int k = 0; k < K_CONST; ++k )
	  {
		if ( knn_set1[k] > max_dist )
		{
		  max_dist = knn_set1[k];
		  max_dist_id = k;
		}
	  }

	  // Replace the entry with the max distance
	  if ( dist < max_dist )
		knn_set1[max_dist_id] = dist;
	}
    index = 2;
    return;
  }


    // Output knn_set if index = 2
	// turn index to 1, then return
	if (index == 2){
	    for(int i = 0; i < K_CONST; i++)
	    {
	        Output_1.write(knn_set1[i]);
	    }

	    index = 1;
	    return;
	}

  return;
}


// Given 10xK minimum distance values, this function
// finds the actual K nearest neighbors and determines the
// final output based on the most common int represented by
// these nearest neighbors (i.e., a vote among KNNs).

void knn_vote_cluster0(hls::stream<ap_uint<32> > & Input_1, hls::stream<ap_uint<32> > & Output_1)
{
  #pragma HLS inline
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
  // local buffers
  static int knn_set[PAR_FACTOR * K_CONST / 2];
#pragma HLS array_partition variable=knn_set complete dim=0
  // final K nearest neighbors
  int min_distance_list[K_CONST];
  #pragma HLS array_partition variable=min_distance_list complete dim=0
  // labels for the K nearest neighbors
  int label_list[K_CONST];
  #pragma HLS array_partition variable=label_list complete dim=0
  // voting boxes

  // Get knn_set
  for(int i = 0; i < PAR_FACTOR * K_CONST / 2; i ++)
  {
	  knn_set[i] = Input_1.read();
  }
  for(int i = 0; i < PAR_FACTOR * K_CONST / 2; i ++)
  {
    Output_1.write(Input_1.read());
  }
  int pos = 1000;

  // initialize
  INIT_1: for (int i = 0;i < K_CONST; i ++ )
  {
	#pragma HLS unroll
	min_distance_list[i] = 256;
	label_list[i] = 9;
  }

  // go through all the lanes
  // do an insertion sort to keep a sorted neighbor list
  LANES: for (int i = 0; i < PAR_FACTOR / 2; i ++ )
  {
	INSERTION_SORT_OUTER: for (int j = 0; j < K_CONST; j ++ )
	{
	  #pragma HLS pipeline
	  pos = 1000;
	  INSERTION_SORT_INNER: for (int r = 0; r < K_CONST; r ++ )
	  {
		#pragma HLS unroll
		pos = ((knn_set[i*K_CONST+j] < min_distance_list[r]) && (pos > K_CONST)) ? r : pos;
	  }

	  INSERT: for (int r = K_CONST ;r > 0; r -- )
	  {
		#pragma HLS unroll
		if(r-1 > pos)
		{
		  min_distance_list[r-1] = min_distance_list[r-2];
		  label_list[r-1] = label_list[r-2];
		}
		else if (r-1 == pos)
		{
		  min_distance_list[r-1] = knn_set[i*K_CONST+j];
		  label_list[r-1] = i / (PAR_FACTOR / 10);
		}
	  }
	}
  }
  for(int i = 0; i < K_CONST; i++)
  {
	  Output_1.write(min_distance_list[i]);
	  Output_1.write(label_list[i]);
  }


  return;
}
void knn_vote_cluster1(hls::stream<ap_uint<32> > & Input_1, hls::stream<ap_uint<128> > & Output_1)
{
  #pragma HLS inline
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
  // local buffers
  static int knn_set[PAR_FACTOR * K_CONST / 2];
#pragma HLS array_partition variable=knn_set complete dim=0
  // final K nearest neighbors
  int min_distance_list[K_CONST];
  #pragma HLS array_partition variable=min_distance_list complete dim=0
  // labels for the K nearest neighbors
  int label_list[K_CONST];
  #pragma HLS array_partition variable=label_list complete dim=0
  // voting boxes
  int vote_list[10];
  #pragma HLS array_partition variable=vote_list complete dim=0

  // Get knn_set
  for(int i = 0; i < PAR_FACTOR * K_CONST / 2; i ++)
  {
	  knn_set[i] = Input_1.read();
  }
  int pos = 1000;

  // initialize
  INIT_1: for (int i = 0;i < K_CONST; i ++ )
  {
	#pragma HLS unroll
	min_distance_list[i] = Input_1.read();
	label_list[i] = Input_1.read();
  }

  INIT_2: for (int i = 0;i < 10; i ++ )
  {
	#pragma HLS unroll
	vote_list[i] = 0;
  }

  // go through all the lanes
  // do an insertion sort to keep a sorted neighbor list
  LANES: for (int i = 0; i < PAR_FACTOR / 2; i ++ )
  {
	INSERTION_SORT_OUTER: for (int j = 0; j < K_CONST; j ++ )
	{
	  #pragma HLS pipeline
	  pos = 1000;
	  INSERTION_SORT_INNER: for (int r = 0; r < K_CONST; r ++ )
	  {
		#pragma HLS unroll
		pos = ((knn_set[i*K_CONST+j] < min_distance_list[r]) && (pos > K_CONST)) ? r : pos;
	  }

	  INSERT: for (int r = K_CONST ;r > 0; r -- )
	  {
		#pragma HLS unroll
		if(r-1 > pos)
		{
		  min_distance_list[r-1] = min_distance_list[r-2];
		  label_list[r-1] = label_list[r-2];
		}
		else if (r-1 == pos)
		{
		  min_distance_list[r-1] = knn_set[i*K_CONST+j];
		  label_list[r-1] = i / (PAR_FACTOR / 10) + 5;
		}
	  }
	}
  }

  // vote
  INCREMENT: for (int i = 0;i < K_CONST; i ++ )
  {
	#pragma HLS pipeline
	vote_list[label_list[i]] += 1;
  }

  LabelType max_vote;
  max_vote = 0;

  // find the maximum value
  VOTE: for (int i = 0;i < 10; i ++ )
  {
	#pragma HLS unroll
	if(vote_list[i] >= vote_list[max_vote])
	{
	  max_vote = i;
	}
  }
  static int index = 1;
  if(index == 1){
	  Output_1.write(2001);
	  index = 0;
  }
  bit128 Output_tmp;
  Output_tmp(7,0) = max_vote;
  Output_tmp(127,8) = 0;

  Output_1.write(Output_tmp);
  return;
}

// top-level hardware function
// since AXIDMA_SIMPLE interface does not support arrays with size more than 16384 on interface
// we call this function twice to transfer data
//void DigitRec(WholeDigitType global_training_set[NUM_TRAINING / 2], WholeDigitType global_test_set[NUM_TEST], LabelType global_results[NUM_TEST], int run)
//{
void DigitRec(hls::stream<ap_uint<128> > & Input_1, hls::stream<ap_uint<128> > & Output_1)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1

  hls::stream<ap_uint<32> > Data_in0("sb00");
  hls::stream<ap_uint<32> > Data_in1("sb01");
  hls::stream<ap_uint<32> > Data_in2("sb02");
  hls::stream<ap_uint<32> > Data_in3("sb03");
  hls::stream<ap_uint<32> > Data_in4("sb04");
  hls::stream<ap_uint<32> > Data_in5("sb05");
  hls::stream<ap_uint<32> > Data_in6("sb06");
  hls::stream<ap_uint<32> > Data_in7("sb07");
  hls::stream<ap_uint<32> > Data_in8("sb08");
  hls::stream<ap_uint<32> > Data_in9("sb09");
  hls::stream<ap_uint<32> > Data_in10("sb10");
  hls::stream<ap_uint<32> > Data_in11("sb11");
  hls::stream<ap_uint<32> > Data_in12("sb12");
  hls::stream<ap_uint<32> > Data_in13("sb13");
  hls::stream<ap_uint<32> > Data_in14("sb14");
  hls::stream<ap_uint<32> > Data_in15("sb15");
  hls::stream<ap_uint<32> > Data_in16("sb16");
  hls::stream<ap_uint<32> > Data_in17("sb17");
  hls::stream<ap_uint<32> > Data_in18("sb18");
  hls::stream<ap_uint<32> > Data_in19("sb19");

  hls::stream<ap_uint<32> > knn_out0("sb20");
  hls::stream<ap_uint<32> > knn_out1("sb21");
  hls::stream<ap_uint<32> > knn_out2("sb22");
  hls::stream<ap_uint<32> > knn_out3("sb23");
  hls::stream<ap_uint<32> > knn_out4("sb24");
  hls::stream<ap_uint<32> > knn_out5("sb25");
  hls::stream<ap_uint<32> > knn_out6("sb26");
  hls::stream<ap_uint<32> > knn_out7("sb27");
  hls::stream<ap_uint<32> > knn_out8("sb28");
  hls::stream<ap_uint<32> > knn_out9("sb29");
  hls::stream<ap_uint<32> > knn_out10("sb30");
  hls::stream<ap_uint<32> > knn_out11("sb31");
  hls::stream<ap_uint<32> > knn_out12("sb32");
  hls::stream<ap_uint<32> > knn_out13("sb33");
  hls::stream<ap_uint<32> > knn_out14("sb34");
  hls::stream<ap_uint<32> > knn_out15("sb35");
  hls::stream<ap_uint<32> > knn_out16("sb36");
  hls::stream<ap_uint<32> > knn_out17("sb37");
  hls::stream<ap_uint<32> > knn_out18("sb38");
  hls::stream<ap_uint<32> > knn_out19("sb39");
  hls::stream<ap_uint<32> > knn_out20("sb40");

  hls::stream<ap_uint<32> > knn_vote0("sb41");

  update_knn_cluster_0(Input_1, Data_in0, knn_out1, knn_out0);
  update_knn_cluster_1(Data_in0, Data_in1, knn_out2, knn_out1);
  update_knn_cluster_2(Data_in1, Data_in2, knn_out3, knn_out2);
  update_knn_cluster_3(Data_in2, Data_in3, knn_out4, knn_out3);
  update_knn_cluster_4(Data_in3, Data_in4, knn_out5, knn_out4);
  update_knn_cluster_5(Data_in4, Data_in5, knn_out6, knn_out5);
  update_knn_cluster_6(Data_in5, Data_in6, knn_out7, knn_out6);
  update_knn_cluster_7(Data_in6, Data_in7, knn_out8, knn_out7);
  update_knn_cluster_8(Data_in7, Data_in8, knn_out9, knn_out8);
  update_knn_cluster_9(Data_in8, Data_in9, knn_out10, knn_out9);
  update_knn_cluster_10(Data_in9, Data_in10, knn_out11, knn_out10);
  update_knn_cluster_11(Data_in10, Data_in11, knn_out12, knn_out11);
  update_knn_cluster_12(Data_in11, Data_in12, knn_out13, knn_out12);
  update_knn_cluster_13(Data_in12, Data_in13, knn_out14, knn_out13);
  update_knn_cluster_14(Data_in13, Data_in14, knn_out15, knn_out14);
  update_knn_cluster_15(Data_in14, Data_in15, knn_out16, knn_out15);
  update_knn_cluster_16(Data_in15, Data_in16, knn_out17, knn_out16);
  update_knn_cluster_17(Data_in16, Data_in17, knn_out18, knn_out17);
  update_knn_cluster_18(Data_in17, Data_in18, knn_out19, knn_out18);
  update_knn_cluster_19(Data_in18, knn_out19);


  TEST_LOOP: for(int t = 0; t < NUM_TEST; t++)
  {
	  update_knn_cluster_0(Input_1, Data_in0, knn_out1, knn_out0);
	  update_knn_cluster_1(Data_in0, Data_in1, knn_out2, knn_out1);
	  update_knn_cluster_2(Data_in1, Data_in2, knn_out3, knn_out2);
	  update_knn_cluster_3(Data_in2, Data_in3, knn_out4, knn_out3);
	  update_knn_cluster_4(Data_in3, Data_in4, knn_out5, knn_out4);
	  update_knn_cluster_5(Data_in4, Data_in5, knn_out6, knn_out5);
	  update_knn_cluster_6(Data_in5, Data_in6, knn_out7, knn_out6);
	  update_knn_cluster_7(Data_in6, Data_in7, knn_out8, knn_out7);
	  update_knn_cluster_8(Data_in7, Data_in8, knn_out9, knn_out8);
	  update_knn_cluster_9(Data_in8, Data_in9, knn_out10, knn_out9);
	  update_knn_cluster_10(Data_in9, Data_in10, knn_out11, knn_out10);
	  update_knn_cluster_11(Data_in10, Data_in11, knn_out12, knn_out11);
	  update_knn_cluster_12(Data_in11, Data_in12, knn_out13, knn_out12);
	  update_knn_cluster_13(Data_in12, Data_in13, knn_out14, knn_out13);
	  update_knn_cluster_14(Data_in13, Data_in14, knn_out15, knn_out14);
	  update_knn_cluster_15(Data_in14, Data_in15, knn_out16, knn_out15);
	  update_knn_cluster_16(Data_in15, Data_in16, knn_out17, knn_out16);
	  update_knn_cluster_17(Data_in16, Data_in17, knn_out18, knn_out17);
	  update_knn_cluster_18(Data_in17, Data_in18, knn_out19, knn_out18);
	  update_knn_cluster_19(Data_in18, knn_out19);

	  update_knn_cluster_19(Data_in18, knn_out19);
	  update_knn_cluster_18(Data_in17, Data_in18, knn_out19, knn_out18);
	  update_knn_cluster_17(Data_in16, Data_in17, knn_out18, knn_out17);
	  update_knn_cluster_16(Data_in15, Data_in16, knn_out17, knn_out16);
	  update_knn_cluster_15(Data_in14, Data_in15, knn_out16, knn_out15);
	  update_knn_cluster_14(Data_in13, Data_in14, knn_out15, knn_out14);
	  update_knn_cluster_13(Data_in12, Data_in13, knn_out14, knn_out13);
	  update_knn_cluster_12(Data_in11, Data_in12, knn_out13, knn_out12);
	  update_knn_cluster_11(Data_in10, Data_in11, knn_out12, knn_out11);
	  update_knn_cluster_10(Data_in9, Data_in10, knn_out11, knn_out10);
	  update_knn_cluster_9(Data_in8, Data_in9, knn_out10, knn_out9);
	  update_knn_cluster_8(Data_in7, Data_in8, knn_out9, knn_out8);
	  update_knn_cluster_7(Data_in6, Data_in7, knn_out8, knn_out7);
	  update_knn_cluster_6(Data_in5, Data_in6, knn_out7, knn_out6);
	  update_knn_cluster_5(Data_in4, Data_in5, knn_out6, knn_out5);
	  update_knn_cluster_4(Data_in3, Data_in4, knn_out5, knn_out4);
	  update_knn_cluster_3(Data_in2, Data_in3, knn_out4, knn_out3);
	  update_knn_cluster_2(Data_in1, Data_in2, knn_out3, knn_out2);
	  update_knn_cluster_1(Data_in0, Data_in1, knn_out2, knn_out1);
	  update_knn_cluster_0(Input_1, Data_in0, knn_out1, knn_out0);

	  knn_vote_cluster0(knn_out0, knn_vote0);
	  knn_vote_cluster1(knn_vote0, Output_1);
  }
  return;
}

/*
 * Monolithic case
 */

// Given the test instance and a (new) training instance, this
// function maintains/updates an array of K minimum
// distances per training set.
void update_knn( WholeDigitType test_inst, WholeDigitType train_inst, int min_distances[K_CONST] )
{
  #pragma HLS inline
#pragma HLS array_partition variable=min_distances complete dim=0


  // Compute the difference using XOR
  WholeDigitType diff = test_inst ^ train_inst;

  int dist = 0;

  dist = popcount(diff);

  int max_dist = 0;
  int max_dist_id = 0;
  int k = 0;

  // Find the max distance
  FIND_MAX_DIST: for ( int k = 0; k < K_CONST; ++k )
  {
    if ( min_distances[k] > max_dist )
    {
      max_dist = min_distances[k];
      max_dist_id = k;
    }
  }

  // Replace the entry with the max distance
  if ( dist < max_dist )
    min_distances[max_dist_id] = dist;

  return;
}

// Given 10xK minimum distance values, this function
// finds the actual K nearest neighbors and determines the
// final output based on the most common int represented by
// these nearest neighbors (i.e., a vote among KNNs).
LabelType knn_vote( int knn_set[PAR_FACTOR * K_CONST] )
{
  #pragma HLS inline

  // local buffers

  // final K nearest neighbors
  int min_distance_list[K_CONST];
  #pragma HLS array_partition variable=min_distance_list complete dim=0
  // labels for the K nearest neighbors
  int label_list[K_CONST];
  #pragma HLS array_partition variable=label_list complete dim=0
  // voting boxes
  int vote_list[10];
  #pragma HLS array_partition variable=vote_list complete dim=0

  int pos = 1000;

  // initialize
  INIT_1: for (int i = 0;i < K_CONST; i ++ )
  {
    #pragma HLS unroll
    min_distance_list[i] = 256;
    label_list[i] = 9;
  }

  INIT_2: for (int i = 0;i < 10; i ++ )
  {
    #pragma HLS unroll
    vote_list[i] = 0;
  }

  // go through all the lanes
  // do an insertion sort to keep a sorted neighbor list
  LANES: for (int i = 0; i < PAR_FACTOR; i ++ )
  {
    INSERTION_SORT_OUTER: for (int j = 0; j < K_CONST; j ++ )
    {
      #pragma HLS pipeline
      pos = 1000;
      INSERTION_SORT_INNER: for (int r = 0; r < K_CONST; r ++ )
      {
        #pragma HLS unroll
        pos = (
        		(knn_set[i*K_CONST+j] < min_distance_list[r])
				&&
				(pos > K_CONST)
			  ) ? r : pos;
        //printf("i=%d, j=%d, r=%d, pos=%d\n", i, j, r, pos);
      }

      INSERT: for (int r = K_CONST ;r > 0; r -- )
      {
        #pragma HLS unroll
        if(r-1 > pos)
        {
          min_distance_list[r-1] = min_distance_list[r-2];
          label_list[r-1] = label_list[r-2];
        }
        else if (r-1 == pos)
        {
          min_distance_list[r-1] = knn_set[i*K_CONST+j];
          label_list[r-1] = i / (PAR_FACTOR / 10);
        }
      }
      //printf("min_distance_list[%d]=%d, min_distance_list[%d]=%d, min_distance_list[%d]=%d\n",0,
    	//	  min_distance_list[0],
		//	  1,
		//	  min_distance_list[1],
		//	  2,
		//	  min_distance_list[2]);
     // printf("label_list[%d]=%d, label_list[%d]=%d, label_list[%d]=%d\n",
    		//  0,
			//  label_list[0],
		//	  1,
		//	  label_list[1],
		//	  2,
		//	  label_list[2]);

    }
  }

  // vote
  INCREMENT: for (int i = 0;i < K_CONST; i ++ )
  {
    #pragma HLS pipeline
    vote_list[label_list[i]] += 1;
  }

  LabelType max_vote;
  max_vote = 0;

  // find the maximum value
  VOTE: for (int i = 0;i < 10; i ++ )
  {
    #pragma HLS unroll
    if(vote_list[i] >= vote_list[max_vote])
    {
      max_vote = i;
    }
  }

  return max_vote;

}

// top-level hardware function
// since AXIDMA_SIMPLE interface does not support arrays with size more than 16384 on interface
// we call this function twice to transfer data
void DigitRec_mono(hls::stream<ap_uint<128> > & Input_1, hls::stream<ap_uint<128> > & Output_1)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
  // This array stores K minimum distances per training set
  int knn_set[PAR_FACTOR * K_CONST];
  #pragma HLS array_partition variable=knn_set complete dim=0

  static WholeDigitType training_set [NUM_TRAINING];
  // to be used in a pragma
  const int unroll_factor = PAR_FACTOR;
  #pragma HLS array_partition variable=training_set block factor=unroll_factor dim=0

  static WholeDigitType test_set     [NUM_TEST];
  static LabelType results           [NUM_TEST];

  ap_uint<32> run = 0;
  ap_uint<32> output_result[NUM_TEST / 4];


    // copy the training set for the first time
    for (int i = 0; i < NUM_TRAINING; i ++ ){
      #pragma HLS pipeline
    	training_set[i].range(255, 128) =Input_1.read();
    	training_set[i].range(127, 0) =Input_1.read();
    }

  for (int i = 0; i < NUM_TEST; i ++ ){
    #pragma HLS pipeline
	  test_set[i].range(255, 128) =Input_1.read();
	  test_set[i].range(127, 0) =Input_1.read();
  }

  // loop through test set
  TEST_LOOP: for (int t = 0; t < NUM_TEST; ++t)
  {
    // fetch one instance
    WholeDigitType test_instance = test_set[t];

    // Initialize the knn set
    SET_KNN_SET: for ( int i = 0; i < K_CONST * PAR_FACTOR ; ++i )
    {
      #pragma HLS unroll
      // Note that the max distance is 256
      knn_set[i] = 256;
    }

    TRAINING_LOOP : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
    {
      #pragma HLS pipeline
      LANES : for ( int j = 0; j < PAR_FACTOR; j++ )
      {
        #pragma HLS unroll
        // Read a new instance from the training set
        WholeDigitType training_instance = training_set[j * NUM_TRAINING / PAR_FACTOR + i];

        // Update the KNN set
        update_knn( test_instance, training_instance, &knn_set[j * K_CONST] );
      }
    }


    // Compute the final output
    LabelType max_vote = knn_vote(knn_set);
    results[t] = max_vote;

  }

  // copy the results out
  Output_1.write(2001);
  for (int i = 0; i < NUM_TEST; i ++ )
  {
	bit128 out_tmp = 0;
	out_tmp(7,0)=results[i];
	out_tmp(127,8) = 0;
    #pragma HLS pipeline
    Output_1.write(out_tmp);
  }

}


void knn_vote_small1( int knn_set[2 * K_CONST],
		                  int min_distance_list[K_CONST],
						  int label_list[K_CONST],
						  LabelType label_in)
{
  #pragma HLS inline

  // final K nearest neighbors
  #pragma HLS array_partition variable=min_distance_list complete dim=0
  // labels for the K nearest neighbors
  #pragma HLS array_partition variable=label_list complete dim=0

  // voting boxes
  int vote_list[10];
  #pragma HLS array_partition variable=vote_list complete dim=0

  int pos = 1000;

  INIT_2: for (int i = 0;i < 10; i ++ )
  {
    #pragma HLS unroll
    vote_list[i] = 0;
  }

  // go through all the lanes
  // do an insertion sort to keep a sorted neighbor list
  LANES: for (int i = 0; i < 2; i ++ )
  {
    INSERTION_SORT_OUTER: for (int j = 0; j < K_CONST; j ++ )
    {
      #pragma HLS pipeline
      pos = 1000;
      INSERTION_SORT_INNER: for (int r = 0; r < K_CONST; r ++ )
      {
        #pragma HLS unroll
        pos = (
        		(knn_set[i*K_CONST+j] < min_distance_list[r])
				&&
				(pos > K_CONST)
			  ) ? r : pos;
        //printf("i=%d, j=%d, r=%d, pos=%d\n", i, j, r, pos);
      }

      INSERT: for (int r = K_CONST ;r > 0; r -- )
      {
        #pragma HLS unroll
        if(r-1 > pos)
        {
          min_distance_list[r-1] = min_distance_list[r-2];
          label_list[r-1] = label_list[r-2];
        }
        else if (r-1 == pos)
        {
          min_distance_list[r-1] = knn_set[i*K_CONST+j];
          label_list[r-1] = label_in;
        }
      }
      printf("min_distance_list[%d]=%d, min_distance_list[%d]=%d, min_distance_list[%d]=%d\n",
    		  0,
    		  min_distance_list[0],
			  1,
			  min_distance_list[1],
			  2,
			  min_distance_list[2]);
      printf("label_list[%d]=%d, label_list[%d]=%d, label_list[%d]=%d\n",
    		  0,
			  label_list[0],
			  1,
			  label_list[1],
			  2,
			  label_list[2]);

    }
  }
}



void knn_vote_small( int knn_set[2 * K_CONST],
		                  int min_distance_list[K_CONST],
						  int label_list[K_CONST],
						  LabelType label_in)
{
  #pragma HLS inline
#pragma HLS array_partition variable=knn_set complete dim=0
  // final K nearest neighbors
  #pragma HLS array_partition variable=min_distance_list complete dim=0
  // labels for the K nearest neighbors
  #pragma HLS array_partition variable=label_list complete dim=0


  int pos = 1000;



  // go through all the lanes
  // do an insertion sort to keep a sorted neighbor list
  LANES: for (int i = 0; i < 2; i ++ )
  {
    INSERTION_SORT_OUTER: for (int j = 0; j < K_CONST; j ++ )
    {
      #pragma HLS pipeline
      pos = 1000;
      INSERTION_SORT_INNER: for (int r = 0; r < K_CONST; r ++ )
      {
        #pragma HLS unroll
        pos = (
        		(knn_set[i*K_CONST+j] < min_distance_list[r])
				&&
				(pos > K_CONST)
			  ) ? r : pos;
        //printf("i=%d, j=%d, r=%d, pos=%d\n", i, j, r, pos);
      }

      INSERT: for (int r = K_CONST ;r > 0; r -- )
      {
        #pragma HLS unroll
        if(r-1 > pos)
        {
          min_distance_list[r-1] = min_distance_list[r-2];
          label_list[r-1] = label_list[r-2];
        }
        else if (r-1 == pos)
        {
          min_distance_list[r-1] = knn_set[i*K_CONST+j];
          label_list[r-1] = label_in;
        }
      }
      //printf("min_distance_list[%d]=%d, min_distance_list[%d]=%d, min_distance_list[%d]=%d\n",0,
    	//	  min_distance_list[0],
		//	  1,
		//	  min_distance_list[1],
		//	  2,
		//	  min_distance_list[2]);
     // printf("label_list[%d]=%d, label_list[%d]=%d, label_list[%d]=%d\n",
    		//  0,
			//  label_list[0],
		//	  1,
		//	  label_list[1],
		//	  2,
		//	  label_list[2]);

    }
  }
}


LabelType knn_vote_final(int label_list[K_CONST])
{
#pragma HLS array_partition variable=label_list complete dim=0
#pragma HLS inline

  int vote_list[10];
#pragma HLS array_partition variable=vote_list complete dim=0


  INIT_2: for (int i = 0;i < 10; i ++ )
  {
    #pragma HLS unroll
    vote_list[i] = 0;
  }

  // vote
  INCREMENT: for (int i = 0;i < K_CONST; i ++ )
  {
    #pragma HLS pipeline
    vote_list[label_list[i]] += 1;
  }

  LabelType max_vote;
  max_vote = 0;

  // find the maximum value
  VOTE: for (int i = 0;i < 10; i ++ )
  {
    #pragma HLS unroll
    if(vote_list[i] >= vote_list[max_vote])
    {
      max_vote = i;
    }
  }

  return max_vote;

}



#define PAR_FACTOR_NEW 20

#define NUM1 1
void update_knn1(hls::stream<ap_uint<32> > & Input_1,
		hls::stream<ap_uint<32> > & Output_1)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1

static WholeDigitType training_set [NUM_TRAINING / PAR_FACTOR_NEW];
#pragma HLS array_partition variable=training_set block factor=2 dim=0

static WholeDigitType test_instance;


static int knn_set[K_CONST*2];
#pragma HLS array_partition variable=knn_set complete dim=0

WholeDigitType data_temp;
static int index = 0;

  if (index == 0)
  {
	  //Store the local training set
	  STORE_LOCAL: for(int i = 0; i < NUM_TRAINING / PAR_FACTOR_NEW; i++)
	  {
#pragma HLS pipeline
		training_set[i].range(255, 224) =Input_1.read();
		training_set[i].range(223, 192) =Input_1.read();
		training_set[i].range(191, 160) =Input_1.read();
		training_set[i].range(159, 128) =Input_1.read();
		training_set[i].range(127,  96) =Input_1.read();
		training_set[i].range(95,   64) =Input_1.read();
		training_set[i].range(63,   32) =Input_1.read();
		training_set[i].range(31,    0) =Input_1.read();
	  }

	  //Transit the training sets for other pages
	  TRANSFER_LOOP: for(int i = 0; i < NUM_TRAINING / PAR_FACTOR_NEW * (PAR_FACTOR_NEW - NUM1); i++)
	  {
#pragma HLS pipeline
			data_temp.range(255, 224) =Input_1.read();
			data_temp.range(223, 192) =Input_1.read();
			data_temp.range(191, 160) =Input_1.read();
			data_temp.range(159, 128) =Input_1.read();
			data_temp.range(127,  96) =Input_1.read();
			data_temp.range(95,   64) =Input_1.read();
			data_temp.range(63,   32) =Input_1.read();
			data_temp.range(31,    0) =Input_1.read();
			Output_1.write(data_temp.range(255, 224));
			Output_1.write(data_temp.range(223, 192));
			Output_1.write(data_temp.range(191, 160));
			Output_1.write(data_temp.range(159, 128));
			Output_1.write(data_temp.range(127,  96));
			Output_1.write(data_temp.range(95,   64));
			Output_1.write(data_temp.range(63,   32));
			Output_1.write(data_temp.range(31,    0));
	  }

	  index = 1;
  }

  index++;
#ifdef DEBUG
  printf("test set %d\n", index-2);
#endif
  test_instance(255, 224) = Input_1.read();
  test_instance(223, 192) = Input_1.read();
  test_instance(191, 160) = Input_1.read();
  test_instance(159, 128) = Input_1.read();
  test_instance(127,  96) = Input_1.read();
  test_instance(95,   64) = Input_1.read();
  test_instance(63,   32) = Input_1.read();
  test_instance(31,    0) = Input_1.read();
  Output_1.write(test_instance(255, 224));
  Output_1.write(test_instance(223, 192));
  Output_1.write(test_instance(191, 160));
  Output_1.write(test_instance(159, 128));
  Output_1.write(test_instance(127,  96));
  Output_1.write(test_instance(95,   64));
  Output_1.write(test_instance(63,   32));
  Output_1.write(test_instance(31,    0));

  int min_distance_list[K_CONST];
#pragma HLS array_partition variable=min_distance_list complete dim=0

  int label_list[K_CONST];
#pragma HLS array_partition variable=label_list complete dim=0



  for(int i=0; i<K_CONST; i++)
  {
#pragma HLS unroll
	  min_distance_list[i] = 256;
	  label_list[i] = 0;
  }

  // Initialize the knn set
   SET_KNN_SET: for ( int i = 0; i < K_CONST * 2 ; ++i )
   {
#pragma HLS unroll
     // Note that the max distance is 256
     knn_set[i] = 256;
   }

   TRAINING_LOOP : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
   {
       #pragma HLS pipeline
       LANES : for ( int j = 0; j < 2; j++ )
       {
         #pragma HLS unroll
         WholeDigitType training_instance = training_set[j * NUM_TRAINING / PAR_FACTOR + i];
         update_knn( test_instance, training_instance, &knn_set[j * K_CONST] );
       }
   }

#ifdef DEBUG
   printf("knn_update1");
   for(int i=0; i<6; i++){
   	printf("knn_set[%d]=%d,", i, knn_set[i]);
   }
   printf("\n");
#endif

   //update min_distance_list and label_list according to the new knn_set
   LabelType label_in = 0;
   knn_vote_small(knn_set, min_distance_list, label_list, label_in);

   bit128 output_tmp1, output_tmp2;

   for(int i=0; i<K_CONST; i++)
   {
#pragma HLS unroll
	   output_tmp1(i*32+31, i*32) = min_distance_list[i];
	   output_tmp2(i*32+31, i*32) = label_list[i];
   }

   Output_1.write(output_tmp1(127,96));
   Output_1.write(output_tmp1(95, 64));
   Output_1.write(output_tmp1(63, 32));
   Output_1.write(output_tmp1(31,  0));
   Output_1.write(output_tmp2(127,96));
   Output_1.write(output_tmp2(95, 64));
   Output_1.write(output_tmp2(63, 32));
   Output_1.write(output_tmp2(31,  0));

  return;
}


#define NUM2 2
void update_knn2(hls::stream<ap_uint<32> > & Input_1, hls::stream<ap_uint<32> > & Output_1)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1

static WholeDigitType training_set [NUM_TRAINING / PAR_FACTOR_NEW];
#pragma HLS array_partition variable=training_set block factor=2 dim=0

static WholeDigitType test_instance;


static int knn_set[K_CONST*2];
#pragma HLS array_partition variable=knn_set complete dim=0

WholeDigitType data_temp;
static int index = 0;



  if (index == 0)
  {
	  //Store the local training set
	  STORE_LOCAL: for(int i = 0; i < NUM_TRAINING / PAR_FACTOR_NEW; i++)
	  {
#pragma HLS pipeline
			training_set[i].range(255, 224) =Input_1.read();
			training_set[i].range(223, 192) =Input_1.read();
			training_set[i].range(191, 160) =Input_1.read();
			training_set[i].range(159, 128) =Input_1.read();
			training_set[i].range(127,  96) =Input_1.read();
			training_set[i].range(95,   64) =Input_1.read();
			training_set[i].range(63,   32) =Input_1.read();
			training_set[i].range(31,    0) =Input_1.read();
	  }

	  //Transit the training sets for other pages
	  TRANSFER_LOOP: for(int i = 0; i < NUM_TRAINING / PAR_FACTOR_NEW * (PAR_FACTOR_NEW - NUM2); i++)
	  {
#pragma HLS pipeline
			data_temp.range(255, 224) =Input_1.read();
			data_temp.range(223, 192) =Input_1.read();
			data_temp.range(191, 160) =Input_1.read();
			data_temp.range(159, 128) =Input_1.read();
			data_temp.range(127,  96) =Input_1.read();
			data_temp.range(95,   64) =Input_1.read();
			data_temp.range(63,   32) =Input_1.read();
			data_temp.range(31,    0) =Input_1.read();
			Output_1.write(data_temp.range(255, 224));
			Output_1.write(data_temp.range(223, 192));
			Output_1.write(data_temp.range(191, 160));
			Output_1.write(data_temp.range(159, 128));
			Output_1.write(data_temp.range(127,  96));
			Output_1.write(data_temp.range(95,   64));
			Output_1.write(data_temp.range(63,   32));
			Output_1.write(data_temp.range(31,    0));
	  }

	  index = 1;
  }


  test_instance(255, 224) = Input_1.read();
  test_instance(223, 192) = Input_1.read();
  test_instance(191, 160) = Input_1.read();
  test_instance(159, 128) = Input_1.read();
  test_instance(127,  96) = Input_1.read();
  test_instance(95,   64) = Input_1.read();
  test_instance(63,   32) = Input_1.read();
  test_instance(31,    0) = Input_1.read();
  Output_1.write(test_instance(255, 224));
  Output_1.write(test_instance(223, 192));
  Output_1.write(test_instance(191, 160));
  Output_1.write(test_instance(159, 128));
  Output_1.write(test_instance(127,  96));
  Output_1.write(test_instance(95,   64));
  Output_1.write(test_instance(63,   32));
  Output_1.write(test_instance(31,    0));

  int min_distance_list[K_CONST];
  int label_list[K_CONST];

  bit128 input_tmp1, input_tmp2;
  input_tmp1(127,  96) = Input_1.read();
  input_tmp1(95,   64) = Input_1.read();
  input_tmp1(63,   32) = Input_1.read();
  input_tmp1(31,    0) = Input_1.read();
  input_tmp2(127,  96) = Input_1.read();
  input_tmp2(95,   64) = Input_1.read();
  input_tmp2(63,   32) = Input_1.read();
  input_tmp2(31,    0) = Input_1.read();

  for(int i=0; i<K_CONST; i++)
  {
#pragma HLS unroll
	  min_distance_list[i] = (int) input_tmp1(i*32+31, i*32);
	  label_list[i] = (int) input_tmp2(i*32+31, i*32);
  }

  // Initialize the knn set
   SET_KNN_SET: for ( int i = 0; i < K_CONST * 2 ; ++i )
   {
#pragma HLS unroll
     // Note that the max distance is 256
     knn_set[i] = 256;
   }

   TRAINING_LOOP : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
   {
       #pragma HLS pipeline
       LANES : for ( int j = 0; j < 2; j++ )
       {
         #pragma HLS unroll
         WholeDigitType training_instance = training_set[j * NUM_TRAINING / PAR_FACTOR + i];
         update_knn( test_instance, training_instance, &knn_set[j * K_CONST] );
       }
   }

#ifdef DEBUG
   printf("knn_update3");
   for(int i=0; i<6; i++){
   	printf("knn_set[%d]=%d,", i, knn_set[i]);
   }
   printf("\n");
#endif

   //update min_distance_list and label_list according to the new knn_set
   LabelType label_in = 0;
   knn_vote_small(knn_set, min_distance_list, label_list, label_in);

   bit128 output_tmp1, output_tmp2;

   for(int i=0; i<K_CONST; i++)
   {
#pragma HLS unroll
	   output_tmp1(i*32+31, i*32) = min_distance_list[i];
	   output_tmp2(i*32+31, i*32) = label_list[i];
   }


   Output_1.write(output_tmp1(127,96));
   Output_1.write(output_tmp1(95, 64));
   Output_1.write(output_tmp1(63, 32));
   Output_1.write(output_tmp1(31,  0));
   Output_1.write(output_tmp2(127,96));
   Output_1.write(output_tmp2(95, 64));
   Output_1.write(output_tmp2(63, 32));
   Output_1.write(output_tmp2(31,  0));
  return;
}


#define NUM3 3
void update_knn3(hls::stream<ap_uint<32> > & Input_1, hls::stream<ap_uint<32> > & Output_1)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1

static WholeDigitType training_set [NUM_TRAINING / PAR_FACTOR_NEW];
#pragma HLS array_partition variable=training_set block factor=2 dim=0

static WholeDigitType test_instance;


static int knn_set[K_CONST*2];
#pragma HLS array_partition variable=knn_set complete dim=0

WholeDigitType data_temp;
static int index = 0;



  if (index == 0)
  {
	  //Store the local training set
	  STORE_LOCAL: for(int i = 0; i < NUM_TRAINING / PAR_FACTOR_NEW; i++)
	  {
#pragma HLS pipeline
			training_set[i].range(255, 224) =Input_1.read();
			training_set[i].range(223, 192) =Input_1.read();
			training_set[i].range(191, 160) =Input_1.read();
			training_set[i].range(159, 128) =Input_1.read();
			training_set[i].range(127,  96) =Input_1.read();
			training_set[i].range(95,   64) =Input_1.read();
			training_set[i].range(63,   32) =Input_1.read();
			training_set[i].range(31,    0) =Input_1.read();
	  }

	  //Transit the training sets for other pages
	  TRANSFER_LOOP: for(int i = 0; i < NUM_TRAINING / PAR_FACTOR_NEW * (PAR_FACTOR_NEW - NUM3); i++)
	  {
#pragma HLS pipeline
			data_temp.range(255, 224) =Input_1.read();
			data_temp.range(223, 192) =Input_1.read();
			data_temp.range(191, 160) =Input_1.read();
			data_temp.range(159, 128) =Input_1.read();
			data_temp.range(127,  96) =Input_1.read();
			data_temp.range(95,   64) =Input_1.read();
			data_temp.range(63,   32) =Input_1.read();
			data_temp.range(31,    0) =Input_1.read();
			Output_1.write(data_temp.range(255, 224));
			Output_1.write(data_temp.range(223, 192));
			Output_1.write(data_temp.range(191, 160));
			Output_1.write(data_temp.range(159, 128));
			Output_1.write(data_temp.range(127,  96));
			Output_1.write(data_temp.range(95,   64));
			Output_1.write(data_temp.range(63,   32));
			Output_1.write(data_temp.range(31,    0));
	  }

	  index = 1;
  }


  test_instance(255, 224) = Input_1.read();
  test_instance(223, 192) = Input_1.read();
  test_instance(191, 160) = Input_1.read();
  test_instance(159, 128) = Input_1.read();
  test_instance(127,  96) = Input_1.read();
  test_instance(95,   64) = Input_1.read();
  test_instance(63,   32) = Input_1.read();
  test_instance(31,    0) = Input_1.read();
  Output_1.write(test_instance(255, 224));
  Output_1.write(test_instance(223, 192));
  Output_1.write(test_instance(191, 160));
  Output_1.write(test_instance(159, 128));
  Output_1.write(test_instance(127,  96));
  Output_1.write(test_instance(95,   64));
  Output_1.write(test_instance(63,   32));
  Output_1.write(test_instance(31,    0));

  int min_distance_list[K_CONST];
  int label_list[K_CONST];

  bit128 input_tmp1, input_tmp2;
  input_tmp1(127,  96) = Input_1.read();
  input_tmp1(95,   64) = Input_1.read();
  input_tmp1(63,   32) = Input_1.read();
  input_tmp1(31,    0) = Input_1.read();
  input_tmp2(127,  96) = Input_1.read();
  input_tmp2(95,   64) = Input_1.read();
  input_tmp2(63,   32) = Input_1.read();
  input_tmp2(31,    0) = Input_1.read();

  for(int i=0; i<K_CONST; i++)
  {
#pragma HLS unroll
	  min_distance_list[i] = (int) input_tmp1(i*32+31, i*32);
	  label_list[i] = (int) input_tmp2(i*32+31, i*32);
  }

  // Initialize the knn set
   SET_KNN_SET: for ( int i = 0; i < K_CONST * 2 ; ++i )
   {
#pragma HLS unroll
     // Note that the max distance is 256
     knn_set[i] = 256;
   }

   TRAINING_LOOP : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
   {
       #pragma HLS pipeline
       LANES : for ( int j = 0; j < 2; j++ )
       {
         #pragma HLS unroll
         WholeDigitType training_instance = training_set[j * NUM_TRAINING / PAR_FACTOR + i];
         update_knn( test_instance, training_instance, &knn_set[j * K_CONST] );
       }
   }

#ifdef DEBUG
   printf("knn_update3");
   for(int i=0; i<6; i++){
   	printf("knn_set[%d]=%d,", i, knn_set[i]);
   }
   printf("\n");
#endif

   //update min_distance_list and label_list according to the new knn_set
   LabelType label_in = 1;
   knn_vote_small(knn_set, min_distance_list, label_list, label_in);

   bit128 output_tmp1, output_tmp2;

   for(int i=0; i<K_CONST; i++)
   {
#pragma HLS unroll
	   output_tmp1(i*32+31, i*32) = min_distance_list[i];
	   output_tmp2(i*32+31, i*32) = label_list[i];
   }


   Output_1.write(output_tmp1(127,96));
   Output_1.write(output_tmp1(95, 64));
   Output_1.write(output_tmp1(63, 32));
   Output_1.write(output_tmp1(31,  0));
   Output_1.write(output_tmp2(127,96));
   Output_1.write(output_tmp2(95, 64));
   Output_1.write(output_tmp2(63, 32));
   Output_1.write(output_tmp2(31,  0));
  return;
}


#define NUM4 4
void update_knn4(hls::stream<ap_uint<32> > & Input_1, hls::stream<ap_uint<32> > & Output_1)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1

static WholeDigitType training_set [NUM_TRAINING / PAR_FACTOR_NEW];
#pragma HLS array_partition variable=training_set block factor=2 dim=0

static WholeDigitType test_instance;


static int knn_set[K_CONST*2];
#pragma HLS array_partition variable=knn_set complete dim=0

WholeDigitType data_temp;
static int index = 0;



  if (index == 0)
  {
	  //Store the local training set
	  STORE_LOCAL: for(int i = 0; i < NUM_TRAINING / PAR_FACTOR_NEW; i++)
	  {
#pragma HLS pipeline
			training_set[i].range(255, 224) =Input_1.read();
			training_set[i].range(223, 192) =Input_1.read();
			training_set[i].range(191, 160) =Input_1.read();
			training_set[i].range(159, 128) =Input_1.read();
			training_set[i].range(127,  96) =Input_1.read();
			training_set[i].range(95,   64) =Input_1.read();
			training_set[i].range(63,   32) =Input_1.read();
			training_set[i].range(31,    0) =Input_1.read();
	  }

	  //Transit the training sets for other pages
	  TRANSFER_LOOP: for(int i = 0; i < NUM_TRAINING / PAR_FACTOR_NEW * (PAR_FACTOR_NEW - NUM4); i++)
	  {
#pragma HLS pipeline
			data_temp.range(255, 224) =Input_1.read();
			data_temp.range(223, 192) =Input_1.read();
			data_temp.range(191, 160) =Input_1.read();
			data_temp.range(159, 128) =Input_1.read();
			data_temp.range(127,  96) =Input_1.read();
			data_temp.range(95,   64) =Input_1.read();
			data_temp.range(63,   32) =Input_1.read();
			data_temp.range(31,    0) =Input_1.read();
			Output_1.write(data_temp.range(255, 224));
			Output_1.write(data_temp.range(223, 192));
			Output_1.write(data_temp.range(191, 160));
			Output_1.write(data_temp.range(159, 128));
			Output_1.write(data_temp.range(127,  96));
			Output_1.write(data_temp.range(95,   64));
			Output_1.write(data_temp.range(63,   32));
			Output_1.write(data_temp.range(31,    0));
	  }

	  index = 1;
  }


  test_instance(255, 224) = Input_1.read();
  test_instance(223, 192) = Input_1.read();
  test_instance(191, 160) = Input_1.read();
  test_instance(159, 128) = Input_1.read();
  test_instance(127,  96) = Input_1.read();
  test_instance(95,   64) = Input_1.read();
  test_instance(63,   32) = Input_1.read();
  test_instance(31,    0) = Input_1.read();
  Output_1.write(test_instance(255, 224));
  Output_1.write(test_instance(223, 192));
  Output_1.write(test_instance(191, 160));
  Output_1.write(test_instance(159, 128));
  Output_1.write(test_instance(127,  96));
  Output_1.write(test_instance(95,   64));
  Output_1.write(test_instance(63,   32));
  Output_1.write(test_instance(31,    0));

  int min_distance_list[K_CONST];
  int label_list[K_CONST];

  bit128 input_tmp1, input_tmp2;
  input_tmp1(127,  96) = Input_1.read();
  input_tmp1(95,   64) = Input_1.read();
  input_tmp1(63,   32) = Input_1.read();
  input_tmp1(31,    0) = Input_1.read();
  input_tmp2(127,  96) = Input_1.read();
  input_tmp2(95,   64) = Input_1.read();
  input_tmp2(63,   32) = Input_1.read();
  input_tmp2(31,    0) = Input_1.read();
  for(int i=0; i<K_CONST; i++)
  {
#pragma HLS unroll
	  min_distance_list[i] = (int) input_tmp1(i*32+31, i*32);
	  label_list[i] = (int) input_tmp2(i*32+31, i*32);
  }

  // Initialize the knn set
   SET_KNN_SET: for ( int i = 0; i < K_CONST * 2 ; ++i )
   {
#pragma HLS unroll
     // Note that the max distance is 256
     knn_set[i] = 256;
   }

   TRAINING_LOOP : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
   {
       #pragma HLS pipeline
       LANES : for ( int j = 0; j < 2; j++ )
       {
         #pragma HLS unroll
         WholeDigitType training_instance = training_set[j * NUM_TRAINING / PAR_FACTOR + i];
         update_knn( test_instance, training_instance, &knn_set[j * K_CONST] );
       }
   }

#ifdef DEBUG
   printf("knn_update4");
   for(int i=0; i<6; i++){
   	printf("knn_set[%d]=%d,", i, knn_set[i]);
   }
   printf("\n");
#endif

   //update min_distance_list and label_list according to the new knn_set
   LabelType label_in = 1;
   knn_vote_small(knn_set, min_distance_list, label_list, label_in);

   bit128 output_tmp1, output_tmp2;

   for(int i=0; i<K_CONST; i++)
   {
#pragma HLS unroll
	   output_tmp1(i*32+31, i*32) = min_distance_list[i];
	   output_tmp2(i*32+31, i*32) = label_list[i];
   }


   Output_1.write(output_tmp1(127,96));
   Output_1.write(output_tmp1(95, 64));
   Output_1.write(output_tmp1(63, 32));
   Output_1.write(output_tmp1(31,  0));
   Output_1.write(output_tmp2(127,96));
   Output_1.write(output_tmp2(95, 64));
   Output_1.write(output_tmp2(63, 32));
   Output_1.write(output_tmp2(31,  0));
  return;
}


#define NUM5 5
void update_knn5(hls::stream<ap_uint<32> > & Input_1, hls::stream<ap_uint<32> > & Output_1)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1

static WholeDigitType training_set [NUM_TRAINING / PAR_FACTOR_NEW];
#pragma HLS array_partition variable=training_set block factor=2 dim=0

static WholeDigitType test_instance;


static int knn_set[K_CONST*2];
#pragma HLS array_partition variable=knn_set complete dim=0

WholeDigitType data_temp;
static int index = 0;



  if (index == 0)
  {
	  //Store the local training set
	  STORE_LOCAL: for(int i = 0; i < NUM_TRAINING / PAR_FACTOR_NEW; i++)
	  {
#pragma HLS pipeline
			training_set[i].range(255, 224) =Input_1.read();
			training_set[i].range(223, 192) =Input_1.read();
			training_set[i].range(191, 160) =Input_1.read();
			training_set[i].range(159, 128) =Input_1.read();
			training_set[i].range(127,  96) =Input_1.read();
			training_set[i].range(95,   64) =Input_1.read();
			training_set[i].range(63,   32) =Input_1.read();
			training_set[i].range(31,    0) =Input_1.read();
	  }

	  //Transit the training sets for other pages
	  TRANSFER_LOOP: for(int i = 0; i < NUM_TRAINING / PAR_FACTOR_NEW * (PAR_FACTOR_NEW - NUM5); i++)
	  {
#pragma HLS pipeline
			data_temp.range(255, 224) =Input_1.read();
			data_temp.range(223, 192) =Input_1.read();
			data_temp.range(191, 160) =Input_1.read();
			data_temp.range(159, 128) =Input_1.read();
			data_temp.range(127,  96) =Input_1.read();
			data_temp.range(95,   64) =Input_1.read();
			data_temp.range(63,   32) =Input_1.read();
			data_temp.range(31,    0) =Input_1.read();
			Output_1.write(data_temp.range(255, 224));
			Output_1.write(data_temp.range(223, 192));
			Output_1.write(data_temp.range(191, 160));
			Output_1.write(data_temp.range(159, 128));
			Output_1.write(data_temp.range(127,  96));
			Output_1.write(data_temp.range(95,   64));
			Output_1.write(data_temp.range(63,   32));
			Output_1.write(data_temp.range(31,    0));
	  }

	  index = 1;
  }


  test_instance(255, 224) = Input_1.read();
  test_instance(223, 192) = Input_1.read();
  test_instance(191, 160) = Input_1.read();
  test_instance(159, 128) = Input_1.read();
  test_instance(127,  96) = Input_1.read();
  test_instance(95,   64) = Input_1.read();
  test_instance(63,   32) = Input_1.read();
  test_instance(31,    0) = Input_1.read();
  Output_1.write(test_instance(255, 224));
  Output_1.write(test_instance(223, 192));
  Output_1.write(test_instance(191, 160));
  Output_1.write(test_instance(159, 128));
  Output_1.write(test_instance(127,  96));
  Output_1.write(test_instance(95,   64));
  Output_1.write(test_instance(63,   32));
  Output_1.write(test_instance(31,    0));

  int min_distance_list[K_CONST];
  int label_list[K_CONST];

  bit128 input_tmp1, input_tmp2;
  input_tmp1(127,  96) = Input_1.read();
  input_tmp1(95,   64) = Input_1.read();
  input_tmp1(63,   32) = Input_1.read();
  input_tmp1(31,    0) = Input_1.read();
  input_tmp2(127,  96) = Input_1.read();
  input_tmp2(95,   64) = Input_1.read();
  input_tmp2(63,   32) = Input_1.read();
  input_tmp2(31,    0) = Input_1.read();

  for(int i=0; i<K_CONST; i++)
  {
#pragma HLS unroll
	  min_distance_list[i] = (int) input_tmp1(i*32+31, i*32);
	  label_list[i] = (int) input_tmp2(i*32+31, i*32);
  }

  // Initialize the knn set
   SET_KNN_SET: for ( int i = 0; i < K_CONST * 2 ; ++i )
   {
#pragma HLS unroll
     // Note that the max distance is 256
     knn_set[i] = 256;
   }

   TRAINING_LOOP : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
   {
       #pragma HLS pipeline
       LANES : for ( int j = 0; j < 2; j++ )
       {
         #pragma HLS unroll
         WholeDigitType training_instance = training_set[j * NUM_TRAINING / PAR_FACTOR + i];
         update_knn( test_instance, training_instance, &knn_set[j * K_CONST] );
       }
   }

#ifdef DEBUG
   printf("knn_update5");
   for(int i=0; i<6; i++){
   	printf("knn_set[%d]=%d,", i, knn_set[i]);
   }
   printf("\n");
#endif

   //update min_distance_list and label_list according to the new knn_set
   LabelType label_in = 2;
   knn_vote_small(knn_set, min_distance_list, label_list, label_in);

   bit128 output_tmp1, output_tmp2;

   for(int i=0; i<K_CONST; i++)
   {
#pragma HLS unroll
	   output_tmp1(i*32+31, i*32) = min_distance_list[i];
	   output_tmp2(i*32+31, i*32) = label_list[i];
   }


   Output_1.write(output_tmp1(127,96));
   Output_1.write(output_tmp1(95, 64));
   Output_1.write(output_tmp1(63, 32));
   Output_1.write(output_tmp1(31,  0));
   Output_1.write(output_tmp2(127,96));
   Output_1.write(output_tmp2(95, 64));
   Output_1.write(output_tmp2(63, 32));
   Output_1.write(output_tmp2(31,  0));
  return;
}


#define NUM6 6
void update_knn6(hls::stream<ap_uint<32> > & Input_1, hls::stream<ap_uint<32> > & Output_1)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1

static WholeDigitType training_set [NUM_TRAINING / PAR_FACTOR_NEW];
#pragma HLS array_partition variable=training_set block factor=2 dim=0

static WholeDigitType test_instance;


static int knn_set[K_CONST*2];
#pragma HLS array_partition variable=knn_set complete dim=0

WholeDigitType data_temp;
static int index = 0;



  if (index == 0)
  {
	  //Store the local training set
	  STORE_LOCAL: for(int i = 0; i < NUM_TRAINING / PAR_FACTOR_NEW; i++)
	  {
#pragma HLS pipeline
			training_set[i].range(255, 224) =Input_1.read();
			training_set[i].range(223, 192) =Input_1.read();
			training_set[i].range(191, 160) =Input_1.read();
			training_set[i].range(159, 128) =Input_1.read();
			training_set[i].range(127,  96) =Input_1.read();
			training_set[i].range(95,   64) =Input_1.read();
			training_set[i].range(63,   32) =Input_1.read();
			training_set[i].range(31,    0) =Input_1.read();
	  }

	  //Transit the training sets for other pages
	  TRANSFER_LOOP: for(int i = 0; i < NUM_TRAINING / PAR_FACTOR_NEW * (PAR_FACTOR_NEW - NUM6); i++)
	  {
#pragma HLS pipeline
			data_temp.range(255, 224) =Input_1.read();
			data_temp.range(223, 192) =Input_1.read();
			data_temp.range(191, 160) =Input_1.read();
			data_temp.range(159, 128) =Input_1.read();
			data_temp.range(127,  96) =Input_1.read();
			data_temp.range(95,   64) =Input_1.read();
			data_temp.range(63,   32) =Input_1.read();
			data_temp.range(31,    0) =Input_1.read();
			Output_1.write(data_temp.range(255, 224));
			Output_1.write(data_temp.range(223, 192));
			Output_1.write(data_temp.range(191, 160));
			Output_1.write(data_temp.range(159, 128));
			Output_1.write(data_temp.range(127,  96));
			Output_1.write(data_temp.range(95,   64));
			Output_1.write(data_temp.range(63,   32));
			Output_1.write(data_temp.range(31,    0));
	  }

	  index = 1;
  }


  test_instance(255, 224) = Input_1.read();
  test_instance(223, 192) = Input_1.read();
  test_instance(191, 160) = Input_1.read();
  test_instance(159, 128) = Input_1.read();
  test_instance(127,  96) = Input_1.read();
  test_instance(95,   64) = Input_1.read();
  test_instance(63,   32) = Input_1.read();
  test_instance(31,    0) = Input_1.read();
  Output_1.write(test_instance(255, 224));
  Output_1.write(test_instance(223, 192));
  Output_1.write(test_instance(191, 160));
  Output_1.write(test_instance(159, 128));
  Output_1.write(test_instance(127,  96));
  Output_1.write(test_instance(95,   64));
  Output_1.write(test_instance(63,   32));
  Output_1.write(test_instance(31,    0));

  int min_distance_list[K_CONST];
  int label_list[K_CONST];

  bit128 input_tmp1, input_tmp2;
  input_tmp1(127,  96) = Input_1.read();
  input_tmp1(95,   64) = Input_1.read();
  input_tmp1(63,   32) = Input_1.read();
  input_tmp1(31,    0) = Input_1.read();
  input_tmp2(127,  96) = Input_1.read();
  input_tmp2(95,   64) = Input_1.read();
  input_tmp2(63,   32) = Input_1.read();
  input_tmp2(31,    0) = Input_1.read();
  for(int i=0; i<K_CONST; i++)
  {
#pragma HLS unroll
	  min_distance_list[i] = (int) input_tmp1(i*32+31, i*32);
	  label_list[i] = (int) input_tmp2(i*32+31, i*32);
  }

  // Initialize the knn set
   SET_KNN_SET: for ( int i = 0; i < K_CONST * 2 ; ++i )
   {
#pragma HLS unroll
     // Note that the max distance is 256
     knn_set[i] = 256;
   }

   TRAINING_LOOP : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
   {
       #pragma HLS pipeline
       LANES : for ( int j = 0; j < 2; j++ )
       {
         #pragma HLS unroll
         WholeDigitType training_instance = training_set[j * NUM_TRAINING / PAR_FACTOR + i];
         update_knn( test_instance, training_instance, &knn_set[j * K_CONST] );
       }
   }

#ifdef DEBUG
   printf("knn_update6");
   for(int i=0; i<6; i++){
   	printf("knn_set[%d]=%d,", i, knn_set[i]);
   }
   printf("\n");
#endif

   //update min_distance_list and label_list according to the new knn_set
   LabelType label_in = 2;
   knn_vote_small(knn_set, min_distance_list, label_list, label_in);

   bit128 output_tmp1, output_tmp2;

   for(int i=0; i<K_CONST; i++)
   {
#pragma HLS unroll
	   output_tmp1(i*32+31, i*32) = min_distance_list[i];
	   output_tmp2(i*32+31, i*32) = label_list[i];
   }


   Output_1.write(output_tmp1(127,96));
   Output_1.write(output_tmp1(95, 64));
   Output_1.write(output_tmp1(63, 32));
   Output_1.write(output_tmp1(31,  0));
   Output_1.write(output_tmp2(127,96));
   Output_1.write(output_tmp2(95, 64));
   Output_1.write(output_tmp2(63, 32));
   Output_1.write(output_tmp2(31,  0));
  return;
}


#define NUM7 7
void update_knn7(hls::stream<ap_uint<32> > & Input_1, hls::stream<ap_uint<32> > & Output_1)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1

static WholeDigitType training_set [NUM_TRAINING / PAR_FACTOR_NEW];
#pragma HLS array_partition variable=training_set block factor=2 dim=0

static WholeDigitType test_instance;


static int knn_set[K_CONST*2];
#pragma HLS array_partition variable=knn_set complete dim=0

WholeDigitType data_temp;
static int index = 0;



  if (index == 0)
  {
	  //Store the local training set
	  STORE_LOCAL: for(int i = 0; i < NUM_TRAINING / PAR_FACTOR_NEW; i++)
	  {
#pragma HLS pipeline
			training_set[i].range(255, 224) =Input_1.read();
			training_set[i].range(223, 192) =Input_1.read();
			training_set[i].range(191, 160) =Input_1.read();
			training_set[i].range(159, 128) =Input_1.read();
			training_set[i].range(127,  96) =Input_1.read();
			training_set[i].range(95,   64) =Input_1.read();
			training_set[i].range(63,   32) =Input_1.read();
			training_set[i].range(31,    0) =Input_1.read();
	  }

	  //Transit the training sets for other pages
	  TRANSFER_LOOP: for(int i = 0; i < NUM_TRAINING / PAR_FACTOR_NEW * (PAR_FACTOR_NEW - NUM7); i++)
	  {
#pragma HLS pipeline
			data_temp.range(255, 224) =Input_1.read();
			data_temp.range(223, 192) =Input_1.read();
			data_temp.range(191, 160) =Input_1.read();
			data_temp.range(159, 128) =Input_1.read();
			data_temp.range(127,  96) =Input_1.read();
			data_temp.range(95,   64) =Input_1.read();
			data_temp.range(63,   32) =Input_1.read();
			data_temp.range(31,    0) =Input_1.read();
			Output_1.write(data_temp.range(255, 224));
			Output_1.write(data_temp.range(223, 192));
			Output_1.write(data_temp.range(191, 160));
			Output_1.write(data_temp.range(159, 128));
			Output_1.write(data_temp.range(127,  96));
			Output_1.write(data_temp.range(95,   64));
			Output_1.write(data_temp.range(63,   32));
			Output_1.write(data_temp.range(31,    0));
	  }

	  index = 1;
  }


  test_instance(255, 224) = Input_1.read();
  test_instance(223, 192) = Input_1.read();
  test_instance(191, 160) = Input_1.read();
  test_instance(159, 128) = Input_1.read();
  test_instance(127,  96) = Input_1.read();
  test_instance(95,   64) = Input_1.read();
  test_instance(63,   32) = Input_1.read();
  test_instance(31,    0) = Input_1.read();
  Output_1.write(test_instance(255, 224));
  Output_1.write(test_instance(223, 192));
  Output_1.write(test_instance(191, 160));
  Output_1.write(test_instance(159, 128));
  Output_1.write(test_instance(127,  96));
  Output_1.write(test_instance(95,   64));
  Output_1.write(test_instance(63,   32));
  Output_1.write(test_instance(31,    0));

  int min_distance_list[K_CONST];
  int label_list[K_CONST];

  bit128 input_tmp1, input_tmp2;
  input_tmp1(127,  96) = Input_1.read();
  input_tmp1(95,   64) = Input_1.read();
  input_tmp1(63,   32) = Input_1.read();
  input_tmp1(31,    0) = Input_1.read();
  input_tmp2(127,  96) = Input_1.read();
  input_tmp2(95,   64) = Input_1.read();
  input_tmp2(63,   32) = Input_1.read();
  input_tmp2(31,    0) = Input_1.read();

  for(int i=0; i<K_CONST; i++)
  {
#pragma HLS unroll
	  min_distance_list[i] = (int) input_tmp1(i*32+31, i*32);
	  label_list[i] = (int) input_tmp2(i*32+31, i*32);
  }

  // Initialize the knn set
   SET_KNN_SET: for ( int i = 0; i < K_CONST * 2 ; ++i )
   {
#pragma HLS unroll
     // Note that the max distance is 256
     knn_set[i] = 256;
   }

   TRAINING_LOOP : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
   {
       #pragma HLS pipeline
       LANES : for ( int j = 0; j < 2; j++ )
       {
         #pragma HLS unroll
         WholeDigitType training_instance = training_set[j * NUM_TRAINING / PAR_FACTOR + i];
         update_knn( test_instance, training_instance, &knn_set[j * K_CONST] );
       }
   }

#ifdef DEBUG
   printf("knn_update7");
   for(int i=0; i<6; i++){
   	printf("knn_set[%d]=%d,", i, knn_set[i]);
   }
   printf("\n");
#endif


   //update min_distance_list and label_list according to the new knn_set
   LabelType label_in = 3;
   knn_vote_small(knn_set, min_distance_list, label_list, label_in);

   bit128 output_tmp1, output_tmp2;

   for(int i=0; i<K_CONST; i++)
   {
#pragma HLS unroll
	   output_tmp1(i*32+31, i*32) = min_distance_list[i];
	   output_tmp2(i*32+31, i*32) = label_list[i];
   }


   Output_1.write(output_tmp1(127,96));
   Output_1.write(output_tmp1(95, 64));
   Output_1.write(output_tmp1(63, 32));
   Output_1.write(output_tmp1(31,  0));
   Output_1.write(output_tmp2(127,96));
   Output_1.write(output_tmp2(95, 64));
   Output_1.write(output_tmp2(63, 32));
   Output_1.write(output_tmp2(31,  0));
  return;
}


#define NUM8 8
void update_knn8(hls::stream<ap_uint<32> > & Input_1, hls::stream<ap_uint<32> > & Output_1)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1

static WholeDigitType training_set [NUM_TRAINING / PAR_FACTOR_NEW];
#pragma HLS array_partition variable=training_set block factor=2 dim=0

static WholeDigitType test_instance;


static int knn_set[K_CONST*2];
#pragma HLS array_partition variable=knn_set complete dim=0

WholeDigitType data_temp;
static int index = 0;



  if (index == 0)
  {
	  //Store the local training set
	  STORE_LOCAL: for(int i = 0; i < NUM_TRAINING / PAR_FACTOR_NEW; i++)
	  {
#pragma HLS pipeline
			training_set[i].range(255, 224) =Input_1.read();
			training_set[i].range(223, 192) =Input_1.read();
			training_set[i].range(191, 160) =Input_1.read();
			training_set[i].range(159, 128) =Input_1.read();
			training_set[i].range(127,  96) =Input_1.read();
			training_set[i].range(95,   64) =Input_1.read();
			training_set[i].range(63,   32) =Input_1.read();
			training_set[i].range(31,    0) =Input_1.read();
	  }

	  //Transit the training sets for other pages
	  TRANSFER_LOOP: for(int i = 0; i < NUM_TRAINING / PAR_FACTOR_NEW * (PAR_FACTOR_NEW - NUM8); i++)
	  {
#pragma HLS pipeline
			data_temp.range(255, 224) =Input_1.read();
			data_temp.range(223, 192) =Input_1.read();
			data_temp.range(191, 160) =Input_1.read();
			data_temp.range(159, 128) =Input_1.read();
			data_temp.range(127,  96) =Input_1.read();
			data_temp.range(95,   64) =Input_1.read();
			data_temp.range(63,   32) =Input_1.read();
			data_temp.range(31,    0) =Input_1.read();
			Output_1.write(data_temp.range(255, 224));
			Output_1.write(data_temp.range(223, 192));
			Output_1.write(data_temp.range(191, 160));
			Output_1.write(data_temp.range(159, 128));
			Output_1.write(data_temp.range(127,  96));
			Output_1.write(data_temp.range(95,   64));
			Output_1.write(data_temp.range(63,   32));
			Output_1.write(data_temp.range(31,    0));
	  }

	  index = 1;
  }


  test_instance(255, 224) = Input_1.read();
  test_instance(223, 192) = Input_1.read();
  test_instance(191, 160) = Input_1.read();
  test_instance(159, 128) = Input_1.read();
  test_instance(127,  96) = Input_1.read();
  test_instance(95,   64) = Input_1.read();
  test_instance(63,   32) = Input_1.read();
  test_instance(31,    0) = Input_1.read();
  Output_1.write(test_instance(255, 224));
  Output_1.write(test_instance(223, 192));
  Output_1.write(test_instance(191, 160));
  Output_1.write(test_instance(159, 128));
  Output_1.write(test_instance(127,  96));
  Output_1.write(test_instance(95,   64));
  Output_1.write(test_instance(63,   32));
  Output_1.write(test_instance(31,    0));

  int min_distance_list[K_CONST];
  int label_list[K_CONST];

  bit128 input_tmp1, input_tmp2;
  input_tmp1(127,  96) = Input_1.read();
  input_tmp1(95,   64) = Input_1.read();
  input_tmp1(63,   32) = Input_1.read();
  input_tmp1(31,    0) = Input_1.read();
  input_tmp2(127,  96) = Input_1.read();
  input_tmp2(95,   64) = Input_1.read();
  input_tmp2(63,   32) = Input_1.read();
  input_tmp2(31,    0) = Input_1.read();

  for(int i=0; i<K_CONST; i++)
  {
#pragma HLS unroll
	  min_distance_list[i] = (int) input_tmp1(i*32+31, i*32);
	  label_list[i] = (int) input_tmp2(i*32+31, i*32);
  }

  // Initialize the knn set
   SET_KNN_SET: for ( int i = 0; i < K_CONST * 2 ; ++i )
   {
#pragma HLS unroll
     // Note that the max distance is 256
     knn_set[i] = 256;
   }

   TRAINING_LOOP : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
   {
       #pragma HLS pipeline
       LANES : for ( int j = 0; j < 2; j++ )
       {
         #pragma HLS unroll
         WholeDigitType training_instance = training_set[j * NUM_TRAINING / PAR_FACTOR + i];
         update_knn( test_instance, training_instance, &knn_set[j * K_CONST] );
       }
   }

#ifdef DEBUG
   printf("knn_update8");
   for(int i=0; i<6; i++){
   	printf("knn_set[%d]=%d,", i, knn_set[i]);
   }
   printf("\n");
#endif

   //update min_distance_list and label_list according to the new knn_set
   LabelType label_in = 3;
   knn_vote_small(knn_set, min_distance_list, label_list, label_in);

   bit128 output_tmp1, output_tmp2;

   for(int i=0; i<K_CONST; i++)
   {
#pragma HLS unroll
	   output_tmp1(i*32+31, i*32) = min_distance_list[i];
	   output_tmp2(i*32+31, i*32) = label_list[i];
   }


   Output_1.write(output_tmp1(127,96));
   Output_1.write(output_tmp1(95, 64));
   Output_1.write(output_tmp1(63, 32));
   Output_1.write(output_tmp1(31,  0));
   Output_1.write(output_tmp2(127,96));
   Output_1.write(output_tmp2(95, 64));
   Output_1.write(output_tmp2(63, 32));
   Output_1.write(output_tmp2(31,  0));
  return;
}


#define NUM9 9
void update_knn9(hls::stream<ap_uint<32> > & Input_1, hls::stream<ap_uint<32> > & Output_1)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1

static WholeDigitType training_set [NUM_TRAINING / PAR_FACTOR_NEW];
#pragma HLS array_partition variable=training_set block factor=2 dim=0

static WholeDigitType test_instance;


static int knn_set[K_CONST*2];
#pragma HLS array_partition variable=knn_set complete dim=0

WholeDigitType data_temp;
static int index = 0;



  if (index == 0)
  {
	  //Store the local training set
	  STORE_LOCAL: for(int i = 0; i < NUM_TRAINING / PAR_FACTOR_NEW; i++)
	  {
#pragma HLS pipeline
			training_set[i].range(255, 224) =Input_1.read();
			training_set[i].range(223, 192) =Input_1.read();
			training_set[i].range(191, 160) =Input_1.read();
			training_set[i].range(159, 128) =Input_1.read();
			training_set[i].range(127,  96) =Input_1.read();
			training_set[i].range(95,   64) =Input_1.read();
			training_set[i].range(63,   32) =Input_1.read();
			training_set[i].range(31,    0) =Input_1.read();
	  }

	  //Transit the training sets for other pages
	  TRANSFER_LOOP: for(int i = 0; i < NUM_TRAINING / PAR_FACTOR_NEW * (PAR_FACTOR_NEW - NUM9); i++)
	  {
#pragma HLS pipeline
			data_temp.range(255, 224) =Input_1.read();
			data_temp.range(223, 192) =Input_1.read();
			data_temp.range(191, 160) =Input_1.read();
			data_temp.range(159, 128) =Input_1.read();
			data_temp.range(127,  96) =Input_1.read();
			data_temp.range(95,   64) =Input_1.read();
			data_temp.range(63,   32) =Input_1.read();
			data_temp.range(31,    0) =Input_1.read();
			Output_1.write(data_temp.range(255, 224));
			Output_1.write(data_temp.range(223, 192));
			Output_1.write(data_temp.range(191, 160));
			Output_1.write(data_temp.range(159, 128));
			Output_1.write(data_temp.range(127,  96));
			Output_1.write(data_temp.range(95,   64));
			Output_1.write(data_temp.range(63,   32));
			Output_1.write(data_temp.range(31,    0));
	  }

	  index = 1;
  }


  test_instance(255, 224) = Input_1.read();
  test_instance(223, 192) = Input_1.read();
  test_instance(191, 160) = Input_1.read();
  test_instance(159, 128) = Input_1.read();
  test_instance(127,  96) = Input_1.read();
  test_instance(95,   64) = Input_1.read();
  test_instance(63,   32) = Input_1.read();
  test_instance(31,    0) = Input_1.read();
  Output_1.write(test_instance(255, 224));
  Output_1.write(test_instance(223, 192));
  Output_1.write(test_instance(191, 160));
  Output_1.write(test_instance(159, 128));
  Output_1.write(test_instance(127,  96));
  Output_1.write(test_instance(95,   64));
  Output_1.write(test_instance(63,   32));
  Output_1.write(test_instance(31,    0));
  int min_distance_list[K_CONST];
  int label_list[K_CONST];

  bit128 input_tmp1, input_tmp2;
  input_tmp1(127,  96) = Input_1.read();
  input_tmp1(95,   64) = Input_1.read();
  input_tmp1(63,   32) = Input_1.read();
  input_tmp1(31,    0) = Input_1.read();
  input_tmp2(127,  96) = Input_1.read();
  input_tmp2(95,   64) = Input_1.read();
  input_tmp2(63,   32) = Input_1.read();
  input_tmp2(31,    0) = Input_1.read();

  for(int i=0; i<K_CONST; i++)
  {
#pragma HLS unroll
	  min_distance_list[i] = (int) input_tmp1(i*32+31, i*32);
	  label_list[i] = (int) input_tmp2(i*32+31, i*32);
  }

  // Initialize the knn set
   SET_KNN_SET: for ( int i = 0; i < K_CONST * 2 ; ++i )
   {
#pragma HLS unroll
     // Note that the max distance is 256
     knn_set[i] = 256;
   }

   TRAINING_LOOP : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
   {
       #pragma HLS pipeline
       LANES : for ( int j = 0; j < 2; j++ )
       {
         #pragma HLS unroll
         WholeDigitType training_instance = training_set[j * NUM_TRAINING / PAR_FACTOR + i];
         update_knn( test_instance, training_instance, &knn_set[j * K_CONST] );
       }
   }

#ifdef DEBUG
   printf("knn_update9");
   for(int i=0; i<6; i++){
   	printf("knn_set[%d]=%d,", i, knn_set[i]);
   }
   printf("\n");
#endif

   //update min_distance_list and label_list according to the new knn_set
   LabelType label_in = 4;
   knn_vote_small(knn_set, min_distance_list, label_list, label_in);

   bit128 output_tmp1, output_tmp2;

   for(int i=0; i<K_CONST; i++)
   {
#pragma HLS unroll
	   output_tmp1(i*32+31, i*32) = min_distance_list[i];
	   output_tmp2(i*32+31, i*32) = label_list[i];
   }


   Output_1.write(output_tmp1(127,96));
   Output_1.write(output_tmp1(95, 64));
   Output_1.write(output_tmp1(63, 32));
   Output_1.write(output_tmp1(31,  0));
   Output_1.write(output_tmp2(127,96));
   Output_1.write(output_tmp2(95, 64));
   Output_1.write(output_tmp2(63, 32));
   Output_1.write(output_tmp2(31,  0));
  return;
}


#define NUM10 10
void update_knn10(hls::stream<ap_uint<32> > & Input_1, hls::stream<ap_uint<32> > & Output_1)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1

static WholeDigitType training_set [NUM_TRAINING / PAR_FACTOR_NEW];
#pragma HLS array_partition variable=training_set block factor=2 dim=0

static WholeDigitType test_instance;


static int knn_set[K_CONST*2];
#pragma HLS array_partition variable=knn_set complete dim=0

WholeDigitType data_temp;
static int index = 0;



  if (index == 0)
  {
	  //Store the local training set
	  STORE_LOCAL: for(int i = 0; i < NUM_TRAINING / PAR_FACTOR_NEW; i++)
	  {
#pragma HLS pipeline
			training_set[i].range(255, 224) =Input_1.read();
			training_set[i].range(223, 192) =Input_1.read();
			training_set[i].range(191, 160) =Input_1.read();
			training_set[i].range(159, 128) =Input_1.read();
			training_set[i].range(127,  96) =Input_1.read();
			training_set[i].range(95,   64) =Input_1.read();
			training_set[i].range(63,   32) =Input_1.read();
			training_set[i].range(31,    0) =Input_1.read();
	  }

	  //Transit the training sets for other pages
	  TRANSFER_LOOP: for(int i = 0; i < NUM_TRAINING / PAR_FACTOR_NEW * (PAR_FACTOR_NEW - NUM10); i++)
	  {
#pragma HLS pipeline
			data_temp.range(255, 224) =Input_1.read();
			data_temp.range(223, 192) =Input_1.read();
			data_temp.range(191, 160) =Input_1.read();
			data_temp.range(159, 128) =Input_1.read();
			data_temp.range(127,  96) =Input_1.read();
			data_temp.range(95,   64) =Input_1.read();
			data_temp.range(63,   32) =Input_1.read();
			data_temp.range(31,    0) =Input_1.read();
			Output_1.write(data_temp.range(255, 224));
			Output_1.write(data_temp.range(223, 192));
			Output_1.write(data_temp.range(191, 160));
			Output_1.write(data_temp.range(159, 128));
			Output_1.write(data_temp.range(127,  96));
			Output_1.write(data_temp.range(95,   64));
			Output_1.write(data_temp.range(63,   32));
			Output_1.write(data_temp.range(31,    0));
	  }

	  index = 1;
  }


  test_instance(255, 224) = Input_1.read();
  test_instance(223, 192) = Input_1.read();
  test_instance(191, 160) = Input_1.read();
  test_instance(159, 128) = Input_1.read();
  test_instance(127,  96) = Input_1.read();
  test_instance(95,   64) = Input_1.read();
  test_instance(63,   32) = Input_1.read();
  test_instance(31,    0) = Input_1.read();
  Output_1.write(test_instance(255, 224));
  Output_1.write(test_instance(223, 192));
  Output_1.write(test_instance(191, 160));
  Output_1.write(test_instance(159, 128));
  Output_1.write(test_instance(127,  96));
  Output_1.write(test_instance(95,   64));
  Output_1.write(test_instance(63,   32));
  Output_1.write(test_instance(31,    0));

  int min_distance_list[K_CONST];
  int label_list[K_CONST];

  bit128 input_tmp1, input_tmp2;
  input_tmp1(127,  96) = Input_1.read();
  input_tmp1(95,   64) = Input_1.read();
  input_tmp1(63,   32) = Input_1.read();
  input_tmp1(31,    0) = Input_1.read();
  input_tmp2(127,  96) = Input_1.read();
  input_tmp2(95,   64) = Input_1.read();
  input_tmp2(63,   32) = Input_1.read();
  input_tmp2(31,    0) = Input_1.read();

  for(int i=0; i<K_CONST; i++)
  {
#pragma HLS unroll
	  min_distance_list[i] = (int) input_tmp1(i*32+31, i*32);
	  label_list[i] = (int) input_tmp2(i*32+31, i*32);
  }

  // Initialize the knn set
   SET_KNN_SET: for ( int i = 0; i < K_CONST * 2 ; ++i )
   {
#pragma HLS unroll
     // Note that the max distance is 256
     knn_set[i] = 256;
   }

   TRAINING_LOOP : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
   {
       #pragma HLS pipeline
       LANES : for ( int j = 0; j < 2; j++ )
       {
         #pragma HLS unroll
         WholeDigitType training_instance = training_set[j * NUM_TRAINING / PAR_FACTOR + i];
         update_knn( test_instance, training_instance, &knn_set[j * K_CONST] );
       }
   }

#ifdef DEBUG
   printf("knn_update10");
   for(int i=0; i<6; i++){
   	printf("knn_set[%d]=%d,", i, knn_set[i]);
   }
   printf("\n");
#endif

   //update min_distance_list and label_list according to the new knn_set
   LabelType label_in = 4;
   knn_vote_small(knn_set, min_distance_list, label_list, label_in);

   bit128 output_tmp1, output_tmp2;

   for(int i=0; i<K_CONST; i++)
   {
#pragma HLS unroll
	   output_tmp1(i*32+31, i*32) = min_distance_list[i];
	   output_tmp2(i*32+31, i*32) = label_list[i];
   }


   Output_1.write(output_tmp1(127,96));
   Output_1.write(output_tmp1(95, 64));
   Output_1.write(output_tmp1(63, 32));
   Output_1.write(output_tmp1(31,  0));
   Output_1.write(output_tmp2(127,96));
   Output_1.write(output_tmp2(95, 64));
   Output_1.write(output_tmp2(63, 32));
   Output_1.write(output_tmp2(31,  0));
  return;
}


#define NUM11 11
void update_knn11(hls::stream<ap_uint<32> > & Input_1, hls::stream<ap_uint<32> > & Output_1)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1

static WholeDigitType training_set [NUM_TRAINING / PAR_FACTOR_NEW];
#pragma HLS array_partition variable=training_set block factor=2 dim=0

static WholeDigitType test_instance;


static int knn_set[K_CONST*2];
#pragma HLS array_partition variable=knn_set complete dim=0

WholeDigitType data_temp;
static int index = 0;



  if (index == 0)
  {
	  //Store the local training set
	  STORE_LOCAL: for(int i = 0; i < NUM_TRAINING / PAR_FACTOR_NEW; i++)
	  {
#pragma HLS pipeline
			training_set[i].range(255, 224) =Input_1.read();
			training_set[i].range(223, 192) =Input_1.read();
			training_set[i].range(191, 160) =Input_1.read();
			training_set[i].range(159, 128) =Input_1.read();
			training_set[i].range(127,  96) =Input_1.read();
			training_set[i].range(95,   64) =Input_1.read();
			training_set[i].range(63,   32) =Input_1.read();
			training_set[i].range(31,    0) =Input_1.read();
	  }

	  //Transit the training sets for other pages
	  TRANSFER_LOOP: for(int i = 0; i < NUM_TRAINING / PAR_FACTOR_NEW * (PAR_FACTOR_NEW - NUM11); i++)
	  {
#pragma HLS pipeline
			data_temp.range(255, 224) =Input_1.read();
			data_temp.range(223, 192) =Input_1.read();
			data_temp.range(191, 160) =Input_1.read();
			data_temp.range(159, 128) =Input_1.read();
			data_temp.range(127,  96) =Input_1.read();
			data_temp.range(95,   64) =Input_1.read();
			data_temp.range(63,   32) =Input_1.read();
			data_temp.range(31,    0) =Input_1.read();
			Output_1.write(data_temp.range(255, 224));
			Output_1.write(data_temp.range(223, 192));
			Output_1.write(data_temp.range(191, 160));
			Output_1.write(data_temp.range(159, 128));
			Output_1.write(data_temp.range(127,  96));
			Output_1.write(data_temp.range(95,   64));
			Output_1.write(data_temp.range(63,   32));
			Output_1.write(data_temp.range(31,    0));
	  }

	  index = 1;
  }


  test_instance(255, 224) = Input_1.read();
  test_instance(223, 192) = Input_1.read();
  test_instance(191, 160) = Input_1.read();
  test_instance(159, 128) = Input_1.read();
  test_instance(127,  96) = Input_1.read();
  test_instance(95,   64) = Input_1.read();
  test_instance(63,   32) = Input_1.read();
  test_instance(31,    0) = Input_1.read();
  Output_1.write(test_instance(255, 224));
  Output_1.write(test_instance(223, 192));
  Output_1.write(test_instance(191, 160));
  Output_1.write(test_instance(159, 128));
  Output_1.write(test_instance(127,  96));
  Output_1.write(test_instance(95,   64));
  Output_1.write(test_instance(63,   32));
  Output_1.write(test_instance(31,    0));
  int min_distance_list[K_CONST];
  int label_list[K_CONST];

  bit128 input_tmp1, input_tmp2;
  input_tmp1(127,  96) = Input_1.read();
  input_tmp1(95,   64) = Input_1.read();
  input_tmp1(63,   32) = Input_1.read();
  input_tmp1(31,    0) = Input_1.read();
  input_tmp2(127,  96) = Input_1.read();
  input_tmp2(95,   64) = Input_1.read();
  input_tmp2(63,   32) = Input_1.read();
  input_tmp2(31,    0) = Input_1.read();

  for(int i=0; i<K_CONST; i++)
  {
#pragma HLS unroll
	  min_distance_list[i] = (int) input_tmp1(i*32+31, i*32);
	  label_list[i] = (int) input_tmp2(i*32+31, i*32);
  }

  // Initialize the knn set
   SET_KNN_SET: for ( int i = 0; i < K_CONST * 2 ; ++i )
   {
#pragma HLS unroll
     // Note that the max distance is 256
     knn_set[i] = 256;
   }

   TRAINING_LOOP : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
   {
       #pragma HLS pipeline
       LANES : for ( int j = 0; j < 2; j++ )
       {
         #pragma HLS unroll
         WholeDigitType training_instance = training_set[j * NUM_TRAINING / PAR_FACTOR + i];
         update_knn( test_instance, training_instance, &knn_set[j * K_CONST] );
       }
   }

#ifdef DEBUG
   printf("knn_update11");
   for(int i=0; i<6; i++){
   	printf("knn_set[%d]=%d,", i, knn_set[i]);
   }
   printf("\n");
#endif

   //update min_distance_list and label_list according to the new knn_set
   LabelType label_in = 5;
   knn_vote_small(knn_set, min_distance_list, label_list, label_in);

   bit128 output_tmp1, output_tmp2;

   for(int i=0; i<K_CONST; i++)
   {
#pragma HLS unroll
	   output_tmp1(i*32+31, i*32) = min_distance_list[i];
	   output_tmp2(i*32+31, i*32) = label_list[i];
   }


   Output_1.write(output_tmp1(127,96));
   Output_1.write(output_tmp1(95, 64));
   Output_1.write(output_tmp1(63, 32));
   Output_1.write(output_tmp1(31,  0));
   Output_1.write(output_tmp2(127,96));
   Output_1.write(output_tmp2(95, 64));
   Output_1.write(output_tmp2(63, 32));
   Output_1.write(output_tmp2(31,  0));
  return;
}


#define NUM12 12
void update_knn12(hls::stream<ap_uint<32> > & Input_1, hls::stream<ap_uint<32> > & Output_1)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1

static WholeDigitType training_set [NUM_TRAINING / PAR_FACTOR_NEW];
#pragma HLS array_partition variable=training_set block factor=2 dim=0

static WholeDigitType test_instance;


static int knn_set[K_CONST*2];
#pragma HLS array_partition variable=knn_set complete dim=0

WholeDigitType data_temp;
static int index = 0;



  if (index == 0)
  {
	  //Store the local training set
	  STORE_LOCAL: for(int i = 0; i < NUM_TRAINING / PAR_FACTOR_NEW; i++)
	  {
#pragma HLS pipeline
			training_set[i].range(255, 224) =Input_1.read();
			training_set[i].range(223, 192) =Input_1.read();
			training_set[i].range(191, 160) =Input_1.read();
			training_set[i].range(159, 128) =Input_1.read();
			training_set[i].range(127,  96) =Input_1.read();
			training_set[i].range(95,   64) =Input_1.read();
			training_set[i].range(63,   32) =Input_1.read();
			training_set[i].range(31,    0) =Input_1.read();
	  }

	  //Transit the training sets for other pages
	  TRANSFER_LOOP: for(int i = 0; i < NUM_TRAINING / PAR_FACTOR_NEW * (PAR_FACTOR_NEW - NUM12); i++)
	  {
#pragma HLS pipeline
			data_temp.range(255, 224) =Input_1.read();
			data_temp.range(223, 192) =Input_1.read();
			data_temp.range(191, 160) =Input_1.read();
			data_temp.range(159, 128) =Input_1.read();
			data_temp.range(127,  96) =Input_1.read();
			data_temp.range(95,   64) =Input_1.read();
			data_temp.range(63,   32) =Input_1.read();
			data_temp.range(31,    0) =Input_1.read();
			Output_1.write(data_temp.range(255, 224));
			Output_1.write(data_temp.range(223, 192));
			Output_1.write(data_temp.range(191, 160));
			Output_1.write(data_temp.range(159, 128));
			Output_1.write(data_temp.range(127,  96));
			Output_1.write(data_temp.range(95,   64));
			Output_1.write(data_temp.range(63,   32));
			Output_1.write(data_temp.range(31,    0));
	  }

	  index = 1;
  }


  test_instance(255, 224) = Input_1.read();
  test_instance(223, 192) = Input_1.read();
  test_instance(191, 160) = Input_1.read();
  test_instance(159, 128) = Input_1.read();
  test_instance(127,  96) = Input_1.read();
  test_instance(95,   64) = Input_1.read();
  test_instance(63,   32) = Input_1.read();
  test_instance(31,    0) = Input_1.read();
  Output_1.write(test_instance(255, 224));
  Output_1.write(test_instance(223, 192));
  Output_1.write(test_instance(191, 160));
  Output_1.write(test_instance(159, 128));
  Output_1.write(test_instance(127,  96));
  Output_1.write(test_instance(95,   64));
  Output_1.write(test_instance(63,   32));
  Output_1.write(test_instance(31,    0));

  int min_distance_list[K_CONST];
  int label_list[K_CONST];

  bit128 input_tmp1, input_tmp2;
  input_tmp1(127,  96) = Input_1.read();
  input_tmp1(95,   64) = Input_1.read();
  input_tmp1(63,   32) = Input_1.read();
  input_tmp1(31,    0) = Input_1.read();
  input_tmp2(127,  96) = Input_1.read();
  input_tmp2(95,   64) = Input_1.read();
  input_tmp2(63,   32) = Input_1.read();
  input_tmp2(31,    0) = Input_1.read();

  for(int i=0; i<K_CONST; i++)
  {
#pragma HLS unroll
	  min_distance_list[i] = (int) input_tmp1(i*32+31, i*32);
	  label_list[i] = (int) input_tmp2(i*32+31, i*32);
  }

  // Initialize the knn set
   SET_KNN_SET: for ( int i = 0; i < K_CONST * 2 ; ++i )
   {
#pragma HLS unroll
     // Note that the max distance is 256
     knn_set[i] = 256;
   }

   TRAINING_LOOP : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
   {
       #pragma HLS pipeline
       LANES : for ( int j = 0; j < 2; j++ )
       {
         #pragma HLS unroll
         WholeDigitType training_instance = training_set[j * NUM_TRAINING / PAR_FACTOR + i];
         update_knn( test_instance, training_instance, &knn_set[j * K_CONST] );
       }
   }

#ifdef DEBUG
   printf("knn_update12");
   for(int i=0; i<6; i++){
   	printf("knn_set[%d]=%d,", i, knn_set[i]);
   }
   printf("\n");
#endif

   //update min_distance_list and label_list according to the new knn_set
   LabelType label_in = 5;
   knn_vote_small(knn_set, min_distance_list, label_list, label_in);

   bit128 output_tmp1, output_tmp2;

   for(int i=0; i<K_CONST; i++)
   {
#pragma HLS unroll
	   output_tmp1(i*32+31, i*32) = min_distance_list[i];
	   output_tmp2(i*32+31, i*32) = label_list[i];
   }


   Output_1.write(output_tmp1(127,96));
   Output_1.write(output_tmp1(95, 64));
   Output_1.write(output_tmp1(63, 32));
   Output_1.write(output_tmp1(31,  0));
   Output_1.write(output_tmp2(127,96));
   Output_1.write(output_tmp2(95, 64));
   Output_1.write(output_tmp2(63, 32));
   Output_1.write(output_tmp2(31,  0));
  return;
}


#define NUM13 13
void update_knn13(hls::stream<ap_uint<32> > & Input_1, hls::stream<ap_uint<32> > & Output_1)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1

static WholeDigitType training_set [NUM_TRAINING / PAR_FACTOR_NEW];
#pragma HLS array_partition variable=training_set block factor=2 dim=0

static WholeDigitType test_instance;


static int knn_set[K_CONST*2];
#pragma HLS array_partition variable=knn_set complete dim=0

WholeDigitType data_temp;
static int index = 0;



  if (index == 0)
  {
	  //Store the local training set
	  STORE_LOCAL: for(int i = 0; i < NUM_TRAINING / PAR_FACTOR_NEW; i++)
	  {
#pragma HLS pipeline
			training_set[i].range(255, 224) =Input_1.read();
			training_set[i].range(223, 192) =Input_1.read();
			training_set[i].range(191, 160) =Input_1.read();
			training_set[i].range(159, 128) =Input_1.read();
			training_set[i].range(127,  96) =Input_1.read();
			training_set[i].range(95,   64) =Input_1.read();
			training_set[i].range(63,   32) =Input_1.read();
			training_set[i].range(31,    0) =Input_1.read();
	  }

	  //Transit the training sets for other pages
	  TRANSFER_LOOP: for(int i = 0; i < NUM_TRAINING / PAR_FACTOR_NEW * (PAR_FACTOR_NEW - NUM13); i++)
	  {
#pragma HLS pipeline
			data_temp.range(255, 224) =Input_1.read();
			data_temp.range(223, 192) =Input_1.read();
			data_temp.range(191, 160) =Input_1.read();
			data_temp.range(159, 128) =Input_1.read();
			data_temp.range(127,  96) =Input_1.read();
			data_temp.range(95,   64) =Input_1.read();
			data_temp.range(63,   32) =Input_1.read();
			data_temp.range(31,    0) =Input_1.read();
			Output_1.write(data_temp.range(255, 224));
			Output_1.write(data_temp.range(223, 192));
			Output_1.write(data_temp.range(191, 160));
			Output_1.write(data_temp.range(159, 128));
			Output_1.write(data_temp.range(127,  96));
			Output_1.write(data_temp.range(95,   64));
			Output_1.write(data_temp.range(63,   32));
			Output_1.write(data_temp.range(31,    0));
	  }

	  index = 1;
  }


  test_instance(255, 224) = Input_1.read();
  test_instance(223, 192) = Input_1.read();
  test_instance(191, 160) = Input_1.read();
  test_instance(159, 128) = Input_1.read();
  test_instance(127,  96) = Input_1.read();
  test_instance(95,   64) = Input_1.read();
  test_instance(63,   32) = Input_1.read();
  test_instance(31,    0) = Input_1.read();
  Output_1.write(test_instance(255, 224));
  Output_1.write(test_instance(223, 192));
  Output_1.write(test_instance(191, 160));
  Output_1.write(test_instance(159, 128));
  Output_1.write(test_instance(127,  96));
  Output_1.write(test_instance(95,   64));
  Output_1.write(test_instance(63,   32));
  Output_1.write(test_instance(31,    0));

  int min_distance_list[K_CONST];
  int label_list[K_CONST];

  bit128 input_tmp1, input_tmp2;
  input_tmp1(127,  96) = Input_1.read();
  input_tmp1(95,   64) = Input_1.read();
  input_tmp1(63,   32) = Input_1.read();
  input_tmp1(31,    0) = Input_1.read();
  input_tmp2(127,  96) = Input_1.read();
  input_tmp2(95,   64) = Input_1.read();
  input_tmp2(63,   32) = Input_1.read();
  input_tmp2(31,    0) = Input_1.read();
  for(int i=0; i<K_CONST; i++)
  {
#pragma HLS unroll
	  min_distance_list[i] = (int) input_tmp1(i*32+31, i*32);
	  label_list[i] = (int) input_tmp2(i*32+31, i*32);
  }

  // Initialize the knn set
   SET_KNN_SET: for ( int i = 0; i < K_CONST * 2 ; ++i )
   {
#pragma HLS unroll
     // Note that the max distance is 256
     knn_set[i] = 256;
   }

   TRAINING_LOOP : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
   {
       #pragma HLS pipeline
       LANES : for ( int j = 0; j < 2; j++ )
       {
         #pragma HLS unroll
         WholeDigitType training_instance = training_set[j * NUM_TRAINING / PAR_FACTOR + i];
         update_knn( test_instance, training_instance, &knn_set[j * K_CONST] );
       }
   }

#ifdef DEBUG
   printf("knn_update13");
   for(int i=0; i<6; i++){
   	printf("knn_set[%d]=%d,", i, knn_set[i]);
   }
   printf("\n");
#endif


   //update min_distance_list and label_list according to the new knn_set
   LabelType label_in = 6;
   knn_vote_small(knn_set, min_distance_list, label_list, label_in);

   bit128 output_tmp1, output_tmp2;

   for(int i=0; i<K_CONST; i++)
   {
#pragma HLS unroll
	   output_tmp1(i*32+31, i*32) = min_distance_list[i];
	   output_tmp2(i*32+31, i*32) = label_list[i];
   }


   Output_1.write(output_tmp1(127,96));
   Output_1.write(output_tmp1(95, 64));
   Output_1.write(output_tmp1(63, 32));
   Output_1.write(output_tmp1(31,  0));
   Output_1.write(output_tmp2(127,96));
   Output_1.write(output_tmp2(95, 64));
   Output_1.write(output_tmp2(63, 32));
   Output_1.write(output_tmp2(31,  0));
  return;
}


#define NUM14 14
void update_knn14(hls::stream<ap_uint<32> > & Input_1, hls::stream<ap_uint<32> > & Output_1)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1

static WholeDigitType training_set [NUM_TRAINING / PAR_FACTOR_NEW];
#pragma HLS array_partition variable=training_set block factor=2 dim=0

static WholeDigitType test_instance;


static int knn_set[K_CONST*2];
#pragma HLS array_partition variable=knn_set complete dim=0

WholeDigitType data_temp;
static int index = 0;



  if (index == 0)
  {
	  //Store the local training set
	  STORE_LOCAL: for(int i = 0; i < NUM_TRAINING / PAR_FACTOR_NEW; i++)
	  {
#pragma HLS pipeline
			training_set[i].range(255, 224) =Input_1.read();
			training_set[i].range(223, 192) =Input_1.read();
			training_set[i].range(191, 160) =Input_1.read();
			training_set[i].range(159, 128) =Input_1.read();
			training_set[i].range(127,  96) =Input_1.read();
			training_set[i].range(95,   64) =Input_1.read();
			training_set[i].range(63,   32) =Input_1.read();
			training_set[i].range(31,    0) =Input_1.read();
	  }

	  //Transit the training sets for other pages
	  TRANSFER_LOOP: for(int i = 0; i < NUM_TRAINING / PAR_FACTOR_NEW * (PAR_FACTOR_NEW - NUM14); i++)
	  {
#pragma HLS pipeline
			data_temp.range(255, 224) =Input_1.read();
			data_temp.range(223, 192) =Input_1.read();
			data_temp.range(191, 160) =Input_1.read();
			data_temp.range(159, 128) =Input_1.read();
			data_temp.range(127,  96) =Input_1.read();
			data_temp.range(95,   64) =Input_1.read();
			data_temp.range(63,   32) =Input_1.read();
			data_temp.range(31,    0) =Input_1.read();
			Output_1.write(data_temp.range(255, 224));
			Output_1.write(data_temp.range(223, 192));
			Output_1.write(data_temp.range(191, 160));
			Output_1.write(data_temp.range(159, 128));
			Output_1.write(data_temp.range(127,  96));
			Output_1.write(data_temp.range(95,   64));
			Output_1.write(data_temp.range(63,   32));
			Output_1.write(data_temp.range(31,    0));
	  }

	  index = 1;
  }


  test_instance(255, 224) = Input_1.read();
  test_instance(223, 192) = Input_1.read();
  test_instance(191, 160) = Input_1.read();
  test_instance(159, 128) = Input_1.read();
  test_instance(127,  96) = Input_1.read();
  test_instance(95,   64) = Input_1.read();
  test_instance(63,   32) = Input_1.read();
  test_instance(31,    0) = Input_1.read();
  Output_1.write(test_instance(255, 224));
  Output_1.write(test_instance(223, 192));
  Output_1.write(test_instance(191, 160));
  Output_1.write(test_instance(159, 128));
  Output_1.write(test_instance(127,  96));
  Output_1.write(test_instance(95,   64));
  Output_1.write(test_instance(63,   32));
  Output_1.write(test_instance(31,    0));
  int min_distance_list[K_CONST];
  int label_list[K_CONST];

  bit128 input_tmp1, input_tmp2;
  input_tmp1(127,  96) = Input_1.read();
  input_tmp1(95,   64) = Input_1.read();
  input_tmp1(63,   32) = Input_1.read();
  input_tmp1(31,    0) = Input_1.read();
  input_tmp2(127,  96) = Input_1.read();
  input_tmp2(95,   64) = Input_1.read();
  input_tmp2(63,   32) = Input_1.read();
  input_tmp2(31,    0) = Input_1.read();

  for(int i=0; i<K_CONST; i++)
  {
#pragma HLS unroll
	  min_distance_list[i] = (int) input_tmp1(i*32+31, i*32);
	  label_list[i] = (int) input_tmp2(i*32+31, i*32);
  }

  // Initialize the knn set
   SET_KNN_SET: for ( int i = 0; i < K_CONST * 2 ; ++i )
   {
#pragma HLS unroll
     // Note that the max distance is 256
     knn_set[i] = 256;
   }

   TRAINING_LOOP : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
   {
       #pragma HLS pipeline
       LANES : for ( int j = 0; j < 2; j++ )
       {
         #pragma HLS unroll
         WholeDigitType training_instance = training_set[j * NUM_TRAINING / PAR_FACTOR + i];
         update_knn( test_instance, training_instance, &knn_set[j * K_CONST] );
       }
   }

#ifdef DEBUG
   printf("knn_update14");
   for(int i=0; i<6; i++){
   	printf("knn_set[%d]=%d,", i, knn_set[i]);
   }
   printf("\n");
#endif


   //update min_distance_list and label_list according to the new knn_set
   LabelType label_in = 6;
   knn_vote_small(knn_set, min_distance_list, label_list, label_in);

   bit128 output_tmp1, output_tmp2;

   for(int i=0; i<K_CONST; i++)
   {
#pragma HLS unroll
	   output_tmp1(i*32+31, i*32) = min_distance_list[i];
	   output_tmp2(i*32+31, i*32) = label_list[i];
   }


   Output_1.write(output_tmp1(127,96));
   Output_1.write(output_tmp1(95, 64));
   Output_1.write(output_tmp1(63, 32));
   Output_1.write(output_tmp1(31,  0));
   Output_1.write(output_tmp2(127,96));
   Output_1.write(output_tmp2(95, 64));
   Output_1.write(output_tmp2(63, 32));
   Output_1.write(output_tmp2(31,  0));
  return;
}


#define NUM15 15
void update_knn15(hls::stream<ap_uint<32> > & Input_1, hls::stream<ap_uint<32> > & Output_1)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1

static WholeDigitType training_set [NUM_TRAINING / PAR_FACTOR_NEW];
#pragma HLS array_partition variable=training_set block factor=2 dim=0

static WholeDigitType test_instance;


static int knn_set[K_CONST*2];
#pragma HLS array_partition variable=knn_set complete dim=0

WholeDigitType data_temp;
static int index = 0;



  if (index == 0)
  {
	  //Store the local training set
	  STORE_LOCAL: for(int i = 0; i < NUM_TRAINING / PAR_FACTOR_NEW; i++)
	  {
#pragma HLS pipeline
			training_set[i].range(255, 224) =Input_1.read();
			training_set[i].range(223, 192) =Input_1.read();
			training_set[i].range(191, 160) =Input_1.read();
			training_set[i].range(159, 128) =Input_1.read();
			training_set[i].range(127,  96) =Input_1.read();
			training_set[i].range(95,   64) =Input_1.read();
			training_set[i].range(63,   32) =Input_1.read();
			training_set[i].range(31,    0) =Input_1.read();
	  }

	  //Transit the training sets for other pages
	  TRANSFER_LOOP: for(int i = 0; i < NUM_TRAINING / PAR_FACTOR_NEW * (PAR_FACTOR_NEW - NUM15); i++)
	  {
#pragma HLS pipeline
			data_temp.range(255, 224) =Input_1.read();
			data_temp.range(223, 192) =Input_1.read();
			data_temp.range(191, 160) =Input_1.read();
			data_temp.range(159, 128) =Input_1.read();
			data_temp.range(127,  96) =Input_1.read();
			data_temp.range(95,   64) =Input_1.read();
			data_temp.range(63,   32) =Input_1.read();
			data_temp.range(31,    0) =Input_1.read();
			Output_1.write(data_temp.range(255, 224));
			Output_1.write(data_temp.range(223, 192));
			Output_1.write(data_temp.range(191, 160));
			Output_1.write(data_temp.range(159, 128));
			Output_1.write(data_temp.range(127,  96));
			Output_1.write(data_temp.range(95,   64));
			Output_1.write(data_temp.range(63,   32));
			Output_1.write(data_temp.range(31,    0));
	  }

	  index = 1;
  }


  test_instance(255, 224) = Input_1.read();
  test_instance(223, 192) = Input_1.read();
  test_instance(191, 160) = Input_1.read();
  test_instance(159, 128) = Input_1.read();
  test_instance(127,  96) = Input_1.read();
  test_instance(95,   64) = Input_1.read();
  test_instance(63,   32) = Input_1.read();
  test_instance(31,    0) = Input_1.read();
  Output_1.write(test_instance(255, 224));
  Output_1.write(test_instance(223, 192));
  Output_1.write(test_instance(191, 160));
  Output_1.write(test_instance(159, 128));
  Output_1.write(test_instance(127,  96));
  Output_1.write(test_instance(95,   64));
  Output_1.write(test_instance(63,   32));
  Output_1.write(test_instance(31,    0));

  int min_distance_list[K_CONST];
  int label_list[K_CONST];

  bit128 input_tmp1, input_tmp2;
  input_tmp1(127,  96) = Input_1.read();
  input_tmp1(95,   64) = Input_1.read();
  input_tmp1(63,   32) = Input_1.read();
  input_tmp1(31,    0) = Input_1.read();
  input_tmp2(127,  96) = Input_1.read();
  input_tmp2(95,   64) = Input_1.read();
  input_tmp2(63,   32) = Input_1.read();
  input_tmp2(31,    0) = Input_1.read();
  for(int i=0; i<K_CONST; i++)
  {
#pragma HLS unroll
	  min_distance_list[i] = (int) input_tmp1(i*32+31, i*32);
	  label_list[i] = (int) input_tmp2(i*32+31, i*32);
  }

  // Initialize the knn set
   SET_KNN_SET: for ( int i = 0; i < K_CONST * 2 ; ++i )
   {
#pragma HLS unroll
     // Note that the max distance is 256
     knn_set[i] = 256;
   }

   TRAINING_LOOP : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
   {
       #pragma HLS pipeline
       LANES : for ( int j = 0; j < 2; j++ )
       {
         #pragma HLS unroll
         WholeDigitType training_instance = training_set[j * NUM_TRAINING / PAR_FACTOR + i];
         update_knn( test_instance, training_instance, &knn_set[j * K_CONST] );
       }
   }

#ifdef DEBUG
   printf("knn_update15");
   for(int i=0; i<6; i++){
   	printf("knn_set[%d]=%d,", i, knn_set[i]);
   }
   printf("\n");
#endif

   //update min_distance_list and label_list according to the new knn_set
   LabelType label_in = 7;
   knn_vote_small(knn_set, min_distance_list, label_list, label_in);

   bit128 output_tmp1, output_tmp2;

   for(int i=0; i<K_CONST; i++)
   {
#pragma HLS unroll
	   output_tmp1(i*32+31, i*32) = min_distance_list[i];
	   output_tmp2(i*32+31, i*32) = label_list[i];
   }


   Output_1.write(output_tmp1(127,96));
   Output_1.write(output_tmp1(95, 64));
   Output_1.write(output_tmp1(63, 32));
   Output_1.write(output_tmp1(31,  0));
   Output_1.write(output_tmp2(127,96));
   Output_1.write(output_tmp2(95, 64));
   Output_1.write(output_tmp2(63, 32));
   Output_1.write(output_tmp2(31,  0));
  return;
}


#define NUM16 16
void update_knn16(hls::stream<ap_uint<32> > & Input_1, hls::stream<ap_uint<32> > & Output_1)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1

static WholeDigitType training_set [NUM_TRAINING / PAR_FACTOR_NEW];
#pragma HLS array_partition variable=training_set block factor=2 dim=0

static WholeDigitType test_instance;


static int knn_set[K_CONST*2];
#pragma HLS array_partition variable=knn_set complete dim=0

WholeDigitType data_temp;
static int index = 0;



  if (index == 0)
  {
	  //Store the local training set
	  STORE_LOCAL: for(int i = 0; i < NUM_TRAINING / PAR_FACTOR_NEW; i++)
	  {
#pragma HLS pipeline
			training_set[i].range(255, 224) =Input_1.read();
			training_set[i].range(223, 192) =Input_1.read();
			training_set[i].range(191, 160) =Input_1.read();
			training_set[i].range(159, 128) =Input_1.read();
			training_set[i].range(127,  96) =Input_1.read();
			training_set[i].range(95,   64) =Input_1.read();
			training_set[i].range(63,   32) =Input_1.read();
			training_set[i].range(31,    0) =Input_1.read();
	  }

	  //Transit the training sets for other pages
	  TRANSFER_LOOP: for(int i = 0; i < NUM_TRAINING / PAR_FACTOR_NEW * (PAR_FACTOR_NEW - NUM16); i++)
	  {
#pragma HLS pipeline
			data_temp.range(255, 224) =Input_1.read();
			data_temp.range(223, 192) =Input_1.read();
			data_temp.range(191, 160) =Input_1.read();
			data_temp.range(159, 128) =Input_1.read();
			data_temp.range(127,  96) =Input_1.read();
			data_temp.range(95,   64) =Input_1.read();
			data_temp.range(63,   32) =Input_1.read();
			data_temp.range(31,    0) =Input_1.read();
			Output_1.write(data_temp.range(255, 224));
			Output_1.write(data_temp.range(223, 192));
			Output_1.write(data_temp.range(191, 160));
			Output_1.write(data_temp.range(159, 128));
			Output_1.write(data_temp.range(127,  96));
			Output_1.write(data_temp.range(95,   64));
			Output_1.write(data_temp.range(63,   32));
			Output_1.write(data_temp.range(31,    0));
	  }

	  index = 1;
  }


  test_instance(255, 224) = Input_1.read();
  test_instance(223, 192) = Input_1.read();
  test_instance(191, 160) = Input_1.read();
  test_instance(159, 128) = Input_1.read();
  test_instance(127,  96) = Input_1.read();
  test_instance(95,   64) = Input_1.read();
  test_instance(63,   32) = Input_1.read();
  test_instance(31,    0) = Input_1.read();
  Output_1.write(test_instance(255, 224));
  Output_1.write(test_instance(223, 192));
  Output_1.write(test_instance(191, 160));
  Output_1.write(test_instance(159, 128));
  Output_1.write(test_instance(127,  96));
  Output_1.write(test_instance(95,   64));
  Output_1.write(test_instance(63,   32));
  Output_1.write(test_instance(31,    0));

  int min_distance_list[K_CONST];
  int label_list[K_CONST];

  bit128 input_tmp1, input_tmp2;
  input_tmp1(127,  96) = Input_1.read();
  input_tmp1(95,   64) = Input_1.read();
  input_tmp1(63,   32) = Input_1.read();
  input_tmp1(31,    0) = Input_1.read();
  input_tmp2(127,  96) = Input_1.read();
  input_tmp2(95,   64) = Input_1.read();
  input_tmp2(63,   32) = Input_1.read();
  input_tmp2(31,    0) = Input_1.read();

  for(int i=0; i<K_CONST; i++)
  {
#pragma HLS unroll
	  min_distance_list[i] = (int) input_tmp1(i*32+31, i*32);
	  label_list[i] = (int) input_tmp2(i*32+31, i*32);
  }

  // Initialize the knn set
   SET_KNN_SET: for ( int i = 0; i < K_CONST * 2 ; ++i )
   {
#pragma HLS unroll
     // Note that the max distance is 256
     knn_set[i] = 256;
   }

   TRAINING_LOOP : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
   {
       #pragma HLS pipeline
       LANES : for ( int j = 0; j < 2; j++ )
       {
         #pragma HLS unroll
         WholeDigitType training_instance = training_set[j * NUM_TRAINING / PAR_FACTOR + i];
         update_knn( test_instance, training_instance, &knn_set[j * K_CONST] );
       }
   }

#ifdef DEBUG
   printf("knn_update16");
   for(int i=0; i<6; i++){
   	printf("knn_set[%d]=%d,", i, knn_set[i]);
   }
   printf("\n");
#endif


   //update min_distance_list and label_list according to the new knn_set
   LabelType label_in = 7;
   knn_vote_small(knn_set, min_distance_list, label_list, label_in);

   bit128 output_tmp1, output_tmp2;

   for(int i=0; i<K_CONST; i++)
   {
#pragma HLS unroll
	   output_tmp1(i*32+31, i*32) = min_distance_list[i];
	   output_tmp2(i*32+31, i*32) = label_list[i];
   }


   Output_1.write(output_tmp1(127,96));
   Output_1.write(output_tmp1(95, 64));
   Output_1.write(output_tmp1(63, 32));
   Output_1.write(output_tmp1(31,  0));
   Output_1.write(output_tmp2(127,96));
   Output_1.write(output_tmp2(95, 64));
   Output_1.write(output_tmp2(63, 32));
   Output_1.write(output_tmp2(31,  0));
  return;
}


#define NUM17 17
void update_knn17(hls::stream<ap_uint<32> > & Input_1, hls::stream<ap_uint<32> > & Output_1)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1

static WholeDigitType training_set [NUM_TRAINING / PAR_FACTOR_NEW];
#pragma HLS array_partition variable=training_set block factor=2 dim=0

static WholeDigitType test_instance;


static int knn_set[K_CONST*2];
#pragma HLS array_partition variable=knn_set complete dim=0

WholeDigitType data_temp;
static int index = 0;



  if (index == 0)
  {
	  //Store the local training set
	  STORE_LOCAL: for(int i = 0; i < NUM_TRAINING / PAR_FACTOR_NEW; i++)
	  {
#pragma HLS pipeline
			training_set[i].range(255, 224) =Input_1.read();
			training_set[i].range(223, 192) =Input_1.read();
			training_set[i].range(191, 160) =Input_1.read();
			training_set[i].range(159, 128) =Input_1.read();
			training_set[i].range(127,  96) =Input_1.read();
			training_set[i].range(95,   64) =Input_1.read();
			training_set[i].range(63,   32) =Input_1.read();
			training_set[i].range(31,    0) =Input_1.read();
	  }

	  //Transit the training sets for other pages
	  TRANSFER_LOOP: for(int i = 0; i < NUM_TRAINING / PAR_FACTOR_NEW * (PAR_FACTOR_NEW - NUM17); i++)
	  {
#pragma HLS pipeline
			data_temp.range(255, 224) =Input_1.read();
			data_temp.range(223, 192) =Input_1.read();
			data_temp.range(191, 160) =Input_1.read();
			data_temp.range(159, 128) =Input_1.read();
			data_temp.range(127,  96) =Input_1.read();
			data_temp.range(95,   64) =Input_1.read();
			data_temp.range(63,   32) =Input_1.read();
			data_temp.range(31,    0) =Input_1.read();
			Output_1.write(data_temp.range(255, 224));
			Output_1.write(data_temp.range(223, 192));
			Output_1.write(data_temp.range(191, 160));
			Output_1.write(data_temp.range(159, 128));
			Output_1.write(data_temp.range(127,  96));
			Output_1.write(data_temp.range(95,   64));
			Output_1.write(data_temp.range(63,   32));
			Output_1.write(data_temp.range(31,    0));
	  }

	  index = 1;
  }


  test_instance(255, 224) = Input_1.read();
  test_instance(223, 192) = Input_1.read();
  test_instance(191, 160) = Input_1.read();
  test_instance(159, 128) = Input_1.read();
  test_instance(127,  96) = Input_1.read();
  test_instance(95,   64) = Input_1.read();
  test_instance(63,   32) = Input_1.read();
  test_instance(31,    0) = Input_1.read();
  Output_1.write(test_instance(255, 224));
  Output_1.write(test_instance(223, 192));
  Output_1.write(test_instance(191, 160));
  Output_1.write(test_instance(159, 128));
  Output_1.write(test_instance(127,  96));
  Output_1.write(test_instance(95,   64));
  Output_1.write(test_instance(63,   32));
  Output_1.write(test_instance(31,    0));

  int min_distance_list[K_CONST];
  int label_list[K_CONST];

  bit128 input_tmp1, input_tmp2;
  input_tmp1(127,  96) = Input_1.read();
  input_tmp1(95,   64) = Input_1.read();
  input_tmp1(63,   32) = Input_1.read();
  input_tmp1(31,    0) = Input_1.read();
  input_tmp2(127,  96) = Input_1.read();
  input_tmp2(95,   64) = Input_1.read();
  input_tmp2(63,   32) = Input_1.read();
  input_tmp2(31,    0) = Input_1.read();

  for(int i=0; i<K_CONST; i++)
  {
#pragma HLS unroll
	  min_distance_list[i] = (int) input_tmp1(i*32+31, i*32);
	  label_list[i] = (int) input_tmp2(i*32+31, i*32);
  }

  // Initialize the knn set
   SET_KNN_SET: for ( int i = 0; i < K_CONST * 2 ; ++i )
   {
#pragma HLS unroll
     // Note that the max distance is 256
     knn_set[i] = 256;
   }

   TRAINING_LOOP : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
   {
       #pragma HLS pipeline
       LANES : for ( int j = 0; j < 2; j++ )
       {
         #pragma HLS unroll
         WholeDigitType training_instance = training_set[j * NUM_TRAINING / PAR_FACTOR + i];
         update_knn( test_instance, training_instance, &knn_set[j * K_CONST] );
       }
   }

#ifdef DEBUG
   printf("knn_update17");
   for(int i=0; i<6; i++){
   	printf("knn_set[%d]=%d,", i, knn_set[i]);
   }
   printf("\n");
#endif

   //update min_distance_list and label_list according to the new knn_set
   LabelType label_in = 8;
   knn_vote_small(knn_set, min_distance_list, label_list, label_in);

   bit128 output_tmp1, output_tmp2;

   for(int i=0; i<K_CONST; i++)
   {
#pragma HLS unroll
	   output_tmp1(i*32+31, i*32) = min_distance_list[i];
	   output_tmp2(i*32+31, i*32) = label_list[i];
   }


   Output_1.write(output_tmp1(127,96));
   Output_1.write(output_tmp1(95, 64));
   Output_1.write(output_tmp1(63, 32));
   Output_1.write(output_tmp1(31,  0));
   Output_1.write(output_tmp2(127,96));
   Output_1.write(output_tmp2(95, 64));
   Output_1.write(output_tmp2(63, 32));
   Output_1.write(output_tmp2(31,  0));
  return;
}


#define NUM18 18
void update_knn18(hls::stream<ap_uint<32> > & Input_1, hls::stream<ap_uint<32> > & Output_1)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1

static WholeDigitType training_set [NUM_TRAINING / PAR_FACTOR_NEW];
#pragma HLS array_partition variable=training_set block factor=2 dim=0

static WholeDigitType test_instance;


static int knn_set[K_CONST*2];
#pragma HLS array_partition variable=knn_set complete dim=0

WholeDigitType data_temp;
static int index = 0;



  if (index == 0)
  {
	  //Store the local training set
	  STORE_LOCAL: for(int i = 0; i < NUM_TRAINING / PAR_FACTOR_NEW; i++)
	  {
#pragma HLS pipeline
			training_set[i].range(255, 224) =Input_1.read();
			training_set[i].range(223, 192) =Input_1.read();
			training_set[i].range(191, 160) =Input_1.read();
			training_set[i].range(159, 128) =Input_1.read();
			training_set[i].range(127,  96) =Input_1.read();
			training_set[i].range(95,   64) =Input_1.read();
			training_set[i].range(63,   32) =Input_1.read();
			training_set[i].range(31,    0) =Input_1.read();
	  }

	  //Transit the training sets for other pages
	  TRANSFER_LOOP: for(int i = 0; i < NUM_TRAINING / PAR_FACTOR_NEW * (PAR_FACTOR_NEW - NUM18); i++)
	  {
#pragma HLS pipeline
			data_temp.range(255, 224) =Input_1.read();
			data_temp.range(223, 192) =Input_1.read();
			data_temp.range(191, 160) =Input_1.read();
			data_temp.range(159, 128) =Input_1.read();
			data_temp.range(127,  96) =Input_1.read();
			data_temp.range(95,   64) =Input_1.read();
			data_temp.range(63,   32) =Input_1.read();
			data_temp.range(31,    0) =Input_1.read();
			Output_1.write(data_temp.range(255, 224));
			Output_1.write(data_temp.range(223, 192));
			Output_1.write(data_temp.range(191, 160));
			Output_1.write(data_temp.range(159, 128));
			Output_1.write(data_temp.range(127,  96));
			Output_1.write(data_temp.range(95,   64));
			Output_1.write(data_temp.range(63,   32));
			Output_1.write(data_temp.range(31,    0));
	  }

	  index = 1;
  }


  test_instance(255, 224) = Input_1.read();
  test_instance(223, 192) = Input_1.read();
  test_instance(191, 160) = Input_1.read();
  test_instance(159, 128) = Input_1.read();
  test_instance(127,  96) = Input_1.read();
  test_instance(95,   64) = Input_1.read();
  test_instance(63,   32) = Input_1.read();
  test_instance(31,    0) = Input_1.read();
  Output_1.write(test_instance(255, 224));
  Output_1.write(test_instance(223, 192));
  Output_1.write(test_instance(191, 160));
  Output_1.write(test_instance(159, 128));
  Output_1.write(test_instance(127,  96));
  Output_1.write(test_instance(95,   64));
  Output_1.write(test_instance(63,   32));
  Output_1.write(test_instance(31,    0));

  int min_distance_list[K_CONST];
  int label_list[K_CONST];

  bit128 input_tmp1, input_tmp2;
  input_tmp1(127,  96) = Input_1.read();
  input_tmp1(95,   64) = Input_1.read();
  input_tmp1(63,   32) = Input_1.read();
  input_tmp1(31,    0) = Input_1.read();
  input_tmp2(127,  96) = Input_1.read();
  input_tmp2(95,   64) = Input_1.read();
  input_tmp2(63,   32) = Input_1.read();
  input_tmp2(31,    0) = Input_1.read();

  for(int i=0; i<K_CONST; i++)
  {
#pragma HLS unroll
	  min_distance_list[i] = (int) input_tmp1(i*32+31, i*32);
	  label_list[i] = (int) input_tmp2(i*32+31, i*32);
  }

  // Initialize the knn set
   SET_KNN_SET: for ( int i = 0; i < K_CONST * 2 ; ++i )
   {
#pragma HLS unroll
     // Note that the max distance is 256
     knn_set[i] = 256;
   }

   TRAINING_LOOP : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
   {
       #pragma HLS pipeline
       LANES : for ( int j = 0; j < 2; j++ )
       {
         #pragma HLS unroll
         WholeDigitType training_instance = training_set[j * NUM_TRAINING / PAR_FACTOR + i];
         update_knn( test_instance, training_instance, &knn_set[j * K_CONST] );
       }
   }

#ifdef DEBUG
   printf("knn_update18");
   for(int i=0; i<6; i++){
   	printf("knn_set[%d]=%d,", i, knn_set[i]);
   }
   printf("\n");
#endif

   //update min_distance_list and label_list according to the new knn_set
   LabelType label_in = 8;
   knn_vote_small(knn_set, min_distance_list, label_list, label_in);

   bit128 output_tmp1, output_tmp2;

   for(int i=0; i<K_CONST; i++)
   {
#pragma HLS unroll
	   output_tmp1(i*32+31, i*32) = min_distance_list[i];
	   output_tmp2(i*32+31, i*32) = label_list[i];
   }


   Output_1.write(output_tmp1(127,96));
   Output_1.write(output_tmp1(95, 64));
   Output_1.write(output_tmp1(63, 32));
   Output_1.write(output_tmp1(31,  0));
   Output_1.write(output_tmp2(127,96));
   Output_1.write(output_tmp2(95, 64));
   Output_1.write(output_tmp2(63, 32));
   Output_1.write(output_tmp2(31,  0));
  return;
}


#define NUM19 19
void update_knn19(hls::stream<ap_uint<32> > & Input_1, hls::stream<ap_uint<32> > & Output_1)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1

static WholeDigitType training_set [NUM_TRAINING / PAR_FACTOR_NEW];
#pragma HLS array_partition variable=training_set block factor=2 dim=0

static WholeDigitType test_instance;


static int knn_set[K_CONST*2];
#pragma HLS array_partition variable=knn_set complete dim=0

WholeDigitType data_temp;
static int index = 0;



  if (index == 0)
  {
	  //Store the local training set
	  STORE_LOCAL: for(int i = 0; i < NUM_TRAINING / PAR_FACTOR_NEW; i++)
	  {
#pragma HLS pipeline
			training_set[i].range(255, 224) =Input_1.read();
			training_set[i].range(223, 192) =Input_1.read();
			training_set[i].range(191, 160) =Input_1.read();
			training_set[i].range(159, 128) =Input_1.read();
			training_set[i].range(127,  96) =Input_1.read();
			training_set[i].range(95,   64) =Input_1.read();
			training_set[i].range(63,   32) =Input_1.read();
			training_set[i].range(31,    0) =Input_1.read();
	  }

	  //Transit the training sets for other pages
	  TRANSFER_LOOP: for(int i = 0; i < NUM_TRAINING / PAR_FACTOR_NEW * (PAR_FACTOR_NEW - NUM19); i++)
	  {
#pragma HLS pipeline
		data_temp.range(255, 224) =Input_1.read();
		data_temp.range(223, 192) =Input_1.read();
		data_temp.range(191, 160) =Input_1.read();
		data_temp.range(159, 128) =Input_1.read();
		data_temp.range(127,  96) =Input_1.read();
		data_temp.range(95,   64) =Input_1.read();
		data_temp.range(63,   32) =Input_1.read();
		data_temp.range(31,    0) =Input_1.read();
		Output_1.write(data_temp.range(255, 224));
		Output_1.write(data_temp.range(223, 192));
		Output_1.write(data_temp.range(191, 160));
		Output_1.write(data_temp.range(159, 128));
		Output_1.write(data_temp.range(127,  96));
		Output_1.write(data_temp.range(95,   64));
		Output_1.write(data_temp.range(63,   32));
		Output_1.write(data_temp.range(31,    0));
	  }

	  index = 1;
  }


  test_instance(255, 224) = Input_1.read();
  test_instance(223, 192) = Input_1.read();
  test_instance(191, 160) = Input_1.read();
  test_instance(159, 128) = Input_1.read();
  test_instance(127,  96) = Input_1.read();
  test_instance(95,   64) = Input_1.read();
  test_instance(63,   32) = Input_1.read();
  test_instance(31,    0) = Input_1.read();
  Output_1.write(test_instance(255, 224));
  Output_1.write(test_instance(223, 192));
  Output_1.write(test_instance(191, 160));
  Output_1.write(test_instance(159, 128));
  Output_1.write(test_instance(127,  96));
  Output_1.write(test_instance(95,   64));
  Output_1.write(test_instance(63,   32));
  Output_1.write(test_instance(31,    0));

  int min_distance_list[K_CONST];
  int label_list[K_CONST];

  bit128 input_tmp1, input_tmp2;
  input_tmp1(127,  96) = Input_1.read();
  input_tmp1(95,   64) = Input_1.read();
  input_tmp1(63,   32) = Input_1.read();
  input_tmp1(31,    0) = Input_1.read();
  input_tmp2(127,  96) = Input_1.read();
  input_tmp2(95,   64) = Input_1.read();
  input_tmp2(63,   32) = Input_1.read();
  input_tmp2(31,    0) = Input_1.read();

  for(int i=0; i<K_CONST; i++)
  {
#pragma HLS unroll
	  min_distance_list[i] = (int) input_tmp1(i*32+31, i*32);
	  label_list[i] = (int) input_tmp2(i*32+31, i*32);
  }

  // Initialize the knn set
   SET_KNN_SET: for ( int i = 0; i < K_CONST * 2 ; ++i )
   {
#pragma HLS unroll
     // Note that the max distance is 256
     knn_set[i] = 256;
   }

   TRAINING_LOOP : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
   {
       #pragma HLS pipeline
       LANES : for ( int j = 0; j < 2; j++ )
       {
         #pragma HLS unroll
         WholeDigitType training_instance = training_set[j * NUM_TRAINING / PAR_FACTOR + i];
         update_knn( test_instance, training_instance, &knn_set[j * K_CONST] );
       }
   }

#ifdef DEBUG
   printf("knn_update19");
   for(int i=0; i<6; i++){
   	printf("knn_set[%d]=%d,", i, knn_set[i]);
   }
   printf("\n");
#endif

   //update min_distance_list and label_list according to the new knn_set
   LabelType label_in = 9;
   knn_vote_small(knn_set, min_distance_list, label_list, label_in);

   bit128 output_tmp1, output_tmp2;

   for(int i=0; i<K_CONST; i++)
   {
#pragma HLS unroll
	   output_tmp1(i*32+31, i*32) = min_distance_list[i];
	   output_tmp2(i*32+31, i*32) = label_list[i];
   }


  Output_1.write(output_tmp1(127,96));
  Output_1.write(output_tmp1(95, 64));
  Output_1.write(output_tmp1(63, 32));
  Output_1.write(output_tmp1(31,  0));
  Output_1.write(output_tmp2(127,96));
  Output_1.write(output_tmp2(95, 64));
  Output_1.write(output_tmp2(63, 32));
  Output_1.write(output_tmp2(31,  0));
  return;
}


#define NUM20 20
void update_knn20(hls::stream<ap_uint<32> > & Input_1, hls::stream<ap_uint<32> > & Output_1)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1

static WholeDigitType training_set [NUM_TRAINING / PAR_FACTOR_NEW];
#pragma HLS array_partition variable=training_set block factor=2 dim=0

static WholeDigitType test_instance;


static int knn_set[K_CONST*2];
#pragma HLS array_partition variable=knn_set complete dim=0

WholeDigitType data_temp;
static int index = 0;

if (index == 0)
{
	  //Store the local training set
	  STORE_LOCAL: for(int i = 0; i < NUM_TRAINING / PAR_FACTOR_NEW; i++)
	  {
#pragma HLS pipeline
		training_set[i].range(255, 224) =Input_1.read();
		training_set[i].range(223, 192) =Input_1.read();
		training_set[i].range(191, 160) =Input_1.read();
		training_set[i].range(159, 128) =Input_1.read();
		training_set[i].range(127,  96) =Input_1.read();
		training_set[i].range(95,   64) =Input_1.read();
		training_set[i].range(63,   32) =Input_1.read();
		training_set[i].range(31,    0) =Input_1.read();
	  }

	  Output_1.write(2001);
	  index = 1;
}


  test_instance(255, 224) = Input_1.read();
  test_instance(223, 192) = Input_1.read();
  test_instance(191, 160) = Input_1.read();
  test_instance(159, 128) = Input_1.read();
  test_instance(127,  96) = Input_1.read();
  test_instance(95,   64) = Input_1.read();
  test_instance(63,   32) = Input_1.read();
  test_instance(31,    0) = Input_1.read();
  //Output_1.write(test_instance(255, 128));
  //Output_1.write(test_instance(127, 0));

  int min_distance_list[K_CONST];
  int label_list[K_CONST];

  bit128 input_tmp1, input_tmp2;
  input_tmp1(127,  96) = Input_1.read();
  input_tmp1(95,   64) = Input_1.read();
  input_tmp1(63,   32) = Input_1.read();
  input_tmp1(31,    0) = Input_1.read();
  input_tmp2(127,  96) = Input_1.read();
  input_tmp2(95,   64) = Input_1.read();
  input_tmp2(63,   32) = Input_1.read();
  input_tmp2(31,    0) = Input_1.read();

  for(int i=0; i<K_CONST; i++)
  {
#pragma HLS unroll
	  min_distance_list[i] = (int) input_tmp1(i*32+31, i*32);
	  label_list[i] = (int) input_tmp2(i*32+31, i*32);
  }

  // Initialize the knn set
   SET_KNN_SET: for ( int i = 0; i < K_CONST * 2 ; ++i )
   {
#pragma HLS unroll
     // Note that the max distance is 256
     knn_set[i] = 256;
   }

   TRAINING_LOOP : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
   {
       #pragma HLS pipeline
       LANES : for ( int j = 0; j < 2; j++ )
       {
         #pragma HLS unroll
         WholeDigitType training_instance = training_set[j * NUM_TRAINING / PAR_FACTOR + i];
         update_knn( test_instance, training_instance, &knn_set[j * K_CONST] );
       }
   }


   //update min_distance_list and label_list according to the new knn_set
   LabelType label_in = 9;
   knn_vote_small(knn_set, min_distance_list, label_list, label_in);

#ifdef DEBUG
   printf("knn_update20");
   for(int i=0; i<6; i++){
   	printf("knn_set[%d]=%d,", i, knn_set[i]);
   }
   printf("\n");

   printf("lable_list\n");
  	for(int i=0; i<K_CONST; i++)
  	{
  #pragma HLS unroll
  	  label_list[i] = (int) input_tmp2(i*32+31, i*32);
  	  printf("%d,", label_list[i]);
      }
  	printf("\n");

  	printf("min_distance_list\n");
  	for(int i=0; i<K_CONST; i++)
  	{
  #pragma HLS unroll
  	  min_distance_list[i] = (int) input_tmp1(i*32+31, i*32);
  	  printf("%d,", min_distance_list[i]);
      }
  	printf("\n");
#endif


   bit32 output_tmp1;
   LabelType result = knn_vote_final(label_list);

   output_tmp1(7,0) = result;
   output_tmp1(31,8) = 0;
   Output_1.write(output_tmp1);

  return;
}


void DigitRec2(hls::stream<ap_uint<32> > & Input_1, hls::stream<ap_uint<32> > & Output_1)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1

	bit128 input_tmp1, input_tmp2;
	int min_distance_list[3];
	int  label_list[3];

	hls::stream<ap_uint<32> > knn_out1("knn_out1");
	hls::stream<ap_uint<32> > knn_out2("knn_out2");
	hls::stream<ap_uint<32> > knn_out3("knn_out3");
	hls::stream<ap_uint<32> > knn_out4("knn_out4");
	hls::stream<ap_uint<32> > knn_out5("knn_out5");
	hls::stream<ap_uint<32> > knn_out6("knn_out6");
	hls::stream<ap_uint<32> > knn_out7("knn_out7");
	hls::stream<ap_uint<32> > knn_out8("knn_out8");
	hls::stream<ap_uint<32> > knn_out9("knn_out9");
	hls::stream<ap_uint<32> > knn_out10("knn_out10");
	hls::stream<ap_uint<32> > knn_out11("knn_out11");
	hls::stream<ap_uint<32> > knn_out12("knn_out12");
	hls::stream<ap_uint<32> > knn_out13("knn_out13");
	hls::stream<ap_uint<32> > knn_out14("knn_out14");
	hls::stream<ap_uint<32> > knn_out15("knn_out15");
	hls::stream<ap_uint<32> > knn_out16("knn_out16");
	hls::stream<ap_uint<32> > knn_out17("knn_out17");
	hls::stream<ap_uint<32> > knn_out18("knn_out18");
	hls::stream<ap_uint<32> > knn_out19("knn_out19");
	hls::stream<ap_uint<32> > knn_out20("knn_out20");


	update_knn1(Input_1, knn_out1);
	update_knn2(knn_out1, knn_out2);
	update_knn3(knn_out2, knn_out3);
	update_knn4(knn_out3, knn_out4);
	update_knn5(knn_out4, knn_out5);
	update_knn6(knn_out5, knn_out6);
	update_knn7(knn_out6, knn_out7);
	update_knn8(knn_out7, knn_out8);
	update_knn9(knn_out8, knn_out9);
	update_knn10(knn_out9, knn_out10);
	update_knn11(knn_out10, knn_out11);
	update_knn12(knn_out11, knn_out12);
	update_knn13(knn_out12, knn_out13);
	update_knn14(knn_out13, knn_out14);
	update_knn15(knn_out14, knn_out15);
	update_knn16(knn_out15, knn_out16);
	update_knn17(knn_out16, knn_out17);
	update_knn18(knn_out17, knn_out18);
	update_knn19(knn_out18, knn_out19);
	update_knn20(knn_out19, Output_1);


	for(int i=0; i<2000-1; i++)
	{

		update_knn1(Input_1, knn_out1);
		update_knn2(knn_out1, knn_out2);
		update_knn3(knn_out2, knn_out3);
		update_knn4(knn_out3, knn_out4);
		update_knn5(knn_out4, knn_out5);
		update_knn6(knn_out5, knn_out6);
		update_knn7(knn_out6, knn_out7);
		update_knn8(knn_out7, knn_out8);
		update_knn9(knn_out8, knn_out9);
		update_knn10(knn_out9, knn_out10);
		update_knn11(knn_out10, knn_out11);
		update_knn12(knn_out11, knn_out12);
		update_knn13(knn_out12, knn_out13);
		update_knn14(knn_out13, knn_out14);
		update_knn15(knn_out14, knn_out15);
		update_knn16(knn_out15, knn_out16);
		update_knn17(knn_out16, knn_out17);
		update_knn18(knn_out17, knn_out18);
		update_knn19(knn_out18, knn_out19);
		update_knn20(knn_out19, Output_1);
	}

	printf("We can run without hanging\n");

}

void update_knn2_backup(hls::stream<ap_uint<128> > & Input_1, hls::stream<ap_uint<128> > & Output_1)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1

#pragma HLS inline

static WholeDigitType training_set [NUM_TRAINING / PAR_FACTOR_NEW];
#pragma HLS array_partition variable=training_set block factor=2 dim=0

static WholeDigitType test_instance;


int knn_set1[K_CONST];
#pragma HLS array_partition variable=knn_set1 complete dim=0

int knn_set2[K_CONST];
#pragma HLS array_partition variable=knn_set2 complete dim=0

int knn_set[K_CONST*2];
#pragma HLS array_partition variable=knn_set complete dim=0


WholeDigitType data_temp;
static int index = 0;



  if (index == 0)
  {
	  //Store the local training set
	  STORE_LOCAL: for(int i = 0; i < NUM_TRAINING / PAR_FACTOR_NEW; i++)
	  {
#pragma HLS pipeline
		training_set[i].range(255, 128) =Input_1.read();
		training_set[i].range(127, 0) =Input_1.read();
	  }

	  //Transit the training sets for other pages
	  TRANSFER_LOOP: for(int i = 0; i < NUM_TRAINING / PAR_FACTOR_NEW * (PAR_FACTOR_NEW - NUM2); i++)
	  {
#pragma HLS pipeline
		data_temp.range(255, 128) =Input_1.read();
		data_temp.range(127, 0) =Input_1.read();
		Output_1.write(data_temp.range(255, 128));
		Output_1.write(data_temp.range(127, 0));
	  }

	  index = 1;
  }


  test_instance(255, 128) = Input_1.read();
  test_instance(127, 0  ) = Input_1.read();
  Output_1.write(test_instance(255, 128));
  Output_1.write(test_instance(127, 0));

  int min_distance_list[K_CONST];
  int label_list[K_CONST];

  bit128 input_tmp1, input_tmp2;
  input_tmp1 = Input_1.read();
  input_tmp2 = Input_1.read();

  for(int i=0; i<K_CONST; i++)
  {
#pragma HLS unroll
	  min_distance_list[i] = (int) input_tmp1(i*32+31, i*32);
	  label_list[i] = (int) input_tmp2(i*32+31, i*32);
  }

  // Initialize the knn set
   SET_KNN_SET12: for ( int i = 0; i < K_CONST; ++i )
   {
#pragma HLS unroll
     // Note that the max distance is 256
     knn_set1[i] = 256;
     knn_set2[i] = 256;
   }

   // Initialize the knn set
    SET_KNN_SET: for ( int i = 0; i < K_CONST * 2 ; ++i )
    {
 #pragma HLS unroll
      // Note that the max distance is 256
      knn_set[i] = 256;
    }


   TRAINING_LOOP : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
   {
       #pragma HLS pipeline
       //LANES : for ( int j = 0; j < 2; j++ )
       //{
         //#pragma HLS unroll
         WholeDigitType training_instance1 = training_set[i];
         update_knn( test_instance, training_instance1, &knn_set1[0] );
         WholeDigitType training_instance2 = training_set[NUM_TRAINING / PAR_FACTOR + i];
         update_knn( test_instance, training_instance2, &knn_set2[0] );
       //}
   }

   // update the knn set
    UPDATE_KNN_SET: for ( int i = 0; i < K_CONST; ++i )
    {
 #pragma HLS unroll
      // Note that the max distance is 256
      knn_set[i] = knn_set1[i];
      knn_set[i+K_CONST] = knn_set2[i];
    }


#ifdef DEBUG
   printf("knn_update2");
   for(int i=0; i<6; i++){
   	printf("knn_set[%d]=%d,", i, knn_set[i]);
   }
   printf("\n");
#endif





   //update min_distance_list and label_list according to the new knn_set
   LabelType label_in = 1;
   knn_vote_small(knn_set, min_distance_list, label_list, label_in);

   bit128 output_tmp1, output_tmp2;

   for(int i=0; i<K_CONST; i++)
   {
#pragma HLS unroll
	   output_tmp1(i*32+31, i*32) = min_distance_list[i];
	   output_tmp2(i*32+31, i*32) = label_list[i];
   }


  Output_1.write(output_tmp1);
  Output_1.write(output_tmp2);
  return;
}

