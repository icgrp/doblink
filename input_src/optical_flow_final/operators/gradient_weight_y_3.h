
// average the gradient in y direction
void gradient_weight_y_3(
    hls::stream<databus_t> &Input_1,
    hls::stream<databus_t> &Output_1);
#pragma map_target=HW page_num=8 inst_mem_size = 65536
