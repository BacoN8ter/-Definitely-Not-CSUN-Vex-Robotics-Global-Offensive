
/*
	Drive

	Function for user control that is based off tank drive
	ch3 <- left drive
	ch2 <- right drive
	Only assigns if above a DEADZONE
*/
#define DEADZONE 15

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
