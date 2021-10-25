/*===============================================================*/
/*                                                               */
/*                       3d_rendering.cpp                        */
/*                                                               */
/*      Main host function for the 3D Rendering application.     */
/*                                                               */
/*===============================================================*/

// standard C/C++ headers
#include <cstdio>
#include <cstdlib>
#include <getopt.h>
#include <string>
#include <time.h>
#include <sys/time.h>
#define SDSOC
#ifdef OCL
  // harness headers
  #include "CLWorld.h"
  #include "CLKernel.h"
  #include "CLMemObj.h"
  // harness namespace
  using namespace rosetta;
#endif

#ifdef SDSOC
  // sdsoc headers
  //#include "sds_lib.h"
  // hardware function declaration
  #include "../sdsoc/rendering_new.h"
#endif

#ifdef SW
  # include "../sw/rendering_sw.h"
#endif

// other headers
#include "utils.h"
#include "typedefs.h"
#include "check_result.h"

// data
#include "input_data.h"


int main(int argc, char ** argv)
{
  printf("3D Rendering Application\n");
  hls::stream<ap_uint<32> > Input_1("top_input");
  hls::stream<ap_uint<32> > Output_1("top_output");
  #ifdef OCL
    // parse command line arguments for opencl version
    std::string kernelFile("");
    parse_sdaccel_command_line_args(argc, argv, kernelFile);
  #endif
  // sdsoc and sw versions have no additional command line arguments

  // for this benchmark, data is included in array triangle_3ds

  // timers
  struct timeval start, end;

  // opencl version host code
  #ifdef OCL

    // create space for input and output
    bit32* input  = new bit32[3 * NUM_3D_TRI];
    bit32* output = new bit32[NUM_FB];

    // pack input data for better performance
    for ( int i = 0; i < NUM_3D_TRI; i ++)
    {
      input[3*i](7,0)     = triangle_3ds[i].x0;
      input[3*i](15,8)    = triangle_3ds[i].y0;
      input[3*i](23,16)   = triangle_3ds[i].z0;
      input[3*i](31,24)   = triangle_3ds[i].x1;
      input[3*i+1](7,0)   = triangle_3ds[i].y1;
      input[3*i+1](15,8)  = triangle_3ds[i].z1;
      input[3*i+1](23,16) = triangle_3ds[i].x2;
      input[3*i+1](31,24) = triangle_3ds[i].y2;
      input[3*i+2](7,0)   = triangle_3ds[i].z2;
      input[3*i+2](31,8)  = 0;
    }

    // create OpenCL world
    CLWorld rendering_world = CLWorld(TARGET_DEVICE, CL_DEVICE_TYPE_ACCELERATOR);

    // add the bitstream file
    rendering_world.addProgram(kernelFile);

    // create kernels
    // this kernel is written in C++
    CLKernel Rendering(rendering_world.getContext(), rendering_world.getProgram(), "rendering", rendering_world.getDevice());

    // create mem objects
    CLMemObj input_mem ( (void*)input,  sizeof(bit32), 3 * NUM_3D_TRI, CL_MEM_READ_ONLY);
    CLMemObj output_mem( (void*)output, sizeof(bit32), NUM_FB,         CL_MEM_WRITE_ONLY);

    // start timer
    gettimeofday(&start, 0);

    // add them to the world
    // added in sequence, each of them can be referenced by an index
    rendering_world.addMemObj(input_mem);
    rendering_world.addMemObj(output_mem);

    // set work size
    int global_size[3] = {1, 1, 1};
    int local_size[3] = {1, 1, 1};
    Rendering.set_global(global_size);
    Rendering.set_local(local_size);

    // add them to the world
    rendering_world.addKernel(Rendering);

    // set kernel arguments
    rendering_world.setMemKernelArg(0, 0, 0);
    rendering_world.setMemKernelArg(0, 1, 1);

    // run!
    rendering_world.runKernels();

    // read the data back
    rendering_world.readMemObj(1);

    // end timer
    gettimeofday(&end, 0);
  #endif

  #ifdef SDSOC
    // create space for input and output
    bit128 input_tmp;
    bit32 input[3 * NUM_3D_TRI];
    bit32 output[NUM_FB];

    // pack input data for better performance
    for ( int i = 0; i < NUM_3D_TRI; i++)
    {
        input_tmp(7,   0) = triangle_3ds[i].x0;
        input_tmp(15,  8) = triangle_3ds[i].y0;
        input_tmp(23, 16) = triangle_3ds[i].z0;
        input_tmp(31, 24) = triangle_3ds[i].x1;
        input_tmp(39, 32) = triangle_3ds[i].y1;
        input_tmp(47, 40) = triangle_3ds[i].z1;
        input_tmp(55, 48) = triangle_3ds[i].x2;
        input_tmp(63, 56) = triangle_3ds[i].y2;
        input_tmp(71, 64) = triangle_3ds[i].z2;
        input_tmp(127,72)  = 0;
        //Input_1.write(input_tmp);
    }

    data_gen(Input_1);

    // run hardware function and time it

    //gettimeofday(&start, 0);
    //unsigned long long clock = sds_clock_counter();
    rendering_m(Input_1, Output_1);
    //clock = sds_clock_counter() - clock;
    //gettimeofday(&end, 0);
    bit32 tmp;
    for ( int i = 0; i < NUM_FB; i++)
    {
      tmp = Output_1.read();
      output[i]= tmp(31, 0);
    }

  #endif

  #ifdef SW
    // output
    bit8 output[MAX_X][MAX_Y];
    // run and time sw function
    gettimeofday(&start, 0);
    rendering_sw(triangle_3ds, output);
    gettimeofday(&end, 0);
  #endif

  // check results
  printf("Checking results:\n");
  check_results(output);

  // print time
  //long long elapsed = (end.tv_sec - start.tv_sec) * 1000000LL + end.tv_usec - start.tv_usec;
  //long long elapsed = clock / 1199880;
  //printf("elapsed time: %lld ms\n", elapsed);

  // cleanup
  #ifdef OCL
    rendering_world.releaseWorld();
    delete []input;
    delete []output;
  #endif


  return EXIT_SUCCESS;

}
