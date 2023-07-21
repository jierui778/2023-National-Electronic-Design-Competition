#ifndef __CONTROL_H
#define __CONTROL_H
#include "sys.h"


//int TargetL,TargetR;
void Control_Init(void);//初始化控制
int ChangeSpeedMotorL(int NowEncoderValueL, int TargetSpeedL);
int ChangeSpeedMotorR(int NowEncoderValueR, int TargetSpeedR);
void Car_Model(uint8_t velocity, uint8_t turn); // 小车运动的数学模型
void All_Stop(void);//小车遇到控制错误时停止
#endif
