#include "motor.h"
#include "timer.h"
void Motor_Init()
{
    TIM1_PWM_Init(MOTOR_RELOAD_VALUE, 0); // 10Khz的PWM频率

    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);                                // 使能GPIOB时钟
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15; // 端口配置
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;                                     // 推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure); // 根据设定参数初始化GPIOB
    
    
    
       
    
}
void SetPwm_MotorL(int pwml)
{
    if (pwml > 0)
    {
        Ain1 = 1;
        Ain2 = 0;
        TIM_SetCompare1(TIM1, 7199-pwml);
    }
    else
    {
        Ain1 = 0;
        Ain2 = 1;
        TIM_SetCompare1(TIM1, 7199+pwml);
    }
}
void SetPwm_MotorR(int pwm)
{
    if (pwm > 0)
    {
        Bin1 = 1;
        Bin2 = 0;
        TIM_SetCompare4(TIM1, pwm);
    }
    else
    {
        Bin1 = 0;
        Bin2 = 1;
        TIM_SetCompare4(TIM1, -pwm);
    }
}
