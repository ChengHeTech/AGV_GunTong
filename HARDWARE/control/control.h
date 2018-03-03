#ifndef __CONTROL_H
#define __CONTROL_H
#include "my_include.h"


extern u16 g_RuanQi_Speed;


//上层的行走方向控制函数
void Zi_Dong(void);
void Shou_Dong(void);
void Qian_Jin(void);
void Hou_Tui(void);
//void Zuo_Xuan(void);
//void You_Xuan(void);
void Ting_Zhi(void);
void Qi_Dong(void);
void Zuo_Fen(void);
void Zhong_Fen(void);
void You_Fen(void);
void Cha_Sheng(void);
void Cha_Jiang(void);

void GunTong_L(u8 enable);
void GunTong_R(u8 enable);
void SD_Trun_L(void);
void SD_Trun_R(void);	
	
void Ruan_Qi(u16 speed_min,u16 *speed_zhi);



#endif
