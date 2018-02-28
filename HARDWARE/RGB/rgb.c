#include "rgb.h"


//PD4  -- 前车灯 --       (2个灯的信号并在一起)
//PD3  -- 后车灯 -- 	  (2个灯的信号并在一起)

//PB10 -- 蓝色 -- 常亮    (2个灯的信号并在一起)
//PB0  -- 黄色 -- 切换	  (2个灯的信号并在一起)
//高电平触发 -- 常态下拉
void rgb_init(void) //牵引杆开出--PB10--的初始化也在这里
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//使能GPIOB时钟	
	//RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOA时钟	
	
	//行车灯GND控制 -- PD4:前灯 PD3:后灯
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);	//使能GPIOD时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉 -- 低电平触发
	GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化
	GPIO_SetBits(GPIOD,GPIO_Pin_3|GPIO_Pin_4);	
	
	
	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_10;  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//下拉
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化
	GPIO_ResetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_10);
	//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_8;
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
	//GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	//GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	//GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化
	//GPIO_SetBits(GPIOA,GPIO_Pin_15 | GPIO_Pin_8);



}
