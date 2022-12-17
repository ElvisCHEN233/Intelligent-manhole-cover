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

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//ʹ��TIM2ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA,ENABLE);//ʹ��GPIOA/GPIOBʱ��

    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;//��������
    GPIO_Init(GPIOB,&GPIO_InitStructure);
    GPIO_ResetBits(GPIOB,GPIO_Pin_1);//PB1 ����

    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);//PB0 �������

	
	
    //��ʼ����ʱ�� 2 TIM2
    TIM_TimeBaseStructure.TIM_Period = arr; //�趨�������Զ���װֵ
    TIM_TimeBaseStructure.TIM_Prescaler =psc; //Ԥ��Ƶ��
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //��ʼ�� TIM2


}





//һ�ų����� ǰ��
float hsr04_get(void)
{
	int rate_time =0;
	uint16_t cnt=0;
	float dis=0;

	//������ʼ�ź�
	Trig=0;
	DelayUs(10);             
	Trig=1;
	DelayUs(15);            	 	 //����һ��10us�ĸߵ�ƽ
	Trig=0;
	
	while(Echo == 0);        		  //�����������ȥ
	TIM_Cmd(TIM2 ,ENABLE); 			 //������ʱ��
	while(Echo == 1)        		 //�������������,����ʱ�䲻����20ms�����̾��벻����3.4m
	{
		DelayUs(20);
		rate_time ++;
		if(rate_time>=1000)
			break;	
	}
	TIM_Cmd(TIM2 ,DISABLE); 		 //�رն�ʱ��

	
	cnt = TIM_GetCounter(TIM2);		//��ȡ��ʱ���ļ���ֵ
	dis = ((float)cnt) / 58 ;    	//��λ��cm
	TIM2->CNT = 0;

	return dis;		
}

//���ų����� ��
float hsr04_get_2(void)
{
	int rate_time =0;
	uint16_t cnt=0;
	float dis=0;

	//������ʼ�ź�
	Trig_2=0;
	DelayUs(10);             
	Trig_2=1;
	DelayUs(15);            	 	 //����һ��10us�ĸߵ�ƽ
	Trig_2=0;
	
	while(Echo_2 == 0);        		  //�����������ȥ
	TIM_Cmd(TIM2 ,ENABLE); 			 //������ʱ��
	while(Echo_2 == 1)        		 //�������������,����ʱ�䲻����20ms�����̾��벻����3.4m
	{
		DelayUs(20);
		rate_time ++;
		if(rate_time>=1000)
			break;	
	}
	TIM_Cmd(TIM2 ,DISABLE); 		 //�رն�ʱ��

	
	cnt = TIM_GetCounter(TIM2);		//��ȡ��ʱ���ļ���ֵ
	dis = ((float)cnt) / 58 ;    	//��λ��cm
	TIM2->CNT = 0;

	return dis;		
}


//���ų����� �ҷ�
float hsr04_get_3(void)
{
	int rate_time =0;
	uint16_t cnt=0;
	float dis=0;

	//������ʼ�ź�
	Trig_3=0;
	DelayUs(10);             
	Trig_3=1;
	DelayUs(15);            	 	 //����һ��10us�ĸߵ�ƽ
	Trig_3=0;
	
	while(Echo_3 == 0);        		  //�����������ȥ
	TIM_Cmd(TIM2 ,ENABLE); 			 //������ʱ��
	while(Echo_3 == 1)        		 //�������������,����ʱ�䲻����20ms�����̾��벻����3.4m
	{
		DelayUs(20);
		rate_time ++;
		if(rate_time>=1000)
			break;	
	}
	TIM_Cmd(TIM2 ,DISABLE); 		 //�رն�ʱ��

	
	cnt = TIM_GetCounter(TIM2);		//��ȡ��ʱ���ļ���ֵ
	dis = ((float)cnt) / 58 ;    	//��λ��cm
	TIM2->CNT = 0;

	return dis;		
}



