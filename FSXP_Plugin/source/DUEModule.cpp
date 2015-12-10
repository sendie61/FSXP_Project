/*
 * DUEModule.cpp
 *
 *  Created on: Dec 10, 2015
 *      Author: F
 */

#include "DUEModule.h"
#include <logwriter.h>
#include <log.h>

DUEModule::DUEModule(boost::shared_ptr<Connection> dataSocket) :
		connection(dataSocket) {
	// TODO Auto-generated constructor stub
	PPL::Log() << PPL::Log::Info << "[DUEModule::" << __FUNCTION__
			<< "] new DUEModule created (ip="
			<< dataSocket->GetSocket().remote_endpoint().address().to_string()
			<< ")" << PPL::Log::endl;
}

DUEModule::~DUEModule() {
	// TODO Auto-generated destructor stub
}

