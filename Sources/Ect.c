#include "Ect.h"

#include <hidef.h>
#include "derivative.h"

void Ect_Init(void)
{
    ECT_TSCR1_TFFCA = 1U;    //定时器标志位快速清除
    ECT_TSCR1_TEN = 1U;      //定时器使能，1：允许定时器正常工作；0：使主定时器不起作用(包括计时器)
    ECT_TIOS = 0xFFU;        //指定所有通道为输出比较方式
    ECT_TCTL1 = 0x00U;       //后四个通道设置为定时器与输出引脚断开
    ECT_TCTL2 = 0x00U;       //前四个通道设置为定时器与输出引脚断开
    ECT_DLYCT = 0x00U;       //延迟控制功能禁止
    ECT_ICOVW = 0x00U;       //对应的寄存器允许被覆盖，  1：对应存储器不允许覆盖
    ECT_ICSYS = 0x00U;       //禁止IC及PAC的保持寄存器
    ECT_TIE = 0x00U;         //禁止所有通道定时中断
    ECT_TSCR2 = 0x07U;       //预分频系数pr2-pr0:111,时钟周期为4us
    ECT_TFLG1 = 0xFFU;       //清除各IC/OC中断标志位
    ECT_TFLG2 = 0xFFU;       //清除自由定时器中断标志位
}