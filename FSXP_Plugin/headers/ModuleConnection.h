/*
 * ModuleConnection.h
 *
 *  Created on: Mar 1, 2015
 *      Author: F
 */

#ifndef MODULECONNECTION_H_
#define MODULECONNECTION_H_

#include <network.h>

class ModuleConnection: public Connection {
private:
	void OnAccept(const std::string & host, uint16_t port);
	void OnConnect(const std::string & host, uint16_t port);
	void OnSend(const std::vector<uint8_t> & buffer);
	void OnRecv(std::vector<uint8_t> & buffer);
	void OnTimer(const boost::posix_time::time_duration & delta);
	void OnError(const boost::system::error_code & error);
public:
	ModuleConnection(boost::shared_ptr<Hive> hive);
	~ModuleConnection() {};
};


#endif /* MODULECONNECTION_H_ */
