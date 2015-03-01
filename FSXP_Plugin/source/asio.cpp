/*
 * asio.cpp
 *
 *  Created on: Feb 26, 2015
 *      Author: F
 */

#include "asio.h"

using namespace PPL;

//boost::mutex global_stream_lock;

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
//	worker_thread.join_all();
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
