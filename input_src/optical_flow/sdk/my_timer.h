
int RtcPsuSecondsIntrExample();

static int SetupInterruptSystem(XScuGic *IntcInstancePtr,
				XRtcPsu *RtcInstancePtr,
				u16 RtcIntrId);

void Handler(void *CallBackRef, u32 Event);

int ClearRtcPsu(void);
