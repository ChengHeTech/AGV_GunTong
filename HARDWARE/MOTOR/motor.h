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
	
}AGV_CtXunZheng;

typedef struct
{
//	u8 button_Car;				//�������
//	u8 button_Screen;			//������
//	u8 button_network_PC;		//��λ��
//	u8 button_yaokong_youxian;	//����ң��
	
	u8 Start_AGV_SysCode;		//ϵͳ�������
	u8 Start_IR;				//ϵͳ�������
	u8 Start_jixie;				//ϵͳ�������
	
	u8 button_Start;			
	
	u8 Start_Auto_PID;			//�ײ�PID�����Ŀ���--�Զ�
	
	u8 Start_Manu_PID;			//�ײ�PID�����Ŀ���--�ֶ�
	
	u8 Start_button_Car;		//�����̴���
	//u8 Start_Manu;

}AGV_Start_flag;




extern u16 g_AGV_Car_Speed;
extern u16 g_AGV_shoudong_Speed;
extern u16 g_AGV_shoudong_Speed_bili ;
extern u16 g_AGV_shoudong_dir;	
extern u8  g_AGV_Car_dir;				//0:ǰ��  1:����
extern u8  g_AGV_Car_fencha_dir;		//ȫ��Ψһ//0:��ֲ�  1:�ҷֲ�

extern float g_qianlun_L2R_val[2] ;		//ǰ������ת����ֵ
extern float g_houlun_L2R_val[2]  ;		//��������ת����ֵ


extern AGV_CtXunZheng g_CtXunZheng;
extern AGV_Start_flag g_Start_flag;
extern u8  g_AGV_Car_mode;				//0:�Զ�  1:�ֶ�
extern u8 g_XZ_Ok;
extern u8 g_XZ_Beep;



void motor_init(void);

void QJ(void);
void HT(void);
void ZY(void);
void YY(void);
void stop(void);
void delay_rtos(u32 h,u32 m,u32 s,u32 ms);

void Motor_Zzhuan(u8 Motor,u32 PWM);           //���ǵ�������ڵĿ��ƴ�
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



void qianlun_Go(u16 temp_speed);			//ǰ��ǰ��
void qianlun_Back(u16 temp_speed);		//ǰ�ֺ���
void houlun_Go(u16 temp_speed);			//����ǰ��
void houlun_Back(u16 temp_speed);		//���ֺ���



#endif

