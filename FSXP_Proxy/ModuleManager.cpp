/*
 * ModuleManager.cpp
 *
 *  Created on: Jan 31, 2015
 *      Author: F
 */

#include "ModuleManager.h"

ModuleManager::ModuleManager(){
	// TODO Auto-generated constructor stub

}

ModuleManager::~ModuleManager() {
	// TODO Auto-generated destructor stub
}

bool ModuleManager::processMessage(aJsonObject* msg) {
	modules_type moduleType= DUEPROXY;
	ModuleBase* foundModule= NULL;
	uint8_t subaddr=0;
	uint16_t arraylen=0;
	bool rv = false;
	if (msg != NULL) {
		aJsonObject* modObj = aJson.getObjectItem(msg, modType[moduleType]);
		if (modObj != NULL) {
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

ModuleBase* ModuleManager::getModule(uint8_t moduleType, uint8_t subAddr) {
	ModuleBase* foundModule = NULL;
	int moduleItter = 0;
	// look if module already exists.
	while ( moduleItter < moduleList.size() && !foundModule) {
		if (moduleList.operator [](moduleItter)->isAddressed(moduleType, subAddr))
			foundModule =moduleList.operator [](moduleItter);
		moduleItter++;
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

void ModuleManager::addModule(ModuleBase* newModule) {
	moduleList.push_back(newModule);
}

