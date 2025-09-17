# CODE_ADVANCE_WRITER
C语言进阶写法
==
这段时间学习了LINUX内核，里面的代码写法对于我来说收获颇丰。

因此我自己写了一份教程，来给以后的自己及师弟师妹们查阅。

代码最终效果:
        1.实现点亮LED
        2.实现流水灯

开发环境:使用STM32G030F6P6开发板，自带灯是PB0，使用CUBEMX+KEIL

'代码框架'<br>
```
zhizhentest
  MDK-ARM
    main.c
  CORE
    Src
      ZHIZHEN.C
    Inc
      ZHIZHEN.H
```
框架就是HAL库开发的基本框架

接下来在ZHIZHEN.H里定义一个led_operations类型，并且使用一个结构体（类似宏定义）来提高代码可读性
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
//定义结构体完成
 struct led_operations board_demo_led_opr = {
    .init = board_demo_led_init,
    .ctl  = board_demo_led_ctl,
};
```
由于我们一会跨文件，在main.c文件里面实验，因此需要在.h文件进行声明
```
（其实直接在mian.c里面export struct led_operations board_demo_led_opr也可以，但是这样会导致代码冗余）
.h文件本身也是声明文件，变量等直接在这里面进行声明，后续其他.c文件要调用该变量，直接#include ".c"就好
```



