#ifndef __OLED_H
#define __OLED_H
#include "sys.h"
void OLED_Init(void);//OLED初始化
void OLED_Clear(void);//OLED清屏
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char); //显示一个字符
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String);
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);

#endif
