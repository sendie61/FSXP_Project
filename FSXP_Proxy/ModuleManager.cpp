/*
 * ModuleManager.cpp
 *
 *  Created on: Jan 31, 2015
 *      Author: F
 */

#include "ModuleManager.h"

ModuleManager::ModuleManager() :
		moduleList(NULL), lastModule(NULL) {
	// TODO Auto-generated constructor stub

}

ModuleManager::~ModuleManager() {
	// TODO Auto-generated destructor stub
}

moduleItem* ModuleManager::addModule(ModuleBase* newModule) {
	moduleItem* newItem= new(moduleItem);
	if (newItem){
		if (lastModule)
			lastModule->nextItem= newItem;
		else
			moduleList= newItem;
		lastModule= newItem;
	}
	return newItem;
}

void ModuleManager::emptyList(void) {
	moduleItem* current= moduleList;
	moduleItem* next= moduleList;

	while (next->nextItem){

	}
}
