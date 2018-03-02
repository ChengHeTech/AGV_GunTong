#ifndef __CDHDATA_H
#define __CDHDATA_H	 
#include "my_include.h"

typedef struct 		
{
	u8 zeroNum;			//�ŵ����յ�ĸ���
	u8 zeroLoctaion[16];//�ŵ����յ��λ��
	u8 zeroContinue;	//�ϵ��Ƿ�����
	
	u8 Num;				//��Ч�㣨�ŵ��������㣩�ĸ���
	int Distance;		//��Ч�������ĵľ���
	u8 Error;			//�쳣�㣨���졢�ֲ��һЩ���ڿ��ǵ�����Χ�ڵ������ʱ����ֵ
}Fencha_struct;				


typedef struct
{
	int moter1_speed;
	int moter2_speed;
	int moter3_speed;
	int moter4_speed;
}PIDspeed;





extern u8 n,a;
extern Fencha_struct front_cdh16,back_cdh16,backl_cdh8,backr_cdh8; //�ⲿ����һ��Fencha_struct���͵�ȫ�ֱ���
extern Fencha_struct findtemp;//�����������еĽṹ�������ⲿ����

extern Fencha_struct g_CDH8_qian_1;
extern Fencha_struct g_CDH8_qian_2;

extern Fencha_struct g_CDH8_hou_1;
extern Fencha_struct g_CDH8_hou_2;











Fencha_struct FindSpace(u16 dst,u8 num,u8 dir);//16λ�����⵽�ŵ��������ݺ���
Fencha_struct FindSpace1(u8 dst,u8 num,u8 dir);//8λ�����⵽�ŵ��������ݺ���
 		
void PID_AUTO_QianLun(u16 j_speed,float kp,float ki,float kd);
void PID_AUTO_HouLun(u16 j_speed2,float kp2,float ki2,float kd2);	//���ֵ�PID����

void PID_SD_Adjust(u16 j_speed,float kp,u16 ki,float kd);

#endif
