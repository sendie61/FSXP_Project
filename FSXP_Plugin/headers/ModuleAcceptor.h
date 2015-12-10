/*
 * ModuleAcceptor.h
 *
 *  Created on: Mar 1, 2015
 *      Author: F
 */

#ifndef MODULEACCEPTOR_H_
#define MODULEACCEPTOR_H_

#include <vector>
#include <network.h>
#include "pluginpath.h"
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include "DUEModule.h"

using namespace std;

class ModuleAcceptor: public Acceptor {
public:
	ModuleAcceptor(boost::shared_ptr<Hive> hive);
	~ModuleAcceptor() {
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

#endif /* MODULEACCEPTOR_H_ */
