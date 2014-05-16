/* 	Library for Sparkfun MonsterMoto Shield
 Karl A. Stolleis - Author
 2/19/12 Revision 1
 */

#include <HMotor.h>

/**
 Constructor establishes values for all motor pins
 and sets all pins to output mode.  allStop() is
 called to prevent premature motion.
 **/
HMotor::HMotor(){
	
	rightSideMotor[0] = 7; // A side
	rightSideMotor[1] = 8; // B side
	rightSidePWM = 5;
	leftSideMotor[0] = 4; // A side
	leftSideMotor[1] = 9; // B side
	leftSidePWM = 6;
	rightSideCurrent = A2;
	leftSideCurrent = A3;
	rightSideEnable = A0;
	leftSideEnable = A1;
	
	pinMode(rightSideMotor[0], OUTPUT);
	pinMode(rightSideMotor[1], OUTPUT);
	pinMode(rightSidePWM, OUTPUT);
	pinMode(leftSideMotor[0], OUTPUT);
	pinMode(leftSideMotor[1], OUTPUT);
	pinMode(leftSidePWM, OUTPUT);
	
	allStop();
	
}


/**
 Sets forward motion at using args for each side of vehicle.
 Speed values are constrained between useable min and max for
 PWM values.  Uses private helper functions for each side.
 **/
void HMotor::forward(byte lSpd, byte rSpd){
	
	lSpd = constrain(lSpd, 100, 255);
	rSpd = constrain(rSpd, 100, 255);
	
	leftSideForward(lSpd);
	rightSideForward(rSpd);
	
}

/**
 Sets backward motion at using args for each side of vehicle.
 Speed values are constrained between useable min and max for
 PWM values.  Uses private helper functions for each side.
 **/
void HMotor::backward(byte lSpd, byte rSpd){
	
	lSpd = constrain(lSpd, 100, 255);
	rSpd = constrain(rSpd, 100, 255);
	
	leftSideBackward(lSpd);
	rightSideBackward(rSpd);
	
}

/**
 Uses single PWM value to cause rotation right.  Both sides
 of vehicle will use same motor speed for rotation.
 Uses private helper functions for each side.
 **/
void HMotor::rotateRight(byte spd){
	
	leftSideForward(spd);
	rightSideBackward(spd);
	
}

/**
 Uses single PWM value to cause rotation left.  Both sides
 of vehicle will use same motor speed for rotation.
 Uses private helper functions for each side.
 **/
void HMotor::rotateLeft(byte spd){
	
	leftSideBackward(spd);
	rightSideForward(spd);
	
}

/**
 Stops all motor motion by setting all digital motor pin values
 to LOW and both PWM values to zero.
 **/
void HMotor::allStop(void){
	
	digitalWrite(rightSideMotor[0], LOW);
	digitalWrite(rightSideMotor[1], LOW);
	digitalWrite(leftSideMotor[0], LOW);
	digitalWrite(leftSideMotor[1], LOW);
	analogWrite(rightSidePWM, 0);
	analogWrite(leftSidePWM, 0);
	
}

/**
 Sets right side motors to forward motion by setting motor
 pin 8 to HIGH and PWM value to arg on pin 5
 **/
void HMotor::rightSideForward(byte spd){
	
	digitalWrite(rightSideMotor[1], HIGH);
	analogWrite(rightSidePWM, spd);
	
}

/**
 Sets right side motors to reverse motion by setting motor
 pin 7 to HIGH and PWM value to arg on pin 5.
 **/
void HMotor::rightSideBackward(byte spd){
	
	digitalWrite(rightSideMotor[0], HIGH);
	analogWrite(rightSidePWM, spd);
	
}

/**
 Sets left side motors to forward motion by setting motor
 pin 9 to HIGH and PWM value to arg on pin 6.
 **/
void HMotor::leftSideForward(byte spd){
	
	digitalWrite(leftSideMotor[1], HIGH);
	analogWrite(leftSidePWM, spd);
	
}

/**
 Sets left side motors to forward motion by setting motor
 pin 4 to HIGH and PWM value to arg on pin 6.
 **/
void HMotor::leftSideBackward(byte spd){
	
	digitalWrite(leftSideMotor[0], HIGH);
	analogWrite(leftSidePWM, spd);
	
}

// TODO - set up functions to make use of current sense and enable pins
// Current sense is analog data - analogRead(pin)
// Enable is digital function

