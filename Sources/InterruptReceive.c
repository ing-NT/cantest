/* #include "InterruptReceive.h" */
#include "Can0.h"

#include "hidef.h"
#include "derivative.h"
Bool SOURCESINTERRUPT_RECEIVEFLAG = FALSE;

/* 加入PIT中断 */
#pragma CODE_SEG __NEAR_SEG NON_BANKED       /* 中断函数置于非分页区内 */
void interrupt VectorNumber_Vpit0 Interrupt_Receive(void)
{
    struct Can0_MsgType can0_msg;
    if (Can0_Receive(&can0_msg))  //
    {
        if (can0_msg.id == 0x01U)
        {
            SOURCESINTERRUPT_RECEIVEFLAG = TRUE;
        }
        else
        {
            SOURCESINTERRUPT_RECEIVEFLAG = FALSE;
        }
    }
    if (PITTF_PTF0 == 1U)
    {
        PITTF_PTF0 = 1U;
    }
}
#pragma CODE_SEG DEFAULT                      /* 后续代码置于默认区域内 */



/* 加入实时中断 */
//#pragma CODE_SEG __NEAR_SEG NON_BANKED       /* 中断函数置于非分页区内 */
//void interrupt 7U Interrupt_Receive(void)
//{
//    struct Can0_MsgType can0_msg;
//    if (Can0_Receive(&can0_msg))
//    {
//        if (can0_msg.id == 0x01U)
//        {
//            SOURCESINTERRUPT_RECEIVEFLAG = TRUE;
//        }
//        else
//        {
//            SOURCESINTERRUPT_RECEIVEFLAG = FALSE;
//        }
//    }
//    CRGFLG_RTIF = 1U;                          /* Clr RTI interrupt flag */
//}
//#pragma CODE_SEG DEFAULT                      /* 后续代码置于默认区域内 */


Bool InterruptReceive_ResultFlag(void)
{
    return SOURCESINTERRUPT_RECEIVEFLAG;
}