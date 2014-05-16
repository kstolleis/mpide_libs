
#include <HUS.h>

HUS::HUS(uint8_t signalPin) {
    
    ping = signalPin;
    
}

bool HUS::collision(int bound) {
	if (dist() <= bound){
        return true;
    } else {
        return false;
    }
    
}

int HUS::dist() {

    pinMode(ping, OUTPUT);
    digitalWrite(ping, LOW);
    delayMicroseconds(2);
    digitalWrite(ping, HIGH);
    delayMicroseconds(5);
    digitalWrite(ping, LOW);
    pinMode(ping, INPUT);

        unsigned long time = pulseIn(ping, HIGH) / 2;

        return min((time / 29.0), maxDist);
    
}

