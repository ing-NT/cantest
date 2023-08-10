/* #include "InterruptReceive.h" */
#include "Can0.h"

#include "hidef.h"
#include "derivative.h"
Bool Interrupt_ReceiveFlag = FALSE;

/* ����ʵʱ�ж� */
#pragma CODE_SEG __NEAR_SEG NON_BANKED       /* �жϺ������ڷǷ�ҳ���� */
void interrupt 7U Interrupt_Receive(void)
{
    struct Can0_MsgType can0_msg;
    if (Can0_Receive(&can0_msg))
    {
        if (can0_msg.id == 0x01U)
        {
            Interrupt_ReceiveFlag = TRUE;
        }
        else
        {
            Interrupt_ReceiveFlag = FALSE;
        }
    }
    CRGFLG_RTIF = 1U;                          /* Clr RTI interrupt flag */
}
#pragma CODE_SEG DEFAULT                      /* ������������Ĭ�������� */


Bool Interrupt_ReceiveResultFlag(void)
{
    return Interrupt_ReceiveFlag;
}