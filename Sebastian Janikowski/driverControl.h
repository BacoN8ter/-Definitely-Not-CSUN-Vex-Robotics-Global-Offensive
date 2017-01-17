#define DEADZONE 20

//declare method
void drive();
void lift();
void claw();


void drive()
{
	int rightPower = vexRT[Ch2];
	int leftPower = vexRT[Ch3];

	rightPower = abs(rightPower) < DEADZONE ? 0 : rightPower;
	leftPower = abs(leftPower) < DEADZONE ? 0 : leftPower;

	motor[left1] = leftPower;
	motor[left2] = leftPower;
	motor[left3] = leftPower;

	motor[right1] = rightPower;
	motor[right2] = rightPower;
	motor[right3] = rightPower;

}

void lift()
{
	if(vexRT[Btn5U])
	{
		motor[leftLift] = 127;
		motor[rightLift] = 127;
	}
	else if(vexRT[Btn5D])
	{
		motor[leftLift] = -127;
		motor[rightLift] = -127;
	}
	else
	{
		motor[leftLift] = 0;
		motor[rightLift] = 0;
	}
}

void claw()
{
	if(vexRT[Btn6U])
	{
		motor[leftClaw] = 127;
		motor[rightClaw] = 127;
	}
	else if(vexRT[Btn6D])
	{
		motor[leftClaw] = -127;
		motor[rightClaw] = -127;
	}
	else
	{
		motor[leftClaw] = 0;
		motor[rightClaw] = 0;
	}
}
