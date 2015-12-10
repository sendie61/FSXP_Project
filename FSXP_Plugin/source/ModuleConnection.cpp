/*
 * ModuleConnection.cpp
 *
 *  Created on: Mar 1, 2015
 *      Author: F
 */

#include "ModuleConnection.h"
#include <logwriter.h>
#include <log.h>

void ModuleConnection::OnAccept(const std::string & host, uint16_t port) {
	PPL::Log() << PPL::Log::Info << "[ModuleConnection::" << __FUNCTION__
			<< "] " << "Connection with " << host << " on port:" << port
			<< " Accepted." << PPL::Log::endl;

	// Start the next receive
	Recv();
}

void ModuleConnection::OnConnect(const std::string & host, uint16_t port) {
	PPL::Log() << PPL::Log::Info << "[ModuleConnection::" << __FUNCTION__
			<< "] " << "Connected with " << host << " on port:" << port
			<< PPL::Log::endl;

	// Start the next receive
	Recv();
}

void ModuleConnection::OnSend(const std::vector<uint8_t> & buffer) {
}

void ModuleConnection::OnRecv(std::vector<uint8_t> & buffer) {

	// Start the next receive
	Recv();

	// Echo the data back
	Send(buffer);
}

void ModuleConnection::OnTimer(const boost::posix_time::time_duration & delta) {
}

void ModuleConnection::OnError(const boost::system::error_code & error) {
	PPL::Log() << PPL::Log::Info << "[ModuleConnection::" << __FUNCTION__
			<< "] " << error.message() << PPL::Log::endl;
}

ModuleConnection::ModuleConnection(boost::shared_ptr<Hive> hive) :
		Connection(hive) {
}
