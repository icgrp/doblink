#include <backends/cxxrtl/cxxrtl.h>

#if defined(CXXRTL_INCLUDE_CAPI_IMPL) || \
    defined(CXXRTL_INCLUDE_VCD_CAPI_IMPL)
#include <backends/cxxrtl/cxxrtl_capi.cc>
#endif

#if defined(CXXRTL_INCLUDE_VCD_CAPI_IMPL)
#include <backends/cxxrtl/cxxrtl_vcd_capi.cc>
#endif

using namespace cxxrtl_yosys;

namespace cxxrtl_design {

// \CORE_GENERATION_INFO: matmul_partition_matmul_partition,hls_ip_2020_2,{HLS_INPUT_TYPE=cxx,HLS_INPUT_FLOAT=0,HLS_INPUT_FIXED=0,HLS_INPUT_PART=xc7a200t-sbg484-1,HLS_INPUT_CLOCK=10.000000,HLS_INPUT_ARCH=others,HLS_SYN_CLOCK=4.559000,HLS_SYN_LAT=2306,HLS_SYN_TPT=none,HLS_SYN_MEM=16,HLS_SYN_DSP=0,HLS_SYN_FF=507,HLS_SYN_LUT=525,HLS_VERSION=2020_2}
// \top: 1
// \src: matmul_partition.v:12.1-663.10
struct p_matmul__partition : public module {
	// \hdlname: regslice_both_Output_1_V_U B_V_data_1_state
	// \src: matmul_partition.v:194.1-204.2|matmul_partition_regslice_both.v:25.13-25.29
	wire<2> p_regslice__both__Output__1__V__U_2e_B__V__data__1__state;
	// \hdlname: regslice_both_Output_1_V_U B_V_data_1_payload_A
	// \src: matmul_partition.v:194.1-204.2|matmul_partition_regslice_both.v:31.23-31.43
	wire<32> p_regslice__both__Output__1__V__U_2e_B__V__data__1__payload__A;
	// \hdlname: regslice_both_Output_1_V_U B_V_data_1_payload_B
	// \src: matmul_partition.v:194.1-204.2|matmul_partition_regslice_both.v:32.23-32.43
	wire<32> p_regslice__both__Output__1__V__U_2e_B__V__data__1__payload__B;
	// \hdlname: regslice_both_Output_1_V_U B_V_data_1_sel_rd
	// \src: matmul_partition.v:194.1-204.2|matmul_partition_regslice_both.v:33.8-33.25
	wire<1> p_regslice__both__Output__1__V__U_2e_B__V__data__1__sel__rd;
	// \hdlname: regslice_both_Output_1_V_U B_V_data_1_sel_wr
	// \src: matmul_partition.v:194.1-204.2|matmul_partition_regslice_both.v:34.8-34.25
	wire<1> p_regslice__both__Output__1__V__U_2e_B__V__data__1__sel__wr;
	// \hdlname: regslice_both_Input_1_V_U B_V_data_1_state
	// \src: matmul_partition.v:180.1-190.2|matmul_partition_regslice_both.v:25.13-25.29
	wire<2> p_regslice__both__Input__1__V__U_2e_B__V__data__1__state;
	// \hdlname: regslice_both_Input_1_V_U B_V_data_1_payload_A
	// \src: matmul_partition.v:180.1-190.2|matmul_partition_regslice_both.v:31.23-31.43
	wire<32> p_regslice__both__Input__1__V__U_2e_B__V__data__1__payload__A;
	// \hdlname: regslice_both_Input_1_V_U B_V_data_1_payload_B
	// \src: matmul_partition.v:180.1-190.2|matmul_partition_regslice_both.v:32.23-32.43
	wire<32> p_regslice__both__Input__1__V__U_2e_B__V__data__1__payload__B;
	// \hdlname: regslice_both_Input_1_V_U B_V_data_1_sel_rd
	// \src: matmul_partition.v:180.1-190.2|matmul_partition_regslice_both.v:33.8-33.25
	wire<1> p_regslice__both__Input__1__V__U_2e_B__V__data__1__sel__rd;
	// \hdlname: regslice_both_Input_1_V_U B_V_data_1_sel_wr
	// \src: matmul_partition.v:180.1-190.2|matmul_partition_regslice_both.v:34.8-34.25
	wire<1> p_regslice__both__Input__1__V__U_2e_B__V__data__1__sel__wr;
	// \src: matmul_partition.v:168.1-176.2|matmul_partition_A_V_0.v:0.0-0.0|matmul_partition_A_V_0.v:59.28-65.15
	wire<256> i_flatten_5c_A__V__1__U_2e__5c_matmul__partition__A__V__0__ram__U_2e__24_memwr_24__5c_ram_24_matmul__partition__A__V__0_2e_v_3a_28_24_1__EN;
	// \src: matmul_partition.v:168.1-176.2|matmul_partition_A_V_0.v:0.0-0.0|matmul_partition_A_V_0.v:59.28-65.15
	wire<256> i_flatten_5c_A__V__1__U_2e__5c_matmul__partition__A__V__0__ram__U_2e__24_memwr_24__5c_ram_24_matmul__partition__A__V__0_2e_v_3a_28_24_1__DATA;
	// \src: matmul_partition.v:168.1-176.2|matmul_partition_A_V_0.v:0.0-0.0|matmul_partition_A_V_0.v:59.28-65.15
	wire<6> i_flatten_5c_A__V__1__U_2e__5c_matmul__partition__A__V__0__ram__U_2e__24_memwr_24__5c_ram_24_matmul__partition__A__V__0_2e_v_3a_28_24_1__ADDR;
	// \hdlname: A_V_1_U matmul_partition_A_V_0_ram_U q0
	// \src: matmul_partition.v:168.1-176.2|matmul_partition_A_V_0.v:16.24-16.26|matmul_partition_A_V_0.v:59.28-65.15
	wire<256> p_A__V__1__U_2e_matmul__partition__A__V__0__ram__U_2e_q0;
	// \src: matmul_partition.v:154.1-162.2|matmul_partition_A_V_0.v:0.0-0.0|matmul_partition_A_V_0.v:59.28-65.15
	wire<256> i_flatten_5c_A__V__0__U_2e__5c_matmul__partition__A__V__0__ram__U_2e__24_memwr_24__5c_ram_24_matmul__partition__A__V__0_2e_v_3a_28_24_1__EN;
	// \src: matmul_partition.v:154.1-162.2|matmul_partition_A_V_0.v:0.0-0.0|matmul_partition_A_V_0.v:59.28-65.15
	wire<256> i_flatten_5c_A__V__0__U_2e__5c_matmul__partition__A__V__0__ram__U_2e__24_memwr_24__5c_ram_24_matmul__partition__A__V__0_2e_v_3a_28_24_1__DATA;
	// \src: matmul_partition.v:154.1-162.2|matmul_partition_A_V_0.v:0.0-0.0|matmul_partition_A_V_0.v:59.28-65.15
	wire<6> i_flatten_5c_A__V__0__U_2e__5c_matmul__partition__A__V__0__ram__U_2e__24_memwr_24__5c_ram_24_matmul__partition__A__V__0_2e_v_3a_28_24_1__ADDR;
	// \hdlname: A_V_0_U matmul_partition_A_V_0_ram_U q0
	// \src: matmul_partition.v:154.1-162.2|matmul_partition_A_V_0.v:16.24-16.26|matmul_partition_A_V_0.v:59.28-65.15
	wire<256> p_A__V__0__U_2e_matmul__partition__A__V__0__ram__U_2e_q0;
	// \src: matmul_partition.v:125.13-125.24
	wire<8> p_i__1__reg__156;
	// \src: matmul_partition.v:124.13-124.22
	wire<8> p_i__reg__145;
	// \src: matmul_partition.v:115.14-115.35
	wire<32> p_trunc__ln674__1__reg__449;
	// \src: matmul_partition.v:113.14-113.32
	wire<32> p_p__Result__6__reg__444;
	// \src: matmul_partition.v:112.14-112.32
	wire<32> p_p__Result__5__reg__439;
	// \src: matmul_partition.v:111.14-111.32
	wire<32> p_p__Result__4__reg__434;
	// \src: matmul_partition.v:110.14-110.32
	wire<32> p_p__Result__3__reg__429;
	// \src: matmul_partition.v:109.14-109.32
	wire<32> p_p__Result__2__reg__424;
	// \src: matmul_partition.v:108.14-108.32
	wire<32> p_p__Result__1__reg__419;
	// \src: matmul_partition.v:107.13-107.31
	wire<1> p_icmp__ln674__reg__409;
	// \src: matmul_partition.v:102.13-102.29
	wire<8> p_add__ln64__reg__391;
	// \src: matmul_partition.v:100.14-100.29
	wire<32> p_tmp__V__6__reg__386;
	// \src: matmul_partition.v:99.14-99.29
	wire<32> p_tmp__V__5__reg__381;
	// \src: matmul_partition.v:98.14-98.29
	wire<32> p_tmp__V__4__reg__376;
	// \src: matmul_partition.v:97.14-97.29
	wire<32> p_tmp__V__3__reg__371;
	// \src: matmul_partition.v:96.14-96.29
	wire<32> p_tmp__V__2__reg__366;
	// \src: matmul_partition.v:95.14-95.29
	wire<32> p_tmp__V__1__reg__361;
	// \src: matmul_partition.v:94.13-94.31
	wire<1> p_icmp__ln414__reg__357;
	// \src: matmul_partition.v:92.13-92.32
	wire<6> p_trunc__ln414__reg__352;
	// \src: matmul_partition.v:90.14-90.27
	wire<32> p_tmp__V__reg__347;
	// \src: matmul_partition.v:88.13-88.29
	wire<8> p_add__ln50__reg__339;
	// \init: 1
	// \fsm_encoding: none
	// \src: matmul_partition.v:65.42-65.51
	wire<19> p_ap__CS__fsm {0x1u};
	// \src: matmul_partition.v:58.9-58.26
	/*input*/ value<1> p_Output__1__V__TREADY;
	// \src: matmul_partition.v:57.10-57.27
	/*output*/ value<1> p_Output__1__V__TVALID;
	// \src: matmul_partition.v:56.16-56.32
	/*output*/ value<32> p_Output__1__V__TDATA;
	// \src: matmul_partition.v:55.10-55.26
	/*output*/ value<1> p_Input__1__V__TREADY;
	// \src: matmul_partition.v:54.9-54.25
	/*input*/ value<1> p_Input__1__V__TVALID;
	// \src: matmul_partition.v:53.15-53.30
	/*input*/ value<32> p_Input__1__V__TDATA;
	// \src: matmul_partition.v:52.10-52.18
	/*output*/ value<1> p_ap__ready;
	// \src: matmul_partition.v:51.10-51.17
	/*output*/ value<1> p_ap__idle;
	// \src: matmul_partition.v:50.10-50.17
	/*output*/ value<1> p_ap__done;
	// \src: matmul_partition.v:49.9-49.17
	/*input*/ value<1> p_ap__start;
	// \src: matmul_partition.v:48.9-48.17
	/*input*/ value<1> p_ap__rst__n;
	// \src: matmul_partition.v:47.9-47.15
	/*input*/ value<1> p_ap__clk;
	value<1> prev_p_ap__clk;
	bool posedge_p_ap__clk() const {
		return !prev_p_ap__clk.slice<0>().val() && p_ap__clk.slice<0>().val();
	}
	// \hdlname: regslice_both_Output_1_V_U apdone_blk
	// \src: matmul_partition.v:194.1-204.2|matmul_partition_regslice_both.v:21.12-21.22
	/*outline*/ value<1> p_regslice__both__Output__1__V__U_2e_apdone__blk;
	// \hdlname: regslice_both_Output_1_V_U B_V_data_1_data_out
	// \src: matmul_partition.v:194.1-204.2|matmul_partition_regslice_both.v:27.23-27.42
	/*outline*/ value<32> p_regslice__both__Output__1__V__U_2e_B__V__data__1__data__out;
	// \hdlname: regslice_both_Output_1_V_U B_V_data_1_vld_reg
	// \src: matmul_partition.v:194.1-204.2|matmul_partition_regslice_both.v:28.9-28.27
	/*outline*/ value<1> p_regslice__both__Output__1__V__U_2e_B__V__data__1__vld__reg;
	// \hdlname: regslice_both_Output_1_V_U B_V_data_1_vld_out
	// \src: matmul_partition.v:194.1-204.2|matmul_partition_regslice_both.v:30.9-30.27
	/*outline*/ value<1> p_regslice__both__Output__1__V__U_2e_B__V__data__1__vld__out;
	// \hdlname: regslice_both_Output_1_V_U B_V_data_1_load_A
	// \src: matmul_partition.v:194.1-204.2|matmul_partition_regslice_both.v:36.9-36.26
	/*outline*/ value<1> p_regslice__both__Output__1__V__U_2e_B__V__data__1__load__A;
	// \hdlname: regslice_both_Output_1_V_U B_V_data_1_load_B
	// \src: matmul_partition.v:194.1-204.2|matmul_partition_regslice_both.v:37.9-37.26
	/*outline*/ value<1> p_regslice__both__Output__1__V__U_2e_B__V__data__1__load__B;
	// \hdlname: regslice_both_Output_1_V_U B_V_data_1_state_cmp_full
	// \src: matmul_partition.v:194.1-204.2|matmul_partition_regslice_both.v:38.9-38.34
	/*outline*/ value<1> p_regslice__both__Output__1__V__U_2e_B__V__data__1__state__cmp__full;
	// \hdlname: regslice_both_Output_1_V_U B_V_data_1_ack_in
	// \src: matmul_partition.v:194.1-204.2|matmul_partition_regslice_both.v:39.9-39.26
	/*outline*/ value<1> p_regslice__both__Output__1__V__U_2e_B__V__data__1__ack__in;
	// \hdlname: regslice_both_Input_1_V_U apdone_blk
	// \src: matmul_partition.v:180.1-190.2|matmul_partition_regslice_both.v:21.12-21.22
	/*outline*/ value<1> p_regslice__both__Input__1__V__U_2e_apdone__blk;
	// \hdlname: regslice_both_Input_1_V_U B_V_data_1_data_out
	// \src: matmul_partition.v:180.1-190.2|matmul_partition_regslice_both.v:27.23-27.42
	/*outline*/ value<32> p_regslice__both__Input__1__V__U_2e_B__V__data__1__data__out;
	// \hdlname: regslice_both_Input_1_V_U B_V_data_1_vld_reg
	// \src: matmul_partition.v:180.1-190.2|matmul_partition_regslice_both.v:28.9-28.27
	/*outline*/ value<1> p_regslice__both__Input__1__V__U_2e_B__V__data__1__vld__reg;
	// \hdlname: regslice_both_Input_1_V_U B_V_data_1_vld_out
	// \src: matmul_partition.v:180.1-190.2|matmul_partition_regslice_both.v:30.9-30.27
	/*outline*/ value<1> p_regslice__both__Input__1__V__U_2e_B__V__data__1__vld__out;
	// \hdlname: regslice_both_Input_1_V_U B_V_data_1_load_A
	// \src: matmul_partition.v:180.1-190.2|matmul_partition_regslice_both.v:36.9-36.26
	/*outline*/ value<1> p_regslice__both__Input__1__V__U_2e_B__V__data__1__load__A;
	// \hdlname: regslice_both_Input_1_V_U B_V_data_1_load_B
	// \src: matmul_partition.v:180.1-190.2|matmul_partition_regslice_both.v:37.9-37.26
	/*outline*/ value<1> p_regslice__both__Input__1__V__U_2e_B__V__data__1__load__B;
	// \hdlname: regslice_both_Input_1_V_U B_V_data_1_state_cmp_full
	// \src: matmul_partition.v:180.1-190.2|matmul_partition_regslice_both.v:38.9-38.34
	/*outline*/ value<1> p_regslice__both__Input__1__V__U_2e_B__V__data__1__state__cmp__full;
	// \hdlname: regslice_both_Input_1_V_U B_V_data_1_ack_in
	// \src: matmul_partition.v:180.1-190.2|matmul_partition_regslice_both.v:39.9-39.26
	/*outline*/ value<1> p_regslice__both__Input__1__V__U_2e_B__V__data__1__ack__in;
	// \src: matmul_partition.v:143.9-143.18
	/*outline*/ value<1> p_ap__ce__reg;
	// \src: matmul_partition.v:140.8-140.38
	/*outline*/ value<1> p_Output__1__V__TVALID__int__regslice;
	// \src: matmul_partition.v:139.14-139.43
	/*outline*/ value<32> p_Output__1__V__TDATA__int__regslice;
	// \src: matmul_partition.v:137.8-137.37
	/*outline*/ value<1> p_Input__1__V__TREADY__int__regslice;
	// \src: matmul_partition.v:133.14-133.23
	/*outline*/ value<19> p_ap__NS__fsm;
	// \src: matmul_partition.v:132.16-132.34
	/*outline*/ value<256> p_p__Val2__s__fu__257__p3;
	// \src: matmul_partition.v:131.14-131.29
	/*outline*/ value<2> p_tmp__1__fu__241__p4;
	// \src: matmul_partition.v:130.14-130.35
	/*outline*/ value<6> p_trunc__ln674__fu__231__p1;
	// \src: matmul_partition.v:129.14-129.27
	/*outline*/ value<2> p_tmp__fu__183__p4;
	// \src: matmul_partition.v:128.16-128.36
	/*outline*/ value<256> p_p__Result__s__fu__204__p9;
	// \src: matmul_partition.v:127.15-127.35
	/*outline*/ value<64> p_zext__ln674__fu__235__p1;
	// \src: matmul_partition.v:126.15-126.35
	/*outline*/ value<64> p_zext__ln414__fu__199__p1;
	// \src: matmul_partition.v:122.8-122.17
	/*outline*/ value<1> p_A__V__1__we0;
	// \src: matmul_partition.v:121.8-121.17
	/*outline*/ value<1> p_A__V__1__ce0;
	// \src: matmul_partition.v:120.13-120.27
	/*outline*/ value<6> p_A__V__1__address0;
	// \src: matmul_partition.v:118.8-118.17
	/*outline*/ value<1> p_A__V__0__we0;
	// \src: matmul_partition.v:117.8-117.17
	/*outline*/ value<1> p_A__V__0__ce0;
	// \src: matmul_partition.v:116.13-116.27
	/*outline*/ value<6> p_A__V__0__address0;
	// \src: matmul_partition.v:114.15-114.38
	/*outline*/ value<32> p_trunc__ln674__1__fu__335__p1;
	// \src: matmul_partition.v:106.14-106.34
	/*outline*/ value<1> p_icmp__ln674__fu__251__p2;
	// \src: matmul_partition.v:105.14-105.33
	/*outline*/ value<1> p_icmp__ln64__fu__225__p2;
	// \src: matmul_partition.v:103.9-103.26
	/*outline*/ value<1> p_ap__CS__fsm__state10;
	// \src: matmul_partition.v:101.14-101.32
	/*outline*/ value<8> p_add__ln64__fu__219__p2;
	// \src: matmul_partition.v:93.14-93.34
	/*outline*/ value<1> p_icmp__ln414__fu__193__p2;
	// \src: matmul_partition.v:91.14-91.35
	/*outline*/ value<6> p_trunc__ln414__fu__179__p1;
	// \src: matmul_partition.v:89.8-89.23
	/*outline*/ value<1> p_ap__block__state2;
	// \src: matmul_partition.v:87.14-87.32
	/*outline*/ value<8> p_add__ln50__fu__167__p2;
	// \src: matmul_partition.v:86.9-86.26
	/*outline*/ value<1> p_ap__CS__fsm__state19;
	// \src: matmul_partition.v:85.9-85.26
	/*outline*/ value<1> p_ap__CS__fsm__state18;
	// \src: matmul_partition.v:84.9-84.26
	/*outline*/ value<1> p_ap__CS__fsm__state17;
	// \src: matmul_partition.v:83.9-83.26
	/*outline*/ value<1> p_ap__CS__fsm__state16;
	// \src: matmul_partition.v:82.9-82.26
	/*outline*/ value<1> p_ap__CS__fsm__state15;
	// \src: matmul_partition.v:81.9-81.26
	/*outline*/ value<1> p_ap__CS__fsm__state14;
	// \src: matmul_partition.v:80.9-80.26
	/*outline*/ value<1> p_ap__CS__fsm__state13;
	// \src: matmul_partition.v:79.9-79.26
	/*outline*/ value<1> p_ap__CS__fsm__state12;
	// \src: matmul_partition.v:78.9-78.26
	/*outline*/ value<1> p_ap__CS__fsm__state11;
	// \src: matmul_partition.v:77.8-77.30
	/*outline*/ value<1> p_Output__1__V__TDATA__blk__n;
	// \src: matmul_partition.v:76.9-76.25
	/*outline*/ value<1> p_ap__CS__fsm__state9;
	// \src: matmul_partition.v:75.9-75.25
	/*outline*/ value<1> p_ap__CS__fsm__state8;
	// \src: matmul_partition.v:74.9-74.25
	/*outline*/ value<1> p_ap__CS__fsm__state7;
	// \src: matmul_partition.v:73.9-73.25
	/*outline*/ value<1> p_ap__CS__fsm__state6;
	// \src: matmul_partition.v:72.9-72.25
	/*outline*/ value<1> p_ap__CS__fsm__state5;
	// \src: matmul_partition.v:71.9-71.25
	/*outline*/ value<1> p_ap__CS__fsm__state4;
	// \src: matmul_partition.v:70.9-70.25
	/*outline*/ value<1> p_ap__CS__fsm__state3;
	// \src: matmul_partition.v:69.14-69.33
	/*outline*/ value<1> p_icmp__ln50__fu__173__p2;
	// \src: matmul_partition.v:68.9-68.25
	/*outline*/ value<1> p_ap__CS__fsm__state2;
	// \src: matmul_partition.v:67.8-67.29
	/*outline*/ value<1> p_Input__1__V__TDATA__blk__n;
	// \src: matmul_partition.v:66.9-66.25
	/*outline*/ value<1> p_ap__CS__fsm__state1;
	// \src: matmul_partition.v:64.9-64.21
	/*outline*/ value<1> p_ap__rst__n__inv;
	// \hdlname: A_V_1_U matmul_partition_A_V_0_ram_U ram
	// \src: matmul_partition.v:168.1-176.2|matmul_partition_A_V_0.v:19.18-19.21|matmul_partition_A_V_0.v:59.28-65.15
	memory<256> memory_p_A__V__1__U_2e_matmul__partition__A__V__0__ram__U_2e_ram { 64u };
	// \hdlname: A_V_0_U matmul_partition_A_V_0_ram_U ram
	// \src: matmul_partition.v:154.1-162.2|matmul_partition_A_V_0.v:19.18-19.21|matmul_partition_A_V_0.v:59.28-65.15
	memory<256> memory_p_A__V__0__U_2e_matmul__partition__A__V__0__ram__U_2e_ram { 64u };

	p_matmul__partition() {}
	p_matmul__partition(adopt, p_matmul__partition other) {}

	void reset() override {
		*this = p_matmul__partition(adopt {}, std::move(*this));
	}

	bool eval() override;
	bool commit() override;

	void debug_eval();
	debug_outline debug_eval_outline { std::bind(&p_matmul__partition::debug_eval, this) };

	void debug_info(debug_items &items, std::string path = "") override;
}; // struct p_matmul__partition

bool p_matmul__partition::eval() {
	bool converged = true;
	bool posedge_p_ap__clk = this->posedge_p_ap__clk();
	value<1> i_procmux_24_1153__Y;
	value<1> i_procmux_24_1012__Y;
	value<6> i_procmux_24_647__Y;
	value<256> i_procmux_24_644__Y;
	value<256> i_procmux_24_641__Y;
	value<6> i_procmux_24_617__Y;
	value<256> i_procmux_24_614__Y;
	value<256> i_procmux_24_611__Y;
	// \hdlname: regslice_both_Output_1_V_U ap_clk
	// \src: matmul_partition.v:194.1-204.2|matmul_partition_regslice_both.v:12.11-12.17
	value<1> p_regslice__both__Output__1__V__U_2e_ap__clk;
	// \hdlname: regslice_both_Output_1_V_U B_V_data_1_state_cmp_full
	// \src: matmul_partition.v:194.1-204.2|matmul_partition_regslice_both.v:38.9-38.34
	value<1> p_regslice__both__Output__1__V__U_2e_B__V__data__1__state__cmp__full;
	// \hdlname: regslice_both_Input_1_V_U ap_clk
	// \src: matmul_partition.v:180.1-190.2|matmul_partition_regslice_both.v:12.11-12.17
	value<1> p_regslice__both__Input__1__V__U_2e_ap__clk;
	// \hdlname: regslice_both_Input_1_V_U B_V_data_1_data_out
	// \src: matmul_partition.v:180.1-190.2|matmul_partition_regslice_both.v:27.23-27.42
	value<32> p_regslice__both__Input__1__V__U_2e_B__V__data__1__data__out;
	// \hdlname: regslice_both_Input_1_V_U B_V_data_1_state_cmp_full
	// \src: matmul_partition.v:180.1-190.2|matmul_partition_regslice_both.v:38.9-38.34
	value<1> p_regslice__both__Input__1__V__U_2e_B__V__data__1__state__cmp__full;
	// \src: matmul_partition.v:168.1-176.2|matmul_partition_A_V_0.v:29.15-29.18|matmul_partition_A_V_0.v:59.28-65.15
	value<256> i_flatten_5c_A__V__1__U_2e__5c_matmul__partition__A__V__0__ram__U_2e__24_memrd_24__5c_ram_24_matmul__partition__A__V__0_2e_v_3a_29_24_12__DATA;
	// \hdlname: A_V_1_U matmul_partition_A_V_0_ram_U clk
	// \src: matmul_partition.v:168.1-176.2|matmul_partition_A_V_0.v:17.7-17.10|matmul_partition_A_V_0.v:59.28-65.15
	value<1> p_A__V__1__U_2e_matmul__partition__A__V__0__ram__U_2e_clk;
	// \hdlname: A_V_1_U matmul_partition_A_V_0_ram_U we0
	// \src: matmul_partition.v:168.1-176.2|matmul_partition_A_V_0.v:15.7-15.10|matmul_partition_A_V_0.v:59.28-65.15
	value<1> p_A__V__1__U_2e_matmul__partition__A__V__0__ram__U_2e_we0;
	// \hdlname: A_V_1_U matmul_partition_A_V_0_ram_U ce0
	// \src: matmul_partition.v:168.1-176.2|matmul_partition_A_V_0.v:13.7-13.10|matmul_partition_A_V_0.v:59.28-65.15
	value<1> p_A__V__1__U_2e_matmul__partition__A__V__0__ram__U_2e_ce0;
	// \src: matmul_partition.v:154.1-162.2|matmul_partition_A_V_0.v:29.15-29.18|matmul_partition_A_V_0.v:59.28-65.15
	value<256> i_flatten_5c_A__V__0__U_2e__5c_matmul__partition__A__V__0__ram__U_2e__24_memrd_24__5c_ram_24_matmul__partition__A__V__0_2e_v_3a_29_24_12__DATA;
	// \hdlname: A_V_0_U matmul_partition_A_V_0_ram_U clk
	// \src: matmul_partition.v:154.1-162.2|matmul_partition_A_V_0.v:17.7-17.10|matmul_partition_A_V_0.v:59.28-65.15
	value<1> p_A__V__0__U_2e_matmul__partition__A__V__0__ram__U_2e_clk;
	// \hdlname: A_V_0_U matmul_partition_A_V_0_ram_U we0
	// \src: matmul_partition.v:154.1-162.2|matmul_partition_A_V_0.v:15.7-15.10|matmul_partition_A_V_0.v:59.28-65.15
	value<1> p_A__V__0__U_2e_matmul__partition__A__V__0__ram__U_2e_we0;
	// \hdlname: A_V_0_U matmul_partition_A_V_0_ram_U ce0
	// \src: matmul_partition.v:154.1-162.2|matmul_partition_A_V_0.v:13.7-13.10|matmul_partition_A_V_0.v:59.28-65.15
	value<1> p_A__V__0__U_2e_matmul__partition__A__V__0__ram__U_2e_ce0;
	// \src: matmul_partition.v:647.30-647.85
	value<256> i_ternary_24_matmul__partition_2e_v_3a_647_24_461__Y;
	// \src: matmul_partition.v:506.18-506.127
	value<1> i_and_24_matmul__partition_2e_v_3a_506_24_411__Y;
	// \src: matmul_partition.v:448.18-448.153
	value<1> i_and_24_matmul__partition_2e_v_3a_448_24_377__Y;
	// \src: matmul_partition.v:394.23-394.48
	value<1> i_eq_24_matmul__partition_2e_v_3a_394_24_316__Y;
	// \src: matmul_partition.v:392.23-392.48
	value<1> i_eq_24_matmul__partition_2e_v_3a_392_24_315__Y;
	// \src: matmul_partition.v:390.23-390.48
	value<1> i_eq_24_matmul__partition_2e_v_3a_390_24_314__Y;
	// \src: matmul_partition.v:388.23-388.48
	value<1> i_eq_24_matmul__partition_2e_v_3a_388_24_313__Y;
	// \src: matmul_partition.v:386.23-386.48
	value<1> i_eq_24_matmul__partition_2e_v_3a_386_24_312__Y;
	// \src: matmul_partition.v:384.23-384.48
	value<1> i_eq_24_matmul__partition_2e_v_3a_384_24_311__Y;
	// \src: matmul_partition.v:382.14-382.39
	value<1> i_eq_24_matmul__partition_2e_v_3a_382_24_310__Y;
	// \src: matmul_partition.v:381.10-381.48
	value<1> i_eq_24_matmul__partition_2e_v_3a_381_24_309__Y;
	// \src: matmul_partition.v:331.10-331.35
	value<1> i_eq_24_matmul__partition_2e_v_3a_331_24_219__Y;
	// \src: matmul_partition.v:305.10-305.35
	value<1> i_eq_24_matmul__partition_2e_v_3a_305_24_202__Y;
	// \src: matmul_partition.v:257.10-257.35
	value<1> i_eq_24_matmul__partition_2e_v_3a_257_24_188__Y;
	// \src: matmul_partition.v:243.10-243.68
	value<1> i_and_24_matmul__partition_2e_v_3a_243_24_182__Y;
	// \src: matmul_partition.v:139.14-139.43
	value<32> p_Output__1__V__TDATA__int__regslice;
	// \src: matmul_partition.v:120.13-120.27
	value<6> p_A__V__1__address0;
	// \src: matmul_partition.v:116.13-116.27
	value<6> p_A__V__0__address0;
	// \src: matmul_partition.v:105.14-105.33
	value<1> p_icmp__ln64__fu__225__p2;
	// \src: matmul_partition.v:104.9-104.46
	value<1> p_regslice__both__Output__1__V__U__apdone__blk;
	// \src: matmul_partition.v:69.14-69.33
	value<1> p_icmp__ln50__fu__173__p2;
	// \src: matmul_partition.v:647.30-647.85
	// cell $ternary$matmul_partition.v:647$461
	i_ternary_24_matmul__partition_2e_v_3a_647_24_461__Y = (p_icmp__ln674__reg__409.curr ? p_A__V__0__U_2e_matmul__partition__A__V__0__ram__U_2e_q0.curr : p_A__V__1__U_2e_matmul__partition__A__V__0__ram__U_2e_q0.curr);
	// connection
	i_eq_24_matmul__partition_2e_v_3a_394_24_316__Y = p_ap__CS__fsm.curr.slice<11>().val();
	// connection
	i_eq_24_matmul__partition_2e_v_3a_392_24_315__Y = p_ap__CS__fsm.curr.slice<12>().val();
	// connection
	i_eq_24_matmul__partition_2e_v_3a_390_24_314__Y = p_ap__CS__fsm.curr.slice<13>().val();
	// connection
	i_eq_24_matmul__partition_2e_v_3a_388_24_313__Y = p_ap__CS__fsm.curr.slice<14>().val();
	// connection
	i_eq_24_matmul__partition_2e_v_3a_386_24_312__Y = p_ap__CS__fsm.curr.slice<15>().val();
	// connection
	i_eq_24_matmul__partition_2e_v_3a_384_24_311__Y = p_ap__CS__fsm.curr.slice<16>().val();
	// connection
	i_eq_24_matmul__partition_2e_v_3a_382_24_310__Y = p_ap__CS__fsm.curr.slice<17>().val();
	// connection
	i_eq_24_matmul__partition_2e_v_3a_381_24_309__Y = p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr.slice<1>().val();
	// cells $ternary$matmul_partition.v:639$455 $eq$matmul_partition.v:639$454
	p_icmp__ln50__fu__173__p2 = (eq_uu<1>(p_i__reg__145.curr, value<8>{0x80u}) ? value<1>{0x1u} : value<1>{0u});
	// cells $ternary$matmul_partition.v:641$457 $eq$matmul_partition.v:641$456
	p_icmp__ln64__fu__225__p2 = (eq_uu<1>(p_i__1__reg__156.curr, value<8>{0x80u}) ? value<1>{0x1u} : value<1>{0u});
	// cells $flatten\regslice_both_Output_1_V_U.$or$matmul_partition_regslice_both.v:117$529 $flatten\regslice_both_Output_1_V_U.$eq$matmul_partition_regslice_both.v:117$528 $flatten\regslice_both_Output_1_V_U.$logic_and$matmul_partition_regslice_both.v:117$527 $flatten\regslice_both_Output_1_V_U.$eq$matmul_partition_regslice_both.v:117$526 $flatten\regslice_both_Output_1_V_U.$eq$matmul_partition_regslice_both.v:117$525
	p_regslice__both__Output__1__V__U__apdone__blk = or_uu<1>(logic_and<1>(eq_uu<1>(p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr, value<2>{0x3u}), not_u<1>(p_Output__1__V__TREADY)), eq_uu<1>(p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr, value<2>{0x1u}));
	// cells $procmux$1012 $or$matmul_partition.v:407$349 $and$matmul_partition.v:407$348 $or$matmul_partition.v:407$345 $and$matmul_partition.v:407$344 $or$matmul_partition.v:407$341 $and$matmul_partition.v:407$340 $or$matmul_partition.v:407$337 $and$matmul_partition.v:407$336 $or$matmul_partition.v:407$333 $and$matmul_partition.v:407$332 $or$matmul_partition.v:407$329 $and$matmul_partition.v:407$328 $or$matmul_partition.v:407$325 $and$matmul_partition.v:407$324 $and$matmul_partition.v:407$321
	i_procmux_24_1012__Y = (or_uu<1>(or_uu<1>(or_uu<1>(or_uu<1>(or_uu<1>(or_uu<1>(or_uu<1>(and_uu<1>(p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr.slice<1>().val(), p_ap__CS__fsm.curr.slice<17>().val()), and_uu<1>(p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr.slice<1>().val(), p_ap__CS__fsm.curr.slice<16>().val())), and_uu<1>(p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr.slice<1>().val(), p_ap__CS__fsm.curr.slice<15>().val())), and_uu<1>(p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr.slice<1>().val(), p_ap__CS__fsm.curr.slice<14>().val())), and_uu<1>(p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr.slice<1>().val(), p_ap__CS__fsm.curr.slice<13>().val())), and_uu<1>(p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr.slice<1>().val(), p_ap__CS__fsm.curr.slice<12>().val())), and_uu<1>(p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr.slice<1>().val(), p_ap__CS__fsm.curr.slice<11>().val())), and_uu<1>(p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr.slice<1>().val(), p_ap__CS__fsm.curr.slice<10>().val())) ? value<1>{0x1u} : value<1>{0u});
	// cells $procmux$1153 $or$matmul_partition.v:365$289 $and$matmul_partition.v:365$288 $and$matmul_partition.v:365$286 $eq$matmul_partition.v:365$285 $not$matmul_partition.v:365$284 $and$matmul_partition.v:365$283 $eq$matmul_partition.v:365$282 $eq$matmul_partition.v:365$281 $or$matmul_partition.v:365$280 $and$matmul_partition.v:365$279 $or$matmul_partition.v:365$276 $and$matmul_partition.v:365$275 $or$matmul_partition.v:365$272 $and$matmul_partition.v:365$271 $or$matmul_partition.v:365$268 $and$matmul_partition.v:365$267 $or$matmul_partition.v:365$264 $and$matmul_partition.v:365$263 $or$matmul_partition.v:365$260 $and$matmul_partition.v:365$259 $and$matmul_partition.v:365$256
	i_procmux_24_1153__Y = (or_uu<1>(or_uu<1>(or_uu<1>(or_uu<1>(or_uu<1>(or_uu<1>(or_uu<1>(and_uu<1>(p_ap__CS__fsm.curr.slice<8>().val(), p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr.slice<0>().val()), and_uu<1>(p_ap__CS__fsm.curr.slice<7>().val(), p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr.slice<0>().val())), and_uu<1>(p_ap__CS__fsm.curr.slice<6>().val(), p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr.slice<0>().val())), and_uu<1>(p_ap__CS__fsm.curr.slice<5>().val(), p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr.slice<0>().val())), and_uu<1>(p_ap__CS__fsm.curr.slice<4>().val(), p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr.slice<0>().val())), and_uu<1>(p_ap__CS__fsm.curr.slice<3>().val(), p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr.slice<0>().val())), and_uu<1>(p_ap__CS__fsm.curr.slice<2>().val(), p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr.slice<0>().val())), and_uu<1>(and_uu<1>(not_u<1>(and_uu<1>(not_u<1>(p_icmp__ln50__fu__173__p2), not_u<1>(p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr.slice<0>().val()))), not_u<1>(p_icmp__ln50__fu__173__p2)), p_ap__CS__fsm.curr.slice<1>().val())) ? value<1>{0x1u} : value<1>{0u});
	// connection
	i_eq_24_matmul__partition_2e_v_3a_305_24_202__Y = p_ap__CS__fsm.curr.slice<9>().val();
	// connection
	i_eq_24_matmul__partition_2e_v_3a_331_24_219__Y = p_ap__CS__fsm.curr.slice<9>().val();
	// cells $and$matmul_partition.v:448$377 $and$matmul_partition.v:448$375 $not$matmul_partition.v:448$373 $and$matmul_partition.v:448$372 $eq$matmul_partition.v:448$371 $eq$matmul_partition.v:448$370
	i_and_24_matmul__partition_2e_v_3a_448_24_377__Y = and_uu<1>(and_uu<1>(not_u<1>(and_uu<1>(not_u<1>(p_icmp__ln50__fu__173__p2), not_u<1>(p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr.slice<0>().val()))), p_icmp__ln50__fu__173__p2), p_ap__CS__fsm.curr.slice<1>().val());
	// cells $and$matmul_partition.v:506$411 $eq$matmul_partition.v:506$410 $and$matmul_partition.v:506$409
	i_and_24_matmul__partition_2e_v_3a_506_24_411__Y = and_uu<1>(and_uu<1>(p_ap__CS__fsm.curr.slice<9>().val(), p_icmp__ln64__fu__225__p2), not_u<1>(p_regslice__both__Output__1__V__U__apdone__blk));
	// cells $procmux$1174 $and$matmul_partition.v:323$217 $and$matmul_partition.v:323$215
	p_A__V__0__U_2e_matmul__partition__A__V__0__ram__U_2e_we0 = (and_uu<1>(and_uu<1>(p_ap__CS__fsm.curr.slice<8>().val(), p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr.slice<0>().val()), p_icmp__ln414__reg__357.curr) ? value<1>{0x1u} : value<1>{0u});
	// cells $procmux$1159 $and$matmul_partition.v:349$234 $eq$matmul_partition.v:349$233 $and$matmul_partition.v:349$232
	p_A__V__1__U_2e_matmul__partition__A__V__0__ram__U_2e_we0 = (and_uu<1>(and_uu<1>(p_ap__CS__fsm.curr.slice<8>().val(), p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr.slice<0>().val()), not_u<1>(p_icmp__ln414__reg__357.curr)) ? value<1>{0x1u} : value<1>{0u});
	// cells $procmux$1186 $procmux$1183 $procmux$1180
	p_A__V__0__address0 = (i_eq_24_matmul__partition_2e_v_3a_305_24_202__Y ? p_i__1__reg__156.curr.slice<5,0>().val() : (i_eq_24_matmul__partition_2e_v_3a_305_24_202__Y ? value<6>{0u} : (p_ap__CS__fsm.curr.slice<8>().val() ? p_trunc__ln414__reg__352.curr : value<6>{0u})));
	// cells $procmux$1177 $or$matmul_partition.v:315$211 $and$matmul_partition.v:315$210 $eq$matmul_partition.v:315$209 $and$matmul_partition.v:315$207
	p_A__V__0__U_2e_matmul__partition__A__V__0__ram__U_2e_ce0 = (or_uu<1>(and_uu<1>(p_ap__CS__fsm.curr.slice<8>().val(), p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr.slice<0>().val()), and_uu<1>(p_ap__CS__fsm.curr.slice<9>().val(), not_u<1>(p_regslice__both__Output__1__V__U__apdone__blk))) ? value<1>{0x1u} : value<1>{0u});
	// \full_case: 1
	// \src: matmul_partition_regslice_both.v:95.5-99.8
	// cell $procmux$590
	p_regslice__both__Input__1__V__U_2e_B__V__data__1__data__out = (p_regslice__both__Input__1__V__U_2e_B__V__data__1__sel__rd.curr ? p_regslice__both__Input__1__V__U_2e_B__V__data__1__payload__B.curr : p_regslice__both__Input__1__V__U_2e_B__V__data__1__payload__A.curr);
	// cells $procmux$1171 $procmux$1168 $procmux$1165
	p_A__V__1__address0 = (i_eq_24_matmul__partition_2e_v_3a_331_24_219__Y ? p_i__1__reg__156.curr.slice<5,0>().val() : (i_eq_24_matmul__partition_2e_v_3a_331_24_219__Y ? value<6>{0u} : (p_ap__CS__fsm.curr.slice<8>().val() ? p_trunc__ln414__reg__352.curr : value<6>{0u})));
	// cells $procmux$1162 $or$matmul_partition.v:341$228 $and$matmul_partition.v:341$227 $eq$matmul_partition.v:341$226 $and$matmul_partition.v:341$224
	p_A__V__1__U_2e_matmul__partition__A__V__0__ram__U_2e_ce0 = (or_uu<1>(and_uu<1>(p_ap__CS__fsm.curr.slice<8>().val(), p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr.slice<0>().val()), and_uu<1>(p_ap__CS__fsm.curr.slice<9>().val(), not_u<1>(p_regslice__both__Output__1__V__U__apdone__blk))) ? value<1>{0x1u} : value<1>{0u});
	// cells $flatten\regslice_both_Input_1_V_U.$ternary$matmul_partition_regslice_both.v:106$524 $flatten\regslice_both_Input_1_V_U.$ne$matmul_partition_regslice_both.v:106$523
	p_regslice__both__Input__1__V__U_2e_B__V__data__1__state__cmp__full = (ne_uu<1>(p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr, value<2>{0x1u}) ? value<1>{0x1u} : value<1>{0u});
	// cells $flatten\regslice_both_Output_1_V_U.$ternary$matmul_partition_regslice_both.v:106$524 $flatten\regslice_both_Output_1_V_U.$ne$matmul_partition_regslice_both.v:106$523
	p_regslice__both__Output__1__V__U_2e_B__V__data__1__state__cmp__full = (ne_uu<1>(p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr, value<2>{0x1u}) ? value<1>{0x1u} : value<1>{0u});
	// cells $and$matmul_partition.v:243$182 $eq$matmul_partition.v:243$180
	i_and_24_matmul__partition_2e_v_3a_243_24_182__Y = and_uu<1>(not_u<1>(p_icmp__ln50__fu__173__p2), p_ap__CS__fsm.curr.slice<1>().val());
	// connection
	i_eq_24_matmul__partition_2e_v_3a_257_24_188__Y = p_ap__CS__fsm.curr.slice<10>().val();
	// cells $procmux$647 $procmux$638 $procmux$636
	i_procmux_24_647__Y = (p_A__V__0__U_2e_matmul__partition__A__V__0__ram__U_2e_ce0 ? (p_A__V__0__U_2e_matmul__partition__A__V__0__ram__U_2e_ce0 ? (p_A__V__0__U_2e_matmul__partition__A__V__0__ram__U_2e_we0 ? p_A__V__0__address0 : value<6>{0u}) : value<6>{0u}) : value<6>{0u});
	// cells $procmux$644 $procmux$632 $procmux$630
	i_procmux_24_644__Y = (p_A__V__0__U_2e_matmul__partition__A__V__0__ram__U_2e_ce0 ? (p_A__V__0__U_2e_matmul__partition__A__V__0__ram__U_2e_ce0 ? (p_A__V__0__U_2e_matmul__partition__A__V__0__ram__U_2e_we0 ? p_tmp__V__reg__347.curr.concat(p_tmp__V__1__reg__361.curr).concat(p_tmp__V__2__reg__366.curr).concat(p_tmp__V__3__reg__371.curr).concat(p_tmp__V__4__reg__376.curr).concat(p_tmp__V__5__reg__381.curr).concat(p_tmp__V__6__reg__386.curr).concat(p_regslice__both__Input__1__V__U_2e_B__V__data__1__data__out).val() : value<256>{0u,0u,0u,0u,0u,0u,0u,0u}) : value<256>{0u,0u,0u,0u,0u,0u,0u,0u}) : value<256>{0u,0u,0u,0u,0u,0u,0u,0u});
	// cells $procmux$641 $procmux$626 $procmux$624
	i_procmux_24_641__Y = (p_A__V__0__U_2e_matmul__partition__A__V__0__ram__U_2e_ce0 ? (p_A__V__0__U_2e_matmul__partition__A__V__0__ram__U_2e_ce0 ? (p_A__V__0__U_2e_matmul__partition__A__V__0__ram__U_2e_we0 ? value<256>{0xffffffffu,0xffffffffu,0xffffffffu,0xffffffffu,0xffffffffu,0xffffffffu,0xffffffffu,0xffffffffu} : value<256>{0u,0u,0u,0u,0u,0u,0u,0u}) : value<256>{0u,0u,0u,0u,0u,0u,0u,0u}) : value<256>{0u,0u,0u,0u,0u,0u,0u,0u});
	// cells $procmux$617 $procmux$608 $procmux$606
	i_procmux_24_617__Y = (p_A__V__1__U_2e_matmul__partition__A__V__0__ram__U_2e_ce0 ? (p_A__V__1__U_2e_matmul__partition__A__V__0__ram__U_2e_ce0 ? (p_A__V__1__U_2e_matmul__partition__A__V__0__ram__U_2e_we0 ? p_A__V__1__address0 : value<6>{0u}) : value<6>{0u}) : value<6>{0u});
	// cells $procmux$614 $procmux$602 $procmux$600
	i_procmux_24_614__Y = (p_A__V__1__U_2e_matmul__partition__A__V__0__ram__U_2e_ce0 ? (p_A__V__1__U_2e_matmul__partition__A__V__0__ram__U_2e_ce0 ? (p_A__V__1__U_2e_matmul__partition__A__V__0__ram__U_2e_we0 ? p_tmp__V__reg__347.curr.concat(p_tmp__V__1__reg__361.curr).concat(p_tmp__V__2__reg__366.curr).concat(p_tmp__V__3__reg__371.curr).concat(p_tmp__V__4__reg__376.curr).concat(p_tmp__V__5__reg__381.curr).concat(p_tmp__V__6__reg__386.curr).concat(p_regslice__both__Input__1__V__U_2e_B__V__data__1__data__out).val() : value<256>{0u,0u,0u,0u,0u,0u,0u,0u}) : value<256>{0u,0u,0u,0u,0u,0u,0u,0u}) : value<256>{0u,0u,0u,0u,0u,0u,0u,0u});
	// cells $procmux$611 $procmux$596 $procmux$594
	i_procmux_24_611__Y = (p_A__V__1__U_2e_matmul__partition__A__V__0__ram__U_2e_ce0 ? (p_A__V__1__U_2e_matmul__partition__A__V__0__ram__U_2e_ce0 ? (p_A__V__1__U_2e_matmul__partition__A__V__0__ram__U_2e_we0 ? value<256>{0xffffffffu,0xffffffffu,0xffffffffu,0xffffffffu,0xffffffffu,0xffffffffu,0xffffffffu,0xffffffffu} : value<256>{0u,0u,0u,0u,0u,0u,0u,0u}) : value<256>{0u,0u,0u,0u,0u,0u,0u,0u}) : value<256>{0u,0u,0u,0u,0u,0u,0u,0u});
	// \src: matmul_partition.v:154.1-162.2|matmul_partition_A_V_0.v:29.15-29.18|matmul_partition_A_V_0.v:59.28-65.15
	// memory \A_V_0_U.matmul_partition_A_V_0_ram_U.ram read port 0
	auto tmp_0 = memory_index(p_A__V__0__address0, 0, 64);
	CXXRTL_ASSERT(tmp_0.valid && "out of bounds read");
	if(tmp_0.valid) {
		value<256> tmp_1 = memory_p_A__V__0__U_2e_matmul__partition__A__V__0__ram__U_2e_ram[tmp_0.index];
		i_flatten_5c_A__V__0__U_2e__5c_matmul__partition__A__V__0__ram__U_2e__24_memrd_24__5c_ram_24_matmul__partition__A__V__0_2e_v_3a_29_24_12__DATA = tmp_1;
	} else {
		i_flatten_5c_A__V__0__U_2e__5c_matmul__partition__A__V__0__ram__U_2e__24_memrd_24__5c_ram_24_matmul__partition__A__V__0_2e_v_3a_29_24_12__DATA = value<256> {};
	}
	// \src: matmul_partition.v:168.1-176.2|matmul_partition_A_V_0.v:29.15-29.18|matmul_partition_A_V_0.v:59.28-65.15
	// memory \A_V_1_U.matmul_partition_A_V_0_ram_U.ram read port 0
	auto tmp_2 = memory_index(p_A__V__1__address0, 0, 64);
	CXXRTL_ASSERT(tmp_2.valid && "out of bounds read");
	if(tmp_2.valid) {
		value<256> tmp_3 = memory_p_A__V__1__U_2e_matmul__partition__A__V__0__ram__U_2e_ram[tmp_2.index];
		i_flatten_5c_A__V__1__U_2e__5c_matmul__partition__A__V__0__ram__U_2e__24_memrd_24__5c_ram_24_matmul__partition__A__V__0_2e_v_3a_29_24_12__DATA = tmp_3;
	} else {
		i_flatten_5c_A__V__1__U_2e__5c_matmul__partition__A__V__0__ram__U_2e__24_memrd_24__5c_ram_24_matmul__partition__A__V__0_2e_v_3a_29_24_12__DATA = value<256> {};
	}
	// cells $procmux$1147 $procmux$1144 $procmux$1142 $procmux$1138 $procmux$1136 $procmux$1133 $procmux$1129 $procmux$1127 $procmux$1124 $procmux$1121 $procmux$1117 $procmux$1115 $procmux$1112 $procmux$1109 $procmux$1106 $procmux$1102 $procmux$1100 $procmux$1097 $procmux$1094 $procmux$1091 $procmux$1088 $procmux$1084 $procmux$1082 $procmux$1079 $procmux$1076 $procmux$1073 $procmux$1070 $procmux$1067 $procmux$1063 $procmux$1061 $procmux$1058 $procmux$1055 $procmux$1052 $procmux$1049 $procmux$1046 $procmux$1043 $procmux$1039 $procmux$1037 $procmux$1034 $procmux$1031 $procmux$1028 $procmux$1025 $procmux$1022 $procmux$1019 $procmux$1016
	p_Output__1__V__TDATA__int__regslice = (i_eq_24_matmul__partition_2e_v_3a_381_24_309__Y ? (i_eq_24_matmul__partition_2e_v_3a_381_24_309__Y ? (i_eq_24_matmul__partition_2e_v_3a_382_24_310__Y ? p_trunc__ln674__1__reg__449.curr : (i_eq_24_matmul__partition_2e_v_3a_381_24_309__Y ? (i_eq_24_matmul__partition_2e_v_3a_382_24_310__Y ? value<32>{0u} : (i_eq_24_matmul__partition_2e_v_3a_384_24_311__Y ? p_p__Result__6__reg__444.curr : (i_eq_24_matmul__partition_2e_v_3a_381_24_309__Y ? (i_eq_24_matmul__partition_2e_v_3a_382_24_310__Y ? value<32>{0u} : (i_eq_24_matmul__partition_2e_v_3a_384_24_311__Y ? value<32>{0u} : (i_eq_24_matmul__partition_2e_v_3a_386_24_312__Y ? p_p__Result__5__reg__439.curr : (i_eq_24_matmul__partition_2e_v_3a_381_24_309__Y ? (i_eq_24_matmul__partition_2e_v_3a_382_24_310__Y ? value<32>{0u} : (i_eq_24_matmul__partition_2e_v_3a_384_24_311__Y ? value<32>{0u} : (i_eq_24_matmul__partition_2e_v_3a_386_24_312__Y ? value<32>{0u} : (i_eq_24_matmul__partition_2e_v_3a_388_24_313__Y ? p_p__Result__4__reg__434.curr : (i_eq_24_matmul__partition_2e_v_3a_381_24_309__Y ? (i_eq_24_matmul__partition_2e_v_3a_382_24_310__Y ? value<32>{0u} : (i_eq_24_matmul__partition_2e_v_3a_384_24_311__Y ? value<32>{0u} : (i_eq_24_matmul__partition_2e_v_3a_386_24_312__Y ? value<32>{0u} : (i_eq_24_matmul__partition_2e_v_3a_388_24_313__Y ? value<32>{0u} : (i_eq_24_matmul__partition_2e_v_3a_390_24_314__Y ? p_p__Result__3__reg__429.curr : (i_eq_24_matmul__partition_2e_v_3a_381_24_309__Y ? (i_eq_24_matmul__partition_2e_v_3a_382_24_310__Y ? value<32>{0u} : (i_eq_24_matmul__partition_2e_v_3a_384_24_311__Y ? value<32>{0u} : (i_eq_24_matmul__partition_2e_v_3a_386_24_312__Y ? value<32>{0u} : (i_eq_24_matmul__partition_2e_v_3a_388_24_313__Y ? value<32>{0u} : (i_eq_24_matmul__partition_2e_v_3a_390_24_314__Y ? value<32>{0u} : (i_eq_24_matmul__partition_2e_v_3a_392_24_315__Y ? p_p__Result__2__reg__424.curr : (i_eq_24_matmul__partition_2e_v_3a_381_24_309__Y ? (i_eq_24_matmul__partition_2e_v_3a_382_24_310__Y ? value<32>{0u} : (i_eq_24_matmul__partition_2e_v_3a_384_24_311__Y ? value<32>{0u} : (i_eq_24_matmul__partition_2e_v_3a_386_24_312__Y ? value<32>{0u} : (i_eq_24_matmul__partition_2e_v_3a_388_24_313__Y ? value<32>{0u} : (i_eq_24_matmul__partition_2e_v_3a_390_24_314__Y ? value<32>{0u} : (i_eq_24_matmul__partition_2e_v_3a_392_24_315__Y ? value<32>{0u} : (i_eq_24_matmul__partition_2e_v_3a_394_24_316__Y ? p_p__Result__1__reg__419.curr : (i_eq_24_matmul__partition_2e_v_3a_381_24_309__Y ? (i_eq_24_matmul__partition_2e_v_3a_382_24_310__Y ? value<32>{0u} : (i_eq_24_matmul__partition_2e_v_3a_384_24_311__Y ? value<32>{0u} : (i_eq_24_matmul__partition_2e_v_3a_386_24_312__Y ? value<32>{0u} : (i_eq_24_matmul__partition_2e_v_3a_388_24_313__Y ? value<32>{0u} : (i_eq_24_matmul__partition_2e_v_3a_390_24_314__Y ? value<32>{0u} : (i_eq_24_matmul__partition_2e_v_3a_392_24_315__Y ? value<32>{0u} : (i_eq_24_matmul__partition_2e_v_3a_394_24_316__Y ? value<32>{0u} : (p_ap__CS__fsm.curr.slice<10>().val() ? i_ternary_24_matmul__partition_2e_v_3a_647_24_461__Y.slice<255,224>().val() : value<32>{0u})))))))) : value<32>{0u})))))))) : value<32>{0u}))))))) : value<32>{0u})))))) : value<32>{0u}))))) : value<32>{0u})))) : value<32>{0u}))) : value<32>{0u})) : value<32>{0u}) : value<32>{0u});
	// connection
	p_A__V__0__U_2e_matmul__partition__A__V__0__ram__U_2e_clk = p_ap__clk;
	// connection
	p_A__V__1__U_2e_matmul__partition__A__V__0__ram__U_2e_clk = p_ap__clk;
	// connection
	p_regslice__both__Output__1__V__U_2e_ap__clk = p_ap__clk;
	// connection
	p_regslice__both__Input__1__V__U_2e_ap__clk = p_ap__clk;
	// \src: matmul_partition_A_V_0.v:28.13-28.29
	// memory \A_V_0_U.matmul_partition_A_V_0_ram_U.ram write port 0
	if (posedge_p_ap__clk) {
		auto tmp_4 = memory_index(i_procmux_24_647__Y, 0, 64);
		CXXRTL_ASSERT(tmp_4.valid && "out of bounds write");
		if (tmp_4.valid) {
			memory_p_A__V__0__U_2e_matmul__partition__A__V__0__ram__U_2e_ram.update(tmp_4.index, i_procmux_24_644__Y, i_procmux_24_641__Y, 0);
		}
	}
	// \src: matmul_partition_A_V_0.v:28.13-28.29
	// memory \A_V_1_U.matmul_partition_A_V_0_ram_U.ram write port 0
	if (posedge_p_ap__clk) {
		auto tmp_5 = memory_index(i_procmux_24_617__Y, 0, 64);
		CXXRTL_ASSERT(tmp_5.valid && "out of bounds write");
		if (tmp_5.valid) {
			memory_p_A__V__1__U_2e_matmul__partition__A__V__0__ram__U_2e_ram.update(tmp_5.index, i_procmux_24_614__Y, i_procmux_24_611__Y, 0);
		}
	}
	// cells $procdff$1241 $procmux$552 $procmux$549 $flatten\regslice_both_Output_1_V_U.$or$matmul_partition_regslice_both.v:70$485 $flatten\regslice_both_Output_1_V_U.$and$matmul_partition_regslice_both.v:70$484 $flatten\regslice_both_Output_1_V_U.$eq$matmul_partition_regslice_both.v:70$483 $flatten\regslice_both_Output_1_V_U.$eq$matmul_partition_regslice_both.v:70$482 $flatten\regslice_both_Output_1_V_U.$and$matmul_partition_regslice_both.v:70$481 $flatten\regslice_both_Output_1_V_U.$and$matmul_partition_regslice_both.v:70$479 $flatten\regslice_both_Output_1_V_U.$eq$matmul_partition_regslice_both.v:70$478 $flatten\regslice_both_Output_1_V_U.$eq$matmul_partition_regslice_both.v:70$477 $procmux$546 $flatten\regslice_both_Output_1_V_U.$or$matmul_partition_regslice_both.v:72$494 $flatten\regslice_both_Output_1_V_U.$and$matmul_partition_regslice_both.v:72$493 $flatten\regslice_both_Output_1_V_U.$and$matmul_partition_regslice_both.v:72$491 $flatten\regslice_both_Output_1_V_U.$eq$matmul_partition_regslice_both.v:72$490 $flatten\regslice_both_Output_1_V_U.$eq$matmul_partition_regslice_both.v:72$489 $flatten\regslice_both_Output_1_V_U.$and$matmul_partition_regslice_both.v:72$488 $flatten\regslice_both_Output_1_V_U.$eq$matmul_partition_regslice_both.v:72$487 $flatten\regslice_both_Output_1_V_U.$eq$matmul_partition_regslice_both.v:72$486 $procmux$543 $flatten\regslice_both_Output_1_V_U.$or$matmul_partition_regslice_both.v:74$513 $flatten\regslice_both_Output_1_V_U.$and$matmul_partition_regslice_both.v:74$512 $flatten\regslice_both_Output_1_V_U.$eq$matmul_partition_regslice_both.v:74$510 $flatten\regslice_both_Output_1_V_U.$or$matmul_partition_regslice_both.v:74$509 $flatten\regslice_both_Output_1_V_U.$and$matmul_partition_regslice_both.v:74$508 $flatten\regslice_both_Output_1_V_U.$eq$matmul_partition_regslice_both.v:74$507 $flatten\regslice_both_Output_1_V_U.$and$matmul_partition_regslice_both.v:74$506 $flatten\regslice_both_Output_1_V_U.$not$matmul_partition_regslice_both.v:74$505 $flatten\regslice_both_Output_1_V_U.$and$matmul_partition_regslice_both.v:74$504 $flatten\regslice_both_Output_1_V_U.$eq$matmul_partition_regslice_both.v:74$502 $flatten\regslice_both_Output_1_V_U.$not$matmul_partition_regslice_both.v:74$501 $flatten\regslice_both_Output_1_V_U.$and$matmul_partition_regslice_both.v:74$500 $flatten\regslice_both_Output_1_V_U.$eq$matmul_partition_regslice_both.v:74$498 $flatten\regslice_both_Output_1_V_U.$and$matmul_partition_regslice_both.v:74$497 $flatten\regslice_both_Output_1_V_U.$eq$matmul_partition_regslice_both.v:74$495
	if (posedge_p_ap__clk) {
		p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.next = (p_ap__rst__n ? (or_uu<1>(and_uu<1>(and_uu<1>(eq_uu<1>(value<2>{0x3u}, p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr), not_u<1>(i_procmux_24_1012__Y)), p_Output__1__V__TREADY), and_uu<1>(eq_uu<1>(value<2>{0x2u}, p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr), not_u<1>(i_procmux_24_1012__Y))) ? value<2>{0x2u} : (or_uu<1>(and_uu<1>(eq_uu<1>(value<2>{0x1u}, p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr), not_u<1>(p_Output__1__V__TREADY)), and_uu<1>(and_uu<1>(eq_uu<1>(value<2>{0x3u}, p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr), not_u<1>(p_Output__1__V__TREADY)), i_procmux_24_1012__Y)) ? value<2>{0x1u} : (or_uu<1>(or_uu<1>(and_uu<1>(eq_uu<1>(value<2>{0x1u}, p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr), p_Output__1__V__TREADY), and_uu<1>(and_uu<1>(not_u<1>(and_uu<1>(not_u<1>(p_Output__1__V__TREADY), i_procmux_24_1012__Y)), not_u<1>(and_uu<1>(not_u<1>(i_procmux_24_1012__Y), p_Output__1__V__TREADY))), eq_uu<1>(value<2>{0x3u}, p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr))), and_uu<1>(eq_uu<1>(value<2>{0x2u}, p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr), i_procmux_24_1012__Y)) ? value<2>{0x3u} : value<2>{0x2u}))) : value<2>{0u});
	}
	// cells $procdff$1253 $procmux$650
	if (posedge_p_ap__clk) {
		p_A__V__0__U_2e_matmul__partition__A__V__0__ram__U_2e_q0.next = (p_A__V__0__U_2e_matmul__partition__A__V__0__ram__U_2e_ce0 ? i_flatten_5c_A__V__0__U_2e__5c_matmul__partition__A__V__0__ram__U_2e__24_memrd_24__5c_ram_24_matmul__partition__A__V__0_2e_v_3a_29_24_12__DATA : p_A__V__0__U_2e_matmul__partition__A__V__0__ram__U_2e_q0.curr);
	}
	// \src: matmul_partition.v:168.1-176.2|matmul_partition_A_V_0.v:24.1-31.4|matmul_partition_A_V_0.v:59.28-65.15
	// cell $procdff$1252
	if (posedge_p_ap__clk) {
		i_flatten_5c_A__V__1__U_2e__5c_matmul__partition__A__V__0__ram__U_2e__24_memwr_24__5c_ram_24_matmul__partition__A__V__0_2e_v_3a_28_24_1__EN.next = i_procmux_24_611__Y;
	}
	// \src: matmul_partition.v:168.1-176.2|matmul_partition_A_V_0.v:24.1-31.4|matmul_partition_A_V_0.v:59.28-65.15
	// cell $procdff$1251
	if (posedge_p_ap__clk) {
		i_flatten_5c_A__V__1__U_2e__5c_matmul__partition__A__V__0__ram__U_2e__24_memwr_24__5c_ram_24_matmul__partition__A__V__0_2e_v_3a_28_24_1__DATA.next = i_procmux_24_614__Y;
	}
	// \src: matmul_partition.v:168.1-176.2|matmul_partition_A_V_0.v:24.1-31.4|matmul_partition_A_V_0.v:59.28-65.15
	// cell $procdff$1250
	if (posedge_p_ap__clk) {
		i_flatten_5c_A__V__1__U_2e__5c_matmul__partition__A__V__0__ram__U_2e__24_memwr_24__5c_ram_24_matmul__partition__A__V__0_2e_v_3a_28_24_1__ADDR.next = i_procmux_24_617__Y;
	}
	// cells $procdff$1249 $procmux$620
	if (posedge_p_ap__clk) {
		p_A__V__1__U_2e_matmul__partition__A__V__0__ram__U_2e_q0.next = (p_A__V__1__U_2e_matmul__partition__A__V__0__ram__U_2e_ce0 ? i_flatten_5c_A__V__1__U_2e__5c_matmul__partition__A__V__0__ram__U_2e__24_memrd_24__5c_ram_24_matmul__partition__A__V__0_2e_v_3a_29_24_12__DATA : p_A__V__1__U_2e_matmul__partition__A__V__0__ram__U_2e_q0.curr);
	}
	// cells $procdff$1248 $procmux$587 $flatten\regslice_both_Input_1_V_U.$and$matmul_partition_regslice_both.v:104$522
	if (posedge_p_ap__clk) {
		p_regslice__both__Input__1__V__U_2e_B__V__data__1__payload__B.next = (and_uu<1>(p_regslice__both__Input__1__V__U_2e_B__V__data__1__state__cmp__full, p_regslice__both__Input__1__V__U_2e_B__V__data__1__sel__wr.curr) ? p_Input__1__V__TDATA : p_regslice__both__Input__1__V__U_2e_B__V__data__1__payload__B.curr);
	}
	// cells $procdff$1247 $procmux$585 $flatten\regslice_both_Input_1_V_U.$and$matmul_partition_regslice_both.v:103$521 $flatten\regslice_both_Input_1_V_U.$not$matmul_partition_regslice_both.v:103$520
	if (posedge_p_ap__clk) {
		p_regslice__both__Input__1__V__U_2e_B__V__data__1__payload__A.next = (and_uu<1>(not_u<1>(p_regslice__both__Input__1__V__U_2e_B__V__data__1__sel__wr.curr), p_regslice__both__Input__1__V__U_2e_B__V__data__1__state__cmp__full) ? p_Input__1__V__TDATA : p_regslice__both__Input__1__V__U_2e_B__V__data__1__payload__A.curr);
	}
	// cells $procdff$1246 $procmux$583 $procmux$580 $flatten\regslice_both_Input_1_V_U.$or$matmul_partition_regslice_both.v:70$485 $flatten\regslice_both_Input_1_V_U.$and$matmul_partition_regslice_both.v:70$484 $flatten\regslice_both_Input_1_V_U.$eq$matmul_partition_regslice_both.v:70$483 $flatten\regslice_both_Input_1_V_U.$eq$matmul_partition_regslice_both.v:70$482 $flatten\regslice_both_Input_1_V_U.$and$matmul_partition_regslice_both.v:70$481 $flatten\regslice_both_Input_1_V_U.$and$matmul_partition_regslice_both.v:70$479 $flatten\regslice_both_Input_1_V_U.$eq$matmul_partition_regslice_both.v:70$478 $flatten\regslice_both_Input_1_V_U.$eq$matmul_partition_regslice_both.v:70$477 $procmux$577 $flatten\regslice_both_Input_1_V_U.$or$matmul_partition_regslice_both.v:72$494 $flatten\regslice_both_Input_1_V_U.$and$matmul_partition_regslice_both.v:72$493 $flatten\regslice_both_Input_1_V_U.$and$matmul_partition_regslice_both.v:72$491 $flatten\regslice_both_Input_1_V_U.$eq$matmul_partition_regslice_both.v:72$490 $flatten\regslice_both_Input_1_V_U.$eq$matmul_partition_regslice_both.v:72$489 $flatten\regslice_both_Input_1_V_U.$and$matmul_partition_regslice_both.v:72$488 $flatten\regslice_both_Input_1_V_U.$eq$matmul_partition_regslice_both.v:72$487 $flatten\regslice_both_Input_1_V_U.$eq$matmul_partition_regslice_both.v:72$486 $procmux$574 $flatten\regslice_both_Input_1_V_U.$or$matmul_partition_regslice_both.v:74$513 $flatten\regslice_both_Input_1_V_U.$and$matmul_partition_regslice_both.v:74$512 $flatten\regslice_both_Input_1_V_U.$eq$matmul_partition_regslice_both.v:74$510 $flatten\regslice_both_Input_1_V_U.$or$matmul_partition_regslice_both.v:74$509 $flatten\regslice_both_Input_1_V_U.$and$matmul_partition_regslice_both.v:74$508 $flatten\regslice_both_Input_1_V_U.$eq$matmul_partition_regslice_both.v:74$507 $flatten\regslice_both_Input_1_V_U.$and$matmul_partition_regslice_both.v:74$506 $flatten\regslice_both_Input_1_V_U.$not$matmul_partition_regslice_both.v:74$505 $flatten\regslice_both_Input_1_V_U.$and$matmul_partition_regslice_both.v:74$504 $flatten\regslice_both_Input_1_V_U.$eq$matmul_partition_regslice_both.v:74$502 $flatten\regslice_both_Input_1_V_U.$not$matmul_partition_regslice_both.v:74$501 $flatten\regslice_both_Input_1_V_U.$and$matmul_partition_regslice_both.v:74$500 $flatten\regslice_both_Input_1_V_U.$eq$matmul_partition_regslice_both.v:74$498 $flatten\regslice_both_Input_1_V_U.$and$matmul_partition_regslice_both.v:74$497 $flatten\regslice_both_Input_1_V_U.$eq$matmul_partition_regslice_both.v:74$495
	if (posedge_p_ap__clk) {
		p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.next = (p_ap__rst__n ? (or_uu<1>(and_uu<1>(and_uu<1>(eq_uu<1>(value<2>{0x3u}, p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr), not_u<1>(p_Input__1__V__TVALID)), i_procmux_24_1153__Y), and_uu<1>(eq_uu<1>(value<2>{0x2u}, p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr), not_u<1>(p_Input__1__V__TVALID))) ? value<2>{0x2u} : (or_uu<1>(and_uu<1>(eq_uu<1>(value<2>{0x1u}, p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr), not_u<1>(i_procmux_24_1153__Y)), and_uu<1>(and_uu<1>(eq_uu<1>(value<2>{0x3u}, p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr), not_u<1>(i_procmux_24_1153__Y)), p_Input__1__V__TVALID)) ? value<2>{0x1u} : (or_uu<1>(or_uu<1>(and_uu<1>(eq_uu<1>(value<2>{0x1u}, p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr), i_procmux_24_1153__Y), and_uu<1>(and_uu<1>(not_u<1>(and_uu<1>(not_u<1>(i_procmux_24_1153__Y), p_Input__1__V__TVALID)), not_u<1>(and_uu<1>(not_u<1>(p_Input__1__V__TVALID), i_procmux_24_1153__Y))), eq_uu<1>(value<2>{0x3u}, p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr))), and_uu<1>(eq_uu<1>(value<2>{0x2u}, p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr), p_Input__1__V__TVALID)) ? value<2>{0x3u} : value<2>{0x2u}))) : value<2>{0u});
	}
	// cells $procdff$1245 $procmux$571 $procmux$568 $flatten\regslice_both_Input_1_V_U.$and$matmul_partition_regslice_both.v:58$473 $flatten\regslice_both_Input_1_V_U.$not$matmul_partition_regslice_both.v:59$474
	if (posedge_p_ap__clk) {
		p_regslice__both__Input__1__V__U_2e_B__V__data__1__sel__wr.next = (p_ap__rst__n ? (and_uu<1>(p_Input__1__V__TVALID, p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr.slice<1>().val()) ? not_u<1>(p_regslice__both__Input__1__V__U_2e_B__V__data__1__sel__wr.curr) : p_regslice__both__Input__1__V__U_2e_B__V__data__1__sel__wr.curr) : value<1>{0u});
	}
	// cells $procdff$1278 $procmux$1237 $procmux$982 $procmux$983_CMP0 $procmux$984_CMP0 $procmux$985_CMP0 $procmux$986_CMP0 $procmux$987_CMP0 $procmux$988_CMP0 $procmux$989_CMP0 $procmux$990_CMP0 $procmux$991_CMP0 $procmux$992_CMP0 $procmux$993_CMP0 $procmux$994_CMP0 $procmux$995_CMP0 $procmux$996_CMP0 $procmux$997_CMP0 $procmux$998_CMP0 $procmux$999_CMP0 $procmux$1000_CMP0 $procmux$1001_CMP0 $procmux$656 $procmux$657_CMP0 $procmux$654 $and$matmul_partition.v:571$443 $procmux$663 $procmux$664_CMP0 $procmux$661 $and$matmul_partition.v:564$440 $procmux$671 $procmux$672_CMP0 $procmux$669 $and$matmul_partition.v:557$437 $procmux$680 $procmux$681_CMP0 $procmux$678 $and$matmul_partition.v:550$434 $procmux$690 $procmux$691_CMP0 $procmux$688 $and$matmul_partition.v:543$431 $procmux$701 $procmux$702_CMP0 $procmux$699 $and$matmul_partition.v:536$428 $procmux$713 $procmux$714_CMP0 $procmux$711 $and$matmul_partition.v:529$425 $procmux$726 $procmux$727_CMP0 $procmux$724 $and$matmul_partition.v:522$422 $procmux$740 $procmux$741_CMP0 $procmux$738 $and$matmul_partition.v:515$419 $procmux$773 $procmux$774_CMP0 $procmux$771 $procmux$758 $procmux$759_CMP0 $procmux$756 $procmux$753 $and$matmul_partition.v:508$416 $eq$matmul_partition.v:508$415 $and$matmul_partition.v:508$414 $eq$matmul_partition.v:508$413 $procmux$789 $procmux$790_CMP0 $procmux$787 $and$matmul_partition.v:499$406 $procmux$806 $procmux$807_CMP0 $procmux$804 $and$matmul_partition.v:492$403 $procmux$824 $procmux$825_CMP0 $procmux$822 $and$matmul_partition.v:485$400 $procmux$843 $procmux$844_CMP0 $procmux$841 $and$matmul_partition.v:478$397 $procmux$863 $procmux$864_CMP0 $procmux$861 $and$matmul_partition.v:471$394 $procmux$884 $procmux$885_CMP0 $procmux$882 $and$matmul_partition.v:464$391 $procmux$906 $procmux$907_CMP0 $procmux$904 $and$matmul_partition.v:457$388 $procmux$955 $procmux$956_CMP0 $procmux$953 $procmux$932 $procmux$933_CMP0 $procmux$930 $procmux$927 $and$matmul_partition.v:450$385 $and$matmul_partition.v:450$383 $eq$matmul_partition.v:450$382 $not$matmul_partition.v:450$381 $and$matmul_partition.v:450$380 $eq$matmul_partition.v:450$379 $eq$matmul_partition.v:450$378 $procmux$979 $procmux$980_CMP0 $procmux$977 $and$matmul_partition.v:441$369
	if (posedge_p_ap__clk) {
		p_ap__CS__fsm.next = (p_ap__rst__n ? (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x40000u}) ? (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x40000u}) ? (and_uu<1>(p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr.slice<1>().val(), p_ap__CS__fsm.curr.slice<18>().val()) ? value<19>{0x200u} : value<19>{0x40000u}) : value<19>{0u}) : (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x20000u}) ? (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x20000u}) ? (and_uu<1>(p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr.slice<1>().val(), p_ap__CS__fsm.curr.slice<17>().val()) ? value<19>{0x40000u} : value<19>{0x20000u}) : value<19>{0u}) : (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x10000u}) ? (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x10000u}) ? (and_uu<1>(p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr.slice<1>().val(), p_ap__CS__fsm.curr.slice<16>().val()) ? value<19>{0x20000u} : value<19>{0x10000u}) : value<19>{0u}) : (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x8000u}) ? (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x8000u}) ? (and_uu<1>(p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr.slice<1>().val(), p_ap__CS__fsm.curr.slice<15>().val()) ? value<19>{0x10000u} : value<19>{0x8000u}) : value<19>{0u}) : (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x4000u}) ? (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x4000u}) ? (and_uu<1>(p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr.slice<1>().val(), p_ap__CS__fsm.curr.slice<14>().val()) ? value<19>{0x8000u} : value<19>{0x4000u}) : value<19>{0u}) : (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x2000u}) ? (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x2000u}) ? (and_uu<1>(p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr.slice<1>().val(), p_ap__CS__fsm.curr.slice<13>().val()) ? value<19>{0x4000u} : value<19>{0x2000u}) : value<19>{0u}) : (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x1000u}) ? (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x1000u}) ? (and_uu<1>(p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr.slice<1>().val(), p_ap__CS__fsm.curr.slice<12>().val()) ? value<19>{0x2000u} : value<19>{0x1000u}) : value<19>{0u}) : (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x800u}) ? (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x800u}) ? (and_uu<1>(p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr.slice<1>().val(), p_ap__CS__fsm.curr.slice<11>().val()) ? value<19>{0x1000u} : value<19>{0x800u}) : value<19>{0u}) : (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x400u}) ? (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x400u}) ? (and_uu<1>(p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr.slice<1>().val(), p_ap__CS__fsm.curr.slice<10>().val()) ? value<19>{0x800u} : value<19>{0x400u}) : value<19>{0u}) : (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x200u}) ? (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x200u}) ? (i_and_24_matmul__partition_2e_v_3a_506_24_411__Y ? value<19>{0x1u} : (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x200u}) ? (i_and_24_matmul__partition_2e_v_3a_506_24_411__Y ? value<19>{0u} : (and_uu<1>(and_uu<1>(p_ap__CS__fsm.curr.slice<9>().val(), not_u<1>(p_icmp__ln64__fu__225__p2)), not_u<1>(p_regslice__both__Output__1__V__U__apdone__blk)) ? value<19>{0x400u} : value<19>{0x200u})) : value<19>{0u})) : value<19>{0u}) : (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x100u}) ? (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x100u}) ? (and_uu<1>(p_ap__CS__fsm.curr.slice<8>().val(), p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr.slice<0>().val()) ? value<19>{0x2u} : value<19>{0x100u}) : value<19>{0u}) : (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x80u}) ? (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x80u}) ? (and_uu<1>(p_ap__CS__fsm.curr.slice<7>().val(), p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr.slice<0>().val()) ? value<19>{0x100u} : value<19>{0x80u}) : value<19>{0u}) : (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x40u}) ? (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x40u}) ? (and_uu<1>(p_ap__CS__fsm.curr.slice<6>().val(), p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr.slice<0>().val()) ? value<19>{0x80u} : value<19>{0x40u}) : value<19>{0u}) : (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x20u}) ? (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x20u}) ? (and_uu<1>(p_ap__CS__fsm.curr.slice<5>().val(), p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr.slice<0>().val()) ? value<19>{0x40u} : value<19>{0x20u}) : value<19>{0u}) : (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x10u}) ? (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x10u}) ? (and_uu<1>(p_ap__CS__fsm.curr.slice<4>().val(), p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr.slice<0>().val()) ? value<19>{0x20u} : value<19>{0x10u}) : value<19>{0u}) : (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x8u}) ? (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x8u}) ? (and_uu<1>(p_ap__CS__fsm.curr.slice<3>().val(), p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr.slice<0>().val()) ? value<19>{0x10u} : value<19>{0x8u}) : value<19>{0u}) : (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x4u}) ? (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x4u}) ? (and_uu<1>(p_ap__CS__fsm.curr.slice<2>().val(), p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr.slice<0>().val()) ? value<19>{0x8u} : value<19>{0x4u}) : value<19>{0u}) : (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x2u}) ? (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x2u}) ? (i_and_24_matmul__partition_2e_v_3a_448_24_377__Y ? value<19>{0x200u} : (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x2u}) ? (i_and_24_matmul__partition_2e_v_3a_448_24_377__Y ? value<19>{0u} : (and_uu<1>(and_uu<1>(not_u<1>(and_uu<1>(not_u<1>(p_icmp__ln50__fu__173__p2), not_u<1>(p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr.slice<0>().val()))), not_u<1>(p_icmp__ln50__fu__173__p2)), p_ap__CS__fsm.curr.slice<1>().val()) ? value<19>{0x4u} : value<19>{0x2u})) : value<19>{0u})) : value<19>{0u}) : (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x1u}) ? (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x1u}) ? (and_uu<1>(p_ap__start, p_ap__CS__fsm.curr.slice<0>().val()) ? value<19>{0x2u} : value<19>{0x1u}) : value<19>{0u}) : value<19>{0u}))))))))))))))))))) : value<19>{0x1u});
	}
	// cells $procdff$1277 $procmux$1234 $and$matmul_partition.v:215$157 $and$matmul_partition.v:215$155 $not$matmul_partition.v:215$153 $and$matmul_partition.v:215$152 $eq$matmul_partition.v:215$151 $eq$matmul_partition.v:215$150 $procmux$1231 $and$matmul_partition.v:217$160
	if (posedge_p_ap__clk) {
		p_i__1__reg__156.next = (and_uu<1>(and_uu<1>(not_u<1>(and_uu<1>(not_u<1>(p_icmp__ln50__fu__173__p2), not_u<1>(p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr.slice<0>().val()))), p_icmp__ln50__fu__173__p2), p_ap__CS__fsm.curr.slice<1>().val()) ? value<8>{0u} : (and_uu<1>(p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr.slice<1>().val(), p_ap__CS__fsm.curr.slice<18>().val()) ? p_add__ln64__reg__391.curr : p_i__1__reg__156.curr));
	}
	// cells $procdff$1276 $procmux$1229 $and$matmul_partition.v:223$164 $procmux$1226 $and$matmul_partition.v:225$167
	if (posedge_p_ap__clk) {
		p_i__reg__145.next = (and_uu<1>(p_ap__start, p_ap__CS__fsm.curr.slice<0>().val()) ? value<8>{0u} : (and_uu<1>(p_ap__CS__fsm.curr.slice<8>().val(), p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr.slice<0>().val()) ? p_add__ln50__reg__339.curr : p_i__reg__145.curr));
	}
	// cells $procdff$1275 $procmux$1224 $and$matmul_partition.v:231$174 $not$matmul_partition.v:231$172 $and$matmul_partition.v:231$171 $eq$matmul_partition.v:231$170 $eq$matmul_partition.v:231$169 $add$matmul_partition.v:587$444
	if (posedge_p_ap__clk) {
		p_add__ln50__reg__339.next = (and_uu<1>(not_u<1>(and_uu<1>(not_u<1>(p_icmp__ln50__fu__173__p2), not_u<1>(p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr.slice<0>().val()))), p_ap__CS__fsm.curr.slice<1>().val()) ? add_uu<8>(p_i__reg__145.curr, value<8>{0x1u}) : p_add__ln50__reg__339.curr);
	}
	// cells $procdff$1274 $procmux$1222 $and$matmul_partition.v:237$178 $eq$matmul_partition.v:237$177 $add$matmul_partition.v:589$445
	if (posedge_p_ap__clk) {
		p_add__ln64__reg__391.next = (and_uu<1>(p_ap__CS__fsm.curr.slice<9>().val(), not_u<1>(p_regslice__both__Output__1__V__U__apdone__blk)) ? add_uu<8>(p_i__1__reg__156.curr, value<8>{0x1u}) : p_add__ln64__reg__391.curr);
	}
	// cells $procdff$1273 $procmux$1216 $ternary$matmul_partition.v:637$453 $eq$matmul_partition.v:637$452
	if (posedge_p_ap__clk) {
		p_icmp__ln414__reg__357.next = (i_and_24_matmul__partition_2e_v_3a_243_24_182__Y ? (logic_not<1>(p_i__reg__145.curr.slice<7,6>().val()) ? value<1>{0x1u} : value<1>{0u}) : p_icmp__ln414__reg__357.curr);
	}
	// cells $procdff$1272 $procmux$1218
	if (posedge_p_ap__clk) {
		p_trunc__ln414__reg__352.next = (i_and_24_matmul__partition_2e_v_3a_243_24_182__Y ? p_i__reg__145.curr.slice<5,0>().val() : p_trunc__ln414__reg__352.curr);
	}
	// cells $procdff$1271 $procmux$1220
	if (posedge_p_ap__clk) {
		p_tmp__V__reg__347.next = (i_and_24_matmul__partition_2e_v_3a_243_24_182__Y ? p_regslice__both__Input__1__V__U_2e_B__V__data__1__data__out : p_tmp__V__reg__347.curr);
	}
	// cells $procdff$1270 $procmux$1214 $and$matmul_partition.v:251$186 $eq$matmul_partition.v:251$185 $ternary$matmul_partition.v:643$459 $eq$matmul_partition.v:643$458
	if (posedge_p_ap__clk) {
		p_icmp__ln674__reg__409.next = (and_uu<1>(p_ap__CS__fsm.curr.slice<9>().val(), not_u<1>(p_icmp__ln64__fu__225__p2)) ? (logic_not<1>(p_i__1__reg__156.curr.slice<7,6>().val()) ? value<1>{0x1u} : value<1>{0u}) : p_icmp__ln674__reg__409.curr);
	}
	// cells $procdff$1269 $procmux$1200
	if (posedge_p_ap__clk) {
		p_trunc__ln674__1__reg__449.next = (i_eq_24_matmul__partition_2e_v_3a_257_24_188__Y ? i_ternary_24_matmul__partition_2e_v_3a_647_24_461__Y.slice<31,0>().val() : p_trunc__ln674__1__reg__449.curr);
	}
	// cells $procdff$1268 $procmux$1202
	if (posedge_p_ap__clk) {
		p_p__Result__6__reg__444.next = (i_eq_24_matmul__partition_2e_v_3a_257_24_188__Y ? i_ternary_24_matmul__partition_2e_v_3a_647_24_461__Y.slice<63,32>().val() : p_p__Result__6__reg__444.curr);
	}
	// cells $procdff$1267 $procmux$1204
	if (posedge_p_ap__clk) {
		p_p__Result__5__reg__439.next = (i_eq_24_matmul__partition_2e_v_3a_257_24_188__Y ? i_ternary_24_matmul__partition_2e_v_3a_647_24_461__Y.slice<95,64>().val() : p_p__Result__5__reg__439.curr);
	}
	// cells $procdff$1266 $procmux$1206
	if (posedge_p_ap__clk) {
		p_p__Result__4__reg__434.next = (i_eq_24_matmul__partition_2e_v_3a_257_24_188__Y ? i_ternary_24_matmul__partition_2e_v_3a_647_24_461__Y.slice<127,96>().val() : p_p__Result__4__reg__434.curr);
	}
	// cells $procdff$1265 $procmux$1208
	if (posedge_p_ap__clk) {
		p_p__Result__3__reg__429.next = (i_eq_24_matmul__partition_2e_v_3a_257_24_188__Y ? i_ternary_24_matmul__partition_2e_v_3a_647_24_461__Y.slice<159,128>().val() : p_p__Result__3__reg__429.curr);
	}
	// cells $procdff$1240 $procmux$540 $procmux$537 $flatten\regslice_both_Output_1_V_U.$and$matmul_partition_regslice_both.v:58$473 $flatten\regslice_both_Output_1_V_U.$not$matmul_partition_regslice_both.v:59$474
	if (posedge_p_ap__clk) {
		p_regslice__both__Output__1__V__U_2e_B__V__data__1__sel__wr.next = (p_ap__rst__n ? (and_uu<1>(i_procmux_24_1012__Y, p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr.slice<1>().val()) ? not_u<1>(p_regslice__both__Output__1__V__U_2e_B__V__data__1__sel__wr.curr) : p_regslice__both__Output__1__V__U_2e_B__V__data__1__sel__wr.curr) : value<1>{0u});
	}
	// cells $procdff$1239 $procmux$534 $procmux$531 $flatten\regslice_both_Output_1_V_U.$and$matmul_partition_regslice_both.v:46$467 $flatten\regslice_both_Output_1_V_U.$not$matmul_partition_regslice_both.v:47$468
	if (posedge_p_ap__clk) {
		p_regslice__both__Output__1__V__U_2e_B__V__data__1__sel__rd.next = (p_ap__rst__n ? (and_uu<1>(p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr.slice<0>().val(), p_Output__1__V__TREADY) ? not_u<1>(p_regslice__both__Output__1__V__U_2e_B__V__data__1__sel__rd.curr) : p_regslice__both__Output__1__V__U_2e_B__V__data__1__sel__rd.curr) : value<1>{0u});
	}
	// cells $procdff$1244 $procmux$565 $procmux$562 $flatten\regslice_both_Input_1_V_U.$and$matmul_partition_regslice_both.v:46$467 $flatten\regslice_both_Input_1_V_U.$not$matmul_partition_regslice_both.v:47$468
	if (posedge_p_ap__clk) {
		p_regslice__both__Input__1__V__U_2e_B__V__data__1__sel__rd.next = (p_ap__rst__n ? (and_uu<1>(p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr.slice<0>().val(), i_procmux_24_1153__Y) ? not_u<1>(p_regslice__both__Input__1__V__U_2e_B__V__data__1__sel__rd.curr) : p_regslice__both__Input__1__V__U_2e_B__V__data__1__sel__rd.curr) : value<1>{0u});
	}
	// \src: matmul_partition.v:154.1-162.2|matmul_partition_A_V_0.v:24.1-31.4|matmul_partition_A_V_0.v:59.28-65.15
	// cell $procdff$1254
	if (posedge_p_ap__clk) {
		i_flatten_5c_A__V__0__U_2e__5c_matmul__partition__A__V__0__ram__U_2e__24_memwr_24__5c_ram_24_matmul__partition__A__V__0_2e_v_3a_28_24_1__ADDR.next = i_procmux_24_647__Y;
	}
	// cells $procdff$1264 $procmux$1210
	if (posedge_p_ap__clk) {
		p_p__Result__2__reg__424.next = (i_eq_24_matmul__partition_2e_v_3a_257_24_188__Y ? i_ternary_24_matmul__partition_2e_v_3a_647_24_461__Y.slice<191,160>().val() : p_p__Result__2__reg__424.curr);
	}
	// cells $procdff$1263 $procmux$1212
	if (posedge_p_ap__clk) {
		p_p__Result__1__reg__419.next = (i_eq_24_matmul__partition_2e_v_3a_257_24_188__Y ? i_ternary_24_matmul__partition_2e_v_3a_647_24_461__Y.slice<223,192>().val() : p_p__Result__1__reg__419.curr);
	}
	// cells $procdff$1262 $procmux$1198
	if (posedge_p_ap__clk) {
		p_tmp__V__1__reg__361.next = (p_ap__CS__fsm.curr.slice<2>().val() ? p_regslice__both__Input__1__V__U_2e_B__V__data__1__data__out : p_tmp__V__1__reg__361.curr);
	}
	// cells $procdff$1261 $procmux$1196
	if (posedge_p_ap__clk) {
		p_tmp__V__2__reg__366.next = (p_ap__CS__fsm.curr.slice<3>().val() ? p_regslice__both__Input__1__V__U_2e_B__V__data__1__data__out : p_tmp__V__2__reg__366.curr);
	}
	// cells $procdff$1260 $procmux$1194
	if (posedge_p_ap__clk) {
		p_tmp__V__3__reg__371.next = (p_ap__CS__fsm.curr.slice<4>().val() ? p_regslice__both__Input__1__V__U_2e_B__V__data__1__data__out : p_tmp__V__3__reg__371.curr);
	}
	// \src: matmul_partition.v:154.1-162.2|matmul_partition_A_V_0.v:24.1-31.4|matmul_partition_A_V_0.v:59.28-65.15
	// cell $procdff$1256
	if (posedge_p_ap__clk) {
		i_flatten_5c_A__V__0__U_2e__5c_matmul__partition__A__V__0__ram__U_2e__24_memwr_24__5c_ram_24_matmul__partition__A__V__0_2e_v_3a_28_24_1__EN.next = i_procmux_24_641__Y;
	}
	// \src: matmul_partition.v:154.1-162.2|matmul_partition_A_V_0.v:24.1-31.4|matmul_partition_A_V_0.v:59.28-65.15
	// cell $procdff$1255
	if (posedge_p_ap__clk) {
		i_flatten_5c_A__V__0__U_2e__5c_matmul__partition__A__V__0__ram__U_2e__24_memwr_24__5c_ram_24_matmul__partition__A__V__0_2e_v_3a_28_24_1__DATA.next = i_procmux_24_644__Y;
	}
	// cells $procdff$1259 $procmux$1192
	if (posedge_p_ap__clk) {
		p_tmp__V__4__reg__376.next = (p_ap__CS__fsm.curr.slice<5>().val() ? p_regslice__both__Input__1__V__U_2e_B__V__data__1__data__out : p_tmp__V__4__reg__376.curr);
	}
	// cells $procdff$1258 $procmux$1190
	if (posedge_p_ap__clk) {
		p_tmp__V__5__reg__381.next = (p_ap__CS__fsm.curr.slice<6>().val() ? p_regslice__both__Input__1__V__U_2e_B__V__data__1__data__out : p_tmp__V__5__reg__381.curr);
	}
	// cells $procdff$1257 $procmux$1188
	if (posedge_p_ap__clk) {
		p_tmp__V__6__reg__386.next = (p_ap__CS__fsm.curr.slice<7>().val() ? p_regslice__both__Input__1__V__U_2e_B__V__data__1__data__out : p_tmp__V__6__reg__386.curr);
	}
	// cells $procdff$1243 $procmux$556 $flatten\regslice_both_Output_1_V_U.$and$matmul_partition_regslice_both.v:104$522
	if (posedge_p_ap__clk) {
		p_regslice__both__Output__1__V__U_2e_B__V__data__1__payload__B.next = (and_uu<1>(p_regslice__both__Output__1__V__U_2e_B__V__data__1__state__cmp__full, p_regslice__both__Output__1__V__U_2e_B__V__data__1__sel__wr.curr) ? p_Output__1__V__TDATA__int__regslice : p_regslice__both__Output__1__V__U_2e_B__V__data__1__payload__B.curr);
	}
	// cells $procdff$1242 $procmux$554 $flatten\regslice_both_Output_1_V_U.$and$matmul_partition_regslice_both.v:103$521 $flatten\regslice_both_Output_1_V_U.$not$matmul_partition_regslice_both.v:103$520
	if (posedge_p_ap__clk) {
		p_regslice__both__Output__1__V__U_2e_B__V__data__1__payload__A.next = (and_uu<1>(not_u<1>(p_regslice__both__Output__1__V__U_2e_B__V__data__1__sel__wr.curr), p_regslice__both__Output__1__V__U_2e_B__V__data__1__state__cmp__full) ? p_Output__1__V__TDATA__int__regslice : p_regslice__both__Output__1__V__U_2e_B__V__data__1__payload__A.curr);
	}
	// cells $procmux$1009 $and$matmul_partition.v:415$355 $eq$matmul_partition.v:415$354 $and$matmul_partition.v:415$353
	p_ap__done = (and_uu<1>(and_uu<1>(p_ap__CS__fsm.curr.slice<9>().val(), p_icmp__ln64__fu__225__p2), not_u<1>(p_regslice__both__Output__1__V__U__apdone__blk)) ? value<1>{0x1u} : value<1>{0u});
	// cells $procmux$1006 $and$matmul_partition.v:423$359 $eq$matmul_partition.v:423$357
	p_ap__idle = (and_uu<1>(not_u<1>(p_ap__start), p_ap__CS__fsm.curr.slice<0>().val()) ? value<1>{0x1u} : value<1>{0u});
	// cells $procmux$1003 $and$matmul_partition.v:431$365 $eq$matmul_partition.v:431$364 $and$matmul_partition.v:431$363
	p_ap__ready = (and_uu<1>(and_uu<1>(p_ap__CS__fsm.curr.slice<9>().val(), p_icmp__ln64__fu__225__p2), not_u<1>(p_regslice__both__Output__1__V__U__apdone__blk)) ? value<1>{0x1u} : value<1>{0u});
	// \full_case: 1
	// \src: matmul_partition_regslice_both.v:95.5-99.8
	// cell $procmux$559
	p_Output__1__V__TDATA = (p_regslice__both__Output__1__V__U_2e_B__V__data__1__sel__rd.curr ? p_regslice__both__Output__1__V__U_2e_B__V__data__1__payload__B.curr : p_regslice__both__Output__1__V__U_2e_B__V__data__1__payload__A.curr);
	// connection
	p_Output__1__V__TVALID = p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr.slice<0>().val();
	// connection
	p_Input__1__V__TREADY = p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr.slice<1>().val();
	return converged;
}

bool p_matmul__partition::commit() {
	bool changed = false;
	if (p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.commit()) changed = true;
	if (p_regslice__both__Output__1__V__U_2e_B__V__data__1__payload__A.commit()) changed = true;
	if (p_regslice__both__Output__1__V__U_2e_B__V__data__1__payload__B.commit()) changed = true;
	if (p_regslice__both__Output__1__V__U_2e_B__V__data__1__sel__rd.commit()) changed = true;
	if (p_regslice__both__Output__1__V__U_2e_B__V__data__1__sel__wr.commit()) changed = true;
	if (p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.commit()) changed = true;
	if (p_regslice__both__Input__1__V__U_2e_B__V__data__1__payload__A.commit()) changed = true;
	if (p_regslice__both__Input__1__V__U_2e_B__V__data__1__payload__B.commit()) changed = true;
	if (p_regslice__both__Input__1__V__U_2e_B__V__data__1__sel__rd.commit()) changed = true;
	if (p_regslice__both__Input__1__V__U_2e_B__V__data__1__sel__wr.commit()) changed = true;
	if (i_flatten_5c_A__V__1__U_2e__5c_matmul__partition__A__V__0__ram__U_2e__24_memwr_24__5c_ram_24_matmul__partition__A__V__0_2e_v_3a_28_24_1__EN.commit()) changed = true;
	if (i_flatten_5c_A__V__1__U_2e__5c_matmul__partition__A__V__0__ram__U_2e__24_memwr_24__5c_ram_24_matmul__partition__A__V__0_2e_v_3a_28_24_1__DATA.commit()) changed = true;
	if (i_flatten_5c_A__V__1__U_2e__5c_matmul__partition__A__V__0__ram__U_2e__24_memwr_24__5c_ram_24_matmul__partition__A__V__0_2e_v_3a_28_24_1__ADDR.commit()) changed = true;
	if (p_A__V__1__U_2e_matmul__partition__A__V__0__ram__U_2e_q0.commit()) changed = true;
	if (i_flatten_5c_A__V__0__U_2e__5c_matmul__partition__A__V__0__ram__U_2e__24_memwr_24__5c_ram_24_matmul__partition__A__V__0_2e_v_3a_28_24_1__EN.commit()) changed = true;
	if (i_flatten_5c_A__V__0__U_2e__5c_matmul__partition__A__V__0__ram__U_2e__24_memwr_24__5c_ram_24_matmul__partition__A__V__0_2e_v_3a_28_24_1__DATA.commit()) changed = true;
	if (i_flatten_5c_A__V__0__U_2e__5c_matmul__partition__A__V__0__ram__U_2e__24_memwr_24__5c_ram_24_matmul__partition__A__V__0_2e_v_3a_28_24_1__ADDR.commit()) changed = true;
	if (p_A__V__0__U_2e_matmul__partition__A__V__0__ram__U_2e_q0.commit()) changed = true;
	if (p_i__1__reg__156.commit()) changed = true;
	if (p_i__reg__145.commit()) changed = true;
	if (p_trunc__ln674__1__reg__449.commit()) changed = true;
	if (p_p__Result__6__reg__444.commit()) changed = true;
	if (p_p__Result__5__reg__439.commit()) changed = true;
	if (p_p__Result__4__reg__434.commit()) changed = true;
	if (p_p__Result__3__reg__429.commit()) changed = true;
	if (p_p__Result__2__reg__424.commit()) changed = true;
	if (p_p__Result__1__reg__419.commit()) changed = true;
	if (p_icmp__ln674__reg__409.commit()) changed = true;
	if (p_add__ln64__reg__391.commit()) changed = true;
	if (p_tmp__V__6__reg__386.commit()) changed = true;
	if (p_tmp__V__5__reg__381.commit()) changed = true;
	if (p_tmp__V__4__reg__376.commit()) changed = true;
	if (p_tmp__V__3__reg__371.commit()) changed = true;
	if (p_tmp__V__2__reg__366.commit()) changed = true;
	if (p_tmp__V__1__reg__361.commit()) changed = true;
	if (p_icmp__ln414__reg__357.commit()) changed = true;
	if (p_trunc__ln414__reg__352.commit()) changed = true;
	if (p_tmp__V__reg__347.commit()) changed = true;
	if (p_add__ln50__reg__339.commit()) changed = true;
	if (p_ap__CS__fsm.commit()) changed = true;
	prev_p_ap__clk = p_ap__clk;
	if (memory_p_A__V__1__U_2e_matmul__partition__A__V__0__ram__U_2e_ram.commit()) changed = true;
	if (memory_p_A__V__0__U_2e_matmul__partition__A__V__0__ram__U_2e_ram.commit()) changed = true;
	return changed;
}

void p_matmul__partition::debug_eval() {
	// \src: matmul_partition.v:647.30-647.85
	value<256> i_ternary_24_matmul__partition_2e_v_3a_647_24_461__Y;
	// \src: matmul_partition.v:506.18-506.127
	value<1> i_and_24_matmul__partition_2e_v_3a_506_24_411__Y;
	// \src: matmul_partition.v:448.18-448.153
	value<1> i_and_24_matmul__partition_2e_v_3a_448_24_377__Y;
	// \src: matmul_partition.v:394.23-394.48
	value<1> i_eq_24_matmul__partition_2e_v_3a_394_24_316__Y;
	// \src: matmul_partition.v:392.23-392.48
	value<1> i_eq_24_matmul__partition_2e_v_3a_392_24_315__Y;
	// \src: matmul_partition.v:390.23-390.48
	value<1> i_eq_24_matmul__partition_2e_v_3a_390_24_314__Y;
	// \src: matmul_partition.v:388.23-388.48
	value<1> i_eq_24_matmul__partition_2e_v_3a_388_24_313__Y;
	// \src: matmul_partition.v:386.23-386.48
	value<1> i_eq_24_matmul__partition_2e_v_3a_386_24_312__Y;
	// \src: matmul_partition.v:384.23-384.48
	value<1> i_eq_24_matmul__partition_2e_v_3a_384_24_311__Y;
	// \src: matmul_partition.v:382.14-382.39
	value<1> i_eq_24_matmul__partition_2e_v_3a_382_24_310__Y;
	// \src: matmul_partition.v:381.10-381.48
	value<1> i_eq_24_matmul__partition_2e_v_3a_381_24_309__Y;
	// \src: matmul_partition.v:331.10-331.35
	value<1> i_eq_24_matmul__partition_2e_v_3a_331_24_219__Y;
	// \src: matmul_partition.v:305.10-305.35
	value<1> i_eq_24_matmul__partition_2e_v_3a_305_24_202__Y;
	// \src: matmul_partition.v:647.30-647.85
	// cell $ternary$matmul_partition.v:647$461
	i_ternary_24_matmul__partition_2e_v_3a_647_24_461__Y = (p_icmp__ln674__reg__409.curr ? p_A__V__0__U_2e_matmul__partition__A__V__0__ram__U_2e_q0.curr : p_A__V__1__U_2e_matmul__partition__A__V__0__ram__U_2e_q0.curr);
	// connection
	i_eq_24_matmul__partition_2e_v_3a_394_24_316__Y = p_ap__CS__fsm.curr.slice<11>().val();
	// connection
	i_eq_24_matmul__partition_2e_v_3a_392_24_315__Y = p_ap__CS__fsm.curr.slice<12>().val();
	// connection
	i_eq_24_matmul__partition_2e_v_3a_390_24_314__Y = p_ap__CS__fsm.curr.slice<13>().val();
	// connection
	i_eq_24_matmul__partition_2e_v_3a_388_24_313__Y = p_ap__CS__fsm.curr.slice<14>().val();
	// connection
	i_eq_24_matmul__partition_2e_v_3a_386_24_312__Y = p_ap__CS__fsm.curr.slice<15>().val();
	// connection
	i_eq_24_matmul__partition_2e_v_3a_384_24_311__Y = p_ap__CS__fsm.curr.slice<16>().val();
	// connection
	i_eq_24_matmul__partition_2e_v_3a_382_24_310__Y = p_ap__CS__fsm.curr.slice<17>().val();
	// connection
	i_eq_24_matmul__partition_2e_v_3a_381_24_309__Y = p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr.slice<1>().val();
	// cells $ternary$matmul_partition.v:639$455 $eq$matmul_partition.v:639$454
	p_icmp__ln50__fu__173__p2 = (eq_uu<1>(p_i__reg__145.curr, value<8>{0x80u}) ? value<1>{0x1u} : value<1>{0u});
	// cells $flatten\regslice_both_Output_1_V_U.$or$matmul_partition_regslice_both.v:117$529 $flatten\regslice_both_Output_1_V_U.$eq$matmul_partition_regslice_both.v:117$528 $flatten\regslice_both_Output_1_V_U.$logic_and$matmul_partition_regslice_both.v:117$527 $flatten\regslice_both_Output_1_V_U.$eq$matmul_partition_regslice_both.v:117$526 $flatten\regslice_both_Output_1_V_U.$eq$matmul_partition_regslice_both.v:117$525
	p_regslice__both__Output__1__V__U_2e_apdone__blk = or_uu<1>(logic_and<1>(eq_uu<1>(p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr, value<2>{0x3u}), not_u<1>(p_Output__1__V__TREADY)), eq_uu<1>(p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr, value<2>{0x1u}));
	// cells $ternary$matmul_partition.v:641$457 $eq$matmul_partition.v:641$456
	p_icmp__ln64__fu__225__p2 = (eq_uu<1>(p_i__1__reg__156.curr, value<8>{0x80u}) ? value<1>{0x1u} : value<1>{0u});
	// connection
	i_eq_24_matmul__partition_2e_v_3a_305_24_202__Y = p_ap__CS__fsm.curr.slice<9>().val();
	// connection
	i_eq_24_matmul__partition_2e_v_3a_331_24_219__Y = p_ap__CS__fsm.curr.slice<9>().val();
	// cells $and$matmul_partition.v:448$377 $and$matmul_partition.v:448$375 $not$matmul_partition.v:448$373 $and$matmul_partition.v:448$372 $eq$matmul_partition.v:448$371 $eq$matmul_partition.v:448$370
	i_and_24_matmul__partition_2e_v_3a_448_24_377__Y = and_uu<1>(and_uu<1>(not_u<1>(and_uu<1>(not_u<1>(p_icmp__ln50__fu__173__p2), not_u<1>(p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr.slice<0>().val()))), p_icmp__ln50__fu__173__p2), p_ap__CS__fsm.curr.slice<1>().val());
	// cells $and$matmul_partition.v:506$411 $eq$matmul_partition.v:506$410 $and$matmul_partition.v:506$409
	i_and_24_matmul__partition_2e_v_3a_506_24_411__Y = and_uu<1>(and_uu<1>(p_ap__CS__fsm.curr.slice<9>().val(), p_icmp__ln64__fu__225__p2), not_u<1>(p_regslice__both__Output__1__V__U_2e_apdone__blk));
	// cells $procmux$1174 $and$matmul_partition.v:323$217 $and$matmul_partition.v:323$215
	p_A__V__0__we0 = (and_uu<1>(and_uu<1>(p_ap__CS__fsm.curr.slice<8>().val(), p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr.slice<0>().val()), p_icmp__ln414__reg__357.curr) ? value<1>{0x1u} : value<1>{0u});
	// cells $procmux$1159 $and$matmul_partition.v:349$234 $eq$matmul_partition.v:349$233 $and$matmul_partition.v:349$232
	p_A__V__1__we0 = (and_uu<1>(and_uu<1>(p_ap__CS__fsm.curr.slice<8>().val(), p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr.slice<0>().val()), not_u<1>(p_icmp__ln414__reg__357.curr)) ? value<1>{0x1u} : value<1>{0u});
	// cells $procmux$1177 $or$matmul_partition.v:315$211 $and$matmul_partition.v:315$210 $eq$matmul_partition.v:315$209 $and$matmul_partition.v:315$207
	p_A__V__0__ce0 = (or_uu<1>(and_uu<1>(p_ap__CS__fsm.curr.slice<8>().val(), p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr.slice<0>().val()), and_uu<1>(p_ap__CS__fsm.curr.slice<9>().val(), not_u<1>(p_regslice__both__Output__1__V__U_2e_apdone__blk))) ? value<1>{0x1u} : value<1>{0u});
	// cells $procmux$1162 $or$matmul_partition.v:341$228 $and$matmul_partition.v:341$227 $eq$matmul_partition.v:341$226 $and$matmul_partition.v:341$224
	p_A__V__1__ce0 = (or_uu<1>(and_uu<1>(p_ap__CS__fsm.curr.slice<8>().val(), p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr.slice<0>().val()), and_uu<1>(p_ap__CS__fsm.curr.slice<9>().val(), not_u<1>(p_regslice__both__Output__1__V__U_2e_apdone__blk))) ? value<1>{0x1u} : value<1>{0u});
	// cells $procmux$1186 $procmux$1183 $procmux$1180
	p_A__V__0__address0 = (i_eq_24_matmul__partition_2e_v_3a_305_24_202__Y ? p_i__1__reg__156.curr.slice<5,0>().val() : (i_eq_24_matmul__partition_2e_v_3a_305_24_202__Y ? value<6>{0u} : (p_ap__CS__fsm.curr.slice<8>().val() ? p_trunc__ln414__reg__352.curr : value<6>{0u})));
	// \full_case: 1
	// \src: matmul_partition_regslice_both.v:95.5-99.8
	// cell $procmux$590
	p_regslice__both__Input__1__V__U_2e_B__V__data__1__data__out = (p_regslice__both__Input__1__V__U_2e_B__V__data__1__sel__rd.curr ? p_regslice__both__Input__1__V__U_2e_B__V__data__1__payload__B.curr : p_regslice__both__Input__1__V__U_2e_B__V__data__1__payload__A.curr);
	// cells $procmux$1171 $procmux$1168 $procmux$1165
	p_A__V__1__address0 = (i_eq_24_matmul__partition_2e_v_3a_331_24_219__Y ? p_i__1__reg__156.curr.slice<5,0>().val() : (i_eq_24_matmul__partition_2e_v_3a_331_24_219__Y ? value<6>{0u} : (p_ap__CS__fsm.curr.slice<8>().val() ? p_trunc__ln414__reg__352.curr : value<6>{0u})));
	// connection
	p_Input__1__V__TREADY__int__regslice = (or_uu<1>(or_uu<1>(or_uu<1>(or_uu<1>(or_uu<1>(or_uu<1>(or_uu<1>(and_uu<1>(p_ap__CS__fsm.curr.slice<8>().val(), p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr.slice<0>().val()), and_uu<1>(p_ap__CS__fsm.curr.slice<7>().val(), p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr.slice<0>().val())), and_uu<1>(p_ap__CS__fsm.curr.slice<6>().val(), p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr.slice<0>().val())), and_uu<1>(p_ap__CS__fsm.curr.slice<5>().val(), p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr.slice<0>().val())), and_uu<1>(p_ap__CS__fsm.curr.slice<4>().val(), p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr.slice<0>().val())), and_uu<1>(p_ap__CS__fsm.curr.slice<3>().val(), p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr.slice<0>().val())), and_uu<1>(p_ap__CS__fsm.curr.slice<2>().val(), p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr.slice<0>().val())), and_uu<1>(and_uu<1>(not_u<1>(and_uu<1>(not_u<1>(p_icmp__ln50__fu__173__p2), not_u<1>(p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr.slice<0>().val()))), not_u<1>(p_icmp__ln50__fu__173__p2)), p_ap__CS__fsm.curr.slice<1>().val())) ? value<1>{0x1u} : value<1>{0u});
	// cells $flatten\regslice_both_Input_1_V_U.$ternary$matmul_partition_regslice_both.v:106$524 $flatten\regslice_both_Input_1_V_U.$ne$matmul_partition_regslice_both.v:106$523
	p_regslice__both__Input__1__V__U_2e_B__V__data__1__state__cmp__full = (ne_uu<1>(p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr, value<2>{0x1u}) ? value<1>{0x1u} : value<1>{0u});
	// cells $flatten\regslice_both_Output_1_V_U.$ternary$matmul_partition_regslice_both.v:106$524 $flatten\regslice_both_Output_1_V_U.$ne$matmul_partition_regslice_both.v:106$523
	p_regslice__both__Output__1__V__U_2e_B__V__data__1__state__cmp__full = (ne_uu<1>(p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr, value<2>{0x1u}) ? value<1>{0x1u} : value<1>{0u});
	// connection
	p_tmp__fu__183__p4 = p_i__reg__145.curr.slice<7,6>().val();
	// connection
	p_tmp__1__fu__241__p4 = p_i__1__reg__156.curr.slice<7,6>().val();
	// connection
	p_ap__rst__n__inv = not_u<1>(p_ap__rst__n);
	// connection
	p_regslice__both__Output__1__V__U_2e_B__V__data__1__vld__out = p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr.slice<0>().val();
	// connection
	p_regslice__both__Input__1__V__U_2e_B__V__data__1__ack__in = p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr.slice<1>().val();
	// cells $procmux$982 $procmux$983_CMP0 $procmux$984_CMP0 $procmux$985_CMP0 $procmux$986_CMP0 $procmux$987_CMP0 $procmux$988_CMP0 $procmux$989_CMP0 $procmux$990_CMP0 $procmux$991_CMP0 $procmux$992_CMP0 $procmux$993_CMP0 $procmux$994_CMP0 $procmux$995_CMP0 $procmux$996_CMP0 $procmux$997_CMP0 $procmux$998_CMP0 $procmux$999_CMP0 $procmux$1000_CMP0 $procmux$1001_CMP0 $procmux$656 $procmux$657_CMP0 $procmux$654 $and$matmul_partition.v:571$443 $procmux$663 $procmux$664_CMP0 $procmux$661 $and$matmul_partition.v:564$440 $procmux$671 $procmux$672_CMP0 $procmux$669 $and$matmul_partition.v:557$437 $procmux$680 $procmux$681_CMP0 $procmux$678 $and$matmul_partition.v:550$434 $procmux$690 $procmux$691_CMP0 $procmux$688 $and$matmul_partition.v:543$431 $procmux$701 $procmux$702_CMP0 $procmux$699 $and$matmul_partition.v:536$428 $procmux$713 $procmux$714_CMP0 $procmux$711 $and$matmul_partition.v:529$425 $procmux$726 $procmux$727_CMP0 $procmux$724 $and$matmul_partition.v:522$422 $procmux$740 $procmux$741_CMP0 $procmux$738 $and$matmul_partition.v:515$419 $procmux$773 $procmux$774_CMP0 $procmux$771 $procmux$758 $procmux$759_CMP0 $procmux$756 $procmux$753 $and$matmul_partition.v:508$416 $eq$matmul_partition.v:508$415 $and$matmul_partition.v:508$414 $eq$matmul_partition.v:508$413 $procmux$789 $procmux$790_CMP0 $procmux$787 $and$matmul_partition.v:499$406 $procmux$806 $procmux$807_CMP0 $procmux$804 $and$matmul_partition.v:492$403 $procmux$824 $procmux$825_CMP0 $procmux$822 $and$matmul_partition.v:485$400 $procmux$843 $procmux$844_CMP0 $procmux$841 $and$matmul_partition.v:478$397 $procmux$863 $procmux$864_CMP0 $procmux$861 $and$matmul_partition.v:471$394 $procmux$884 $procmux$885_CMP0 $procmux$882 $and$matmul_partition.v:464$391 $procmux$906 $procmux$907_CMP0 $procmux$904 $and$matmul_partition.v:457$388 $procmux$955 $procmux$956_CMP0 $procmux$953 $procmux$932 $procmux$933_CMP0 $procmux$930 $procmux$927 $and$matmul_partition.v:450$385 $and$matmul_partition.v:450$383 $eq$matmul_partition.v:450$382 $not$matmul_partition.v:450$381 $and$matmul_partition.v:450$380 $eq$matmul_partition.v:450$379 $eq$matmul_partition.v:450$378 $procmux$979 $procmux$980_CMP0 $procmux$977 $and$matmul_partition.v:441$369
	p_ap__NS__fsm = (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x40000u}) ? (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x40000u}) ? (and_uu<1>(p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr.slice<1>().val(), p_ap__CS__fsm.curr.slice<18>().val()) ? value<19>{0x200u} : value<19>{0x40000u}) : value<19>{0u}) : (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x20000u}) ? (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x20000u}) ? (and_uu<1>(p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr.slice<1>().val(), p_ap__CS__fsm.curr.slice<17>().val()) ? value<19>{0x40000u} : value<19>{0x20000u}) : value<19>{0u}) : (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x10000u}) ? (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x10000u}) ? (and_uu<1>(p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr.slice<1>().val(), p_ap__CS__fsm.curr.slice<16>().val()) ? value<19>{0x20000u} : value<19>{0x10000u}) : value<19>{0u}) : (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x8000u}) ? (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x8000u}) ? (and_uu<1>(p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr.slice<1>().val(), p_ap__CS__fsm.curr.slice<15>().val()) ? value<19>{0x10000u} : value<19>{0x8000u}) : value<19>{0u}) : (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x4000u}) ? (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x4000u}) ? (and_uu<1>(p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr.slice<1>().val(), p_ap__CS__fsm.curr.slice<14>().val()) ? value<19>{0x8000u} : value<19>{0x4000u}) : value<19>{0u}) : (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x2000u}) ? (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x2000u}) ? (and_uu<1>(p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr.slice<1>().val(), p_ap__CS__fsm.curr.slice<13>().val()) ? value<19>{0x4000u} : value<19>{0x2000u}) : value<19>{0u}) : (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x1000u}) ? (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x1000u}) ? (and_uu<1>(p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr.slice<1>().val(), p_ap__CS__fsm.curr.slice<12>().val()) ? value<19>{0x2000u} : value<19>{0x1000u}) : value<19>{0u}) : (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x800u}) ? (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x800u}) ? (and_uu<1>(p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr.slice<1>().val(), p_ap__CS__fsm.curr.slice<11>().val()) ? value<19>{0x1000u} : value<19>{0x800u}) : value<19>{0u}) : (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x400u}) ? (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x400u}) ? (and_uu<1>(p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr.slice<1>().val(), p_ap__CS__fsm.curr.slice<10>().val()) ? value<19>{0x800u} : value<19>{0x400u}) : value<19>{0u}) : (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x200u}) ? (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x200u}) ? (i_and_24_matmul__partition_2e_v_3a_506_24_411__Y ? value<19>{0x1u} : (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x200u}) ? (i_and_24_matmul__partition_2e_v_3a_506_24_411__Y ? value<19>{0u} : (and_uu<1>(and_uu<1>(p_ap__CS__fsm.curr.slice<9>().val(), not_u<1>(p_icmp__ln64__fu__225__p2)), not_u<1>(p_regslice__both__Output__1__V__U_2e_apdone__blk)) ? value<19>{0x400u} : value<19>{0x200u})) : value<19>{0u})) : value<19>{0u}) : (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x100u}) ? (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x100u}) ? (and_uu<1>(p_ap__CS__fsm.curr.slice<8>().val(), p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr.slice<0>().val()) ? value<19>{0x2u} : value<19>{0x100u}) : value<19>{0u}) : (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x80u}) ? (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x80u}) ? (and_uu<1>(p_ap__CS__fsm.curr.slice<7>().val(), p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr.slice<0>().val()) ? value<19>{0x100u} : value<19>{0x80u}) : value<19>{0u}) : (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x40u}) ? (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x40u}) ? (and_uu<1>(p_ap__CS__fsm.curr.slice<6>().val(), p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr.slice<0>().val()) ? value<19>{0x80u} : value<19>{0x40u}) : value<19>{0u}) : (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x20u}) ? (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x20u}) ? (and_uu<1>(p_ap__CS__fsm.curr.slice<5>().val(), p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr.slice<0>().val()) ? value<19>{0x40u} : value<19>{0x20u}) : value<19>{0u}) : (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x10u}) ? (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x10u}) ? (and_uu<1>(p_ap__CS__fsm.curr.slice<4>().val(), p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr.slice<0>().val()) ? value<19>{0x20u} : value<19>{0x10u}) : value<19>{0u}) : (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x8u}) ? (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x8u}) ? (and_uu<1>(p_ap__CS__fsm.curr.slice<3>().val(), p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr.slice<0>().val()) ? value<19>{0x10u} : value<19>{0x8u}) : value<19>{0u}) : (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x4u}) ? (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x4u}) ? (and_uu<1>(p_ap__CS__fsm.curr.slice<2>().val(), p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr.slice<0>().val()) ? value<19>{0x8u} : value<19>{0x4u}) : value<19>{0u}) : (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x2u}) ? (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x2u}) ? (i_and_24_matmul__partition_2e_v_3a_448_24_377__Y ? value<19>{0x200u} : (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x2u}) ? (i_and_24_matmul__partition_2e_v_3a_448_24_377__Y ? value<19>{0u} : (and_uu<1>(and_uu<1>(not_u<1>(and_uu<1>(not_u<1>(p_icmp__ln50__fu__173__p2), not_u<1>(p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr.slice<0>().val()))), not_u<1>(p_icmp__ln50__fu__173__p2)), p_ap__CS__fsm.curr.slice<1>().val()) ? value<19>{0x4u} : value<19>{0x2u})) : value<19>{0u})) : value<19>{0u}) : (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x1u}) ? (eq_uu<1>(p_ap__CS__fsm.curr, value<19>{0x1u}) ? (and_uu<1>(p_ap__start, p_ap__CS__fsm.curr.slice<0>().val()) ? value<19>{0x2u} : value<19>{0x1u}) : value<19>{0u}) : value<19>{0u})))))))))))))))))));
	// cells $procmux$1147 $procmux$1144 $procmux$1142 $procmux$1138 $procmux$1136 $procmux$1133 $procmux$1129 $procmux$1127 $procmux$1124 $procmux$1121 $procmux$1117 $procmux$1115 $procmux$1112 $procmux$1109 $procmux$1106 $procmux$1102 $procmux$1100 $procmux$1097 $procmux$1094 $procmux$1091 $procmux$1088 $procmux$1084 $procmux$1082 $procmux$1079 $procmux$1076 $procmux$1073 $procmux$1070 $procmux$1067 $procmux$1063 $procmux$1061 $procmux$1058 $procmux$1055 $procmux$1052 $procmux$1049 $procmux$1046 $procmux$1043 $procmux$1039 $procmux$1037 $procmux$1034 $procmux$1031 $procmux$1028 $procmux$1025 $procmux$1022 $procmux$1019 $procmux$1016
	p_Output__1__V__TDATA__int__regslice = (i_eq_24_matmul__partition_2e_v_3a_381_24_309__Y ? (i_eq_24_matmul__partition_2e_v_3a_381_24_309__Y ? (i_eq_24_matmul__partition_2e_v_3a_382_24_310__Y ? p_trunc__ln674__1__reg__449.curr : (i_eq_24_matmul__partition_2e_v_3a_381_24_309__Y ? (i_eq_24_matmul__partition_2e_v_3a_382_24_310__Y ? value<32>{0u} : (i_eq_24_matmul__partition_2e_v_3a_384_24_311__Y ? p_p__Result__6__reg__444.curr : (i_eq_24_matmul__partition_2e_v_3a_381_24_309__Y ? (i_eq_24_matmul__partition_2e_v_3a_382_24_310__Y ? value<32>{0u} : (i_eq_24_matmul__partition_2e_v_3a_384_24_311__Y ? value<32>{0u} : (i_eq_24_matmul__partition_2e_v_3a_386_24_312__Y ? p_p__Result__5__reg__439.curr : (i_eq_24_matmul__partition_2e_v_3a_381_24_309__Y ? (i_eq_24_matmul__partition_2e_v_3a_382_24_310__Y ? value<32>{0u} : (i_eq_24_matmul__partition_2e_v_3a_384_24_311__Y ? value<32>{0u} : (i_eq_24_matmul__partition_2e_v_3a_386_24_312__Y ? value<32>{0u} : (i_eq_24_matmul__partition_2e_v_3a_388_24_313__Y ? p_p__Result__4__reg__434.curr : (i_eq_24_matmul__partition_2e_v_3a_381_24_309__Y ? (i_eq_24_matmul__partition_2e_v_3a_382_24_310__Y ? value<32>{0u} : (i_eq_24_matmul__partition_2e_v_3a_384_24_311__Y ? value<32>{0u} : (i_eq_24_matmul__partition_2e_v_3a_386_24_312__Y ? value<32>{0u} : (i_eq_24_matmul__partition_2e_v_3a_388_24_313__Y ? value<32>{0u} : (i_eq_24_matmul__partition_2e_v_3a_390_24_314__Y ? p_p__Result__3__reg__429.curr : (i_eq_24_matmul__partition_2e_v_3a_381_24_309__Y ? (i_eq_24_matmul__partition_2e_v_3a_382_24_310__Y ? value<32>{0u} : (i_eq_24_matmul__partition_2e_v_3a_384_24_311__Y ? value<32>{0u} : (i_eq_24_matmul__partition_2e_v_3a_386_24_312__Y ? value<32>{0u} : (i_eq_24_matmul__partition_2e_v_3a_388_24_313__Y ? value<32>{0u} : (i_eq_24_matmul__partition_2e_v_3a_390_24_314__Y ? value<32>{0u} : (i_eq_24_matmul__partition_2e_v_3a_392_24_315__Y ? p_p__Result__2__reg__424.curr : (i_eq_24_matmul__partition_2e_v_3a_381_24_309__Y ? (i_eq_24_matmul__partition_2e_v_3a_382_24_310__Y ? value<32>{0u} : (i_eq_24_matmul__partition_2e_v_3a_384_24_311__Y ? value<32>{0u} : (i_eq_24_matmul__partition_2e_v_3a_386_24_312__Y ? value<32>{0u} : (i_eq_24_matmul__partition_2e_v_3a_388_24_313__Y ? value<32>{0u} : (i_eq_24_matmul__partition_2e_v_3a_390_24_314__Y ? value<32>{0u} : (i_eq_24_matmul__partition_2e_v_3a_392_24_315__Y ? value<32>{0u} : (i_eq_24_matmul__partition_2e_v_3a_394_24_316__Y ? p_p__Result__1__reg__419.curr : (i_eq_24_matmul__partition_2e_v_3a_381_24_309__Y ? (i_eq_24_matmul__partition_2e_v_3a_382_24_310__Y ? value<32>{0u} : (i_eq_24_matmul__partition_2e_v_3a_384_24_311__Y ? value<32>{0u} : (i_eq_24_matmul__partition_2e_v_3a_386_24_312__Y ? value<32>{0u} : (i_eq_24_matmul__partition_2e_v_3a_388_24_313__Y ? value<32>{0u} : (i_eq_24_matmul__partition_2e_v_3a_390_24_314__Y ? value<32>{0u} : (i_eq_24_matmul__partition_2e_v_3a_392_24_315__Y ? value<32>{0u} : (i_eq_24_matmul__partition_2e_v_3a_394_24_316__Y ? value<32>{0u} : (p_ap__CS__fsm.curr.slice<10>().val() ? i_ternary_24_matmul__partition_2e_v_3a_647_24_461__Y.slice<255,224>().val() : value<32>{0u})))))))) : value<32>{0u})))))))) : value<32>{0u}))))))) : value<32>{0u})))))) : value<32>{0u}))))) : value<32>{0u})))) : value<32>{0u}))) : value<32>{0u})) : value<32>{0u}) : value<32>{0u});
	// connection
	p_regslice__both__Output__1__V__U_2e_B__V__data__1__ack__in = p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr.slice<1>().val();
	// \full_case: 1
	// \src: matmul_partition_regslice_both.v:95.5-99.8
	// cell $procmux$559
	p_regslice__both__Output__1__V__U_2e_B__V__data__1__data__out = (p_regslice__both__Output__1__V__U_2e_B__V__data__1__sel__rd.curr ? p_regslice__both__Output__1__V__U_2e_B__V__data__1__payload__B.curr : p_regslice__both__Output__1__V__U_2e_B__V__data__1__payload__A.curr);
	// connection
	p_Output__1__V__TVALID__int__regslice = (or_uu<1>(or_uu<1>(or_uu<1>(or_uu<1>(or_uu<1>(or_uu<1>(or_uu<1>(and_uu<1>(p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr.slice<1>().val(), p_ap__CS__fsm.curr.slice<17>().val()), and_uu<1>(p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr.slice<1>().val(), p_ap__CS__fsm.curr.slice<16>().val())), and_uu<1>(p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr.slice<1>().val(), p_ap__CS__fsm.curr.slice<15>().val())), and_uu<1>(p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr.slice<1>().val(), p_ap__CS__fsm.curr.slice<14>().val())), and_uu<1>(p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr.slice<1>().val(), p_ap__CS__fsm.curr.slice<13>().val())), and_uu<1>(p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr.slice<1>().val(), p_ap__CS__fsm.curr.slice<12>().val())), and_uu<1>(p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr.slice<1>().val(), p_ap__CS__fsm.curr.slice<11>().val())), and_uu<1>(p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr.slice<1>().val(), p_ap__CS__fsm.curr.slice<10>().val())) ? value<1>{0x1u} : value<1>{0u});
	// connection
	p_regslice__both__Input__1__V__U_2e_B__V__data__1__vld__out = p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr.slice<0>().val();
	// connection
	p_p__Result__s__fu__204__p9 = p_tmp__V__reg__347.curr.concat(p_tmp__V__1__reg__361.curr).concat(p_tmp__V__2__reg__366.curr).concat(p_tmp__V__3__reg__371.curr).concat(p_tmp__V__4__reg__376.curr).concat(p_tmp__V__5__reg__381.curr).concat(p_tmp__V__6__reg__386.curr).concat(p_regslice__both__Input__1__V__U_2e_B__V__data__1__data__out).val();
	// connection
	p_regslice__both__Input__1__V__U_2e_apdone__blk = or_uu<1>(logic_and<1>(eq_uu<1>(p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr, value<2>{0x3u}), not_u<1>(p_Input__1__V__TREADY__int__regslice)), eq_uu<1>(p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr, value<2>{0x1u}));
	// connection
	p_trunc__ln674__fu__231__p1 = p_i__1__reg__156.curr.slice<5,0>().val();
	// connection
	p_p__Val2__s__fu__257__p3 = i_ternary_24_matmul__partition_2e_v_3a_647_24_461__Y;
	// connection
	p_Input__1__V__TDATA__blk__n = (or_uu<1>(or_uu<1>(or_uu<1>(or_uu<1>(or_uu<1>(or_uu<1>(or_uu<1>(p_ap__CS__fsm.curr.slice<8>().val(), p_ap__CS__fsm.curr.slice<7>().val()), p_ap__CS__fsm.curr.slice<6>().val()), p_ap__CS__fsm.curr.slice<5>().val()), p_ap__CS__fsm.curr.slice<4>().val()), p_ap__CS__fsm.curr.slice<3>().val()), p_ap__CS__fsm.curr.slice<2>().val()), and_uu<1>(not_u<1>(p_icmp__ln50__fu__173__p2), p_ap__CS__fsm.curr.slice<1>().val())) ? p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr.slice<0>().val() : value<1>{0x1u});
	// connection
	p_Output__1__V__TDATA__blk__n = (or_uu<1>(or_uu<1>(or_uu<1>(or_uu<1>(or_uu<1>(or_uu<1>(or_uu<1>(or_uu<1>(p_ap__CS__fsm.curr.slice<18>().val(), p_ap__CS__fsm.curr.slice<17>().val()), p_ap__CS__fsm.curr.slice<16>().val()), p_ap__CS__fsm.curr.slice<15>().val()), p_ap__CS__fsm.curr.slice<14>().val()), p_ap__CS__fsm.curr.slice<13>().val()), p_ap__CS__fsm.curr.slice<12>().val()), p_ap__CS__fsm.curr.slice<11>().val()), p_ap__CS__fsm.curr.slice<10>().val()) ? p_regslice__both__Output__1__V__U_2e_B__V__data__1__state.curr.slice<1>().val() : value<1>{0x1u});
	// connection
	p_ap__block__state2 = and_uu<1>(not_u<1>(p_icmp__ln50__fu__173__p2), not_u<1>(p_regslice__both__Input__1__V__U_2e_B__V__data__1__state.curr.slice<0>().val()));
	// \src: matmul_partition.v:194.1-204.2|matmul_partition_regslice_both.v:104.29-104.74
	// cell $flatten\regslice_both_Output_1_V_U.$and$matmul_partition_regslice_both.v:104$522
	p_regslice__both__Output__1__V__U_2e_B__V__data__1__load__B = and_uu<1>(p_regslice__both__Output__1__V__U_2e_B__V__data__1__state__cmp__full, p_regslice__both__Output__1__V__U_2e_B__V__data__1__sel__wr.curr);
	// cells $flatten\regslice_both_Output_1_V_U.$and$matmul_partition_regslice_both.v:103$521 $flatten\regslice_both_Output_1_V_U.$not$matmul_partition_regslice_both.v:103$520
	p_regslice__both__Output__1__V__U_2e_B__V__data__1__load__A = and_uu<1>(not_u<1>(p_regslice__both__Output__1__V__U_2e_B__V__data__1__sel__wr.curr), p_regslice__both__Output__1__V__U_2e_B__V__data__1__state__cmp__full);
	// \src: matmul_partition.v:180.1-190.2|matmul_partition_regslice_both.v:104.29-104.74
	// cell $flatten\regslice_both_Input_1_V_U.$and$matmul_partition_regslice_both.v:104$522
	p_regslice__both__Input__1__V__U_2e_B__V__data__1__load__B = and_uu<1>(p_regslice__both__Input__1__V__U_2e_B__V__data__1__state__cmp__full, p_regslice__both__Input__1__V__U_2e_B__V__data__1__sel__wr.curr);
	// cells $flatten\regslice_both_Input_1_V_U.$and$matmul_partition_regslice_both.v:103$521 $flatten\regslice_both_Input_1_V_U.$not$matmul_partition_regslice_both.v:103$520
	p_regslice__both__Input__1__V__U_2e_B__V__data__1__load__A = and_uu<1>(not_u<1>(p_regslice__both__Input__1__V__U_2e_B__V__data__1__sel__wr.curr), p_regslice__both__Input__1__V__U_2e_B__V__data__1__state__cmp__full);
	// connection
	p_zext__ln674__fu__235__p1 = value<58>{0u,0u}.concat(p_trunc__ln674__fu__231__p1).val();
	// connection
	p_zext__ln414__fu__199__p1 = value<58>{0u,0u}.concat(p_trunc__ln414__reg__352.curr).val();
	// connection
	p_trunc__ln674__1__fu__335__p1 = p_p__Val2__s__fu__257__p3.slice<31,0>().val();
	// connection
	p_trunc__ln414__fu__179__p1 = p_i__reg__145.curr.slice<5,0>().val();
	// cells $ternary$matmul_partition.v:643$459 $eq$matmul_partition.v:643$458
	p_icmp__ln674__fu__251__p2 = (logic_not<1>(p_tmp__1__fu__241__p4) ? value<1>{0x1u} : value<1>{0u});
	// cells $ternary$matmul_partition.v:637$453 $eq$matmul_partition.v:637$452
	p_icmp__ln414__fu__193__p2 = (logic_not<1>(p_tmp__fu__183__p4) ? value<1>{0x1u} : value<1>{0u});
	// connection
	p_ap__CS__fsm__state9 = p_ap__CS__fsm.curr.slice<8>().val();
	// connection
	p_ap__CS__fsm__state8 = p_ap__CS__fsm.curr.slice<7>().val();
	// connection
	p_ap__CS__fsm__state7 = p_ap__CS__fsm.curr.slice<6>().val();
	// connection
	p_ap__CS__fsm__state6 = p_ap__CS__fsm.curr.slice<5>().val();
	// connection
	p_ap__CS__fsm__state5 = p_ap__CS__fsm.curr.slice<4>().val();
	// connection
	p_ap__CS__fsm__state4 = p_ap__CS__fsm.curr.slice<3>().val();
	// connection
	p_ap__CS__fsm__state3 = p_ap__CS__fsm.curr.slice<2>().val();
	// connection
	p_ap__CS__fsm__state2 = p_ap__CS__fsm.curr.slice<1>().val();
	// connection
	p_ap__CS__fsm__state19 = p_ap__CS__fsm.curr.slice<18>().val();
	// connection
	p_ap__CS__fsm__state18 = p_ap__CS__fsm.curr.slice<17>().val();
	// connection
	p_ap__CS__fsm__state17 = p_ap__CS__fsm.curr.slice<16>().val();
	// connection
	p_ap__CS__fsm__state16 = p_ap__CS__fsm.curr.slice<15>().val();
	// connection
	p_ap__CS__fsm__state15 = p_ap__CS__fsm.curr.slice<14>().val();
	// connection
	p_ap__CS__fsm__state14 = p_ap__CS__fsm.curr.slice<13>().val();
	// connection
	p_ap__CS__fsm__state13 = p_ap__CS__fsm.curr.slice<12>().val();
	// connection
	p_ap__CS__fsm__state12 = p_ap__CS__fsm.curr.slice<11>().val();
	// connection
	p_ap__CS__fsm__state11 = p_ap__CS__fsm.curr.slice<10>().val();
	// connection
	p_ap__CS__fsm__state10 = p_ap__CS__fsm.curr.slice<9>().val();
	// connection
	p_ap__CS__fsm__state1 = p_ap__CS__fsm.curr.slice<0>().val();
	// \src: matmul_partition.v:589.30-589.48
	// cell $add$matmul_partition.v:589$445
	p_add__ln64__fu__219__p2 = add_uu<8>(p_i__1__reg__156.curr, value<8>{0x1u});
	// \src: matmul_partition.v:587.30-587.46
	// cell $add$matmul_partition.v:587$444
	p_add__ln50__fu__167__p2 = add_uu<8>(p_i__reg__145.curr, value<8>{0x1u});
}

CXXRTL_EXTREMELY_COLD
void p_matmul__partition::debug_info(debug_items &items, std::string path) {
	assert(path.empty() || path[path.size() - 1] == ' ');
	items.add(path + "regslice_both_Output_1_V_U ap_clk", debug_item(debug_alias(), p_ap__clk, 0));
	items.add(path + "regslice_both_Output_1_V_U ap_rst", debug_item(debug_eval_outline, p_ap__rst__n__inv, 0));
	items.add(path + "regslice_both_Output_1_V_U data_in", debug_item(debug_eval_outline, p_Output__1__V__TDATA__int__regslice, 0));
	items.add(path + "regslice_both_Output_1_V_U vld_in", debug_item(debug_eval_outline, p_Output__1__V__TVALID__int__regslice, 0));
	items.add(path + "regslice_both_Output_1_V_U ack_in", debug_item(debug_eval_outline, p_regslice__both__Output__1__V__U_2e_B__V__data__1__ack__in, 0));
	items.add(path + "regslice_both_Output_1_V_U data_out", debug_item(debug_eval_outline, p_regslice__both__Output__1__V__U_2e_B__V__data__1__data__out, 0));
	items.add(path + "regslice_both_Output_1_V_U vld_out", debug_item(debug_eval_outline, p_regslice__both__Output__1__V__U_2e_B__V__data__1__vld__out, 0));
	items.add(path + "regslice_both_Output_1_V_U ack_out", debug_item(debug_alias(), p_Output__1__V__TREADY, 0));
	items.add(path + "regslice_both_Output_1_V_U apdone_blk", debug_item(debug_eval_outline, p_regslice__both__Output__1__V__U_2e_apdone__blk, 0));
	items.add(path + "regslice_both_Output_1_V_U B_V_data_1_state", debug_item(p_regslice__both__Output__1__V__U_2e_B__V__data__1__state, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "regslice_both_Output_1_V_U B_V_data_1_data_in", debug_item(debug_eval_outline, p_Output__1__V__TDATA__int__regslice, 0));
	items.add(path + "regslice_both_Output_1_V_U B_V_data_1_data_out", debug_item(debug_eval_outline, p_regslice__both__Output__1__V__U_2e_B__V__data__1__data__out, 0));
	items.add(path + "regslice_both_Output_1_V_U B_V_data_1_vld_reg", debug_item(debug_eval_outline, p_regslice__both__Output__1__V__U_2e_B__V__data__1__vld__reg, 0));
	items.add(path + "regslice_both_Output_1_V_U B_V_data_1_vld_in", debug_item(debug_eval_outline, p_Output__1__V__TVALID__int__regslice, 0));
	items.add(path + "regslice_both_Output_1_V_U B_V_data_1_vld_out", debug_item(debug_eval_outline, p_regslice__both__Output__1__V__U_2e_B__V__data__1__vld__out, 0));
	items.add(path + "regslice_both_Output_1_V_U B_V_data_1_payload_A", debug_item(p_regslice__both__Output__1__V__U_2e_B__V__data__1__payload__A, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "regslice_both_Output_1_V_U B_V_data_1_payload_B", debug_item(p_regslice__both__Output__1__V__U_2e_B__V__data__1__payload__B, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "regslice_both_Output_1_V_U B_V_data_1_sel_rd", debug_item(p_regslice__both__Output__1__V__U_2e_B__V__data__1__sel__rd, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "regslice_both_Output_1_V_U B_V_data_1_sel_wr", debug_item(p_regslice__both__Output__1__V__U_2e_B__V__data__1__sel__wr, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "regslice_both_Output_1_V_U B_V_data_1_sel", debug_item(debug_alias(), p_regslice__both__Output__1__V__U_2e_B__V__data__1__sel__rd, 0));
	items.add(path + "regslice_both_Output_1_V_U B_V_data_1_load_A", debug_item(debug_eval_outline, p_regslice__both__Output__1__V__U_2e_B__V__data__1__load__A, 0));
	items.add(path + "regslice_both_Output_1_V_U B_V_data_1_load_B", debug_item(debug_eval_outline, p_regslice__both__Output__1__V__U_2e_B__V__data__1__load__B, 0));
	items.add(path + "regslice_both_Output_1_V_U B_V_data_1_state_cmp_full", debug_item(debug_eval_outline, p_regslice__both__Output__1__V__U_2e_B__V__data__1__state__cmp__full, 0));
	items.add(path + "regslice_both_Output_1_V_U B_V_data_1_ack_in", debug_item(debug_eval_outline, p_regslice__both__Output__1__V__U_2e_B__V__data__1__ack__in, 0));
	items.add(path + "regslice_both_Output_1_V_U B_V_data_1_ack_out", debug_item(debug_alias(), p_Output__1__V__TREADY, 0));
	items.add(path + "regslice_both_Input_1_V_U ap_clk", debug_item(debug_alias(), p_ap__clk, 0));
	items.add(path + "regslice_both_Input_1_V_U ap_rst", debug_item(debug_eval_outline, p_ap__rst__n__inv, 0));
	items.add(path + "regslice_both_Input_1_V_U data_in", debug_item(debug_alias(), p_Input__1__V__TDATA, 0));
	items.add(path + "regslice_both_Input_1_V_U vld_in", debug_item(debug_alias(), p_Input__1__V__TVALID, 0));
	items.add(path + "regslice_both_Input_1_V_U ack_in", debug_item(debug_eval_outline, p_regslice__both__Input__1__V__U_2e_B__V__data__1__ack__in, 0));
	items.add(path + "regslice_both_Input_1_V_U data_out", debug_item(debug_eval_outline, p_regslice__both__Input__1__V__U_2e_B__V__data__1__data__out, 0));
	items.add(path + "regslice_both_Input_1_V_U vld_out", debug_item(debug_eval_outline, p_regslice__both__Input__1__V__U_2e_B__V__data__1__vld__out, 0));
	items.add(path + "regslice_both_Input_1_V_U ack_out", debug_item(debug_eval_outline, p_Input__1__V__TREADY__int__regslice, 0));
	items.add(path + "regslice_both_Input_1_V_U apdone_blk", debug_item(debug_eval_outline, p_regslice__both__Input__1__V__U_2e_apdone__blk, 0));
	items.add(path + "regslice_both_Input_1_V_U B_V_data_1_state", debug_item(p_regslice__both__Input__1__V__U_2e_B__V__data__1__state, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "regslice_both_Input_1_V_U B_V_data_1_data_in", debug_item(debug_alias(), p_Input__1__V__TDATA, 0));
	items.add(path + "regslice_both_Input_1_V_U B_V_data_1_data_out", debug_item(debug_eval_outline, p_regslice__both__Input__1__V__U_2e_B__V__data__1__data__out, 0));
	items.add(path + "regslice_both_Input_1_V_U B_V_data_1_vld_reg", debug_item(debug_eval_outline, p_regslice__both__Input__1__V__U_2e_B__V__data__1__vld__reg, 0));
	items.add(path + "regslice_both_Input_1_V_U B_V_data_1_vld_in", debug_item(debug_alias(), p_Input__1__V__TVALID, 0));
	items.add(path + "regslice_both_Input_1_V_U B_V_data_1_vld_out", debug_item(debug_eval_outline, p_regslice__both__Input__1__V__U_2e_B__V__data__1__vld__out, 0));
	items.add(path + "regslice_both_Input_1_V_U B_V_data_1_payload_A", debug_item(p_regslice__both__Input__1__V__U_2e_B__V__data__1__payload__A, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "regslice_both_Input_1_V_U B_V_data_1_payload_B", debug_item(p_regslice__both__Input__1__V__U_2e_B__V__data__1__payload__B, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "regslice_both_Input_1_V_U B_V_data_1_sel_rd", debug_item(p_regslice__both__Input__1__V__U_2e_B__V__data__1__sel__rd, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "regslice_both_Input_1_V_U B_V_data_1_sel_wr", debug_item(p_regslice__both__Input__1__V__U_2e_B__V__data__1__sel__wr, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "regslice_both_Input_1_V_U B_V_data_1_sel", debug_item(debug_alias(), p_regslice__both__Input__1__V__U_2e_B__V__data__1__sel__rd, 0));
	items.add(path + "regslice_both_Input_1_V_U B_V_data_1_load_A", debug_item(debug_eval_outline, p_regslice__both__Input__1__V__U_2e_B__V__data__1__load__A, 0));
	items.add(path + "regslice_both_Input_1_V_U B_V_data_1_load_B", debug_item(debug_eval_outline, p_regslice__both__Input__1__V__U_2e_B__V__data__1__load__B, 0));
	items.add(path + "regslice_both_Input_1_V_U B_V_data_1_state_cmp_full", debug_item(debug_eval_outline, p_regslice__both__Input__1__V__U_2e_B__V__data__1__state__cmp__full, 0));
	items.add(path + "regslice_both_Input_1_V_U B_V_data_1_ack_in", debug_item(debug_eval_outline, p_regslice__both__Input__1__V__U_2e_B__V__data__1__ack__in, 0));
	items.add(path + "regslice_both_Input_1_V_U B_V_data_1_ack_out", debug_item(debug_eval_outline, p_Input__1__V__TREADY__int__regslice, 0));
	items.add(path + "A_V_1_U reset", debug_item(debug_eval_outline, p_ap__rst__n__inv, 0));
	items.add(path + "A_V_1_U clk", debug_item(debug_alias(), p_ap__clk, 0));
	items.add(path + "A_V_1_U address0", debug_item(debug_eval_outline, p_A__V__1__address0, 0));
	items.add(path + "A_V_1_U ce0", debug_item(debug_eval_outline, p_A__V__1__ce0, 0));
	items.add(path + "A_V_1_U we0", debug_item(debug_eval_outline, p_A__V__1__we0, 0));
	items.add(path + "A_V_1_U d0", debug_item(debug_eval_outline, p_p__Result__s__fu__204__p9, 0));
	items.add(path + "A_V_1_U q0", debug_item(debug_alias(), p_A__V__1__U_2e_matmul__partition__A__V__0__ram__U_2e_q0, 0));
	items.add(path + "A_V_1_U matmul_partition_A_V_0_ram_U clk", debug_item(debug_alias(), p_ap__clk, 0));
	items.add(path + "A_V_1_U matmul_partition_A_V_0_ram_U q0", debug_item(p_A__V__1__U_2e_matmul__partition__A__V__0__ram__U_2e_q0, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "A_V_1_U matmul_partition_A_V_0_ram_U we0", debug_item(debug_eval_outline, p_A__V__1__we0, 0));
	items.add(path + "A_V_1_U matmul_partition_A_V_0_ram_U d0", debug_item(debug_eval_outline, p_p__Result__s__fu__204__p9, 0));
	items.add(path + "A_V_1_U matmul_partition_A_V_0_ram_U ce0", debug_item(debug_eval_outline, p_A__V__1__ce0, 0));
	items.add(path + "A_V_1_U matmul_partition_A_V_0_ram_U addr0", debug_item(debug_eval_outline, p_A__V__1__address0, 0));
	items.add(path + "A_V_0_U reset", debug_item(debug_eval_outline, p_ap__rst__n__inv, 0));
	items.add(path + "A_V_0_U clk", debug_item(debug_alias(), p_ap__clk, 0));
	items.add(path + "A_V_0_U address0", debug_item(debug_eval_outline, p_A__V__0__address0, 0));
	items.add(path + "A_V_0_U ce0", debug_item(debug_eval_outline, p_A__V__0__ce0, 0));
	items.add(path + "A_V_0_U we0", debug_item(debug_eval_outline, p_A__V__0__we0, 0));
	items.add(path + "A_V_0_U d0", debug_item(debug_eval_outline, p_p__Result__s__fu__204__p9, 0));
	items.add(path + "A_V_0_U q0", debug_item(debug_alias(), p_A__V__0__U_2e_matmul__partition__A__V__0__ram__U_2e_q0, 0));
	items.add(path + "A_V_0_U matmul_partition_A_V_0_ram_U clk", debug_item(debug_alias(), p_ap__clk, 0));
	items.add(path + "A_V_0_U matmul_partition_A_V_0_ram_U q0", debug_item(p_A__V__0__U_2e_matmul__partition__A__V__0__ram__U_2e_q0, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "A_V_0_U matmul_partition_A_V_0_ram_U we0", debug_item(debug_eval_outline, p_A__V__0__we0, 0));
	items.add(path + "A_V_0_U matmul_partition_A_V_0_ram_U d0", debug_item(debug_eval_outline, p_p__Result__s__fu__204__p9, 0));
	items.add(path + "A_V_0_U matmul_partition_A_V_0_ram_U ce0", debug_item(debug_eval_outline, p_A__V__0__ce0, 0));
	items.add(path + "A_V_0_U matmul_partition_A_V_0_ram_U addr0", debug_item(debug_eval_outline, p_A__V__0__address0, 0));
	items.add(path + "ap_ce_reg", debug_item(debug_eval_outline, p_ap__ce__reg, 0));
	items.add(path + "regslice_both_Output_1_V_U_vld_out", debug_item(debug_eval_outline, p_regslice__both__Output__1__V__U_2e_B__V__data__1__vld__out, 0));
	items.add(path + "Output_1_V_TREADY_int_regslice", debug_item(debug_eval_outline, p_regslice__both__Output__1__V__U_2e_B__V__data__1__ack__in, 0));
	items.add(path + "Output_1_V_TVALID_int_regslice", debug_item(debug_eval_outline, p_Output__1__V__TVALID__int__regslice, 0));
	items.add(path + "Output_1_V_TDATA_int_regslice", debug_item(debug_eval_outline, p_Output__1__V__TDATA__int__regslice, 0));
	items.add(path + "regslice_both_Input_1_V_U_ack_in", debug_item(debug_eval_outline, p_regslice__both__Input__1__V__U_2e_B__V__data__1__ack__in, 0));
	items.add(path + "Input_1_V_TREADY_int_regslice", debug_item(debug_eval_outline, p_Input__1__V__TREADY__int__regslice, 0));
	items.add(path + "Input_1_V_TVALID_int_regslice", debug_item(debug_eval_outline, p_regslice__both__Input__1__V__U_2e_B__V__data__1__vld__out, 0));
	items.add(path + "Input_1_V_TDATA_int_regslice", debug_item(debug_eval_outline, p_regslice__both__Input__1__V__U_2e_B__V__data__1__data__out, 0));
	items.add(path + "regslice_both_Input_1_V_U_apdone_blk", debug_item(debug_eval_outline, p_regslice__both__Input__1__V__U_2e_apdone__blk, 0));
	items.add(path + "ap_NS_fsm", debug_item(debug_eval_outline, p_ap__NS__fsm, 0));
	items.add(path + "p_Val2_s_fu_257_p3", debug_item(debug_eval_outline, p_p__Val2__s__fu__257__p3, 0));
	items.add(path + "tmp_1_fu_241_p4", debug_item(debug_eval_outline, p_tmp__1__fu__241__p4, 0));
	items.add(path + "trunc_ln674_fu_231_p1", debug_item(debug_eval_outline, p_trunc__ln674__fu__231__p1, 0));
	items.add(path + "tmp_fu_183_p4", debug_item(debug_eval_outline, p_tmp__fu__183__p4, 0));
	items.add(path + "p_Result_s_fu_204_p9", debug_item(debug_eval_outline, p_p__Result__s__fu__204__p9, 0));
	items.add(path + "zext_ln674_fu_235_p1", debug_item(debug_eval_outline, p_zext__ln674__fu__235__p1, 0));
	items.add(path + "zext_ln414_fu_199_p1", debug_item(debug_eval_outline, p_zext__ln414__fu__199__p1, 0));
	items.add(path + "i_1_reg_156", debug_item(p_i__1__reg__156, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "i_reg_145", debug_item(p_i__reg__145, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "A_V_1_q0", debug_item(debug_alias(), p_A__V__1__U_2e_matmul__partition__A__V__0__ram__U_2e_q0, 0));
	items.add(path + "A_V_1_we0", debug_item(debug_eval_outline, p_A__V__1__we0, 0));
	items.add(path + "A_V_1_ce0", debug_item(debug_eval_outline, p_A__V__1__ce0, 0));
	items.add(path + "A_V_1_address0", debug_item(debug_eval_outline, p_A__V__1__address0, 0));
	items.add(path + "A_V_0_q0", debug_item(debug_alias(), p_A__V__0__U_2e_matmul__partition__A__V__0__ram__U_2e_q0, 0));
	items.add(path + "A_V_0_we0", debug_item(debug_eval_outline, p_A__V__0__we0, 0));
	items.add(path + "A_V_0_ce0", debug_item(debug_eval_outline, p_A__V__0__ce0, 0));
	items.add(path + "A_V_0_address0", debug_item(debug_eval_outline, p_A__V__0__address0, 0));
	items.add(path + "trunc_ln674_1_reg_449", debug_item(p_trunc__ln674__1__reg__449, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "trunc_ln674_1_fu_335_p1", debug_item(debug_eval_outline, p_trunc__ln674__1__fu__335__p1, 0));
	items.add(path + "p_Result_6_reg_444", debug_item(p_p__Result__6__reg__444, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "p_Result_5_reg_439", debug_item(p_p__Result__5__reg__439, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "p_Result_4_reg_434", debug_item(p_p__Result__4__reg__434, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "p_Result_3_reg_429", debug_item(p_p__Result__3__reg__429, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "p_Result_2_reg_424", debug_item(p_p__Result__2__reg__424, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "p_Result_1_reg_419", debug_item(p_p__Result__1__reg__419, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "icmp_ln674_reg_409", debug_item(p_icmp__ln674__reg__409, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "icmp_ln674_fu_251_p2", debug_item(debug_eval_outline, p_icmp__ln674__fu__251__p2, 0));
	items.add(path + "icmp_ln64_fu_225_p2", debug_item(debug_eval_outline, p_icmp__ln64__fu__225__p2, 0));
	items.add(path + "regslice_both_Output_1_V_U_apdone_blk", debug_item(debug_eval_outline, p_regslice__both__Output__1__V__U_2e_apdone__blk, 0));
	items.add(path + "ap_CS_fsm_state10", debug_item(debug_eval_outline, p_ap__CS__fsm__state10, 0));
	items.add(path + "add_ln64_reg_391", debug_item(p_add__ln64__reg__391, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "add_ln64_fu_219_p2", debug_item(debug_eval_outline, p_add__ln64__fu__219__p2, 0));
	items.add(path + "tmp_V_6_reg_386", debug_item(p_tmp__V__6__reg__386, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "tmp_V_5_reg_381", debug_item(p_tmp__V__5__reg__381, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "tmp_V_4_reg_376", debug_item(p_tmp__V__4__reg__376, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "tmp_V_3_reg_371", debug_item(p_tmp__V__3__reg__371, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "tmp_V_2_reg_366", debug_item(p_tmp__V__2__reg__366, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "tmp_V_1_reg_361", debug_item(p_tmp__V__1__reg__361, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "icmp_ln414_reg_357", debug_item(p_icmp__ln414__reg__357, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "icmp_ln414_fu_193_p2", debug_item(debug_eval_outline, p_icmp__ln414__fu__193__p2, 0));
	items.add(path + "trunc_ln414_reg_352", debug_item(p_trunc__ln414__reg__352, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "trunc_ln414_fu_179_p1", debug_item(debug_eval_outline, p_trunc__ln414__fu__179__p1, 0));
	items.add(path + "tmp_V_reg_347", debug_item(p_tmp__V__reg__347, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "ap_block_state2", debug_item(debug_eval_outline, p_ap__block__state2, 0));
	items.add(path + "add_ln50_reg_339", debug_item(p_add__ln50__reg__339, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "add_ln50_fu_167_p2", debug_item(debug_eval_outline, p_add__ln50__fu__167__p2, 0));
	items.add(path + "ap_CS_fsm_state19", debug_item(debug_eval_outline, p_ap__CS__fsm__state19, 0));
	items.add(path + "ap_CS_fsm_state18", debug_item(debug_eval_outline, p_ap__CS__fsm__state18, 0));
	items.add(path + "ap_CS_fsm_state17", debug_item(debug_eval_outline, p_ap__CS__fsm__state17, 0));
	items.add(path + "ap_CS_fsm_state16", debug_item(debug_eval_outline, p_ap__CS__fsm__state16, 0));
	items.add(path + "ap_CS_fsm_state15", debug_item(debug_eval_outline, p_ap__CS__fsm__state15, 0));
	items.add(path + "ap_CS_fsm_state14", debug_item(debug_eval_outline, p_ap__CS__fsm__state14, 0));
	items.add(path + "ap_CS_fsm_state13", debug_item(debug_eval_outline, p_ap__CS__fsm__state13, 0));
	items.add(path + "ap_CS_fsm_state12", debug_item(debug_eval_outline, p_ap__CS__fsm__state12, 0));
	items.add(path + "ap_CS_fsm_state11", debug_item(debug_eval_outline, p_ap__CS__fsm__state11, 0));
	items.add(path + "Output_1_V_TDATA_blk_n", debug_item(debug_eval_outline, p_Output__1__V__TDATA__blk__n, 0));
	items.add(path + "ap_CS_fsm_state9", debug_item(debug_eval_outline, p_ap__CS__fsm__state9, 0));
	items.add(path + "ap_CS_fsm_state8", debug_item(debug_eval_outline, p_ap__CS__fsm__state8, 0));
	items.add(path + "ap_CS_fsm_state7", debug_item(debug_eval_outline, p_ap__CS__fsm__state7, 0));
	items.add(path + "ap_CS_fsm_state6", debug_item(debug_eval_outline, p_ap__CS__fsm__state6, 0));
	items.add(path + "ap_CS_fsm_state5", debug_item(debug_eval_outline, p_ap__CS__fsm__state5, 0));
	items.add(path + "ap_CS_fsm_state4", debug_item(debug_eval_outline, p_ap__CS__fsm__state4, 0));
	items.add(path + "ap_CS_fsm_state3", debug_item(debug_eval_outline, p_ap__CS__fsm__state3, 0));
	items.add(path + "icmp_ln50_fu_173_p2", debug_item(debug_eval_outline, p_icmp__ln50__fu__173__p2, 0));
	items.add(path + "ap_CS_fsm_state2", debug_item(debug_eval_outline, p_ap__CS__fsm__state2, 0));
	items.add(path + "Input_1_V_TDATA_blk_n", debug_item(debug_eval_outline, p_Input__1__V__TDATA__blk__n, 0));
	items.add(path + "ap_CS_fsm_state1", debug_item(debug_eval_outline, p_ap__CS__fsm__state1, 0));
	items.add(path + "ap_CS_fsm", debug_item(p_ap__CS__fsm, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "ap_rst_n_inv", debug_item(debug_eval_outline, p_ap__rst__n__inv, 0));
	items.add(path + "Output_1_V_TREADY", debug_item(p_Output__1__V__TREADY, 0, debug_item::INPUT|debug_item::UNDRIVEN));
	items.add(path + "Output_1_V_TVALID", debug_item(debug_eval_outline, p_regslice__both__Output__1__V__U_2e_B__V__data__1__vld__out, 0));
	items.add(path + "Output_1_V_TDATA", debug_item(debug_eval_outline, p_regslice__both__Output__1__V__U_2e_B__V__data__1__data__out, 0));
	items.add(path + "Input_1_V_TREADY", debug_item(debug_eval_outline, p_regslice__both__Input__1__V__U_2e_B__V__data__1__ack__in, 0));
	items.add(path + "Input_1_V_TVALID", debug_item(p_Input__1__V__TVALID, 0, debug_item::INPUT|debug_item::UNDRIVEN));
	items.add(path + "Input_1_V_TDATA", debug_item(p_Input__1__V__TDATA, 0, debug_item::INPUT|debug_item::UNDRIVEN));
	items.add(path + "ap_ready", debug_item(p_ap__ready, 0, debug_item::OUTPUT|debug_item::DRIVEN_COMB));
	items.add(path + "ap_idle", debug_item(p_ap__idle, 0, debug_item::OUTPUT|debug_item::DRIVEN_COMB));
	items.add(path + "ap_done", debug_item(p_ap__done, 0, debug_item::OUTPUT|debug_item::DRIVEN_COMB));
	items.add(path + "ap_start", debug_item(p_ap__start, 0, debug_item::INPUT|debug_item::UNDRIVEN));
	items.add(path + "ap_rst_n", debug_item(p_ap__rst__n, 0, debug_item::INPUT|debug_item::UNDRIVEN));
	items.add(path + "ap_clk", debug_item(p_ap__clk, 0, debug_item::INPUT|debug_item::UNDRIVEN));
	items.add(path + "A_V_1_U matmul_partition_A_V_0_ram_U ram", debug_item(memory_p_A__V__1__U_2e_matmul__partition__A__V__0__ram__U_2e_ram, 0));
	items.add(path + "A_V_0_U matmul_partition_A_V_0_ram_U ram", debug_item(memory_p_A__V__0__U_2e_matmul__partition__A__V__0__ram__U_2e_ram, 0));
}

} // namespace cxxrtl_design

extern "C"
cxxrtl_toplevel cxxrtl_design_create() {
	return new _cxxrtl_toplevel { std::unique_ptr<cxxrtl_design::p_matmul__partition>(new cxxrtl_design::p_matmul__partition) };
}
