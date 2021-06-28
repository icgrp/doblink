#include "typedefs.h"
#include "stream.h"
XRtcPsu RtcPsu;		/* Instance of the RTC Device */
XScuGic InterruptController;	/* Instance of the Interrupt Controller */
u32 Seconds = 0;


stream_inst stream(0, 0);


/**************************************************************************/
/**
*
* This function is the handler which performs processing to handle interrupt
* events from the device.  It is called from an interrupt context. so the
* amount of processing should be minimal.
*
* This handler provides an example of how to handle interrupt data for the
* device and is application specific.
*
* @param	CallBackRef contains a callback reference from the driver,
*		in this case it is the instance pointer for the XRtcPsu driver.
* @param	Event contains the specific kind of event that has occurred.
*
* @return	None.
*
* @note		None.
*
***************************************************************************/
void Handler(void *CallBackRef, u32 Event)
{
	Seconds++;
	//xil_printf("Seconds = %d\n", Seconds);
	/* A new second event */
	if (Event == XRTCPSU_EVENT_SECS_GEN) {
		unsigned data = 0;
		unsigned int read_exist = 0;
		unsigned int cnt = 0;
		xil_printf("timer launches\n");
		while(cnt <100){
			read_exist = stream.stream1_read(&data);
			if(read_exist == 1) { xil_printf("p2p: %d\n", data); }
			cnt++;
		}
		cnt = 0;
		while(cnt <100){
			read_exist = stream.stream2_read(&data);
			if(read_exist == 1) { xil_printf("data_redir: %d\n", data); }
			cnt++;
		}

		cnt = 0;
		while(cnt <100){
			read_exist = stream.stream3_read(&data);
			if(read_exist == 1) { xil_printf("rasterization: %d\n", data); }
			cnt++;
		}

		cnt = 0;
		while(cnt <100){
			read_exist = stream.stream4_read(&data);
			if(read_exist == 1) { xil_printf("zculling_top: %d\n", data); }
			cnt++;
		}

		cnt = 0;
		while(cnt <100){
			read_exist = stream.stream5_read(&data);
			if(read_exist == 1) { xil_printf("zculling_bot: %d\n", data); }
			cnt++;
		}

		cnt = 0;
		while(cnt <100){
			read_exist = stream.stream6_read(&data);
			if(read_exist == 1) { xil_printf("color_top: %d\n", data); }
			cnt++;
		}

		cnt = 0;
		while(cnt <100){
			read_exist = stream.stream7_read(&data);
			if(read_exist == 1) { xil_printf("color_bot: %d\n", data); }
			cnt++;
		}
	}
}


/*****************************************************************************/
/**
*
* This function sets up the interrupt system so interrupts can occur for the
* RTC. This function is application-specific. The user should modify this
* function to fit the application.
*
* @param	IntcInstancePtr is a pointer to the instance of the INTC.
* @param	RtcInstancePtr contains a pointer to the instance of the RTC
*		driver which is going to be connected to the interrupt
*		controller.
* @param	RtcIntrId is the interrupt Id and is typically
*		XPAR_<XRTCPSU_instance>_INTR value from xparameters.h.
*
* @return	XST_SUCCESS if successful, otherwise XST_FAILURE.
*
* @note		None.
*
****************************************************************************/
static int SetupInterruptSystem(XScuGic *IntcInstancePtr,
				XRtcPsu *RtcInstancePtr,
				u16 RtcIntrId)
{
	int Status;

#ifndef TESTAPP_GEN
	XScuGic_Config *IntcConfig; /* Config for interrupt controller */

	/* Initialize the interrupt controller driver */
	IntcConfig = XScuGic_LookupConfig(INTC_DEVICE_ID);
	if (NULL == IntcConfig) {
		return XST_FAILURE;
	}

	Status = XScuGic_CfgInitialize(IntcInstancePtr, IntcConfig,
					IntcConfig->CpuBaseAddress);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Connect the interrupt controller interrupt handler to the
	 * hardware interrupt handling logic in the processor.
	 */
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
				(Xil_ExceptionHandler) XScuGic_InterruptHandler,
				IntcInstancePtr);
#endif

	/*
	 * Connect a device driver handler that will be called when an
	 * interrupt for the device occurs, the device driver handler
	 * performs the specific interrupt processing for the device
	 */
	Status = XScuGic_Connect(IntcInstancePtr, RtcIntrId,
				  (Xil_ExceptionHandler) XRtcPsu_InterruptHandler,
				  (void *) RtcInstancePtr);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/* Enable the interrupt for the device */
	XScuGic_Enable(IntcInstancePtr, RtcIntrId);


#ifndef TESTAPP_GEN
	/* Enable interrupts */
	 Xil_ExceptionEnable();
#endif

	return XST_SUCCESS;
}


int RtcPsuSecondsIntrExample(void)
{
	XScuGic *IntcInstPtr;
	XRtcPsu *RtcInstPtr;
	u16 DeviceId;
	u16 RtcIntrId;

	IntcInstPtr = &InterruptController;
	RtcInstPtr = &RtcPsu;
	DeviceId = RTC_DEVICE_ID;
	RtcIntrId = RTC_SEC_INT_IRQ_ID;


	int Status;
	XRtcPsu_Config *Config;

	/*
	 * Initialize the RTC driver so that it's ready to use
	 * Look up the configuration in the config table, then initialize it.
	 */
	Config = XRtcPsu_LookupConfig(DeviceId);
	if (NULL == Config) {
		return XST_FAILURE;
	}

	Status = XRtcPsu_CfgInitialize(RtcInstPtr, Config, Config->BaseAddr);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/* Check hardware build */
	Status = XRtcPsu_SelfTest(RtcInstPtr);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Connect the RTC to the interrupt subsystem such that interrupts
	 * can occur. This function is application specific.
	 */
	Status = SetupInterruptSystem(IntcInstPtr, RtcInstPtr, RtcIntrId);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Setup the handlers for the RTC that will be called from the
	 * interrupt context when alarm and seconds interrupts are raised,
	 * specify a pointer to the RTC driver instance as the callback reference
	 * so the handlers are able to access the instance data
	 */
	XRtcPsu_SetHandler(RtcInstPtr, (XRtcPsu_Handler)Handler, RtcInstPtr);

	/*
	 * Enable the interrupt of the RTC device so interrupts will occur.
	 */
	XRtcPsu_SetInterruptMask(RtcInstPtr,XRTC_INT_EN_SECS_MASK);

	//while( Seconds != REPETATIONS);

	/*
	 * Disable the interrupt of the RTC device so interrupts will not occur.
	 */

	return XST_SUCCESS;
}

int ClearRtcPsu(void)
{
	XRtcPsu *RtcInstPtr;

	RtcInstPtr = &RtcPsu;


	XRtcPsu_ClearInterruptMask(RtcInstPtr,XRTC_INT_DIS_SECS_MASK);

	return XST_SUCCESS;
}
