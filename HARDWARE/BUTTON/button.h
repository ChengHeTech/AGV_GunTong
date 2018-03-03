#ifndef _BUTTON_H
#define _BUTTON_H

#include "my_include.h"

typedef struct
{
	//ǰ����
	u8 IR_qian_jin;
	u8 IR_qian_yuan;
	//�����
	u8 IR_hou_jin;
	u8 IR_hou_yuan;
	//ǰ��е
	u8 JIXIE_qian;
	//���е
	u8 JIXIE_hou;

}AGV_Senser_Enable;

extern AGV_Senser_Enable g_Senser_Enable;




//PF4 -- ֹͣ
//PF5 -- ����
//PF6 -- ��_��Ͳ������� 	-- (ԭ��ͣ)

//PF14-- ǰ_������� 		-- (ǣ���˿���2)--Զ
//PF10-- ��_������� 		-- (ǣ���˿���1)--Զ

//PF9 -- ǰ����---��
//PF8 -- �����--��

//PA6 -- ǰ��ײ
//PA7 -- ���ײ

//PF7 -- ��_��Ͳ������� 	-- (���ÿ���1) 


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




