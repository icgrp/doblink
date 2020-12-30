// This is free and unencumbered software released into the public domain.
//
// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non-commercial, and by any
// means.

// A simple Sieve of Eratosthenes

#include "firmware.h"

#define STREAMOUT1  0x10000008
#define STREAMOUT2  0x10000010
#define STREAMOUT3  0x10000018
#define STREAMOUT4  0x10000020
#define STREAMIN1   0x10000004
#define STREAMIN2   0x1000000c
#define STREAMIN3   0x10000014
#define STREAMIN4   0x1000001c

int main(void)
{
  char const *s = "Hello world!\n";
  int i = 0;
  //stream();
  hls::stream< ap_uint<32>> s_in1(STREAMIN1); 
  hls::stream< ap_uint<32>> s_out1(STREAMOUT1); 
  hls::stream< ap_uint<32>> s_out2(STREAMOUT2); 
  for(i=0; i<3192; i++){
    data_redir_m(s_in1, s_out1, s_out2);
  }
  return 0;

}  
