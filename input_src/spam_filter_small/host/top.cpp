/*===============================================================*/
/*                                                               */
/*                          sgd.cpp                              */
/*                                                               */
/*             Hardware function for spam filtering.             */
/*                                                               */
/*===============================================================*/

#include "../host/typedefs.h"
#include "../operators/data_in_redir.h"
#include "../operators/data_1_4_1.h"
#include "../operators/data_1_4_2.h"
#include "../operators/dotProduct_1.h"
#include "../operators/dotProduct_2.h"
#include "../operators/dotProduct_3.h"
#include "../operators/dotProduct_4.h"
#include "../operators/data_1_4_3.h"
#include "../operators/data_1_4_4.h"
#include "../operators/Sigmoid_axi.h"
#include "../operators/data_2_1.h"

//#define PROFILE
// wrapper for the streamin part
// prevent incorrect flattening
#ifdef PROFILE
  unsigned long data_in_redir_in1=0;
  unsigned long data_in_redir_out1=0;
  unsigned long data_in_redir_out2=0;
  unsigned long data_1_4_1_in1=0;
  unsigned long data_1_4_1_out1=0;
  unsigned long data_1_4_1_out2=0;
  unsigned long data_1_4_1_out3=0;
  unsigned long data_1_4_1_out4=0;
  unsigned long data_1_4_3_in1=0;
  unsigned long data_1_4_3_out1=0;
  unsigned long data_1_4_3_out2=0;
  unsigned long data_1_4_3_out3=0;
  unsigned long data_1_4_3_out4=0;
  unsigned long dotProduct_1_in1=0;
  unsigned long dotProduct_1_in2=0;
  unsigned long dotProduct_1_out1=0;
  unsigned long dotProduct_1_out2=0;
  unsigned long add_4_1_1_in1=0;
  unsigned long add_4_1_1_in2=0;
  unsigned long add_4_1_1_in3=0;
  unsigned long add_4_1_1_in4=0;
  unsigned long add_4_1_1_out1=0;
  unsigned long add_2_1_in1=0;
  unsigned long add_2_1_in2=0;
  unsigned long add_2_1_out1=0;
  unsigned long Sigmoid_axi_in1=0;
  unsigned long Sigmoid_axi_out1=0;
  unsigned long Sigmoid_axi_out2=0;
  unsigned long data_4_1_1_in1=0;
  unsigned long data_4_1_1_in2=0;
  unsigned long data_4_1_1_in3=0;
  unsigned long data_4_1_1_in4=0;
  unsigned long data_4_1_1_out1=0;
  unsigned long data_2_1_in1=0;
  unsigned long data_2_1_in2=0;
  unsigned long data_2_1_out1=0;
#endif



  // top-level function
  void top( hls::stream<ap_uint<32> > & Input_1,
  			hls::stream<ap_uint<32> > & Output_1
  			)
  {
  #pragma HLS INTERFACE ap_hs port=Input_1
  #pragma HLS INTERFACE ap_hs port=Output_1
  	static int epoch = 0;

  	hls::stream<ap_uint<32> >  Output_1_redir("sb1");
  	hls::stream<ap_uint<32> >  Output_2_redir("sb2");
  	hls::stream<ap_uint<32> >  Output_1_1_4_1("sb3");
  	hls::stream<ap_uint<32> >  Output_2_1_4_1("sb4");
  	hls::stream<ap_uint<32> >  Output_3_1_4_1("sb5");
  	hls::stream<ap_uint<32> >  Output_4_1_4_1("sb6");
  	hls::stream<ap_uint<32> >  Output_1_1_4_2("sb7");
  	hls::stream<ap_uint<32> >  Output_2_1_4_2("sb8");
  	hls::stream<ap_uint<32> >  Output_3_1_4_2("sb9");
  	hls::stream<ap_uint<32> >  Output_4_1_4_2("sb10");
  	hls::stream<ap_uint<32> >  Output_1_dot_1("sb12");
  	hls::stream<ap_uint<32> >  Output_2_dot_1("sb13");
  	hls::stream<ap_uint<32> >  Output_1_dot_2("sb14");
  	hls::stream<ap_uint<32> >  Output_2_dot_2("sb15");
  	hls::stream<ap_uint<32> >  Output_1_dot_3("sb16");
  	hls::stream<ap_uint<32> >  Output_2_dot_3("sb17");
  	hls::stream<ap_uint<32> >  Output_1_dot_4("sb18");
  	hls::stream<ap_uint<32> >  Output_2_dot_4("sb19");
  	hls::stream<ap_uint<32> >  Output_1_dot_5("sb20");
  	hls::stream<ap_uint<32> >  Output_2_dot_5("sb21");
  	hls::stream<ap_uint<32> >  Output_1_dot_6("sb22");
  	hls::stream<ap_uint<32> >  Output_2_dot_6("sb23");
  	hls::stream<ap_uint<32> >  Output_1_dot_7("sb24");
  	hls::stream<ap_uint<32> >  Output_2_dot_7("sb25");
  	hls::stream<ap_uint<32> >  Output_1_dot_8("sb26");
  	hls::stream<ap_uint<32> >  Output_2_dot_8("sb27");
  	hls::stream<ap_uint<32> >  Output_1_add_4_1_1("sb28");
  	hls::stream<ap_uint<32> >  Output_1_add_4_1_2("sb29");
  	hls::stream<ap_uint<32> >  Output_1_add_2_1("sb30");
  	hls::stream<ap_uint<32> >  Output_1_sig("sb31");
  	hls::stream<ap_uint<32> >  Output_2_sig("sb32");
  	hls::stream<ap_uint<32> >  Output_1_1_4_3("sb33");
  	hls::stream<ap_uint<32> >  Output_2_1_4_3("sb34");
  	hls::stream<ap_uint<32> >  Output_3_1_4_3("sb35");
  	hls::stream<ap_uint<32> >  Output_4_1_4_3("sb36");
  	hls::stream<ap_uint<32> >  Output_1_1_4_4("sb37");
  	hls::stream<ap_uint<32> >  Output_2_1_4_4("sb38");
  	hls::stream<ap_uint<32> >  Output_3_1_4_4("sb39");
  	hls::stream<ap_uint<32> >  Output_4_1_4_4("sb40");
  	hls::stream<ap_uint<32> >  Output_1_4_1_1("sb41");
  	hls::stream<ap_uint<32> >  Output_1_4_1_2("sb42");

  	data_in_redir(Input_1, Output_1_redir, Output_2_redir);
	data_1_4_1(Output_1_redir, Output_2_dot_1, Output_2_dot_2,
			   Output_1_1_4_1, Output_2_1_4_1,  Output_1_4_1_1);
	data_1_4_2(Output_2_redir, Output_2_dot_3, Output_2_dot_4,
			   Output_3_1_4_1, Output_4_1_4_1, Output_1_4_1_2);

  	TRAINING_INST: for( int training_id = 0; training_id < NUM_TRAINING; training_id ++ ){
  		dotProduct_1(Output_1_1_4_1, Output_1_1_4_3, Output_1_dot_1, Output_2_dot_1);
  		dotProduct_2(Output_2_1_4_1, Output_2_1_4_3, Output_1_dot_2, Output_2_dot_2);
  		dotProduct_3(Output_3_1_4_1, Output_3_1_4_3, Output_1_dot_3, Output_2_dot_3);
  		dotProduct_4(Output_4_1_4_1, Output_4_1_4_3, Output_1_dot_4, Output_2_dot_4);

  		data_1_4_3(Output_1_dot_1, Output_1_dot_2, Output_1_sig,
  				Output_1_add_4_1_1, Output_1_1_4_3, Output_2_1_4_3);
  		data_1_4_4(Output_1_dot_3, Output_1_dot_4, Output_2_sig,
  				Output_1_add_4_1_2, Output_3_1_4_3, Output_4_1_4_3);

  		Sigmoid_axi(Output_1_add_4_1_1, Output_1_add_4_1_2, Output_1_sig, Output_2_sig);

  		data_1_4_3(Output_1_dot_1, Output_1_dot_2, Output_1_sig,
  				Output_1_add_4_1_1, Output_1_1_4_3, Output_2_1_4_3);
  		data_1_4_4(Output_1_dot_3, Output_1_dot_4, Output_2_sig,
  				Output_1_add_4_1_2, Output_3_1_4_3, Output_4_1_4_3);

  		dotProduct_1(Output_1_1_4_1, Output_1_1_4_3, Output_1_dot_1, Output_2_dot_1);
  		dotProduct_2(Output_2_1_4_1, Output_2_1_4_3, Output_1_dot_2, Output_2_dot_2);
  		dotProduct_3(Output_3_1_4_1, Output_3_1_4_3, Output_1_dot_3, Output_2_dot_3);
  		dotProduct_4(Output_4_1_4_1, Output_4_1_4_3, Output_1_dot_4, Output_2_dot_4);
  	}
  	if(epoch==4){
  	  	data_1_4_1(Output_1_redir, Output_2_dot_1, Output_2_dot_2,
  	  			   Output_1_1_4_1, Output_2_1_4_1,  Output_1_4_1_1);
  	  	data_1_4_2(Output_2_redir, Output_2_dot_3, Output_2_dot_4,
  	  			   Output_3_1_4_1, Output_4_1_4_1, Output_1_4_1_2);

  		data_2_1(Output_1_4_1_1, Output_1_4_1_2, Output_1);
  	}
  	epoch++;
  }



