/*
 * JsonParser.h
 *
 *  Created on: Jan 3, 2015
 *      Author: F
 */

#ifndef JSONPARSER_H_
#define JSONPARSER_H_

#include <aJSON.h>
#include <SD.h>
#include <IPAddress.h>

	/**
	  * @brief Class with 'aJson' helper functions
	  * used for initializing TCPcommunication
	  * and parsing FSXP-protocol messages.
	  */
class JsonParser {
public:
	JsonParser();
	virtual ~JsonParser();

	/**
	  * @brief Convert aJson array to IPAddress
	  * used for initializing TCPcommunication
	  */
	bool Json2IP(IPAddress& IpAddr, aJsonObject* aJsonObj);

	/**
	  * @brief Convert aJson array to a MACAddress
	  * used for initializing TCPcommunication
	  * the MACAddress is a uint8_t[6]
	  */
	bool Json2MAC(uint8_t* MACAddr, aJsonObject* aJsonObj);

	bool readFile2String(String& aStr, char * filename);
};

#endif /* JSONPARSER_H_ */
