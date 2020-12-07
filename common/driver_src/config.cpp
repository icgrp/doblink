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
//packet anchor



}
