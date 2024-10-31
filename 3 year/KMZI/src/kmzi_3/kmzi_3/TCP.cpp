#include "TCP.h"

TCPServer::TCPServer(const char* ipAddr, int port) {
	int erStat = WSAStartup(MAKEWORD(2, 2), &wsData);
	if (erStat != 0) {
		std::cout << WSAGetLastError();
		throw std::runtime_error("Error WinSock version initializaion");
	}
	else std::cout << "WinSock initialization is OK\n";

	ServSock = socket(AF_INET, SOCK_STREAM, 0);

	if (ServSock == INVALID_SOCKET) {
		closesocket(ServSock);
		WSACleanup();
		throw std::runtime_error("Error initialization socket");
	}
	else std::cout << "Server socket initialization is OK\n";

	erStat = inet_pton(AF_INET, ipAddr, &ip_to_num);

	if (erStat <= 0) {
		throw std::runtime_error("Error in IP translation to special numeric format");
	}

	ZeroMemory(&servInfo, sizeof(servInfo));
	servInfo.sin_family = AF_INET;
	servInfo.sin_addr = ip_to_num;
	servInfo.sin_port = htons(port);

	erStat = bind(ServSock, (sockaddr*)&servInfo, sizeof(servInfo));
	if (erStat != 0) {
		std::cout << WSAGetLastError() << "\n";
		closesocket(ServSock);
		WSACleanup(); 
		throw std::runtime_error("Error Socket binding to server info");
	}
	else std::cout << "Binding socket to Server info is OK\n";
}

TCPServer::~TCPServer() {
	closesocket(ServSock);
	closesocket(ClientConn);
	WSACleanup();
}

bool TCPServer::connectClient() {
	int erStat = listen(ServSock, SOMAXCONN);
	if (erStat != 0) {
		std::cout << WSAGetLastError() << "\n";
		closesocket(ServSock);
		WSACleanup();
		std::runtime_error("Can't start to listen to");
		return false;
	}
	else std::cout << "Listening...\n";

	ZeroMemory(&clientInfo, sizeof(clientInfo));
	int clientInfo_size = sizeof(clientInfo);
	ClientConn = accept(ServSock, (sockaddr*)&clientInfo, &clientInfo_size);

	if (ClientConn == INVALID_SOCKET) {
		std::cout << WSAGetLastError() << "\n";
		closesocket(ServSock);
		closesocket(ClientConn);
		WSACleanup();
		return false;
		std::runtime_error("Client detected, but can't connect to a client. Error # ");
	}
	else std::cout << "Connection to a client established successfully\n";

	servBuff = std::pair<std::vector<char>, std::vector<char>>(std::vector<char>(BUFF_SIZE), std::vector<char>(BUFF_SIZE));
	clientBuff = std::pair<std::vector<char>, std::vector<char>>(std::vector<char>(BUFF_SIZE), std::vector<char>(BUFF_SIZE));
	short packet_size = 0;
	return true;
}


TCPClient::TCPClient() {
	int erStat = WSAStartup(MAKEWORD(2, 2), &wsData);

	if (erStat != 0) {
		std::cout << WSAGetLastError();
		throw std::runtime_error("Error WinSock version initializaion");
	}
	else std::cout << "WinSock initialization is OK\n";

	ClientSock = socket(AF_INET, SOCK_STREAM, 0);

	if (ClientSock == INVALID_SOCKET) {
		std::cout << WSAGetLastError();
		closesocket(ClientSock);
		WSACleanup();
		throw std::runtime_error("Error initialization socket");
	}
	else std::cout << "Client socket initialization is OK\n";
}

TCPClient::~TCPClient() {
	closesocket(ClientSock);
	WSACleanup();
}

bool TCPClient::connectServer(const char* ipAddr, int port) {
	in_addr ip_to_num;
	int erStat = inet_pton(AF_INET, ipAddr, &ip_to_num);
	if (erStat <= 0) {
		std::cout << "Error in IP translation to special numeric format\n";
		return false;
	}

	sockaddr_in servInfo;
	ZeroMemory(&servInfo, sizeof(servInfo));

	servInfo.sin_family = AF_INET;
	servInfo.sin_addr = ip_to_num;
	servInfo.sin_port = htons(port);

	erStat = connect(ClientSock, (sockaddr*)&servInfo, sizeof(servInfo));
	if (erStat == SOCKET_ERROR) {
		std::cout << "Connection failed. Error #" << WSAGetLastError();
		return false;
	}
	return true;
}