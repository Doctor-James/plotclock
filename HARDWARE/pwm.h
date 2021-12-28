#ifndef __PWM_H
#define __PWM_H


#define Left_Pwm   TIM3->CCR1  //PA6
#define Right_Pwm   TIM3->CCR2  //PA7
#define Lift_Pwm   TIM3->CCR3  //PB0

void pwm_init(void);


#endif


