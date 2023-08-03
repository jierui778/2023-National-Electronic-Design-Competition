#include "control.h"
#include "math.h"
#include "servo.h"
#include "key.h"
#include "usart.h"
#include "delay.h"
#include "timer.h" 
#include "pid.h"
#include "oled.h"

void Control_Init()
{
    Servo_Init();
    Servo_Reset();//初始化舵机并复位
    delay_init();//初始化延时函数
    KEY_Init();//初始化按键
    OLED_Init();//初始化OLED
    Serial_Init(115200);//初始化串口

}
/**
 * @description: 寻找原点
 * @param {int} Targetx：目标x轴坐标
 * @param {int} Targety：目标y轴坐标
 * @param {int} Currentx：当前x轴坐标
 * @param {int} Currenty：当前y轴坐标
 * @return {*}
 */
void FindOrigin(int Targetx, int Targety, int Currentx, int Currenty)
{
    int biasx = 0, biasy = 0;
    biasx = Currentx - Targetx;
    biasy = Currenty - Targety;
    if (biasx>0) // 目标位于当前位置右侧
    {
        Servo_SetAngle_x(-biasx);
    }
    else // 目标位于当前位置左侧
    {
        Servo_SetAngle_x(biasx);
    }
    if (biasy>0)//目标位于当前位置上方
    {
        Servo_SetAngle_y(biasy);
    }
    else//目标位于当前位置下方
    {
        Servo_SetAngle_y(-biasy);
    }
}
/**
 * @description: 激光沿外框移动
 * @param {int} Targetx：目标x轴坐标
 * @param {int} Targety：目标y轴坐标
 * @param {int} Currentx：当前x轴坐标
 * @param {int} Currenty：当前y轴坐标
 * @return {*}无
 */
void TrackLine(int Targetx, int Targety, int Currentx, int Currenty)
{
    int biasx = 0, biasy = 0;
    biasx = Currentx - Targetx;
    biasy = Currenty - Targety;
    if(biasx>0||biasy>0)//当前位置在目标位置第一象限
    {
        Servo_SetAngle_x(biasx);
        Servo_SetAngle_y(biasy);
    }
    else if(biasx<0||biasy>0)//当前位置在目标位置第二象限
    
    {
        Servo_SetAngle_x(-biasx);
        Servo_SetAngle_y(-biasy);
    }
    else if (biasx<0||biasy<0)//当前位置在目标位置第三象限
    {
        Servo_SetAngle_x(biasx);
        Servo_SetAngle_y(biasy);
    }
    else if (biasx>0||biasy<0)//当前位置在目标位置第四象限
    {
        Servo_SetAngle_x(-biasx);
        Servo_SetAngle_y(-biasy);
    }
}
// void Task_Run(float )
// {





// }