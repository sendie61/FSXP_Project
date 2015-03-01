/*
 * ModuleConnection.cpp
 *
 *  Created on: Mar 1, 2015
 *      Author: F
 */

#include "ModuleConnection.h"

void ModuleConnection::OnAccept(const std::string & host, uint16_t port) {

	// Start the next receive
	Recv();
}

void ModuleConnection::OnConnect(const std::string & host, uint16_t port) {

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
}

ModuleConnection::ModuleConnection(boost::shared_ptr<Hive> hive) :
		Connection(hive) {
}
