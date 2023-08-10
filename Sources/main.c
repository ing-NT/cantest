#include <hidef.h>           /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include "Can0.h"
#include "Pll.h"
#include "Ect.h"
#include "Delay.h"
#include "Rti.h"
#include "InterruptReceive.h"

#define MSG_ID      0x01U
#define DATA_LEN_TX 8U

void main(void)
{
	unsigned int a;
	Bool main_ReceiveFlag = FALSE;
	static unsigned char Msg[8U] = {0x0aU, 0x01U, 0x0cU, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U};
  	struct Can0_MsgType can0_msg, msg;
 	/* 初始化 */
  	DisableInterrupts;
  	Pll_Init();
  	Rti_Init();
  	Ect_Init();
  	DDRC_DDRC4 = 1U;
	PORTC_PC4 = 1U;
  	Can0_Init();
	//EnableInterrupts;

	/* 发送报文 */
  	can0_msg.id = MSG_ID;
  	for (a = 0U; a < DATA_LEN_TX; a++)
  	{
  		can0_msg.data[a] = Msg[a];
  	}
  	can0_msg.len = DATA_LEN_TX;
	can0_msg.RTR = 0U;
	can0_msg.IDE = 0U;
	can0_msg.prty = 0U;

//	for ( ; ; )
//	{
//		if(Can0_Receive(&msg))
//		{
//			Delay(4U);
//	    	Can0_Send(can0_msg);
//	    	Delay(8U);       /* 2s */
//	    }
//	}
//}

	for ( ; ; )
	{
		main_ReceiveFlag = Interrupt_ReceiveResultFlag();
		if (main_ReceiveFlag)
	  	{
	    	Can0_Send(can0_msg);
	    	Delay(8U);
	  	}
	}
}
