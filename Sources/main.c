#include <hidef.h>           /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include "Can.h"
#include "Pll.h"
#include "Ect.h"
#include "Delay.h"
#include "Rti.h"
#include "InterruptReceive.h"

#define ID          0x01U
#define DATA_LEN_TX 8U

void main(void)
{
	unsigned int a;
	static unsigned char Send_Data[8U] = {0x0aU, 0x01U, 0x0cU, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U};
  	struct Can_MsgType msg_for_send, msg_for_receive;
 	/* ³õÊ¼»¯ */
  	DisableInterrupts;
  	Pll_Init();
  	Rti_Init();
  	Ect_Init();
  	DDRC_DDRC4 = 1U;   /* ×¢ÒâË³Ðò²»ÄÜºÍCan0_Init()µ÷»» */
	PORTC_PC4 = 1U;
  	Can0_Init();
	/* EnableInterrupts; */

	/* ÌîÐ´·¢ËÍ±¨ÎÄÄÚÈÝ */
  	msg_for_send.id = ID;
  	for (a = 0U; a < DATA_LEN_TX; a++)
  	{
  		msg_for_send.data[a] = Send_Data[a];
  	}
  	msg_for_send.len = DATA_LEN_TX;
	msg_for_send.RTR = 0U;
	msg_for_send.prty = 0U;

	for ( ; ; )
	{
		if(Can_Receive(&msg_for_receive))
		{
			Delay(4U);
	    	Can_Send(msg_for_send);
	    	Delay(8U);       /* 2s */
	    }
	}
}
/*
	for ( ; ; ) {
	  if (Receive_Interrupt_Result_Flag()) {
	    Can_Send(msg_for_send);
	    Delay_1Ms(8U);
	  }
	}
}
*/