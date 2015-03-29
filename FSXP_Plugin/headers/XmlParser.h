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

#define ATTR_SET "<xmlattr>"
#define XMLFILENAME	"FSXPmodule.xml"

using namespace boost;
using namespace boost::property_tree;

/**
 * @brief Helper class
 * parse the XML file
 */
class XmlParser {
public:
	/**
	 * @brief Search fot the XML file
	 * does own search for xml file if necessary
	 */
	const char* findXmlFile();

	/**
	 * @brief find all DUEPROXY ip addresses
	 * does own search for xml file if necessary
	 */
	std::vector<std::string> getIpAddresses(std::string XMLFilename= "");

	/**
	 * @brief find the DUEPROXY with specific ip addresses
	 * Necessary when this particular one connects
	 */
	boost::property_tree::ptree & getDueProxyByAddress( std::string ip);
private:
	PPL::PluginPath PluginPath;
};

#endif /* XMLPARSER_H_ */
