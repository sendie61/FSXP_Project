/*
 * ModuleBase.cpp
 *
 *  Created on: Jan 31, 2015
 *      Author: F
 */

#include "ModuleBase.h"

ModuleBase::ModuleBase(uint8_t subaddr, uint8_t memSize) :
		moduleId(UNKNOWN), subaddress(0), memoryMap(NULL), memorySize(0) {

	this->subaddress = subaddr;
	setMemorySize(memSize);
}

ModuleBase::~ModuleBase() {

	delete this->memoryMap;
}

bool ModuleBase::processMessage(aJsonObject* msg) {
	bool rv = false;
	rv = true;
	return rv;
}

void ModuleBase::setMemorySize(uint8_t memorySize) {
	this->memorySize = memorySize;
	this->memoryMap = new uint8_t(memorySize);
}

uint8_t ModuleBase::writeMemory(String iHexString) {
	uint8_t wrote = 0;
	IntelHex iHex(iHexString);
	if (iHex.getType() == DAT) {
		if (iHex.getAddress() + iHex.getLength() < this->memorySize) {
			memcpy(this->memoryMap + iHex.getAddress(), iHex.getDataArray(),
					iHex.getLength());  //copy in memoryMap
			wrote = iHex.getLength();
		}
	}
	return wrote;
}
