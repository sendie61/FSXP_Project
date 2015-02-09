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
#include "vector.h"

class ModuleManager {
public:
	ModuleManager();
	virtual ~ModuleManager();
	bool processMessage(aJsonObject* msg);
	ModuleBase* getModule(uint8_t moduleType, uint8_t subAddr);
	void addModule(ModuleBase* newModule);
private:
	Vector<ModuleBase*> moduleList;
};

#endif /* MODULEMANAGER_H_ */
