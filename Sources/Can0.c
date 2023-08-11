#include "Can0.h"

#include "hidef.h"
#include "derivative.h"

/*********************************************************/
/*                     CAN0��ʼ��                        */
/*********************************************************/
void Can0_Init(void)
{
    if (CAN0CTL0_INITRQ == 0U)          /* ��ѯ�Ƿ�����ʼ��״̬ */
    {
        CAN0CTL0_INITRQ = 1U;             /* �����ʼ��״̬ */
    }
    while (CAN0CTL1_INITAK == 0U)      /* �ȴ������ʼ��״̬ */
    {
    }

    CAN0BTR0_SJW = 0U;                  /* ����ͬ����ת��� */
    CAN0BTR0_BRP = 7U;                  /* ���ò�����,250Kbit/s */
    CAN0BTR1 = 0x1CU;                   /* ����ʱ��1��ʱ��2��Tq���� ,����Ƶ��Ϊ32MHz */

    /* �ر��˲��� */
    CAN0IDMR0 = 0xFFU;
    CAN0IDMR1 = 0xFFU;
    CAN0IDMR2 = 0xFFU;
    CAN0IDMR3 = 0xFFU;
    CAN0IDMR4 = 0xFFU;
    CAN0IDMR5 = 0xFFU;
    CAN0IDMR6 = 0xFFU;
    CAN0IDMR7 = 0xFFU;

    CAN0CTL1 = 0xC0U;                   /* ʹ��MSCANģ��,����Ϊһ������ */
    CAN0CTL0 = 0x00U;                   /* ������������ģʽ */
    while (CAN0CTL1_INITAK)             /* �ȴ��ص���������ģģʽ */
    {
    }
    while (CAN0CTL0_SYNCH == 0U)        /* �ȴ�MSCAN��CAN����ʱ��ͬ�� */
    {
    }
    CAN0RFLG_RXF = 1U;                  /* �����Ϣ���ܻ����� */
    CAN0RIER_RXFIE = 1U;                /* ʹ�ܽ����ж� */
}

/*********************************************************/
/*                     CAN0����                          */
/*********************************************************/
Bool Can0_Send(struct Can0_MsgType can0_msg)
{
    Bool SourcesCan0_SendResultFlag = FALSE;
    unsigned int send_buf, sp;
    if (can0_msg.len > 8U || CAN0CTL0_SYNCH == 0U)  /* ������ݳ��� || �������ʱ�� */
    {
        SourcesCan0_SendResultFlag = FALSE;
    }
    /*
    if (CAN0CTL0_SYNCH == 0U)
    //{
    //    SourcesCan0_SendResultFlag = FALSE;
    //}
    */
    else
    {
        send_buf = 0U;
        do
        {                           /* Ѱ�ҿ��еĻ����� */
            CAN0TBSEL = CAN0TFLG;
            send_buf = CAN0TBSEL;
        }
        while (!send_buf);

        if (can0_msg.IDE == 0U)              /* ���canЭ���Ǳ�׼/��չģʽ 0����׼  1:��չ */
        {
            CAN0TXIDR0 = (unsigned char)(can0_msg.id >> 3U);   /* д���ʶ�� */
            CAN0TXIDR1 = (unsigned char)(can0_msg.id << 5U);
        }
        else
        {
            CAN0TXIDR0 = (unsigned char)(can0_msg.id >> 21U);
            CAN0TXIDR1 = (unsigned char)(((can0_msg.id >> 15U) & 0x07U) | ((can0_msg.id) & 0xE0U) | 0x18U);
            CAN0TXIDR2 = (unsigned char)(can0_msg.id >> 7U);
            CAN0TXIDR3 = (unsigned char)(can0_msg.id << 1U);
        }
        if (can0_msg.RTR)
        {                                             /* �ж�RTR,1:Զ��֡ 0������֡ */
            CAN0TXIDR1 |= 0x10U;
        }
        for (sp = 0U; sp < can0_msg.len; sp++)             /* д������ */
        {
            *((&CAN0TXDSR0) + sp) = can0_msg.data[sp];
        }
        CAN0TXDLR = can0_msg.len;     /* д�����ݳ��� */
        CAN0TXTBPR = can0_msg.prty;   /* д�����ȼ� */
        CAN0TFLG = send_buf;     /* ���TXx��־(������׼������) */
        SourcesCan0_SendResultFlag = TRUE;
    }
    return SourcesCan0_SendResultFlag;
}

/*********************************************************/
/*                     CAN0����                          */
/*********************************************************/
Bool Can0_Receive(struct Can0_MsgType *can0_msg)
{
    unsigned int sp2;
    Bool SourcesCan0_ReceiveResultFlag = FALSE;
    if (!CAN0RFLG_RXF)             /* �����ձ�־ */
    {
        SourcesCan0_ReceiveResultFlag = FALSE;
    }
    else
    {
        if (!CAN0RXIDR1_IDE)              /* ���canЭ���Ǳ�׼/��չģʽ 0����׼  1:��չ */
        {
            can0_msg->id = (unsigned int)(CAN0RXIDR0 << 3U) |       /* ����ʶ�� */
                          (unsigned char)(CAN0RXIDR1 >> 5U);
        }
        else
        {
            can0_msg->id = (((unsigned long)CAN0RXIDR0) << 21U) | ((unsigned long)(CAN0RXIDR1 & 0xE0U) << 13U) |
                          ((unsigned long)(CAN0RXIDR1 & 0x07U) << 15U) | (((unsigned long)CAN0RXIDR2) << 7U) |
                          ((unsigned long)(CAN0RXIDR3 & 0xFEU) >> 1U);
        }
        if (CAN0RXIDR1 & 0x10U)
        {
            can0_msg->RTR = TRUE;
        }
        else
        {
            can0_msg->RTR = FALSE;
        }
        can0_msg->len = CAN0RXDLR;                             /* ��ȡ���ݳ��� */
        for (sp2 = 0U; sp2 < can0_msg->len; sp2++)             /* ��ȡ���� */
        {
            can0_msg->data[sp2] = *((&CAN0RXDSR0) + sp2);
        }
        CAN0RFLG = 0x01U;     /* ���RXF��־(������׼������) */
        SourcesCan0_ReceiveResultFlag = TRUE;
    }
    return SourcesCan0_ReceiveResultFlag;
}