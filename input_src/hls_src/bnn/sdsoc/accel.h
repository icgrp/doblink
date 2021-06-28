#ifndef ACCEL_ACCEL_H
#define ACCEL_ACCEL_H

#include <cstddef>
#include <hls_stream.h>
#include <stdlib.h>   // include this before sds_lib.h for size_t

#include "Typedefs.h"

//-------------------------------------------------------------------
// Constants
//-------------------------------------------------------------------

//#define CHECK_OUTPUT

const unsigned WORD_SIZE = 64;
const unsigned WT_SIZE = 9;
const unsigned CONV_W_PER_WORD = 7;
const unsigned CONV1_W_PER_WORD = 4;
const unsigned KH_PER_WORD = 4;
const unsigned BYTE_SIZE = 8;
const unsigned K = 3;

const unsigned MAX_WIDTH = WORD_SIZE;
const unsigned BANK_WIDTH = 8;
const unsigned LOG_BANK_WIDTH = 3;

const unsigned CONV_ROWS = 3;
const unsigned CONV_COLS = BANK_WIDTH+2;
const unsigned CONV_BANKS = WORD_SIZE / BANK_WIDTH;

//-------------------------------------------------------------------
// Typedefs
//-------------------------------------------------------------------
enum LayerTypeEnum {LAYER_CONV1, LAYER_CONV, LAYER_DENSE, LAYER_LAST};

typedef ap_int<WORD_SIZE> Word;
typedef ap_int<WT_SIZE> WtType;
typedef ap_uint<22> Address;
typedef ap_int<12> ConvSum;
typedef ap_int<5> ConvOut;
typedef ap_uint<10> IdxType;
typedef ap_fixed<16,4> C1Comp;
typedef ap_int<16> NormComp;
typedef ap_int<16> DenseSum;
typedef ap_fixed<16,12> DenseNorm;

typedef ap_fixed<20,2, AP_RND> C1InputType;
typedef ap_fixed<24,6, AP_RND> C1ConvType;

typedef ap_uint<32> bft_word;


//-------------------------------------------------------------------
// Template functions
//-------------------------------------------------------------------
template<typename T>
void load_kh(T& comp, const long kh_mem[], Address idx) {
  Word kh_word = kh_mem[idx/KH_PER_WORD];
  IdxType off = idx % KH_PER_WORD;
  if (off == 0)
    comp(15,0) = kh_word(15, 0);
  else if (off == 1)
    comp(15,0) = kh_word(31,16);
  else if (off == 2)
    comp(15,0) = kh_word(47,32);
  else
    comp(15,0) = kh_word(63,48);
}

#endif
