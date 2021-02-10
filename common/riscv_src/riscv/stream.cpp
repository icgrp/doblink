// This is free and unencumbered software released into the public domain.
//
// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non-commercial, and by any
// means.

// A simple Sieve of Eratosthenes
#include "firmware.h"
//#include "ap_int.h"
static void stats_print_dec(unsigned int val, int digits, bool zero_pad)
{
	char buffer[32];
	char *p = buffer;
	while (val || digits > 0) {
		if (val)
			*(p++) = '0' + val % 10;
		else
			*(p++) = zero_pad ? '0' : ' ';
		val = val / 10;
		digits--;
	}
	while (p != buffer) {
		if (p[-1] == ' ' && p[-2] == ' ') p[-1] = '.';
		print_chr(*(--p));
	}
        print_chr('\n');
}


void stream(void) 
{
  int din=0;
  int i;
  //float x=0;
  
  //x = 1.43456;
  //unsigned int num_cycles, num_instr;
  int num_cycles = 48;
  //__asm__ volatile ("rdcycle %0; rdinstret %1;" : "=r"(num_cycles), "=r"(num_instr));
  print_str("before write_stream");
  stats_print_dec(num_cycles, 8, false);

  for(i=0; i<100; i++)
  {
    print_dec(i);
    print_str("\n");
    write_word1(i);
    write_word2(i);
    write_word3(i);
    write_word4(i);
  }

  //__asm__ volatile ("rdcycle %0; rdinstret %1;" : "=r"(num_cycles), "=r"(num_instr));
  print_str("after write_stream");
  stats_print_dec(num_cycles, 8, false);

  din = 0; 
  print_str("din=");
  print_dec(i);
  print_str("\n");
  for(i=0; i<100; i++)
  {
    //print_str("read i=");
    //print_dec(i);
    //print_str("\n");
    din = din+read_word1();
    din = din+read_word2();
    din = din+read_word3();
    din = din+read_word4();
    //print_dec(din);
    //print_str("\n");
    //x = x + 1;
    //print_str("float: ");
    //print_float(x);
    //print_str("\n");
    //print_dec(din);
  }
  //__asm__ volatile ("rdcycle %0; rdinstret %1;" : "=r"(num_cycles), "=r"(num_instr));
  print_str("after read_stream");
  stats_print_dec(din, 8, false);


  
}


