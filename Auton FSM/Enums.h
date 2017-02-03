
enum States
{
	Start,
	IdleRobot,
	FindObj,
	GoToObj,
	GrabObj,
	UpdateMap,
	GoToFence,
	Score
};

enum SubStates
{
	IdleClaw,
	OpenClaw,
	CloseClaw,
	LiftClaw
};

enum Phase
{
	Instruction,
	Roam
};
