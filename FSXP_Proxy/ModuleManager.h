/*
 * ModuleManager.h
 *
 *  Created on: Jan 31, 2015
 *      Author: F
 */

#ifndef MODULEMANAGER_H_
#define MODULEMANAGER_H_

#include "ModuleBase.h"

typedef struct moduleItem{
	ModuleBase* module;
	moduleItem* nextItem;
};

class ModuleManager {
public:
	ModuleManager();
	virtual ~ModuleManager();

	moduleItem* addModule(ModuleBase* newModule);
	void emptyList(void);
private:
	moduleItem* moduleList;
	moduleItem* lastModule;
};

#endif /* MODULEMANAGER_H_ */
