/*
 * DUEModule.h
 *
 *  Created on: Dec 10, 2015
 *      Author: F
 */

#include "ModuleConnection.h"

#ifndef DUEMODULE_H_
#define DUEMODULE_H_

class DUEModule {
public:
	DUEModule(boost::shared_ptr<Connection> dataSocket);
	virtual ~DUEModule();

private:
	/**
	 * @brief the data connection
	 * got from ModuleAcceptor::OnAccept
	 */
	boost::shared_ptr<Connection> connection;

};

#endif /* DUEMODULE_H_ */
