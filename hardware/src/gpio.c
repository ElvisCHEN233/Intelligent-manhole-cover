#include "gpio.h"



void Gpio_Init(void)
{
	
	GPIO_InitTypeDef gpio_initstruct;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB , ENABLE);							//打开GPIOB的时钟
	
//	//PA1 -- 左方红外   PA8 -- 右方红外   PA12 -- 后方红外
//	gpio_initstruct.GPIO_Pin =  GPIO_Pin_1 | GPIO_Pin_12 |  GPIO_Pin_8;
//	gpio_initstruct.GPIO_Mode = GPIO_Mode_IPU ;
//	GPIO_Init(GPIOA, &gpio_initstruct);	

//	
//	
//	//PB13 -- 蜂鸣器  PB14 -- 报警灯
//	gpio_initstruct.GPIO_Mode = GPIO_Mode_Out_PP;									//设置为推挽输出模式
//	gpio_initstruct.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;
//	gpio_initstruct.GPIO_Speed = GPIO_Speed_50MHz;									//承载的最大频率
//	GPIO_Init(GPIOB, &gpio_initstruct);	
//	
//	GPIO_SetBits(GPIOB,GPIO_Pin_13);//关蜂鸣器
//	GPIO_SetBits(GPIOB,GPIO_Pin_14);//关报警灯
}
