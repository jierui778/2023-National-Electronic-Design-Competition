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
/*函数功能：限制PWM赋值
入口参数：无
返回  值：无*/
//void Pwm_Limit(MotorL, MotorR)
//{
//    if (MotorL > 4000)
//        MotorL = 4000;
//    if (MotorL < -4000)
//        MotorL = -4000;
//    if (MotorR > 4000)
//        MotorR = 4000;
//    if (MotorR < -4000)
//        MotorR = -4000;
//}

/*函数功能：赋值给PWM寄存器
入口参数：左轮PWM、右轮PWM
返回 值：无 */
void Set_Pwm(uint8_t MotorL, uint8_t MotorR)
{
    if (MotorL > 0)
    {
        Ain1 = 1;
        Ain2 = 0;
        PWML = MotorL;
    }
    else
    {
        Ain1 = 0;
        Ain2 = 1;
        PWML = -MotorL;
    }
    if (MotorR > 0)
    {
        Bin1 = 1;
        Bin2 = 0;
        PWMR = MotorR;
    }
    else
    {
        Bin1 = 0;
        Bin2 = 1;
        PWMR = -MotorR;
    }
}
