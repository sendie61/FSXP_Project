/*
 * IntelHex.cpp
 *
 *  Created on: Jan 27, 2015
 *      Author: F
 */

#include "IntelHex.h"

IntelHex::IntelHex() :
		valid(false), type(DAT), length(0), address(0) {
	// TODO Auto-generated constructor stub
}

IntelHex::IntelHex(String& aStr) :
		valid(false), type(DAT), length(0), address(0) {
	setDataArray(aStr);
}

IntelHex::~IntelHex() {
	// TODO Auto-generated destructor stub
}

void IntelHex::setDataArray(String& aStr) {
	if (validate(aStr)) {
		parse(aStr);
	}
}

uint8_t* IntelHex::getDataArray() {
	return dataArray;
}

uint8_t IntelHex::getLength() {
	return length;
}

recordTypes IntelHex::getType() {
	return type;
}

bool IntelHex::isValid() {
	return valid;
}

uint16_t IntelHex::getAddress() const {
	return address;
}

bool IntelHex::validate(String& aStr) {
	valid = false;
	uint8_t checksum = 0, i, len = aStr.length();
	if ((len >= 11) && (len < 44)) {		// must be  11 < n < 44
		if (aStr[0] == ':') {				// first char must be ':'
			type = recordTypes(hex2dec(aStr[7]) * 16 + hex2dec(aStr[8])); // save 'type'
			if ((type == END && len == 11) || (type == EXE && len == 11) || type == DAT) {	// if EOF -> NO DATA
				for (i = 1; i < len; i += 2) {	// itterate through string
					checksum += (hex2dec(aStr[i]) * 16 + hex2dec(aStr[i + 1]));
				}
				if (checksum == 0)
					valid = true;
			}
		}
	}
	return valid;
}

void IntelHex::parse(String& aStr) {
	uint8_t i, j = 9, len = aStr.length();
	length = hex2dec(aStr[1]) * 16 + hex2dec(aStr[2]);
	address = (hex2dec(aStr[3]) * 16 + hex2dec(aStr[4])) * 256L
			+ hex2dec(aStr[5]) * 16 + hex2dec(aStr[6]);
	type = recordTypes(hex2dec(aStr[7] * 16 + hex2dec(aStr[8])));

	for (i = 0; i < length; i++) {		// itterate through string
		dataArray[i] = hex2dec(aStr[j++]) * 16 + hex2dec(aStr[j++]);
	}
}

uint8_t IntelHex::hex2dec(unsigned char c) {
	if (c >= '0' && c <= '9') {
		return c - '0';
	} else if (c >= 'A' && c <= 'F') {
		return c - 'A' + 10;
	} else if (c >= 'a' && c <= 'f') {
		return c - 32 - 'A' + 10;
	}
	return 0;
}

