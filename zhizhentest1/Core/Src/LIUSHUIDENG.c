 #include "chenshuze.h"
//接下来定义一个结构体，
//目的是一个流水灯里面有两组LED，使用数组来管理
struct liushuideng{
	
	struct led_list led[2];// 当前有两个LED，那么就选择2
} ;//按键的结构体
 struct liushuideng LIUSHUI;    //定义一个liushuideng类型的名称为LIUSHUI的结构体
 //控制单个led灯
 void LIUSHUIDENG_ctl_dange (struct led_list led)
{
   if(led.led_code == led2) //如果输入参数为led2
   {
		if(led.staus==ON) //进来后判断stuas是ON/OFF
		{     //这个开发板低电平点量
			 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
		}
		else if(led.staus==OFF)
		{
			 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
		}
   
   }
   if(led.led_code == led3) //如果输入参数为led3
   {
		if(led.staus==ON) //进来后判断stuas是ON/OFF
		{     //这个开发板低电平点量
			 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
		}
		else if(led.staus==OFF)
		{
			 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);
		}
   
   }
   
} 
  struct led_operations_two LIUSHUIDENG = {
    .ctl  = LIUSHUIDENG_ctl_dange,
};
  //控制两个
void countel_BOTH(struct liushuideng liushui)
{

   LIUSHUIDENG_ctl_dange(liushui.led[0]);
	LIUSHUIDENG_ctl_dange(liushui.led[1]);
}
 void  dispose_main(void)
 {
   LIUSHUI.led[0].staus=OFF;// LIUSHUI定义的时候 struct liushuideng *LIUSHUI;是作为指针来定义的，所以使用->  
   LIUSHUI.led[0].led_code=led2;
   LIUSHUI.led[1].led_code=led3;
   LIUSHUI.led[1].staus=OFF;
	countel_BOTH(LIUSHUI);
	 HAL_Delay(1000);
	 LIUSHUI.led[0].staus=ON;// LIUSHUI定义的时候 struct liushuideng *LIUSHUI;是作为指针来定义的，所以使用->  
   LIUSHUI.led[0].led_code=led2;
   LIUSHUI.led[1].led_code=led3;
   LIUSHUI.led[1].staus=ON;
	countel_BOTH(LIUSHUI);
	  HAL_Delay(1000);
 
 }
