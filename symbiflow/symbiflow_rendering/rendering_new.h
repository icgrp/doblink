/*===============================================================*/
/*                                                               */
/*                         rendering.h                           */
/*                                                               */
/*                 C++ kernel for 3D Rendering                   */
/*                                                               */
/*===============================================================*/

#ifndef __RENDERING_H__
#define __RENDERING_H__

#include "../host/typedefs.h"

//#pragma SDS data access_pattern(input:SEQUENTIAL, output:SEQUENTIAL)

void rendering_m (
		  hls::stream<ap_uint<32> > & Input_1,
		  hls::stream<ap_uint<32> > & Output_1
		);

void data_gen(
		  hls::stream<ap_uint<32> > & Output_1
		);

#endif

