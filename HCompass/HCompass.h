
#ifndef HCompass_h
#define HCompass_h

//#if defined(ARDUINO) && ARDUINO >= 100
//#include "Arduino.h"
//#else
#include "WProgram.h"
//#endif
  
#include <Wire.h>

class HCompass {

	public:

    static void compassInit();
    static float head();
    static int roundHead();

	private:
    
    const static uint8_t comSlave = 0x42 >> 1;
    const static uint8_t comRead = 0x41;

};

#endif