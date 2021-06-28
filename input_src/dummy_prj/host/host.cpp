/*===============================================================*/
/*                                                               */
/*                       3d_rendering.cpp                        */
/*                                                               */
/*      Main host function for the 3D Rendering application.     */
/*                                                               */
/*===============================================================*/

// standard C/C++ headers
#include <cstdio>
#include <cstdlib>
#include <getopt.h>
#include <string>
#include <time.h>
#include <sys/time.h>
#define SDSOC


#ifdef SDSOC
  // sdsoc headers
  //#include "sds_lib.h"
  // hardware function declaration
  #include "top.h"
#endif



int main(int argc, char ** argv)
{
  printf("Data Mover Application\n");
  hls::stream<ap_uint<32> > Input_1;
  hls::stream<ap_uint<32> > Output_1;

  data_gen(Input_1);
  top(Input_1, Output_1);
  for(int i=0; i<32768; i++){
	  bit32 tmp;
	  tmp = Output_1.read();
	  printf("%d op = %d\n", i, tmp.to_int());
  }

  return EXIT_SUCCESS;

}
