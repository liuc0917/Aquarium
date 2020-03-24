#include "GUI.h"
#include "tftlcd.h"
#include "touch.h"
#include "GUIDRV_Template.h"
#include "GUIDRV_FlexColor.h"

//�봥�����йض��壬����ʵ�������д
#define TOUCH_AD_TOP		160  	//���´������Ķ�����д�� Y ��ģ������ֵ��
#define TOUCH_AD_BOTTOM		3990 	//���´������ĵײ���д�� Y ��ģ������ֵ��
#define TOUCH_AD_LEFT 		160		//���´���������࣬д�� X ��ģ������ֵ��
#define TOUCH_AD_RIGHT		3990	//���´��������Ҳ࣬д�� X ��ģ������ֵ��


//��Ļ��С
#if (lcddev_dir==0)
	#define XSIZE_PHYS  320 //X��
	#define YSIZE_PHYS  480 //Y��
	#define VXSIZE_PHYS	320 
	#define VYSIZE_PHYS 480
#else
	#define XSIZE_PHYS  480 //X��
	#define YSIZE_PHYS  320 //Y��
	#define VXSIZE_PHYS	480 
	#define VYSIZE_PHYS 320
#endif

//���ü��
#ifndef   VXSIZE_PHYS
  #define VXSIZE_PHYS XSIZE_PHYS
#endif
#ifndef   VYSIZE_PHYS
  #define VYSIZE_PHYS YSIZE_PHYS
#endif
#ifndef   XSIZE_PHYS
  #error Physical X size of display is not defined!
#endif
#ifndef   YSIZE_PHYS
  #error Physical Y size of display is not defined!
#endif
#ifndef   GUICC_565
  #error Color conversion not defined!
#endif
#ifndef   GUIDRV_FLEXCOLOR
  #error No display driver defined!
#endif

//���ó���,���ڴ�����ʾ��������,������ɫת���������ʾ�ߴ�
void LCD_X_Config(void) {
	GUI_DEVICE_CreateAndLink(&GUIDRV_Template_API, GUICC_M565, 0, 0); //������ʾ��������
	LCD_SetSizeEx (0, tftlcd_data.width , tftlcd_data.height);
  	LCD_SetVSizeEx(0, tftlcd_data.width , tftlcd_data.height);	
#ifndef TFTLCD_R61509
	if(tftlcd_data.dir == 0) //����
	{					
		GUI_TOUCH_Calibrate(GUI_COORD_X,0,tftlcd_data.width,240,3600);
		GUI_TOUCH_Calibrate(GUI_COORD_Y,0,tftlcd_data.height,365,3760);
	}else //����
	{
		GUI_TOUCH_SetOrientation(GUI_SWAP_XY|GUI_MIRROR_X);   //|GUI_MIRROR_Y
		GUI_TOUCH_Calibrate(GUI_COORD_X,0,tftlcd_data.height,240,3600); 	
		GUI_TOUCH_Calibrate(GUI_COORD_Y,0,tftlcd_data.width,365,3760);
	}	
#else
	if(tftlcd_data.dir == 0) //����
	{					
		GUI_TOUCH_Calibrate(GUI_COORD_X,0,tftlcd_data.width,240,3600);
		GUI_TOUCH_Calibrate(GUI_COORD_Y,0,tftlcd_data.height,365,3760));
	}else //����
	{
		GUI_TOUCH_SetOrientation(GUI_SWAP_XY|GUI_MIRROR_X); 
		GUI_TOUCH_Calibrate(GUI_COORD_X,0,tftlcd_data.height,240,3600); 	
		GUI_TOUCH_Calibrate(GUI_COORD_Y,0,tftlcd_data.width,365,3760);
	}	
#endif
}


//��ʾ�������Ļص�����
int LCD_X_DisplayDriver(unsigned LayerIndex, unsigned Cmd, void * pData) {
  int r;
  (void) LayerIndex;
  (void) pData;
  
  switch (Cmd) {
  case LCD_X_INITCONTROLLER: {
	//����ʼ����ʱ�򱻵���,��Ҫ��������ʾ������,�����ʾ���������ⲿ��ʼ������Ҫ�û���ʼ��
		
	//	TFTLCD_Init(); //��ʼ��LCD �Ѿ��ڿ�ʼ��ʼ����,���Դ˴�����Ҫ��ʼ����
    return 0;
  }
		default:
    r = -1;
	}
  return r;
}
