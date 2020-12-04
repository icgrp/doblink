void gradient_xyz_calc(//input_t frame[MAX_HEIGHT][MAX_WIDTH],
    hls::stream< ap_uint<32> > &Input_1,
    hls::stream<databus_t> &Output_1,
    hls::stream<databus_t> &Output_2,
    hls::stream<databus_t> &Output_3);
#pragma map_target=HW page_num=8
