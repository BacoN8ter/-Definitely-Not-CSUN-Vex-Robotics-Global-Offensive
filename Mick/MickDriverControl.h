
/*
Drive

Function for user control that is based off tank drive
ch3 <- left drive
ch2 <- right drive
Only assigns if above a DEADZONE
*/
#define DEADZONE 40

void Drive()
{
	int rightPower = vexRT[Ch2];
	int leftPower = vexRT[Ch3];

	rightPower = (abs(rightPower) > DEADZONE) ? rightPower : 0;
	leftPower = (abs(leftPower) > DEADZONE) ? leftPower : 0;

	motor[leftDriveBack] = leftPower;
	motor[leftDriveCenter] = leftPower;
	motor[leftDriveFront] = leftPower;

	motor[rightDriveBack] = rightPower;
	motor[rightDriveCenter] = rightPower;
	motor[rightDriveFront] = rightPower;

}

/*
Lift controls
6U to
6D to lower Lift
*/
void Lift()
{
	if(vexRT[Btn6U]==1){
		motor[leftLift] =   -127;
		motor[leftLift2] =  -127;
		motor[rightLift] =  -127;
		motor[rightLift2] = -127;
	}
	else if(vexRT[Btn6D]==1){
		motor[leftLift] =   127;
		motor[leftLift2] =  127;
		motor[rightLift] =  127;
		motor[rightLift2] = 127;
	}
	else
	{
		motor[leftLift] =   0;
		motor[leftLift2] =  0;
		motor[rightLift] =  0;
		motor[rightLift2] = 0;
	}
}

bool Pressed = false;
void Claw()
{
	//needs pnuematics
	if(vexRT[Btn5U] && !Pressed)
	{
		ClawPosition = !ClawPosition;
		SensorValue[ClawPort] = ClawPosition;
		Pressed = true;
	}
	else if(!vexRT[Btn5U])
	{
		Pressed = false;
	}
}
