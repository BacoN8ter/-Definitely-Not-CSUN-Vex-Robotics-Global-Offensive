#include "Enums.h"
#include "TestTracking.c"

SubStates subState = IdleClaw;
Phase phase = Instruction;

void IdleRobotState(States *state)
{
	Stop();
	/*"roaming phase" -> findObj*/
	/*"instruction phase" -> GoToObj*/
	if(phase == Roam)
	{
	}
	if(phase == Instruction)
	{
		*state = GoToObj;
	}
}

void FindObjState(States *state)
{
	/*object found -> GoToObj*/
}

void GoToObjState(States *state)
{
	/*at obj position and see it -> GrabObj*/
}

void GrabObjState(States *state)
{
	switch(subState)
			{
			case IdleClaw:
				break;

			case OpenClaw:
				break;

			case CloseClaw:
				break;

			case LiftClaw:
			/*obj has been grabbed and lifted -> update map*/
				break;
			}
}

void UpdateMapState(States *state)
{
	/*map updated -> GoToFence*/
}

void GoToFenceState(States *state)
{
	/*found a fence spot ->score*/
}

void ScoreState(States *state)
{
		switch(subState)
			{
			case LiftClaw:
				break;

			case OpenClaw:
				break;

			case IdleClaw:
			/*obj have been dropped -> idle state*/
				break;
			}
}
