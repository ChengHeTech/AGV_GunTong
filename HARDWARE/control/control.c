#include "control.h" 


//�ϲ�����߷�����ƺ�����ʼ
void Zi_Dong(void)					//�е��Զ�����
{
	g_AGV_Sta.Car_Auto2Manu_mode = 0;
	//HmiScreenControlMode = g_AGV_Sta.Car_Auto2Manu_mode;		////����ģʽ--��ʱû��ʾ����������
	
	speek("�Զ�");
	delay_rtos(0,0,0,g_Speaker_delay);
	
}
void Shou_Dong(void)
{
	AGV_System_Stop();

	g_AGV_Sta.Car_Auto2Manu_mode = 1;

	//HmiScreenControlMode = g_AGV_Sta.Car_Auto2Manu_mode;
	//	HmiScreenRunState = 0;		//����״ָ̬ʾ
	
	speek("�ֶ�");	
	delay_rtos(0,0,0,g_Speaker_delay);
}
void Qian_Jin(void)
{
	g_AGV_Sta.Car_dir = 0;

	//	HmiScreenRunState = 1;
	
	speek("ǰ��");
	delay_rtos(0,0,0,g_Speaker_delay);
}
void Hou_Tui(void)
{
	g_AGV_Sta.Car_dir = 1;
				
	
	//	HmiScreenRunState = 1;
	speek("����");
	delay_rtos(0,0,0,g_Speaker_delay);
}

void Ting_Zhi(void)
{
	AGV_System_Stop();
	HmiTaskState = 4;					//ֹͣ
	
	//	HmiScreenRunState = 0;
	speek("ֹͣ");
	delay_rtos(0,0,0,g_Speaker_delay);
	
}
void Qi_Dong(void)
{

		
	AGV_System_Start();
	
	HmiTaskState = 5;				//��������
	//HmiScreenRunState = 1;
	speek("����");
	delay_rtos(0,0,0,g_Speaker_delay);
}
void Zuo_Fen(void)
{
	g_AGV_Sta.Car_fencha_dir = 0;			//�ֲ��־

	speek("��ֲ�");
	delay_rtos(0,0,0,g_Speaker_delay);
}

void You_Fen(void)
{
	g_AGV_Sta.Car_fencha_dir = 1;			//�ֲ��־
	speek("�ҷֲ�");
	delay_rtos(0,0,0,g_Speaker_delay);

}

void GunTong_R(u8 enable)
{
	
	if(enable)
	{
		guntong_start = 1;						//��Ͳ��ת
		speek("��Ͳ��ת");
		delay_rtos(0,0,0,g_Speaker_delay);
		
		
	}
	else
	{
		guntong_start = 0;						//��Ͳ��ת
	}
	
	//delay_rtos(0,0,0,g_Speaker_delay);
}

void GunTong_L(u8 enable)
{
	if(enable)
	{
		guntong_start = 1;	
		guntong_fanzhuan = 1;					//��Ͳ��ת

		speek("��Ͳ[=tong3]��ת");
		
		delay_rtos(0,0,0,g_Speaker_delay);
	}
	else
	{
		guntong_start = 0;	
		guntong_fanzhuan = 0;					//��Ͳ��ת
	}
	
	
	//delay_rtos(0,0,0,g_Speaker_delay);
}

void SD_Trun_L(void)
{
											//����ת��
	delay_rtos(0,0,0,g_Speaker_delay);
}

void SD_Trun_R(void)
{
											//����ת��
	
	delay_rtos(0,0,0,g_Speaker_delay);
}


u16 g_RuanQi_Speed = 100;
void Ruan_Qi(u16 speed_min1,u16 * speed_zhi)
{	
	u16 temp_speed=0;
	u16 temp_cha=0;
	u16 temp_cha2=0;
	u8 temp_i=0;
	
	temp_speed = *speed_zhi;
	
	temp_cha = abs(*speed_zhi-speed_min1);
	
	if(temp_cha < 500)
	{
		if(*speed_zhi > speed_min1)
		{
			temp_cha2 = temp_cha/10;
			for(temp_i=0;temp_i<10;temp_i++)
			{
				if(temp_cha2 > temp_speed)
				{
					temp_cha2 = temp_speed;
				}	
				*speed_zhi = temp_cha2;
				temp_cha2 += temp_cha2;
				delay_rtos(0,0,0,125);			//1.25�����				
			}		
		}
		else
		{
			*speed_zhi = temp_speed;
		}

	}
	else
	{
		
		if(*speed_zhi > speed_min1)
		{
			temp_cha2 = temp_cha/20;
			for(temp_i=0;temp_i<20;temp_i++)
			{
				if(temp_cha2 > temp_speed)
				{
					temp_cha2 = temp_speed;
				}	
				*speed_zhi = temp_cha2;
				temp_cha2 += temp_cha2;
				delay_rtos(0,0,0,125);			//2.5�����
			}		
		}
		else
		{
			*speed_zhi = temp_speed;
		}	
	
	}
	

}




