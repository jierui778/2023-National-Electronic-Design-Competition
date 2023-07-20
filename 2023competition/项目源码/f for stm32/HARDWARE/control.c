#include "control.h"
/*小车的数学模型*/
/*左加右减*/
void Car_Model(uint8_t velocity, uint8_t turn)
{
    TargetL = velocity + turn;
    TargetR = velocity - turn; // 两轮差速调整方向
}
/*小车遇到控制错误，全部停止运行*/
void All_Stop(void)
{
    TargetL = 0;
    TargetR = 0;
}