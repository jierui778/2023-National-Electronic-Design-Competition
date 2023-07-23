#include "stm32f10x.h"
#include "usart.h"
#include "delay.h"
#include "mpu6050.h"


int temp;
int main(void)
{	
    MPU6050_IIC_Init();
    delay_init();
    MPU6050_Init();
    DMP_Init();
    
    
    uart_init(9600);  
    
while(1)
{
    temp = MPU6050_testConnection();
//    printf("%d\n",temp);
    

}
}

