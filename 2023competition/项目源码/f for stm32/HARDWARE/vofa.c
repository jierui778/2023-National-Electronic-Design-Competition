#include "vofa.h"
#include "sys.h"
#include "usart.h"

void Vofa_Serial_init(u32 bound)
{
    uart_init(bound);
}
void FireWater_Send(uint8_t *chr,float a, float b,float c,float d)//四通道数据
{
    printf("%s,%f,%f,%f,%f\n", *chr, a, b, c, d);
    // u8 i;
    // u8 sum=0;
    // u8 data[8]={0x55,0x55,0x00,0x00,0x00,0x00,0x00,0x00};
    // for(i=0;i<7;i++)
    // {
    //     sum+=data[i];
    // }
    // data[7]=sum;
    // for(i=0;i<8;i++)
    // {
    //     USART_SendData(USART1,data[i]);
    //     while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
    // }
}


// void float_turn_u8(float f,uint8_t *c)
// {
//     uint8_t i;
//     FloatlongType data;
//     data.fdata=f;
//     for(i=0;i<4;i++)
//     {
//         c[i]=data.cdata[i];
//     }



// }
// void JustFloat_Send()
// {
//     u8 i;
//     u8 sum=0;
//     u8 data[8]={0x55,0x55,0x00,0x00,0x00,0x00,0x00,0x00};
//     for(i=0;i<7;i++)
//     {
//         sum+=data[i];
//     }
//     data[7]=sum;
//     for(i=0;i<8;i++)
//     {
//         USART_SendData(USART1,data[i]);
//         while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
//     }
// }