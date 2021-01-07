#ifndef __MOTOR_H
#define __MOTOR_H
#include "timer.h"
#include "encoder.h"

#define range 50
#define step 100
#define RATIO 1
#define MAX 5000


void Motor_Init(void);
void move_left(int speed);
void move_right(int speed);
int calc_speed(u16 adc);

#endif
