#include"encoder.h"
#include"sys.h"
#include"timer.h"

void Encoder_Init(void)
{
	Encoder_TIM3_Init();
	Encoder_TIM4_Init();
}
// void Encoder_TIM3_Init(void)
// {
//     TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
// 	TIM_ICInitTypeDef TIM_ICInitStructure;  
// 	GPIO_InitTypeDef GPIO_InitStructure;

// 	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);    //使能定时器2的时钟

// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);   //使能PA端口时钟

// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;	//端口配置
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   //浮空输入
// 	GPIO_Init(GPIOA, &GPIO_InitStructure);					//根据设定参数初始化GPIOA

// 	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
// 	TIM_TimeBaseStructure.TIM_Prescaler = 0x0;              //预分频器 
// 	TIM_TimeBaseStructure.TIM_Period = 65535;  //设定计数器自动重装值
// 	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //选择时钟分频：不分频
// 	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//TIM向上计数  
// 	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
// 	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//使用编码器模式3
	
// 	TIM_ICStructInit(&TIM_ICInitStructure);
// 	TIM_ICInitStructure.TIM_ICFilter = 10;
// 	TIM_ICInit(TIM3, &TIM_ICInitStructure);
// 	TIM_ClearFlag(TIM3, TIM_FLAG_Update);                   //清除TIM的更新标志位
// 	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
// 	//Reset counter
// 	TIM_SetCounter(TIM3,0);
// 	//===============================================
// //	TIM3->CNT = 0x7fff;
// 	//===============================================
// 	TIM_Cmd(TIM3, ENABLE); 
// }
// void Encoder_TIM4_Init(void)
// {
// 	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
// 	TIM_ICInitTypeDef TIM_ICInitStructure;  
// 	GPIO_InitTypeDef GPIO_InitStructure;
// 	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);    //使能定时器4的时钟
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);   //使能PB端口时钟

// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;	//端口配置
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   //浮空输入
// 	GPIO_Init(GPIOB, &GPIO_InitStructure);					//根据设定参数初始化GPIOB

// 	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
// 	TIM_TimeBaseStructure.TIM_Prescaler = 0x0;              // 预分频器 
// 	TIM_TimeBaseStructure.TIM_Period = 65535;  //设定计数器自动重装值
// 	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //选择时钟分频：不分频
// 	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//TIM向上计数  
// 	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
// 	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//使用编码器模式3
// 	TIM_ICStructInit(&TIM_ICInitStructure);
// 	TIM_ICInitStructure.TIM_ICFilter = 10;
// 	TIM_ICInit(TIM4, &TIM_ICInitStructure);
// 	TIM_ClearFlag(TIM4, TIM_FLAG_Update);                   //清除TIM的更新标志位
// 	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
// 	//Reset counter
// 	TIM_SetCounter(TIM4,0);
// 	//===============================================
// //	TIM4->CNT = 0x7fff;
// 	//===============================================
// 	TIM_Cmd(TIM4, ENABLE);  
// }
int Read_Encoder(u8 TIMX)
{
	int value; 
	switch(TIMX)
	{
		case 3:
			value = (short)TIM_GetCounter(TIM3);
			TIM_SetCounter(TIM3,0);
			break;
		case 4:
			value = (short)TIM_GetCounter(TIM4);
			TIM_SetCounter(TIM4,0);
			break;
		default:
			value=0;
			break;
	}
	return value;
}