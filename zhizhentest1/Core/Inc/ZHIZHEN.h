//#ifndef __ZHIZHEN_H
//#define __ZHIZHEN_H
////宏定义作用，避免因为重复在.c文件引用#include "ZHIZHEN.h"而导致的重复定义
////宏定义解释，当代码运行到这个.h文件，发现还没有定义__ZHIZHEN_H，那么进入下面的代码，进行定义
////并且声明以下的代码。
////而第二次进到这个.h文件发现该宏定义已经声明，那么就直接从最下面的#endif运行走了，也就可以避免重复定义
////定义一个led结构体函数 ，也就是led_operations类型的结构体，有以下两个子函数
//struct led_operations {
//	void (*init) (int which); /* 初始化LED, which-哪个LED */       
//	void (*ctl) (int which, char status); /* 控制LED, which-哪个LED, status:1-亮,0-灭 */
//};

//													        
////led宏定义 							        
//typedef enum                      
//{   	led1                     = 0,
//		led2                      = 1, 
//		led3					 =2,
//}led;
////led状态宏定义 							        
//typedef enum                      
//{   	ON                     	 = 1,
//		OFF                      = 0,                                                                        
//}led_stuas;

//extern struct led_operations board_demo_led_opr;
// void led_counter(struct led_operations *opr);


//#endif
