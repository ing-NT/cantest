#include "Delay.h"

#include "hidef.h"
#include "derivative.h"

void Delay(unsigned int n)
{
    unsigned int i;
    for (i = 0U; i < n; i++)             //等待n个0.125s
    {
        ECT_TFLG1_C0F = 1U;              //清除标志位
        ECT_TC0 = ECT_TCNT + 31250U;     //设置输出比较时间0.125s
        while (ECT_TFLG1_C0F == 0U)      //等待，直到发生输出比较事件
        {
        }
    }
}

 /*
 void Delay()
 {
    ECT_TFLG1_C0F = 1;              //清除标志位
    ECT_TC0 = ECT_TCNT + 31250;     //设置输出比较时间0.125s
    while (ECT_TFLG1_C0F == 0)     //等待，直到发生输出比较事件
    {
    }
    ECT_TFLG1_C0F = 1;              //清除标志位
    ECT_TC0 = ECT_TCNT + 31250;     //设置输出比较时间0.125s
    while (ECT_TFLG1_C0F == 0)
    {    //等待，直到发生输出比较事件
    }
    ECT_TFLG1_C0F = 1;              //清除标志位
    ECT_TC0 = ECT_TCNT + 31250;     //设置输出比较时间0.125s
    while (ECT_TFLG1_C0F == 0)
    {                               //等待，直到发生输出比较事件
    }
    ECT_TFLG1_C0F = 1;              //清除标志位
    ECT_TC0 = ECT_TCNT + 31250;     //设置输出比较时间0.125s
    while (ECT_TFLG1_C0F == 0)
    {                               //等待，直到发生输出比较事件
    }
}
*/