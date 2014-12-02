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

#define MSG_SOH	0x01
#define MSG_HEADER_LEN 	7

const char tcpstate[3][11] PROGMEM
		= { "INIT      ", "CONNECTING", "CONNECTED " };

typedef struct{
byte mac[6];		// our mac address
IPAddress ip;		// our IP
IPAddress server; 	// server's IP
IPAddress DNS; 		// DNS server IP
IPAddress gateway; 	// gateway IP
IPAddress subnet; 	// subnet
uint16_t port;		// server's port
} clientSettings;


class TCPComm: public EthernetClient {
public:
	TCPComm();
	void setup(clientSettings cs);
	void loop();
	void checkState();
	int8_t start();
	uint16_t sendMessage(String message);
	virtual ~TCPComm();

	EthernetClient client;

private:
	clientSettings settings;

	enum e_connectResult {
		SUCCESS = 1,
		TIMED_OUT = -1,
		INVALID_SERVER = -2,
		TRUNCATED = -3,
		INVALID_RESPONSE = -4
	};
	typedef enum e_tcpState {
		INIT = 0, CONNECTING, CONNECTED
	};
	e_tcpState state, oldState;

	struct {
		byte soh;
		char msgLength[6];
		char *msg;  // <-DIT IS NIET GOED!!!
	} msg2Send;
};

#endif /* TCPCOMM_H_ */
