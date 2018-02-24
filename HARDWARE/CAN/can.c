#include "can.h"

u8 g_Get_RFID_buff[16];
u8 g_cinavi1_RXbuff[16];  //ǰ�ŵ���
u8 g_cinavi2_RXbuff[16];	
u8 g_cinavi3_RXbuff[16];  
u8 g_cinavi4_RXbuff[16];	//��ŵ���

u16 g_AGV_RFID_ID;//�ر�  //
u8  g_flag_RFID_beep;

//CAN��ʼ��
//tsjw:����ͬ����Ծʱ�䵥Ԫ.��Χ:CAN_SJW_1tq~ CAN_SJW_4tq
//tbs2:ʱ���2��ʱ�䵥Ԫ.   ��Χ:CAN_BS2_1tq~CAN_BS2_8tq;
//tbs1:ʱ���1��ʱ�䵥Ԫ.   ��Χ:CAN_BS1_1tq ~CAN_BS1_16tq
//brp :�����ʷ�Ƶ��.��Χ:1~1024; tq=(brp)*tpclk1
//������=Fpclk1/((tbs1+1+tbs2+1+1)*brp);
//mode:CAN_Mode_Normal,��ͨģʽ;CAN_Mode_LoopBack,�ػ�ģʽ;
//Fpclk1��ʱ���ڳ�ʼ����ʱ������Ϊ42M,�������CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,6,CAN_Mode_LoopBack);
//������Ϊ:42M/((6+7+1)*6)=500Kbps
//����ֵ:0,��ʼ��OK;
//    ����,��ʼ��ʧ��; 
u8 CAN1_Mode_Init(u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode) //PA11 PA12
{

  	GPIO_InitTypeDef GPIO_InitStructure; 
	CAN_InitTypeDef        CAN_InitStructure;
  	CAN_FilterInitTypeDef  CAN_FilterInitStructure;
#if CAN1_RX0_INT_ENABLE 
   	NVIC_InitTypeDef  NVIC_InitStructure;
#endif
    //ʹ�����ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��PORTAʱ��	                   											 

  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);//ʹ��CAN1ʱ��	
	
    //��ʼ��GPIO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11| GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
    GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��PA11,PA12
	
	  //���Ÿ���ӳ������
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource11,GPIO_AF_CAN1); //GPIOA11����ΪCAN1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource12,GPIO_AF_CAN1); //GPIOA12����ΪCAN1
	  
  	//CAN��Ԫ����
   	CAN_InitStructure.CAN_TTCM=DISABLE;	//��ʱ�䴥��ͨ��ģʽ   
  	CAN_InitStructure.CAN_ABOM=DISABLE;	//����Զ����߹���	  
  	CAN_InitStructure.CAN_AWUM=DISABLE;//˯��ģʽͨ���������(���CAN->MCR��SLEEPλ)
  	CAN_InitStructure.CAN_NART=ENABLE;	//��ֹ�����Զ����� 
  	CAN_InitStructure.CAN_RFLM=DISABLE;	//���Ĳ�����,�µĸ��Ǿɵ�  
  	CAN_InitStructure.CAN_TXFP=DISABLE;	//���ȼ��ɱ��ı�ʶ������ 
  	CAN_InitStructure.CAN_Mode= mode;	 //ģʽ���� 
  	CAN_InitStructure.CAN_SJW=tsjw;	//����ͬ����Ծ���(Tsjw)Ϊtsjw+1��ʱ�䵥λ CAN_SJW_1tq~CAN_SJW_4tq
  	CAN_InitStructure.CAN_BS1=tbs1; //Tbs1��ΧCAN_BS1_1tq ~CAN_BS1_16tq
  	CAN_InitStructure.CAN_BS2=tbs2;//Tbs2��ΧCAN_BS2_1tq ~	CAN_BS2_8tq
  	CAN_InitStructure.CAN_Prescaler=brp;  //��Ƶϵ��(Fdiv)Ϊbrp+1	
  	CAN_Init(CAN1, &CAN_InitStructure);   // ��ʼ��CAN1 
    
		//���ù�����
 	CAN_FilterInitStructure.CAN_FilterNumber=0;	  //������0
  	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask; 
  	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit; //32λ 
  	CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;////32λID
  	CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
  	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;//32λMASK
  	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
   	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0;//������0������FIFO0
  	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; //���������0
  	CAN_FilterInit(&CAN_FilterInitStructure);//�˲�����ʼ��
		
#if CAN1_RX0_INT_ENABLE
	
	 CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);//FIFO0��Ϣ�Һ��ж�����.		    
  
  	NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;     // �����ȼ�Ϊ1
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;            // �����ȼ�Ϊ0
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);
#endif
	return 0;
} 

u8 CAN2_Mode_Init(u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode) //PB5  PB6
{

  	GPIO_InitTypeDef GPIO_InitStructure; 
	CAN_InitTypeDef        CAN_InitStructure;
  	CAN_FilterInitTypeDef  CAN_FilterInitStructure;
#if CAN2_RX0_INT_ENABLE 
   	NVIC_InitTypeDef  NVIC_InitStructure;
#endif
    //ʹ�����ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//ʹ��PORTBʱ��	                   											 

  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);//ʹ��CAN2ʱ��	
	
    //��ʼ��GPIO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5| GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
    GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��PB5,PB6
	
	  //���Ÿ���ӳ������
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource5,GPIO_AF_CAN2); //GPIOB5����ΪCAN2
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF_CAN2); //GPIOB6����ΪCAN2
	  
  	//CAN��Ԫ����
   	CAN_InitStructure.CAN_TTCM=DISABLE;	//��ʱ�䴥��ͨ��ģʽ   
  	CAN_InitStructure.CAN_ABOM=DISABLE;	//����Զ����߹���	  
  	CAN_InitStructure.CAN_AWUM=DISABLE;//˯��ģʽͨ���������(���CAN->MCR��SLEEPλ)
  	CAN_InitStructure.CAN_NART=ENABLE;	//��ֹ�����Զ����� 
  	CAN_InitStructure.CAN_RFLM=DISABLE;	//���Ĳ�����,�µĸ��Ǿɵ�  
  	CAN_InitStructure.CAN_TXFP=DISABLE;	//���ȼ��ɱ��ı�ʶ������ 
  	CAN_InitStructure.CAN_Mode= mode;	 //ģʽ���� 
  	CAN_InitStructure.CAN_SJW=tsjw;	//����ͬ����Ծ���(Tsjw)Ϊtsjw+1��ʱ�䵥λ CAN_SJW_1tq~CAN_SJW_4tq
  	CAN_InitStructure.CAN_BS1=tbs1; //Tbs1��ΧCAN_BS1_1tq ~CAN_BS1_16tq
  	CAN_InitStructure.CAN_BS2=tbs2;//Tbs2��ΧCAN_BS2_1tq ~	CAN_BS2_8tq
  	CAN_InitStructure.CAN_Prescaler=brp;  //��Ƶϵ��(Fdiv)Ϊbrp+1	
  	CAN_Init(CAN2, &CAN_InitStructure);   // ��ʼ��CAN1 
    
		//���ù�����
 	CAN_FilterInitStructure.CAN_FilterNumber=14;	  //������14
  	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask; 
  	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit; //32λ 
  	CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;////32λID
  	CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
  	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;//32λMASK
  	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
   	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0;//������0������FIFO0
  	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; //���������14
  	CAN_FilterInit(&CAN_FilterInitStructure);//�˲�����ʼ��
		
#if CAN2_RX0_INT_ENABLE
	
	 CAN_ITConfig(CAN2,CAN_IT_FMP0,ENABLE);//FIFO0��Ϣ�Һ��ж�����.		    
  
  	NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX0_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;     // �����ȼ�Ϊ1
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;            // �����ȼ�Ϊ0
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);
#endif
	return 0;
}
 

u8 g_Ct_chugui[4];
#if CAN1_RX0_INT_ENABLE	//ʹ��RX0�ж�   
//�жϷ�����			    
void CAN1_RX0_IRQHandler(void)			//�ŵ����ɼ�
{
  	CanRxMsg RxMessage;
	int i=0;
    CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);
	
//	if(RxMessage.StdId == 1)			//ǰ1�ŵ���
//	{
//		for(i=0;i<RxMessage.DLC;i++)
//		g_cinavi1_RXbuff[i]=RxMessage.Data[i];
//		g_CDH8_qian_1 = FindSpace1(g_cinavi1_RXbuff[0],8,g_AGV_Car_fencha_dir);
////		if(g_CDH8_qian_1.Distance)	//��0��
////		{
////			g_Ct_chugui[0] = g_CDH8_qian_1.Distance;
////		}
//		
//	}   
//	if(RxMessage.StdId == 2)			//ǰ2�ŵ���
//	{
//		for(i=0;i<RxMessage.DLC;i++)
//		g_cinavi2_RXbuff[i]=RxMessage.Data[i]; 
//		g_CDH8_qian_2 = FindSpace1(g_cinavi2_RXbuff[0],8,g_AGV_Car_fencha_dir);
////		if(g_CDH8_qian_2.Distance)	//��0��
////		{
////			g_Ct_chugui[1] = g_CDH8_qian_2.Distance;
////		}
//	}
//	if(RxMessage.StdId == 3)			//��1�ŵ���
//	{
//		for(i=0;i<RxMessage.DLC;i++)
//		g_cinavi3_RXbuff[i]=RxMessage.Data[i]; 
//		g_CDH8_hou_1 = FindSpace1(g_cinavi3_RXbuff[0],8,g_AGV_Car_fencha_dir);
////		if(g_CDH8_qian_2.Distance)	//��0��
////		{
////			g_Ct_chugui[1] = g_CDH8_qian_2.Distance;
////		}
//	}
//	if(RxMessage.StdId == 4)			//��2�ŵ���
//	{
//		for(i=0;i<RxMessage.DLC;i++)
//		g_cinavi4_RXbuff[i]=RxMessage.Data[i]; 
//		g_CDH8_hou_2 = FindSpace1(g_cinavi4_RXbuff[0],8,g_AGV_Car_fencha_dir);
////		if(g_CDH8_qian_2.Distance)	//��0��
////		{
////			g_Ct_chugui[1] = g_CDH8_qian_2.Distance;
////		}
//	}
	

	
}
#endif

u16 g_SD_buff[16];


#if CAN2_RX0_INT_ENABLE	//ʹ��RX0�ж�    
//�жϷ�����			    
void CAN2_RX0_IRQHandler(void)  //�ر괫���� �жϴ���
{
  	CanRxMsg RxMessage;
	int i=0;
    CAN_Receive(CAN2, CAN_FIFO0, &RxMessage);
	
	if(RxMessage.StdId == 16)			//�ر괫����ID: 16
	{
		for(i=0;i<RxMessage.DLC;i++)
		g_Get_RFID_buff[i]=RxMessage.Data[i]; 
		g_AGV_RFID_ID = g_Get_RFID_buff[1]<<8|g_Get_RFID_buff[0];
		g_flag_RFID_beep = 1;
		
	}  	

	//0:   //0:ֹͣ1:ǰ�� 2:���� 3:��ת 4:��ת 5���� 6���� 7���� 8���� 9���� 10���� 
	//1:   //�ٶ� 0-100
	//2:   //����

	if(RxMessage.StdId == 2)			//�ֳ�ҡ��ң����  //10msһ��
	{
		for(i=0;i<RxMessage.DLC;i++)
		g_SD_buff[i]=RxMessage.Data[i]; 
		
		g_AGV_shoudong_dir 	 = g_SD_buff[0];
		g_AGV_shoudong_Speed = g_SD_buff[1] * 30 * g_AGV_shoudong_Speed_bili/10;		//0-100*30//0-3000
		
		
	}  	

if(RxMessage.StdId == 1)			//ǰ1�ŵ���
	{
		for(i=0;i<RxMessage.DLC;i++)
		g_cinavi1_RXbuff[i]=RxMessage.Data[i];
		g_CDH8_qian_1 = FindSpace1(g_cinavi1_RXbuff[0],8,g_AGV_Car_fencha_dir);
//		if(g_CDH8_qian_1.Distance)	//��0��
//		{
//			g_Ct_chugui[0] = g_CDH8_qian_1.Distance;
//		}
		
	}   
	
//	if(RxMessage.StdId == 2)			//ǰ2�ŵ���
//	{
//		for(i=0;i<RxMessage.DLC;i++)
//		g_cinavi2_RXbuff[i]=RxMessage.Data[i]; 
//		g_CDH8_qian_2 = FindSpace1(g_cinavi2_RXbuff[0],8,g_AGV_Car_fencha_dir);
////		if(g_CDH8_qian_2.Distance)	//��0��
////		{
////			g_Ct_chugui[1] = g_CDH8_qian_2.Distance;
////		}
//	}
//	
	if(RxMessage.StdId == 3)			//��1�ŵ���
	{
		for(i=0;i<RxMessage.DLC;i++)
		g_cinavi3_RXbuff[i]=RxMessage.Data[i]; 
		g_CDH8_hou_1 = FindSpace1(g_cinavi3_RXbuff[0],8,g_AGV_Car_fencha_dir);
//		if(g_CDH8_qian_2.Distance)	//��0��
//		{
//			g_Ct_chugui[1] = g_CDH8_qian_2.Distance;
//		}
	}
	if(RxMessage.StdId == 4)			//��2�ŵ���
	{
		for(i=0;i<RxMessage.DLC;i++)
		g_cinavi4_RXbuff[i]=RxMessage.Data[i]; 
		g_CDH8_hou_2 = FindSpace1(g_cinavi4_RXbuff[0],8,g_AGV_Car_fencha_dir);
//		if(g_CDH8_qian_2.Distance)	//��0��
//		{
//			g_Ct_chugui[1] = g_CDH8_qian_2.Distance;
//		}
	}
	
	
}
#endif
//		//�����ر�  --  �ɰ�
//		//rece_buf
//		if(rece2_index>0)
//		{
//			p=strstr(rece_buf,l);
//			if(p)
//			{
//				dst[0]=p[15];
//				dst[1]=p[16];
//				dst[2]=p[17];
//				for(i=0;i<rece2_index;i++)
//				rece_buf[i]=0;
//				rece2_index=0;
//				g_AGV_RFID_ID=(dst[0]-0x30)*100+(dst[1]-0x30)*10+(dst[2]-0x30);
//				PLC_Data[1]=g_AGV_RFID_ID;
//			}
//		} 	





//can����һ������(�̶���ʽ:IDΪ0X12,��׼֡,����֡)	
//len:���ݳ���(���Ϊ8)				     
//msg:����ָ��,���Ϊ8���ֽ�.
//����ֵ:0,�ɹ�;
//		 ����,ʧ��;
u8 CAN1_Send_Msg(u16 ID,char* msg,u8 len)
{	
  u8 mbox;
  u16 i=0;
  CanTxMsg TxMessage;
  TxMessage.StdId=ID;	 // ��׼��ʶ��Ϊ0
  TxMessage.ExtId=ID;	 // ������չ��ʾ����29λ��
  TxMessage.IDE=0;		  // ʹ����չ��ʶ��
  TxMessage.RTR=0;		  // ��Ϣ����Ϊ����֡��һ֡8λ
  TxMessage.DLC=len;							 // ������֡��Ϣ
  for(i=0;i<len;i++)
  TxMessage.Data[i]=msg[i];				 // ��һ֡��Ϣ          
  mbox= CAN_Transmit(CAN1, &TxMessage);   
  i=0;
  while((CAN_TransmitStatus(CAN1, mbox)==CAN_TxStatus_Failed)&&(i<0XFFF))i++;	//�ȴ����ͽ���
  if(i>=0XFFF)return 1;
  return 0;		

}
//can�ڽ������ݲ�ѯ
//buf:���ݻ�����;	 
//����ֵ:0,�����ݱ��յ�;
//		 ����,���յ����ݳ���;
//u8 CAN1_Receive_Msg(void)
//{		   		   
// 	u32 i;
//	CanRxMsg RxMessage;
//    if( CAN_MessagePending(CAN1,CAN_FIFO0)==0)return 0;		//û�н��յ�����,ֱ���˳� 
//	CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);//��ȡ����	
//	
//	if(RxMessage.StdId == 5)
//	{
//		for(i=0;i<RxMessage.DLC;i++)
//		g_cinavi5_RXbuff[i]=RxMessage.Data[i];
//		
//	}   
//	if(RxMessage.StdId == 6)
//	{
//		for(i=0;i<RxMessage.DLC;i++)
//		g_cinavi6_RXbuff[i]=RxMessage.Data[i]; 
//	}
//	
//	return RxMessage.DLC;	
//}

//can����һ������(�̶���ʽ:IDΪ0X12,��׼֡,����֡)	
//len:���ݳ���(���Ϊ8)				     
//msg:����ָ��,���Ϊ8���ֽ�.
//����ֵ:0,�ɹ�;
//		 ����,ʧ��;
u8 CAN2_Send_Msg(u16 ID,char* msg,u8 len)
{	
  u8 mbox;
  u16 i=0;
  CanTxMsg TxMessage;
  TxMessage.StdId=ID;	 // ��׼��ʶ��Ϊ0
  TxMessage.ExtId=ID;	 // ������չ��ʾ����29λ��
  TxMessage.IDE=0;		  // ʹ����չ��ʶ��
  TxMessage.RTR=0;		  // ��Ϣ����Ϊ����֡��һ֡8λ
  TxMessage.DLC=len;							 // ������֡��Ϣ
  for(i=0;i<len;i++)
  TxMessage.Data[i]=msg[i];				 // ��һ֡��Ϣ          
  mbox= CAN_Transmit(CAN2, &TxMessage);   
  i=0;
  while((CAN_TransmitStatus(CAN2, mbox)==CAN_TxStatus_Failed)&&(i<0XFFF))i++;	//�ȴ����ͽ���
  if(i>=0XFFF)return 1;
  return 0;		


}
//can�ڽ������ݲ�ѯ
//buf:���ݻ�����;	 
//����ֵ:0,�����ݱ��յ�;
//		 ����,���յ����ݳ���;
u8 CAN2_Receive_Msg(u8 *buf)
{		   		   
 	u32 i;
	CanRxMsg RxMessage;
    if( CAN_MessagePending(CAN2,CAN_FIFO0)==0)return 0;		//û�н��յ�����,ֱ���˳� 
	

	CAN_Receive(CAN2, CAN_FIFO0, &RxMessage);//��ȡ����	
    for(i=0;i<RxMessage.DLC;i++)
    buf[i]=RxMessage.Data[i];  
	//LED4 = !LED4;
	return RxMessage.DLC;	
}


//
//������Canopen����
//
char CanOpen_buff[8];

void AGV_CanOpen_Send(void)		//���� CAN2
{
	
	CanOpen_buff[0] = 1;
	CanOpen_buff[1] = 0;
	

	CAN1_Send_Msg(0,CanOpen_buff,2);
	delay_rtos(0,0,0,20);


}

void AGV_CanOpen_Send1(void)
{
	
	CanOpen_buff[0] = 6;
	CanOpen_buff[1] = 0;
	CanOpen_buff[2] = 0;
	CanOpen_buff[3] = 0;	
	CanOpen_buff[4] = 0;
	CanOpen_buff[5] = 0;	

	CAN1_Send_Msg(0x201,CanOpen_buff,6);
	delay_rtos(0,0,0,20);
	CAN1_Send_Msg(0x202,CanOpen_buff,6);
	delay_rtos(0,0,0,20);
	CAN1_Send_Msg(0x203,CanOpen_buff,6);
	delay_rtos(0,0,0,20);
	CAN1_Send_Msg(0x204,CanOpen_buff,6);
	delay_rtos(0,0,0,20);


}

void AGV_CanOpen_Send2(void)
{
	
	CanOpen_buff[0] = 7;
	CanOpen_buff[1] = 0;
	CanOpen_buff[2] = 0;
	CanOpen_buff[3] = 0;	
	CanOpen_buff[4] = 0;
	CanOpen_buff[5] = 0;	

	CAN1_Send_Msg(0x201,CanOpen_buff,6);
	delay_rtos(0,0,0,20);
	CAN1_Send_Msg(0x202,CanOpen_buff,6);
	delay_rtos(0,0,0,20);
	CAN1_Send_Msg(0x203,CanOpen_buff,6);
	delay_rtos(0,0,0,20);
	CAN1_Send_Msg(0x204,CanOpen_buff,6);
	delay_rtos(0,0,0,20);

}
//u8 g_flag_Motec_init;
void Motec_init(void)		
{

	delay_rtos(0,0,2,100);
	AGV_CanOpen_Send();
	AGV_CanOpen_Send1();
	AGV_CanOpen_Send2();
		
	
	//g_flag_Motec_init = 1;		//��ʼ����ɱ�־	

}

//�ٶ�
void AGV_CanOpen_Send3(u8 node_id,int speed) 
{
	u16 temp_COB_ID=0;
	
	if(node_id > 127)					//�ڵ�ID���ܳ���127
	{
		node_id = 127;
	}
	temp_COB_ID = 0x200+node_id;		//11λCOB_ID
	
	
	
	CanOpen_buff[0] = 0x0f;
	CanOpen_buff[1] = 0;
	CanOpen_buff[2] = speed;
	CanOpen_buff[3] = speed>>8;	
	

	CAN1_Send_Msg(temp_COB_ID,CanOpen_buff,4);
	delay_rtos(0,0,0,20);								//������ʱmotec����������ʱ
}







