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
Ultrasound::Ultrasound(byte us_trigger, byte us_echo)
{
	pinMode(us_trigger, OUTPUT);
	pinMode(us_echo, INPUT);
	_us_trigger = us_trigger;
	_us_echo = us_echo;
}

/**
*	Checks for any objects at or within user-specified boundry (in cm)
*	Returns false if clear, true otherwise
**/
bool Ultrasound::collision_detection(float boundry)
{
	if (distance() <= boundry) return true;
	return false;
}

/** 
*	Returns 'float' in CM of distance from ranging device to object
*	See SRF05 doc for information about shape and spread of ultrasonic
*	pattern.  Accurate to 400 cm as per doc.
**/
float Ultrasound::distance()
{
	//50ms delay to ensure no overlap with previous measurements
	delay(50);
	
	//Trigger pulse
	digitalWrite(_us_trigger,HIGH);
	delayMicroseconds(10);
	digitalWrite(_us_trigger,LOW);

	//Convert to cm
	return (pulseIn(_us_echo,HIGH)/58.0);
}

///////////////////
////LEGACY CODE////
///////////////////

/** 
*	Returns 'float' in cm of distance from ranging device to object.
*	This is for use with a single wire tx/rx.
*	See SRF05 doc for information about shape and spread of ultrasonic
*	pattern.  Accurate to 400 cm as per doc.
**/
//  int Ultrasound::swDistance() { 
//    long duration, cm; 
//    pinMode(_us_singleWire, OUTPUT); 
//    digitalWrite(_us_singleWire, LOW); 
//    delayMicroseconds(2); 
//    digitalWrite(_us_singleWire, HIGH); 
//    delayMicroseconds(5); 
//    digitalWrite(_us_singleWire, LOW); 
//    pinMode(_us_singleWire, INPUT); 
//    duration = pulseIn(_us_singleWire, HIGH); // convert the time into a distance 
//     cm = microsecondsToCentimeters(duration); 
//   return cm ; 
// } 


// long Ultrasound::microsecondsToCentimeters(long microseconds) { 
//     return microseconds / 60.0; // The speed of sound is 340 m/s or 29 microseconds per centimeter.
// } 