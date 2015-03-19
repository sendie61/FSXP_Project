/*
 * XmlParser.cpp
 *
 *  Created on: Mar 8, 2015
 *      Author: F
 */

#include "XmlParser.h"

const boost::property_tree::ptree& empty_ptree(){
    static boost::property_tree::ptree t;
    return t;
}

const char* XmlParser::findXmlFile() {
	std::string path;
	try{
		path= PluginPath.prependPlanePath(XMLFILENAME);
		std::cout << path << std::endl;
	}catch( ...){
		std::cout << "failed:" << std::endl;
	}
	return path.c_str();
}

std::vector<std::string> XmlParser::getIpAddresses() {
	std::vector<std::string> a;
	return a;
}

boost::property_tree::ptree& XmlParser::getDueProxyByAddress(std::string ip) {
	boost::property_tree::ptree t=empty_ptree();
	return t;
}
