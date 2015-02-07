/*
 * ModuleManager.h
 *
 *  Created on: Jan 31, 2015
 *      Author: F
 */

#ifndef MODULEMANAGER_H_
#define MODULEMANAGER_H_

#include "ModuleBase.h"
#include "DueProxyModule.h"

typedef struct moduleItem {
	ModuleBase* module;
	moduleItem* nextItem;
};

class ModuleManager {
public:
	ModuleManager();
	virtual ~ModuleManager();
	bool processMessage(aJsonObject* msg);
	ModuleBase* getModule(uint8_t moduleType, uint8_t subAddr);
	moduleItem* addModule(ModuleBase* newModule);
private:
	moduleItem* moduleList;
	moduleItem* lastModule;
};

#endif /* MODULEMANAGER_H_ */
