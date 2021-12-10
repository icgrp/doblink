#include "../host/typedefs.h"

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


// find pixels in the triangles from the bounding box
void rasterization2_odd (
		hls::stream<ap_uint<32> > & Input_1,
		hls::stream<ap_uint<32> > & Output_1,
		hls::stream<ap_uint<32> > & Output_2
		)
{
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

	flag = (bit2) Input_1.read();
	triangle_2d_same.x0=Input_1.read();
	triangle_2d_same.y0=Input_1.read();
	triangle_2d_same.x1=Input_1.read();
	triangle_2d_same.y1=Input_1.read();
	triangle_2d_same.x2=Input_1.read();
	triangle_2d_same.y2=Input_1.read();
	triangle_2d_same.z=Input_1.read();
	max_index[0]=Input_1.read();
	max_min[0]=Input_1.read();
	max_min[1]=Input_1.read();
	max_min[2]=Input_1.read();
	max_min[3]=Input_1.read();
	max_min[4]=Input_1.read();

  // clockwise the vertices of input 2d triangle
  if ( flag )
  {
	  Output_1.write(i_top);
	  Output_2.write(i_bot);
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
  for(j=0; j<i; j++){
#pragma HLS PIPELINE II=1
	  out_tmp(7, 0) = fragment[j].x;
	  out_tmp(15, 8) = fragment[j].y;
	  y_tmp = (int) out_tmp(15, 8);
	  out_tmp(23, 16) = fragment[j].z;
	  out_tmp(31, 24) = fragment[j].color;
	  if( y_tmp > 127) Output_1.write(out_tmp);
	  else Output_2.write(out_tmp);
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

	flag = (bit2) Input_1.read();
	triangle_2d_same.x0=Input_1.read();
	triangle_2d_same.y0=Input_1.read();
	triangle_2d_same.x1=Input_1.read();
	triangle_2d_same.y1=Input_1.read();
	triangle_2d_same.x2=Input_1.read();
	triangle_2d_same.y2=Input_1.read();
	triangle_2d_same.z=Input_1.read();
	max_index[0]=Input_1.read();
	max_min[0]=Input_1.read();
	max_min[1]=Input_1.read();
	max_min[2]=Input_1.read();
	max_min[3]=Input_1.read();
	max_min[4]=Input_1.read();

  // clockwise the vertices of input 2d triangle
  if ( flag )
  {
	  Output_1.write(i_top);
	  Output_2.write(i_bot);
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
  for(j=0; j<i; j++){
#pragma HLS PIPELINE II=1
	  out_tmp(7, 0) = fragment[j].x;
	  out_tmp(15, 8) = fragment[j].y;
	  y_tmp = (int) out_tmp(15, 8);
	  out_tmp(23, 16) = fragment[j].z;
	  out_tmp(31, 24) = fragment[j].color;
	  if(y_tmp > 127) Output_1.write(out_tmp);
	  else Output_2.write(out_tmp);
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
#pragma HLS INTERFACE axis register port=Input_1
#pragma HLS INTERFACE axis register port=Input_2
#pragma HLS INTERFACE axis register port=Output_1
#pragma HLS INTERFACE axis register port=Output_2
#pragma HLS INTERFACE axis register port=Output_3
#pragma HLS INTERFACE axis register port=Output_4

	rasterization2_odd(
			Input_1,
			Output_1,
			Output_2);

	rasterization2_even(
			Input_2,
			Output_3,
			Output_4);


}
