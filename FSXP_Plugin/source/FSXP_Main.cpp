// FSXP Plugin
//

#include "asio.h"
#include <logwriter.h>
#include <log.h>
#include <pluginpath.h>
#include "XmlParser.h"

using namespace PPL;

boost::shared_ptr<Asio> AsioSystem;

float ConnectionLoopCallback(float inElapsedSinceLastCall,
		float inElapsedTimeSinceLastFlightLoop, int inCounter, void * inRefcon);


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

/////////////////////////////////////////////////////////////////////////////////
//OwnedData compiles with G++ but not MSVC. Replacing OwnedData with Float
//and leaving the PPL::DataRefs as DataRefs does compile with MSVC.

PLUGIN_API int XPluginStart(char* outName, char * outSig, char * outDesc) {
	string LogFile;
	PluginPath LogFilePath;
	LogFilePath.prependXPlanePath(LogFile);
	LogFile += "FSXPLog.txt";
	LogWriter::getLogger().setLogFile(LogFile);

	AsioSystem =boost::shared_ptr<Asio>(new Asio);
	XPLMDebugString("FSXP_Plugin: Started\n");
	Log() << Log::Info << "FSXP_Plugin: Started " << Log::endl;

	// Plugin  Info
	strcpy(outName, "FSXP_Plugin");
	strcpy(outSig, "FSXP.Plugin.Modules_communication");
	strcpy(outDesc, "Arduino DUE-PROXY Communication plugin.");


	XPLMRegisterFlightLoopCallback(ConnectionLoopCallback, /* Callback */
	1.0, /* Interval */
	NULL); /* refcon not used. */


	return 1;
}

PLUGIN_API void XPluginStop(void) {
	XPLMDebugString("FSXP_Plugin: Stopped\n");
	Log() << Log::Info << "FSXP_Plugin: Stopped" << Log::endl;
	AsioSystem.reset();
}

PLUGIN_API int XPluginEnable(void) {
	XPLMDebugString("FSXP_Plugin: Enabled\n");
	Log() << Log::Info << "FSXP_Plugin: Enabled" << Log::endl;

	AsioSystem->start();
	return 1;
}

PLUGIN_API void XPluginDisable(void) {
	XPLMDebugString("FSXP_Plugin: Disabled\n");
	Log() << Log::Info << "FSXP_Plugin: Disabled" << Log::endl;

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

