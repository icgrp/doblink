/*===============================================================*/
/*                                                               */
/*                          kernel.h                             */
/*                                                               */
/*        Defines types and constants for host function          */
/*                                                               */
/*===============================================================*/

#ifndef __TYPEDEFS_H__
#define __TYPEDEFS_H__
//#include "ap_fixed.h"
const int MAX_HEIGHT = 436;
const int MAX_WIDTH = 1024;
#include "hls_stream.h"
#include "ap_fixed.h"
#define SDSOC
#include <cassert>
#include "/opt/Xilinx/Vivado/2020.2/include/multimediaIps/xf_video_mem.hpp"

// basic typedefs
#ifdef SDSOC
	#include "ap_fixed.h"
	typedef ap_fixed<17,9> input_t;
	typedef ap_fixed<32,13> pixel_t;
	typedef ap_fixed<48,27> outer_pixel_t;
	typedef ap_fixed<96,56> calc_pixel_t;
	typedef ap_fixed<32,13> vel_pixel_t;
	//typedef ap_fixed<16,8> input_t;
        //typedef ap_fixed<32,13> pixel_t;
        //typedef float outer_pixel_t;
	//typedef float calc_pixel_t;
	//typedef float vel_pixel_t;

#endif

typedef struct{
	pixel_t x;
	pixel_t y;
	pixel_t z;
}gradient_t;

typedef struct{
    outer_pixel_t val[6];
}outer_t; 

typedef struct{
    outer_pixel_t val[6];
}tensor_t;

typedef struct{
    vel_pixel_t x;
    vel_pixel_t y;
}velocity_t;

#ifndef SW
  #include "ap_int.h"
  // for data packing
  typedef ap_uint<64> frames_t;
  typedef ap_uint<32> bit32;
#endif

#ifdef OCL
  #include <string>
  // change the target device here
  const std::string TARGET_DEVICE = "xilinx:aws-vu9p-f1:4ddr-xpr-2pr:4.0";
#endif

#endif
