#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <conio.h>
#pragma comment(lib, "Ws2_32.lib")

using namespace std;
bool connect(std::string ip, int port, SOCKET& ClientSock);
void custom_input(vector <char>& buff);

int main()
{
	WSADATA wsData;
	int erStat = WSAStartup(MAKEWORD(2, 2), &wsData);

	if (erStat != 0) {
		cout << "Error WinSock version initializaion #";
		cout << WSAGetLastError();
		return 1;
	}
	else cout << "WinSock initialization is OK" << endl;

	SOCKET ClientSock = socket(AF_INET, SOCK_DGRAM, 0);

	if (ClientSock == INVALID_SOCKET) {
		cout << "Error initialization socket # " << WSAGetLastError() << endl;
		closesocket(ClientSock);
		WSACleanup();
		return 1;
	}
	else cout << "Client socket initialization is OK" << endl;

	bool is_connected = false; //writing ip and port
	std::string ip;
	int port;
	while (!is_connected) {
		std::cout << "Enter ip: ";
		std::cin >> ip;
		std::cout << "Enter port: ";
		std::cin >> port;
		is_connected = connect(ip, port, ClientSock);
	}

	if (erStat != 0) {
		cout << "Connection to Server is FAILED. Error # " << WSAGetLastError() << endl;
		closesocket(ClientSock);
		WSACleanup();
		return 1;
	}
	else cout << "Connection established SUCCESSFULLY. Ready to send a message to Server\n";

	const int BUFF_SIZE = 1024;
	vector <char> servBuff(BUFF_SIZE), clientBuff(BUFF_SIZE);
	short packet_size = 0;		
	ofstream fout("log.txt");
	while (true) {
		cout << "Your (Client) message to Server: ";
		custom_input(clientBuff);

		if (clientBuff[0] == 'x' && clientBuff[1] == 'x' && clientBuff[2] == 'x') {
			shutdown(ClientSock, SD_BOTH);
			break;
		}

		packet_size = send(ClientSock, clientBuff.data(), clientBuff.size(), 0);
		std::time_t now = std::time(nullptr);
		std::tm localTime;
		localtime_s(&localTime, &now);
		fout << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S") << " : " << clientBuff.data() << "\n";

		if (packet_size == SOCKET_ERROR) {
			cout << "Can't send message to Server. Error # " << WSAGetLastError() << endl;
			break;
		}

		packet_size = recv(ClientSock, servBuff.data(), servBuff.size(), 0);
		now = std::time(nullptr);
		localtime_s(&localTime, &now);

		if (packet_size == SOCKET_ERROR) {
			cout << "Can't receive message from Server. Error # " << WSAGetLastError() << endl;
			break;
		}
		else {
			fout << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S") << " : " << servBuff.data() << "\n";
			cout << "Server message: " << servBuff.data() << endl;
		}
	}
	fout.close();
	closesocket(ClientSock);
	WSACleanup();
}

bool connect(std::string ip, int port, SOCKET& ClientSock) {
	char cip[100];
	strncpy_s(cip, ip.c_str(), sizeof(cip) - 1);
	cip[sizeof(cip) - 1] = '\0';

	in_addr ip_to_num;
	int erStat = inet_pton(AF_INET, cip, &ip_to_num);
	if (erStat <= 0) {
		cout << "Error in IP translation to special numeric format" << endl;
		return false;
	}

	sockaddr_in servInfo;
	ZeroMemory(&servInfo, sizeof(servInfo));

	servInfo.sin_family = AF_INET;
	servInfo.sin_addr = ip_to_num;
	servInfo.sin_port = htons(port);

	erStat = connect(ClientSock, (sockaddr*)&servInfo, sizeof(servInfo));
	if (erStat == SOCKET_ERROR) {
		int error = WSAGetLastError();
		cout << "Connection failed. Error #" << error << endl;
		return false;
	}
	return true;
}

void custom_input(vector <char>& buff) {
	int index = 0;
	while (1) {
		char ch = _getch();
		if (ch == 109) {
			printf("\n");
			break;
		}
		if (ch == 8 && index > 0) {
			buff[--index] = '\0';
			printf("\b \b");
		}
		else if (ch >= 32 && ch <= 126 && index < buff.size() - 1) {
			buff[index++] = ch;
			printf("%c", ch);
		}
	}
	buff[index] = '\0';
}