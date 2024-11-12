#pragma once
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <vector>
#include <stdexcept>
#pragma comment(lib, "Ws2_32.lib")
class TCPServer {
public:
	void initialise(const char* ipAddr, int port);
	~TCPServer();
	bool connectClient();
	bool sendMessage(const std::string& message);
	bool receiveMessage(std::string& message);
	void abbort();
private:
	WSADATA wsData;
	SOCKET ServSock;
	in_addr ip_to_num;
	sockaddr_in servInfo;
	sockaddr_in clientInfo;
	SOCKET ClientConn;
	const short BUFF_SIZE = 1024;
	std::pair <std::vector<char>, std::vector<char>> servBuff, clientBuff;
};

class TCPClient {
public:
	void initialise();
	~TCPClient();
	bool connectServer(const char* ipAddr, int port);
	bool sendMessage(const std::string& message);
	bool receiveMessage(std::string& message);
	void abbort();
private:
	WSADATA wsData;
	SOCKET ClientSock;
	in_addr ip_to_num;
	const short BUFF_SIZE = 1024;
	std::pair <std::vector<char>, std::vector<char>> servBuff, clientBuff;
};