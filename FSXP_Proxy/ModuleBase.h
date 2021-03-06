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
#include "stdio.h"
/**
 * @brief abstract class ModuleBase
 * all module classes descent from here
 */
class ModuleBase {
public:
	/**
	 * @brief constructor
	 */
	ModuleBase(uint8_t subaddr = 0, uint8_t memSize = 0);

	virtual ~ModuleBase();

	/**
	 * @brief process the json message
	 * MUST be implemented by the descendant classes
	 */
	virtual bool processMessage(aJsonObject* msg)=0;

	/**
	 * @brief set the communication memoryblock size
	 */
	void setMemorySize(uint8_t memorySize);

	/**
	 * @brief return the size of the communication memoryblock
	 */
	uint8_t getMemorySize() const {
		return memorySize;
	}
	;

	/**
	 * @brief is this object addres by type and subAddr?
	 */
	virtual uint8_t writeModule(String iHexString);

	/**
	 * @brief is this object addres by type and subAddr?
	 */
	bool isAddressed(uint8_t type, uint8_t subAddr);

	/**
	 * @brief getter ModuleType
	 */
	modules_type getModuleType() const {
		return moduleType;
	}

	/**
	 * @brief getter subAddr
	 */
	uint8_t getSubaddress() const {
		return subaddress;
	}

protected:
	/**
	 * @brief subAddr
	 */
	uint8_t subaddress;
	/**
	 * @brief moduleType
	 */
	modules_type moduleType;

private:
	uint8_t memorySize;
};

#endif /* MODULEBASE_H_ */
