/*===============================================================*/
/*                                                               */
/*                       check_result.cpp                        */
/*                                                               */
/*      Software evaluation of training and test error rate      */
/*                                                               */
/*===============================================================*/

#include <cstdio>
#include "typedefs.h"

#ifndef SW
void check_results(bit32* output)
#else
void check_results(bit8 output[MAX_X][MAX_Y])
#endif
{
  #ifndef SW
    bit8 frame_buffer_print[MAX_X][MAX_Y];

    // read result from the 32-bit output buffer
    for (int i = 0, j = 0, n = 0; n < NUM_FB; n ++ )
    {
      bit32 temp = output[n];
      unsigned char char_tmp;
      char_tmp = temp(7,0);
      frame_buffer_print[i][j++] = char_tmp;
      char_tmp = temp(15,8);
	  frame_buffer_print[i][j++] = char_tmp;
	  char_tmp = temp(23,16);
	  frame_buffer_print[i][j++] = char_tmp;
	  char_tmp = temp(31,24);
	  frame_buffer_print[i][j++] = char_tmp;
      if(j == MAX_Y)
      {
        i++;
        j = 0;
      }
    }
  #endif

  // print result
  printf("Image After Rendering: \n");
  for (int j = MAX_X - 1; j >= 0; j -- )
  {
    for (int i = 0; i < MAX_Y; i ++ )
    {
      int pix;
      #ifndef SW
        pix = frame_buffer_print[i][j].to_int();
      #else
        pix = output[i][j];

      #endif

      if (pix)
        printf("1");
      else
        printf("0");
    }
    printf("\n");
  }

}
