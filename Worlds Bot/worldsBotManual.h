
#define deadzone 30
#define maxpower 127

#define HIGHLIFTLIMIT 3750
#define LOWLIFTLIMIT 1900
#define FENCE_HEIGHT 2900

#define WIDE_CLAW_OPEN 1850
#define CLOSE_CLAW 100
#define MID_OPEN_CLAW 500
#define OPEN_CLAW_LIMIT 3300
#define CLOSE_CLAW_LIMIT 0

task drive(){
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

task lift(){
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

task claw(){
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

	//right_enc = SensorValue[R_ENC];
}
