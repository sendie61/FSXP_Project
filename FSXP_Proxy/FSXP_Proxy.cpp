
#include "FSXP_Proxy.h"
#include "TCPComm.h"
#include "FSXP_constants.h"
#include "Timer.h"
#include "IntelHex.h"
#define led1 LED_BUILTIN
#define BUFFER_SIZE 200

TCPComm TCPclient;
Timer tim100ms;

//The setup function is called once at startup of the sketch
void setup() {
// Add your initialization code here
	// Open serial communications and wait for port to open:
	byte tmp[8];
	Serial.begin(115200);
	Serial.println("[Main thread started]");

	TCPclient.setup("/network/ifaces.jsn");
	pinMode(LED_BUILTIN, OUTPUT);
	tim100ms.oscillate(LED_BUILTIN, 500L, HIGH);
}

// The loop function is called in an endless loop
void loop() {
//Add your repeated code here
	TCPclient.loop();
	tim100ms.update();

}
