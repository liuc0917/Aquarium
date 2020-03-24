#include "OS.h"
#include "GUI.h"
#include "GUIDemo.h"

#include "DrawComp.h"
#include "DrawComp_api.h"
#include "ds18b20.h"
#include "tftlcd.h"
#include "usart.h"

//drawcomp任务
void drawcomp_task(void *p_arg)
{
	OS_ERR err;
	float temp;
	u16 tem_dat;
	u8 dat[8];
	CPU_SR_ALLOC();
	
	DS18B20_Init();
	//LCD_Clear(BLACK);
			
	while(1)
	{
		OS_CRITICAL_ENTER();
		temp=DS18B20_GetTemperture();
		OS_CRITICAL_EXIT();
		tem_dat=temp*100;
		dat[0]=tem_dat/1000+0x30;
		dat[1]=tem_dat%1000/100+0x30;
		dat[2]='.';
		dat[3]=tem_dat%1000%100/10+0x30;
		dat[4]=tem_dat%1000%100%10+0x30;
		dat[5]='C';
		dat[6]='\0';
		printf("Temperturn = %f \r\n", temp);
		LCD_ShowString(120,50,320,30,12,dat);       
		OSTimeDlyHMSM(0,0,0,100,OS_OPT_TIME_PERIODIC,&err);//延时1s
	}
}

//TOUCH任务
void touch_task(void *p_arg)
{
	OS_ERR err;
	while(1)
	{
		GUI_TOUCH_Exec();	
		OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_PERIODIC,&err);//延时5ms
	}
}

