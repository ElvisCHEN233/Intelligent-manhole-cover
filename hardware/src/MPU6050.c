#include "stm32f10x.h"
#include "MPU6050.h"
#include "delay.h"

short G_X,G_Y,G_Z,T_T;			 //X,Y,Z��Ƕȣ��¶�
extern short A_X,A_Y,A_Z;					 //X,Y,Z���ٶ�
char  test=0; 							 //IIC�õ�

/*******************************************************************************
* Function Name  : I2C_GPIO_Config
* Description    : Configration Simulation IIC GPIO
* Input          : None 
* Output         : None
* Return         : None
****************************************************************************** */
void I2C_GPIO_Config(void)				//IIC���ų�ʼ��
{
  GPIO_InitTypeDef  GPIO_InitStructure; 
 
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;  
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/*******************************************************************************
* Function Name  : I2C_delay
* Description    : Simulation IIC Timing series delay
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void I2C_delay(void)
{
		
   u8 i=30; //��������Ż��ٶ�	����������͵�5����д��
   while(i) 
   { 
     i--; 
   }  
}


/*******************************************************************************
* Function Name  : I2C_Start
* Description    : Master Start Simulation IIC Communication
* Input          : None
* Output         : None
* Return         : Wheather	 Start
****************************************************************************** */
bool I2C_Start(void)			//IIC��ʼ
{
	SDA_H;
	SCL_H;
	I2C_delay();
	if(!SDA_read)return FALSE;	//SDA��Ϊ�͵�ƽ������æ,�˳�
	SDA_L;
	I2C_delay();
	if(SDA_read) return FALSE;	//SDA��Ϊ�ߵ�ƽ�����߳���,�˳�
	SDA_L;
	I2C_delay();
	return TRUE;
}
/*******************************************************************************
* Function Name  : I2C_Stop
* Description    : Master Stop Simulation IIC Communication
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void I2C_Stop(void)				//IICֹͣ
{
	SCL_L;
	I2C_delay();
	SDA_L;
	I2C_delay();
	SCL_H;
	I2C_delay();
	SDA_H;
	I2C_delay();
} 
/*******************************************************************************
* Function Name  : I2C_Ack
* Description    : Master Send Acknowledge Single
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void I2C_Ack(void)		//IIC����
{	
	SCL_L;
	I2C_delay();
	SDA_L;
	I2C_delay();
	SCL_H;
	I2C_delay();
	SCL_L;
	I2C_delay();
}   
/*******************************************************************************
* Function Name  : I2C_NoAck
* Description    : Master Send No Acknowledge Single
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void I2C_NoAck(void)	
{	
	SCL_L;
	I2C_delay();
	SDA_H;
	I2C_delay();
	SCL_H;
	I2C_delay();
	SCL_L;
	I2C_delay();
} 
/*******************************************************************************
* Function Name  : I2C_WaitAck
* Description    : Master Reserive Slave Acknowledge Single
* Input          : None
* Output         : None
* Return         : Wheather	 Reserive Slave Acknowledge Single
****************************************************************************** */
bool I2C_WaitAck(void) 	 //����Ϊ:=1��ACK,=0��ACK  �ȴ�����
{
	SCL_L;
	I2C_delay();
	SDA_H;			
	I2C_delay();
	SCL_H;
	I2C_delay();
	if(SDA_read)
	{
      SCL_L;
	  I2C_delay();
      return FALSE;
	}
	SCL_L;
	I2C_delay();
	return TRUE;
}
/*******************************************************************************
* Function Name  : I2C_SendByte
* Description    : Master Send a Byte to Slave
* Input          : Will Send Date
* Output         : None
* Return         : None
****************************************************************************** */
void I2C_SendByte(u8 SendByte) //���ݴӸ�λ����λ//��������
{
    u8 i=8;
    while(i--)
    {
        SCL_L;
        I2C_delay();
      if(SendByte&0x80)
        SDA_H;  
      else 
        SDA_L;
        SendByte<<=1;
        I2C_delay();
		SCL_H;
        I2C_delay();
    }
    SCL_L;
}  
/*******************************************************************************
* Function Name  : I2C_RadeByte
* Description    : Master Reserive a Byte From Slave
* Input          : None
* Output         : None
* Return         : Date From Slave 
****************************************************************************** */
unsigned char I2C_RadeByte(void)  //���ݴӸ�λ����λ//��ȡ�ֽ�
{ 
    u8 i=8;
    u8 ReceiveByte=0;

    SDA_H;				
    while(i--)
    {
      ReceiveByte<<=1;      
      SCL_L;
      I2C_delay();
	  SCL_H;
      I2C_delay();	
      if(SDA_read)
      {
        ReceiveByte|=0x01;
      }
    }
    SCL_L;
    return ReceiveByte;
} 




//ZRX          
//���ֽ�д��*******************************************

bool Single_Write(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data)		     //void 
{
  	if(!I2C_Start())return FALSE;
    I2C_SendByte(SlaveAddress);   //�����豸��ַ+д�ź�//I2C_SendByte(((REG_Address & 0x0700) >>7) | SlaveAddress & 0xFFFE);//���ø���ʼ��ַ+������ַ 
    if(!I2C_WaitAck()){I2C_Stop(); return FALSE;}
    I2C_SendByte(REG_Address );   //���õ���ʼ��ַ      
    I2C_WaitAck();	
    I2C_SendByte(REG_data);
    I2C_WaitAck();   
    I2C_Stop(); 
    delay5ms();
    return TRUE;
}

//���ֽڶ�ȡ*****************************************
unsigned char Single_Read(unsigned char SlaveAddress,unsigned char REG_Address)
{   unsigned char REG_data;     	
	if(!I2C_Start())return FALSE;
    I2C_SendByte(SlaveAddress); //I2C_SendByte(((REG_Address & 0x0700) >>7) | REG_Address & 0xFFFE);//���ø���ʼ��ַ+������ַ 
    if(!I2C_WaitAck()){I2C_Stop();test=1; return FALSE;}
    I2C_SendByte((u8) REG_Address);   //���õ���ʼ��ַ      
    I2C_WaitAck();
    I2C_Start();
    I2C_SendByte(SlaveAddress+1);
    I2C_WaitAck();

	REG_data= I2C_RadeByte();
    I2C_NoAck();
    I2C_Stop();
    //return TRUE;
	return REG_data;

}						      



//��ʼ��MPU6050��������Ҫ��ο�pdf�����޸�************************
void Init_MPU6050(void)
{
/*
   Single_Write(MPU6050_Addr,PWR_M, 0x80);   //
   Single_Write(MPU6050_Addr,SMPL, 0x07);    //
   Single_Write(MPU6050_Addr,DLPF, 0x1E);    //��2000��
   Single_Write(MPU6050_Addr,INT_C, 0x00 );  //
   Single_Write(MPU6050_Addr,PWR_M, 0x00);   //
*/
	I2C_GPIO_Config();								//����IICʹ�ö˿�
	DelayMs(10);

	Single_Write(MPU6050_Addr,PWR_MGMT_1, 0x00);	//�������״̬
	Single_Write(MPU6050_Addr,SMPLRT_DIV, 0x07);
	Single_Write(MPU6050_Addr,CONFIG, 0x06);
	Single_Write(MPU6050_Addr,GYRO_CONFIG, 0x18);
	Single_Write(MPU6050_Addr,ACCEL_CONFIG, 0x01);
}
	
//******��ȡMPU6050����****************************************
void READ_MPU6050(void)
{
	unsigned char BUF0[10];       //�������ݻ�����
	unsigned char BUF1[10];       //�������ݻ�����
	/*	��ȡ����������		*/
	//***********************************************************
   BUF0[0]=Single_Read(MPU6050_Addr,GYRO_XOUT_L); 
   BUF0[1]=Single_Read(MPU6050_Addr,GYRO_XOUT_H);
   G_X =	(BUF0[1]<<8)|BUF0[0];
   G_X =(double)G_X*250/327.68; 						   //��ȡ����X������

   BUF0[2]=Single_Read(MPU6050_Addr,GYRO_YOUT_L);
   BUF0[3]=Single_Read(MPU6050_Addr,GYRO_YOUT_H);
   G_Y =	(BUF0[3]<<8)|BUF0[2];
   G_Y =(double)G_Y*250/327.68; 						   //��ȡ����Y������
	
   BUF0[4]=Single_Read(MPU6050_Addr,GYRO_ZOUT_L);
   BUF0[5]=Single_Read(MPU6050_Addr,GYRO_ZOUT_H);
   G_Z =	(BUF0[5]<<8)|BUF0[4];
   G_Z =(double)G_Z*250/327.68; 					       //��ȡ����Z������

   BUF0[6]=Single_Read(MPU6050_Addr,TEMP_OUT_L); 
   BUF0[7]=Single_Read(MPU6050_Addr,TEMP_OUT_H); 
   T_T =(BUF0[7]<<8)|BUF0[6];
   T_T =(((double) (T_T + 13200)) / 280)-39;// ��ȡ������¶�
	
	//ACCEL_ZOUT_L
	//*************************************************************
		/*	��ȡ���ٶ�����		*/
	//***********************************************************
   BUF1[0]=Single_Read(MPU6050_Addr,ACCEL_XOUT_L); 
   BUF1[1]=Single_Read(MPU6050_Addr,ACCEL_XOUT_H);
   A_X =	(BUF1[1]<<8)|BUF1[0];
   A_X = (double)A_X/163.84; 						   //��ȡ����X������

   BUF1[2]=Single_Read(MPU6050_Addr,ACCEL_YOUT_L);
   BUF1[3]=Single_Read(MPU6050_Addr,ACCEL_YOUT_H);
   A_Y =	(BUF1[3]<<8)|BUF1[2];
   A_Y = (double)A_Y/163.84; 						   //��ȡ����Y������
	
   BUF1[4]=Single_Read(MPU6050_Addr,ACCEL_ZOUT_L);
   BUF1[5]=Single_Read(MPU6050_Addr,ACCEL_ZOUT_H);
   A_Z =	(BUF1[5]<<8)|BUF1[4];
   A_Z = (double)A_Z/163.84; 					       //��ȡ����Z������
	//*************************************************************
}



void delay5ms(void)
{
		
   int i=5000;  
   while(i) 
   { 
     i--; 
   }  
}







