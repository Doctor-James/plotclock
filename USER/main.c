#include "main.h"

int main(void)
{
delay_init();
pwm_init();
Control control;
//control.set_XY(30,30);
//control.GoHome();
//control.Lift(LIFT_STATE::ON_DRAW);
control.DrawNumber(0, 25, 5, 1);
delay_ms(100);
control.DrawNumber(18, 30, 11, 0.9);
delay_ms(100);
control.DrawNumber(25, 25, 0, 1);
delay_ms(100);
control.DrawNumber(45, 25, 6, 1);

//control.GoTo(30,30);
//TIM_SetCompare1(TIM4, 15);//90¶È
//TIM_SetCompare2(TIM4, 5);//90¶È
while(1)
{

}
	
}




