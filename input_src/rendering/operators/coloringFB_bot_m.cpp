#include "../host/typedefs.h"

typedef struct
{
  unsigned char x;
  unsigned char y;
  unsigned char color;
} Pixel_new;



// color the frame buffer
void coloringFB_bot_m(
		hls::stream<ap_uint<32> > & Input_1,
		hls::stream<ap_uint<32> > & Output_1)

{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
  #pragma HLS INLINE off
  int i,j;
  static unsigned char frame_buffer[MAX_X][MAX_Y/2];
  Pixel_new pixels;
  static unsigned short counter=0;
  unsigned short size_pixels;
  bit32 in_tmp;
  size_pixels=Input_1.read();
#ifdef PROFILE
  coloringFB_bot_m_in_1++;
#endif
  bit32 out_FB = 0;

  if ( counter == 0 )
  {
    // initilize the framebuffer for a new image
    COLORING_FB_INIT_ROW: for (i = 0; i < MAX_X; i++)
    {
      #pragma HLS PIPELINE II=1
      COLORING_FB_INIT_COL: for (j = 0; j < MAX_Y/2; j++)
        frame_buffer[i][j] = 0;
    }
  }

  // update the framebuffer
  COLORING_FB: for (i = 0; i < size_pixels; i++)
  {
    #pragma HLS PIPELINE II=1
	 in_tmp = Input_1.read();
#ifdef PROFILE
  coloringFB_bot_m_in_1++;
#endif
	 pixels.x=(in_tmp&0xff);
	 pixels.y=(in_tmp>>8)&0xff;
	 pixels.color=(in_tmp>>16)&0xff;
    frame_buffer[ pixels.x ][ pixels.y ] = pixels.color;
  }

  counter++;
  if(counter==NUM_3D_TRI){
	  for (i=0; i<MAX_X; i++){
		  for(j=0; j<MAX_Y/2; j+=4){
#pragma HLS PIPELINE II=1
			  for (int k=0; k<4; k++){
				  out_FB( k*8+7,  k*8) = frame_buffer[i][j+k];
			  }
			  Output_1.write(out_FB);
#ifdef PROFILE
  coloringFB_bot_m_out_1++;
#endif
		  }
	  }
	  counter=0;
  }
}


