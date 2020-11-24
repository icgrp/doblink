/*===============================================================*/
/*                                                               */
/*                          typedefs.h                           */
/*                                                               */
/*                     Typedefs for the host                     */
/*                                                               */
/*===============================================================*/

#ifndef __TYPEDEFS_H__
#define __TYPEDEFS_H__
#include <hls_stream.h>
#include <ap_int.h>
 typedef ap_uint<128> bit128;
 typedef ap_uint<64> frames_t;
 typedef ap_uint<32> stdio_t;
 typedef ap_uint<32> bit32;

 #define HW
//#include <hls_stream.h>

#ifndef SW
//#include <ap_int.h>
#include <ap_fixed.h>
#endif

// resolution 256x256
const int MAX_X = 256;
const int MAX_Y = 256;

// number of values in frame buffer: 32 bits
const int NUM_FB = MAX_X * MAX_Y / 4;
// dataset information 
const int NUM_3D_TRI = 3192;

#ifdef OCL
  #include <string>
  // target device
  // change here to map to a different device
  const std::string TARGET_DEVICE = "xilinx:aws-vu9p-f1:4ddr-xpr-2pr:4.0";
#endif

#ifndef SW
  // hls header
//  #include "ap_int.h"
  // specialized datatypes
  typedef ap_uint<1> bit1;
  typedef ap_uint<2> bit2;
  typedef ap_uint<8> bit8;
  typedef ap_uint<16> bit16;
  typedef ap_uint<32> bit32;
#else
  typedef unsigned char bit8;
  typedef unsigned short bit16;
  typedef unsigned char bit2;
  typedef unsigned char bit1;
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
#define ENABLE_DATAFLOW
#endif


//#include "ap_fixed.h"
const int MAX_HEIGHT = 436;
const int MAX_WIDTH = 1024;
typedef ap_fixed<17,9> input_t;
typedef ap_fixed<32,13> pixel_t;
typedef ap_fixed<48,27> outer_pixel_t;
typedef ap_fixed<96,56> calc_pixel_t;
typedef ap_fixed<32,13> vel_pixel_t;

typedef ap_uint<160> bit160;

typedef ap_uint<288> widebus_t;

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

typedef ap_uint<32> databus_t;

#include "./gmp.h"

#include "ap_fixed.h"
#include <hls_video.h>


/// macro wrappers for hw sw
#ifdef HW
	#define STREAM hls::stream<ap_uint<32> >
	#define STREAM_READ( stream ) stream.read();
	#define STREAM_WRITE( stream,value ) stream.write(value);
#else
	#define STREAM pr_flow::stream
	#define STREAM_READ( stream )(\
	{							 \
	pr_flow::wide_t temp; 		 \
	stream.read(&temp); 		 \
	temp.lower_32;					 \
	})
	#define STREAM_WRITE( stream,value )(\
	{							 \
	pr_flow::wide_t temp; 		 \
	temp.lower_32 = value;			 \
	temp.upper_32 = 0;			     \
	stream.write(temp); 	 	 \
	})
#endif
