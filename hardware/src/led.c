

//单片机头文件
#include "stm32f10x.h"

//LED头文件
#include "led.h"
#include "delay.h"

LED_STATUS led_status;


/*
************************************************************
*	函数名称：	Led_Init
*
*	函数功能：	LED初始化
*
*	入口参数：	无
*
*	返回参数：	无
*
*	说明：		LED4-PB6	LED5-PB7	LED6-PB8	LED7-PB9
				高电平关灯		低电平开灯
************************************************************
*/
void Led_Init(void)
{
	
	GPIO_InitTypeDef gpio_initstruct;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA, ENABLE);							//打开GPIOB的时钟
	

	
	
	
	
	gpio_initstruct.GPIO_Mode = GPIO_Mode_Out_PP;									//设置为推挽输出模式
	gpio_initstruct.GPIO_Pin = GPIO_Pin_12;
	gpio_initstruct.GPIO_Speed = GPIO_Speed_50MHz;									//承载的最大频率

	
	GPIO_Init(GPIOB, &gpio_initstruct);												//初始化GPIOB
		
	Led_test(LED_OFF);
}




/*
************************************************************
*	函数名称：	Led_test
*
*	函数功能：	LED4控制
*
*	入口参数：	status：LED_ON-开灯	LED_OFF-关灯
*
*	返回参数：	无
*
*	说明：		
************************************************************
*/
void Led_test(LED_ENUM status)
{

	GPIO_WriteBit(GPIOB, GPIO_Pin_12, status != LED_ON ? Bit_SET : Bit_RESET);
	led_status.Led1Sta = status;

}






/*
************************************************************
*	函数名称：	Led2_Set
*
*	函数功能：	LED4控制
*
*	入口参数：	status：LED_ON-开灯	LED_OFF-关灯
*
*	返回参数：	无
*
*	说明：		
************************************************************
*/
void Led2_Set(LED_ENUM status)
{

	GPIO_WriteBit(GPIOB, GPIO_Pin_6, status != LED_ON ? Bit_SET : Bit_RESET);
	led_status.Led2Sta = status;

}

/*
************************************************************
*	函数名称：	Led3_Set
*
*	函数功能：	LED5控制
*
*	入口参数：	status：LED_ON-开灯	LED_OFF-关灯
*
*	返回参数：	无
*
*	说明：		
************************************************************
*/
void Led3_Set(LED_ENUM status)
{

	GPIO_WriteBit(GPIOB, GPIO_Pin_7, status != LED_ON ? Bit_SET : Bit_RESET);
	led_status.Led3Sta = status;

}

/*
************************************************************
*	函数名称：	Led4_Set
*
*	函数功能：	LED6控制
*
*	入口参数：	status：LED_ON-开灯	LED_OFF-关灯
*
*	返回参数：	无
*
*	说明：		
************************************************************
*/
void Led4_Set(LED_ENUM status)
{

	GPIO_WriteBit(GPIOB, GPIO_Pin_8, status != LED_ON ? Bit_SET : Bit_RESET);
	led_status.Led4Sta = status;

}

/*
************************************************************
*	函数名称：	Led5_Set
*
*	函数功能：	LED7控制
*
*	入口参数：	status：LED_ON-开灯	LED_OFF-关灯
*
*	返回参数：	无
*
*	说明：		
************************************************************
*/
void Led5_Set(LED_ENUM status)
{

	GPIO_WriteBit(GPIOB, GPIO_Pin_9, status != LED_ON ? Bit_SET : Bit_RESET);
	led_status.Led5Sta = status;

}

void Light_Start(void)
{
	Led_test(LED_ON);
	DelayXms(50);
	Led_test(LED_OFF);
	DelayXms(50);
	Led_test(LED_ON);
	DelayXms(50);
	Led_test(LED_OFF);
	
}