#ifndef __SERVO_H
#define __SERVO_H

#include "sys.h"
void Servo_Init(void);   //初始化
void PWM_SetCompare_x(uint16_t Compare_x);//设置x轴pwm
void PWM_SetCompare_y(uint16_t Compare_y);//设置y轴pwm
void Servo_SetAngle_x(float Angle);//设置x轴偏移角度
void Servo_SetAngle_y(float Angle);//设置y轴偏移角度
void Servo_SetBias_x(float Bias);//设置x轴偏移量
void Servo_SetBias_y(float Bias);//设置y轴偏移量

void Servo_Reset(void);//复位
#endif
