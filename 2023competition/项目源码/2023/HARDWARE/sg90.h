#ifndef __SG90_H
#define __SG90_H

#include "sys.h"
void SG90_Init(void);   //初始化
void TIM2_PWM_Init(uint32_t arr, uint32_t psc); //定时器2PWM初始化
void PWM_SetCompare_x(uint16_t Compare_x);
void PWM_SetCompare_y(uint16_t Compare_y);
void Servo_SetAngle_x(float Angle);
void Servo_SetAngle_y(float Angle);


#endif
