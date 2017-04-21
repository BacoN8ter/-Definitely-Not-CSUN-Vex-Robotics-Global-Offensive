
#include <UART.h>
#include <worldsBotManual.h>

void moveUp(int power, int dist);
void moveDown(int power,int dist);
void rotateLeft(int power, int dist);
void rotateRight(int power, int dist);
void Raise_Tower(int power,int height);

void turnOffClaw();
//=========================================================================
// Drive Functions
//=========================================================================
void PowerToAllDriveMotors(int power){
		motor[ld1] = power;
		motor[ld2] = power;
		motor[ld3] = power;

		motor[rd1] = power;
		motor[rd2] = power;
		motor[rd3] = power;

}

void moveUp(int power, int dist){


	int moveTo = SensorValue[L_ENC] + dist;

	while(SensorValue[L_ENC] < moveTo){
		PowerToAllDriveMotors(power);
    }

  PowerToAllDriveMotors(0);
  wait10Msec(50);

}

void moveDown(int power, int dist){

	int moveTo = SensorValue[L_ENC] - dist;

	while(SensorValue[L_ENC] >  moveTo){
		PowerToAllDriveMotors(-power);
    }

   PowerToAllDriveMotors(0);
   wait10Msec(50);

}

void rotateToAngle(int angle){



	//determine if the robot needs to turn left or right depending
	// on its current angle and the angle passed in
  //Turn Left
	if (jetsonSensors.yaw < angle){

		while(jetsonSensors.yaw < angle){
				motor[ld1] = -50;
				motor[ld2] = -50;
				motor[ld3] = -50;

				motor[rd1] = 50;
				motor[rd2] = 50;
				motor[rd3] = 50;

		}
	}
	else if(jetsonSensors.yaw > angle){

		while(jetsonSensors.yaw > angle){

				motor[ld1] = 50;
				motor[ld2] = 50;
				motor[ld3] = 50;

				motor[rd1] = -50;
				motor[rd2] = -50;
				motor[rd3] = -50;
		}

	}

	PowerToAllDriveMotors(0);

}
void rotateLeft(int power,int dist){


		int rotateTo = SensorValue[L_ENC] - dist;


		while(SensorValue[L_ENC] > rotateTo){
			motor[ld1] = -power;
			motor[ld2] = -power;
			motor[ld3] = -power;

			motor[rd1] = power;
			motor[rd2] = power;
			motor[rd3] = power;

		}

		PowerToAllDriveMotors(0);

		wait10Msec(50);

}

void rotateRight(int power,int dist){


		int rotateTo = SensorValue[L_ENC] + dist;


		while(SensorValue[L_ENC] < rotateTo){
			motor[ld1] = power;
			motor[ld2] = power;
			motor[ld3] = power;

			motor[rd1] = -power;
			motor[rd2] = -power;
			motor[rd3] = -power;

		}

		PowerToAllDriveMotors(0);

		wait10Msec(50);

}

//=========================================================================
// Tower Functions
//=========================================================================

void Raise_Tower(int power, int height){

    time1[T1] = 0;
	int time_step = time1[T1];

	while(SensorValue[L_POT] < height && time1[T1]< time_step +1100){
		motor[lift1] = -power;
		motor[lift2] = -power;
	}

	motor[lift1] = 0;
	motor[lift2] = 0;

	wait10Msec(20);

}


//PID Raise_Tower:
void Raise_Tower_PID(int power, int height){


	int pGain = 0.3;
	int iGain = 0.2;
	int dGain = 0.1;

	int error = height - SensorValue[L_POT];
	int error_sum = 0;

	time1[T1] = 0;

	while(error > 100){

		error = height - SensorValue[L_POT];
		error_sum = error_sum + error;

		int p1 = error;
		int t1 = time1[T1];
		wait10Msec(2);
		int p2 = height- SensorValue[L_POT];
		int t2 = time1[T1];
		int derive_e = (p2-p1)/(t2-t1);

		int speed = (error * pGain) + (error_sum * iGain) + (derive_e * dGain);

		motor[lift1] = -speed;
		motor[lift2] = -speed;
	}

	motor[lift1] = 0;
	motor[lift2] = 0;

}

void Lower_Tower(int power, int height){

    time1[T1] = 0;
	int time_step = time1[T1];

	while(SensorValue[L_POT] > height && time1[T1]< time_step +1100){
		motor[lift1] = power;
		motor[lift2] = power;
	}

	motor[lift1] = 0;
	motor[lift2] = 0;

	wait10Msec(20);

}
//=========================================================================
// Claw Functions
//=========================================================================
void Close_Claw(int power,int wide){

	time1[T1] = 0;
	int time_step = time1[T1];

	//Close Claw
	while (SensorValue[C_POT] > wide && SensorValue[C_POT] > 0 && time1[T1]< time_step +2800){

		motor[claw1] = -power;
		motor[claw2] = -power;

	}

	motor[claw1] = 0;
	motor[claw2] = 0;
	wait10Msec(20);

}

void Close_Claw(int time)
{
	int power = maxpower;
	motor[claw1] = power;
	motor[claw2] = power;

	wait1Msec(time);

	motor[claw1] = 40;
	motor[claw2] = 40;

}

void Open_Claw(int power, int wide){

	time1[T1] = 0;
	int time_step = time1[T1];

	//Open Claw
	while(SensorValue[C_POT] < wide && SensorValue[C_POT] < OPEN_CLAW_LIMIT && time1[T1]< time_step +1800){

		motor[claw1] = power;
		motor[claw2] = power;

	}

  turnOffClaw();
	wait10Msec(20);


}


void Open_Claw(int time)
{
	int power = maxpower;
	motor[claw1] = -power;
	motor[claw2] = -power;

	wait1Msec(time);

	motor[claw1] = 0;
	motor[claw2] = 0;

}

void turnOffClaw(){

	motor[claw1] = 0;
	motor[claw2] = 0;
}
