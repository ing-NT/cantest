#include "Ect.h"

#include <hidef.h>
#include "derivative.h"

void Ect_Init(void)
{
    ECT_TSCR1_TFFCA = 1U;    //��ʱ����־λ�������
    ECT_TSCR1_TEN = 1U;      //��ʱ��ʹ�ܣ�1������ʱ������������0��ʹ����ʱ����������(������ʱ��)
    ECT_TIOS = 0xFFU;        //ָ������ͨ��Ϊ����ȽϷ�ʽ
    ECT_TCTL1 = 0x00U;       //���ĸ�ͨ������Ϊ��ʱ����������ŶϿ�
    ECT_TCTL2 = 0x00U;       //ǰ�ĸ�ͨ������Ϊ��ʱ����������ŶϿ�
    ECT_DLYCT = 0x00U;       //�ӳٿ��ƹ��ܽ�ֹ
    ECT_ICOVW = 0x00U;       //��Ӧ�ļĴ����������ǣ�  1����Ӧ�洢����������
    ECT_ICSYS = 0x00U;       //��ֹIC��PAC�ı��ּĴ���
    ECT_TIE = 0x00U;         //��ֹ����ͨ����ʱ�ж�
    ECT_TSCR2 = 0x07U;       //Ԥ��Ƶϵ��pr2-pr0:111,ʱ������Ϊ4us
    ECT_TFLG1 = 0xFFU;       //�����IC/OC�жϱ�־λ
    ECT_TFLG2 = 0xFFU;       //������ɶ�ʱ���жϱ�־λ
}