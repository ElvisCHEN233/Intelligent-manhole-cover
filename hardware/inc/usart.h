#ifndef _USART_H_
#define _USART_H_


#include "stm32f10x.h"


#define USART_DEBUG		USART1		//���Դ�ӡ��ʹ�õĴ�����

extern unsigned char Usart3Len;	//usart1���յ����ݳ���
extern  char Usart3Buf[512];	//usart1���ջ���

void Usart1_Init(unsigned int baud);

void Usart2_Init(unsigned int baud);

void Usart3_Init(unsigned int baud);

void Usart_SendString(USART_TypeDef *USARTx, unsigned char *str, unsigned short len);

void UsartPrintf(USART_TypeDef *USARTx, char *fmt,...);

void UsartSend(USART_TypeDef *USARTx, char *fmt);

#endif
