// Do not remove the include below
#include "FSXP_Universal.h"
#include <SCoop.h>
#include <storage.h>
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


defineTask(tcpTask,300)

void tcpTask::setup() {
//	trace("tcpTask");
	TCPclient.setup(mySCoop);
}

void tcpTask::loop() {
	TCPclient.loop();
	mySCoop.yield();
}


defineTimerRun(Timer1,100) {
	if (Serial.available()) {
		char c = Serial.read();
		if (c == 'a')
			flashTask.pause();
		if (c == 'b')
			flashTask.resume();
		if (c == 'l'){		// Stack left info
			Serial.print("tcpTask-stackleft: ");
			Serial.println(tcpTask.stackLeft());
		}
	}
}


//The setup function is called once at startup of the sketch
void setup() {
// Add your initialization code here
	// Open serial communications and wait for port to open:
	byte tmp[8];
	Serial.begin(115200);
	Serial.println("[Main thread started]");

/*
	storage mac(MAC_ADDRESS, 6);
	tmp[0] = 0xde;
	tmp[1] = 0xad;
	tmp[2] = 0xbe;
	tmp[3] = 0xef;
	tmp[4] = 0xfe;
	tmp[5] = 0xed;
	mac.store(tmp, 6);

	storage ip(FSXP_SERVER, 4);
	tmp[0] = 192;
	tmp[1] = 168;
	tmp[2] = 2;
	tmp[3] = 21;
//	tmp[3] = 5;
	ip.store(tmp, 4);

	storage ourip(OUR_DEFAULT_IP, 4);
	tmp[0] = 192;
	tmp[1] = 168;
	tmp[2] = 2;
	tmp[3] = 200;
	ourip.store(tmp, 4);

	storage port(FSXP_PORT);
	port.store(1201);
*/

	mySCoop.start();
}

// The loop function is called in an endless loop
void loop() {
//Add your repeated code here
	mySCoop.sleep(500);

}
