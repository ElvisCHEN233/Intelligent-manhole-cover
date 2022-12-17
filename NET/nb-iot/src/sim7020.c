

#include "stm32f10x.h"  //包含需要的头文件

#include "sim7020.h"    //包含需要的头文件
#include "delay.h"      //包含需要的头文件
#include "usart.h"
#include <string.h>
#include <stdio.h>

//unsigned char sim7020_buf[256];
unsigned short sim7020_cntPre = 0;

extern char SIM7020_RX_BUF[512];
extern unsigned int SIM7020_RxCounter;      //定义一个变量，记录串口2总共接收了多少字节的数据
extern char  Sta_flag;//0：配置完成处理数据状态   1：AT指令配置模块状态

/*-------------------------------------------------*/
/*函数名：初始化sim7020开关机IO                    */
/*参  数：无                                       */
/*返回值：无                                       */
/*-------------------------------------------------*/
void SIM_PwrKeyInit(void)
{    	 
//	GPIO_InitTypeDef GPIO_InitStructure;                     //定义一个设置GPIO的变量
//	
//	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);      //使能GPIOB端口时钟
//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;                //准备设置PB0
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;            //输出模式
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;           //推免输出
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_400KHz;       //400K速度
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;           //下拉
//	GPIO_Init(GPIOB, &GPIO_InitStructure);                   //设置PB0	
//	POWER_KEY(0);                                            //初始化的时候设置成低电平
}
/*-------------------------------------------------*/
/*函数名：初始化sim7020开关机状态IO                */
/*参  数：无                                       */
/*返回值：无                                       */
/*-------------------------------------------------*/
void SIM_PwrStaInit(void)
{    	 
//	GPIO_InitTypeDef GPIO_InitStructure;                     //定义一个设置GPIO的变量
//	
//	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);      //使能GPIOB端口时钟
//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;                //准备设置PB1
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;             //输入模式
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_400KHz;       //400K速度
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;           //下拉
//	GPIO_Init(GPIOB, &GPIO_InitStructure);                   //设置PB1	
}
/*-------------------------------------------------*/
/*函数名：初始化sim7020复位IO                       */
/*参  数：无                                       */
/*返回值：无                                       */
/*-------------------------------------------------*/
void SIM_RstKeyInit(void)
{    	 
//	GPIO_InitTypeDef GPIO_InitStructure;                     //定义一个设置GPIO的变量
//	
//	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);      //使能GPIO7端口时钟
//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;                //准备设置PA7
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;             //输入模式
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_400KHz;       //400K速度
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;           //下拉
//	GPIO_Init(GPIOA, &GPIO_InitStructure);                   //设置PA7	
//	RESET_KEY(0);                                            //初始化的时候设置成低电平
}
/*-------------------------------------------------*/
/*函数名：开机                                     */
/*参  数：无                                       */
/*返回值：无                                       */
/*------------------------------------------------*/
char SIM_PowerON(void)
{
//	SIM_PwrKeyInit();   //初始化sim7020开关机IO
//	SIM_PwrStaInit();   //初始化sim7020开关机状态IO 
//	SIM_RstKeyInit();   //初始化sim7020复位IO
//	
//	if(POWER_STA==0){   							           //如果PB1是低电平，表示目前处于关机状态		
//		UsartPrintf(USART_DEBUG, "\r\n目前处于关机状态，准备开机\r\n");         //串口输出信息
//		POWER_KEY(1);                                          //先拉高PB0
//		DelayMs(800);										   //延时
//		POWER_KEY(0);										   //再拉低PB0，开机
//	}else{                                                     //反之PB1是高电平，表示目前处于开机状态
//		UsartPrintf(USART_DEBUG, "\r\n目前处于开机状态，准备重启\r\n");         //串口输出信息		
//		POWER_KEY(1);                                          //先拉高PB0
//		DelayMs(1200);										   //延时
//		POWER_KEY(0);										   //再拉低PB0		
//		DelayMs(2000);										   //延时
//		POWER_KEY(1);                                          //先拉高PB0
//		DelayMs(800);										   //延时
//		POWER_KEY(0);										   //再拉低PB0，开机
//	}
//	DelayMs(2000);								    		   //延时
//	if(POWER_STA){                                             //如果PB1是低电平，表示开机或是重启成功
//		UsartPrintf(USART_DEBUG, "开机成功\r\n");                             //串口输出信息
//	}else{												       //反之PB1是高电平，表示开始或是重启失败
//		UsartPrintf(USART_DEBUG, "开机失败\r\n"); 							   //串口输出信息
//		return 1;                                              //返回1，表示失败
//	}	
//	return 0;                                                  //返回0，表示成功
}
/*-------------------------------------------------*/
/*函数名：AT测试指令                                */
/*参  数：timeout：超时时间（100ms的倍数）          */
/*返回值：0：正确   其他：错误                      */
/*-------------------------------------------------*/
char SIM7020_ATTest_Cmd(int timeout)
{
	while(timeout--){                                  //等待超时时间到0
		SIM7020_RxCounter=0;                           //7020接收数据量变量清零                        
		memset(SIM7020_RX_BUF,0,SIM7020_RXBUFF_SIZE);  //清空7020接收缓冲区 	
		UsartPrintf(USART2, "AT\r\n");                      //发送指令
		UsartPrintf(USART_DEBUG, "%d ",timeout);                      //串口输出现在的剩余超时时间
		DelayMs(100);                                 //延时100ms
		if(strstr(SIM7020_RX_BUF,"OK"))                //如果接收到OK表示指令成功
			break;       						       //主动跳出while循环		
	}
	UsartPrintf(USART_DEBUG, "\r\n");                                 //串口输出信息
	if(timeout<=0)return 1;                            //如果timeout<=0，说明超时时间到零了，也没能收到OK，返回1，表示错误
	return 0;		         				           //返回0，正确，说明收到OK，通过break主动跳出while
}
/*-------------------------------------------------*/
/*函数名：发送AT指令                               */
/*参  数：cmd：AT指令                              */
/*参  数：timeout：超时时间（100ms的倍数）         */
/*返回值：0：正确   其他：错误                     */
/*-------------------------------------------------*/
char SIM7020_Send_Cmd(char *cmd, int timeout)
{
	SIM7020_RxCounter=0;                           //7020接收数据量变量清零                        
	memset(SIM7020_RX_BUF,0,SIM7020_RXBUFF_SIZE);  //清空7020接收缓冲区 	
	UsartPrintf(USART2, "%s\r\n",cmd);                  //发送指令
	
	while(timeout--){                              //等待超时时间到0
		UsartPrintf(USART_DEBUG, "%d ",timeout);                  //串口输出现在的剩余超时时间
		DelayMs(1000);                             //延时100ms
		if(strstr(SIM7020_RX_BUF,"OK"))            //如果接收到OK表示指令成功
			break;       						   //主动跳出while循环		
	}
	UsartPrintf(USART_DEBUG, "\r\n");                             //串口输出信息
	if(timeout<=0)return 1;                        //如果timeout<=0，说明超时时间到零了，也没能收到OK，返回1，表示错误
	return 0;		         				       //返回0，正确，说明收到OK，通过break主动跳出while
}
/*-------------------------------------------------*/
/*函数名：检查SIM卡状态指令                          */
/*参  数：timeout：超时时间（1s的倍数）              */
/*返回值：0：正确   其他：错误                      */
/*-------------------------------------------------*/
char SIM7020_CPIN_Cmd(int timeout)
{
	SIM7020_RxCounter=0;                           //7020接收数据量变量清零                        
	memset(SIM7020_RX_BUF,0,SIM7020_RXBUFF_SIZE);  //清空7020接收缓冲区 	
	UsartPrintf(USART2, "AT+CPIN?\r\n");                //发送指令
	while(timeout--){                              //等待超时时间到0
		UsartPrintf(USART_DEBUG, "%d ",timeout);                  //串口输出现在的剩余超时时间
		DelayMs(1000);                            //延时1s
		if(strstr(SIM7020_RX_BUF,"READY"))         //如果接收到READY表示指令成功
			break;       						   //主动跳出while循环		
	}
	UsartPrintf(USART_DEBUG, "\r\n");                             //串口输出信息
	if(timeout<=0)return 1;                        //如果timeout<=0，说明超时时间到零了，也没能收到READY，返回1，表示错误
	return 0;		         				       //返回0，正确，说明收到READY，通过break主动跳出while
}
/*-------------------------------------------------*/
/*函数名：检查网络附着指令                          */
/*参  数：timeout：超时时间（1s的倍数）             */
/*返回值：0：正确   其他：错误                      */
/*-------------------------------------------------*/
char SIM7020_CGREG_Cmd(int timeout)
{
	while(timeout--){                                  //等待超时时间到0
		SIM7020_RxCounter=0;                           //7020接收数据量变量清零                        
		memset(SIM7020_RX_BUF,0,SIM7020_RXBUFF_SIZE);  //清空7020接收缓冲区 	
		UsartPrintf(USART2, "AT+CGREG?\r\n");               //发送指令
		UsartPrintf(USART_DEBUG, "%d ",timeout);                      //串口输出现在的剩余超时时间
		DelayMs(1000);                                //延时1s
		if(strstr(SIM7020_RX_BUF,"+CGREG: 0,1"))       //如果接收到+CGREG: 0,1表示指令成功
			break;       						       //主动跳出while循环		
	}
	UsartPrintf(USART_DEBUG, "\r\n");                                 //串口输出信息
	if(timeout<=0)return 1;                            //如果timeout<=0，说明超时时间到零了，也没能收到+CGREG: 0,1，返回1，表示错误
	return 0;		         				           //返回0，正确，说明收到+CGREG: 0,1，通过break主动跳出while
}
/*-------------------------------------------------*/
/*函数名：检查PDN激活状态                          */
/*参  数：timeout：超时时间（1s的倍数）             */
/*返回值：0：正确   其他：错误                      */
/*-------------------------------------------------*/
char SIM7020_CGACT_Cmd(int timeout)
{
	while(timeout--){                                  //等待超时时间到0
		SIM7020_RxCounter=0;                           //7020接收数据量变量清零                        
		memset(SIM7020_RX_BUF,0,SIM7020_RXBUFF_SIZE);  //清空7020接收缓冲区 	
		UsartPrintf(USART2, "AT+CGACT?\r\n");               //发送指令
		UsartPrintf(USART_DEBUG, "%d ",timeout);                      //串口输出现在的剩余超时时间
		DelayMs(1000);                                //延时1s
		if(strstr(SIM7020_RX_BUF,"+CGACT: 1,1"))       //如果接收到+CGACT: 1,1表示指令成功
			break;       						       //主动跳出while循环		
	}
	UsartPrintf(USART_DEBUG, "\r\n");                                 //串口输出信息
	if(timeout<=0)return 1;                            //如果timeout<=0，说明超时时间到零了，也没能收到+CGACT: 1,1，返回1，表示错误
	return 0;		         				           //返回0，正确，说明收到+CGACT: 1,1，通过break主动跳出while
}
/*-------------------------------------------------*/
/*函数名：检查信号质量指令                          */
/*参  数：timeout：超时时间（100ms的倍数）          */
/*返回值：0：正确   其他：错误                      */
/*-------------------------------------------------*/
char SIM7020_CSQ_Cmd(int timeout)
{
	char temp[20],csq[20];                         //临时缓冲区
	
	SIM7020_RxCounter=0;                           //7020接收数据量变量清零                        
	memset(SIM7020_RX_BUF,0,SIM7020_RXBUFF_SIZE);  //清空7020接收缓冲区 	
	memset(temp,0,20);                             //清空缓冲区
    memset(csq,0,20);                              //清空缓冲区 	
	
	UsartPrintf(USART2, "AT+CSQ\r\n");                  //发送指令
	while(timeout--){                              //等待超时时间到0
		UsartPrintf(USART_DEBUG, "%d ",timeout);                  //串口输出现在的剩余超时时间
		DelayMs(100);                             //延时100ms
		if(strstr(SIM7020_RX_BUF,"OK"))            //如果接收到OK表示指令成功
			break;       						   //主动跳出while循环
	}
	UsartPrintf(USART_DEBUG, "\r\n");                             //串口输出信息
	if(timeout<=0) return 99;                      //如果timeout<=0，说明超时时间到零了，也没能收到OK，返回99，表示错误
	else{                                          //反之，表示正确，说明收到OK，通过break主动跳出while
		sscanf(SIM7020_RX_BUF,"%[^ ] %[^,],%[^\r]",temp,csq,temp);   //格式化搜索，信号质量
	}
	return SIM7020_StrNum_to_HexNum(csq,strlen(csq));		         				       
}
/*-------------------------------------------------*/
/*函数名：查询网络下发APN和分配的IP地址指令        */
/*参  数：timeout：超时时间（100ms的倍数）         */
/*返回值：0：正确   其他：错误                     */
/*-------------------------------------------------*/
char SIM7020_CGCONTRDP_Cmd(int timeout)
{
	char temp[40],apn[40],ip[40];                  //临时缓冲区
	
	SIM7020_RxCounter=0;                           //7020接收数据量变量清零                        
	memset(SIM7020_RX_BUF,0,SIM7020_RXBUFF_SIZE);  //清空7020接收缓冲区 	
	memset(temp,0,40);                             //清空缓冲区
    memset(apn,0,40);                              //清空缓冲区 	
	memset(ip,0,40);                               //清空缓冲区	
	
	UsartPrintf(USART2, "AT+CGCONTRDP\r\n");            //发送指令
	while(timeout--){                              //等待超时时间到0
		UsartPrintf(USART_DEBUG, "%d ",timeout);                  //串口输出现在的剩余超时时间
		DelayMs(100);                             //延时100ms
		if(strstr(SIM7020_RX_BUF,"OK"))            //如果接收到OK表示指令成功
			break;       						   //主动跳出while循环
	}
	UsartPrintf(USART_DEBUG, "\r\n");                             //串口输出信息
	if(timeout<=0)return 1;                        //如果timeout<=0，说明超时时间到零了，也没能收到OK，返回1，表示错误
	else{                                          //反之，表示正确，说明收到OK，通过break主动跳出while
		sscanf(SIM7020_RX_BUF,"%[^,],%[^,],%[^,],%[^\r]",temp,temp,apn,ip);    //格式化搜索，apn和ip信息
		UsartPrintf(USART_DEBUG, "APN：%s\r\n",apn);              //串口输出信息
		UsartPrintf(USART_DEBUG, "ip和子网掩码：%s\r\n",ip);      //串口输出信息
	}
	return 0;		         				       //返回0，正确，
}
/*-------------------------------------------------*/
/*函数名：锁定波特率指令                           */
/*参  数：bound：波特率                           */
/*参  数：timeout：超时时间（100ms的倍数）          */
/*返回值：0：正确   其他：错误                      */
/*-------------------------------------------------*/
char SIM7020_IPR_Cmd(int bound, int timeout)
{
	SIM7020_RxCounter=0;                           //7020接收数据量变量清零                        
	memset(SIM7020_RX_BUF,0,SIM7020_RXBUFF_SIZE);  //清空7020接收缓冲区 	
	UsartPrintf(USART2, "AT+IPR=%d\r\n",bound);         //发送指令
	while(timeout--){                              //等待超时时间到0
		UsartPrintf(USART_DEBUG, "%d ",timeout);                  //串口输出现在的剩余超时时间
		DelayMs(100);                             //延时100ms
		if(strstr(SIM7020_RX_BUF,"OK"))            //如果接收到OK表示指令成功
			break;       						   //主动跳出while循环
	}
	UsartPrintf(USART_DEBUG, "\r\n");                             //串口输出信息
	if(timeout<=0)return 1;                        //如果timeout<=0，说明超时时间到零了，也没能收到OK，返回1，表示错误
	return 0;		         				       //返回0，正确，说明收到OK，通过break主动跳出while
}
/*-------------------------------------------------*/
/*函数名：关闭PSM模式指令                           */
/*参  数：timeout：超时时间（1s的倍数）             */
/*返回值：0：正确   其他：错误                      */
/*-------------------------------------------------*/
char SIM7020_PSM_OFF(int timeout)
{
	while(timeout--){                                  //等待超时时间到0
		SIM7020_RxCounter=0;                           //7020接收数据量变量清零                        
		memset(SIM7020_RX_BUF,0,SIM7020_RXBUFF_SIZE);  //清空7020接收缓冲区 	
		UsartPrintf(USART2, "AT+CPSMS=0\r\n");              //发送指令
		UsartPrintf(USART_DEBUG, "%d ",timeout);                      //串口输出现在的剩余超时时间
		DelayMs(1000);                                //延时1s
		if(strstr(SIM7020_RX_BUF,"OK"))                //如果接收到OK表示指令成功
			break;       						       //主动跳出while循环		
	}
	UsartPrintf(USART_DEBUG, "\r\n");                                 //串口输出信息
	if(timeout<=0)return 1;                            //如果timeout<=0，说明超时时间到零了，也没能收到OK，返回1，表示错误
	return 0;		         				           //返回0，正确，说明收到OK，通过break主动跳出while
}
/*-------------------------------------------------*/
/*函数名：关闭eDRX模式指令                          */
/*参  数：timeout：超时时间（1s的倍数）             */
/*返回值：0：正确   其他：错误                      */
/*-------------------------------------------------*/
char SIM7020_eDRX_OFF(int timeout)
{
	while(timeout--){                                  //等待超时时间到0
		SIM7020_RxCounter=0;                           //7020接收数据量变量清零                        
		memset(SIM7020_RX_BUF,0,SIM7020_RXBUFF_SIZE);  //清空7020接收缓冲区 	
		UsartPrintf(USART2, "AT+CEDRXS=0\r\n");             //发送指令
		UsartPrintf(USART_DEBUG, "%d ",timeout);                      //串口输出现在的剩余超时时间
		DelayMs(1000);                                //延时1s
		if(strstr(SIM7020_RX_BUF,"OK"))                //如果接收到OK表示指令成功
			break;       						       //主动跳出while循环		
	}
	UsartPrintf(USART_DEBUG, "\r\n");                                 //串口输出信息
	if(timeout<=0)return 1;                            //如果timeout<=0，说明超时时间到零了，也没能收到OK，返回1，表示错误
	else return 0;		         				       //返回0，正确，说明收到OK，通过break主动跳出while
}

/*-------------------------------------------------*/
/*函数名：发送连接服务器命                         */
/*参  数：timeout：超时时间（1s的倍数）             */
/*返回值：0：正确   其他：错误                      */
/*-------------------------------------------------*/
char SIM7020_OneNET_CONN(int timeout)
{
	while(timeout--){                                  //等待超时时间到0
		SIM7020_RxCounter=0;                           //7020接收数据量变量清零                        
		memset(SIM7020_RX_BUF,0,SIM7020_RXBUFF_SIZE);  //清空7020接收缓冲区 	
		UsartPrintf(USART2, ESP8266_ONENET_INFO);             //发送指令
		UsartPrintf(USART_DEBUG, "%d ",timeout);                      //串口输出现在的剩余超时时间
		DelayMs(1000);                                //延时1s
		if(strstr(SIM7020_RX_BUF,"CONNECT"))                //如果接收到OK表示指令成功
			break;       						       //主动跳出while循环		
	}
	UsartPrintf(USART_DEBUG, "\r\n");                                 //串口输出信息
	if(timeout<=0)return 1;                            //如果timeout<=0，说明超时时间到零了，也没能收到OK，返回1，表示错误
	else return 0;		         				       //返回0，正确，说明收到OK，通过break主动跳出while
}

/*-------------------------------------------------*/
/*函数名：SIM7020 初始化                            */
/*参  数：无                                        */
/*返回值：无                                       */
/*-------------------------------------------------*/
char SIM7020_Init(void)
{
	char num,csq;
	u8 return_value;
	
	SIM_PowerON();                                            //开机或重启
	
	//1.AT -- OK
	UsartPrintf(USART_DEBUG, "发送测试指令，等待串口正常... ...\r\n");       //串口输出信息
	if(SIM7020_ATTest_Cmd(50)){                               //超时单位100ms，超时时间5s
		UsartPrintf(USART_DEBUG, "测试指令超时，准备重启\r\n");              //串口输出信息
		return_value = 1;                                             //返回1
	}else UsartPrintf(USART_DEBUG, "测试指令成功\r\n");                      //串口输出信息
	
	//2.AT+CPIN? -- READY	
	UsartPrintf(USART_DEBUG, "准备检查SIM卡状态... ...\r\n");                //串口输出信息
	if(SIM7020_CPIN_Cmd(10)){                                 //超时单位1s，超时时间10s
		UsartPrintf(USART_DEBUG, "检查SIM卡状态超时，准备重启\r\n");         //串口输出信息
		return_value = 2;                                             //返回2
	}else UsartPrintf(USART_DEBUG, "SIM卡状态正常\r\n");                     //串口输出信息
	
	//3.AT+CSQ -- OK	
	num = 5;                                                  //最多查询5次
	while(num--){                                             //循环查询
		UsartPrintf(USART_DEBUG, "准备检查信号质量... ...\r\n");             //串口输出信息
		csq = SIM7020_CSQ_Cmd(50);                            //超时单位100ms，超时时间5s
		if((csq>0)&&(csq<=31)){                               //按到信号范围是否正确
			UsartPrintf(USART_DEBUG, "信号强度范围0~31,99表示无信号\r\n");   //串口输出信息
			UsartPrintf(USART_DEBUG, "信号强度：%d\r\n",csq);                //串口输出信息
			break;                                            //跳出while
		}
		DelayMs(1000);                                       //延时1s
	}
	if(num<=0)return_value = 3;                                       //如果num<=0，说明超过最大查询次数，也没成功，返回3，表示错误
	else UsartPrintf(USART_DEBUG, "检查信号质量成功\r\n");                   //串口输出信息
	
	//4.AT+CGREG? -- +CGREG: 0,1
	UsartPrintf(USART_DEBUG, "准备查询网络附着... ...\r\n");                 //串口输出信息
	if(SIM7020_CGREG_Cmd(10)){                                //超时单位1s，超时时间10s
		UsartPrintf(USART_DEBUG, "查询网络附着超时，准备重启\r\n");          //串口输出信息
		return_value = 4;                                             //返回4
	}else UsartPrintf(USART_DEBUG, "网络附着成功\r\n");                      //串口输出信息
		
	//5.AT+CGACT? -- +CGACT: 1,1
	UsartPrintf(USART_DEBUG, "准备查询PDN 激活... ...\r\n");                 //串口输出信息
	if(SIM7020_CGACT_Cmd(10)){                                //超时单位1s，超时时间10s
		UsartPrintf(USART_DEBUG, "查询PDN 激活超时，准备重启\r\n");          //串口输出信息
		return_value = 5;                                             //返回5
	}else UsartPrintf(USART_DEBUG, "PDN 激活成功\r\n");                      //串口输出信息
	
	//6.AT+CGCONTRDP -- OK
	UsartPrintf(USART_DEBUG, "准备查询APN和分配的IP地址... ...\r\n");        //串口输出信息
	if(SIM7020_CGCONTRDP_Cmd(50)){                            //超时单位100ms，超时时间5s
		UsartPrintf(USART_DEBUG, "查询APN和分配的IP地址超时，准备重启\r\n"); //串口输出信息
		return_value = 6;                                             //返回6
	}
	
	//7.AT+CPSMS=0  -- OK
	UsartPrintf(USART_DEBUG, "准备关闭PCM模式... ...\r\n");                  //串口输出信息
	if(SIM7020_PSM_OFF(20)){                                  //超时单位1s，超时时间20s
		UsartPrintf(USART_DEBUG, "关闭PCM模式超时，准备重启\r\n");           //串口输出信息
		return_value = 7;                                             //返回7
	}else UsartPrintf(USART_DEBUG, "关闭PCM模式成功\r\n");                   //串口输出信息
	
	//8.AT+CEDRXS=0 -- OK
	UsartPrintf(USART_DEBUG, "准备关闭eDRX模式... ...\r\n");                 //串口输出信息
	if(SIM7020_eDRX_OFF(20)){                                 //超时单位1s，超时时间20s
		UsartPrintf(USART_DEBUG, "关闭eDRX模式超时，准备重启\r\n");          //串口输出信息
		return_value = 8;                                             //返回8
	}else UsartPrintf(USART_DEBUG, "关闭eDRX模式成功\r\n");                  //串口输出信息
	
	//9.AT+CIPSTART="TCP","183.230.40.33","80"
	UsartPrintf(USART_DEBUG, "准备连接服务器... ...\r\n");                 //串口输出信息
	if(SIM7020_OneNET_CONN(20)){                                 //超时单位1s，超时时间20s
		UsartPrintf(USART_DEBUG, "连接服务器超时，准备重启\r\n");          //串口输出信息
		return_value = 9;                                             //返回8
	}else UsartPrintf(USART_DEBUG, "连接服务器成功\r\n");                  //串口输出信息
	
	
	UsartPrintf(USART_DEBUG, "\r\n");                                        //串口输出信息
	Sta_flag = 0;                                             //配置完成，模块状态=1，处于处理数据状态 	
	SIM7020_RxCounter=0;                                      //7020接收数据量变量清零                        
	memset(SIM7020_RX_BUF,0,SIM7020_RXBUFF_SIZE);             //清空7020接收缓冲区 		 	
	return_value = 0;   
	
	if(return_value==0)                     
		UsartPrintf(USART_DEBUG, "模块配置成功\r\n");          //串口输出信息
	else
		UsartPrintf(USART_DEBUG, "配置失败  return_value = %d\r\n",return_value);            //串口输出信息

	
	return 0;
	    										//正确返回0

} 
/*-------------------------------------------------*/
/*函数名：把16进制数据转换成字符串                 */
/*参  数：data:需要转换的数据                      */
/*参  数：data_len:需要转换的数据长度              */
/*参  数：out:存放转换后的数据                     */
/*参  数：out_len:缓冲区长度                       */
/*返回值：无                                       */
/*-------------------------------------------------*/
void SIM7020_Hex_to_Str(char *data, int data_len, char *out, int out_len)
{
	char temp[2];
	int  i;
	
	memset(out,0,out_len);              //清空缓冲区
	for(i=0;i<data_len;i++){            //for循环
		sprintf(temp,"%02X",data[i]);   //转化数据，转成16进制字符串
		strcat(out,temp);               //追加到out缓冲区              
	} 	
}
/*-------------------------------------------------*/
/*函数名：把字符串转换成16进制数据                 */
/*参  数：data:需要转换的数据                      */
/*参  数：data_len:需要转换的数据长度              */
/*参  数：out:存放转换后的数据                     */
/*参  数：out_len:缓冲区长度                       */
/*返回值：无                                       */
/*-------------------------------------------------*/
void SIM7020_Str_to_Hex(char *data, int data_len, char *out, int out_len)
{
	int  i;
	
	memset(out,0,out_len);                //清空临时缓冲区
	for(i=0;i<data_len/2;i++){            //for循环
		if(((data[2*i]>='0')&&(data[2*i]<='9'))&&((data[2*i+1]>='0')&&(data[2*i+1]<='9')))
			out[i] = (data[2*i]-0x30)*16 + (data[2*i+1]-0x30);  
		
		else if(((data[2*i]>='0')&&(data[2*i]<='9'))&&((data[2*i+1]>='A')&&(data[2*i+1]<='F')))
			out[i] = (data[2*i]-0x30)*16 + (data[2*i+1]-0x37);  
		else if(((data[2*i]>='0')&&(data[2*i]<='9'))&&((data[2*i+1]>='a')&&(data[2*i+1]<='f')))
			out[i] = (data[2*i]-0x30)*16 + (data[2*i+1]-0x57); 
		
		else if(((data[2*i]>='A')&&(data[2*i]<='F'))&&((data[2*i+1]>='0')&&(data[2*i+1]<='9')))
			out[i] = (data[2*i]-0x37)*16 + (data[2*i+1]-0x30); 
		else if(((data[2*i]>='a')&&(data[2*i]<='f'))&&((data[2*i+1]>='0')&&(data[2*i+1]<='9')))
			out[i] = (data[2*i]-0x57)*16 + (data[2*i+1]-0x30); 
		
		else if(((data[2*i]>='A')&&(data[2*i]<='F'))&&((data[2*i+1]>='A')&&(data[2*i+1]<='F')))
			out[i] = (data[2*i]-0x37)*16 + (data[2*i+1]-0x37);
		else if(((data[2*i]>='a')&&(data[2*i]<='f'))&&((data[2*i+1]>='a')&&(data[2*i+1]<='f')))
			out[i] = (data[2*i]-0x57)*16 + (data[2*i+1]-0x57); 			
	} 	
}
/*-------------------------------------------------*/
/*函数名：把字符串数字转换成16进制数字             */
/*参  数：data:需要转换的数据                      */
/*参  数：data_len:需要转换的数据位数              */
/*返回值：转换后的数字                             */
/*-------------------------------------------------*/
int SIM7020_StrNum_to_HexNum(char *data, int data_len)
{
	int num;
	
	num = 0;
	switch(data_len){
		case 1: num += data[0] - 0x30;
				break;
		case 2: num += (data[0] - 0x30)*10;
				num += (data[1] - 0x30);
				break;
		case 3: num += (data[0] - 0x30)*100;
				num += (data[1] - 0x30)*10;
				num += (data[2] - 0x30);
				break;
		case 4: num += (data[0] - 0x30)*1000;
				num += (data[1] - 0x30)*100;
				num += (data[2] - 0x30)*10;
				num += (data[3] - 0x30);
				break;
	}
	return num;
}






/*
* 描述：发送数据
*/
void Sim7020_SendData(unsigned char *data, unsigned short len)
{

	char cmdBuf[32];
	
	Sim7020_Clear();								//清空接收缓存
	
	sprintf(cmdBuf, "AT+CIPSEND=%d\r\n", len);		//发送命令
	UsartPrintf(USART2,cmdBuf);
	
	while(!strstr(SIM7020_RX_BUF,">"));            //收到‘>’时可以发送数据

	Usart_SendString(USART2, data, len);		//发送设备连接请求数据
	UsartPrintf(USART_DEBUG, "数据发送成功 \r\n");

		


}



/*
* 描述：发送命令
*/
_Bool Sim7020_SendCmd(char *cmd, char *res)
{
	
	unsigned char timeOut = 200;

	Usart_SendString(USART2, (unsigned char *)cmd, strlen((const char *)cmd));
	
	while(timeOut--)
	{
		if(Sim7020_WaitRecive() == REV_OK)							//如果收到数据
		{
			if(strstr((const char *)SIM7020_RX_BUF, res) != NULL)		//如果检索到关键词
			{
				Sim7020_Clear();									//清空缓存
				
				return 0;
			}
		}
		
		DelayXms(10);
	}
	
	return 1;

}


/*
* 描述：等待接收完成
*/
_Bool Sim7020_WaitRecive(void)
{

	if(SIM7020_RxCounter == 0) 							//如果接收计数为0 则说明没有处于接收数据中，所以直接跳出，结束函数
		return REV_WAIT;
		
	if(SIM7020_RxCounter == sim7020_cntPre)				//如果上一次的值和这次相同，则说明接收完毕
	{
		SIM7020_RxCounter = 0;							//清0接收计数
			
		return REV_OK;								//返回接收完成标志
	}
		
	sim7020_cntPre = SIM7020_RxCounter;					//置为相同
	
	return REV_WAIT;								//返回接收未完成标志

}


/*
* 描述：清空缓存
*/
void Sim7020_Clear(void)
{

	SIM7020_RxCounter=0;                           //7020接收数据量变量清零                        
	memset(SIM7020_RX_BUF,0,SIM7020_RXBUFF_SIZE);  //清空7020接收缓冲区 	

}


/*
* 描述：获取平台返回的数据
*/
unsigned char *Sim7020_GetIPD(unsigned short timeOut)
{

	char *ptrIPD = NULL;
	
	do
	{
		if(Sim7020_WaitRecive() == REV_OK)								//如果接收完成
		{
			ptrIPD = strstr((char *)SIM7020_RX_BUF, "IPD,");				//搜索“IPD”头
			if(ptrIPD == NULL)											//如果没找到，可能是IPD头的延迟，还是需要等待一会，但不会超过设定的时间
			{
				//UsartPrintf(USART_DEBUG, "\"IPD\" not found\r\n");
			}
			else
			{
				ptrIPD = strchr(ptrIPD, ':');							//找到':'
				if(ptrIPD != NULL)
				{
					ptrIPD++;
					return (unsigned char *)(ptrIPD);
				}
				else
					return NULL;
				
			}
		}
		
		DelayXms(5);													//延时等待
	} while(timeOut--);
	
	return NULL;														//超时还未找到，返回空指针

}
