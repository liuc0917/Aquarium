#include "app_include.h"

#include "InitialTask.h"

int main()
{	
	OS_ERR err;
	CPU_SR_ALLOC();
	
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //�ж����ȼ����� ��2��
	USART1_Init(9600);
	LED_Init();
	TFTLCD_Init();			//LCD��ʼ��
	TOUCH_Init();
	FSMC_SRAM_Init();
	RTC_Init();
	
	my_mem_init(SRAMIN);		//��ʼ���ڲ��ڴ��
	my_mem_init(SRAMEX);		//��ʼ���ⲿSRAM�ڴ��

	OSInit(&err);		//��ʼ��UCOSIII
	OS_CRITICAL_ENTER();//�����ٽ���
	//������ʼ����
	OSTaskCreate((OS_TCB 	* )&InitialTaskTCB,			//������ƿ�
				 (CPU_CHAR	* )"initial task", 			//��������
                 (OS_TASK_PTR )initial_task, 			//������
                 (void		* )0,						//���ݸ��������Ĳ���
                 (OS_PRIO	  )INITIAL_TASK_PRIO,    	//�������ȼ�
                 (CPU_STK   * )&INITIAL_TASK_STK[0],	//�����ջ����ַ
                 (CPU_STK_SIZE)INITIAL_STK_SIZE/10,		//�����ջ�����λ
                 (CPU_STK_SIZE)INITIAL_STK_SIZE,		//�����ջ��С
                 (OS_MSG_QTY  )0,						//�����ڲ���Ϣ�����ܹ����յ������Ϣ��Ŀ,Ϊ0ʱ��ֹ������Ϣ
                 (OS_TICK	  )0,						//��ʹ��ʱ��Ƭ��תʱ��ʱ��Ƭ���ȣ�Ϊ0ʱΪĬ�ϳ��ȣ�
                 (void   	* )0,						//�û�����Ĵ洢��
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //����ѡ��
                 (OS_ERR 	* )&err);					//��Ÿú�������ʱ�ķ���ֵ
	OS_CRITICAL_EXIT();	//�˳��ٽ���
	OSStart(&err);  //����UCOSIII
	while(1);
}

