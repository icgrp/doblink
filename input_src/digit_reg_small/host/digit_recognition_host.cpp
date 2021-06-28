/*===============================================================*/
/*                                                               */
/*                    digit_recognition.cpp                      */
/*                                                               */
/*   Main host function for the Digit Recognition application.   */
/*                                                               */
/*===============================================================*/

// standard C/C++ headers
#include <cstdio>
#include <cstdlib>
#include <getopt.h>
#include <string>
#include <time.h>
#include <sys/time.h>
#include <hls_stream.h>
#define SDSOC


#ifdef SDSOC
  // sdsoc headers
//  #include "sds_lib.h"
  // hardware function declaration
  #include "../host/top.h"
#endif

// other headers
#include "utils.h"
#include "typedefs.h"
#include "check_result.h"

// data
#include "training_data.h"
#include "testing_data.h"



int main(int argc, char ** argv)
{
  printf("Digit Recognition Application\n");

  #ifdef OCL
    // parse command line arguments for opencl version
    std::string kernelFile("");
    parse_sdaccel_command_line_args(argc, argv, kernelFile);
  #endif
  // sw and sdsoc version have no additional command line arguments

  // for this benchmark, data is already included in arrays:
  //   training_data: contains 18000 training samples, with 1800 samples for each digit class
  //   testing_data:  contains 2000 test samples
  //   expected:      contains labels for the test samples

  // timers
  struct timeval start, end;

  // sdsoc version host code
  #ifdef SDSOC
    // allocate space for hardware function
    WholeDigitType* training_in0 = (WholeDigitType*)malloc(sizeof(WholeDigitType) * NUM_TRAINING / 2);
    WholeDigitType* training_in1 = (WholeDigitType*)malloc(sizeof(WholeDigitType) * NUM_TRAINING / 2);
    WholeDigitType* test_in      = (WholeDigitType*)malloc(sizeof(WholeDigitType) * NUM_TEST);
  
    hls::stream<ap_uint<32> > Input_1("main_input");
    hls::stream<ap_uint<32> > Output_1("main_output");

    // pack the data into a wide datatype
    for (int i = 0; i < NUM_TRAINING / 2; i ++ )
    {
      training_in0[i].range(63 , 0  ) = training_data[i*DIGIT_WIDTH+0];
      training_in0[i].range(127, 64 ) = training_data[i*DIGIT_WIDTH+1];
      training_in0[i].range(191, 128) = training_data[i*DIGIT_WIDTH+2];
      training_in0[i].range(255, 192) = training_data[i*DIGIT_WIDTH+3];
    }
    for (int i = 0; i < NUM_TRAINING / 2; i ++ )
    {
      training_in1[i].range(63 , 0  ) = training_data[(NUM_TRAINING / 2 + i)*DIGIT_WIDTH+0];
      training_in1[i].range(127, 64 ) = training_data[(NUM_TRAINING / 2 + i)*DIGIT_WIDTH+1];
      training_in1[i].range(191, 128) = training_data[(NUM_TRAINING / 2 + i)*DIGIT_WIDTH+2];
      training_in1[i].range(255, 192) = training_data[(NUM_TRAINING / 2 + i)*DIGIT_WIDTH+3];
    }
  
    for (int i = 0; i < NUM_TEST; i ++ )
    {
      test_in[i].range(63 , 0  ) = testing_data[i*DIGIT_WIDTH+0];
      test_in[i].range(127, 64 ) = testing_data[i*DIGIT_WIDTH+1];
      test_in[i].range(191, 128) = testing_data[i*DIGIT_WIDTH+2];
      test_in[i].range(255, 192) = testing_data[i*DIGIT_WIDTH+3];
    }

    // create space for result
    LabelType* result = (LabelType*)malloc(sizeof(LabelType) * NUM_TEST);

    /*
    // prepare for input stream
    //Input_1.write(0);
    for (int i = 0; i < NUM_TRAINING / 2 / REDUCE_FAC; i ++){
    	Input_1.write(training_in0[REDUCE_FAC*i].range(255, 224));
    	printf("0x%08x,\n", (unsigned int) training_in0[REDUCE_FAC*i].range(255, 224));
    	Input_1.write(training_in0[REDUCE_FAC*i].range(223, 192));
    	printf("0x%08x,\n", (unsigned int) training_in0[REDUCE_FAC*i].range(223, 192));
    	Input_1.write(training_in0[REDUCE_FAC*i].range(191, 160));
    	printf("0x%08x,\n", (unsigned int) training_in0[REDUCE_FAC*i].range(191, 160));
    	Input_1.write(training_in0[REDUCE_FAC*i].range(159, 128));
    	printf("0x%08x,\n", (unsigned int) training_in0[REDUCE_FAC*i].range(159, 128));
    	Input_1.write(training_in0[REDUCE_FAC*i].range(127,  96));
    	printf("0x%08x,\n", (unsigned int) training_in0[REDUCE_FAC*i].range(127,  96));
    	Input_1.write(training_in0[REDUCE_FAC*i].range(95,   64));
    	printf("0x%08x,\n", (unsigned int) training_in0[REDUCE_FAC*i].range(95,   64));
    	Input_1.write(training_in0[REDUCE_FAC*i].range(63,   32));
    	printf("0x%08x,\n", (unsigned int) training_in0[REDUCE_FAC*i].range(63,   32));
    	Input_1.write(training_in0[REDUCE_FAC*i].range(31,   0));
    	printf("0x%08x,\n", (unsigned int) training_in0[REDUCE_FAC*i].range(31,    0));

    }

    for (int i = 0; i < NUM_TRAINING / 2 / REDUCE_FAC; i ++){
    	Input_1.write(training_in1[REDUCE_FAC*i].range(255, 224));
    	printf("0x%08x,\n", (unsigned int) training_in1[REDUCE_FAC*i].range(255, 224));
    	Input_1.write(training_in1[REDUCE_FAC*i].range(223, 192));
    	printf("0x%08x,\n", (unsigned int) training_in1[REDUCE_FAC*i].range(223, 192));
    	Input_1.write(training_in1[REDUCE_FAC*i].range(191, 160));
    	printf("0x%08x,\n", (unsigned int) training_in1[REDUCE_FAC*i].range(191, 160));
    	Input_1.write(training_in1[REDUCE_FAC*i].range(159, 128));
    	printf("0x%08x,\n", (unsigned int) training_in1[REDUCE_FAC*i].range(159, 128));
    	Input_1.write(training_in1[REDUCE_FAC*i].range(127,  96));
    	printf("0x%08x,\n", (unsigned int) training_in1[REDUCE_FAC*i].range(127,  96));
    	Input_1.write(training_in1[REDUCE_FAC*i].range(95,   64));
    	printf("0x%08x,\n", (unsigned int) training_in1[REDUCE_FAC*i].range(95,   64));
    	Input_1.write(training_in1[REDUCE_FAC*i].range(63,   32));
    	printf("0x%08x,\n", (unsigned int) training_in1[REDUCE_FAC*i].range(63,   32));
    	Input_1.write(training_in1[REDUCE_FAC*i].range(31,   0));
    	printf("0x%08x,\n", (unsigned int) training_in1[REDUCE_FAC*i].range(31,    0));
	}

    for (int i = 0; i < NUM_TEST; i ++){
		Input_1.write(test_in[i].range(255, 224));
		printf("0x%08x,\n", (unsigned int) test_in[i].range(255, 224));
		Input_1.write(test_in[i].range(223, 192));
		printf("0x%08x,\n", (unsigned int) test_in[i].range(223, 192));
		Input_1.write(test_in[i].range(191, 160));
		printf("0x%08x,\n", (unsigned int) test_in[i].range(191, 160));
		Input_1.write(test_in[i].range(159, 128));
		printf("0x%08x,\n", (unsigned int) test_in[i].range(159, 128));
		Input_1.write(test_in[i].range(127,  96));
		printf("0x%08x,\n", (unsigned int) test_in[i].range(127,  96));
		Input_1.write(test_in[i].range(95,   64));
		printf("0x%08x,\n", (unsigned int) test_in[i].range(95,   64));
		Input_1.write(test_in[i].range(63,   32));
		printf("0x%08x,\n", (unsigned int) test_in[i].range(63,   32));
		Input_1.write(test_in[i].range(31,    0));
		printf("0x%08x,\n", (unsigned int) test_in[i].range(31,    0));
	}
    */


    data_gen(Input_1);
    // second call: execute
    gettimeofday(&start, NULL);
    //DigitRec(training_in1, test_in, result, 1);
    top(Input_1, Output_1);
    gettimeofday(&end, NULL);
  #endif

  // sw version host code
  #ifdef SW
    // create space for the result
    LabelType* result = new LabelType[NUM_TEST];

    // software version
    gettimeofday(&start, NULL);
    DigitRec_sw(training_data, testing_data, result);
    gettimeofday(&end, NULL);
  #endif
    // get output stream
    int num_result = Output_1.read();
    for(int i = 0; i < NUM_TEST; i ++)
    {
    	bit32 Output_tmp = Output_1.read();
    	result[i] = Output_tmp(7, 0);
    }

  // check results
  printf("Checking results, we should get  1878 / 2000 correct!:\n");
  check_results( result, expected, NUM_TEST );
    
  // print time
  long long elapsed = (end.tv_sec - start.tv_sec) * 1000000LL + end.tv_usec - start.tv_usec;   
  printf("elapsed time: %lld us\n", elapsed);

  // cleanup
  #ifdef OCL
    digit_rec_world.releaseWorld();
    delete []result;
  #endif

  #ifdef SDSOC
    free(training_in0);
    free(training_in1);
    free(test_in);
    free(result);
  #endif

  #ifdef SW
    delete []result;
  #endif

  return EXIT_SUCCESS;

}




