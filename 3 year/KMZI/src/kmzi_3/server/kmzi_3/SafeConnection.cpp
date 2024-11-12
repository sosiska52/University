#include "SafeConnection.h"

void Host::establishServer(const char* ip, int port) {
	tcpData.initialise(ip, port);
}

bool Host::establishConnection() {
	return tcpData.connectClient();
}

void Host::exchangeInfo() {
	if (tcpData.sendMessage(std::to_string(DSA.p)))
		if (tcpData.sendMessage(std::to_string(DSA.q)))
			if (tcpData.sendMessage(std::to_string(DSA.a)))
				if (tcpData.sendMessage(std::to_string(DSA.v))) {
					std::cout << "Info exchanged\n";
					return;
				}
	tcpData.abbort();
}

bool Host::signMessage(const std::string& message, std::string& signature) {
	if(!tcpData.sendMessage(message)){
		tcpData.abbort();
		return false;
	}

	std::pair<unsigned long long, unsigned long long> sign;
	std::string temp;
	temp.resize(1024);
	if (tcpData.receiveMessage(temp)) {
		signature = temp;
		sign.first = std::stoull(temp);
		if (tcpData.receiveMessage(temp)) {
			sign.second = std::stoull(temp);
			if (DSA.verify(sign, message)) {
				signature += temp;
				return true;
			}
		}
	}
	tcpData.abbort();
	return false;
}

////////////////////////

void Client::establishServer() {
	tcpData.initialise();
}

bool Client::establishConnection(const char* ip, int port) {
	return tcpData.connectServer(ip, port);
}

void Client::exchangeInfo() {
	std::string temp;
	temp.resize(1024);
	if (tcpData.receiveMessage(temp))
	{
		DSA.p = std::stoull(temp);
		if (tcpData.receiveMessage(temp))
		{
			DSA.q = std::stoull(temp);
			if (tcpData.receiveMessage(temp))
			{
				DSA.a = std::stoull(temp);
				if (tcpData.receiveMessage(temp)) {
					DSA.v = std::stoull(temp);
					std::cout << "Info exchanged\n";
					return;
				}
			}
		}
	}
	tcpData.abbort();
}

bool Client::signMessage() {
	std::string message;
	message.resize(1024);
	if (!tcpData.receiveMessage(message)) {
		tcpData.abbort();
		return false;
	}

	std::pair <unsigned long long, unsigned long long> sign;
	sign = DSA.sign(message);
	if (tcpData.sendMessage(std::to_string(sign.first))) {
		if (tcpData.sendMessage(std::to_string(sign.second))) {
			return true;
		}
	}
	tcpData.abbort();
	return false;
}