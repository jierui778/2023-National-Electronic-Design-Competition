#ifndef __SG90_H
#define __SG90_H

#include "sys.h"
void SG90_Init(void);   //初始化
void PWM_SetCompare_x(uint16_t Compare_x);
void PWM_SetCompare_y(uint16_t Compare_y);
void Servo_SetAngle_x(float Angle);
void Servo_SetAngle_y(float Angle);


#endif
