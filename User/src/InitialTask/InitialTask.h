#ifndef __INITIALTASK_H
#define __INITIALTASK_H

#define INITIAL_TASK_PRIO				3				//�������ȼ�
#define INITIAL_STK_SIZE 				1024			//�����ջ��С	

extern OS_TCB 	InitialTaskTCB;							//������ƿ�
extern CPU_STK 	INITIAL_TASK_STK[INITIAL_STK_SIZE];		//�����ջ	

void initial_task(void *p_arg);

#endif

