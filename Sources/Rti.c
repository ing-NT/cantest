#include "Rti.h"

#include "hidef.h"
#include "derivative.h"

void Rti_Init(void) {
  CRGINT_RTIE = 1U;
  //RTICTL���㣺T=(RTR[3:0]+1)*2^(RTR[6:4]+9)/osc clock ��PLL�����޹�
  RTICTL = 0xb3U;   //0.01s
}