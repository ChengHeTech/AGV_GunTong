#include "control.h" 


//�ϲ�����߷�����ƺ�����ʼ
void Zi_Dong(void)
{
	g_AGV_Status.Car_mode = 0;			//�е��Զ�����
	g_AGV_Status.Car_Speaker_flag=1;
	HmiScreenControlMode = g_AGV_Status.Car_mode;
	
	osdelay_ms(g_Speaker_delay);
}
void Shou_Dong(void)
{
	AGV_System_Stop();					//�е��ֶ�ǰ�ȷ���ֹͣ
	g_AGV_Status.Car_mode = 1;			//�е��ֶ�����
	g_AGV_Status.Car_Speaker_flag=2;
	HmiScreenControlMode = g_AGV_Status.Car_mode;
	HmiScreenRunState = 0;
	
	osdelay_ms(g_Speaker_delay);
}
void Qian_Jin(void)
{
	g_AGV_Status.Car_dir = 0;					//
	g_AGV_Status.Car_Speaker_flag=3;
	HmiScreenRunState = 1;
	
	osdelay_ms(g_Speaker_delay);
}

void gongwei_duijie(void)							//��λ�Խ�
{
	//g_AGV_Status.Car_dir = 1;				//
	g_AGV_Status.Car_Speaker_flag=4;
	HmiScreenRunState = 1;
	
	osdelay_ms(g_Speaker_delay);
}
void Hou_Tui(void)
{
	g_AGV_Status.Car_dir = 1;				//����
	g_AGV_Status.Car_Speaker_flag=5;
	HmiScreenRunState = 1;
	
	osdelay_ms(g_Speaker_delay);
}

void Ting_Zhi(void)
{
	AGV_System_Stop();
	g_AGV_Status.Car_Speaker_flag=6;
	
	HmiScreenRunState = 0;
	
	osdelay_ms(g_Speaker_delay);
}

void Qi_Dong(void)
{
	//���û�����񣬵�����ʾ����
//	if(HmiTask==0)
//	{
//		HmiScreenSetGet = QiDongTiShiJieMian;
//	}
//	else
//	{
		AGV_System_Start();

		g_AGV_Status.Car_Speaker_flag=7;
		

		//����״̬Ϊ��������
		HmiTaskState = 5;
		HmiScreenRunState = 1;
	
		osdelay_ms(g_Speaker_delay);
//	}
}
void Zuo_Fen(void)
{
	g_AGV_Status.Car_fencha_dir=0;				//�ֲ��־
	g_AGV_Status.Car_Speaker_flag=8;

	
	osdelay_ms(g_Speaker_delay);
}
	//void Zhong_Fen(void)
	//{
	//	g_AGV_Status.Car_fencha_dir=0;				//�ֲ��־
	//	g_AGV_Status.Car_Speaker_flag=9;
	//	
	//	osdelay_ms(g_Speaker_delay);
	//}
void You_Fen(void)
{
	g_AGV_Status.Car_fencha_dir=1;				//�ֲ��־
	g_AGV_Status.Car_Speaker_flag=10;
	
	osdelay_ms(g_Speaker_delay);

}

void GunTong_Trun_L_UP(void)					//��ת�ϻ�
{
	
	agv_routr2station.guntong_L = 1;
	agv_routr2station.guntong_R = 0;
	g_AGV_Status.Car_Speaker_flag=11;
	
	osdelay_ms(g_Speaker_delay);
	

	


}
void GunTong_Trun_L_DOWN(void)					//��תж��
{
	
	agv_routr2station.guntong_L = 1;
	agv_routr2station.guntong_R = 0;
	g_AGV_Status.Car_Speaker_flag=11;
	
	osdelay_ms(g_Speaker_delay);
	
	
	


}
void GunTong_Trun_R_UP(void)					//��ת�ϻ�
{
	
	agv_routr2station.guntong_R = 1;
	agv_routr2station.guntong_L = 0;
	g_AGV_Status.Car_Speaker_flag=12;
	
	
	osdelay_ms(g_Speaker_delay);


}


void GunTong_Trun_R_DOWN(void)
{
	
	agv_routr2station.guntong_R = 1;
	agv_routr2station.guntong_L = 0;
	g_AGV_Status.Car_Speaker_flag=12;
	
	
	osdelay_ms(g_Speaker_delay);


}



////�ٶ�PWM��ֵ�жϺ���
////speed_min1������趨�ٶ�С�ڸ�����ֱ�ӽ��ٶ�ֵ��ֵ��PWM
////speed_zhi�� �����ٶ�ֵ
//void Ruan_Qi(u16 speed_min1,u16 speed_zhi)
//{	
//		if(speed_zhi>speed_min1)		 //������
//		{
//			PWM_val(TIM4,2,speed_min1);
//			osdelay_ms(20);
//			PWM_val(TIM4,2,speed_zhi);
//		}
//		else												 //�ٶȵ�ʱֱ�Ӹ�ֵ
//		{	
//			PWM_val(TIM4,2,speed_zhi);//��������ʱ����Ļ�趨�ٶ��ٸ�ֵ������	
//		}
//}




