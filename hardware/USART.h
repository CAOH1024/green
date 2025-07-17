#ifndef __USART_H
#define __USART_H

#include "stm32f10x.h"

extern uint8_t Serial_RXPacket[4];
extern uint8_t TXpacket[4];

int Serial_Init(void);
uint16_t Serial_SendByte(uint8_t DATA);
uint16_t Serial_SendArray(uint8_t *array,uint16_t len);
uint32_t Pow(uint16_t a,uint16_t b);
uint16_t Serial_SendNum(uint16_t num,uint16_t len);
void Serial_SendString(char *String);
void Serial_printf(char *format, ...);
uint16_t Serial_GetFlag(void);
void Serial_SendPacket(uint8_t Array[]);

#endif
