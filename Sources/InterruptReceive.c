/* #include "InterruptReceive.h" */
#include "Can.h"

#include "hidef.h"
#include "derivative.h"

/* ����ʵʱ�ж� */
#pragma CODE_SEG __NEAR_SEG NON_BANKED       /* �жϺ������ڷǷ�ҳ���� */
void interrupt 7U Interrupt_Receive(void)
{
    Bool Can0_ReceiveFlag = FALSE;
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
#pragma CODE_SEG DEFAULT                      /* ������������Ĭ�������� */


Bool Receive_Interrupt_Result_Flag(void)
{
    return Can0_ReceiveFlag;
}