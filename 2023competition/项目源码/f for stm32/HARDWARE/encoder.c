#include"encoder.h"
#include"sys.h"
#include"timer.h"

void Encoder_Init(void)
{
	Encoder_TIM3_Init();
	Encoder_TIM4_Init();
}
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
