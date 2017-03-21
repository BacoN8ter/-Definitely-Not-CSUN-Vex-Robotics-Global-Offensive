#define AUTONDEADZONE 50

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
			error = (abs(error) > AUTONDEADZONE) ? error : AUTONDEADZONE;
			SetDrive(error);
			wait1Msec(1);
			travel = (SensorValue[leftDriveEncoder] + SensorValue[rightDriveEncoder]) / 2;
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
			error = (abs(error) > AUTONDEADZONE) ? error : sgn(error) * AUTONDEADZONE;
			SetDrive(error);
			wait1Msec(1);
			travel = (SensorValue[leftDriveEncoder] + SensorValue[rightDriveEncoder]) / 2;
	}
	SetDrive(0);
}

void TurnGyro(int angle)
{
	SensorValue[gyro] = 0;
	float kp = 0.05;

	while(abs(SensorValue[gyro] - angle) > 10)
	{
		float error = angle - SensorValue[gyro];
		error = abs(error * kp) < AUTONDEADZONE ? sgn(error) * AUTONDEADZONE : error * kp;
		SetDriveTurn(-error);
		wait1Msec(10);
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
			error = (abs(error) > AUTONDEADZONE) ? error : AUTONDEADZONE;
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
			error = (abs(error) > AUTONDEADZONE) ? error : AUTONDEADZONE;
			SetDriveTurn(-error);
			wait1Msec(1);
			travel = SensorValue[leftDriveEncoder];
	}
	SetDrive(0);
}

task StarLift()
{
	SetLift(-127);
	wait1Msec(800);
	SetLift(-10);
}

task HighLift()
{
	SetLift(-127);
	wait1Msec(1000);
	SetLift(-80);
}

task LowLift()
{
	SetLift(127);
	wait1Msec(1500);
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
	SetClaw(110);
}

task CloseClawNonBlocking()
{
	SetClaw(127);
	wait1Msec(1000);
	SetClaw(90);
}

task CloseClawSlight()
{
	SetClaw(127);
	wait1Msec(100);
	SetClaw(0);
}

task UpdateSensors()
{
	clawPotentiometer.value = SensorValue[clawPot];
	liftPotentiometer.value = SensorValue[liftPot];
}
