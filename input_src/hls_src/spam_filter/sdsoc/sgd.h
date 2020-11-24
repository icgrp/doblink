/*===============================================================*/
/*                                                               */
/*                            sgd.h                              */
/*                                                               */
/*          Top-level hardware function declaration              */
/*                                                               */
/*===============================================================*/

#include "../host/typedefs.h"
#include <hls_stream.h>

// top-level function declaration
void SgdLR( hls::stream<ap_uint<32> > & Input_1,
			hls::stream<ap_uint<32> > & Output_1
			);

void SgdLR_mono( hls::stream<ap_uint<32> > & Input_1,
			hls::stream<ap_uint<32> > & Output_1
			);
