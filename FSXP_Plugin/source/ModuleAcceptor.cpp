/*
 * ModuleAcceptor.cpp
 *
 *  Created on: Mar 1, 2015
 *      Author: F
 */

#include "ModuleAcceptor.h"
#include "XmlParser.h"
#include <logwriter.h>
#include <log.h>

ModuleAcceptor::ModuleAcceptor(boost::shared_ptr<Hive> hive) :
		Acceptor(hive) {

// read the xml, filter the IP addresses to know which one to accept.
}

bool ModuleAcceptor::OnAccept(boost::shared_ptr<Connection> connection,
		const std::string & host, uint16_t port) {

	if (AcceptConnection(connection)){
		PPL::Log() << PPL::Log::Info << "ModuleAcceptor::OnAccept: Connection with "<< host << " Accepted." << PPL::Log::endl;
		return true;
	}
	else{
		connection->Disconnect();
		PPL::Log() << PPL::Log::Info << "ModuleAcceptor::OnAccept: Connection with "<< host << " Denied." << PPL::Log::endl;
		return false;
	}
}

void ModuleAcceptor::OnTimer(const boost::posix_time::time_duration & delta) {
}

void ModuleAcceptor::OnError(const boost::system::error_code & error) {
	PPL::Log() << PPL::Log::Info << "ModuleAcceptor::OnError: " << error.message() << PPL::Log::endl;
}

bool ModuleAcceptor::AcceptConnection(boost::shared_ptr<Connection> connection){
	XmlParser XmlParser;
	XmlParser.findXmlFile();
    ModuleIPs= XmlParser.getIpAddresses(XmlParser.findXmlFile());

	std::string clientAddress= connection->GetSocket().remote_endpoint().address().to_string();
	for(string ip: ModuleIPs){
		if (ip == clientAddress)
			return true;
	}
	return false;
}
