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
#include <SCoop.h>

const char tcpstate[3][11]={"INIT      ","CONNECTING","CONNECTED "};

class TCPComm: public EthernetClient {
public:
	TCPComm();
	void setup(SCoop sced);
	void loop();
	void checkState();
	int8_t GetIP();
	virtual ~TCPComm();

	EthernetClient client;

	byte mac[6];	// our mac address
	byte ip[4];		// our IP
	byte server[4]; // server's
	uint16_t port;	// port

	enum e_connectResult {SUCCESS=1, TIMED_OUT=-1, INVALID_SERVER=-2, TRUNCATED=-3, INVALID_RESPONSE=-4};
	enum e_tcpState {INIT=0, CONNECTING, CONNECTED} state;
	SCoop sceduler;
};

#endif /* TCPCOMM_H_ */
