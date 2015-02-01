/*
 * DueProxyModule.h
 *
 *  Created on: Jan 31, 2015
 *      Author: F
 */

#ifndef DUEPROXYMODULE_H_
#define DUEPROXYMODULE_H_

#include "ModuleBase.h"

#define DUEPROXYMEMSIZE 0x50

class DueProxyModule: public ModuleBase {
public:
	DueProxyModule(uint8_t subaddr = 0);
	virtual ~DueProxyModule();
	bool processMessage(aJsonObject* msg);
	void setMemorySize(uint8_t memorySize);
	uint8_t writeModule(String iHexString);
	void executeDirty();

private:
	void setDirty(uint16_t start, uint8_t length = 1);
	void setClean(uint16_t start, uint8_t length = 1);
	void cleanAll();

	uint16_t dirtyFlags[DUEPROXYMEMSIZE / 16];
	uint8_t* memoryMap;				// startaddress of communication memory
};

#endif /* DUEPROXYMODULE_H_ */
