#include "accel.h"

#include "input_data.h"

#define IMAGE_SIZE (32 * 32)

void mem
(
  hls::stream<bft_word> & Input_1, // Main input
  hls::stream<bft_word> & Input_2, // fp_conv
  hls::stream<bft_word> & Input_3, // fp_conv
  hls::stream<bft_word> & Input_4, // bin_conv
  hls::stream<bft_word> & Input_5, // bin_conv
  hls::stream<bft_word> & Input_6, // bin_dense
  //hls::stream<bft_word> & Input_7, // bin_dense
  hls::stream<bft_word> & Output_1, // fp_conv
  hls::stream<bft_word> & Output_2, // bin_conv
  hls::stream<bft_word> & Output_3, // bin_dense
  hls::stream<bft_word> & Output_4, // Main output
  hls::stream<bft_word> & Output_5, // Start bin_conv_wt
  hls::stream<bft_word> & Output_6 // Start bin_dense_wt
  //hls::stream<bft_word> & Output_7 // Start bin_dense_wt
);

void fp_conv
(
  hls::stream<bft_word> & Input_1,
  hls::stream<bft_word> & Output_1,
  hls::stream<bft_word> & Output_2
);

void bin_conv
(
  hls::stream<bft_word> & Input_1,
  hls::stream<bft_word> & Input_2,
  hls::stream<bft_word> & Output_1,
  hls::stream<bft_word> & Output_2
);

void bin_dense
(
  hls::stream<bft_word> & Input_1,
  hls::stream<bft_word> & Input_2,
  hls::stream<bft_word> & Input_3,
  hls::stream<bft_word> & Output_1,
  hls::stream<bft_word> & Output_2
);

void bin_conv_wt_0
(
  hls::stream<bft_word> & Input_1,
  hls::stream<bft_word> & Output_1
);

void bin_conv_wt_1
(
  hls::stream<bft_word> & Input_1,
  hls::stream<bft_word> & Output_1
);

void bin_conv_wt_2
(
  hls::stream<bft_word> & Input_1,
  hls::stream<bft_word> & Output_1
);

void bin_conv_wt_3
(
  hls::stream<bft_word> & Input_1,
  hls::stream<bft_word> & Output_1
);

void bin_conv_wt_4
(
  hls::stream<bft_word> & Input_1,
  hls::stream<bft_word> & Output_1
);

void bin_conv_wt_5
(
  hls::stream<bft_word> & Input_1,
  hls::stream<bft_word> & Output_1
);

void bin_conv_wt_6
(
  hls::stream<bft_word> & Input_1,
  hls::stream<bft_word> & Output_1
);

void bin_conv_wt_7
(
  hls::stream<bft_word> & Input_1,
  hls::stream<bft_word> & Output_1
);

void bin_conv_wt_8
(
  hls::stream<bft_word> & Input_1,
  hls::stream<bft_word> & Output_1
);

void bin_dense_wt_0
(
  hls::stream<bft_word> & Input_1,
  hls::stream<bft_word> & Output_1
);

void bin_dense_wt_1
(
  hls::stream<bft_word> & Input_1,
  hls::stream<bft_word> & Output_1
);

void bin_dense_wt_2
(
  hls::stream<bft_word> & Input_1,
  hls::stream<bft_word> & Output_1
);

void bin_dense_wt_3
(
  hls::stream<bft_word> & Input_1,
  hls::stream<bft_word> & Output_1
);

void bin_dense_wt_4
(
  hls::stream<bft_word> & Input_1,
  hls::stream<bft_word> & Output_1
);

void bin_dense_wt_5
(
  hls::stream<bft_word> & Input_1,
  hls::stream<bft_word> & Output_1
);

void bin_dense_wt_6
(
  hls::stream<bft_word> & Input_1,
  hls::stream<bft_word> & Output_1
);

void bin_dense_wt_7
(
  hls::stream<bft_word> & Input_1,
  hls::stream<bft_word> & Output_1
);

void bin_dense_wt_8
(
  hls::stream<bft_word> & Input_1,
  hls::stream<bft_word> & Output_1
);

void bin_dense_wt_9
(
  hls::stream<bft_word> & Input_1,
  hls::stream<bft_word> & Output_1
);

void bin_dense_wt_10
(
  hls::stream<bft_word> & Input_1,
  hls::stream<bft_word> & Output_1
);

void bin_dense_wt_11
(
  hls::stream<bft_word> & Input_1,
  hls::stream<bft_word> & Output_1
);

void bin_dense_wt_12
(
  hls::stream<bft_word> & Input_1,
  hls::stream<bft_word> & Output_1
);

void bin_dense_wt_13
(
  hls::stream<bft_word> & Input_1,
  hls::stream<bft_word> & Output_1
);

void bin_dense_wt_14
(
  hls::stream<bft_word> & Input_1,
  hls::stream<bft_word> & Output_1
);

void bin_dense_wt_15
(
  hls::stream<bft_word> & Input_1,
  hls::stream<bft_word> & Output_1
);

int main()
{
  hls::stream<bft_word> Input_1;

  hls::stream<bft_word> Start_0;
  hls::stream<bft_word> Start_1;
  hls::stream<bft_word> Start_2;

  hls::stream<bft_word> Weight_0;
  hls::stream<bft_word> Weight_1;
  hls::stream<bft_word> Weight_2;
  hls::stream<bft_word> Weight_3;
  hls::stream<bft_word> Weight_4;
  hls::stream<bft_word> Weight_5;
  hls::stream<bft_word> Weight_6;
  hls::stream<bft_word> Weight_6_0;
  hls::stream<bft_word> Weight_7;
  hls::stream<bft_word> Weight_8;
  hls::stream<bft_word> Weight_9;
  hls::stream<bft_word> Weight_10;
  hls::stream<bft_word> Weight_11;
  hls::stream<bft_word> Weight_12;
  hls::stream<bft_word> Weight_13;
  hls::stream<bft_word> Weight_14;
  hls::stream<bft_word> Weight_15;
  hls::stream<bft_word> Weight_16;
  hls::stream<bft_word> Weight_17;
  hls::stream<bft_word> Weight_18;
  hls::stream<bft_word> Weight_19;
  hls::stream<bft_word> Weight_20;

  hls::stream<bft_word> Stream_0;
  hls::stream<bft_word> Stream_1_0;
  hls::stream<bft_word> Stream_1_1;
  hls::stream<bft_word> Stream_2;
  hls::stream<bft_word> Stream_3;
  hls::stream<bft_word> Stream_4;
  hls::stream<bft_word> Stream_5;
  hls::stream<bft_word> Stream_6;
  hls::stream<bft_word> Stream_7;
  hls::stream<bft_word> Stream_8;
  hls::stream<bft_word> Stream_9;
  hls::stream<bft_word> Stream_10;
  hls::stream<bft_word> Stream_11;
  hls::stream<bft_word> Stream_12;
  hls::stream<bft_word> Stream_13;

  hls::stream<bft_word> Output_1;

  for (int i = 0; i < IMAGE_SIZE; i++)
  {
    Word w = input_data[i];
    Input_1.write(w(63, 32));
    Input_1.write(w(31, 0));
  }

  printf("mem 0\n");
  mem(Input_1, Stream_2, Stream_4, Stream_5, Stream_6, Stream_7,
      Stream_8, Stream_10, Stream_12, Output_1, Start_0, Start_1);

  printf("bin_conv_wt_0\n");
  bin_conv_wt_0(Start_0, Weight_0);

  printf("bin_conv_wt_1\n");
  bin_conv_wt_1(Weight_0, Weight_1);

  printf("bin_conv_wt_2\n");
  bin_conv_wt_2(Weight_1, Weight_2);

  printf("bin_conv_wt_3\n");
  bin_conv_wt_3(Weight_2, Weight_3);

  printf("bin_conv_wt_4\n");
  bin_conv_wt_4(Weight_3, Weight_4);

  printf("bin_conv_wt_5\n");
  bin_conv_wt_5(Weight_4, Weight_5);

  printf("bin_conv_wt_6\n");
  bin_conv_wt_6(Weight_5, Weight_6);

  printf("bin_conv_wt_7\n");
  bin_conv_wt_7(Weight_6, Weight_6_0);

  printf("bin_conv_wt_8\n");
  bin_conv_wt_8(Weight_6_0, Stream_0);

  printf("bin_dense_wt_0\n");
  bin_dense_wt_0(Start_1, Weight_7);

  printf("bin_dense_wt_1\n");
  bin_dense_wt_1(Weight_7, Weight_8);

  printf("bin_dense_wt_2\n");
  bin_dense_wt_2(Weight_8, Weight_9);

  printf("bin_dense_wt_3\n");
  bin_dense_wt_3(Weight_9, Weight_10);

  printf("bin_dense_wt_4\n");
  bin_dense_wt_4(Weight_10, Weight_11);

  printf("bin_dense_wt_5\n");
  bin_dense_wt_5(Weight_11, Weight_12);

  printf("bin_dense_wt_6\n");
  bin_dense_wt_6(Weight_12, Weight_13);

  printf("bin_dense_wt_7\n");
  bin_dense_wt_7(Weight_13, Stream_1_0);


  printf("fp_conv\n");
  fp_conv(Stream_8, Stream_2, Start_2);

  printf("bin_dense_wt_8\n");
  bin_dense_wt_8(Start_2, Weight_14);

  printf("bin_dense_wt_9\n");
  bin_dense_wt_9(Weight_14, Weight_15);

  printf("bin_dense_wt_10\n");
  bin_dense_wt_10(Weight_15, Weight_16);

  printf("bin_dense_wt_11\n");
  bin_dense_wt_11(Weight_16, Weight_17);

  printf("bin_dense_wt_12\n");
  bin_dense_wt_12(Weight_17, Weight_18);

  printf("bin_dense_wt_13\n");
  bin_dense_wt_13(Weight_18, Weight_19);

  printf("bin_dense_wt_14\n");
  bin_dense_wt_14(Weight_19, Weight_20);

  printf("bin_dense_wt_15\n");
  bin_dense_wt_15(Weight_20, Stream_1_1);


  printf("mem 1\n");
  mem(Input_1, Stream_2,  Stream_4, Stream_5, Stream_6, Stream_7,
      Stream_8,  Stream_10, Stream_12, Output_1, Start_0, Start_1);

  printf("bin_conv_0\n");
  bin_conv(Stream_10, Stream_0, Stream_4, Stream_5);

  printf("mem 2\n");
  mem(Input_1, Stream_2,  Stream_4, Stream_5, Stream_6, Stream_7,
      Stream_8, Stream_10, Stream_12, Output_1, Start_0, Start_1);

  printf("bin_conv_1\n");
  bin_conv(Stream_10, Stream_0, Stream_4, Stream_5);

  printf("mem 3\n");
  mem(Input_1, Stream_2, Stream_4, Stream_5, Stream_6, Stream_7,
      Stream_8, Stream_10, Stream_12, Output_1, Start_0, Start_1);

  printf("bin_conv_2\n");
  bin_conv(Stream_10, Stream_0, Stream_4, Stream_5);

  printf("mem 4\n");
  mem(Input_1, Stream_2, Stream_4, Stream_5, Stream_6, Stream_7,
      Stream_8, Stream_10, Stream_12, Output_1, Start_0, Start_1);

  printf("bin_conv_3\n");
  bin_conv(Stream_10, Stream_0, Stream_4, Stream_5);

  printf("mem 5\n");
  mem(Input_1, Stream_2, Stream_4, Stream_5, Stream_6, Stream_7,
      Stream_8, Stream_10, Stream_12, Output_1, Start_0, Start_1);

  printf("bin_conv_4\n");
  bin_conv(Stream_10, Stream_0, Stream_4, Stream_5);

  printf("mem 6\n");
  mem(Input_1, Stream_2, Stream_4, Stream_5, Stream_6, Stream_7,
      Stream_8, Stream_10, Stream_12, Output_1, Start_0, Start_1);

  printf("bin_dense_0\n");
  bin_dense(Stream_12, Stream_1_0, Stream_1_1, Stream_6, Stream_7);

  printf("mem 7\n");
  mem(Input_1, Stream_2, Stream_4, Stream_5, Stream_6, Stream_7,
      Stream_8, Stream_10, Stream_12, Output_1, Start_0, Start_1);

  printf("bin_dense_1\n");
  bin_dense(Stream_12, Stream_1_0, Stream_1_1, Stream_6, Stream_7);

  printf("mem 8\n");
  mem(Input_1, Stream_2, Stream_4, Stream_5, Stream_6, Stream_7,
      Stream_8, Stream_10, Stream_12, Output_1, Start_0, Start_1);

  printf("bin_dense_2\n");
  bin_dense(Stream_12, Stream_1_0, Stream_1_1, Stream_6, Stream_7);

  printf("mem 9\n");
  mem(Input_1, Stream_2, Stream_4, Stream_5, Stream_6, Stream_7,
      Stream_8, Stream_10, Stream_12, Output_1, Start_0, Start_1);


  Word word1 = Output_1.read();
  Word word2 = Output_1.read();
  printf("%d, Output: %li\n", word1(31, 0).to_int(), word2(7, 0).to_long());
  for(int i = 0; i<126; i++){
  	word2 = Output_1.read();
  }
}
