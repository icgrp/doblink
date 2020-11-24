/*===============================================================*/
/*                                                               */
/*                        rendering.cpp                          */
/*                                                               */
/*                 C++ kernel for 3D Rendering                   */
/*                                                               */
/*===============================================================*/

#include "../host/typedefs.h"
#define PROFILE

#ifdef PROFILE
	int data_redir_m_in_1=0;
	int data_redir_m_out_1=0;
	int data_redir_m_out_2=0;
	int rasterization2_m_in_1=0;
	int rasterization2_m_in_2=0;
	int rasterization2_m_out_1=0;
	int rasterization2_m_out_2=0;
	int rasterization2_m_out_3=0;
	int rasterization2_m_out_4=0;
	int zculling_top_in_1=0;
	int zculling_top_in_2=0;
	int zculling_top_out_1=0;
	int zculling_bot_in_1=0;
	int zculling_bot_in_2=0;
	int zculling_bot_out_1=0;
	int coloringFB_top_m_in_1=0;
	int coloringFB_top_m_in_2=0;
	int coloringFB_top_m_out_1=0;
	int coloringFB_bot_m_in_1=0;
	int coloringFB_bot_m_out_1=0;
#endif
/*======================UTILITY FUNCTIONS========================*/
const int default_depth = 128;

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


// Given a pixel, determine whether it is inside the triangle
// by Pineda algorithm
// if so, return true
// else, return false
bit1 pixel_in_triangle( bit8 x, bit8 y, Triangle_2D triangle_2d )
{

  int pi0, pi1, pi2;

  pi0 = (x - triangle_2d.x0) * (triangle_2d.y1 - triangle_2d.y0) - (y - triangle_2d.y0) * (triangle_2d.x1 - triangle_2d.x0);
  pi1 = (x - triangle_2d.x1) * (triangle_2d.y2 - triangle_2d.y1) - (y - triangle_2d.y1) * (triangle_2d.x2 - triangle_2d.x1);
  pi2 = (x - triangle_2d.x2) * (triangle_2d.y0 - triangle_2d.y2) - (y - triangle_2d.y2) * (triangle_2d.x0 - triangle_2d.x2);

  return (pi0 >= 0 && pi1 >= 0 && pi2 >= 0);
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

/*======================PROCESSING STAGES========================*/

// project a 3D triangle to a 2D triangle
void data_redir (
		hls::stream<ap_uint<32> > & Input_1,
		hls::stream<ap_uint<32> > & Output_1,
		hls::stream<ap_uint<32> > & Output_2
		)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
#pragma HLS INTERFACE ap_hs port=Output_2
#pragma HLS DATAFLOW
  bit32 in_tmp;

  in_tmp = Input_1.read();
  Output_1.write(in_tmp);
  in_tmp = Input_1.read();
  Output_1.write(in_tmp);
  in_tmp = Input_1.read();
  Output_1.write(in_tmp);
  in_tmp = Input_1.read();
  Output_2.write(in_tmp);
  in_tmp = Input_1.read();
  Output_2.write(in_tmp);
  in_tmp = Input_1.read();
  Output_2.write(in_tmp);

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

// project a 3D triangle to a 2D triangle
void projection_even_m (
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
#ifdef PROFILE
  data_redir_m_out_1+=4;
#endif

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
#ifdef PROFILE
  data_redir_m_out_1+=4;
#endif
  return;
}







// calculate bounding box for a 2D triangle
void rasterization1_even_m (
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
#ifdef PROFILE
  data_redir_m_out_2+=4;
#endif

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
#ifdef PROFILE
  data_redir_m_out_2+=4;
#endif
  return;
}


// find pixels in the triangles from the bounding box
void rasterization2_odd (
		hls::stream<ap_uint<32> > & Input_1,
		hls::stream<ap_uint<32> > & Output_1,
		hls::stream<ap_uint<32> > & Output_2
		)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
#pragma HLS INTERFACE ap_hs port=Output_2
  #pragma HLS INLINE off
	bit16 i = 0;
	bit16 i_top = 0;
	bit16 i_bot = 0;
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
#ifdef PROFILE
	rasterization2_m_in_1+=4;
#endif

  // clockwise the vertices of input 2d triangle
  if ( flag )
  {
	  Output_1.write(i_top);
	  Output_2.write(i_bot);
#ifdef PROFILE
		rasterization2_m_out_1++;
		rasterization2_m_out_2++;
#endif
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
      if(y>127) i_top++;
      else i_bot++;
    }
  }

  Output_1.write(i_top);
  Output_2.write(i_bot);
#ifdef PROFILE
		rasterization2_m_out_1++;
		rasterization2_m_out_2++;
#endif
  for(j=0; j<i; j++){
#pragma HLS PIPELINE II=1
	  out_tmp(7, 0) = fragment[j].x;
	  out_tmp(15, 8) = fragment[j].y;
	  y_tmp = (int) out_tmp(15, 8);
	  out_tmp(23, 16) = fragment[j].z;
	  out_tmp(31, 24) = fragment[j].color;
	  if( y_tmp > 127){
		  Output_1.write(out_tmp);
#ifdef PROFILE
		rasterization2_m_out_1++;
#endif
	  }
	  else
	  {
		  Output_2.write(out_tmp);
#ifdef PROFILE
		rasterization2_m_out_2++;
#endif
	  }
  }

  return;
}


// find pixels in the triangles from the bounding box
void rasterization2_even (
		hls::stream<ap_uint<32> > & Input_1,
		hls::stream<ap_uint<32> > & Output_1,
		hls::stream<ap_uint<32> > & Output_2
		)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
#pragma HLS INTERFACE ap_hs port=Output_2
  #pragma HLS INLINE off
	bit16 i = 0;
	bit16 i_top = 0;
	bit16 i_bot = 0;
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
#ifdef PROFILE
		rasterization2_m_in_2+=4;
#endif

  // clockwise the vertices of input 2d triangle
  if ( flag )
  {
	  Output_1.write(i_top);
	  Output_2.write(i_bot);
#ifdef PROFILE
		rasterization2_m_out_3++;
		rasterization2_m_out_4++;
#endif
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
      if(y>127) i_top++;
      else i_bot++;
    }
  }

  Output_1.write(i_top);
  Output_2.write(i_bot);
#ifdef PROFILE
		rasterization2_m_out_3++;
		rasterization2_m_out_4++;
#endif
  for(j=0; j<i; j++){
#pragma HLS PIPELINE II=1
	  out_tmp(7, 0) = fragment[j].x;
	  out_tmp(15, 8) = fragment[j].y;
	  y_tmp = (int) out_tmp(15, 8);
	  out_tmp(23, 16) = fragment[j].z;
	  out_tmp(31, 24) = fragment[j].color;
	  if(y_tmp > 127)
	  {
		  Output_1.write(out_tmp);
#ifdef PROFILE
		rasterization2_m_out_3++;
#endif
	  }
	  else
	  {
		  Output_2.write(out_tmp);
#ifdef PROFILE
		rasterization2_m_out_4++;
#endif
	  }
  }

  return;
}



void rasterization2_m (
		hls::stream<ap_uint<32> > & Input_1,
		hls::stream<ap_uint<32> > & Output_1,
		hls::stream<ap_uint<32> > & Output_2,

		hls::stream<ap_uint<32> > & Input_2,
		hls::stream<ap_uint<32> > & Output_3,
		hls::stream<ap_uint<32> > & Output_4
		)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Input_2
#pragma HLS INTERFACE ap_hs port=Output_1
#pragma HLS INTERFACE ap_hs port=Output_2
#pragma HLS INTERFACE ap_hs port=Output_3
#pragma HLS INTERFACE ap_hs port=Output_4

	rasterization2_odd(
			Input_1,
			Output_1,
			Output_2);

	rasterization2_even(
			Input_2,
			Output_3,
			Output_4);


}

int total_1 = 0;
int total_2 = 0;
// color the frame buffer
void coloringFB_top_m(
		hls::stream<ap_uint<32> > & Input_1,
		hls::stream<ap_uint<32> > & Input_2,
		hls::stream<ap_uint<32> > & Output_1)

{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Input_2
#pragma HLS INTERFACE ap_hs port=Output_1
  #pragma HLS INLINE off
  int i,j;
  static bit8 frame_buffer[MAX_X][MAX_Y/2];
  Pixel pixels;
  static bit16 counter=0;
  bit16 size_pixels;
  bit32 in_tmp;
  size_pixels=Input_1.read();
#ifdef PROFILE
  coloringFB_top_m_in_1++;
#endif
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
#ifdef PROFILE
  coloringFB_top_m_in_1++;
#endif
	 pixels.x=in_tmp(7, 0);
	 pixels.y=in_tmp(15, 8);
	 pixels.color=in_tmp(23, 16);
    frame_buffer[ pixels.x ][ pixels.y-128 ] = pixels.color;
  }

  counter++;
  if(counter==NUM_3D_TRI){
	  for (int l=0; l<16; l++){
	    Output_1.write(16400);
#ifdef PROFILE
  coloringFB_top_m_out_1++;
#endif
	  }
	  for (i=0; i<MAX_X; i++){
		  RECV: for(int k=0; k<MAX_Y/2; k+=4){
#pragma HLS PIPELINE II=1
			  Output_1.write(Input_2.read());
#ifdef PROFILE
  coloringFB_top_m_out_1++;
#endif
#ifdef PROFILE
  coloringFB_top_m_in_2++;
#endif
		  }
		  SEND: for(j=0; j<MAX_Y/2; j+=4){
#pragma HLS PIPELINE II=1
			  for (int k=0; k<4; k++){
				  out_FB( k*8+7,  k*8) = frame_buffer[i][j+k];
			  }
			  Output_1.write(out_FB);
#ifdef PROFILE
  coloringFB_top_m_out_1++;
#endif
		  }
	  }
	  counter=0;
  }
}


// color the frame buffer
void coloringFB_bot_m(
		hls::stream<ap_uint<32> > & Input_1,
		hls::stream<ap_uint<32> > & Output_1)

{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
  #pragma HLS INLINE off
  int i,j;
  static bit8 frame_buffer[MAX_X][MAX_Y/2];
  Pixel pixels;
  static bit16 counter=0;
  bit16 size_pixels;
  bit32 in_tmp;
  size_pixels=Input_1.read();
#ifdef PROFILE
  coloringFB_bot_m_in_1++;
#endif
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
#ifdef PROFILE
  coloringFB_bot_m_in_1++;
#endif
	 pixels.x=in_tmp(7, 0);
	 pixels.y=in_tmp(15, 8);
	 pixels.color=in_tmp(23, 16);
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


void data_redir_m (
		hls::stream<ap_uint<32> > & Input_1,
		hls::stream<ap_uint<32> > & Output_1,
		hls::stream<ap_uint<32> > & Output_2
		)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
#pragma HLS INTERFACE ap_hs port=Output_2

  bit32 input_lo;
  bit32 input_mi;
  bit32 input_hi;
  bit128 input_tmp;

  hls::stream<ap_uint<32> > Output_1_1;
  hls::stream<ap_uint<32> > Output_2_2;
  Triangle_2D triangle_2ds_1;
  Triangle_2D triangle_2ds_2;


#ifdef PROFILE
  data_redir_m_in_1+=3;
#endif


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



#ifdef PROFILE
  data_redir_m_in_1+=3;
#endif

  input_lo = Input_1.read();
  input_mi = Input_1.read();
  input_hi = Input_1.read();
  projection_even_m (
  		input_lo,
  		input_mi,
  		input_hi,
		&triangle_2ds_2);


  rasterization1_even_m (
		triangle_2ds_2,
  		Output_2);
}






// project a 3D triangle to a 2D triangle
void projection_odd (
		hls::stream<ap_uint<32> > & Input_1,
		hls::stream<ap_uint<32> > & Output_1
		)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
  #pragma HLS INLINE off
  Triangle_3D triangle_3d;
  Triangle_2D triangle_2d;;
  // Setting camera to (0,0,-1), the canvas at z=0 plane
  // The 3D model lies in z>0 space
  // The coordinate on canvas is proportional to the corresponding coordinate
  // on space

    bit32 input_lo  = (bit32) Input_1.read();
    bit32 input_mi  = (bit32) Input_1.read();
    bit32 input_hi  = (bit32) Input_1.read();

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
    triangle_2d.x0 = triangle_3d.x0;
    triangle_2d.y0 = triangle_3d.y0;
    triangle_2d.x1 = triangle_3d.x1;
    triangle_2d.y1 = triangle_3d.y1;
    triangle_2d.x2 = triangle_3d.x2;
    triangle_2d.y2 = triangle_3d.y2;
    triangle_2d.z  = triangle_3d.z0 / 3 + triangle_3d.z1 / 3 + triangle_3d.z2 / 3;
  }

  else if(angle == 1)
  {
    triangle_2d.x0 = triangle_3d.x0;
    triangle_2d.y0 = triangle_3d.z0;
    triangle_2d.x1 = triangle_3d.x1;
    triangle_2d.y1 = triangle_3d.z1;
    triangle_2d.x2 = triangle_3d.x2;
    triangle_2d.y2 = triangle_3d.z2;
    triangle_2d.z  = triangle_3d.y0 / 3 + triangle_3d.y1 / 3 + triangle_3d.y2 / 3;
  }

  else if(angle == 2)
  {
    triangle_2d.x0 = triangle_3d.z0;
    triangle_2d.y0 = triangle_3d.y0;
    triangle_2d.x1 = triangle_3d.z1;
    triangle_2d.y1 = triangle_3d.y1;
    triangle_2d.x2 = triangle_3d.z2;
    triangle_2d.y2 = triangle_3d.y2;
    triangle_2d.z  = triangle_3d.x0 / 3 + triangle_3d.x1 / 3 + triangle_3d.x2 / 3;
  }
  Output_1.write(triangle_2d.x0);
  Output_1.write(triangle_2d.y0);
  Output_1.write(triangle_2d.x1);
  Output_1.write(triangle_2d.y1);
  Output_1.write(triangle_2d.x2);
  Output_1.write(triangle_2d.y2);
  Output_1.write(triangle_2d.z);
}

// project a 3D triangle to a 2D triangle
void projection_even (
		hls::stream<ap_uint<32> > & Input_1,
		hls::stream<ap_uint<32> > & Output_1
		)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
  #pragma HLS INLINE off
  Triangle_3D triangle_3d;
  Triangle_2D triangle_2d;;
  // Setting camera to (0,0,-1), the canvas at z=0 plane
  // The 3D model lies in z>0 space
  // The coordinate on canvas is proportional to the corresponding coordinate
  // on space

    bit32 input_lo  = (bit32) Input_1.read();
    bit32 input_mi  = (bit32) Input_1.read();
    bit32 input_hi  = (bit32) Input_1.read();

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
    triangle_2d.x0 = triangle_3d.x0;
    triangle_2d.y0 = triangle_3d.y0;
    triangle_2d.x1 = triangle_3d.x1;
    triangle_2d.y1 = triangle_3d.y1;
    triangle_2d.x2 = triangle_3d.x2;
    triangle_2d.y2 = triangle_3d.y2;
    triangle_2d.z  = triangle_3d.z0 / 3 + triangle_3d.z1 / 3 + triangle_3d.z2 / 3;
  }

  else if(angle == 1)
  {
    triangle_2d.x0 = triangle_3d.x0;
    triangle_2d.y0 = triangle_3d.z0;
    triangle_2d.x1 = triangle_3d.x1;
    triangle_2d.y1 = triangle_3d.z1;
    triangle_2d.x2 = triangle_3d.x2;
    triangle_2d.y2 = triangle_3d.z2;
    triangle_2d.z  = triangle_3d.y0 / 3 + triangle_3d.y1 / 3 + triangle_3d.y2 / 3;
  }

  else if(angle == 2)
  {
    triangle_2d.x0 = triangle_3d.z0;
    triangle_2d.y0 = triangle_3d.y0;
    triangle_2d.x1 = triangle_3d.z1;
    triangle_2d.y1 = triangle_3d.y1;
    triangle_2d.x2 = triangle_3d.z2;
    triangle_2d.y2 = triangle_3d.y2;
    triangle_2d.z  = triangle_3d.x0 / 3 + triangle_3d.x1 / 3 + triangle_3d.x2 / 3;
  }
  Output_1.write(triangle_2d.x0);
  Output_1.write(triangle_2d.y0);
  Output_1.write(triangle_2d.x1);
  Output_1.write(triangle_2d.y1);
  Output_1.write(triangle_2d.x2);
  Output_1.write(triangle_2d.y2);
  Output_1.write(triangle_2d.z);
}


// calculate bounding box for a 2D triangle
void rasterization1_odd (
		hls::stream<ap_uint<32> > & Input_1,
		hls::stream<ap_uint<32> > & Output_1)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
	Triangle_2D triangle_2d;
	Triangle_2D triangle_2d_same;
	static bit8 max_min[5]={0, 0, 0, 0, 0};
	static bit16 max_index[1]={0};

	triangle_2d.x0=Input_1.read();
	triangle_2d.y0=Input_1.read();
	triangle_2d.x1=Input_1.read();
	triangle_2d.y1=Input_1.read();
	triangle_2d.x2=Input_1.read();
	triangle_2d.y2=Input_1.read();
	triangle_2d.z=Input_1.read();


  #pragma HLS INLINE off
  // clockwise the vertices of input 2d triangle
  if ( check_clockwise( triangle_2d ) == 0 ){
	Output_1.write(1);
	Output_1.write(triangle_2d_same.x0);
	Output_1.write(triangle_2d_same.y0);
	Output_1.write(triangle_2d_same.x1);
	Output_1.write(triangle_2d_same.y1);
	Output_1.write(triangle_2d_same.x2);
	Output_1.write(triangle_2d_same.y2);
	Output_1.write(triangle_2d_same.z);
	Output_1.write(max_index[0]);
	Output_1.write(max_min[0]);
	Output_1.write(max_min[1]);
	Output_1.write(max_min[2]);
	Output_1.write(max_min[3]);
	Output_1.write(max_min[4]);
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

  Output_1.write(0);
  Output_1.write(triangle_2d_same.x0);
  Output_1.write(triangle_2d_same.y0);
  Output_1.write(triangle_2d_same.x1);
  Output_1.write(triangle_2d_same.y1);
  Output_1.write(triangle_2d_same.x2);
  Output_1.write(triangle_2d_same.y2);
  Output_1.write(triangle_2d_same.z);
  Output_1.write(max_index[0]);
  Output_1.write(max_min[0]);
  Output_1.write(max_min[1]);
  Output_1.write(max_min[2]);
  Output_1.write(max_min[3]);
  Output_1.write(max_min[4]);
  return;
}

// calculate bounding box for a 2D triangle
void rasterization1_even (
		hls::stream<ap_uint<32> > & Input_1,
		hls::stream<ap_uint<32> > & Output_1)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
	Triangle_2D triangle_2d;
	Triangle_2D triangle_2d_same;
	static bit8 max_min[5]={0, 0, 0, 0, 0};
	static bit16 max_index[1]={0};

	triangle_2d.x0=Input_1.read();
	triangle_2d.y0=Input_1.read();
	triangle_2d.x1=Input_1.read();
	triangle_2d.y1=Input_1.read();
	triangle_2d.x2=Input_1.read();
	triangle_2d.y2=Input_1.read();
	triangle_2d.z=Input_1.read();


  #pragma HLS INLINE off
  // clockwise the vertices of input 2d triangle
  if ( check_clockwise( triangle_2d ) == 0 ){
	Output_1.write(1);
	Output_1.write(triangle_2d_same.x0);
	Output_1.write(triangle_2d_same.y0);
	Output_1.write(triangle_2d_same.x1);
	Output_1.write(triangle_2d_same.y1);
	Output_1.write(triangle_2d_same.x2);
	Output_1.write(triangle_2d_same.y2);
	Output_1.write(triangle_2d_same.z);
	Output_1.write(max_index[0]);
	Output_1.write(max_min[0]);
	Output_1.write(max_min[1]);
	Output_1.write(max_min[2]);
	Output_1.write(max_min[3]);
	Output_1.write(max_min[4]);
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

  Output_1.write(0);
  Output_1.write(triangle_2d_same.x0);
  Output_1.write(triangle_2d_same.y0);
  Output_1.write(triangle_2d_same.x1);
  Output_1.write(triangle_2d_same.y1);
  Output_1.write(triangle_2d_same.x2);
  Output_1.write(triangle_2d_same.y2);
  Output_1.write(triangle_2d_same.z);
  Output_1.write(max_index[0]);
  Output_1.write(max_min[0]);
  Output_1.write(max_min[1]);
  Output_1.write(max_min[2]);
  Output_1.write(max_min[3]);
  Output_1.write(max_min[4]);
  return;
}




// filter hidden pixels
void zculling_top (
		hls::stream<ap_uint<32> > & Input_1,
		hls::stream<ap_uint<32> > & Input_2,
		hls::stream<ap_uint<32> > & Output_1
	  )
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Input_2
#pragma HLS INTERFACE ap_hs port=Output_1
  #pragma HLS INLINE off
  CandidatePixel fragment;
  static bit16 counter=0;
  int i, j;
  Pixel pixels[500];
  bit16 size;
  bit32 in_tmp;
  bit32 out_tmp;
  static bit1 odd_even = 0;
  if(odd_even == 0) {
	  size = Input_1.read();
#ifdef PROFILE
		zculling_top_in_1++;
#endif
  } else {
	  size = Input_2.read();
#ifdef PROFILE
		zculling_top_in_2++;
#endif

  }


  // initilize the z-buffer in rendering first triangle for an image
  static bit8 z_buffer[MAX_X/2][MAX_Y];
  if (counter == 0)
  {
    ZCULLING_INIT_ROW: for ( bit16 i = 0; i < MAX_X/2; i++)
    {
      #pragma HLS PIPELINE II=1
      ZCULLING_INIT_COL: for ( bit16 j = 0; j < MAX_Y; j++)
      {
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
	if (odd_even == 0){
		in_tmp = Input_1.read();
#ifdef PROFILE
		zculling_top_in_1++;
#endif
	}
	else {
		in_tmp = Input_2.read();
#ifdef PROFILE
		zculling_top_in_2++;
#endif
	}
	fragment.x = in_tmp(7, 0);
	fragment.y = in_tmp(15, 8);
	fragment.z = in_tmp(23, 16);
	fragment.color = in_tmp(31, 24);
    if( fragment.z < z_buffer[fragment.y-128][fragment.x] )
    {

      pixels[pixel_cntr].x     = fragment.x;
      pixels[pixel_cntr].y     = fragment.y;
      pixels[pixel_cntr].color = fragment.color;
      pixel_cntr++;
      z_buffer[fragment.y-128][fragment.x] = fragment.z;
    }
  }

  Output_1.write(pixel_cntr);
#ifdef PROFILE
		zculling_top_out_1++;
#endif
  for(j=0; j<pixel_cntr; j++){
#pragma HLS PIPELINE II=1
	  out_tmp(7,  0) = pixels[j].x;
      out_tmp(15, 8) = pixels[j].y;
      out_tmp(23, 16) = pixels[j].color;
	  out_tmp(31, 24) = 0;
	  Output_1.write(out_tmp);
#ifdef PROFILE
		zculling_top_out_1++;
#endif
  }


  counter++;
  odd_even = ~odd_even;
  if(counter==NUM_3D_TRI){counter=0;}
  return;
}

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
  CandidatePixel fragment;
  static bit16 counter=0;
  int i, j;
  Pixel pixels[500];
  bit16 size;
  bit32 in_tmp;
  bit32 out_tmp;
  static bit1 odd_even = 0;
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
  static bit8 z_buffer[MAX_X/2][MAX_Y];
  if (counter == 0)
  {
    ZCULLING_INIT_ROW: for ( bit16 i = 0; i < MAX_X/2; i++)
    {
      #pragma HLS PIPELINE II=1
      ZCULLING_INIT_COL: for ( bit16 j = 0; j < MAX_Y; j++)
      {
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
  odd_even = ~odd_even;
  if(counter==NUM_3D_TRI){counter=0;}
  return;
}


// color the frame buffer
void coloringFB_top(
		hls::stream<ap_uint<32> > & Input_1,
		hls::stream<ap_uint<32> > & Output_1)

{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
  #pragma HLS INLINE off
  int i,j;
  static bit8 frame_buffer[MAX_X][MAX_Y/2];
  Pixel pixels;
  static bit16 counter=0;
  bit16 size_pixels;
  bit32 in_tmp;
  size_pixels=Input_1.read();


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
	  for (i=0; i<MAX_X; i++){
		  for(j=0; j<MAX_Y/2; j++){
			  Output_1.write(frame_buffer[i][j]);
		  }
	  }
	  counter=0;
  }
}


// color the frame buffer
void coloringFB_bot(
		hls::stream<ap_uint<32> > & Input_1,
		hls::stream<ap_uint<32> > & Output_1)

{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
  #pragma HLS INLINE off
  int i,j;
  static bit8 frame_buffer[MAX_X][MAX_Y/2];
  Pixel pixels;
  static bit16 counter=0;
  bit16 size_pixels;
  bit32 in_tmp;
  size_pixels=Input_1.read();


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
    frame_buffer[ pixels.x ][ pixels.y ] = pixels.color;
  }

  counter++;
  if(counter==NUM_3D_TRI){
	  for (i=0; i<MAX_X; i++){
		  for(j=0; j<MAX_Y/2; j++){
			  Output_1.write(frame_buffer[i][j]);
		  }
	  }
	  counter=0;
  }
}


// color the frame buffer


void output_FB_dul(
		    hls::stream<ap_uint<32> > & Input_1,
			hls::stream<ap_uint<32> > & Input_2,
			hls::stream<ap_uint<32> > & Output_1)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Input_2
#pragma HLS INTERFACE ap_hs port=Output_1
  #pragma HLS INLINE
  bit32 out_FB = 0;
  int i,j;


  for(j=0; j<16; j++){
	  Output_1.write(16400);
  }





  OUTPUT_FB_ROW: for ( bit16 i = 0; i < MAX_X; i++)
  {

    OUTPUT_FB_COL: for ( bit16 j = 0; j < MAX_Y; j = j + 4)
    {
#pragma HLS PIPELINE II=4
      if(j<MAX_Y/2){
		  out_FB( 7,  0) = Input_2.read();
		  out_FB(15,  8) = Input_2.read();
		  out_FB(23, 16) = Input_2.read();
		  out_FB(31, 24) = Input_2.read();
		  Output_1.write(out_FB);
      }else{
		  out_FB( 7,  0) = Input_1.read();
		  out_FB(15,  8) = Input_1.read();
		  out_FB(23, 16) = Input_1.read();
		  out_FB(31, 24) = Input_1.read();
		  Output_1.write(out_FB);
      }
    }
  }
}



void rendering (
		  hls::stream<ap_uint<32> > & Input_1,
		  hls::stream<ap_uint<32> > & Output_1
		)

//( bit32 input[3*NUM_3D_TRI], bit32 output[NUM_FB])
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
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
  hls::stream<ap_uint<32> > Output_redir_odd;
  hls::stream<ap_uint<32> > Output_redir_even;

  hls::stream<ap_uint<32> > Output_projc_odd;
  hls::stream<ap_uint<32> > Output_projc_even;
  hls::stream<ap_uint<32> > Output_r1_odd;
  hls::stream<ap_uint<32> > Output_r1_even;

  hls::stream<ap_uint<32> > Output_r2_odd_top;
  hls::stream<ap_uint<32> > Output_r2_odd_bot;
  hls::stream<ap_uint<32> > Output_r2_even_top;
  hls::stream<ap_uint<32> > Output_r2_even_bot;


  hls::stream<ap_uint<32> > Output_zcu_top;
  hls::stream<ap_uint<32> > Output_zcu_bot;
  hls::stream<ap_uint<32> > Output_cfb_top;
  hls::stream<ap_uint<32> > Output_cfb_bot;
  // processing NUM_3D_TRI 3D triangles
  TRIANGLES: for (bit16 i = 0; i < NUM_3D_TRI/2; i++)
  {



    // five stages for processing each 3D triangle
	data_redir(Input_1, Output_redir_odd, Output_redir_even);

    projection_odd(Output_redir_odd, Output_projc_odd);
    projection_even(Output_redir_even, Output_projc_even);

    rasterization1_odd(Output_projc_odd, Output_r1_odd);
    rasterization1_even(Output_projc_even, Output_r1_even);
    rasterization2_odd(Output_r1_odd, Output_r2_odd_top, Output_r2_odd_bot);
    zculling_top( Output_r2_odd_top, Output_r2_even_top, Output_zcu_top);
    zculling_bot(Output_r2_odd_bot, Output_r2_even_bot, Output_zcu_bot);
    coloringFB_top(Output_zcu_top, Output_cfb_top);
    coloringFB_bot(Output_zcu_bot, Output_cfb_bot);


    rasterization2_even(Output_r1_even, Output_r2_even_top, Output_r2_even_bot);
    zculling_top( Output_r2_odd_top, Output_r2_even_top, Output_zcu_top);
    zculling_bot(Output_r2_odd_bot, Output_r2_even_bot, Output_zcu_bot);
    coloringFB_top(Output_zcu_top, Output_cfb_top);
    coloringFB_bot(Output_zcu_bot, Output_cfb_bot);

  }

  // output values: frame buffer
  output_FB_dul(Output_cfb_top, Output_cfb_bot,Output_1);
}


void rendering_m (
		  hls::stream<ap_uint<32> > & Input_1,
		  hls::stream<ap_uint<32> > & Output_1
		)

//( bit32 input[3*NUM_3D_TRI], bit32 output[NUM_FB])
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
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
  hls::stream<ap_uint<32> > Output_redir_odd("sb1");
#pragma HLS STREAM variable=Output_redir_odd depth=default_depth

  hls::stream<ap_uint<32> > Output_redir_even("sb2");
#pragma HLS STREAM variable=Output_redir_even depth=default_depth

  hls::stream<ap_uint<32> > Output_projc_odd("sb3");
#pragma HLS STREAM variable=Output_projc_odd depth=default_depth
  hls::stream<ap_uint<32> > Output_projc_even("sb4");
#pragma HLS STREAM variable=Output_projc_even depth=default_depth
  hls::stream<ap_uint<32> > Output_r1_odd("sb5");
#pragma HLS STREAM variable=Output_r1_odd depth=default_depth
  hls::stream<ap_uint<32> > Output_r1_even("sb6");
#pragma HLS STREAM variable=Output_r1_even depth=default_depth

  hls::stream<ap_uint<32> > Output_r2_odd_top("sb7");
#pragma HLS STREAM variable=Output_r2_odd_top depth=default_depth
  hls::stream<ap_uint<32> > Output_r2_odd_bot("sb8");
#pragma HLS STREAM variable=Output_r2_odd_bot depth=default_depth
  hls::stream<ap_uint<32> > Output_r2_even_top("sb9");
#pragma HLS STREAM variable=Output_r2_even_top depth=default_depth
  hls::stream<ap_uint<32> > Output_r2_even_bot("sb10");
#pragma HLS STREAM variable=Output_r2_even_bot depth=default_depth


  hls::stream<ap_uint<32> > Output_zcu_top("sb11");
#pragma HLS STREAM variable=Output_zcu_top depth=default_depth
  hls::stream<ap_uint<32> > Output_zcu_bot("sb12");
#pragma HLS STREAM variable=Output_zcu_bot depth=default_depth
  hls::stream<ap_uint<32> > Output_cfb_top("sb13");
#pragma HLS STREAM variable=Output_cfb_top depth=default_depth
  hls::stream<ap_uint<32> > Output_cfb_bot("sb14");
#pragma HLS STREAM variable=Output_cfb_bot depth=default_depth


  // processing NUM_3D_TRI 3D triangles
  TRIANGLES: for (bit16 i = 0; i < NUM_3D_TRI/2; i++)
  {



    // five stages for processing each 3D triangle
	data_redir_m(Input_1, Output_redir_odd, Output_redir_even);


    rasterization2_m(Output_redir_odd, Output_r2_odd_top, Output_r2_odd_bot,
    Output_redir_even, Output_r2_even_top, Output_r2_even_bot);

    zculling_top( Output_r2_odd_top, Output_r2_even_top, Output_zcu_top);
    zculling_bot(Output_r2_odd_bot, Output_r2_even_bot, Output_zcu_bot);
    coloringFB_bot_m(Output_zcu_bot, Output_cfb_bot);
    coloringFB_top_m(Output_zcu_top, Output_cfb_bot, Output_1);



    zculling_top( Output_r2_odd_top, Output_r2_even_top, Output_zcu_top);
    zculling_bot(Output_r2_odd_bot, Output_r2_even_bot, Output_zcu_bot);
    coloringFB_bot_m(Output_zcu_bot, Output_cfb_bot);
    coloringFB_top_m(Output_zcu_top, Output_cfb_bot, Output_1);


  }

  // output values: frame buffer
  //output_FB_dul(Output_cfb_top, Output_cfb_bot,Output_1);

#ifdef PROFILE
  printf("data_redir_m_in_1,%d\n", data_redir_m_in_1);
  printf("data_redir_m_out_1,%d\n", data_redir_m_out_1);
  printf("data_redir_m_out_2,%d\n", data_redir_m_out_2);
  printf("rasterization2_m_in_1,%d\n", rasterization2_m_in_1);
  printf("rasterization2_m_in_2,%d\n", rasterization2_m_in_2);
  printf("rasterization2_m_out_1,%d\n", rasterization2_m_out_1);
  printf("rasterization2_m_out_2,%d\n", rasterization2_m_out_2);
  printf("rasterization2_m_out_3,%d\n", rasterization2_m_out_3);
  printf("rasterization2_m_out_4,%d\n", rasterization2_m_out_4);
  printf("zculling_top_in_1,%d\n", zculling_top_in_1);
  printf("zculling_top_in_2,%d\n", zculling_top_in_2);
  printf("zculling_top_out_1,%d\n", zculling_top_out_1);
  printf("zculling_bot_in_1,%d\n", zculling_bot_in_1);
  printf("zculling_bot_in_2,%d\n", zculling_bot_in_2);
  printf("zculling_bot_out_1,%d\n", zculling_bot_out_1);
  printf("coloringFB_top_in_1,%d\n", coloringFB_top_m_in_1);
  printf("coloringFB_top_in_2,%d\n", coloringFB_top_m_in_2);
  printf("coloringFB_top_out_1,%d\n", coloringFB_top_m_out_1);
  printf("coloringFB_bot_in_1,%d\n", coloringFB_bot_m_in_1);
  printf("coloringFB_bot_out_1,%d\n", coloringFB_bot_m_out_1);
#endif


}

// project a 3D triangle to a 2D triangle
void projection ( Triangle_3D triangle_3d, Triangle_2D *triangle_2d, bit2 angle )
{
  #pragma HLS INLINE off
  // Setting camera to (0,0,-1), the canvas at z=0 plane
  // The 3D model lies in z>0 space
  // The coordinate on canvas is proportional to the corresponding coordinate
  // on space
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
bit2 rasterization1 ( Triangle_2D triangle_2d, bit8 max_min[], Triangle_2D *triangle_2d_same, bit16 max_index[])
{
  #pragma HLS INLINE off
  // clockwise the vertices of input 2d triangle
  if ( check_clockwise( triangle_2d ) == 0 )
    return 1;
  if ( check_clockwise( triangle_2d ) < 0 )
    clockwise_vertices( &triangle_2d );

  // copy the same 2D triangle
  triangle_2d_same->x0 = triangle_2d.x0;
  triangle_2d_same->y0 = triangle_2d.y0;
  triangle_2d_same->x1 = triangle_2d.x1;
  triangle_2d_same->y1 = triangle_2d.y1;
  triangle_2d_same->x2 = triangle_2d.x2;
  triangle_2d_same->y2 = triangle_2d.y2;
  triangle_2d_same->z  = triangle_2d.z ;

  // find the rectangle bounds of 2D triangles
  max_min[0] = find_min( triangle_2d.x0, triangle_2d.x1, triangle_2d.x2 );
  max_min[1] = find_max( triangle_2d.x0, triangle_2d.x1, triangle_2d.x2 );
  max_min[2] = find_min( triangle_2d.y0, triangle_2d.y1, triangle_2d.y2 );
  max_min[3] = find_max( triangle_2d.y0, triangle_2d.y1, triangle_2d.y2 );
  max_min[4] = max_min[1] - max_min[0];

  // calculate index for searching pixels
  max_index[0] = (max_min[1] - max_min[0]) * (max_min[3] - max_min[2]);

  return 0;
}

// find pixels in the triangles from the bounding box
bit16 rasterization2 ( bit2 flag, bit8 max_min[], bit16 max_index[], Triangle_2D triangle_2d_same, CandidatePixel fragment2[] )
{
  #pragma HLS INLINE off
  // clockwise the vertices of input 2d triangle
  if ( flag )
  {
    return 0;
  }
  bit8 color = 100;
  bit16 i = 0;

  RAST2: for ( bit16 k = 0; k < max_index[0]; k++ )
  {
    #pragma HLS PIPELINE II=1
    bit8 x = max_min[0] + k%max_min[4];
    bit8 y = max_min[2] + k/max_min[4];

    if( pixel_in_triangle( x, y, triangle_2d_same ) )
    {
      fragment2[i].x = x;
      fragment2[i].y = y;
      fragment2[i].z = triangle_2d_same.z;
      fragment2[i].color = color;
      i++;
    }
  }

  return i;
}

// filter hidden pixels
bit16 zculling ( bit16 counter, CandidatePixel fragments[], bit16 size, Pixel pixels[])
{
  #pragma HLS INLINE off

  // initilize the z-buffer in rendering first triangle for an image
  static bit8 z_buffer[MAX_X][MAX_Y];
  if (counter == 0)
  {
    ZCULLING_INIT_ROW: for ( bit16 i = 0; i < MAX_X; i++)
    {
#pragma HLS PIPELINE II=1
      ZCULLING_INIT_COL: for ( bit16 j = 0; j < MAX_Y; j++)
      {
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
    if( fragments[n].z < z_buffer[fragments[n].y][fragments[n].x] )
    {
      pixels[pixel_cntr].x     = fragments[n].x;
      pixels[pixel_cntr].y     = fragments[n].y;
      pixels[pixel_cntr].color = fragments[n].color;
      pixel_cntr++;
      z_buffer[fragments[n].y][fragments[n].x] = fragments[n].z;
    }
  }

  return pixel_cntr;
}

// color the frame buffer
void coloringFB(bit16 counter,  bit16 size_pixels, Pixel pixels[], bit8 frame_buffer[MAX_X][MAX_Y])
{
  #pragma HLS INLINE off

  if ( counter == 0 )
  {
    // initilize the framebuffer for a new image
    COLORING_FB_INIT_ROW: for ( bit16 i = 0; i < MAX_X; i++)
    {
#pragma HLS PIPELINE II=1
      COLORING_FB_INIT_COL: for ( bit16 j = 0; j < MAX_Y; j++)
        frame_buffer[i][j] = 0;
    }
  }

  // update the framebuffer
  COLORING_FB: for ( bit16 i = 0; i < size_pixels; i++)
  {
    #pragma HLS PIPELINE II=1
    frame_buffer[ pixels[i].x ][ pixels[i].y ] = pixels[i].color;
  }

}

// stream out the frame buffer
void output_FB(bit8 frame_buffer[MAX_X][MAX_Y], bit32 output[NUM_FB])
{
  #pragma HLS INLINE
  bit32 out_FB = 0;
  //static int flag = 0;
  OUTPUT_FB_ROW: for ( bit16 i = 0; i < MAX_X; i++)
  {

    OUTPUT_FB_COL: for ( bit16 j = 0; j < MAX_Y; j = j + 4)
    {
#pragma HLS PIPELINE II=1
    	INNERLOOP: for(bit16 k = 0; k < 4; k++)
    	{
    		out_FB( k*8+7,  k*8) = frame_buffer[i][j + k];
    	}
      output[i * MAX_Y / 4 + j / 4] = out_FB;
    }
  }

}


/*========================TOP FUNCTION===========================*/
void rendering_mono(
		  hls::stream<ap_uint<128> > & Input_1,
		  hls::stream<ap_uint<128> > & Output_1
		)

//( bit32 input[3*NUM_3D_TRI], bit32 output[NUM_FB])
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1

  // local variables
  Triangle_3D triangle_3ds;
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

  // processing NUM_3D_TRI 3D triangles
  TRIANGLES: for (bit16 i = 0; i < NUM_3D_TRI; i++)
  {
	bit128 input_tmp = Input_1.read();
    bit32 input_lo  = input_tmp(31,0);
    bit32 input_mi  = input_tmp(63,32);
    bit32 input_hi  = input_tmp(95,64);

    triangle_3ds.x0 = input_lo( 7,  0);
    triangle_3ds.y0 = input_lo(15,  8);
    triangle_3ds.z0 = input_lo(23, 16);
    triangle_3ds.x1 = input_lo(31, 24);
    triangle_3ds.y1 = input_mi( 7,  0);
    triangle_3ds.z1 = input_mi(15,  8);
    triangle_3ds.x2 = input_mi(23, 16);
    triangle_3ds.y2 = input_mi(31, 24);
    triangle_3ds.z2 = input_hi( 7,  0);

    //#ifdef USE_DATAFLOW
      #pragma HLS dataflow
    //#endif

    // five stages for processing each 3D triangle
    projection( triangle_3ds, &triangle_2ds, angle );
    flag = rasterization1( triangle_2ds, max_min, &triangle_2ds_same, max_index);
    size_fragment = rasterization2( flag, max_min, max_index, triangle_2ds_same, fragment );
    size_pixels = zculling( i, fragment, size_fragment, pixels);
    coloringFB ( i, size_pixels, pixels, frame_buffer);
  }



	for(int j=0; j<256; j++){
	  Output_1.write(4352);
	}

    bit128 out_FB = 0;
    OUTPUT_FB_ROW: for ( bit16 i = 0; i < MAX_X; i++)
    {
      OUTPUT_FB_COL: for ( bit16 j = 0; j < MAX_Y; j = j + 16)
      {
#pragma HLS PIPELINE II=1
    	  INNERLOOP: for(bit16 k = 0; k < 16; k++)
    	  {
    	    out_FB(k*8+7,  k*8) = frame_buffer[i][j + k];
    	  }
    	  Output_1.write(out_FB);
      }
    }

}

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
        input_tmp(7,   0) = triangle_3ds[i].y1;
        input_tmp(15,  8) = triangle_3ds[i].z1;
        input_tmp(23, 16) = triangle_3ds[i].x2;
        input_tmp(31, 24) = triangle_3ds[i].y2;
        Output_1.write(input_tmp);
        input_tmp(7,   0) = triangle_3ds[i].z2;
        input_tmp(31,  8)  = 0;
        Output_1.write(input_tmp);
    }
}

#define USER_WIDTH 64

void user_kernel(
		  hls::stream<ap_uint<USER_WIDTH> > & Input_1,
		  hls::stream<ap_uint<USER_WIDTH> > & Output_1
		)

{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
		Output_1.write(Input_1.read()+5);
}

void user_fifo(
		  hls::stream<ap_uint<32> > & Input_1,
		  hls::stream<ap_uint<32> > & Output_1
		)

{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
		int i;
		int tmp[16];
		for (i=0; i<16; i++)
		{
			tmp[i] = Input_1.read();
			Output_1.write(tmp[i]);
		}
}



