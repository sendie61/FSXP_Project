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
	bool execute( uint8_t RegAddress);
private:
	void setDirty(uint16_t start, uint8_t length = 1);
	void setClean(uint16_t start, uint8_t length = 1);
	void cleanAll();

	uint16_t dirtyFlags[DUEPROXYMEMSIZE / 16];
	uint8_t* memoryMap;				// startaddress of communication memory
	enum Registers {
		IODIRA = 0,
		IODIRB,
		IODIRC,
		IODIRD,
		IPOLA,
		IPOLB,
		IPOLC,
		IPOLD,
		GPINTENA,
		GPINTENB,
		GPINTENC,
		GPINTEND,
		INTFA,
		INTFB,
		INTFC,
		INTFD,
		INTCAPA,
		INTCAPB,
		INTCAPC,
		INTCAPD,
		GPIOA,
		GPIOB,
		GPIOC,
		GPIOD,
		OLATA,
		OLATB,
		OLATV,
		OLATD,
		SPAREA,
		SPAREB,
		SPAREC,
		SPARED,
		PWM2,
		PWM2_,
		PWM3,
		PWM3_,
		PWM5,
		PWM5_,
		PWM6,
		PWM6_,
		PWM7,
		PWM7_,
		PWM8,
		PWM8_,
		PWM9,
		PWM9_,
		PWM11,
		PWM11_,
		PWM12,
		PWM12_,
		PWM13,
		PWM13_,
		ADCINTENA,
		ADCINTENB,
		ADCINTFA,
		ADCINTFB,
		ADC0,
		ADC0_,
		ADC1,
		ADC1_,
		ADC2,
		ADC2_,
		ADC3,
		ADC3_,
		ADC4,
		ADC4_,
		ADC5,
		ADC5_,
		ADC6,
		ADC6_,
		ADC7,
		ADC7_,
		ADC10,
		ADC10_,
		ADC11,
		ADC11_,
		ADC12,
		ADC12_,
		ADC13,
		ADC13_
	};

};

#endif /* DUEPROXYMODULE_H_ */
