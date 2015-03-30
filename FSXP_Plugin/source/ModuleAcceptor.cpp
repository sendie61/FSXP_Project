/*
 * ModuleAcceptor.cpp
 *
 *  Created on: Mar 1, 2015
 *      Author: F
 */

#include "ModuleAcceptor.h"
#include "XmlParser.h"

ModuleAcceptor::ModuleAcceptor(boost::shared_ptr<Hive> hive) :
		Acceptor(hive) {

// @TODO : read the xml, filter the IP addresses to know which one to accept.
	ParseXml("../FSXPmodules.xml");
}

bool ModuleAcceptor::OnAccept(boost::shared_ptr<Connection> connection,
		const std::string & host, uint16_t port) {
	XmlParser XmlParser;
	XmlParser.findXmlFile();
	return true;
}

void ModuleAcceptor::OnTimer(const boost::posix_time::time_duration & delta) {
}

void ModuleAcceptor::OnError(const boost::system::error_code & error) {
}

void ModuleAcceptor::ParseXml(string filename) {
	using boost::property_tree::ptree;
	ptree pt;
}
