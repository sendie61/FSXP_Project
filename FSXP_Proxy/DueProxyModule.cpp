/*
 * DueProxyModule.cpp
 *
 *  Created on: Jan 31, 2015
 *      Author: F
 */

#include "DueProxyModule.h"

DueProxyModule::DueProxyModule(uint8_t subaddr) :
		memoryMap(NULL) {

	this->subaddress = subaddr;
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
	memset(this->memoryMap,0,getMemorySize());
}

uint8_t DueProxyModule::writeModule(String iHexString) {
	uint8_t wrote = 0;
	IntelHex iHex(iHexString);
	if (iHex.getAddress() + iHex.getLength() < getMemorySize()) {
		setDirty(iHex.getAddress(), iHex.getLength());
		memcpy(this->memoryMap + iHex.getAddress(), iHex.getDataArray(),
				iHex.getLength());  //copy in memoryMap
		wrote = iHex.getLength();
		if (iHex.getType()==EXE){	//execute the dirty ones

		}
		else if (iHex.getType()==EOF){	//clean dirtyFlags
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

void DueProxyModule::cleanAll() {
	for (uint8_t i = 0; i < DUEPROXYMEMSIZE / 16; i++)
		dirtyFlags[i] = 0;
}
