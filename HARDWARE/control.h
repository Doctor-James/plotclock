#ifndef __CONTROL_H
#define __CONTROL_H
#include "main.h"

enum LIFT_STATE
{
	ON_DRAW,
	BETWEEN_NUMS,
	LIFTED
};

//舵机类
class Servo
{
	protected:
		int angle;
};

class Servo_right : public Servo
{
	public:
		void write(float angle);
		int read();
};

class Servo_left : public Servo
{
	public:
		void write(float angle);
		int read();
};

class Servo_lift : public Servo
{
	public:
		void write(float angle);
		int read();
};

//控制类
class Control
{
	public:
		Control();
		void DrawNumber(float bx, float by, int num, float scale);

		void Lift(LIFT_STATE s);
		void GoTo(double pX, double pY);
		void GoHome();
		void Clear();
	
		bool CmdRoutine();
		void circleClockwise(float bx, float by, float radius, int start, int ende, float sqee);
		void circleAntiClockwise(float bx, float by, float radius, int start, int ende, float sqee);
		double return_angle(double a, double b, double c);
		void set_XY(double Tx, double Ty);
		float angle_transition(float angle);
	private:
		//悬臂的长度，根据图纸可得
		int L1 = 35;
		int L2 = 57.2;
		int L3 = 13;
	
		// 左右舵机轴心位置
		int O1X = 22;
		int O1Y = -25;
		int O2X = 47;
		int O2Y = -25;
	
		//笔现在的位置
		double lastX = 35;
		double lastY = 50;
	
		Servo_lift servo_lift;
		Servo_left servo_left;
		Servo_right servo_right;
	

};


#endif


