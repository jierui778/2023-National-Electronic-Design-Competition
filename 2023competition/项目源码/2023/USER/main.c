#include "stm32f10x.h" // Device header
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "OLED.h"
#include "servo.h"
#include "pid.h"
#include "timer.h"
float x, y = 0.0;
float Target_x = 120.0;
float Target_y = 120.0;
float set_x, set_y;
float get_x, get_y;
float servo_x = 1500.0; // 舵机目标值，
float servo_y = 1500.0;
uint16_t i;

int main(void)
{
    delay_init();    // 延时函数初始化
    uart_init(9600); // 串口初始化为9600
    OLED_Init();     // OLED初始化
    // 	  Serial_Init();                                     //串口3初始化
    TIM1_PWM_Init(20000 - 1, 72 - 1);
    while (1)
    {

        Servo_SetAngle_y(0);
        Servo_SetAngle_x(5);
    }
}
