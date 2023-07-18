#include"pid.h"
PID SpeedDate=
{
    -40,
    -0.1,
    -0.1
};
PID TraceTurndate=
{
    0.5,
    0.1,
    0.1
};//两个pid参数，乱给的










int Position_PID(float Encoder,float Target)
{
    static float Bias,LastBias,PrevBias;
    static float Integral;
    static float result;
    Bias=Encoder-Target;
    Integral+=Bias;
    result=SpeedDate.kp*Bias+SpeedDate.ki*Integral+SpeedDate.kd*(Bias-LastBias);
    LastBias=Bias;
    return result;
}   