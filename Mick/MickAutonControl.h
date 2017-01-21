
struct Potentiometer{
	int value;
	int minValue;
	int maxValue;
};

Potentiometer liftPotentiometer;
Potentiometer clawPotentiometer;

//helper functions
void SetDrive(int power)
{
		motor[leftDriveBack] = power;
		motor[leftDriveCenter] = power;
		motor[leftDriveFront] = power;

		motor[rightDriveBack] = power;
		motor[rightDriveCenter] = power;
		motor[rightDriveFront] = power;
}

void SetDriveTurn(int power)
{
		motor[leftDriveBack] = -power;
		motor[leftDriveCenter] = -power;
		motor[leftDriveFront] = -power;

		motor[rightDriveBack] = power;
		motor[rightDriveCenter] = power;
		motor[rightDriveFront] = power;
}


void SetClaw(int power)
{
	  motor[leftRoller] = power;
	  motor[rightRoller] = power;
}

void SetLift(int power)
{
		motor[leftLift] = power;
		motor[rightLift] = power;
}


void MoveForward(int distance)
{
	SensorValue[rightDriveEncoder] = 0;
	SensorValue[leftDriveEncoder] = 0;

	int travel = 0;
	while(travel < distance)
	{
			int error = distance - travel;
			error = (abs(error) > DEADZONE) ? error : DEADZONE;
			SetDrive(error);
			wait1Msec(1);
			travel = SensorValue[leftDriveEncoder] + SensorValue[rightDriveEncoder] / 2;
	}
	SetDrive(0);
}

void MoveBackward(int distance)
{
	SensorValue[rightDriveEncoder] = 0;
	SensorValue[leftDriveEncoder] = 0;

	int travel = 0;
	while(travel > distance)
	{
			int error = distance - travel;
			error = (abs(error) > DEADZONE) ? error : DEADZONE;
			SetDrive(error);
			wait1Msec(1);
			travel = SensorValue[leftDriveEncoder] + SensorValue[rightDriveEncoder] / 2;
	}
	SetDrive(0);
}

void TurnLeft(int degrees)
{
	SensorValue[rightDriveEncoder] = 0;
	SensorValue[leftDriveEncoder] = 0;
	int travel = 0;
	while(travel < degrees)
	{
			int error = degrees - travel;
			error = (abs(error) > DEADZONE) ? error : DEADZONE;
			SetDriveTurn(error);
			wait1Msec(1);
			travel = SensorValue[rightDriveEncoder];
	}
	SetDrive(0);
}

void TurnRight(int degrees)
{
	SensorValue[leftDriveEncoder] = 0;
	SensorValue[rightDriveEncoder] = 0;
	int travel = 0;
	while(travel < degrees)
	{
			int error = degrees - travel;
			error = (abs(error) > DEADZONE) ? error : DEADZONE;
			SetDriveTurn(-error);
			wait1Msec(1);
			travel = SensorValue[leftDriveEncoder];
	}
	SetDrive(0);
}

task StarLift()
{
	SetLift(-127);
	wait1Msec(725);
	SetLift(0);
}

task HighLift()
{
	SetLift(-127);
	wait1Msec(1000);
	SetLift(-40);
}

task LowLift()
{
	SetLift(127);
	wait1Msec(1000);
	SetLift(0);
}

task OpenClaw()
{
	SetClaw(-127);
	wait1Msec(800);
	SetClaw(0);
	/*
	float proportion = 5;
	int error = clawPotentiometer.maxValue - clawPotentiometer.value;
	while(abs(error) > 5)
	{
		SetClaw(error * proportion);
		error = clawPotentiometer.maxValue - clawPotentiometer.value;
	}
	*/
}

void ReleasePayload()
{
	SetClaw(-127);
	wait1Msec(1000);
	SetClaw(0);
}

void CloseClaw()
{
	SetClaw(127);
	wait1Msec(1000);
	SetClaw(100);
}

task UpdateSensors()
{
	clawPotentiometer.value = SensorValue[clawPot];
	liftPotentiometer.value = SensorValue[liftPot];
}
