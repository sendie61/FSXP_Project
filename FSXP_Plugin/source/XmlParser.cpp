/*
 * XmlParser.cpp
 *
 *  Created on: Mar 8, 2015
 *      Author: F
 */

#include <boost/filesystem.hpp>
#include <boost/asio/ip/address.hpp>
#include "XmlParser.h"
#include "logwriter.h"
#include "log.h"

const boost::property_tree::ptree& empty_ptree() {
	static boost::property_tree::ptree t;
	return t;
}

const char* XmlParser::findXmlFile() {
	std::string path;
	PPL::Log() << PPL::Log::Info << "Looking for " << XMLFILENAME << "..."
			<< PPL::Log::endl;
	PPL::PluginPath PluginPath;
	path = PluginPath.prependPlanePath(XMLFILENAME);
	if (exists(boost::filesystem::path(path))) {
		PPL::Log() << PPL::Log::Info << "Found XML file @ " << path
				<< PPL::Log::endl;
	} else {
		path = PluginPath.prependPluginPath(XMLFILENAME);
		if (exists(boost::filesystem::path(path))) {
			PPL::Log() << PPL::Log::Info << "Found XML file @ " << path
					<< PPL::Log::endl;
		} else {
			PPL::Log() << PPL::Log::Error << XMLFILENAME << " not found."
					<< PPL::Log::endl;
		}
	}
	return path.c_str();
}

std::vector<std::string> XmlParser::getIpAddresses(std::string XMLFilename) {
	std::vector<std::string> IPList;
	boost::property_tree::ptree tree;
	if (XMLFilename.length() == 0) {
		XMLFilename = findXmlFile();
	}
	read_xml(XMLFilename, tree);
	const boost::property_tree::ptree & simulator = tree.get_child("simulator",
			empty_ptree());
	PPL::Log() << PPL::Log::Info << "Looking for DUEPROXIES IP addresses..."
			<< PPL::Log::endl;
	BOOST_FOREACH(const boost::property_tree::ptree::value_type &f, simulator) {
		const boost::property_tree::ptree & dueproxy = f.second.get_child(
		ATTR_SET, empty_ptree());
		BOOST_FOREACH(const boost::property_tree::ptree::value_type &v, dueproxy) {
			std::cout << "First: " << v.first.data() << " Second: "
					<< v.second.data() << std::endl;
			if (v.first.compare("ip") == false) {
				PPL::Log() << PPL::Log::Info << "Found DUEPROXY with IP: "
						<< v.second.data() << PPL::Log::endl;
				IPList.push_back(v.second.data());
			}
		}
	}
	return IPList;
}

bool XmlParser::getDueProxyByAddress(std::string ip,
		boost::property_tree::ptree &dueTree, std::string XMLFilename) {
	bool rv = false;
	boost::property_tree::ptree tree;
	if (XMLFilename.length() == 0) {
		XMLFilename = findXmlFile();
	}
	read_xml(XMLFilename, tree);
	const boost::property_tree::ptree & simulator = tree.get_child("simulator",
			empty_ptree());
	PPL::Log() << PPL::Log::Info << "Looking for DUEPROXIES IP addresses..."
			<< PPL::Log::endl;
	BOOST_FOREACH(const boost::property_tree::ptree::value_type &f, simulator) {
		const boost::property_tree::ptree & dueproxy = f.second.get_child(
		ATTR_SET, empty_ptree());
		BOOST_FOREACH(const boost::property_tree::ptree::value_type &v, dueproxy) {
			std::cout << "First: " << v.first.data() << " Second: "
					<< v.second.data() << std::endl;
			if (v.first.compare("ip") == false) {
				if (v.second.data() == ip) {
					dueTree = dueproxy;
					rv = true;
					PPL::Log() << PPL::Log::Info << "Found DUEPROXY with IP: "
							<< v.second.data() << PPL::Log::endl;
				}
			}
		}
	}
	if (!rv)
		PPL::Log() << PPL::Log::Error << "Did not find DUEPROXY with IP: " << ip
				<< PPL::Log::endl;
	return rv;
}

