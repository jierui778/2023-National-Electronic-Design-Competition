#include "stm32f10x.h" // Device header
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "OLED.h"
#include "servo.h"
#include "pid.h"
#include "timer.h"
#include "control.h"
float x, y = 0.0;
float Target_x = 120.0;
float Target_y = 120.0;
float set_x, set_y;
float get_x, get_y;
float servo_x = 1500.0; // 舵机目标值，
float servo_y = 1500.0;
uint16_t i;
uint8_t Origin_FindFlag=0;
uint8_t Targetx1 = 0, Targety1 = 0, Currentx1 = 0, Currenty1 = 0;
uint8_t Targetx2 = 0, Targety2 = 0, Currentx2 = 0, Currenty2 = 0;
uint8_t Stop_Flag = 0;

int main(void)
{
    // 	  Serial_Init();                       //串口3初始化
    Control_Init(); // 舵机初始化

    while (1)
    {

        // Find_Origin(Targetx1, Targety1, Currentx1, Currenty1);
        // if(Origin_FindFlag)//如果找到原点
        // {
        //     TrackLine(Targetx2, Targety2, Currentx2, Currenty2);//开启跟踪
        // }





        
    }
}
