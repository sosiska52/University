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
void custom_input(vector<char>& buff, int buff_size);

int main() {
    WSADATA wsData;
    int erStat = WSAStartup(MAKEWORD(2, 2), &wsData);

    if (erStat != 0) {
        cout << "Error WinSock version initialization #" << WSAGetLastError() << endl;
        return 1;
    }
    cout << "WinSock initialization is OK" << endl;

    SOCKET ClientSock;
    ClientSock = socket(AF_INET, SOCK_DGRAM, 0);
    if (ClientSock == INVALID_SOCKET) {
        cout << "Error initializing socket # " << WSAGetLastError() << endl;
        return 1;
    }
    cout << "Client socket initialization is OK" << endl;

    std::string ip;
    int port;
    sockaddr_in servInfo;
    while (true) {
        cout << "Enter IP: ";
        cin >> ip;
        cout << "Enter port: ";
        cin >> port;

        ZeroMemory(&servInfo, sizeof(servInfo));
        servInfo.sin_family = AF_INET;
        inet_pton(AF_INET, ip.c_str(), &servInfo.sin_addr);
        servInfo.sin_port = htons(port);

        vector<char> testBuff(1);
        testBuff[0] = 't';
        if (sendto(ClientSock, testBuff.data(), testBuff.size(), 0, (sockaddr*)&servInfo, sizeof(servInfo)) != SOCKET_ERROR) {
            break;
        }
        else cout << "Connection failed. Please try again." << endl;
    }

    cout << "Connection established SUCCESSFULLY. Ready to send a message to Server\n";

    const int BUFF_SIZE = 1024;
    vector<char> servBuff(BUFF_SIZE), clientBuff(BUFF_SIZE);
    ofstream fout("log.txt");

    while (true) {
        cout << "Your (Client) message to Server: ";
        custom_input(clientBuff, BUFF_SIZE);

        if (clientBuff[0] == 'x' && clientBuff[1] == 'x' && clientBuff[2] == 'x') {
            break;
        }

        short packet_size = sendto(ClientSock, clientBuff.data(), strlen(clientBuff.data()), 0, (sockaddr*)&servInfo, sizeof(servInfo));
        std::time_t now = std::time(nullptr);
        std::tm localTime;
        localtime_s(&localTime, &now);
        fout << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S") << " : " << clientBuff.data() << "\n";

        if (packet_size == SOCKET_ERROR) {
            cout << "Can't send message to Server. Error # " << WSAGetLastError() << endl;
        }

        sockaddr_in from;
        int fromLen = sizeof(from);
        packet_size = recvfrom(ClientSock, servBuff.data(), servBuff.size(), 0, (sockaddr*)&from, &fromLen);
        now = std::time(nullptr);
        localtime_s(&localTime, &now);

        if (packet_size == SOCKET_ERROR) {
            cout << "Can't receive message from Server. Error # " << WSAGetLastError() << endl;
        }
        else {
            servBuff[packet_size] = '\0';
            fout << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S") << " : " << servBuff.data() << "\n";
            cout << "Server message: " << servBuff.data() << endl;
        }
    }

    fout.close();
    closesocket(ClientSock);
    WSACleanup();
}

void custom_input(vector<char>& buff, int buff_size) {
    int index = 0;
    while (true) {
        char ch = _getch();
        if (ch == 109) {  
            printf("\n");
            break;
        }
        if (ch == 8 && index > 0) {
            buff[--index] = '\0';
            printf("\b \b");
        }
        else if (ch >= 32 && ch <= 126 && index < buff_size - 1) {
            buff[index++] = ch;
            printf("%c", ch);
        }
    }
    buff[index] = '\0';
}