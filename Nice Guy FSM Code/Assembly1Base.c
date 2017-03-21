#pragma config(Sensor, dgtl1,  leftDriveEncoder, sensorQuadEncoder)
#pragma config(Sensor, dgtl11, rightDriveEncoder, sensorQuadEncoder)
#pragma config(Motor,  port1,           rightClaw,     tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           rightBack,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           rightFront,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           rightTop,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           rightLift,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           leftLift,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           leftFront,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           leftTop,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           leftBack,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          leftClaw,      tmotorVex393_HBridge, openLoop)

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"
#include "SillyAutonFunctions.h"
/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/



void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks
  // running between Autonomous and Driver controlled modes. You will need to
  // manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task autonomous()
{
  // ..........................................................................
  // Insert user code here.
  // ..........................................................................

  // Remove this function call once you have "real" code.
  AutonomousCodePlaceholderForTesting();
}

void DriverControl();
bool Locked = false;
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task usercontrol()
{
  // User control code here, inside the loop

  while (true)
  {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................
		DriverControl();
    UserControlCodePlaceholderForTesting();
  }
}

void DriverControl()
{
	if(abs(vexRT[Ch2]) > 10)
	{
		motor[leftBack] = vexRT[Ch2];
		motor[leftFront] = vexRT[Ch2];
		motor[leftTop] = vexRT[Ch2];
	}
	else
	{
		motor[leftBack] = 0;
		motor[leftFront] = 0;
		motor[leftTop] = 0;
	}
	if(abs(vexRT[Ch3]) >10)
	{
		motor[rightBack] = vexRT[Ch3];
		motor[rightFront] = vexRT[Ch3];
		motor[rightTop] = vexRT[Ch3];
	}
	else
	{
		motor[rightBack] = 0;
		motor[rightFront] = 0;
		motor[rightTop] = 0;
	}
	if(vexRT[Btn6U])
	{
		motor[leftLift] = 127;
		motor[rightLift] = 127;
	}
	else if(vexRT[Btn6D])
	{
			motor[leftLift] = -127;
			motor[rightLift] = -127;
	}
	else
	{
		motor[leftLift] = 0;
		motor[rightLift] = 0;
	}


	if(vexRT[Btn5D])
	{
		motor[leftClaw] = -127;
		motor[rightClaw] = -127;
		Locked = false;
	}
	if(vexRT[Btn8R] || Locked)
	{
		Locked = true;
		motor[leftClaw] = 90;
		motor[rightClaw] = 90;
	}
	else if(vexRT[Btn5U])
	{
		motor[leftClaw] = 127;
		motor[rightClaw] = 127;
	}
	else
	{
		motor[leftClaw] = 0;
		motor[rightClaw] = 0;
	}
}
