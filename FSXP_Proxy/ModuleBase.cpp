/*
 * ModuleBase.cpp
 *
 *  Created on: Jan 31, 2015
 *      Author: F
 */

#include "ModuleBase.h"

ModuleBase::ModuleBase(uint8_t subaddr, uint8_t memSize) :
		subaddress(0), memorySize(0) {
	moduleType=UNKNOWN;
	this->subaddress = subaddr;
	setMemorySize(memSize);
}

ModuleBase::~ModuleBase() {

}

void ModuleBase::setMemorySize(uint8_t memorySize) {
	this->memorySize = memorySize;
}

bool ModuleBase::isAddressed(uint8_t type, uint8_t subAddr) {
	return (getModuleType()==type && getSubaddress()==subAddr);
}
