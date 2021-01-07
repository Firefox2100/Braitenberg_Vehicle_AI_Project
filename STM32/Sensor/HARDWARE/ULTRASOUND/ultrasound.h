#ifndef __ULTRASOUND_H
#define __ULTRASOUND_H

#include "sys.h"
#include "delay.h"

void Ultrasound_Init(void);
void Ultrasound_Start(void);
float Ultrasound_Measure(void);

#endif
