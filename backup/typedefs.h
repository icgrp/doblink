/*===============================================================*/
/*                                                               */
/*                          typedefs.h                           */
/*                                                               */
/*                     Typedefs for the host                     */
/*                                                               */
/*===============================================================*/

#ifndef __TYPEDEFS_H__
#define __TYPEDEFS_H__
#define RISCV
#include "hls_stream.h"
#include "ap_int.h"
// resolution 256x256
const int MAX_X = 256;
const int MAX_Y = 256;

// number of values in frame buffer: 32 bits
const int NUM_FB = MAX_X * MAX_Y / 4;
// dataset information 
const int NUM_3D_TRI = 3192;


#ifndef SW
  // hls header
  // specialized datatypes
  typedef ap_uint<1> bit1;
  typedef ap_uint<2> bit2;
  typedef ap_uint<8> bit8;
  typedef ap_uint<16> bit16;
  typedef ap_uint<32> bit32;
  typedef ap_uint<64> bit64;
  typedef ap_uint<96> bit96;
  typedef ap_uint<128> bit128;
#else
  typedef unsigned char bit8;
  typedef unsigned int bit32;
#endif

// struct: 3D triangle
typedef struct
{
  bit8   x0;
  bit8   y0;
  bit8   z0;
  bit8   x1;
  bit8   y1;
  bit8   z1;
  bit8   x2;
  bit8   y2;
  bit8   z2;
} Triangle_3D;

// struct: 2D triangle
typedef struct
{
  bit8   x0;
  bit8   y0;
  bit8   x1;
  bit8   y1;
  bit8   x2;
  bit8   y2;
  bit8   z;
} Triangle_2D;

// struct: candidate pixels
typedef struct
{
  bit8   x;
  bit8   y;
  bit8   z;
  bit8   color;
} CandidatePixel;

// struct: colored pixel
typedef struct
{
  bit8   x;
  bit8   y;
  bit8   color;
} Pixel;

// dataflow switch

//#include "ap_fixed.h"
const int MAX_HEIGHT = 436;
const int MAX_WIDTH = 1024;
#include "ap_fixed.h"
#include "ap_int.h"
#include "hls_video.h"
#include "hls_stream.h"
typedef ap_uint<32> databus_t;
typedef ap_uint<128> bit128;
typedef ap_uint<160> bit160;

typedef ap_uint<288> widebus_t;
// define these constants so they can be used in pragma
const int max_width = MAX_WIDTH;
const int default_depth = MAX_WIDTH;


// basic typedefs
	//#include "/home/ylxiao/Xilinx/Vivado/2018.3/include/gmp.h"
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
	

typedef struct{
	pixel_t x;
	pixel_t y;
	pixel_t z;
}gradient_t;

typedef struct{
    outer_pixel_t val[6];
}outer_t; 

typedef struct{
    outer_pixel_t val[3];
}outer_half_t;

typedef struct{
    outer_pixel_t val[6];
}tensor_t;

typedef struct{
    outer_pixel_t val[3];
}tensor_half_t;

typedef struct{
    vel_pixel_t x;
    vel_pixel_t y;
}velocity_t;

  // for data packing
  typedef ap_uint<64> frames_t;
  typedef ap_uint<32> stdio_t;


typedef float float_t;















#define SDSOC

// dataset information
const int NUM_FEATURES  = 1024;
const int NUM_SAMPLES   = 5000;
const int NUM_TRAINING  = 4500;
const int NUM_TESTING   = 500;
const int STEP_SIZE     = 60000; 
const int NUM_EPOCHS    = 5;
const int DATA_SET_SIZE = NUM_FEATURES * NUM_SAMPLES;



#ifdef SDSOC
  // embedded platforms have less off-chip bandwidth
  #define VFTYPE_WIDTH  64
  #define VDTYPE_WIDTH  64
#endif

#define PAR_FACTOR 32
#define PAR_FACTOR_DEC 4
// datatypes for accelerator

  // features / parameters
  typedef ap_uint<128> bit128;
  typedef ap_uint<32> bit32;
  #define FTYPE_TWIDTH 32
  #define FTYPE_IWIDTH 13
  typedef ap_fixed<FTYPE_TWIDTH,FTYPE_IWIDTH> FeatureType;
  typedef ap_uint<VFTYPE_WIDTH>               VectorFeatureType;
  const size_t F_VECTOR_SIZE = VFTYPE_WIDTH / FTYPE_TWIDTH;
  // training data
  #define DTYPE_TWIDTH 16
  #define DTYPE_IWIDTH 4
  typedef ap_fixed<DTYPE_TWIDTH,DTYPE_IWIDTH>  DataType;
  typedef ap_uint<VDTYPE_WIDTH>                VectorDataType;
  const size_t D_VECTOR_SIZE = VDTYPE_WIDTH / DTYPE_TWIDTH;
  // label
  #define LTYPE_WIDTH   8
  #define VLTYPE_WIDTH  32
  typedef ap_uint<LTYPE_WIDTH>                 LabelType;
  typedef ap_uint<VLTYPE_WIDTH>                VectorLabelType;
  const size_t L_VECTOR_SIZE = VLTYPE_WIDTH / LTYPE_WIDTH;
  
  // datatypes for the LUT
  #define LUTOUT_TWIDTH     16
  #define LUTOUT_IWIDTH     6
  #define LUTIN_TWIDTH      16
  #define LUTIN_IWIDTH      8
  //typedef ap_ufixed<32, 20> TmpFixed; 
  typedef ap_fixed<32, 20> TmpFixed; 
  typedef ap_uint<LUTIN_TWIDTH> IdxFixed; 
  typedef ap_fixed<LUTIN_TWIDTH, LUTIN_IWIDTH> LutInFixed;
  typedef ap_fixed<LUTOUT_TWIDTH, LUTOUT_IWIDTH> LutOutFixed;



















#define ENABLE_DATAFLOW
#endif
