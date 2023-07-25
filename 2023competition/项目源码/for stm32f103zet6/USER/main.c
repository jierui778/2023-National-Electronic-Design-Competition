#include "stm32f10x.h"
#include "usart.h"
#include "delay.h"
#include "oled.h"
#include "mpu6050.h"

int temp;
short a, b, c;
int main(void)
{
    delay_init();
    MPU6050_Init();
    //    uart_init(9600);
    //    MPU_Init();
    OLED_Init();
    temp = MPU6050_Init();

    while (1)
    {
        //    MPU6050_GetAccelerometer(&a,&b,&c);
        ////    MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//�õ����ٶȴ���������

        MPU6050_GetGyroscope(&a, &b, &c);
        OLED_ShowSignedNum(1, 0, temp, 5, 16, 1);
        OLED_ShowSignedNum(1, 16, b, 5, 16, 1);
        OLED_ShowSignedNum(1, 32, c, 5, 16, 1);
        OLED_Refresh();

        //    printf("%d\n",temp);
    }
}
