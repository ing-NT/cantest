#include "Pit.h"

#include "hidef.h"
#include "derivative.h"

void Pit_Init(void)
{
	PITCFLMT_PITE = 0U;      /* 关闭PIT */
	PITCE_PCE0 = 1U;         /* PIT通道使能寄存器中，PCE0通道使能 */
	PITMUX = 0x00U;          /* 通道0/1/2/3 使用时基0 */
	PITMTLD0 = 80U - 1U;
	PITLD0 = 400U - 1U;	     /* T = (PITMTLD+1)*(PITLD+1)/Fbus = 1ms */
	PITINTE_PINTE0 = 0x01U;   /* 开启PIT通道0的中断功能 */
	PITCFLMT_PITE = 1U;
}