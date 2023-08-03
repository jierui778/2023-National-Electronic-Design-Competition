
#include "stm32f10x.h" // Device header
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "OLED.h"
#include "servo.h"
#include "pid.h"
float x,y = 0.0;
float Target_x=120.0;
float Target_y=120.0;
float set_x,set_y;
float get_x,get_y;
float servo_x = 1500.0;													//舵机目标值，
float servo_y = 1500.0;
uint16_t i;

int main(void)
{
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	  TIM2_PWM_Init(20000-1,72-1);
    delay_init();                                   // 延时函数初始化
//    uart_init(9600);                                // 串口初始化为9600
    OLED_Init();                                    // OLED初始化
	  Serial_Init();                                     //串口3初始化
		
	  TIM_SetCompare2(TIM2,servo_x);				
	  TIM_SetCompare3(TIM2,servo_y);	

    while (1)
    {
//					OLED_ShowSignedNum(1, 0, Serial_RxPacket[1], 5, 16, 1);
//					OLED_ShowSignedNum(1, 24, Serial_RxPacket[2], 5, 16, 1);
//					OLED_ShowSignedNum(1, 48, Serial_RxPacket[3], 5, 16, 1);
//					OLED_ShowSignedNum(64, 0, Serial_RxPacket[4], 5, 16, 1);
//					OLED_ShowSignedNum(64, 24, Serial_RxPacket[5], 5, 16, 1);
//					OLED_ShowSignedNum(64, 48, Serial_RxPacket[6], 5, 16, 1);
			
    }
		
}
