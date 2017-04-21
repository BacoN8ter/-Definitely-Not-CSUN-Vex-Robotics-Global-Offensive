#include <sensorFunctions.h>
#include <worldsBotManual.h>


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


}

void RightSquareAuton1(){

	startTask(initialLift);
	startTask(initialOpenClaw);

	moveUp(maxpower,1800);
	Raise_Tower(maxpower,HIGHLIFTLIMIT);
	moveDown(maxpower,900);

	rotateLeft(40,380);
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
	moveUp(maxpower,650);
	startTask(initialOpenClaw);

	rotateLeft(60,450);

	moveUp(maxpower,400);
	//Close_Claw(maxpower,CLOSE_CLAW_LIMIT);
	Close_Claw(2000);

	Raise_Tower(maxpower,HIGHLIFTLIMIT);

	moveUp(maxpower,600);

	rotateRight(40,520);
	moveUp(maxpower,900);

	//Open_Claw(maxpower,WIDE_CLAW_OPEN);
	Open_Claw(1000);
	//cube scored

	//Open_Claw(maxpower,WIDE_CLAW_OPEN);
	moveDown(maxpower,300);


	rotateRight(40,840);
	Lower_Tower(maxpower,LOWLIFTLIMIT);
	moveUp(maxpower, 200);
	Close_Claw(2000);

	Raise_Tower(maxpower, HIGHLIFTLIMIT);
	rotateRight(60, 800);
	moveUP(maxpower,1100);

	Open_Claw(600);

}

void LeftSquareAuton2(){

	startTask(initialOpenClaw);
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


void RightSquareWallRoutine(){

//----------------------------------------------------------------
// Part 1 - Score 4 farzone stars
//----------------------------------------------------------------
	//Lift tower,close claw, lower tower
	startTask(initialLift);
	//Raise_Tower(maxpower,FENCE_HEIGHT);
	moveDown(maxpower,100);
	Close_Claw(1500);

	wait10Msec(50);

	//Lower Tower
	Lower_Tower(maxpower,LOWLIFTLIMIT);
	Open_Claw(50);

	moveUp(maxpower,2400);

	moveDown(maxpower,200);
	Raise_Tower(maxpower,HIGHLIFTLIMIT);

	Turn(/*A degrees towards the fence*/);

	moveDown(1000);

	startTask(keepLiftUp);

	moveUp(maxpower,1800);

	Open_Claw(900);

	stopTask(keepLiftUp);
	turnOffClaw();
	
//----------------------------------------------------------------
// Part 2 - Score Center Cube
//----------------------------------------------------------------
	moveDown(maxpower,1800);

	Turn(/*A degrees towards the starting position*/);

	moveUp(maxpower,1000);

	Turn(/*A degrees towards the cube*/);

	Lower_Tower(maxpower,LOWLIFTLIMIT);

	moveUp(maxpower,100);

	keepClawClosed(900);

	Raise_Tower(maxpower,HIGHLIFTLIMIT);

	int cube_check = cubeCheck();

	if(cube_Check == 1){

		Turn(/*90 degrees to the Left*/);

		moveUp(maxpower,300);

		Turn(/*To the fence*/);

	}

	moveUp(maxpower,1700);

	Open_Claw(900);
	
//----------------------------------------------------------------
// Part 3 - Search the field and Score Objects
//----------------------------------------------------------------

	moveDown(maxpower,900);

	Turn(/*Turn with bot facing east*/);

	moveDown(1500);

	Lower_Tower(maxpower,LOWLIFTLIMIT);

	//Start Searching:

}
