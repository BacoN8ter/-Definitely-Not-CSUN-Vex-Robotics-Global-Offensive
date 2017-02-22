//Auton Functions

#define KpT 0.9
#define KpD 4.5
//calculates the angle needed to turn in order to face the target point
int AngleBetween(int x1, int y1, int x2, int y2)
{
	return radiansToDegrees(atan2(y2 - y1, x2 - x1));
}

//turns the desired amount of degrees in the proper direction
void Turn(int targetAngle)
{
	//current difference between the angle calculated and the current for
	//proportional control turning
	float difference = (targetAngle - Bot.Heading);
	//calculate to see if it is faster to turn left or right
	while(difference > 180)
	{
		difference -= 360;
	}
	while(difference < -180)
	{
		difference += 360;
	}
//p control
	while(abs(difference) > 1)
	{
		difference = (targetAngle - Bot.Heading);
		while(difference > 180)
		{
			difference -= 360;
		}
		while(difference < -180)
		{
			difference += 360;
		}

		int power = difference * KpT;
		power = power < -100 ? -100 : power;
		power = power > 100 ? 100 : power;
		motor[leftBack] = power;
		motor[leftFront] = power;
		motor[leftTop] = power;
		motor[rightBack] = -power;
		motor[rightFront] = -power;
		motor[rightTop] = -power;

		while(time1[T2] < 10){}
		time1[T2] = 0;
	}

}

//everything put together in order to travel to target point from current point
void Move(float X, float Y){
	//turn to angle
	Turn(AngleBetween(Bot.X, Bot.Y, X, Y));
	//calculate hypotenuse
	float difference = sqrt(pow(Bot.X - X, 2) + pow(Bot.Y - Y, 2));
//p control for driving the hypotenuse
	while(difference > 0.05){

		difference -= sqrt(pow(Bot.XSpeed, 2) + pow(Bot.YSpeed, 2));

		int power = difference * KpD;
		power = power < 10 ? 10 : power;
		//float angleOffset = (AngleBetween(Bot.X, Bot.Y, X, Y) - Bot.Heading);
		power = power >= 100 ? 100 : power;

		motor[leftTop] = power;// + angleOffset;
		motor[leftFront] = power;// + angleOffset;
		motor[leftBack] = power;// + angleOffset;

		motor[leftTop] = power;// - angleOffset;
		motor[leftFront] = power;// - angleOffset;
		motor[leftBack] = power;// + angleOffset;


		while(time1[T2] < 100){
		}
		time1[T2] = 0;
	}
}

void Stop(){
		motor[leftBack] = 0;
		motor[leftFront] = 0;
		motor[leftTop] = 0;
		motor[rightBack] = 0;
		motor[rightFront] = 0;
		motor[rightTop] = 0;
}
