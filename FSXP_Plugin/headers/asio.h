/*
 * asio.h
 *
 *  Created on: Feb 26, 2015
 *      Author: F
 */

#ifndef ASIO_H_
#define ASIO_H_

#include "network.h"
#include <conio.h>
#include <boost/thread/mutex.hpp>
#include <boost/thread.hpp>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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

#include "dataref.h"
#include "owneddata.h"

class ModuleConnection: public Connection {
private:
	void OnAccept(const std::string & host, uint16_t port);
	void OnConnect(const std::string & host, uint16_t port);
	void OnSend(const std::vector<uint8_t> & buffer);
	void OnRecv(std::vector<uint8_t> & buffer);
	void OnTimer(const boost::posix_time::time_duration & delta);
	void OnError(const boost::system::error_code & error);
public:
	ModuleConnection(boost::shared_ptr<Hive> hive);
	~ModuleConnection() {};
};

class ModuleAcceptor: public Acceptor {
private:
	bool OnAccept(boost::shared_ptr<Connection> connection,
			const std::string & host, uint16_t port);
	void OnTimer(const boost::posix_time::time_duration & delta);
	void OnError(const boost::system::error_code & error);
public:
	ModuleAcceptor(boost::shared_ptr<Hive> hive);
	~ModuleAcceptor() {
	}
	;
};

class Asio{
private:
	boost::shared_ptr<Hive> hive;
	boost::shared_ptr<ModuleAcceptor> acceptor;
	boost::shared_ptr<ModuleConnection> connection;
	boost::thread_group worker_thread;

public:
	Asio();
	~Asio();
	void init();
	void start();
	void stop();
	void dataRefChanged(int val);
};

#endif /* ASIO_H_ */
