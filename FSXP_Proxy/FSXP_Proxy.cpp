// Do not remove the include below
#include <SCoop.h>

#include "FSXP_Proxy.h"
#include "TCPComm.h"
#include "FSXP_constants.h"

#define led1 LED_BUILTIN
#define BUFFER_SIZE 200

TCPComm TCPclient;

// Flasing LED task
//defineTask(flashTask)
//
//void flashTask::setup() {
//	trace("flashTask");
//	pinMode(led1, OUTPUT);
//}
//
//void flashTask::loop() {
//	digitalWrite(led1, HIGH);
//	sleepSync(50);
//	digitalWrite(led1, LOW);
//	sleepSync(1000);
//}

defineTask(tcpTask, 2024)


/**
 * Parse the JSON String. Uses aJson library
 *
 * Refer to http://hardwarefun.com/tutorials/parsing-json-in-arduino
 */
bool parseJson(aJsonStream *jsonFile, clientSettings& cs) {
	bool rc = true;

	aJsonObject* root = aJson.parse(jsonFile);

	if (root != NULL) {
		aJsonObject* settings = aJson.getObjectItem(root, "settings");

		if (settings != NULL) {
			Serial.println("Parsed successfully 1 ");
			aJsonObject* dns = aJson.getObjectItem(settings, "dns");

			aJson.print(dns);

			uint8_t dnsBytes[5];
			Serial.print("Array Size DNS: ");
			uint8_t arraySize = aJson.getArraySize(dns);
			Serial.println(arraySize);
			Serial.println("Parsed successfully 2 ");
			for (int c = 0; c < arraySize; c++) {
				dnsBytes[c] = (uint8_t) aJson.getArrayItem(dns, c)->valueint;
			}
			dnsBytes[4] = '\0';
			cs.gateway = (const uint8_t *) dnsBytes;
			Serial.println("Parsed successfully 3 ");
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
	// if the file is available, read&parse it:
	clientSettings cs;
	bool value=  false;
	if (dataFile) {
		value = parseJson( (aJsonStream *) &dataFile, cs);
		dataFile.close();
	}
	// if the file isn't open, pop up an error:
	else {
		Serial.println(F("error opening datalog.txt"));
	}



	if (value) {
		Serial.print(F("Successfully Parsed: "));
		Serial.println(value);
	} else {
		Serial.print(F("There was some problem in parsing the JSON"));
	}
	cs.ip = (const uint8_t *) "1234";

	TCPclient.setup(cs);

	Serial.println(F("SD/Ethernet-HW initialization done."));
	mySCoop.Atomic++;
	TCPclient.setup("/network/ifaces.jsn");
	mySCoop.Atomic++;

}

void tcpTask::loop() {
	mySCoop.Atomic++;
	TCPclient.loop();
	mySCoop.Atomic++;
}

defineTimerRun(Timer1,100) {
	if (Serial.available()) {
		char c = Serial.read();
		if (c == 'a') {
	//		flashTask.pause();
			TCPclient.sendMessage("Pause");
		}
		if (c == 'b') {
	//		flashTask.resume();
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

//defineTimerRun(Timer2,3000) {
//			TCPclient.sendMessage("     4TEsT");
//}

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
