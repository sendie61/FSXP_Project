/*
 * TCPComm.cpp
 *
 *  Created on: Nov 15, 2014
 *      Author: F
 */

#include "TCPComm.h"
#include "FSXP_constants.h"

EthernetClient TCPclient;
aJsonStream tcp_stream(&TCPclient);

// some tricks to be able to callback a member function
TCPComm* ptTCPComm;
static void checkState_wrapper() {
	ptTCPComm->checkState();
}
// end of tricks

TCPComm::TCPComm():
	state(UNKNOWN), oldState(UNKNOWN){
	// TODO Auto-generated constructor stub
	ptTCPComm = this;
}

void TCPComm::setup(char * iniFilename) {
	// get init-file from SD card

	aJsonObject* root = NULL;

	const int SS_SD_CARD = 4;

	if (!SD.begin(SS_SD_CARD)) {
		Serial.println(F("SD CARD initialization failed!"));
	} else {
		root = Parser.parseFile(iniFilename);
		if (root != NULL) {
			aJsonObject* settingsObj = aJson.getObjectItem(root, "settings");

			if (settingsObj != NULL) {
				Parser.Json2IP(settings.DNS,
						aJson.getObjectItem(settingsObj, "dns"));
				Parser.Json2IP(settings.gateway,
						aJson.getObjectItem(settingsObj, "gateway"));
				Parser.Json2IP(settings.ip,
						aJson.getObjectItem(settingsObj, "ip"));
				Parser.Json2IP(settings.server,
						aJson.getObjectItem(settingsObj, "server"));
				Parser.Json2IP(settings.subnet,
						aJson.getObjectItem(settingsObj, "subnet"));
				Parser.Json2MAC(settings.mac,
						aJson.getObjectItem(settingsObj, "mac"));
				settings.port =
						aJson.getObjectItem(settingsObj, "port")->valueint;
			}
		}
		state = INIT;
		checkStateTimer.every(1000L, checkState_wrapper);
	}
}

void TCPComm::loop() {
	checkStateTimer.update();
	checkForData();
}

void TCPComm::checkForData() {
	if (state == CONNECTED) {
		if (tcp_stream.available()) {
			aJsonObject *msg = aJson.parse(&tcp_stream);
		    processMessage(msg);
		    aJson.deleteItem(msg);
		}
	}
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
		if (TCPclient.connect(settings.server, settings.port) == SUCCESS) {
			Serial.println("connected");
			TCPclient.println("GET /search?q=arduino HTTP/1.0");
			TCPclient.println();
			state = CONNECTED;
		} else {
			Serial.println("connection failed");
			state = INIT;
		}
		break;

	case CONNECTED:
		if (!TCPclient.connected()) {
			TCPclient.stop();
			state = CONNECTING;
		}
		break;
	case UNKNOWN:
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
	int8_t rv = 0;

	//Ethernet.begin(settings.mac); // get ip from DHCP
	//Ethernet.begin(settings.mac, settings.ip);
	Ethernet.begin(settings.mac, settings.ip, settings.DNS, settings.gateway,
			settings.subnet);

	return rv;
}

uint16_t TCPComm::sendMessage(String message) {
	// TODO auto add HEADER
	msg2Send.soh = MSG_SOH;
	sprintf(msg2Send.msgLength, "%6d", message.length());
	msg2Send.msg = (char*) message.c_str();
	Serial.println(msg2Send.msg);
	Serial.println(static_cast<char*>(static_cast<void*>(&msg2Send)));
	return TCPclient.print((char *) (&msg2Send)) + MSG_HEADER_LEN;
}

bool TCPComm::processMessage(aJsonObject* root) {
	String iHexString;
	bool rv=false;
	if (root != NULL) {
		aJsonObject* i2cObj = aJson.getObjectItem(root, "I2C_IO");
		if (i2cObj != NULL) {
			uint8_t subaddr = aJson.getObjectItem(i2cObj, "-subaddr")->valueint;
			aJsonObject* initObj = aJson.getObjectItem(i2cObj, "INIT");
			if (initObj != NULL) {
				uint16_t arraylen = aJson.getArraySize(initObj);
				for (uint8_t i = 0; i < arraylen; i++)
					iHexString = aJson.getArrayItem(initObj, i)->valuestring;
				rv=true;
			}
		}
	}
	return rv;
}

TCPComm::~TCPComm() {
	// TODO Auto-generated destructor stub
}

