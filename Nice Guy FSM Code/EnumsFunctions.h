#include "Enums.h"
#include "TestTracking.c"

SubStates subState = IdleClaw;
Phase phase = Instruction;

States IdleRobotState(States state)
{
	Stop();
	/*"roaming phase" -> findObj*/
	/*"instruction phase" -> GoToObj*/
	if(phase == Roam)
	{
	}
	if(phase == Instruction)
	{
		return GoToObj;
	}
	else
	{
		return IdleRobot;
	}
}

States FindObjState(States state)
{
	/* search for object */
}

States GoToObjState(States state)
{
	/*at obj position and see it -> GrabObj*/
	Move(wayPoint.x,wayPoint.y);
	if(ComparePosition(Bot.X, wayPoint.x) && ComparePosition(Bot.Y,wayPoint.y))
	{
		return GrabObj;
	}
	else
	{
		return GoToObj;
	}
}

States GrabObjState(States state)
{
	switch(subState)
			{
			case IdleClaw:
			subState = OpenClaw;
				break;

			case OpenClaw:
			/*open the claw*/
			/*Drive forward to pick up obj*/
			subState = CloseClaw;
				break;

			case CloseClaw:
			/*CloseClaw*/
			subState = LiftClaw;
				break;

			case LiftClaw:
			/*obj has been grabbed and lifted -> update map*/
			return UpdateMap;
				break;
			}
			return GrabObj;
}

States UpdateMapState(States state)
{
	/*map updated -> GoToFence*/
	if(true)
	{
		return GoToFence;
	}
	else
	{
		return UpdateMap;
	}
}

States GoToFenceState(States state)
{
	/*found a fence spot ->score*/
	if(true)
	{
		return Score;
	}
	else
	{
	}
}

States ScoreState(States state)
{
		switch(subState)
			{
			case LiftClaw:
			/*lift Claw and approach fence*/
			subState = OpenClaw;
				break;

			case OpenClaw:
			/*Open claw*/
			subState = IdleClaw;
				break;

			case IdleClaw:
			/*obj have been dropped -> idle state*/
			/*get distance and low claw again*/
			return IdleRobot;
				break;
			}
			return Score;
}
