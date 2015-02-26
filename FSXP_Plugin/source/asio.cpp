/*
 * asio.cpp
 *
 *  Created on: Feb 26, 2015
 *      Author: F
 */

#include "asio.h"

boost::mutex global_stream_lock;

void MyConnection::OnAccept(const std::string & host, uint16_t port) {
	global_stream_lock.lock();
	std::cout << "[" << __FUNCTION__ << "] " << host << ":" << port
			<< std::endl;
	global_stream_lock.unlock();

	// Start the next receive
	Recv();
}

void MyConnection::OnConnect(const std::string & host, uint16_t port) {
	global_stream_lock.lock();
	std::cout << "[" << __FUNCTION__ << "] " << host << ":" << port
			<< std::endl;
	global_stream_lock.unlock();

	// Start the next receive
	Recv();
}

void MyConnection::OnSend(const std::vector<uint8_t> & buffer) {
	global_stream_lock.lock();
	std::cout << "[" << __FUNCTION__ << "] " << buffer.size() << " bytes"
			<< std::endl;
	for (size_t x = 0; x < buffer.size(); ++x) {
		std::cout << std::hex << std::setfill('0') << std::setw(2)
				<< (int) buffer[x] << " ";
		if ((x + 1) % 16 == 0) {
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
	global_stream_lock.unlock();
}

void MyConnection::OnRecv(std::vector<uint8_t> & buffer) {
	global_stream_lock.lock();
	std::cout << "[" << __FUNCTION__ << "] " << buffer.size() << " bytes"
			<< std::endl;
	for (size_t x = 0; x < buffer.size(); ++x) {
		std::cout << std::hex << std::setfill('0') << std::setw(2)
				<< (int) buffer[x] << " ";
		if ((x + 1) % 16 == 0) {
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
	global_stream_lock.unlock();

	// Start the next receive
	Recv();

	// Echo the data back
	Send(buffer);
}

void MyConnection::OnTimer(const boost::posix_time::time_duration & delta) {
	global_stream_lock.lock();
	std::cout << "[" << __FUNCTION__ << "] " << delta << std::endl;
	global_stream_lock.unlock();
}

void MyConnection::OnError(const boost::system::error_code & error) {
	global_stream_lock.lock();
	std::cout << "[" << __FUNCTION__ << "] " << error << std::endl;
	global_stream_lock.unlock();
}

MyConnection::MyConnection(boost::shared_ptr<Hive> hive) :
		Connection(hive) {
}

bool MyAcceptor::OnAccept(boost::shared_ptr<Connection> connection,
		const std::string & host, uint16_t port) {
	global_stream_lock.lock();
	std::cout << "MyAcceptor::[" << __FUNCTION__ << "] " << host << ":" << port
			<< std::endl;
	global_stream_lock.unlock();

	return true;
}

void MyAcceptor::OnTimer(const boost::posix_time::time_duration & delta) {
	global_stream_lock.lock();
	std::cout << "MyAcceptor::[" << __FUNCTION__ << "] " << delta << std::endl;
	global_stream_lock.unlock();
}

void MyAcceptor::OnError(const boost::system::error_code & error) {
	global_stream_lock.lock();
	std::cout << "MyAcceptor::[" << __FUNCTION__ << "] " << error << std::endl;
	global_stream_lock.unlock();
}

MyAcceptor::MyAcceptor(boost::shared_ptr<Hive> hive) :
		Acceptor(hive) {
}

void WorkerThread(boost::shared_ptr<Hive> hive) {
	global_stream_lock.lock();
	std::cout << "[" << boost::this_thread::get_id() << "] Thread Start"
			<< std::endl;
	global_stream_lock.unlock();

	while (true) {
		try {
			hive->Run();
		} catch (std::exception & ex) {
			global_stream_lock.lock();
			std::cout << "[" << boost::this_thread::get_id() << "] Exception: "
					<< ex.what() << std::endl;
			global_stream_lock.unlock();
		}
	}

	global_stream_lock.lock();
	std::cout << "[" << boost::this_thread::get_id() << "] Thread Finish"
			<< std::endl;
	global_stream_lock.unlock();

}

Asio::Asio() :
		hive(new Hive()), acceptor(new MyAcceptor(hive)), connection(new MyConnection(hive)) {
	acceptor->Listen("0.0.0.0", 1201);

	worker_thread.create_thread(boost::bind(&WorkerThread, hive));
}

void Asio::start() {


	acceptor->Accept(connection);
//	acceptor->Accept( connection2 );
//	acceptor->Accept( connection3 );

	while (!_kbhit()) {
//		hive->Poll();
		Sleep(3000);
		global_stream_lock.lock();
		std::cout << "." << std::endl;
		global_stream_lock.unlock();
		if (connection->HasError()) {
			connection.reset(new MyConnection(hive));
			acceptor->Accept(connection);
		}
	}
	hive->Stop();

}

