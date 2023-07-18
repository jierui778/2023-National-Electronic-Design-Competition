#ifndef __PID_H
#define __PID_H
#include "sys.h"
typedef struct
{
    float kp;
    float ki;
    float kd;
}PID;
extern int Position_PID(float Encoder,float Target);
extern int Position_PID2(float Encoder,float Target);
extern int PositionPIDToSpeed(float Encoder,float Target);


#endif
