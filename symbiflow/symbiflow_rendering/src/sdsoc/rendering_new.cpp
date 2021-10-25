/*===============================================================*/
/*                                                               */
/*                        rendering.cpp                          */
/*                                                               */
/*                 C++ kernel for 3D Rendering                   */
/*                                                               */
/*===============================================================*/

#include "rendering_new.h"

/*======================UTILITY FUNCTIONS========================*/
const int default_depth = 128;


void data_gen(
		  hls::stream<ap_uint<32> > & Output_1
		)

//( bit32 input[3*NUM_3D_TRI], bit32 output[NUM_FB])
{
#pragma HLS INTERFACE ap_hs port=Output_1
#include "../host/input_data.h"
    // create space for input and output
    bit32 input_tmp;
    bit32 input[3 * NUM_3D_TRI];
    bit32 output[NUM_FB];

    // pack input data for better performance
    for ( int i = 0; i < NUM_3D_TRI; i++)
    {
        input_tmp(7,   0) = triangle_3ds[i].x0;
        input_tmp(15,  8) = triangle_3ds[i].y0;
        input_tmp(23, 16) = triangle_3ds[i].z0;
        input_tmp(31, 24) = triangle_3ds[i].x1;
        Output_1.write(input_tmp);

        input_tmp(7, 0) = triangle_3ds[i].y1;
        input_tmp(15, 8) = triangle_3ds[i].z1;
        input_tmp(23, 16) = triangle_3ds[i].x2;
        input_tmp(31, 24) = triangle_3ds[i].y2;
        Output_1.write(input_tmp);

        input_tmp(7, 0) = triangle_3ds[i].z2;
        input_tmp(31, 8) = 0;
        Output_1.write(input_tmp);
    }
}

// Determine whether three vertices of a trianlgLe
// (x0,y0) (x1,y1) (x2,y2) are in clockwise order by Pineda algorithm
// if so, return a number > 0
// else if three points are in line, return a number == 0
// else in counterclockwise order, return a number < 0
int check_clockwise( Triangle_2D triangle_2d )
{
  int cw;

  cw = (triangle_2d.x2 - triangle_2d.x0) * (triangle_2d.y1 - triangle_2d.y0)
       - (triangle_2d.y2 - triangle_2d.y0) * (triangle_2d.x1 - triangle_2d.x0);

  return cw;

}

// swap (x0, y0) (x1, y1) of a Triangle_2D
void clockwise_vertices( Triangle_2D *triangle_2d )
{

  bit8 tmp_x, tmp_y;

  tmp_x = triangle_2d->x0;
  tmp_y = triangle_2d->y0;

  triangle_2d->x0 = triangle_2d->x1;
  triangle_2d->y0 = triangle_2d->y1;

  triangle_2d->x1 = tmp_x;
  triangle_2d->y1 = tmp_y;

}

bit1 pixel_in_triangle( bit8 x, bit8 y, Triangle_2D triangle_2d )
{

  int pi0, pi1, pi2;

  pi0 = (x - triangle_2d.x0) * (triangle_2d.y1 - triangle_2d.y0) - (y - triangle_2d.y0) * (triangle_2d.x1 - triangle_2d.x0);
  pi1 = (x - triangle_2d.x1) * (triangle_2d.y2 - triangle_2d.y1) - (y - triangle_2d.y1) * (triangle_2d.x2 - triangle_2d.x1);
  pi2 = (x - triangle_2d.x2) * (triangle_2d.y0 - triangle_2d.y2) - (y - triangle_2d.y2) * (triangle_2d.x0 - triangle_2d.x2);

  return (pi0 >= 0 && pi1 >= 0 && pi2 >= 0);
}

// find the max from 3 integers
bit8 find_max( bit8 in0, bit8 in1, bit8 in2 )
{
  if (in0 > in1)
  {
    if (in0 > in2)
      return in0;
    else
      return in2;
  }
  else
  {
    if (in1 > in2)
      return in1;
    else
      return in2;
  }
}

// find the min from 3 integers
bit8 find_min( bit8 in0, bit8 in1, bit8 in2 )
{
  if (in0 < in1)
  {
    if (in0 < in2)
      return in0;
    else
      return in2;
  }
  else
  {
    if (in1 < in2)
      return in1;
    else
      return in2;
  }
}


// project a 3D triangle to a 2D triangle
void projection_odd_m (
		bit32 input_lo,
		bit32 input_mi,
		bit32 input_hi,
		Triangle_2D *triangle_2d
		)
{
  #pragma HLS INLINE off
  Triangle_3D triangle_3d;
  // Setting camera to (0,0,-1), the canvas at z=0 plane
  // The 3D model lies in z>0 space
  // The coordinate on canvas is proportional to the corresponding coordinate
  // on space

    bit2 angle = 0;
    triangle_3d.x0 = input_lo( 7,  0);
    triangle_3d.y0 = input_lo(15,  8);
    triangle_3d.z0 = input_lo(23, 16);
    triangle_3d.x1 = input_lo(31, 24);
    triangle_3d.y1 = input_mi( 7,  0);
    triangle_3d.z1 = input_mi(15,  8);
    triangle_3d.x2 = input_mi(23, 16);
    triangle_3d.y2 = input_mi(31, 24);
    triangle_3d.z2 = input_hi( 7,  0);

  if(angle == 0)
  {
    triangle_2d->x0 = triangle_3d.x0;
    triangle_2d->y0 = triangle_3d.y0;
    triangle_2d->x1 = triangle_3d.x1;
    triangle_2d->y1 = triangle_3d.y1;
    triangle_2d->x2 = triangle_3d.x2;
    triangle_2d->y2 = triangle_3d.y2;
    triangle_2d->z  = triangle_3d.z0 / 3 + triangle_3d.z1 / 3 + triangle_3d.z2 / 3;
  }

  else if(angle == 1)
  {
    triangle_2d->x0 = triangle_3d.x0;
    triangle_2d->y0 = triangle_3d.z0;
    triangle_2d->x1 = triangle_3d.x1;
    triangle_2d->y1 = triangle_3d.z1;
    triangle_2d->x2 = triangle_3d.x2;
    triangle_2d->y2 = triangle_3d.z2;
    triangle_2d->z  = triangle_3d.y0 / 3 + triangle_3d.y1 / 3 + triangle_3d.y2 / 3;
  }

  else if(angle == 2)
  {
    triangle_2d->x0 = triangle_3d.z0;
    triangle_2d->y0 = triangle_3d.y0;
    triangle_2d->x1 = triangle_3d.z1;
    triangle_2d->y1 = triangle_3d.y1;
    triangle_2d->x2 = triangle_3d.z2;
    triangle_2d->y2 = triangle_3d.y2;
    triangle_2d->z  = triangle_3d.x0 / 3 + triangle_3d.x1 / 3 + triangle_3d.x2 / 3;
  }

}



// calculate bounding box for a 2D triangle
void rasterization1_odd_m (
		Triangle_2D triangle_2d,
		hls::stream<ap_uint<32> > & Output_1)
{
	Triangle_2D triangle_2d_same;
	static bit8 max_min[5]={0, 0, 0, 0, 0};
	static bit16 max_index[1]={0};


  #pragma HLS INLINE off
  // clockwise the vertices of input 2d triangle
  if ( check_clockwise( triangle_2d ) == 0 ){
	bit32 tmp;
	tmp(7,0) = 1;
	tmp(15, 8) = triangle_2d_same.x0;
	tmp(23,16) = triangle_2d_same.y0;
	tmp(31,24) = triangle_2d_same.x1;
	Output_1.write(tmp);

	tmp(7,0) = triangle_2d_same.y1;
	tmp(15, 8) = triangle_2d_same.x2;
	tmp(23,16) = triangle_2d_same.y2;
	tmp(31,24) = triangle_2d_same.z;
	Output_1.write(tmp);

	tmp(15,0) = max_index[0];
	tmp(23,16) = max_min[0];
	tmp(31,24) = max_min[1];
	Output_1.write(tmp);

	tmp(7,0) = max_min[2];
	tmp(15, 8) = max_min[3];
	tmp(23,16) = max_min[4];
	tmp(31,24) = 0;
	Output_1.write(tmp);
    return;
  }
  if ( check_clockwise( triangle_2d ) < 0 )
    clockwise_vertices( &triangle_2d );




  // copy the same 2D triangle
  triangle_2d_same.x0 = triangle_2d.x0;
  triangle_2d_same.y0 = triangle_2d.y0;
  triangle_2d_same.x1 = triangle_2d.x1;
  triangle_2d_same.y1 = triangle_2d.y1;
  triangle_2d_same.x2 = triangle_2d.x2;
  triangle_2d_same.y2 = triangle_2d.y2;
  triangle_2d_same.z  = triangle_2d.z ;

  // find the rectangle bounds of 2D triangles
  max_min[0] = find_min( triangle_2d.x0, triangle_2d.x1, triangle_2d.x2 );
  max_min[1] = find_max( triangle_2d.x0, triangle_2d.x1, triangle_2d.x2 );
  max_min[2] = find_min( triangle_2d.y0, triangle_2d.y1, triangle_2d.y2 );
  max_min[3] = find_max( triangle_2d.y0, triangle_2d.y1, triangle_2d.y2 );
  max_min[4] = max_min[1] - max_min[0];

  // calculate index for searching pixels
  max_index[0] = (max_min[1] - max_min[0]) * (max_min[3] - max_min[2]);
  bit32 tmp;

  tmp(7,0) = 0;
  tmp(15,8) = triangle_2d_same.x0;
  tmp(23,16) = triangle_2d_same.y0;
  tmp(31,24) = triangle_2d_same.x1;
  Output_1.write(tmp);

  tmp(7,0) = triangle_2d_same.y1;
  tmp(15,8) = triangle_2d_same.x2;
  tmp(23,16) = triangle_2d_same.y2;
  tmp(31,24) = triangle_2d_same.z;
  Output_1.write(tmp);

  tmp(15,0) = max_index[0];
  tmp(23,16) = max_min[0];
  tmp(31,24) = max_min[1];
  Output_1.write(tmp);

  tmp(7,0) = max_min[2];
  tmp(15,8) = max_min[3];
  tmp(23, 16) = max_min[4];
  tmp(31, 24) = 0;
  Output_1.write(tmp);
  return;
}

void data_redir_m (
		hls::stream<ap_uint<32> > & Input_1,
		hls::stream<ap_uint<32> > & Output_1
		)
{
//#pragma HLS INTERFACE ap_hs port=Input_1
//#pragma HLS INTERFACE ap_hs port=Output_1

  bit32 input_lo;
  bit32 input_mi;
  bit32 input_hi;

  Triangle_2D triangle_2ds_1;

  input_lo = Input_1.read();
  input_mi = Input_1.read();
  input_hi = Input_1.read();
  projection_odd_m (
  		input_lo,
  		input_mi,
  		input_hi,
		&triangle_2ds_1);

  rasterization1_odd_m (
		triangle_2ds_1,
    	Output_1);
}



// find pixels in the triangles from the bounding box
void rasterization2_odd (
		hls::stream<ap_uint<32> > & Input_1,
		hls::stream<ap_uint<32> > & Output_1
		)
{
//#pragma HLS INTERFACE ap_hs port=Input_1
//#pragma HLS INTERFACE ap_hs port=Output_1
  #pragma HLS INLINE off
	bit16 i = 0;
	bit16 i_top = 0;
	int y_tmp;
	int j;
	Triangle_2D triangle_2d_same;
	bit2 flag;
	bit8 max_min[5];
	bit16 max_index[1];
	bit32 out_tmp;
	static CandidatePixel fragment[500];

	bit32 tmp = Input_1.read();
	flag = (bit2) tmp(1,0);
	triangle_2d_same.x0=tmp(15,8);
	triangle_2d_same.y0=tmp(23,16);
	triangle_2d_same.x1=tmp(31,24);

	tmp = Input_1.read();
	triangle_2d_same.y1=tmp(7,0);
	triangle_2d_same.x2=tmp(15,8);
	triangle_2d_same.y2=tmp(23,16);
	triangle_2d_same.z=tmp(31,24);

	tmp = Input_1.read();
	max_index[0]=tmp(15,0);
	max_min[0]=tmp(23,16);
	max_min[1]=tmp(31,24);

	tmp = Input_1.read();
	max_min[2]=tmp(7,0);
	max_min[3]=tmp(15,8);
	max_min[4]=tmp(23, 16);

  // clockwise the vertices of input 2d triangle
  if ( flag )
  {
	  Output_1.write(i_top);
    return;
  }
  bit8 color = 100;


  RAST2: for ( bit16 k = 0; k < max_index[0]; k++ )
  {
    #pragma HLS PIPELINE II=1
    bit8 x = max_min[0] + k%max_min[4];
    bit8 y = max_min[2] + k/max_min[4];

    if( pixel_in_triangle( x, y, triangle_2d_same ) )
    {
      fragment[i].x = x;
      fragment[i].y = y;
      fragment[i].z = triangle_2d_same.z;
      fragment[i].color = color;
      i++;
      i_top++;
    }
  }

  Output_1.write(i_top);
  for(j=0; j<i; j++){
#pragma HLS PIPELINE II=1
	  out_tmp(7, 0) = fragment[j].x;
	  out_tmp(15, 8) = fragment[j].y;
	  y_tmp = (int) out_tmp(15, 8);
	  out_tmp(23, 16) = fragment[j].z;
	  out_tmp(31, 24) = fragment[j].color;
	  Output_1.write(out_tmp);
  }

  return;
}

void rasterization2_m (
		hls::stream<ap_uint<32> > & Input_1,
		hls::stream<ap_uint<32> > & Output_1
		)
{
//#pragma HLS INTERFACE ap_hs port=Input_1
//#pragma HLS INTERFACE ap_hs port=Output_1

	rasterization2_odd(
			Input_1,
			Output_1);

}

// filter hidden pixels
void zculling_top (
		hls::stream<ap_uint<32> > & Input_1,
		hls::stream<ap_uint<32> > & Output_1
	  )
{
//#pragma HLS INTERFACE ap_hs port=Input_1
//#pragma HLS INTERFACE ap_hs port=Output_1
  #pragma HLS INLINE off
  CandidatePixel fragment;
  static bit16 counter=0;
  int i, j;
  Pixel pixels[500];
  bit16 size;
  bit32 in_tmp;
  bit32 out_tmp;
  size = Input_1.read();


  // initilize the z-buffer in rendering first triangle for an image
  static bit8 z_buffer[MAX_X][MAX_Y];
  if (counter == 0)
  {
    ZCULLING_INIT_ROW: for ( bit16 i = 0; i < MAX_X; i++)
    {
      ZCULLING_INIT_COL: for ( bit16 j = 0; j < MAX_Y; j++)
      {
		#pragma HLS PIPELINE II=1
        z_buffer[i][j] = 255;
      }
    }
  }


  // pixel counter
  bit16 pixel_cntr = 0;

  // update z-buffer and pixels
  ZCULLING: for ( bit16 n = 0; n < size; n++ )
  {
#pragma HLS PIPELINE II=1
	in_tmp = Input_1.read();
	fragment.x = in_tmp(7, 0);
	fragment.y = in_tmp(15, 8);
	fragment.z = in_tmp(23, 16);
	fragment.color = in_tmp(31, 24);
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
  for(j=0; j<pixel_cntr; j++){
#pragma HLS PIPELINE II=1
	  out_tmp(7,  0) = pixels[j].x;
      out_tmp(15, 8) = pixels[j].y;
      out_tmp(23, 16) = pixels[j].color;
	  out_tmp(31, 24) = 0;
	  Output_1.write(out_tmp);
  }


  counter++;
  if(counter==NUM_3D_TRI){counter=0;}
  return;
}


// color the frame buffer
void coloringFB_bot_m(
		hls::stream<ap_uint<32> > & Input_1,
		hls::stream<ap_uint<32> > & Output_1)

{
//#pragma HLS INTERFACE ap_hs port=Input_1
//#pragma HLS INTERFACE ap_hs port=Output_1
  #pragma HLS INLINE off
  int i,j;
  static bit8 frame_buffer[MAX_X][MAX_Y];
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
      COLORING_FB_INIT_COL: for ( bit16 j = 0; j < MAX_Y; j++) {
		#pragma HLS PIPELINE II=1
        frame_buffer[i][j] = 0;
      }
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
    frame_buffer[ pixels.x ][ pixels.y ] = pixels.color;
  }

  counter++;
  if(counter==NUM_3D_TRI){
	  for (i=0; i<MAX_X; i++){
		  for(j=0; j<MAX_Y; j+=4){
			  for (int k=0; k<4; k++){
				  #pragma HLS PIPELINE II=1
				  out_FB( k*8+7,  k*8) = frame_buffer[i][j+k];
			  }
			  Output_1.write(out_FB);
		  }
	  }
	  counter=0;
  }
}

void identity(
		hls::stream<ap_uint<32> > & Input_1,
		hls::stream<ap_uint<32> > & Output_1)

{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
	Output_1.write(Input_1.read());
}

void add_1(
		hls::stream<ap_uint<32> > & Input_1,
		hls::stream<ap_uint<32> > & Output_1)

{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
	Output_1.write(Input_1.read() + 1);
}

void rendering_m (
		  hls::stream<ap_uint<32> > & Input_1,
		  hls::stream<ap_uint<32> > & Output_1
		)

//( bit32 input[3*NUM_3D_TRI], bit32 output[NUM_FB])
{
#pragma HLS interface ap_hs  port=Input_1
#pragma HLS interface ap_hs  port=Output_1
#pragma HLS DATAFLOW
  // local variables
  Triangle_2D triangle_2ds;
  Triangle_2D triangle_2ds_same;

  bit16 size_fragment;
  CandidatePixel fragment[500];

  bit16 size_pixels;
  Pixel pixels[500];

  bit8 frame_buffer[MAX_X][MAX_Y];
  bit2 angle = 0;

  bit8 max_min[5];
  bit16 max_index[1];
  bit2 flag;
  hls::stream<ap_uint<32> > Output_redir_odd("Output_redir_odd");
#pragma HLS STREAM variable=Output_redir_odd depth=1024


  hls::stream<ap_uint<32> > Output_r2_odd_top("Output_r2_odd_top");
#pragma HLS STREAM variable=Output_r2_odd_top depth=1024

  hls::stream<ap_uint<32> > Output_zcu_top("Output_zcu_top");
#pragma HLS STREAM variable=Output_zcu_top depth=1024


  // processing NUM_3D_TRI 3D triangles
  TRIANGLES: for (bit16 i = 0; i < NUM_3D_TRI; i++)
  {



    // five stages for processing each 3D triangle
	data_redir_m(Input_1, Output_redir_odd);
    rasterization2_m(Output_redir_odd, Output_r2_odd_top);
    zculling_top( Output_r2_odd_top, Output_zcu_top);
    coloringFB_bot_m(Output_zcu_top, Output_1);

  }

  // output values: frame buffer
  //output_FB_dul(Output_cfb_top, Output_cfb_bot,Output_1);
}
