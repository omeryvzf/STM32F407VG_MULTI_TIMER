#include "stm32f4xx.h"
#include "stm32f4xx_tim.h"

void gpioConfig(){
	GPIO_InitTypeDef	GPIOInitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	GPIOInitStructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIOInitStructure.GPIO_OType=GPIO_OType_PP;
	GPIOInitStructure.GPIO_Pin=GPIO_Pin_0| GPIO_Pin_2;
	GPIOInitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIOInitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOB,&GPIOInitStructure);

}
void timerConfig(){
	TIM_TimeBaseInitTypeDef	TIMERInitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);

	//tim3
	TIMERInitStructure.TIM_ClockDivision=1;
	TIMERInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIMERInitStructure.TIM_Period=5999;
	TIMERInitStructure.TIM_Prescaler=999;
	TIMERInitStructure.TIM_RepetitionCounter=0;

	TIM_TimeBaseInit(TIM3,&TIMERInitStructure);
	TIM_SelectOutputTrigger(TIM3,TIM_TRGOSource_Update);
	TIM_Cmd(TIM3,ENABLE);
	//tim4
	TIMERInitStructure.TIM_ClockDivision=1;
	TIMERInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIMERInitStructure.TIM_Period=5999;
	TIMERInitStructure.TIM_Prescaler=3999;
	TIMERInitStructure.TIM_RepetitionCounter=0;

	TIM_TimeBaseInit(TIM4,&TIMERInitStructure);
	TIM_SelectOutputTrigger(TIM4,TIM_TRGOSource_Update);
	TIM_Cmd(TIM4,ENABLE);

}
void nvicConfig(){
	NVIC_InitTypeDef	NVICInitStructure;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	// tim3
	NVICInitStructure.NVIC_IRQChannel=TIM3_IRQn;
	NVICInitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVICInitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVICInitStructure.NVIC_IRQChannelSubPriority=0;
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	NVIC_Init(&NVICInitStructure);
	//tim4
	NVICInitStructure.NVIC_IRQChannel=TIM4_IRQn;
	NVICInitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVICInitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVICInitStructure.NVIC_IRQChannelSubPriority=0;
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
	NVIC_Init(&NVICInitStructure);

}
void toggleLed(uint16_t pin){
	uint16_t readLed=GPIO_ReadInputDataBit(GPIOB,pin);
	if (readLed==(uint16_t)Bit_SET){
		GPIO_ResetBits(GPIOB,pin);
	}
	else{
		GPIO_SetBits(GPIOB,pin);
	}
}
void TIM3_IRQHandler(){
	toggleLed(GPIO_Pin_0);
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
}
void TIM4_IRQHandler(){
	toggleLed(GPIO_Pin_2);
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
}

int main(void){
	gpioConfig();
	timerConfig();
	nvicConfig();


	while (1){
	  ///

  }
}
