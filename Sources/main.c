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
	Bool Receive_Flag = FALSE;
	static unsigned char Msg[8U] = {0x0aU, 0x01U, 0x0cU, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U};
  	struct Can_MsgType Can_msg;
 	/* 初始化 */
  	DisableInterrupts;
  	Pll_Init();
  	Rti_Init();
  	Ect_Init();
  	DDRC_DDRC4 = 1U;
	PORTC_PC4 = 1U;
  	Can0_Init();
	EnableInterrupts;

	/* 发送报文 */
  	Can_msg.id = ID;
  	for (a = 0U; a < DATA_LEN_TX; a++)
  	{
  		Can_msg.data[a] = Msg[a];
  	}
  	Can_msg.len = DATA_LEN_TX;
	Can_msg.RTR = 0U;
	Can_msg.prty = 0U;

//	for ( ; ; )
//	{
//		if(Can_Receive(&msg))
//		{
//			Delay(4U);
//	    	Can_Send(Can_msg);
//	    	Delay(8U);       /* 2s */
//	    }
//	}
//}
	for ( ; ; )
	{
		Receive_Flag = Receive_Interrupt_Result_Flag();
		if (Receive_Flag)
	  	{
	    	Can_Send(Can_msg);
	    	Delay(8U);
	  	}
	}
}
