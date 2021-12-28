#ifndef __MAIN_H
#define __MAIN_H


#include "stm32f10x.h"
#include "stdio.h"
#include "stdlib.h"
#include "delay.h"
#include "pwm.h"
#include "control.h"
#include "usart.h"
#include "control.h"
#include "math.h"



//位操作
//IO口操作宏定义
#define BITBAND(addr,bitnum) 	((addr &0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)			*((volatile unsigned long*)(addr)) 
#define BIT_ADDR(addr,bitnum) 	MEM_ADDR(BITBAND(addr,bitnum)) 

//IO口地址映射
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
                                          
#define GPIOA_IDR_Addr    (GPIOA_BASE+8)  //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8)  //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8)  //0x40011008 
 
//IO口操作
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)


//取绝对值函数
#define ABS(x) ((x)>0? (x):(-(x)))
//限幅函数
#define LIMIT_MAX_MIN(x, max, min)	(((x) <= (min)) ? (min):(((x) >= (max)) ? (max) : (x)))


typedef struct
{
	float Pitch;
	float Yaw;
	float Roll;
	
}ANGLE_T;

typedef struct
{
	unsigned short x;
	unsigned short y;
	unsigned char Key_F;
	unsigned char Key_B;
	unsigned char Key_L;
	unsigned char Key_R;
	unsigned char Key_SW;
	unsigned char Check1;
	unsigned char Check2;
	
	unsigned char Key_F_Last;
	unsigned char Key_B_Last;
	unsigned char Key_L_Last;
	unsigned char Key_R_Last;
	
}RC_t;



void system_Init(void);
void data_init(void);


#endif



