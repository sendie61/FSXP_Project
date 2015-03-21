# FSXP_Project
X-Plane plugin and Arduino DUE firmware. Make Hardware modules that communicate with x-plane datarefs and commands. Windows 64 bit only.

This project was started for my B737NG cockpit (http://B737NG.flightsimulators.eu)
I am interfacing all the hardware to Arduino DUE and some SPI and I2C chips. 
These communicate via TCP/IP through an X-Plane plugin with x-plane.
The Arduino firmware is captured in the project FSXP-Proxy, and the plugin is FSXP-plugin
These are all Eclipse projects.
The idea is to have all the configuration written in a (aircraft dependant) xml file that resides on the (x-plane) PC 
and is read at loading an airplane in x-plane by the FSXP-plugin.
It initializes the plugin and the arduino's...
