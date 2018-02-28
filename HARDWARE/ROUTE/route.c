#include "route.h"

u16 SystemParameter[SystemParaNum];//ϵͳ����

u16 RouteStationNum[RouteNum]; 		//ÿ��·������վ����
u16 NowRouteInfor[StationNum][StaiionInfor];   //��ǰ·����Ϣ
u16 StationInfor[StaiionInfor]; 
u16 HmiRouteNumFlag = 0; //��һ��·���ţ��ж�·���仯��
u16 HmiRouteCopiedNumTemp=0;//������·������ʱ����


u16 ProcessStepNum[ProcessNum]; 		   //ÿ�����̰�������
u16 NowProcessInfor[StepNum][StepInfor];  //��ǰ������Ϣ
//u16 NowStepInfor[StepInfor];              //����������Ϣ

u16 HmiProcessNumFlag = 0; //��һ�����̺ţ��ж����̱仯��
u16 HmiProcessCopiedNumTemp=0;//���������̺���ʱ����


//
//---------------ϵͳ------------//
//
//��ϵͳ��ȡһ������ num:����λ��
u16 GetOneParameterFromSystem(u16 num)
{
	u16 buf[1];
	//��ȡϵͳ����	
	W25QXX_Read_16(buf,num,1);
	return buf[0];
}

//��ȡ����ϵͳ������������Ĭ������SystemParameter
void GetAllParameterFromSystem(void)
{
	//��ȡϵͳ����	
	W25QXX_Read_16(SystemParameter,0,SystemParaNum);
}

//����һ��������ϵͳ value:����ֵ num:�������
void SetOneParameterToSystem(u16 value,u16 num)
{
	u16 buf[1];
	buf[0] = value;
	W25QXX_Write_16(buf,num,1);
}

//�������в�����ϵͳ ��SystemParameter��������ݴ���Flash
void SetAllParameterToSystem()
{
	W25QXX_Write_16(SystemParameter,0,SystemParaNum);
}



//
//---------------·��------------//
//
//��ȡ·������վ������ num:·����
u16 GetRouteStationNum(u16 num)
{
	//��ȡ
	W25QXX_Read_16(&RouteStationNum[num-1],RouteStationNumAdress(num),1);	
	
	//������Χ����
	if(RouteStationNum[num-1]>StationNum)
		RouteStationNum[num-1] = 0;
	return RouteStationNum[num-1];
}

//��������·��������վ����
void SetAllStationNum()
{
	W25QXX_Write_16(RouteStationNum,RouteStationNumAdress(1),RouteNum);
}
//��ȡ·����Ϣ,num:·����
void GetRouteData(u16 num)
{
	u16 i;
	//��ȡվ������
	HmiStationNum = GetRouteStationNum(num);		//���µ���������
	
	//��ȡվ����Ϣ
	for(i=0;i<RouteStationNum[num-1];i++)
	{
		W25QXX_Read_16(&NowRouteInfor[i][0],NowStationInforAdress(num,i),StaiionInfor);
	}
}


//����·����Ϣ,num:·����
void SetRouteData(u16 num)
{
	u16 i;
	//����·������վ����
	RouteStationNum[HmiRouteNum-1] = HmiStationNum;
	//����
	W25QXX_Write_16(&RouteStationNum[HmiRouteNum-1],RouteStationNumAdress(HmiRouteNum),1);	

	
	//����·��վ�������Ϣ
	for(i=0;i<RouteStationNum[num-1];i++)
	{
		W25QXX_Write_16(&NowRouteInfor[i][0],NowStationInforAdress(num,i),StaiionInfor);	
//		osdelay_ms(10);
	}
}


//����·����ǰվ�㶯�������ݵ�����
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

//�ӽ������·��վ�����ݵ���ǰ
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




//��������·��վ�����ݵ�����
void ClearStationToHmi()
{
	//Ĭ��վ����Ϣ
	HmiRoadData0  = 0;	//Զ�̺��� Ĭ��Ϊ0 0������1����2����
	HmiRoadData1  = 0;	//��վ��ʱʱ��
	HmiRoadData2  = 0;	//��·����ֲ� 0������1����ֲ� 2���ҷֲ�	
	HmiRoadData3  = 0;	//����� 0������ 1������� 2�������	
	HmiRoadData4  = 0;	//��λĬ��ѡ������ 0������ 1������ 2������ 3������   	       
	HmiRoadData5  = 666;	//�ر�Ĭ��
	HmiRoadData6  = 0;	//����	0��ֹͣ	1��ǰ��	2:����	3������  4��ͨ��
//	HmiRoadData7  = 0;	//������
//	HmiRoadData8  = 5;	//����ʱ��
//	HmiRoadData9  = 1;	//��ת����
//	HmiRoadData10 = 0;	//���ݵ�ʹ����� 0:��ʹ��1:ȥһ¥2:ȥ��¥ //ʹ�õ���:�泵��һ¥�������¥��泵����¥�����һ¥,����Ϊ��ʹ�õ���
//	HmiRoadData11 = 0;  //λ��
//	HmiRoadData12 = 0;  //��ŵ���ģ��ر겻����
//	HmiRoadData13 = 0;  //�Ҵŵ���ģ��ر겻����
//	HmiRoadData14 = 0;  //ǰ�ŵ���ģ��ر겻����
//	HmiRoadData15 = 1;  //��ŵ���ģ��ر괥��1��
//	HmiRoadData16 = 1;  //�Ҵŵ���ģ��ر괥��1��
//	HmiRoadData17 = 1;  //ǰ�ŵ���ģ��ر괥��1��
//	HmiRoadData18 = 0;  //�豸�������͵������ź�
//	HmiRoadData19 = 0;  //��۱���

}




//
//---------------����------------//
//
//���漰�����������ݣ���ǰ������������Ϣ��
void	SetProcessData()
{
	u16 i = 0;
	//���̲���
	
	ProcessStepNum[HmiProcessNum-1] = HmiStepNum;
	//����
	W25QXX_Write_16(&ProcessStepNum[HmiProcessNum-1],ProcessStepNumAdress(HmiProcessNum),1);	

	
	//������Ϣ
	//���µ�ǰ��������ʼ·����
	NowProcessInfor[HmiProcessSerialNum-1][0] = HmiProcessStartNum;
	//���µ�ǰ�����Ķ���
	NowProcessInfor[HmiProcessSerialNum-1][1] = HmiProcessAction;
	//���µ�ǰ�����Ľ���·���Ż��ظ�ִ�д���
	NowProcessInfor[HmiProcessSerialNum-1][2] = HmiProcessStopNum;
	
	//����
	for(i=0;i<HmiStepNum;i++)
		W25QXX_Write_16(&NowProcessInfor[i][0],NowStepInforAdress(HmiProcessNum,i),StepInfor);	
}


//��ȡ���̰�������
u16	GetProcessStepNum(u16 num)
{
	//��ȡ
	W25QXX_Read_16(&ProcessStepNum[num-1],ProcessStepNumAdress(num),1);	
	
	return ProcessStepNum[num-1];
}

//�����������̰�������
void SetAllStepNum()
{
	W25QXX_Write_16(ProcessStepNum,ProcessStepNumAdress(1),ProcessNum);
}

//��ȡ�������������ݣ���ǰ������������Ϣ��
void	GetProcessData()
{
	u16 i = 0;
	//���̲���
	
	//��ȡ
	W25QXX_Read_16(&ProcessStepNum[HmiProcessNum-1],ProcessStepNumAdress(HmiProcessNum),1);	
	//����
	HmiStepNum = ProcessStepNum[HmiProcessNum-1];
	
	HmiProcessSerialNum = 1;
	
	//���̲��������趨���ֵ��ֱ����0
	if(HmiStepNum>StepNum)
	{
		//����������Ϊ0
		HmiStepNum = 0;
		//�������Ϊ0
		HmiProcessSerialNum = 0;
	}
	
	//������Ϣ
	//��ȡ
	for(i=0;i<HmiStepNum;i++)
		W25QXX_Read_16(&NowProcessInfor[i][0],NowStepInforAdress(HmiProcessNum,i),StepInfor);	
	
	//���µ�ǰ��������ʼ·����
	HmiProcessStartNum = 	NowProcessInfor[HmiProcessSerialNum-1][0];
	//���µ�ǰ�����Ķ���
	HmiProcessAction = 	NowProcessInfor[HmiProcessSerialNum-1][1];
	//���µ�ǰ�����Ľ���·���Ż��ظ�ִ�д���
	HmiProcessStopNum = 	NowProcessInfor[HmiProcessSerialNum-1][2];
}


//��ȡ������ָ���������ݣ�ָ����������Ϣ��
void	GetProcessDataFrom(u16 num)
{
	u16 i = 0;
	//���̲���
	
	//��ȡ
	W25QXX_Read_16(&ProcessStepNum[num-1],ProcessStepNumAdress(num),1);	
	//����
	HmiStepNum = ProcessStepNum[num-1];
	
	HmiProcessSerialNum = 1;
	
	//���̲��������趨���ֵ��ֱ����0
	if(HmiStepNum>StepNum)
	{
		//����������Ϊ0
		HmiStepNum = 0;
		//�������Ϊ0
		HmiProcessSerialNum = 0;
	}
	
	//������Ϣ
	//��ȡ
	for(i=0;i<HmiStepNum;i++)
		W25QXX_Read_16(&NowProcessInfor[i][0],NowStepInforAdress(num,i),StepInfor);	
	
	//���µ�ǰ��������ʼ·����
	HmiProcessStartNum = 	NowProcessInfor[HmiProcessSerialNum-1][0];
	//���µ�ǰ�����Ķ���
	HmiProcessAction = 	NowProcessInfor[HmiProcessSerialNum-1][1];
	//���µ�ǰ�����Ľ���·���Ż��ظ�ִ�д���
	HmiProcessStopNum = 	NowProcessInfor[HmiProcessSerialNum-1][2];
}



//�����������ݵ�����
void UpdataProcessToHmi()
{
	//���µ�ǰ��������ʼ·����
	HmiProcessStartNum = 	NowProcessInfor[HmiProcessSerialNum-1][0];
	//���µ�ǰ�����Ķ���
	HmiProcessAction = 	NowProcessInfor[HmiProcessSerialNum-1][1];
	//���µ�ǰ�����Ľ���·���Ż��ظ�ִ�д���
	HmiProcessStopNum = 	NowProcessInfor[HmiProcessSerialNum-1][2];
}

//�����������ݵ�����
void ClearStepToHmi()
{
	//���µ�ǰ��������ʼ·����
	HmiProcessStartNum = 1;
	//���µ�ǰ�����Ķ���
	HmiProcessAction = 0;
	//���µ�ǰ�����Ľ���·���Ż��ظ�ִ�д���
	HmiProcessStopNum = 0;
}

//���뼰�����������ݣ���ǰ������������Ϣ��
void	InsertProcessData()
{
	u16 i,j;
	//���̲���
	
	ProcessStepNum[HmiProcessNum-1] = HmiStepNum;
	//����
	W25QXX_Write_16(&ProcessStepNum[HmiProcessNum-1],ProcessStepNumAdress(HmiProcessNum),1);	

	
	//������Ϣ
	//����ǰ����������������ƶ�һλ
	for(i=HmiStepNum;i>=HmiProcessSerialNum;i--)
	{
		for(j=0;j<StepInfor;j++)
		{
			NowProcessInfor[i-1][j] = NowProcessInfor[i-1-1][j];
		}
	}
	
	//�����²�������
	
	//���µ�ǰ��������ʼ·����
	NowProcessInfor[HmiProcessSerialNum-1][0] = HmiProcessStartNum;
	//���µ�ǰ�����Ķ���
	NowProcessInfor[HmiProcessSerialNum-1][1] = HmiProcessAction;
	//���µ�ǰ�����Ľ���·���Ż��ظ�ִ�д���
	NowProcessInfor[HmiProcessSerialNum-1][2] = HmiProcessStopNum;

		
	//����
	for(i=0;i<HmiStepNum;i++)
		W25QXX_Write_16(&NowProcessInfor[i][0],NowStepInforAdress(HmiProcessNum,i),StepInfor);	
}


//ɾ���������������ݣ���ǰ������������Ϣ��
void	DeleteProcessData()
{
	u16 i,j;
	//���̲���
	if(HmiStepNum>0)
	{
		//��������������ǰ�ƶ�һλ
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
		
		//����
		for(i=0;i<HmiStepNum;i++)
			W25QXX_Write_16(&NowProcessInfor[i][0],NowStepInforAdress(HmiProcessNum,i),StepInfor);	
		
		ProcessStepNum[HmiProcessNum-1] = HmiStepNum;
		//����
		W25QXX_Write_16(&ProcessStepNum[HmiProcessNum-1],ProcessStepNumAdress(HmiProcessNum),1);	

		//���½���
		UpdataProcessToHmi();	
	}
}







//�Զ�������ʾ��Ϣ����
void HmiAutoReload()
{
	//�������ִ�����̣�������·����
	if(HmiTask == 2)					//��Ļ����: ������0 ִ��·��1 ִ������2
	{
		//��ȡ������Ϣ
		GetProcessData();
		HmiRouteNum = NowProcessInfor[0][0];
	}
	//����վ����
	//��ȡ·������վ����
	HmiStationNum = GetRouteStationNum(HmiRouteNum);
	//��ǰ�ر�����
	HmiRfidNum = 0;
	
	//��ȡ��ǰ·����Ϣ
	GetRouteData(HmiRouteNum);	
	//������һ�ر�
	HmiNextRfidNum = NowRouteInfor[0][5];
}




void UserConfigInit(void)
{

	W25QXX_Init();			//W25QXX��ʼ��
	
	while(W25QXX_ReadID()!=W25Q128)//��ⲻ��W25Q128��LED��˸
	{
		LED4 = !LED4;//DS0��˸
		BEEP = !BEEP;
		delay_rtos(0,0,0,100);
	}
	 
	
    GetAllParameterFromSystem();		//��ȡ���Ե�ϵͳ����

    if(SystemParameter[0] != 5) 		//�״�flash��û����ʱ�������⵼�����ݶ�ʧ��ˢ���ʼ��
    {
#if 1									//Ϊ1	//����ǰ100���ڴ���д���ʼ�� -- ϵͳ����
        SystemParameter[0] = 5;			//�ж��Ƿ��һ��д��ı�־
        SystemParameter[1] = 0;	
        SystemParameter[2] = 0;
        SystemParameter[3] = 4;			//�ֶ��ٶȱ��� -- 4/10*3000
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
        SystemParameter[24] = 0; 		//·����
        SystemParameter[25] = 0; 		//
        SystemParameter[26] = 0; 		//
        SystemParameter[27] = 0; 		//
        SystemParameter[28] = 0; 		//
        SystemParameter[29] = 0; 		//
        SystemParameter[30] = 1;		//����
        SystemParameter[31] = 6; 		//ϵͳ����
        SystemParameter[32] = 1; 		//ϵͳ����
        SystemParameter[33] = 1; 		//ϵͳ�������� -- 0:��1:�ر�
        SystemParameter[34] = 0; 		//����״̬��
        SystemParameter[35] = 300; 		//����
        SystemParameter[36] = 800; 		//����
        SystemParameter[37] = 1500; 	//����
        SystemParameter[38] = 300; 		//��λ�Խ��ٶ�
        SystemParameter[39] = 0;
        SystemParameter[40] = 700;	//Ѱ������ٶ�
        SystemParameter[41] = 60;	//��λ��Ѱ���ٶȱ�
        SystemParameter[42] = 600;	//�����Ϲ��ٶ�
        SystemParameter[43] = 2900;	//�������ٶ�
        SystemParameter[44] = 0;
        SystemParameter[45] = 0;
        SystemParameter[46] = 0;
        SystemParameter[47] = 0;
        SystemParameter[48] = 0;
        SystemParameter[49] = 0;
        SystemParameter[50] = 25;	//�Զ�Kp
        SystemParameter[51] = 40;    //�Զ�Ki
        SystemParameter[52] = 0;	//�Զ�Kd
        SystemParameter[53] = 80;	//�ֶ�Kp
        SystemParameter[54] = 100;	//�ֶ�Ki
        SystemParameter[55] = 0;	//�ֶ�Kd
        SystemParameter[56] = 10;	//PID����ʱ��
        SystemParameter[57] = 59;	//ǰ����ֵ
        SystemParameter[58] = 102;	//ǰ����ֵ
        SystemParameter[59] = 146;  	//ǰ����ֵ

        SystemParameter[60] = 49; 	//������ֵ
        SystemParameter[61] = 90; 	//������ֵ
        SystemParameter[62] = 135; 	//������ֵ
        SystemParameter[63] = 0; 	//
        SystemParameter[64] = 0; 	//
        SystemParameter[65] = 0; 	//
        SystemParameter[66] = 0; 	//
        SystemParameter[67] = 0; 	//
        SystemParameter[68] = 0; 	//
        SystemParameter[69] = 0; 	//
        SystemParameter[70] = 20; 	//�޵籨��ֵ
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
        //�洢����ϵͳ����
        SetAllParameterToSystem();

#if 1
        //���·������վ����
        memset(RouteStationNum, 0, RouteNum);
        //��������·��������վ����
        SetAllStationNum();

        //������̰�������
        memset(ProcessStepNum, 0, ProcessNum);
        //�����������̰����Ĳ���
        SetAllStepNum();
#endif
    }


	
//	
//ϵͳ�������µ���������
//	
		
	
	//	
	//ϵͳ������Flash���µ�ϵͳ��
	//				
	AGV_SYS.SD_Speed_bili       = 		  SystemParameter[3];	//�ֶ��ٶȱ��� -- 4/10*3000

	AGV_SYS.ID 					=         SystemParameter[30];	//����
	AGV_SYS.yinliang			=         SystemParameter[31]; 	//ϵͳ����
	AGV_SYS.Auto_Speed_bili		=         SystemParameter[32]; 	//�Զ������ٶȵı���
	AGV_SYS.Key_yuyin 			=         SystemParameter[33]; 	//ϵͳ��������
	AGV_SYS.Key_RGB_LED 		=         SystemParameter[34]; 	//����״̬��
	AGV_SYS.L_speed 			=         SystemParameter[35];  //����
	AGV_SYS.M_speed 			=         SystemParameter[36];  //����
	AGV_SYS.H_speed 			=         SystemParameter[37]; 	//����
	AGV_SYS.duijie_speed 		=         SystemParameter[38]; 	//��λ�Խ��ٶ�
		   
	AGV_SYS.XZ_MAX_Speed 		=         SystemParameter[40]; 	//Ѱ������ٶ�
	AGV_SYS.XZ_DWQ_Speed_bili	=         SystemParameter[41];	//��λ��Ѱ���ٶȱ�
	AGV_SYS.XZ_CiTiao_Speed 	=         SystemParameter[42]; 	//�����Ϲ��ٶ�
	AGV_SYS.Motor_MAX_Speed 	=         SystemParameter[43];	//�������ٶ�


	AGV_SYS.AUTO_Kp       		=		  SystemParameter[50];	//�Զ�Kp
	AGV_SYS.AUTO_Ki        		=		  SystemParameter[51];  //�Զ�Ki
	AGV_SYS.AUTO_Kd        		=		  SystemParameter[52];	//�Զ�Kd
	AGV_SYS.SD_Kp       		=		  SystemParameter[53];	//�ֶ�Kp
	AGV_SYS.SD_Ki        		=		  SystemParameter[54];	//�ֶ�Ki
	AGV_SYS.SD_Kd        		=		  SystemParameter[55];	//�ֶ�Kd
	AGV_SYS.PID_time 			=         SystemParameter[56];	//PID����ʱ��

	g_DWQ.qianlun_L_val        	=		  SystemParameter[57];	//ǰ����ֵ
	g_DWQ.qianlun_zhong_val     =	      SystemParameter[58];	//ǰ����ֵ
	g_DWQ.qianlun_R_val        	=		  SystemParameter[59];  //ǰ����ֵ

	g_DWQ.houlun_L_val        	=		  SystemParameter[60]; 	//������ֵ
	g_DWQ.houlun_zhong_val    	=		  SystemParameter[61]; 	//������ֵ
	g_DWQ.houlun_R_val        	=		  SystemParameter[62]; 	//������ֵ

	Battery_Warining.Warining_Val_NoBattery = SystemParameter[70];

	//	
	//ϵͳ������Flash���µ���������
	//				
	g_shoudong_screen_speed     = 		  SystemParameter[3];	//�ֶ��ٶȱ��� -- 4/10*3000

	g_AGV_ID 					=         SystemParameter[30];	//����
	g_AGV_speaker_val 			=         SystemParameter[31]; 	//ϵͳ����
	g_sys_set_agvSPEED			=         SystemParameter[32]; 	//ϵͳ���� -- �Զ�
	g_AGV_speaker_key 			=         SystemParameter[33]; 	//ϵͳ��������
	g_AGV_LED_car_state			=         SystemParameter[34]; 	//����״̬��
	HmiDiSu       				=         SystemParameter[35];  //����
	HmiZhongSu     				=         SystemParameter[36];  //����
	HmiGaoSu      				=         SystemParameter[37]; 	//����
	g_AGV_speed_duijie			=         SystemParameter[38]; 	//��λ�Խ��ٶ�
			   	   
	XZ_Speed40					=         SystemParameter[40]; 	//Ѱ������ٶ�
	XZ_Speed41					=         SystemParameter[41];	//��λ��Ѱ���ٶȱ�
	XZ_Speed42					=         SystemParameter[42]; 	//�����Ϲ��ٶ�
	XZ_Speed43					=         SystemParameter[43];	//�������ٶ�

	g_screen_Auto_Kp			=		  SystemParameter[50];	//�Զ�Kp
	g_screen_Auto_Ki			=		  SystemParameter[51];  //�Զ�Ki
	g_screen_Auto_Kd			=		  SystemParameter[52];	//�Զ�Kd
	g_screen_Manu_Kp			=		  SystemParameter[53];	//�ֶ�Kp
	g_screen_Manu_Ki			=		  SystemParameter[54];	//�ֶ�Ki
	g_screen_Manu_Kd			=		  SystemParameter[55];	//�ֶ�Kd
	g_screen_control_TIME		=         SystemParameter[56];	//PID����ʱ��

	g_screen_qianlun_ZuoZhi		=		  SystemParameter[57];	//ǰ����ֵ
	g_screen_qianlun_ZhongZhi	=	      SystemParameter[58];	//ǰ����ֵ
	g_screen_qianlun_YouZhi		=		  SystemParameter[59];  //ǰ����ֵ

	g_screen_houlun_ZuoZhi		=		  SystemParameter[60]; 	//������ֵ
	g_screen_houlun_ZhongZhi 	=		  SystemParameter[61]; 	//������ֵ
	g_screen_houlun_YouZhi 		=		  SystemParameter[62]; 	//������ֵ

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
//�����Զ�������Ϣ
//
    //HmiAutoReload();


    //��ȡ·������վ����
    GetRouteStationNum(HmiRouteNum);

    //��ȡ��ǰ·����Ϣ
    GetRouteData(HmiRouteNum);
	
    //��ȡ��������������
    GetProcessData();
}







AGV_station agv_routr2station[StationNum];		//

























