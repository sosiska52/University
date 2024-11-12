#include <iostream>
#include "SafeConnection.h"

int main()
{/*
	Client client;
	client.establishServer();
	client.establishConnection("127.168.0.1", 666);
	client.exchangeInfo();
	if (client.signMessage())
		std::cout << "Success\n";
	else
		std::cout << "Something went wrong\n";*/
	std::string msg = "hello";
	ShnorDigitalSignature dsa;
	std::pair<unsigned long long, unsigned long long> sign = dsa.sign(msg);
	if (dsa.verify(sign, msg))
		std::cout << "Signature: e = " << sign.first << ", y = " << sign.second << "\n";
}