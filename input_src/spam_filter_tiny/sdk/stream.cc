#include "stream.h"
#include "xparameters.h"
#include "xil_io.h"
#include "stdio.h"
#define AXI_REG0 XPAR_BFT0_AXI2STREAM_V1_0_0_BASEADDR
#define AXI_REG1 XPAR_BFT0_AXI2STREAM_V1_0_0_BASEADDR+4
#define AXI_REG2 XPAR_BFT0_AXI2STREAM_V1_0_0_BASEADDR+8
#define AXI_REG3 XPAR_BFT0_AXI2STREAM_V1_0_0_BASEADDR+12
#define AXI_REG4 XPAR_BFT0_AXI2STREAM_V1_0_0_BASEADDR+16
#define AXI_REG5 XPAR_BFT0_AXI2STREAM_V1_0_0_BASEADDR+20
#define AXI_REG6 XPAR_BFT0_AXI2STREAM_V1_0_0_BASEADDR+24
#define AXI_REG7 XPAR_BFT0_AXI2STREAM_V1_0_0_BASEADDR+28
#define AXI_REG8 XPAR_BFT0_AXI2STREAM_V1_0_0_BASEADDR+32
#define AXI_REG9 XPAR_BFT0_AXI2STREAM_V1_0_0_BASEADDR+36
#define AXI_REG10 XPAR_BFT0_AXI2STREAM_V1_0_0_BASEADDR+40
#define AXI_REG11 XPAR_BFT0_AXI2STREAM_V1_0_0_BASEADDR+44
#define AXI_REG12 XPAR_BFT0_AXI2STREAM_V1_0_0_BASEADDR+48
#define AXI_REG13 XPAR_BFT0_AXI2STREAM_V1_0_0_BASEADDR+52
#define AXI_REG14 XPAR_BFT0_AXI2STREAM_V1_0_0_BASEADDR+56
#define AXI_REG15 XPAR_BFT0_AXI2STREAM_V1_0_0_BASEADDR+60



stream_inst::stream_inst(int STATUS_REG, unsigned int CTRL_REG)
{
	this->status_reg = STATUS_REG;
	this->ctrl_reg = CTRL_REG;
}

void stream_inst::ap_start(void)
{
	this->ctrl_reg |= (0x00000001 << 14);
	Xil_Out32(AXI_REG7, this->ctrl_reg);
}


void stream_inst::stream1_write(unsigned int data)
{
	Xil_Out32(AXI_REG0, data);
	this->status_reg = Xil_In32(AXI_REG15);
	int cnt = 1;
	while(this->status_reg & (0x00000001 << 1)){
		cnt++;
		//printf("try %d times, stream1 cannot write, AXI_REG15=%08x\n", cnt, this->status_reg);
		//this->print_status();
		this->status_reg = Xil_In32(AXI_REG15);
	}
	this->ctrl_reg ^= (0x00000001 << 0);
	Xil_Out32(AXI_REG7, this->ctrl_reg);
}

void stream_inst::stream2_write(unsigned int data)
{

	Xil_Out32(AXI_REG1, data);
	this->status_reg = Xil_In32(AXI_REG15);
	int cnt = 1;
	while(this->status_reg & (0x00000001 << 3)) {
		cnt++;
		//printf("try %d times, stream2 cannot write, AXI_REG15=%08x\n", cnt, this->status_reg);
		//this->print_status();
		this->status_reg = Xil_In32(AXI_REG15);
	}
	this->ctrl_reg ^= (0x00000001 << 2);
	Xil_Out32(AXI_REG7, this->ctrl_reg);
}

void stream_inst::stream3_write(unsigned int data)
{
	Xil_Out32(AXI_REG2, data);
	this->status_reg = Xil_In32(AXI_REG15);
	int cnt = 1;
	while(this->status_reg & (0x00000001 << 5)){
		cnt++;
		//printf("try %d times, stream3 cannot write, AXI_REG15=%08x\n", cnt, this->status_reg);
		//this->print_status();
		this->status_reg = Xil_In32(AXI_REG15);
	}
	this->ctrl_reg ^= (0x00000001 << 4);
	Xil_Out32(AXI_REG7, this->ctrl_reg);
}

void stream_inst::stream4_write(unsigned int data)
{
	Xil_Out32(AXI_REG3, data);
	this->status_reg = Xil_In32(AXI_REG15);
	int cnt = 0;
	while(this->status_reg & (0x00000001 << 7)){
		cnt++;
		//printf("try %d times, stream4 cannot write, AXI_REG15=%08x\n", cnt, this->status_reg);
		//this->print_status();
		this->status_reg = Xil_In32(AXI_REG15);
	}
	this->ctrl_reg ^= (0x00000001 << 6);
	Xil_Out32(AXI_REG7, this->ctrl_reg);
}

void stream_inst::stream5_write(unsigned int data)
{
	Xil_Out32(AXI_REG4, data);
	this->status_reg = Xil_In32(AXI_REG15);
	int cnt = 0;
	while(this->status_reg & (0x00000001 << 9)){
		cnt++;
		//printf("try %d times, stream5 cannot write, AXI_REG15=%08x\n", cnt, this->status_reg);
		//this->print_status();
		this->status_reg = Xil_In32(AXI_REG15);
	}
	this->ctrl_reg ^= (0x00000001 << 8);
	Xil_Out32(AXI_REG7, this->ctrl_reg);
}

void stream_inst::stream6_write(unsigned int data)
{
	Xil_Out32(AXI_REG5, data);
	this->status_reg = Xil_In32(AXI_REG15);
	int cnt = 0;
	while(this->status_reg & (0x00000001 << 11)){
		cnt++;
		//printf("try %d times, stream6 cannot write, AXI_REG15=%08x\n", cnt, this->status_reg);
		//this->print_status();
		this->status_reg = Xil_In32(AXI_REG15);
	}
	this->ctrl_reg ^= (0x00000001 << 10);
	Xil_Out32(AXI_REG7, this->ctrl_reg);
}

void stream_inst::stream7_write(unsigned int data)
{
	Xil_Out32(AXI_REG6, data);
	this->status_reg = Xil_In32(AXI_REG15);
	int cnt = 0;
	while(this->status_reg & (0x00000001 << 13)){
		cnt++;
		//printf("try %d times, stream1 cannot write, AXI_REG15=%08x\n", cnt, this->status_reg);
		//this->print_status();
		this->status_reg = Xil_In32(AXI_REG15);
	}
	this->ctrl_reg ^= (0x00000001 << 12);
	Xil_Out32(AXI_REG7, this->ctrl_reg);
}

unsigned int stream_inst::stream1_read(unsigned int * data)
{
	*data = 0;
	int cnt = 0;
	while(Xil_In32(AXI_REG15) & (0x00000001 << 0)){
		if (cnt > 10){
			return 0;
		}
		cnt++;
		this->status_reg = Xil_In32(AXI_REG15);
	}
	this->ctrl_reg ^= (0x00000001 << 1);
	Xil_Out32(AXI_REG7, ctrl_reg);
	*data = Xil_In32(AXI_REG8);
	return 1;
}

unsigned int stream_inst::stream2_read(unsigned int * data)
{
	*data = 0;
	int cnt = 0;
	while(Xil_In32(AXI_REG15) & (0x00000001 << 2)){
		if (cnt > 10){
			return 0;
		}
		cnt++;
	}
	this->ctrl_reg ^= (0x00000001 << 3);
	Xil_Out32(AXI_REG7, ctrl_reg);
	*data = Xil_In32(AXI_REG9);
	return 1;
}

unsigned int stream_inst::stream3_read(unsigned int * data)
{
	*data = 0;
	int cnt = 0;
	while(Xil_In32(AXI_REG15) & (0x00000001 << 4)){
		if (cnt > 10){
			return 0;
		}
		cnt++;
	}
	this->ctrl_reg ^= (0x00000001 << 5);
	Xil_Out32(AXI_REG7, ctrl_reg);
	*data = Xil_In32(AXI_REG10);
	return 1;
}

unsigned int stream_inst::stream4_read(unsigned int * data)
{
	*data = 0;
	int cnt = 0;
	while(Xil_In32(AXI_REG15) & (0x00000001 << 6)){
		if (cnt > 10){
			return 0;
		}
		cnt++;
	}
	this->ctrl_reg ^= (0x00000001 << 7);
	Xil_Out32(AXI_REG7, ctrl_reg);
	*data = Xil_In32(AXI_REG11);
	return 1;
}

unsigned int stream_inst::stream5_read(unsigned int * data)
{
	*data = 0;
	int cnt = 0;
	while(Xil_In32(AXI_REG15) & (0x00000001 << 8)){
		if (cnt > 10){
			return 0;
		}
		cnt++;
	}
	this->ctrl_reg ^= (0x00000001 << 9);
	Xil_Out32(AXI_REG7, ctrl_reg);
	*data = Xil_In32(AXI_REG12);
	return 1;
}

unsigned int stream_inst::stream6_read(unsigned int * data)
{
	*data = 0;
	int cnt = 0;
	while(Xil_In32(AXI_REG15) & (0x00000001 << 10)){
		if (cnt > 10){
			return 0;
		}
		cnt++;
	}
	this->ctrl_reg ^= (0x00000001 << 11);
	Xil_Out32(AXI_REG7, ctrl_reg);
	*data = Xil_In32(AXI_REG13);
	return 1;
}

unsigned int stream_inst::stream7_read(unsigned int * data)
{
	*data = 0;
	int cnt = 0;
	while(Xil_In32(AXI_REG15) & (0x00000001 << 12)){
		if (cnt > 10){
			return 0;
		}
		cnt++;
	}
	this->ctrl_reg ^= (0x00000001 << 13);
	Xil_Out32(AXI_REG7, ctrl_reg);
	*data = Xil_In32(AXI_REG14);
	return 1;
}

void stream_inst::print_status()
{
	unsigned data = 0;
	data = Xil_In32(AXI_REG7);
	printf("AXI_REG7=%08x\n", data);
	data = Xil_In32(AXI_REG15);
	for(int i=0; i<7; i++){
		if ((data>>(2*i))&0x00000001){
			printf("stream in%d is empty!\n", i);
		}
	}
	printf("AXI_REG15=%08x\n", data);
	for(int i=0; i<7; i++){
		if (data &(0x00000001 << (2*i+1))){
			printf("stream out%d is full!\n", i);
		}
	}

}

