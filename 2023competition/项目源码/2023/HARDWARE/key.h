#ifndef __KEY_H
#define __KEY_H
#include "sys.h"


#define KEY0 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)//读取按键0
#define WK_UP GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//PA0  WK_UP






void KEY_Init(void);//IO初始化
u8 KEY_Scan(u8);  	//按键扫描函数
#endif