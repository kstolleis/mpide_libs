/* Library for SRF05 Ultrasonic Ranger
*	on Arduino platform
*	Rev 10/23/11
*	Joshua Hecker
*/

#include <Ultrasound.h>

/**
*	Empty constructor
**/
Ultrasound::Ultrasound(){}

/**
*	Constructor args are pins for trigger, echo, instantions of Compass and Movement classes
*	and last arg for pin for use in single wire mode (see initial comment block)
**/
Ultrasound::Ultrasound(byte triggerIn, byte echoIn)
{
	pinMode(triggerIn, OUTPUT);
	pinMode(echoIn, INPUT);
	usTrigger = triggerIn;
	usEcho = echoIn;
}

/**
*	Checks for any objects at or within user-specified boundry (in cm)
*	Returns false if clear, true otherwise
**/
bool Ultrasound::collisionDetection(float boundary)
{
	if (distance() <= boundary) return true;
	return false;
}

/** 
*	Returns 'int' in CM of distance from ranging device to object
*	See SRF05 doc for information about shape and spread of ultrasonic
*	pattern.  Accurate to 400 cm as per doc.
**/
int Ultrasound::distance()
{
	
	//Trigger pulse
	digitalWrite(usTrigger,HIGH);
	delayMicroseconds(10);
	digitalWrite(usTrigger,LOW);

	//Convert to cm
	return (int)(pulseIn(usEcho,HIGH)/58.0);
}

