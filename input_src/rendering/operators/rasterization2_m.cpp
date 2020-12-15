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




/*
static bit1 pixel_in_triangle( bit8 x, bit8 y, Triangle_2D triangle_2d )
{

  int pi0, pi1, pi2;

  pi0 = (x - triangle_2d.x0) * (triangle_2d.y1 - triangle_2d.y0) - (y - triangle_2d.y0) * (triangle_2d.x1 - triangle_2d.x0);
  pi1 = (x - triangle_2d.x1) * (triangle_2d.y2 - triangle_2d.y1) - (y - triangle_2d.y1) * (triangle_2d.x2 - triangle_2d.x1);
  pi2 = (x - triangle_2d.x2) * (triangle_2d.y0 - triangle_2d.y2) - (y - triangle_2d.y2) * (triangle_2d.x0 - triangle_2d.x2);

  return (pi0 >= 0 && pi1 >= 0 && pi2 >= 0);
}
*/

static bool pixel_in_triangle( unsigned char x, unsigned char y, Triangle_2D_new triangle_2d )
{

  int pi0, pi1, pi2;

  pi0 = (x - triangle_2d.x0) * (triangle_2d.y1 - triangle_2d.y0) - (y - triangle_2d.y0) * (triangle_2d.x1 - triangle_2d.x0);
  pi1 = (x - triangle_2d.x1) * (triangle_2d.y2 - triangle_2d.y1) - (y - triangle_2d.y1) * (triangle_2d.x2 - triangle_2d.x1);
  pi2 = (x - triangle_2d.x2) * (triangle_2d.y0 - triangle_2d.y2) - (y - triangle_2d.y2) * (triangle_2d.x0 - triangle_2d.x2);

  return (pi0 >= 0 && pi1 >= 0 && pi2 >= 0);
}

// find pixels in the triangles from the bounding box
static void rasterization2_odd (
		hls::stream<ap_uint<32> > & Input_1,
		hls::stream<ap_uint<32> > & Output_1,
		hls::stream<ap_uint<32> > & Output_2
		)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
#pragma HLS INTERFACE ap_hs port=Output_2
  #pragma HLS INLINE off
	unsigned short i = 0;
	unsigned short i_top = 0;
	unsigned short i_bot = 0;
	int y_tmp;
	int j;
	Triangle_2D_new triangle_2d_same;
	unsigned char flag;
	unsigned char max_min[5];
	unsigned short max_index[1];
	unsigned int out_tmp;
	CandidatePixel_new fragment[500];

	unsigned int tmp = Input_1.read();
	//printf("In1: %08x\n", tmp);
	flag = (unsigned char) (tmp & 0x3);
	triangle_2d_same.x0=(unsigned char) ((tmp >> 8)  & 0xff);
	triangle_2d_same.y0=(unsigned char) ((tmp >> 16) & 0xff);
	triangle_2d_same.x1=(unsigned char) ((tmp >> 24) & 0xff);

	tmp = Input_1.read();
	//printf("In1: %08x\n", tmp);
	triangle_2d_same.y1=(unsigned char) (tmp & 0xff);
	triangle_2d_same.x2=(unsigned char) ((tmp >> 8)& 0xff);
	triangle_2d_same.y2=(unsigned char) ((tmp >> 16)& 0xff);
	triangle_2d_same.z= (unsigned char) ((tmp >> 24)& 0xff);

	tmp = Input_1.read();
	//printf("In1: %08x\n", tmp);
	max_index[0]=(unsigned short) (tmp & 0xffff);
	max_min[0]=(unsigned char) ((tmp >> 16)& 0xff);
	max_min[1]=(unsigned char) ((tmp >> 24)& 0xff);

	tmp = Input_1.read();
	//printf("In1: %08x\n", tmp);
	max_min[2]=(unsigned char) (tmp & 0xff);
	max_min[3]=(unsigned char) ((tmp >> 8)& 0xff);
	max_min[4]=(unsigned char) ((tmp >> 16)& 0xff);
#ifdef PROFILE
		rasterization2_m_in_2+=4;
#endif

  // clockwise the vertices of input 2d triangle
  if ( flag )
  {
	  Output_1.write(i_top);
	  //printf("out1: %08x\n", i_top);
	  Output_2.write(i_bot);
	  //printf("out2: %08x\n", i_bot);
#ifdef PROFILE
		rasterization2_m_out_3++;
		rasterization2_m_out_4++;
#endif
    return;
  }
  unsigned char color = 100;


  RAST2: for ( unsigned short k = 0; k < max_index[0]; k++ )
  {
    #pragma HLS PIPELINE II=1
	unsigned char x = max_min[0] + k%max_min[4];
	unsigned char y = max_min[2] + k/max_min[4];

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
  //printf("out1: %08x\n", i_top);
  Output_2.write(i_bot);
  //printf("out2: %08x\n", i_bot);
#ifdef PROFILE
		rasterization2_m_out_3++;
		rasterization2_m_out_4++;
#endif
  for(j=0; j<i; j++){
#pragma HLS PIPELINE II=1

	  out_tmp = fragment[j].x;
	  out_tmp = out_tmp + (((unsigned int)fragment[j].y)<<8);
	  y_tmp = (int) fragment[j].y;
	  out_tmp = out_tmp + (((unsigned int)fragment[j].z)<<16);
	  out_tmp = out_tmp + (((unsigned int)fragment[j].color)<<24);
	  if(y_tmp > 127)
	  {
		  Output_1.write(out_tmp);
		  //printf("out1: %08x\n", out_tmp);
#ifdef PROFILE
		rasterization2_m_out_3++;
#endif
	  }
	  else
	  {
		  Output_2.write(out_tmp);
		  //printf("out2: %08x\n", out_tmp);
#ifdef PROFILE
		rasterization2_m_out_4++;
#endif
	  }
  }

  return;
}

// find pixels in the triangles from the bounding box
static void rasterization2_even (
		hls::stream<ap_uint<32> > & Input_1,
		hls::stream<ap_uint<32> > & Output_1,
		hls::stream<ap_uint<32> > & Output_2
		)
{
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Output_1
#pragma HLS INTERFACE ap_hs port=Output_2
  #pragma HLS INLINE off
	unsigned short i = 0;
	unsigned short i_top = 0;
	unsigned short i_bot = 0;
	int y_tmp;
	int j;
	Triangle_2D_new triangle_2d_same;
	unsigned char flag;
	unsigned char max_min[5];
	unsigned short max_index[1];
	unsigned int out_tmp;
	CandidatePixel_new fragment[500];

	unsigned int tmp = Input_1.read();
	flag = (unsigned char) (tmp & 0x3);
	triangle_2d_same.x0=(unsigned char) ((tmp >> 8)  & 0xff);
	triangle_2d_same.y0=(unsigned char) ((tmp >> 16) & 0xff);
	triangle_2d_same.x1=(unsigned char) ((tmp >> 24) & 0xff);

	tmp = Input_1.read();
	triangle_2d_same.y1=(unsigned char) (tmp & 0xff);
	triangle_2d_same.x2=(unsigned char) ((tmp >> 8)& 0xff);
	triangle_2d_same.y2=(unsigned char) ((tmp >> 16)& 0xff);
	triangle_2d_same.z= (unsigned char) ((tmp >> 24)& 0xff);

	tmp = Input_1.read();
	max_index[0]=(unsigned short) (tmp & 0xffff);
	max_min[0]=(unsigned char) ((tmp >> 16)& 0xff);
	max_min[1]=(unsigned char) ((tmp >> 24)& 0xff);

	tmp = Input_1.read();
	max_min[2]=(unsigned char) (tmp & 0xff);
	max_min[3]=(unsigned char) ((tmp >> 8)& 0xff);
	max_min[4]=(unsigned char) ((tmp >> 16)& 0xff);
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
  unsigned char color = 100;


  RAST2: for (unsigned short k = 0; k < max_index[0]; k++ )
  {
    #pragma HLS PIPELINE II=1
	unsigned char  x = max_min[0] + k%max_min[4];
	unsigned char  y = max_min[2] + k/max_min[4];

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

	  out_tmp = fragment[j].x;
	  out_tmp = out_tmp + (((unsigned int)fragment[j].y)<<8);
	  y_tmp = (int) fragment[j].y;
	  out_tmp = out_tmp + (((unsigned int)fragment[j].z)<<16);
	  out_tmp = out_tmp + (((unsigned int)fragment[j].color)<<24);
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

