#include "Delay.h"

#include "hidef.h"
#include "derivative.h"

void Delay(unsigned int n)
{
    unsigned int i;
    for (i = 0U; i < n; i++)             //�ȴ�n��0.125s
    {
        ECT_TFLG1_C0F = 1U;              //�����־λ
        ECT_TC0 = ECT_TCNT + 31250U;     //��������Ƚ�ʱ��0.125s
        while (ECT_TFLG1_C0F == 0U)      //�ȴ���ֱ����������Ƚ��¼�
        {
        }
    }
}

 /*
 void Delay()
 {
    ECT_TFLG1_C0F = 1;              //�����־λ
    ECT_TC0 = ECT_TCNT + 31250;     //��������Ƚ�ʱ��0.125s
    while (ECT_TFLG1_C0F == 0)     //�ȴ���ֱ����������Ƚ��¼�
    {
    }
    ECT_TFLG1_C0F = 1;              //�����־λ
    ECT_TC0 = ECT_TCNT + 31250;     //��������Ƚ�ʱ��0.125s
    while (ECT_TFLG1_C0F == 0)
    {    //�ȴ���ֱ����������Ƚ��¼�
    }
    ECT_TFLG1_C0F = 1;              //�����־λ
    ECT_TC0 = ECT_TCNT + 31250;     //��������Ƚ�ʱ��0.125s
    while (ECT_TFLG1_C0F == 0)
    {                               //�ȴ���ֱ����������Ƚ��¼�
    }
    ECT_TFLG1_C0F = 1;              //�����־λ
    ECT_TC0 = ECT_TCNT + 31250;     //��������Ƚ�ʱ��0.125s
    while (ECT_TFLG1_C0F == 0)
    {                               //�ȴ���ֱ����������Ƚ��¼�
    }
}
*/