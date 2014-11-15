// Do not remove the include below
#include "FSXP_Universal.h"
#include "storage.h"

//The setup function is called once at startup of the sketch
void setup() {
// Add your initialization code here
	// Open serial communications and wait for port to open:
	char tmp[8];
	Serial.begin(115200);
	Serial.println("Starting...");
	storage mac(0x0ff0, 6);
	mac.retrieve(tmp);
	for (int i = 0; i < 6; i++) {
		Serial.print((char)tmp[i], HEX);
		Serial.print(' ');
	}
	Serial.println();
	tmp[0]= 0x12; tmp[1]=0x34; tmp[2]=0x56; tmp[3]=0x78; tmp[4]=0x9a; tmp[5]=0xbc;
	mac.store(tmp,6);
	mac.retrieve(tmp);
	for (int i = 0; i < 6; i++) {
		Serial.print((char)tmp[i], HEX);
		Serial.print(' ');
	}
}

// The loop function is called in an endless loop
void loop() {
//Add your repeated code here
}
