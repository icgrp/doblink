#include "axi_lite_driver.h"
#include <generated/mem.h>
#include "config_spam_filter_small.h"

//width of a packet is 49 bits
//bft2arm_packet = {1'b1, SLV_REG1[15:0], SLV_REG0[31:0]}
//arm2bft_packet = {SLV_REG5[16:0], SLV_REG4[31:0]}
//input fifo empty = SLV_REG3[1]
//output fifo full = SLV_REG3[0]
//input fifo rd_en = SLV_REG7[1]
#define SLV_REG0 AXILITE2BFT_BASE+0
#define SLV_REG1 AXILITE2BFT_BASE+4
#define SLV_REG2 AXILITE2BFT_BASE+8
#define SLV_REG3 AXILITE2BFT_BASE+12
#define SLV_REG4 AXILITE2BFT_BASE+16
#define SLV_REG5 AXILITE2BFT_BASE+20
#define SLV_REG6 AXILITE2BFT_BASE+24
#define SLV_REG7 AXILITE2BFT_BASE+28


#define WRITE_OP 0
#define READ_OP 1
#define CHECK_ACK 2
void read_from_fifo(int * ctrl_reg)
{
  //check if the input fifo is empty
  while((lx_read32(SLV_REG3)>>1)&&1);

  //toggle the rd_en bits to start one reading
  *ctrl_reg = (*ctrl_reg) ^ 0x00000002;
  //input fifo rd_en = SLV_REG7[1]
  lx_write32(SLV_REG7, *ctrl_reg);

  //bft2arm_packet = {1'b1, SLV_REG1[15:0], SLV_REG0[31:0]}
  // rev_0 = lx_read32(SLV_REG0);
  // rev_1 = lx_read32(SLV_REG1);

  //xil_printf( "The received data is %08x_%08d \n", rev_1, rev_0);

}


static void write_to_fifo(int high_32_bits, int low_32_bits, int * ctrl_reg)
{
    //arm2bft_packet = {SLV_REG5[16:0], SLV_REG4[31:0]}
    lx_write32(SLV_REG5, high_32_bits);
    lx_write32(SLV_REG4, low_32_bits);
    *ctrl_reg = (*ctrl_reg) ^ 0x00000001;
    lx_write32(SLV_REG7, *ctrl_reg);
}


void init_regs(void)
{
   int i = 0;
   static int ctrl_reg = 0;

   for (i=4; i<8; i++) {lx_write32(SLV_REG0+i*4, 0x00000000);}

//DMA.Output_1->data_in_redir.Input_1
  write_to_fifo(0x1000, 0x92201fc0, &ctrl_reg);
  write_to_fifo(0x2100, 0x21900000, &ctrl_reg);
//dotProduct_3.Output_1->data_1_4_4.Input_1
  write_to_fifo(0x7000, 0x9a201fc0, &ctrl_reg);
  write_to_fifo(0xa100, 0x27900000, &ctrl_reg);
//Sigmoid_axi.Output_1->data_1_4_3.Input_3
  write_to_fifo(0xb000, 0x99401fc0, &ctrl_reg);
  write_to_fifo(0x9100, 0x4b900000, &ctrl_reg);
//data_1_4_2.Output_2->dotProduct_4.Input_1
  write_to_fifo(0x4000, 0xa8201fc0, &ctrl_reg);
  write_to_fifo(0x8100, 0x24a00000, &ctrl_reg);
//dotProduct_1.Output_1->data_1_4_3.Input_1
  write_to_fifo(0x5000, 0x99201fc0, &ctrl_reg);
  write_to_fifo(0x9100, 0x25900000, &ctrl_reg);
//data_1_4_1.Output_1->dotProduct_1.Input_1
  write_to_fifo(0x3000, 0x95201fc0, &ctrl_reg);
  write_to_fifo(0x5100, 0x23900000, &ctrl_reg);
//data_1_4_1.Output_2->dotProduct_2.Input_1
  write_to_fifo(0x3000, 0xa6201fc0, &ctrl_reg);
  write_to_fifo(0x6100, 0x23a00000, &ctrl_reg);
//data_1_4_4.Output_3->dotProduct_4.Input_2
  write_to_fifo(0xa000, 0xb8301fc0, &ctrl_reg);
  write_to_fifo(0x8100, 0x3ab00000, &ctrl_reg);
//data_1_4_2.Output_3->data_2_1.Input_2
  write_to_fifo(0x4000, 0xbc301fc0, &ctrl_reg);
  write_to_fifo(0xc100, 0x34b00000, &ctrl_reg);
//data_1_4_2.Output_1->dotProduct_3.Input_1
  write_to_fifo(0x4000, 0x97201fc0, &ctrl_reg);
  write_to_fifo(0x7100, 0x24900000, &ctrl_reg);
//data_1_4_3.Output_2->dotProduct_1.Input_2
  write_to_fifo(0x9000, 0xa5301fc0, &ctrl_reg);
  write_to_fifo(0x5100, 0x39a00000, &ctrl_reg);
//data_in_redir.Output_1->data_1_4_1.Input_1
  write_to_fifo(0x2000, 0x93201fc0, &ctrl_reg);
  write_to_fifo(0x3100, 0x22900000, &ctrl_reg);
//data_1_4_3.Output_1->Sigmoid_axi.Input_1
  write_to_fifo(0x9000, 0x9b201fc0, &ctrl_reg);
  write_to_fifo(0xb100, 0x29900000, &ctrl_reg);
//data_in_redir.Output_2->data_1_4_2.Input_1
  write_to_fifo(0x2000, 0xa4201fc0, &ctrl_reg);
  write_to_fifo(0x4100, 0x22a00000, &ctrl_reg);
//dotProduct_4.Output_1->data_1_4_4.Input_2
  write_to_fifo(0x8000, 0x9a301fc0, &ctrl_reg);
  write_to_fifo(0xa100, 0x38900000, &ctrl_reg);
//dotProduct_2.Output_2->data_1_4_1.Input_3
  write_to_fifo(0x6000, 0xa3401fc0, &ctrl_reg);
  write_to_fifo(0x3100, 0x46a00000, &ctrl_reg);
//dotProduct_2.Output_1->data_1_4_3.Input_2
  write_to_fifo(0x6000, 0x99301fc0, &ctrl_reg);
  write_to_fifo(0x9100, 0x36900000, &ctrl_reg);
//dotProduct_1.Output_2->data_1_4_1.Input_2
  write_to_fifo(0x5000, 0xa3301fc0, &ctrl_reg);
  write_to_fifo(0x3100, 0x35a00000, &ctrl_reg);
//data_2_1.Output_1->DMA.Input_1
  write_to_fifo(0xc000, 0x91201fc0, &ctrl_reg);
  write_to_fifo(0x1100, 0x2c900000, &ctrl_reg);
//Sigmoid_axi.Output_2->data_1_4_4.Input_3
  write_to_fifo(0xb000, 0xaa401fc0, &ctrl_reg);
  write_to_fifo(0xa100, 0x4ba00000, &ctrl_reg);
//dotProduct_4.Output_2->data_1_4_2.Input_3
  write_to_fifo(0x8000, 0xa4401fc0, &ctrl_reg);
  write_to_fifo(0x4100, 0x48a00000, &ctrl_reg);
//data_1_4_4.Output_2->dotProduct_3.Input_2
  write_to_fifo(0xa000, 0xa7301fc0, &ctrl_reg);
  write_to_fifo(0x7100, 0x3aa00000, &ctrl_reg);
//data_1_4_4.Output_1->Sigmoid_axi.Input_2
  write_to_fifo(0xa000, 0x9b301fc0, &ctrl_reg);
  write_to_fifo(0xb100, 0x3a900000, &ctrl_reg);
//data_1_4_1.Output_3->data_2_1.Input_1
  write_to_fifo(0x3000, 0xbc201fc0, &ctrl_reg);
  write_to_fifo(0xc100, 0x23b00000, &ctrl_reg);
//dotProduct_3.Output_2->data_1_4_2.Input_2
  write_to_fifo(0x7000, 0xa4301fc0, &ctrl_reg);
  write_to_fifo(0x4100, 0x37a00000, &ctrl_reg);
//data_1_4_3.Output_3->dotProduct_2.Input_2
  write_to_fifo(0x9000, 0xb6301fc0, &ctrl_reg);
  write_to_fifo(0x6100, 0x39b00000, &ctrl_reg);
	//packet anchor

}
