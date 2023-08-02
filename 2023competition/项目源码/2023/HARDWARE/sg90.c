#include "sg90.h"


void SG90_Init()
{
    TIM1_PWM_Init(20000 - 1, 72 - 1);
}

void PWM_SetCompare_x(uint16_t Compare_x)
{
	TIM_SetCompare1(TIM1, Compare_x);																	//这是设置CCR的值，并不是直接设置占空比
}
void PWM_SetCompare_y(uint16_t Compare_y)
{
	TIM_SetCompare4(TIM1, Compare_y);																	//这是设置CCR的值，并不是直接设置占空比
}

void Servo_SetAngle_x(float Angle)
{
	PWM_SetCompare_x(Angle / 180 * 2000 +1500);
}

void Servo_SetAngle_y(float Angle)
{
	PWM_SetCompare_y(-Angle / 180 * 2000 + 1500);
}