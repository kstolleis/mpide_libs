
#include <HCompass.h>

void HCompass::compassInit(){
    
  	Wire.begin();
    
}

float HCompass::head() {
    
	uint8_t MSB,LSB;
	int tempHead;
    
	Wire.beginTransmission(comSlave);
	Wire.send(comRead);
	Wire.endTransmission();
	
	delayMicroseconds(700);
	
	Wire.requestFrom(comSlave, (byte) 2);
	MSB = Wire.receive();
	LSB = Wire.receive();
	
	tempHead = (MSB << 8) + LSB;
    tempHead = (tempHead + 3600) % 3600;

	return tempHead / 10.0;
    
}

int HCompass::roundHead() {
    
    uint8_t MSB,LSB;
	int tempHead;
    
	Wire.beginTransmission(comSlave);
	Wire.send(comRead);
	Wire.endTransmission();
	
	delayMicroseconds(700);
	
	Wire.requestFrom(comSlave, (byte) 2);
	MSB = Wire.receive();
	LSB = Wire.receive();
	
	tempHead = (MSB << 8) + LSB;
    tempHead = (tempHead + 3600) % 3600;
    
	return tempHead / 10;
    
}