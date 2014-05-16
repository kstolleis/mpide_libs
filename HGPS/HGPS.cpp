

#include <HGPS.h>

HGPS::HGPS() {

    sec = 0.0;
    min = 0;
    hr = 0;
    time = 0.0;
    lat = 0.0;
    lon = 0.0;
    alt = 0.0;
    valid = false;

    delimiter = ",";

    success = 0;
}

void HGPS::readNMEA() {

    while (Serial1.available() > 0) {

        serialChar = Serial1.read();
        nmeaString += serialChar;

        if (serialChar == '\n') {

            if (nmeaString.startsWith("$GPGGA")) {
                parseGGA(nmeaString);
            }

            nmeaString = "";
        }

    }

}

void HGPS::parseGGA(String nmeaTemp) {

    int delimSet[20];
    int delimIndex = nmeaTemp.indexOf(delimiter);
    int i = 0;
    while (delimIndex != -1) {
        delimSet[i] = delimIndex;
        delimIndex = nmeaTemp.indexOf(delimiter, delimIndex + 1);
        i++;
    }

    char temp[20];
    nmeaTemp.substring(delimSet[0] + 1, delimSet[1]).toCharArray(temp, 20);
    time = atof(temp);
    memset(temp, '0', 20);

    nmeaTemp.substring(delimSet[1] + 1, delimSet[2]).toCharArray(temp, 20);
    lat = ddmmDD(atof(temp));
    memset(temp, '0', 20);

    if(nmeaTemp.substring(delimSet[2] + 1, delimSet[3]) == "S"){
		lat = lat * -1;
	}

    nmeaTemp.substring(delimSet[3] + 1, delimSet[4]).toCharArray(temp, 20);
    lon = ddmmDD(atof(temp));
    memset(temp, '0', 20);

    if(nmeaTemp.substring(delimSet[4] + 1, delimSet[5]) == "W"){
		lon = lon * -1;
	}

    if(nmeaTemp.substring(delimSet[5] + 1, delimSet[6]) != "0"){
		valid = true;
	}

    nmeaTemp.substring(delimSet[8] + 1, delimSet[9]).toCharArray(temp, 20);
    alt = atof(temp);
    memset(temp, '0', 20);

}

double HGPS::ddmmDD(double ddmm){
	double deg = fmod(ddmm, 100);
	double dec = (int) ddmm / 100;
	double nr = (dec + (deg / 60)) * 100000;
	double r = round(nr);
	return r / 100000;
	// convert NMEA ddmm to decimal degrees rounded to 5 decimal places
}

double HGPS::twoPointHeading(double lat1, double lon1, double lat2, double lon2) {
    lat1 = degreesRadians(lat1);
    lon1 = degreesRadians(lon1);
    lat2 = degreesRadians(lat2);
    lon2 = degreesRadians(lon2);
    double denominator = log((tan((lat2 / 2) + (PI / 4))) / (tan((lat1 / 2)+(PI / 4))));
    double numerator = (lon2 - lon1);
    return fmod((radiansDegrees(atan2(numerator, denominator)) + 360), 360);
}

double HGPS::twoPointDistance(double lat1, double lon1, double lat2, double lon2) {
    double theta = twoPointHeading(lat1, lon1, lat2, lon2);
    lat1 = degreesRadians(lat1);
    lat2 = degreesRadians(lat2);
    return (lat2 - lat1) / cos(degreesRadians(theta)) * EARTH_RAD;
}

void HGPS::setAirborne1G() {

    success = 0;
    uint8_t setNav[] = {
        0xB5, 0x62, 0x06, 0x24, 0x24, 0x00, 0xFF, 0xFF, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x10, 0x27, 0x00, 0x00, 0x05, 0x00, 0xFA, 0x00, 0xFA, 0x00, 0x64, 0x00, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0xDC
    };
    while (!success) {
        sendUBX(setNav, sizeof (setNav) / sizeof (uint8_t));
        success = getUBX_ACK(setNav);
    }
}

void HGPS::setAirborne4G() {
    success = 0;
    Serial.println("Setting uBlox nav mode: Airborne < 4G");
    uint8_t setNav[] = {
        0xB5, 0x62, 0x06, 0x24, 0x24, 0x00, 0xFF, 0xFF, 0x08, 0x03, 0x00, 0x00, 0x00, 0x00, 0x10, 0x27, 0x00, 0x00, 0x05, 0x00, 0xFA, 0x00, 0xFA, 0x00, 0x64, 0x00, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x20
    };
    while (!success) {
        sendUBX(setNav, sizeof (setNav) / sizeof (uint8_t));
        success = getUBX_ACK(setNav);
    }
}

void HGPS::setAutomotive() {
    success = 0;
    Serial.println("Setting uBlox nav mode: Automotive");
    uint8_t setNav[] = {
        0xB5, 0x62, 0x06, 0x24, 0x24, 0x00, 0xFF, 0xFF, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x10, 0x27, 0x00, 0x00, 0x05, 0x00, 0xFA, 0x00, 0xFA, 0x00, 0x64, 0x00, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 0x98
    };
    while (!success) {
        sendUBX(setNav, sizeof (setNav) / sizeof (uint8_t));
        success = getUBX_ACK(setNav);
    }
}

void HGPS::set5Hz() {
    success = 0;
    Serial.println("Setting uBlox update rate: 5Hz");
    uint8_t setUpdate[] = {
        0xB5, 0x62, 0x06, 0x08, 0x06, 0x00, 0xC8, 0x00, 0x01, 0x00, 0x01, 0x00, 0xDE, 0x6A
    };
    while (!success) {
        sendUBX(setUpdate, sizeof (setUpdate) / sizeof (uint8_t));
        success = getUBX_ACK(setUpdate);
    }
}

void HGPS::set1Hz() {
    success = 0;
    Serial.println("Setting uBlox update rate: 1Hz");
    uint8_t setUpdate[] = {
        0xB5, 0x62, 0x06, 0x08, 0x06, 0x00, 0xE8, 0x03, 0x01, 0x00, 0x01, 0x00, 0x01, 0x39
    };
    while (!success) {
        sendUBX(setUpdate, sizeof (setUpdate) / sizeof (uint8_t));
        success = getUBX_ACK(setUpdate);
    }
}

void HGPS::set5Sec() {
    success = 0;
    Serial.println("Setting uBlox update rate: 5 sec");
    uint8_t setUpdate[] = {
        0xB5, 0x62, 0x06, 0x08, 0x06, 0x00, 0x88, 0x13, 0x01, 0x00, 0x01, 0x00, 0xB1, 0x49
    };
    while (!success) {
        sendUBX(setUpdate, sizeof (setUpdate) / sizeof (uint8_t));
        success = getUBX_ACK(setUpdate);
    }
}

void HGPS::set10Sec() {
    success = 0;
    Serial.println("Setting uBlox update rate: 10 sec");
    uint8_t setUpdate[] = {
        0xB5, 0x62, 0x06, 0x08, 0x06, 0x00, 0x10, 0x27, 0x01, 0x00, 0x01, 0x00, 0xB4D, 0xDD
    };
    while (!success) {
        sendUBX(setUpdate, sizeof (setUpdate) / sizeof (uint8_t));
        success = getUBX_ACK(setUpdate);
    }
}

void HGPS::sbasOff() {
    success = 0;
    Serial.println("Setting uBlox SBAS: OFF");
    uint8_t setUpdate[] = {
        0xB5, 0x62, 0x06, 0x16, 0x08, 0x00, 0x00, 0x03, 0x03, 0x00, 0x51, 0x62, 0x06, 0x00, 0xE3, 0x27
    };
    while (!success) {
        sendUBX(setUpdate, sizeof (setUpdate) / sizeof (uint8_t));
        success = getUBX_ACK(setUpdate);
    }
}

void HGPS::allButGGA() {

    success = 0;
    uint8_t setGLL[] = {
        0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x2B
    };
    while (!success) {
        sendUBX(setGLL, sizeof (setGLL) / sizeof (uint8_t));
        success = getUBX_ACK(setGLL);
    }

    success = 0;
    uint8_t setGSA[] = {
        0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x32
    };
    while (!success) {
        sendUBX(setGSA, sizeof (setGSA) / sizeof (uint8_t));
        success = getUBX_ACK(setGSA);
    }

    success = 0;
    uint8_t setGSV[] = {
        0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x39
    };
    while (!success) {
        sendUBX(setGSV, sizeof (setGSV) / sizeof (uint8_t));
        success = getUBX_ACK(setGSV);
    }

    success = 0;
    uint8_t setRMC[] = {
        0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x04, 0x40
    };
    while (!success) {
        sendUBX(setRMC, sizeof (setRMC) / sizeof (uint8_t));
        success = getUBX_ACK(setRMC);
    }

    success = 0;
    uint8_t setVTG[] = {
        0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x46
    };
    while (!success) {
        sendUBX(setVTG, sizeof (setVTG) / sizeof (uint8_t));
        success = getUBX_ACK(setVTG);
    }

}

void HGPS::sendUBX(uint8_t *MSG, uint8_t len) {
    for (int i = 0; i < len; i++) {
        Serial1.write(MSG[i]);
        //Serial.print(MSG[i], HEX);
    }
    Serial1.println();
}

bool HGPS::getUBX_ACK(uint8_t *MSG) {
    uint8_t b;
    uint8_t ackByteID = 0;
    uint8_t ackPacket[10];
    unsigned long startTime = millis();

    ackPacket[0] = 0xB5; // header
    ackPacket[1] = 0x62; // header
    ackPacket[2] = 0x05; // class
    ackPacket[3] = 0x01; // id
    ackPacket[4] = 0x02; // length
    ackPacket[5] = 0x00;
    ackPacket[6] = MSG[2]; // ACK class
    ackPacket[7] = MSG[3]; // ACK id
    ackPacket[8] = 0; // CK_A
    ackPacket[9] = 0; // CK_B

    for (uint8_t i = 2; i < 8; i++) {
        ackPacket[8] = ackPacket[8] + ackPacket[i];
        ackPacket[9] = ackPacket[9] + ackPacket[8];
    }

    while (1) {
        if (ackByteID > 9) {
            return true;
        }

        if (millis() - startTime > 3000) {
            return false;
        }

        if (Serial1.available()) {
            b = Serial1.read();

            if (b == ackPacket[ackByteID]) {
                ackByteID++;
                //Serial.print(b, HEX);
            } else {
                ackByteID = 0;
            }
        }
    }
}


