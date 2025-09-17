#ifndef __LIUSHUIDENG_H
#define __LIUSHUIDENG_H
#include <stdint.h>

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
