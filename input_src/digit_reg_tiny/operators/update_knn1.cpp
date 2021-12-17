#include "../host/typedefs.h"

static int popcount(WholeDigitType x)
{
  // most straightforward implementation
  // actually not bad on FPGA
  int cnt = 0;
  for (int i = 0; i < 256; i ++ )
  {
#pragma HLS unroll factor=4
    cnt = cnt + x(i,i);
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


static void knn_vote_small1( int knn_set1[2 * K_CONST],
		                  int min_distance_list[K_CONST],
						  int label_list[K_CONST],
						  LabelType label_in)
{
  #pragma HLS inline
#pragma HLS array_partition variable=knn_set1 complete dim=0
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
        		(knn_set1[i*K_CONST+j] < min_distance_list[r])
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
          min_distance_list[r-1] = knn_set1[i*K_CONST+j];
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



#define NUM1 1
void update_knn1_sub(hls::stream<ap_uint<32> > & Input_1,
		hls::stream<ap_uint<32> > & Output_1)
{
static WholeDigitType training_set1 [NUM_TRAINING / PAR_FACTOR_NEW];
//#pragma HLS array_partition variable=training_set1 block factor=2 dim=0

static WholeDigitType test_instance1;
bit32 tmp;

static int knn_set1[K_CONST*2];
#pragma HLS array_partition variable=knn_set1 complete dim=0

WholeDigitType data_temp;
static int index1 = 0;

  if (index1 == 0)
  {
	  //Store the local training set
	  STORE_LOCAL: for(int i = 0; i < NUM_TRAINING / PAR_FACTOR_NEW; i++)
	  {
#pragma HLS pipeline
		training_set1[i](255, 224) =Input_1.read();
		training_set1[i](223, 192) =Input_1.read();
		training_set1[i](191, 160) =Input_1.read();
		training_set1[i](159, 128) =Input_1.read();
		training_set1[i](127,  96) =Input_1.read();
		training_set1[i](95,   64) =Input_1.read();
		training_set1[i](63,   32) =Input_1.read();
		training_set1[i](31,    0) =Input_1.read();

	  }

	  //Transit the training sets for other pages
	  TRANSFER_LOOP: for(int i = 0; i < NUM_TRAINING / PAR_FACTOR_NEW * (PAR_FACTOR_NEW / REDUCE_FAC - NUM1); i++)
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

	  index1 = 1;
  }

  index1++;
#ifdef DEBUG
  printf("test set %d\n", index1-2);
#endif



  test_instance1(255, 224) = Input_1.read();
  test_instance1(223, 192) = Input_1.read();
  test_instance1(191, 160) = Input_1.read();
  test_instance1(159, 128) = Input_1.read();
  test_instance1(127,  96) = Input_1.read();
  test_instance1(95,   64) = Input_1.read();
  test_instance1(63,   32) = Input_1.read();
  test_instance1(31,    0) = Input_1.read();
  tmp(31,0) = test_instance1(255, 224);
  Output_1.write(tmp);
  tmp(31,0) = test_instance1(223, 192);
  Output_1.write(tmp);
  tmp(31,0) = test_instance1(191, 160);
  Output_1.write(tmp);
  tmp(31,0) = test_instance1(159, 128);
  Output_1.write(tmp);
  tmp(31,0) = test_instance1(127,  96);
  Output_1.write(tmp);
  tmp(31,0) = test_instance1(95,   64);
  Output_1.write(tmp);
  tmp(31,0) = test_instance1(63,   32);
  Output_1.write(tmp);
  tmp(31,0) = test_instance1(31,    0);
  Output_1.write(tmp);


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
   SET_knn_set1: for ( int i = 0; i < K_CONST * 2 ; ++i )
   {
#pragma HLS unroll
     // Note that the max distance is 256
     knn_set1[i] = 256;
   }

   TRAINING_LOOP : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
   {
       #pragma HLS pipeline
       LANES : for ( int j = 0; j < 2; j++ )
       {
         #pragma HLS unroll
         WholeDigitType training_instance = training_set1[j * NUM_TRAINING / PAR_FACTOR + i];
         update_knn( test_instance1, training_instance, &knn_set1[j * K_CONST] );
       }
   }

#ifdef DEBUG
   printf("knn_update1");
   for(int i=0; i<6; i++){
   	printf("knn_set1[%d]=%d,", i, knn_set1[i]);
   }
   printf("\n");
#endif

   //update min_distance_list and label_list according to the new knn_set1
   LabelType label_in = 0;
   knn_vote_small1(knn_set1, min_distance_list, label_list, label_in);

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


// static int popcount2(WholeDigitType x)
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

// static void update_knn_2( WholeDigitType test_inst, WholeDigitType train_inst, int min_distances[K_CONST] )
// {
//   #pragma HLS inline
// #pragma HLS array_partition variable=min_distances complete dim=0


//   // Compute the difference using XOR
//   WholeDigitType diff = test_inst ^ train_inst;

//   int dist = 0;

//   dist = popcount(diff);

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


static void knn_vote_small2( int knn_set2[2 * K_CONST],
		                  int min_distance_list[K_CONST],
						  int label_list[K_CONST],
						  LabelType label_in)
{
  #pragma HLS inline
#pragma HLS array_partition variable=knn_set2 complete dim=0
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
        		(knn_set2[i*K_CONST+j] < min_distance_list[r])
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
          min_distance_list[r-1] = knn_set2[i*K_CONST+j];
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


#define NUM2 2
void update_knn2_sub(hls::stream<ap_uint<32> > & Input_1, hls::stream<ap_uint<32> > & Output_1)
{

static WholeDigitType training_set2 [NUM_TRAINING / PAR_FACTOR_NEW];
//#pragma HLS array_partition variable=training_set2 block factor=2 dim=0

static WholeDigitType test_instance2;


static int knn_set2[K_CONST*2];
#pragma HLS array_partition variable=knn_set2 complete dim=0

WholeDigitType data_temp;
static int index2 = 0;
bit32 tmp;


  if (index2 == 0)
  {
	  //Store the local training set
	  STORE_LOCAL: for(int i = 0; i < NUM_TRAINING / PAR_FACTOR_NEW; i++)
	  {
#pragma HLS pipeline
			training_set2[i](255, 224) =Input_1.read();
			training_set2[i](223, 192) =Input_1.read();
			training_set2[i](191, 160) =Input_1.read();
			training_set2[i](159, 128) =Input_1.read();
			training_set2[i](127,  96) =Input_1.read();
			training_set2[i](95,   64) =Input_1.read();
			training_set2[i](63,   32) =Input_1.read();
			training_set2[i](31,    0) =Input_1.read();

	  }

	  //Transit the training sets for other pages
	  TRANSFER_LOOP: for(int i = 0; i < NUM_TRAINING / PAR_FACTOR_NEW * (PAR_FACTOR_NEW / REDUCE_FAC - NUM2); i++)
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

	  index2 = 1;
  }

  test_instance2(255, 224) = Input_1.read();
  test_instance2(223, 192) = Input_1.read();
  test_instance2(191, 160) = Input_1.read();
  test_instance2(159, 128) = Input_1.read();
  test_instance2(127,  96) = Input_1.read();
  test_instance2(95,   64) = Input_1.read();
  test_instance2(63,   32) = Input_1.read();
  test_instance2(31,    0) = Input_1.read();
  tmp(31,0) = test_instance2(255, 224);
  Output_1.write(tmp);
  tmp(31,0) = test_instance2(223, 192);
  Output_1.write(tmp);
  tmp(31,0) = test_instance2(191, 160);
  Output_1.write(tmp);
  tmp(31,0) = test_instance2(159, 128);
  Output_1.write(tmp);
  tmp(31,0) = test_instance2(127,  96);
  Output_1.write(tmp);
  tmp(31,0) = test_instance2(95,   64);
  Output_1.write(tmp);
  tmp(31,0) = test_instance2(63,   32);
  Output_1.write(tmp);
  tmp(31,0) = test_instance2(31,    0);
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
   SET_knn_set2: for ( int i = 0; i < K_CONST * 2 ; ++i )
   {
#pragma HLS unroll
     // Note that the max distance is 256
     knn_set2[i] = 256;
   }

   TRAINING_LOOP : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
   {
       #pragma HLS pipeline
       LANES : for ( int j = 0; j < 2; j++ )
       {
         #pragma HLS unroll
         WholeDigitType training_instance = training_set2[j * NUM_TRAINING / PAR_FACTOR + i];
         update_knn( test_instance2, training_instance, &knn_set2[j * K_CONST] );
       }
   }

#ifdef DEBUG
   printf("knn_update3");
   for(int i=0; i<6; i++){
   	printf("knn_set2[%d]=%d,", i, knn_set2[i]);
   }
   printf("\n");
#endif

   //update min_distance_list and label_list according to the new knn_set2
   LabelType label_in = 1;
   knn_vote_small2(knn_set2, min_distance_list, label_list, label_in);

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

void update_knn1(hls::stream<ap_uint<32> > & Input_1, hls::stream<ap_uint<32> > & Output_1)
{
#pragma HLS INTERFACE axis register port=Input_1
#pragma HLS INTERFACE axis register port=Output_1
#pragma HLS allocation function instances=popcount limit=2
#pragma HLS allocation function instances=update_knn limit=2

hls::stream<ap_uint<32> > knn_out1("knn_out1");
#pragma HLS STREAM variable=knn_out1 depth=1024

#pragma HLS DATAFLOW
update_knn1_sub(Input_1, knn_out1);
update_knn2_sub(knn_out1, Output_1);

return;
}