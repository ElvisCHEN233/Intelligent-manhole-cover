#include "timer.h"


//************************************************************************************************
//**名      称：TIM3_PWM_Init
//**说      明：舵机控制初始化
//**形      参：PWM_value：0~10，0，输出高电平
//**返  回  值：无
//************************************************************************************************
void TIM1_PWM_Init(u16 arr,u16 psc)

{  

     GPIO_InitTypeDef GPIO_InitStructure;

    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

    TIM_OCInitTypeDef  TIM_OCInitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);// 

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  //使能GPIO外设时钟使能

   //设置该引脚为复用输出功能,输出TIM1 CH1的PWM脉冲波形

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //TIM_CH1

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出

    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOA, &GPIO_InitStructure);

  TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值  80K

  TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  不分频

  TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim

  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式

  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //根据     TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2

  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能

  TIM_OCInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值

  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高

  TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx

  TIM_CtrlPWMOutputs(TIM1,ENABLE);  //MOE 主输出使能 

  TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH1预装载使能     

  TIM_ARRPreloadConfig(TIM1, ENABLE); //使能TIMx在ARR上的预装载寄存器

  TIM_Cmd(TIM1, ENABLE);  //使能TIM1

}

//*****************************************************************************************************
//*函数名： for steering
//*函数功能：0~19999
//*参数：
//*备注：
//*****************************************************************************************************
void Control_PWM_DJ(u16 PWM_value)
{
	TIM3->CCR4 = PWM_value;
} 

