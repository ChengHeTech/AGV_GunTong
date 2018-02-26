#ifndef _BATEERY_H
#define _BATEERY_H

#include "my_include.h"

#define g_battery_RXbuff_len 128
#define g_battery_TXbuff_len 128


typedef struct
{
	u16 dianya;
	u16 Realy_mah;
	u16 Std_mah;
	u16 XunHuan_time;	//ѭ������


}battery;

extern battery g_battery;
extern char g_battery_TXbuff[g_battery_TXbuff_len];




void USART3_Configuration(u32 bound);

void DMA_Uart3_Init(void);  //﮵�ص������232תTTL

void Uart3_Start_DMA_Tx(u16 size);
void GET_Battery(void);








#endif





