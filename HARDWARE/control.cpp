#include "control.h"

//舵机类，角度的读写
void Servo_right::write(float angle)
{
	int pwm_set = (int)((angle+45)/9.0);
	TIM_SetCompare2(TIM4, pwm_set);
}

int Servo_right::read()
{
	angle = 9*(TIM4->CCR1)-45;
	return angle;
}

void Servo_left::write(float angle)
{
	int pwm_set = (int)((angle+45)/9.0);
	TIM_SetCompare1(TIM4, pwm_set);
}

int Servo_left::read()
{
	angle = 9*(TIM4->CCR2)-45;
	return angle;
}

void Servo_lift::write(float angle)
{
	int pwm_set = (int)((angle+45)/9.0);
	TIM_SetCompare3(TIM4, pwm_set);
}

int Servo_lift::read()
{
	angle = 9*(TIM4->CCR3)-45;
	return angle;
}


//控制
Control::Control()
{
	GoTo(35, 50);
	Lift(LIFT_STATE::BETWEEN_NUMS);
	delay_ms(100);
}
//lift舵机抬起
void Control::Lift(LIFT_STATE s)
{
	int target;

	switch (s)
	{
	case LIFT_STATE::ON_DRAW:
		target = 55;
		break;
	case LIFT_STATE::BETWEEN_NUMS:
		target = 10;
		break;
	case LIFT_STATE::LIFTED:
		target = 0;
		break;
	}

	servo_lift.write(target);
	delay_ms(100);
}

//放笔
void Control::GoHome()
{
	Lift(LIFT_STATE::LIFTED);
	GoTo(76, 43);
	Lift(LIFT_STATE::BETWEEN_NUMS);
}


double Control::return_angle(double a, double b, double c)
{
	return acos((a * a + c * c - b * b) / (2 * a * c));
}


//去到（x，y）位置
void Control::set_XY(double Tx, double Ty)
{
	double dx, dy, c, a1, a2, Hx, Hy;
	float angle_r,angle_l;

	// 相对左舵机的位置
	dx = Tx - O1X;
	dy = Ty - O1Y;

	//角度关系看坐标系定义
	c = sqrt(dx * dx + dy * dy); // 
	a1 = atan2(dy, dx); //
	a2 = return_angle(L1, L2, c);

	angle_l = angle_transition(a1+a2);
	servo_left.write(angle_l);


	a2 = return_angle(L2, L1, c);
	Hx = Tx + L3 * cos((a1 - a2 + 0.621) + 3.1415926); //36.5度
	Hy = Ty + L3 * sin((a1 - a2 + 0.621) + 3.1415926);


	dx = Hx - O2X;
	dy = Hy - O2Y;

	c = sqrt(dx * dx + dy * dy);
	a1 = atan2(dy, dx);
	a2 = return_angle(L1, (L2 - L3), c);

	angle_r = angle_transition(a1-a2);
	servo_right.write(angle_r);
  delay_us(100);
}


void Control::GoTo(double pX, double pY)
{
	double dx, dy, c;
	int i;

	dx = pX - lastX;
	dy = pY - lastY;
	//将一大步分为四小步
	c = floor(4 * sqrt(dx * dx + dy * dy));

	if (c < 1) c = 1;

	for (i = 0; i <= c; i++)
	{
		set_XY(lastX + (i * dx / c), lastY + (i * dy / c));
		delay_us(100);
	}

	lastX = pX;
	lastY = pY;
}

void Control::circleAntiClockwise(float bx, float by, float radius, int start, int ende, float sqee)
{
	float inkr = 0.2;
	float count = 0;

	do
	{
		GoTo(sqee*radius * cos(start + count) + bx,
			radius * sin(start + count) + by);
		count += inkr;
		delay_ms(1);
	} while ((start + count) <= ende);
}

void Control::circleClockwise(float bx, float by, float radius, int start, int ende, float sqee)
{
	float inkr = -0.05;
	float count = 0;

	do
	{
		GoTo(radius * cos(start + count) + bx,
			radius * sin(start + count) + by);
		count += inkr;
		delay_ms(1);
	} while ((start + count) > ende);

}

void Control::DrawNumber(float bx, float by, int num, float scale)
{
	switch (num)
	{

	case 0:
		GoTo(bx + 7 * scale, by + 7 * scale);
		Lift(LIFT_STATE::ON_DRAW);
		delay_ms(100);
		circleAntiClockwise(bx + 7 * scale, by + 7 * scale, 10 * scale, 0, 7, 0.5);
		Lift(LIFT_STATE::BETWEEN_NUMS);
		break;
	case 1:
		GoTo(bx + 10 * scale, by + 20 * scale);
		delay_ms(100);
		Lift(LIFT_STATE::ON_DRAW);
		delay_ms(100);
		GoTo(bx + 10 * scale, by + (-15)* scale);
		delay_ms(100);
		Lift(LIFT_STATE::BETWEEN_NUMS);
		break;
	case 2:
		GoTo(bx + 5* scale, by + 10 * scale);
		Lift(LIFT_STATE::ON_DRAW);
		delay_ms(100);
		circleClockwise(bx + 8 * scale, by + 14 * scale, 6 * scale, 3, -2, 1);
		delay_ms(100);
		GoTo(bx + 1 * scale, by + 0 * scale);
		delay_ms(100);
		GoTo(bx + 12 * scale, by + 0 * scale);
		Lift(LIFT_STATE::BETWEEN_NUMS);
		break;
	case 3:
		GoTo(bx + 2 * scale, by + 17 * scale);
		Lift(LIFT_STATE::ON_DRAW);
		circleClockwise(bx + 5 * scale, by + 15 * scale, 5 * scale, 3, -3, 1);
		circleClockwise(bx + 5 * scale, by + 8 * scale, 6* scale, 3, -2, 1);
		GoTo(bx + (-5)* scale, by + 4* scale);
		Lift(LIFT_STATE::BETWEEN_NUMS);
		break;
	case 4:
		GoTo(bx + 10 * scale, by + 0 * scale);
		Lift(LIFT_STATE::ON_DRAW);
		GoTo(bx + 10 * scale, by + 20 * scale);
		GoTo(bx + 2 * scale, by + 6 * scale);
		GoTo(bx + 12 * scale, by + 6 * scale);
		Lift(LIFT_STATE::BETWEEN_NUMS);
		break;
	case 5:
		GoTo(bx + 2 * scale, by + 5 * scale);
		Lift(LIFT_STATE::ON_DRAW);
		circleAntiClockwise(bx + 5 * scale, by + 6 * scale, 6 * scale, -2.5, 2, 1);
		GoTo(bx + 5 * scale, by + 20 * scale);
		GoTo(bx + 12 * scale, by + 20 * scale);
		Lift(LIFT_STATE::BETWEEN_NUMS);
		break;
	case 6:
		GoTo(bx + 2 * scale, by + 10 * scale);
		Lift(LIFT_STATE::ON_DRAW);
		circleClockwise(bx + 7 * scale, by + 6 * scale, 6 * scale, 3, -4.4, 1);
		GoTo(bx + 11 * scale, by + 20 * scale);
		Lift(LIFT_STATE::BETWEEN_NUMS);
		break;
	case 7:
		GoTo(bx + 2 * scale, by + 20 * scale);
		Lift(LIFT_STATE::ON_DRAW);
		GoTo(bx + 12 * scale, by + 20 * scale);
		GoTo(bx + 2 * scale, by + 0);
		Lift(LIFT_STATE::BETWEEN_NUMS);
		break;
	case 8:
		GoTo(bx + 5 * scale, by + 10 * scale);
		Lift(LIFT_STATE::ON_DRAW);
		circleClockwise(bx + 5 * scale, by + 15 * scale, 5 * scale, 4.7, -1.6, 1);
		circleAntiClockwise(bx + 5 * scale, by + 5 * scale, 5 * scale, -4.7, 2, 1);
		Lift(LIFT_STATE::BETWEEN_NUMS);
		break;

	case 9:
		GoTo(bx + 9 * scale, by + 11 * scale);
		Lift(LIFT_STATE::ON_DRAW);
		circleClockwise(bx + 7 * scale, by + 15 * scale, 5 * scale, 4, -0.5, 1);
		GoTo(bx + 5 * scale, by + 5);
		Lift(LIFT_STATE::BETWEEN_NUMS);
		break;

	case 111:

		Lift(LIFT_STATE::ON_DRAW);
		GoTo(70, 46);
		GoTo(65, 43);

		GoTo(65, 49);
		GoTo(5, 49);
		GoTo(5, 45);
		GoTo(65, 45);
		GoTo(65, 40);

		GoTo(5, 40);
		GoTo(5, 35);
		GoTo(65, 35);
		GoTo(65, 30);

		GoTo(5, 30);
		GoTo(5, 25);
		GoTo(65, 25);
		GoTo(65, 20);

		GoTo(5, 20);
		GoTo(60, 44);

		GoTo(75.2, 47);
		Lift(LIFT_STATE::LIFTED);

		break;

	case 11:
		GoTo(bx + 5 * scale, by + 15 * scale);
		Lift(LIFT_STATE::ON_DRAW);
		circleAntiClockwise(bx + 5 * scale, by + 15 * scale, 0.1 * scale, 1, -1, 1);
		delay_ms(200);
		Lift(LIFT_STATE::BETWEEN_NUMS);
		GoTo(bx + 5 * scale, by + 5 * scale);
		Lift(LIFT_STATE::ON_DRAW);
		circleAntiClockwise(bx + 5 * scale, by + 5 * scale, 0.1 * scale, 1, -1, 1);
		delay_ms(200);
		Lift(LIFT_STATE::BETWEEN_NUMS);
		break;

	}
}

void Control::Clear()
{
	DrawNumber(3, 3, 111, 1);
}


float Control::angle_transition(float angle)
{
 return (angle/3.1415926)*180 ; 
}
