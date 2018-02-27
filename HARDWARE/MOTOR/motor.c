#include "motor.h"

u16 g_MAX_Speed = 2999;

u16 g_AGV_Car_Speed;	
u16 g_AGV_shoudong_Speed;
u16 g_AGV_shoudong_Speed_bili = 4;
u16 g_AGV_shoudong_dir;			//0:ֹͣ1:ǰ�� 2:���� 3:��ת 4:��ת 5���� 6���� 7���� 8���� 9���� 10���� 
u8  g_AGV_Car_dir;				//ȫ��Ψһ//0:ǰ��    1:����

u8  g_AGV_Car_fencha_dir;		//ȫ��Ψһ//0:��ֲ�  1:�ҷֲ�
u8  g_AGV_Car_mode = 1;				//0:�Զ�  1:�ֶ�





////���������
////ʹ���ź�,�����ź�,���ų�ʼ��
//void motor_init(void) 
//{
//	GPIO_InitTypeDef  GPIO_InitStructure;

//	//Motec��������ʹ������PD -- 0 1 3 4
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);	//ʹ��GPIODʱ��
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);	//
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);	//

//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_4;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
//	GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��
//	GPIO_SetBits(GPIOD,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_4);
//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10| GPIO_Pin_11| GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;			//���
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;			//����
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;		//100MHz
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;			//����
//	GPIO_Init(GPIOG, &GPIO_InitStructure);					//
//	GPIO_SetBits(GPIOG,GPIO_Pin_10| GPIO_Pin_11| GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15);
//		
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;			//���
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;			//����
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;		//100MHz
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;			//����
//	GPIO_Init(GPIOB, &GPIO_InitStructure);
//	GPIO_SetBits(GPIOB,GPIO_Pin_3 | GPIO_Pin_4);
//	
//	
//}


//void motec_pulse(u8 speed)	//0~100
//{
//	u16 temp_true=0;
//	
//	//--100k -- 210    210 00 000
//	//--1k -- 21000
//	if(speed<1)
//	{
//		speed = 1;
//	}
//	else if(speed>100)
//	{
//		speed = 100;
//	}
//	temp_true = 500/speed;		

////100k -- 10/2=5
////1k -- 1000/2=500
//	PWM_1 = !PWM_1;
//	delay_us(temp_true);	//100k	
//	
//}




void Motor_Zzhuan(u8 Motor,u32 speed)           //���ǵ�������ڵĿ��ƴ�
{	
	if(speed > g_MAX_Speed)	//2999
	{
		speed = g_MAX_Speed;
	}
	switch(Motor)
	{
		case 1:									//���1		
			AGV_CanOpen_Send3(1,speed);
		break;
		case 2:									//���2
			AGV_CanOpen_Send3(2,speed);
		break;                                  
		case 3:									//���3
			AGV_CanOpen_Send3(3,speed);
		break;                                  
		case 4:									//���4
			AGV_CanOpen_Send3(4,speed);
		break;                                  
		default:
		break;
	}
}

void Motor_Fzhuan(u8 Motor,u32 speed)
{
	int tmep_spd=0;
	
		
	if(speed == 0)
	{
		tmep_spd = 0;
	}
	else if(speed > g_MAX_Speed)
	{
		tmep_spd = -g_MAX_Speed;
	}
	else
	{
		tmep_spd = -speed;
	}
	
	switch(Motor)
	{
		case 1:									//���1		
			AGV_CanOpen_Send3(1,tmep_spd);
		break;
		case 2:									//���2
			AGV_CanOpen_Send3(2,tmep_spd);
		break;                                  
		case 3:									//���3
			AGV_CanOpen_Send3(3,tmep_spd);
		break;                                  
		case 4:									//���4
			AGV_CanOpen_Send3(4,tmep_spd);
		break;
		default:
		break;
	}
}

//
//ǰ�����ֵĿ���
//
void qianlun_Go(u16 temp_speed)			//ǰ��ǰ��
{
	Motor_Zzhuan(1,temp_speed); Motor_Fzhuan(2,temp_speed);
}
void qianlun_Back(u16 temp_speed)		//ǰ�ֺ���
{
	Motor_Fzhuan(1,temp_speed); Motor_Zzhuan(2,temp_speed);
}

u16 g_XZ_MAX_Speed = 700;




void qianlun_TurnL(u16 temp_speed)		//ǰ����ת
{
	if(temp_speed > g_XZ_MAX_Speed)
	{
		temp_speed = g_XZ_MAX_Speed;
	}
	Motor_Fzhuan(1,temp_speed); Motor_Fzhuan(2,temp_speed);
}
void qianlun_TurnR(u16 temp_speed)		//ǰ����ת
{
	if(temp_speed > g_XZ_MAX_Speed)
	{
		temp_speed = g_XZ_MAX_Speed;
	}
	Motor_Zzhuan(1,temp_speed); Motor_Zzhuan(2,temp_speed);
}
//
//�������ֵĿ���
//
void houlun_Go(u16 temp_speed)			//����ǰ��
{
	Motor_Zzhuan(3,temp_speed); Motor_Fzhuan(4,temp_speed);
}
void houlun_Back(u16 temp_speed)		//���ֺ���
{
	Motor_Fzhuan(3,temp_speed); Motor_Zzhuan(4,temp_speed);
}
void houlun_TurnL(u16 temp_speed)		//������ת
{
	if(temp_speed > g_XZ_MAX_Speed)
	{
		temp_speed = g_XZ_MAX_Speed;
	}
	Motor_Fzhuan(3,temp_speed); Motor_Fzhuan(4,temp_speed);
}
void houlun_TurnR(u16 temp_speed)		//������ת
{
	if(temp_speed > g_XZ_MAX_Speed)
	{
		temp_speed = g_XZ_MAX_Speed;
	}
	Motor_Zzhuan(3,temp_speed); Motor_Zzhuan(4,temp_speed);
}



//��λ��0��Ӧǰ����
//��λ��1��Ӧ������
u16 g_xz_dwq[2];
u8 g_XZ_Ok;
u8 g_XZ_Beep;
u8 g_XZ_Speed = 60;
void DwqXunZheng_QH(void)
{
	//OS_ERR err;
	int temp_cha[2]={0,0};
	
	
	g_xz_dwq[0] = g_After_filter[1];	
	temp_cha[0] = g_xz_dwq[0] - g_DWQ.qianlun_zhong_val;
	
	BEEP = 1;
	
	while( abs(temp_cha[0]) > 2)
	{
		
		if(g_xz_dwq[0] > g_DWQ.qianlun_zhong_val)		//����ƫ��,��ת
		{
			qianlun_TurnL( abs(temp_cha[0]) * g_XZ_Speed );			//����ٶ�90*10����
		} 
		if(g_xz_dwq[0]<g_DWQ.qianlun_zhong_val)		//����ƫ��,��ת
		{
			qianlun_TurnR( abs(temp_cha[0]) * g_XZ_Speed );
		}
		
		//OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_HMSM_STRICT,&err);
		
		g_xz_dwq[0] =  g_After_filter[1];		
		temp_cha[0] = g_xz_dwq[0] - g_DWQ.qianlun_zhong_val;
		
	}
	MotoStop(1);	
	MotoStop(2);	
	
	g_xz_dwq[1] = g_After_filter[2];	
	temp_cha[1] = g_xz_dwq[1] - g_DWQ.houlun_zhong_val;
	while( abs(temp_cha[1]) > 2)
	{
		if(g_xz_dwq[1]>g_DWQ.houlun_zhong_val)		//����ƫ��,��ת
		{
			houlun_TurnL( abs(temp_cha[1]) * g_XZ_Speed );
		}
		if(g_xz_dwq[1]<g_DWQ.houlun_zhong_val)		//����ƫ��,��ת
		{
			houlun_TurnR( abs(temp_cha[1]) * g_XZ_Speed );
		}
		
		//OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_HMSM_STRICT,&err);
			
		g_xz_dwq[1] = g_After_filter[2];		
		temp_cha[1] = g_xz_dwq[1] - g_DWQ.houlun_zhong_val;
	}	
	
	
	
	
	MotoStop(3);	
	MotoStop(4);	

	g_XZ_Ok = 1;
	//g_XZ_Beep = 1;
	BEEP = 0;

}

AGV_CtXunZheng g_CtXunZheng;




void CtXunZheng_qian(u8 cidaohang_id,u16 xunzheng_speed0)
{
	OS_ERR err;
	
	u16 temp_dianweiqi_1=0;
	u8 temp_flag_L_jixian0=0;
	u8 temp_flag_R_jixian0=0;
	u8 temp_flag_NoFind=0;
	
	if(cidaohang_id == 1)		//ǰ1�ŵ���
	{
		while(g_CDH8_qian_1.Num<2)		//����2������		
		{									
					
			temp_dianweiqi_1 = g_After_filter[1];	//ǰ������λ��
			
			if(!temp_flag_L_jixian0)			//����δ��λ
			{
				if(temp_dianweiqi_1 > g_DWQ.qianlun_L_val)	//������ת��λ��ֵ��С 2.0
				{
					qianlun_TurnL(xunzheng_speed0);		//��һ����ת
				}
				else						//��һ�ε����޺���ת
				{
					MotoStop(1);
					MotoStop(2);
					qianlun_TurnR(xunzheng_speed0);
					temp_flag_L_jixian0 = 1;	//���޵�λ��־
				}				
			}
			else								//���޵�λ
			{
				if(!temp_flag_R_jixian0)			//�Ҽ���δ��λ
				{
					if(temp_dianweiqi_1 < g_DWQ.qianlun_R_val)	//������ת��λ��ֵ��� 2.0
					{
						qianlun_TurnR(xunzheng_speed0);		//��ת
					}
					else						//�Ҽ��޺���ת
					{
						MotoStop(1);
						MotoStop(2);
						//qianlun_TurnL(xunzheng_speed0);
						temp_flag_R_jixian0 = 1;	//�Ҽ��޵�λ��־
					}				
				}
				else							//�Ҽ��޵�λ
				{
					DwqXunZheng_QH();			//���ұ�������δ�ҵ��ŵ���,��λ��Ѱ������
					temp_flag_NoFind = 1;
					
					break;
				}					
			}
			OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_HMSM_STRICT,&err);	
		}	
		if(temp_flag_NoFind)		//û�ҵ�����
		{
			g_CtXunZheng.XunZ_OK_qian_1 = 0;
		}
		else						//�ҵ�����
		{
			g_CtXunZheng.XunZ_OK_qian_1 = 1;
		}
		MotoStop(1);
		MotoStop(2);		
	}
	else if(cidaohang_id == 2)		//ǰ2�ŵ���
	{
		while(g_CDH8_qian_2.Num<2)		//��⵽2������		
		{									
					
			temp_dianweiqi_1 = g_After_filter[1];	//ǰ������λ��
			
			if(!temp_flag_L_jixian0)			//����δ��λ
			{
				if(temp_dianweiqi_1 > g_DWQ.qianlun_L_val)	//������ת��λ��ֵ��С 0.5
				{
					qianlun_TurnL(xunzheng_speed0);		//��һ����ת
				}
				else						//��һ�ε����޺���ת
				{
					MotoStop(2);
					MotoStop(1);
					qianlun_TurnR(xunzheng_speed0);
					temp_flag_L_jixian0 = 1;	//���޵�λ��־
				}				
			}
			else								//���޵�λ
			{
				if(!temp_flag_R_jixian0)			//�Ҽ���δ��λ
				{
					if(temp_dianweiqi_1 < g_DWQ.qianlun_R_val)	//������ת��λ��ֵ��� 2.0
					{
						qianlun_TurnR(xunzheng_speed0);		//��ת
					}
					else						//�Ҽ��޺���ת
					{					
						MotoStop(2);
						MotoStop(1);	
						//qianlun_TurnL(xunzheng_speed0);						
						temp_flag_R_jixian0 = 1;	//�Ҽ��޵�λ��־
					}				
				}
				else							//�Ҽ��޵�λ
				{
					DwqXunZheng_QH();			//���ұ�������δ�ҵ��ŵ���,��λ��Ѱ������
					temp_flag_NoFind = 1;
					
					break;
				}					
			}
			OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_HMSM_STRICT,&err);	
		}
		if(temp_flag_NoFind)		//û�ҵ�����
		{
			g_CtXunZheng.XunZ_OK_qian_2 = 0;
		}
		else						//�ҵ�����
		{
			g_CtXunZheng.XunZ_OK_qian_2 = 1;
		}	
		MotoStop(2);
		MotoStop(1);		
	}	


}
void CtXunZheng_hou(u8 cidaohang_id,u16 xunzheng_speed)
{
	OS_ERR err;
	
	u16 temp_dianweiqi_2=0;
	u8 temp_flag_L_jixian=0;		//���޵�λ��־
	u8 temp_flag_R_jixian=0;		//�Ҽ��޵�λ��־
	u8 temp_flag_NoFind1=0;
	
	if(cidaohang_id == 1)		//��1�ŵ���
	{
		while(g_CDH8_hou_1.Num<2)		//��⵽2������		
		{									
					
			temp_dianweiqi_2 = g_After_filter[2];	//��������λ��
			
			if(!temp_flag_L_jixian)			//����δ��λ
			{
				if(temp_dianweiqi_2 > g_DWQ.houlun_L_val)	//������ת��λ��ֵ��С 2.0
				{
					houlun_TurnL(xunzheng_speed);		//��һ����ת
				}
				else						//��һ�ε����޺���ת
				{
					MotoStop(3);
					MotoStop(4);
					houlun_TurnR(xunzheng_speed);
					temp_flag_L_jixian = 1;	//���޵�λ��־
				}				
			}
			else								//���޵�λ
			{
				if(!temp_flag_R_jixian)			//�Ҽ���δ��λ
				{
					if(temp_dianweiqi_2 < g_DWQ.houlun_R_val)	//������ת��λ��ֵ��� 2.0
					{
						houlun_TurnR(xunzheng_speed);		//��ת
					}
					else						//�Ҽ��޺���ת
					{
						MotoStop(3);
						MotoStop(4);
						//houlun_TurnL(xunzheng_speed);
						temp_flag_R_jixian = 1;	//�Ҽ��޵�λ��־
					}				
				}
				else							//�Ҽ��޵�λ
				{
					DwqXunZheng_QH();			//���ұ�������δ�ҵ��ŵ���,��λ��Ѱ������
					temp_flag_NoFind1 = 1;
					break;
				}					
			}
			OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_HMSM_STRICT,&err);	
		}	
		if(temp_flag_NoFind1)		//û�ҵ�����
		{
			g_CtXunZheng.XunZ_OK_hou_1 = 0;
		}
		else						//�ҵ�����
		{
			g_CtXunZheng.XunZ_OK_hou_1 = 1;
		}	
		MotoStop(3);
		MotoStop(4);			
	}
	else if(cidaohang_id == 2)		//��2�ŵ���
	{
		while(g_CDH8_hou_2.Num<2)		//��⵽2������		
		{									
					
			temp_dianweiqi_2 = g_After_filter[2];	//��������λ��
			
			if(!temp_flag_L_jixian)			//����δ��λ
			{
				if(temp_dianweiqi_2 > g_DWQ.houlun_L_val)	//������ת��λ��ֵ��С 2.0
				{
					houlun_TurnL(xunzheng_speed);		//��һ����ת
				}
				else						//��һ�ε����޺���ת
				{
					MotoStop(4);
					MotoStop(3);
					houlun_TurnR(xunzheng_speed);
					temp_flag_L_jixian = 1;	//���޵�λ��־
				}				
			}
			else								//���޵�λ
			{
				if(!temp_flag_R_jixian)			//�Ҽ���δ��λ
				{
					if(temp_dianweiqi_2 < g_DWQ.houlun_R_val)	//������ת��λ��ֵ��� 2.0
					{
						houlun_TurnR(xunzheng_speed);		//��ת
					}
					else						//�Ҽ��޺���ת
					{
						MotoStop(4);
						MotoStop(3);						
						//houlun_TurnL(xunzheng_speed);
						temp_flag_R_jixian = 1;	//�Ҽ��޵�λ��־
					}				
				}
				else							//�Ҽ��޵�λ
				{
					DwqXunZheng_QH();			//���ұ�������δ�ҵ��ŵ���,��λ��Ѱ������
					temp_flag_NoFind1 = 1;
					break;					
				}					
			}
			OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_HMSM_STRICT,&err);	
		}
		if(temp_flag_NoFind1)		//û�ҵ�����
		{
			g_CtXunZheng.XunZ_OK_hou_2 = 0;
		}
		else						//�ҵ�����
		{
			g_CtXunZheng.XunZ_OK_hou_2 = 1;
		}	
		MotoStop(4);
		MotoStop(3);		
	}	


}


void check_CtXunZ_OK(u16 XunZ_speed)
{
	u8 temp_Val=0;
	
	if(!g_AGV_Car_dir)	//0:ǰ��
	{
		CtXunZheng_qian(1,XunZ_speed);
		CtXunZheng_hou (1,XunZ_speed);		
		
		
		if(g_CtXunZheng.XunZ_OK_qian_1 && g_CtXunZheng.XunZ_OK_hou_1)
		{
			g_CtXunZheng.XunZ_OK_go_on_Both = 1;
			temp_Val = 1;
		}
		else
		{
			g_CtXunZheng.XunZ_OK_go_on_Both = 0;
			temp_Val = 0;		
		}
		
	}
	else				//1:����
	{
		CtXunZheng_hou (2,XunZ_speed);	
		CtXunZheng_qian(2,XunZ_speed);
		
		
		if(g_CtXunZheng.XunZ_OK_hou_2 && g_CtXunZheng.XunZ_OK_qian_2)
		{
			g_CtXunZheng.XunZ_OK_go_back_Both = 1;
			temp_Val = 1;
		}
		else
		{
			g_CtXunZheng.XunZ_OK_go_back_Both = 0;
			temp_Val = 0;
		}	
	}
	//g_CtXunZheng.XunZ_OK_AGV = temp_Val;
	g_Start_flag.Start_Auto_PID = temp_Val;	//1:�ҵ����� 0:δ�ҵ�


}

void AGV_System_Stop(void)
{
	MotoStop(0);
	g_Start_flag.Stop_AGV_SysCode = 1;

}	
void AGV_System_Start(void)
{
	g_Start_flag.Start_AGV_SysCode = 1;
}

u16 g_CT_XZ_MAX_Speed = 600;
u8 g_glag_bizhang;
void AGV_Stop2Start(void)
{

//	if(Ԥ��1 == 0)							//��λ�������ź�
//	{
//		g_Start_flag.button_Start = 1;
//	}			
	if(g_shoudong_start == 1)				//�̴��� -- �������������� 1��Ч
	{		
		g_Start_flag.Start_button_Car = 1;
	}		
	if(AGV_input_24V_buff[1]==1 && AGV_input_24V_buff[0]==0)	
	{
		g_Start_flag.Start_button_Car = 1;	//�̴���--���������������
	}
	if(g_Start_flag.Start_AGV_SysCode)		//������--��������������������ֹͣ //1����
	{
		g_Start_flag.Start_AGV_SysCode = 0;
		g_Start_flag.Start_button_Car = 1;
	}	
	
	
	
	if(g_Start_flag.Start_IR)				//������--��������������������ֹͣ //1����
	{
		g_Start_flag.button_Start = 1;
	}	

	if(g_Start_flag.Start_jixie)			//������--��������������������ֹͣ //1����
	{
		g_Start_flag.button_Start = 1;
	}	



//	if(Ԥ��2 == 1)							//��λ��ֹͣ�ź�
//	{
//		g_Start_flag.button_Start = 0;
//	}			
	if(g_shoudong_stop == 1)				//�̴���--������ֹͣ���� 1��Ч
	{
		g_Start_flag.Stop_button_Car = 1;
	}			
	if(AGV_input_24V_buff[0]==1)			//�̴���--�������ֹͣ���� -- ϵͳ������ͣ��Ҳ���������ͣ
	{
		g_Start_flag.Stop_button_Car = 1;
	}	
	if(g_Start_flag.Stop_AGV_SysCode)		//������--��������������������ֹͣ //1����
	{
		g_Start_flag.Stop_AGV_SysCode = 0;
		g_Start_flag.Stop_button_Car = 1;
	}			

	
	
	if(!g_Start_flag.Start_IR)				//������--//��������������������ֹͣ //1����
	{
		g_Start_flag.button_Start = 0;
	}		

	
	if(!g_Start_flag.Start_jixie)			//������--��������������������ֹͣ //1����
	{
		g_Start_flag.button_Start = 0;
	}	
	

	if(!g_AGV_Car_mode)	//0:�Զ�
	{
		//AGV����Ѱ��
		if(g_Start_flag.Start_button_Car==1 && g_Start_flag.button_Start==1)	
		{
			g_Start_flag.Start_button_Car = 0;			//����Զ�������־
			g_Start_flag.Stop_button_Car = 0;
			if(!g_Start_flag.Start_Auto_PID)			//�Զ�ģʽδ����		-- ���Ҫ�޸�?
			{
				//�Զ�ģʽ--�ŵ���Ѱ��

				check_CtXunZ_OK(g_CT_XZ_MAX_Speed);		//g_Start_flag.Start_Auto_PID��������һ;				
							
			}
		}
		//AGV����
		if(g_Start_flag.Stop_button_Car==0 && g_Start_flag.button_Start==1)				//����δ����
		{
			

			if(g_glag_bizhang == 1)
			{
				g_glag_bizhang = 0;	
				check_CtXunZ_OK(g_CT_XZ_MAX_Speed);		//g_Start_flag.Start_Auto_PID��������һ;								
			}
			
//			if(g_CtXunZheng.XunZ_OK_AGV == 1)		//�ĳɼ��Ѱ�춯�������ǳɹ�
//			{
//				check_CtXunZ_OK(g_CT_XZ_MAX_Speed);		//g_Start_flag.Start_Auto_PID��������һ;				
//			}					
				
				
				
//			if(g_CtXunZheng.XunZ_OK_AGV == 0)		//�ĳɼ��Ѱ�춯�������ǳɹ�
//			{
//				check_CtXunZ_OK(g_CT_XZ_MAX_Speed);		//g_Start_flag.Start_Auto_PID��������һ;				
//			}		
		
		}
		//AGVֹͣ
		if(g_Start_flag.Stop_button_Car==1 || g_Start_flag.button_Start==0)		
		{
			if(g_Start_flag.button_Start==0)		//����ֹͣ
			{	
				g_glag_bizhang = 1;
			}
			//g_Start_flag.Stop_button_Car = 0;
			g_Start_flag.Start_Auto_PID = 0;	
//			g_CtXunZheng.XunZ_OK_AGV = 0;
			MotoStop(0);
	

			//ctxunz
		}
	}	
	else				//1:�ֶ�
	{

		if(g_Start_flag.Stop_button_Car==1 || g_Start_flag.button_Start==0)	//���ϴ��������� 0:����	
		{
			g_Start_flag.Stop_button_Car = 0;
			g_Start_flag.Start_Manu_PID	 = 0;				//����ֹͣ��־
			

		}				

	}

	
	
	
//	if(!g_Start_flag.button_Start)			//����ֹͣ
//	{
//		MotoStop(0);
//		g_Start_flag.Start_Auto_PID = 0;
//		
//		 
//	}
//	else									//��������
//	{
//		check_CtXunZ_OK(300);				//�Զ�ģʽ--�ŵ���Ѱ��
//		
//	}
}








void QJ(void)
{
//	g_agv_start = 1;g_agv_stop = 0;
//	if(Count_bin(Cdh_Num(1).num1)<4)
//	{
//		if(Cdh_Num(1).num1>0xf0)	out1=1;//++++
//		else
//			out1=2;	
//	}							
	//CtXunZheng_QH();
	//R_Q(dir,DstSpeed);
}
void HT(void)
{
//	g_agv_start = 1;g_agv_stop = 0;
//	if(Count_bin(Cdh_Num(2).num2)<4)
//	{
//		if(Cdh_Num(2).num2>0xf0)	out2=1;//++++
//		else
//			out2=2;	
//	}								
	//CtXunZheng_QH();
	//R_Q(dir,DstSpeed);
}
void ZY(void)
{
//	OS_ERR err;						
//	DwqXunZheng_L();
//	Motor_Fzhuan(1,190);
//	Motor_Fzhuan(2,200);
//	Motor_Fzhuan(3,190);
//	Motor_Fzhuan(4,200);
////	while(!(Count_bin(Cdh_Num(2).num2)>2||Count_bin(Cdh_Num(4).num4)>2))
////	{
////		OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ20ms
////	}
//	OSTimeDlyHMSM(0,0,1,500,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ20ms
//	MotoStop(1);
//	MotoStop(2);
//	CtXunZheng_QH();
}
void YY(void)
{
//	OS_ERR err;
//	DwqXunZheng_L();
//	Motor_Zzhuan(1,190);
//	Motor_Zzhuan(2,200);
//	Motor_Zzhuan(3,190);
//	Motor_Zzhuan(4,200);
////	while(!(Count_bin(Cdh_Num(1).num1)>2||Count_bin(Cdh_Num(3).num3)>2))
////	{
////		OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ20ms
////	}
//	OSTimeDlyHMSM(0,0,1,500,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ20ms
//	MotoStop(1);
//	MotoStop(2);
//	CtXunZheng_QH();	
}

void stop(void)
{
	//R_T();		
}


//void Moter_EnableAll(void)
//{
//	PDout(4)=1;//ʹ��
//	PDout(3)=1;//ʹ��		
//	PDout(1)=1;//ʹ��		
//	PDout(0)=1;//ʹ��	
//}
void MotoStop(u8 num)
{
	if(num>0 && num < 5)
	{
		AGV_CanOpen_Send3(num,0);	
	}
	else if(num==0)
	{
		AGV_CanOpen_Send3(1,0);	
		AGV_CanOpen_Send3(2,0);	
		AGV_CanOpen_Send3(3,0);	
		AGV_CanOpen_Send3(4,0);	
	}
}





void delay_rtos(u32 h,u32 m,u32 s,u32 ms)
{
	OS_ERR err;
	OSTimeDlyHMSM(h,m,s,ms,OS_OPT_TIME_HMSM_STRICT,&err);
}


AGV_Start_flag g_Start_flag = 
{
	0, 		//u8 Start_AGV_SysCode;		//ϵͳ�������
	0, 		//u8 Start_IR;				//ϵͳ�������
	0,		//u8 Start_jixie;			//ϵͳ�������
	0,		//u8 button_Start;		
	0, 		//u8 Start_Auto_PID;		//�ײ�PID�����Ŀ���--�Զ�
	0,   	//u8 Start_Manu_PID;		//�ײ�PID�����Ŀ���--�ֶ�
	0,
	0,
	1
};     
       
      














