#ifndef __INITIALTASK_H
#define __INITIALTASK_H

#define INITIAL_TASK_PRIO				3				//任务优先级
#define INITIAL_STK_SIZE 				1024			//任务堆栈大小	

extern OS_TCB 	InitialTaskTCB;							//任务控制块
extern CPU_STK 	INITIAL_TASK_STK[INITIAL_STK_SIZE];		//任务堆栈	

void initial_task(void *p_arg);

#endif

