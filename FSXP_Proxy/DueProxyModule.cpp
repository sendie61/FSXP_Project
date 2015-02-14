/*
 * DueProxyModule.cpp
 *
 *  Created on: Jan 31, 2015
 *      Author: F
 */

#include "DueProxyModule.h"

DueProxyModule::DueProxyModule(uint8_t subaddr) :
		memoryMap(NULL) {
	moduleType = DUEPROXY;
	subaddress = subaddr;
	setMemorySize(DUEPROXYMEMSIZE);
	cleanAll();
}

DueProxyModule::~DueProxyModule() {

	delete this->memoryMap;
}

bool DueProxyModule::processMessage(aJsonObject* msg) {
	bool rv = false;
	if (msg != NULL) {
		aJsonObject* initObj = aJson.getObjectItem(msg, "IHEX");
		if (initObj != NULL) {
			uint16_t arraylen = aJson.getArraySize(initObj);
			for (uint8_t i = 0; i < arraylen; i++)
				writeModule(aJson.getArrayItem(initObj, i)->valuestring);
			rv = true;
		}
	}
	return rv;
}

void DueProxyModule::setMemorySize(uint8_t memorySize) {
	ModuleBase::setMemorySize(memorySize);
	this->memoryMap = new uint8_t(getMemorySize());
	memset(this->memoryMap, 0, getMemorySize());
}

uint8_t DueProxyModule::writeModule(String iHexString) {
	uint8_t wrote = 0;
	IntelHex iHex(iHexString);
	if (iHex.getAddress() + iHex.getLength() < getMemorySize()) {
		setDirty(iHex.getAddress(), iHex.getLength());
		memcpy(this->memoryMap + iHex.getAddress(), iHex.getDataArray(),
				iHex.getLength());  //copy in memoryMap
		wrote = iHex.getLength();
		if (iHex.getType() == EXE) {	//execute the dirty ones
			executeDirty();
		} else if (iHex.getType() == EOF) {	//clean dirtyFlags
			cleanAll();
		}

	}
	return wrote;	// bytes written
}

void DueProxyModule::setDirty(uint16_t start, uint8_t length) {
	if ((start + length) < DUEPROXYMEMSIZE) {
		for (uint8_t adr = start; adr < start + length; adr++) {
			bitSet(dirtyFlags[adr / 16], adr % 16);
		}
	}
}

void DueProxyModule::setClean(uint16_t start, uint8_t length) {
	if ((start + length) < DUEPROXYMEMSIZE) {
		for (uint8_t adr = start; adr < start + length; adr++) {
			bitClear(dirtyFlags[adr / 16], adr % 16);
		}
	}
}

void DueProxyModule::executeDirty() {
	for (uint8_t i = 0; i < DUEPROXYMEMSIZE / 16; i++) {
		if (dirtyFlags[i] != 0) {
			for (uint8_t b = 0; b < 16; b++) {
				if (bitRead(dirtyFlags[i], b)) {
					execute(i * 16 + b);
				}
			}
		}
	}
}

bool DueProxyModule::execute(uint8_t RegAddress) {
	bool rv = false;
	uint8_t b = 0;
	Serial.print("RegAddress=");
	Serial.println(RegAddress);
	switch (RegAddress) {
	case IODIRA:
	case IODIRB:
	case IODIRC:
	case IODIRD:
		for (b = 0; b < 8; b++) {
			pinMode(22 + (RegAddress - IODIRA) * 8 + b,
			bitRead(*(memoryMap+RegAddress) , b) ? INPUT : OUTPUT);
		}
		setClean(RegAddress, 1);
		break;
	case OLATA:
	case OLATB:
	case OLATC:
	case OLATD:
		for (b = 0; b < 8; b++) {
			int adr = 22 + (RegAddress - OLATA) * 8 + b;
			bool dat = bitRead(*(memoryMap + RegAddress), b);
			Serial.print(dat ? 1 : 0);
			Serial.print(", ");
			digitalWrite(adr, dat ? HIGH : LOW);
		}
		Serial.println("");
		setClean(RegAddress, 1);
		break;
	default:
		setClean(RegAddress, 1);
		break;
	}
	return rv;
}

void DueProxyModule::cleanAll() {
	for (uint8_t i = 0; i < DUEPROXYMEMSIZE / 16; i++)
		dirtyFlags[i] = 0;
}
