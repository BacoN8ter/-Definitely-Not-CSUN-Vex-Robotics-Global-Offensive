
#define deadzone 30
#define maxpower 127

#define HIGHLIFTLIMIT 3750
#define LOWLIFTLIMIT 2000
#define FENCE_HEIGHT 2900

#define WIDE_CLAW_OPEN 1850
#define CLOSE_CLAW 100
#define MID_OPEN_CLAW 500
#define OPEN_CLAW_LIMIT 3300
#define CLOSE_CLAW_LIMIT 240

int lift_pot,claw_pot,left_enc,right_enc;

task drive_task(){
	while(true){

		int leftStick = vexRT[Ch3];
		int rightStick = vexRT[Ch2];

		if(abs(leftStick) <= deadzone)
			leftStick = 0;

		if(abs(rightStick) <= deadzone)
			rightStick = 0;

		motor[ld1] = leftStick;
		motor[ld2] = leftStick;
		motor[ld3] = leftStick;

		motor[rd1] = rightStick;
		motor[rd2] = rightStick;
		motor[rd3] = rightStick;

	}
}

void drive(){
			int leftStick = vexRT[Ch3];
		int rightStick = vexRT[Ch2];

		if(abs(leftStick) <= deadzone)
			leftStick = 0;

		if(abs(rightStick) <= deadzone)
			rightStick = 0;

		motor[ld1] = leftStick;
		motor[ld2] = leftStick;
		motor[ld3] = leftStick;

		motor[rd1] = rightStick;
		motor[rd2] = rightStick;
		motor[rd3] = rightStick;
}

void lift(){
		if(vexRT[Btn6D] == 1){
			motor[lift1] = maxpower;
			motor[lift2] = maxpower;
		}
		else if(vexRT[Btn6U] == 1 && SensorValue[L_POT] < HIGHLIFTLIMIT){
			motor[lift1] = -maxpower;
			motor[lift2] = -maxpower;
		}
		else {
			motor[lift1] = 0;
			motor[lift2] = 0;
		}
}

void claw(){
		if(vexRT[Btn5D] == 1){
			motor[claw1] = -maxpower;
			motor[claw2] = -maxpower;
		}
		else if(vexRT[Btn5U] == 1){
			motor[claw1] = maxpower;
			motor[claw2] = maxpower;
		}
		else{
			motor[claw1] = 0;
			motor[claw2] = 0;
		}
}

task lift_task(){
	while(true){

		if(vexRT[Btn6D] == 1){
			motor[lift1] = maxpower;
			motor[lift2] = maxpower;
		}
		else if(vexRT[Btn6U] == 1){
			motor[lift1] = -maxpower;
			motor[lift2] = -maxpower;
		}
		else {
			motor[lift1] = 0;
			motor[lift2] = 0;
		}
	}

}

task claw_task(){
	while(true){

		if(vexRT[Btn5D] == 1){
			motor[claw1] = maxpower;
			motor[claw2] = maxpower;
		}
		else if(vexRT[Btn5U] == 1){
			motor[claw1] = -maxpower;
			motor[claw2] = -maxpower;
		}
		else{
			motor[claw1] = 0;
			motor[claw2] = 0;
		}
	}
}

task SensorReader(){

  SensorValue[L_ENC] = 0;
  SensorValue[R_ENC] = 0;
	while(true){
	lift_pot = SensorValue[L_POT];
	claw_pot = SensorValue[C_POT];
	left_enc = SensorValue[L_ENC];
	right_enc = SensorValue[R_ENC];
  }
}
