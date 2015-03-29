/*
 * XmlParser.cpp
 *
 *  Created on: Mar 8, 2015
 *      Author: F
 */

#include <boost/filesystem.hpp>
#include "XmlParser.h"
#include "logwriter.h"
#include "log.h"

using namespace PPL;


const ptree& empty_ptree(){
    static ptree t;
    return t;
}

const char* XmlParser::findXmlFile() {
	std::string path;
	Log() << Log::Info << "Looking for " << XMLFILENAME << "..." << Log::endl;

	path = PluginPath.prependPlanePath(XMLFILENAME);
	if (exists(boost::filesystem::path(path))) {
		Log() << Log::Info << "Found XML file @ " << path << Log::endl;
	} else {
		path = PluginPath.prependPluginPath(XMLFILENAME);
		if (exists(boost::filesystem::path(path))) {
			Log() << Log::Info << "Found XML file @ " << path << Log::endl;
		} else {
			Log() << Log::Error << XMLFILENAME << " not found." << Log::endl;
		}
	}
	return path.c_str();
}

std::vector<std::string> XmlParser::getIpAddresses(std::string XMLFilename) {
	std::vector<std::string> IPList;
	ptree tree;
	if (XMLFilename.length()==0){
		XMLFilename= findXmlFile();
	}
//	read_xml(std::string("C:/Users/F/workspace/boost1/src/FSXPmodules.xml"), tree);
	read_xml(XMLFilename, tree);
	const ptree & dueproxies = tree.get_child("simulator", empty_ptree());
	Log() << Log::Info << "Looking for DUEPROXIES IP addresses..." << Log::endl;
	BOOST_FOREACH(const ptree::value_type &f, dueproxies) {
		std::string at = f.first + "." + ATTR_SET;
		const ptree & attributes = f.second.get_child(ATTR_SET, empty_ptree());
		std::cout << "Extracting attributes from " << at << ":" << std::endl;
		BOOST_FOREACH(const ptree::value_type &v, attributes) {
			std::cout << "First: " << v.first.data() << " Second: "	<< v.second.data() << std::endl;
			if (v.first.compare("ip")==false) {
				Log() << Log::Info << "Found DUEPROXY with IP: " << v.second.data() << Log::endl;
				IPList.push_back(v.second.data());
			}
		}
	}
	return IPList;
}

boost::property_tree::ptree& XmlParser::getDueProxyByAddress(std::string ip) {
	boost::property_tree::ptree t=empty_ptree();
	return t;
}
