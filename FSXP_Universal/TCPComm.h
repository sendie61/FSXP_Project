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


class TCPComm: public EthernetClient {
public:
	TCPComm();
	void setup();
	void loop();
	virtual ~TCPComm();

	EthernetClient client;

	byte mac[6];	// our mac address
	byte ip[4];		// our IP
	byte server[4]; // server's
	uint16_t port;	// port
};

#endif /* TCPCOMM_H_ */
