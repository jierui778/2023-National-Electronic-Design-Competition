#include "servo.h"
/**
 * @description: 舵机初始化
 * @return {*}无
 */
void Servo_Init()
{
    TIM1_PWM_Init(20000 - 1, 72 - 1);
}
/**
 * @description: 设置x轴舵机pwm
 * @param {uint16_t} Compare_x：x轴pwm
 * @return {*}
 */
void PWM_SetCompare_x(uint16_t Compare_x)
{
    TIM_SetCompare1(TIM1, Compare_x); // 这是设置CCR的值，并不是直接设置占空比
}
/**
 * @description: 设置y轴舵机pwm
 * @param {uint16_t} Compare_y：y轴pwm
 * @return {*}
 */
void PWM_SetCompare_y(uint16_t Compare_y)
{
    TIM_SetCompare4(TIM1, Compare_y); // 这是设置CCR的值，并不是直接设置占空比
}
/**
 * @description: 设置x轴偏移角度
 * @param {float} Angle：x轴偏移角度
 * @return {*}无
 */
void Servo_SetAngle_x(float Angle)
{
    PWM_SetCompare_x((Angle+4) / 180 * 2000 + 1500);
}
/**
 * @description: 设置y轴偏移角度
 * @param {float} Angle：y轴偏移角度
 * @return {*}无
 */
void Servo_SetAngle_y(float Angle)
{
    PWM_SetCompare_y(-Angle / 180 * 2000 + 1500);
}
/**
 * @description: 舵机恢复原始位置
 * @return {*}无
 */
void Servo_Reset()
{
    Servo_SetAngle_x(0);
    Servo_SetAngle_y(0);
}
void Servo_TrackLine()
{
    
}

