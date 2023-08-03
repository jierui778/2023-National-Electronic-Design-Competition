#include "stm32f10x.h" // Device header
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "OLED.h"
#include "servo.h"
#include "pid.h"
#include "timer.h"
float x, y = 0.0;
float Target_x = 80;
float Target_y = 60;
uint16_t set_x, set_y,get_Rlight_x,get_Rlight_y;
uint16_t get_x, get_y;
float servo_x = 1500.0; // 舵机目标值，
float servo_y = 1500.0;
uint16_t i;
float theta;
int main(void)
{
    delay_init();    // 延时函数初始化
    uart_init(9600); // 串口初始化为9600
    OLED_Init();     // OLED初始化
    Serial_Init();                                     //串口3初始化
    TIM1_PWM_Init(20000 - 1, 72 - 1);
//	  Servo_SetAngle_y(60);
//	  Servo_SetAngle_x(60);
//    OLED_ShowNum(1,1,1,5,16,1);
    while (1)
    {

        Servo_SetAngle_y(10);
        Servo_SetAngle_x(10+i);
		   	i++;
		   	if (i>70){i--;}
					if (i<10){i++;}
				delay_ms(1000);
				OLED_ShowNum(0,1,Serial_RxPacket[0],3,16,1);
				OLED_ShowNum(32,1,Serial_RxPacket[1],3,16,1);
				OLED_ShowNum(0,24,Serial_RxPacket[2],3,16,1);
				OLED_ShowNum(32,24,Serial_RxPacket[3],3,16,1);
				OLED_ShowNum(0,48,Serial_RxPacket[4],3,16,1);
				OLED_ShowNum(32,48,Serial_RxPacket[5],3,16,1);	
//					get_x = Serial_RxPacket[0];
//					get_y = Serial_RxPacket[1];
//					theta = (Serial_RxPacket[2]*256+Serial_RxPacket[3])/100.0;
//				OLED_ShowNum(32,48,theta*100,5,16,1);	
				get_Rlight_x=	Serial_RxPacket[4];
				get_Rlight_y=  Serial_RxPacket[5];

				OLED_Refresh();
			
    }
		
}
