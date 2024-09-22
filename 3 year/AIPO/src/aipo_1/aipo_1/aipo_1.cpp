#include <iostream>
#include <WinSock2.h>
#include <Windows.h>
#include <stdexcept>
#include <system_error>

#define MY_PORT 666

DWORD WINAPI WorkWithClient(LPVOID client_socket);

int nclients = 0;

class WinsockLib {
private:
	WSADATA wsaData{};
public:
	WinsockLib() {
		const int startupResult = WSAStartup(WINSOCK_VERSION, &wsaData);
		if (startupResult) 
			throw std::system_error(startupResult, std::system_category());
	}

	~WinsockLib() {
		const int cleanupResult = WSACleanup();
	}
};

class myWinSock {
public:
	SOCKET mySocket;

	myWinSock() {
		mySocket = socket(AF_INET, SOCK_STREAM, 0);
		if (mySocket < 0) 
			throw std::system_error(mySocket, std::system_category());
	}

	~myWinSock() {
		closesocket(mySocket);
	}
};

int main()
{
	try {
		WinsockLib winsock;
		char buff[1024];
		std::cout << "SERVER DEMO\n";

		myWinSock mWS;
		sockaddr_in local_addr{};
		local_addr.sin_family = AF_INET;
		local_addr.sin_port = htons(MY_PORT);
		local_addr.sin_addr.S_un.S_addr = 0;

		const int bindRes = bind(mWS.mySocket, (sockaddr*)&local_addr, sizeof(local_addr));
		if (bindRes) 
			throw std::system_error(bindRes, std::system_category());

		const int listenRes = listen(mWS.mySocket, 0x100);
		if (listenRes)
			throw std::system_error(listenRes, std::system_category());

		SOCKET client_socket;
		sockaddr_in client_addr;
		int client_addr_size = sizeof(client_addr);
		while (client_socket = accept(mWS.mySocket, (sockaddr*)&client_addr, &client_addr_size)) {
			nclients++;
			HOSTENT* hst;
			hst = gethostbyaddr((char*)&client_addr.sin_addr.S_un.S_addr, 4, AF_INET);
			printf("+%s [%s] new connect!\n",(hst) ? hst-> h_name:"",inet_ntoa(client_addr.sin_addr));
			//PRINTNUSERS
			DWORD thID;
			CreateThread(NULL, NULL, WorkWithClient, &client_socket, NULL, &thID);
		}
	}
	catch (std::system_error& e) {
		std::cerr << "Initialization error: " << e.what() << " (error code: " << e.code() << ")" << std::endl;
		return EXIT_FAILURE;

	}
	return EXIT_SUCCESS;
}

DWORD WINAPI WorkWithClient(LPVOID client_socket) {
	SOCKET my_sock;
	my_sock = ((SOCKET*)client_socket)[0];
	char buff[20 * 1024];
#define sHELLO "Hello, Student!\r\n";
}