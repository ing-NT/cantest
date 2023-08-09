#ifndef SOURCES_CAN_H_
#define SOURCES_CAN_H_
#include "hidef.h"
#include "derivative.h"

extern void Can0_Init(void);
struct Can_MsgType           /* 报文的结构体 */
{
    unsigned int id;         /* 帧ID */
    unsigned char RTR;       /* RTR:1为远程帧,0为数据帧 */
    unsigned char IDE;
    unsigned char data[8U];   /*  帧数据 */
    unsigned char len;       /* 数据长度 */
    unsigned char prty;      /* 优先级 */
};

extern Bool Can_Send(struct Can_MsgType msg);
extern Bool Can_Receive(struct Can_MsgType *msg);

#endif