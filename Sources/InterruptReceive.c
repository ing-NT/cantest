//#include "InterruptReceive.h"
#include "Can.h"

#include "hidef.h"
#include "derivative.h"
Bool Can0_Receive_successflag;
struct CAN_MSG msg_get;
/*
#pragma CODE_SEG __NEAR_SEG NON_BANKED       //中断函数置于非分页区内
void interrupt Interrupt_Receive(void) {
  if (Can_Receive(&msg_get)) {
    if (msg_get->id == 0x01) {
      Can0_Receive_successflag = TRUE;
    } else {
        Can0_Receive_successflag = FALSE;
      }
  }
}
#pragma CODE_SEG DEFAULT                      //后续代码置于默认区域内
*/

//加入实时中断
#pragma CODE_SEG __NEAR_SEG NON_BANKED       //中断函数置于非分页区内
void interrupt 7U Interrupt_Receive(void)
{
    if (Can_Receive(&msg_get))
    {
        if (msg_get.id == 0x01U)
        {
            Can0_Receive_successflag = TRUE;
        } else
        {
        Can0_Receive_successflag = FALSE;
        }
    }
    CRGFLG_RTIF = 1U;                          // Clr RTI interrupt flag
}
#pragma CODE_SEG DEFAULT                      //后续代码置于默认区域内


Bool Receive_Interrupt_Result_Flag(void)
{
    return Can0_Receive_successflag;
}