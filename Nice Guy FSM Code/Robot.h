// Demonstrate X, Y, Theta
// Start and navigate to a zone then to the ramp
// Show that the position is acurately maintain

// Bonus for random movement to ramp or scoring zone

// 22cm wheel circumfrence
// C = 2*pi*r

#define TimeStep 100.0

/*
Robot struct. The values included are directly related to XY Theta. X,Y,PrevX, PrevY are
used to calculate the displacement between two coordinate points
X and Y speed is how far the robot moves every time the position is updated
Heading is the current angle of the robot
*/
typedef struct
{
	float X;
	float PrevX;
	float Y;
	float PrevY;
	float XSpeed;
	float YSpeed;
	int Heading;
}Robot;

typedef struct
{
	float x;
	float y;
	/*color?*/
}Waypoint;

/*
Encoder struct is a better way of defining an encoder.
Normally, FLL and Vex encoders have 360 ticks per rotation.
Basically 1 tick = 1 degree of encoder movement
more accurate encoders have more ticks/revolution
*/
typedef struct
{
	int currTick;
	int prevTick;
	float gearRatio;
}Encoder;

Robot Bot;
Encoder leftDriveEnc, rightDriveEnc;
Waypoint wayPoint;

//Functions
float CalculateDistance(Encoder EncoderL, Encoder EncoderR);

/*
task that constantly updates the current position of the
robot as it navigates the field.
*/
task UpdatePosition()
{
	while(true)
	{



		float distance = CalculateDistance(leftDriveEnc, rightDriveEnc);

		Bot.Heading = SensorValue[gyro] % 360; //this keeps the robot direction constrained to the range 0-360 degrees

		//calculate the distance the robot has traveled along its path (the hypotenuse)
		Bot.XSpeed = cosDegrees(Bot.Heading) * distance;
		Bot.YSpeed = sinDegrees(Bot.Heading) * distance;
		//updates the robots position based on the displacement calculated above
		Bot.X += Bot.XSpeed;
		Bot.Y += Bot.YSpeed;
		//wait a litte bit to prevent the CPU from getting overworked
		while(time1[T1] < TimeStep){}
		time1[T1] = 0;
	}
}
bool ComparePosition(float x, float X)
{
	if(abs(X-x) < 0.5)
	{
		return true;
	}
	else
	{
		return false;
	}
}

float Minimum(float A, float B)
{
	return A<B?A:B;
}
float Average(float A, float B)
{
	return (A+B)/2.0;
}

//this function calculates the distance traveled between updates
float CalculateDistance(Encoder EncoderL,Encoder EncoderR)
{
	float wheelCircumference = 20.0;
	EncoderL.prevTick = EncoderL.currTick;
	EncoderR.prevTick = EncoderR.currTick;

	EncoderL.currTick = SensorValue[leftDriveEncoder];
	EncoderR.currTick = SensorValue[rightDriveEncoder];
	// 20cm wheel circumfrence
	return EncoderR.gearRatio * wheelCircumference * Average(EncoderL.currTick - EncoderL.prevTick, EncoderR.currTick - EncoderR.prevTick) / 360.0;
}

void Initialize(Robot bot, Encoder encoderL, Encoder encoderR)
{
	SensorValue[gyro] = 0;
	bot.X = 0;
	bot.Y = 0;
	bot.Heading = 0;
	encoderL.currTick = 0;
	encoderR.currTick = 0;
	encoderL.prevTick = 0;
	encoderR.prevTick = 0;
	encoderL.gearRatio = 4.0 / 3.0;
	encoderR.gearRatio = 4.0 / 3.0;
	time1[T1] = 0;
}
