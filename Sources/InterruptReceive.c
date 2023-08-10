/* #include "InterruptReceive.h" */
#include "Can0.h"

#include "hidef.h"
#include "derivative.h"
Bool SourcesInterrupt_ReceiveFlag = FALSE;

/* ����ʵʱ�ж� */
#pragma CODE_SEG __NEAR_SEG NON_BANKED       /* �жϺ������ڷǷ�ҳ���� */
void interrupt 7U Interrupt_Receive(void)
{
    struct Can0_MsgType can0_msg;
    if (Can0_Receive(&can0_msg))
    {
        if (can0_msg.id == 0x01U)
        {
            SourcesInterrupt_ReceiveFlag = TRUE;
        }
        else
        {
            SourcesInterrupt_ReceiveFlag = FALSE;
        }
    }
    CRGFLG_RTIF = 1U;                          /* Clr RTI interrupt flag */
}
#pragma CODE_SEG DEFAULT                      /* ������������Ĭ�������� */


Bool InterruptReceive_ResultFlag(void)
{
    return SourcesInterrupt_ReceiveFlag;
}