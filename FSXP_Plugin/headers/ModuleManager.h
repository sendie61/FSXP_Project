/*
 * ModuleAcceptor.h
 *
 *  Created on: Mar 1, 2015
 *      Author: F
 */

#ifndef MODULEMANAGER_H_
#define MODULEMANAGER_H_

#include <network.h>
#include "pluginpath.h"
#include <boost/property_tree/xml_parser.hpp>
#include "DUEModule.h"

using namespace std;

class ModuleManager: public Acceptor {
public:
	ModuleManager(boost::shared_ptr<Hive> hive);
	~ModuleManager() {
	}
	;
private:
	/**
	 * @brief some client wants to connect
	 * Check if port is valid
	 * Check if we know this IP
	 * Connect, else Deny
	 */
	bool OnAccept(boost::shared_ptr<Connection> connection,
			const std::string & host, uint16_t port);
	/**
	 * @brief timer overflow
	 */
	void OnTimer(const boost::posix_time::time_duration & delta);
	void OnError(const boost::system::error_code & error);
	bool AcceptConnection(boost::shared_ptr<Connection> connection);

private:

};

#endif /* MODULEMANAGER_H_ */
