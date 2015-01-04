/*
 * TCPComm.cpp
 *
 *  Created on: Nov 15, 2014
 *      Author: F
 */

#include "TCPComm.h"
#include "FSXP_constants.h"

TCPComm::TCPComm() {
	// TODO Auto-generated constructor stub
}

void TCPComm::setup(char * iniFilename) {
	// get info from SD card

	String settingString;
	Parser.readFile2String(settingString, iniFilename);
	aJsonObject* root = aJson.parse((char *) settingString.c_str());
	if (root != NULL) {
		aJsonObject* settingsObj = aJson.getObjectItem(root, "settings");

		if (settingsObj != NULL) {
			Parser.Json2IP(settings.DNS, aJson.getObjectItem(settingsObj, "dns"));
			Parser.Json2IP(settings.gateway, aJson.getObjectItem(settingsObj, "gateway"));
			Parser.Json2IP(settings.ip, aJson.getObjectItem(settingsObj, "ip"));
			Parser.Json2IP(settings.server, aJson.getObjectItem(settingsObj, "server"));
			Parser.Json2IP(settings.subnet, aJson.getObjectItem(settingsObj, "subnet"));
			Parser.Json2MAC(settings.mac, aJson.getObjectItem(settingsObj, "mac"));
			settings.port= aJson.getObjectItem(settingsObj, "port")->valueint;
		}
	}
	state = INIT;
	oldState = CONNECTED;
}

void TCPComm::loop() {
	checkState();
}

void TCPComm::checkState() {
	 switch (state) {

	case INIT:
		if (start() == SUCCESS) {
			state = CONNECTING;
		}
		state = CONNECTING;
		break;

	case CONNECTING:
		if (client.connect("192.168.2.5", 80) == SUCCESS) {
		//if (client.connect(settings.server, settings.port) == SUCCESS) {
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
	if (state != oldState) {
		Serial.print("TCP_State changed to ");
		Serial.println(tcpstate[state]);
		oldState = state;
	}
}

int8_t TCPComm::start() {
	Serial.print("My MAC = ");
	for (int i = 0; i < 6; i++) {
		Serial.print(settings.mac[i], HEX);
		Serial.print('.');
	}
	Serial.println();
	Serial.println("DHCP request...");
	int8_t rv = 0;
	//Ethernet.begin(settings.mac); // get ip from DHCP
	//Ethernet.begin(settings.mac, settings.ip);
	Ethernet.begin(settings.mac, settings.ip, settings.DNS, settings.gateway, settings.subnet);
	Serial.print("My IP = ");
	Serial.println(Ethernet.localIP());
	//Serial.println(settings.ip);
	Serial.print("gateway = ");
	Serial.println(Ethernet.gatewayIP());
	//Serial.println(settings.gateway);
	Serial.print("connecting to ");
	Serial.print(settings.server);
	Serial.print(":");
	Serial.print(settings.port);
	Serial.println("...");
	return rv;
}

uint16_t TCPComm::sendMessage(String message) {
	// TODO auto add HEADER
	msg2Send.soh = MSG_SOH;
	sprintf(msg2Send.msgLength, "%6d", message.length());
	msg2Send.msg = (char*) message.c_str();
	Serial.println(msg2Send.msg);
	Serial.println(static_cast<char*>(static_cast<void*>(&msg2Send)));
	return client.print((char *) (&msg2Send)) + MSG_HEADER_LEN;
}

TCPComm::~TCPComm() {
	// TODO Auto-generated destructor stub
}

