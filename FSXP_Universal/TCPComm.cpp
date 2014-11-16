/*
 * TCPComm.cpp
 *
 *  Created on: Nov 15, 2014
 *      Author: F
 */

#include "TCPComm.h"
#include "FSXP_constants.h"
#include <storage.h>

TCPComm::TCPComm() {
	// TODO Auto-generated constructor stub

}

void TCPComm::setup() {

	// get MAC from EEPROM
	storage MACaddress(MAC_ADDRESS, 6);
	MACaddress.retrieve(mac);

	// get server IP from EEPROM
	storage IPaddress(FSXP_SERVER, 4);
	IPaddress.retrieve(server);

	// get server port from EEPROM
	storage Port(FSXP_PORT);
	Port.retrieve(port);

	Ethernet.begin(mac); // get ip from DHCP
	delay(1000);

	Serial.println("connecting...");

	if (client.connect(server, port) == SUCCESS) {
		Serial.println("connected");
		client.println("GET /search?q=arduino HTTP/1.0");
		client.println();
	} else {
		Serial.println("connection failed");
	}
}

void TCPComm::loop() {

	if (client.available()) {
		char c = client.read();
		Serial.print(c);
	}

	if (!client.connected()) {
//	    Serial.println();
//	    Serial.println("disconnecting.");
		client.stop();

	}
}

TCPComm::~TCPComm() {
	// TODO Auto-generated destructor stub
}

