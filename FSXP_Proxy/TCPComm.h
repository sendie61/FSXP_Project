/*
 * TCPComm.h
 *
 *  Created on: Nov 15, 2014
 *      Author: F
 */

#ifndef TCPCOMM_H_
#define TCPCOMM_H_

#include <Ethernet.h>
#include <EthernetClient.h>

#include "JsonParser.h"
#include "Timer.h"
#include "ModuleManager.h"

#define MSG_SOH	0x01
#define MSG_HEADER_LEN 	7

#define CHECKSTATEPERIOD 5000L	// every 5 seconds a state-check

const char tcpstate[4][11] PROGMEM
= { "INIT      ", "CONNECTING", "CONNECTED ", "UNKNOWN   " };

/**
 * @brief clientSettings structure
 */
typedef struct {
	/** our mac address */
	uint8_t mac[6];
	/** our IP */
	IPAddress ip;
	/** server's IP */
	IPAddress server;
	/** DNS server IP */
	IPAddress DNS;
	/** gateway IP */
	IPAddress gateway;
	/** subnet */
	IPAddress subnet;
	/** server's port */
	uint16_t port;
} clientSettings;

/**
 * @brief EthernetClient handles the reception of FSXP-plugin data
 */
class TCPComm: public EthernetClient {
public:
	TCPComm();
	/**
	  * @brief setup() initialize TCPCommunication
	  * reads settings from ini- (json) file on SD-card
	  */
	void setup(char * iniFilename);

	/**
	  * @brief loop() main loop
	  * check for received data and
	  * update checkstate timer
	  */
	void loop();

	/**
	  * @brief check TCP/IP state
	  * automatic mechanism to try establish a connection, when lost
	  */
	void checkState();

	/**
	  * @brief check for received data
	  * and hand it to the moduleManager
	  */
	void checkForData();

	/**
	  * @brief setup the TCP/IP connection
	  */
	int8_t start();

	/**
	  * @brief send message to plugin
	  */
	uint16_t sendMessage(String message);
	virtual ~TCPComm();
	/**
	  * @brief the instance of the moduleManager class
	  */
	ModuleManager ModuleMgr;

private:
	clientSettings settings;
	JsonParser Parser;

	enum e_connectResult {
		SUCCESS = 1,
		TIMED_OUT = -1,
		INVALID_SERVER = -2,
		TRUNCATED = -3,
		INVALID_RESPONSE = -4
	};
	typedef enum e_tcpState {
		INIT = 0, CONNECTING, CONNECTED, UNKNOWN
	};
	e_tcpState state, oldState;

	Timer checkStateTimer;
};

#endif /* TCPCOMM_H_ */
