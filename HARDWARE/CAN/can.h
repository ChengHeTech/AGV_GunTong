#ifndef __CAN_H
#define __CAN_H	 
#include "my_include.h"	    

	
//0:停止1:前进 2:后退 3:左转 4:右转 5左上 6右上 7左下 8右下 9左旋 10右旋 

typedef struct
{
	int jiaodu;
	u8  SD_ir;
	u16 SD_Speed;

	



}yaokong;
	
	
	
	
	
	
//CAN1接收RX0中断使能
#define CAN1_RX0_INT_ENABLE	1		//0,不使能;1,使能.		
//CAN2接收RX0中断使能
#define CAN2_RX0_INT_ENABLE	1		//0,不使能;1,使能.	


extern u8 g_Get_RFID_buff[16];
extern u8 g_cinavi5_RXbuff[16];  //前磁导航
extern u8 g_cinavi6_RXbuff[16];	//后磁导航


extern int g_SD_buff[16];

extern u16 g_AGV_RFID_ID;//地标


extern u8  g_flag_RFID_beep;
extern u8 g_flag_Motec_init;

extern u8 g_cinavi1_RXbuff[16];  //前磁导航
extern u8 g_cinavi2_RXbuff[16];	
extern u8 g_cinavi3_RXbuff[16];  
extern u8 g_cinavi4_RXbuff[16];	//后磁导航
extern u8 g_watie_Motec_init ;				//等待500ms

extern u8 g_Init_OK_Motec;

extern yaokong g_AGV_yaokong;






										 							 				    
u8 CAN1_Mode_Init(u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode);//CAN初始化
u8 CAN2_Mode_Init(u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode);//CAN初始化
 
u8 CAN1_Send_Msg(u16 ID,char* msg,u8 len);						//发送数据

u8 CAN1_Receive_Msg(void);							//接收数据

u8 CAN2_Receive_Msg(u8 *buf);
u8 CAN2_Send_Msg(u16 ID,char* msg,u8 len);


void AGV_CanOpen_Send(void);
void AGV_CanOpen_Send1(void);
void AGV_CanOpen_Send2(void);
void AGV_CanOpen_Send3(u8 node_id,int speed);
void Motec_init(void);

void check_Motec_init(void);






#endif

















