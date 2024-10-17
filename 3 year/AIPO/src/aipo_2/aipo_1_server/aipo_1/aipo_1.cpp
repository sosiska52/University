#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <vector>
#include <fstream>
#pragma comment(lib, "Ws2_32.lib")

int main() {
	WSADATA wsData;
	int erStat = WSAStartup(MAKEWORD(2, 2), &wsData);
	if (erStat != 0) {
		std::cout << "Error WinSock version initializaion #";
		std::cout << WSAGetLastError();
		return 1;
	}
	else std::cout << "WinSock initialization is OK\n";

	SOCKET ServSock = socket(AF_INET, SOCK_DGRAM, 0);

	if (ServSock == INVALID_SOCKET) {
		std::cout << "Error initialization socket # " << WSAGetLastError() << "\n";
		closesocket(ServSock);
		WSACleanup();
		return 1;
	}
	else std::cout << "Server socket initialization is OK\n";

	in_addr ip_to_num;
	erStat = inet_pton(AF_INET, "127.0.0.1", &ip_to_num);

	if (erStat <= 0) {
		std::cout << "Error in IP translation to special numeric format\n";
		return 1;
	}

	sockaddr_in servInfo;
	ZeroMemory(&servInfo, sizeof(servInfo));
	servInfo.sin_family = AF_INET;
	servInfo.sin_addr = ip_to_num;
	servInfo.sin_port = htons(666);

	erStat = bind(ServSock, (sockaddr*)&servInfo, sizeof(servInfo));
	if (erStat != 0) {
		std::cout << "Error Socket binding to server info. Error # " << WSAGetLastError() << "\n";
		closesocket(ServSock);
		WSACleanup();
		return 1;
	}
	else std::cout << "Binding socket to Server info is OK\n";

	erStat = listen(ServSock, SOMAXCONN);
	if (erStat != 0) {
		std::cout << "Can't start to listen to. Error # " << WSAGetLastError() << "\n";
		closesocket(ServSock);
		WSACleanup();
		return 1;
	}
	else std::cout << "Listening...\n";

	sockaddr_in clientInfo;
	ZeroMemory(&clientInfo, sizeof(clientInfo));
	int clientInfo_size = sizeof(clientInfo);
	SOCKET ClientConn = accept(ServSock, (sockaddr*)&clientInfo, &clientInfo_size);

	if (ClientConn == INVALID_SOCKET) {
		std::cout << "Client detected, but can't connect to a client. Error # " << WSAGetLastError() << "\n";
		closesocket(ServSock);
		closesocket(ClientConn);
		WSACleanup();
		return 1;
	}
	else std::cout << "Connection to a client established successfully\n";

	const short BUFF_SIZE = 1024;
	std::vector <char> servBuff(BUFF_SIZE), clientBuff(BUFF_SIZE);
	short packet_size = 0;
	bool is_saving = false;
	std::ofstream fout("save.txt");
	if (!fout.is_open()) {
		std::cout << "Can't open file. Ending session\n";
		std::string message = "Error. Can't open file";
		clientBuff.assign(message.begin(), message.end());
		packet_size = send(ClientConn, clientBuff.data(), clientBuff.size(), 0);
		shutdown(ClientConn, SD_BOTH);
		closesocket(ServSock);
		closesocket(ClientConn);
		WSACleanup();
		fout.close();
		return 1;
	}
	fout.clear();

	while (true) {
		packet_size = recv(ClientConn, servBuff.data(), servBuff.size(), 0);
		std::cout << "Client's message: " << servBuff.data() << "\n";

		if (servBuff[0] == 's' && servBuff[1] == 'a' && servBuff[2] == 'v' && servBuff[3] == 'e')
			is_saving = true;

		if (is_saving)
			fout << servBuff.data() << "\n";

		if (servBuff[0] == '#' && servBuff[1] == 'e' && servBuff[2] == 'n' && servBuff[3] == 'd' && servBuff[4] == '#' && servBuff[5] == '#') {
			std::string message = "Succesfully saved";
			clientBuff.assign(message.begin(), message.end());
			is_saving = false;
		}
		else {
			std::cout << "Your (host) message: ";
			fgets(clientBuff.data(), clientBuff.size(), stdin);
		}

		if (clientBuff[0] == 'x' && clientBuff[1] == 'x' && clientBuff[2] == 'x') {
			shutdown(ClientConn, SD_BOTH);
			break;
		}

		packet_size = send(ClientConn, clientBuff.data(), clientBuff.size(), 0);

		if (packet_size == SOCKET_ERROR) {
			std::cout << "Can't send message to Client. Error # " << WSAGetLastError() << "\n";
			break;
		}
	}
	fout.close();
	closesocket(ServSock);
	closesocket(ClientConn);
	WSACleanup();
}