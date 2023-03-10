#ifndef _LED_H_
#define _LED_H_





typedef struct
{
	_Bool Led1Sta;
	_Bool Led2Sta;
	_Bool Led3Sta;
	_Bool Led4Sta;
	_Bool Led5Sta;

} LED_STATUS;

extern LED_STATUS led_status;


typedef enum
{

	LED_OFF = 0,
	LED_ON

} LED_ENUM;


void Led_Init(void);

void Led_test(LED_ENUM status);

void Led2_Set(LED_ENUM status);

void Led3_Set(LED_ENUM status);

void Led4_Set(LED_ENUM status);

void Led5_Set(LED_ENUM status);

void Light_Start(void);

#endif
