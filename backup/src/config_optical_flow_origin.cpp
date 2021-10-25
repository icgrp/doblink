#include "xaxidma.h"
#include "xparameters.h"
#include "xdebug.h"

#include "sleep.h"
#include "config_optical_flow_origin.h"
//#include "config.h"

//width of a packet is 49 bits
//bft2arm_packet = {1'b1, SLV_REG1[15:0], SLV_REG0[31:0]}
//arm2bft_packet = {SLV_REG5[16:0], SLV_REG4[31:0]}
//input fifo empty = SLV_REG3[1]
//output fifo full = SLV_REG3[0]
//input fifo rd_en = SLV_REG7[1]
#define BFT_ADDR_SHIFT 11

config::config(unsigned int ADDR_BASE, unsigned int CTRL_REG){
	ctrl_reg = CTRL_REG;
	reg0 = ADDR_BASE;
	reg1 = ADDR_BASE + 4;
	reg2 = ADDR_BASE + 8;
	reg3 = ADDR_BASE + 12;
	reg4 = ADDR_BASE + 16;
	reg5 = ADDR_BASE + 20;
	reg6 = ADDR_BASE + 24;
	reg7 = ADDR_BASE + 28;
}

void config::read_from_fifo()
{
   unsigned int rev_0, rev_1;

    //check if the input fifo is empty
    while((Xil_In32(reg3)>>1)&&1);

    //toggle the rd_en bits to start one reading
    ctrl_reg = ctrl_reg ^ 0x00000002;
    //input fifo rd_en = SLV_REG7[1]
    Xil_Out32(reg7, ctrl_reg);

    //bft2arm_packet = {1'b1, SLV_REG1[15:0], SLV_REG0[31:0]}
    rev_0 = Xil_In32(reg0);
    rev_1 = Xil_In32(reg1);

   xil_printf( "= %d \n", rev_0);

}


void config::write_to_fifo(int high_32_bits, int low_32_bits)
{
    //arm2bft_packet = {SLV_REG5[16:0], SLV_REG4[31:0]}
    Xil_Out32(reg5, high_32_bits);
    Xil_Out32(reg4, low_32_bits);
    ctrl_reg = ctrl_reg ^ 0x00000001;
    Xil_Out32(reg7, ctrl_reg);
}


void config::init_regs()
{
	int i = 0;
	for (i=4; i<8; i++) {Xil_Out32(reg0+i*4, 0x00000000);}
//gradient_xy_calc.Output_1->gradient_weight_y.Input_1
  write_to_fifo(0xe000, 0x99900fe0);
  write_to_fifo(0x9880, 0x2e480000);
//gradient_weight_x.Output_1->outer_product.Input_1
  write_to_fifo(0xf000, 0x9d100fe0);
  write_to_fifo(0xd080, 0x2f480000);
//tensor_weight_x.Output_1->flow_calc.Input_1
  write_to_fifo(0x2000, 0x9c100fe0);
  write_to_fifo(0xc080, 0x22480000);
//unpack.Output_2->gradient_xy_calc.Input_1
  write_to_fifo(0x1800, 0xae100fe0);
  write_to_fifo(0xe080, 0x21d00000);
//DMA.Output_1->unpack.Input_1
  write_to_fifo(0x800, 0x91900fe0);
  write_to_fifo(0x1880, 0x20c80000);
//flow_calc.Output_1->DMA.Input_1
  write_to_fifo(0xc000, 0x90900fe0);
  write_to_fifo(0x880, 0x2c480000);
//gradient_z_calc.Output_1->gradient_weight_y.Input_3
  write_to_fifo(0xa000, 0x99a00fe0);
  write_to_fifo(0x9880, 0x4a480000);
//gradient_weight_y.Output_1->gradient_weight_x.Input_1
  write_to_fifo(0x9800, 0x9f100fe0);
  write_to_fifo(0xf080, 0x29c80000);
//outer_product.Output_1->tensor_weight_y.Input_1
  write_to_fifo(0xd000, 0x94100fe0);
  write_to_fifo(0x4080, 0x2d480000);
//tensor_weight_y.Output_1->tensor_weight_x.Input_1
  write_to_fifo(0x4000, 0x92100fe0);
  write_to_fifo(0x2080, 0x24480000);
//gradient_xy_calc.Output_2->gradient_weight_y.Input_2
  write_to_fifo(0xe000, 0xa9980fe0);
  write_to_fifo(0x9880, 0x3e500000);
//unpack.Output_1->gradient_z_calc.Input_1
  write_to_fifo(0x1800, 0x9a100fe0);
  write_to_fifo(0xa080, 0x21c80000);
	//packet anchor
        sleep(1);
}

void config::ap_start()
{

    Xil_Out32(reg6, 1);
    sleep(1);
}

void config::instr_config(unsigned int bft_addr, const unsigned int *instr_data, unsigned int len)
{
	unsigned int rev_0, rev_1;
	unsigned int i;

	rev_1 = (bft_addr << BFT_ADDR_SHIFT) | 0x00000001;
	for(i=0; i<len; i++){
		//if(i%1000==0) { xil_printf("i = %d\n", i); }
		rev_0 = ((i*4) << 8) + ((instr_data[i]>>0)  & 0x000000ff);
		//xil_printf( "send %08x_%08x\n", rev_1, rev_0);
		write_to_fifo(rev_1, rev_0);
		rev_0 = ((i*4+1) << 8) + ((instr_data[i]>>8)  & 0x000000ff);
		//xil_printf( "send %08x_%08x\n", rev_1, rev_0);
		write_to_fifo(rev_1, rev_0);
		rev_0 = ((i*4+2) << 8) + ((instr_data[i]>>16) & 0x000000ff);
		//xil_printf( "send %08x_%08x\n", rev_1, rev_0);
		write_to_fifo(rev_1, rev_0);
		rev_0 = ((i*4+3) << 8) + ((instr_data[i]>>24) & 0x000000ff);
		//xil_printf( "send %08x_%08x\n", rev_1, rev_0);
		write_to_fifo(rev_1, rev_0);
    }
	xil_printf("RISCV %d Configuration Done\n", bft_addr);
}

void config::app()
{
	int i;

	// download firmware to riscv
/*
	for(i=0; i<60; i++){
		xil_printf("%d op ", i);
		write_to_fifo(0x4900+i, i);
		xil_printf("%d ", i+1);
		write_to_fifo(0x4980+i, i+1);
		read_from_fifo();
	}
*/
}
