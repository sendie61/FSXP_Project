/*
 * asio.h
 *
 *  Created on: Feb 26, 2015
 *      Author: F
 */

#ifndef ASIO_H_
#define ASIO_H_

#include "network.h"
#include <conio.h>
#include <boost/thread/mutex.hpp>
#include <boost/thread.hpp>


class MyConnection: public Connection {
private:
	void OnAccept(const std::string & host, uint16_t port);
	void OnConnect(const std::string & host, uint16_t port);
	void OnSend(const std::vector<uint8_t> & buffer);
	void OnRecv(std::vector<uint8_t> & buffer);
	void OnTimer(const boost::posix_time::time_duration & delta);
	void OnError(const boost::system::error_code & error);
public:
	MyConnection(boost::shared_ptr<Hive> hive);
	~MyConnection() {

	}
	;
};

class MyAcceptor: public Acceptor {
private:
	bool OnAccept(boost::shared_ptr<Connection> connection,
			const std::string & host, uint16_t port);
	void OnTimer(const boost::posix_time::time_duration & delta);
	void OnError(const boost::system::error_code & error);
public:
	MyAcceptor(boost::shared_ptr<Hive> hive);
	~MyAcceptor() {
	}
	;
};

class Asio{
public:
	Asio();

	void start();
	void stop();

private:
	boost::shared_ptr<Hive> hive;
	boost::shared_ptr<MyAcceptor> acceptor;
	boost::shared_ptr<MyConnection> connection;
	boost::thread_group worker_thread;

};

#endif /* ASIO_H_ */
