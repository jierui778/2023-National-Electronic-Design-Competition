#include "stm32f10x.h"
#include "sys.h"
#include "timer.h"
#include "usart.h"
#include "encoder.h"
#include "oled.h"

int main(void)
{

    // Encoder_Init();
    // uart_init(9600);
    // int value;
    OLED_Init();//OLED初始化
    while(1)
    {
        // value = (short)Read_Encoder(4);
        // printf("%d\n",value);
        // printf()
        OLED_ShowString(1,1,"666");
    }
    
}
