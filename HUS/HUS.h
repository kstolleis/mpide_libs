
#ifndef HUS_h
#define HUS_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class HUS {
    
public:
    
    HUS(uint8_t signalPin);
    
    bool collision(int bound);
    int dist();
	
private:

    const static int maxDist = 275;
    uint8_t ping;
    
};

#endif