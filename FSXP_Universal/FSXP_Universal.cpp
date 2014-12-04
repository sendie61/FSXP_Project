// Do not remove the include below
#include "FSXP_Universal.h"
#include <SCoop.h>
#include <SD.h>
#include <aJSON.h>
#include "TCPComm.h"
#include "FSXP_constants.h"

#define led1 LED_BUILTIN

TCPComm TCPclient;

// Flasing LED task
defineTask(flashTask)
void flashTask::setup() {
//	trace("flashTask");
	pinMode(led1, OUTPUT);
}

void flashTask::loop() {
	digitalWrite(led1, HIGH);
	sleepSync(50);
	digitalWrite(led1, LOW);
	sleepSync(1000);
}

defineTask(tcpTask, 1024)

/**
 * Parse the JSON String. Uses aJson library
 *
 * Refer to http://hardwarefun.com/tutorials/parsing-json-in-arduino
 */
bool parseJson(char *jsonString, clientSettings& cs) {
	bool rc = true;

	aJsonObject* root = aJson.parse(jsonString);

	if (root != NULL) {
		aJsonObject* settings = aJson.getObjectItem(root, "settings");

		if (settings != NULL) {
			Serial.println("Parsed successfully 1 ");
			aJsonObject* dns = aJson.getObjectItem(settings, "gateway");
			uint8_t dnsBytes[5];
			Serial.print("Array Size DNS: ");
			Serial.println(aJson.getArraySize(dns));
			for (int c = 0; c < aJson.getArraySize(dns); c++) {
				dnsBytes[c] = (uint8_t) aJson.getArrayItem(dns, c)->valueint;
			}
			dnsBytes[4] = '\0';
			cs.gateway = (const uint8_t *) dnsBytes;
			Serial.println("Parsed successfully 2 ");
		}
	}
	cs.server = (const uint8_t *) "ABCD";
	return rc;
}

void tcpTask::setup() {
//	trace("tcpTask");
	const int CS = 4;
	const int SS = 10;

	pinMode(SS, OUTPUT);
	if (!SD.begin(CS)) {
		Serial.println(F("initialization failed!"));
		return;
	}
	Serial.println(F("initialization done."));

	File dataFile = SD.open("/network/ifaces.jsn");
	String jsonString = "";

	// if the file is available, read it:
	if (dataFile) {
		while (dataFile.available()) {
			jsonString += (char) dataFile.read();
		}
		dataFile.close();
	}
	// if the file isn't open, pop up an error:
	else {
		Serial.println(F("error opening datalog.txt"));
	}
	Serial.println(jsonString); //test it

	clientSettings cs;

	bool value = parseJson((char *) jsonString.c_str(), cs);

	if (value) {
		Serial.print(F("Successfully Parsed: "));
		Serial.println(value);
	} else {
		Serial.print(F("There was some problem in parsing the JSON"));
	}
	cs.ip = (const uint8_t *) "1234";

	TCPclient.setup(cs);
}

void tcpTask::loop() {
	TCPclient.loop();
	mySCoop.yield();
}

defineTimerRun(Timer1,100) {
	if (Serial.available()) {
		char c = Serial.read();
		if (c == 'a') {
			flashTask.pause();
			TCPclient.sendMessage("Pause");
		}
		if (c == 'b') {
			flashTask.resume();
			TCPclient.sendMessage("Resume");
		}
		if (c == 'l') {		// Stack left info
			Serial.print("tcpTask-stackleft: ");
			Serial.println(tcpTask.stackLeft());
		}
		if (c == 't') {
			TCPclient.sendMessage("\x1     4Test");
		}
	}
}

defineTimerRun(Timer2,3000) {
//			TCPclient.sendMessage("     4TEsT");
}

//The setup function is called once at startup of the sketch
void setup() {
// Add your initialization code here
	// Open serial communications and wait for port to open:
	byte tmp[8];
	Serial.begin(115200);
	Serial.println("[Main thread started]");

	mySCoop.start();
}

// The loop function is called in an endless loop
void loop() {
//Add your repeated code here
	mySCoop.sleep(500);

}
