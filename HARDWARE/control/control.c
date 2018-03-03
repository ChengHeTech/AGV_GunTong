#include "control.h" 


//上层的行走方向控制函数开始
void Zi_Dong(void)
{
//	Mode_flag = 1;			//切到自动程序
//	yuyin_flag=1;
//	HmiScreenControlMode = Mode_flag;
//	
//	osdelay_ms(g_Speaker_delay);
}
void Shou_Dong(void)
{
//	QD_flag=0;					//切到手动前先发个停止
//	Mode_flag = 0;			//切到手动程序
//	yuyin_flag=2;
//	HmiScreenControlMode = Mode_flag;
//	HmiScreenRunState = 0;
//	
//	osdelay_ms(g_Speaker_delay);
}
void Qian_Jin(void)
{
//	FX_flag=1;					//由屏上的前进按钮确定控制叉车的行驶方向标志FX_flag
//	yuyin_flag=3;
//	HmiScreenRunState = 1;
//	
//	osdelay_ms(g_Speaker_delay);
}
void Hou_Zuo(void)
{
//	FX_flag=2;					//由屏上的后退左按钮确定控制叉车的行驶方向标志FX_flag
//	yuyin_flag=4;
//	HmiScreenRunState = 1;
//	
//	osdelay_ms(g_Speaker_delay);
}
void Hou_You(void)
{
//	FX_flag=3;					//由屏上的后退右按钮确定控制叉车的行驶方向标志FX_flag
//	yuyin_flag=5;
//	HmiScreenRunState = 1;
//	
//	osdelay_ms(g_Speaker_delay);
}
void Ting_Zhi(void)
{
//	QD_flag=0;					//启动标志清0
//	yuyin_flag=6;
//	
//	HmiScreenRunState = 0;
//	
//	osdelay_ms(g_Speaker_delay);
	
	AGV_System_Stop();
	HmiTaskState = 4;				//停止
	
}
void Qi_Dong(void)
{
	//	//如果没有任务，弹出提示界面
	//	if(HmiTask==0)
	//	{
	//		HmiScreenSetGet = QiDongTiShiJieMian;
	//	}
	//	else
	//	{
		//QD_flag=1;				//启动标志置1
		//PID.SumError=0;   //当再次启动是将PID的I项清零
	//		PID1.SumError=0;
		//yuyin_flag=7;
		//Ruan_Qi(SPEED_min,0);	//设定速度PWM赋值给车
	//		PWM_val(TIM4,2,speed);//当按启动时将屏幕设定速度再赋值给车。
		//任务状态为正在运行
		
		AGV_System_Start();
		
		HmiTaskState = 5;				//正在运行
		//HmiScreenRunState = 1;
	
		osdelay_ms(g_Speaker_delay);
	//}
}
void Zuo_Fen(void)
{
//	FC_flag=1;				//分叉标志
//	yuyin_flag=8;

//	
//	osdelay_ms(g_Speaker_delay);
}
void Zhong_Fen(void)
{
//	FC_flag=0;				//分叉标志
//	yuyin_flag=9;
//	
//	osdelay_ms(g_Speaker_delay);
}
void You_Fen(void)
{
//	FC_flag=2;				//分叉标志
//	yuyin_flag=10;
//	
//	osdelay_ms(g_Speaker_delay);

}

u16 g_RuanQi_Speed = 100;
//速度PWM赋值判断函数
//speed_min1：如果设定速度小于改量则直接将速度值赋值给PWM
//speed_zhi： 欲赋速度值
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
				delay_rtos(0,0,0,100);			//1秒加速				
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
				delay_rtos(0,0,0,100);			//2秒加速
			}		
		}
		else
		{
			*speed_zhi = temp_speed;
		}	
	
	}
	

}




