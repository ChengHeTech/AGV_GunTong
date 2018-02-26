#ifndef _RGB_H
#define _RGB_H

#include "my_include.h"


//PB10 -- 蓝色 -- 前    (2个灯的信号并在一起)
//PB0  -- 蓝色 -- 后	(2个灯的信号并在一起)
#define  Car_LED_Blue_qian 	 PBout(10)   //高电平触发
#define  Car_LED_Blue_hou	 PBout(0)    //高电平触发







void rgb_init(void);










#endif

