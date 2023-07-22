#ifndef __MOTOR_H
#define __MOTOR_H
#include "sys.h"
#define PWML   TIM1->CCR1  //PA8
#define PWMR   TIM1->CCR4  //

#define MOTOR_RELOAD_VALUE 7199//定义电机最大速度占空比
#define PWM_MAX 7199
#define PWM_MIN -7199

//左电机控制正反转
#define Ain1 PBout(13)//AIN1
#define Ain2 PBout(12)//AIN2

//右电机控制正反转
#define Bin1 PBout(14)//BIN1
#define Bin2 PBout(15)//BIN2

void Motor_Init(void);          // 初始化电机  
void SetPwm_MotorL(int pwm);    // 设置左电机PWM
void SetPwm_MotorR(int pwm);    // 设置右电机PWM

#endif
