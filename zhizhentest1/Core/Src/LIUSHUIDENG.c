 #include "chenshuze.h"
//����������һ���ṹ�壬
//Ŀ����һ����ˮ������������LED��ʹ������������
struct liushuideng{
	
	struct led_list led[2];// ��ǰ������LED����ô��ѡ��2
} ;//�����Ľṹ��
 struct liushuideng LIUSHUI;    //����һ��liushuideng���͵�����ΪLIUSHUI�Ľṹ��
 //���Ƶ���led��
 void LIUSHUIDENG_ctl_dange (struct led_list led)
{
   if(led.led_code == led2) //����������Ϊled2
   {
		if(led.staus==ON) //�������ж�stuas��ON/OFF
		{     //���������͵�ƽ����
			 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
		}
		else if(led.staus==OFF)
		{
			 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
		}
   
   }
   if(led.led_code == led3) //����������Ϊled3
   {
		if(led.staus==ON) //�������ж�stuas��ON/OFF
		{     //���������͵�ƽ����
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
  //��������
void countel_BOTH(struct liushuideng liushui)
{

   LIUSHUIDENG_ctl_dange(liushui.led[0]);
	LIUSHUIDENG_ctl_dange(liushui.led[1]);
}
 void  dispose_main(void)
 {
   LIUSHUI.led[0].staus=OFF;// LIUSHUI�����ʱ�� struct liushuideng *LIUSHUI;����Ϊָ��������ģ�����ʹ��->  
   LIUSHUI.led[0].led_code=led2;
   LIUSHUI.led[1].led_code=led3;
   LIUSHUI.led[1].staus=OFF;
	countel_BOTH(LIUSHUI);
	 HAL_Delay(1000);
	 LIUSHUI.led[0].staus=ON;// LIUSHUI�����ʱ�� struct liushuideng *LIUSHUI;����Ϊָ��������ģ�����ʹ��->  
   LIUSHUI.led[0].led_code=led2;
   LIUSHUI.led[1].led_code=led3;
   LIUSHUI.led[1].staus=ON;
	countel_BOTH(LIUSHUI);
	  HAL_Delay(1000);
 
 }
