#ifndef __DELAY_H
#define __DELAY_H 	

#include "stm32f10x.h"  

void delay_init(void);
void delay_us(u32 ntime);
void delay_ms(u32 ntime);

#endif




