#pragma once
#include "TCP.h"
#include "ShnorDigitalSignature.h"
class Host
{
public: 
	void establishServer(const char* ip, int port);
	bool establishConnection();
	void exchangeInfo();
	bool signMessage(const std::string& message, std::string& signature);
private:
	TCPServer tcpData;
	ShnorDigitalSignature DSA;
};

class Client {
public:
	void establishServer();
	bool establishConnection(const char* ip, int port);
	void exchangeInfo();
	bool signMessage();
private:
	TCPClient tcpData;
	ShnorDigitalSignature DSA;
};