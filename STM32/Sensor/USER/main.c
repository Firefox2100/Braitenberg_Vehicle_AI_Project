#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "light.h"
#include "ultrasound.h"
#include "timer.h"

#define ILL 0.25
#define DIS 0.01
#define RATIO 1

//GPIO Usage:
//PB1 trigger for ultrasound
//PB5 PWM output
//PB10 echo for ultrasound
//PB6 PB7 IIC bus IO

void output(u16 illuminance, float distance);

int main(void)
{
	u16 illuminance;
	float distance;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	//uart_init(9600);	 //���ڳ�ʼ��Ϊ9600
  delay_init();	    	 //��ʱ������ʼ��
  LED_Init();
	TIM3_PWM_Init(899,0);
	Light_Init();
	Ultrasound_Init();
	bh_data_send(BHPowOn);
	bh_data_send(BHReset);
	bh_data_send(BHModeL); //�ֱ���4lx������ʱ��16ms
  delay_ms(180);
	while(1)
  {
		illuminance=bh_data_read();
		distance=Ultrasound_Measure();
		output(illuminance,distance);
		delay_ms(100);
	}
}

void output(u16 illuminance, float distance)
{
	u16 pwmval;
	pwmval = (illuminance*ILL+distance*DIS)*RATIO;
	
	TIM_SetCompare2(TIM3,pwmval);
}
