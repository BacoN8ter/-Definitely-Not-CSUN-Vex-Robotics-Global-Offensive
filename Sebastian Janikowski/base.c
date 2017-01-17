#pragma config(Motor,  port1,           leftClaw,      tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           left1,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           left2,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           left3,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           leftLift,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           rightLift,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           right3,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           right2,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           right1,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          rightClaw,     tmotorVex393_HBridge, openLoop, reversed)

#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"
#include "driverControl.h"

void pre_auton()
{

  bStopTasksBetweenModes = true;

}

task autonomous()
{

  AutonomousCodePlaceholderForTesting();
}

task usercontrol()
{
  // User control code here, inside the loop

  while (true)
  {
    drive();
    lift();
    claw();
  }
}
