#include "gpio.h"



void Gpio_Init(void)
{
	
	GPIO_InitTypeDef gpio_initstruct;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB , ENABLE);							//��GPIOB��ʱ��
	
//	//PA1 -- �󷽺���   PA8 -- �ҷ�����   PA12 -- �󷽺���
//	gpio_initstruct.GPIO_Pin =  GPIO_Pin_1 | GPIO_Pin_12 |  GPIO_Pin_8;
//	gpio_initstruct.GPIO_Mode = GPIO_Mode_IPU ;
//	GPIO_Init(GPIOA, &gpio_initstruct);	

//	
//	
//	//PB13 -- ������  PB14 -- ������
//	gpio_initstruct.GPIO_Mode = GPIO_Mode_Out_PP;									//����Ϊ�������ģʽ
//	gpio_initstruct.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;
//	gpio_initstruct.GPIO_Speed = GPIO_Speed_50MHz;									//���ص����Ƶ��
//	GPIO_Init(GPIOB, &gpio_initstruct);	
//	
//	GPIO_SetBits(GPIOB,GPIO_Pin_13);//�ط�����
//	GPIO_SetBits(GPIOB,GPIO_Pin_14);//�ر�����
}
