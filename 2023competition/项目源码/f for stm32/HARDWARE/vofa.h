#ifndef __VOFA_H
#define __VOFA_H
#include "sys.h"
#include "usart.h"
#include "delay.h"  
//vofa下位机代码

void Vofa_Serial_init(u32 bound);
void FireWater_Send(uint8_t *chr,float a,float b,float c,float d);
void JustFloat_Send();
void RawData_Send();


#endif