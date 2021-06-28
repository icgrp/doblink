#include "xrtcpsu.h"		/* RTCPSU device driver */
#ifdef __cplusplus
#endif


#include "xscugic.h"		/* Interrupt controller device driver */
#include "xil_exception.h"
#include "xil_printf.h"


#define RTC_DEVICE_ID         XPAR_XRTCPSU_0_DEVICE_ID
#define INTC_DEVICE_ID			XPAR_SCUGIC_SINGLE_DEVICE_ID
#define RTC_SEC_INT_IRQ_ID	XPAR_XRTCPSU_SECONDS_INTR

#define REPETATIONS 10

#define DMA_BASE_ADDR       XPAR_AXIDMA_0_BASEADDR
#define DMA_DEV_ID          XPAR_AXIDMA_0_DEVICE_ID

#ifdef XPAR_AXI_7SDDR_0_S_AXI_BASEADDR
#define DDR_BASE_ADDR       XPAR_AXI_7SDDR_0_S_AXI_BASEADDR
#elif XPAR_MIG7SERIES_0_BASEADDR
#define DDR_BASE_ADDR       XPAR_MIG7SERIES_0_BASEADDR
#elif XPAR_MIG_0_BASEADDR
#define DDR_BASE_ADDR       XPAR_MIG_0_BASEADDR
#elif XPAR_PSU_DDR_0_S_AXI_BASEADDR
#define DDR_BASE_ADDR       XPAR_PSU_DDR_0_S_AXI_BASEADDR
#endif

/******************** Constant Definitions **********************************/

/*********************** TEMPORARY ******************************************/
/*
 * Device hardware build related constants.
 */
//#define DMA_BASE_ADDR       XPAR_AXIDMA_0_BASEADDR
#define DMA_DEV0_ID          XPAR_AXIDMA_0_DEVICE_ID
#define DMA_DEV1_ID          XPAR_AXIDMA_1_DEVICE_ID
#define DMA_DEV2_ID          XPAR_AXIDMA_2_DEVICE_ID


#ifdef XPAR_AXI_7SDDR_0_S_AXI_BASEADDR
#define DDR_BASE_ADDR       XPAR_AXI_7SDDR_0_S_AXI_BASEADDR
#elif XPAR_MIG7SERIES_0_BASEADDR
#define DDR_BASE_ADDR       XPAR_MIG7SERIES_0_BASEADDR
#elif XPAR_MIG_0_BASEADDR
#define DDR_BASE_ADDR       XPAR_MIG_0_BASEADDR
#elif XPAR_PSU_DDR_0_S_AXI_BASEADDR
#define DDR_BASE_ADDR       XPAR_PSU_DDR_0_S_AXI_BASEADDR
#endif

#ifndef DDR_BASE_ADDR
#warning CHECK FOR THE VALID DDR ADDRESS IN XPARAMETERS.H, \
		DEFAULT SET TO 0x01000000
#define MEM_BASE_ADDR       0x01000000
#else
#define MEM_BASE_ADDR      (DDR_BASE_ADDR + 0x1000000)
#endif


// 8 MB for tx0 ring buffer
#define TX0_BD_SPACE_BASE	(MEM_BASE_ADDR)
#define TX0_BD_SPACE_HIGH	(TX0_BD_SPACE_BASE + 0x007FFFFF)

// 8 MB for rx0 ring buffer
#define RX0_BD_SPACE_BASE	(TX0_BD_SPACE_BASE + 0x00800000)
#define RX0_BD_SPACE_HIGH	(RX0_BD_SPACE_BASE + 0x007FFFFF)

// 8 MB for rx1 ring buffer
#define TX1_BD_SPACE_BASE	(RX0_BD_SPACE_BASE + 0x00800000)
#define TX1_BD_SPACE_HIGH	(TX1_BD_SPACE_BASE + 0x007FFFFF)

// 8 MB for rx1 ring buffer
#define RX1_BD_SPACE_BASE	(TX1_BD_SPACE_BASE + 0x00800000)
#define RX1_BD_SPACE_HIGH	(RX1_BD_SPACE_BASE + 0x007FFFFF)


// 128 MB for tx_buffer
#define TX0_BUFFER_BASE		(RX1_BD_SPACE_BASE + 0x00800000)

// 128 MB for rx buffer
#define RX0_BUFFER_BASE		(TX0_BUFFER_BASE   + 0x08000000)

// 256 MB for tx_buffer
#define TX1_BUFFER_BASE		(RX0_BUFFER_BASE   + 0x10000000)

// 128 MB for rx buffer
#define RX1_BUFFER_BASE		(TX1_BUFFER_BASE   + 0x08000000)


//128 KB
#define MAX_PKT_LEN0			0x2000
#define NUMBER_OF_PACKETS0 		0x1

//128 KB
#define MAX_PKT_LEN_RX0			0x2000
#define NUMBER_OF_PACKETS_RX0 		0x1


//128 KB
#define MAX_PKT_LEN1			0x2000
#define NUMBER_OF_PACKETS1 		172

//128 KB
#define MAX_PKT_LEN_RX1			0x2000
#define NUMBER_OF_PACKETS_RX1 	0x100


#define TEST_START_VALUE	0xC

/**************************** Type Definitions *******************************/


/***************** Macros (Inline Functions) Definitions *********************/


/************************** Function Prototypes ******************************/
#if defined(XPAR_UARTNS550_0_BASEADDR)
static void Uart550_Setup(void);
#endif



