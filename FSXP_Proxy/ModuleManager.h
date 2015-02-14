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

/**
 * @brief ModuleManager manages all modules
 * search for existing modules
 * create new module objects.
 * route messages to the corresponding modules
 */
class ModuleManager {
public:
	ModuleManager();
	virtual ~ModuleManager();
	/**
	 * @brief takes care of routing the message to the addressed module
	 */
	bool processMessage(aJsonObject* msg);

	/**
	 * @brief find the module with corresponding 'type' and 'subaddr'
	 * in the list of managed modules
	 * and creates a new one if not found.
	 */
	ModuleBase* getModule(uint8_t moduleType, uint8_t subAddr);

	/**
	 * @brief create a new module and add it to the list
	 */
	void addModule(ModuleBase* newModule);
private:
	Vector<ModuleBase*> moduleList;
};

#endif /* MODULEMANAGER_H_ */
