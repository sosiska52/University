#include <iostream>
#include "SafeConnection.h"

int main()
{
	Host host;
	host.establishServer("127.168.0.1", 666);
	host.establishConnection();
	host.exchangeInfo();
	std::string msg = "Messege to sign";
	msg.resize(1024);
	std::string signature;
	if (host.signMessage(msg, signature))
		std::cout << "Signature: " << signature << "\n";
	else
		std::cout << "Something went wrong\n";
}