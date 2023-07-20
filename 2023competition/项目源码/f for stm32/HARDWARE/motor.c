#include "motor.h"

void Motor_Init()
{
    TIM1_PWM_Init(4500, 0); // Khz的PWM频率
}
/*函数功能：限制PWM赋值
入口参数：无
返回  值：无*/
void Pwm_Limit(MotorL, MotorR)
{
    if (MotorL > 4000)
        MotorL = 4000;
    if (MotorL < -4000)
        MotorL = -4000;
    if (MotorR > 4000)
        MotorR = 4000;
    if (MotorR < -4000)
        MotorR = -4000;
}

/*函数功能：赋值给PWM寄存器
入口参数：左轮PWM、右轮PWM
返回 值：无 */
void Set_Pwm(uint8_t MotorL, uint8_t MotorR)
{
    Pwm_Limit(MotorL,MotorR);
    if(MotorL>0)
    {
        AIN1=1;
        AIN2=0;
        PWML=MotorL;
    }
    else
    {
        AIN1=0;
        AIN2=1;
        PWML=-MotorL;
    }
    if(MotorR>0)
    {
        BIN1=1;
        BIN2=0;
        PWMR=MotorR;
    }
    else
    {
        BIN1=0;
        BIN2=1;
        PWMR=-MotorR;
    }
}

