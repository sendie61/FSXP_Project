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
	  * @brief IntelHEX recordTypes
	  * EXE is a new one:
	  *   Directly execute these values
	  */

enum recordTypes {
	DAT = 0, END, EXTSS, STRSA, EXTLA, STRLA, EXE
};

/**
 * @brief Convert INTELhex string to char array
 * used for parsing json hex arrays
 */
class IntelHex {
public:
	IntelHex();
	IntelHex(String& aStr);
	virtual ~IntelHex();

	/**
	 * @brief Validates and parses INTELhex string
	 */
	void setDataArray(String& aStr);

	/**
	 * @brief returns the 16-byte HEX data
	 */
	uint8_t *getDataArray();

	/**
	 * @brief returns the number of bytes in dataArray
	 */
	uint8_t getLength();

	/**
	 * @brief returns IntelHEX recordType
	 */
	recordTypes getType();

	/**
	 * @brief returns TRUE if validate passed
	 */
	bool isValid();

	/**
	 * @brief returns the start address
	 */
	uint16_t getAddress() const;

private:
	/**
	 * @brief Validates INTELhex string
	 * checks syntax, length and type
	 */
	bool validate(String& aStr);

	/**
	 * @brief parses INTELhex string
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
	recordTypes type;
	uint8_t length;
	uint16_t address;
};

#endif /* INTELHEX_H_ */
