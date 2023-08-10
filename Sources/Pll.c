#include "Ect.h"

#include "hidef.h"
#include "derivative.h"
/*********************************************************/
/*                     锁相环初始化                      */
/*********************************************************/

void Pll_Init(void)
{
    CLKSEL_PLLSEL = 0U;   /* 内部总线时钟来源于晶振 */
    PLLCTL_PLLON = 0U;    /* 关闭PLL */
    SYNR = 0x40U | 0x03U;
    REFDV = 0x80U |0x01U;
    POSTDIV = 0x00U;      /* PLL为64MHz */
    PLLCTL_PLLON = 1U;    /* 打开PLL */

    _asm(nop);
    _asm(nop);                     /* 等待两个机器周期 */
    while (CRGFLG_LOCK == 0U)      /* 根据CRGFLG寄存器的LOCK位，确定PLL是否稳定 */
    {
    }                              /* LOCK==1稳定，LOCK==0不稳定 */
    CLKSEL_PLLSEL = 1U;            /* 内部总线时钟选择PLL作为时钟源 */
}