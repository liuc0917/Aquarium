//SYSTEM INCLUDE
#include "os.h"
#include "includes.h"
#include "GUI.h"
#include "GUIDemo.h"

//USER INCLUDE
#include "task_info.h"
#include "InitialTask.h"
#include "DrawComp.h"
#include "CtrlTask.h"

//������ƿ�
OS_TCB InitialTaskTCB;
OS_TCB TouchTaskTCB;
OS_TCB CtrlTaskTCB;
OS_TCB DRAWCOMPTaskTCB;

//�����ջ
CPU_STK INITIAL_TASK_STK[INITIAL_STK_SIZE];
CPU_STK TOUCH_TASK_STK[TOUCH_STK_SIZE];
CPU_STK CTRL_TASK_STK[CTRL_STK_SIZE];
CPU_STK DRAWCOMP_TASK_STK[DRAWCOMP_STK_SIZE];

//��ʼ������
void initial_task(void *p_arg)
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
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC,ENABLE);//����CRCʱ��
	WM_SetCreateFlags(WM_CF_MEMDEV);
	GUI_Init();  			//STemWin��ʼ��
	
	OS_CRITICAL_ENTER();	//�����ٽ���
	
	//DrawComp����	
	OSTaskCreate((OS_TCB*     )&DRAWCOMPTaskTCB,		
				 (CPU_CHAR*   )"DrawComp task", 		
                 (OS_TASK_PTR )drawcomp_task, 			
                 (void*       )0,					
                 (OS_PRIO	  )DRAWCOMP_TASK_PRIO,     
                 (CPU_STK*    )&DRAWCOMP_TASK_STK[0],	
                 (CPU_STK_SIZE)DRAWCOMP_STK_SIZE/10,	
                 (CPU_STK_SIZE)DRAWCOMP_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,  					
                 (void*       )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR*     )&err);
				 
	//����������
	OSTaskCreate((OS_TCB*     )&TouchTaskTCB,		
				 (CPU_CHAR*   )"Touch task", 		
                 (OS_TASK_PTR )touch_task, 			
                 (void*       )0,					
                 (OS_PRIO	  )TOUCH_TASK_PRIO,     
                 (CPU_STK*    )&TOUCH_TASK_STK[0],	
                 (CPU_STK_SIZE)TOUCH_STK_SIZE/10,	
                 (CPU_STK_SIZE)TOUCH_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,  					
                 (void*       )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR*     )&err);			 
	//LED1����
	OSTaskCreate((OS_TCB*     )&CtrlTaskTCB,		
				 (CPU_CHAR*   )"Ctrl task", 		
                 (OS_TASK_PTR )ctrl_task, 			
                 (void*       )0,					
                 (OS_PRIO	  )CTRL_TASK_PRIO,     
                 (CPU_STK*    )&CTRL_TASK_STK[0],	
                 (CPU_STK_SIZE)CTRL_STK_SIZE/10,	
                 (CPU_STK_SIZE)CTRL_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,  					
                 (void*       )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR*     )&err);				 
	OS_TaskSuspend((OS_TCB*)&InitialTaskTCB,&err);		//����ʼ����			 
	OS_CRITICAL_EXIT();	//�˳��ٽ���
}

