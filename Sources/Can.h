#ifndef SOURCES_CAN_H_
#define SOURCES_CAN_H_
#include "hidef.h"
#include "derivative.h"

extern void Can0_Init(void);
struct Can_MsgType           /* ���ĵĽṹ�� */
{
    unsigned int id;         /* ֡ID */
    unsigned char RTR;       /* RTR:1ΪԶ��֡,0Ϊ����֡ */
    unsigned char IDE;
    unsigned char data[8U];   /*  ֡���� */
    unsigned char len;       /* ���ݳ��� */
    unsigned char prty;      /* ���ȼ� */
};

extern Bool Can_Send(struct Can_MsgType msg);
extern Bool Can_Receive(struct Can_MsgType *msg);

#endif