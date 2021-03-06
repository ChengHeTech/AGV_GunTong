#include "motor.h"





			





#if 0
////电机驱动器
////使能信号,方向信号,引脚初始化
//void motor_init(void) 
//{
//	GPIO_InitTypeDef  GPIO_InitStructure;


//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);	//
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);	//


//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10| GPIO_Pin_11| GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;			//输出
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;			//推挽
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;		//100MHz
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;			//上拉
//	GPIO_Init(GPIOG, &GPIO_InitStructure);					//
//	GPIO_SetBits(GPIOG,GPIO_Pin_10| GPIO_Pin_11| GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15);
//		
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;			//输出
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;			//推挽
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;		//100MHz
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;			//上拉
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
#endif



//
//
//

void Motor_Zzhuan(u8 Motor,u32 speed)           //这是电机驱动口的控制处
{	
	if(speed > AGV_SYS.Motor_MAX_Speed)	//2999
	{
		speed = AGV_SYS.Motor_MAX_Speed;
	}
	switch(Motor)
	{
		case 1:									//电机1		
			AGV_CanOpen_Send3(1,speed);
		break;
		case 2:									//电机2
			AGV_CanOpen_Send3(2,speed);
		break;                                  
		case 3:									//电机3
			AGV_CanOpen_Send3(3,speed);
		break;                                  
		case 4:									//电机4
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
	else if(speed > AGV_SYS.Motor_MAX_Speed)
	{
		tmep_spd = -AGV_SYS.Motor_MAX_Speed;
	}
	else
	{
		tmep_spd = -speed;
	}
	
	switch(Motor)
	{
		case 1:									//电机1		
			AGV_CanOpen_Send3(1,tmep_spd);
		break;
		case 2:									//电机2
			AGV_CanOpen_Send3(2,tmep_spd);
		break;                                  
		case 3:									//电机3
			AGV_CanOpen_Send3(3,tmep_spd);
		break;                                  
		case 4:									//电机4
			AGV_CanOpen_Send3(4,tmep_spd);
		break;
		default:
		break;
	}
}

//
//前驱动轮的控制
//
void LunZi_Go(u8 ID,u16 temp_speed)			
{

	switch(ID)
	{	
		case 1:
			Motor_Zzhuan(1,temp_speed); 
			break;
		case 2:
			Motor_Fzhuan(2,temp_speed); 
			break;	
		case 3:
			Motor_Zzhuan(3,temp_speed); 
			break;	
		case 4:
			Motor_Fzhuan(4,temp_speed); 
			break;	
		default:
			break;
	}
	
}

void LunZi_Back(u8 ID,u16 temp_speed)			
{

	switch(ID)
	{	
		case 1:
			Motor_Fzhuan(1,temp_speed); 
			break;
		case 2:
			Motor_Zzhuan(2,temp_speed); 
			break;	
		case 3:
			Motor_Fzhuan(3,temp_speed); 
			break;	
		case 4:
			Motor_Zzhuan(4,temp_speed); 
			break;	
		default:
			break;
	}
	
}





void qianlun_TurnL(u16 temp_speed)		//前轮左转
{
	if(temp_speed > AGV_SYS.XZ_MAX_Speed)
	{
		temp_speed = AGV_SYS.XZ_MAX_Speed;
	}

	LunZi_Back(1,temp_speed);LunZi_Go(2,temp_speed);
}
void qianlun_TurnR(u16 temp_speed)		//前轮右转
{
	if(temp_speed > AGV_SYS.XZ_MAX_Speed)
	{
		temp_speed = AGV_SYS.XZ_MAX_Speed;
	}
	Motor_Zzhuan(1,temp_speed); Motor_Zzhuan(2,temp_speed);

	LunZi_Go(1,temp_speed);LunZi_Back(2,temp_speed);
}





void houlun_TurnL(u16 temp_speed)		//后轮左转
{
	if(temp_speed > AGV_SYS.XZ_MAX_Speed)
	{
		temp_speed = AGV_SYS.XZ_MAX_Speed;
	}
	
	LunZi_Back(3,temp_speed);LunZi_Go(4,temp_speed);
}
void houlun_TurnR(u16 temp_speed)		//后轮右转
{
	if(temp_speed > AGV_SYS.XZ_MAX_Speed)
	{
		temp_speed = AGV_SYS.XZ_MAX_Speed;
	}
	LunZi_Go(3,temp_speed);LunZi_Back(4,temp_speed);
}



//电位器0对应前驱动
//电位器1对应后驱动
u16 g_xz_dwq[2];
u8 g_XZ_Ok;
u8 g_XZ_Beep;

void DwqXunZheng_QH(void)
{
	u8 temp_i=60;
	u8 temp_j=60;
	int temp_cha[2]={0,0};
	

	g_xz_dwq[0] = g_After_filter[1];	
	temp_cha[0] = g_xz_dwq[0] - g_DWQ.qianlun_zhong_val;
	
	BEEP = 1;
	
	while( abs(temp_cha[0]) > 3 && temp_i--)
	{
		
		if(g_xz_dwq[0] > g_DWQ.qianlun_zhong_val)		//驱动偏右,左转
		{
			qianlun_TurnL( abs(temp_cha[0]) * AGV_SYS.XZ_DWQ_Speed_bili );			//最大速度90*10左右
		} 
		if(g_xz_dwq[0]<g_DWQ.qianlun_zhong_val)		//驱动偏左,右转
		{
			qianlun_TurnR( abs(temp_cha[0]) * AGV_SYS.XZ_DWQ_Speed_bili );
		}
		
		//OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_HMSM_STRICT,&err);
		
		g_xz_dwq[0] =  g_After_filter[1];		
		temp_cha[0] = g_xz_dwq[0] - g_DWQ.qianlun_zhong_val;
		
		
		
	}
	MotoStop(1);	
	MotoStop(2);	
	
	g_xz_dwq[1] = g_After_filter[2];	
	temp_cha[1] = g_xz_dwq[1] - g_DWQ.houlun_zhong_val;
	while( abs(temp_cha[1]) > 3 && temp_j--)
	{
		if(g_xz_dwq[1]>g_DWQ.houlun_zhong_val)		//驱动偏右,左转
		{
			houlun_TurnL( abs(temp_cha[1]) * AGV_SYS.XZ_DWQ_Speed_bili );
		}
		if(g_xz_dwq[1]<g_DWQ.houlun_zhong_val)		//驱动偏左,右转
		{
			houlun_TurnR( abs(temp_cha[1]) * AGV_SYS.XZ_DWQ_Speed_bili );
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


u8 g_CT_XZ_jiian = 15;

void CtXunZheng_qian(u8 cidaohang_id,u16 xunzheng_speed0)
{
	OS_ERR err;
	
	u16 temp_dianweiqi_1=0;
	u8 temp_flag_L_jixian0=0;
	u8 temp_flag_R_jixian0=0;
	u8 temp_flag_NoFind=0;
	
	if(cidaohang_id == 1)		//前1磁导航
	{
		while(g_CDH8_qian_1.Num<2)		//少于4个亮点		
		{									
					
			temp_dianweiqi_1 = g_After_filter[1];	//前驱动电位器
			
			if(!temp_flag_L_jixian0)			//左极限未到位
			{
				if(temp_dianweiqi_1 > (g_DWQ.qianlun_L_val+g_CT_XZ_jiian))	//轮子左转电位器值变小 2.0
				{
					qianlun_TurnL(xunzheng_speed0);		//第一次左转
				}
				else						//第一次到左极限后右转
				{
					MotoStop(1);
					MotoStop(2);
					qianlun_TurnR(xunzheng_speed0);
					temp_flag_L_jixian0 = 1;	//左极限到位标志
				}				
			}
			else								//左极限到位
			{
				if(!temp_flag_R_jixian0)			//右极限未到位
				{
					if(temp_dianweiqi_1 < g_DWQ.qianlun_R_val-g_CT_XZ_jiian)	//轮子右转电位器值变大 2.0
					{
						qianlun_TurnR(xunzheng_speed0);		//右转
					}
					else						//右极限后左转
					{
						MotoStop(1);
						MotoStop(2);
						//qianlun_TurnL(xunzheng_speed0);
						temp_flag_R_jixian0 = 1;	//右极限到位标志
					}				
				}
				else							//右极限到位
				{
					DwqXunZheng_QH();			//左右遍历结束未找到磁导航,电位器寻正结束
					temp_flag_NoFind = 1;
					
					break;
				}					
			}
			OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_HMSM_STRICT,&err);	
		}	
		if(temp_flag_NoFind)		//没找到磁条
		{
			g_CtXunZheng.XunZ_OK_qian_1 = 0;
		}
		else						//找到磁条
		{
			g_CtXunZheng.XunZ_OK_qian_1 = 1;
		}
		MotoStop(1);
		MotoStop(2);		
	}
	else if(cidaohang_id == 2)		//前2磁导航
	{
		while(g_CDH8_qian_2.Num<2)		//检测到2个亮点		
		{									
					
			temp_dianweiqi_1 = g_After_filter[1];	//前驱动电位器
			
			if(!temp_flag_L_jixian0)			//左极限未到位
			{
				if(temp_dianweiqi_1 > g_DWQ.qianlun_L_val+g_CT_XZ_jiian)	//轮子左转电位器值变小 0.5
				{
					qianlun_TurnL(xunzheng_speed0);		//第一次左转
				}
				else						//第一次到左极限后右转
				{
					MotoStop(2);
					MotoStop(1);
					qianlun_TurnR(xunzheng_speed0);
					temp_flag_L_jixian0 = 1;	//左极限到位标志
				}				
			}
			else								//左极限到位
			{
				if(!temp_flag_R_jixian0)			//右极限未到位
				{
					if(temp_dianweiqi_1 < g_DWQ.qianlun_R_val-g_CT_XZ_jiian)	//轮子右转电位器值变大 2.0
					{
						qianlun_TurnR(xunzheng_speed0);		//右转
					}
					else						//右极限后左转
					{					
						MotoStop(2);
						MotoStop(1);	
						//qianlun_TurnL(xunzheng_speed0);						
						temp_flag_R_jixian0 = 1;	//右极限到位标志
					}				
				}
				else							//右极限到位
				{
					DwqXunZheng_QH();			//左右遍历结束未找到磁导航,电位器寻正结束
					temp_flag_NoFind = 1;
					
					break;
				}					
			}
			OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_HMSM_STRICT,&err);	
		}
		if(temp_flag_NoFind)		//没找到磁条
		{
			g_CtXunZheng.XunZ_OK_qian_2 = 0;
		}
		else						//找到磁条
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
	u8 temp_flag_L_jixian=0;		//左极限到位标志
	u8 temp_flag_R_jixian=0;		//右极限到位标志
	u8 temp_flag_NoFind1=0;
	
	if(cidaohang_id == 1)		//后1磁导航
	{
		while(g_CDH8_hou_1.Num<2)		//检测到2个亮点		
		{									
					
			temp_dianweiqi_2 = g_After_filter[2];	//后驱动电位器
			
			if(!temp_flag_L_jixian)			//左极限未到位
			{
				if(temp_dianweiqi_2 > g_DWQ.houlun_L_val+g_CT_XZ_jiian)	//轮子左转电位器值变小 2.0
				{
					houlun_TurnL(xunzheng_speed);		//第一次左转
				}
				else						//第一次到左极限后右转
				{
					MotoStop(3);
					MotoStop(4);
					houlun_TurnR(xunzheng_speed);
					temp_flag_L_jixian = 1;	//左极限到位标志
				}				
			}
			else								//左极限到位
			{
				if(!temp_flag_R_jixian)			//右极限未到位
				{
					if(temp_dianweiqi_2 < g_DWQ.houlun_R_val-g_CT_XZ_jiian)	//轮子右转电位器值变大 2.0
					{
						houlun_TurnR(xunzheng_speed);		//右转
					}
					else						//右极限后左转
					{
						MotoStop(3);
						MotoStop(4);
						//houlun_TurnL(xunzheng_speed);
						temp_flag_R_jixian = 1;	//右极限到位标志
					}				
				}
				else							//右极限到位
				{
					DwqXunZheng_QH();			//左右遍历结束未找到磁导航,电位器寻正结束
					temp_flag_NoFind1 = 1;
					break;
				}					
			}
			OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_HMSM_STRICT,&err);	
		}	
		if(temp_flag_NoFind1)		//没找到磁条
		{
			g_CtXunZheng.XunZ_OK_hou_1 = 0;
		}
		else						//找到磁条
		{
			g_CtXunZheng.XunZ_OK_hou_1 = 1;
		}	
		MotoStop(3);
		MotoStop(4);			
	}
	else if(cidaohang_id == 2)		//后2磁导航
	{
		while(g_CDH8_hou_2.Num<2)		//检测到2个亮点		
		{									
					
			temp_dianweiqi_2 = g_After_filter[2];	//后驱动电位器
			
			if(!temp_flag_L_jixian)			//左极限未到位
			{
				if(temp_dianweiqi_2 > g_DWQ.houlun_L_val+g_CT_XZ_jiian)	//轮子左转电位器值变小 2.0
				{
					houlun_TurnL(xunzheng_speed);		//第一次左转
				}
				else						//第一次到左极限后右转
				{
					MotoStop(4);
					MotoStop(3);
					houlun_TurnR(xunzheng_speed);
					temp_flag_L_jixian = 1;	//左极限到位标志
				}				
			}
			else								//左极限到位
			{
				if(!temp_flag_R_jixian)			//右极限未到位
				{
					if(temp_dianweiqi_2 < g_DWQ.houlun_R_val-g_CT_XZ_jiian)	//轮子右转电位器值变大 2.0
					{
						houlun_TurnR(xunzheng_speed);		//右转
					}
					else						//右极限后左转
					{
						MotoStop(4);
						MotoStop(3);						
						//houlun_TurnL(xunzheng_speed);
						temp_flag_R_jixian = 1;	//右极限到位标志
					}				
				}
				else							//右极限到位
				{
					DwqXunZheng_QH();			//左右遍历结束未找到磁导航,电位器寻正结束
					temp_flag_NoFind1 = 1;
					break;					
				}					
			}
			OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_HMSM_STRICT,&err);	
		}
		if(temp_flag_NoFind1)		//没找到磁条
		{
			g_CtXunZheng.XunZ_OK_hou_2 = 0;
		}
		else						//找到磁条
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
	
	if(!g_AGV_Sta.Car_dir)	//0:前进
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
	else				//1:后退
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
	g_Start_flag.Start_Auto_PID = temp_Val;	//1:找到磁条 0:未找到
	if(temp_Val)
	{
		Ruan_Qi(g_RuanQi_Speed,&AGV_SYS.Car_Auto_Speed);
	}

		
	
	
	

}

void AGV_System_Stop(void)
{
	//MotoStop(0);
	g_Start_flag.Stop_AGV_SysCode = 1;
	delay_rtos(0,0,0,100);

}	
void AGV_System_Start(void)
{
	g_Start_flag.Start_AGV_SysCode = 1;
	delay_rtos(0,0,0,100);
}


u8 g_glag_bizhang;
void AGV_Stop2Start(void)
{

//	if(预留1 == 0)							//上位机启动信号
//	{
//		g_Start_flag.button_Start = 1;
//	}			
	if(g_shoudong_start == 1)				//短触发 -- 触摸屏启动按键 1有效
	{		
		g_Start_flag.Start_button_Car = 1;
	}		
	if(AGV_input_24V_buff[1]==1 && AGV_input_24V_buff[0]==0)	
	{
		g_Start_flag.Start_button_Car = 1;	//短触发--车辆面板启动按键
		
		
	}
	if(g_Start_flag.Start_AGV_SysCode)		//长触发--程序调用这个变量来启动停止 //1启动
	{
		g_Start_flag.Start_AGV_SysCode = 0;
		g_Start_flag.Start_button_Car = 1;
	}	
	
	
	
	if(g_Start_flag.Start_IR)				//长触发--程序调用这个变量来启动停止 //1启动
	{
		g_Start_flag.button_Start = 1;
	}	

	if(g_Start_flag.Start_jixie)			//长触发--程序调用这个变量来启动停止 //1启动
	{
		g_Start_flag.button_Start = 1;
	}	



//	if(预留2 == 1)							//上位机停止信号
//	{
//		g_Start_flag.button_Start = 0;
//	}			
	if(g_shoudong_stop == 1)				//短触发--触摸屏停止按键 1有效
	{
		g_Start_flag.Stop_button_Car = 1;
	}			
	if(AGV_input_24V_buff[0]==1)			//短触发--车辆面板停止按键 -- 系统程序中停车也用这个变量停
	{
		g_Start_flag.Stop_button_Car = 1;
	
	}	
	if(g_Start_flag.Stop_AGV_SysCode)		//长触发--程序调用这个变量来启动停止 //1启动
	{
		g_Start_flag.Stop_AGV_SysCode = 0;
		g_Start_flag.Stop_button_Car = 1;
	}			

	
	
	if(!g_Start_flag.Start_IR)				//长触发--//程序调用这个变量来启动停止 //1启动
	{
		g_Start_flag.button_Start = 0;
	}		

	
	if(!g_Start_flag.Start_jixie)			//长触发--程序调用这个变量来启动停止 //1启动
	{
		g_Start_flag.button_Start = 0;
	}	
	
//	if(g_Start_flag.button_Start == 1)//避障语音
//	{
//	
//	}
//	else
//	{
//	
//	}
//	if(g_Start_flag.Start_button_Car == 1)
//	{
//		speek("启动");
//	}	
//	if(g_Start_flag.Stop_button_Car == 1)
//	{
//		speek("停止");
//	}
	

	if(!g_AGV_Sta.Car_Auto2Manu_mode)	//0:自动
	{
		//AGV磁条寻正
		if(g_Start_flag.Start_button_Car==1 && g_Start_flag.button_Start==1)	
		{
			g_Start_flag.Start_button_Car = 0;			//清除自动启动标志
			g_Start_flag.Stop_button_Car = 0;
			if(!g_Start_flag.Start_Auto_PID)			//自动模式未运行		-- 这块要修改?
			{
				//自动模式--磁导航寻正

				check_CtXunZ_OK(AGV_SYS.XZ_CiTiao_Speed);		//g_Start_flag.Start_Auto_PID在这里置一;				
							
			}
		}
		//AGV启动
		if(g_Start_flag.Stop_button_Car==0 && g_Start_flag.button_Start==1)				//避障未触发
		{
			

			if(g_glag_bizhang == 1)
			{				
				check_CtXunZ_OK(AGV_SYS.XZ_CiTiao_Speed);		//g_Start_flag.Start_Auto_PID在这里置一;	
				g_glag_bizhang = 0;					
			}
			
//			if(g_CtXunZheng.XunZ_OK_AGV == 1)		//改成检测寻轨动作而不是成功
//			{
//				check_CtXunZ_OK(AGV_SYS.XZ_CiTiao_Speed);		//g_Start_flag.Start_Auto_PID在这里置一;				
//			}					
				
				
				
//			if(g_CtXunZheng.XunZ_OK_AGV == 0)		//改成检测寻轨动作而不是成功
//			{
//				check_CtXunZ_OK(AGV_SYS.XZ_CiTiao_Speed);		//g_Start_flag.Start_Auto_PID在这里置一;				
//			}		
		
		}
		//AGV停止
		if(g_Start_flag.Stop_button_Car==1 || g_Start_flag.button_Start==0)		
		{
			if(g_Start_flag.button_Start==0)		//避障停止
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
	else				//1:手动
	{

		if(g_Start_flag.Stop_button_Car==1 || g_Start_flag.button_Start==0)	//避障传感器触发 0:触发	
		{
			g_Start_flag.Stop_button_Car = 0;
			g_Start_flag.Start_Manu_PID	 = 0;				//给键停止标志
			

		}				

	}

	
	
	
//	if(!g_Start_flag.button_Start)			//按键停止
//	{
//		MotoStop(0);
//		g_Start_flag.Start_Auto_PID = 0;
//		
//		 
//	}
//	else									//按键启动
//	{
//		check_CtXunZ_OK(300);				//自动模式--磁导航寻正
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
////		OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_HMSM_STRICT,&err); //延时20ms
////	}
//	OSTimeDlyHMSM(0,0,1,500,OS_OPT_TIME_HMSM_STRICT,&err); //延时20ms
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
////		OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_HMSM_STRICT,&err); //延时20ms
////	}
//	OSTimeDlyHMSM(0,0,1,500,OS_OPT_TIME_HMSM_STRICT,&err); //延时20ms
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
//	PDout(4)=1;//使能
//	PDout(3)=1;//使能		
//	PDout(1)=1;//使能		
//	PDout(0)=1;//使能	
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
	0, 		//u8 Start_AGV_SysCode;		//系统程序调用
	1, 		//u8 Start_IR;				//系统程序调用
	1,		//u8 Start_jixie;			//系统程序调用
	0,		//u8 button_Start;		
	0, 		//u8 Start_Auto_PID;		//底层PID函数的开关--自动
	0,   	//u8 Start_Manu_PID;		//底层PID函数的开关--手动
	0,
	0,
	1
};     
       















