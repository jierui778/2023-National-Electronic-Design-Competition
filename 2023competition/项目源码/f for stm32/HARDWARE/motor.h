#ifndef __MOTOR_H
#define __MOTOR_H
#include "sys.h"
#define PWML   TIM1->CCR1  //PA8
#define PWMR   TIM1->CCR4  //PA11
//左电机控制正反转
#define AIN1 PBout(0)//AIN1
#define AIN2 PBout(1)//AIN2

//右电机控制正反转
#define BIN1 PBout(2)//BIN1
#define BIN2 PBout(3)//BIN2

void Motor_Init(void);//初始化电机  
void Pwm_Limit(MotorL, MotorR);//限制PWM值
void Set_Pwm(uint8_t MotorL,uint8_t MotorR);//设置左右电机的PWM值

#endif