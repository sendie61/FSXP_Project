/*
 * ModuleAcceptor.cpp
 *
 *  Created on: Mar 1, 2015
 *      Author: F
 */

#include "ModuleAcceptor.h"

bool ModuleAcceptor::OnAccept(boost::shared_ptr<Connection> connection,
		const std::string & host, uint16_t port) {

	return true;
}

void ModuleAcceptor::OnTimer(const boost::posix_time::time_duration & delta) {
}

void ModuleAcceptor::OnError(const boost::system::error_code & error) {
}

ModuleAcceptor::ModuleAcceptor(boost::shared_ptr<Hive> hive) :
		Acceptor(hive) {

}

