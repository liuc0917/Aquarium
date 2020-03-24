#include "app_include.h"

#include "InitialTask.h"

int main()
{	
	OS_ERR err;
	CPU_SR_ALLOC();
	
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //中断优先级分组 分2组
	USART1_Init(9600);
	LED_Init();
	TFTLCD_Init();			//LCD初始化
	TOUCH_Init();
	FSMC_SRAM_Init();
	RTC_Init();
	
	my_mem_init(SRAMIN);		//初始化内部内存池
	my_mem_init(SRAMEX);		//初始化外部SRAM内存池

	OSInit(&err);		//初始化UCOSIII
	OS_CRITICAL_ENTER();//进入临界区
	//创建开始任务
	OSTaskCreate((OS_TCB 	* )&InitialTaskTCB,			//任务控制块
				 (CPU_CHAR	* )"initial task", 			//任务名字
                 (OS_TASK_PTR )initial_task, 			//任务函数
                 (void		* )0,						//传递给任务函数的参数
                 (OS_PRIO	  )INITIAL_TASK_PRIO,    	//任务优先级
                 (CPU_STK   * )&INITIAL_TASK_STK[0],	//任务堆栈基地址
                 (CPU_STK_SIZE)INITIAL_STK_SIZE/10,		//任务堆栈深度限位
                 (CPU_STK_SIZE)INITIAL_STK_SIZE,		//任务堆栈大小
                 (OS_MSG_QTY  )0,						//任务内部消息队列能够接收的最大消息数目,为0时禁止接收消息
                 (OS_TICK	  )0,						//当使能时间片轮转时的时间片长度，为0时为默认长度，
                 (void   	* )0,						//用户补充的存储区
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //任务选项
                 (OS_ERR 	* )&err);					//存放该函数错误时的返回值
	OS_CRITICAL_EXIT();	//退出临界区
	OSStart(&err);  //开启UCOSIII
	while(1);
}

