# CODE_ADVANCE_WRITER
C语言进阶写法
==
这段时间在学习LINUX内核，里面的代码写法对于我来说收获颇丰。

因此我自己写了一份教程，来给以后的自己及师弟师妹们查阅。

代码最终效果:
        1.实现点亮LED
        2.实现流水灯

开发环境:使用STM32G030F6P6开发板，自带灯是PB0，流水灯使用的是PB7/PB9,使用CUBEMX+KEIL

主要演示结构体写法，指针写法在源码里，我使用define定义自行查阅

'代码框架'<br>
```
zhizhentest
  MDK-ARM
    main.c
  CORE
    Src
      ZHIZHEN.C
    Inc
      chenshuze.h//用于对底层的.h文件进行声明，方便管理，这样只需要在main.c里面include "chenshuze.h"就行
      ZHIZHEN.H
```
框架就是HAL库开发的基本框架

接下来在ZHIZHEN.H里定义一个led_operations类型，并且使用一个枚举常量（类似宏定义）来提高代码可读性
```
--ZHIZHEN.H中
#ifndef __ZHIZHEN_H
#define __ZHIZHEN_H
struct led_operations {
	void (*init) (int which); /* 初始化LED, which-哪个LED */       
	void (*ctl) (int which, char status); /* 控制LED, which-哪个LED, status:1-亮,0-灭 */
};
//led枚举常量 							        
typedef enum     //选择是哪个led                 
{   	led1                     = 0,
		led2                      = 1,                                                                        
}led;
//led状态枚举常量(类似宏定义) 							        
typedef enum                      
{   	ON                     	 = 1,
		OFF                      = 0,                                                                        
}led_stuas;
#endif
```
然后来到ZHIZHEN.C里进行定义一个led_operations类型，名为 board_demo_led_opr结构体

这个结构体内是有函数的，所以我们要先定义结构体内部函数
```
--ZHIZHEN.C中
#include "ZHIZHEN.h"
#include	 "gpio.h"//HAL库中引用HAL_GPIO_WritePin()函数需要
void board_demo_led_init (int which) //参数要和.h里规定的一样，具体需要返回什么参数/输入什么参数，就在.h文件里改
{
   //执行gpio的初始化,当然HAL库并不需要，标准库的GPIO初始化可以放在这里
}
 void board_demo_led_ctl (int which, char status)
{
   if(which == led1) //如果输入参数为led1
   {
		if(status==ON)
		{     //这个开发板低电平点量
			 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
		}
		else if(status==OFF)
		{
			 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
		}
   }
}
//定义结构体写法
 struct led_operations board_demo_led_opr = {
    .init = board_demo_led_init,
    .ctl  = board_demo_led_ctl,
};
//指针写法
 struct led_operations *board_demo_led_opr = {
    .init = board_demo_led_init,
    .ctl  = board_demo_led_ctl,
};
```
由于我们一会跨文件，在main.c文件里面实验，因此需要在.h文件进行声明
```
（其实直接在mian.c里面export struct led_operations board_demo_led_opr也可以，但是这样会导致代码冗余）
.h文件本身也是声明文件，变量等直接在这里面进行声明，后续其他.c文件要调用该变量，直接#include ".h"就好
```
回到ZHIZHEN.H
```
--ZHIZHEN.H中
#ifndef __ZHIZHEN_H
#define __ZHIZHEN_H
struct led_operations {
	void (*init) (int which); /* 初始化LED, which-哪个LED */       
	void (*ctl) (int which, char status); /* 控制LED, which-哪个LED, status:1-亮,0-灭 */
};
//led宏定义 							        
typedef enum     //选择是哪个led                 
{   	led1                     = 0,
		led2                      = 1,                                                                        
}led;
//led状态宏定义 							        
typedef enum                      
{   	ON                     	 = 1,
		OFF                      = 0,                                                                        
}led_stuas;
extern struct led_operations board_demo_led_opr;//添加
#endif
```
为了在后续及以后的开发中，不同的.c文件调用相同的.h文件不需要重复复制粘贴一堆#include，选择在chenshuze.h中将需要的#include进行集中，最后不同的.c文件只需要#include "chenshuze.h"就可以调用不同的.h文件内声明的函数/变量
```
--chenshuze.h中
#ifndef __CHENSHUZE_H
#define __CHENSHUZE_H
#include "ZHIZHEN.h"
...根据需要添加其他的.h
#endif
```
然后来到main.c文件，在最上面的#include区进行include chenshuze.h
```
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "chenshuze.h"//这个
/* USER CODE END Includes */
```
然后来到mian入口
```
这两份代码效果一样的，都实现了PB0的电平翻转
while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  HAL_Delay(1000);
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);//就是直接调用
	  HAL_Delay(1000);
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
  }
//结构体写法
while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  HAL_Delay(1000);
	  board_demo_led_opr.ctl(led1,ON);//输入哪个led，然后内部再进行判断，区别就是封装好了
      //如果前面定义的是指针，那么就使用board_demo_led_opr->ctl(led1,ON);
	  HAL_Delay(1000);		
	  board_demo_led_opr.ctl(led1,OFF);
  }
//指针写法
while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  HAL_Delay(1000);
	  board_demo_led_opr->ctl(led1,ON);//输入哪个led，然后内部再进行判断，区别就是封装好了
      //如果前面定义的是指针，那么就使用board_demo_led_opr->ctl(led1,ON);
	  HAL_Delay(1000);		
	  board_demo_led_opr->ctl(led1,OFF);
  }
```
 board_demo_led_opr.ctl(led1,ON);是在外部的结构体使用教程
 
 接下来演示函数入口传入的结构体使用方法

定义一个led_counter(struct led_operations opr)，需要的参数是led_operations类型的
//创建一个led控制，这个与直接在main里调用的写法是不一样的
```
//结构体写法
 void led_counter(struct led_operations opr)
 {
	   opr.ctl(led1,ON);//后续调用这个函数，传入的是board_demo_led_opr结构体，因此这一条约等于board_demo_led_opr.ctl(led1,ON);
	   HAL_Delay(1000);
	   opr.ctl(led1,OFF);
	   HAL_Delay(1000);
 }
//指针写法
 void led_counter(struct led_operations *opr)
 {
	   opr->ctl(led1,ON);//后续调用这个函数，传入的是board_demo_led_opr结构体，因此这一条约等于board_demo_led_opr->ctl(led1,ON);
	   HAL_Delay(1000);
	   opr->ctl(led1,OFF);
	   HAL_Delay(1000);
 }
```
接下来在ZHIZHEN.h进行声明 void led_counter(struct led_operations *opr);/void led_counter(struct led_operations opr);，（基础操作不演示）
然后在main的函数入口while直接调用led_counter(&board_demo_led_opr);
```
  while (1)
  {
    /* USER CODE END WHILE */
    /* USER CODE BEGIN 3 */
      //结构体写法
	  led_counter(board_demo_led_opr);
      //指针写法
	  led_counter(&board_demo_led_opr);
  }
```

上面这份代码项目名为zhizhentest

实验二是流水灯
跟实验1的区别就是，我将流水灯这个大主体，添加了一个struct led_list led[2];结构体，表示流水灯有两个led，

新建一个LIUSHUIDENG.c/LIUSHUIDENG.h

先在LIUSHUIDENG.h里面定义led_list每一个led的参数
```
--LIUSHUIDENG_H中
#ifndef __LIUSHUIDENG_H
#define __LIUSHUIDENG_H
#include <stdint.h>//否则uint8_t报错
 //led宏定义 							        
typedef enum                      
{   	led1                     = 0,
		led2                      = 1, 
		led3					 =2,
}liushui_led;
//led状态宏定义 							        
typedef enum                      
{   	ON                     	 = 1,
		OFF                      = 0,                                                                        
}liushui_led_stuas;
//定义一个led，有以下参数
struct led_list {
	int  led_code;//后续这个值直接传入  liushui_led里面的led1/led2来表示指的是哪一个led
	uint8_t staus;//定义当前LED的状态
	uint8_t polarity; //正负极性
	int forward_time; //正极的持续时间
	int negative_time;//负极的持续时间
};
  struct led_operations_two { //改名字避免跟实验一冲突      
	void (*ctl) (struct led_list led); /* 控制LED, which-哪个LED, status:1-亮,0-灭 */
};
 void  dispose_main(void);
#endif
```
接下来回到LIUSHUIDENG.c

```
--LIUSHUIDENG.c中
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
 void  dispose_main(void)//然后把这个直接丢进main函数里跑就行了
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
```
进阶写法演示完毕，在下面再贴上之前我仅仅会用的结构体参数写法。

源自工创赛HWT101陀螺仪的读取数据部分
```
--MYUSART.h中
 typedef struct HWT101_USART
{
		uint8_t Rx_flag;											
		uint8_t Rx_len;												
		uint8_t frame_head;					
		uint8_t RxBuffer[HWT101_RXBUFFER_LEN];		
		float angle;						
	
		float w_Before_calibration;	
	    float w_After_calibration;	
		float ball_angle; 
		float turn_start_yaw;
}HWT101_USART;
```
来到HWT101.C
```
HWT101_USART HWT101;

void HWT101_data_reduction(void)
{
		...省略
			float angle = ((float)yaw / 32768.0f) * 180.0f;
            HWT101.angle = angle;//使用
		...
}

```


