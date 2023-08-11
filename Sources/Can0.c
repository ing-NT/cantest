#include "Can0.h"

#include "hidef.h"
#include "derivative.h"

/*********************************************************/
/*                     CAN0初始化                        */
/*********************************************************/
void Can0_Init(void)
{
    if (CAN0CTL0_INITRQ == 0U)          /* 查询是否进入初始化状态 */
    {
        CAN0CTL0_INITRQ = 1U;             /* 进入初始化状态 */
    }
    while (CAN0CTL1_INITAK == 0U)      /* 等待进入初始化状态 */
    {
    }

    CAN0BTR0_SJW = 0U;                  /* 设置同步跳转宽度 */
    CAN0BTR0_BRP = 7U;                  /* 设置波特率,250Kbit/s */
    CAN0BTR1 = 0x1CU;                   /* 设置时段1和时段2的Tq个数 ,总线频率为32MHz */

    /* 关闭滤波器 */
    CAN0IDMR0 = 0xFFU;
    CAN0IDMR1 = 0xFFU;
    CAN0IDMR2 = 0xFFU;
    CAN0IDMR3 = 0xFFU;
    CAN0IDMR4 = 0xFFU;
    CAN0IDMR5 = 0xFFU;
    CAN0IDMR6 = 0xFFU;
    CAN0IDMR7 = 0xFFU;

    CAN0CTL1 = 0xC0U;                   /* 使能MSCAN模块,设置为一般运行 */
    CAN0CTL0 = 0x00U;                   /* 返回正常运行模式 */
    while (CAN0CTL1_INITAK)             /* 等待回到正常运行模模式 */
    {
    }
    while (CAN0CTL0_SYNCH == 0U)        /* 等待MSCAN与CAN总线时钟同步 */
    {
    }
    CAN0RFLG_RXF = 1U;                  /* 清空消息接受缓冲器 */
    CAN0RIER_RXFIE = 1U;                /* 使能接收中断 */
}

/*********************************************************/
/*                     CAN0发送                          */
/*********************************************************/
Bool Can0_Send(struct Can0_MsgType can0_msg)
{
    Bool SourcesCan0_SendResultFlag = FALSE;
    unsigned int send_buf, sp;
    if (can0_msg.len > 8U || CAN0CTL0_SYNCH == 0U)  /* 检查数据长度 || 检查总线时钟 */
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
        {                           /* 寻找空闲的缓冲器 */
            CAN0TBSEL = CAN0TFLG;
            send_buf = CAN0TBSEL;
        }
        while (!send_buf);

        if (can0_msg.IDE == 0U)              /* 检测can协议是标准/扩展模式 0：标准  1:扩展 */
        {
            CAN0TXIDR0 = (unsigned char)(can0_msg.id >> 3U);   /* 写入标识符 */
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
        {                                             /* 判断RTR,1:远程帧 0：数据帧 */
            CAN0TXIDR1 |= 0x10U;
        }
        for (sp = 0U; sp < can0_msg.len; sp++)             /* 写入数据 */
        {
            *((&CAN0TXDSR0) + sp) = can0_msg.data[sp];
        }
        CAN0TXDLR = can0_msg.len;     /* 写入数据长度 */
        CAN0TXTBPR = can0_msg.prty;   /* 写入优先级 */
        CAN0TFLG = send_buf;     /* 清除TXx标志(缓冲器准备发送) */
        SourcesCan0_SendResultFlag = TRUE;
    }
    return SourcesCan0_SendResultFlag;
}

/*********************************************************/
/*                     CAN0接收                          */
/*********************************************************/
Bool Can0_Receive(struct Can0_MsgType *can0_msg)
{
    unsigned int sp2;
    Bool SourcesCan0_ReceiveResultFlag = FALSE;
    if (!CAN0RFLG_RXF)             /* 检测接收标志 */
    {
        SourcesCan0_ReceiveResultFlag = FALSE;
    }
    else
    {
        if (!CAN0RXIDR1_IDE)              /* 检测can协议是标准/扩展模式 0：标准  1:扩展 */
        {
            can0_msg->id = (unsigned int)(CAN0RXIDR0 << 3U) |       /* 读标识符 */
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
        can0_msg->len = CAN0RXDLR;                             /* 读取数据长度 */
        for (sp2 = 0U; sp2 < can0_msg->len; sp2++)             /* 读取数据 */
        {
            can0_msg->data[sp2] = *((&CAN0RXDSR0) + sp2);
        }
        CAN0RFLG = 0x01U;     /* 清除RXF标志(缓冲器准备接收) */
        SourcesCan0_ReceiveResultFlag = TRUE;
    }
    return SourcesCan0_ReceiveResultFlag;
}