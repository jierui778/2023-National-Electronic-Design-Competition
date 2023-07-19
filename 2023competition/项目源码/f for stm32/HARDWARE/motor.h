#ifndef __MOTOR_H
#define __MOTOR_H
#include "sys.h"

void Motor_Init(void);//初始化电机  
void Set_Pwm_All(uint8_t pwm);//设置左右电机的PWM值
void Set_Pwm_MotorL(uint8_t pwm);//设置左电机的PWM值
void Set_Pwm_MotorR(uint8_t pwm);//设置右电机的PWM值

#endif