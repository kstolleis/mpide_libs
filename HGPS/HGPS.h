#include <stdio.h>
#include <math.h>
#include "UnitConversions.h"

#ifndef HGPS_h
#define HGPS_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#ifndef PI
#define PI 3.14159265358979323846264338327950288419716939937510
#endif
#ifndef EARTH_RAD
#define EARTH_RAD 6371000.0 // meters at sea level
#endif

class HGPS {
public:

    HGPS();

    int hr, min;
    double time, sec, lat, lon, alt;
    bool valid;

    void readNMEA();

    static double twoPointHeading(double lat1, double lon1, double lat2, double lon2);
    static double twoPointDistance(double lat1, double lon1, double lat2, double lon2);

	static double ddmmDD(double ddmm);

    void setAirborne1G();
    void setAirborne4G();
    void setAutomotive();
    void set5Hz();
    void set1Hz();
    void set5Sec();
    void set10Sec();
    void sbasOff();
    void allButGGA();

private:

    String nmeaString;
	String delimiter;
    char serialChar;

	void parseGGA(String nmeaTemp);
	void parseRMC();
	void parseVTG();
	void parseGLL();

    long success;
    void sendUBX(uint8_t *MSG, uint8_t len);
    bool getUBX_ACK(uint8_t *MSG);

};

#endif
