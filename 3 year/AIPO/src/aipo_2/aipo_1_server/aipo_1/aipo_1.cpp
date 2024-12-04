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
        std::cout << "Error WinSock version initialization #" << WSAGetLastError() << "\n";
        return 1;
    }
    std::cout << "WinSock initialization is OK\n";

    SOCKET ServSock = socket(AF_INET, SOCK_DGRAM, 0);
    if (ServSock == INVALID_SOCKET) {
        std::cout << "Error initializing socket # " << WSAGetLastError() << "\n";
        WSACleanup();
        return 1;
    }
    std::cout << "Server socket initialization is OK\n";

    sockaddr_in servInfo;
    ZeroMemory(&servInfo, sizeof(servInfo));
    servInfo.sin_family = AF_INET;

    erStat = inet_pton(AF_INET, "127.168.0.1", &servInfo.sin_addr);
    if (erStat <= 0) {
        std::cout << "Error in IP translation to special numeric format\n";
        closesocket(ServSock);
        WSACleanup();
        return 1;
    }

    servInfo.sin_port = htons(666);

    erStat = bind(ServSock, (sockaddr*)&servInfo, sizeof(servInfo));
    if (erStat != 0) {
        std::cout << "Error binding socket to server info. Error # " << WSAGetLastError() << "\n";
        closesocket(ServSock);
        WSACleanup();
        return 1;
    }
    std::cout << "Binding socket to Server info is OK\n";

    sockaddr_in clientInfo;
    int clientInfo_size = sizeof(clientInfo);
    const short BUFF_SIZE = 1024;
    std::vector<char> servBuff(BUFF_SIZE), clientBuff(BUFF_SIZE);
    bool is_saving = false;
    std::ofstream fout("save.txt");

    if (!fout.is_open()) {
        std::cout << "Can't open file. Ending session\n";
        std::string message = "Error. Can't open file";
        sendto(ServSock, message.c_str(), message.size(), 0, (sockaddr*)&clientInfo, clientInfo_size);
        closesocket(ServSock);
        WSACleanup();
        return 1;
    }
    fout.clear();

    std::cout << "...\n";
    while (true) {
        int packet_size = recvfrom(ServSock, servBuff.data(), servBuff.size(), 0, (sockaddr*)&clientInfo, &clientInfo_size);
        if (packet_size == SOCKET_ERROR) {
            std::cout << "Error receiving data. Error # " << WSAGetLastError() << "\n";
            break;
        }
        servBuff[packet_size] = '\0';
        std::cout << "Client's message: " << servBuff.data() << "\n";

        if (strncmp(servBuff.data(), "save", 4) == 0)
            is_saving = true;

        if (is_saving)
            fout << servBuff.data() << "\n";

        if (strncmp(servBuff.data(), "#end##", 6) == 0) {
            std::string message = "Successfully saved";
            sendto(ServSock, message.c_str(), message.size(), 0, (sockaddr*)&clientInfo, clientInfo_size);
            is_saving = false;
        }
        else {
            std::cout << "Your (host) message: ";
            fgets(clientBuff.data(), clientBuff.size(), stdin);
            if (strncmp(clientBuff.data(), "xxx", 3) == 0) {
                break;
            }
            sendto(ServSock, clientBuff.data(), strlen(clientBuff.data()), 0, (sockaddr*)&clientInfo, clientInfo_size);
        }
    }

    fout.close();
    closesocket(ServSock);
    WSACleanup();
}