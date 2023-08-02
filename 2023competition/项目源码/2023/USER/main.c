#include "stm32f10x.h" // Device header
#include "sys.h"
#include "delay.h"
#include "usart.h"


int main(void)

{

    delay_init();                                   // 延时函数初始化
    while (1)
    {
        delay_ms(100);



    }
}
