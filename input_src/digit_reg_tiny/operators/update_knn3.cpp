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


static void knn_vote_small5( int knn_set5[2 * K_CONST],
		                  int min_distance_list[K_CONST],
						  int label_list[K_CONST],
						  LabelType label_in)
{
  #pragma HLS inline
#pragma HLS array_partition variable=knn_set5 complete dim=0
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
        		(knn_set5[i*K_CONST+j] < min_distance_list[r])
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
          min_distance_list[r-1] = knn_set5[i*K_CONST+j];
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


#define NUM5 5
void update_knn5_sub(hls::stream<ap_uint<32> > & Input_1, hls::stream<ap_uint<32> > & Output_1)
{

static WholeDigitType training_set5 [NUM_TRAINING / PAR_FACTOR_NEW];
//#pragma HLS array_partition variable=training_set5 block factor=2 dim=0

static WholeDigitType test_instance5;


static int knn_set5[K_CONST*2];
#pragma HLS array_partition variable=knn_set5 complete dim=0

WholeDigitType data_temp;
static int index5 = 0;
bit32 tmp;


  if (index5 == 0)
  {
	  //Store the local training set
	  STORE_LOCAL: for(int i = 0; i < NUM_TRAINING / PAR_FACTOR_NEW; i++)
	  {
#pragma HLS pipeline
			training_set5[i](255, 224) =Input_1.read();
			training_set5[i](223, 192) =Input_1.read();
			training_set5[i](191, 160) =Input_1.read();
			training_set5[i](159, 128) =Input_1.read();
			training_set5[i](127,  96) =Input_1.read();
			training_set5[i](95,   64) =Input_1.read();
			training_set5[i](63,   32) =Input_1.read();
			training_set5[i](31,    0) =Input_1.read();
	  }

	  //Transit the training sets for other pages
	  TRANSFER_LOOP: for(int i = 0; i < NUM_TRAINING / PAR_FACTOR_NEW * (PAR_FACTOR_NEW / REDUCE_FAC - NUM5); i++)
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

	  index5 = 1;
  }


  test_instance5(255, 224) = Input_1.read();
  test_instance5(223, 192) = Input_1.read();
  test_instance5(191, 160) = Input_1.read();
  test_instance5(159, 128) = Input_1.read();
  test_instance5(127,  96) = Input_1.read();
  test_instance5(95,   64) = Input_1.read();
  test_instance5(63,   32) = Input_1.read();
  test_instance5(31,    0) = Input_1.read();
  tmp(31,0) = test_instance5(255, 224);
  Output_1.write(tmp);
  tmp(31,0) = test_instance5(223, 192);
  Output_1.write(tmp);
  tmp(31,0) = test_instance5(191, 160);
  Output_1.write(tmp);
  tmp(31,0) = test_instance5(159, 128);
  Output_1.write(tmp);
  tmp(31,0) = test_instance5(127,  96);
  Output_1.write(tmp);
  tmp(31,0) = test_instance5(95,   64);
  Output_1.write(tmp);
  tmp(31,0) = test_instance5(63,   32);
  Output_1.write(tmp);
  tmp(31,0) = test_instance5(31,    0);
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
   SET_knn_set5: for ( int i = 0; i < K_CONST * 2 ; ++i )
   {
#pragma HLS unroll
     // Note that the max distance is 256
     knn_set5[i] = 256;
   }

   TRAINING_LOOP : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
   {
       #pragma HLS pipeline II=16
       LANES : for ( int j = 0; j < 2; j++ )
       {
         WholeDigitType training_instance = training_set5[j * NUM_TRAINING / PAR_FACTOR + i];
         update_knn( test_instance5, training_instance, &knn_set5[j * K_CONST] );
       }
   }

#ifdef DEBUG
   printf("knn_update11");
   for(int i=0; i<6; i++){
   	printf("knn_set5[%d]=%d,", i, knn_set5[i]);
   }
   printf("\n");
#endif

   //update min_distance_list and label_list according to the new knn_set5
   LabelType label_in = 4;
   knn_vote_small5(knn_set5, min_distance_list, label_list, label_in);

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

// static int popcount6(WholeDigitType x)
// {
//   // most straightforward implementation
//   // actually not bad on FPGA
//   int cnt = 0;
//   for (int i = 0; i < 256; i ++ )
//   {
// #pragma HLS unroll factor=4
//     cnt = cnt + x(i, i);
//   }
//   return cnt;
// }

// static void update_knn_6( WholeDigitType test_inst, WholeDigitType train_inst, int min_distances[K_CONST] )
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


static void knn_vote_small6( int knn_set6[2 * K_CONST],
		                  int min_distance_list[K_CONST],
						  int label_list[K_CONST],
						  LabelType label_in)
{
  #pragma HLS inline
#pragma HLS array_partition variable=knn_set6 complete dim=0
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
        		(knn_set6[i*K_CONST+j] < min_distance_list[r])
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
          min_distance_list[r-1] = knn_set6[i*K_CONST+j];
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


#define NUM6 6
void update_knn6_sub(hls::stream<ap_uint<32> > & Input_1, hls::stream<ap_uint<32> > & Output_1)
{

static WholeDigitType training_set6 [NUM_TRAINING / PAR_FACTOR_NEW];
//#pragma HLS array_partition variable=training_set6 block factor=2 dim=0

static WholeDigitType test_instance6;


static int knn_set6[K_CONST*2];
#pragma HLS array_partition variable=knn_set6 complete dim=0

WholeDigitType data_temp;
static int index6 = 0;
bit32 tmp;


  if (index6 == 0)
  {
	  //Store the local training set
	  STORE_LOCAL: for(int i = 0; i < NUM_TRAINING / PAR_FACTOR_NEW; i++)
	  {
#pragma HLS pipeline
			training_set6[i](255, 224) =Input_1.read();
			training_set6[i](223, 192) =Input_1.read();
			training_set6[i](191, 160) =Input_1.read();
			training_set6[i](159, 128) =Input_1.read();
			training_set6[i](127,  96) =Input_1.read();
			training_set6[i](95,   64) =Input_1.read();
			training_set6[i](63,   32) =Input_1.read();
			training_set6[i](31,    0) =Input_1.read();
	  }

	  //Transit the training sets for other pages
	  TRANSFER_LOOP: for(int i = 0; i < NUM_TRAINING / PAR_FACTOR_NEW * (PAR_FACTOR_NEW / REDUCE_FAC - NUM6); i++)
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

	  index6 = 1;
  }


  test_instance6(255, 224) = Input_1.read();
  test_instance6(223, 192) = Input_1.read();
  test_instance6(191, 160) = Input_1.read();
  test_instance6(159, 128) = Input_1.read();
  test_instance6(127,  96) = Input_1.read();
  test_instance6(95,   64) = Input_1.read();
  test_instance6(63,   32) = Input_1.read();
  test_instance6(31,    0) = Input_1.read();
  tmp(31,0) = test_instance6(255, 224);
  Output_1.write(tmp);
  tmp(31,0) = test_instance6(223, 192);
  Output_1.write(tmp);
  tmp(31,0) = test_instance6(191, 160);
  Output_1.write(tmp);
  tmp(31,0) = test_instance6(159, 128);
  Output_1.write(tmp);
  tmp(31,0) = test_instance6(127,  96);
  Output_1.write(tmp);
  tmp(31,0) = test_instance6(95,   64);
  Output_1.write(tmp);
  tmp(31,0) = test_instance6(63,   32);
  Output_1.write(tmp);
  tmp(31,0) = test_instance6(31,    0);
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
   SET_knn_set6: for ( int i = 0; i < K_CONST * 2 ; ++i )
   {
#pragma HLS unroll
     // Note that the max distance is 256
     knn_set6[i] = 256;
   }

   TRAINING_LOOP : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
   {
       #pragma HLS pipeline II=16
       LANES : for ( int j = 0; j < 2; j++ )
       {
         WholeDigitType training_instance = training_set6[j * NUM_TRAINING / PAR_FACTOR + i];
         update_knn( test_instance6, training_instance, &knn_set6[j * K_CONST] );
       }
   }

#ifdef DEBUG
   printf("knn_update11");
   for(int i=0; i<6; i++){
   	printf("knn_set6[%d]=%d,", i, knn_set6[i]);
   }
   printf("\n");
#endif

   //update min_distance_list and label_list according to the new knn_set6
   LabelType label_in = 5;
   knn_vote_small6(knn_set6, min_distance_list, label_list, label_in);

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

void update_knn3(hls::stream<ap_uint<32> > & Input_1, hls::stream<ap_uint<32> > & Output_1)
{
#pragma HLS INTERFACE axis register port=Input_1
#pragma HLS INTERFACE axis register port=Output_1
#pragma HLS allocation function instances=popcount limit=2
#pragma HLS allocation function instances=update_knn limit=2

hls::stream<ap_uint<32> > knn_out5("knn_out5");
#pragma HLS STREAM variable=knn_out5 depth=1024

#pragma HLS DATAFLOW
update_knn5_sub(Input_1, knn_out5);
update_knn6_sub(knn_out5, Output_1);

return;
}