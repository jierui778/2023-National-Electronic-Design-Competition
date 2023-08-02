#include "sg90.h"


void SG90_Init()
{






}

void TIM2_PWM_Init(uint32_t arr, uint32_t psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); // 使能定时器2时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // 使能GPIOA时钟

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_0; // GPIOA1
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // 复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure); // 初始化GPIOA1

    TIM_TimeBaseStructure.TIM_Period = arr; // 自动重装载值
    TIM_TimeBaseStructure.TIM_Prescaler = psc; // 定时器分频
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; // 时钟分频
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数模式
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); // 初始化定时器2

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; // PWM模式1
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; // 输出使能
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; // 高电平有效
    TIM_OC1Init(TIM2, &TIM_OCInitStructure); // 初始化定时器2 OC1
    TIM_OC2Init(TIM2, &TIM_OCInitStructure);// 初始化定时器2 OC2

    TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable); // 使能TIM2在CCR1上的预装载寄存器
    TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable); // 使能TIM2在CCR2上的预装载寄存器


    TIM_Cmd(TIM2, ENABLE); // 使能定时器2
}
