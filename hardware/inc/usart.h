#ifndef _USART_H_
#define _USART_H_


#include "stm32f10x.h"


#define USART_DEBUG		USART1		//调试打印所使用的串口组

extern unsigned char Usart3Len;	//usart1接收的数据长度
extern  char Usart3Buf[512];	//usart1接收缓存

void Usart1_Init(unsigned int baud);

void Usart2_Init(unsigned int baud);

void Usart3_Init(unsigned int baud);

void Usart_SendString(USART_TypeDef *USARTx, unsigned char *str, unsigned short len);

void UsartPrintf(USART_TypeDef *USARTx, char *fmt,...);

void UsartSend(USART_TypeDef *USARTx, char *fmt);

#endif
