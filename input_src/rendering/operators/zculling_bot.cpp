#include "../host/typedefs.h"

// struct: 2D triangle
typedef struct
{
  unsigned char x0;
  unsigned char y0;
  unsigned char x1;
  unsigned char y1;
  unsigned char x2;
  unsigned char y2;
  unsigned char z;
} Triangle_2D_new;

typedef struct
{
  unsigned char x;
  unsigned char y;
  unsigned char z;
  unsigned char color;
} CandidatePixel_new;

typedef struct
{
  unsigned char x;
  unsigned char y;
  unsigned char color;
} Pixel_new;


// filter hidden pixels
void zculling_bot (
		hls::stream<ap_uint<32> > & Input_1,
		hls::stream<ap_uint<32> > & Input_2,
		hls::stream<ap_uint<32> > & Output_1
	  )
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Input_2
#pragma HLS INTERFACE ap_hs port=Output_1
  #pragma HLS INLINE off
  CandidatePixel_new fragment;
  static unsigned short counter=0;
  int i, j;
  Pixel_new pixels[500];
  unsigned short size;
  unsigned int in_tmp;
  bit32 out_tmp;
  static bool odd_even = 0;
  if(odd_even == 0){
	  size = Input_1.read();
#ifdef PROFILE
		zculling_bot_in_1++;
#endif
  }
  else {
	  size = Input_2.read();
#ifdef PROFILE
		zculling_bot_in_2++;
#endif
  }


  // initilize the z-buffer in rendering first triangle for an image
  static unsigned char z_buffer[MAX_X/2][MAX_Y];
  if (counter == 0)
  {
    ZCULLING_INIT_ROW: for (i = 0; i < MAX_X/2; i++)
    {
      #pragma HLS PIPELINE II=1
      ZCULLING_INIT_COL: for (j = 0; j < MAX_Y; j++)
      {
        z_buffer[i][j] = 255;
      }
    }
  }


  // pixel counter
  unsigned short pixel_cntr = 0;

  // update z-buffer and pixels
  ZCULLING: for (unsigned short n = 0; n < size; n++ )
  {
#pragma HLS PIPELINE II=1
	if (odd_even == 0){
		in_tmp = Input_1.read();
#ifdef PROFILE
		zculling_bot_in_1++;
#endif
	}
	else{
		in_tmp = Input_2.read();
#ifdef PROFILE
		zculling_bot_in_2++;
#endif
	}
	fragment.x = (in_tmp&0xff);
	fragment.y = (in_tmp>>8)&0xff;
	fragment.z = (in_tmp>>16)&0xff;
	fragment.color = (in_tmp>>24)&0xff;
    if( fragment.z < z_buffer[fragment.y][fragment.x] )
    {

      pixels[pixel_cntr].x     = fragment.x;
      pixels[pixel_cntr].y     = fragment.y;
      pixels[pixel_cntr].color = fragment.color;
      pixel_cntr++;
      z_buffer[fragment.y][fragment.x] = fragment.z;
    }
  }

  Output_1.write(pixel_cntr);
#ifdef PROFILE
		zculling_bot_out_1++;
#endif
  for(j=0; j<pixel_cntr; j++){
#pragma HLS PIPELINE II=1
	  out_tmp(7,  0) = pixels[j].x;
      out_tmp(15, 8) = pixels[j].y;
      out_tmp(23, 16) = pixels[j].color;
	  out_tmp(31, 24) = 0;
	  Output_1.write(out_tmp);
#ifdef PROFILE
		zculling_bot_out_1++;
#endif
  }


  counter++;
  odd_even = odd_even==0 ? 1 : 0;
  if(counter==NUM_3D_TRI){counter=0;}
  return;
}


