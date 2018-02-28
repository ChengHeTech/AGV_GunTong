#ifndef _RGB_H
#define _RGB_H

#include "my_include.h"

//PD4  -- 前车灯 --       (2个灯的信号并在一起)
//PD3  -- 后车灯 -- 	  (2个灯的信号并在一起)

//PB10 -- 蓝色 -- 常亮    (2个灯的信号并在一起)
//PB0  -- 黄色 -- 切换	  (2个灯的信号并在一起)


#define  Car_LED_Blue 	 PBout(10)   //高电平触发
#define  Car_LED_Yellow	 PBout(0)    //高电平触发

#define  Car_LED_Qian_Enable PDout(4)   //低电平触发
#define  Car_LED_Hou_Enable	 PDout(3)   //低电平触发





void rgb_init(void);










#endif

