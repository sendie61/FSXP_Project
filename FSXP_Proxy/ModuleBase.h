/*
 * ModuleBase.h
 *
 *  Created on: Jan 31, 2015
 *      Author: F
 */

#ifndef MODULEBASE_H_
#define MODULEBASE_H_

#include "JsonParser.h"
#include "FSXP_constants.h"
#include "IntelHex.h"

class ModuleBase {
public:
	ModuleBase(uint8_t subaddr=0, uint8_t memSize=0);

	virtual ~ModuleBase();

	const modules_t getModuleId() const {
		return moduleId;
	}

	/**
	  * @brief process the json message
	  */
	virtual bool processMessage(aJsonObject* msg);

	/**
	  * @brief Creates the communication memoryblock
	  */
	void setMemorySize(uint8_t memorySize);

	/**
	  * @brief return the size of the communication memoryblock
	  */
	uint8_t getMemorySize() const {
		return memorySize;
	};

	uint8_t writeMemory( String iHexString);

	uint8_t	subaddress;

	uint8_t* memoryMap;				// startaddress of communication memory

private:
	uint8_t	memorySize;
	const modules_t	moduleId;		// the moduleId << 8 + subaddress, should be unique
};

#endif /* MODULEBASE_H_ */
