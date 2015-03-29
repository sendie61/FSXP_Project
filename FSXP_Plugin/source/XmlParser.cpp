/*
 * XmlParser.cpp
 *
 *  Created on: Mar 8, 2015
 *      Author: F
 */

#include "XmlParser.h"

const ptree& empty_ptree(){
    static ptree t;
    return t;
}

const char* XmlParser::findXmlFile() {
	std::string path;
	try{
		path= PluginPath.prependPlanePath(XMLFILENAME);
		std::cout << path << std::endl;
	}catch( ...){
		try{
			path= PluginPath.prependPluginResourcesPath(XMLFILENAME);
			std::cout << path << std::endl;
		}catch( ...){
			std::cout << "failed:" << std::endl;
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
	BOOST_FOREACH(const ptree::value_type &f, dueproxies) {
		std::string at = f.first + "." + ATTR_SET;
		const ptree & attributes = f.second.get_child(ATTR_SET, empty_ptree());
		std::cout << "Extracting attributes from " << at << ":" << std::endl;
		BOOST_FOREACH(const ptree::value_type &v, attributes) {
			std::cout << "First: " << v.first.data() << " Second: "	<< v.second.data() << std::endl;
			if (v.first.compare("ip")==false) {
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
