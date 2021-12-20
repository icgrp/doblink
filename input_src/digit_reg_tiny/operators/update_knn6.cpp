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

static void knn_vote_small10( int knn_set10[2 * K_CONST],
		                  int min_distance_list[K_CONST],
						  int label_list[K_CONST],
						  LabelType label_in)
{
  #pragma HLS inline
#pragma HLS array_partition variable=knn_set10 complete dim=0
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
        		(knn_set10[i*K_CONST+j] < min_distance_list[r])
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
          min_distance_list[r-1] = knn_set10[i*K_CONST+j];
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

static LabelType knn_vote_final10(int label_list[K_CONST])
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



#define NUM10 10
void update_knn10_sub(hls::stream<ap_uint<32> > & Input_1, hls::stream<ap_uint<32> > & Output_1)
{

static WholeDigitType training_set10 [NUM_TRAINING / PAR_FACTOR_NEW];
//#pragma HLS array_partition variable=training_set10 block factor=2 dim=0

static WholeDigitType test_instance10;


static int knn_set10[K_CONST*2];
#pragma HLS array_partition variable=knn_set10 complete dim=0

WholeDigitType data_temp;
static int index10 = 0;

if (index10 == 0)
{
	  //Store the local training set
	  STORE_LOCAL: for(int i = 0; i < NUM_TRAINING / PAR_FACTOR_NEW; i++)
	  {

		training_set10[i](255, 224) =Input_1.read();
		training_set10[i](223, 192) =Input_1.read();
		training_set10[i](191, 160) =Input_1.read();
		training_set10[i](159, 128) =Input_1.read();
		training_set10[i](127,  96) =Input_1.read();
		training_set10[i](95,   64) =Input_1.read();
		training_set10[i](63,   32) =Input_1.read();
		training_set10[i](31,    0) =Input_1.read();

	  }

	  Output_1.write(2001);
	  index10 = 1;
}


 // for(int j=255; j>0; j=j-32){
//	  test_instance10(j, j-31) =Input_1.read();
  //}


  test_instance10(255, 224) = Input_1.read();
  test_instance10(223, 192) = Input_1.read();
  test_instance10(191, 160) = Input_1.read();
  test_instance10(159, 128) = Input_1.read();
  test_instance10(127,  96) = Input_1.read();
  test_instance10(95,   64) = Input_1.read();
  test_instance10(63,   32) = Input_1.read();
  test_instance10(31,    0) = Input_1.read();

  //Output_1.write(test_instance10(255, 128));
  //Output_1.write(test_instance10(127, 0));

  int min_distance_list[K_CONST];
  int label_list[K_CONST];

  bit128 input_tmp1, input_tmp2;

  //for(int j=127; j>0; j=j-32){
	//  input_tmp1(j,  j-31) = Input_1.read();
  //}

  input_tmp1(127,  96) = Input_1.read();
  input_tmp1(95,   64) = Input_1.read();
  input_tmp1(63,   32) = Input_1.read();
  input_tmp1(31,    0) = Input_1.read();


  //for(int j=127; j>0; j=j-32){
//	  input_tmp2(j,  j-31) = Input_1.read();
  //}

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
   SET_knn_set10: for ( int i = 0; i < K_CONST * 2 ; ++i )
   {
#pragma HLS unroll
     // Note that the max distance is 256
     knn_set10[i] = 256;
   }

   TRAINING_LOOP : for ( int i = 0; i < NUM_TRAINING / PAR_FACTOR; ++i )
   {
       LANES : for ( int j = 0; j < 2; j++ )
       {
         WholeDigitType training_instance = training_set10[j * NUM_TRAINING / PAR_FACTOR + i];
         update_knn( test_instance10, training_instance, &knn_set10[j * K_CONST] );
       }
   }


   //update min_distance_list and label_list according to the new knn_set10
   LabelType label_in = 9;
   knn_vote_small10(knn_set10, min_distance_list, label_list, label_in);

#ifdef DEBUG
   printf("knn_update20");
   for(int i=0; i<6; i++){
   	printf("knn_set10[%d]=%d,", i, knn_set10[i]);
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
   LabelType result = knn_vote_final10(label_list);

   output_tmp1(7,0) = result;
   output_tmp1(31,8) = 0;
   Output_1.write(output_tmp1);

  return;
}

void update_knn6(hls::stream<ap_uint<32> > & Input_1, hls::stream<ap_uint<32> > & Output_1)
{
#pragma HLS INTERFACE axis register port=Input_1
#pragma HLS INTERFACE axis register port=Output_1

#pragma HLS allocation function instances=popcount limit=2
#pragma HLS allocation function instances=update_knn limit=2

update_knn10_sub(Input_1, Output_1);

return;
}