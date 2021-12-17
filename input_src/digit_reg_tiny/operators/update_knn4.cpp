#include "../host/typedefs.h"

static int popcount(WholeDigitType x)
{
  // most straightforward implementation
  // actually not bad on FPGA
  int cnt = 0;
  for (int i = 0; i < 256; i ++ )
  {
#pragma HLS unroll factor=4
    cnt = cnt + x(i, i);
  }
  return cnt;
}

static void update_knn( WholeDigitType test_inst, WholeDigitType train_inst, int min_distances[K_CONST] )
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


static void knn_vote_small7( int knn_set7[2 * K_CONST],
		                  int min_distance_list[K_CONST],
						  int label_list[K_CONST],
						  LabelType label_in)
{
  #pragma HLS inline
#pragma HLS array_partition variable=knn_set7 complete dim=0
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
      #pragma HLS pipeline II=16
      pos = 1000;
      INSERTION_SORT_INNER: for (int r = 0; r < K_CONST; r ++ )
      {
      
        pos = (
        		(knn_set7[i*K_CONST+j] < min_distance_list[r])
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
          min_distance_list[r-1] = knn_set7[i*K_CONST+j];
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


#define NUM7 7
void update_knn7_sub(hls::stream<ap_uint<32> > & Input_1, hls::stream<ap_uint<32> > & Output_1)
{

static WholeDigitType training_set7 [NUM_TRAINING / PAR_FACTOR_NEW];
//#pragma HLS array_partition variable=training_set7 block factor=2 dim=0

static WholeDigitType test_instance7;


static int knn_set7[K_CONST*2];
#pragma HLS array_partition variable=knn_set7 complete dim=0

WholeDigitType data_temp;
static int index7 = 0;
bit32 tmp;


  if (index7 == 0)
  {
	  //Store the local training set
	  STORE_LOCAL: for(int i = 0; i < NUM_TRAINING / PAR_FACTOR_NEW; i++)
	  {
#pragma HLS pipeline
			training_set7[i](255, 224) =Input_1.read();
			training_set7[i](223, 192) =Input_1.read();
			training_set7[i](191, 160) =Input_1.read();
			training_set7[i](159, 128) =Input_1.read();
			training_set7[i](127,  96) =Input_1.read();
			training_set7[i](95,   64) =Input_1.read();
			training_set7[i](63,   32) =Input_1.read();
			training_set7[i](31,    0) =Input_1.read();
	  }

	  //Transit the training sets for other pages
	  TRANSFER_LOOP: for(int i = 0; i < NUM_TRAINING / PAR_FACTOR_NEW * (PAR_FACTOR_NEW / REDUCE_FAC - NUM7); i++)
	  {
#pragma HLS pipeline
			data_temp(255, 224) =Input_1.read();
			data_temp(223, 192) =Input_1.read();
			data_temp(191, 160) =Input_1.read();
			data_temp(159, 128) =Input_1.read();
			data_temp(127,  96) =Input_1.read();
			data_temp(95,   64) =Input_1.read();
			data_temp(63,   32) =Input_1.read();
			data_temp(31,    0) =Input_1.read();
			bit32 tmp;
			tmp(31, 0) = data_temp.range(255, 224);
			Output_1.write(tmp);
			tmp(31, 0) = data_temp.range(223, 192);
			Output_1.write(tmp);
			tmp(31, 0) = data_temp.range(191, 160);
			Output_1.write(tmp);
			tmp(31, 0) = data_temp.range(159, 128);
			Output_1.write(tmp);
			tmp(31, 0) = data_temp.range(127,  96);
			Output_1.write(tmp);
			tmp(31, 0) = data_temp.range(95,   64);
			Output_1.write(tmp);
			tmp(31, 0) = data_temp.range(63,   32);
			Output_1.write(tmp);
			tmp(31, 0) = data_temp.range(31,    0);
			Output_1.write(tmp);
	  }

	  index7 = 1;
  }


  test_instance7(255, 224) = Input_1.read();
  test_instance7(223, 192) = Input_1.read();
  test_instance7(191, 160) = Input_1.read();
  test_instance7(159, 128) = Input_1.read();
  test_instance7(127,  96) = Input_1.read();
  test_instance7(95,   64) = Input_1.read();
  test_instance7(63,   32) = Input_1.read();
  test_instance7(31,    0) = Input_1.read();
  tmp(31,0) = test_instance7(255, 224);
  Output_1.write(tmp);
  tmp(31,0) = test_instance7(223, 192);
  Output_1.write(tmp);
  tmp(31,0) = test_instance7(191, 160);
  Output_1.write(tmp);
  tmp(31,0) = test_instance7(159, 128);
  Output_1.write(tmp);
  tmp(31,0) = test_instance7(127,  96);
  Output_1.write(tmp);
  tmp(31,0) = test_instance7(95,   64);
  Output_1.write(tmp);
  tmp(31,0) = test_instance7(63,   32);
  Output_1.write(tmp);
  tmp(31,0) = test_instance7(31,    0);
  Output_1.write(tmp);

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
   SET_knn_set7: for ( int i = 0; i < K_CONST * 2 ; ++i )
   {
#pragma HLS unroll
     // Note that the max distance is 256
     knn_set7[i] = 256;
   }

   TRAINING_LOOP : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
   {
       #pragma HLS pipeline II=16
       LANES : for ( int j = 0; j < 2; j++ )
       {
         WholeDigitType training_instance = training_set7[j * NUM_TRAINING / PAR_FACTOR + i];
         update_knn( test_instance7, training_instance, &knn_set7[j * K_CONST] );
       }
   }

#ifdef DEBUG
   printf("knn_update11");
   for(int i=0; i<6; i++){
   	printf("knn_set7[%d]=%d,", i, knn_set7[i]);
   }
   printf("\n");
#endif

   //update min_distance_list and label_list according to the new knn_set7
   LabelType label_in = 6;
   knn_vote_small7(knn_set7, min_distance_list, label_list, label_in);

   bit128 output_tmp1, output_tmp2;

   for(int i=0; i<K_CONST; i++)
   {
#pragma HLS unroll
	   output_tmp1(i*32+31, i*32) = min_distance_list[i];
	   output_tmp2(i*32+31, i*32) = label_list[i];
   }


   tmp(31,0) = output_tmp1(127,96);
   Output_1.write(tmp);
   tmp(31,0) = output_tmp1(95, 64);
   Output_1.write(tmp);
   tmp(31,0) = output_tmp1(63, 32);
   Output_1.write(tmp);
   tmp(31,0) = output_tmp1(31,  0);
   Output_1.write(tmp);
   tmp(31,0) = output_tmp2(127,96);
   Output_1.write(tmp);
   tmp(31,0) = output_tmp2(95, 64);
   Output_1.write(tmp);
   tmp(31,0) = output_tmp2(63, 32);
   Output_1.write(tmp);
   tmp(31,0) = output_tmp2(31,  0);
   Output_1.write(tmp);


  return;
}

// static int popcount8(WholeDigitType x)
// {
//   // most straightforward implementation
//   // actually not bad on FPGA
//   int cnt = 0;
//   for (int i = 0; i < 256; i ++ )
//   {
// #pragma HLS unroll
//     cnt = cnt + x(i, i);
//   }
//   return cnt;
// }

// static void update_knn( WholeDigitType test_inst, WholeDigitType train_inst, int min_distances[K_CONST] )
// {
//   #pragma HLS inline
// #pragma HLS array_partition variable=min_distances complete dim=0


//   // Compute the difference using XOR
//   WholeDigitType diff = test_inst ^ train_inst;

//   int dist = 0;

//   dist = popcount8(diff);

//   int max_dist = 0;
//   int max_dist_id = 0;
//   int k = 0;

//   // Find the max distance
//   FIND_MAX_DIST: for ( int k = 0; k < K_CONST; ++k )
//   {
//     if ( min_distances[k] > max_dist )
//     {
//       max_dist = min_distances[k];
//       max_dist_id = k;
//     }
//   }

//   // Replace the entry with the max distance
//   if ( dist < max_dist )
//     min_distances[max_dist_id] = dist;

//   return;
// }


static void knn_vote_small8( int knn_set8[2 * K_CONST],
		                  int min_distance_list[K_CONST],
						  int label_list[K_CONST],
						  LabelType label_in)
{
  #pragma HLS inline
#pragma HLS array_partition variable=knn_set8 complete dim=0
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
      #pragma HLS pipeline II=16
      pos = 1000;
      INSERTION_SORT_INNER: for (int r = 0; r < K_CONST; r ++ )
      {
        pos = (
        		(knn_set8[i*K_CONST+j] < min_distance_list[r])
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
          min_distance_list[r-1] = knn_set8[i*K_CONST+j];
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


#define NUM8 8
void update_knn8_sub(hls::stream<ap_uint<32> > & Input_1, hls::stream<ap_uint<32> > & Output_1)
{

static WholeDigitType training_set8 [NUM_TRAINING / PAR_FACTOR_NEW];
//#pragma HLS array_partition variable=training_set8 block factor=2 dim=0

static WholeDigitType test_instance8;


static int knn_set8[K_CONST*2];
#pragma HLS array_partition variable=knn_set8 complete dim=0

WholeDigitType data_temp;
static int index8 = 0;
bit32 tmp;


  if (index8 == 0)
  {
	  //Store the local training set
	  STORE_LOCAL: for(int i = 0; i < NUM_TRAINING / PAR_FACTOR_NEW; i++)
	  {
#pragma HLS pipeline
			training_set8[i](255, 224) =Input_1.read();
			training_set8[i](223, 192) =Input_1.read();
			training_set8[i](191, 160) =Input_1.read();
			training_set8[i](159, 128) =Input_1.read();
			training_set8[i](127,  96) =Input_1.read();
			training_set8[i](95,   64) =Input_1.read();
			training_set8[i](63,   32) =Input_1.read();
			training_set8[i](31,    0) =Input_1.read();
	  }

	  //Transit the training sets for other pages
	  TRANSFER_LOOP: for(int i = 0; i < NUM_TRAINING / PAR_FACTOR_NEW * (PAR_FACTOR_NEW / REDUCE_FAC - NUM8); i++)
	  {
#pragma HLS pipeline
			data_temp(255, 224) =Input_1.read();
			data_temp(223, 192) =Input_1.read();
			data_temp(191, 160) =Input_1.read();
			data_temp(159, 128) =Input_1.read();
			data_temp(127,  96) =Input_1.read();
			data_temp(95,   64) =Input_1.read();
			data_temp(63,   32) =Input_1.read();
			data_temp(31,    0) =Input_1.read();
			bit32 tmp;
			tmp(31, 0) = data_temp.range(255, 224);
			Output_1.write(tmp);
			tmp(31, 0) = data_temp.range(223, 192);
			Output_1.write(tmp);
			tmp(31, 0) = data_temp.range(191, 160);
			Output_1.write(tmp);
			tmp(31, 0) = data_temp.range(159, 128);
			Output_1.write(tmp);
			tmp(31, 0) = data_temp.range(127,  96);
			Output_1.write(tmp);
			tmp(31, 0) = data_temp.range(95,   64);
			Output_1.write(tmp);
			tmp(31, 0) = data_temp.range(63,   32);
			Output_1.write(tmp);
			tmp(31, 0) = data_temp.range(31,    0);
			Output_1.write(tmp);
	  }

	  index8 = 1;
  }


  test_instance8(255, 224) = Input_1.read();
  test_instance8(223, 192) = Input_1.read();
  test_instance8(191, 160) = Input_1.read();
  test_instance8(159, 128) = Input_1.read();
  test_instance8(127,  96) = Input_1.read();
  test_instance8(95,   64) = Input_1.read();
  test_instance8(63,   32) = Input_1.read();
  test_instance8(31,    0) = Input_1.read();
  tmp(31,0) = test_instance8(255, 224);
  Output_1.write(tmp);
  tmp(31,0) = test_instance8(223, 192);
  Output_1.write(tmp);
  tmp(31,0) = test_instance8(191, 160);
  Output_1.write(tmp);
  tmp(31,0) = test_instance8(159, 128);
  Output_1.write(tmp);
  tmp(31,0) = test_instance8(127,  96);
  Output_1.write(tmp);
  tmp(31,0) = test_instance8(95,   64);
  Output_1.write(tmp);
  tmp(31,0) = test_instance8(63,   32);
  Output_1.write(tmp);
  tmp(31,0) = test_instance8(31,    0);
  Output_1.write(tmp);

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
   SET_knn_set8: for ( int i = 0; i < K_CONST * 2 ; ++i )
   {
#pragma HLS unroll
     // Note that the max distance is 256
     knn_set8[i] = 256;
   }

   TRAINING_LOOP : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
   {
       #pragma HLS pipeline II=16
       LANES : for ( int j = 0; j < 2; j++ )
       {
         WholeDigitType training_instance = training_set8[j * NUM_TRAINING / PAR_FACTOR + i];
         update_knn( test_instance8, training_instance, &knn_set8[j * K_CONST] );
       }
   }

#ifdef DEBUG
   printf("knn_update11");
   for(int i=0; i<6; i++){
   	printf("knn_set8[%d]=%d,", i, knn_set8[i]);
   }
   printf("\n");
#endif

   //update min_distance_list and label_list according to the new knn_set8
   LabelType label_in = 7;
   knn_vote_small8(knn_set8, min_distance_list, label_list, label_in);

   bit128 output_tmp1, output_tmp2;

   for(int i=0; i<K_CONST; i++)
   {
#pragma HLS unroll
	   output_tmp1(i*32+31, i*32) = min_distance_list[i];
	   output_tmp2(i*32+31, i*32) = label_list[i];
   }


   tmp(31,0) = output_tmp1(127,96);
   Output_1.write(tmp);
   tmp(31,0) = output_tmp1(95, 64);
   Output_1.write(tmp);
   tmp(31,0) = output_tmp1(63, 32);
   Output_1.write(tmp);
   tmp(31,0) = output_tmp1(31,  0);
   Output_1.write(tmp);
   tmp(31,0) = output_tmp2(127,96);
   Output_1.write(tmp);
   tmp(31,0) = output_tmp2(95, 64);
   Output_1.write(tmp);
   tmp(31,0) = output_tmp2(63, 32);
   Output_1.write(tmp);
   tmp(31,0) = output_tmp2(31,  0);
   Output_1.write(tmp);


  return;
}

void update_knn4(hls::stream<ap_uint<32> > & Input_1, hls::stream<ap_uint<32> > & Output_1)
{
#pragma HLS INTERFACE axis register port=Input_1
#pragma HLS INTERFACE axis register port=Output_1
#pragma HLS allocation function instances=popcount limit=2
#pragma HLS allocation function instances=update_knn limit=2

hls::stream<ap_uint<32> > knn_out7("knn_out7");
#pragma HLS STREAM variable=knn_out7 depth=1024

#pragma HLS DATAFLOW
update_knn7_sub(Input_1, knn_out7);
update_knn8_sub(knn_out7, Output_1);

return;
}