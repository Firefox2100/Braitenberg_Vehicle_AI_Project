#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "timer.h"
#include "adc.h"
#include "encoder.h"
#include "motor.h"

//GPIO Usage:
//PA6 TIM3_CH1 for PWM output
//PA7 TIM3_CH2 for PWM output
//PB0 PB1 AB encoder input for TIM2
//PB6 PB7 AB encoder input for TIM4
//PA1 PA2 analog input

u16 PWM_left;
u16 PWM_right;

int main(void)
{
	u16 adc1, adc2;      //ADC读取到的值
	int speed_left, speed_right;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	//uart_init(9600);	 //串口初始化为9600
  delay_init();	    	 //延时函数初始化
  LED_Init();
	Adc_Init();
	Motor_Init();
  
	while(1)
  {
		adc1=Get_Adc_Average(ADC_Channel_1, 10);
		adc1=Get_Adc_Average(ADC_Channel_2, 10);
		speed_left=calc_speed(adc1);
		speed_right=calc_speed(adc2);
		move_left(speed_left);
		move_right(speed_right);
		delay_ms(150);
	}
}
