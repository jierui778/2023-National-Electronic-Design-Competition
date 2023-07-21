#include "control.h"
#include "motor.h"
#include "encoder.h"
#include "pid.h"
/**
 * @description: 模块全部初始化
 * @return {*}
 */
void Control_Init(void)
{
    Motor_Init();
    Encoder_Init();


}

//void ChangeSpeedMotorL(int NowEncoderValue,int TargetEncoderValue)
//{
//    int pwm;
//    int bias;
//    int Target;
//    SpeedL=PositionPIDToSpeed(NowEncoderValue,TargetEncoderValue,SpeedDate);
//    Set_Pwm(SpeedL,TargetR);
//}
/**
 * @description: 小车运动的数学模型 
 * @param {uint8_t} velocity 小车速度值
 * @param {uint8_t} turn 小车转向值
 * @return {*}
 */
void Car_Model(uint8_t velocity, uint8_t turn)
{
    TargetL = velocity + turn;
    TargetR = velocity - turn; // 两轮差速调整方向
}
/**
 * @description: 小车遇到控制错误时停止
 * @return {*}
 */
void All_Stop(void)
{
    TargetL = 0;
    TargetR = 0;
}
/**
 * @description: 根据偏差角度计算转向pwm
 * @param {int} angle 偏差角度
 * @return {int} pwm 转向pwm
 */
int ChangeTraceTurn(int angle)
{
    int pwm;
    int bias;
    bias=angle;
    pwm=Position_PID(bias,TraceTurnDate);
    return pwm;
}
void TraceMove(int angle,int velocity)
{
    int pwmturn;
    int SpeedL,SpeedR;  //左右轮速度
    pwmturn=ChangeTraceTurn(angle);
    SpeedL=velocity+pwmturn;
    Set_Pwm(TargetL,TargetR);
}
