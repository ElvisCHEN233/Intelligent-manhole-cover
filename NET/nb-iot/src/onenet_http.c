

#include "stm32f10x.h"    //包含需要的头文件
#include "onenet_http.h"  //包含需要的头文件
#include "stdio.h"        //包含需要的头文件
#include "stdarg.h"		  //包含需要的头文件 
#include "string.h"       //包含需要的头文件
#include "usart.h"
#include "sim7020.h"      //包含需要的头文件
#include "delay.h"        //包含需要的头文件
#include "led.h"          //包含需要的头文件

char RXbuff[1024];        
static char temp[256];
char keytemp[256];
char *ptr;

extern char SIM7020_RX_BUF[512];
extern unsigned int SIM7020_RxCounter;      //定义一个变量，记录串口2总共接收了多少字节的数据

//水位
extern unsigned int water;

//温度         
extern int temper;        

//湿度
extern int humid;

//烟雾浓度
extern u8 smoke;

//井盖状态标志位
extern u8 cover;

/*-------------------------------------------------*/
/*函数名：OneNet服务器 HTTP GET报文                */
/*参  数：device_id： 设备ID                       */
/*参  数：timeout：超时时间（100ms的倍数）         */
/*返回值：0：正确  其他：错误                      */
/*-------------------------------------------------*/
char SIM7020C_OneNetGET(char *device_id,int timeout)
{		
	memset(RXbuff,0,1024);                                                    //清空缓冲区
	memset(temp,0,256);                                                       //清空缓冲区
	memset(keytemp,0,256);                                                    //清空缓冲区
	
	UsartPrintf(USART_DEBUG, "准备创建HTTP主机\r\n");                                        //串口输出信息
	if(SIM7020_Send_Cmd("AT+CHTTPCREATE=\"http://api.heclouds.com\"",100)){   //超时单位100ms，超时时间10s
		UsartPrintf(USART_DEBUG, "创建HTTP主机失败，准备重启\r\n");                          //串口输出信息
		return 1;                                                             //返回1
	}else UsartPrintf(USART_DEBUG, "创建HTTP主机成功\r\n");                                  //串口输出信息
	
	UsartPrintf(USART_DEBUG, "准备连接服务器\r\n");                                          //串口输出信息
	if(SIM7020_Send_Cmd("AT+CHTTPCON=0",100)){                                //超时单位100ms，超时时间10s
		UsartPrintf(USART_DEBUG, "连接服务器失败，准备重启\r\n");                            //串口输出信息
		return 2;                                                             //返回2
	}else UsartPrintf(USART_DEBUG, "连接服务器成功\r\n");                                    //串口输出信息
	
	sprintf(temp,"api-key:%s\r\n",API_KEY);                                              //构建数据
	SIM7020_Hex_to_Str(temp,strlen(temp),keytemp,256);                                   //转换数据
	sprintf(temp,"AT+CHTTPSEND=0,0,\"/devices/%s/datapoints\",%s",device_id,keytemp);    //构建数据
	UsartPrintf(USART_DEBUG, "准备发送GET请求\r\n");                                     //串口输出信息
	UsartPrintf(USART_DEBUG, "发送的内容为：\r\n"); 
	UsartPrintf(USART_DEBUG, temp); 
	if(SIM7020_Send_Cmd(temp,100)){                                                      //超时单位100ms，超时时间10s
		UsartPrintf(USART_DEBUG, "发送GET请求失败，准备重启\r\n");                                      //串口输出信息
		return 3;                                                                        //返回3
	}else UsartPrintf(USART_DEBUG, "发送GET请求成功\r\n");                                              //串口输出信息
	
	while(timeout--){                                                                    //等待超时时间到0
		DelayMs(100);                                                                   //延时100ms
		if(strstr(SIM7020_RX_BUF,"+CHTTPNMIC:"))                                         //如果接收到OK表示指令成功
			break;       						                                         //主动跳出while循环		
	}
	UsartPrintf(USART_DEBUG, "\r\n");                                                                   //串口输出信息
	if(timeout<=0)return 4;                                                              //如果timeout<=0，说明超时时间到零了，也没能收到+CHTTPNMIC:，返回4，表示错误
	UsartPrintf(USART_DEBUG, "接收数据成功\r\n");                                                       //串口输出信息
	ptr = strstr(SIM7020_RX_BUF,"+CHTTPNMIC:");                                          //搜索+CHTTPNMIC:
	memset(keytemp,0,256);                                                               //清空缓冲区
	sscanf(ptr,"%[^,],%[^,],%[^,],%[^,],%[^\r]",temp,temp,temp,temp,keytemp);            //格式化搜索保存数据
	SIM7020_Str_to_Hex(keytemp,strlen(keytemp),RXbuff,1024);                             //转换数据
	UsartPrintf(USART_DEBUG, "%s\r\n",RXbuff);                                                          //串口输出信息
	
	ptr = strstr(RXbuff,"\"id\":\"text_aaa\"");                                          //搜索 "id":"switch_1" 查询开关1状态
	if(ptr!=NULL)
	{                                                                       //如果搜索到了，进入if
		UsartPrintf(USART_DEBUG, "查询开关1状态正确\r\n");//串口提示数据
		UsartPrintf(USART_DEBUG, "采集到的数值为：%d \r\n",*(ptr-4));
		if(*(ptr-4) == '0') 
		{
//			LED1_OFF;//如果是0，关闭LED1  
		}
                                                 
		else 
		{
//			LED1_ON;//反之是1，打开LED1 
		}
                                                                   							
	}
	else 
		UsartPrintf(USART_DEBUG, "查询开关1状态失败\r\n");                                            //串口提示数据
	
	UsartPrintf(USART_DEBUG, "准备断开连接\r\n");                                                       //串口输出信息
	if(SIM7020_Send_Cmd("AT+CHTTPDISCON=0",100)){                                        //超时单位100ms，超时时间10s
		UsartPrintf(USART_DEBUG, "断开连接失败，准备重启\r\n");                                         //串口输出信息
		return 5;                                                                        //返回5
	}else UsartPrintf(USART_DEBUG, "断开连接成功\r\n");                                                 //串口输出信息
	
	UsartPrintf(USART_DEBUG, "准备释放销毁HTTP\r\n");                                                   //串口输出信息
	if(SIM7020_Send_Cmd("AT+CHTTPDESTROY=0",100)){                                       //超时单位100ms，超时时间10s
		UsartPrintf(USART_DEBUG, "释放销毁HTTP失败，准备重启\r\n");                                     //串口输出信息
		return 6;                                                                        //返回6
	}else UsartPrintf(USART_DEBUG, "释放销毁HTTP成功\r\n");                                             //串口输出信息
		
	return 0;                                                                            //正确，返回0
}



/*
* 描述：数据流封装
*/
void OneNet_FillBuf(char *buf)
{
	
	char text[24];
	char buf1[128];
	
	memset(text, 0, sizeof(text));
	memset(buf1, 0, sizeof(buf1));
	
	strcpy(buf1, "{");
	
	memset(text, 0, sizeof(text));
	sprintf(text, "\"water\":%d,", water);
	strcat(buf1, text);
	
	memset(text, 0, sizeof(text));
	sprintf(text, "\"temper\":%d,", temper);
	strcat(buf1, text);
	
	memset(text, 0, sizeof(text));
	sprintf(text, "\"humid\":%d,", humid);
	strcat(buf1, text);
	
	memset(text, 0, sizeof(text));
	sprintf(text, "\"smoke\":%d,", smoke);
	strcat(buf1, text);
	
	memset(text, 0, sizeof(text));
	sprintf(text, "\"cover\":%d", cover);
	strcat(buf1, text);
	
	strcat(buf1, "}");
	
	sprintf(buf, "POST /devices/%s/datapoints?type=3 HTTP/1.1\r\napi-key:%s\r\nHost:api.heclouds.com\r\n"
					"Content-Length:%d\r\n\r\n",
	
					DEVID, APIKEY, strlen(buf1));
					
	strcat(buf, buf1);

}



/*
* 描述：数据发送
*/
void OneNet_SendData(void)
{
	
	char buf[256];
	
	memset(buf, 0, sizeof(buf));
	
	OneNet_FillBuf(buf);									//封装数据流
	
	Sim7020_SendData((unsigned char *)buf, strlen(buf));	//上传数据
	
}


/*
* 描述：平台返回数据检测
*/
void OneNet_RevPro(unsigned char *dataPtr)
{

	if(strstr((char *)dataPtr, "CLOSED"))
	{
		UsartPrintf(USART_DEBUG, "TCP CLOSED\r\n");
	}
	else
	{
		//这里用来检测是否发送成功
		if(strstr((char *)dataPtr, "succ"))
		{
			UsartPrintf(USART_DEBUG, "Tips:	Send OK\r\n");
		}
		else
		{
			UsartPrintf(USART_DEBUG, "Tips:	Send Err\r\n");
		}
	}
	
	Sim7020_Clear();

}




