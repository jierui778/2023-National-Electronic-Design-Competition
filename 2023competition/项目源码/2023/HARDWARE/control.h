#ifndef __CONTROL_H
#define __CONTROL_H

#include "sys.h"


void Control_Init(void);   //初始化

void TrackLine(int Targetx, int Targety, int Currentx, int Currenty); // 舵机跟踪线路
void FindOrigin(int Targetx, int Targety, int Currentx, int Currenty); //舵机找原点
#endif