
#include <UnitConversions.h>
#include <stdio.h>
#include <math.h>

#ifndef PI
#define PI 3.14159265358979323846264338327950288419716939937510
#endif

double radiansDegrees(double rads){
    return rads * (180 / PI);
}

double degreesRadians(double deg){
    return deg * (PI / 180);
}

double metersFeet(double met){
    return met * 3.2808399;
}

double feetMeters(double ft){
    return ft / 3.2808399;
}