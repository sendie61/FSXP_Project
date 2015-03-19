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

using namespace std;

class ModuleAcceptor: public Acceptor {
private:
	bool OnAccept(boost::shared_ptr<Connection> connection,
			const std::string & host, uint16_t port);
	void OnTimer(const boost::posix_time::time_duration & delta);
	void OnError(const boost::system::error_code & error);

	void ParseXml(string filename);
	PPL::PluginPath pluginPath;
	vector<string> ModuleIPs;	// list of IP's of Modules from XMLfile
public:
	ModuleAcceptor(boost::shared_ptr<Hive> hive);
	~ModuleAcceptor() {
	}
	;
};

#endif /* MODULEACCEPTOR_H_ */
