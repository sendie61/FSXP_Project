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

void TCPComm::setup(SCoop sced) {
	sceduler = sced;
	// get MAC from EEPROM
	storage MACaddress(MAC_ADDRESS, 6);
	MACaddress.retrieve(mac);

	// get server IP from EEPROM
	storage IPaddress(FSXP_SERVER, 4);
	IPaddress.retrieve(server);

	// get server port from EEPROM
	storage Port(FSXP_PORT);
	Port.retrieve(port);
	state = INIT;
//	Ethernet.begin(mac); // get ip from DHCP

}

void TCPComm::loop() {
	checkState();
}

void TCPComm::checkState() {
	Serial.print("TCP_State changed to ");
	Serial.println(tcpstate[state]);
	switch (state) {

	case INIT:
		if (GetIP() == SUCCESS) {
			state = CONNECTING;
		}
		state = CONNECTING;
		break;

	case CONNECTING:
		if (client.connect(server, port) == SUCCESS) {
			Serial.println("connected");
			client.println("GET /search?q=arduino HTTP/1.0");
			client.println();
			state = CONNECTED;
		} else {
			Serial.println("connection failed");
			state = INIT;
		}
		break;

	case CONNECTED:
		if (client.available()) {
			char c = client.read();
			Serial.print(c);
		}

		if (!client.connected()) {
			//	    Serial.println();
			//	    Serial.println("disconnecting.");
			client.stop();
			state = CONNECTING;
		}
		break;
	default:
		;
	};
}

int8_t TCPComm::GetIP() {
	Serial.print("My MAC = ");
	for (int i = 0; i < 6; i++) {
		Serial.print(mac[i], HEX);
		Serial.print('.');
	}
	Serial.println();
	Serial.println("DHCP request...");
	int8_t rv = Ethernet.begin(mac); // get ip from DHCP
//	sceduler.delay(1000);
	Serial.print("My IP = ");
	Serial.println(Ethernet.localIP());
	Serial.print("gateway = ");
	Serial.println(Ethernet.gatewayIP());
	Serial.print("connecting to ");
	Serial.print(IPAddress(server));
	Serial.print(":");
	Serial.print(port);
	Serial.println("...");
	return rv;
}

TCPComm::~TCPComm() {
	// TODO Auto-generated destructor stub
}

