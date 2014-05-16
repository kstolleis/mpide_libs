

#ifndef HMotor_h
#define HMotor_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class HMotor{
    
public:
    
	HMotor();
	
	void forward(byte lSpd, byte rSpd);
	void backward(byte lSpd, byte rSpd);
	void rotateRight(byte spd);
	void rotateLeft(byte spd);
	void allStop();
	
private:
	
	byte rightSideMotor[2];
	byte rightSidePWM;
	byte leftSideMotor[2];
	byte leftSidePWM;
	byte rightSideCurrent;
	byte leftSideCurrent;
	byte rightSideEnable;
	byte leftSideEnable;
	
	void rightSideForward(byte spd);
	void rightSideBackward(byte spd);
	void leftSideForward(byte spd);
	void leftSideBackward(byte spd);
	
};

#endif
