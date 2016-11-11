#pragma config(Motor,  port2,           liftLeft,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           liftRight,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           liftExtra,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           driveFrontLeft, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           driveBackLeft, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           driveFrontRight, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           driveBackRight, tmotorVex393_MC29, openLoop)

#include "DriverControl.h"

task main()
{
	while(true)
	{
		Drive();
		Lift();
	}
}
