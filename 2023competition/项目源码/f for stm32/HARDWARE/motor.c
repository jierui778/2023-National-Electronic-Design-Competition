#include "motor.h"

void Motor_Init()
{
    TIM1_PWM_Init(4500, 0); // Khz的PWM频率
}
void Set_Pwm_All(uint8_t pwm)
{
    TIM_SetCompare1(TIM1, pwm);
    TIM_SetCompare4(TIM1, pwm);
}
void Set_Pwm_MotorL(uint8_t pwm)
{
    TIM_SetCompare1(TIM1, pwm);
}
void Set_Pwm_MotorR(uint8_t pwm)
{
    TIM_SetCompare4(TIM1, pwm);
}
