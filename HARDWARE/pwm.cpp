#include "main.h"


//		��������������Ծ�׼��ע���������λ��
//		TIM_SetCompare1(TIM4, 5);//0��
//		TIM_SetCompare1(TIM4, 10);//45��
//		TIM_SetCompare1(TIM4, 15);//90��
//		TIM_SetCompare1(TIM4, 20);//135��
//		TIM_SetCompare1(TIM4, 25);//180��
void pwm_init(void)
{  
	GPIO_InitTypeDef 			gpio;
	TIM_TimeBaseInitTypeDef 	base;
	TIM_OCInitTypeDef  			oc;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	//PWM
	gpio.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8; // right|left|lift
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;  
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&gpio);
	
	//1msһ���ж�
	base.TIM_Period = 199; 
	base.TIM_Prescaler = 7199; 
	base.TIM_ClockDivision = TIM_CKD_DIV1;
	base.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM4,&base); 
	
	oc.TIM_OCMode = TIM_OCMode_PWM1; 
	oc.TIM_OutputState = TIM_OutputState_Enable;
	oc.TIM_OCPolarity = TIM_OCPolarity_High; 	
	
	TIM_OC1Init(TIM4,&oc); 
	TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);  

	TIM_OC2Init(TIM4,&oc); 
	TIM_OC2PreloadConfig(TIM1,TIM_OCPreload_Enable);  
	
	TIM_OC3Init(TIM4,&oc); 
	TIM_OC3PreloadConfig(TIM1,TIM_OCPreload_Enable);  
	
	TIM_ARRPreloadConfig(TIM4,ENABLE);//ʹ��Ԥװ�ؼĴ���
	TIM_Cmd(TIM4,ENABLE); 
}



