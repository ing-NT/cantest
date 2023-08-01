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
static unsigned char send_data[8U] = {0x0aU, 0x01U, 0x0cU, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U};

void main(void)
{
	unsigned int a;
  	struct CAN_MSG msg_send,receive_msg;
 	//初始化
  	DisableInterrupts;
  	Pll_Init();
  	Rti_Init();
  	Ect_Init();
  	DDRC_DDRC4 = 1U;   //注意顺序不能和Can0_Init()调换
	PORTC_PC4 = 1U;
  	Can0_Init();
	//EnableInterrupts;

	//填写发送报文内容
  	msg_send.id = ID;
  	for (a = 0U; a < DATA_LEN_TX; a++)
  	{
  		msg_send.data[a] = send_data[a];
  	}
  	msg_send.len = DATA_LEN_TX;
	msg_send.RTR = 0U;
	msg_send.prty = 0U;

	for ( ; ; )
	{
		if(Can_Receive(&receive_msg))
		{
			Delay(4U);
	    	Can_Send(msg_send);
	    	Delay(8U);       //2s
	    }
	}
}
/*
	for ( ; ; ) {                   //测试中断
	  if (Receive_Interrupt_Result_Flag()) {
	    Can_Send(msg_send);
	    Delay_1Ms(8U);        //2s
	  }
	}
}
*/