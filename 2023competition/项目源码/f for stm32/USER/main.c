<<<<<<< HEAD
#include "stm32f10x.h"
#include "sys.h"
#include "timer.h"
#include "usart.h"
#include "encoder.h"
#include "oled.h"

int main(void)
{

    // Encoder_Init();
    // uart_init(9600);
    // int value;
    OLED_Init();//OLEDåˆå§‹åŒ–
    OLED_ColorTurn(0);
    while(1)
    {

        OLED_DrawPoint(120,6,1);
        OLED_Refresh();
        // value = (short)Read_Encoder(4);
        // printf("%d\n",value);
        // printf()
//        OLED_ColorTurn(1);
//        OLED_ShowString(1,1,"666");
    }
    
=======
#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "OLED.h"
#include "MPU6050.h"

uint8_t ID;
int16_t AX, AY, AZ, GX, GY, GZ;

int main(void)
{
	OLED_Init();
	MPU6050_Init();
	
	OLED_ShowString(1, 1, "ID:");
	ID = MPU6050_GetID();
	OLED_ShowHexNum(1, 4, ID, 2);
	
	while (1)
	{
		MPU6050_GetData(&AX, &AY, &AZ, &GX, &GY, &GZ);//·µ»Ø6Öá´«¸ÐÆ÷µÄÖµ
		OLED_ShowSignedNum(2, 1, AX, 5);
		OLED_ShowSignedNum(3, 1, AY, 5);
		OLED_ShowSignedNum(4, 1, AZ, 5);
		OLED_ShowSignedNum(2, 8, GX, 5);
		OLED_ShowSignedNum(3, 8, GY, 5);
		OLED_ShowSignedNum(4, 8, GZ, 5);
	}
>>>>>>> d97c8e45af3a089e71086adf8ce217e14cbf8ade
}
