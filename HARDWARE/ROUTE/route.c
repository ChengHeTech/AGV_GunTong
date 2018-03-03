#include "route.h"

u16 SystemParameter[SystemParaNum];//系统参数

u16 RouteStationNum[RouteNum]; 		//每条路径包含站点数
u16 NowRouteInfor[StationNum][StaiionInfor];   //当前路径信息
u16 StationInfor[StaiionInfor]; 
u16 HmiRouteNumFlag = 0; //上一个路径号，判断路径变化用
u16 HmiRouteCopiedNumTemp=0;//被复制路径号临时变量


u16 ProcessStepNum[ProcessNum]; 		   //每个流程包含步数
u16 NowProcessInfor[StepNum][StepInfor];  //当前流程信息
//u16 NowStepInfor[StepInfor];              //单个步骤信息

u16 HmiProcessNumFlag = 0; //上一个流程号，判断流程变化用
u16 HmiProcessCopiedNumTemp=0;//被复制流程号临时变量


//
//---------------系统------------//
//
//从系统获取一个参数 num:参数位置
u16 GetOneParameterFromSystem(u16 num)
{
	u16 buf[1];
	//读取系统参数	
	W25QXX_Read_16(buf,num,1);
	return buf[0];
}

//获取所有系统参数，并存入默认数组SystemParameter
void GetAllParameterFromSystem(void)
{
	//读取系统参数	
	W25QXX_Read_16(SystemParameter,0,SystemParaNum);
}

//设置一个参数到系统 value:参数值 num:参数序号
void SetOneParameterToSystem(u16 value,u16 num)
{
	u16 buf[1];
	buf[0] = value;
	W25QXX_Write_16(buf,num,1);
}

//设置所有参数到系统 将SystemParameter数组的数据存入Flash
void SetAllParameterToSystem()
{
	W25QXX_Write_16(SystemParameter,0,SystemParaNum);
}



//
//---------------路径------------//
//
//获取路径包含站点总数 num:路径号
u16 GetRouteStationNum(u16 num)
{
	//读取
	W25QXX_Read_16(&RouteStationNum[num-1],RouteStationNumAdress(num),1);	
	
	//超出范围置零
	if(RouteStationNum[num-1]>StationNum)
		RouteStationNum[num-1] = 0;
	return RouteStationNum[num-1];
}

//保存所有路径包含的站点数
void SetAllStationNum()
{
	W25QXX_Write_16(RouteStationNum,RouteStationNumAdress(1),RouteNum);
}
//获取路径信息,num:路径号
void GetRouteData(u16 num)
{
	u16 i;
	//读取站点总数
	HmiStationNum = GetRouteStationNum(num);		//更新到触摸屏上
	
	//读取站点信息
	for(i=0;i<RouteStationNum[num-1];i++)
	{
		W25QXX_Read_16(&NowRouteInfor[i][0],NowStationInforAdress(num,i),StaiionInfor);
	}
}


//保存路径信息,num:路径号
void SetRouteData(u16 num)
{
	u16 i;
	//保存路径包含站点数
	RouteStationNum[HmiRouteNum-1] = HmiStationNum;
	//保存
	W25QXX_Write_16(&RouteStationNum[HmiRouteNum-1],RouteStationNumAdress(HmiRouteNum),1);	

	
	//保存路径站点包含信息
	for(i=0;i<RouteStationNum[num-1];i++)
	{
		W25QXX_Write_16(&NowRouteInfor[i][0],NowStationInforAdress(num,i),StaiionInfor);	
//		osdelay_ms(10);
	}
}


//更新路径当前站点动作的数据到界面
void UpdataStationToHmi()
{
		HmiRoadData0  = NowRouteInfor[HmiStationSerialNum-1][0];
		HmiRoadData1  = NowRouteInfor[HmiStationSerialNum-1][1];
		HmiRoadData2  = NowRouteInfor[HmiStationSerialNum-1][2];
		HmiRoadData3  = NowRouteInfor[HmiStationSerialNum-1][3];
		HmiRoadData4  = NowRouteInfor[HmiStationSerialNum-1][4];
		HmiRoadData5  = NowRouteInfor[HmiStationSerialNum-1][5];
		HmiRoadData6  = NowRouteInfor[HmiStationSerialNum-1][6];
//		HmiRoadData7  = NowRouteInfor[HmiStationSerialNum-1][7];
//		HmiRoadData8  = NowRouteInfor[HmiStationSerialNum-1][8];
//		HmiRoadData9  = NowRouteInfor[HmiStationSerialNum-1][9];
//		HmiRoadData10 = NowRouteInfor[HmiStationSerialNum-1][10];
//		HmiRoadData11 = NowRouteInfor[HmiStationSerialNum-1][11];
//		HmiRoadData12 = NowRouteInfor[HmiStationSerialNum-1][12];
//		HmiRoadData13 = NowRouteInfor[HmiStationSerialNum-1][13];
//		HmiRoadData14 = NowRouteInfor[HmiStationSerialNum-1][14];
//		HmiRoadData15 = NowRouteInfor[HmiStationSerialNum-1][15];
//		HmiRoadData16 = NowRouteInfor[HmiStationSerialNum-1][16];
//		HmiRoadData17 = NowRouteInfor[HmiStationSerialNum-1][17];
//		HmiRoadData18 = NowRouteInfor[HmiStationSerialNum-1][18];
//		HmiRoadData19 = NowRouteInfor[HmiStationSerialNum-1][19];
}

//从界面更新路径站点数据到当前
void UpdataStationToNow()
{
		NowRouteInfor[HmiStationSerialNum-1][0]  = HmiRoadData0 ;
		NowRouteInfor[HmiStationSerialNum-1][1]  = HmiRoadData1 ;
		NowRouteInfor[HmiStationSerialNum-1][2]  = HmiRoadData2 ;
		NowRouteInfor[HmiStationSerialNum-1][3]  = HmiRoadData3 ;
		NowRouteInfor[HmiStationSerialNum-1][4]  = HmiRoadData4 ;
		NowRouteInfor[HmiStationSerialNum-1][5]  = HmiRoadData5 ;
		NowRouteInfor[HmiStationSerialNum-1][6]  = HmiRoadData6 ;
//		NowRouteInfor[HmiStationSerialNum-1][7]  = HmiRoadData7 ;
//		NowRouteInfor[HmiStationSerialNum-1][8]  = HmiRoadData8 ;
//   	NowRouteInfor[HmiStationSerialNum-1][9]  = HmiRoadData9 ;
//		NowRouteInfor[HmiStationSerialNum-1][10] = HmiRoadData10;
//		NowRouteInfor[HmiStationSerialNum-1][11] = HmiRoadData11;
//		NowRouteInfor[HmiStationSerialNum-1][12] = HmiRoadData12;
//   	NowRouteInfor[HmiStationSerialNum-1][13] = HmiRoadData13;
//		NowRouteInfor[HmiStationSerialNum-1][14] = HmiRoadData14;
//		NowRouteInfor[HmiStationSerialNum-1][15] = HmiRoadData15;
//		NowRouteInfor[HmiStationSerialNum-1][16] = HmiRoadData16;
//		NowRouteInfor[HmiStationSerialNum-1][17] = HmiRoadData17;
//		NowRouteInfor[HmiStationSerialNum-1][18] = HmiRoadData18;
//		NowRouteInfor[HmiStationSerialNum-1][19] = HmiRoadData19;
}




//清零重置路径站点数据到界面
void ClearStationToHmi()
{
	//默认站点信息
	HmiRoadData0  = 0;	//远程红外 默认为0 0：保持1：开2：关
	HmiRoadData1  = 0;	//到站延时时间
	HmiRoadData2  = 0;	//岔路口左分叉 0：保持1：左分叉 2：右分叉	
	HmiRoadData3  = 0;	//叉臂下 0：保持 1：叉臂上 2：叉臂下	
	HmiRoadData4  = 0;	//档位默认选择慢速 0：保持 1：慢速 2：中速 3：快速   	       
	HmiRoadData5  = 666;	//地标默认
	HmiRoadData6  = 0;	//动作	0：停止	1：前进	2:后左	3：后右  4：通过
//	HmiRoadData7  = 0;	//工作区
//	HmiRoadData8  = 5;	//快旋时间
//	HmiRoadData9  = 1;	//旋转次数
//	HmiRoadData10 = 0;	//电梯的使用与否 0:不使用1:去一楼2:去三楼 //使用电梯:叉车从一楼叉货上三楼或叉车从三楼叉货上一楼,其余为不使用电梯
//	HmiRoadData11 = 0;  //位置
//	HmiRoadData12 = 0;  //左磁导航模拟地标不触发
//	HmiRoadData13 = 0;  //右磁导航模拟地标不触发
//	HmiRoadData14 = 0;  //前磁导航模拟地标不触发
//	HmiRoadData15 = 1;  //左磁导航模拟地标触发1次
//	HmiRoadData16 = 1;  //右磁导航模拟地标触发1次
//	HmiRoadData17 = 1;  //前磁导航模拟地标触发1次
//	HmiRoadData18 = 0;  //设备给车发送的启动信号
//	HmiRoadData19 = 0;  //叉臂避障

}




//
//---------------流程------------//
//
//保存及更新流程数据（当前操作的流程信息）
void	SetProcessData()
{
	u16 i = 0;
	//流程步数
	
	ProcessStepNum[HmiProcessNum-1] = HmiStepNum;
	//保存
	W25QXX_Write_16(&ProcessStepNum[HmiProcessNum-1],ProcessStepNumAdress(HmiProcessNum),1);	

	
	//流程信息
	//更新当前单步的起始路径号
	NowProcessInfor[HmiProcessSerialNum-1][0] = HmiProcessStartNum;
	//更新当前单步的动作
	NowProcessInfor[HmiProcessSerialNum-1][1] = HmiProcessAction;
	//更新当前单步的结束路径号或重复执行次数
	NowProcessInfor[HmiProcessSerialNum-1][2] = HmiProcessStopNum;
	
	//保存
	for(i=0;i<HmiStepNum;i++)
		W25QXX_Write_16(&NowProcessInfor[i][0],NowStepInforAdress(HmiProcessNum,i),StepInfor);	
}


//获取流程包含步数
u16	GetProcessStepNum(u16 num)
{
	//读取
	W25QXX_Read_16(&ProcessStepNum[num-1],ProcessStepNumAdress(num),1);	
	
	return ProcessStepNum[num-1];
}

//保存所有流程包含步数
void SetAllStepNum()
{
	W25QXX_Write_16(ProcessStepNum,ProcessStepNumAdress(1),ProcessNum);
}

//获取及更新流程数据（当前操作的流程信息）
void	GetProcessData()
{
	u16 i = 0;
	//流程步数
	
	//读取
	W25QXX_Read_16(&ProcessStepNum[HmiProcessNum-1],ProcessStepNumAdress(HmiProcessNum),1);	
	//更新
	HmiStepNum = ProcessStepNum[HmiProcessNum-1];
	
	HmiProcessSerialNum = 1;
	
	//流程步数超过设定最大值，直接置0
	if(HmiStepNum>StepNum)
	{
		//流程数设置为0
		HmiStepNum = 0;
		//序号设置为0
		HmiProcessSerialNum = 0;
	}
	
	//流程信息
	//读取
	for(i=0;i<HmiStepNum;i++)
		W25QXX_Read_16(&NowProcessInfor[i][0],NowStepInforAdress(HmiProcessNum,i),StepInfor);	
	
	//更新当前单步的起始路径号
	HmiProcessStartNum = 	NowProcessInfor[HmiProcessSerialNum-1][0];
	//更新当前单步的动作
	HmiProcessAction = 	NowProcessInfor[HmiProcessSerialNum-1][1];
	//更新当前单步的结束路径号或重复执行次数
	HmiProcessStopNum = 	NowProcessInfor[HmiProcessSerialNum-1][2];
}


//获取及更新指定流程数据（指定的流程信息）
void	GetProcessDataFrom(u16 num)
{
	u16 i = 0;
	//流程步数
	
	//读取
	W25QXX_Read_16(&ProcessStepNum[num-1],ProcessStepNumAdress(num),1);	
	//更新
	HmiStepNum = ProcessStepNum[num-1];
	
	HmiProcessSerialNum = 1;
	
	//流程步数超过设定最大值，直接置0
	if(HmiStepNum>StepNum)
	{
		//流程数设置为0
		HmiStepNum = 0;
		//序号设置为0
		HmiProcessSerialNum = 0;
	}
	
	//流程信息
	//读取
	for(i=0;i<HmiStepNum;i++)
		W25QXX_Read_16(&NowProcessInfor[i][0],NowStepInforAdress(num,i),StepInfor);	
	
	//更新当前单步的起始路径号
	HmiProcessStartNum = 	NowProcessInfor[HmiProcessSerialNum-1][0];
	//更新当前单步的动作
	HmiProcessAction = 	NowProcessInfor[HmiProcessSerialNum-1][1];
	//更新当前单步的结束路径号或重复执行次数
	HmiProcessStopNum = 	NowProcessInfor[HmiProcessSerialNum-1][2];
}



//更新流程数据到界面
void UpdataProcessToHmi()
{
	//更新当前单步的起始路径号
	HmiProcessStartNum = 	NowProcessInfor[HmiProcessSerialNum-1][0];
	//更新当前单步的动作
	HmiProcessAction = 	NowProcessInfor[HmiProcessSerialNum-1][1];
	//更新当前单步的结束路径号或重复执行次数
	HmiProcessStopNum = 	NowProcessInfor[HmiProcessSerialNum-1][2];
}

//更新流程数据到界面
void ClearStepToHmi()
{
	//更新当前单步的起始路径号
	HmiProcessStartNum = 1;
	//更新当前单步的动作
	HmiProcessAction = 0;
	//更新当前单步的结束路径号或重复执行次数
	HmiProcessStopNum = 0;
}

//插入及更新流程数据（当前操作的流程信息）
void	InsertProcessData()
{
	u16 i,j;
	//流程步数
	
	ProcessStepNum[HmiProcessNum-1] = HmiStepNum;
	//保存
	W25QXX_Write_16(&ProcessStepNum[HmiProcessNum-1],ProcessStepNumAdress(HmiProcessNum),1);	

	
	//流程信息
	//将当前及后面所数据向后移动一位
	for(i=HmiStepNum;i>=HmiProcessSerialNum;i--)
	{
		for(j=0;j<StepInfor;j++)
		{
			NowProcessInfor[i-1][j] = NowProcessInfor[i-1-1][j];
		}
	}
	
	//更新新插入数据
	
	//更新当前单步的起始路径号
	NowProcessInfor[HmiProcessSerialNum-1][0] = HmiProcessStartNum;
	//更新当前单步的动作
	NowProcessInfor[HmiProcessSerialNum-1][1] = HmiProcessAction;
	//更新当前单步的结束路径号或重复执行次数
	NowProcessInfor[HmiProcessSerialNum-1][2] = HmiProcessStopNum;

		
	//保存
	for(i=0;i<HmiStepNum;i++)
		W25QXX_Write_16(&NowProcessInfor[i][0],NowStepInforAdress(HmiProcessNum,i),StepInfor);	
}


//删除及更新流程数据（当前操作的流程信息）
void	DeleteProcessData()
{
	u16 i,j;
	//流程步数
	if(HmiStepNum>0)
	{
		//将后面所数据向前移动一位
		if((HmiStepNum>0)&&(HmiStepNum!=HmiProcessSerialNum))
		{
			for(i=HmiProcessSerialNum;i<HmiStepNum;i++)
			{
				for(j=0;j<StepInfor;j++)
				{
					NowProcessInfor[i-1][j] = NowProcessInfor[i][j];
				}
			}
		}
		
		HmiStepNum--;
		if(HmiStepNum==0)
			HmiProcessSerialNum = 0;
		else
			if((HmiStepNum+1)==HmiProcessSerialNum)
				HmiProcessSerialNum--;
		
		//保存
		for(i=0;i<HmiStepNum;i++)
			W25QXX_Write_16(&NowProcessInfor[i][0],NowStepInforAdress(HmiProcessNum,i),StepInfor);	
		
		ProcessStepNum[HmiProcessNum-1] = HmiStepNum;
		//保存
		W25QXX_Write_16(&ProcessStepNum[HmiProcessNum-1],ProcessStepNumAdress(HmiProcessNum),1);	

		//更新界面
		UpdataProcessToHmi();	
	}
}







//自动界面显示信息重载
void HmiAutoReload()
{
	//如果正在执行流程，则重载路径号
	if(HmiTask == 2)					//屏幕任务: 无任务0 执行路径1 执行流程2
	{
		//获取流程信息
		GetProcessData();
		HmiRouteNum = NowProcessInfor[0][0];
	}
	//重载站点数
	//获取路径包含站点数
	HmiStationNum = GetRouteStationNum(HmiRouteNum);
	//当前地标清零
	HmiRfidNum = 0;
	
	//获取当前路径信息
	GetRouteData(HmiRouteNum);	
	//重载下一地标
	HmiNextRfidNum = NowRouteInfor[0][5];
}




void UserConfigInit(void)
{

	W25QXX_Init();			//W25QXX初始化
	
	while(W25QXX_ReadID()!=W25Q128)//检测不到W25Q128，LED闪烁
	{
		LED4 = !LED4;//DS0闪烁
		BEEP = !BEEP;
		delay_rtos(0,0,0,100);
	}
	 
	
    GetAllParameterFromSystem();		//获取所以的系统参数

    if(SystemParameter[0] != 5) 		//首次flash中没数据时或者意外导致数据丢失先刷入初始量
    {
#if 1									//为1	//车的前100个内存中写入初始量 -- 系统参数
        SystemParameter[0] = 5;			//判断是否第一次写入的标志
        SystemParameter[1] = 0;	
        SystemParameter[2] = 0;
        SystemParameter[3] = 4;			//手动速度比例 -- 4/10*3000
        SystemParameter[4] = 0; 
        SystemParameter[5] = 0; 
        SystemParameter[6] = 0;			//
        SystemParameter[7] = 0;
		
        SystemParameter[8] = 0;  		
        SystemParameter[9] = 0; 		
        SystemParameter[10] = 0; 		
		
        SystemParameter[11] = 0;		
        SystemParameter[12] = 0; 	
        SystemParameter[13] = 0; 	
        SystemParameter[14] = 0; 		
        SystemParameter[15] = 0; 		
        SystemParameter[16] = 0;
        SystemParameter[17] = 0;
        SystemParameter[18] = 0; 		
        SystemParameter[19] = 0; 		
        SystemParameter[20] = 0; 		
        SystemParameter[21] = 0;
        SystemParameter[22] = 0;
        SystemParameter[23] = 0;
        SystemParameter[24] = 0; 		//路径号
        SystemParameter[25] = 0; 		//
        SystemParameter[26] = 0; 		//
        SystemParameter[27] = 0; 		//
        SystemParameter[28] = 0; 		//
        SystemParameter[29] = 0; 		//
        SystemParameter[30] = 1;		//车号
        SystemParameter[31] = 6; 		//系统音量
        SystemParameter[32] = 1; 		//系统车速
        SystemParameter[33] = 1; 		//系统语音开关 -- 0:打开1:关闭
        SystemParameter[34] = 0; 		//车身状态灯
        SystemParameter[35] = 300; 		//低速
        SystemParameter[36] = 800; 		//中速
        SystemParameter[37] = 1500; 	//高速
        SystemParameter[38] = 300; 		//工位对接速度
        SystemParameter[39] = 0;
        SystemParameter[40] = 700;	//寻正最大速度
        SystemParameter[41] = 60;	//电位器寻正速度比
        SystemParameter[42] = 600;	//磁条上轨速度
        SystemParameter[43] = 2900;	//电机最大速度
        SystemParameter[44] = 0;
        SystemParameter[45] = 0;
        SystemParameter[46] = 0;
        SystemParameter[47] = 0;
        SystemParameter[48] = 0;
        SystemParameter[49] = 0;
        SystemParameter[50] = 25;	//自动Kp
        SystemParameter[51] = 40;    //自动Ki
        SystemParameter[52] = 0;	//自动Kd
        SystemParameter[53] = 80;	//手动Kp
        SystemParameter[54] = 100;	//手动Ki
        SystemParameter[55] = 0;	//手动Kd
        SystemParameter[56] = 10;	//PID控制时间
        SystemParameter[57] = 54;	//前轮左值
        SystemParameter[58] = 114;	//前轮中值
        SystemParameter[59] = 163;  	//前轮右值

        SystemParameter[60] = 49; 	//后轮左值
        SystemParameter[61] = 90; 	//后轮中值
        SystemParameter[62] = 135; 	//后轮右值
        SystemParameter[63] = 0; 	//
        SystemParameter[64] = 0; 	//
        SystemParameter[65] = 0; 	//
        SystemParameter[66] = 0; 	//
        SystemParameter[67] = 0; 	//
        SystemParameter[68] = 0; 	//
        SystemParameter[69] = 0; 	//
        SystemParameter[70] = 20; 	//无电报警值
        SystemParameter[71] = 0; 	//
        SystemParameter[72] = 0; 	//
        SystemParameter[73] = 0; 	//
        SystemParameter[74] = 0; 	//
        SystemParameter[75] = 0; 	//
		SystemParameter[76] = 0; 	//
        SystemParameter[77] = 0;
        SystemParameter[78] = 0;
        SystemParameter[79] = 0;
        SystemParameter[80] = 0;
        SystemParameter[81] = 0;
        SystemParameter[82] = 0;
        SystemParameter[83] = 0;
        SystemParameter[84] = 0;
        SystemParameter[85] = 0;
        SystemParameter[86] = 0;
        SystemParameter[87] = 0;
        SystemParameter[88] = 0;
        SystemParameter[89] = 0;
        SystemParameter[98] = 0; 
        SystemParameter[99] = 0; 
#endif
        //存储所有系统参数
        SetAllParameterToSystem();

#if 1
        //清除路径包含站点数
        memset(RouteStationNum, 0, RouteNum);
        //保存所有路径包含的站点数
        SetAllStationNum();

        //清除流程包含步数
        memset(ProcessStepNum, 0, ProcessNum);
        //保存所有流程包含的步数
        SetAllStepNum();
#endif
    }


	
//	
//系统参数更新到触摸屏上
//	
		
	
	//	
	//系统参数从Flash更新到系统中
	//				
	AGV_SYS.SD_Speed_bili       = 		  SystemParameter[3];	//手动速度比例 -- 4/10*3000

	AGV_SYS.ID 					=         SystemParameter[30];	//车号
	AGV_SYS.yinliang			=         SystemParameter[31]; 	//系统音量
	AGV_SYS.Auto_Speed_bili		=         SystemParameter[32]; 	//自动运行速度的比例
	AGV_SYS.Key_yuyin 			=         SystemParameter[33]; 	//系统语音开关
	AGV_SYS.Key_RGB_LED 		=         SystemParameter[34]; 	//车身状态灯
	AGV_SYS.L_speed 			=         SystemParameter[35];  //低速
	AGV_SYS.M_speed 			=         SystemParameter[36];  //中速
	AGV_SYS.H_speed 			=         SystemParameter[37]; 	//高速
	AGV_SYS.duijie_speed 		=         SystemParameter[38]; 	//工位对接速度
		   
	AGV_SYS.XZ_MAX_Speed 		=         SystemParameter[40]; 	//寻正最大速度
	AGV_SYS.XZ_DWQ_Speed_bili	=         SystemParameter[41];	//电位器寻正速度比
	AGV_SYS.XZ_CiTiao_Speed 	=         SystemParameter[42]; 	//磁条上轨速度
	AGV_SYS.Motor_MAX_Speed 	=         SystemParameter[43];	//电机最大速度


	AGV_SYS.AUTO_Kp       		=		  SystemParameter[50];	//自动Kp
	AGV_SYS.AUTO_Ki        		=		  SystemParameter[51];  //自动Ki
	AGV_SYS.AUTO_Kd        		=		  SystemParameter[52];	//自动Kd
	AGV_SYS.SD_Kp       		=		  SystemParameter[53];	//手动Kp
	AGV_SYS.SD_Ki        		=		  SystemParameter[54];	//手动Ki
	AGV_SYS.SD_Kd        		=		  SystemParameter[55];	//手动Kd
	AGV_SYS.PID_time 			=         SystemParameter[56];	//PID控制时间

	g_DWQ.qianlun_L_val        	=		  SystemParameter[57];	//前轮左值
	g_DWQ.qianlun_zhong_val     =	      SystemParameter[58];	//前轮中值
	g_DWQ.qianlun_R_val        	=		  SystemParameter[59];  //前轮右值

	g_DWQ.houlun_L_val        	=		  SystemParameter[60]; 	//后轮左值
	g_DWQ.houlun_zhong_val    	=		  SystemParameter[61]; 	//后轮中值
	g_DWQ.houlun_R_val        	=		  SystemParameter[62]; 	//后轮右值

	Battery_Warining.Warining_Val_NoBattery = SystemParameter[70];

	//	
	//系统参数从Flash更新到触摸屏上
	//				
	g_shoudong_screen_speed     = 		  SystemParameter[3];	//手动速度比例 -- 4/10*3000

	g_AGV_ID 					=         SystemParameter[30];	//车号
	g_AGV_speaker_val 			=         SystemParameter[31]; 	//系统音量
	g_sys_set_agvSPEED			=         SystemParameter[32]; 	//系统车速 -- 自动
	g_AGV_speaker_key 			=         SystemParameter[33]; 	//系统语音开关
	g_AGV_LED_car_state			=         SystemParameter[34]; 	//车身状态灯
	HmiDiSu       				=         SystemParameter[35];  //低速
	HmiZhongSu     				=         SystemParameter[36];  //中速
	HmiGaoSu      				=         SystemParameter[37]; 	//高速
	g_AGV_speed_duijie			=         SystemParameter[38]; 	//工位对接速度
			   	   
	XZ_Speed40					=         SystemParameter[40]; 	//寻正最大速度
	XZ_Speed41					=         SystemParameter[41];	//电位器寻正速度比
	XZ_Speed42					=         SystemParameter[42]; 	//磁条上轨速度
	XZ_Speed43					=         SystemParameter[43];	//电机最大速度

	g_screen_Auto_Kp			=		  SystemParameter[50];	//自动Kp
	g_screen_Auto_Ki			=		  SystemParameter[51];  //自动Ki
	g_screen_Auto_Kd			=		  SystemParameter[52];	//自动Kd
	g_screen_Manu_Kp			=		  SystemParameter[53];	//手动Kp
	g_screen_Manu_Ki			=		  SystemParameter[54];	//手动Ki
	g_screen_Manu_Kd			=		  SystemParameter[55];	//手动Kd
	g_screen_control_TIME		=         SystemParameter[56];	//PID控制时间

	g_screen_qianlun_ZuoZhi		=		  SystemParameter[57];	//前轮左值
	g_screen_qianlun_ZhongZhi	=	      SystemParameter[58];	//前轮中值
	g_screen_qianlun_YouZhi		=		  SystemParameter[59];  //前轮右值

	g_screen_houlun_ZuoZhi		=		  SystemParameter[60]; 	//后轮左值
	g_screen_houlun_ZhongZhi 	=		  SystemParameter[61]; 	//后轮中值
	g_screen_houlun_YouZhi 		=		  SystemParameter[62]; 	//后轮右值

	Li_Warning_val_NoBattery 	= 		  SystemParameter[70];


	
	switch(AGV_SYS.Auto_Speed_bili)
	{
		case 0:
				AGV_SYS.Car_Auto_Speed 	= AGV_SYS.L_speed;
			break;
		case 1:
				AGV_SYS.Car_Auto_Speed 	= AGV_SYS.M_speed;
			break;	
		case 2:
				AGV_SYS.Car_Auto_Speed 	= AGV_SYS.H_speed;
			break;	
		default :
			break;
	
	}	


//
//加载自动界面信息
//
    //HmiAutoReload();


    //获取路径包含站点数
    GetRouteStationNum(HmiRouteNum);

    //获取当前路径信息
    GetRouteData(HmiRouteNum);
	
    //获取及更新流程数据
    GetProcessData();
}


	////执行站点动作
	//void StationAction(u16 num)
	//{
	// 
	//    while(g_AGV_Sta.Car_Auto2Manu_mode  || !g_Start_flag.Start_Auto_PID )	 //非启动或者非自动
	//    {
	//        osdelay_ms(20);
	//    }

	//    HmiStationSerialNum++;
	//    //清空地标
	//    g_AGV_RFID_ID = 0;


	//	
	//	
	//    //目标地标显示
	//    HmiNextRfidNum = NowRouteInfor[num][5];								//4x90

	//    //等待目标地标
	//    while(g_AGV_RFID_ID==0 || g_AGV_RFID_ID != NowRouteInfor[num][5])	//扫到地标，是目标值的话则跳出while
	//    {
	//        osdelay_ms(10);
	//    }

	//    HmiRfidNum = g_AGV_RFID_ID;	//监测到地标后更新当前地标				//4x130


	//	
	//    //延时到站
	//    if(NowRouteInfor[num][1] > 0)
	//    {
	//        osdelay_s(NowRouteInfor[num][1] / 10);
	//        osdelay_ms((NowRouteInfor[num][1] % 10) * 100);
	//    }

	//    switch(NowRouteInfor[num][6])//停止、前进、后退左、后退右、左旋、右旋
	//    {
	//		case 0:
	//			break;	//保持上次信息
	//		case 1:		//停止
	//		case 2:		//前进
	//		case 3:		//后退左
	//		case 4:		//后退右
	//		case 6:		//左旋
	//		case 7:		//右旋
	//		{
	//			Ting_Zhi();			//到站停止			
	//		}
	//			break;
	//		case 5:
	//			break;	//通过
	//    }
	//    switch(NowRouteInfor[num][4])//速度档位判断
	//    {
	//		case 0:
	//			break;//保持上次信息
	//		case 1://低速
	//		{
	//			speek("1挡");
	//			
	//			
	///////////////////////////////////////////////到这里了			
	//			
	//			
	//			AGV_SYS.Car_Auto_Speed = HmiDiSu;
	//			osdelay_ms(g_Speaker_delay);
	//		}
	//		break;
	//		case 2://中速
	//		{
	//			speek("2挡");
	//			AGV_SYS.Car_Auto_Speed = HmiZhongSu;
	//			osdelay_ms(g_Speaker_delay);
	//		}
	//		break;
	//		case 3://高速
	//		{
	//			speek("3挡");
	//			AGV_SYS.Car_Auto_Speed = HmiGaoSu;
	//			osdelay_ms(g_Speaker_delay);
	//		}
	//		break;
	//		case 4://对接低速
	//		{
	//			speek("对接低速");
	//			AGV_SYS.Car_Auto_Speed = AGV_SYS.duijie_speed;
	//			osdelay_ms(g_Speaker_delay);
	//		}
	//		break;
	//    }
	//    switch(NowRouteInfor[num][0])//雷达避障开关判断
	//    {
	//		case 0:
	//			break;//保持上次信息
	//		case 1://开
	//		{
	////			LDBZ_flag = 0;
	////			speek("雷达打开");
	////			osdelay_ms(g_Speaker_delay);
	//		}
	//		break;
	//		case 2://关
	//		{
	////			LDBZ_flag = 1;
	////			speek("雷达关闭");
	////			osdelay_ms(g_Speaker_delay);
	//		}
	//		break;
	//    }
	//    switch(NowRouteInfor[num][19])//叉臂红外开关判断
	//    {
	//		case 0:
	//			break;//保持上次信息
	//		case 1://开
	//		{
	////			HBZ_flag = 0;
	////			speek("后开");
	////			osdelay_ms(g_Speaker_delay);
	//		}
	//		break;
	//		case 2://关
	//		{
	////			HBZ_flag = 1;
	////			speek("后关");
	////			osdelay_ms(g_Speaker_delay);
	//		}
	//		break;
	//    }

	//    switch(NowRouteInfor[num][2])//分叉判断
	//    {
	//		case 0:
	//			break;//保持上次信息
	//		case 1://左分叉
	//		{
	//			Zuo_Fen();
	//			osdelay_ms(g_Speaker_delay);
	//		}
	//		break;
	//		case 2://右分叉
	//		{
	//			You_Fen();
	//			osdelay_ms(g_Speaker_delay);
	//		}
	//		break;
	//    }


	////    switch(NowRouteInfor[num][3])//叉臂上下判断
	////    {
	////		case 0:
	////			break;//保持上次信息
	////		case 1://叉臂上升
	////		{
	////			osdelay_s(1);
	////			Cha_Sheng();
	////		}
	////		break;
	////		case 2://叉臂下降
	////		{
	////			osdelay_s(1);
	////			Cha_Jiang();
	////		}
	////		break;

	////    }

	////	//判断是否需要延时
	////	if(NowRouteInfor[num][8]!=0)
	////		osdelay_s(NowRouteInfor[num][8]);

	////    switch(NowRouteInfor[num][11])//与机械手设备通信
	////    {
	////    case 0:
	////        //没有请求进入
	////        PLC2_Data[32] = 0;
	////        break;//没有与设备交互
	////    case 1://和一号设备交互
	////    {
	////        Ting_Zhi();
	////        //向设备发送请求进入信号
	////        PLC2_Data[32] = NowRouteInfor[num][11];
	////        yuyin_flag = 22; //请求进入语音
	////        //等待准入信号
	////        while(PLC2_Data[33] != 1)
	////        {
	////            osdelay_ms(10);
	////        }
	////        Qi_Dong();
	////        yuyin_flag = 23; //允许进入语音
	////        //清除请求进入信号
	////        PLC2_Data[32] = 0;
	////        //清空准入信号
	////        PLC2_Data[33] = 0;
	////    }
	////    break;
	////    case 2://和二号设备交互
	////    {
	////        Ting_Zhi();
	////        //向设备发送请求进入信号
	////        PLC2_Data[32] = NowRouteInfor[num][11];
	////        yuyin_flag = 22; //请求进入语音
	////        //等待准入信号
	////        while(PLC2_Data[34] != 1)
	////        {
	////            osdelay_ms(10);
	////        }
	////        Qi_Dong();
	////        yuyin_flag = 23; //允许进入语音

	////        //清除请求进入信号
	////        PLC2_Data[32] = 0;
	////        //清空准入信号
	////        PLC2_Data[34] = 0;
	////    }
	////    break;
	////    case 3://和三号设备交互
	////    {
	////        Ting_Zhi();
	////        //向设备发送请求进入信号
	////        PLC2_Data[32] = NowRouteInfor[num][11];
	////        yuyin_flag = 22; //请求进入语音
	////        //等待准入信号
	////        while(PLC2_Data[35] != 1)
	////        {
	////            osdelay_ms(10);
	////        }
	////        Qi_Dong();
	////        yuyin_flag = 23; //允许进入语音

	////        //清除请求进入信号
	////        PLC2_Data[32] = 0;
	////        //清空准入信号
	////        PLC2_Data[35] = 0;
	////    }
	////    break;
	////    case 4://和四号设备交互
	////    {
	////        Ting_Zhi();
	////        //向设备发送请求进入信号
	////        PLC2_Data[32] = NowRouteInfor[num][11];
	////        yuyin_flag = 22; //请求进入语音
	////        //等待准入信号
	////        while(PLC2_Data[36] != 1)
	////        {
	////            osdelay_ms(10);
	////        }
	////        Qi_Dong();
	////        yuyin_flag = 23; //允许进入语音
	////        //清除请求进入信号
	////        PLC2_Data[32] = 0;
	////        //清空准入信号
	////        PLC2_Data[36] = 0;
	////    }
	////    break;
	////    }

	////    switch(NowRouteInfor[num][7])//进入设备工作区
	////    {
	////    case 0:
	////        PLC2_Data[38] = 0;
	////        PLC2_Data[39] = 0;
	////        PLC2_Data[40] = 0;
	////        PLC2_Data[41] = 0;
	////        break;
	////    case 1:
	////        PLC2_Data[38] = 1;
	////        break;
	////    case 2:
	////        PLC2_Data[39] = 1;
	////        break;
	////    case 3:
	////        PLC2_Data[40] = 1;
	////        break;
	////    case 4:
	////        PLC2_Data[41] = 1;
	////        break;
	////    }


	////    //AGV对电梯的使用情况
	////    switch(NowRouteInfor[num][10])
	////    {
	////    case 0:
	////        break;//电梯不使用
	////    case 1://AGV去一楼
	////    {
	////        AGV_QuYiLou();
	////    }
	////    break;
	////    case 2://AGV去三楼
	////    {
	////        AGV_QuSanLou();
	////    }
	////    break;
	////    }

	////    switch(NowRouteInfor[num][6])//动作执行再判断
	////	{
	////		case 0:
	////			break;//保持上次信息
	////		case 1:
	////			break;//停止
	////		case 2://前进
	////		{
	////			Qian_Jin();
	////			osdelay_ms(g_Speaker_delay);
	////			Qi_Dong();
	////			osdelay_ms(g_Speaker_delay);
	////		}
	////		break;
	////		case 3://后退左
	////		{
	////			Hou_Zuo();
	////			osdelay_ms(g_Speaker_delay);
	////			Qi_Dong();
	////			osdelay_ms(g_Speaker_delay);

	////		}
	////		break;
	////		case 4://后退右
	////		{
	////			Hou_You();
	////			osdelay_ms(g_Speaker_delay);
	////			Qi_Dong();
	////			osdelay_ms(g_Speaker_delay);
	////		}
	////		break;
	////		case 6://左旋
	////		{
	////			Xuan_Zhuang_Ci_Shu = NowRouteInfor[num][9];
	////			Xuan_Zhuang_Kuai_Su_time = NowRouteInfor[num][8];
	////			last_flag = FX_flag;
	////			osdelay_ms(SPEEKTIME);
	////			QD_flag = 1;
	////			//旋转后方向
	////			if(NowRouteInfor[num][18] == 0) //保持
	////			{
	////				zuoxuan(last_flag);
	////			}
	////			else
	////			{
	////				zuoxuan(NowRouteInfor[num][18]);
	////			}
	////		}
	////		break;
	////		case 7://右旋
	////		{
	////			Xuan_Zhuang_Ci_Shu = NowRouteInfor[num][9];
	////			Xuan_Zhuang_Kuai_Su_time = NowRouteInfor[num][8];
	////			last_flag = FX_flag;
	////			osdelay_ms(SPEEKTIME);
	////			QD_flag = 1;
	////			//旋转后方向
	////			if(NowRouteInfor[num][18] == 0) //保持
	////			{
	////				youxuan(last_flag);
	////			}
	////			else
	////			{
	////				youxuan(NowRouteInfor[num][18]);
	////			}
	////		}
	////		break;
	////    }
	//}









AGV_station agv_routr2station[StationNum];		//



//执行站点动作
void StationAction(u16 num)
{
 
    while(g_AGV_Sta.Car_Auto2Manu_mode  || !g_Start_flag.Start_Auto_PID )	 //非启动或者非自动
    {
        osdelay_ms(20);
    }

    HmiStationSerialNum++;
    //清空地标
    g_AGV_RFID_ID = 0;


	
	
    //目标地标显示
    HmiNextRfidNum = NowRouteInfor[num][5];								//4x90

    //等待目标地标
    while(g_AGV_RFID_ID==0 || g_AGV_RFID_ID != NowRouteInfor[num][5])	//扫到地标，是目标值的话则跳出while
    {
        osdelay_ms(10);
    }

    HmiRfidNum = g_AGV_RFID_ID;	//监测到地标后更新当前地标				//4x130


	
    //延时到站
    if(NowRouteInfor[num][1] > 0)
    {
        osdelay_s(NowRouteInfor[num][1] / 10);
        osdelay_ms((NowRouteInfor[num][1] % 10) * 100);
    }

    switch(NowRouteInfor[num][6])//停止、前进、后退左、后退右、左旋、右旋
    {
		case 0:
			break;	//保持上次信息
		case 1:		//停止
		case 2:		//前进
		case 3:		//后退左
		case 4:		//后退右
		
			Ting_Zhi();			//到站停止			
		
			break;
		case 5:
			break;	//通过
    }
    switch(NowRouteInfor[num][4])//速度档位判断
    {
		case 0:
			break;//保持上次信息
		case 1://低速
		{
			//speek("1挡");
			
			AGV_SYS.Car_Auto_Speed = HmiDiSu;
			osdelay_ms(g_Speaker_delay);

		}
		break;
		case 2://中速
		{
			//speek("2挡");
			AGV_SYS.Car_Auto_Speed = HmiZhongSu;
			osdelay_ms(g_Speaker_delay);
		}
		break;
		case 3://高速
		{
			//speek("3挡");
			AGV_SYS.Car_Auto_Speed = HmiGaoSu;
			osdelay_ms(g_Speaker_delay);
		}
		break;
		case 4://对接低速
		{
			//speek("对接低速");
			AGV_SYS.Car_Auto_Speed = AGV_SYS.duijie_speed;
			osdelay_ms(g_Speaker_delay);
		}
		break;
    }
	
	
   switch(NowRouteInfor[num][0])//远程红外
    {
		case 0:
			break;//保持上次信息
		case 1://开
		{
			g_Senser_Enable.IR_qian_yuan = 1;
			g_Senser_Enable.IR_hou_yuan  = 1;
			
//			speek("远红外打开");
//			osdelay_ms(g_Speaker_delay);
			

		}
		break;
		case 2://关
		{
			g_Senser_Enable.IR_qian_yuan = 0;
			g_Senser_Enable.IR_hou_yuan  = 0;
			
//			speek("远红外关闭");
//			osdelay_ms(g_Speaker_delay);

		}
		break;
    }
    switch(NowRouteInfor[num][19])//近程红外
    {
		case 0:
			break;//保持上次信息
		case 1://开
		{
			g_Senser_Enable.IR_qian_jin = 1;
			g_Senser_Enable.IR_hou_jin  = 1;
//			
//			speek("近红外打开");
//			osdelay_ms(g_Speaker_delay);
		}
		break;
		case 2://关
		{
			g_Senser_Enable.IR_qian_jin = 0;
			g_Senser_Enable.IR_hou_jin  = 0;
			
//			speek("近红外关闭");
//			osdelay_ms(g_Speaker_delay);
		}
		break;
    }

    switch(NowRouteInfor[num][2])//分叉判断
    {
		case 0:
			break;//保持上次信息
		case 1://左分叉
		{
			Zuo_Fen();
			osdelay_ms(g_Speaker_delay);
		}
		break;
		case 2://右分叉
		{
			You_Fen();
			osdelay_ms(g_Speaker_delay);
		}
		break;
    }


    switch(NowRouteInfor[num][3])//滚筒动作
    {
		case 0:
			break;//不转
		case 1://左侧卸货
		{
			speek("左侧卸货");
			osdelay_s(1);
			GunTong_Trun_L_DOWN();
		}
		break;
		case 2://左侧装货
		{
			speek("左侧装货");
			osdelay_s(1);
			GunTong_Trun_L_UP();
		}
		case 3://右侧卸货
		{
			speek("右侧卸货");
			osdelay_s(1);
			GunTong_Trun_R_DOWN();
		}
		break;
		case 4://右侧装货
		{
			speek("右侧装货");
			osdelay_s(1);
			GunTong_Trun_R_UP();
		}		
		break;

    }
	
//@@
//备用接口
//	
#if 0
	//判断是否需要延时
	if(NowRouteInfor[num][8]!=0)
		osdelay_s(NowRouteInfor[num][8]);

	switch(NowRouteInfor[num][11])//与机械手设备通信
	{
	case 0:
		//没有请求进入
		PLC2_Data[32] = 0;
		break;//没有与设备交互
	case 1://和一号设备交互
	{
		Ting_Zhi();
		//向设备发送请求进入信号
		PLC2_Data[32] = NowRouteInfor[num][11];
		g_AGV_Status.Car_Speaker_flag = 22; //请求进入语音
		//等待准入信号
		while(PLC2_Data[33] != 1)
		{
			osdelay_ms(10);
		}
		Qi_Dong();
		g_AGV_Status.Car_Speaker_flag = 23; //允许进入语音
		//清除请求进入信号
		PLC2_Data[32] = 0;
		//清空准入信号
		PLC2_Data[33] = 0;
	}
	break;
	case 2://和二号设备交互
	{
		Ting_Zhi();
		//向设备发送请求进入信号
		PLC2_Data[32] = NowRouteInfor[num][11];
		g_AGV_Status.Car_Speaker_flag = 22; //请求进入语音
		//等待准入信号
		while(PLC2_Data[34] != 1)
		{
			osdelay_ms(10);
		}
		Qi_Dong();
		g_AGV_Status.Car_Speaker_flag = 23; //允许进入语音

		//清除请求进入信号
		PLC2_Data[32] = 0;
		//清空准入信号
		PLC2_Data[34] = 0;
	}
	break;
	case 3://和三号设备交互
	{
		Ting_Zhi();
		//向设备发送请求进入信号
		PLC2_Data[32] = NowRouteInfor[num][11];
		g_AGV_Status.Car_Speaker_flag = 22; //请求进入语音
		//等待准入信号
		while(PLC2_Data[35] != 1)
		{
			osdelay_ms(10);
		}
		Qi_Dong();
		g_AGV_Status.Car_Speaker_flag = 23; //允许进入语音

		//清除请求进入信号
		PLC2_Data[32] = 0;
		//清空准入信号
		PLC2_Data[35] = 0;
	}
	break;
	case 4://和四号设备交互
	{
		Ting_Zhi();
		//向设备发送请求进入信号
		PLC2_Data[32] = NowRouteInfor[num][11];
		g_AGV_Status.Car_Speaker_flag = 22; //请求进入语音
		//等待准入信号
		while(PLC2_Data[36] != 1)
		{
			osdelay_ms(10);
		}
		Qi_Dong();
		g_AGV_Status.Car_Speaker_flag = 23; //允许进入语音
		//清除请求进入信号
		PLC2_Data[32] = 0;
		//清空准入信号
		PLC2_Data[36] = 0;
	}
	break;
	}

	switch(NowRouteInfor[num][7])//进入设备工作区
	{
	case 0:
		PLC2_Data[38] = 0;
		PLC2_Data[39] = 0;
		PLC2_Data[40] = 0;
		PLC2_Data[41] = 0;
		break;
	case 1:
		PLC2_Data[38] = 1;
		break;
	case 2:
		PLC2_Data[39] = 1;
		break;
	case 3:
		PLC2_Data[40] = 1;
		break;
	case 4:
		PLC2_Data[41] = 1;
		break;
	}


	//AGV对电梯的使用情况
	switch(NowRouteInfor[num][10])
	{
	case 0:
		break;//电梯不使用
	case 1://AGV去一楼
	{
		AGV_QuYiLou();
	}
	break;
	case 2://AGV去三楼
	{
		AGV_QuSanLou();
	}
	break;
	}
#endif
//
//备用接口
//@@	

    switch(NowRouteInfor[num][6])//动作执行再判断	//到站动作	 0：保持	1：停止	2:前进	3：工位对接  4：后退 
	{
		case 0:
			break;//保持上次信息
		case 1:
			break;//停止
		case 2://前进
		{
			g_AGV_Sta.Car_dir = g_AGV_Sta.Car_dir;
			Qi_Dong();			
			
		}
		break;
		case 3://工位对接
		{
//			gongwei_duijie();
//			osdelay_ms(g_Speaker_delay);
//			Qi_Dong();
//			osdelay_ms(g_Speaker_delay);

		}
		break;
		case 4://后退
		{
			g_AGV_Sta.Car_dir = !g_AGV_Sta.Car_dir;
			Qi_Dong();
			
		}
		break;
		
    }
}





//执行流程
void ActiveProcess(void)
{
    //保存流程号
    SetOneParameterToSystem(HmiProcessNum, 25);
    SystemParameter[26] = HmiTask;
    //保存任务号
    SetOneParameterToSystem(HmiTask, 26);

    //任务状态为正在运行
    HmiTaskState = 5;

    HmiTask = 2;

    //加载自动界面信息
    HmiAutoReload();

    g_AGV_Sta.Car_dir = 0; //方向切换到前进

    //跳转到自动界面
    HmiScreenSetGet = ZiDongJieMian;
}















