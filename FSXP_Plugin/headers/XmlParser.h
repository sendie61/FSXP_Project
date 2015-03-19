/*
 * XmlParser.h
 *
 *  Created on: Mar 8, 2015
 *      Author: F
 */

#ifndef XMLPARSER_H_
#define XMLPARSER_H_

#include <iostream>
#include <vector>
#include <string>
#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <pluginpath.h>

#define ATTR_SET ".<xmlattr>"
#define XMLFILENAME	"FSXPmodule.xml"

class XmlParser {
public:
	const char* findXmlFile();
	std::vector<std::string> getIpAddresses();
	boost::property_tree::ptree & getDueProxyByAddress( std::string ip);
private:
	PPL::PluginPath PluginPath;
};

#endif /* XMLPARSER_H_ */
