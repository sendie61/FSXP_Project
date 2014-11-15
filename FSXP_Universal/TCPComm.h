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

	byte mac[6];
	byte ip[4];
	byte server[4]; // Google
};

#endif /* TCPCOMM_H_ */
