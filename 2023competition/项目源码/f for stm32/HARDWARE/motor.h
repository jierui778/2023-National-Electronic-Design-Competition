#ifndef __MOTOR_H
#define __MOTOR_H
#include "sys.h"
#define PWML   TIM1->CCR1  //PA8
#define PWMR   TIM1->CCR4  //

#define MOTOR_RELOAD_VALUE 7199//定义电机最大速度占空比
#define PWM_MAX 7200
#define PWM_MIN -7200

//左电机控制正反转
#define Ain1 PBout(12)//AIN1
#define Ain2 PBout(13)//AIN2

//右电机控制正反转
#define Bin1 PBout(14)//BIN1
#define Bin2 PBout(15)//BIN2

void Motor_Init(void);          // 初始化电机  
//void Pwm_Limit(MotorL, MotorR);//限制PWM值
void Set_Pwm(uint8_t MotorL,uint8_t MotorR);//设置左右电机的PWM值

#endif
