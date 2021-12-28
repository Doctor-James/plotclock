#include "main.h"


void delay_init()
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);	
	
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;
	
	SysTick->LOAD=72-1;	
}			


void delay_us(u32 ntime)
{
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;
	
	while(ntime--)
		while((SysTick->CTRL&0x010000)==0);
	
	SysTick->CTRL&= ~SysTick_CTRL_ENABLE_Msk;
}


void delay_ms(u32 ntime)
{
	ntime*=1000;
	
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;
	
	while(ntime--)
		while((SysTick->CTRL&0x010000)==0);
	
	SysTick->CTRL&= ~SysTick_CTRL_ENABLE_Msk;
}



