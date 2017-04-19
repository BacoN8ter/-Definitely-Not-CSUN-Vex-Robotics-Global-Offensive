#include <sensorFunctions.h>
#include <worldsBotManual.h>
/*

task chooseAuton(){


	while(true){

		if(autoBit0 == 1)
			AUTON_CHOICE = 0;

		else if(autoBit1 == 1)
			AUTON_CHOICE = 1;

		else if(autoBit2 == 1)
			AUTON_CHOICE = 2;

		else if(autoBit3 == 1)
			AUTON_CHOICE = 3;

	}
}
*/

task initialLift(){

	Raise_Tower(70,FENCE_HEIGHT);

}

task initialOpenClaw(){

	Close_Claw(70,WIDE_CLAW_OPEN);
}

task keepClawClosed(){

		while(SensorValue[C_POT] > CLOSE_CLAW){

	  }
}

void LeftSquareAuton1(){

	startTask(initialLift);
	startTask(initialOpenClaw);

	moveUp(maxpower,1800);
	Raise_Tower(maxpower,HIGHLIFTLIMIT);
	moveDown(maxpower,900);

	rotateRight(40,420);
	Lower_Tower(100,LOWLIFTLIMIT + 400);

	moveUp(maxpower,100);
	Close_Claw(maxpower,CLOSE_CLAW);

	//Cube is grabbed
	Raise_Tower(maxpower,HIGHLIFTLIMIT);
	moveUp(maxpower,400);
	rotateLeft(40,420);

	moveUp(maxpower,900);
	Open_Claw(maxpower,WIDE_CLAW_OPEN);

	moveDown(maxpower,300);
	rotateRight(40,840);

	Lower_Tower(maxpower,LOWLIFTLIMIT);
	moveUp(maxpower,100);

	Close_Claw(maxpower,CLOSE_CLAW);
	moveDown(maxpower,100);

	Raise_Tower(maxpower,HIGHLIFTLIMIT);
	rotateLeft(40,840);

	moveUp(maxpower,900);
	Open_Claw(maxpower,WIDE_CLAW_OPEN);
/*
	moveDown(maxpower,200);
	rotateLeft(40,840);

	Lower_Tower(maxpower,LOWLIFTLIMIT);
	moveUp(maxpower,100);

	Close_Claw(maxpower,CLOSE_CLAW);
	moveDown(maxpower,100);

  Raise_Tower(maxpower,HIGHLIFTLIMIT);
  rotateRight(40,840);

  moveUp(maxpower,900);
  Open_Claw(maxpower,WIDE_CLAW_OPEN);

  moveDown(maxpower,900);

  */

}

void RightSquareAuton1(){

	startTask(initialLift);
	startTask(initialOpenClaw);

	moveUp(maxpower,1800);
	Raise_Tower(maxpower,HIGHLIFTLIMIT);
	moveDown(maxpower,900);

	rotateLeft(40,420);
	Lower_Tower(100,LOWLIFTLIMIT + 400);

	moveUp(maxpower,100);
	Close_Claw(maxpower,CLOSE_CLAW);

	//Cube is grabbed
	Raise_Tower(maxpower,HIGHLIFTLIMIT);
	moveUp(maxpower,400);
	rotateRight(40,420);

	moveUp(maxpower,900);
	Open_Claw(maxpower,WIDE_CLAW_OPEN);

	moveDown(maxpower,300);
	rotateRight(40,840);

	Lower_Tower(maxpower,LOWLIFTLIMIT);
	moveUp(maxpower,100);

	Close_Claw(maxpower,CLOSE_CLAW);
	moveDown(maxpower,100);

	Raise_Tower(maxpower,HIGHLIFTLIMIT);
	rotateLeft(40,840);

	moveUp(maxpower,900);
	Open_Claw(maxpower,WIDE_CLAW_OPEN);
/*
	moveDown(maxpower,200);
	rotateLeft(40,840);

	Lower_Tower(maxpower,LOWLIFTLIMIT);
	moveUp(maxpower,100);

	Close_Claw(maxpower,CLOSE_CLAW);
	moveDown(maxpower,100);

  Raise_Tower(maxpower,HIGHLIFTLIMIT);
  rotateRight(40,840);

  moveUp(maxpower,900);
  Open_Claw(maxpower,WIDE_CLAW_OPEN);

  moveDown(maxpower,900);

  */

}

void RightSquareAuton2(){

	moveUp(maxpower,600);
	rotateLeft(40,300);

	moveUp(maxpower,100);
	Close_Claw(maxpower,CLOSE_CLAW_LIMIT);

	Raise_Tower(maxpower,HIGHLIFTLIMIT);
	moveUp(maxpower,600);

	rotateRight(40,420);
	moveUp(maxpower,900);

	Open_Claw(maxpower,WIDE_CLAW_OPEN);
  moveDown(maxpower,200);

  rotateLeft(40,840);
  moveUp(maxpower,100);

  Close_Claw(maxpower,CLOSE_CLAW);
  moveDown(maxpower,100);

  Raise_Tower(maxpower,HIGHLIFTLIMIT);
  rotateRight(40,840);

  moveUP(maxpower,900);
  Open_Claw(maxpower,WIDE_CLAW_OPEN);

  moveDown(maxpower,200);

}

void LeftSquareAuton2(){

	moveUp(maxpower,600);
	rotateLeft(40,300);

	moveUp(maxpower,100);
	Close_Claw(maxpower,CLOSE_CLAW_LIMIT);

	Raise_Tower(maxpower,HIGHLIFTLIMIT);
	moveUp(maxpower,600);

	rotateRight(40,420);
	moveUp(maxpower,900);

	Open_Claw(maxpower,WIDE_CLAW_OPEN);
  moveDown(maxpower,200);

  rotateLeft(40,840);
  moveUp(maxpower,100);

  Close_Claw(maxpower,CLOSE_CLAW);
  moveDown(maxpower,100);

  Raise_Tower(maxpower,HIGHLIFTLIMIT);
  rotateRight(40,840);

  moveUP(maxpower,900);
  Open_Claw(maxpower,WIDE_CLAW_OPEN);

  moveDown(maxpower,200);

}
