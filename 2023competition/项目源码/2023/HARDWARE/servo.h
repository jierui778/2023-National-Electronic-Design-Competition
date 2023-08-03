/*
 * @Author: Azlic 2311032232@qq.com
 * @Date: 2023-08-03 08:21:55
 * @LastEditors: Azlic 2311032232@qq.com
 * @LastEditTime: 2023-08-03 18:58:46
 * @FilePath: \competition\2023competition\项目源码\2023\HARDWARE\servo.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef __SERVO_H
#define __SERVO_H

#include "sys.h"
void Servo_Init(void);   //初始化
void PWM_SetCompare_x(uint16_t Compare_x);//设置x轴pwm
void PWM_SetCompare_y(uint16_t Compare_y);//设置y轴pwm
void Servo_SetAngle_x(float Angle);//设置x轴偏移角度
void Servo_SetAngle_y(float Angle);//设置y轴偏移角度
void Servo_SetBias_x(float Bias);//设置x轴偏移量
void Servo_SetBias_y(float Bias);//设置y轴偏移量
<<<<<<< HEAD
void Servo_SetBias_x(float Bias);//设置x轴偏移量
void Servo_SetBias_y(float Bias);//设置y轴偏移量
=======
>>>>>>> 17b694d56a43349a362b130eed5bc9bea1ff3c1a

void Servo_Reset(void);//复位
#endif
