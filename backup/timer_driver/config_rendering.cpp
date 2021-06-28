#include "xaxidma.h"
#include "xparameters.h"
#include "xdebug.h"


//width of a packet is 49 bits
//bft2arm_packet = {1'b1, SLV_REG1[15:0], SLV_REG0[31:0]}
//arm2bft_packet = {SLV_REG5[16:0], SLV_REG4[31:0]}
//input fifo empty = SLV_REG3[1]
//output fifo full = SLV_REG3[0]
//input fifo rd_en = SLV_REG7[1]
#define SLV_REG0 XPAR_AXI_LEAF_AXILITE2BFT_V2_0_0_BASEADDR+0
#define SLV_REG1 XPAR_AXI_LEAF_AXILITE2BFT_V2_0_0_BASEADDR+4
#define SLV_REG2 XPAR_AXI_LEAF_AXILITE2BFT_V2_0_0_BASEADDR+8
#define SLV_REG3 XPAR_AXI_LEAF_AXILITE2BFT_V2_0_0_BASEADDR+12
#define SLV_REG4 XPAR_AXI_LEAF_AXILITE2BFT_V2_0_0_BASEADDR+16
#define SLV_REG5 XPAR_AXI_LEAF_AXILITE2BFT_V2_0_0_BASEADDR+20
#define SLV_REG6 XPAR_AXI_LEAF_AXILITE2BFT_V2_0_0_BASEADDR+24
#define SLV_REG7 XPAR_AXI_LEAF_AXILITE2BFT_V2_0_0_BASEADDR+28


#define WRITE_OP 0
#define READ_OP 1
#define CHECK_ACK 2
void read_from_fifo(int * ctrl_reg)
{
   int rev_0, rev_1;

    //check if the input fifo is empty
    while((Xil_In32(SLV_REG3)>>1)&&1);

    //toggle the rd_en bits to start one reading
   *ctrl_reg = (*ctrl_reg) ^ 0x00000002;
    //input fifo rd_en = SLV_REG7[1]
    Xil_Out32(SLV_REG7, *ctrl_reg);

    //bft2arm_packet = {1'b1, SLV_REG1[15:0], SLV_REG0[31:0]}
    rev_0 = Xil_In32(SLV_REG0);
    rev_1 = Xil_In32(SLV_REG1);

   //xil_printf( "The received data is %08x_%08d \n", rev_1, rev_0);

}


void write_to_fifo(int high_32_bits, int low_32_bits, int * ctrl_reg)
{
    //arm2bft_packet = {SLV_REG5[16:0], SLV_REG4[31:0]}
    Xil_Out32(SLV_REG5, high_32_bits);
    Xil_Out32(SLV_REG4, low_32_bits);
    *ctrl_reg = (*ctrl_reg) ^ 0x00000001;
    Xil_Out32(SLV_REG7, *ctrl_reg);
}


void init_regs()
{
   int i = 0;
   static int ctrl_reg = 0;

  for (i=4; i<8; i++) {Xil_Out32(SLV_REG0+i*4, 0x00000000);}
  //write_to_fifo(0x800, 0x94100fe0, &ctrl_reg);
//rasterization2_m.Output_1->zculling_top.Input_1
  write_to_fifo(0x4800, 0x93100fe0, &ctrl_reg);
  write_to_fifo(0x3080, 0x24c80000, &ctrl_reg);
//zculling_bot.Output_1->coloringFB_bot_m.Input_1
  write_to_fifo(0x3800, 0x95100fe0, &ctrl_reg);
  write_to_fifo(0x5080, 0x23c80000, &ctrl_reg);
//data_redir_m.Output_1->rasterization2_m.Input_1
  write_to_fifo(0x2000, 0x94900fe0, &ctrl_reg);
  write_to_fifo(0x4880, 0x22480000, &ctrl_reg);
//coloringFB_bot_m.Output_1->coloringFB_top_m.Input_2
  write_to_fifo(0x5000, 0x92980fe0, &ctrl_reg);
  write_to_fifo(0x2880, 0x35480000, &ctrl_reg);
//rasterization2_m.Output_3->zculling_top.Input_2
  write_to_fifo(0x4800, 0xb3180fe0, &ctrl_reg);
  write_to_fifo(0x3080, 0x34d80000, &ctrl_reg);
//zculling_top.Output_2->DEBUG.Input_4
  write_to_fifo(0x3000, 0xa1280fe0, &ctrl_reg);
  write_to_fifo(0x1080, 0x53500000, &ctrl_reg);
//p2p.Output_1->data_redir_m.Input_1
  write_to_fifo(0x5800, 0x92100fe0, &ctrl_reg);
  write_to_fifo(0x2080, 0x25c80000, &ctrl_reg);
//coloringFB_top_m.Output_1->DMA.Input_1
  write_to_fifo(0x2800, 0x90900fe0, &ctrl_reg);
  write_to_fifo(0x880, 0x22c80000, &ctrl_reg);
//data_redir_m.Output_2->rasterization2_m.Input_2
  write_to_fifo(0x2000, 0xa4980fe0, &ctrl_reg);
  write_to_fifo(0x4880, 0x32500000, &ctrl_reg);
//zculling_top.Output_1->coloringFB_top_m.Input_1
  write_to_fifo(0x3000, 0x92900fe0, &ctrl_reg);
  write_to_fifo(0x2880, 0x23480000, &ctrl_reg);
//coloringFB_bot_m.Output_2->DEBUG.Input_7
  write_to_fifo(0x5000, 0xa1400fe0, &ctrl_reg);
  write_to_fifo(0x1080, 0x85500000, &ctrl_reg);
//data_redir_m.Output_3->DEBUG.Input_2
  write_to_fifo(0x2000, 0xb1180fe0, &ctrl_reg);
  write_to_fifo(0x1080, 0x32580000, &ctrl_reg);
//coloringFB_top_m.Output_2->DEBUG.Input_6
  write_to_fifo(0x2800, 0xa1380fe0, &ctrl_reg);
  write_to_fifo(0x1080, 0x72d00000, &ctrl_reg);
//DMA.Output_1->p2p.Input_1
  write_to_fifo(0x800, 0x95900fe0, &ctrl_reg);
  write_to_fifo(0x5880, 0x20c80000, &ctrl_reg);
//rasterization2_m.Output_2->zculling_bot.Input_1
  write_to_fifo(0x4800, 0xa3900fe0, &ctrl_reg);
  write_to_fifo(0x3880, 0x24d00000, &ctrl_reg);
//zculling_bot.Output_2->DEBUG.Input_5
  write_to_fifo(0x3800, 0xa1300fe0, &ctrl_reg);
  write_to_fifo(0x1080, 0x63d00000, &ctrl_reg);
//rasterization2_m.Output_4->zculling_bot.Input_2
  write_to_fifo(0x4800, 0xc3980fe0, &ctrl_reg);
  write_to_fifo(0x3880, 0x34e00000, &ctrl_reg);
//rasterization2_m.Output_5->DEBUG.Input_3
  write_to_fifo(0x4800, 0xd1200fe0, &ctrl_reg);
  write_to_fifo(0x1080, 0x44e80000, &ctrl_reg);
//p2p.Output_2->DEBUG.Input_1
  write_to_fifo(0x5800, 0xa1100fe0, &ctrl_reg);
  write_to_fifo(0x1080, 0x25d00000, &ctrl_reg);
//packet anchor



}
