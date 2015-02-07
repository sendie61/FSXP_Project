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

ModuleBase* ModuleManager::getModule(uint8_t moduleType, uint8_t subAddr) {
	ModuleBase* foundModule = NULL;
	moduleItem* moduleItter = moduleList;
	// look if module already exists.
	while (moduleItter) {
		if (moduleItter->module->isAddressed(moduleType, subAddr))
			foundModule = moduleItter->module;
	}
	if (!foundModule){
		// create a new one...
		switch (moduleType){
		case DUEPROXY:
			foundModule= (ModuleBase*) new DueProxyModule(subAddr);
			break;
		case I2C_IO:
			// TODO			foundModule= (ModuleBase*) new I2cIoModule(subAddr);
			break;
		case SPI_LDISP:
			// TODO			foundModule= (ModuleBase*) new SpiLdispModule(subAddr);
			break;
		case I2C_ARD:
			// TODO			foundModule= (ModuleBase*) new I2cArdModule(subAddr);
			break;
		default:
			break;
		}
		if (foundModule)
			addModule(foundModule);
	}
	return foundModule;
}

bool ModuleManager::processMessage(aJsonObject* msg) {
	String iHexString;
	modules_type moduleType= UNKNOWN;
	ModuleBase* foundModule= NULL;
	uint8_t subaddr=0;
	uint16_t arraylen=0;
	bool rv = false;
	if (msg != NULL) {
		aJsonObject* modObj = aJson.getObjectItem(msg, modType[moduleType]);
		if (modObj != NULL) {
			moduleType= I2C_IO;
			if ((arraylen = aJson.getArraySize(modObj))!=0){
				for (uint8_t i = 0; i < arraylen; i++){
					uint8_t subaddr = aJson.getObjectItem(modObj, "-subaddr")->valueint;
					if ((foundModule=getModule(moduleType,subaddr))!=NULL){
						foundModule->processMessage(modObj);
					}
				}
			}
		}
	}
	return rv;
}

moduleItem* ModuleManager::addModule(ModuleBase* newModule) {
	moduleItem* newItem = new (moduleItem);
	newItem->module=newModule;
	newItem->nextItem=NULL;
	if (newItem) {
		if (lastModule)
			lastModule->nextItem = newItem;
		else
			moduleList = newItem;
		lastModule = newItem;
	}
	return newItem;
}

