/*
 * IntelHex.h
 *
 *  Created on: Jan 27, 2015
 *      Author: F
 */

#ifndef INTELHEX_H_
#define INTELHEX_H_

#include <stdint.h>
#include <WString.h>

	/**
	  * @brief Convert INTELhex string to char array
	  * used for parsing json hex arrays
	  */
class IntelHex {
public:
	IntelHex();
	IntelHex(String& aStr);
	virtual ~IntelHex();
	void setDataArray(String& aStr);
	uint8_t *getDataArray();
	uint8_t getLength();
	uint8_t getType();
	bool isValid();
	uint16_t getAddress() const;

private:
	/**
	  * @brief Validates INTELhex string
	  * checks syntax, length and type
	  */
	bool validate(String& aStr);

	/**
	  * @brief parse INTELhex string
	  * converts the ASCII value's to hex array
	  */
	void parse(String& aStr);

	/**
	  * @brief hex to decimal converter
	  * converts the ASCII value's to hex array
	  * for 1 BYTE
	  */
	uint8_t hex2dec(unsigned char c);
	uint8_t dataArray[16];
	bool valid;
	uint8_t type;
	uint8_t length;
	uint16_t address;
};

#endif /* INTELHEX_H_ */
