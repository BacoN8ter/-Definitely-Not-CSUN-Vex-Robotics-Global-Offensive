/*
Driver Control Code

*/

#define DEADZONE 15

//Functions
void Drive();
void Lift();


int DeadzoneCheck(int power, int deadzone)
{
	return abs(power) < deadzone ? 0 : power;
}

void Drive()
{
	int x = vexRT[Ch4];
	int y = vexRT[Ch3];
	int theta = vexRT[Ch1];

	x = DeadzoneCheck(x, DEADZONE);
	y = DeadzoneCheck(y, DEADZONE);
	theta = DeadzoneCheck(theta, DEADZONE);

	motor[driveFrontLeft] = x + y + theta;
	motor[driveFrontRight] = x - y + theta;
	motor[driveBackLeft] = -x + y + theta;
	motor[driveBackRight] = -x - y + theta;

}

void Lift()
{
	if(vexRT[Btn6U])
	{
		motor[liftExtra] = -127;
		motor[liftRight] = 127;
		motor[liftLeft] = -127;
	}
	else if(vexRT[Btn6D])
	{
		motor[liftExtra] = 127;
		motor[liftRight] = -127;
		motor[liftLeft] = 12127;
	}
	else
	{
		motor[liftExtra] = 0;
		motor[liftRight] = 0;
		motor[liftLeft] = 0;
	}
}
