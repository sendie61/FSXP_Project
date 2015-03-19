/*
 * ModuleAcceptor.cpp
 *
 *  Created on: Mar 1, 2015
 *      Author: F
 */

#include "ModuleAcceptor.h"
#include "XmlParser.h"

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

ModuleAcceptor::ModuleAcceptor(boost::shared_ptr<Hive> hive) :
		Acceptor(hive) {

// @TODO : read the xml, filter the IP addresses to know which one to accept.
	ParseXml("../FSXPmodules.xml");
}

void ModuleAcceptor::ParseXml(string filename) {
	using boost::property_tree::ptree;
	ptree pt;

/*
	boost::property_tree::xml_parser::read_xml(filename, pt);

	BOOST_FOREACH (ptree::value_type const& vContainer, pt.get_child ("root")) {

		BOOST_FOREACH (ptree::value_type const& vItem, pt.get_child ("root.container")) {
			std::cout << "\t1---------------------\n";
		}
		std::cout << "\t2---------------------\n";
*/
}
