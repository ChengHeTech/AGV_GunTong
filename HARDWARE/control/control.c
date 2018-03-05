#include "control.h" 


//上层的行走方向控制函数开始
void Zi_Dong(void)					//切到自动程序
{
	g_AGV_Sta.Car_Auto2Manu_mode = 0;
	//HmiScreenControlMode = g_AGV_Sta.Car_Auto2Manu_mode;		////操作模式--暂时没显示到触摸屏上
	
	speek("自动");
	delay_rtos(0,0,0,g_Speaker_delay);
	
}
void Shou_Dong(void)
{
	AGV_System_Stop();

	g_AGV_Sta.Car_Auto2Manu_mode = 1;

	//HmiScreenControlMode = g_AGV_Sta.Car_Auto2Manu_mode;
	//	HmiScreenRunState = 0;		//运行状态指示
	
	speek("手动");	
	delay_rtos(0,0,0,g_Speaker_delay);
}
void Qian_Jin(void)
{
	g_AGV_Sta.Car_dir = 0;

	//	HmiScreenRunState = 1;
	
	speek("前进");
	delay_rtos(0,0,0,g_Speaker_delay);
}
void Hou_Tui(void)
{
	g_AGV_Sta.Car_dir = 1;
				
	
	//	HmiScreenRunState = 1;
	speek("后退");
	delay_rtos(0,0,0,g_Speaker_delay);
}

void Ting_Zhi(void)
{
	AGV_System_Stop();
	HmiTaskState = 4;					//停止
	
	//	HmiScreenRunState = 0;
	speek("停止");
	delay_rtos(0,0,0,g_Speaker_delay);
	
}
void Qi_Dong(void)
{

		
	AGV_System_Start();
	
	HmiTaskState = 5;				//正在运行
	//HmiScreenRunState = 1;
	speek("启动");
	delay_rtos(0,0,0,g_Speaker_delay);
}
void Zuo_Fen(void)
{
	g_AGV_Sta.Car_fencha_dir = 0;			//分叉标志

	speek("左分叉");
	delay_rtos(0,0,0,g_Speaker_delay);
}

void You_Fen(void)
{
	g_AGV_Sta.Car_fencha_dir = 1;			//分叉标志
	speek("右分叉");
	delay_rtos(0,0,0,g_Speaker_delay);

}

void GunTong_R(u8 enable)
{
	
	if(enable)
	{
		guntong_start = 1;						//滚筒左转
		speek("滚筒右转");
		delay_rtos(0,0,0,g_Speaker_delay);
		
		
	}
	else
	{
		guntong_start = 0;						//滚筒左转
	}
	
	//delay_rtos(0,0,0,g_Speaker_delay);
}

void GunTong_L(u8 enable)
{
	if(enable)
	{
		guntong_start = 1;	
		guntong_fanzhuan = 1;					//滚筒右转

		speek("滚筒[=tong3]左转");
		
		delay_rtos(0,0,0,g_Speaker_delay);
	}
	else
	{
		guntong_start = 0;	
		guntong_fanzhuan = 0;					//滚筒右转
	}
	
	
	//delay_rtos(0,0,0,g_Speaker_delay);
}

void SD_Trun_L(void)
{
											//车左转向
	delay_rtos(0,0,0,g_Speaker_delay);
}

void SD_Trun_R(void)
{
											//车右转向
	
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
				delay_rtos(0,0,0,125);			//1.25秒加速				
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
				delay_rtos(0,0,0,125);			//2.5秒加速
			}		
		}
		else
		{
			*speed_zhi = temp_speed;
		}	
	
	}
	

}




