#ifndef __CONTROL_H
#define __CONTROL_H
#include "sys.h"


int TargetL,TargetR;
void Control_Init(void);
void Car_Model(uint8_t velocity,uint8_t turn);//小车运动的数学模型
void All_Stop(void);//小车遇到控制错误时停止
#endif