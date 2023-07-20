#include"pid.h"

/*定义速度PID参数结构体，在这里设置速度PID参数*/
PID SpeedDate=
{
    -0.3,
    -0.05,
    0
};
/*定义速度PID参数结构体，在这里设置转向PID参数*/
PID TraceTurndate=
{
    0.5,
    0.1,
    0.1
};//两个pid参数，乱给的，后期修改

/* *        [in] float deviation: 和目标值得偏差
 *        [in] _PID pid: 位置式pid的参数*/
int Position_PID(float deviation, PID pid)
{
    float Position_KP=pid.kp,Position_KI=pid.ki,Position_KD=pid.kd;//获取设置的pid参数
    static float Bias, Integral_Bias,Last_Bias,PwmKI;
    int Pwm;
    Bias=deviation;
    Integral_Bias+=Bias;
    Pwm=Position_KP*Bias+Position_KI*Integral_Bias+Position_KD*(Bias-Last_Bias);
    return Pwm;
}
int Position_PID2(float deviation, PID pid)
{
    float Position_KP = pid.kp, Position_KI = pid.ki, Position_KD = pid.kd; // 获取设置的pid参数
    static float Bias, Integral_Bias, Last_Bias, PwmKI;
    int Pwm;
    Bias = deviation;
    Integral_Bias += Bias;
    Pwm = Position_KP * Bias + Position_KI * Integral_Bias + Position_KD * (Bias - Last_Bias);
    return Pwm;
}
/**/
int PositionPIDToSpeed(float deviation,PID pid)
{
    float Position_KP=pid.kp,Position_KI=pid.ki,Position_KD=pid.kd;//获取设置的pid参数
    static float Bias,Integral_bias,Last_Bias,PwmKI=0;
    int Pwm;
    Bias=deviation;//获取偏差
    Integral_bias+=Bias;//求出偏差积分
    PwmKI = Position_KI *Integral_bias;//求出积分项
    Pwm = Position_KP * Bias + PwmKI + Position_KD * (Bias - Last_Bias);
    Last_Bias=Bias;//保存上一次偏差
    return Pwm;
}
// int PositionPIDToSpeed2(float Encoder,float Target)
// {
//     static float Bias,LastBias,PrevBias;
//     static float Integral;
//     static float result;
//     Bias=Encoder-Target;
//     Integral+=Bias;
//     result=SpeedDate.kp*Bias+SpeedDate.ki*Integral+SpeedDate.kd*(Bias-LastBias);
//     LastBias=Bias;
//     return result;
// }
//int Position_PID(float Encoder,float Target)
//{
//    static float Bias,LastBias,PrevBias;
//    static float Integral;
//    static float result;
//    Bias=Encoder-Target;
//    Integral+=Bias;
//    result=SpeedDate.kp*Bias+SpeedDate.ki*Integral+SpeedDate.kd*(Bias-LastBias);
//    LastBias=Bias;
//    return result;
//}   
