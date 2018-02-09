
void setDrive(int x, int y) {

	int left  = (y + x) / 2;
	int right = (y - x) / 2;

	motor[drvFrontRight] = right;
	motor[drvBackRight]  = right;

	motor[drvFrontLeft]  = left;
	motor[drvBackLeft]   = left;
}

void driveControl() {

	int a = (abs(vexRT[Ch4]) > DEADZONE) ? (vexRT[Ch4]) : (0);
	int b = (abs(vexRT[Ch3]) > DEADZONE) ? (vexRT[Ch3]) : (0);

	if (INV_DRV_A) {
		a *= -1;
		b *= -1;
	}

	if (INV_DRV_B) setDrive(b, a);
	else           setDrive(a, b);
}

void setLift(int speed) {
	motor[leftLowerLiftMotor]  = speed;
	motor[leftUpperLiftMotor]  = speed;
	motor[rightLowerLiftMotor] = speed;
	motor[rightUpperLiftMotor] = speed;
}

void liftControl() {
	if (vexRT[Btn8R]) {
		setLift(LIFT_SPEED);
	} else if (vexRT[Btn8L]) {
		setLift(-1 * LIFT_SPEED);
	} else {
		setLift(MOTOR_OFF);
	}
}

void setLEDs(int red = -1, int yellow = -1, int green = -1) {
	if (red    > -1 && red    < 2) SensorValue[LEDred]    = red;
	if (yellow > -1 && yellow < 2) SensorValue[LEDyellow] = yellow;
	if (green  > -1 && green  < 2) SensorValue[LEDgreen]  = green;
}

void halt() {
	setDrive(MOTOR_OFF, MOTOR_OFF);
	setLift(MOTOR_OFF);
}

void lockdown() {
	while(true) {
		halt();
	}
}

bool killSwitch() {
	if (vexRT[Btn7D] == 1 && vexRT[Btn8D] == 1) {
		killSwitchState = true;
		halt();
	} else if (vexRT[Btn7U] == 1 && vexRT[Btn8U] == 1) {
		killSwitchState = false;
	}

	if (killSwitchState) setLEDs(1);
	else                 setLEDs(0);

	return killSwitchState;
}
