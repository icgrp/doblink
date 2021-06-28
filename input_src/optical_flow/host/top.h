/*===============================================================*/
/*                                                               */
/*                       optical_flow.h                          */
/*                                                               */
/*             Hardware function for optical flow                */
/*                                                               */
/*===============================================================*/


// top-level function 
void top(hls::stream< bit32 > & Input_1,
		 hls::stream< bit32 > & Output_1);

void data_gen(hls::stream< bit32 > &Output_1);
