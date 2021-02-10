// This is free and unencumbered software released into the public domain.
//
// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non-commercial, and by any
// means.

#include "firmware.h"

#define OUTPORT     0x10000000
#define STREAMOUT1  0x10000008
#define STREAMOUT2  0x10000010
#define STREAMOUT3  0x10000018
#define STREAMOUT4  0x10000020
#define STREAMIN1   0x10000004
#define STREAMIN2   0x1000000c
#define STREAMIN3   0x10000014
#define STREAMIN4   0x1000001c
//#define INPORT  0x10000

void print_chr(char ch)
{
	*((volatile uint32_t*)OUTPORT) = ch;
}

void print_str(const char *p)
{
	while (*p != 0)
		*((volatile uint32_t*)OUTPORT) = *(p++);
}


void print_dec(unsigned int val)
{
	char buffer[10];
	char *p = buffer;
	while (val || p == buffer) {
		*(p++) = val % 10;
		val = val / 10;
	}
	while (p != buffer) {
		*((volatile uint32_t*)OUTPORT) = '0' + *(--p);
	}
}


void print_float(float din)
{
        unsigned int val;
        val = (unsigned int) (din * 100);
 
	char buffer[10];
	char *p = buffer;
        int len = 0;
	while (val || p == buffer) {
                len++;
		*(p++) = val % 10;
		val = val / 10;
	}
	while (p != buffer) {
                if(len==2)  *((volatile uint32_t*)OUTPORT) = '.';
		*((volatile uint32_t*)OUTPORT) = '0' + *(--p);
                len--;
	}
}

void print_hex(unsigned int val, int digits)
{
	for (int i = (4*digits)-4; i >= 0; i -= 4)
		*((volatile uint32_t*)OUTPORT) = "0123456789ABCDEF"[(val >> i) % 16];
}

uint32_t  read_word1(void)
{
	return *((volatile uint32_t*)STREAMIN1);
}

void write_word1(uint32_t out_value)
{
	 *((volatile uint32_t*)STREAMOUT1) = out_value;
}

uint32_t  read_word2(void)
{
	return *((volatile uint32_t*)STREAMIN2);
}

void write_word2(uint32_t out_value)
{
	 *((volatile uint32_t*)STREAMOUT2) = out_value;
}

uint32_t  read_word3(void)
{
	return *((volatile uint32_t*)STREAMIN3);
}

void write_word3(uint32_t out_value)
{
	 *((volatile uint32_t*)STREAMOUT3) = out_value;
}

uint32_t  read_word4(void)
{
	return *((volatile uint32_t*)STREAMIN4);
}

void write_word4(uint32_t out_value)
{
	 *((volatile uint32_t*)STREAMOUT4) = out_value;
}






