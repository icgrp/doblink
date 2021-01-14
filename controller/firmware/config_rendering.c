#include "axi_lite_driver.h"
#include <generated/csr.h>
#include <generated/mem.h>
#include "config_rendering.h"

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
  int rev_0, rev_1;

  //check if the input fifo is empty
  while((lx_read32(SLV_REG3)>>1)&&1);

  //toggle the rd_en bits to start one reading
  *ctrl_reg = (*ctrl_reg) ^ 0x00000002;
  //input fifo rd_en = SLV_REG7[1]
  lx_write32(SLV_REG7, *ctrl_reg);

  //bft2arm_packet = {1'b1, SLV_REG1[15:0], SLV_REG0[31:0]}
  rev_0 = lx_read32(SLV_REG0);
  rev_1 = lx_read32(SLV_REG1);

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

  write_to_fifo(0x2000, 0x92403f80, &ctrl_reg);
  write_to_fifo(0x2200, 0x23200000, &ctrl_reg);
  write_to_fifo(0x2000, 0xa2603f80, &ctrl_reg);
  write_to_fifo(0x2200, 0x33400000, &ctrl_reg);
  write_to_fifo(0x2000, 0xb2803f80, &ctrl_reg);
  write_to_fifo(0x2200, 0x43600000, &ctrl_reg);
  write_to_fifo(0x2000, 0xc2a03f80, &ctrl_reg);
  write_to_fifo(0x2200, 0x53800000, &ctrl_reg);
  write_to_fifo(0x2000, 0xd2c03f80, &ctrl_reg);
  write_to_fifo(0x2200, 0x63a00000, &ctrl_reg);
  write_to_fifo(0x2000, 0xe2e03f80, &ctrl_reg);
  write_to_fifo(0x2200, 0x73c00000, &ctrl_reg);
  write_to_fifo(0x2000, 0xf6403f80, &ctrl_reg);
  write_to_fifo(0x6200, 0x23e00000, &ctrl_reg);
  write_to_fifo(0x6000, 0x9c403f80, &ctrl_reg);
  write_to_fifo(0xc200, 0x27200000, &ctrl_reg);
  write_to_fifo(0x6000, 0xac603f80, &ctrl_reg);
  write_to_fifo(0xc200, 0x37400000, &ctrl_reg);
  write_to_fifo(0xc000, 0x9e403f80, &ctrl_reg);
  write_to_fifo(0xe200, 0x2d200000, &ctrl_reg);
  write_to_fifo(0xc000, 0xaa403f80, &ctrl_reg);
  write_to_fifo(0xa200, 0x2d400000, &ctrl_reg);
  write_to_fifo(0xc000, 0xbe603f80, &ctrl_reg);
  write_to_fifo(0xe200, 0x3d600000, &ctrl_reg);
  write_to_fifo(0xc000, 0xca603f80, &ctrl_reg);
  write_to_fifo(0xa200, 0x3d800000, &ctrl_reg);
  write_to_fifo(0xe000, 0x94403f80, &ctrl_reg);
  write_to_fifo(0x4200, 0x2f200000, &ctrl_reg);
  write_to_fifo(0xa000, 0x98403f80, &ctrl_reg);
  write_to_fifo(0x8200, 0x2b200000, &ctrl_reg);
  write_to_fifo(0x8000, 0x94603f80, &ctrl_reg);
  write_to_fifo(0x4200, 0x39200000, &ctrl_reg);
  write_to_fifo(0x4000, 0x93003f80, &ctrl_reg);
  write_to_fifo(0x2200, 0x85200000, &ctrl_reg);
}
