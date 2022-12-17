#include "hsr04.h" 
#include <string.h>
#include <stdio.h>
#include "delay.h"

#define Trig PBout(0) // PB0
#define Echo PBin(1) // PB1

#define Trig_2 PAout(6) // PA6
#define Echo_2 PAin(7) // PA7

#define Trig_3 PAout(4) // PA4
#define Echo_3 PAin(5) // PA5






void HCSR04_Init(u16 arr,u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//使能TIM2时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA,ENABLE);//使能GPIOA/GPIOB时钟

    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;//下拉输入
    GPIO_Init(GPIOB,&GPIO_InitStructure);
    GPIO_ResetBits(GPIOB,GPIO_Pin_1);//PB1 下拉

    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);//PB0 推挽输出

	
	
    //初始化定时器 2 TIM2
    TIM_TimeBaseStructure.TIM_Period = arr; //设定计数器自动重装值
    TIM_TimeBaseStructure.TIM_Prescaler =psc; //预分频器
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //初始化 TIM2


}





//一号超声波 前方
float hsr04_get(void)
{
	int rate_time =0;
	uint16_t cnt=0;
	float dis=0;

	//发出起始信号
	Trig=0;
	DelayUs(10);             
	Trig=1;
	DelayUs(15);            	 	 //输入一个10us的高电平
	Trig=0;
	
	while(Echo == 0);        		  //超声波发射出去
	TIM_Cmd(TIM2 ,ENABLE); 			 //开启定时器
	while(Echo == 1)        		 //超声波反射回来,来回时间不超过20ms，单程距离不超过3.4m
	{
		DelayUs(20);
		rate_time ++;
		if(rate_time>=1000)
			break;	
	}
	TIM_Cmd(TIM2 ,DISABLE); 		 //关闭定时器

	
	cnt = TIM_GetCounter(TIM2);		//获取定时器的计数值
	dis = ((float)cnt) / 58 ;    	//单位：cm
	TIM2->CNT = 0;

	return dis;		
}

//二号超声波 左方
float hsr04_get_2(void)
{
	int rate_time =0;
	uint16_t cnt=0;
	float dis=0;

	//发出起始信号
	Trig_2=0;
	DelayUs(10);             
	Trig_2=1;
	DelayUs(15);            	 	 //输入一个10us的高电平
	Trig_2=0;
	
	while(Echo_2 == 0);        		  //超声波发射出去
	TIM_Cmd(TIM2 ,ENABLE); 			 //开启定时器
	while(Echo_2 == 1)        		 //超声波反射回来,来回时间不超过20ms，单程距离不超过3.4m
	{
		DelayUs(20);
		rate_time ++;
		if(rate_time>=1000)
			break;	
	}
	TIM_Cmd(TIM2 ,DISABLE); 		 //关闭定时器

	
	cnt = TIM_GetCounter(TIM2);		//获取定时器的计数值
	dis = ((float)cnt) / 58 ;    	//单位：cm
	TIM2->CNT = 0;

	return dis;		
}


//三号超声波 右方
float hsr04_get_3(void)
{
	int rate_time =0;
	uint16_t cnt=0;
	float dis=0;

	//发出起始信号
	Trig_3=0;
	DelayUs(10);             
	Trig_3=1;
	DelayUs(15);            	 	 //输入一个10us的高电平
	Trig_3=0;
	
	while(Echo_3 == 0);        		  //超声波发射出去
	TIM_Cmd(TIM2 ,ENABLE); 			 //开启定时器
	while(Echo_3 == 1)        		 //超声波反射回来,来回时间不超过20ms，单程距离不超过3.4m
	{
		DelayUs(20);
		rate_time ++;
		if(rate_time>=1000)
			break;	
	}
	TIM_Cmd(TIM2 ,DISABLE); 		 //关闭定时器

	
	cnt = TIM_GetCounter(TIM2);		//获取定时器的计数值
	dis = ((float)cnt) / 58 ;    	//单位：cm
	TIM2->CNT = 0;

	return dis;		
}



