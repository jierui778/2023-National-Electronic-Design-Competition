#ifndef __ENCODER_H
#define __ENCODER_H
#include "sys.h"

// extern void Encoder_TIM3_Init(void);
// extern void Encoder_TIM4_Init(void);
extern void Encoder_Init(void);//编码器初始化
extern int Read_Encoder(u8 TIMX);//读取编码器速度

#endif

