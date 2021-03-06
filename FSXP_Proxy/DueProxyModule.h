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

/**
 * @brief DueProxyModule class
 * descendent of ModuleBase
 * takes care of the handling of DUEPROXY-module
 * messages end commands
 */
class DueProxyModule: public ModuleBase {
public:
	/**
	 * @brief constructor
	 */
	DueProxyModule(uint8_t subaddr = 0);
	virtual ~DueProxyModule();

	/**
	 * @brief process the json message
	 * overrules parent's virtual processMessage()
	 */
	bool processMessage(aJsonObject* msg);

	/**
	 * @brief call parent's setMemorySize
	 * and create a new register block (memoryMap)
	 */
	void setMemorySize(uint8_t memorySize);

	/**
	 * @brief writes (iHEX)data into memoryMap
	 */
	uint8_t writeModule(String iHexString);

	/**
	 * @brief Find the 'dirty'bytes and
	 * do what is necessary only on 'Dirty' bytes
	 */
	void executeDirty();

	/**
	 * @brief do what is necessary on RegAddress in memoryMap
	 */
	bool execute(uint8_t RegAddress);

private:
	void setDirty(uint16_t start, uint8_t length = 1);
	void setClean(uint16_t start, uint8_t length = 1);
	void cleanAll();

	uint16_t dirtyFlags[DUEPROXYMEMSIZE / 16];
	uint8_t* memoryMap;				// startaddress of communication memory
	enum Registers {
		IODIRA = 0,IODIRB,IODIRC,IODIRD,
		IPOLA,IPOLB,IPOLC,IPOLD,
		GPINTENA,GPINTENB,GPINTENC,GPINTEND,
		INTFA,INTFB,INTFC,INTFD,
		INTCAPA,INTCAPB,INTCAPC,INTCAPD,
		GPIOA,GPIOB,GPIOC,GPIOD,
		OLATA,OLATB,OLATC,OLATD,
		SPAREA,SPAREB,SPAREC,SPARED,
		PWM2,PWM2_,
		PWM3,PWM3_,
		PWM5,PWM5_,
		PWM6,PWM6_,
		PWM7,PWM7_,
		PWM8,PWM8_,
		PWM9,PWM9_,
		PWM11,PWM11_,
		PWM12,PWM12_,
		PWM13,PWM13_,
		ADCINTENA,ADCINTENB,ADCINTFA,ADCINTFB,
		ADC0,ADC0_,
		ADC1,ADC1_,
		ADC2,ADC2_,
		ADC3,ADC3_,
		ADC4,ADC4_,
		ADC5,ADC5_,
		ADC6,ADC6_,
		ADC7,ADC7_,
		ADC10,ADC10_,
		ADC11,ADC11_,
		ADC12,ADC12_,
		ADC13,ADC13_
	};

};

#endif /* DUEPROXYMODULE_H_ */
