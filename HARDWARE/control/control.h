#ifndef __CONTROL_H
#define __CONTROL_H
#include "my_include.h"

#define SPEED_min 500//设定速度的最小限值




//上层的行走方向控制函数
void Zi_Dong(void);
void Shou_Dong(void);
void Qian_Jin(void);
void gongwei_duijie(void);
void Hou_Tui(void);
//void Zuo_Xuan(void);
//void You_Xuan(void);
void Ting_Zhi(void);
void Qi_Dong(void);
void Zuo_Fen(void);
void Zhong_Fen(void);
void You_Fen(void);


void Ruan_Qi(u16 speed_min,u16 speed_zhi);

void GunTong_Trun_L_UP(void);
void GunTong_Trun_L_DOWN(void);
void GunTong_Trun_R_UP(void);
void GunTong_Trun_R_DOWN(void);

#endif
