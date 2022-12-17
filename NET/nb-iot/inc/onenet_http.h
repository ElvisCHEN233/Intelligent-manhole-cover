

#ifndef _ONENET_HTTP_H
#define _ONENET_HTTP_H

#define SWITCH_DID         "684827553"						//设备ID
#define API_KEY            "PzvPprQYmc05RYgsD5k=nCsxge0="	//APIKey

#define DEVID	"684827553"
#define APIKEY	"PzvPprQYmc05RYgsD5k=nCsxge0="



extern char RXbuff[1024];      //接收数据缓冲区

char SIM7020C_OneNetGET(char *device_id,int timeout);

void OneNet_FillBuf(char *buf);

void OneNet_SendData(void);

void OneNet_RevPro(unsigned char *dataPtr);

#endif
