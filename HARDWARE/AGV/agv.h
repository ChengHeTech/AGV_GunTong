#ifndef _AGV_H
#define _AGV_H

#include "my_include.h"


typedef struct
{
	u8 SD_Speed_bili;
	//u16 Car_SD_Speed;
	
	u16 ID;
	
	u8  yinliang;
	u8	Auto_Speed_bili;
	u16	Car_Auto_Speed;
	u8  Key_yuyin;
	u8  Key_RGB_LED;
	
	u16 L_speed;
	u16 M_speed;
	u16 H_speed;
	
	u16 duijie_speed;
	
	u16 XZ_MAX_Speed;
	u16 XZ_DWQ_Speed_bili;
	u16 XZ_CiTiao_Speed;
	u16 Motor_MAX_Speed;


	float AUTO_Kp;
	float AUTO_Ki;
	float AUTO_Kd;

	float SD_Kp;
	float SD_Ki;
	float SD_Kd;
	
	u8 PID_time;
	
}AGV_System;

typedef struct
{

	u8  Car_dir;				//全局唯一//0:前进    1:后退

	u8  Car_fencha_dir;		//全局唯一//0:左分叉  1:右分叉
	u8  Car_mode ;			//0:自动  1:手动	
	
	u8  Car_Speaker_flag;
	
	u16 RFID_ID;

	
}AGV_Status;


extern AGV_System AGV_SYS;

extern AGV_Status g_AGV_Status;












#endif

