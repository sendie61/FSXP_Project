/*
 * ModuleAcceptor.cpp
 *
 *  Created on: Mar 1, 2015
 *      Author: F
 */

#include "XmlParser.h"
#include <logwriter.h>
#include <log.h>
#include <ModuleManager.h>

ModuleManager::ModuleManager(boost::shared_ptr<Hive> hive) :
		Acceptor(hive) {
}

bool ModuleManager::OnAccept(boost::shared_ptr<Connection> connection,
		const std::string & host, uint16_t port) {

	//Should we accept this client? (based on IP-address)
	if (AcceptConnection(connection)) {
		PPL::Log() << PPL::Log::Info << "[ModuleAcceptor::" << __FUNCTION__
				<< "]  Connection with " << host << " Accepted."
				<< PPL::Log::endl;

		// go ahead accept another connection
		boost::shared_ptr<ModuleConnection> new_connection(
				new ModuleConnection(GetHive()));
		this->Accept(new_connection);
		return true;

	} else {
		PPL::Log() << PPL::Log::Info << "[ModuleAcceptor::" << __FUNCTION__
				<< "] Connection with " << host << " Denied." << PPL::Log::endl;
		connection->Disconnect();

		// go ahead accept another connection
		connection.reset(new ModuleConnection(GetHive())); // reuse the connection
		this->Accept(connection);
		return false;
	}
}

void ModuleManager::OnTimer(const boost::posix_time::time_duration & delta) {
}

void ModuleManager::OnError(const boost::system::error_code & error) {
	PPL::Log() << PPL::Log::Info << "[ModuleAcceptor::" << __FUNCTION__ << "] "
			<< error.message() << PPL::Log::endl;
}

bool ModuleManager::AcceptConnection(
		boost::shared_ptr<Connection> connection) {
	XmlParser XmlParser;
	XmlParser.findXmlFile();
	vector<string> ModuleIPs = XmlParser.getIpAddresses(
			XmlParser.findXmlFile());

	std::string clientAddress =
			connection->GetSocket().remote_endpoint().address().to_string();
	for (string ip : ModuleIPs) {
		if (ip == clientAddress)
			return true;
	}
	return false;
}
