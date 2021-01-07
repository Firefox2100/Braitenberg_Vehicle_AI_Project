#include "motor.h"

void Motor_Init(void)
{
	Encoder_Init_TIM2();
	Encoder_Init_TIM4();
	TIM1_Int_Init(99,7199);//10Hz
	TIM3_Int_Init(899, 0);//80KHz
}

void move_left(int speed)
{
	if(speed>(Encoder_Left+range))
	{
		PWM_left=PWM_left-step;
	}
	else if(speed<(Encoder_Left-range))
	{
		PWM_left=PWM_left+step;
	}
}

void move_right(int speed)
{
	if(speed>(Encoder_Right+range))
	{
		PWM_right=PWM_right-step;
	}
	else if(speed<(Encoder_Right-range))
	{
		PWM_right=PWM_right+step;
	}
}

int calc_speed(u16 adc)
{
	int speed = MAX - adc / RATIO;
	return speed;
}
