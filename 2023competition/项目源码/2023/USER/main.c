/*
 * @Author: Azlic 2311032232@qq.com
 * @Date: 2023-08-02 08:09:36
 * @LastEditors: Azlic 2311032232@qq.com
 * @LastEditTime: 2023-08-03 18:57:35
 * @FilePath: \competition\2023competition\项目源码\2023\USER\main.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

#include "stm32f10x.h" // Device header
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "OLED.h"
#include "servo.h"
#include "pid.h"
<<<<<<< HEAD
float x,y = 0.0;
float Target_x=120.0;
float Target_y=120.0;
float set_x,set_y;
float get_x,get_y;
float servo_x = 1500.0;													//舵机目标值，
=======
#include "timer.h"
#include "control.h"
float x, y = 0.0;
float Target_x = 80;
float Target_y = 60;
uint16_t set_x, set_y,get_Rlight_x,get_Rlight_y;
uint16_t get_x, get_y;
float servo_x = 1500.0; // 舵机目标值，
>>>>>>> 5ccf993e13b6129b4dd19ca7270155aefc35e861
float servo_y = 1500.0;
uint16_t i;
uint8_t Origin_FindFlag=0;
uint8_t Targetx1 = 0, Targety1 = 0, Currentx1 = 0, Currenty1 = 0;
uint8_t Targetx2 = 0, Targety2 = 0, Currentx2 = 0, Currenty2 = 0;
uint8_t Stop_Flag = 0;

float theta;
int main(void)
{
    delay_init();    // 延时函数初始化
    uart_init(9600); // 串口初始化为9600
    OLED_Init();     // OLED初始化
    // 	  Serial_Init();                                     //串口3初始化
    TIM1_PWM_Init(20000 - 1, 72 - 1);
//	  Servo_SetAngle_y(60);
//	  Servo_SetAngle_x(60);
//    OLED_ShowNum(1,1,1,5,16,1);
    while (1)
    {

        // Find_Origin(Targetx1, Targety1, Currentx1, Currenty1);
        // if(Origin_FindFlag)//如果找到原点
        // {
        //     TrackLine(Targetx2, Targety2, Currentx2, Currenty2);//开启跟踪
        // }





        
>>>>>>> 5ccf993e13b6129b4dd19ca7270155aefc35e861
    }
		
}
