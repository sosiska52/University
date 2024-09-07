#include <iostream>
#include <WinSock2.h>
#include <stdexcept>
#include <system_error>

class WinsockCL {
private:
	WSADATA wsaData{};
public:
	WinsockCL() {
		const int startupResult = WSAStartup(WINSOCK_VERSION, &wsaData);
		if (startupResult) {
			throw std::system_error(startupResult, std::system_category());
		}
	}

	~WinsockCL() {
		const int cleanupResult = WSACleanup();
	}
};

int main()
{
	WinsockCL winsock;
	return 0;
}