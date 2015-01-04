
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


//defineTimerRun(Timer1,100) {
//	if (Serial.available()) {
//		char c = Serial.read();
//		if (c == 'a') {
//	//		flashTask.pause();
//			TCPclient.sendMessage("Pause");
//		}
//		if (c == 'b') {
//	//		flashTask.resume();
//			TCPclient.sendMessage("Resume");
//		}
//		if (c == 'l') {		// Stack left info
//			Serial.print("tcpTask-stackleft: ");
//			Serial.println(tcpTask.stackLeft());
//		}
//		if (c == 't') {
//			TCPclient.sendMessage("\x1     4Test");
//		}
//	}
//}

//The setup function is called once at startup of the sketch
void setup() {
// Add your initialization code here
	// Open serial communications and wait for port to open:
	byte tmp[8];
	Serial.begin(115200);
	Serial.println("[Main thread started]");

	TCPclient.setup("/network/ifaces.jsn");
}

// The loop function is called in an endless loop
void loop() {
//Add your repeated code here
	TCPclient.loop();
}
