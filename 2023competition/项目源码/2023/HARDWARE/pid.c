#include "pid.h"




///*定义速度PID参数结构体，在这里设置PID参数*/
PID x_dir =
    {
        -100,
        -1,
        0};
/*定义速度PID参数结构体，在这里设置PID参数*/
PID y_dir =
    {
        50,
        0,
        10}; // 两个pid参数，乱给的，后期修改

				
				
/* *        [in] float deviation: 和目标值得偏差
 *        [in] _PID pid: 位置式pid的参数*/

//int Position_PID(float deviation, PID pid)
//{
//    float Position_KP = pid.kp, Position_KI = pid.ki, Position_KD = pid.kd; // 获取设置的pid参数
//    static float Bias, Integral_Bias, Last_Bias, PwmKI;
//    int Pwm;
//    Bias = deviation;
//    Integral_Bias += Bias;
//    Pwm = Position_KP * Bias + Position_KI * Integral_Bias + Position_KD * (Bias - Last_Bias);
//    return Pwm;
//}
//int Position_PID2(float deviation, PID pid)
//{
//    float Position_KP = pid.kp, Position_KI = pid.ki, Position_KD = pid.kd; // 获取设置的pid参数
//    static float Bias, Integral_Bias, Last_Bias, PwmKI;
//    int Pwm;
//    Bias = deviation;
//    Integral_Bias += Bias;
//    Pwm = Position_KP * Bias + Position_KI * Integral_Bias + Position_KD * (Bias - Last_Bias);
//    return Pwm;
//}
/**/
int PositionPIDToSpeed_x(float deviation, PID pid)
{
    float Position_KP = pid.kp, Position_KI = pid.ki, Position_KD = pid.kd; // 获取设置的pid参数
    static float Bias, Integral_bias, Last_Bias, PwmKI = 0;
    int Pwm;
    Bias = deviation;                    // 获取偏差
    Integral_bias += Bias;               // 求出偏差积分
    PwmKI = Position_KI * Integral_bias; // 求出积分项
    if(PwmKI>PWM_MAX) Integral_bias=PWM_MAX/Position_KI;    //限幅
    Pwm = Position_KP * Bias + PwmKI + Position_KD * (Bias - Last_Bias);
    Last_Bias = Bias; // 保存上一次偏差
    return Pwm;
}
int PositionPIDToSpeed_y(float deviation,PID pid)
{
    float Position_KP = pid.kp, Position_KI = pid.ki, Position_KD = pid.kd; // 获取设置的pid参数
    static float Bias, Integral_bias, Last_Bias, PwmKI = 0;
    int Pwm;
    Bias = deviation;                    // 获取偏差
    Integral_bias += Bias;               // 求出偏差积分
    PwmKI = Position_KI * Integral_bias; // 求出积分项
    if(PwmKI>PWM_MAX) Integral_bias=PWM_MAX/Position_KI;
    Pwm = Position_KP * Bias + PwmKI + Position_KD * (Bias - Last_Bias);
    Last_Bias = Bias; // 保存上一次偏差
    return Pwm;
}
int Change_x(int Now_x_ValueL, int Target_x)
{
    int pwm=0;
    int bias=0;
    bias =Now_x_ValueL-Target_x;
    pwm = PositionPIDToSpeed_x(bias, x_dir);
    if (pwm > PWM_MAX)
    {
        pwm = PWM_MAX;
    }
    else if (pwm < PWM_MIN)
    {
        pwm = PWM_MIN;
    }
    return pwm;
}
int Change_y(int Now_y_ValueL, int Target_y)
{
    int pwm=0;
    int bias=0;
    bias =Now_y_ValueL-Target_y;
    pwm = PositionPIDToSpeed_x(bias, x_dir);
    if (pwm > PWM_MAX)
    {
        pwm = PWM_MAX;
    }
    else if (pwm < PWM_MIN)
    {
        pwm = PWM_MIN;
    }
    return pwm;
}

