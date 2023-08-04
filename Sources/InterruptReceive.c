/* #include "InterruptReceive.h" */
#include "Can.h"

#include "hidef.h"
#include "derivative.h"
Bool Can0_ReceiveFlag = FALSE;

/* 加入实时中断 */
#pragma CODE_SEG __NEAR_SEG NON_BANKED       /* 中断函数置于非分页区内 */
void interrupt 7U Interrupt_Receive(void)
{
    struct Can_MsgType can_msg;
    if (Can_Receive(&can_msg))
    {
        if (can_msg.id == 0x01U)
        {
            Can0_ReceiveFlag = TRUE;
        }
        else
        {
            Can0_ReceiveFlag = FALSE;
        }
    }
    CRGFLG_RTIF = 1U;                          /* Clr RTI interrupt flag */
}
#pragma CODE_SEG DEFAULT                      /* 后续代码置于默认区域内 */


Bool Receive_InterruptResultFlag(void)
{
    return Can0_ReceiveFlag;
}