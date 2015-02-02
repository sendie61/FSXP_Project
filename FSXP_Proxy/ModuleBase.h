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

	/**
	  * @brief process the json message
	  */
	virtual bool processMessage(aJsonObject* msg);

	/**
	  * @brief set the communication memoryblock size
	  */
	void setMemorySize(uint8_t memorySize);

	/**
	  * @brief return the size of the communication memoryblock
	  */
	uint8_t getMemorySize() const {
		return memorySize;
	};

	virtual uint8_t writeModule( String iHexString);

	uint8_t	subaddress;


private:
	uint8_t	memorySize;
};

#endif /* MODULEBASE_H_ */