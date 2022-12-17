
#ifndef __SIM7020_H
#define __SIM7020_H


#define ESP8266_ONENET_INFO		"AT+CIPSTART=\"TCP\",\"183.230.40.33\",80\r\n"

#define  POWER_KEY(x)    GPIO_WriteBit(GPIOB, GPIO_Pin_0,  (BitAction)x)  //PB0 控制sim7020模块的开关机按键
#define  RESET_KEY(x)    GPIO_WriteBit(GPIOA, GPIO_Pin_7,  (BitAction)x)  //PA7 控制sim7020模块的复位按键
#define  POWER_STA       GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1)         //PB1的电平，可以判断sim7020是开机还是关机
#define  SIM7020_RXBUFF_SIZE       512
#define REV_OK		0	//接收完成标志
#define REV_WAIT	1	//接收未完成标志



void SIM_PwrKeyInit(void);
void SIM_PwrStaInit(void);
void SIM_RstKeyInit(void);
char SIM_PowerON(void);
char SIM7020_ATTest_Cmd(int counter);
char SIM7020_Send_Cmd(char *cmd, int timeout);
char SIM7020_CPIN_Cmd(int timeout);
char SIM7020_CGREG_Cmd(int timeout);
char SIM7020_CGACT_Cmd(int timeout);
char SIM7020_CSQ_Cmd(int timeout);
char SIM7020_CGCONTRDP_Cmd(int timeout);
char SIM7020_IPR_Cmd(int bound, int timeout);
char SIM7020_PSM_OFF(int timeout);
char SIM7020_eDRX_OFF(int timeout);
char SIM7020_Init(void);
void SIM7020_Hex_to_Str(char *data, int data_len, char *out, int out_len);
void SIM7020_Str_to_Hex(char *data, int data_len, char *out, int out_len);
int SIM7020_StrNum_to_HexNum(char *data, int data_len);

_Bool Sim7020_WaitRecive(void);
_Bool Sim7020_SendCmd(char *cmd, char *res);
void Sim7020_SendData(unsigned char *data, unsigned short len);
void Sim7020_Clear(void);
unsigned char *Sim7020_GetIPD(unsigned short timeOut);
#endif
