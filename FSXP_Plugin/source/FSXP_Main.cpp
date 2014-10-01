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

 #define XPLM200 = 1;  // This example requires SDK2.0


 #include "XPLMPlugin.h"
 #include "XPLMDisplay.h"
 #include "XPLMGraphics.h"
 #include "XPLMProcessing.h"
 #include "XPLMDataAccess.h"
 #include "XPLMMenus.h"
 #include "XPLMUtilities.h"
 #include "XPWidgets.h"
 #include "XPStandardWidgets.h"
 #include "XPLMScenery.h"
 #include <string.h>
 #include <stdio.h>
 #include <stdlib.h>

//#include "dataref.h"
#include "owneddata.h"

using namespace PPL;

 XPLMDataRef gCounterDataRef = NULL;          //  Our custom dataref

 int     gCounterValue;                       //  Our custom dataref's value
 int     GetCounterDataRefCB(void* inRefcon);
 void    SetCounterDataRefCB(void* inRefcon, int outValue);

 XPLMCommandRef CounterUpCommand = NULL;	//  Our two custom commands
 XPLMCommandRef CounterDownCommand = NULL;

 int    CounterUpCommandHandler(XPLMCommandRef       inCommand,          //  Our two custom command handlers
                                XPLMCommandPhase     inPhase,
                                void *               inRefcon);

 int    CounterDownCommandHandler(XPLMCommandRef     inCommand,
                                 XPLMCommandPhase    inPhase,
                                 void *              inRefcon);

 //input data
 DataRef<int> inHasDME("sim/cockpit2/radios/indicators/nav1_has_dme");
 DataRef<float> inDMEDist("sim/cockpit2/radios/indicators/nav1_dme_distance_nm");

 //output data
 /////////////////////////////////////////////////////////////////////////////////
 OwnedData<float> DMENeedle("Dozer/AWA-VAN3-DME/needle");
 //float DMENeedle = 0;
 /////////////////////////////////////////////////////////////////////////////////
 //OwnedData compiles with G++ but not MSVC. Replacing OwnedData with Float
 //and leaving the PPL::DataRefs as DataRefs does compile with MSVC.


 PLUGIN_API int XPluginStart(
         char *        outName,
         char *        outSig,
         char *        outDesc)
 {

 // Plugin Info
     strcpy(outName, "FSXP_Plugin");
     strcpy(outSig, "BlueSideUpBob.Example.CustomCommandsAndDataRef");
     strcpy(outDesc, "This is the first try.");

 //  Create our custom integer dataref
 gCounterDataRef = XPLMRegisterDataAccessor("BSUB/CounterDataRef",
                                             xplmType_Int,                                  // The types we support
                                             1,                                             // Writable
                                             GetCounterDataRefCB, SetCounterDataRefCB,      // Integer accessors
                                             NULL, NULL,                                    // Float accessors
                                             NULL, NULL,                                    // Doubles accessors
                                             NULL, NULL,                                    // Int array accessors
                                             NULL, NULL,                                    // Float array accessors
                                             NULL, NULL,                                    // Raw data accessors
                                             NULL, NULL);                                   // Refcons not used

 DataRef<float> ap_alt("sim/cockpit/autopilot/altitude", ReadWrite);
 // float ap_alt_meters = ap_alt * 12; // note that DataRef ap_alt is treated as a float !
 ap_alt = 5007*2.5 ; // note that you can write to ap_alt like you can write to float !


 // Find and intialize our Counter dataref
 gCounterDataRef = XPLMFindDataRef ("BSUB/CounterDataRef");
 XPLMSetDatai(gCounterDataRef, 0);


 // Create our commands; these will increment and decrement our custom dataref.
 CounterUpCommand = XPLMCreateCommand("BSUB/CounterUpCommand", "Counter Up");
 CounterDownCommand = XPLMCreateCommand("BSUB/CounterDownCommand", "Counter Down");

 // Register our custom commands
 XPLMRegisterCommandHandler(CounterUpCommand,           // in Command name
                            CounterUpCommandHandler,    // in Handler
                            1,                          // Receive input before plugin windows.
                            (void *) 0);                // inRefcon.

 XPLMRegisterCommandHandler(CounterDownCommand,
                            CounterDownCommandHandler,
                            1,
                            (void *) 0);

 return 1;
 }


 PLUGIN_API void     XPluginStop(void)
 {
 XPLMUnregisterDataAccessor(gCounterDataRef);
 XPLMUnregisterCommandHandler(CounterUpCommand, CounterUpCommandHandler, 0, 0);
 XPLMUnregisterCommandHandler(CounterDownCommand, CounterDownCommandHandler, 0, 0);
 }

 PLUGIN_API void XPluginDisable(void)
 {
 }

 PLUGIN_API int XPluginEnable(void)
 {
     return 1;
 }

 PLUGIN_API void XPluginReceiveMessage(XPLMPluginID    inFromWho,
                                      long             inMessage,
                                      void *           inParam)
 {
 }

 int     GetCounterDataRefCB(void* inRefcon)
 {
     return gCounterValue;
 }

 void	SetCounterDataRefCB(void* inRefcon, int inValue)
 {
      gCounterValue = inValue;
 }

 int    CounterUpCommandHandler(XPLMCommandRef       inCommand,
                                XPLMCommandPhase     inPhase,
                                void *               inRefcon)
 {
 //  If inPhase == 0 the command is executed once on button down.
 if (inPhase == 0)
     {
      gCounterValue++;
      if(gCounterValue > 10) {gCounterValue = 10;}
     }
 // Return 1 to pass the command to plugin windows and X-Plane.
 // Returning 0 disables further processing by X-Plane.

 return 0;
 }

 int    CounterDownCommandHandler(XPLMCommandRef       inCommand,
                         XPLMCommandPhase     inPhase,
                         void *               inRefcon)
 {
 //  If inPhase == 1 the command is executed continuously.
      if (inPhase == 1)
    {
           gCounterValue--;
           if(gCounterValue < -10) {gCounterValue = -10;}
     }

 return 0;
 }
