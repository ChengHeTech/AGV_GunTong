#ifndef _AGV_H
#define _AGV_H

#include "my_include.h"


typedef struct
{
	u8 SD_Speed_bili;
	u16 Car_SD_Speed;
	
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




extern AGV_System AGV_SYS;














#endif

