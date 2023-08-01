#include "Can.h"

#include "hidef.h"
#include "derivative.h"

/*********************************************************/
/*                     CAN0��ʼ��                        */
/*********************************************************/
void Can0_Init(void)
{
    if (CAN0CTL0_INITRQ == 0U) {        //��ѯ�Ƿ�����ʼ��״̬
    CAN0CTL0_INITRQ = 1U;             //�����ʼ��״̬
    }
    while (CAN0CTL1_INITAK == 0U);      //�ȴ������ʼ��״̬

    CAN0BTR0_SJW = 0U;                  //����ͬ����ת���
    CAN0BTR0_BRP = 7U;                  //���ò�����,250Kbit/s
    CAN0BTR1 = 0x1cU;                   //����ʱ��1��ʱ��2��Tq���� ,����Ƶ��Ϊ32MHz

    //�ر��˲���
    CAN0IDMR0 = 0xFFU;
    CAN0IDMR1 = 0xFFU;
    CAN0IDMR2 = 0xFFU;
    CAN0IDMR3 = 0xFFU;
    CAN0IDMR4 = 0xFFU;
    CAN0IDMR5 = 0xFFU;
    CAN0IDMR6 = 0xFFU;
    CAN0IDMR7 = 0xFFU;

    CAN0CTL1 = 0xc0U;                   //ʹ��MSCANģ��,����Ϊһ������
    CAN0CTL0 = 0x00U;                   //������������ģʽ
    while (CAN0CTL1_INITAK) {           //�ȴ��ص���������ģģʽ
    }
    while (CAN0CTL0_SYNCH == 0U) {      // �ȴ�MSCAN��CAN����ʱ��ͬ��
    }
    CAN0RFLG_RXF = 1U;                  //�����Ϣ���ܻ�����    CAN4RFLG_RXF = 1
    CAN0RIER_RXFIE = 1U;                //ʹ�ܽ����ж�
}

/*********************************************************/
/*                     CAN0����                          */
/*********************************************************/
Bool Can_Send(struct CAN_MSG msg)
{
    unsigned int send_buf,sp;
    if (msg.len > 8U)           //������ݳ���
    {
        return FALSE;
    }
    if (CAN0CTL0_SYNCH == 0U)   //�������ʱ��
    {
        return FALSE;
    }
    send_buf = 0U;
    do
    {                           //Ѱ�ҿ��еĻ�����
        CAN0TBSEL = CAN0TFLG;
        send_buf = CAN0TBSEL;
    }
    while (!send_buf);

    CAN0TXIDR0 = (unsigned char)(msg.id >> 3U);   //д���ʶ��
    CAN0TXIDR1 = (unsigned char)(msg.id << 5U);
    if (msg.RTR)
    {                                             //�ж�RTR,1:Զ��֡ 0������֡
    CAN0TXIDR1 |= 0x10U;
    }
    for (sp = 0U; sp < msg.len; sp++)             //д������
    {
    *((&CAN0TXDSR0) + sp) = msg.data[sp];
    }
    CAN0TXDLR = msg.len;     //д�����ݳ���
    CAN0TXTBPR = msg.prty;   //д�����ȼ�
    CAN0TFLG = send_buf;     //��TXx��־(������׼������)
    return TRUE;
}


/*********************************************************/
/*                     CAN0����                          */
/*********************************************************/
Bool Can_Receive(struct CAN_MSG *msg)
{
    unsigned int sp2;
    if (!CAN0RFLG_RXF)             //�����ձ�־
    {
        return FALSE;
    }
    if (CAN0RXIDR1_IDE)              //���canЭ���Ǳ�׼/��չģʽ 0����׼  1:��չ
    {
        return FALSE;
    }
    msg->id = (unsigned int)(CAN0RXIDR0 << 3U) |       //����ʶ��
              (unsigned char)(CAN0RXIDR1 >> 5U);
    if (CAN0RXIDR1 & 0x10U)
    {
        msg->RTR = TRUE;
    } else
    {
        msg->RTR = FALSE;
    }
    msg->len = CAN0RXDLR;                             //��ȡ���ݳ���
    for (sp2 = 0U; sp2 < msg->len; sp2++)             //��ȡ����
    {
        msg->data[sp2] = *((&CAN0RXDSR0) + sp2);
    }
    CAN0RFLG = 0x01U;                                  //��RXF��־(������׼������)
    return TRUE;
}