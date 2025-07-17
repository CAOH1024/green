#include "USART.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>

#define Packet_len 4

uint8_t Serial_RXPacket[4];
uint8_t TXpacket[4];
uint8_t RXFLAG;
uint8_t i = 0;


int Serial_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART2,&USART_InitStructure);
	
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_Cmd(USART2,ENABLE);
	
	return 0;
}

void Serial_SendByte(uint8_t DATA){
	USART_SendData(USART2,DATA);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
}

void Serial_SendArray(uint8_t *array,uint16_t len){
	for(uint16_t i=0;i<len;i++){
		Serial_SendByte(array[i]);
	}
}

uint32_t Pow(uint16_t a,uint16_t b){
	uint32_t res = 1;
	while(b){
		res *= a;
		b--;}
	return res;
}	
	
void Serial_SendNum(uint16_t num,uint16_t len){
	uint16_t temp;
	while(len){
		temp = num / Pow(10,len-1);
		Serial_SendByte(temp+'0');
		num = num % Pow(10,len-1);
		len--;
	}
}

void Serial_SendString(char *String){
	for(uint16_t i=0;String[i]!='\0';i++){
		Serial_SendByte(String[i]);
	}
}

void Serial_printf(char *format, ...){
	char String[100];
	va_list arg;
	va_start(arg,format);
	vsprintf(String,format,arg);
	va_end(arg);
	Serial_SendString(String);
}

uint16_t Serial_GetFlag(void){
	if(RXFLAG==1){
		RXFLAG=0;
		return 1;
	}
	return 0;
}

void Serial_SendPacket(void){
	Serial_SendByte(0xFF);
	Serial_SendArray(TXpacket,Packet_len);
	Serial_SendByte(0xFE);
}


void USART1_IRQHandler(void)
{
	static uint8_t RxState = 0;
	static uint8_t pRxPacket = 0;
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		uint8_t RxData = USART_ReceiveData(USART1);

		if (RxState == 0)
		{
			if (RxData == 0xFF)
			{
				RxState = 1;
				pRxPacket = 0;
			}
		}
		else if (RxState == 1)
		{
			Serial_RXPacket[pRxPacket] = RxData;
			pRxPacket ++;
			if (pRxPacket > 5)
			{
				RxState = 2;
			}
		}
		else if (RxState == 2)
		{
			if (RxData == 0xFE)
			{
				RxState = 0;
				RXFLAG = 1;
			}
		}

		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
}
