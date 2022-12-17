#ifndef _HSR04_H_
#define _HSR04_H_

#include "delay.h"
#include "stm32f10x.h"
#include "sys.h"




float hsr04_get(void);
float hsr04_get_2(void);
float hsr04_get_3(void);
void HCSR04_Init(u16 arr,u16 psc);

// void get_height();
#endif
