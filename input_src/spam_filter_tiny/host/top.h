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
void top( hls::stream<ap_uint<32> > & Input_1,
			hls::stream<ap_uint<32> > & Output_1
			);

