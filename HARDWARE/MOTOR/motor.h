#ifndef _MOTOR_H
#define _MOTOR_H

#include "my_include.h"




typedef struct
{
	u8 XunZ_OK_qian_1;
	u8 XunZ_OK_qian_2;	

	u8 XunZ_OK_hou_1;
	u8 XunZ_OK_hou_2;	
	
	u8 XunZ_OK_go_on_Both;
	u8 XunZ_OK_go_back_Both;
	
	u8 XunZ_OK_AGV;
	
}AGV_CtXunZheng;

typedef struct
{
//	u8 button_Car;				//车辆面板
//	u8 button_Screen;			//触摸屏
//	u8 button_network_PC;		//上位机
//	u8 button_yaokong_youxian;	//有线遥控
	
	u8 Start_AGV_SysCode;		//启动--系统程序调用
	u8 Stop_AGV_SysCode;		//停止--系统程序调用
	
	u8 Start_IR;				//红外避障
	u8 Start_jixie;				//机械避障
	
	u8 button_Start;			//避障传感器--总开关		
	
	u8 Start_Auto_PID;			//底层PID函数的开关--自动
	u8 Start_Manu_PID;			//底层PID函数的开关--手动
	
	u8 Start_button_Car;		//启动--总开关
	u8 Stop_button_Car;			//停止--总开关
	

}AGV_Start_flag;








extern float g_qianlun_L2R_val[2] ;		//前轮左右转向极限值
extern float g_houlun_L2R_val[2]  ;		//后轮左右转向极限值


extern AGV_CtXunZheng g_CtXunZheng;
extern AGV_Start_flag g_Start_flag;

extern u8 g_XZ_Ok;
extern u8 g_XZ_Beep;




void motor_init(void);

void QJ(void);
void HT(void);
void ZY(void);
void YY(void);
void stop(void);
void delay_rtos(u32 h,u32 m,u32 s,u32 ms);

void Motor_Zzhuan(u8 Motor,u32 PWM);           //这是电机驱动口的控制处
void Motor_Fzhuan(u8 Motor,u32 PWM);
void MotoStop(u8 num);
void Moter_EnableAll(void);
void DwqXunZheng_QH(void);
void CtXunZheng_qian(u8 cidaohang_id,u16 xunzheng_speed0);
void CtXunZheng_hou(u8 cidaohang_id,u16 xunzheng_speed);
void check_CtXunZ_OK(u16 XunZ_speed);
void AGV_System_Start(void);
void AGV_System_Stop(void);
void AGV_Stop2Start(void);

void motec_pulse(u8 speed);	//0~100
void IO_moni_pulse(u16 tem_delay);
void motec_pulse(u8 speed);	//0~100




void LunZi_Go(u8 ID,u16 temp_speed);
void LunZi_Back(u8 ID,u16 temp_speed);
	











#endif

