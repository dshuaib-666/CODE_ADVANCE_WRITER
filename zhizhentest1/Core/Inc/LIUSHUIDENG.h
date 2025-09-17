#ifndef __LIUSHUIDENG_H
#define __LIUSHUIDENG_H
#include <stdint.h>

 //led�궨�� 							        
typedef enum                      
{   	led1                     = 0,
		led2                      = 1, 
		led3					 =2,
}liushui_led;
//led״̬�궨�� 							        
typedef enum                      
{   	ON                     	 = 1,
		OFF                      = 0,                                                                        
}liushui_led_stuas;

//����һ��led�������²���
struct led_list {
	int  led_code;//�������ֱֵ�Ӵ���  liushui_led�����led1/led2����ʾָ������һ��led
	uint8_t staus;//���嵱ǰLED��״̬
	uint8_t polarity; //��������
	int forward_time; //�����ĳ���ʱ��
	int negative_time;//�����ĳ���ʱ��
};
  struct led_operations_two { //�����ֱ����ʵ��һ��ͻ      
	void (*ctl) (struct led_list led); /* ����LED, which-�ĸ�LED, status:1-��,0-�� */
};
 void  dispose_main(void);

#endif
