#include "ultrasound.h"

void Ultrasound_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;    
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//����GPIOBʱ��
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //����TIM2ʱ��

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;    //��Ӧtrig����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_ResetBits(GPIOB,GPIO_Pin_1);    

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;    //��Ӧecho����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //�������
  GPIO_Init(GPIOB, &GPIO_InitStructure);    

//��ʱ����ʼ��,��Ƶϵ��Ϊ71,��Ƶ��Ϊ1MHZ,ÿ������1us,(Ƶ��Խ��Խ��ȷ)
//��װ��ֵΪ65535,���ʱ��Ϊ1us*65536=    65.536ms=0.065536s
//һ�����ڿ��Բ�� 0.065536s * 340m/s / 2 = 11.14112m
  TIM_TimeBaseStructure.TIM_Period = 65535; 
  TIM_TimeBaseStructure.TIM_Prescaler = 71; 
  TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
  TIM_TimeBaseStructure.TIM_CounterMode = 
  TIM_CounterMode_Up; 
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //    
}

void Ultrasound_Start(void)
{
  GPIO_SetBits(GPIOB, GPIO_Pin_1); //??PB1??
  delay_us(20);            //??20us
  GPIO_ResetBits(GPIOB, GPIO_Pin_1); //??PB1??
}

float Ultrasound_Measure(void) //
{
  while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)==1);//echo?????,???????,??????
  Ultrasound_Start(); //?????    
  while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10) == 0);//?? echo??????    
  TIM_SetCounter(TIM2,0); //?????
  TIM_Cmd(TIM2, ENABLE); //?????2,????
  while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10) == 1);//?? echo??????
  TIM_Cmd(TIM2, DISABLE);    //?????2,????    
  return (TIM_GetCounter(TIM2))/1000000*340/2 *100;    //???????cm
}
