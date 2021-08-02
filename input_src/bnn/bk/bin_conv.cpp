#include "Typedefs.h"
#include "load_kh.h"


TwoBit encode_bit(const Bit& b) {
#pragma HLS INLINE
  return (b == 0) ? TwoBit(1) : TwoBit(-1);
}

ConvOut conv3x3b(
    const TwoBit line_buffer_m[CONV_BANKS][CONV_ROWS][CONV_COLS],
    const Bit conv_params_m[K][K],
    const ap_uint<4> bank,
    const IdxType cc
) {
#pragma HLS INLINE
  ConvOut sum = 0;
  for (ap_uint<2> kr = 0; kr < K; ++kr) {
    for (ap_uint<2> kc = 0; kc < K; ++kc) {
      TwoBit data = line_buffer_m[bank][kr][cc+kc];
      const Bit& wt = conv_params_m[2-kr][2-kc];
      data[1] = (wt & data[0]) ^ data[1];
      sum += data;
    }
  }
  return sum;
}

void conv_word(
    const TwoBit line_buffer_m[CONV_BANKS][CONV_ROWS][CONV_COLS],
    const Bit conv_params_m[K][K],
    ConvOut conv_out_buffer_m[WORD_SIZE]
) {
#pragma HLS PIPELINE
  for (ap_uint<4> bank = 0; bank < CONV_BANKS; ++bank) {
    for (ap_uint<4> cc = 0; cc < BANK_WIDTH; ++cc) {
      conv_out_buffer_m[bank*BANK_WIDTH+cc] = conv3x3b( line_buffer_m, conv_params_m, bank, cc );
    }
  }
}

void process_word(
    const TwoBit  word_buffer_m[CONV_BANKS][CONV_COLS],
    const TwoBit  old_word_buffer_m[CONV_BANKS][CONV_COLS],
    const bool lb[CONV_BANKS],
    const bool rb[CONV_BANKS],
    TwoBit  line_buffer_m[CONV_BANKS][CONV_ROWS][CONV_COLS],
    const   Bit conv_params_m[K][K],
    ConvOut conv_out_buffer_m[WORD_SIZE],
    const   ap_uint<3> log_width,
    const   ap_uint<6> words_per_image,
    const   IdxType wrd
) {
#pragma HLS INLINE
  // slices_per_line = width / BANK_WIDTH
  const ap_uint<5> slices_per_line = 1 << (log_width - LOG_BANK_WIDTH);
  const bool first_wrd = (wrd == 0);
  const bool last_wrd = (wrd == words_per_image);

  // Prologue
  // Update bottom row, slices are shifted left. Some slices copied from previous word (middle row)
  for (ap_uint<4> bank = 0; bank < CONV_BANKS; ++bank) {
    ap_int<6> s_idx = bank + slices_per_line - CONV_BANKS;
    if (s_idx < 0) {
      // set to zero or copy from old word (middle row)
      for (ap_uint<4> cc = 1; cc < CONV_COLS-1; ++cc) {
        line_buffer_m[bank][CONV_ROWS-1][cc] = old_word_buffer_m[CONV_BANKS+s_idx][cc];
      }
      line_buffer_m[bank][CONV_ROWS-1][0          ] = lb[bank] ? TwoBit(0) : old_word_buffer_m[CONV_BANKS+s_idx][0];
      line_buffer_m[bank][CONV_ROWS-1][CONV_COLS-1] = rb[bank] ? TwoBit(0) : old_word_buffer_m[CONV_BANKS+s_idx][CONV_COLS-1];
    } else {
      // fill from new word
      for (ap_uint<4> cc = 1; cc < CONV_COLS-1; ++cc) {
        line_buffer_m[bank][CONV_ROWS-1][cc] = (last_wrd) ? TwoBit(0) : word_buffer_m[s_idx][cc];
      }
      line_buffer_m[bank][CONV_ROWS-1][0          ] = (last_wrd || lb[bank]) ? TwoBit(0) : word_buffer_m[s_idx][0];
      line_buffer_m[bank][CONV_ROWS-1][CONV_COLS-1] = (last_wrd || rb[bank]) ? TwoBit(0) : word_buffer_m[s_idx][CONV_COLS-1];
    }
  }



  // Convolution
  conv_word( line_buffer_m, conv_params_m, conv_out_buffer_m );

  // Update
  // Fill line buffer with lines from the new word
  for (ap_uint<4> bank = 0; bank < CONV_BANKS; ++bank) {
    // --------------------------------------------------------------
    // Top row, slices are shifted right by slices_per_line
    ap_int<6> s_idx0 = bank - slices_per_line;
    if (s_idx0 >= 0) {
      // slice from input word
      for (ap_uint<4> cc = 1; cc < CONV_COLS-1; ++cc) {
        line_buffer_m[bank][0][cc] = word_buffer_m[s_idx0][cc];
      }
      line_buffer_m[bank][0][0          ] = lb[bank] ? TwoBit(0) : word_buffer_m[s_idx0][0];
      line_buffer_m[bank][0][CONV_COLS-1] = rb[bank] ? TwoBit(0) : word_buffer_m[s_idx0][CONV_COLS-1];
    } else {
      // set to zero or copy from old word (middle row)
      for (ap_uint<4> cc = 1; cc < CONV_COLS-1; ++cc) {
        line_buffer_m[bank][0][cc] = (first_wrd) ? TwoBit(0) : old_word_buffer_m[CONV_BANKS+s_idx0][cc];
      }
      line_buffer_m[bank][0][0          ] = (first_wrd || lb[bank]) ? TwoBit(0) : old_word_buffer_m[CONV_BANKS+s_idx0][0];
      line_buffer_m[bank][0][CONV_COLS-1] = (first_wrd || rb[bank]) ? TwoBit(0) : old_word_buffer_m[CONV_BANKS+s_idx0][CONV_COLS-1];
    }

    // --------------------------------------------------------------
    // Middle row, simply copy the word into the line buffer
    for (ap_uint<4> cc = 1; cc < CONV_COLS-1; ++cc) {
      line_buffer_m[bank][1][cc] = word_buffer_m[bank][cc];
    }
    // Fill end buffer bits
    line_buffer_m[bank][1][0          ] = lb[bank] ? TwoBit(0) : word_buffer_m[bank][0];
    line_buffer_m[bank][1][CONV_COLS-1] = rb[bank] ? TwoBit(0) : word_buffer_m[bank][CONV_COLS-1];
  }


}


// -----------------------------------------------------------------------
// A single PE reads from all inputs and weights to generate a single
// output feature map.
// * Make sure this function gets inlined by VHLS, or cosim may fail!
// -----------------------------------------------------------------------
void bin_conv(
	hls::stream< Word > & Input_1,
    Word wt_mem[CONVOLVERS][C_WT_WORDS],
    NormComp nc,
    Word dmem[2][CONVOLVERS][C_DMEM_WORDS],
    ap_uint<1> d_i_idx,
    ap_uint<1> d_o_idx,
    const unsigned   n_inputs,
    const Address    o_index,
    const ap_uint<1> new_batch,
    const ap_uint<2> width_mode,  // 0=8'b, 1=16'b, 2=32'b
    const ap_uint<2> norm_mode    // 0='do nothing', 1='do norm', 2='do pool'
) {
  const ap_uint<3> log_width = width_mode + LOG_BANK_WIDTH;
  const ap_uint<5> words_per_image = 1 << (2*width_mode);
  const unsigned n_phases = n_inputs / CONVOLVERS;
  const unsigned images_per_phase = PIX_PER_PHASE >> (2*log_width);
  const unsigned WORDS_PER_PHASE = PIX_PER_PHASE / WORD_SIZE;

  Word wt_word_buffer_list[2];



  // ---------------------------------------------------------------------
  // buffers
  // ---------------------------------------------------------------------
  TwoBit  line_buffer[CONVOLVERS][CONV_BANKS][CONV_ROWS][CONV_COLS];
#pragma HLS ARRAY_PARTITION variable=line_buffer complete dim=0
  Bit     conv_params[CONVOLVERS][K][K];
#pragma HLS ARRAY_PARTITION variable=conv_params complete dim=0

  //                   32               64
  ConvSum fixed_buffer[WORDS_PER_PHASE][WORD_SIZE];
#pragma HLS ARRAY_RESHAPE     variable=fixed_buffer cyclic factor=32 dim=2


//#pragma HLS ARRAY_PARTITION variable=fixed_buffer complete dim=2
  ConvSum fixed_temp[WORD_SIZE];
#pragma HLS ARRAY_PARTITION variable=fixed_temp complete dim=0
  // per-convolver buffers
  TwoBit  word_buffer[CONVOLVERS][CONV_BANKS][CONV_COLS];
#pragma HLS ARRAY_PARTITION variable=word_buffer complete dim=0
  TwoBit  old_word_buffer[CONVOLVERS][CONV_BANKS][CONV_COLS];
#pragma HLS ARRAY_PARTITION variable=old_word_buffer complete dim=0
  ConvOut conv_out_buffer[CONVOLVERS][WORD_SIZE];
#pragma HLS ARRAY_PARTITION variable=conv_out_buffer complete dim=0
  // edge padding flag bits
  bool lb[CONV_BANKS];
#pragma HLS ARRAY_PARTITION variable=lb complete dim=0
  bool rb[CONV_BANKS];
#pragma HLS ARRAY_PARTITION variable=rb complete dim=0

  static Address wt_addr = 0;           // address of weight word
  static ap_uint<3> wt_offset = 0;      // offset 0..6 of param
  if (new_batch != 0) { wt_addr = 0; wt_offset = 0; }

  // ---------------------------------------------------------------------
  // Calculate edge padding flag bits
  const ap_uint<4> log_slice = log_width - LOG_BANK_WIDTH;
  const ap_uint<4> w_div_8 = (1 << log_width) >> 3;
  ap_uint<4> mask = ~ap_uint<4>(0);   // set mask to all 1s
  mask = mask >> (4-log_slice);
  //                               8
  for (ap_uint<4> bank = 0; bank < CONV_BANKS; ++bank) {
    #pragma HLS unroll
    const ap_uint<4> x = bank & mask;
    lb[bank] = (x == 0);          // (bank % w_div_8) == 0
    rb[bank] = (x+1 == w_div_8);  // (bank % w_div_8) == w_div_8-1
  }

  // ---------------------------------------------------------------------
  // Reset conv buffer
                          //32
  for (IdxType i = 0; i < WORDS_PER_PHASE; ++i) {
    for (IdxType j = 0; j < WORD_SIZE; ++j) {
      #pragma HLS UNROLL
      fixed_buffer[i][j] = 0;
    }
  }


  //wt_word_buffer_list[0] = wt_mem[0][wt_addr];
  //wt_word_buffer_list[1] = wt_mem[1][wt_addr];
  wt_word_buffer_list[0] = Input_1.read();
  wt_word_buffer_list[1] = Input_1.read();

  //printf("0x%08x%08x,\n", (unsigned int)wt_word_buffer_list[0](63,32), (unsigned int)wt_word_buffer_list[0](31,0));
  //printf("0x%08x%08x,\n", (unsigned int)wt_word_buffer_list[1](63,32), (unsigned int)wt_word_buffer_list[1](31,0));
  // ---------------------------------------------------------------------
  // Compute in phases
  // Each phase processes CONVOLVERS * WORDS_PER_PHASE input words
  // ---------------------------------------------------------------------
  LOOP_PHASES:
  for (ap_uint<10> p = 0; p < n_phases; p += images_per_phase) {
#pragma HLS LOOP_TRIPCOUNT min=1 max=512
    // wrd = which word in the current image
    // wrd_phase = which wrd in the current phase
    ap_uint<8> wrd = 0;
    ap_uint<8> wrd_phase = 0;

    // Load a word each iteration, and then process it
    // We load WORDS_PER_PHASE words per phase, however we also need 1 extra "empty"
    // iteration per image in the phase to do the loop epilogue, so the loop bound
    // is WORDS_PER_PHASE + images_per_phase
    LOOP_WORDS_IN_PHASE:
    for (ap_uint<8> count = 0; count < WORDS_PER_PHASE+images_per_phase; ++count) {
#pragma HLS DEPENDENCE variable=fixed_buffer inter false
#pragma HLS LOOP_TRIPCOUNT min=17 max=32
#pragma HLS PIPELINE
      // First word of an image
      if (wrd == 0) {
        Word wt_word_buffer[CONVOLVERS];

        // -------------------------------------------------------------------
        // Load param word
        // Each word contains CONV_W_PER_WORD weight filters, after we use
        // them all we should load the next word
        // -------------------------------------------------------------------
        LOOP_WT_WORDS:
        for (IdxType m = 0; m < CONVOLVERS; ++m) {
          /*if (wt_offset == 0)
            wt_word_buffer[m] = wt_mem[m][wt_addr];
          else
            wt_word_buffer[m] = wt_word_buffer[m] >> WT_SIZE;
          */
          //wt_word_buffer[m] = wt_mem[m][wt_addr] >> ap_uint<6>(WT_SIZE*wt_offset);
          wt_word_buffer[m] = wt_word_buffer_list[m] >> ap_uint<6>(WT_SIZE*wt_offset);
        }
        if (wt_offset == CONV_W_PER_WORD-1) {
          ++wt_addr;
          //wt_word_buffer_list[0] = wt_mem[0][wt_addr];
          //wt_word_buffer_list[1] = wt_mem[1][wt_addr];
          wt_word_buffer_list[0] = Input_1.read();
          wt_word_buffer_list[1] = Input_1.read();
          //printf("0x%08x%08x,\n", (unsigned int)wt_word_buffer_list[0](63,32), (unsigned int)wt_word_buffer_list[0](31,0));
          //printf("0x%08x%08x,\n", (unsigned int)wt_word_buffer_list[1](63,32), (unsigned int)wt_word_buffer_list[1](31,0));
          wt_offset = 0;
        } else {
          ++wt_offset;
        }
        //print_wt_word(wt_word_buffer[0]);

        // -------------------------------------------------------------------
        // Load params
        // Each word contains CONV_W_PER_WORD weight filters packed into the first
        // 63 bits, the last bit is unused. Wts are stored in output-major order.
        // -------------------------------------------------------------------
        LOOP_LOAD_WTS:
        for (IdxType m = 0; m < CONVOLVERS; ++m) {
          for (ap_uint<2> kr = 0; kr < K; ++kr) {
            for (ap_uint<2> kc = 0; kc < K; ++kc)
              conv_params[m][kr][kc] = wt_word_buffer[m][kr*K+kc];
          }
        }
      }

      // -------------------------------------------------------------------
      // Every word in an image
      // -------------------------------------------------------------------
      // Load word
      // (wrd_phase-wrd) is which wrd in the current phase, aligned to img boundary
      if (wrd != words_per_image) {
        LOOP_CONVOLVER_LOAD:
        for (IdxType m = 0; m < CONVOLVERS; ++m) {
          Word word = dmem[d_i_idx][m][p*words_per_image + wrd_phase];
          for (IdxType bank = 0; bank < CONV_BANKS; ++bank) {
            for (IdxType cc = 0; cc < CONV_COLS-2; ++cc) {
              word_buffer[m][bank][cc+1] = encode_bit(word[ap_uint<6>(bank*BANK_WIDTH+cc)]);
            }
            word_buffer[m][bank][0          ] = (bank==0)            ?
              TwoBit(0) : encode_bit(word[ap_uint<6>(bank*BANK_WIDTH-1)]);
            word_buffer[m][bank][CONV_COLS-1] = (bank==CONV_BANKS-1) ?
              TwoBit(0) : encode_bit(word[ap_uint<6>(bank*BANK_WIDTH+BANK_WIDTH)]);
          }
        }
      }

      // Compute
      LOOP_CONVOLVERS:
      for (IdxType m = 0; m < CONVOLVERS; ++m) {
        // Do the following for each word in an image
        process_word( word_buffer[m], old_word_buffer[m], lb, rb, line_buffer[m], conv_params[m],
            conv_out_buffer[m], log_width, words_per_image, wrd );
      } // CONVOLVERS

      for (IdxType m = 0; m < CONVOLVERS; ++m) {
        for (IdxType bank = 0; bank < CONV_BANKS; ++bank) {
          for (IdxType cc = 0; cc < CONV_COLS; ++cc) {
            old_word_buffer[m][bank][cc] = word_buffer[m][bank][cc];
        } }
      }

      // -------------------------------------------------------------------
      // Sum results across convolvers
      // -------------------------------------------------------------------
      for (IdxType i = 0; i < WORD_SIZE; ++i) {
        // Ignore conv results after processing the first word
        if (wrd > 0) {
          ConvSum s = 0;
          for (IdxType m = 0; m < CONVOLVERS; ++m)
            s += conv_out_buffer[m][i];
          fixed_buffer[wrd_phase-1][i] += s;
        }
      }

      // -------------------------------------------------------------------
      // Increment counters
      // -------------------------------------------------------------------
      if (wrd != words_per_image) {
        wrd++;
        wrd_phase++;
      } else {
        wrd = 0;
      }
    } // wrd_phase = 0 .. WORDS_PER_PHASE

  } // n_phases



  LOOP_ACC_PHASES:
  for (ap_uint<5> w = 0; w < words_per_image; ++w) {
#pragma HLS PIPELINE
#pragma HLS LOOP_TRIPCOUNT min=1 max=1
    for (IdxType b = 0; b < WORD_SIZE; ++b) {
      #pragma HLS unroll
      fixed_temp[b] = fixed_buffer[w][b];
    }

    LOOP_ACC_PHASES_I:
    for (ap_uint<8> i = words_per_image; i < WORDS_PER_PHASE; i += words_per_image) {
#pragma HLS LOOP_TRIPCOUNT min=1 max=16
      for (IdxType b = 0; b < WORD_SIZE; ++b) {
        fixed_temp[b] += fixed_buffer[w+i][b];
    } }

    for (IdxType b = 0; b < WORD_SIZE; ++b) {
      #pragma HLS unroll
      fixed_buffer[w][b] = fixed_temp[b];
    }
  }

  const Address bank_idx = o_index % CONVOLVERS;
  const Address bank_off = o_index / CONVOLVERS;
  const ap_uint<5> pool_width = 1 << (log_width-1);

  static Word outword;
  Word poolword;
  LOOP_BATCH_NORM:
  for (ap_uint<6> w = 0; w < words_per_image; ++w) {
#pragma HLS LOOP_TRIPCOUNT min=1 max=16
#pragma HLS PIPELINE
    Word binword;
    Address o_bank_idx = bank_idx;
    Address o_bank_offset = bank_off*words_per_image + w;
    const ap_uint<6> out_offset = (w % 4) << 4;

    for (ap_uint<7> i = 0; i < WORD_SIZE; ++i) {
      binword[i] = (fixed_buffer[w][i] >= nc) ? 0 : 1;
    }

    if (norm_mode == 1) {
      outword = binword;
    }
    else if (norm_mode == 2) {
      // horizontal pooling first
      ap_int<WORD_SIZE/2> poolword_h;
      for (ap_uint<6> i = 0; i < WORD_SIZE/2; ++i) {
        poolword_h[i] = binword[2*i] & binword[2*i+1];
      }

      // vertical pooling
      for (ap_uint<6> i = 0; i < WORD_SIZE/4; ++i) {
        // source indices
        ap_uint<5> i0 = i >> (log_width-1);
        i0 = (i0 << log_width) + i(log_width-2,0);
        ap_uint<5> i1 = i0 + pool_width;
        // dest index
        ap_uint<6> d0 = out_offset + i;
        poolword[d0] = poolword_h[i0] & poolword_h[i1];
      }

      // For log_width > 3 we can just assign the word, but log_width = 3 means width = 8,
      // which means pooled width = 4, which is only 16 bits, which is less than 1 Word.
      // So each time we get here we only have 16 bits, meaning we have to accumulate four
      // of these 16-bit batches before writing a word out.
      if (log_width != LOG_BANK_WIDTH) {
        o_bank_offset /= 4;
        outword = poolword;
      } else {
        outword = outword >> WORD_SIZE/4;
        outword(63,48) = poolword(15,0);
        o_bank_idx = (o_index/4)%CONVOLVERS;
        o_bank_offset = (o_index/4)/CONVOLVERS;
      }
    }

    dmem[d_o_idx][o_bank_idx][o_bank_offset] = outword;
  }
}

