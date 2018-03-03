#include "control.h" 


//上层的行走方向控制函数开始
void Zi_Dong(void)
{
	g_AGV_Status.Car_mode = 0;			//切到自动程序
	g_AGV_Status.Car_Speaker_flag=1;
	HmiScreenControlMode = g_AGV_Status.Car_mode;
	
	osdelay_ms(g_Speaker_delay);
}
void Shou_Dong(void)
{
	AGV_System_Stop();					//切到手动前先发个停止
	g_AGV_Status.Car_mode = 1;			//切到手动程序
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

void gongwei_duijie(void)							//工位对接
{
	//g_AGV_Status.Car_dir = 1;				//
	g_AGV_Status.Car_Speaker_flag=4;
	HmiScreenRunState = 1;
	
	osdelay_ms(g_Speaker_delay);
}
void Hou_Tui(void)
{
	g_AGV_Status.Car_dir = 1;				//后退
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
	//如果没有任务，弹出提示界面
//	if(HmiTask==0)
//	{
//		HmiScreenSetGet = QiDongTiShiJieMian;
//	}
//	else
//	{
		AGV_System_Start();

		g_AGV_Status.Car_Speaker_flag=7;
		

		//任务状态为正在运行
		HmiTaskState = 5;
		HmiScreenRunState = 1;
	
		osdelay_ms(g_Speaker_delay);
//	}
}
void Zuo_Fen(void)
{
	g_AGV_Status.Car_fencha_dir=0;				//分叉标志
	g_AGV_Status.Car_Speaker_flag=8;

	
	osdelay_ms(g_Speaker_delay);
}
	//void Zhong_Fen(void)
	//{
	//	g_AGV_Status.Car_fencha_dir=0;				//分叉标志
	//	g_AGV_Status.Car_Speaker_flag=9;
	//	
	//	osdelay_ms(g_Speaker_delay);
	//}
void You_Fen(void)
{
	g_AGV_Status.Car_fencha_dir=1;				//分叉标志
	g_AGV_Status.Car_Speaker_flag=10;
	
	osdelay_ms(g_Speaker_delay);

}

void GunTong_Trun_L_UP(void)					//左转上货
{
	
	agv_routr2station.guntong_L = 1;
	agv_routr2station.guntong_R = 0;
	g_AGV_Status.Car_Speaker_flag=11;
	
	osdelay_ms(g_Speaker_delay);
	

	


}
void GunTong_Trun_L_DOWN(void)					//左转卸货
{
	
	agv_routr2station.guntong_L = 1;
	agv_routr2station.guntong_R = 0;
	g_AGV_Status.Car_Speaker_flag=11;
	
	osdelay_ms(g_Speaker_delay);
	
	
	


}
void GunTong_Trun_R_UP(void)					//右转上货
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



////速度PWM赋值判断函数
////speed_min1：如果设定速度小于改量则直接将速度值赋值给PWM
////speed_zhi： 欲赋速度值
//void Ruan_Qi(u16 speed_min1,u16 speed_zhi)
//{	
//		if(speed_zhi>speed_min1)		 //软启动
//		{
//			PWM_val(TIM4,2,speed_min1);
//			osdelay_ms(20);
//			PWM_val(TIM4,2,speed_zhi);
//		}
//		else												 //速度低时直接赋值
//		{	
//			PWM_val(TIM4,2,speed_zhi);//当按启动时将屏幕设定速度再赋值给车。	
//		}
//}




