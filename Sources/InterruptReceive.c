/* #include "InterruptReceive.h" */
#include "Can.h"

#include "hidef.h"
#include "derivative.h"

/* 加入实时中断 */
#pragma CODE_SEG __NEAR_SEG NON_BANKED       /* 中断函数置于非分页区内 */
void interrupt 7U Interrupt_Receive(void)
{
    Bool Can0_ReceiveFlag = FALSE;
    struct Can_MsgType Can_msg;
    if (Can_Receive(&Can_msg))
    {
        if (Can_msg.id == 0x01U)
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


Bool Receive_Interrupt_Result_Flag(void)
{
    return Can0_ReceiveFlag;
}