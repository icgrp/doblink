
#include "../host/typedefs.h"



// color the frame buffer
void coloringFB_top_m(
		hls::stream<ap_uint<32> > & Input_1,
		hls::stream<ap_uint<32> > & Input_2,
		hls::stream<ap_uint<32> > & Output_1)

{
#pragma HLS INTERFACE axis register port=Input_1
#pragma HLS INTERFACE axis register port=Input_2
#pragma HLS INTERFACE axis register port=Output_1
  int i,j;
  static bit8 frame_buffer[MAX_X][MAX_Y/2];
  Pixel pixels;
  static bit16 counter=0;
  bit16 size_pixels;
  bit32 in_tmp;
  size_pixels=Input_1.read();
  bit32 out_FB = 0;

  if ( counter == 0 )
  {
    // initilize the framebuffer for a new image
    COLORING_FB_INIT_ROW: for ( bit16 i = 0; i < MAX_X; i++)
    {
      #pragma HLS PIPELINE II=1
      COLORING_FB_INIT_COL: for ( bit16 j = 0; j < MAX_Y/2; j++)
        frame_buffer[i][j] = 0;
    }
  }

  // update the framebuffer
  COLORING_FB: for ( bit16 i = 0; i < size_pixels; i++)
  {
    #pragma HLS PIPELINE II=1
	 in_tmp = Input_1.read();
	 pixels.x=in_tmp(7, 0);
	 pixels.y=in_tmp(15, 8);
	 pixels.color=in_tmp(23, 16);
    frame_buffer[ pixels.x ][ pixels.y-128 ] = pixels.color;
  }

  counter++;
  if(counter==NUM_3D_TRI){
	  for (int l=0; l<16; l++){
	    Output_1.write(16400);
	  }
	  for (i=0; i<MAX_X; i++){
		  for(int k=0; k<MAX_Y/2; k+=4){
			  Output_1.write(Input_2.read());
		  }
		  for(j=0; j<MAX_Y/2; j+=4){
			  out_FB( 7,  0) = frame_buffer[i][j];
			  out_FB(15,  8) = frame_buffer[i][j+1];
			  out_FB(23, 16) = frame_buffer[i][j+2];
			  out_FB(31, 24) = frame_buffer[i][j+3];
			  Output_1.write(out_FB);
		  }
	  }
	  counter=0;
  }
}


