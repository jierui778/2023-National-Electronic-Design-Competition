#include "stm32f10x.h" // Device header
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "sg90.h"

int main(void)

{
    TIM2_PWM_Init(200 - 1, 8400 - 1);               // 20Khz的PWM频率
    delay_init();                                   // 延时函数初始化
    while (1)
    {
        delay_ms(100);
        TIM_SetCompare2(TIM2, 190);
        while (1)
        {
            
        }
    }
}
