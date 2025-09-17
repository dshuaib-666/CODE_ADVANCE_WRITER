//#include "chenshuze.h"
//#include	 "gpio.h"
//void board_demo_led_init (int which) //参数要和.h里规定的一样，具体需要返回什么参数/输入什么参数，就在.h文件里改
//{
//   //执行gpio的初始化,当然HAL库并不需要就放着不动
//}
// void board_demo_led_ctl (int which, char status)
//{
//   if(which == led1) //如果输入参数为led1
//   {
//		if(status==ON)
//		{     //这个开发板低电平点量
//			 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
//		}
//		else if(status==OFF)
//		{
//			 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
//		}
//   
//   }
//   
//}

// struct led_operations board_demo_led_opr = {
//    .init = board_demo_led_init,
//    .ctl  = board_demo_led_ctl,
//};
// //接下来演示函数内部调用传入的结构体
////创建一个led控制，这个与直接在main里调用的写法是不一样的
// void led_counter(struct led_operations *opr)
// {
//	   opr-> ctl(led1,ON);
//	   HAL_Delay(1000);
//	   opr-> ctl(led1,OFF);
//	   HAL_Delay(1000);
// }



