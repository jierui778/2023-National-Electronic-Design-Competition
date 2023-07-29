#include "stm32f10x.h" // Device header
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "exti.h"

int main(void)

{
    delay_init();                                   // 延时函数初始化
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // 设置NVIC中断分组2:2位抢占优先级，2位响应优先级
    uart_init(115200);                              // 串口初始化为115200
    LED_Init();                                     // 初始化与LED连接的硬件接口
    KEY_Init();                                     // 初始化与按键连接的硬件接口
    EXTIX_Init();                                   // 外部中断初始化
    LED0 = 0;                                       // 先点亮红灯
    while (1)
    {
        delay_ms(1000);
    }
}
