#include "xparameters.h"	/* SDK generated parameters */
//#include "xrtcpsu.h"		/* RTCPSU device driver */
//#include "xscugic.h"		/* Interrupt controller device driver */
//#include "xil_exception.h"
//#include "xil_printf.h"

#include "dma_driver.h"
#include "stream.h"
#include "typedefs.h"
#include "config_bnn.h"
#include "my_timer.h"
#include "sleep.h"


int main(void)
{
	int Status;
	/* Run the RtcPsu Interrupt example, specify the the Device ID */
	Status = RtcPsuSecondsIntrExample();
	if (Status != XST_SUCCESS) {
		xil_printf("RTC Seconds Interrupt Example Test Failed\r\n");
		return XST_FAILURE;
	} else {
		printf("Timer interrupt Completed\n\r");
	}

	config my_config(XPAR_BFT0_AXILITE2BFT_V2_0_0_BASEADDR, 0);
	my_config.init_regs();
	printf("Initialization Completed\n\r");
	my_config.app();

	my_config.ap_start();
	dma_inst dma0(DMA_DEV0_ID,
			 RX0_BD_SPACE_HIGH,
			 RX0_BD_SPACE_BASE,
			 MAX_PKT_LEN0,
			 MAX_PKT_LEN_RX0,
			 TX0_BD_SPACE_HIGH,
			 TX0_BD_SPACE_BASE,
			 NUMBER_OF_PACKETS0,
			 NUMBER_OF_PACKETS_RX0,
			 RX0_BUFFER_BASE,
			 TX0_BUFFER_BASE);

	dma_inst dma1(DMA_DEV1_ID,
			 RX1_BD_SPACE_HIGH,
			 RX1_BD_SPACE_BASE,
			 MAX_PKT_LEN1,
			 MAX_PKT_LEN_RX1,
			 TX1_BD_SPACE_HIGH,
			 TX1_BD_SPACE_BASE,
			 NUMBER_OF_PACKETS1,
			 NUMBER_OF_PACKETS_RX1,
			 RX1_BUFFER_BASE,
			 TX1_BUFFER_BASE);

	Status = dma0.dma_init();
	if (Status != XST_SUCCESS) {
		xil_printf("Device Initiation Failed!\r\n");
		return XST_FAILURE;
	}

	Status = dma1.dma_init();
	if (Status != XST_SUCCESS) {
		xil_printf("Device Initiation Failed!\r\n");
		return XST_FAILURE;
	}

	Status = dma0.TxRxSetup(1, 1);
	if (Status != XST_SUCCESS) {
		xil_printf("Device TxRX0 Setup Failed!\r\n");
		return XST_FAILURE;
	}

	Status = dma1.TxRxSetup(1, 0);
	if (Status != XST_SUCCESS) {
		xil_printf("Device TxRX1 Setup Failed!\r\n");
		return XST_FAILURE;
	}


	Status = dma0.RecvPackets();
		if (Status != XST_SUCCESS) {
			xil_printf("Receiving Packets Failed!\r\n");
			return XST_FAILURE;
	}


	Status = dma0.WR2TxBuffer0();
	if (Status != XST_SUCCESS) {
		xil_printf("Write Buffer Failed!\r\n");
		return XST_FAILURE;
	}

	Status = dma1.WR2TxBuffer1();
	if (Status != XST_SUCCESS) {
		xil_printf("Write Buffer Failed!\r\n");
		return XST_FAILURE;
	}

	Status = dma0.SendPackets();
	if (Status != XST_SUCCESS) {
		xil_printf("Sending0 Packets Failed!\r\n");
		return XST_FAILURE;
	}

	Status = dma1.SendPackets();
	if (Status != XST_SUCCESS) {
		xil_printf("Sending1 Packets Failed!\r\n");
		return XST_FAILURE;
	}

	Status = dma0.CleanTxBuffer();
	if (Status != XST_SUCCESS) {
		xil_printf("Cleaning TxBuffer0 Failed!\r\n");
		return XST_FAILURE;
	}

	Status = dma1.CleanTxBuffer();
	if (Status != XST_SUCCESS) {
		xil_printf("Cleaning TxBuffer1 Failed!\r\n");
		return XST_FAILURE;
	}

	Status = dma0.RecvWait();
	if (Status != XST_SUCCESS) {
		xil_printf("Receiving Waits Failed!\r\n");
		return XST_FAILURE;
	}

	Status = dma0.CheckData();
	if (Status != XST_SUCCESS) {
		xil_printf("Checking Data Failed!\r\n");
		return XST_FAILURE;
	}

	Status = dma0.print_results();
	if (Status != XST_SUCCESS) {
		xil_printf("Printing results Failed!\r\n");
		return XST_FAILURE;
	}

	Status = dma0.CleanRxBuffer();
	if (Status != XST_SUCCESS) {
		xil_printf("Cleaning RxBuffer Failed!\r\n");
		return XST_FAILURE;
	}



	for(int i=0; i<10; i++){
		sleep(1);
		//printf("%d seconds\n", i);
	}


	ClearRtcPsu();
	xil_printf("Successfully ran RTC Seconds Interrupt Example Test\r\n");
	xil_printf("Optical_flow is completed\n\r");
	return XST_SUCCESS;
}


