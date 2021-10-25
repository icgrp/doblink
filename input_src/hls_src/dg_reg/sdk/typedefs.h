/******************** Constant Definitions **********************************/

/*********************** TEMPORARY ******************************************/
/*
 * Device hardware build related constants.
 */
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

#ifndef DDR_BASE_ADDR
#warning CHECK FOR THE VALID DDR ADDRESS IN XPARAMETERS.H, \
		DEFAULT SET TO 0x01000000
#define MEM_BASE_ADDR       0x01000000
#else
#define MEM_BASE_ADDR      (DDR_BASE_ADDR + 0x1000000)
#endif


// 8 MB for tx ring buffer
#define TX_BD_SPACE_BASE	(MEM_BASE_ADDR)
#define TX_BD_SPACE_HIGH	(MEM_BASE_ADDR + 0x007FFFFF)

// 8 MB for rx ring buffer
#define RX_BD_SPACE_BASE	(MEM_BASE_ADDR + 0x00800000)
#define RX_BD_SPACE_HIGH	(MEM_BASE_ADDR + 0x00FFFFFF)

// 240 MB for tx_buffer
#define TX_BUFFER_BASE		(MEM_BASE_ADDR + 0x01000000)

// 240 MB for RX buffer
#define RX_BUFFER_BASE		(MEM_BASE_ADDR + 0x10000000)
#define RX_BUFFER_HIGH		(MEM_BASE_ADDR + 0x1EFFFFFF)


#define MAX_PKT_LEN		0x2710
//#define NUMBER_OF_PACKETS 	0x400
#define NUMBER_OF_PACKETS 	0x40

#define MAX_PKT_LEN_RX		0x1F40
//#define NUMBER_OF_PACKETS 	0x400
#define NUMBER_OF_PACKETS_RX 	0x5


#define TEST_START_VALUE	0xC

/**************************** Type Definitions *******************************/


/***************** Macros (Inline Functions) Definitions *********************/


/************************** Function Prototypes ******************************/
#if defined(XPAR_UARTNS550_0_BASEADDR)
static void Uart550_Setup(void);
#endif



