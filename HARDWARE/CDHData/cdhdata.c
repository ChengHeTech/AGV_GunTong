#include "cdhdata.h"


//�������ĵ������������������ҵ�CDH_read_dataa�������ܣ�
Fencha_struct front_cdh16,back_cdh16,backl_cdh8,backr_cdh8;//����һ��Fencha_struct���͵�ȫ�ֱ���
Fencha_struct findtemp={0,0,0,0,0,0};//�����������еĽṹ�����鶨��

Fencha_struct g_CDH8_qian_1;
Fencha_struct g_CDH8_qian_2;

Fencha_struct g_CDH8_hou_1;
Fencha_struct g_CDH8_hou_2;

//16λ�ŵ������ݴ�����

//dst:�ŵ�����ԭʼ16���Ƶ�16λ��
//num:����ʱ�����������������1~15��
//dir:�ֲ淽��1����ֲ棬2���ҷֲ�
//����ֵ��Fencha_struct�ṹ��

Fencha_struct FindSpace(u16 dst,u8 num,u8 dir)
{
	u16 i=0,dirr=dir;
	u16 p=~dst,numr=0,numl=0;
	Fencha_struct find;
	AA:	
	find.zeroNum = 0;
	find.zeroContinue = 0;
	find.Num = 0;
	find.Distance = 0;
	find.Error = 0;
	//������Ч��ĸ���
	for(i=0;i<16;i++)
	{
		if((p>>i)&0x0001)
		{
			find.Num++;
		}
	}
	//�ж��ұ�0�ĸ���
	for(i=0;i<16;i++)
	{
		if(((p>>i)&0x0001)==0)
		{
			numr++;
		}
		else
		{
			i=16;//ֱ���˳�
		}
	}
	
	//�ж����0�ĸ���
	for(i=0;i<16;i++)
	{
		if(((p<<i)&0x8000)==0)
		{
			numl++;
		}
		else
		{
			i=16;//ֱ���˳�
		}
	}		
	//����0�ĸ�����������0���ֵ�λ��
	for(i=numr;i<(16-numl);i++)
	{
		if(((p>>i)&0x0001)==0)
		{
			find.zeroLoctaion[find.zeroNum]=i;
			find.zeroNum++;
		}
	}
		
	//�ж϶ϵ��Ƿ�����
	if(find.zeroNum>0)
	{
		find.zeroContinue = 1;
		if(find.zeroNum>1)
		{
			for(i = 0;i<(find.zeroNum-1);i++)
			{
				if(find.zeroLoctaion[i+1]-find.zeroLoctaion[i]==1)
				{
					continue;
				}
				else
				{
					find.zeroContinue++;
				}
			}
		}
	}
	//������Ч���������λ�õľ���
	if(find.Num==0)//û�ҵ���Ч�㣬���뷵��0
	{
		find.Distance = 16;
		find.Error = 1;		
	}

	else
	{
		if(find.zeroNum>0)//�жϵ㣬����0
		{
			if(find.zeroContinue==1)//һ���ֲ�
			{
				if(dirr==2)//�ҷֲ�
				{
					for(i=numr;i<16;i++)
					{
						if((p>>i)&0x0001)
						{
							p = p&(~(0x0001<<i));
						}
						else
						{
							i = 16;
						}
					}
					goto AA;
				}
				else if(dirr==1)//��ֲ�
				{
					for(i=numl;i<16;i++)
					{
						if((p<<i)&0x8000)
						{
							p = p&(~(0x8000>>i));
						}
						else
						{
							i = 16;
						}
					}
					goto AA;
				}
				else
				{
					find.Error = 1;
				}
			}
			
		}
		else//�������
		{
			if(find.Num<=num)
			{				
				find.Distance = numl - numr ;
			}
			else
			{
				find.Error = 1;
			}
		}
	}
	
	findtemp = find;
	return find;

}
//8λ�ŵ������ݴ�����
//dst:�ŵ�����ԭʼ16���Ƶ�8λ��
//num:����ʱ�����������������1~7��
//dir:�ֲ淽��1����ֲ棬2���ҷֲ�
//����ֵ��Fencha_struct�ṹ��

Fencha_struct FindSpace1(u8 dst,u8 num,u8 dir)
{
	u8 i=0,dirr=dir;
	u8 p=~dst,numr=0,numl=0;
	Fencha_struct find;
	AA:	
	find.zeroNum = 0;
	find.zeroContinue = 0;
	find.Num = 0;
	find.Distance = 0;
	find.Error = 0;
	//������Ч��ĸ���
	for(i=0;i<8;i++)
	{
		if((p>>i)&0x01)
		{
			find.Num++;
		}
	}
	//�ж��ұ�0�ĸ���
	for(i=0;i<8;i++)
	{
		if(((p>>i)&0x01)==0)
		{
			numr++;
		}
		else
		{
			i=8;//ֱ���˳�
		}
	}
	
	//�ж����0�ĸ���
	for(i=0;i<8;i++)
	{
		if(((p<<i)&0x80)==0)
		{
			numl++;
		}
		else
		{
			i=8;//ֱ���˳�
		}
	}		
	//����0�ĸ�����������0���ֵ�λ��
	for(i=numr;i<(8-numl);i++)
	{
		if(((p>>i)&0x01)==0)
		{
			find.zeroLoctaion[find.zeroNum]=i;
			find.zeroNum++;						//�յ����
		}
	}
		
	//�ж϶ϵ��Ƿ�����
	if(find.zeroNum>0)
	{
		find.zeroContinue = 1;
		if(find.zeroNum>1)
		{
			for(i = 0;i<(find.zeroNum-1);i++)
			{
				if(find.zeroLoctaion[i+1]-find.zeroLoctaion[i]==1)
				{
					continue;
				}
				else
				{
					find.zeroContinue++;
				}
			}
		}
	}
	//������Ч���������λ�õľ���
	if(find.Num==0)//û�ҵ���Ч�㣬���뷵��0
		find.Error = 1;
	else
	{
//		if((findtemp.zeroNum==0)&&(find.zeroNum>4)&&(findtemp.Num>0))
//		{
//				if(find.zeroLoctaion[find.zeroNum/2]>=9)
//					dirr = 2;
//				else
//					dirr = 1;
//		}
		if(find.zeroNum>0)//�жϵ㣬����0
		{
			if(find.zeroContinue==1)//һ���ֲ�
			{
				if(dirr==2)//�ҷֲ�
				{
					for(i=numr;i<8;i++)
					{
						if((p>>i)&0x01)
						{
							p = p&(~(0x01<<i));
						}
						else
						{
							i = 8;
						}
					}
					goto AA;
				}
				else if(dirr==1)//��ֲ�
				{
					for(i=numl;i<8;i++)
					{
						if((p<<i)&0x80)
						{
							p = p&(~(0x80>>i));
						}
						else
						{
							i = 8;
						}
					}
					goto AA;
				}
				else
				{
					find.Error = 1;
				}
			}
			
		}
		else//�������
		{
			if(find.Num<=num)
			{
				find.Distance = numl - numr;
			}
			else
			{
				find.Error = 1;
			}
		}
	}
	
	findtemp = find;
	return find;

}





u8 g_PID_time = 5;		//ms




float g_Auto_Kp=25;
float g_Auto_Ki=40;
float g_Auto_Kd=5;

float Cdh1_Inc;
float Cdh2_Inc;
float Cdh3_Inc;
float Cdh4_Inc;

PIDspeed PID_speed;
//�ŵ���PID����
void PID_AUTO_QianLun(u16 j_speed,float kp,float ki,float kd)
{
	u8 num = 0;
	PID.Kp = kp;
	PID.Ki = ki;
	PID.Kd = kd; 
	
	PID.SetTarget = 0;		//PIDĿ��ֵ
	
	if(g_AGV_Car_dir == 0)
	{
		while( g_CDH8_qian_1.Num==0 && num<50 )				//�յ���0.5��
		{
			num++;
			delay_rtos(0,0,0,10);
		}			
		if(g_CDH8_qian_1.Num==0)							//δ���������ֹͣ
		{
			AGV_System_Stop();					//ֹͣ
			HmiTaskState = 4;								//��������ʾ����ֹͣ
		}
		else
		{
			HmiTaskState = 5;								//��������
			
			
			Cdh1_Inc = IncPIDCalc(g_CDH8_qian_1.Distance);	//1 λ��ʽPID//�����ֵ						
			PID_speed.moter1_speed = j_speed-Cdh1_Inc;
			PID_speed.moter2_speed = j_speed+Cdh1_Inc;
			
			if(PID_speed.moter1_speed>j_speed)	PID_speed.moter1_speed = j_speed;
			if(PID_speed.moter2_speed>j_speed)	PID_speed.moter2_speed = j_speed;


			if(PID_speed.moter1_speed<0)	PID_speed.moter1_speed = 0;
			if(PID_speed.moter2_speed<0)	PID_speed.moter2_speed = 0;


			Motor_Zzhuan(1,PID_speed.moter1_speed); Motor_Fzhuan(2,PID_speed.moter2_speed);
			
			
						
		}
	}
	else if(g_AGV_Car_dir == 1)					//����
	{
		while(g_CDH8_qian_2.Num==0 && num!=50)		//�յ���0.5��
		{
			num++;
			delay_rtos(0,0,0,10);
		}
		if(g_CDH8_qian_2.Num==0)
		{
			AGV_System_Stop();					//ֹͣ
			HmiTaskState = 4;					//�޴���ֹͣ
		}
		else
		{
			HmiTaskState = 5;					//��������
			

			
			Cdh2_Inc = IncPIDCalc(g_CDH8_qian_2.Distance);//2 λ��ʽPID//�����ֵ
			PID_speed.moter2_speed = j_speed-Cdh2_Inc;	
			PID_speed.moter1_speed = j_speed+Cdh2_Inc;
							
			
			if(PID_speed.moter1_speed>j_speed)	PID_speed.moter1_speed = j_speed;
			if(PID_speed.moter2_speed>j_speed)	PID_speed.moter2_speed = j_speed;

			if(PID_speed.moter1_speed<0)	PID_speed.moter1_speed = 0;
			if(PID_speed.moter2_speed<0)	PID_speed.moter2_speed = 0;

		
			
			
			Motor_Zzhuan(2,PID_speed.moter2_speed);	Motor_Fzhuan(1,PID_speed.moter1_speed);
			
					
		}

	}
}

void PID_AUTO_HouLun(u16 j_speed2,float kp2,float ki2,float kd2)	//���ֵ�PID����
{
	u8 num2 = 0;
	PID2.Kp = kp2;
	PID2.Ki = ki2;
	PID2.Kd = kd2; 
	
	PID2.SetTarget = 0;		//PID2Ŀ��ֵ
	
	if(g_AGV_Car_dir == 0)	//ǰ��
	{
		while( g_CDH8_hou_1.Num==0 && num2<50 )				//�յ���0.5��
		{
			num2++;
			delay_rtos(0,0,0,10);
		}			
		if(g_CDH8_hou_1.Num==0)							//δ���������ֹͣ
		{
			AGV_System_Stop();							//ֹͣ
			HmiTaskState = 4;								//��������ʾ����ֹͣ
		}
		else
		{
			HmiTaskState = 5;								//��������
			
			Cdh3_Inc = IncPIDCalc2(g_CDH8_hou_1.Distance);	//1 λ��ʽPID//�����ֵ						
			PID_speed.moter3_speed = j_speed2-Cdh3_Inc;
			PID_speed.moter4_speed = j_speed2+Cdh3_Inc;
			
			if(PID_speed.moter3_speed>j_speed2)	PID_speed.moter3_speed = j_speed2;
			if(PID_speed.moter4_speed>j_speed2)	PID_speed.moter4_speed = j_speed2;


			if(PID_speed.moter3_speed<0)	PID_speed.moter3_speed = 0;
			if(PID_speed.moter4_speed<0)	PID_speed.moter4_speed = 0;


			Motor_Zzhuan(3,PID_speed.moter3_speed); Motor_Fzhuan(4,PID_speed.moter4_speed);
			
			
						
		}
	}
	else if(g_AGV_Car_dir == 1)					//����
	{
		while(g_CDH8_hou_2.Num==0 && num2!=50)		//�յ���0.5��
		{
			num2++;
			delay_rtos(0,0,0,10);
		}
		if(g_CDH8_hou_2.Num==0)
		{
			AGV_System_Stop();
			HmiTaskState = 4;					//�޴���ֹͣ
		}
		else
		{
			HmiTaskState = 5;					//��������
			

			
			Cdh4_Inc = IncPIDCalc2(g_CDH8_hou_2.Distance);//2 λ��ʽPID//�����ֵ
			PID_speed.moter4_speed = j_speed2-Cdh4_Inc;	
			PID_speed.moter3_speed = j_speed2+Cdh4_Inc;
							
			
			if(PID_speed.moter4_speed>j_speed2)	PID_speed.moter4_speed = j_speed2;
			if(PID_speed.moter3_speed>j_speed2)	PID_speed.moter3_speed = j_speed2;

			if(PID_speed.moter4_speed<0)	PID_speed.moter4_speed = 0;
			if(PID_speed.moter3_speed<0)	PID_speed.moter3_speed = 0;

		
			
			
			Motor_Zzhuan(4,PID_speed.moter4_speed);	Motor_Fzhuan(3,PID_speed.moter3_speed);
			
					
		}

	}
}





float g_SD_Kp = 200;
float g_SD_Ki = 100;
float g_SD_Kd = 0;
u16 g_ffff = 105;		//����Ƕ�_��ֵ------://��ת3/4  ��ת 1/4 �м� 1/2

int DWQ1_Inc;
int DWQ2_Inc;
int DWQ3_Inc;
int DWQ4_Inc;

PIDspeed PID__SD_speed;
u8 g_Trun_Val = 10;			//�ֶ�ת��Ƕ�
void PID_SD_Adjust(u16 j_speed,float kp,float ki,float kd)
{
	PID2.Kp = PID.Kp = kp;
	PID2.Ki = PID.Ki = ki;
	PID2.Kd = PID.Kd = kd; 
	
	//0:ֹͣ1:ǰ�� 2:���� 3:��ת 4:��ת 5���� 6���� 7���� 8���� 9���� 10���� 	
	
	HmiTaskState = 5;								//�������� -- �ֶ�

	switch(g_AGV_shoudong_dir)	//�趨Ŀ��ֵ
	{
		case 1:					//ǰ��
		case 2:					//����
			PID.SetTarget  = g_DWQ.qianlun_zhong_val;		//PIDĿ��ֵ--ǰ_�����ֵ�λ����ֵ 0-4096
			PID2.SetTarget = g_DWQ.houlun_zhong_val;		//PIDĿ��ֵ--��_�����ֵ�λ����ֵ 		
			break;
		
		case 5:					//����
			PID.SetTarget  = g_DWQ.qianlun_zhong_val - g_Trun_Val;		//PIDĿ��ֵ--ǰ_�����ֵ�λ����ֵ 
			PID2.SetTarget = g_DWQ.houlun_zhong_val;		//PIDĿ��ֵ--��_�����ֵ�λ����ֵ 						
			break;	
		case 6:					//����
			PID.SetTarget  = g_DWQ.qianlun_zhong_val + g_Trun_Val;		//PIDĿ��ֵ--ǰ_�����ֵ�λ����ֵ 
			PID2.SetTarget = g_DWQ.houlun_zhong_val;		//PIDĿ��ֵ--��_�����ֵ�λ����ֵ 						
			break;
		
		case 8:					//����
			PID2.SetTarget = g_DWQ.houlun_zhong_val - g_Trun_Val;		//PIDĿ��ֵ--��_�����ֵ�λ����ֵ 	
			PID.SetTarget  = g_DWQ.qianlun_zhong_val;		//PIDĿ��ֵ--ǰ_�����ֵ�λ����ֵ 
				break;	
		case 7:					//����
			PID2.SetTarget = g_DWQ.houlun_zhong_val + g_Trun_Val;		//PIDĿ��ֵ--��_�����ֵ�λ����ֵ 	
			PID.SetTarget  = g_DWQ.qianlun_zhong_val;		//PIDĿ��ֵ--ǰ_�����ֵ�λ����ֵ 
			break;			
		
		default:
			break;
	}	
	
	switch(g_AGV_shoudong_dir)	//ʵ�ʿ��Ƶ�����ٶ�			
	{
		case 1:					//ǰ��
		case 5:					//ǰ�����	
		case 6:					//ǰ���ҹ�
			DWQ1_Inc = IncPIDCalc(g_After_filter[1]);		//1 λ��ʽPID//�����ֵ	 0-4096				
			PID__SD_speed.moter1_speed = j_speed+DWQ1_Inc;
			PID__SD_speed.moter2_speed = j_speed-DWQ1_Inc;
			
			DWQ2_Inc = IncPIDCalc2(g_After_filter[2]);		//2 λ��ʽPID//�����ֵ						
			PID__SD_speed.moter3_speed = j_speed+DWQ2_Inc;
			PID__SD_speed.moter4_speed = j_speed-DWQ2_Inc;
			break;
		
		case 2:					//����
		case 8:					//�������	
		case 7:					//�����ҹ�
			DWQ2_Inc = IncPIDCalc2(g_After_filter[2]);		//1 λ��ʽPID//�����ֵ	 0-4096				
			PID__SD_speed.moter4_speed = j_speed+DWQ2_Inc;
			PID__SD_speed.moter3_speed = j_speed-DWQ2_Inc;
			
			DWQ1_Inc = IncPIDCalc(g_After_filter[1]);		//2 λ��ʽPID//�����ֵ						
			PID__SD_speed.moter2_speed = j_speed+DWQ1_Inc;
			PID__SD_speed.moter1_speed = j_speed-DWQ1_Inc;
			break;			
		
		default:
			break;

	}
	

	
	if(PID__SD_speed.moter1_speed > 300*g_AGV_shoudong_Speed_bili)	PID__SD_speed.moter1_speed = 300*g_AGV_shoudong_Speed_bili;
	if(PID__SD_speed.moter2_speed > 300*g_AGV_shoudong_Speed_bili)	PID__SD_speed.moter2_speed = 300*g_AGV_shoudong_Speed_bili;
	if(PID__SD_speed.moter3_speed > 300*g_AGV_shoudong_Speed_bili)	PID__SD_speed.moter3_speed = 300*g_AGV_shoudong_Speed_bili;
	if(PID__SD_speed.moter4_speed > 300*g_AGV_shoudong_Speed_bili)	PID__SD_speed.moter4_speed = 300*g_AGV_shoudong_Speed_bili;


	if(PID__SD_speed.moter1_speed<0)	PID__SD_speed.moter1_speed = 0;
	if(PID__SD_speed.moter2_speed<0)	PID__SD_speed.moter2_speed = 0;
	if(PID__SD_speed.moter3_speed<0)	PID__SD_speed.moter3_speed = 0;
	if(PID__SD_speed.moter4_speed<0)	PID__SD_speed.moter4_speed = 0;


	switch(g_AGV_shoudong_dir)	//ʵ�ʿ��Ƶ�����ٶ�			
	{
		case 1:					//ǰ��
		case 5:					//ǰ�����	
		case 6:					//ǰ���ҹ�
			Motor_Zzhuan(1,PID__SD_speed.moter1_speed); Motor_Fzhuan(2,PID__SD_speed.moter2_speed);
			Motor_Zzhuan(3,PID__SD_speed.moter3_speed); Motor_Fzhuan(4,PID__SD_speed.moter4_speed);
			break;
		
		case 2:					//����
		case 8:					//�������	
		case 7:					//�����ҹ�
			Motor_Zzhuan(4,PID__SD_speed.moter4_speed);	Motor_Fzhuan(3,PID__SD_speed.moter3_speed);				
			Motor_Zzhuan(2,PID__SD_speed.moter2_speed); Motor_Fzhuan(1,PID__SD_speed.moter1_speed);						
			break;			
		
		default:
			break;

	}

}

//ң������
//1��2��3H4L
//
