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
    OLED_ColorTurn(0);
    while(1)
    {

        OLED_DrawPoint(120,6,1);
        OLED_Refresh();
        // value = (short)Read_Encoder(4);
        // printf("%d\n",value);
        // printf()
//        OLED_ColorTurn(1);
//        OLED_ShowString(1,1,"666");
    }
    
}
