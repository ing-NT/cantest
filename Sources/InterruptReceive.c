/* #include "InterruptReceive.h" */
#include "Can0.h"

#include "hidef.h"
#include "derivative.h"
Bool SOURCESINTERRUPT_RECEIVEFLAG = FALSE;

/* ����PIT�ж� */
#pragma CODE_SEG __NEAR_SEG NON_BANKED       /* �жϺ������ڷǷ�ҳ���� */
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
#pragma CODE_SEG DEFAULT                      /* ������������Ĭ�������� */



/* ����ʵʱ�ж� */
//#pragma CODE_SEG __NEAR_SEG NON_BANKED       /* �жϺ������ڷǷ�ҳ���� */
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
//#pragma CODE_SEG DEFAULT                      /* ������������Ĭ�������� */


Bool InterruptReceive_ResultFlag(void)
{
    return SOURCESINTERRUPT_RECEIVEFLAG;
}