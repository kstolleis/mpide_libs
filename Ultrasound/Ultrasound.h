/* Library for SRF05 Ultrasonic Ranger
*	on Arduino platform
*	Rev 10/23/11
*	Joshua Hecker
*/

#ifndef Ultrasound_h
#define Ultrasound_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class Ultrasound
{
	public:
		//Constructors
		Ultrasound();
		Ultrasound(byte us_trigger, byte us_echo);
		
		//Functions
		bool collision_detection(float boundry);
		float distance();
		
		//Legacy Functions
		//int swDistance();
		//long microsecondsToCentimeters(long microseconds);
	
	private:
		//Variables
		byte _us_trigger, _us_echo;
};

#endif