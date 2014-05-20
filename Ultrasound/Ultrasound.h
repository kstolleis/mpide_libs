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

		Ultrasound();
		Ultrasound(byte triggerIn, byte echoIn);
		
		//Functions
		bool collisionDetection(float boundary);
		int distance();
	
	private:
		//Variables
		byte usTrigger, usEcho;
};

#endif
