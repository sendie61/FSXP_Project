// Custom Commands
//
// Custom Commands Control Custom DataRef
//
// This example program creates a custom integer dataref, BSUB/CounterDataRef, and two custom
// commands, BSUB/CounterUpCommand and BSUB/CounterDownCommand.  The custom commands
// are used to increment and decriment the custom dataref.  The custom dataref can be used to drive an
// generic instrument display, animation, etc.
//
// After successfully creating your plugin you will need to use PlaneMaker to create two generic
// triggers, keyed to your custom commands on your aircraft panel.  You will also need to place a generic
// counter such as an LED display on your aircraft panel.
//
// Content added by BlueSideUpBob.
#include "asio.h"

using namespace PPL;

boost::shared_ptr<Asio> AsioSystem;

XPLMDataRef gCounterDataRef = NULL;          //  Our custom dataref

int gCounterValue;                       //  Our custom dataref's value
int GetCounterDataRefCB(void* inRefcon);
void SetCounterDataRefCB(void* inRefcon, int outValue);
float ConnectionLoopCallback(float inElapsedSinceLastCall,
		float inElapsedTimeSinceLastFlightLoop, int inCounter, void * inRefcon);

XPLMCommandRef CounterUpCommand = NULL;	//  Our two custom commands
XPLMCommandRef CounterDownCommand = NULL;

int CounterUpCommandHandler(XPLMCommandRef inCommand, //  Our two custom command handlers
		XPLMCommandPhase inPhase, void * inRefcon);

int CounterDownCommandHandler(XPLMCommandRef inCommand,
		XPLMCommandPhase inPhase, void * inRefcon);

template <typename SimType>
class FSXPDataRef : public DataRef<SimType>
{
	public:
	FSXPDataRef<SimType>(const std::string& identifier, RWType writeability = ReadOnly, bool share = false, bool publish_in_dre = false)
	: DataRef<SimType>(identifier, writeability, share, publish_in_dre){};
	private:
	void doNotify();
};



template<typename SimType>
void FSXPDataRef<SimType>::doNotify() {
	 XPLMDebugString("FSXP_Plugin: doNotify\n");
}


//input  data
FSXPDataRef<int> audio_selection_com1("sim/cockpit2/radios/actuators/audio_selection_com1", ReadOnly, true);

//output data
/////////////////////////////////////////////////////////////////////////////////
OwnedData<float> DMENeedle("Dozer/AWA-VAN3-DME/needle");
//float DMENeedle = 0;
/////////////////////////////////////////////////////////////////////////////////
//OwnedData compiles with G++ but not MSVC. Replacing OwnedData with Float
//and leaving the PPL::DataRefs as DataRefs does compile with MSVC.

PLUGIN_API int XPluginStart(char* outName, char * outSig, char * outDesc) {

	AsioSystem =boost::shared_ptr<Asio>(new Asio);
	XPLMDebugString("FSXP_Plugin: Started\n");

	// Plugin Info
	strcpy(outName, "FSXP_Plugin");
	strcpy(outSig, "FSXP.Plugin.Modules_communication");
	strcpy(outDesc, "Arduino DUE-PROY Communication plugin.");

	//  Create our custom integer dataref
	gCounterDataRef = XPLMRegisterDataAccessor("BSUB/CounterDataRef",
			xplmType_Int,                                // The types we support
			1,                                             // Writable
			GetCounterDataRefCB, SetCounterDataRefCB,      // Integer accessors
			NULL, NULL,                                    // Float accessors
			NULL, NULL,                                    // Doubles accessors
			NULL, NULL,                                   // Int array accessors
			NULL, NULL,                                 // Float array accessors
			NULL, NULL,                                    // Raw data accessors
			NULL, NULL);                                   // Refcons not used

	DataRef<float> ap_alt("sim/cockpit/autopilot/altitude", ReadWrite);
	// float ap_alt_meters = ap_alt * 12; // note that DataRef ap_alt is treated as a float !
	ap_alt = 5007 * 2.5; // note that you can write to ap_alt like you can write to float !

	// Find and intialize our Counter dataref
	gCounterDataRef = XPLMFindDataRef("BSUB/CounterDataRef");
	XPLMSetDatai(gCounterDataRef, 0);

	// Create our commands; these will increment and decrement our custom dataref.
	CounterUpCommand = XPLMCreateCommand("BSUB/CounterUpCommand", "Counter Up");
	CounterDownCommand = XPLMCreateCommand("BSUB/CounterDownCommand",
			"Counter Down");

	// Register our custom commands
	XPLMRegisterCommandHandler(CounterUpCommand,           // in Command name
			CounterUpCommandHandler,    // in Handler
			1,                          // Receive input before plugin windows.
			(void *) 0);                // inRefcon.

	XPLMRegisterCommandHandler(CounterDownCommand, CounterDownCommandHandler, 1,
			(void *) 0);

	XPLMRegisterFlightLoopCallback(ConnectionLoopCallback, /* Callback */
	1.0, /* Interval */
	NULL); /* refcon not used. */
	return 1;
}

PLUGIN_API void XPluginStop(void) {
	XPLMDebugString("FSXP_Plugin: Stopped\n");
	AsioSystem.reset();
	XPLMUnregisterDataAccessor(gCounterDataRef);
	XPLMUnregisterCommandHandler(CounterUpCommand, CounterUpCommandHandler, 0,
			0);
	XPLMUnregisterCommandHandler(CounterDownCommand, CounterDownCommandHandler,
			0, 0);
}

PLUGIN_API int XPluginEnable(void) {
	XPLMDebugString("FSXP_Plugin: Enabled\n");
	AsioSystem->start();
	return 1;
}

PLUGIN_API void XPluginDisable(void) {
	XPLMDebugString("FSXP_Plugin: Disabled\n");
	AsioSystem->stop();
}

PLUGIN_API void XPluginReceiveMessage(XPLMPluginID inFromWho, long inMessage,
		void * inParam) {
}

float ConnectionLoopCallback(float inElapsedSinceLastCall,
		float inElapsedTimeSinceLastFlightLoop, int inCounter,
		void * inRefcon) {
    if (audio_selection_com1.hasChanged()){
    	audio_selection_com1.save();
    	AsioSystem->dataRefChanged(audio_selection_com1);
    }
	return 1.0;
}

int GetCounterDataRefCB(void* inRefcon) {
	return gCounterValue;
}

void SetCounterDataRefCB(void* inRefcon, int inValue) {
	gCounterValue = inValue;
}

int CounterUpCommandHandler(XPLMCommandRef inCommand, XPLMCommandPhase inPhase,
		void * inRefcon) {
	//  If inPhase == 0 the command is executed once on button down.
	if (inPhase == 0) {
		gCounterValue++;
		if (gCounterValue > 10) {
			gCounterValue = 10;
		}
	}
	// Return 1 to pass the command to plugin windows and X-Plane.
	// Returning 0 disables further processing by X-Plane.

	return 0;
}

int CounterDownCommandHandler(XPLMCommandRef inCommand,
		XPLMCommandPhase inPhase, void * inRefcon) {
	//  If inPhase == 1 the command is executed continuously.
	if (inPhase == 1) {
		gCounterValue--;
		if (gCounterValue < -10) {
			gCounterValue = -10;
		}
	}

	return 0;
}
