#include "key.h"
#include "delay.h"


void KEY_Init()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);//使能GPIOA,GPIOE时钟
    
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//设置为下拉输入
    GPIO_Init(GPIOE,&GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//设置为下拉输入
    GPIO_Init(GPIOA,&GPIO_InitStructure);


}
uint8_t KEY_Scan(uint8_t KEY_Num)
{



}