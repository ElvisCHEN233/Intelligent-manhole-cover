//单片机头文件
#include "stm32f10x.h"


//硬件驱动
#include "delay.h"
#include "led.h"
#include "timer.h"
#include "hsr04.h"
#include "gpio.h"
#include "adc.h"
#include "dht11.h"
#include "MPU6050.h"    
#include "usart.h"
#include "sim7020.h"     
#include "onenet_http.h"   

//C库
#include <string.h>
#include <stdio.h>


//水位
unsigned int water = 0;

//温度         
int temper = 0;         

//湿度
int humid = 0;

//烟雾浓度
u8 smoke = 0;

//井盖状态标志位
u8 cover = 0;


/*  临时变量  */
extern char SIM7020_RX_BUF[512]; 
//X,Y,Z加速度
short A_X,A_Y,A_Z;	
char buf_temp[128];	
unsigned char Usart3Len;	//usart3接收的数据长度
char Usart3Buf[512];	//usart3接收缓存	
char  Sta_flag = 1;        //0：配置完成处理数据状态   1：AT指令配置模块状态
char res;
/*
************************************************************
*	函数名称：	Hardware_Init
*
*	函数功能：	硬件初始化
*
*	入口参数：	无
*
*	返回参数：	无
*
*	说明：		初始化单片机功能以及外接设备
************************************************************
*/
void Hardware_Init(void)
{
	SystemInit();//配置系统时钟为72M	
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//中断控制器分组设置

	Delay_Init();									//systick初始化
		
	Usart1_Init(115200);							//串口1，串口
	
	Usart2_Init(115200);							//串口2，nb-iot
	
	Led_Init();										//LED初始化
	
	Gpio_Init();									//IO口初始化
	
	HCSR04_Init(0XFFFF,72-1);   					//超声波初始化 每隔1us计数一次，总共计数65536次
	
	DHT11_Init();									//温湿度传感器初始化
	
	Adc_Init();										//ADC采集	

	Init_MPU6050();									//初始化MPU6050
	
	SIM7020_Init();									//nb-iot初始化                   
	

	UsartPrintf(USART_DEBUG, " Hardware init OK\r\n");
	
	Light_Start();	
}

/*
************************************************************
*	函数名称：	main
*
*	函数功能：	
*
*	入口参数：	无
*
*	返回参数：	0
*
*	说明：		
************************************************************
*/
int main(void)
{
	unsigned short timeCount = 0;	//发送间隔变量
	unsigned char *dataPtr = NULL;
	char buf[256];
	
	Hardware_Init();				//初始化外围硬件
	

	
	
	
	while(1)	
	{
		
		if(++timeCount >= 100)									//时间间隔4s
		{
/********************************** 开始数据采集 ****************************************************************/		
			//1.采集XYZ加速度
			READ_MPU6050();	         //读取MPU6050数据
			
			//2.判断井盖是否打开
			if(A_Z <= 50)
			{
				cover = 1;
				UsartPrintf(USART_DEBUG, "井盖已经被打开\r\n");
			}
			else
				cover = 0;
			
			//3.采集水位
			water = (int)hsr04_get();

			//4.采集温度湿度	
			DHT11_Read_Data(&temper,&humid); 

			//5.烟雾浓度
			smoke =  (float)Get_Adc_Average(0,20)/4096*100;
			
		
/********************************** 数据采集结束,屏幕显示出来**************************************************/
			
			//1.串口打印 

			UsartPrintf(USART_DEBUG, "加速度：A_X:%d  A_Y:%d  A_Z:%d \r\n",A_X,A_Y,A_Z);
			
			UsartPrintf(USART_DEBUG, "水位: %d cm\r\n",water);
					
			UsartPrintf(USART_DEBUG, "温度: %d `C \r\n",temper);
						
			UsartPrintf(USART_DEBUG, "湿度: %d %%\r\n",humid);
			
			UsartPrintf(USART_DEBUG, "烟雾: %d %%\r\n",smoke);
			

/********************************** 数据显示结束，开始数据上传 *************************************************/	
			UsartPrintf(USART_DEBUG, "OneNet_SendData\r\n");
			OneNet_SendData();
			Sim7020_Clear();

			Led_test(LED_ON);//亮灯提醒
			timeCount = 0;
		}
		
		
		dataPtr = Sim7020_GetIPD(0);
		if(dataPtr != NULL)
			OneNet_RevPro(dataPtr);
		if(strstr(SIM7020_RX_BUF, "CLOSED"))
		{
			SIM7020_Init();									//nb-iot初始化    
		}
		
		
		DelayXms(40);
		Led_test(LED_OFF);
	}

}







