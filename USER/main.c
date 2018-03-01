#include "my_include.h"

//����Щ���ȼ��������UCOSIII��5��ϵͳ�ڲ�����
//���ȼ�0���жϷ������������� OS_IntQTask()
//���ȼ�1��ʱ�ӽ������� OS_TickTask()
//���ȼ�2����ʱ���� OS_TmrTask()
//���ȼ�OS_CFG_PRIO_MAX-2��ͳ������ OS_StatTask()
//���ȼ�OS_CFG_PRIO_MAX-1���������� OS_IdleTask()

//�������ȼ�
#define START_TASK_PRIO		3
//�����ջ��С	
#define START_STK_SIZE 		512
//������ƿ�
OS_TCB StartTaskTCB;
//�����ջ	
CPU_STK START_TASK_STK[START_STK_SIZE];
//������
void start_task(void *p_arg);                       //��ʼ����

//�������ȼ�
#define Transducer_TASK_PRIO		4
//�����ջ��С	
#define Transducer_STK_SIZE 		512
//������ƿ�
OS_TCB TransducerTaskTCB;
//�����ջ	
CPU_STK Transducer_TASK_STK[Transducer_STK_SIZE];
void Transducer_task(void *p_arg);					//���Զ�ת������

//�������ȼ�
#define FLOAT_TASK_PRIO		5
//�����ջ��С
#define FLOAT_STK_SIZE		512
//������ƿ�
OS_TCB	FloatTaskTCB;
//�����ջ
__align(8) CPU_STK	FLOAT_TASK_STK[FLOAT_STK_SIZE];
//������
void float_task(void *p_arg);						//��������


//�������ȼ�
#define MOTEC_TASK_PRIO		6
//�����ջ��С	
#define MOTEC_STK_SIZE 		256
//������ƿ�
OS_TCB MOTECTaskTCB;
//�����ջ	
CPU_STK motec_TASK_STK[MOTEC_STK_SIZE];
//������
void motec_task(void *p_arg);						//��ʼ��Motec����������

//�������ȼ�
#define Auto_TASK_PRIO		7
//�����ջ��С	
#define Auto_STK_SIZE 		512
//������ƿ�
OS_TCB AutoTaskTCB;
//�����ջ	
CPU_STK Auto_TASK_STK[Auto_STK_SIZE];
//������
void Auto_task(void *p_arg);						//�Զ�ģʽ����

//�������ȼ� 
#define PID_TASK_PRIO		8
//�����ջ��С	
#define PID_STK_SIZE 		512
//������ƿ�
OS_TCB PIDTaskTCB;
//�����ջ	
CPU_STK PID_TASK_STK[PID_STK_SIZE];
//������
void PID_task(void *p_arg);							//PID����

//�������ȼ�
#define Manual_TASK_PRIO		9
//�����ջ��С	
#define Manual_STK_SIZE 		512
//������ƿ�
OS_TCB ManualTaskTCB;
//�����ջ	
CPU_STK Manual_TASK_STK[Manual_STK_SIZE];
//������
void Manual_task(void *p_arg);						//�ֶ�ģʽ����



//�������ȼ�
#define Screen_TASK_PRIO		10
//�����ջ��С	
#define Screen_STK_SIZE 		512
//������ƿ�
OS_TCB ScreenTaskTCB;
//�����ջ	
CPU_STK Screen_TASK_STK[Screen_STK_SIZE];
//������
void Screen_task(void *p_arg);						//��Ļ����

//�������ȼ�
#define Control_TASK_PRIO		11
//�����ջ��С	
#define Control_STK_SIZE 		512
//������ƿ�
OS_TCB ControlTaskTCB;
//�����ջ	
CPU_STK Control_TASK_STK[Control_STK_SIZE];
//������
void Control_task(void *p_arg);						//��������

//�������ȼ�
#define WIFI_TASK_PRIO		12
//�����ջ��С	
#define WIFI_STK_SIZE 		512
//������ƿ�
OS_TCB WIFITaskTCB;
//�����ջ	
CPU_STK WIFI_TASK_STK[WIFI_STK_SIZE];
//������
void WIFI_task(void *p_arg);						//WIFI����


//�������ȼ�
#define guntong_TASK_PRIO		13
//�����ջ��С	
#define guntong_STK_SIZE 		512
//������ƿ�
OS_TCB guntongTaskTCB;
//�����ջ	
CPU_STK guntong_TASK_STK[guntong_STK_SIZE];
//������
void guntong_task(void *p_arg);						//��Ͳ����



//�������ȼ�
#define DCv_TASK_PRIO		14
//�����ջ��С	
#define DCv_STK_SIZE 		128
//������ƿ�
OS_TCB DCvTaskTCB;
//�����ջ	
CPU_STK DCv_TASK_STK[DCv_STK_SIZE];
//������
void DCv_task(void *p_arg);							//��ѹ�ɼ�





int main(void)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	
	delay_init(168);  	//ʱ�ӳ�ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�жϷ�������
	
	LED_Init();         //LED��ʼ��
	beep_init();   		//PA3
	rgb_init();
	button_input_init();
	//motor_init();
	guntong_init();
	
	DMA_adc1_Init();    				//��λ��
	DMA_Uart2_Init();					//��̫��ת����
	DMA_Uart3_Init();					//﮵��ͨ��
	DMA_Uart4_Init();					//������	
	
	ADC1_Configuration();				//��λ���ɼ�
	USART1_Configuration(9600); 		//����1 PA9PA10 ���ڻ���������
	USART2_Configuration(9600);			//��̫��ת���ڵĽӿ�
	USART3_Configuration(9600);			//������﮵�ص������Ŀ� -- 232תTTL����
	uart4_init(9600);					//������485
	//USART6_Configuration(115200);		
	

	//DMA_Uart6_Init();
	CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,6,CAN_Mode_Normal);//CAN��ʼ������ģʽ,������500Kbps    
	CAN2_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,6,CAN_Mode_Normal);	
	NVIC_Configuration();

	TIM4_PWM_Init(21000-1,4-1);		//  1000,8   21000 000
	PID_Init();
	
	UserConfigInit();				//�û�������ʼ��	

	
	

	OSInit(&err);		//��ʼ��UCOSIII
	OS_CRITICAL_ENTER();//�����ٽ���
	//������ʼ����
	OSTaskCreate((OS_TCB 	* )&StartTaskTCB,		//������ƿ�
								 (CPU_CHAR	* )"start task", 		//��������
                 (OS_TASK_PTR )start_task, 			//������
                 (void		* )0,					//���ݸ��������Ĳ���
                 (OS_PRIO	  )START_TASK_PRIO,     //�������ȼ�
                 (CPU_STK   * )&START_TASK_STK[0],	//�����ջ����ַ
                 (CPU_STK_SIZE)START_STK_SIZE/10,	//�����ջ�����λ
                 (CPU_STK_SIZE)START_STK_SIZE,		//�����ջ��С
                 (OS_MSG_QTY  )0,					//�����ڲ���Ϣ�����ܹ����յ������Ϣ��Ŀ,Ϊ0ʱ��ֹ������Ϣ
                 (OS_TICK	  )0,					//��ʹ��ʱ��Ƭ��תʱ��ʱ��Ƭ���ȣ�Ϊ0ʱΪĬ�ϳ��ȣ�
                 (void   	* )0,					//�û�����Ĵ洢��
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //����ѡ��
                 (OS_ERR 	* )&err);				//��Ÿú�������ʱ�ķ���ֵ
	OS_CRITICAL_EXIT();	//�˳��ٽ���	 
	OSStart(&err);  //����UCOSIII								 
}

//��ʼ������
void start_task(void *p_arg)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	p_arg = p_arg;

	CPU_Init();
#if OS_CFG_STAT_TASK_EN > 0u
   OSStatTaskCPUUsageInit(&err);  	//ͳ������                
#endif
	
#ifdef CPU_CFG_INT_DIS_MEAS_EN		//���ʹ���˲����жϹر�ʱ��
    CPU_IntDisMeasMaxCurReset();	
#endif

#if	OS_CFG_SCHED_ROUND_ROBIN_EN  //��ʹ��ʱ��Ƭ��ת��ʱ��
	 //ʹ��ʱ��Ƭ��ת���ȹ���,ʱ��Ƭ����Ϊ1��ϵͳʱ�ӽ��ģ���1*5=5ms
	OSSchedRoundRobinCfg(DEF_ENABLED,1,&err);  
#endif		
	
	OS_CRITICAL_ENTER();	//�����ٽ���
	
	//����Transducer����
	OSTaskCreate((OS_TCB 	* )&TransducerTaskTCB,			//4
				 (CPU_CHAR	* )"Transducer task", 		
                 (OS_TASK_PTR )Transducer_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )Transducer_TASK_PRIO,     
                 (CPU_STK   * )&Transducer_TASK_STK[0],	
                 (CPU_STK_SIZE)Transducer_STK_SIZE/10,	
                 (CPU_STK_SIZE)Transducer_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);								 

//���������������
	OSTaskCreate((OS_TCB 	* )&FloatTaskTCB,				//5
				 (CPU_CHAR	* )"float test task", 		
                 (OS_TASK_PTR )float_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )FLOAT_TASK_PRIO,     	
                 (CPU_STK   * )&FLOAT_TASK_STK[0],	
                 (CPU_STK_SIZE)FLOAT_STK_SIZE/10,	
                 (CPU_STK_SIZE)FLOAT_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);	

	//�����Զ�����
	OSTaskCreate((OS_TCB 	* )&MOTECTaskTCB,				//6
				 (CPU_CHAR	* )"motec task", 		
                 (OS_TASK_PTR )motec_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )MOTEC_TASK_PRIO,     	
                 (CPU_STK   * )&motec_TASK_STK[0],	
                 (CPU_STK_SIZE)MOTEC_STK_SIZE/10,	
                 (CPU_STK_SIZE)MOTEC_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);
				 
	//�����Զ�����
	OSTaskCreate((OS_TCB 	* )&AutoTaskTCB,				//7
				 (CPU_CHAR	* )"Auto task", 		
                 (OS_TASK_PTR )Auto_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )Auto_TASK_PRIO,     	
                 (CPU_STK   * )&Auto_TASK_STK[0],	
                 (CPU_STK_SIZE)Auto_STK_SIZE/10,	
                 (CPU_STK_SIZE)Auto_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);

	//PID
	OSTaskCreate((OS_TCB 	* )&PIDTaskTCB,					//8
				 (CPU_CHAR	* )"PID task", 		
                 (OS_TASK_PTR )PID_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )PID_TASK_PRIO,     	
                 (CPU_STK   * )&PID_TASK_STK[0],	
                 (CPU_STK_SIZE)PID_STK_SIZE/10,	
                 (CPU_STK_SIZE)PID_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);
				 
	//�����ֶ�����
	OSTaskCreate((OS_TCB 	* )&ManualTaskTCB,				//9
				 (CPU_CHAR	* )"Manual task", 		
                 (OS_TASK_PTR )Manual_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )Manual_TASK_PRIO,     	
                 (CPU_STK   * )&Manual_TASK_STK[0],	
                 (CPU_STK_SIZE)Manual_STK_SIZE/10,	
                 (CPU_STK_SIZE)Manual_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);
				 
	

	//��������������
	OSTaskCreate((OS_TCB 	* )&ScreenTaskTCB,				//10
				 (CPU_CHAR	* )"Screen task", 		
                 (OS_TASK_PTR )Screen_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )Screen_TASK_PRIO,     	
                 (CPU_STK   * )&Screen_TASK_STK[0],	
                 (CPU_STK_SIZE)Screen_STK_SIZE/10,	
                 (CPU_STK_SIZE)Screen_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);	

	//����
	OSTaskCreate((OS_TCB 	* )&ControlTaskTCB,				//11
				 (CPU_CHAR	* )"Control task", 		
                 (OS_TASK_PTR )Control_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )Control_TASK_PRIO,     	
                 (CPU_STK   * )&Control_TASK_STK[0],	
                 (CPU_STK_SIZE)Control_STK_SIZE/10,	
                 (CPU_STK_SIZE)Control_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);				 
	//WIFI
	OSTaskCreate((OS_TCB 	* )&WIFITaskTCB,				//12
				 (CPU_CHAR	* )"WIFI task", 		
                 (OS_TASK_PTR )WIFI_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )WIFI_TASK_PRIO,     	
                 (CPU_STK   * )&WIFI_TASK_STK[0],	
                 (CPU_STK_SIZE)WIFI_STK_SIZE/10,	
                 (CPU_STK_SIZE)WIFI_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);				 
				 
	//WIFI
	OSTaskCreate((OS_TCB 	* )&guntongTaskTCB,				//13
				 (CPU_CHAR	* )"guntong task", 		
                 (OS_TASK_PTR )guntong_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )guntong_TASK_PRIO,     	
                 (CPU_STK   * )&guntong_TASK_STK[0],	
                 (CPU_STK_SIZE)guntong_STK_SIZE/10,	
                 (CPU_STK_SIZE)guntong_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);		
				 
	//��ѹ�ɼ�		
	OSTaskCreate((OS_TCB 	* )&DCvTaskTCB,					//14
				 (CPU_CHAR	* )"DCv task", 		
                 (OS_TASK_PTR )DCv_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )DCv_TASK_PRIO,     	
                 (CPU_STK   * )&DCv_TASK_STK[0],	
                 (CPU_STK_SIZE)DCv_STK_SIZE/10,	
                 (CPU_STK_SIZE)DCv_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);					 
				 
				 
				 
				 
	OS_TaskSuspend((OS_TCB*)&StartTaskTCB,&err);		//����ʼ����			 
	OS_CRITICAL_EXIT();	//�����ٽ���
								 
}




void Transducer_task(void *p_arg)  	//����������ɼ����г���״̬
{
	u8 temp_l=0;
	OS_ERR err;
	p_arg = p_arg;	
	
	while(1)
	{
		
		//ֻʣ�º�����ϵĳ����״̬��
		
		
		agv_24V_input(); 	//�ⲿ24V�����źŲɼ�
		AGV_Stop2Start();	//����ֹͣ�źŵĲɼ�,�����Ƴ���ֹͣ����
		
		
//		//���ߺ�ֹͣ��״̬��
//		if(g_Start_flag.Start_Manu_PID || g_Start_flag.Start_Auto_PID)		
//		{
//			if(temp_l >= 25)
//			{
//				Car_LED_Blue = !Car_LED_Blue;
//				temp_l = 0;
//			}	
//		}
//		else
//		{
//			Car_LED_Blue = 1;	//ֹͣ -- ���Ƴ���
//		}
//		
//		
//		//����ͻ�е���ϵ�״̬��
//		if(!g_Start_flag.Start_IR || !g_Start_flag.button_Start)	//ֹͣ
//		{
//			Car_LED_Yellow = 1;			//�Ƶ���˸
//		}
//		else
//		{
//			Car_LED_Yellow = 0;
//		}
//		

//		if(temp_l>200)
//		{
//			temp_l = 0;
//		}
//		temp_l++;
		
		OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_HMSM_STRICT,&err); //ÿ10ms�������״̬
	}
}

void float_task(void *p_arg)		//����ͻ�е����
{
	OS_ERR err;
	u8 temp_i=0;
	u8 temp_j=0;
	u8 temp_k=0;
	u8 temp_flag[]={0,0,0,0};
	

	u8 temp_Tiaojian[] = {0,0,0,0};					//����
	u8 *temp_Jieguo[]  = {&g_Start_flag.Start_IR,&g_Start_flag.Start_jixie,&g_Start_flag.Start_IR,&g_Start_flag.Start_jixie};		//���
	
	g_Start_flag.Start_IR=1;
	g_Start_flag.Start_jixie=1;

	while(1)
	{	
		#if 0
		
		if(!g_AGV_Car_mode)				//�Զ�ģʽ
		{
			if(!g_AGV_Car_dir)	//0:ǰ��
			{
				temp_j = 0;
			}
			else				//1:����
			{
				temp_j = 2;
			}	
		}
		else							//�ֶ�ģʽ
		{
			//0:ֹͣ1:ǰ�� 2:���� 3:��ת 4:��ת 5���� 6���� 7���� 8���� 9���� 10���� 
			if(g_AGV_shoudong_dir==1||g_AGV_shoudong_dir==5||g_AGV_shoudong_dir==6)			//ǰ��
			{
				temp_j = 0;		
			}
			else if(g_AGV_shoudong_dir==2||g_AGV_shoudong_dir==7||g_AGV_shoudong_dir==8)	//����				//1:����
			{
				temp_j = 2;
			}		
		}
		
		if(temp_j == 0)
		{
			temp_Tiaojian[0] = g_flag_IR_qian_jin;			//����
			temp_Tiaojian[1] = g_flag_fangzhuang_qian;		//����		
		}
		else if(temp_j == 2)
		{
			temp_Tiaojian[2] = g_flag_IR_hou_jin;			//����
			temp_Tiaojian[3] = g_flag_fangzhuang_hou;		//����			
		}

		
	
		
		for(temp_i=temp_j;temp_i<temp_j+2;temp_i++)
		{
			if(temp_Tiaojian[temp_i] == 0)				//��������� 0����
			{
//				delay_rtos(0,0,0,10);
//				if(temp_j == 0)
//				{
//					temp_Tiaojian[0] = g_flag_IR_qian_jin;			//����
//					temp_Tiaojian[1] = g_flag_fangzhuang_qian;		//����		
//				}
//				else if(temp_j == 2)
//				{
//					temp_Tiaojian[2] = g_flag_IR_hou_jin;			//����
//					temp_Tiaojian[3] = g_flag_fangzhuang_hou;		//����			
//				}
				
				if(temp_Tiaojian[temp_i] == 0)				//��������� 0����
				{
					*temp_Jieguo[temp_i] = 0;	//0ֹͣ
				}
			}	
			else
			{
//				delay_rtos(0,0,0,10);
//				if(temp_j == 0)
//				{
//					temp_Tiaojian[0] = g_flag_IR_qian_jin;			//����
//					temp_Tiaojian[1] = g_flag_fangzhuang_qian;		//����		
//				}
//				else if(temp_j == 2)
//				{
//					temp_Tiaojian[2] = g_flag_IR_hou_jin;			//����
//					temp_Tiaojian[3] = g_flag_fangzhuang_hou;		//����			
//				}
				
				if(temp_Tiaojian[temp_i] == 1)		
				{
					if(*temp_Jieguo[temp_i] == 0)
					{
//						temp_k++;
//						if(temp_k > 100)
//						{
//							*temp_Jieguo[temp_i] = 1;	//1����
//						}
						delay_rtos(0,0,1,0);
						*temp_Jieguo[temp_i] = 1;	//1����
					}
					else
					{
						*temp_Jieguo[temp_i] = 1;	//1����
					}
					
				}		
			}					
		}
		
		#endif

		OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱms
	}
}



void motec_task(void *p_arg)			//��ʼ��������
{
	OS_ERR err;
	p_arg = p_arg;

	while(1)
	{
		check_Motec_init();
		delay_rtos(0,0,0,20);
		
	}		
}


//�Զ���������
void Auto_task(void *p_arg)			//�Զ�ģʽ--ǰ��PID
{
	OS_ERR err;
	p_arg = p_arg;

	//speek("����");
	while(1)
	{
		if(AGV_SYS.Car_Auto_Speed>0 && g_AGV_Car_mode == 0) 
		{
			if(g_Start_flag.Start_Auto_PID)		//1:�ҵ�����
			{
				PID_AUTO_QianLun(AGV_SYS.Car_Auto_Speed,AGV_SYS.AUTO_Kp,AGV_SYS.AUTO_Ki,AGV_SYS.AUTO_Kd);	//ǰ��
			}
			else
			{
				OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_HMSM_STRICT,&err); 		//�ݶ�5ms		
			}			
			
		}
		else
		{
			OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_HMSM_STRICT,&err); 		//�ݶ�5ms		
		}
	}		
}
void PID_task(void *p_arg)			//�Զ�ģʽ--����PID
{
	OS_ERR err;
	p_arg = p_arg;
	
	while(1)
	{
		if(AGV_SYS.Car_Auto_Speed>0 && g_AGV_Car_mode == 0) 
		{
			if(g_Start_flag.Start_Auto_PID)		//1:�ҵ�����
			{
				
				PID_AUTO_HouLun(AGV_SYS.Car_Auto_Speed,AGV_SYS.AUTO_Kp,AGV_SYS.AUTO_Ki,AGV_SYS.AUTO_Kd);		//����
				//g_CtXunZheng.XunZ_OK_AGV = 0;	//��������Ϲ��־
			}
			else
			{
				OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_HMSM_STRICT,&err); 		//�ݶ�5ms		
			}			
		}
		else
		{
			OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_HMSM_STRICT,&err); 		//�ݶ�5ms		
		}
	}
}


u16 ppppppp=800;
void Manual_task(void *p_arg)  		//�ֶ�����
{
	//OS_ERR err;
	p_arg = p_arg;
	
	while(1)
	{
		
		if(g_Init_OK_Motec)
		{
			//ǰ������ת -- ���ִ�ֱ,ǰ�ָ���ת��
			//��������ת -- ǰ�ִ�ֱ,���ָ���ת��
		
		
			if(g_AGV_Car_mode) //1://�ֶ�ģʽ
			{	
				if(AGV_SYS.Car_SD_Speed > 50 && g_AGV_shoudong_dir!=0) 	
				{
					if(g_Start_flag.Start_Manu_PID)			//1:����
					{
						g_XZ_Ok = 0;
						
						PID_SD_Adjust(AGV_SYS.Car_SD_Speed,AGV_SYS.SD_Kp,AGV_SYS.SD_Ki,AGV_SYS.SD_Kd);	//��ʱ������
					}		
					else									//0:ֹͣ
					{
						MotoStop(0);
						if(!g_XZ_Ok)
						{
							DwqXunZheng_QH();				//��λ��Ѱ��	
						}					
					}
				}		
				else 
				{
					MotoStop(0);							//��������,��һֱ����				
					if(!g_XZ_Ok)
					{
						DwqXunZheng_QH();					//��λ��Ѱ��	
					}
					
					
					if(g_Start_flag.button_Start==0)
					{
						g_Start_flag.Start_Manu_PID = 0;		//�����ֶ�PID	
					}
					else
					{
						g_Start_flag.Start_Manu_PID = 1;		//�����ֶ�PID	
					}
									
				}					
			}
			else		//0://�Զ�ģʽ
			{
				delay_rtos(0,0,0,20); //
			}			
		}
		
		else
		{
			delay_rtos(0,0,0,20); //
		}

	}
}


void Screen_task(void *p_arg)    	//�������������
{
	OS_ERR err;
	p_arg = p_arg;	
	


	while(1)
	{

		#if 1
		
	    switch(HmiScreenSetGet)
        {

			//�����߽�������
			case ShouDongJieMian: 		//--3					//3//�ֶ���������
			{
				while(HmiScreenSetGet == ShouDongJieMian)		
				{
					
					 if(g_shoudong_manual == 1)						//��Ļ���ֶ���������ʱ
					 {
							//Shou_Dong();		//�е��ֶ�����
						 
							g_AGV_Car_mode = 1;
							speek("�ֶ�");
							delay_rtos(0,0,0,500);
					 }
					 else if(g_shoudong_auto == 1)				//��Ļ���Զ���������ʱ
					 {
							//Zi_Dong();			//�е��Զ�����
							g_AGV_Car_mode = 0;
							speek("�Զ�");
						 delay_rtos(0,0,0,500);
					 }
					 else if(g_shoudong_guntong_zuozhuan == 1)				//��Ͳ��ת
					 {
							//Cha_Sheng();
							guntong_start = 1;		//�ߵ�ƽ��Ч
							speek("��Ͳ��ת");
						 delay_rtos(0,0,0,500);
					 }
					 else if(g_shoudong_guntong_youzhuan == 1)				//��Ͳ��ת
					 {
							//Cha_Jiang();
							guntong_fanzhuan = 1;	//�ߵ�ƽ��Ч
							speek("��Ͳ��ת");
						 delay_rtos(0,0,0,500);
					 }
					 else if(g_shoudong_turn_left == 1)				//��ת
					 {
							//Zuo_Fen();
							speek("��ת��");
						 delay_rtos(0,0,0,500);
					 }
					 else if(g_shoudong_turn_right == 1)				//��ת
					 {
							//You_Fen();
							speek("��ת��");
						 delay_rtos(0,0,0,500);
					 }
					 if(g_AGV_Car_mode == 0)				//0:�Զ�ģʽ 1:�Զ�ģʽ
					 {
							if(g_shoudong_start == 1)			//����
							{
								//Qi_Dong();		//����������
								g_shoudong_start = 1;
								speek("����");
								delay_rtos(0,0,0,500);
							}
							if(g_shoudong_stop == 1)		 	//ֹͣ
							{
								//Ting_Zhi();		//ֹͣ������
								g_shoudong_stop = 1;
								speek("ֹͣ");
								delay_rtos(0,0,0,500);
							}
							else if(g_shoudong_goto == 1)		//����ǰ������,�Զ�ģʽ��,�������߷���
							{
								//Qian_Jin();		//ǰ��ģʽ
								g_AGV_Car_dir = 0;
								speek("����ǰ��");
								delay_rtos(0,0,0,500);
							}
							else if(g_shoudong_goback == 1) 	//���ú��˷���,�Զ�ģʽ��,�������߷���
							{
								//Hou_You();		//����ģʽ
								g_AGV_Car_dir = 1;
								speek("�������");
								delay_rtos(0,0,0,500);
							}
					 }

					 AGV_SYS.SD_Speed_bili = g_shoudong_screen_speed;	//PLC_Data[3]				//������Ļ���ٶ���ʾֵ

					 SystemParameter[3] = AGV_SYS.SD_Speed_bili;		//�ֶ��ٶȱ���:  x/10


					osdelay_ms(20);
				}
				SetOneParameterToSystem(SystemParameter[3], 3);
			}
			break;
			//·���滮�ν���	
			case LuJingSheZhiJieMian: 				//9//·�����ý��棨��һ��ѡ��滮·��ʱ�Ľ��棩
			{
				//���·����Ϊ�㣬����һ
				if(HmiRouteNum == 0)
				{
					 HmiRouteNum = 2;
				}
			}
			break;
			case LuJingGuiHuaJieMian:					//4·���滮����
			case FuZhiLuJingTanChuJieMian:				//11����·������
			case QueDingChaRuZhanDianJieMian: 			//12����·������
			case QueDingShanChuZhanDianJieMian:			//13ɾ��·������
			case XvNiDiBiaoJieMian:  					//14����ر����
			{
				while(HmiScreenSetGet == LuJingGuiHuaJieMian || HmiScreenSetGet == FuZhiLuJingTanChuJieMian ||
						HmiScreenSetGet == QueDingChaRuZhanDianJieMian || HmiScreenSetGet == QueDingShanChuZhanDianJieMian ||
						HmiScreenSetGet == XvNiDiBiaoJieMian)
				{
	//				 //����·��
	//				 if(HmiScreenSetGet == FuZhiLuJingTanChuJieMian)
	////				 {
	////						//������·���ų�ʼ��Ϊ1
	////						HmiRouteCopiedNum = 1;
	////						while(HmiScreenSetGet == FuZhiLuJingTanChuJieMian) //���ڸ���·������
	////						{
	////							//������·����Ϊ��ʱ��1
	////							if(HmiRouteCopiedNum == 0)
	////								 HmiRouteCopiedNum = 1;
	////							if(HmiRouteCopiedNum > RouteNum)
	////							{
	////								 HmiRouteCopiedNum = 1;
	////							}

	////							//����ı��������̺ű仯ʱ����
	////							if(HmiRouteCopiedNumTemp != HmiRouteCopiedNum)
	////								 HmiRouteCopiedCount = GetRouteStationNum(HmiRouteCopiedNum);


	////							//ȷ������
	////							if(HmiRoutemode == 1)
	////							{
	////								 //��ȡ��������Ϣ����ǰ
	////								 GetRouteData(HmiRouteCopiedNum);

	////								 //���沢���±�������Ϣ
	////								 SetRouteData(HmiRouteNum);

	////								 UpdataStationToHmi();

	////								 //���õ�ǰվ��Ϊ1
	////								 if(HmiStationNum != 0)
	////										HmiStationSerialNum = 1;

	////								 //�˳�����ģʽ
	////								 HmiRoutemode = 0;
	////							}
	////							osdelay_ms(10);
	////						}
	////				 }

	//				 //���վ��
	//				 if(HmiRoutemode == 2)									//4x41ȷ��������ģʽ���鿴0������1�����2������3������4��ɾ��5
	//				 {
	//						//վ������һ
	//						HmiStationNum ++;
	//						//վ��ŵ���վ����
	//						HmiStationSerialNum = HmiStationNum;

	//						//�ر������
	//						keynumber = 0;

	//						ClearStationToHmi();
	//				 
	//						while(HmiRoutemode == 2)
	//						{
	//							//��������ر꣬���µ���ʾ��
	//							if(keynumber != 0)
	//							{
	//								 HmiRfidNum = keynumber;//ˢ�µر��
	//								 keynumber = 0;
	//							}

	//							//ȷ��
	//							if(HmiRouteEnter == 1)
	//							{
	//								 HmiRouteEnter = 0;
	//								 //����վ�����ݵ���ǰ����
	//								 UpdataStationToNow();
	//								 //���浱ǰվ������
	//								 SetRouteData(HmiRouteNum);
	//								 //�˳����ģʽ
	//								 HmiRoutemode =	0;
	//							}
	//							else
	//								 //ȡ��
	//								 if(HmiRouteEnter == 2)
	//								 {
	//										HmiRouteEnter = 0;
	//										//վ������һ
	//										HmiStationNum--;
	//										//վ��ŵ���վ����
	//										HmiStationSerialNum = HmiStationNum;
	//										//�˳����ģʽ
	//										HmiRoutemode =	0;
	//								 }
	//							osdelay_ms(10);
	//						}
	//				 }
	//				 //����վ��
	//				 if(HmiRoutemode == 3)
	//				 {
	//						//վ������һ
	//						HmiStationNum ++;
	//						//վ���Ϊ��ʱ��һ
	//						if(HmiStationNum == 0)
	//							HmiStationSerialNum = 1;

	//						//�ر������
	//						keynumber = 0;

	//						ClearStationToHmi();

	//						while(HmiRoutemode == 3)
	//						{
	//							//��������ر꣬���µ���ʾ��
	//							if(keynumber != 0)
	//							{
	//								 HmiRfidNum = keynumber;//ˢ�µر��
	//								 keynumber = 0;
	//							}

	//							//ȷ��
	//							if(HmiRouteEnter == 1)
	//							{
	//								 HmiRouteEnter = 0;

	//								 //վ����Ϣ����ƶ�һ��λ�ã������뵱ǰվ����Ϣ
	//								 for(i = HmiStationNum; i >= HmiStationSerialNum; i--)
	//								 {
	//										for(j = 0; j < StaiionInfor; j++)
	//										{
	//											NowRouteInfor[i][j] = NowRouteInfor[i - 1][j];
	//										}
	//								 }

	//								 //����վ����Ϣ����ǰ
	//								 UpdataStationToNow();

	//								 //����·����Ϣ
	//								 SetRouteData(HmiRouteNum);

	//								 //�˳����ģʽ
	//								 HmiRoutemode =	0;
	//							}
	//							else
	//								 //ȡ��
	//								 if(HmiRouteEnter == 2)
	//								 {
	//										HmiRouteEnter = 0;
	//										//վ������һ
	//										HmiStationNum--;
	//										//վ���Ϊ1ʱ����
	//										if(HmiStationSerialNum == 1)
	//											HmiStationSerialNum = 0;
	//										//�˳����ģʽ
	//										HmiRoutemode =	0;
	//								 }

	//							osdelay_ms(10);
	//						}

	//				 }
	//				 //����վ��
	//				 if(HmiRoutemode == 4)
	//				 {
	//						keynumber = 0;
	//						while(HmiRoutemode == 4)
	//						{
	//							//��������ر꣬���µ���ʾ��
	//							if(keynumber != 0)
	//							{
	//								 HmiRfidNum = keynumber;//ˢ�µر��
	//								 keynumber = 0;
	//							}

	//							//ȷ��
	//							if(HmiRouteEnter == 1)
	//							{
	//								 HmiRouteEnter = 0;
	//								 //����վ�����ݵ���ǰ����
	//								 UpdataStationToNow();
	//								 //���浱ǰվ������
	//								 SetRouteData(HmiRouteNum);
	//								 //�˳����ģʽ
	//								 HmiRoutemode =	0;
	//							}
	//							else
	//								 //ȡ��
	//								 if(HmiRouteEnter == 2)
	//								 {
	//										HmiRouteEnter = 0;
	//										//���µ�����
	//										UpdataStationToHmi();
	//										//�˳����ģʽ
	//										HmiRoutemode =	0;
	//								 }
	//							osdelay_ms(10);
	//						}
	//				 }

	//				 //ɾ��վ��
	//				 if(HmiRoutemode == 5)
	//				 {
	//						if(HmiStationNum > 0)
	//						{
	//							//��������������ǰ�ƶ�һλ
	//							if((HmiStationNum > 0) && ((HmiStationNum) != HmiStationSerialNum))
	//							{
	//								 //վ����Ϣ��ǰ�ƶ�һ��λ��
	//								 for(i = HmiStationSerialNum; i < HmiStationNum; i++)
	//								 {
	//										for(j = 0; j < StaiionInfor; j++)
	//										{
	//											NowRouteInfor[i - 1][j] = NowRouteInfor[i][j];
	//										}
	//								 }
	//							}

	//							HmiStationNum--;
	//							if(HmiStationNum == 0)
	//								 HmiStationSerialNum = 0;
	//							else if((HmiStationNum + 1) == HmiStationSerialNum)
	//								 HmiStationSerialNum--;
	//							//����·����Ϣ
	//							SetRouteData(HmiRouteNum);

	//							//���½���
	//							UpdataStationToHmi();
	//						}
	//						HmiRoutemode = 0;
	//				 }

	//				 //��ѯվ��
	//				 if(HmiRoutemode == 0)
	//				 {
	//						//��·��վ��������0���������Ϊ0ʱ���������Ϊ1����������ʾ����
	//						if((HmiStationNum > 0) && (HmiStationSerialNum == 0))
	//						{
	//							HmiStationSerialNum = 1;
	//							//���µ�����
	//							UpdataStationToHmi();
	//						}
	//						else if(HmiStationNum == 0)
	//						{
	//							HmiStationSerialNum = 0;
	//						}

	//						//·���ű仯ʱ�����½���
	//						if(HmiRouteNumFlag != HmiRouteNum)
	//						{
	//							HmiRouteNumFlag = HmiRouteNum;
	//							//��ȡ·����Ϣ
	//							GetRouteData(HmiRouteNum);
	//							if(HmiStationNum > 0)
	//								 HmiStationSerialNum = 1;
	//							//���µ�����
	//							UpdataStationToHmi();
	//						}

	//						//��һ��
	//						if(HmiStationLast == 1)
	//						{
	//							HmiStationLast = 0;
	//							if(HmiStationSerialNum > 1)
	//								 HmiStationSerialNum--;
	//							else
	//								 HmiStationSerialNum = HmiStationNum;
	//						}
	//						//��һ��
	//						if(HmiStationNext == 2)
	//						{
	//							HmiStationNext = 0;
	//							if(HmiStationSerialNum < HmiStationNum)
	//								 HmiStationSerialNum++;
	//							else if(HmiStationSerialNum != 0)
	//								 HmiStationSerialNum = 1;
	//						}

	//						if(HmiStationNum == 0)		//û��վ��
	//						{
	//							//���վ����Ϣ
	//							ClearStationToHmi();
	//						}
	//						else
	//						{
	//							//����վ����Ϣ
	//							UpdataStationToHmi();
	//						}
	//				 }
					osdelay_ms(10);
				}
			}
			break;
			//���̹滮�ν���
			case LiuChengSheZhiJieMian: 			//10//�������ý��棨��һ��ѡ��滮����ʱ�Ľ��棩
			{
				//������̺�Ϊ�㣬����һ
				if(HmiProcessNum == 0)
				{
					 HmiProcessNum = 1;
				}
			}
			break;
			case LiuChengGuiHuaJieMian:				//���̹滮����
			case FuZhiLiuChengTanChuJieMian:		//�������̽���
			case QueDingChaRuLiuChengJieMian:   	//�������̽���
			case QueDingShanChuLiuChengJieMian: 	//ɾ�����̽���
			{
				while(HmiScreenSetGet == LiuChengGuiHuaJieMian || HmiScreenSetGet == FuZhiLiuChengTanChuJieMian || HmiScreenSetGet == QueDingChaRuLiuChengJieMian || HmiScreenSetGet == QueDingShanChuLiuChengJieMian)
				{
//					 //�鿴ģʽ
//					 if(HmiProcessMode == 0)
//					 {
//							//��ǰ���̲�������0�����ҽ������Ϊ0ʱ���������Ϊ1����������ʾ����
//							if((HmiStepNum > 0) && (HmiProcessSerialNum == 0))
//							{
//								HmiProcessSerialNum = 1;
//								GetProcessData();
//							}
//							else if(HmiStepNum == 0)
//							{
//								HmiProcessSerialNum = 0;
//								HmiProcessStartNum = 0;
//								HmiProcessStopNum = 0;
//								HmiProcessAction = 0;
//							}

//							//���̺ű仯ʱ�����½���
//							if(HmiProcessNumFlag != HmiProcessNum)
//							{
//								HmiProcessNumFlag = HmiProcessNum;
//								GetProcessData();
//							}

//							if(HmiProcessLast == 1) //��һ��
//							{
//								HmiProcessLast = 0;
//								if(HmiProcessSerialNum > 1)
//									 HmiProcessSerialNum--;
//								else
//									 HmiProcessSerialNum = HmiStepNum;
//							}
//							else if(HmiProcessNext == 2) //��һ��
//							{
//								HmiProcessNext = 0;
//								if(HmiProcessSerialNum < HmiStepNum)
//									 HmiProcessSerialNum++;
//								else if(HmiProcessSerialNum != 0)
//									 HmiProcessSerialNum = 1;
//							}

//							if(HmiStepNum == 0)
//							{
//								ClearStepToHmi();
//							}
//							else
//							{
//								UpdataProcessToHmi();
//							}

//					 }

//					 //��������
//					 if(HmiScreenSetGet == FuZhiLiuChengTanChuJieMian)
//					 {
//							//��ʼ����������Ϊ1
//							HmiProcessCopiedNum = 1;
//							while(HmiScreenSetGet == FuZhiLiuChengTanChuJieMian)
//							{
//								//���������̺�Ϊ��ʱ��1
//								if(HmiProcessCopiedNum == 0)
//									 HmiProcessCopiedNum = 1;
//								if(HmiProcessCopiedNum > ProcessNum)
//									 HmiProcessCopiedNum = 1;

//								//����ı��������̺ű仯ʱ����
//								if(HmiProcessCopiedNumTemp != HmiProcessCopiedNum)
//									 HmiProcessCopiedCount = GetProcessStepNum(HmiProcessCopiedNum);

//								//ȷ������
//								if(HmiProcessMode == 1)
//								{
//									 //��ȡ��������Ϣ����ǰ
//									 GetProcessDataFrom(HmiProcessCopiedNum);
//									 //���汻������Ϣ
//									 SetProcessData();

//									 //���õ�ǰ���Ϊ1
//									 if(HmiStepNum != 0)
//											HmiProcessSerialNum = 1;

//									 //�˳�����ģʽ
//									 HmiProcessMode = 0;
//								}
//								osdelay_ms(10);
//							}
//					 }

//					 //�������
//					 if(HmiProcessMode == 2)
//					 {
//							//���̲�����һ
//							HmiStepNum++;
//							//��ŵ���������
//							HmiProcessSerialNum = HmiStepNum;

//							ClearStepToHmi();

//							while(HmiProcessMode == 2)
//							{
//								switch(HmiProcessAction)
//								{
//								case 0://����ִ��
//									 break;
//								case 1://˳��ִ�е�
//									 if(HmiProcessStopNum <= HmiProcessStartNum)
//									 {
//											if(HmiProcessStartNum == ProcessNum)
//												HmiProcessStopNum = HmiProcessStartNum;
//											else
//												HmiProcessStopNum = HmiProcessStartNum + 1;
//									 }
//									 break;
//								case 2://����ִ��
//									 if(HmiProcessStopNum >= HmiProcessStartNum)
//									 {
//											if(HmiProcessStartNum == 1)
//												HmiProcessStopNum = HmiProcessStartNum;
//											else
//												HmiProcessStopNum = HmiProcessStartNum - 1;
//									 }
//									 break;
//								case 3://ѭ��ִ��
//									 if(HmiProcessStopNum == 0)
//									 {
//											HmiProcessStopNum = 1;
//									 }
//									 break;
//								default:
//									 break;
//								}

//								//ȷ��
//								if(HmiProcessEnter == 1)
//								{
//									 HmiProcessEnter = 0;
//									 //���沢��������
//									 SetProcessData();

//									 //�˳����ģʽ
//									 HmiProcessMode = 0;
//								}
//								//ȡ��
//								else if(HmiProcessEnter == 2)
//								{
//									 HmiProcessEnter = 0;

//									 //���̲�����һ
//									 HmiStepNum--;
//									 //��ŵ���������
//									 HmiProcessSerialNum = HmiStepNum;

//									 //�˳����ģʽ
//									 HmiProcessMode = 0;
//								}
//								osdelay_ms(10);
//							}
//					 }


//					 //��������
//					 if(HmiProcessMode == 3)
//					 {
//							//���̲�����һ
//							HmiStepNum++;
//							//���Ϊ��ʱ��һ
//							if(HmiProcessSerialNum == 0)
//								HmiProcessSerialNum = 1;

//							ClearStepToHmi();

//							while(HmiProcessMode == 3)
//							{
//								switch(HmiProcessAction)
//								{
//								case 0://����ִ��
//									 break;
//								case 1://˳��ִ�е�
//									 if(HmiProcessStopNum <= HmiProcessStartNum)
//									 {
//											if(HmiProcessStartNum == ProcessNum)
//												HmiProcessStopNum = HmiProcessStartNum;
//											else
//												HmiProcessStopNum = HmiProcessStartNum + 1;
//									 }
//									 break;
//								case 2://����ִ��
//									 if(HmiProcessStopNum >= HmiProcessStartNum)
//									 {
//											if(HmiProcessStartNum == 1)
//												HmiProcessStopNum = HmiProcessStartNum;
//											else
//												HmiProcessStopNum = HmiProcessStartNum - 1;
//									 }
//									 break;
//								case 3://ѭ��ִ��
//									 if(HmiProcessStopNum == 0)
//									 {
//											HmiProcessStopNum = 1;
//									 }
//									 break;
//								default:
//									 break;
//								}

//								//ȷ��
//								if(HmiProcessEnter == 1)
//								{
//									 HmiProcessEnter = 0;

//									 //���沢��������
//									 InsertProcessData();

//									 //�˳�����ģʽ
//									 HmiProcessMode = 0;
//								}
//								//ȡ��
//								else if(HmiProcessEnter == 2)
//								{
//									 HmiProcessEnter = 0;

//									 //���̲�����һ
//									 HmiStepNum--;
//									 //���Ϊ1ʱ��һ
//									 if(HmiProcessSerialNum == 1)
//											HmiProcessSerialNum = 0;

//									 //�˳����ģʽ
//									 HmiProcessMode = 0;
//								}
//								osdelay_ms(10);
//							}
//					 }

//					 //��������
//					 if(HmiProcessMode == 4)
//					 {
//							while(HmiProcessMode == 4)
//							{
//								switch(HmiProcessAction)
//								{
//								case 0://����ִ��
//									 break;
//								case 1://˳��ִ�е�
//									 if(HmiProcessStopNum <= HmiProcessStartNum)
//									 {
//											if(HmiProcessStartNum == ProcessNum)
//												HmiProcessStopNum = HmiProcessStartNum;
//											else
//												HmiProcessStopNum = HmiProcessStartNum + 1;
//									 }
//									 break;
//								case 2://����ִ��
//									 if(HmiProcessStopNum >= HmiProcessStartNum)
//									 {
//											if(HmiProcessStartNum == 1)
//												HmiProcessStopNum = HmiProcessStartNum;
//											else
//												HmiProcessStopNum = HmiProcessStartNum - 1;
//									 }
//									 break;
//								case 3://ѭ��ִ��
//									 if(HmiProcessStopNum == 0)
//									 {
//											HmiProcessStopNum = 1;
//									 }
//									 break;
//								default:
//									 break;
//								}

//								//ȷ��
//								if(HmiProcessEnter == 1)
//								{
//									 HmiProcessEnter = 0;
//									 //���沢��������
//									 SetProcessData();

//									 //�˳�����ģʽ
//									 HmiProcessMode = 0;
//								}
//								//ȡ��
//								else if(HmiProcessEnter == 2)
//								{
//									 HmiProcessEnter = 0;

//									 //�˳����ģʽ
//									 HmiProcessMode = 0;
//								}
//								osdelay_ms(10);
//							}
//					 }

//					 //ɾ������
//					 if(HmiProcessMode == 5)
//					 {
//							DeleteProcessData();
//							//�˳�ɾ��ģʽ
//							HmiProcessMode = 0;
//					 }

					 osdelay_ms(10);
				}
			}
			break;
			//ִ������ν���
			case ZhiXingLuJingJieMian: 				//18//ִ��·������
			{
				while(HmiScreenSetGet == ZhiXingLuJingJieMian)
				{
//					 if(ZhiXingLuJingQueDing == 1)
//					 {
//							//����·����
//							SetOneParameterToSystem(HmiRouteNum, 24);
//							SystemParameter[26] = HmiTask;
//							//���������
//							SetOneParameterToSystem(HmiTask, 26);
//							ZhiXingLuJingQueDing = 0;

//							//�����Զ�������Ϣ
//							HmiAutoReload();

//							HmiTask = 1;

//							FX_flag = 1; //�����л���ǰ��

//							//��ת���Զ�����
//							HmiScreenSetGet = ZiDongJieMian;
//					 }
					 osdelay_ms(10);
				}
			}
			break;
			case ZhiXingLiuChengJieMian:  			//ִ�����̽���
			{
				while(HmiScreenSetGet == ZhiXingLiuChengJieMian)
				{
//					 if(ZhiXingLiuChengQueDing == 1)
//					 {
//							ActiveProcess();
//							ZhiXingLiuChengQueDing = 0;
//					 }
					 osdelay_ms(10);
				}
			}
			break;
			case ZiDongJieMian: 					//20�Զ����н���
			{
				while(HmiScreenSetGet == ZiDongJieMian)
				{
					 if(PLC_OutPut[4] == 1)						//��Ļ���ֶ���������ʱ
					 {
							//Shou_Dong();		//�е��ֶ�����
							g_AGV_Car_mode = 1;
					 }
					 else if(PLC_OutPut[5] == 1)				//��Ļ���Զ���������ʱ
					 {
							//Zi_Dong();			//�е��Զ�����
							g_AGV_Car_mode = 0;			 
					 }
					 if(g_AGV_Car_mode == 0)				//0:�Զ�ģʽ 1:�ֶ�ģʽ
					 {
							if(PLC_OutPut[11] == 1)			//����
							{
								//Qi_Dong();
								g_shoudong_start = 1;
							}
							if(PLC_OutPut[12] == 1)		 	//ֹͣ
							{
								//Ting_Zhi();
								g_shoudong_stop = 1;
							}
					 }
					 osdelay_ms(20);
				}
			}
			break;
			case QuXiaoRenWuJieMian: 				//ȡ���������
			{
				while(HmiScreenSetGet == QuXiaoRenWuJieMian)
				{
//					 if(QuXiaoRenWuQueDing == 1)
//					 {
//							QuXiaoRenWuQueDing = 0;

//							HmiTask = 0;

//							//����״̬Ϊ����
//							HmiTaskState = 0;

//							//ͣ��
//							Ting_Zhi();

//							//��������ź�
//							PLC2_Data[22] = 1; //(1,�����Ű�ť��10�����¿��Ű�ť)

//							//�л������ʶΪǰ��
//							FX_flag = 1;

//							//����������
//							PLC2_Data[32] = 0;
//							//����豸���ź�
//							PLC2_Data[38] = 0;
//							PLC2_Data[39] = 0;
//							PLC2_Data[40] = 0;
//							PLC2_Data[41] = 0;

//							//��ת���棬����֮ǰ����
//				//							  if(lastscreenNum != 0)
//				//							  {
//				//									HmiScreenSetGet = lastscreenNum;
//				//									lastscreenNum = 0;
//				//							  }
//				//							  else
//								HmiScreenSetGet = 2;

//							//ɾ������
//							OSTaskDel((OS_TCB*)&Task5_TaskTCB, &err);
//							//���´�������
//							OSTaskCreate((OS_TCB 	* )&Task5_TaskTCB,
//											(CPU_CHAR	* )"Task5 task",
//											(OS_TASK_PTR )Task5_task,
//											(void		* )0,
//											(OS_PRIO	  )Task5_TASK_PRIO,
//											(CPU_STK   * )&Task5_TASK_STK[0],
//											(CPU_STK_SIZE)Task5_STK_SIZE / 10,
//											(CPU_STK_SIZE)Task5_STK_SIZE,
//											(OS_MSG_QTY  )0,
//											(OS_TICK	  )0,
//											(void   	* )0,
//											(OS_OPT      )OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
//											(OS_ERR 	* )&err);
//					 }
					 osdelay_ms(10);
				}
			}
			break;
			//���ݵ��Լ�ϵͳ��������γ���
			case ChuanGanQiJieMian:					//22//���������Ը�����������״̬���µ���Ļ��
			{
				while(HmiScreenSetGet == ChuanGanQiJieMian)
				{
					g_IR_yuan_CAR_qian 	= 	AGV_input_24V_buff[2];	//g_flag_IR_qian_yuan;							//#define g_IR_yuan_CAR_qian 		PLC_OutPut[25]	//��ǰԶ�������
					g_IR_yuan_CAR_hou	=	AGV_input_24V_buff[3];	//g_flag_IR_hou_yuan;								//#define g_IR_yuan_CAR_hou		PLC_OutPut[26]	//����Զ�������
                    
					g_IR_jin_CAR_qian	=	AGV_input_24V_buff[8];	g_flag_IR_qian_jin;								//#define g_IR_jin_CAR_qian		PLC_OutPut[29] //��ǰ������
					g_IR_jin_CAR_hou	=	AGV_input_24V_buff[9];	//								//#define g_IR_jin_CAR_hou		PLC_OutPut[30] //���������
                    
					g_jiexie_qian		=	AGV_input_24V_buff[4];	//g_flag_fangzhuang_qian;								//#define g_jiexie_qian			PLC_OutPut[46]	//ǰ��е����
					g_jiexie_hou		=	AGV_input_24V_buff[5];	//g_flag_fangzhuang_hou;								//#define g_jiexie_hou			PLC_OutPut[47]	//���е����
                    
					g_IR_guntong_left	=	AGV_input_24V_buff[6];	//g_flag_guntong_zuo;								//#define g_IR_guntong_left		PLC_OutPut[27]	//��Ͳ�����
					g_IR_guntong_right	=	AGV_input_24V_buff[7];	//g_flag_guntong_you;							//#define g_IR_guntong_right		PLC_OutPut[28]  //��Ͳ�Һ���
					
					g_jixieKEY_start	=	AGV_input_24V_buff[1];	//g_button_start;
					g_jixieKEy_stop		=	AGV_input_24V_buff[0];	//g_button_stop;
					
					osdelay_ms(10);
				}
			}
			break;
			case JiBenShuJuJieMian:					//23//�������ݲ��Խ���
			{
				while(HmiScreenSetGet == JiBenShuJuJieMian)
				{
					
					
					g_screen_qianCDH1 = g_cinavi1_RXbuff[0];
					g_screen_qianCDH2 = g_cinavi2_RXbuff[0];
					g_screen_houCDH1  = g_cinavi3_RXbuff[0];
					g_screen_houCDH2  = g_cinavi4_RXbuff[0];
					
					g_screen_qianlun_jiaodu = g_After_filter[1];
					g_screen_houlun_jiaodu 	= g_After_filter[2];
					
					 AGV_SYS.AUTO_Kp = g_screen_Auto_Kp;		           //�����Զ�Kp
					 AGV_SYS.AUTO_Ki = g_screen_Auto_Ki;                 //�����Զ�ki
					 AGV_SYS.AUTO_Kd = g_screen_Auto_Kd;                 //�����Զ�kd

					 AGV_SYS.SD_Kp = g_screen_Manu_Kp;	          	  //�����ֶ�kp
					 AGV_SYS.SD_Ki = g_screen_Manu_Ki;               	  //�����ֶ�ki
					 AGV_SYS.SD_Kd = g_screen_Manu_Kd;              	  //�����ֶ�kd

//					 AGV_SYS.PID_time  = g_screen_control_TIME;						//����ǰ����PID��������
					
					 g_DWQ.qianlun_L_val 	 = g_screen_qianlun_ZuoZhi;					//ǰ������
					 g_DWQ.qianlun_zhong_val = g_screen_qianlun_ZhongZhi;					//ǰ����ֵ
					 g_DWQ.qianlun_R_val 	 = g_screen_qianlun_YouZhi;					//ǰ���Ҽ���
					
					 g_DWQ.houlun_L_val 	 = g_screen_houlun_ZuoZhi;					//��������
					 g_DWQ.houlun_zhong_val  = g_screen_houlun_ZhongZhi;					//������ֵ
					 g_DWQ.houlun_R_val 	 = g_screen_houlun_YouZhi;					//�����Ҽ���					

					 SystemParameter[50] = g_screen_Auto_Kp;
					 SystemParameter[51] = g_screen_Auto_Ki;
					 SystemParameter[52]= g_screen_Auto_Kd;
					 
					 SystemParameter[53] = g_screen_Manu_Kp;
					 SystemParameter[54] = g_screen_Manu_Ki;
					 SystemParameter[55] = g_screen_Manu_Kd;	
					 
//					 SystemParameter[56]= g_screen_control_TIME;
					 
					 SystemParameter[57]= g_screen_qianlun_ZuoZhi;
					 SystemParameter[58]= g_screen_qianlun_ZhongZhi;
					 SystemParameter[59]= g_screen_qianlun_YouZhi;
					 
					 SystemParameter[60] = g_screen_houlun_ZuoZhi;
					 SystemParameter[61] = g_screen_houlun_ZhongZhi; 	
					 SystemParameter[62] = g_screen_houlun_YouZhi; 
					 
					 osdelay_ms(20);
				}

				W25QXX_Write_16(SystemParameter+50, 50, 13);			//����ǰ��Ļ����д�뵽flash��
			}
			break;
			case ChaBiShuJuJieMian:					//24//Ԥ�����ݵ���
			{
				while(HmiScreenSetGet == ChaBiShuJuJieMian)
				{
					//#define XZ_Speed40       	 PLC_Data[46] 		//Ѱ������ٶ�
					//#define XZ_Speed41        	 PLC_Data[48] 		//��λ��Ѱ���ٶȱ�
					//#define XZ_Speed42       	 PLC_Data[49] 		//����Ѱ���ٶ�
					//#define XZ_Speed43       	 PLC_Data[50] 		//�������ٶ�


					
					AGV_SYS.XZ_MAX_Speed 		= SystemParameter[40] 		= 	XZ_Speed40;
					AGV_SYS.XZ_DWQ_Speed_bili 	= SystemParameter[41] 		= 	XZ_Speed41;
					AGV_SYS.XZ_CiTiao_Speed 	= SystemParameter[42] 		= 	XZ_Speed42;
					AGV_SYS.SD_Speed_bili 		= SystemParameter[43] 		= 	XZ_Speed43;
					

					osdelay_ms(20); 
				}
				W25QXX_Write_16(SystemParameter+40, 40, 4);			//����ǰ��Ļ����д�뵽flash��
			}
			break;
			case LeiDaShuJuJieMian:					//25//���ԭʼ���� 
			{
				while(HmiScreenSetGet == LeiDaShuJuJieMian)
				{
					Li_dianya 				=	g_battery.dianya*10;		
					Li_Realy_mah	        =	g_battery.Realy_mah*10;	
					Li_Std_mah 		        =	g_battery.Std_mah*10;		
					Li_XunHuan_time	        =	g_battery.XunHuan_time;
//		
					if(Li_Warning_val_NoBattery < 100)	//�͵�������ֵ
					{
						Battery_Warining.Warining_Val_NoBattery = Li_Warning_val_NoBattery;//PLC_Data[128]
						
						SystemParameter[70] = Battery_Warining.Warining_Val_NoBattery;					
					}
					else
					{
						Battery_Warining.Warining_Val_NoBattery = 99;//PLC_Data[128]
						
						SystemParameter[70] = Battery_Warining.Warining_Val_NoBattery;						
					}

					
					
//	//				 PLC_Data[135] = g_GetUT_buff[4];
//	//				 PLC_Data[136] = g_GetUT_buff[5];
//	//				 PLC_Data[137] = g_GetUT_buff[6];
//	//				 PLC_Data[138] = g_GetUT_buff[7];

					 osdelay_ms(20);
				}
				SetOneParameterToSystem(SystemParameter[70], 70);
			}
			break;
			case DianTiTiaoShiJieMian:				//26//���ݵ��Խ���(�ڳ��϶Ե��ݵ�һ�н��вٿغ���ʾ����״̬)
			{
				while(HmiScreenSetGet == ChuanGanQiJieMian)
				{
//					if(PLC_OutPut[31] == 1) //��¥�����ť
//					{
//						 PLC2_Data[18] = 0;
//					}
//					else if(PLC_OutPut[32] == 1) //һ¥�����ť
//					{
//						 PLC2_Data[19] = 0;
//					}
//					else if(PLC_OutPut[33] == 1) //3��ť
//					{
//						 PLC2_Data[20] = 0;
//					}
//					else if(PLC_OutPut[34] == 1) //1��ť
//					{
//						 PLC2_Data[21] = 0;
//					}
//					else if(PLC_OutPut[35] == 1) //����
//					{
//						 PLC2_Data[22] = 0;
//					}
//					else if(PLC_OutPut[36] == 1) //����
//					{
//						 PLC2_Data[23] = 0;
//					}
//					PLC_OutPut[37] = PLC2_Data[24]; //��¥ƽ�㣨��������¥��
//					PLC_OutPut[38] = PLC2_Data[25]; //һ¥ƽ�㣨������һ¥��
//					PLC_OutPut[39] = PLC2_Data[26]; //��¥��״̬����/�أ�
//					PLC_OutPut[40] = PLC2_Data[27]; //һ¥��״̬����/�أ�
					
					osdelay_ms(20);
				}
			}
			break;
			case XiTongCanShuJieMian:				//8//ϵͳ�������棬�ٶȵĵ�λ���á��״���ֵ���趨
			{
				while(HmiScreenSetGet == XiTongCanShuJieMian)
				{
					//30��ʼ				
					AGV_SYS.ID 				 = 		g_AGV_ID; 				//����	  
					AGV_SYS.yinliang		 = 		g_AGV_speaker_val;     	//ϵͳ����      
					AGV_SYS.Auto_Speed_bili	 = 		g_sys_set_agvSPEED;    	//AGV���� -- ���и� 
					AGV_SYS.Key_yuyin 		 = 		g_AGV_speaker_key ;	  	//ϵͳ��������     
					AGV_SYS.Key_RGB_LED 	 = 		g_AGV_LED_car_state ;  	//����״̬��    
					AGV_SYS.L_speed 		 = 		HmiDiSu ;      			//����    
					AGV_SYS.M_speed 		 = 		HmiZhongSu;     		//����    
					AGV_SYS.H_speed 		 = 		HmiGaoSu  ;    			//����
					AGV_SYS.duijie_speed 	 =		g_AGV_speed_duijie;		//��λ�Խ��ٶ�

					SystemParameter[30]		 = 		g_AGV_ID; 				//����	  
					SystemParameter[31] 	 = 		g_AGV_speaker_val;     	//ϵͳ����      
					SystemParameter[32] 	 = 		g_sys_set_agvSPEED;    	//AGV���� -- ���и� 
					SystemParameter[33]	 	 = 		g_AGV_speaker_key ;	  	//ϵͳ��������     
					SystemParameter[34] 	 = 		g_AGV_LED_car_state ;  	//����״̬��    
					SystemParameter[35] 	 = 		HmiDiSu ;      			//����    
					SystemParameter[36] 	 = 		HmiZhongSu;     		//����    
					SystemParameter[37] 	 = 		HmiGaoSu  ;    			//����
					SystemParameter[38] 	 = 		g_AGV_speed_duijie;		//��λ�Խ��ٶ�
					
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
					
					
                                                                                                               
					 osdelay_ms(20);
				}

				W25QXX_Write_16(SystemParameter+30, 30, 9);	//����ǰ��Ļ����д�뵽flash��
			}
			break; 
			//�û���������
			case YongHuShouYeJieMian:				//27//�û���ҳ
			{
				while(HmiScreenSetGet == YongHuShouYeJieMian)
				{
//					 if(PLC_Data[107] == 1)		//ȥ�������
//					 {
//							HmiProcessNum = 1;
//							PLC_Data[107] = 0;

//							//ִ������
//							ActiveProcess();
//					 }
//					 else if(PLC_Data[107] == 2)
//					 {
//							HmiProcessNum = 2;	//��������
//							PLC_Data[107] = 0;

//							//ִ������
//							ActiveProcess();
//					 }
					 osdelay_ms(20);
				}
			}
			break;
			
			default:
			break;
        }		

		#endif

			
		OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_HMSM_STRICT,&err);
	}	
}






//1.������λ��Ѱ��
//2.�������������´ŵ���Ѱ��
//3.ǰ���Ϲ����go

void Control_task(void *p_arg)		// ִ��·����ִ������ -- Ӧ�ò��������
{
	u16 i=0;
	u16 j=0; 
	u16 k=0;
	
	OS_ERR err;
	p_arg = p_arg;

	while(1)
    {
        //if(g_AGV_Car_mode == 0 && g_Start_flag.Start_Auto_PID == 1) //�Զ�ģʽ��������
//        {
//            //ִ��·��
//            if(HmiTask == 1)							//������ 0:������ 1:ִ��·�� 2:ִ������
//            {
//               
//                HmiRfidNum = 0; 						//�����ǰ�ر�
//                HmiStationSerialNum = 0;				//վ�������0
//                //������ѡ·����ִ����Ӧ����
//                for(i = 0; i < HmiStationNum; i++)
//                {
//                    StationAction(i);
//                }
//                HmiTask = 0;


//            }
//            else
//            {
//                //ִ������
//                if(HmiTask == 2)
//                {

//                    
//                    HmiRfidNum = 0;						//�����ǰ�ر�
//                    HmiProcessSerialNum = 0;			//���������0
//                    for(i = 0; i < HmiStepNum; i++)
//                    {
//                        HmiProcessSerialNum++;			//��������Լ�
//                        switch(NowProcessInfor[i][1])
//                        {
//							case 0://����ִ��
//								//����·����
//								HmiRouteNum = NowProcessInfor[i][0];
//								//��ȡ·������վ����
//								GetRouteStationNum(HmiRouteNum);
//								//��ȡ��ǰ·����Ϣ
//								GetRouteData(HmiRouteNum);

//								HmiStationSerialNum = 0;
//								//������ѡ·����ִ����Ӧ����
//								for(j = 0; j < HmiStationNum; j++)
//								{
//									StationAction(j);
//								}
//								break;
//							case 1://˳��ִ��
//								for(k = NowProcessInfor[i][0]; k <= NowProcessInfor[i][2]; k++)
//								{
//									//����·����
//									HmiRouteNum = k;
//									//��ȡ·������վ����
//									GetRouteStationNum(HmiRouteNum);
//									//��ȡ��ǰ·����Ϣ
//									GetRouteData(HmiRouteNum);

//									HmiStationSerialNum = 0;
//									//������ѡ·����ִ����Ӧ����
//									for(j = 0; j < HmiStationNum; j++)
//									{
//										StationAction(j);
//									}
//								}
//								break;
//							case 2://����ִ��
//								for(k = NowProcessInfor[i][0]; k >= NowProcessInfor[i][2]; k--)
//								{
//									//����·����
//									HmiRouteNum = k;
//									//��ȡ·������վ����
//									GetRouteStationNum(HmiRouteNum);
//									//��ȡ��ǰ·����Ϣ
//									GetRouteData(HmiRouteNum);

//									HmiStationSerialNum = 0;
//									//������ѡ·����ִ����Ӧ����
//									for(j = 0; j < HmiStationNum; j++)
//									{
//										StationAction(j);
//									}
//								}
//								break;
//							case 3://ѭ��ִ��
//								//����·����
//								HmiRouteNum = NowProcessInfor[i][0];
//								//��ȡ·������վ����
//								GetRouteStationNum(HmiRouteNum);
//								//��ȡ��ǰ·����Ϣ
//								GetRouteData(HmiRouteNum);
//								for(k = 0; k < NowProcessInfor[i][2]; k++)
//								{
//									HmiStationSerialNum = 0;
//									//������ѡ·����ִ����Ӧ����
//									for(j = 0; j < HmiStationNum; j++)
//									{
//										StationAction(j);
//									}
//								}
//								break;
//							default:
//								break;
//                        }
//                    }
//                    HmiTask = 0;
//					
//					
//					


//                    //HmiScreenSetGet = 16;//�����û���ҳ

////					if(lastscreenNum!=0)
////					{
//////						HmiScreenSetGet = lastscreenNum;
////						HmiScreenSetGet = 16;//�����û���ҳ
////						lastscreenNum = 0;
////					}
//                }
//            }
//        }
        OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱnms
    }	
	
}



void WIFI_task(void *p_arg)			//��δʹ�� 
{
	
	u8 temp_i=0;
	
	OS_ERR err;
	p_arg = p_arg;
	while(1)
	{
		
		
		
		
		
		
		OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_HMSM_STRICT,&err);
	}
}

void guntong_task(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg;
	while(1)
	{
		if(g_AGV_Car_mode) //1://�ֶ�ģʽ
		{
			if(g_AGV_shoudong_dir == 9)			//ҡ������--��Ͳ��ת
			{
				guntong_start = 1;
			}
			else if(g_AGV_shoudong_dir == 10)	//ҡ������--��Ͳ��ת
			{
				guntong_fanzhuan = 1;
			}
			else
			{
				guntong_start = 0;
				guntong_fanzhuan = 0;
			}
		
		}
		
	
		
		
//		//��յر�
//		g_AGV_RFID_ID=0;
//		while(g_AGV_RFID_ID==0)
//		{
//			OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_HMSM_STRICT,&err);
//		}

//		guntong1();
		
		OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_HMSM_STRICT,&err);
	}
}


//4x32  �Կ�����ַ
//g_After_filter[i]
void DCv_task(void *p_arg)											//��ѹ�ɼ�	
{
	u16 temp_i=0;
	u16 temp_j=0;
	u16 temp_k=0;
	u16 temp_p=0;
	
	u16 temp_m=0;
	

	
	OS_ERR err;
	p_arg = p_arg;
	
	GET_Battery();	//��ȡ�����Ϣ
	
		 Car_LED_Blue 	=1;
		 //Car_LED_Yellow =1;
		
		Car_LED_Qian_Enable	 =0;
		Car_LED_Hou_Enable  =0;	
	

	

	while(1)
	{		
		if(!AGV_SYS.Key_RGB_LED)
		{
			temp_m++;
			if(temp_m == 1)
			{
				Car_LED_Blue 	= 1 ;
				
			}
			if(temp_m == 50)
			{
				Car_LED_Blue 	= 0 ;
				
			}
			if(temp_m == 200)
			{
				
				temp_m = 0;
				
			}			
		}
		else
		{
			Car_LED_Blue 	= 0 ;
		}
			
		
			

				 

			
		
		
		temp_k++;

		if(temp_k > 100)		//1s
		{
			GET_Battery();	//��ȡ�����Ϣ
		
			temp_k = 0;				
		}			
		



		if(Sys_battery != 0 && Sys_battery <= Battery_Warining.Warining_Val_NoBattery)		// <10AH,����
		{
			sprintf(g_warning,"�������ڰٷ�֮%d,�뼰ʱ���",Battery_Warining.Warining_Val_NoBattery);		
			
			temp_p++;
			if(temp_p > 500)				//5s
			{
				if(!AGV_SYS.Key_yuyin)
				{
					speek((u8*)g_warning);
				}
				temp_p = 0;
			}
		 }
		
		

		
		//�����ر��������						//��250ms
		if(g_flag_RFID_beep)
		{
			BEEP = 1;
			temp_j++;
			if(temp_j == 25)
			{
				BEEP = 0;
				g_flag_RFID_beep = 0;	
				temp_j = 0;				
			}

		}

		////Ѱ���������						//��250ms
		//if(g_XZ_Beep)
		//{
		//	BEEP = 1;
		//	temp_j++;
		//	if(temp_j == 10)
		//	{
		//		BEEP = 0;
		//	}
		//	else if(temp_j == 30)
		//	{
		//		BEEP = 1;
		//	}
		//	else if(temp_j == 40)
		//	{
		//		BEEP = 0;
		//		
		//		temp_j = 0;			
		//		g_XZ_Beep = 0;				
		//	}

		//}
		
		//������ͨ��ָʾ�ƺͰ�������ָʾ��LED1		//500ms��˸
		temp_i++;
		if(temp_i == 50)
		{
			LED1 = 0;
			P_RUN_LED = 1;
		}
		if(temp_i == 100)
		{
			LED1 = 1;
			P_RUN_LED = 0;
			temp_i = 0;
		}
		
		
		OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_HMSM_STRICT,&err);	
	}
}









