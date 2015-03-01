/*
 * asio.cpp
 *
 *  Created on: Feb 26, 2015
 *      Author: F
 */

#include "asio.h"

using namespace PPL;



void WorkerThread(boost::shared_ptr<Hive> hive) {

//	while (true) {
		XPLMDebugString("FSXP_WorkerTread started.\n");
		try {
			hive->Run();
		} catch (std::exception & ex) {
			XPLMDebugString("FSXP_WorkerTread: Exception occurred!\n");
		}
		XPLMDebugString("FSXP_WorkerTread stopped.\n");
//	}
}

Asio::Asio()
		:hive(new Hive()), acceptor(new ModuleAcceptor(hive)), connection(new ModuleConnection(hive))
{
}

Asio::~Asio()
{
//	 worker_thread.join_all();
}

void Asio::init() {
	worker_thread.create_thread(boost::bind(&WorkerThread, hive));
}

void Asio::start() {
	hive->Reset();
	acceptor.reset(new ModuleAcceptor(hive));
	acceptor->Listen("0.0.0.0", 1201);
	connection.reset(new ModuleConnection(hive));
	acceptor->Accept(connection);
//		if (connection->HasError()) {
//			connection.reset(new ModuleConnection(hive));
//			acceptor->Accept(connection);
//		}

}

void Asio::stop() {
	hive->Stop();
	worker_thread.join_all();
}

void Asio::dataRefChanged(int val) {
	if (val) {
		std::string str(
				"{ \"DUEPROXY\": [{ \"-subaddr\": 1, \"IHEX\": [ \":10000000F0FFFFFF0000000000000000FFFFFFFF07\", \":10001000FFFFFFFFFFFFFFFFFEFFFFFFFFFFFFFFF1\", \":10002000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE0\", \":10003000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFD0\", \":10004006FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFBA\", \":00000001FF\" ]}]}");
		std::vector<unsigned char> data(str.begin(), str.end());
		connection->Send(data);
	} else {
		std::string str(
				"{ \"DUEPROXY\": [{ \"-subaddr\": 1, \"IHEX\": [ \":10000000F0FFFFFF0000000000000000FFFFFFFF07\", \":10001000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF1\", \":10002000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE0\", \":10003000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFD0\", \":10004006FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFBA\", \":00000001FF\" ]}]}");
		std::vector<unsigned char> data(str.begin(), str.end());
		connection->Send(data);
	}
}
