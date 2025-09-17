# CODE_ADVANCE_WRITER
C语言进阶写法
==
这段时间学习了LINUX内核，里面的代码写法对于我来说收获颇丰。

因此我自己写了一份教程，来给以后的自己及师弟师妹们查阅。

代码最终效果:
        1.实现点亮LED
        2.实现流水灯

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

接下来在ZHIZHEN.H里定义一个led_operations类型
```
struct led_operations {
	void (*init) (int which); /* 初始化LED, which-哪个LED */       
	void (*ctl) (int which, char status); /* 控制LED, which-哪个LED, status:1-亮,0-灭 */
};
```
然后来到ZHIZHEN.C里进行定义一个led_operations类型，名为 board_demo_led_opr结构体

这个结构体内是有函数的，所以我们要先定义结构体内部函数
```
void board_demo_led_init (int which) //参数要和.h里规定的一样，具体需要返回什么参数/输入什么参数，就在.h文件里改
{
   //执行gpio的初始化,当然HAL库并不需要就放着不动
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
```




