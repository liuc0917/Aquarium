#include <stdio.h>
#include "OS.h"

#include "led.h"
#include "Ctrltask.h"

//CTRL »ŒŒÒ
void ctrl_task(void *p_arg)
{
	OS_ERR err;
	while(1)
	{
		//printf("led1_task runing!\r\n");
		led1 = !led1;
		OSTimeDlyHMSM(0,0,1,0,OS_OPT_TIME_PERIODIC,&err);//—” ±200ms
	}
}

