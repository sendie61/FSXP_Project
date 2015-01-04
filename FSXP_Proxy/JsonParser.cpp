/*
 * JsonParser.cpp
 *
 *  Created on: Jan 3, 2015
 *      Author: F
 */

#include "JsonParser.h"

JsonParser::JsonParser() {
	// TODO Auto-generated constructor stub

}

JsonParser::~JsonParser() {
	// TODO Auto-generated destructor stub
}

bool JsonParser::Json2IP(IPAddress& IpAddr, aJsonObject* aJsonObj) {
	bool rc = false;

	if (aJsonObj != NULL) {
		for (int c = 0; c < aJson.getArraySize(aJsonObj); c++) {
			IpAddr[c] = (uint8_t) aJson.getArrayItem(aJsonObj, c)->valueint;
		}
		rc = true;
	}
	return rc;
}

bool JsonParser::Json2MAC(uint8_t* MACAddr, aJsonObject* aJsonObj) {
	bool rc = false;

	if (aJsonObj != NULL) {
		for (int c = 0; c < aJson.getArraySize(aJsonObj); c++) {
			MACAddr[c] = (uint8_t) aJson.getArrayItem(aJsonObj, c)->valueint;
		}
		rc = true;
	}
	return rc;
}

bool JsonParser::readFile2String(String& aStr, char* filename) {
	bool rc = false;

	const int SS_SD_CARD = 4;
	const int SS_ETHERNET = 10;

	pinMode(SS_SD_CARD, OUTPUT);
	digitalWrite(SS_SD_CARD, HIGH);  // SD Card not active
	pinMode(SS_ETHERNET, OUTPUT);
	digitalWrite(SS_ETHERNET, HIGH);  // Ethernet Card not active

	if (!SD.begin(SS_SD_CARD)) {
		Serial.println(F("SD CARD initialization failed!"));
		return rc;
	}

	File dataFile = SD.open(filename);
	if (dataFile) {	// if the file is available, read it:
		while (dataFile.available()) {
			aStr += (char) dataFile.read();
		}
		dataFile.close();
		rc = true;
	}
	// if the file isn't open, pop up an error:
	else {
		Serial.print(F("error opening "));
		Serial.println(filename);
	}
	digitalWrite(SS_SD_CARD, HIGH);  // SD Card not active
	return rc;
}
