#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"

extern void TIM1_PWM_Init(u16 arr, u16 psc); // 定时器1初始化PWM模式
extern void TIM2_Int_Init(u16 arr, u16 psc);
extern void Encoder_TIM3_Init(void); // 定时器3初始化编码器模式
extern void Encoder_TIM4_Init(void); // 定时器4初始化编码器模式
extern void TIM3_IRQHandler(void);   // 定时器3中断服务函数
extern void TIM4_IRQHandler(void);   // 定时器4中断服务函数

#endif
