#include "button.h"


AGV_Senser_Enable g_Senser_Enable = 
{
								//  //ǰ����
		0,						//u8 IR_qian_jin;
		0,						//u8 IR_qian_yuan;
								////�����
		0,						//u8 IR_hou_jin;
		0,						//u8 IR_hou_yuan;
								////ǰ��е
		0,						//u8 JIXIE_qian;
		0						////���е
								//u8 JIXIE_hou;
};






//PF4 -- ֹͣ
//PF5 -- ����
//PF6 -- ��_��Ͳ������� 	-- (ԭ��ͣ)

//PF14-- ǰ_������� 		-- (ǣ���˿���2)   Զ
//PF10-- ��_������� 		-- (ǣ���˿���1)	Զ

//PF9 -- ǰ����---��
//PF8 -- �����--��

//PA6 -- ǰ��ײ
//PA7 -- ���ײ

//PF7 -- ��_��Ͳ������� 	-- (���ÿ���1) 


//�ⲿ�жϳ�ʼ������
void button_input_init(void)//��������,�͵�ƽ����
{	
	GPIO_InitTypeDef GPIO_InitStructure;
	

	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��
		
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4| GPIO_Pin_5| GPIO_Pin_6| GPIO_Pin_7| GPIO_Pin_8| GPIO_Pin_9|
	GPIO_Pin_10| GPIO_Pin_14; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	

}


//#define  g_agv_stop 					PFin(4)
//#define  g_agv_start					PFin(5)

//#define  g_flag_IR_qian_yuan				PFin(14)
//#define  g_flag_IR_hou_yuan				PFin(10)

//#define  g_flag_fangzhuang_qian		PFin(9)
//#define  g_flag_fangzhuang_hou		PFin(8)

//#define  g_flag_guntong_zuo			PFin(6)
//#define  g_flag_guntong_you			PFin(7)


u8 AGV_input_24V_buff[16];

//AGVȫ��״̬
u8 g_AGV_Car_STOP = 1;		//AGVĬ��ֹͣ	
//u8 g_AGV_Car_START;

void agv_24V_input(void)	//δ����������,������
{
	if(!g_button_stop)						//g_jixieKEy_stop
	{
		AGV_input_24V_buff[0] = 1;
	}
	else
	{
		AGV_input_24V_buff[0] = 0;
	}
		
	if(!g_button_start)					//g_jixieKEY_start
	{
		AGV_input_24V_buff[1] = 1;
	}
	else
	{
		AGV_input_24V_buff[1] = 0;
	}		
	
	if(g_Senser_Enable.IR_qian_yuan)	//ʹ�ܺ���
	{
		if(!g_flag_IR_qian_yuan)					//ǰԶ����  	//g_IR_yuan_CAR_qian
		{
			AGV_input_24V_buff[2] =  1;
		}
		else
		{
			AGV_input_24V_buff[2] =  0;
		}	
	}
	else								//�رպ���
	{
		AGV_input_24V_buff[2] =  0;
	}
	

	if(g_Senser_Enable.IR_hou_yuan)	//ʹ�ܺ���
	{
		if(!g_flag_IR_hou_yuan)						//��Զ����		//g_IR_yuan_CAR_hou
		{
			AGV_input_24V_buff[3] =  1;
		}
		else
		{
			AGV_input_24V_buff[3] = 0;
		}		
	}		
	else
	{
		AGV_input_24V_buff[3] =  0;
	}
	

	if(g_Senser_Enable.JIXIE_qian)	//ʹ��
	{
		if(!g_flag_fangzhuang_qian)			//g_jiexie_qian
		{
			AGV_input_24V_buff[4] =  1;
		}
		else
		{
			AGV_input_24V_buff[4] = 0;
		}		
	}	
	else
	{
		AGV_input_24V_buff[4] =  0;
	}

	if(g_Senser_Enable.JIXIE_hou)	//ʹ��
	{
		if(!g_flag_fangzhuang_hou)			//g_jiexie_hou
		{
			AGV_input_24V_buff[5] = 1;
		}
		else
		{
			AGV_input_24V_buff[5] = 0;
		}		
	}		
	else
	{
		AGV_input_24V_buff[5] = 0;
	}
	
	
	if(!g_flag_guntong_zuo)				//g_IR_guntong_left
	{
		AGV_input_24V_buff[6] = 1;
	}
	else
	{
		AGV_input_24V_buff[6] = 0;
	}	
	
	if(!g_flag_guntong_you)				//g_IR_guntong_right
	{
		AGV_input_24V_buff[7] = 1;
	}
	else
	{
		AGV_input_24V_buff[7] = 0;
	}	
	

	if(g_Senser_Enable.IR_qian_jin)	//ʹ��
	{
		if(!g_flag_IR_qian_jin)					//ǰ������  	//g_IR_jin_CAR_qian
		{
			AGV_input_24V_buff[8] =  1; 
		}
		else
		{
			AGV_input_24V_buff[8] = 0;
		}	
	}	
	else
	{
		AGV_input_24V_buff[8] =  0; 	
	}
	
	if(g_Senser_Enable.IR_hou_jin)	//ʹ��
	{
		if(!g_flag_IR_hou_jin)					//�������  	//g_IR_jin_CAR_hou
		{
			AGV_input_24V_buff[9] = 1; 
		}
		else
		{
			AGV_input_24V_buff[9] =  0;
		}	
	}
	else
	{
		AGV_input_24V_buff[9] =  0;
	}
	






}








//�ⲿ�жϳ�ʼ������
//void button_input_init(void)//��������,�͵�ƽ����
//{	
//	GPIO_InitTypeDef GPIO_InitStructure;
//	
//	EXTI_InitTypeDef   EXTI_InitStructure;
//	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��
//		
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//

//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4| GPIO_Pin_5| GPIO_Pin_6| GPIO_Pin_7| GPIO_Pin_8| GPIO_Pin_9|
//	GPIO_Pin_10| GPIO_Pin_14; 
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
//	GPIO_Init(GPIOF, &GPIO_InitStructure);
//	
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource4);	//PF4 ���ӵ��ж���4
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource5);	//PF5 ���ӵ��ж���5
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource6);	//PF6 ���ӵ��ж���6
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource7);	//PF7 ���ӵ��ж���7
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource8);	//PF8 ���ӵ��ж���8
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource9);	//PF9 ���ӵ��ж���9
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource10);	//PF10 ���ӵ��ж���10
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource14);	//PF14 ���ӵ��ж���14
//	
//	/* ����EXTI_Line4 */
//	EXTI_InitStructure.EXTI_Line = EXTI_Line4 ;
//	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
//	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
//	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//�ж���ʹ��
//	EXTI_Init(&EXTI_InitStructure);//����
//	
//	/* ����EXTI_Line5 */
//	EXTI_InitStructure.EXTI_Line = EXTI_Line5 ;
//	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
//	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
//	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//�ж���ʹ��
//	EXTI_Init(&EXTI_InitStructure);//����

//	/* ����EXTI_Line6 */
//	EXTI_InitStructure.EXTI_Line = EXTI_Line6 ;
//	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
//	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
//	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//�ж���ʹ��
//	EXTI_Init(&EXTI_InitStructure);//����
//	
//	/* ����EXTI_Line7 */
//	EXTI_InitStructure.EXTI_Line = EXTI_Line7 ;
//	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
//	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
//	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//�ж���ʹ��
//	EXTI_Init(&EXTI_InitStructure);//����
//	
//	/* ����EXTI_Line8 */
//	EXTI_InitStructure.EXTI_Line = EXTI_Line8 ;
//	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
//	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
//	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//�ж���ʹ��
//	EXTI_Init(&EXTI_InitStructure);//����
//	
//	/* ����EXTI_Line9 */
//	EXTI_InitStructure.EXTI_Line = EXTI_Line9 ;
//	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
//	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
//	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//�ж���ʹ��
//	EXTI_Init(&EXTI_InitStructure);//����
//		/* ����EXTI_Line10 */
//	EXTI_InitStructure.EXTI_Line = EXTI_Line10 ;
//	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
//	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
//	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//�ж���ʹ��
//	EXTI_Init(&EXTI_InitStructure);//����
//	
//	/* ����EXTI_Line14 */
//	EXTI_InitStructure.EXTI_Line = EXTI_Line14 ;
//	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
//	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
//	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//�ж���ʹ��
//	EXTI_Init(&EXTI_InitStructure);//����
//}



// 
//u8 g_flag_butt_stop;
//u8 g_flag_butt_start;

//void EXTI4_IRQHandler(void)
//{
//	if(EXTI_GetITStatus(EXTI_Line4) == SET)
//	{
//		if(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_4)==0)  //ֹͣ����
//		{	
////			MotoStop(1);  
////			g_flag_MOTORstart = 0; //��������ź�
////			g_flag_butt_stop = 1;
////			g_flag_butt_start = 0;
//			
//			g_agv_stop = 1;
//		}
//		EXTI_ClearITPendingBit(EXTI_Line4); //���LINE4�ϵ��жϱ�־λ 		
//	}	
//}



////�ⲿ�жϷ������
//void EXTI9_5_IRQHandler(void)
//{
//	if(EXTI_GetITStatus(EXTI_Line5) == SET)	 
//	{
//		if(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_5)==0)  //��������
//		{
//			g_agv_stop = 0;
//		}
//		
//		EXTI_ClearITPendingBit(EXTI_Line5); //���LINE5�ϵ��жϱ�־λ 
//	}	

//	if(EXTI_GetITStatus(EXTI_Line6) == SET)	 			//��_��Ͳ������� 	-- (ԭ��ͣ)
//	{
//		if(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_6)==0)
//		{
//			
//		}
//		EXTI_ClearITPendingBit(EXTI_Line6); //���LINE6�ϵ��жϱ�־λ 
//	}	
//	
//	if(EXTI_GetITStatus(EXTI_Line7) == SET)	 
//	{
//		if(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_7)==0)	//��_��Ͳ������� 	-- (���ÿ���1) 
//		{
//			
//		}
//		
//		EXTI_ClearITPendingBit(EXTI_Line7); //���LINE7�ϵ��жϱ�־λ 
//	}	
//	if(EXTI_GetITStatus(EXTI_Line8) == SET)	 
//	{
//		if(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_8)==0)		//���ײ
//		{
//			
//		}
//		
//		EXTI_ClearITPendingBit(EXTI_Line8); //���LINE8�ϵ��жϱ�־λ 
//	}	
//	if(EXTI_GetITStatus(EXTI_Line9) == SET)	 
//	{
//		if(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_9)==0)		//ǰ��ײ
//		{
//			
//		}
//		
//		EXTI_ClearITPendingBit(EXTI_Line9); //���LINE9�ϵ��жϱ�־λ 
//	}	
//	
//	 
//}	

//void EXTI15_10_IRQHandler(void)
//{
//	if(EXTI_GetITStatus(EXTI_Line10) == SET)	 
//	{
//		if(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_10)==0)        //��_������� 		-- (ǣ���˿���1)
//		{
//			
//		}
//		
//		EXTI_ClearITPendingBit(EXTI_Line10); //���LINE10�ϵ��жϱ�־λ 
//	}	

//	if(EXTI_GetITStatus(EXTI_Line14) == SET)	 
//	{
//		if(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_14)==0)        //ǰ_������� 		-- (ǣ���˿���2)
//		{
//			g_flag_IR_qian_yuan = 1;
//		}
//		
//		EXTI_ClearITPendingBit(EXTI_Line14); //���LINE14�ϵ��жϱ�־λ 
//	}	



//}





