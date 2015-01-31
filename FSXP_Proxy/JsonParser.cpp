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

aJsonObject* JsonParser::parseFile(char* filename) {
	aJsonObject* root = NULL;

	File dataFile = SD.open(filename);
	if (dataFile) {	// if the file is available, read it:
		aJsonStream file_stream(&dataFile);
		root = aJson.parse(&file_stream);
		dataFile.close();
	}
	// if the file can't be opened, pop up an error:
	else {
		Serial.print(F("error opening "));
		Serial.println(filename);
	}

	return root;
}

