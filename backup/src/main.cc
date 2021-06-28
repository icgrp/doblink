

#include "xparameters.h"	/* SDK generated parameters */
//#include "xrtcpsu.h"		/* RTCPSU device driver */
//#include "xscugic.h"		/* Interrupt controller device driver */
//#include "xil_exception.h"
//#include "xil_printf.h"

#include "dma_driver.h"
#include "stream.h"
#include "typedefs.h"
#include "config_optical_flow_origin.h"
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
	dma_inst dma1(DMA_DEV_ID,
			 RX_BD_SPACE_HIGH,
			 RX_BD_SPACE_BASE,
			 MAX_PKT_LEN,
			 MAX_PKT_LEN_RX,
			 TX_BD_SPACE_HIGH,
			 TX_BD_SPACE_BASE,
			 NUMBER_OF_PACKETS,
			 NUMBER_OF_PACKETS_RX,
			 RX_BUFFER_BASE,
			 TX_BUFFER_BASE);

	Status = dma1.dma_init();
	if (Status != XST_SUCCESS) {
		xil_printf("Device Initiation Failed!\r\n");
		return XST_FAILURE;
	}

	Status = dma1.RecvPackets();
		if (Status != XST_SUCCESS) {
			xil_printf("Receiving Packets Failed!\r\n");
			return XST_FAILURE;
	}

	Status = dma1.WR2TxBuffer();
	if (Status != XST_SUCCESS) {
		xil_printf("Write Buffer Failed!\r\n");
		return XST_FAILURE;
	}

	Status = dma1.SendPackets();
	if (Status != XST_SUCCESS) {
		xil_printf("Sending Packets Failed!\r\n");
		return XST_FAILURE;
	}

	Status = dma1.CleanTxBuffer();
	if (Status != XST_SUCCESS) {
		xil_printf("Cleaning TxBuffer Failed!\r\n");
		return XST_FAILURE;
	}

	Status = dma1.RecvWait();
	if (Status != XST_SUCCESS) {
		xil_printf("Receiving Waits Failed!\r\n");
		return XST_FAILURE;
	}

	Status = dma1.CheckData();
	if (Status != XST_SUCCESS) {
		xil_printf("Checking Data Failed!\r\n");
		return XST_FAILURE;
	}

	Status = dma1.print_results();
	if (Status != XST_SUCCESS) {
		xil_printf("Printing results Failed!\r\n");
		return XST_FAILURE;
	}

	Status = dma1.CleanRxBuffer();
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


