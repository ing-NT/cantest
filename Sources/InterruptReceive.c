//#include "InterruptReceive.h"
#include "Can.h"

#include "hidef.h"
#include "derivative.h"
Bool Can0_Receive_Successflag = FALSE;
struct Can_MsgType msg_get;
/*
#pragma CODE_SEG __NEAR_SEG NON_BANKED       //�жϺ������ڷǷ�ҳ����
void interrupt Interrupt_Receive(void)
{
    if (Can_Receive(&msg_get))
    {
        if (msg_get->id == 0x01)
        {
            Can0_Receive_Successflag = TRUE;
        }
        else
        {
            Can0_Receive_Successflag = FALSE;
        }
    }
}
#pragma CODE_SEG DEFAULT                      //������������Ĭ��������
*/

//����ʵʱ�ж�
#pragma CODE_SEG __NEAR_SEG NON_BANKED       //�жϺ������ڷǷ�ҳ����
void interrupt 7U Interrupt_Receive(void)
{
    if (Can_Receive(&msg_get))
    {
        if (msg_get.id == 0x01U)
        {
            Can0_Receive_Successflag = TRUE;
        }
        else
        {
            Can0_Receive_Successflag = FALSE;
        }
    }
    CRGFLG_RTIF = 1U;                          // Clr RTI interrupt flag
}
#pragma CODE_SEG DEFAULT                      //������������Ĭ��������


Bool Receive_Interrupt_Result_Flag(void)
{
    return Can0_Receive_Successflag;
}