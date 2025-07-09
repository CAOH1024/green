#include "stm32f10x.h"                  // Device header

void PWM_LED_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 |GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	TIM_InternalClockConfig(TIM2);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 20000 - 1;   //ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;   //PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;    //CCR
	TIM_OC1Init(TIM2,&TIM_OCInitStructure);
	TIM_OC2Init(TIM2,&TIM_OCInitStructure);
	
	TIM_Cmd(TIM2, ENABLE);
}

void Set_PWMCCR(uint16_t CCR){
	TIM_SetCompare1(TIM2, CCR);
}

void Set_PWMCCR2(uint16_t CCR){
	TIM_SetCompare2(TIM2, CCR);
}

void Set_Servo_Angle(uint8_t Servo_Num, float angle){
	if(angle > 180) angle = 180;
	if(angle < 0) angle = 0;
	uint16_t CCR = ((angle * 2000 / 180) + 500) + 0.5; // Convert angle to CCR value
	if(Servo_Num == 1) TIM_SetCompare1(TIM2, CCR);
	else if(Servo_Num == 2) TIM_SetCompare2(TIM2, CCR);
}
