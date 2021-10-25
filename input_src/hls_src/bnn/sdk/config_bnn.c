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

	write_to_fifo(0x800, 0x99900fe0, &ctrl_reg);
	write_to_fifo(0x9880, 0x20c80000, &ctrl_reg);
	write_to_fifo(0x9800, 0x91100fe0, &ctrl_reg);
	write_to_fifo(0x1080, 0x29c80000, &ctrl_reg);
	write_to_fifo(0x9800, 0xa9100fe0, &ctrl_reg);
	write_to_fifo(0x9080, 0x29d00000, &ctrl_reg);
	write_to_fifo(0x9800, 0xbb100fe0, &ctrl_reg);
	write_to_fifo(0xb080, 0x29d80000, &ctrl_reg);
	write_to_fifo(0x9800, 0xc0900fe0, &ctrl_reg);
	write_to_fifo(0x880, 0x29e00000, &ctrl_reg);
	write_to_fifo(0x9800, 0xd2100fe0, &ctrl_reg);
	write_to_fifo(0x2080, 0x29e80000, &ctrl_reg);
	write_to_fifo(0x9800, 0xe4900fe0, &ctrl_reg);
	write_to_fifo(0x4880, 0x29f00000, &ctrl_reg);
	write_to_fifo(0x9800, 0xf5100fe0, &ctrl_reg);
	write_to_fifo(0x5080, 0x29f80000, &ctrl_reg);
	write_to_fifo(0x1000, 0x99980fe0, &ctrl_reg);
	write_to_fifo(0x9880, 0x31480000, &ctrl_reg);
	write_to_fifo(0x1000, 0xa9a00fe0, &ctrl_reg);
	write_to_fifo(0x9880, 0x41500000, &ctrl_reg);
	write_to_fifo(0x9000, 0x99a80fe0, &ctrl_reg);
	write_to_fifo(0x9880, 0x59480000, &ctrl_reg);
	write_to_fifo(0x9000, 0xa9b00fe0, &ctrl_reg);
	write_to_fifo(0x9880, 0x69500000, &ctrl_reg);
	write_to_fifo(0xb000, 0x99b80fe0, &ctrl_reg);
	write_to_fifo(0x9880, 0x7b480000, &ctrl_reg);
	write_to_fifo(0xb000, 0xa9c00fe0, &ctrl_reg);
	write_to_fifo(0x9880, 0x8b500000, &ctrl_reg);
	write_to_fifo(0x2000, 0x9a900fe0, &ctrl_reg);
	write_to_fifo(0xa880, 0x22480000, &ctrl_reg);
	write_to_fifo(0xa800, 0x9e900fe0, &ctrl_reg);
	write_to_fifo(0xe880, 0x2ac80000, &ctrl_reg);
	write_to_fifo(0xe800, 0x9b900fe0, &ctrl_reg);
	write_to_fifo(0xb880, 0x2ec80000, &ctrl_reg);
	write_to_fifo(0xb800, 0x9c100fe0, &ctrl_reg);
	write_to_fifo(0xc080, 0x2bc80000, &ctrl_reg);
	write_to_fifo(0xc000, 0x95900fe0, &ctrl_reg);
	write_to_fifo(0x5880, 0x2c480000, &ctrl_reg);
	write_to_fifo(0x5800, 0x96100fe0, &ctrl_reg);
	write_to_fifo(0x6080, 0x25c80000, &ctrl_reg);
	write_to_fifo(0x6000, 0x93100fe0, &ctrl_reg);
	write_to_fifo(0x3080, 0x26480000, &ctrl_reg);
	write_to_fifo(0x3000, 0x91900fe0, &ctrl_reg);
	write_to_fifo(0x1880, 0x23480000, &ctrl_reg);
	write_to_fifo(0x1800, 0x99180fe0, &ctrl_reg);
	write_to_fifo(0x9080, 0x31c80000, &ctrl_reg);
	write_to_fifo(0x4800, 0x9f100fe0, &ctrl_reg);
	write_to_fifo(0xf080, 0x24c80000, &ctrl_reg);
	write_to_fifo(0xf000, 0x9d900fe0, &ctrl_reg);
	write_to_fifo(0xd880, 0x2f480000, &ctrl_reg);
	write_to_fifo(0xd800, 0x9e100fe0, &ctrl_reg);
	write_to_fifo(0xe080, 0x2dc80000, &ctrl_reg);
	write_to_fifo(0xe000, 0x98100fe0, &ctrl_reg);
	write_to_fifo(0x8080, 0x2e480000, &ctrl_reg);
	write_to_fifo(0x8000, 0x98900fe0, &ctrl_reg);
	write_to_fifo(0x8880, 0x28480000, &ctrl_reg);
	write_to_fifo(0x8800, 0x94100fe0, &ctrl_reg);
	write_to_fifo(0x4080, 0x28c80000, &ctrl_reg);
	write_to_fifo(0x4000, 0x9a100fe0, &ctrl_reg);
	write_to_fifo(0xa080, 0x24480000, &ctrl_reg);
	write_to_fifo(0xa000, 0x9b180fe0, &ctrl_reg);
	write_to_fifo(0xb080, 0x3a480000, &ctrl_reg);
	write_to_fifo(0x5000, 0x9f900fe0, &ctrl_reg);
	write_to_fifo(0xf880, 0x25480000, &ctrl_reg);
	write_to_fifo(0xf800, 0x9c900fe0, &ctrl_reg);
	write_to_fifo(0xc880, 0x2fc80000, &ctrl_reg);
	write_to_fifo(0xc800, 0x9d100fe0, &ctrl_reg);
	write_to_fifo(0xd080, 0x2cc80000, &ctrl_reg);
	write_to_fifo(0xd000, 0x96900fe0, &ctrl_reg);
	write_to_fifo(0x6880, 0x2d480000, &ctrl_reg);
	write_to_fifo(0x6800, 0x97900fe0, &ctrl_reg);
	write_to_fifo(0x7880, 0x26c80000, &ctrl_reg);
	write_to_fifo(0x7800, 0x93900fe0, &ctrl_reg);
	write_to_fifo(0x3880, 0x27c80000, &ctrl_reg);
	write_to_fifo(0x3800, 0x92900fe0, &ctrl_reg);
	write_to_fifo(0x2880, 0x23c80000, &ctrl_reg);
	write_to_fifo(0x2800, 0x9b200fe0, &ctrl_reg);
	write_to_fifo(0xb080, 0x42c80000, &ctrl_reg);


}
