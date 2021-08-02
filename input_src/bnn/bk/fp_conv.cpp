#include "Typedefs.h"
#include "load_kh.h"


void fp_conv(
	hls::stream< DMA_Word > & Input_1,
	hls::stream< Word > & Output_1
) {
#pragma HLS INTERFACE ap_hs port=Output_1
#pragma HLS INTERFACE ap_hs port=Input_1
#pragma HLS INTERFACE ap_hs port=Input_2
#include "fp_conv_par.h"

  const unsigned M = 3;
  const unsigned S = 32;
  const unsigned OUTWORDS = 16; // words per output image
  Word kh_mem[KH_WORDS];
#pragma HLS ARRAY_PARTITION variable=kh_mem complete dim=1
  C1InputType win[M][K][K];
#pragma HLS ARRAY_PARTITION variable=win complete dim=0
  C1InputType lbuf[M][K-1][S];
//#pragma HLS ARRAY_PARTITION variable=lbuf complete dim=0
  Word outwords[OUTWORDS];
#pragma HLS ARRAY_PARTITION variable=outwords complete dim=0
  WtType wtbuf[M];
#pragma HLS ARRAY_PARTITION variable=wtbuf complete dim=0

  Address wt_offset = 0;
  ap_uint<3> wt_addr = 0;

  ap_uint<1> d_i_idx = 1;
  ap_uint<1> d_o_idx = 0;
  const Address kh_index = 0;
  const Address o_index = 0;
  const unsigned N = 128;
  Word dmem[2][CONVOLVERS][C_DMEM_WORDS];
#pragma HLS ARRAY_PARTITION variable=dmem complete dim=2
#pragma HLS ARRAY_PARTITION variable=dmem complete dim=1

  int wt_cnt=KH_WORDS;

  fp_data_in: for(int in_data_cnt=0; in_data_cnt<1024; in_data_cnt++) {
#pragma HLS PIPELINE II=1
	DMA_Word in_dmp;
	in_dmp = Input_1.read();
    dmem[1][0][in_data_cnt] = in_dmp(63,0);
  }

  for(int kh_i=0; kh_i<KH_WORDS; kh_i++)
  {
  	kh_mem[kh_i] = fp_conv_wt[kh_i];
  	//printf("%08x%08x,\n", (unsigned int) kh_mem[kh_i](63,32), (unsigned int) kh_mem[kh_i](31,0));
  }

  // Parallelized across m, better for HLS
  LOOP_FP_CONV_O:
  for (IdxType n = 0; n < N; ++n) {
#pragma HLS LOOP_TRIPCOUNT min=1 max=32

    // clear linebuffers for each new output map
    LOOP_RESET_LINEBUFFERS:
    for (IdxType m = 0; m < M; ++m) {
#pragma HLS UNROLL region
#pragma HLS UNROLL
      PROLOG_COLS: for (IdxType c = 0; c < S; ++c) {
        PROLOG_ROWS: for (IdxType r = 0; r < K/2; ++r) {
          for (IdxType lr = 0; lr < K-2; ++lr) {
            lbuf[m][lr][c] = lbuf[m][lr+1][c];
          }
          lbuf[m][K-2][c] = 0;
      } }
    }

    // The weights for the 1st conv layer are just laid out
    // linearly across wt_mem, 3 weights per 64-bit word

    Word wt_word =  fp_conv_wt[wt_cnt];//wt_mem[n % CONVOLVERS][n / CONVOLVERS];
    wt_cnt++;
    //printf("%08x%08x,\n", (unsigned int) wt_word(63,32), (unsigned int) wt_word(31,0));
    LOOP_LOAD_WTS:
    for (ap_uint<2> m = 0; m < M; ++m) {
#pragma HLS UNROLL
      wtbuf[m] = wt_word((m+1)*WT_SIZE-1, m*WT_SIZE);
    }

    // load batch norm params
    C1Comp nc;

    load_kh(nc, kh_mem, (kh_index+n));
    //printf ("  n=%3d, nc=%6.3f\n", n.to_int(), nc.to_float());

    // begin convolution
    LOOP_CONV_ROWS: for (IdxType r = 0; r < S+1; ++r) {
      LOOP_CONV_COLS: for (IdxType c = 0; c < S+1; ++c) {
#pragma HLS PIPELINE
        // load input word
        Word inword = 0;
        if (r < S && c < S) {
          const Address addr = r*S + c;
          inword = dmem[d_i_idx][addr/C_DMEM_WORDS][addr%C_DMEM_WORDS];

        }

        for (ap_uint<2> m = 0; m < M; ++m) {
          // load data: the value of pix is either the pixel at [r,c]
          // 0 -> +1, -1 -> -1
          // or -> 0 for padding around the boundaries
          C1InputType pix;
          const unsigned W = pix.length();
          pix(W-1,0) = inword(W-1+m*W, m*W);

          // window: shift left, leaving rightmost col for new data
          for (IdxType wr = 0; wr < K; ++wr) {
            for (IdxType wc = 0; wc < K-1; ++wc) {
              win[m][wr][wc] = win[m][wr][wc+1];
          } }

          // window: fill top K-1 pixels of rightmost column from lbuf
          for (IdxType wr = 0; wr < K-1; ++wr) {
            C1InputType val = (c != S) ? lbuf[m][wr][c] : C1InputType(0);
            win[m][wr][K-1] = val;
          }

          // window: fill bottom right with new input pixel
          win[m][K-1][K-1] = pix;

          // lbuf: shift up column c
          if (c != S) {
            for (IdxType lr = 0; lr < K-2; ++lr) {
              lbuf[m][lr][c] = lbuf[m][lr+1][c];
            }
            lbuf[m][K-2][c] = pix;
          }
        } // m

        // only perform the conv and store if legal position
        if (r > 0 && c > 0) {
          C1ConvType res = 0;
          for (ap_uint<2> m = 0; m < M; ++m) {
            for (ap_uint<2> wr = 0; wr < K; ++wr) {
              for (ap_uint<2> wc = 0; wc < K; ++wc) {
                const C1InputType& pix = win[m][wr][wc];
                const Bit& b = wtbuf[m][8-(wr*K+wc)];
                res += (b==0) ? pix : (C1InputType)(-pix);
            } }
          }

          // perform normalization right here
          outwords[(r-1)/2][((r-1)%2)*S + (c-1)] =
            (res >= nc) ? Bit(0) : Bit(-1);
        }

      } // CONV_COLS
    } // CONV_ROWS

    // Here i is the word offset within the outwords buffer
    LOOP_OUTPUT:
    for (IdxType i = 0; i < OUTWORDS; ++i) {
#pragma HLS PIPELINE
      Address img_idx = o_index+n;
      Address bank_idx = img_idx % CONVOLVERS;
      Address bank_off = img_idx / CONVOLVERS;
      dmem[d_o_idx][bank_idx][bank_off*OUTWORDS + i] = outwords[i];
      //printf("d_o_idx = %d, bank_idx = %d, bank_off*OUTWORDS + i = %d\n",
      //        		  (unsigned int)(d_o_idx),
      //				  (unsigned int)(bank_idx),
      //				  (unsigned int)(bank_off*OUTWORDS + i));
    }
  } // n
  //for(unsigned int dmem_i=0; dmem_i<2; dmem_i++)
  for(unsigned int dmem_j=0; dmem_j<CONVOLVERS; dmem_j++)
    for(unsigned int dmem_k=0; dmem_k<C_DMEM_WORDS; dmem_k++)
      Output_1.write(dmem[0][dmem_j][dmem_k]);

}
