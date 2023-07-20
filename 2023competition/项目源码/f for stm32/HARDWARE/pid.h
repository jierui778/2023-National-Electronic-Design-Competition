
#ifndef __PID_H
#define __PID_H
#include "sys.h"
/*定义PID结构体*/
typedef struct
{
    float kp;
    float ki;
    float kd;
}PID;
/*外部结构体声明*/
extern PID SpeedDate;//定义速度PID参数结构体，在这里设置速度PID参数
extern PID TraceTurndate;//定义转向PID参数结构体，在这里设置转向PID参数
/**/
extern int Position_PID(float deviation, PID pid);
extern int Position_PID2(float deviation,PID pid);
extern int PositionPIDToSpeed(float deviation,PID pid);
extern int PositionPIDToSpeed2(float deviation,PID pid); 


#endif
