/******************************************************************************
*
* Copyright (C) 2010 - 2017 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/
/*****************************************************************************/
/**
 *
 * @file xaxidma_example_poll_multi_pkts.c
 *
 * This file demonstrates how to use the xaxidma driver on the Xilinx AXI
 * DMA core (AXIDMA) to transfer multiple packets in polling mode when the
 * AXI DMA core is configured in Scatter Gather Mode.
 *
 * This code assumes a loopback hardware widget is connected to the AXI DMA
 * core for data packet loopback.
 *
 * To see the debug print, you need a Uart16550 or uartlite in your system,
 * and please set "-DDEBUG" in your compiler options. You need to rebuild your
 * software executable.
 *
 * Make sure that MEMORY_BASE is defined properly as per the HW system. The
 * h/w system built in Area mode has a maximum DDR memory limit of 64MB. In
 * throughput mode, it is 512MB.  These limits are need to ensured for
 * proper operation of this code.
 *
 *
 * <pre>
 * MODIFICATION HISTORY:
 *
 * Ver   Who  Date     Changes
 * ----- ---- -------- -------------------------------------------------------
 * 1.00a jz   05/17/10 First release
 * 2.00a jz   08/10/10 Second release, added in xaxidma_g.c, xaxidma_sinit.c,
 *		       updated tcl file, added xaxidma_porting_guide.h, removed
 *		       workaround for endianness
 * 4.00a rkv  02/22/11 Name of the file has been changed for naming consistency
 * 5.00a srt  03/06/12 Added Flushing and Invalidation of Caches to fix CRs
 *		       648103, 648701.
 *		       Added V7 DDR Base Address to fix CR 649405.
 * 6.00a srt  03/27/12 Changed API calls to support MCDMA driver.
 * 7.00a srt  06/18/12 API calls are reverted back for backward compatibility.
 * 7.02a srt  03/01/13 Updated DDR base address for IPI designs (CR 703656).
 * 9.1   adk  01/07/16 Updated DDR base address for Ultrascale (CR 799532) and
 *		       removed the defines for S6/V6.
 * 9.3   ms   01/23/17 Modified xil_printf statement in main function to
 *                     ensure that "Successfully ran" and "Failed" strings are
 *                     available in all examples. This is a fix for CR-965028.
 *       ms   04/05/17 Added tabspace for return statements in functions
 *                     for proper documentation while generating doxygen.
 * 9.5   adk  17/10/17 Marked the BD region as Normal Non-Cacheable for A53
 *		       (CR#987026).
 * 9.6   rsp  02/14/18 Support data buffers above 4GB.Use UINTPTR for storing
 *                     and typecasting buffer address(CR-992638).
 * </pre>
 *
 * ***************************************************************************
 */
/***************************** Include Files *********************************/
#include <stdio.h>
#include "xaxidma.h"
#include "xparameters.h"
#include "xdebug.h"

#include "xtime_l.h"
#include "sleep.h"
#ifdef __aarch64__
#include "xil_mmu.h"
#endif

#if defined(XPAR_UARTNS550_0_BASEADDR)
#include "xuartns550_l.h"       /* to use uartns550 */
#endif


#ifndef DEBUG
extern void xil_printf(const char *format, ...);
#endif


#include "input_data_i.h"
#include "label.h"
#include "config_bnn.h"

/******************** Constant Definitions **********************************/

/*********************** TEMPORARY ******************************************/
/*
 * Device hardware build related constants.
 */
#define DMA_BASE_ADDR_0		XPAR_AXIDMA_0_BASEADDR
#define DMA_DEV_ID_0		XPAR_AXIDMA_0_DEVICE_ID
#define DMA_BASE_ADDR_1		XPAR_AXIDMA_1_BASEADDR
#define DMA_DEV_ID_1		XPAR_AXIDMA_1_DEVICE_ID

#ifdef XPAR_AXI_7SDDR_0_S_AXI_BASEADDR
#define DDR_BASE_ADDR		XPAR_AXI_7SDDR_0_S_AXI_BASEADDR
#elif XPAR_MIG7SERIES_0_BASEADDR
#define DDR_BASE_ADDR	XPAR_MIG7SERIES_0_BASEADDR
#elif XPAR_MIG_0_BASEADDR
#define DDR_BASE_ADDR	XPAR_MIG_0_BASEADDR
#elif XPAR_PSU_DDR_0_S_AXI_BASEADDR
#define DDR_BASE_ADDR	XPAR_PSU_DDR_0_S_AXI_BASEADDR
#endif

#ifndef DDR_BASE_ADDR
#warning CHECK FOR THE VALID DDR ADDRESS IN XPARAMETERS.H, \
		DEFAULT SET TO 0x01000000
#define MEM_BASE_ADDR		0x01000000
#else
#define MEM_BASE_ADDR		(DDR_BASE_ADDR + 0x1000000)
#endif


#define TX_BD_SPACE_BASE	(MEM_BASE_ADDR)
#define TX_BD_SPACE_HIGH	(MEM_BASE_ADDR + 0x007FFFFF)
#define RX_BD_SPACE_BASE	(MEM_BASE_ADDR + 0x00800000)
#define RX_BD_SPACE_HIGH	(MEM_BASE_ADDR + 0x00FFFFFF)
#define TX_BUFFER_BASE		(MEM_BASE_ADDR + 0x01000000)
#define RX_BUFFER_BASE		(MEM_BASE_ADDR + 0x10000000)
#define RX_BUFFER_HIGH		(MEM_BASE_ADDR + 0x1EFFFFFF)

#define TX_MAX_PKT_LEN		0x1000
#define TX_NUMBER_OF_PACKETS 	0x2
#define RX_MAX_PKT_LEN		0x200
#define RX_NUMBER_OF_PACKETS 	0x1
#define NUMBER_OF_TEST		0x1
#define TEST_START_VALUE	(TX_MAX_PKT_LEN * TX_NUMBER_OF_PACKETS / 4)

/**************************** Type Definitions *******************************/


/***************** Macros (Inline Functions) Definitions *********************/


/************************** Function Prototypes ******************************/
#if defined(XPAR_UARTNS550_0_BASEADDR)
static void Uart550_Setup(void);
#endif
static int DmaConfig(void);
static int DmaStart(int test);
static int RxSetup(XAxiDma * AxiDmaInstPtr);
static int TxSetup(XAxiDma * AxiDmaInstPtr);
static int SendPackets(u32 SendPacketSize, u32 SendPacketNum, u32 Value, XAxiDma * AxiDmaInstPtr);
static int CheckData(u32 GetPacketSize, u32 GetPacketNum);
static int CheckDmaResult(u32 GetPacketSize, u32 GetPacketNum, XAxiDma * AxiDmaInstPtr_1);

/************************** Variable Definitions *****************************/
/*
 * Device instance definitions
 */
XAxiDma AxiDma_0, AxiDma_1;

/*
 * Buffer for transmit packet.
 */
u32 *Packet = (u32 *) TX_BUFFER_BASE;

static XAxiDma_Bd *LastRxBdPtr = NULL;

XTime Start, End, TStart, TEnd, DMAStart, DMAEnd, TranEnd;

/*****************************************************************************/
/**
*
* Main function
*
* This function is the main entry of the tests on DMA core. It sets up
* DMA engine to be ready to receive and send packets, then a packet is
* transmitted and will be verified after it is received via the DMA loopback
* widget.
*
* @param	None
*
* @return
*		- XST_SUCCESS if test pass,
* 		- XST_FAILURE if test fails
*
* @note		None.
*
******************************************************************************/
int main(void)
{
	int Status, j;
	xil_printf("\r\n--- Entering main() --- \r\n");
	Status = 0;
	double time;
	init_regs();
	sleep(5);

	/* Send packets and check results */
	XTime_GetTime(&TStart);
	for (j = 0; j < NUMBER_OF_TEST; j++){
		Status = DmaStart(j);
		if(Status) return XST_FAILURE;
	}
	XTime_GetTime(&TEnd);
	time = ((double)(TEnd - TStart) / (COUNTS_PER_SECOND / 1000000));
	printf("Send and Check Time: %.2lfus\n", time);

	xil_printf("Successfully ran AXI DMA poll multi Example\r\n");
	xil_printf("--- Exiting main() --- \r\n");
	return XST_SUCCESS;
}
static int DmaConfig(void){
	double time;
	int Status;
	XAxiDma_Config *Config_0, *Config_1;

	#if defined(XPAR_UARTNS550_0_BASEADDR)

		Uart550_Setup();

	#endif

	#ifdef __aarch64__
		Xil_SetTlbAttributes(TX_BD_SPACE_BASE, NORM_NONCACHE);
		Xil_SetTlbAttributes(RX_BD_SPACE_BASE, NORM_NONCACHE);
	#endif

	XTime_GetTime(&Start);
	Config_0 = XAxiDma_LookupConfig(DMA_DEV_ID_0);
	if (!Config_0) {
		xil_printf("No config found for %d\r\n", DMA_DEV_ID_0);

		return XST_FAILURE;
	}

	/* Initialize DMA_0 engine */
	Status = XAxiDma_CfgInitialize(&AxiDma_0, Config_0);
	if (Status != XST_SUCCESS) {
		xil_printf("Initialization failed %d\r\n", Status);

		return XST_FAILURE;
	}

	Config_1 = XAxiDma_LookupConfig(DMA_DEV_ID_1);
	if (!Config_1) {
		xil_printf("No config found for %d\r\n", DMA_DEV_ID_1);

		return XST_FAILURE;
	}

	/* Initialize DMA_1 engine */
	Status = XAxiDma_CfgInitialize(&AxiDma_1, Config_1);
	if (Status != XST_SUCCESS) {
		xil_printf("Initialization failed %d\r\n", Status);

		return XST_FAILURE;
	}
	XTime_GetTime(&End);
	time = ((double)(End - Start) / (COUNTS_PER_SECOND / 1000000));
	printf("DMA Config Time: %.2lfus\n", time);

	XTime_GetTime(&Start);
	if(!XAxiDma_HasSg(&AxiDma_0)) {
		xil_printf("Device 0 configured as simple mode \r\n");
		return XST_FAILURE;
	}

	if(!XAxiDma_HasSg(&AxiDma_1)) {
		xil_printf("Device 1 configured as simple mode \r\n");
		return XST_FAILURE;
	}
	XTime_GetTime(&End);
	time = ((double)(End - Start) / (COUNTS_PER_SECOND / 1000000));
	printf("SG Mode Verifying Time: %.2lfus\n", time);

	XTime_GetTime(&Start);
	Status = TxSetup(&AxiDma_0);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
	XTime_GetTime(&End);
	time = ((double)(End - Start) / (COUNTS_PER_SECOND / 1000000));
	printf("Tx Setup Time: %.2lfus\n", time);

	XTime_GetTime(&Start);
	Status = RxSetup(&AxiDma_1);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
	XTime_GetTime(&End);
	time = ((double)(End - Start) / (COUNTS_PER_SECOND / 1000000));
	printf("Rx Setup Time: %.2lfus\n", time);
	return XST_SUCCESS;
}

static int DmaStart(int test)
{
	int Status;
	double time;

	//xil_printf("\r\n--- Entering test%x --- \r\n", test);
	DmaConfig();
	/* Send packets */
	//Status = SendPackets(MAX_PKT_LEN, NUMBER_OF_PACKETS, &AxiDma_0);

	Status = SendPackets(TX_MAX_PKT_LEN, TX_NUMBER_OF_PACKETS, 1, &AxiDma_0);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
	/* Check DMA transfer result */
	Status = CheckDmaResult(RX_MAX_PKT_LEN, RX_NUMBER_OF_PACKETS, &AxiDma_1);
	if (Status != XST_SUCCESS) {
		xil_printf("AXI DMA poll multi Example Failed\r\n");
		return XST_FAILURE;
	}

	//xil_printf("--- Exiting test_%x --- \r\n", test);

	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	return XST_SUCCESS;
}


#if defined(XPAR_UARTNS550_0_BASEADDR)
/*****************************************************************************/
/*
*
* Uart16550 setup routine, need to set baudrate to 9600 and data bits to 8
*
* @param	None
*
* @return	None
*
* @note		None.
*

******************************************************************************/
static void Uart550_Setup(void)
{
	/* Set the baudrate to be predictable
	 */
	XUartNs550_SetBaud(XPAR_UARTNS550_0_BASEADDR,
			XPAR_XUARTNS550_CLOCK_HZ, 9600);

	XUartNs550_SetLineControlReg(XPAR_UARTNS550_0_BASEADDR,
			XUN_LCR_8_DATA_BITS);

}
#endif

/*****************************************************************************/
/**
*
* This function sets up RX channel of the DMA engine to be ready for packet
* reception
*
* @param	AxiDmaInstPtr is the pointer to the instance of the DMA engine.
*
* @return	- XST_SUCCESS if the setup is successful
*		- XST_FAILURE if setup is failure
*
* @note		None.
*
******************************************************************************/
static int RxSetup(XAxiDma * AxiDmaInstPtr)
{
	XAxiDma_BdRing *RxRingPtr;
	int Delay = 0;
	int Coalesce = 1;
	int Status;
	XAxiDma_Bd BdTemplate;
	XAxiDma_Bd *BdPtr;
	XAxiDma_Bd *BdCurPtr;
	u32 BdCount;
	u32 FreeBdCount;
	UINTPTR RxBufferPtr;
	int i;

	RxRingPtr = XAxiDma_GetRxRing(&AxiDma_1);

	/* Disable all RX interrupts before RxBD space setup */

	XAxiDma_BdRingIntDisable(RxRingPtr, XAXIDMA_IRQ_ALL_MASK);

	/* Set delay and coalescing */
	XAxiDma_BdRingSetCoalesce(RxRingPtr, Coalesce, Delay);

	/* Setup Rx BD space */
	BdCount = XAxiDma_BdRingCntCalc(XAXIDMA_BD_MINIMUM_ALIGNMENT,
				RX_BD_SPACE_HIGH - RX_BD_SPACE_BASE + 1);

	Status = XAxiDma_BdRingCreate(RxRingPtr, RX_BD_SPACE_BASE,
				RX_BD_SPACE_BASE,
				XAXIDMA_BD_MINIMUM_ALIGNMENT, BdCount);

	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Setup an all-zero BD as the template for the Rx channel.
	 */
	XAxiDma_BdClear(&BdTemplate);

	Status = XAxiDma_BdRingClone(RxRingPtr, &BdTemplate);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/* Attach buffers to RxBD ring so we are ready to receive packets
	 */
	FreeBdCount = XAxiDma_BdRingGetFreeCnt(RxRingPtr);
	Status = XAxiDma_BdRingAlloc(RxRingPtr, FreeBdCount, &BdPtr);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	BdCurPtr = BdPtr;
	RxBufferPtr = RX_BUFFER_BASE;

	for (i = 0; i < FreeBdCount; i++) {

		Status = XAxiDma_BdSetBufAddr(BdCurPtr, RxBufferPtr);
		if (Status != XST_SUCCESS) {
			xil_printf("Rx set buffer addr %x on BD %x failed %d\r\n",
			(unsigned int)RxBufferPtr, (UINTPTR)BdCurPtr,
								Status);

			return XST_FAILURE;
		}

		Status = XAxiDma_BdSetLength(BdCurPtr, RX_MAX_PKT_LEN,
				RxRingPtr->MaxTransferLen);
		if (Status != XST_SUCCESS) {
			xil_printf("Rx set length %d on BD %x failed %d\r\n",
			    RX_MAX_PKT_LEN, (UINTPTR)BdCurPtr, Status);

			return XST_FAILURE;
		}

		/* Receive BDs do not need to set anything for the control
		 * The hardware will set the SOF/EOF bits per stream status
		 */
		XAxiDma_BdSetCtrl(BdPtr, 0);
		XAxiDma_BdSetId(BdCurPtr, RxBufferPtr);
		RxBufferPtr += RX_MAX_PKT_LEN;

		if (i == (FreeBdCount - 1)) {
			LastRxBdPtr = BdCurPtr;
		}

		BdCurPtr = (XAxiDma_Bd *)XAxiDma_BdRingNext(RxRingPtr, BdCurPtr);
	}

	Status = XAxiDma_BdRingToHw(RxRingPtr, FreeBdCount, BdPtr);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/* Start RX DMA channel */
	Status = XAxiDma_BdRingStart(RxRingPtr);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	return XST_SUCCESS;
}

/*****************************************************************************/
/**
*
* This function sets up the TX channel of a DMA engine to be ready for packet
* transmission
*
* @param	AxiDmaInstPtr is the instance pointer to the DMA engine.
*
* @return	- XST_SUCCESS if the setup is successful
*		- XST_FAILURE if setup is failure
*
* @note     None.
*
******************************************************************************/
static int TxSetup(XAxiDma * AxiDmaInstPtr)
{
	XAxiDma_BdRing *TxRingPtr;
	XAxiDma_Bd BdTemplate;
	int Delay = 0;
	int Coalesce = 1;
	int Status;
	u32 BdCount;

	TxRingPtr = XAxiDma_GetTxRing(&AxiDma_0);

	/* Disable all TX interrupts before Tx BD space setup */

	XAxiDma_BdRingIntDisable(TxRingPtr, XAXIDMA_IRQ_ALL_MASK);

	/* Set TX delay and coalesce */
	XAxiDma_BdRingSetCoalesce(TxRingPtr, Coalesce, Delay);

	/* Setup Tx BD space  */
	BdCount = XAxiDma_BdRingCntCalc(XAXIDMA_BD_MINIMUM_ALIGNMENT,
				TX_BD_SPACE_HIGH - TX_BD_SPACE_BASE + 1);

	Status = XAxiDma_BdRingCreate(TxRingPtr, TX_BD_SPACE_BASE,
				TX_BD_SPACE_BASE,
				XAXIDMA_BD_MINIMUM_ALIGNMENT, BdCount);
	if (Status != XST_SUCCESS) {
		xil_printf("failed create BD ring in txsetup\r\n");

		return XST_FAILURE;
	}

	/*
	 * We create an all-zero BD as the template.
	 */
	XAxiDma_BdClear(&BdTemplate);

	Status = XAxiDma_BdRingClone(TxRingPtr, &BdTemplate);
	if (Status != XST_SUCCESS) {
		xil_printf("failed bdring clone in txsetup %d\r\n", Status);

		return XST_FAILURE;
	}

	/* Start the TX channel */
	Status = XAxiDma_BdRingStart(TxRingPtr);
	if (Status != XST_SUCCESS) {
		xil_printf("failed start bdring txsetup %d\r\n", Status);

		return XST_FAILURE;
	}

	return XST_SUCCESS;
}

/*****************************************************************************/
/**
*
* This function transmits packets non-blockingly through the DMA engine.
*
* @param	AxiDmaInstPtr points to the DMA engine instance
*
* @return	- XST_SUCCESS if the DMA accepts the packet successfully,
*		- XST_FAILURE if failure.
*
* @note		None.
*
******************************************************************************/
static int SendPackets(u32 SendPacketSize, u32 SendPacketNum, u32 Value, XAxiDma * AxiDmaInstPtr)
{
	XAxiDma_BdRing *TxRingPtr;
	u32 *TxPacket;
	XAxiDma_Bd *BdPtr;
	u32 ProcessedBdCount = 0;
	int Status;
	int index = 0, j;
	UINTPTR BufAddr;
	XAxiDma_Bd *CurBdPtr;
	double time;
	unsigned long i=0;

	/* Create pattern in the packet to transmit
	 */
	TxPacket = (u32 *) Packet;

	XTime_GetTime(&Start);
	for(i = 0; i < 2048000; i ++){
		TxPacket[i] = (u32)input_data_i[i];
		//TxPacket[i * 320 + j] = i * 320 + j;
		index ++;
	}
	XTime_GetTime(&End);
	time = ((double)(End - Start) / (COUNTS_PER_SECOND / 1000000));
	printf("Packet Create Time: %.2lfus\n", time);

	/* Flush the SrcBuffer before the DMA transfer, in case the Data Cache
	 * is enabled
	 */
	XTime_GetTime(&Start);
	Xil_DCacheFlushRange((UINTPTR)TxPacket, SendPacketSize *
							SendPacketNum);
	XTime_GetTime(&End);
	time = ((double)(End - Start) / (COUNTS_PER_SECOND / 1000000));
	printf("Flush SrcBuffer Time: %.2lfus\n", time);

#ifdef __aarch64__
	Xil_DCacheFlushRange((UINTPTR)RX_BUFFER_BASE, SendPacketSize *
						 SendPacketNum);
#endif

	XTime_GetTime(&Start);
	TxRingPtr = XAxiDma_GetTxRing(AxiDmaInstPtr);
	XTime_GetTime(&End);
	time = ((double)(End - Start) / (COUNTS_PER_SECOND / 1000000));
	printf("TX Ring Time: %.2lfus\n", time);

	/* Allocate BDs */
	XTime_GetTime(&Start);
	Status = XAxiDma_BdRingAlloc(TxRingPtr, SendPacketNum, &BdPtr);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
	XTime_GetTime(&End);
	time = ((double)(End - Start) / (COUNTS_PER_SECOND / 1000000));
	printf("Allocate BDs Time: %.2lfus\n", time);

	/* Set up the BDs using the information of the packet to transmit */
	BufAddr = (UINTPTR)Packet;
	CurBdPtr = BdPtr;

	XTime_GetTime(&Start);
	for (i = 0; i < SendPacketNum; i++) {
		u32 CrBits = 0;

		Status = XAxiDma_BdSetBufAddr(CurBdPtr, BufAddr);
		if (Status != XST_SUCCESS) {
			xil_printf("Tx set buffer addr %x on BD %x failed %d\r\n",
			(unsigned int)BufAddr, (UINTPTR)CurBdPtr, Status);

			return XST_FAILURE;
		}

		Status = XAxiDma_BdSetLength(CurBdPtr, SendPacketSize,
				TxRingPtr->MaxTransferLen);
		if (Status != XST_SUCCESS) {
			xil_printf("Tx set length %d on BD %x failed %d\r\n",
					SendPacketSize, (UINTPTR)CurBdPtr, Status);

			return XST_FAILURE;
		}

		if (i == 0) {
			CrBits |= XAXIDMA_BD_CTRL_TXSOF_MASK;

#if (XPAR_AXIDMA_0_SG_INCLUDE_STSCNTRL_STRM == 1)
			/* The first BD has total transfer length set in
			 * the last APP word, this is for the loopback widget
			 */
			Status = XAxiDma_BdSetAppWord(CurBdPtr,
			    XAXIDMA_LAST_APPWORD,
				SendPacketSize * SendPacketNum);

			if (Status != XST_SUCCESS) {
				xil_printf("Set app word failed with %d\r\n",
								Status);
			}
#endif
		}
		if (i == (SendPacketNum - 1)) {
			CrBits |= XAXIDMA_BD_CTRL_TXEOF_MASK;
			XAxiDma_BdSetCtrl(CurBdPtr,
					XAXIDMA_BD_CTRL_TXEOF_MASK);
		}
		XAxiDma_BdSetCtrl(CurBdPtr, CrBits);

		XAxiDma_BdSetId(CurBdPtr, BufAddr);

		BufAddr += SendPacketSize;
		CurBdPtr = (XAxiDma_Bd *)XAxiDma_BdRingNext(TxRingPtr, CurBdPtr);
	}
	XTime_GetTime(&End);
	time = ((double)(End - Start) / (COUNTS_PER_SECOND / 1000000));
	printf("Setup BDs with Packet information Time: %.2lfus\n", time);


	XTime_GetTime(&DMAStart);
	/* Give the BD to DMA to kick off the transmission. */
	Status = XAxiDma_BdRingToHw(TxRingPtr, SendPacketNum, BdPtr);
	if (Status != XST_SUCCESS) {
		xil_printf("to hw failed %d\r\n", Status);

		return XST_FAILURE;
	}

	/* Wait until the TX transactions are done */
	while (ProcessedBdCount < SendPacketNum) {
		ProcessedBdCount += XAxiDma_BdRingFromHw(TxRingPtr,
					       XAXIDMA_ALL_BDS, &BdPtr);
		//printf("%d\n", ProcessedBdCount);
	}
	XTime_GetTime(&DMAEnd);
	time = ((double)(DMAEnd - DMAStart) / (COUNTS_PER_SECOND / 1000000));
	int tran_bytes = SendPacketSize * SendPacketNum;
	printf("%.2fMB for %.2f us. At throughput of %.2fMB/s.\n", ((double)tran_bytes / 1000000), time, (double)(tran_bytes / time));

	/* Free all processed TX BDs for future transmission */
	XTime_GetTime(&Start);
	Status = XAxiDma_BdRingFree(TxRingPtr, ProcessedBdCount, BdPtr);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
	XTime_GetTime(&End);
	time = ((double)(End - Start) / (COUNTS_PER_SECOND / 1000000));
	printf("Free TX BDs Time: %.2lfus\n", time);

	return XST_SUCCESS;
}

/*****************************************************************************/
/**
*
* This function checks data buffer after the DMA transfer is finished.
*
* @param	None
*
* @return	- XST_SUCCESS if validation is successful
*		- XST_FAILURE if validation is failure.
*
* @note		None.
*
******************************************************************************/
static int CheckData(u32 GetPacketSize, u32 GetPacketNum)
{
	u32 *RxPacket;
	int i = 0;

	RxPacket = (u32 *) RX_BUFFER_BASE;

	/* Invalidate the DestBuffer before receiving the data, in case the
	 * Data Cache is enabled
	 */
#ifndef __aarch64__
	Xil_DCacheInvalidateRange((UINTPTR)RxPacket, GetPacketSize *
			GetPacketNum);
#endif
	float err_num = -1000;
	for(i = 0; i < GetPacketSize * GetPacketNum / 4; i++) {
		//printf("%x / %x\n", RxPacket[i], label_i[i/2]);
		if(RxPacket[i] != label_i[i/2]){
			err_num = err_num+1;

		}
		printf("We receive %d\n", (unsigned int)RxPacket[i]);

	}

	printf("The err rate is %%%.2f\n", (err_num/10));

	return XST_SUCCESS;
}

/*****************************************************************************/
/**
*
* This function delays until the DMA transaction is finished, checks data,
* and cleans up.
*
* @param	AxiDmaInstPtr points to the DMA engine instance
*
* @return	- XST_SUCCESS if DMA transfer is successful and data is correct
*		- XST_FAILURE if failure
*
* @note		None.
*
******************************************************************************/
static int CheckDmaResult(u32 GetPacketSize, u32 GetPacketNum, XAxiDma * AxiDmaInstPtr_1)
{
	XAxiDma_BdRing *RxRingPtr;
	XAxiDma_Bd *BdPtr;
	u32 ProcessedBdCount = 0;
	u32 FreeBdCount;
	u32 * RxPacket;
	int Status;
	double time;

	RxRingPtr = XAxiDma_GetRxRing(AxiDmaInstPtr_1);

	/* Wait until the data has been received by the Rx channel */

	XTime_GetTime(&Start);
	//printf("%d\n", XAxiDma_BdRingFromHw(RxRingPtr, XAXIDMA_ALL_BDS, &BdPtr));
	while (ProcessedBdCount < GetPacketNum) {

		ProcessedBdCount += XAxiDma_BdRingFromHw(RxRingPtr,
					       XAXIDMA_ALL_BDS, &BdPtr);
	}
	XTime_GetTime(&End);
	time = ((double)(End - DMAStart) / (COUNTS_PER_SECOND / 1000000));
	printf("Data Send Receive Time: %.2lfus\n", time);

	/* Check received data */
	XTime_GetTime(&Start);
	RxPacket = (u32 *) RX_BUFFER_BASE;
	if (CheckData(GetPacketSize, GetPacketNum) != XST_SUCCESS) {

		return XST_FAILURE;
	}
	XTime_GetTime(&End);
	time = ((double)(End - Start) / (COUNTS_PER_SECOND / 1000000));
	printf("Check Data Time: %.2lfus\n", time);

	/* Free all processed RX BDs for future transmission */
	XTime_GetTime(&Start);
	Status = XAxiDma_BdRingFree(RxRingPtr, ProcessedBdCount, BdPtr);
	if (Status != XST_SUCCESS) {
		xil_printf("free bd failed\r\n");
		return XST_FAILURE;
	}
	XTime_GetTime(&End);
	time = ((double)(End - Start) / (COUNTS_PER_SECOND / 1000000));
	printf("Free RX BDs Time: %.2lfus\n", time);

	/* Return processed BDs to RX channel so we are ready to receive new
	 * packets:
	 *    - Allocate all free RX BDs
	 *    - Pass the BDs to RX channel
	 */
	XTime_GetTime(&Start);
	FreeBdCount = XAxiDma_BdRingGetFreeCnt(RxRingPtr);
	Status = XAxiDma_BdRingAlloc(RxRingPtr, FreeBdCount, &BdPtr);
	if (Status != XST_SUCCESS) {
		xil_printf("bd alloc failed\r\n");
		return XST_FAILURE;
	}

	Status = XAxiDma_BdRingToHw(RxRingPtr, FreeBdCount, BdPtr);
	XTime_GetTime(&End);
	time = ((double)(End - Start) / (COUNTS_PER_SECOND / 1000000));
	printf("Return Time: %.2lfus\n", time);

	return Status;
}
