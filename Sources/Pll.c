#include "Ect.h"

#include "hidef.h"
#include "derivative.h"
/*********************************************************/
/*                     ���໷��ʼ��                      */
/*********************************************************/

void Pll_Init(void)
{
    CLKSEL_PLLSEL = 0U;   /* �ڲ�����ʱ����Դ�ھ��� */
    PLLCTL_PLLON = 0U;    /* �ر�PLL */
    SYNR = 0x40U | 0x03U;
    REFDV = 0x80U |0x01U;
    POSTDIV = 0x00U;      /* PLLΪ64MHz */
    PLLCTL_PLLON = 1U;    /* ��PLL */

    _asm(nop);
    _asm(nop);                     /* �ȴ������������� */
    while (CRGFLG_LOCK == 0U)      /* ����CRGFLG�Ĵ�����LOCKλ��ȷ��PLL�Ƿ��ȶ� */
    {
    }                              /* LOCK==1�ȶ���LOCK==0���ȶ� */
    CLKSEL_PLLSEL = 1U;            /* �ڲ�����ʱ��ѡ��PLL��Ϊʱ��Դ */
}