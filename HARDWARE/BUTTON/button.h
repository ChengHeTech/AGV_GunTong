#ifndef _BUTTON_H
#define _BUTTON_H

#include "my_include.h"

typedef struct
{
	//前红外
	u8 IR_qian_jin;
	u8 IR_qian_yuan;
	//后红外
	u8 IR_hou_jin;
	u8 IR_hou_yuan;
	//前机械
	u8 JIXIE_qian;
	//后机械
	u8 JIXIE_hou;

}AGV_Senser_Enable;

extern AGV_Senser_Enable g_Senser_Enable;




//PF4 -- 停止
//PF5 -- 启动
//PF6 -- 左_滚筒红外对射 	-- (原急停)

//PF14-- 前_红外避障 		-- (牵引杆开入2)--远
//PF10-- 后_红外避障 		-- (牵引杆开入1)--远

//PF9 -- 前红外---近
//PF8 -- 后红外--近

//PA6 -- 前防撞
//PA7 -- 后防撞

//PF7 -- 右_滚筒红外对射 	-- (备用开入1) 


#define  g_button_stop 				PFin(4)
#define  g_button_start				PFin(5)

#define  g_flag_IR_qian_yuan		PFin(14)
#define  g_flag_IR_hou_yuan			PFin(10)

#define  g_flag_IR_qian_jin			PFin(9)
#define  g_flag_IR_hou_jin			PFin(8)

#define  g_flag_fangzhuang_qian		PAin(6)
#define  g_flag_fangzhuang_hou		PAin(7)

#define  g_flag_guntong_zuo			PFin(6)
#define  g_flag_guntong_you			PFin(7)


//#define  g_flag_IR_jin		PFin(4)
//#define  g_flag_IR_yuan		PFin(4)




extern u8 g_AGV_Car_STOP;	
extern u8 AGV_input_24V_buff[16];




void button_input_init(void);

void agv_24V_input(void);











#endif




